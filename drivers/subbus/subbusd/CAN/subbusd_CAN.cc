// #undef HAVE_CAN_H
#include <string.h>
#ifdef HAVE_CAN_H
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#endif
#include "nl_assert.h"
#include "subbusd_int.h"
#include "subbusd_CAN.h"

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
  uint8_t device_id, addr;
  
  switch ( req->sbhdr.command ) {
    case SBC_READACK:
      frame.can_id = (req->data.d1.data >> 8) & 0xFF;
      frame.data[0] = CAN_CMD_CODE_RD;
      frame.data[1] = 1;
      frame.data[2] = req->data.d1.data & 0xFF;
      frame.can_dlc = 3;
      flavor->enqueue_request(&frame, (uint8_t*)&rep.data.value, 2, this);
      break;
    case SBC_MREAD:
      // Setup necessary preconditions, then call processing function
      // Need to decode this and enqueue multiple requests
      // enqueue_sbreq(device_id, req->data.d4.multread_cmd,
      //              req->data.d4.n_reads);
      return status_return(SBS_NOT_IMPLEMENTED);
    case SBC_WRITEACK:
      frame.can_id = (req->data.d0.address >> 8) & 0xFF;
      frame.data[0] = CAN_CMD_CODE_WR_INC;
      frame.data[1] = 3;
      frame.data[2] = req->data.d0.address & 0xFF;
      frame.data[3] = req->data.d0.data & 0xFF;
      frame.data[4] = (req->data.d0.data >> 8) & 0xFF;
      frame.can_dlc = 5;
      flavor->enqueue_request(&frame, 0, 0, this);
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
  if (status < 0) {
    status_return(status);
    return;
  }
  rep.hdr.status = status;
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
    case SBRT_CAP:  // Capabilities: We should not see this here
    default:
      report_err("%s: Invalid ret_type %d in request_complete", iname, rep.hdr.ret_type);
      status_return(SBS_REQ_SYNTAX);
      break;
  }
}

CAN_socket::CAN_socket()
  : DAS_IO::Interface("if_CAN", sizeof(struct can_frame)),
    request_pending(false) {}

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
  // interface: "CAN0"
  addr.can_family = PF_CAN;
  strcpy(ifr.ifr_name, "CAN0");
  if (ioctl(fd, SIOCGIFINDEX, &ifr)) { error }
  addr.can_ifindex = ifr.ifr_ifindex;
  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { error }
  filter.can_id = CAN_ID_REPLY_BIT;
  filter.can_mask = CAN_ID_REPLY_BIT;
  if (setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER, &filter,
      sizeof(struct can_filter)) != 0) { error }
  // Also want to receive error packets
  can_err_mask_t err_mask = (CAN_ERR_TX_TIMEOUT | CAN_ERR_LOSTARB |
      CAN_ERR_CRTL | CAN_ERR_PROT | CAN_ERR_TRX | CAN_ERR_ACK |
      CAN_ERR_BUSOFF | CAN_ERR_BUSERROR);
  if (setsockopt(s, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask,
    sizeof(err_mask)) != 0) { error }
  flags = DAS_IO::Interface::Fl_Read;
  #endif
}

