/** @file quit.cc */
#include "dasio/quit.h"
#include "dasio/msg.h"

namespace DAS_IO {
  Quit::Quit(Server *srvr, bool full) :
      Cmd_reader("Quit", 20, "Quit"),
      srvr(srvr),
      full(full) {}

  bool Quit::app_input() {
    if (nc > 0 && buf[0] == 'Q') {
      msg(0, "%s: received Quit command", iname);
    } else {
      report_err("%s: Received non-Q", iname);
    }
    report_ok(nc);
    return shutdown();
  }

  bool Quit::process_eof() {
    msg(MSG_DBG(0),"%s: received EOF", iname);
    return shutdown();
  }
  
  bool Quit::shutdown() {
    if (srvr) {
      srvr->Shutdown(full);
    } else if (ELoop) {
      ELoop->set_loop_exit();
    }
    return true;
  }
}
