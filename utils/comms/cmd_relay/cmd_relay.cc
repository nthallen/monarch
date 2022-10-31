/** @file cmd_relay.cc
 *  @brief Utility to relay commands between machines
 */
#include "oui.h"
#include "cmd_relay.h"
#include "dasio/msg.h"
#include "dasio/cmd_writer.h"

using namespace DAS_IO;

/**
 * cmd_relay connects to a txsrvr in order to receive commands.
 * It has an rxsrvr member which connects to a remote command
 * server. Its function is to relay commands received from
 * the txsrvr to the rxsrvr.
 */
cmd_relay::cmd_relay() :
    Cmd_reader("txsrvr", 256, "RFDio", "txsrvr"),
    dropping_tx_cmds(false),
    n_tx_cmds_dropped(0),
    total_tx_cmds_dropped(0)
{
  rxsrvr = new Cmd_writer("rxsrvr", "rxsrvr");
  cic_init(rxsrvr);
}

cmd_relay::~cmd_relay() {}

bool cmd_relay::app_input() {
  // msg(MSG, "Received command '%s'", buf);
  if (obuf_empty()) {
    if (dropping_tx_cmds) {
      msg(MSG_DEBUG, "%s: Tx resumed after dropping %d cmds",
        iname, n_tx_cmds_dropped);
      dropping_tx_cmds = false;
      total_tx_cmds_dropped += n_tx_cmds_dropped;
      dropping_tx_cmds = false;
      n_tx_cmds_dropped = 0;
    }
    if (CHP.parse(buf)) {
      consume(nc);
      return false;
    }
    rxsrvr->sendcmd(&CHP);
    report_ok(nc);
#ifdef OLD_CODE    
    // We have allocated an obuf, so we can use auto vars for
    // io and hdr
    struct iovec io[2];
    serio_pkt_hdr hdr;
    hdr.LRC = 0;
    hdr.type = pkt_type_CMD;
    hdr.length = nc;
    io[0].iov_len = sizeof(serio_pkt_hdr);
    io[0].iov_base = &hdr;
    io[1].iov_len = nc;
    io[1].iov_base = buf;
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
    RFD->tx_cmd(io, 2); // Errors are handled in callbacks
    report_ok(nc);
#endif
  } else {
    if (!dropping_tx_cmds) {
      msg(MSG_DEBUG, "%s: dropping command", iname);
      dropping_tx_cmds = true;
    }
    ++n_tx_cmds_dropped;
  }
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  Loop ELoop;
  cmd_relay *relay = new cmd_relay();
  ELoop.add_child(relay);
  relay->connect();
  ELoop.event_loop();
  ELoop.delete_children();
  ELoop.clear_delete_queue(true);
  msg(MSG, "Terminating");
  return 0;
}
