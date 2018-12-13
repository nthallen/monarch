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
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <regex.h>
#include "dasio/interface.h"
#include "nl.h"
#include "msg.h"
#include "nl_assert.h"

bool DAS_IO::Interface::not_found(unsigned char c) {
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

bool DAS_IO::Interface::not_hex( uint16_t &hexval ) {
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

bool DAS_IO::Interface::not_int( int &val ) {
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

bool DAS_IO::Interface::not_str( const char *str_in, unsigned int len ) {
  unsigned int start_cp = cp;
  unsigned int i;
  const unsigned char *str = (const unsigned char *)str_in;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    nl_error( 4, "DAS_IO::Interface precondition failed: "
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

bool DAS_IO::Interface::not_str( const char *str ) {
  return not_str(str, strlen(str));
}

bool DAS_IO::Interface::not_str(const std::string &s) {
  return not_str(s.c_str(), s.length());
}

bool DAS_IO::Interface::not_float( float &val ) {
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

/* Added from TCCON/coelostat.cc by Miles, 6th December 2018 */
bool DAS_IO::Interface::not_fix(int fix, int16_t &val) {
  int saw_decimals = 0, saw_neg = 0, saw_digits = 0;

  val = 0;
  if (buf[cp] == '-') {
    saw_neg = 1;
    ++cp;
  }
  while (cp < nc) {
    if ( isdigit(buf[cp]) ) {
      saw_digits = 1;
      val = val * 10 + buf[cp++] - '0';
      if ( saw_decimals && saw_decimals++ == fix ) break;
    } else if ( !saw_decimals && buf[cp] == '.' ) {
      ++cp;
      saw_decimals = 1;
    } else break;
  }
  if ( saw_decimals == 0 ) {
    // report_err("Missing decimal point at col %d", cp);
    while ( ++saw_decimals <= fix ) val *= 10;
  }
  if ( !saw_digits ) {
    report_err("No digits in not_fix at col %d", cp);
    return true;
  }
  if (saw_neg) val = -val;
  return false;
}

bool DAS_IO::Interface::not_alternate(int &is_first, const char *first,
                                  const char *second) {
  uint16_t start_cp = cp;
  uint16_t i;
  int is_second = 1;
  int chk_first = 1;
  int chk_second = 1;
  is_first = 1;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    nl_error( 4, "Ser_Sel precondition failed: "
      "cp = %d, nc = %d, buf %s",
      cp, nc, buf ? "not NULL" : "is NULL" );
  for (i = 0; cp < nc && (chk_first || chk_second); ++i, ++cp) {
    if ( chk_first ) {
      if (first[i] == '\0') break;
      else if (first[i] != buf[start_cp+i] ) {
        is_first = 0;
        chk_first = 0;
      }
    }
    if ( chk_second ) {
      if (second[i] == '\0') break;
      else if (second[i] != buf[start_cp+i] ) {
        is_second = 0;
        chk_second = 0;
      }
    }
  }
  if (!(is_first || is_second)) {
    report_err( "Expected '%s' or '%s' at column %d",
          first, second, start_cp );
    return true;
  }
  return false;
}

int DAS_IO::Interface::match(const char *str) {
  int i;
  for (i = 0; cp+i < nc && *str != '\0' && buf[cp+i] == *str; ++i, ++str);
  if (*str == '\0') return 1;
  else if (cp+i >= nc) return 0;
  else return -1;
}

bool DAS_IO::Interface::not_alt(const char *alt1, const char *alt0, int &is_alt1,
	  const char *context) {
  int rv1, rv0;
  is_alt1 = -1;
  rv1 = match(alt1);
  if (rv1 > 0) {
    is_alt1 = 1; // definite match
    consume(nc);
    return false;
  } else {
    rv0 = match(alt0);
    if (rv0 > 0) {
      is_alt1 = 0; // definite match
      consume(nc);
      return false;
    }
  }
  if (rv0 == 0 || rv1 == 0) return false;
  report_err("Unexpected string for '%s'", context);
  consume(nc);
  return true;
}

bool DAS_IO::Interface::not_any(const char *alternatives) {
  if (cp < nc) {
    for (const char *alt = alternatives; *alt; ++alt) {
      if (buf[cp] == *alt) {
        ++cp;
        return false;
      }
    }
    report_err("No match for alternatives '%s' at column %d", alternatives, cp);
  }
  return true;
}

bool DAS_IO::Interface::not_bin(uint16_t &word, int nbits) {
  int nbits_in = nbits;
  while (cp < nc && isspace(buf[cp])) {
    ++cp;
  }
  word = 0;
  while (nbits > 0 && cp < nc && (buf[cp] == '0' || buf[cp] == '1')) {
    word = (word<<1) | (buf[cp++]-'0');
    --nbits;
  }
  if (nbits > 0) {
    if (cp < nc)
      report_err("Invalid bit in not_bin(%d) at column %d after %d bits",
	nbits_in, cp, nbits_in-nbits);
    return true;
  }
  return false;
}

bool DAS_IO::Interface::not_ndigits(int n, int &value) {
  int i = n;
  value = 0;
  while ( i > 0 && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    --i;
  }
  if (i > 0) {
    if (cp < nc)
      report_err("Expected %d digits at column %d", n, cp+i-n);
    return true;
  }
  return false;
}

bool DAS_IO::Interface::not_uint16(uint16_t &val) {
  val = 0;
  if (buf[cp] == '-') {
    if (isdigit(buf[++cp])) {
      while (isdigit(buf[cp])) {
        ++cp;
      }
      if (cp < nc)
        report_err("not_ushort: Negative int truncated at col %d", cp);
    } else {
      if (cp < nc)
        report_err("Found '-' and no digits at col %d", cp);
      return true;
    }
  } else if (isdigit(buf[cp])) {
    while (isdigit(buf[cp])) {
      val = val*10 + buf[cp++] - '0';
    }
  } else {
    if (cp < nc)
      report_err("not_ushort: no digits at col %d", cp);
    return true;
  }
  return false;
}

bool DAS_IO::Interface::not_ISO8601(double *Time) {
  struct tm buft;
  float secs;
  time_t ltime;

  if (not_ndigits(4, buft.tm_year) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mon) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str("T", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(secs))
    return true;
  buft.tm_year -= 1900;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("mktime returned error");
  else *Time = ltime + secs;
  return false;
}

bool DAS_IO::Interface::not_nfloat(float *value) {
  float val;
  while (cp < nc && buf[cp] == ' ') ++cp;
  if (cp >= nc) return true;
  if (buf[cp] == ',' || buf[cp] == '\r' || buf[cp] == '\n') {
    *value = 99999.;
    return false;
  }
  if (not_float(val)) return true;
  *value = val;
  return false;
}

bool DAS_IO::Interface::not_double( double *value ) {
  char *endptr;
  int ncf;
  const char* KW;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    msg( 4, "%s not_float precondition failed: "
      "cp = %d, nc = %d, buf %s",
      KW, cp, nc, buf ? "not NULL" : "is NULL" );
  *value = strtod( (char*)&buf[cp], &endptr );
  ncf = endptr - (char*)&buf[cp];
  if ( ncf == 0 ) {
    report_err( "%s Expected float at column %d", KW, cp );
    return true;
  } else {
    nl_assert( ncf > 0 && cp + ncf <= nc );
    cp += ncf;
    return false;
  }
}

bool DAS_IO::Interface::not_ISO8601(double *Time, bool w_hyphens) {
  struct tm buft;
  float secs;
  time_t ltime;
  const char* KW;

  if (not_ndigits(4, buft.tm_year) ||
      (w_hyphens && not_str("-",1)) ||
      not_ndigits(2, buft.tm_mon) ||
      (w_hyphens && not_str("-",1)) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str("T", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(secs))
    return true;
  buft.tm_year -= 1900;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("%s mktime returned error", KW);
  else *Time = ltime + secs;
  return false;
}

bool DAS_IO::Interface::not_nfloat(float *value, float NaNval) {
  float val;
  while (cp < nc && buf[cp] == ' ') ++cp;
  if (cp >= nc) return true;
  if (buf[cp] == ',' || buf[cp] == '\r' || buf[cp] == '\n') {
    *value = NaNval;
    return false;
  }
  if (strncasecmp((const char *)&buf[cp], "NaN", 3) == 0) {
    cp += 3;
    *value = NaNval;
    return false;
  }
  if (not_float(val)) return true;
  *value = val;
  return false;
}

bool DAS_IO::Interface::not_uchar(unsigned char &val) {
  int sval;
  const char* KW;
  if (not_int(sval)) return true;
  if (sval < 0 || sval > 255) {
    report_err("%s uchar value out of range: %d", KW, sval);
    return true;
  }
  val = sval;
  return false;
}

bool DAS_IO::Interface::not_KW(char *KWbuf) {
  int KWi = 0;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  while (cp < nc && KWi < 30 && !isspace(buf[cp]) &&
         buf[cp] != ',') {
    KWbuf[KWi++] = buf[cp++];  
  }
  if (KWi >= 30) {
    report_err("Keyword overflow");
    return true;
  } else if (buf[cp] == ',') {
    KWbuf[KWi] = '\0';
    ++cp;
    return false;
  } else {
    report_err("Unexpected char in not_KW");
    return true;
  }
}