/** @file tm_ip_export.cc
 */
#include <cstring>
#include "tm_ip_export.h"
#include "crc16modbus.h"
#include "dasio/cmd_writer.h"
#include "dasio/tm.h"
#include "dasio/appid.h"
#include "dasio/ascii_escape.h"
#include "nl.h"
#include "oui.h"

const char *ip_export_cross_exp;

/**
 * Establishes connection to the Relay node and receives
 * commands.
 */
ipx_cmd_in::ipx_cmd_in(const char *iname)
    : Client(iname, "Relay", "ip_ex", 0, serio::min_buffer_size)
{
  set_retries(-1, 10, 10, false); // Never stop trying
}

bool ipx_cmd_in::app_input() {
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;

  while (cp < nc) {
    if (not_serio_pkt(have_hdr, type, length, payload)) {
      if (have_hdr && type != pkt_type_CMD) {
        report_err("%s: Invalid command type: '%c'", iname, type);
        ++cp;
        continue;
      }
      return false;
    }
    if (type != pkt_type_CMD) {
      report_err("%s: Invalid command type: '%c'", iname, type);
      ++cp;
      continue;
    }
    char save_char = buf[cp + serio::pkt_hdr_size + length];
    buf[cp + serio::pkt_hdr_size + length] = '\0';
    ci_sendcmd(Cmd_Send, (char *)&buf[cp + serio::pkt_hdr_size]);
    buf[cp + serio::pkt_hdr_size + length] = save_char;
    cp += serio::pkt_hdr_size + length;
  }
  report_ok(cp);
  return false;
}

bool ipx_cmd_in::process_eof() {
  msg(MSG_ERROR, "%s: Connection dropped", iname);
  return reset();
}

ipx_tm_out::ipx_tm_out(const char *iname)
    : Socket(iname, "Relay", "ip_ex", 0, UDP_WRITE),
      dropping_tx_rows(false),
      n_tx_rows_dropped(0),
      total_tx_rows_dropped(0),
      MTU(max_MTU),
      pyld_nc(0)
{
  max_udp_payload = max_MTU - IP_header_len - UDP_header_len;
  payload = (uint8_t *)new_memory(max_udp_payload);
}

ipx_tm_out::~ipx_tm_out() {
  msg(MSG, "%s: Destructing", iname);
  if (dropping_tx_rows) {
    msg(MSG, "%s: dropping %d rows", iname, n_tx_rows_dropped);
  }
  if (total_tx_rows_dropped || n_tx_rows_dropped) {
    msg(MSG, "%s: total rows dropped: %d", iname,
      n_tx_rows_dropped + total_tx_rows_dropped);
  }
}

void ipx_tm_out::update_MTU(int new_MTU) {
  if (new_MTU > max_MTU) {
    msg(MSG_ERROR, "%s: Requested MTU %d exceeds max %d",
      iname, new_MTU, max_MTU);
    new_MTU = max_MTU;
  }
  MTU = new_MTU;
  max_udp_payload = new_MTU - IP_header_len - UDP_header_len;
}

/**
 * @param MFCtr
 * @param raw The raw homerow data without the leading MFCtr or
 *    trailing Synch
 */
void ipx_tm_out::send_row(uint16_t MFCtr, const uint8_t *raw) {
  if (obuf_empty()) {
    if (dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: Tx resumed after dropping %d rows",
        iname, n_tx_rows_dropped);
      dropping_tx_rows = false;
      total_tx_rows_dropped += n_tx_rows_dropped;
      dropping_tx_rows = false;
      n_tx_rows_dropped = 0;
    }
    int rowsize = sizeof(serio_pkt_hdr) + sizeof(MFCtr) + tm_info.tm.nbminf - 4;
    if (pyld_nc + rowsize >= max_udp_payload)
      flush();

    // We have allocated an obuf, so we can use auto vars for
    // io and hdr
    serio_pkt_hdr hdr;
    hdr.LRC = 0;
    hdr.type = pkt_type_TM;
    hdr.length = tm_info.tm.nbminf-2;

    int hdr_offset = pyld_nc;
    pyld_nc += sizeof(serio_pkt_hdr);
    int mfc_offset = pyld_nc;
    memcpy(&payload[pyld_nc], &MFCtr, sizeof(MFCtr));
    pyld_nc += sizeof(MFCtr);
    memcpy(&payload[pyld_nc], (void*)raw, tm_info.tm.nbminf - 4);
    pyld_nc += tm_info.tm.nbminf - 4;
    
    // Calculate the CRC of io[1] and io[2]
    { unsigned CRC = crc16modbus_word(0,0,0);
      CRC = crc16modbus_word(CRC, &payload[mfc_offset], pyld_nc-mfc_offset);
      hdr.CRC = CRC;
      uint8_t *hdrp = (uint8_t *)&hdr;
      for (int i = 1; i < sizeof(serio_pkt_hdr); ++i) {
        hdr.LRC += hdrp[i];
      }
      hdr.LRC = -hdr.LRC;
    }
    memcpy(&payload[hdr_offset],&hdr,sizeof(serio_pkt_hdr));
    if (pyld_nc + rowsize >= max_udp_payload)
      flush();
    rows_this_row = 0;
  } else {
    if (!dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: dropping MFCtr %u", iname, MFCtr);
      dropping_tx_rows = true;
    }
    ++n_tx_rows_dropped;
  }
}

