/** @file ascii_escape.cc */
#include <string.h>
#include "dasio/ascii_escape.h"
#include "nl.h"

void dump_hex(int msgcode, const char *hdr,
                     const char *ibuf, int len) {
  static std::string s;
  while (len) {
    char snbuf[8];
    int ix = 0, nb;
    s.clear();
    s.append(hdr);
    s.append(": ");
    for (ix = 0; ix < 16 && ix < len; ++ix) {
      nb = snprintf(snbuf, 8, " %02x", ibuf[ix]);
      s.append(snbuf);
    }
    msg(msgcode, "%s", s.c_str());
    ibuf += ix;
    len -= ix;
  }
}
