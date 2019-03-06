// #undef HAVE_CAN_H
#include <string.h>
#include "subbusd_CAN_config.h"
#ifdef HAVE_LINUX_CAN_H
  #include <sys/ioctl.h>
  #include <sys/socket.h>
  #include <linux/can.h>
  #include <linux/can/raw.h>
  #include <linux/can/error.h>
  #include <net/if.h>
#endif
#include "nl_assert.h"
#include "subbusd_int.h"
#include "subbusd_CAN.h"
#include "dasio/ascii_escape.h"

using namespace DAS_IO;

subbusd_CAN_client::subbusd_CAN_client(DAS_IO::Authenticator *auth, subbusd_CAN *fl)
    : subbusd_client(auth), flavor(fl) {}
subbusd_CAN_client::~subbusd_CAN_client() {}

Serverside_client *new_subbusd_CAN_client(Authenticator *auth, SubService *ss) {
  ss = ss; // not interested
  subbusd_CAN_client *clt =
    new subbusd_CAN_client(auth, (subbusd_CAN*)ss->svc_data);
  return clt;
}

/*
 * setup reply structure, along with maximum reply size,
 * bytes read. The reply size obviously depends on the command,
 * as does where returned data is reported in the reply.
 */
bool subbusd_CAN_client::incoming_sbreq() {
  int rv, rsize;
  //uint8_t device_id, addr;
  req = (subbusd_req_t *)&buf[0];
  
  switch ( req->sbhdr.command ) {
    case SBC_READACK:
      rep.hdr.ret_type = SBRT_US;
      can_msg.device_id = (req->data.d1.data >> 8) & 0xFF;
      can_msg.sb_can_cmd = CAN_CMD_CODE_RD;
      can_msg.sb_can_seq = 0;
      can_msg.sb_nb = 1;
      can_msg.sb_can[0] = req->data.d1.data & 0xFF;
      can_msg.end_of_request = true;
      flavor->enqueue_request(&can_msg, (uint8_t*)&rep.data.value, 2, this);
      break;
    case SBC_MREAD:
      // Setup necessary preconditions, then call processing function
      // Need to decode this and enqueue multiple requests
      // enqueue_sbreq(device_id, req->data.d4.multread_cmd,
      //              req->data.d4.n_reads);
      setup_mread();
      break;
    case SBC_WRITEACK:
      rep.hdr.ret_type = SBRT_NONE;
      can_msg.device_id = (req->data.d0.address >> 8) & 0xFF;
      can_msg.sb_can_cmd = CAN_CMD_CODE_WR_INC;
      can_msg.sb_can_seq = 0;
      can_msg.sb_nb = 3;
      can_msg.sb_can[0] = req->data.d0.address & 0xFF;
      can_msg.sb_can[1] = req->data.d0.data & 0xFF;
      can_msg.sb_can[2] = (req->data.d0.data >> 8) & 0xFF;
      can_msg.end_of_request = true;
      flavor->enqueue_request(&can_msg, 0, 0, this);
      break;
    case SBC_GETCAPS:
      rep.hdr.status = SBS_OK;
      rep.hdr.ret_type = SBRT_CAP;
      rep.data.capabilities.subfunc = 11; // CAN Driver, defined in Evernote
      rep.data.capabilities.features = 0; // Really none!
      strncpy(rep.data.capabilities.name, SUBBUSD_CAN_NAME, SUBBUS_NAME_MAX);
      return iwrite((const char *)&rep, sizeof(rep));
    case SBC_QUIT:
      status_return(SBS_OK);
      return true; // Is this sufficient?
    default:
      return status_return(SBS_NOT_IMPLEMENTED);
  }
  return false;
}

