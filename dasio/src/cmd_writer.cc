/** @file cmd_writer.cc */
#include <string.h>
#include <stdarg.h>
#include "dasio/cmd_writer.h"
#include "dasio/appid.h"
#include "dasio/cmd_version.h"
#include "dasio/ascii_escape.h"
#include "nl.h"
#include "nl_assert.h"
#include "cmdalgo.h"

namespace DAS_IO {

Cmd_writer *Cmd_writer::Cmd = 0;
bool Cmd_writer::playback = false;

Cmd_writer::Cmd_writer(const char *iname)
      : Client(iname, 128, "cmd", "server") {
  if (Cmd) {
    nl_error(3, "%s: More than one Cmd_writer instance", iname);
  } else {
    Cmd = this;
  }
  PvtLoop.add_child(this);
  version_verified = false;
  sent_quit = recd_quit = false;
  ci_time = 0;
}

// Cmd_writer::Cmd_writer(const char *iname, const char *hostname)
      // : Client(iname, 128, hostname, "cmd", "server") {
// }

Cmd_writer::~Cmd_writer() {
  Cmd = 0;
}

bool Cmd_writer::app_input() {
  uint16_t code;
  switch (buf[cp]) {
    case 'Q':
      if (not_str("Q\n")) {
        if (cp >= nc) return false;
        consume(nc);
        return true;
      }
      recd_quit = true;
      ret_code = CMDREP_QUIT;
      break;
    case 'K':
      if (not_str("K\n")) {
        if (cp >= nc) return false;
        consume(nc);
        return true;
      } else {
        ret_code = CMDREP_OK;
      }
      break;
    case 'S':
      if (not_str("S") ||
          not_uint16(code) ||
          not_str(": ")) {
        if (cp >= nc) return false;
        consume(nc);
        return true;
        // leave ret_code as NOREPLY
      } else {
        nl_error(2, "%s: Syntax error at column %d", iname, code);
        ret_code = CMDREP_SYNERR+code;
      }
      break;
    case 'E':
      if (not_str("S") ||
          not_uint16(code) ||
          not_str(": ")) {
        if (cp >= nc) return false;
        consume(nc);
        return true;
        // leave ret_code as NOREPLY
      } else {
        nl_error(2, "%s: %s", iname, buf+cp);
        ret_code = CMDREP_EXECERR+code;
      }
      break;
    default:
      report_err("%s: Invalid response from server: '%s'",
        iname, ::ascii_escape((const char *)buf, nc));
      consume(nc);
      break;
  }
  report_ok(nc);
  return true;
}

bool Cmd_writer::app_connected() {
  if (!version_verified && ci_version[0] != '\0') {
    char *vcheck;
    int nb = snprintf( vcheck, 0, "[%s:V%s]\n",
      AppID.name, ci_version );
    vcheck = (char *)new_memory(nb+1);
    snprintf(vcheck, nb+1, "[%s:V%s]\n",
      AppID.name, ci_version );
    if (iwrite(vcheck, nb)) return true;
    nl_assert(obuf_empty());
    return true;
  }
  return true;
}

int Cmd_writer::sendcmd(Cmd_Mode mode, const char *cmdtext) {
  const char *cmdopts = "";
  int clen, rv;
  char buf[CMD_MAX_COMMAND_IN+1];
  
  if (sent_quit) return(1);
  // if (!playback && cis_fd < 0 && cic_init() != 0) return(1);
  ret_code = CMDREP_NOREPLY;
  if (cmdtext == NULL) {
    cmdopts = ":X";
    cmdtext = "";
    nl_error(-3, "Sending Quit to Server");
    sent_quit = true;
  } else {
    switch (mode) {
      case 1: cmdopts = ":T"; break;
      case 2: cmdopts = ":Q"; break;
      default: break;
    }
    clen = strlen(cmdtext);
    { int len = clen;
      const char *ts = time_str();

      if (len > 0 && cmdtext[len-1]=='\n') len--;
      nl_error( mode == 2 ? -4 : -3,
          "%s%*.*s", ts, len, len, cmdtext);
    }
  }
  if (playback) return(0);
  clen = snprintf( buf, CMD_MAX_COMMAND_IN+1, "[%s%s]%s",
    AppID.name, cmdopts, cmdtext );
  if ( clen > CMD_MAX_COMMAND_IN ) {
    nl_error( 2, "Command too long" );
    return true;
  }
  iwrite(buf, clen);
  wait();
  return ret_code;
}

void Cmd_writer::wait() {
  PvtLoop.event_loop();
}

const char *Cmd_writer::time_str() {
  static char buf[11];
  int hour, min, sec;
  long int time = ci_time;

  if ( ! playback || time == 0 ) return "";
  if ( time < 0 ) return "-1: ";
  time = time % ( 24 * 3600L );
  hour = time / 3600;
  time = time % 3600;
  min = time / 60;
  sec = time % 60;
  sprintf( buf, "%02d:%02d:%02d: ", hour, min, sec );
  return buf;
}

void Cmd_writer::settime(int32_t time) {
  ci_time = time;
}

}

bool cic_init() {
  if (DAS_IO::Cmd_writer::Cmd || DAS_IO::Cmd_writer::playback)
    return false;
  DAS_IO::Cmd_writer *cmd = new DAS_IO::Cmd_writer("Cmd");
  cmd->connect();
  cmd->wait();
  return ! cmd->is_negotiated();
}

int ci_sendcmd(DAS_IO::Cmd_Mode mode, const char *cmdtext) {
  if (DAS_IO::Cmd_writer::Cmd == 0) {
    if (cic_init()) return true;
  }
  return DAS_IO::Cmd_writer::Cmd->sendcmd(mode, cmdtext);
}

int ci_sendfcmd(DAS_IO::Cmd_Mode mode, const char *fmt, ...) {
  va_list arg;
  char cmdbuf[CMD_INTERP_MAX];

  va_start(arg, fmt);
  vsprintf(cmdbuf, fmt, arg);
  va_end(arg);
  return(ci_sendcmd(mode, cmdbuf));
}
