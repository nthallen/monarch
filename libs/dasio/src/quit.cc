/** @file quit.cc */
#include "dasio/quit.h"

namespace DAS_IO {

  Quit::Quit() : Client("Quit", 20, "cmd", "Quit") {}
  //Quit::Quit(const char *hostname) : Client("Quit", 20, hostname, "cmd", "Quit") {}
  Quit::~Quit() {}
  bool Quit::process_eof() { return true; }
  
}