void subbusd_CAN_client::request_complete(int16_t status, uint16_t n_bytes) {
  rep.hdr.status = status;
  if (status < 0) {
    status_return(status);
    return;
  }
  if (n_bytes & 1) {
    msg(1, "%s: request_complete: n_bytes is odd: %d",
      iname, n_bytes);
  }
  switch (rep.hdr.ret_type) {
    case SBRT_NONE:
      if (n_bytes > 0) {
        report_err("%s: Excess data for SBRT_NONE, nb=%d", iname, n_bytes);
      } else report_ok();
      iwrite((const char *)&rep, sizeof(subbusd_rep_hdr_t));
      break;
    case SBRT_US: // Return unsigned short value
      if (n_bytes != 2) {
        report_err("%s: Expected 2 bytes, received %d", n_bytes);
      } else report_ok();
      iwrite((const char*)&rep, sizeof(subbusd_rep_hdr_t)+2);
      break;
    case SBRT_MREAD: // Multi-Read
    case SBRT_MREADACK: // Multi-Read w/ACK
      if (n_bytes > mread_word_space_remaining*2) {
        report_err("%s: Overrun on mread. n_bytes=%d words_remaining=%d",
          n_bytes, mread_word_space_remaining);
        status_return(SBS_RESP_ERROR);
        return;
      }
      rep.data.mread.n_reads += n_bytes/2;
      if (buf[cp] == '\n') {
        iwrite((const char*)&rep,
          sizeof(subbusd_rep_hdr_t)+2+2*rep.data.mread.n_reads);
        report_ok();
      } else {
        process_mread();
      }
      break;
    case SBRT_CAP:  // Capabilities: We should not see this here
    default:
      report_err("%s: Invalid ret_type %d in request_complete", iname, rep.hdr.ret_type);
      status_return(SBS_REQ_SYNTAX);
      break;
  }
}

void subbusd_CAN_client::setup_mread() {
  cp = ((unsigned char*)&req->data.d4.multread_cmd) - (&buf[0]);
  if (not_str("M") ||
      not_hex(mread_word_space_remaining) ||
      not_str("#")) {
    status_return(SBS_REQ_SYNTAX);
    return;
  }
  if (mread_word_space_remaining != req->data.d4.n_reads) {
    msg(1, "setup_mread() M%X# != n_reads %X",
      mread_word_space_remaining, req->data.d4.n_reads);
  }
  rep.hdr.ret_type = SBRT_MREAD;
  rep.data.mread.n_reads = 0;
  process_mread();
}

/**
 * On entry, buf[cp] should point to [0-9a-fA-F] (start) or ',' (continue)
 * '\n' is also a possibility, but I am handling that in request_complete()
 */
