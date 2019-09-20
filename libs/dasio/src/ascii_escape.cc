/** @file ascii_escape.cc */
#include <string.h>
#include "dasio/ascii_escape.h"

const char *ascii_escape(const char *ibuf, int len) {
  static std::string s;
  char snbuf[8];
  int ix = 0, nb;
  s.clear();
  while (ix < len ) {
    unsigned char c = ibuf[ix++];
    if ( isprint(c) ) {
      s.push_back(c);
    } else {
      switch ( c ) {
        case '\n':
          s.push_back('\\');
          s.push_back('n');
          break;
        case '\r':
          s.push_back('\\');
          s.push_back('r');
          break;
        case '\t':
          s.push_back('\\');
          s.push_back('t');
          break;
        default:
          nb = snprintf( snbuf, 8, "\\x%02x", c);
          s.append(snbuf);
          break;
      }
    }
  }
  return s.c_str();
}

const char *ascii_escape(const std::string &s) {
  return ascii_escape(s.c_str(), s.length());
}

/**
 * Named differently to disambiguate from C version
 * in nortlib2. Invokes the C++ versions, which
 * have no inherent length limitation and can deal
 * with embedded NULs.
 */
const char *ascii_esc(const char *str) {
  return ascii_escape(str, strlen(str));
}