void ipx_tm_out::flush() {
  if (nl_debug_level <= MSG_DEBUG) {
    msg(MSG_DEBUG, "%s: Send packet %d bytes", iname, pyld_nc);
    dump_hex(MSG, iname, payload, pyld_nc);
  }
  iwrite((char*)payload, pyld_nc);
  pyld_nc = 0;
}

#ifdef HAVE_SCAN_DATA
void ipx_tm_out::enqueue_scan(int32_t scannum) {
  next_scan = scannum;
}

/**
 */
void ipx_tm_out::send_scan_data() {
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

ipx_tm_in::ipx_tm_in(ipx_tm_out *tm_out)
    : tm_client(1024),
      tm_out(tm_out)
{}

ipx_tm_in::~ipx_tm_in() {
}

// Extracted and adapted from extmain.skel
unsigned int ipx_tm_in::process_data() {
  const uint8_t *raw;
  int n_rows = rows_in_buf;
  uint16_t MFCtr = buf_mfctr;
  majf_row = (((uint16_t)MFCtr) % tmi(nrowmajf));

  for ( raw = data_row; n_rows > 0; --n_rows, raw += nbQrow ) {
    tm_out->send_row(MFCtr, raw);
    majf_row = (majf_row == tmi(nrowmajf)-1) ? 0 : (majf_row+1);
    ++MFCtr;
  }
  next_minor_frame = MFCtr;
  return rows_in_buf;
}

void ipx_tm_in::process_init() {
  memcpy(&tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t));
  tm_rcvr::process_init();
}

void ipx_tm_in::process_quit() {
  msg(MSG, "%s: process_quit()", iname);
  ELoop->set_loop_exit();
}

ipx_ctrl::ipx_ctrl(const char *iname, const char *cmdchannel,
                    ipx_tm_out *tm_out)
    : Cmd_reader(iname, 80, cmdchannel),
      tm_out(tm_out) {}

bool ipx_ctrl::protocol_input() {
  uint16_t new_MTU;
  if (buf[cp] == 'Q') {
    msg(MSG, "%s: process_quit()", iname);
    ELoop->set_loop_exit();
  } else if (not_str("M") || not_uint16(new_MTU)) {
    msg(MSG_ERROR, "%s: Invalid command: '%s'",
      iname, ascii_escape());
  } else {
    msg(MSG, "%s: Updating MTU to %u", iname, new_MTU);
    tm_out->update_MTU(new_MTU);
  }
  consume(nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  { Loop ELoop;
  
    ipx_cmd_in *cmd_in = new ipx_cmd_in("cmd_in");
    cmd_in->set_cross_exp(ip_export_cross_exp);
    ELoop.add_child(cmd_in);
    cmd_in->connect();
    
    ipx_tm_out *tm_out = new ipx_tm_out("tm_out");
    ELoop.add_child(tm_out);
    tm_out->connect();
    
    // tm_client iname is hard-coded to tm_client
    ipx_tm_in *tm_in = new ipx_tm_in(tm_out);
    ELoop.add_child(tm_in);
    tm_in->connect();
    
    ipx_ctrl *ctrl = new ipx_ctrl("ctrl", "TMIPX", tm_out);
    ELoop.add_child(ctrl);
    ctrl->connect();
    
    ELoop.event_loop();
    ELoop.delete_children();
    ELoop.clear_delete_queue(true);
  }
  AppID.report_shutdown();
  return 0;
}
