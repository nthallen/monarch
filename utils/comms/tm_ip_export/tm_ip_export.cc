/** @file tm_ip_export.cc
 */
#include "tm_ip_export.h"

/**
 * @param MFCtr
 * @param raw The raw homerow data without the leading MFCtr or
 *    trailing Synch
 */
void tm_ip_remote::send_row(uint16_t MFCtr, const uint8_t *raw) {
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

tm_ip_export::tm_ip_export() {
  load_tmdac(".");
}

tm_ip_export::~tm_ip_export() {
}

unsigned int tm_ip_export::process_data() {
  unsigned char *raw;
  int n_rows = rows_in_buf;
  MFCtr = buf_mfctr;
  majf_row = (((uint16_t)MFCtr) % NROWMAJF);

  for ( raw = data_row; n_rows > 0; --n_rows, raw += nbQrow ) {
    home = (union home_row *) raw;
    rmt->send_row(uint16_t MFCtr, const uint8_t *raw);
    // efuncs[majf_row]();
    incmod(majf_row, NROWMAJF);
    ++MFCtr;
  }
  next_minor_frame = MFCtr;
  // EXTRACTION_UPDATE;
  return rows_in_buf;
}

