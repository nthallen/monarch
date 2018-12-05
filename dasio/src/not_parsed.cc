/** @file not_parsed.cc
 * Parsing routines useful for parsing ASCII input data.
 * All of these operate on buf with the current offset
 * at cp and the total number of characters being nc.
 * These all return true if the thing they are looking
 * for was not found. The idea is to string a bunch
 * of these together as:
 *  if (not_a() || not_b() || not_c()) {
 *    report_err("Something went wrong");
 *  } else {
 *    process
 *  }
 * If the error occurs before the end of the input, then
 * an error message is reported via report_err(). In general
 * this should mean that the only error that would need to
 * be manually reported would be for syntax that is not
 * supported by one of the not_*() functions or a timeout.
 */
#include "dasio.h"

#ifdef IMPLEMENTED

bool DAS_IO_Interface::not_found(unsigned char c) {
  while ( cp < nc ) {
    if ( buf[cp++] == c )
      return false;
  }
  if ( nc ) {
    report_err( "Synch char '%c' not found", c );
    nc = cp = 0;
  }
  return true;
}

bool DAS_IO_Interface::not_hex( unsigned short &hexval ) {
  hexval = 0;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  if (! isxdigit(buf[cp])) {
    if (cp < nc)
      report_err("No hex digits at col %d", cp);
    return true;
  }
  while ( cp < nc && isxdigit(buf[cp]) ) {
    unsigned short digval = isdigit(buf[cp]) ? ( buf[cp] - '0' ) :
           ( tolower(buf[cp]) - 'a' + 10 );
    hexval = hexval * 16 + digval;
    ++cp;
  }
  return false;
}

bool DAS_IO_Interface::not_int( int &val ) {
  bool negative = false;
  // fillbuf() guarantees the buffer will be NUL-terminated, so any check
  // that will fail on a NUL is OK without checking the cp < nc
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  if (cp < nc && buf[cp] == '-') {
    negative = true;
    ++cp;
  } else if (cp < nc && buf[cp] == '+') ++cp;
  if ( cp < nc && isdigit(buf[cp]) ) {
    val = buf[cp++] - '0';
    while ( cp < nc && isdigit(buf[cp]) ) {
      val = 10*val + buf[cp++] - '0';
    }
    if (negative) val = -val;
    return false;
  } else {
    if ( cp < nc )
      report_err( "Expected int at column %d", cp );
    return true;
  }
}

bool DAS_IO_Interface::not_str( const char *str_in, unsigned int len ) {
  unsigned int start_cp = cp;
  unsigned int i;
  const unsigned char *str = (const unsigned char *)str_in;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    nl_error( 4, "DAS_IO_Interface precondition failed: "
      "cp = %d, nc = %d, buf %s",
      cp, nc, buf ? "not NULL" : "is NULL" );
  for (i = 0; i < len; ++i) {
    if ( cp >= nc ) {
      return true; // full string is not present
    } else if ( str[i] != buf[cp] ) {
      report_err( "Expected string '%s' at column %d",
        ascii_escape(str_in, len), start_cp );
      return true;
    }
    ++cp;
  }
  return false;
}

bool DAS_IO_Interface::not_str( const char *str ) {
  return not_str(str, strlen(str));
}

bool DAS_IO_Interface::not_str(const std::string &s) {
  return not_str(s.c_str(), s.length());
}

bool DAS_IO_Interface::not_float( float &val ) {
  char *endptr;
  int start_cp = cp;
  int ncf;
  if ( cp < 0 || cp > nc || nc < 0 || nc >= bufsize || buf == 0 )
    msg( 4, "Ser_Sel precondition failed: "
      "cp = %d, nc = %d, bufsize = %d, buf %s",
      cp, nc, bufsize, buf ? "not NULL" : "is NULL" );

  if (cp >= nc) return true;
  if (buf[cp] == '-') {
    if (++cp >= nc) return true;
  }
  if (buf[cp] == '.') {
    if (++cp >= nc) return true;
    if (isdigit(buf[cp])) {
      do { ++cp; }
        while (cp < nc && isdigit(buf[cp]));
    } else {
      return true;
    }
  } else if (isdigit(buf[cp])) {
    do { ++cp; }
      while (cp < nc && isdigit(buf[cp]));
    if (cp < nc && buf[cp] == '.') {
      do { ++cp; }
        while (cp < nc && isdigit(buf[cp]));
    }
  } else {
    report_err("not_float expected [0-9.] at col %d", cp);
    return true;
  }
  if (cp < nc && tolower(buf[cp]) == 'e') {
    if (++cp >= nc) return true;
    if (buf[cp] == '+' || buf[cp] == '-') {
      if (++cp >= nc) return true;
    }
    if (isdigit(buf[cp])) {
      do { ++cp; } while (cp < nc && isdigit(buf[cp]));
    } else {
      report_err("not_float expected digits at col %d", cp);
      return true;
    }
  }

  val = strtof( (char *)&buf[start_cp], &endptr );
  if (endptr == (char *)&buf[cp]) {
    return false;
  }
  ncf = endptr - (char *)buf;
  report_err("strtof at col %d ended at col %d, not %d",
    start_cp, ncf, cp);
  return true;
}

#endif