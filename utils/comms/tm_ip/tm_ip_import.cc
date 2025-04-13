/** @file tm_ip_import.cc
 */
#include <cstring>
#include "tm_ip_import.h"
#include "crc16modbus.h"
#include "dasio/server.h"
#include "dasio/cmd_writer.h"
#include "dasio/tm.h"
#include "dasio/appid.h"
#include "dasio/ascii_escape.h"
#include "dasio/serio_pkt.h"
#include "nl.h"
#include "oui.h"

ipi_relay::ipi_relay(const char *iname)
      : Interface(iname, 0),
        mlf_packet_logger(iname, mlf_base, mlf_config)
{
}

ipi_relay *ipi_relay::instance;
const char *ipi_relay::mlf_base = "TMIPI";
const char *ipi_relay::mlf_config;

ipi_relay *ipi_relay::get_instance()
{
  if (!instance) {
    instance = new ipi_relay("relay");
  }
  return instance;
}

bool ipi_relay::forward(const unsigned char *hdr, uint16_t len)
{
  // serio_pkt_hdr *shdr = (serio_pkt_hdr *)hdr;
  // uint16_t len = shdr->length + serio::pkt_hdr_size;
  log_packet(hdr, len);
  // Now forward to any Clients
  return false;
}


/**
 * ipi_cmd_in connects to the local command txsrvr to receive commands,
 * then forwards them to ipi_cmd_out.
 */
ipi_cmd_in::ipi_cmd_in(const char *iname)
    : Cmd_reader("cmd_in", 256, "cmd_tx")
{
  set_retries(-1, 10, 10, false); // Never stop trying
}

bool ipi_cmd_in::app_input() {
  // msg(MSG, "Received command '%s'", buf);
  if (strcmp((char*)buf, "Q\n") == 0) {
    report_ok(nc);
    return true;
  } else {
    ipi_cmd_out::cond_send_cmd(buf, nc);
    report_ok(nc);
  }
  return false;
}

/***************
 * ipi_cmd_out
 */
ipi_cmd_out::ipi_cmd_out(Authenticator *auth, const char *iname)
    : Serverside_client(auth, iname, 2000),
      relay(ipi_relay::get_instance()),
      bytes_received(0),
      bytes_acknowledged(0),
      bytes_unacknowledged(0)
{
  set_obufsize(2048);
}

void ipi_cmd_out::attach(Server *srvr, const char *service) {
  srvr->add_subservice(new SubService(service, new_ipi_cmd_out, 0));
}

bool ipi_cmd_out::cond_send_cmd(uint8_t *buf, unsigned int nc) {
  if (cmd_out) {
    return cmd_out->send_serio_pkt(buf, nc);
  } else {
    msg(MSG_WARN, "ipi_cmd_out: No connection: cmd dropped: %s", buf);
    ++cmds_dropped;
  }
  return false;
}

ipi_cmd_out *ipi_cmd_out::cmd_out = 0;
int ipi_cmd_out::cmds_dropped = 0;

Serverside_client *ipi_cmd_out::new_ipi_cmd_out(
            Authenticator *Auth, SubService *SS) {
  return new ipi_cmd_out(Auth, Auth->get_client_app());
}

bool ipi_cmd_out::send_serio_pkt(uint8_t *xbuf, unsigned int xnc) {
  // We have allocated an obuf, so we can use auto vars for
  // io and hdr
  struct iovec io[2];
  serio_pkt_hdr hdr;
  hdr.LRC = 0;
  hdr.type = pkt_type_CMD;
  hdr.length = xnc;
  io[0].iov_len = sizeof(serio_pkt_hdr);
  io[0].iov_base = &hdr;
  io[1].iov_len = xnc;
  io[1].iov_base = (void *)xbuf;
  // Calculate the CRC of io[1]
  { unsigned CRC = crc16modbus_word(0,0,0);
    CRC = crc16modbus_word(CRC, io[1].iov_base, io[1].iov_len);
    hdr.CRC = CRC;
    uint8_t *hdrp = (uint8_t *)io[0].iov_base;
    for (uint32_t i = 1; i < io[0].iov_len; ++i) {
      hdr.LRC += hdrp[i];
    }
    hdr.LRC = -hdr.LRC;
  }
  return iwritev(io,2);
}

