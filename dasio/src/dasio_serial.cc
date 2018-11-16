/** @file dasio_serial.cc */
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "nl.h"
#include "dasio_serial.h"

DAS_IO_Serial::DAS_IO_Serial(const char *iname, int bufsz) : DAS_IO_Interface(iname, bufsz) {
  termios_init = false;
}

DAS_IO_Serial::DAS_IO_Serial(const char *iname, int bufsz, const char *path, int open_flags)
    : DAS_IO_Serial(iname, bufsz) {
  init(path, open_flags);
}

DAS_IO_Serial::~DAS_IO_Serial() {}

void DAS_IO_Serial::init(const char *path, int open_flags) {
  termios_init = false;
  if (path == 0) {
    fd = -1;
  } else {
    fd = open(path, open_flags);
    if (fd < 0) {
      if (nl_response > NLRSP_QUIET)
        nl_error(nl_response, "%s: Unable to open device at %s: %s",
          iname, path, strerror(errno));
    } else {
      switch (open_flags & O_ACCMODE) {
        case O_RDWR:
        case O_RDONLY:
          flags |= Fl_Read;
          break;
      }
    }
  }
}

#ifdef PARSTK
  #define STICK_OPT PARSTK
#else
  #ifdef CMSPAR
    #define STICK_OPT CMSPAR
  #endif
#endif

void DAS_IO_Serial::setup( int baud, int bits, char par, int stopbits,
                int min, int time ) {
  int bitsflag;

  if ( fd < 0 ) return;
  if ( termios_init == false && tcgetattr( fd, &termios_p) ) {
    nl_error( 2, "Error on tcgetattr: %s", strerror(errno) );
    return;
  }
  termios_init = true;
  termios_p.c_iflag = 0;
  termios_p.c_lflag &= ~(ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL);
  termios_p.c_cflag = CLOCAL|CREAD;
  termios_p.c_oflag &= ~(OPOST);
  termios_p.c_ispeed = termios_p.c_ospeed = baud;
  switch (bits) {
    case 5: bitsflag = CS5; break;
    case 6: bitsflag = CS6; break;
    case 7: bitsflag = CS7; break;
    case 8: bitsflag = CS8; break;
    default:
      nl_error( 3, "Invalid bits value: %d", bits );
  }
  termios_p.c_cflag |= bitsflag;
  switch (par) {
    case 'n': bitsflag = 0; break;
    case 'e': bitsflag = PARENB; break;
    case 'o': bitsflag = PARENB|PARODD; break;
#ifdef STICK_OPT
    case 'm': bitsflag = PARENB|PARODD|STICK_OPT; break;
    case 's': bitsflag = PARENB|STICK_OPT; break;
#endif
    default:
      nl_error( 3, "Invalid parity selector: '%c'", par );
  }
  termios_p.c_cflag |= bitsflag;
  switch (stopbits) {
    case 1: break;
    case 2: termios_p.c_cflag |= CSTOPB; break;
    default:
      nl_error(3, "Invalid number of stop bits: %d", stopbits );
  }
  termios_p.c_cc[VMIN] = min;
  termios_p.c_cc[VTIME] = time;
  if ( tcsetattr(fd, TCSANOW, &termios_p) )
    nl_error( 2, "Error on tcsetattr: %s", strerror(errno) );
}

void DAS_IO_Serial::update_tc_vmin(int new_vmin) {
  if (! termios_init) {
    if (tcgetattr(fd, &termios_p)) {
      nl_error(2, "Error from tcgetattr: %s",
        strerror(errno));
    }
    termios_init = true;
  }
  if (new_vmin < 1) new_vmin = 1;
  if (new_vmin != termios_p.c_cc[VMIN]) {
    termios_p.c_cc[VMIN] = new_vmin;
    if (tcsetattr(fd, TCSANOW, &termios_p)) {
      nl_error(2, "Error from tcsetattr: %s",
        strerror(errno));
    }
  }
}

void DAS_IO_Serial::flush_input() {
  do {
    nc = cp = 0;
    if (fillbuf()) return;
  } while (nc > 0);
}
