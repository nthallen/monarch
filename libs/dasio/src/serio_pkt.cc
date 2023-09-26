#include <cstring>
#include "dasio/interface.h"
#include "dasio/serio_pkt.h"
#include "crc16modbus.h"
#include "nl.h"
#include "nl_assert.h"

using namespace DAS_IO;

bool Interface::not_serio_pkt_hdr() {
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
      report_err("%s: Skipping %d bytes", iname, cp-cp0);
      return false;
    }
  }
  ++cp;
  report_err("%s: Skipping %d bytes", iname, cp-cp0);
  return true;
}

bool Interface::not_serio_pkt(bool &have_hdr, serio_pkt_type &type,
      uint16_t &length, uint8_t *&payload) {
  nl_assert(bufsize >= serio::min_buffer_size );
  have_hdr = false;
  while (nc-cp >= serio::pkt_hdr_size) {
    if (not_serio_pkt_hdr()) {
      consume(cp);
      return true;
    }
    serio_pkt_hdr hdr;
    memcpy(&hdr, &buf[cp], serio::pkt_hdr_size);
    type = hdr.type;
    length = hdr.length;
    have_hdr = true;
    if (hdr.length > serio::max_pkt_payload) {
      report_err("%s: Invalid pkt length: %d", iname, hdr.length);
      ++cp;
      have_hdr = false;
      continue;
    }
    switch (hdr.type) {
      case pkt_type_TM:
      case pkt_type_PNG_Start:
      case pkt_type_PNG_Cont:
      case pkt_type_CMD:
        break;
      default:
        report_err(isgraph(hdr.type) ?
          "%s: Invalid packet type: '%c'" :
          "%s: Invalid packet type: 0x%02X",
            iname, hdr.type);
      // Ignore type 0, which can show up on a long string of zeros
      case pkt_type_NULL:
        ++cp;
        have_hdr = false;
        continue;
    }
    if (nc-cp < (unsigned)serio::pkt_hdr_size+hdr.length) {
      // Full packet not present
      consume(cp);
      return true;
    }
    if (cp+serio::pkt_hdr_size+hdr.length+1 > (unsigned)bufsize) {
      // It's all there and it can fit, but we're positioned
      // with no room for the final NUL
      consume(cp);
    }
    uint16_t CRC = crc16modbus_word(0,0,0);
    CRC = crc16modbus_word(CRC,
              &buf[cp+serio::pkt_hdr_size], hdr.length);
    if (CRC != hdr.CRC) {
      report_err("%s: CRC error: hdr: 0x%04X calc: 0x%04X",
        iname, hdr.CRC, CRC);
      ++cp;
      continue;
    }
    payload = &buf[cp+serio::pkt_hdr_size];
    return false;
  }
  return true;
}
