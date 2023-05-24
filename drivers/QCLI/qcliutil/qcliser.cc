// #include <sys/dev.h> // need for dev_read() in QNX4
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dasio/serial.h>
#include <dasio/loop.h>
#include "nl.h"
#include "oui.h"
#include "qcliutil.h"

using namespace DAS_IO;

#define MAX_STATUS_WORDS 1024
#define SBUFSIZE (MAX_STATUS_WORDS*sizeof(uint16_t))

class qcli_ser : public Serial {
	public:
		qcli_ser(const char *port);
		bool protocol_input();
		bool protocol_timeout();
		int readcond(uint8_t *extbuf, int bufsize);
		inline bool qwrite(const char *xbuf, int nbytes) { return iwrite(xbuf, nbytes); }
	protected:
};

qcli_ser::qcli_ser(const char *port) : Serial("qclis", SBUFSIZE, port, O_RDWR) {
	setup(57600,8,'n',1,SBUFSIZE,4);
	hwflow_enable(true);
}

bool qcli_ser::protocol_input() {
	return true;
}

bool qcli_ser::protocol_timeout() {
	return true;
}

int qcli_ser::readcond(uint8_t *extbuf, int xbufsize) {
	TO.Set(0, 400);
	flags |= Fl_Timeout;
	ELoop->event_loop();
	int rv = nc < xbufsize ? nc : xbufsize;
	memcpy((char *)extbuf, buf, rv);
	consume(rv);
	TO.Clear();
	return rv;
}

static qcli_ser *qclis;
static Loop *qcli_loop;

qcli_util::qcli_util(/* const char *service, const char *sub_service */)
      : vreq(0) {
}

/* uint16_t qcli_util:read_qcli(int fresh);
   If fresh is non-zero, it means a command has just
   been issued, and we want to give the QCLI time
   to process that command before requesting status.
   I believe that with the serial interface, we
   will need to send a NOP command every time we
   want to read from the QCLI. My reasoning is
   that when fresh is non-zero, although a status
   word is already being transmitted, we will
   need to request another 'fresher' one, and
   when fresh is zero, no prior command has
   been issued, so we need to request a new
   status anyway. The only difference between
   fresh and !fresh is whether we add an
   additional delay before senqcding the NOP
*/
uint16_t qcli_util::read_qcli(bool fresh) {
  uint8_t buf[SBUFSIZE];
  uint16_t status;
  bool rv;
  static int responding = 1;
  
  /* I'll remove this delay since the write always
     has a delay */
  if ( fresh ) delay(3);
  while ( 1 ) {
    write_qcli( QCLI_NOOP );
    rv = qclis->readcond(buf, SBUFSIZE);
    if ( rv == 0 || (rv == -1 && errno == EAGAIN) ) {
      if ( responding ) {
        msg( 2, "QCLI is not responding" );
        responding = 0;
      }
      return 0;
    } else if ( rv == -1 ) {
      msg( 1, "readcond() returned error %d: %s",
            errno, strerror(errno) );
      return 0;
    } else if ( rv & 1 ) {
      msg( 2, "QCLI returned an odd number of bytes (%d)", rv );
      continue;
    } else {
      if ( rv == SBUFSIZE )
        msg( 1, "Input buffer is full" );
      if ( !responding )
        msg( 0, "QCLI is responding" );
      responding = 1;
      status = (buf[rv-2]<<8) + buf[rv-1];
      return status;
    }
  }
}

void qcli_util::write_qcli( uint16_t value ) {
  char buf[3];
  int rv;
  
  buf[0] = value >> 8;
  buf[1] = value & 0xFF;
	if (qclis->qwrite(buf, 2))
//    if (write( qcli_fd, buf, 2 ))
    msg( 1, "qwrite() returned error");
  /* This delay is intended to prevent the FIFO from
     overflowing */
  /* delay3msec(); */
}

uint16_t qcli_util::wr_rd_qcli( uint16_t value ) {
  write_qcli( value );
  return read_qcli(1);
}

void qcli_util::wr_stop_qcli(  uint16_t value ) {
  wr_rd_qcli( value );
}

static void qcli_port_init( const char *port ) {
	qclis = new qcli_ser(port);
	qcli_loop = new Loop();
	qcli_loop->add_child(qclis);
/*   qcli_fd = open( port, O_RDWR );
  if ( qcli_fd == -1 )
    msg( 3, "Unable to open serial port '%s': %s",
      port, strerror(errno) );
 */
}

void qclisrvr_init( int argc, char **argv ) {
  int c;
  const char *port = "/dev/ser1";

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'p':
        port = optarg;
        break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
    }
  }
  qcli_port_init( port );
}
