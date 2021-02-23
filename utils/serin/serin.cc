#include <cstring>
#include "serin.h"
#include "oui.h"
#include "crc16modbus.h"

using namespace DAS_IO;

static uint16_t lcm( uint16_t ain, uint16_t bin ) {
  short int t, a, b;
  // first calculate the gcd via the euclidean algorithm
  a = ain;
  b = bin;
  while ( b != 0 ) {
    t = b;
    b = a % b;
    a = t;
  }
  // assert(a != 0);
  a = ain/a;
  return a * bin;
}

serin::serin() :
      tm_generator(),
      have_tstamp(false),
      next_minor_frame(0) {
  uint16_t mfcspermajf = tmi(nrowmajf)/tm_info.nrowminf;
  uint16_t lcmMn = lcm(mfcspermajf,tmi(nsecsper));
  ROLLOVER_MFC = (UINT16_MAX+1L)%lcmMn;
}

void serin::start() {
  execute("TMc"); // autostart so we can send data whenever it arrives
  Start(Srv_Function, "tm_gen");
  ELoop.delete_children();
  ELoop.clear_delete_queue(true);
}

void serin::service_row_timer() {
  if (regulated) transmit_data(true);
}

void serin::process_tm(serio_pkt_hdr *hdr) {
  if (hdr->length % (tm_info.tm.nbminf-2)) {
    msg(MSG_ERROR,
      "serin: process_tm() nbminf-2=%d does not divide length=%d",
      hdr->length, tm_info.tm.nbminf-2);
  }
  int rows = (hdr->length / (tm_info.tm.nbminf-2));
  uint8_t *raw = ((uint8_t*)hdr) + sizeof(serio_pkt_hdr);
  for (int rowi = 0; rowi < rows; ++rowi) {
    uint8_t *row = &raw[rowi*(tm_info.tm.nbminf-2)];
    uint16_t MFCtr = (row[1]<<8) + row[0];
    if (!have_tstamp) {
      // make tstamp with current time and MFCtr
      commit_tstamp(MFCtr, time(0));
      have_tstamp = true;
    } else if (MFCtr < next_minor_frame) {
      if (MFCtr < ROLLOVER_MFC) {
        // Just make a new tstamp: must have restarted
        commit_tstamp(MFCtr, time(0));
      } else {
        commit_tstamp( 0, tm_info.t_stmp.secs +
          tmi(nsecsper) *
            ((long)UINT16_MAX - tm_info.t_stmp.mfc_num
                - ROLLOVER_MFC + 1) /
              tmi(nrowsper) );
      }
    } else if (MFCtr > tm_info.t_stmp.mfc_num &&
          MFCtr-tm_info.t_stmp.mfc_num > TS_MFC_LIMIT) {
      // Advance time_stamp by a calculated number of seconds, mfcs
      uint16_t q = (MFCtr - tm_info.t_stmp.mfc_num)/tmi(nrowsper);
      commit_tstamp(tm_info.t_stmp.mfc_num + q*tmi(nrowsper),
        tm_info.t_stmp.secs + tmi(nsecsper) * q);
    }
    next_minor_frame = MFCtr+1;
    uint8_t *dest;
    lock(__FILE__,__LINE__);
    int nr = allocate_rows(&dest);
    unlock();
    if (nr > 0) {
      // copy data into the queue and update indexes
      msg(MSG_DBG(1), "Transmitting: MFCtr=%04X", MFCtr);
      // dump_bytes(MSG_DBG(2), cp, cp+tmi(nbminf));
      memcpy(dest, &row[2], nbQrow);
      commit_rows(MFCtr, 0, 1);
      break;
    } else {
      msg(MSG_ERROR, "Dropping row MFCtr %u", MFCtr);
      // it_blocked = IT_BLOCKED_DATA;
      // sem_wait(&it_sem);
    }
  }
}

