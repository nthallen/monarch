/* dccc_if.c defines how we get commands */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "dccc.h"
#include "disc_cmd.h"
#include "nl.h"
#include "dasio/tm.h"

void operate(void) {
  DAS_IO::Server *S = new DAS_IO::Server("dccc");
  S->add_subservice(new DAS_IO::SubService("dccc",
    (DAS_IO::socket_clone_t)new_dccc_ssclient, (void*)0));
  msg(0, "Starting");
  S->Start(DAS_IO::Server::server_type);
  msg(0, "Terminating");
}

dccc_ssclient::~dccc_ssclient() {}

/**
  * Syntax for commands will be:
  ^Q?$ Quit
  ^D\d+ Discrete command (STRB or UNSTRB)
  ^S\d+=\d+ SET or SELECT
  ^M\d+[,\d+]*
  ^N\d+=\d+[,\d+=\d+]*
 */

bool dccc_ssclient::protocol_input() {
  if (nc == 0 || buf[0] == 'Q') {
    report_ok(nc);
    return true;
  }
  bool multi = 0;
  bool need_vals = 0;
  cmd_t pcmd;
  pcmd.n_cmds = 0;
  pcmd.cmd_type = buf[cp++];
  switch (pcmd.cmd_type) {
    case 'D': break;
    case 'S': need_vals = 1; break;
    case 'M': multi = 1; break;
    case 'N': multi = 1; need_vals = 1; break;
    default:
      report_err("%s: Invalid command type received", iname);
      consume(nc);
      return false;
  }
  while (cp < nc) {
    if (not_uint16(pcmd.cmds[pcmd.n_cmds].cmd) ||
        (need_vals &&
          (not_str("=") ||
            not_uint16(pcmd.cmds[pcmd.n_cmds].value)))) {
      report_err("%s: Syntax1", iname);
      consume(nc);
      return false;
    }
    ++pcmd.n_cmds;
    if (cp < nc) {
      switch (buf[cp]) {
        case '\n': ++cp; break;
        case ',':
          ++cp;
          if (pcmd.n_cmds >= MAX_CMDS) {
            report_err("%s: Too many commands in multi-command", iname);
            consume(nc);
            return false;
          }
          continue;
        default:
          report_err("%d: Syntax2", iname);
          consume(nc);
          return false;
      }
    }
  }
  if (pcmd.n_cmds == 0 ||
      (pcmd.n_cmds > 1 && !multi)) {
    report_err("%s: No commands or more than one", iname);
    consume(nc);
    return false;
  }
  process_pcmd(&pcmd);
  report_ok(cp);
  return false;
}

bool dccc_ssclient::process_eof() {
  DAS_IO::Socket::process_eof();
  return true;
}

