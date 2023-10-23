/** @file ascii_escape.cc */
#include <string.h>
#include "dasio/ascii_escape.h"
#include "nl.h"

void dump_hex(int msgcode, const char *hdr,
                     const char *ibuf, int len) {
  static std::string s;
  int offset = 0;
  while (offset < len) {
    char snbuf[8];
    int ix = 0, nb;
    s.clear();
    s.append(hdr);
    s.append(": ");
    snprintf(snbuf, 8, "%3d:", offset);
    s.append(snbuf);
    for (ix = 0; ix < 16 && ix < len; ++ix) {
      nb = snprintf(snbuf, 8, " %02x", ibuf[offset++]);
      s.append(snbuf);
    }
    msg(msgcode, "%s", s.c_str());
  }
}
