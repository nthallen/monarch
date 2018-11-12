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

/**
 * Parsing utility function that searches forward in the buffer for the
 * specified start character. Updates cp to point just past the start
 * char. If the character is not found, the buffer is emptied.
 * @param c The search character
 * @return zero if the character is found.
 */
int DAS_IO_Interface::not_found(unsigned char c) {
  while ( cp < nc ) {
    if ( buf[cp++] == c )
      return 0;
  }
  if ( nc ) {
    report_err( "Synch char '%c' not found", c );
    nc = cp = 0;
  }
  return 1;
}

/**
 * Parsing utility function to read in a hex integer starting
 * at the current position. Integer may be proceeded by optional
 * whitespace.
 * @param[out] hexval The integer value
 * @return zero if an integer was converted, non-zero if the current char is not a digit.
 */
int DAS_IO_Interface::not_hex( unsigned short &hexval ) {
  hexval = 0;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  if (! isxdigit(buf[cp])) {
    if (cp < nc)
      report_err("No hex digits at col %d", cp);
    return 1;
  }
  while ( cp < nc && isxdigit(buf[cp]) ) {
    unsigned short digval = isdigit(buf[cp]) ? ( buf[cp] - '0' ) :
           ( tolower(buf[cp]) - 'a' + 10 );
    hexval = hexval * 16 + digval;
    ++cp;
  }
  return 0;
}

/**
 * Parsing utility function to read in a decimal integer starting
 * at the current position. Integer may be proceeded by optional
 * whitespace and an optional sign.
 * @param[out] val The integer value
 * @return zero if an integer was converted, non-zero if the current char is not a digit.
 */
int DAS_IO_Interface::not_int( int &val ) {
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
    return 0;
  } else {
    if ( cp < nc )
      report_err( "Expected int at column %d", cp );
    return 1;
  }
}

/**
 * Parsing utility function to check that the string matches the
 * input at the current position. On success, advances cp to just
 * after the matched string. On failure, cp points to the first
 * character that does not match. If only a partial record was
 * received, that could be the NUL at the end of the buffer.
 * @param str The comparison string.
 * @return zero if the string matches the input buffer.
 */
int DAS_IO_Interface::not_str( const char *str_in, unsigned int len ) {
  unsigned int start_cp = cp;
  unsigned int i;
  const unsigned char *str = (const unsigned char *)str_in;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    nl_error( 4, "DAS_IO_Interface precondition failed: "
      "cp = %d, nc = %d, buf %s",
      cp, nc, buf ? "not NULL" : "is NULL" );
  for (i = 0; i < len; ++i) {
    if ( cp >= nc ) {
      return 1; // full string is not present
    } else if ( str[i] != buf[cp] ) {
      report_err( "Expected string '%s' at column %d",
        ascii_escape(str_in, len), start_cp );
      return 1;
    }
    ++cp;
  }
  return 0;
}

int DAS_IO_Interface::not_str( const char *str ) {
  return not_str(str, strlen(str));
}

int DAS_IO_Interface::not_str(const std::string &s) {
  return not_str(s.c_str(), s.length());
}


/**
 * Parsing utility function to convert a string in the input
 * buffer to a float value. Updates cp to point just after the
 * converted string on success.
 * @param val[out] The converted value
 * @return zero if the conversion succeeded.
 */
int DAS_IO_Interface::not_float( float &val ) {
  char *endptr;
  int ncf;
  if ( cp < 0 || cp > nc || nc < 0 || nc >= bufsize || buf == 0 )
    msg( 4, "DAS_IO_Interface precondition failed: "
      "cp = %d, nc = %d, bufsize = %d, buf %s",
      cp, nc, bufsize, buf ? "not NULL" : "is NULL" );
  val = strtof( (char*)&buf[cp], &endptr );
  ncf = endptr - (char*)&buf[cp];
  if ( ncf == 0 ) {
    if ( cp < nc )
      report_err( "Expected float at column %d", cp );
    return 1;
  } else {
    nl_assert( ncf > 0 && cp + ncf <= nc );
    cp += ncf;
    return 0;
  }
}

#endif