ipi_cmd_out::~ipi_cmd_out()
{
  if (bytes_received || bytes_acknowledged || bytes_unacknowledged)
  {
    msg(MSG, "%s: Disconnected bytes_rec'd: %u ack'd: %u unack'd: %u",
      bytes_received, bytes_acknowledged, bytes_unacknowledged);
  }
}

bool ipi_cmd_out::connected() {
  if (cmd_out) {
    cmd_out->close();
  }
  cmd_out = this;
  msg(0, "%s: Connection established, flags=0x%X", iname, flags);
  return false;
}

void ipi_cmd_out::close() {
  cmd_out = 0;
  Serverside_client::close();
  msg(0, "%s: Connection closed", iname);
}

bool ipi_cmd_out::protocol_input() {
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;

  while (cp < nc)
  {
    msg(MSG_DBG(1), "%s: protocol_input cp:%u nc:%u",
      iname, cp, nc);
    if (not_serio_pkt(have_hdr, type, length, payload))
      break;
    msg(MSG_DBG(1), "%s: serio_pkt('%c', %u)",
      iname, type, length);
    uint16_t pkt_len = serio::pkt_hdr_size + length;
    relay->forward(&buf[cp], pkt_len);
    bytes_received += pkt_len;
    cp += pkt_len;
  }
  bytes_unacknowledged = bytes_received - bytes_acknowledged;
  msg(MSG_DBG(1), "%s: bytes rec'd: %u ack'd: %u unack'd: %u",
    iname, bytes_received, bytes_acknowledged, bytes_unacknowledged);
  if (bytes_unacknowledged > 2000 && obuf_empty())
    send_ACK(bytes_unacknowledged);
  report_ok(cp);
  return false;
}

void ipi_cmd_out::send_ACK(uint16_t nbytes)
{
  if (obuf_empty())
  {
    serio_ctrl_packet pkt;
    pkt.ctrl.subtype = ctrl_subtype_ACK;
    pkt.ctrl.reserved = 0;
    pkt.ctrl.length = nbytes;
    send_serio_pkt((uint8_t*)&pkt.ctrl, sizeof(pkt.ctrl));
    bytes_acknowledged += nbytes;
    bytes_unacknowledged = bytes_received - bytes_acknowledged;
    msg(MSG_DBG(1), "%s: ACK(%u) total rec'd: %u ack'd: %u",
      iname, nbytes, bytes_received, bytes_acknowledged);
  } else {
    msg(MSG_ERROR, "%s: !obuf_empty() in send_ACK", iname);
  }
}

/********
 * ipi_tm_in
 * Receives telemetry and/or photos via UDP and forwards them
 * to ipi_tm_out to send to serin
 */
ipi_tm_in::ipi_tm_in(ipi_tm_out *tm_out)
    : Socket("tm_in", "Relay", "ip_ex", 1500, UDP_READ),
      tm_out(tm_out),
      buffer_dumped(false),
      relay(ipi_relay::get_instance())
{
  load_tmdac(".");
  set_qerr_threshold(20);
}

ipi_tm_in::~ipi_tm_in() {
}

bool ipi_tm_in::protocol_input() {
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;
  
  /* We are receiving UDP data and we require all serio packets
   * to be entirely contained within a UDP packet, and our buffer
   * will be large enough to receive an entire UDP packet. Therefore
   * we will never have a partial serio packet in our buffer. If
   * we don't find a packet in the buffer, we should discard the
   * entire buffer and wait for the next UDP packet.
   *
   * This logic does not apply when reading from a TCP stream,
   * e.g. in serin.
   */
  buffer_dumped = false;
  while (cp < nc) {
    if (not_serio_pkt(have_hdr, type, length, payload)) {
      if (nc > cp) {
        report_err("%s: discarding %d bytes: no valid packet",
          iname, nc-cp);
      }
      consume(nc);
      return false;
    } else {
      switch (type) {
        case pkt_type_TM:
          if (length != tm_info.tm.nbminf-2) {
            report_err("%s: Invalid TM packet length length %d",
              iname, type, length);
            ++cp; // Look for the next one...
            continue;
          }
          break;
        case pkt_type_CTRL:
        case pkt_type_PNG_Start:
        case pkt_type_PNG_Cont:
        case pkt_type_CMD:
        case pkt_type_XIO:
        case pkt_type_SID:
        case pkt_type_NPH:
          break;
        default:
          report_err(isgraph(type)
            ? "%s: Invalid packet type '%c' length %d"
            : "%s: Invalid packet type 0x%02X length %d",
            iname, type, length);
          ++cp; // Look for the next one...
          continue;
      }
      int pktlen = length + serio::pkt_hdr_size;
      relay->forward(&buf[cp], pktlen);
      if (type == pkt_type_TM) {
        bool rv = tm_out->forward_packet((const char*)&buf[cp], pktlen);
        if (rv) {
          report_ok(cp);
          return rv;
        }
      }
      cp += pktlen;
    }
  }
  report_ok(cp);
  return false;
}