serin_serin::serin_serin(Authenticator *auth, const char *iname,
                         serin *srvr)
    : Serverside_client(auth, iname, serin_serin_bufsize),
      srvr(srvr) {
  set_binary_mode();
}

void serin_serin::attach(serin *srvr) {
  srvr->add_subservice(new SubService("tm_gen/serin", new_serin_serin,
    (void *)srvr));
}

Serverside_client *serin_serin::new_serin_serin(
            Authenticator *Auth, SubService *SS) {
  serin *srvr = (serin *)(SS->svc_data);
  return new serin_serin(Auth, Auth->get_client_app(), srvr);
}

//bool serin_serin::not_serio_pkt_hdr<serin_serin>();

bool serin_serin::not_serio_pkt_hdr() {
  uint8_t lrc_sum = 0;
  int cp0 = cp;
  if (nc-cp < sizeof(serio_pkt_hdr)) return true;
  for (int i = 0; i < sizeof(serio_pkt_hdr); ++i) {
    lrc_sum += buf[cp+i];
  }
  if (lrc_sum == 0) return false;
  while (nc-cp > sizeof(serio_pkt_hdr)) {
    lrc_sum -= buf[cp++];
    lrc_sum += buf[cp+sizeof(serio_pkt_hdr)-1];
    if (lrc_sum == 0) {
      msg(MSG_ERROR, "%s: Skipping %d bytes", iname, cp-cp0);
      return false;
    }
  }
  ++cp;
  msg(MSG_ERROR, "%s: Skipping %d bytes", iname, cp-cp0);
  return true;
}

bool serin_serin::protocol_input() {
  // Process incoming TM records here
  while (nc-cp >= sizeof(serio_pkt_hdr)) {
    if (not_serio_pkt_hdr()) {
      consume(cp);
      return false;
    }
    serio_pkt_hdr *hdr = (serio_pkt_hdr*)&buf[cp];
    if (hdr->length > serio::max_pkt_payload) {
      msg(MSG_ERROR, "%s: Invalid pkt length: %d", iname, hdr->length);
      ++cp;
      continue;
    }
    switch (hdr->type) {
      case pkt_type_TM:
        break;
      case pkt_type_PNG_Start:
      case pkt_type_PNG_Cont:
      case pkt_type_CMD:
      default:
        msg(MSG_ERROR, isgraph(hdr->type) ?
          "%s: Invalid packet type: '%c'" :
          "%s: Invalid packet type: 0x%02X",
            iname, hdr->type);
        ++cp;
        continue;
    }
    if (nc-cp < sizeof(serio_pkt_hdr)+hdr->length) {
      // Full packet not present
      if (cp+sizeof(serio_pkt_hdr)+hdr->length > bufsize) {
        consume(cp);
      }
      break;
    }
    uint16_t CRC = crc16modbus_word(0,0,0);
    CRC = crc16modbus_word(CRC,
              &buf[cp+sizeof(serio_pkt_hdr)], hdr->length);
    if (CRC != hdr->CRC) {
      msg(MSG_ERROR, "%s: CRC error: hdr: 0x%04X calc: 0x%04X",
        iname, hdr->CRC, CRC);
      ++cp;
      continue;
    }
    switch (hdr->type) {
      case pkt_type_TM:
        srvr->process_tm(hdr);
        cp += sizeof(serio_pkt_hdr) + hdr->length;
        report_ok(nc-cp < serio::max_pkt_payload + sizeof(serio_pkt_hdr)
                  ? cp : 0);
        continue;
      case pkt_type_PNG_Start:
      case pkt_type_PNG_Cont:
      case pkt_type_CMD:
      default:
        msg(MSG_ERROR, "%s: Unexpected type on second check", iname);
        ++cp;
        continue;
    }
  }
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  msg(MSG, "Starting");
  load_tmdac(0);
  serin *srvr = new serin();
  srvr->init(4, true);
  serin_serin::attach(srvr);
  srvr->start();
  msg(MSG, "Terminating");
  return 0;
}
