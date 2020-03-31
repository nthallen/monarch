/** @file quit.cc */
#include "dasio/quit.h"
#include "dasio/msg.h"

namespace DAS_IO {
  Quit::Quit() : Cmd_reader("Quit", 20, "Quit") {}
  bool Quit::process_eof() {
    msg(MSG_DBG(0),"%s: received EOF", iname);
    if (ELoop)
      ELoop->set_loop_exit();
    return true;
  }
}
