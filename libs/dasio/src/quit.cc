/** @file quit.cc */
#include "dasio/quit.h"
#include "dasio/msg.h"

namespace DAS_IO {
  Quit::Quit(Server *srvr, bool full) :
      Cmd_reader("Quit", 20, "Quit"),
      srvr(srvr),
      full(full) {}

  bool Quit::process_eof() {
    msg(MSG_DBG(0),"%s: received EOF", iname);
    if (srvr) {
      srvr->Shutdown(full);
    } else if (ELoop) {
      ELoop->set_loop_exit();
    }
    return true;
  }
}
