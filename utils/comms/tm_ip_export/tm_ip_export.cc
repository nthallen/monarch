/** @file tm_ip_export.cc
 */
#include "tm_ip_export.h"
#include "crc16modbus.h"

/**
 * Establishes connection to the Relay node and receives
 * commands.
 */
ipx_cmd_in::ipx_cmd_in()
    : Client("cmd_in", "cmd_in", "ip_ex", 0, serio::max_cmd_packet_size)
{
  set_retries(-1, 10, 60, false); // Never stop trying
}

bool ipx_cmd_in::app_input() {
  // Interpret incoming command? No, just send it to srvr
  while (nc-cp >= serio::pkt_hdr_size) {
    if (not_serio_pkt_hdr()) {
      consume(cp);
      return false;
    }
    serio_pkt_hdr *hdr = (serio_pkt_hdr*)&buf[cp];
    if (hdr->length > serio::max_pkt_payload) {
      report_err("%s: Invalid pkt length: %d", iname, hdr->length);
      ++cp;
      continue;
    }
    switch (hdr->type) {
      case pkt_type_CMD:
        break;
      case pkt_type_TM:
      case pkt_type_PNG_Start:
      case pkt_type_PNG_Cont:
      default:
        msg(MSG_ERROR, isgraph(hdr->type) ?
          "%s: Invalid packet type: '%c'" :
          "%s: Invalid packet type: 0x%02X",
            iname, hdr->type);
      case pkt_type_NULL: // Ignore type 0, which can show up on a long string of zeros
        ++cp;
        continue;
    }
    if (nc-cp < (unsigned)serio::pkt_hdr_size+hdr->length) {
      // Full packet not present
      if (cp+serio::pkt_hdr_size+hdr->length > (unsigned)bufsize) {
        consume(cp);
      }
      break;
    }
    uint16_t CRC = crc16modbus_word(0,0,0);
    CRC = crc16modbus_word(CRC,
              &buf[cp+serio::pkt_hdr_size], hdr->length);
    if (CRC != hdr->CRC) {
      msg(MSG_ERROR, "%s: CRC error: hdr: 0x%04X calc: 0x%04X",
        iname, hdr->CRC, CRC);
      ++cp;
      continue;
    }
    switch (hdr->type) {
      case pkt_type_CMD:
        { char save_char = buf[cp + serio::pkt_hdr_size + hdr->length];
          buf[cp + serio::pkt_hdr_size + hdr->length] = '\0';
          ci_sendcmd(Cmd_Send, (char *)&buf[cp + serio::pkt_hdr_size]);
          buf[cp + serio::pkt_hdr_size + hdr->length] = save_char;
          cp += serio::pkt_hdr_size + hdr->length;
          report_ok(cp);
        }
        continue;
      case pkt_type_TM:
      case pkt_type_PNG_Start:
      case pkt_type_PNG_Cont:
      default:
        msg(MSG_ERROR, "%s: Unexpected type on second check", iname);
        ++cp;
        continue;
    }
  }
  return false;
}

bool ipx_cmd_in::not_serio_pkt_hdr() {
  uint8_t lrc_sum = 0;
  int cp0 = cp;
  if (nc-cp < serio::pkt_hdr_size) return true;
  for (int i = 0; i < serio::pkt_hdr_size; ++i) {
    lrc_sum += buf[cp+i];
  }
  if (lrc_sum == 0) return false;
  while (nc-cp > serio::pkt_hdr_size) {
    lrc_sum -= buf[cp++];
    lrc_sum += buf[cp+serio::pkt_hdr_size-1];
    if (lrc_sum == 0) {
      msg(MSG_ERROR, "%s: Skipping %d bytes", iname, cp-cp0);
      return false;
    }
  }
  ++cp;
  msg(MSG_ERROR, "%s: Skipping %d bytes", iname, cp-cp0);
  return true;
}

UDP::UDP( const char *iname, UDP_mode_t mode, const char *function,
          const char *service, int bufsz)
    : Socket(iname, function, service, bufsz),
      mode(mode) {
  Socket_type = Socket_UDP;
  switch (mode) {
    case UDP_READ:
      is_server = true;
  }
}

ipx_tm_out::ipx_tm_out(const char *iname, )
    : UDP()

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

ipx_tm_in::ipx_tm_in(ipx_tm_out *tm_out)
    : tm_out(tm_out)
{
  load_tmdac(".");
}

ipx_tm_in::~ipx_tm_in() {
}

unsigned int ipx_tm_in::process_data() {
  unsigned char *raw;
  int n_rows = rows_in_buf;
  MFCtr = buf_mfctr;
  majf_row = (((uint16_t)MFCtr) % NROWMAJF);

  for ( raw = data_row; n_rows > 0; --n_rows, raw += nbQrow ) {
    home = (union home_row *) raw;
    tm_out->send_row(uint16_t MFCtr, const uint8_t *raw);
    // efuncs[majf_row]();
    incmod(majf_row, NROWMAJF);
    ++MFCtr;
  }
  next_minor_frame = MFCtr;
  // EXTRACTION_UPDATE;
  return rows_in_buf;
}

int main(int argc, char **argv) {
}
