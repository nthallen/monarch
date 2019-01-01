/**
 * \file interface.cc
 */
#include <errno.h>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "dasio/interface.h"
#include "msg.h"
#include "nl_assert.h"
#include "dasio/ascii_escape.h"

namespace DAS_IO {

/**
 * I am assuming here that this level is low enough that I don't
 * need to have two separate invocations, once for deferred
 * initialization.
 * I am currently choosing to avoid providing an output buffer
 * here.
 * @param name An identifier for the interface to be used when
 * reporting statistics.
 * @param bufsz The size of the input buffer
 */
Interface::Interface(const char *name, int bufsz) {
  iname = name;
  nc = cp = 0;
  bufsize = 0;
  buf = 0;
  fd = -1;
  flags = 0;
  ELoop = 0;
  n_fills = n_empties = n_eagain = n_eintr = 0;
  obuf = 0;
  onc = ocp = 0;
  n_errors = 0;
  n_suppressed = 0;
  total_errors = 0;
  total_suppressed = 0;
  qerr_threshold = 5;
  set_ibufsize(bufsz);
}

Interface::~Interface() {
  if (fd >= 0) {
    close(fd);
    fd = -1;
  }
  set_ibufsize(0);
}

/**
 * Virtual method to allow an interface to bid on the select() timeout
 * along with the Loop. The minimum timeout value is used.
 * @return a Timeout * indicating the requested timeout value or NULL.
 */
Timeout *Interface::GetTimeout() {
  return &TO;
}

bool Interface::ProcessData(int flag) {
  // nl_error(0, "%s: Interface::ProcessData(%d)", iname, flag);
  if ((flags & flag & gflag(0)) && tm_sync())
    return true;
  if ((flags&Fl_Read) && (flags&flag&(Fl_Read|Fl_Timeout))) {
    if (fillbuf()) return true;
    if (protocol_input())
      return true;
  }
  if ((flags & flag & Fl_Write) && iwrite_check())
    return true;
  if ((flags & flag & Fl_Except) && protocol_except())
    return true;
  if ((flags & flag & Fl_Timeout) && TO.Expired() && protocol_timeout())
    return true;
  if (TO.Set()) {
    flags |= Fl_Timeout;
  } else {
    flags &= ~Fl_Timeout;
  }
  return false;
}

/**
 * Sets up a write of nc bytes from the buffer pointed to by str.
 * If the write cannot be accomplished immediately, the information
 * is saved and handled transparently. The caller is
 * responsible for allocating the output buffer(s) and ensuring
 * they are not overrun.
 * The caller can check whether ocp >= onc to determine whther the
 * write has completed.
 * @param str Pointer to the output buffer
 * @param nc The total number of bytes in the output buffer
 * @param cp The starting offset within the output buffer
 * @return true if a fatal error occurs
 */
bool Interface::iwrite(const char *str, unsigned int nc, unsigned int cp) {
  nl_assert(fd >= 0);
  nl_assert(ocp >= onc);
  obuf = (unsigned char *)str;
  onc = nc;
  ocp = cp;
  return iwrite_check();
}

bool Interface::iwrite_check() {
  if (!obuf_empty()) {
    int nb = onc-ocp;
    int ntr = write(fd, obuf+ocp, nb);
    if (ntr < 0 && errno != EAGAIN) {
      flags &= ~Fl_Write;
      return(iwrite_error(errno));
    }
    if (ntr > 0) {
      ocp += ntr;
      iwritten(ntr);
    }
  }
  flags = obuf_empty() ?
    flags & ~Fl_Write :
    flags | Fl_Write;
  return false;
}

bool Interface::iwrite(const std::string &s) {
  return iwrite(s.c_str(), s.length());
}

bool Interface::iwrite(const char *str) {
  return iwrite(str, strlen(str));
}

/**
 * The default implementation does nothing.
 */
void Interface::iwritten(int nb) {}

/**
 * The default implementation returns true.
 */
bool Interface::iwrite_error(int my_errno) {
  nl_error(2, "%s: write error %d: %s", iname, my_errno, strerror(my_errno));
  return true;
}

/**
 * The default function returns true.
 */
bool Interface::read_error(int my_errno) {
  nl_error(2, "%s: read error %d: %s", iname, my_errno, strerror(my_errno));
  return true;
}

/**
 * The default reports unexpected input and returns false;
 */
bool Interface::protocol_input() {
  cp = 0;
  if (nc > 0)
    report_err("Unexpected input");
  return false;
}

/**
 * The default does nothing and returns false.
 */
bool Interface::protocol_timeout() {
  return false;
}

/**
 * The default does nothing and returns false.
 */
bool Interface::protocol_except() {
  return false;
}

/**
 * The default does nothing and returns false.
 */
bool Interface::tm_sync() {
  return false;
}

bool Interface::closed() {
  return true;
}

void Interface::set_ibufsize(int bufsz) {
  if (bufsize != bufsz) {
    if (buf) free_memory(buf);
    bufsize = bufsz;
    buf = bufsize ? (unsigned char *)new_memory(bufsz) : 0;
  }
}

bool Interface::fillbuf(int N) {
  int i;
  if (!buf) nl_error(4, "Ser_Sel::fillbuf with no buffer");
  if (N > bufsize)
    nl_error(4, "Ser_Sel::fillbuf(N) N > bufsize: %d > %d",
      N, bufsize);
  if (nc > N-1) return false;
  ++n_fills;
  i = read( fd, &buf[nc], N - 1 - nc );
  if ( i < 0 ) {
    if ( errno == EAGAIN ) {
      ++n_eagain;
    } else if (errno == EINTR) {
      ++n_eintr;
    } else {
      return read_error(errno);
    }
    return false;
  } else if (i == 0) {
    return closed();
  }
  nc += i;
  buf[nc] = '\0';
  return false;
}

void Interface::consume(int nchars) {
  if ( nchars > 0 ) {
    ++n_empties;
    if ( nchars < nc ) {
      int nb = nc - nchars;
      memmove(&buf[0], &buf[nchars], nb+1);
      nc = nb;
    } else {
      nc = 0;
    }
    cp = 0;
  }
}

void Interface::report_err( const char *fmt, ... ) {
  ++total_errors;
  // Here we're counting up only if there is a threshold and we're still under it
  if ( qerr_threshold >= 0 && n_errors < qerr_threshold )
    ++n_errors;
  // Here we display if there is no threshold or we're under the threshold
  if ( n_suppressed == 0 && ( qerr_threshold < 0 || n_errors < qerr_threshold )) {
    va_list args;

    va_start(args, fmt);
    msgv( 2, fmt, args );
    va_end(args);
    if (nc)
      nl_error(2, "%s: Input was: '%s'", iname, ascii_escape((char*)buf, nc) );
  } else {
    if ( !n_suppressed )
      nl_error(2, "%s: Error threshold reached: suppressing errors", iname);
    ++n_suppressed;
    ++total_suppressed;
  }
}

/**
 * Signals that a successful protocol transfer occurred,
 * reducing the qualified error count, potentially reenabling
 * logging of errors.
 */
void Interface::report_ok(int nchars) {
  if ( n_errors > 0 ) {
    if ( --n_errors <= 0 && n_suppressed ) {
      nl_error( 0, "Error recovery: %d error messages suppressed", n_suppressed );
      n_suppressed = 0;
    }
  }
  if (nchars > 0) {
    consume(nchars);
  }
}

}
