/** @file cmd_hdr_parser.cc 
 */
#include <cstring>
#include <cctype>
#include "nl.h"
#include "dasio/appid.h"
#include "dasio/cmd_server.h"
#include "dasio/msg.h"

namespace DAS_IO {

cmd_hdr_parser::cmd_hdr_parser() {
  int len = strlen(AppID.name);
  hdrID_default = (char*)new_memory(len+1);
  memcpy(hdrID_default, AppID.name, len+1);
  for (int i = 0; i <= len; ++i) {
    char c = hdrID_default[i];
    if (c == '#' || c == ':' || c == ']')
      hdrID_default[i] = '_';
  }
  hdrID_len = 20;
  hdrID_buf = (char*)new_memory(hdrID_len);
  SN = 0;
  mode = 0;
  cmd = 0;
  fmtcmd[0] = '\0';
}

cmd_hdr_parser::~cmd_hdr_parser() {
  if (hdrID_buf) {
    nl_free_memory(hdrID_buf);
    hdrID_buf = 0;
  }
  if (hdrID_default) {
    nl_free_memory(hdrID_default);
    hdrID_default = 0;
  }
}

/**
 * @param ibuf Pointer to command string
 * The string at ibuf must remain unchanged until the
 * command has been fully processed.
 * Checks the command string for header data and sets
 * hdrID_buf, SN, mode and cmd values accordingly.
 * If no header is present, hdrID_buf[0], SN and mode
 * will all be set to zero.
 * @return true if a syntax error is found.
 */
bool cmd_hdr_parser::parse(const unsigned char *ibuf) {
  SN = 0;
  mode = 0;
  cmd = 0;
  fmtcmd[0] = '\0';
  hdrID_buf[0] = '\0';
  if (ibuf == 0) {
    mode = 'X';
    cmd = (const unsigned char *)"\n";
    return false;
  }
  int i = 0;
  if (ibuf[i] == '[') {
    for (++i; ibuf[i]; ++i) {
      switch (ibuf[i]) {
        case '#':
        case ':':
        case ']':
          break;
        default:
          continue;
      }
      break;
    }
    int IDlen = i-1;
    if (IDlen > 0) {
      if (IDlen+1 > hdrID_len) {
        nl_free_memory(hdrID_buf);
        hdrID_len = IDlen+1;
        hdrID_buf = (char*)new_memory(hdrID_len);
      }
      memcpy(hdrID_buf, &ibuf[1], IDlen);
    }
    hdrID_buf[IDlen] = '\0';
    if (ibuf[i] == '#') {
      for (++i; isdigit((unsigned char)ibuf[i]); ++i) {
        SN = SN * 10 + ibuf[i] - '0';
      }
    }
    if (ibuf[i] == ':') {
      mode = ibuf[++i];
      ++i;
    }
    if (ibuf[i] != ']') {
      msg(2, "cmd_hdr_parser: missing closing header bracket");
      return true;
    }
    ++i;
  }
  cmd = &ibuf[i];
  if (!chk_trailing(cmd, "\n")) {
    msg(2, "cmd_hdr_parser: missing or multiple newlines");
    return true;
  }
  return false;
}

/**
 * @return true if ibuf ends with the suffix string
 */
bool cmd_hdr_parser::chk_trailing(const unsigned char *ibuf, const char *suffix) {
  while (*ibuf != *suffix && *ibuf) ++ibuf;
  while (*ibuf == *suffix && *ibuf && *suffix) {
    ++ibuf;
    ++suffix;
  }
  return !(*ibuf || *suffix);
}

/**
 * Formats the previously parsed command into fmtcmd.
 * @return The number of characters in fmtcmd. Zero on overflow
 */
int cmd_hdr_parser::format() {
  int nc = 0;
  nc = snprintf(fmtcmd, remaining(nc), "[%s", hdrID());
  if (SN) {
    nc += snprintf(&fmtcmd[nc], remaining(nc), "#%d", SN);
  }
  if (mode) {
    if (mode == 'V') {
      nc += snprintf(&fmtcmd[nc], remaining(nc), ":%c%s", mode, cmd);
      return retcode(nc);
    } else {
      nc += snprintf(&fmtcmd[nc], remaining(nc), ":%c", mode);
    }
  }
  nc += snprintf(&fmtcmd[nc], remaining(nc), "]%s", cmd);
  if (nc >= Cmd_Server::MAX_COMMAND_IN)
    msg(2, "cmd_hdr_parser: command overflow");
  return retcode(nc);
}

int cmd_hdr_parser::latest_SN = 0;

void cmd_hdr_parser::assign_sn() {
  if (SN == 0) {
    SN = ++latest_SN;
  } else {
    // We expect this when using a Relay
    msg(MSG_DEBUG, "assign_sn: already assigned");
  }
}

cmd_hdr_parser::recent_SN_t cmd_hdr_parser::recent_SN[N_SN_MAX];
int cmd_hdr_parser::first_SN_idx = -1;
int cmd_hdr_parser::N_SN = 0;
int cmd_hdr_parser::recent_retrans = 0;

/**
 * @return true if the specified SN has been seen recently
 */
bool cmd_hdr_parser::check_sn() {
  msg(MSG_DEBUG, "check_sn %d", SN);
  if (SN) {
    msg(MSG_DEBUG, "check_sn idx:%d N_SN:%d", first_SN_idx, N_SN);
    if (first_SN_idx < 0 || first_SN_idx >= N_SN_MAX) {
      first_SN_idx = 0;
      N_SN = 0;
    }
    if (N_SN > 0) {
      for (int N = 0; N < N_SN; ++N) {
        int i = first_SN_idx + N;
        if (i >= N_SN_MAX) i -= N_SN_MAX;
        if (recent_SN[i].SN == SN) {
          ++recent_SN[i].retrans;
          ++recent_retrans;
          return true;
        }
      }
    }
    // Now we have a new SN
    if (N_SN < N_SN_MAX) {
      ++N_SN;
      int i = first_SN_idx + N_SN;
      recent_SN_t *rSN = &recent_SN[i];
      rSN->SN = SN;
      rSN->retrans = 0;
    } else {
      recent_SN_t *rSN = &recent_SN[first_SN_idx];
      recent_retrans -= rSN->retrans;
      rSN->SN = SN;
      rSN->retrans = 0;
      if (++first_SN_idx >= N_SN_MAX) {
        first_SN_idx = 0;
      }
    }
  }
  return false;
}

} // namespace DAS_IO