void ipi_tm_in::dump_buf() {
  msg(MSG_ERROR, "%s: cp:%d nc:%d Input %s", iname, cp, nc,
    buffer_dumped ? "suppressed" : "was:");
  if (!buffer_dumped) {
    dump_hex(MSG, iname, buf, nc);
    buffer_dumped = true;
  }
}

/***************
 * ipi_tm_out
 */
ipi_tm_out::ipi_tm_out(const char *iname, Server *srvr)
    : Client(iname, "tm_gen", "tm_gen", "serin", 10),
      srvr(srvr)
{
}

bool ipi_tm_out::forward_packet(const char *pkt, int length) {
  if (is_negotiated() && obuf_empty()) {
    // ++packets_forwarded;
    // if (nl_debug_level < -1 && !(packets_forwarded%100))
      // msg(MSG_DEBUG, "%s: packets_forwarded: %d", iname, packets_forwarded);
    return iwrite(pkt, length);
  } else {
    msg(MSG_DEBUG, "%s: Packet dropped", iname);
  }
  return false;
}

bool ipi_tm_out::process_eof() {
  if (srvr)
    srvr->Shutdown(true);
  return false;
}

#ifdef HAVE_SCAN_DATA
void ipi_tm_out::enqueue_scan(int32_t scannum) {
  next_scan = scannum;
}

/**
 */