bool CAN_socket::protocol_input() {
  struct can_frame *frame = (struct can_frame*)&buf[0];
  // reassemble response as necessary
  if (nc != sizeof(struct can_frame)) {
    msg(0, "%s: read %d, expected %d with can_dlc=%d",
      iname, nc, CAN_MTU, frame->can_dlc);
  }
  if (!request_pending) {
    report_err("%s: Unexpected input", iname);
    consume(nc);
    return false;
  }
  nl_assert(!reqs.empty());
  can_request request = reqs.front();
  // check for CAN error frame
  if (frame->can_id & (CAN_EFF_FLAG|CAN_RTR_FLAG)) {
    report_err("%s: Unexpected packet type: ID:%08X", iname, frame->can_id);
    consume(nc);
    return false;
  }
  if (frame->can_id & CAN_ERR_FLAG) {
    char msgbuf[80];
    int nc = snprintf(&msgbuf[0], 80, "ErrFrame ID:%8X DLC:%d",
      frame->can_id, frame->can_dlc);
    for (int i = 0; i < frame->can_dlc; ++i) {
      nc += snprintf(&msgbuf[nc], 80-nc, " %02X", frame->data[i]);
    }
    report_err("%s", msgbuf);
    consume(nc);
    return false;
  }
  // check incoming ID with request
  if ((frame->can_id & CAN_ID_BDREQ_MASK) !=
      ((request.frame->can_id & CAN_ID_BDREQ_MASK) | CAN_ID_REPLY_BIT)) {
    report_err("%s: Invalid ID: %X, expected %X", iname,
      frame->can_id, request.frame->can_id | CAN_ID_REPLY_BIT);
    consume(nc);
    return false;
  }
  // check incoming cmd with request
  // check incoming seq with req_seq_no
  if (frame->can_dlc < 2) {
    report_err("%s: DLC:%d (<2)", iname, frame->can_dlc);
    consume(nc);
    return false;
  }
  if (frame->data[0] != CAN_CMD(request.frame->data[0],rep_seq_no)) {
    if (CAN_CMD_CODE(frame->data[0]) == CAN_CMD_CODE_ERROR) {
      if (frame->data[1] == CAN_ERR_NACK) {
        request.clt->request_complete(SBS_NOACK, request.bufsz);
      } else {
        report_err("%s: CAN_ERR %d", iname, frame->data[1]);
        request.clt->request_complete(SBS_RESP_ERROR, 0);
      }
    } else {
      report_err("%s: req/rep cmd,seq mismatch: %02X/%02X",
        iname, frame->data[0], request.frame->data[0]);
    }
    consume(nc);
    return false;
  }
  // if seq == 0, check len with request and update
  int nbdat = frame->can_dlc - 1; // not counting cmd byte
  uint8_t *data = &frame->data[1];
  if (CAN_CMD_SEQ(frame->data[0]) == 0) {
    rep_len = frame->data[1];
    if (rep_len > request.bufsz) {
      report_err("%s: reply length %d exceeds request len %d",
        iname, rep_len, request.bufsz);
      consume(nc);
      return false;
    }
    if (rep_len < request.bufsz)
      request.bufsz = rep_len;
    --nbdat;
    ++data;
  }
  // check dlc_len against remaining request len
  if (nbdat > request.bufsz) {
    report_err("%s: msg overflow. cmdseq=%02X dlc=%d bufsz=%d",
      iname, frame->data[0], frame->can_dlc, request.bufsz);
    consume(nc);
    return false;
  }
  // copy data into reply
  memcpy(request.buf, data, nbdat);
  request.buf += nbdat;
  request.bufsz -= nbdat;
  // update rep_seq_no
  ++rep_seq_no;
  // If request is complete, call clt->request_complete
  if (request.bufsz == 0) {
    request.clt->request_complete(SBS_ACK, rep_len);
  }
  consume(nc);
  return false;
}

void CAN_socket::enqueue_request(struct can_frame *frame, uint8_t *rep_buf, int buflen,
        subbusd_CAN_client *clt) {
  nl_assert(frame);
  nl_assert(frame->can_dlc <= 8);
  reqs.push_back(can_request(frame, rep_buf, buflen, clt));
  process_requests();
}

/**
 * This code currently assumes that all outbound requests will fit in a single
 * packet. 
 */
void CAN_socket::process_requests() {
  if (request_pending) return;
  can_request req = reqs.front();
  request_pending = true;
  req.frame->can_id = (req.frame->can_id & CAN_ID_BOARD_MASK) | CAN_ID_REQID(req_no);
  ++req_no;
  rep_seq_no = 0;
  #ifdef HAVE_LINUX_CAN_H
    iwrite(fd, req.frame, sizeof(struct can_frame));
  #else
  { char msgbuf[80];
    int nc = 0;
    nc += snprintf(&msgbuf[nc], 80-nc, "CANout ID:x%02X Data:", req.frame->can_id);
    for (int i = 0; i < req.frame->can_dlc; ++i) {
      nc += snprintf(&msgbuf[nc], 80-nc, " %02X", req.frame->data[i]);
    }
    msg(0, "%s", msgbuf);
    for (int i = 0; i < req.bufsz; ++i)
      req.buf[i] = i;
    req.clt->request_complete(SBS_ACK, req.bufsz);
    reqs.pop_front();
    request_pending = false;
    ++req_no;
  }
  #endif
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
