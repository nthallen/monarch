/** @file quit.cc */
#include "dasio/quit.h"

namespace DAS_IO {
  Quit::Quit() : Cmd_reader("Quit", 20, "Quit") {}
  bool Quit::process_eof() { return true; }
}