void ipi_tm_out::send_scan_data() {
  while (rows_this_row < rows_per_row) {
    if (cur_scan == 0) {
      if (next_scan == 0) return;
      cur_scan = next_scan;
      next_scan = 0;
      mlf_set_index(mlf, cur_scan);
      scan_fd = mlf_next_fd(mlf);
      nl_error(MSG_DBG(0), "Reading scan %lu from path %s",
        cur_scan, mlf->fpath);
      if (scan_fd < 0) { // error is already reported
        cur_scan = 0;
        return;
      }
      scan_file_size = lseek(scan_fd, 0, SEEK_END);
      if (scan_file_size < 0 || lseek(scan_fd, 0, SEEK_SET) != 0) {
        nl_error(2, "Error getting scan %d length");
        close(scan_fd);
        scan_fd = -1;
        cur_scan = 0;
        return;
      }
      if (scan_file_size > scanbufsize) {
        nl_error(MSG_ERROR, "Scan %d size %lu exceeds max possible %d",
          cur_scan, scan_file_size, scanbufsize);
        close(scan_fd);
        scan_fd = -1;
        cur_scan = 0;
        return;
      }
      int rv = ::read(scan_fd, scanbuf, scan_file_size);
      if (rv < 0) {
        nl_error(MSG_ERROR, "Error %d reading scan %d", errno, cur_scan);
        close(scan_fd);
        scan_fd = -1;
        cur_scan = 0;
        return;
      }
      scan_nb = rv;
      if (rv < scan_file_size) {
        nl_error(MSG_WARN, "Short read on scan %d: %d/%d",
            cur_scan, rv, scan_file_size);
      }
      ssp_hdr = (ssp_scan_hdr_t *)scanbuf;
      int chk_size = sizeof(uint32_t)*(7+ssp_hdr->NChannels*ssp_hdr->NSamples);
      if (chk_size > scan_file_size) {
        nl_error(MSG_ERROR, "Scan file %d is short: %d/%d",
          cur_scan, scan_file_size, chk_size);
        close(scan_fd);
        scan_fd = -1;
        cur_scan = 0;
        return;
      } else if (chk_size < scan_file_size) {
        nl_error(MSG_DBG(0), "Scan file %d is long: %d/%d",
          cur_scan, scan_file_size, chk_size);
        scan_file_size = chk_size;
        if (scan_nb > scan_file_size)
          scan_nb = scan_file_size;
      }
      nl_error(MSG_DBG(0), "Transmitting scan %ld: %lu bytes",
        cur_scan, scan_file_size);
      scan_cp = 0;
      scan_mfctr = 0;
      scan_mfctr_offset = 1;
      scan_file_offset = scan_nb;
    }
    if (flush_row()) return;
    if (scan_mfctr < scan_mfctr_offset ||
        scan_mfctr > scan_mfctr_offset + 255) {
      // create a header
      scan_mfctr_offset = scan_mfctr;
      // row_buf->scan_hdr.scannum = cur_scan;
      // row_buf->scan_hdr.scansize = scan_file_size;
      // row_buf->scan_hdr.mfctr_offset = scan_mfctr++;
      // memset(&row_buf->row[sizeof(scan_hdr_t)], 0,
        // row_len-sizeof(scan_hdr_t)-3);
      // row_buf->row[row_len-3] = 0;
      // memcpy(&(row_buf->row[row_len-2]), &scan_synch, 2);
      // row_offset = 0;
      // if (flush_row()) return;
    }
    if (scan_nb - scan_cp < row_len-3 &&
        scan_file_offset < scan_file_size) {
      // Less than one row of data currently in scanbuf and
      // more data left in the file, so read in more.
      if (scan_nb > scan_cp && scan_cp > 0) {
        memmove(&(row_buf->row[0]), &(row_buf->row[scan_cp]), scan_nb-scan_cp);
        scan_nb -= scan_cp;
        scan_cp = 0;
      }
      int remaining = scan_file_size - scan_file_offset;
      int available = scanbufsize - scan_cp;
      if (remaining > available) {
        if (available > blocksize) {
          // round down to fixed number of blocks
          int blocks = available/blocksize;
          remaining = blocks*blocksize;
        } else {
          remaining = available;
          // This should really never happen. It would mean the
          // scanbufsize is not much bigger than the blocksize
        }
      }
      int rv = ::read(scan_fd, scanbuf+scan_cp, remaining);
      scan_nb += rv;
      scan_file_offset += rv;
    }
    if (scan_cp >= scan_nb) {
      nl_assert(scan_file_offset >= scan_file_size);
      nl_assert(scan_fd >= 0);
      close(scan_fd);
      scan_fd = -1;
      cur_scan = 0;
    } else {
      uint16_t row_mfc = scan_mfctr++ - scan_mfctr_offset;
      uint16_t hdr_offset = 0;
      // transmit a row
      int available = scan_nb - scan_cp;
      if (row_mfc == 0) {
        row_buf->scan_hdr.scannum = cur_scan;
        row_buf->scan_hdr.scansize = scan_file_size;
        row_buf->scan_hdr.mfctr_offset = scan_mfctr_offset;
        hdr_offset = sizeof(scan_hdr_t);
      }
      if (available >= row_len-3-hdr_offset) {
        available = row_len - 3 - hdr_offset;
        memcpy(&(row_buf->row[hdr_offset]), &scanbuf[scan_cp], available);
      } else {
        memcpy(&(row_buf->row[hdr_offset]), &scanbuf[scan_cp], available);
        memset(&(row_buf->row[hdr_offset+available]), 0,
          row_len - 3 - available - hdr_offset);
      }
      row_buf->row[row_len-3] = row_mfc;
      memcpy(&(row_buf->row[row_len-2]), &scan_synch, 2);
      scan_cp += available;
      row_offset = 0;
      if (flush_row()) return;
    }
  }
}

void set_cur_photo(uint32_t Photo_Num) {
  if (TMp) TMp->cur_photo = Photo_Num;
}
#endif

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  { Server S("ip_ex");

    ipi_cmd_in *cmd_in = new ipi_cmd_in("cmd_in");
    S.ELoop.add_child(cmd_in);
    cmd_in->connect();

    ipi_cmd_out::attach(&S, "ip_ex");

    ipi_tm_out *tm_out = new ipi_tm_out("tm_out", &S);
    S.ELoop.add_child(tm_out);
    tm_out->connect();

    // tm_client iname is hard-coded to tm_client
    ipi_tm_in *tm_in = new ipi_tm_in(tm_out);
    S.ELoop.add_child(tm_in);
    tm_in->connect();
    
    S.Start(Server::Srv_TCP);
  }
  AppID.report_shutdown();
  return 0;
}