void subbusd_CAN_client::process_mread() {
  uint16_t arg1, arg2, arg3;
  if (rep.data.mread.n_reads > 0 && cp < nc && buf[cp] == ',') {
    ++cp;
  }
  if (not_hex(arg1)) {
    if (cp >= nc)
      report_err("%s: Truncated mread?", iname);
    status_return(SBS_REQ_SYNTAX);
    return;
  }
  switch (buf[cp]) {
    case ',':
      can_msg.sb_can_cmd = CAN_CMD_CODE_RD;
      can_msg.sb_can_seq = 0;
      can_msg.device_id = (arg1>>8) & 0xFF;
      can_msg.sb_can[0] = arg1&0xFF;
      can_msg.sb_nb = 1;
      format_mread_rd();
      break;
    case ':':
      ++cp;
      if (not_hex(arg2) || not_str(":") || not_hex(arg3) || cp >= nc) {
        if (cp >= nc)
          report_err("%s: Truncated mread?", iname);
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      if (arg3 < arg1 || (arg3&0xFF00) != (arg1&0xFF00)) {
        report_err("%s: Invalid RD_INC %X:1:%X", iname, arg1, arg3);
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      if (arg2 == 1) {
        uint8_t count = (arg3-arg1)+1;
        // setup CAN_CMD_CODE_RD_INC
        can_msg.sb_can_cmd = CAN_CMD_CODE_RD_INC;
        can_msg.sb_can_seq = 0;
        can_msg.device_id = (arg1>>8) & 0xFF;
        can_msg.sb_nb = 2;
        can_msg.sb_can[0] = count; // count
        can_msg.sb_can[1] = arg1 & 0xFF;
        can_msg.end_of_request = (buf[cp] == '\n');
        flavor->enqueue_request(&can_msg,
          (uint8_t*)&rep.data.mread.rvals[rep.data.mread.n_reads],
          count*2, this);
      } else {
        // setup CAN_CMD_CODE_RD and unwind
        can_msg.sb_can_cmd = CAN_CMD_CODE_RD;
        can_msg.sb_can_seq = 0;
        can_msg.device_id = (arg1>>8) & 0xFF;
        can_msg.sb_nb = 0;
        for ( ; arg1 <= arg3; arg1 += arg2) {
          can_msg.sb_can[can_msg.sb_nb] = arg1 & 0xFF;
          ++can_msg.sb_nb;
        }
        format_mread_rd();
        break;
      }
      break;
    case '@':
      ++cp;
      if (arg1 > 255) {
        report_err("%s: Invalid count %d in @", iname, arg1);
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      if (not_hex(arg2) || cp >= nc) {
        if (cp >= nc) report_err("%s: Truncated mread? '%s'", iname,
          ::ascii_escape((const char *)req->data.d4.multread_cmd));
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      can_msg.device_id = (arg2>>8) & 0xFF;
      can_msg.sb_can_cmd = CAN_CMD_CODE_RD_NOINC;
      can_msg.sb_can_seq = 0;
      can_msg.sb_can[0] = arg1&0xFF;
      can_msg.sb_can[1] = arg2&0xFF;
      can_msg.sb_nb = 2;
      can_msg.end_of_request = (buf[cp] == '\n');
      flavor->enqueue_request(&can_msg,
          (uint8_t*)&rep.data.mread.rvals[rep.data.mread.n_reads],
          arg1*2, this);
      break;
    case '|':
      ++cp;
      if (not_hex(arg2) || not_str("@") ||
          not_hex(arg3) || cp >= nc) {
        if (cp >= nc) report_err("%s: Truncated mread? '%s'", iname,
          ::ascii_escape(req->data.d4.multread_cmd));
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      if (arg2 > 255) {
        report_err("%s: Invalid count %d in |@", iname, arg2);
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      if ((arg3&0xFF00) != (arg1&0xFF00)) {
        report_err(
          "%s: Invalid RdAddrNoInc %X|%X@%X to multiple devices.",
          iname, arg1, arg3);
        status_return(SBS_REQ_SYNTAX);
        return;
      }
      can_msg.device_id = (arg1>>8) & 0xFF;
      can_msg.sb_can_cmd = CAN_CMD_CODE_RD_CNT_NOINC;
      can_msg.sb_can_seq = 0;
      can_msg.sb_can[0] = arg1&0xFF;
      can_msg.sb_can[1] = arg2&0xFF;
      can_msg.sb_can[2] = arg3&0xFF;
      can_msg.sb_nb = 3;
      can_msg.end_of_request = (buf[cp] == '\n');
      flavor->enqueue_request(&can_msg,
          (uint8_t*)&rep.data.mread.rvals[rep.data.mread.n_reads],
          2+arg2*2, this);
      break;
    case '\n':
      msg(4, "%s: '\\n' should have been handled", iname);
  }
}

/**
 * On entry, buf[cp] should either point to '\n' or ','
 * I use while(){switch() { }} with both 'continue' and 'break' statements
 * inside the switch. A break inside the switch will hit the break outside
 * the switch and exit the while loop. A continue inside the switch will
 * skip the break and go to the next iteration step.
 */
void subbusd_CAN_client::format_mread_rd() {
  uint16_t arg1, arg2, arg3;
  nl_assert(cp < nc);
  while (cp < nc && buf[cp] == ',') {
    unsigned int cp_sav = cp++;
    if (not_hex(arg1)) {
      if (cp >= nc)
        report_err("%s: Truncated mread?", iname);
      status_return(SBS_REQ_SYNTAX);
      return;
    }
    switch (buf[cp]) {
      case '\n':
      case ',':
        if (((arg1>>8)&0xFF) != can_msg.device_id) {
          cp = cp_sav;
          break;
        }
        can_msg.sb_can[can_msg.sb_nb++] = arg1&0xFF;
        continue;
      case ':':
        ++cp;
        if (not_hex(arg2) || not_str(":") || not_hex(arg3) || cp >= nc) {
          if (cp >= nc)
            report_err("%s: Truncated mread?", iname);
          status_return(SBS_REQ_SYNTAX);
          return;
        }
        if (arg3 < arg1 || (arg3&0xFF00) != (arg1&0xFF00)) {
          report_err("%s: Invalid RD_INC %X:1:%X", iname, arg1, arg3);
          status_return(SBS_REQ_SYNTAX);
          return;
        }
        if (((arg1>>8)&0xFF) != can_msg.device_id || arg2 == 1) {
          cp = cp_sav;
          break;
        }
        // setup CAN_CMD_CODE_RD and unwind
        for ( ; arg1 <= arg3; arg1 += arg2) {
          can_msg.sb_can[can_msg.sb_nb] = arg1 & 0xFF;
          ++can_msg.sb_nb;
        }
        continue;
      default:
        cp = cp_sav;
        break;
    }
    break;
  }
  can_msg.end_of_request = (buf[cp] == '\n');
  flavor->enqueue_request(&can_msg,
    (uint8_t*)&rep.data.mread.rvals[rep.data.mread.n_reads],
    can_msg.sb_nb*2, this);
}

CAN_socket::CAN_socket()
  : DAS_IO::Interface("if_CAN", CAN_MTU+1),
    request_pending(false)
    #ifndef HAVE_LINUX_CAN_H
    , bytectr(0)
    #endif
    {}

CAN_socket::~CAN_socket() {}

void CAN_socket::setup() {
  #ifdef HAVE_LINUX_CAN_H
  struct sockaddr_can addr;
  struct can_filter filter;
  struct ifreq ifr;
	// * family: PF_CAN
	// * type: SOCK_RAW
	// * proto: CAN_RAW
  fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (fd < 0) {
    msg(3, "%s: socket() returned error %d: %s",
      errno, strerror(errno));
  }
  // interface: "CAN0"
  addr.can_family = PF_CAN;
  strcpy(ifr.ifr_name, "can0");
  if (ioctl(fd, SIOCGIFINDEX, &ifr)) {
    msg(3, "%s: ioctl() error %d: %s", iname,
      errno, strerror(errno));
  }
  addr.can_ifindex = ifr.ifr_ifindex;
  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    msg(3, "%s: bind() error %d: %s",
      errno, strerror(errno));
  }
  filter.can_id = CAN_ID_REPLY_BIT;
  filter.can_mask = CAN_ID_REPLY_BIT;
  if (setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER, &filter,
      sizeof(struct can_filter)) != 0) {
    msg(3, "%s: setsockopt() error %d setting filter: %s",
      errno, strerror(errno));
  }
  // Also want to receive error packets
  can_err_mask_t err_mask = (CAN_ERR_TX_TIMEOUT | CAN_ERR_LOSTARB |
      CAN_ERR_CRTL | CAN_ERR_PROT | CAN_ERR_TRX | CAN_ERR_ACK |
      CAN_ERR_BUSOFF | CAN_ERR_BUSERROR);
  if (setsockopt(fd, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask,
        sizeof(err_mask)) != 0) {
    msg(3, "%s: setsockopt() error %d setting error filter: %s",
      errno, strerror(errno));
  }
  flags = DAS_IO::Interface::Fl_Read;
  #endif
}

bool CAN_socket::iwritten(int nb) {
  if (obuf_empty()) process_requests();
}

const char *CAN_socket::ascii_escape() {
  static char abuf[128];
  unsigned int anc = 0;
  for (unsigned lcp = 0; lcp < nc; lcp += CAN_MTU) {
    struct can_frame *repfrm = (struct can_frame*)&buf[lcp];
    unsigned int nb = nc-lcp;
    if (nb < CAN_MTU)
      anc += snprintf(&abuf[anc], 128-anc-1, "Short(%d):", nb);
    unsigned int dlc_offset = (&(repfrm->can_dlc) - &buf[lcp]);
    if (nb >= dlc_offset) {
      anc += snprintf(&abuf[anc], 128-anc-1, " ID:%02X", repfrm->can_id);
      if (nb > dlc_offset) {
        unsigned dlc = repfrm->can_dlc;
        anc += snprintf(&abuf[anc], 128-anc-1, " DLC:%u%s",
          dlc, dlc>8 ? "!" : "");
        if (dlc > 8) dlc = 8;
        unsigned int data_offset =
          (&(repfrm->data[0]) - &buf[lcp]);
        if (nb > data_offset) {
          if (nb < data_offset+dlc)
            dlc = nb-data_offset;
          anc += snprintf(&abuf[anc], 128-anc-1, " [");
          for (int i = 0; i < dlc; ++i) {
            anc += snprintf(&abuf[anc], 128-anc-1, "%s%02X",
              i ? " " : "", repfrm->data[i]);
          }
          anc += snprintf(&abuf[anc], 128-anc-1, "]");
          if (nb > CAN_MTU) {
            anc += snprintf(&abuf[anc], 128-anc-1, "\n");
          }
        }
      }
    } else {
      anc += snprintf(&abuf[anc], 128-anc-1, "[");
      for (int i = 0; i < nb; ++i) {
        anc += snprintf(&abuf[anc], 128-anc-1, "%s%02X",
          i ? " " : "", buf[lcp+i]);
      }
      anc += snprintf(&abuf[anc], 128-anc-1, "]");
    }
  }
  return abuf;
}

bool CAN_socket::protocol_input() {
  struct can_frame *repfrm = (struct can_frame*)&buf[0];
  // reassemble response as necessary
  if (nc != CAN_MTU) {
    msg(0, "%s: read %d, expected %d with can_dlc=%d",
      iname, nc, CAN_MTU, repfrm->can_dlc);
    // This could happen if the frame is shortened with less data
  }
  if (!request_pending) {
    report_err("%s: Unexpected input", iname);
    consume(nc);
    return false;
  }
  nl_assert(!reqs.empty());
  can_request request = reqs.front();
  // check for CAN error frame
  if (repfrm->can_id & (CAN_EFF_FLAG|CAN_RTR_FLAG)) {
    report_err("%s: Unexpected packet type: ID:%08X", iname, repfrm->can_id);
    consume(nc);
    return false;
  }
  if (repfrm->can_id & CAN_ERR_FLAG) {
    char msgbuf[80];
    int nc = snprintf(&msgbuf[0], 80, "ErrFrame ID:%8X DLC:%d",
      repfrm->can_id, repfrm->can_dlc);
    for (int i = 0; i < repfrm->can_dlc; ++i) {
      nc += snprintf(&msgbuf[nc], 80-nc, " %02X", repfrm->data[i]);
    }
    report_err("%s", msgbuf);
    consume(nc);
    return false;
  }
  // check incoming ID with request
  if ((repfrm->can_id & CAN_SFF_MASK) !=
      ((reqfrm.can_id & CAN_SFF_MASK) | CAN_ID_REPLY_BIT)) {
    report_err("%s: Invalid ID: %X, expected %X", iname,
      repfrm->can_id, reqfrm.can_id | CAN_ID_REPLY_BIT);
    consume(nc);
    return false;
  }
  // check incoming cmd with request
  // check incoming seq with req_seq_no
  if (repfrm->can_dlc < 2) {
    report_err("%s: DLC:%d (<2)", iname, repfrm->can_dlc);
    consume(nc);
    return false;
  }
  if (repfrm->data[0] != CAN_CMD(reqfrm.data[0],rep_seq_no)) {
    if (CAN_CMD_CODE(repfrm->data[0]) == CAN_CMD_CODE_ERROR) {
      if (repfrm->data[1] == CAN_ERR_NACK) {
        request.clt->request_complete(SBS_NOACK, rep_recd);
      } else {
        report_err("%s: CAN_ERR %d", iname, repfrm->data[1]);
        request.clt->request_complete(SBS_RESP_ERROR, 0);
      }
    } else {
      report_err("%s: req/rep cmd,seq mismatch: %02X/%02X",
        iname, repfrm->data[0], reqfrm.data[0]);
    }
    consume(nc);
    return false;
  }
  // if seq == 0, check len with request and update
  int nbdat = repfrm->can_dlc - 1; // not counting cmd byte
  uint8_t *data = &repfrm->data[1];
  if (CAN_CMD_SEQ(repfrm->data[0]) == 0) {
    rep_len = repfrm->data[1];
    if (rep_len > request.msg->bufsz) {
      report_err("%s: reply length %d exceeds request len %d",
        iname, rep_len, request.msg->bufsz);
      consume(nc);
      return false;
    }
    --nbdat;
    ++data;
    msg(MSG_DBG(2), "rep_recd: %d", rep_recd);
  }
  // check dlc_len against remaining request len
  if (rep_recd + nbdat > rep_len) {
    report_err("%s: msg overflow. cmdseq=%02X dlc=%d rep_len=%d",
      iname, repfrm->data[0], repfrm->can_dlc, rep_len);
    consume(nc);
    return false;
  }
  if (nl_debug_level <= MSG_DBG(1)) {
    msg(MSG_DBG(1), "CANin %s", ascii_escape());
  }
  
  // copy data into reply
  memcpy(request.msg->buf, data, nbdat);
  request.msg->buf += nbdat;
  rep_recd += nbdat;
  msg(MSG_DBG(2), "Seq:%d nbdat:%d recd:%d rep_len:%d",
    rep_seq_no, nbdat, rep_recd, rep_len);
  // update rep_seq_no
  ++rep_seq_no;
  consume(nc);
  // If request is complete, call clt->request_complete
  if (rep_recd == rep_len) {
    reqs.pop_front();
    // clearing request_pending after request_complete()
    // simply limits the depth of recursion
    request.clt->request_complete(SBS_ACK, rep_len);
    request_pending = false;
    process_requests();
  }
  return false;
}

void CAN_socket::enqueue_request(can_msg_t *can_msg, uint8_t *rep_buf, int buflen,
        subbusd_CAN_client *clt) {
  nl_assert(can_msg);
  reqs.push_back(can_request(can_msg, rep_buf, buflen, clt));
  process_requests();
}

/**
 * Called
 *  - When a new request has been enqueued
 *  - When a previous request has been completed
 *  - When the current request's output has been flushed and more
 *    may be required (req.msg->sb_can_seq > 0)
 */
void CAN_socket::process_requests() {
  if (request_pending || request_processing || reqs.empty()) return;
  can_request req = reqs.front();
  request_processing = true;
  while (!request_pending && obuf_empty()) {
    uint8_t req_seq_no = req.msg->sb_can_seq;
    uint16_t offset = req_seq_no ? (req_seq_no*7 - 1) : 0;
    nl_assert(offset < req.msg->sb_nb);
    uint16_t nbdata = req.msg->sb_nb - offset;
    reqfrm.can_id = CAN_REQUEST_ID(req.msg->device_id,req_no);
    if (req.msg->sb_can_seq) {
      if (nbdata > 7) nbdata = 7;
      reqfrm.can_dlc = nbdata+1;
      reqfrm.data[0] = CAN_CMD(req.msg->sb_can_cmd,req.msg->sb_can_seq);
      memcpy(&reqfrm.data[1], &req.msg->sb_can[offset], nbdata);
    } else {
      rep_recd = 0;
      if (nbdata > 6) nbdata = 6;
      reqfrm.can_dlc = nbdata+2;
      reqfrm.data[0] = CAN_CMD(req.msg->sb_can_cmd,req_seq_no);
      reqfrm.data[1] = req.msg->sb_nb;
      memcpy(&reqfrm.data[2], &req.msg->sb_can[offset], nbdata);
    }
    ++req.msg->sb_can_seq;
    if (offset+nbdata >= req.msg->sb_nb) {
      request_pending = true;
      ++req_no;
    }
    rep_seq_no = 0;
    if (nl_debug_level <= MSG_DBG(1)) {
      char msgbuf[80];
      int nc = 0;
      nc += snprintf(&msgbuf[nc], 80-nc, "CANout ID:x%02X Data:", reqfrm.can_id);
      for (int i = 0; i < reqfrm.can_dlc; ++i) {
        nc += snprintf(&msgbuf[nc], 80-nc, " %02X", reqfrm.data[i]);
      }
      msg(MSG_DBG(1), "%s", msgbuf);
    }
    #ifdef HAVE_LINUX_CAN_H
      iwrite((const char *)&reqfrm, CAN_MTU);
    #else
      // This is development/debugging code
      if (request_pending) {
        for (int i = 0; i < req.msg->bufsz; ++i) {
          req.msg->buf[i] = bytectr++;
        }
        request_pending = false;
        reqs.pop_front();
        request_processing = false; // this is a hack
        req.clt->request_complete(SBS_ACK, req.msg->bufsz);
        break;
      }
    #endif
  }
  request_processing = false;
}

subbusd_CAN::subbusd_CAN() : subbusd_flavor("CAN", new_subbusd_CAN_client) {}
subbusd_CAN::~subbusd_CAN() {}

void subbusd_CAN::init_subbus() {
  // setup socket
  CAN = new CAN_socket();
  CAN->setup();
  subbusd_core::subbusd->srvr.ELoop.add_child(CAN);
}

void subbusd_CAN::shutdown_subbus() {
  // teardown socket
  subbusd_core::subbusd->srvr.ELoop.delete_child(CAN);
  CAN = 0;
}

void subbusd_CAN_init_options(int argc, char **argv) {
  argc = argc;
  argv = argv;
  subbusd_CAN *CAN = new subbusd_CAN();
  nl_assert(subbusd_core::subbusd);
  subbusd_core::subbusd->register_flavor(CAN);
}
