/** @file tm_ip_export.cc
 */
#include "tm_ip_export.h"
#include "crc16modbus.h"
#include "dasio/cmd_writer.h"
#include "dasio/tm.h"
#include "dasio/appid.h"
#include "nl.h"
#include "oui.h"

/**
 * ipi_cmd_in connects to the local command txsrvr to receive commands,
 * then forwards them to ipi_cmd_out.
 */
ipi_cmd_in::ipi_cmd_in(const char *iname, ipi_cmd_out *cmd_out)
    : Cmd_reader("cmd_in", 256, "ip_ex"),
      cmd_out(cmd_out)
{
  set_retries(-1, 10, 60, false); // Never stop trying
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
    : Serverside_client(auth, iname, ipi_cmd_out_bufsize) {
  set_obufsize(2048);
}

void ipi_cmd_out::attach(Server *srvr, const char *service) {
  srvr->add_subservice(new SubService(service, new_ipi_cmd_out, 0);
}

bool ipi_cmd_out::cond_send_cmd(const char *buf, unsigned int nc) {
  if (cmd_out) {
    return cmd_out->send_cmd(buf, nc);
  } else {
    msg(MSG_WARN, "%s: No connection: cmd dropped: %s",
        iname, buf);
    ++cmds_dropped;
  }
  return false;
}

ipi_cmd_out *ipi_cmd_out::cmd_out = 0;
int ipi_cmd_out ipi_cmd_out::cmds_dropped = 0;

Serverside_client *ipi_cmd_out::new_ipi_cmd_out(
            Authenticator *Auth, SubService *SS) {
  return new ipi_cmd_out(Auth, Auth->get_client_app());
}

bool ipi_cmd_out::send_cmd(const char *xbuf, unsigned int xnc) {
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
  io[1].iov_base = xbuf;
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

bool ipi_cmd_out::connected() {
  if (cmd_out) {
    cmd_out->close();
  }
  cmd_out = this;
  msg(0, "%s: Connection established", iname);
  return false;
}

bool ipi_cmd_out::close() {
  cmd_out = 0;
  Serverside_client::close();
  msg(0, "%s: Connection closed", iname);
}

bool ipi_cmd_out::app_input() {
  msg(1, "%s: Unexpected input: %s", iname, buf);
  report_ok(nc);
  return false;
}

/***************
 * ipi_tm_out
 */
ipi_tm_out::ipi_tm_out(const char *iname)
    : Socket(iname, "Uplink", "ip_ex", 0, UDP_WRITE) {
}

/**
 * @param MFCtr
 * @param raw The raw homerow data without the leading MFCtr or
 *    trailing Synch
 */
void ipi_tm_out::send_row(uint16_t MFCtr, const uint8_t *raw) {
  if (obuf_empty()) {
    if (dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: Tx resumed after dropping %d rows",
        iname, n_tx_rows_dropped);
      dropping_tx_rows = false;
      total_tx_rows_dropped += n_tx_rows_dropped;
      dropping_tx_rows = false;
      n_tx_rows_dropped = 0;
    }
    // We have allocated an obuf, so we can use auto vars for
    // io and hdr
    struct iovec io[3];
    serio_pkt_hdr hdr;
    hdr.LRC = 0;
    hdr.type = pkt_type_TM;
    hdr.length = tm_info.tm.nbminf-2;
    io[0].iov_len = sizeof(serio_pkt_hdr);
    io[0].iov_base = &hdr;
    io[1].iov_len = sizeof(MFCtr);
    io[1].iov_base = &MFCtr;
    io[2].iov_len = tm_info.tm.nbminf - 4;
    io[2].iov_base = (void*)raw;
    // Calculate the CRC of io[1] and io[2]
    { unsigned CRC = crc16modbus_word(0,0,0);
      CRC = crc16modbus_word(CRC, io[1].iov_base, io[1].iov_len);
      CRC = crc16modbus_word(CRC, io[2].iov_base, io[2].iov_len);
      hdr.CRC = CRC;
      uint8_t *hdrp = (uint8_t *)io[0].iov_base;
      for (int i = 1; i < io[0].iov_len; ++i) {
        hdr.LRC += hdrp[i];
      }
      hdr.LRC = -hdr.LRC;
    }
    bool rv = iwritev(io, 3);
    rows_this_row = 0;
  } else {
    if (!dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: dropping MFCtr %u", iname, MFCtr);
      dropping_tx_rows = true;
    }
    ++n_tx_rows_dropped;
  }
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

ipi_tm_in::ipi_tm_in(ipi_tm_out *tm_out)
    : tm_client(1024),
      tm_out(tm_out)
{
  load_tmdac(".");
}

ipi_tm_in::~ipi_tm_in() {
}

// Extracted and adapted from extmain.skel
unsigned int ipi_tm_in::process_data() {
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

void ipi_tm_in::process_quit() {
  msg(MSG, "%s: process_quit()", iname);
  ELoop->set_loop_exit();
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  { Server S;

    ipi_cmd_in *cmd_in = new ipi_cmd_in("cmd_in");
    S.ELoop.add_child(cmd_in);
    cmd_in->connect();

    ipi_cmd_out::attach(&S, "ip_ex", cmd_in);
    
    
    ipi_tm_out *tm_out = new ipi_tm_out("tm_out");
    ELoop.add_child(tm_out);
    tm_out->connect();
    
    // tm_client iname is hard-coded to tm_client
    ipi_tm_in *tm_in = new ipi_tm_in(tm_out);
    ELoop.add_child(tm_in);
    tm_in->connect();
    
    ELoop.event_loop();
  }
  AppID.report_shutdown();
  return 0;
}