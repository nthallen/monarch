#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <sys/iofunc.h>
// #include <sys/dispatch.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include "subbusd_serusb.h"
#include "nl_assert.h"
#include "dasio/ascii_escape.h"

// static char sb_ibuf[SB_SERUSB_MAX_RESPONSE];
// static int sb_ibuf_idx = 0;
// static sbd_request_t sbdrq[SUBBUSD_MAX_REQUESTS];
// static sbd_request_t *cur_req;
// static unsigned int sbdrq_head = 0, sbdrq_tail = 0;
// static int sb_fd;
// static struct sigevent ionotify_event;
// static timer_t timeout_timer;
// static struct itimerspec timeout_enable, timeout_disable;
// static int n_timeouts = 0;

// static int n_writes = 0;
// static int n_reads = 0;
// static int n_part_reads = 0;
// static int n_compound_reads = 0;

// static void dequeue_request( signed short status, int n_args,
  // uint16_t arg0, uint16_t arg1, char *s );

// static void set_timeout( int enable ) {
  // if ( timer_settime( timeout_timer, 0,
          // enable ? &timeout_enable : &timeout_disable,
          // NULL ) == -1 ) {
    // msg( 4, "Error setting timer: %s",
      // strerror(errno) );
  // }
// }

// Transmits a request if the currently queued
// request has not been transmitted.
// static void process_request(void) {
  // int cmdlen, n;
  // int no_response = 0;
  // sbd_request_t *sbr;
  // while ( sbdrq_head != sbdrq_tail && cur_req == NULL ) {
    // nl_assert( sbdrq_head < SUBBUSD_MAX_REQUESTS );
    // sbr = &sbdrq[sbdrq_head];
    // nl_assert( sbr->status == SBDR_STATUS_QUEUED );
    // switch (sbr->type) {
      // case SBDR_TYPE_INTERNAL:
        // switch (sbr->request[0]) {
          // case '\n': // NOP
          // case 'V':  // Board Revision
            // break;
          // default:
            // msg( 4, "Invalid internal request" );
        // }
        // break;
      // case SBDR_TYPE_CLIENT:
        // switch (sbr->request[0]) {
          // case 'T':
            // no_response = 1; break;
          // case 'A':
          // case 'R':
          // case 'M':
          // case 'W':
          // case 'V':
          // case 'S':
          // case 'C':
          // case 'B':
          // case 'i':
          // case 'u':
          // case 'D':
          // case 'F':
          // case 'f':
            // break;
          // default:
            // msg( 4, "Invalid client request: '%c'", sbr->request[0] );
        // }
        // break;
      // default:
        // msg(4, "Invalid request type" );
    // }
    // cmdlen = strlen( sbr->request );
    // msg(-2, "Request: '%*.*s'", cmdlen-1, cmdlen-1, sbr->request );
    // n = write(sb_fd, sbr->request, cmdlen);
    // ++n_writes;
    // nl_assert( n == cmdlen );
    // sbr->status = SBDR_STATUS_SENT;
    // cur_req = sbr;
    // if ( no_response )
      // dequeue_request( SBS_OK, 0, 0, 0, "" );
    // else TO.set(1,0); // set_timeout(1);
  // }
// }

// /**
 // * This is where we serialize the request.
 // */
// static void enqueue_sbreq( int type, int rcvid, char *req,
        // uint16_t n_reads ) {
  // sbd_request_t *sbr = &sbdrq[sbdrq_tail];
  // int i;
  // int new_tail = sbdrq_tail+1;
  // int old_tail;
  // if ( new_tail >= SUBBUSD_MAX_REQUESTS ) new_tail = 0;
  // if ( new_tail == sbdrq_head )
    // msg( 4, "Request queue overflow" );
  // for ( i = 0; i < SB_SERUSB_MAX_REQUEST; ) {
    // if ( req[i] == '\n' ) {
      // ++i;
      // break;
    // } else if ( req[i] == '\0' ) {
      // break;
    // } else ++i;
  // }
  // if ( i >= SB_SERUSB_MAX_REQUEST )
    // msg( 4, "Request exceeds %d characters", SB_SERUSB_MAX_REQUEST-1 );
  // sbr->type = type;
  // sbr->rcvid = rcvid;
  // strncpy(sbr->request, req, i);
  // sbr->request[i] = '\0';
  // msg( -2, "Enqueued: '%*.*s'", i-1, i-1, sbr->request );
  // sbr->status = SBDR_STATUS_QUEUED;
  // sbr->n_reads = n_reads;
  // old_tail = sbdrq_tail;
  // sbdrq_tail = new_tail;
  // /* If the queue was empty, process this first request */
  // if ( sbdrq_head == old_tail ) process_request();
// }

// static int sb_data_arm(void) {
  // int cond;
  // cond = ionotify( sb_fd, _NOTIFY_ACTION_POLLARM,
    // _NOTIFY_COND_INPUT, &ionotify_event );
  // if ( cond == -1 )
    // msg( 3, "Error from ionotify: %s", strerror(errno));
  // return cond;
// }


#define RESP_OK 0
#define RESP_UNREC 1 /* Unrecognized code */
#define RESP_UNEXP 2 /* Unexpected code */
#define RESP_INV 3 /* Invalid response syntax */
#define RESP_INTR 4 /* Interrupt code */
#define RESP_ERR 5 /* Error from serusb */

/* sb_data_ready() is a thin wrapper for sb_read_usb()
   which is invoked from dispatch via pulse_attach().
 */
// static int sb_data_ready( message_context_t * ctp, int code,
        // unsigned flags, void * handle ) {
  // sb_read_usb();
  // return 0;
// }

// static int sb_timeout( message_context_t * ctp, int code,
        // unsigned flags, void * handle ) {
  // if ( ++n_timeouts > 1 ) {
    // n_timeouts = 0;
    // if ( cur_req != NULL ) {
      // msg( 1, "%sUSB request '%c' timed out",
        // (cur_req->type == SBDR_TYPE_INTERNAL) ? "Internal " : "",
        // cur_req->request[0] );
      // dequeue_request( -ETIMEDOUT, 0, 0, 0, "" );
    // }
  // }
  // return 0;
// }

/**
 * Initializes the serial parameters for the device. The min
 * and time parameters can be used to optimize reads. See
 * tcsetattr VMIN and VTIME parameters for more information.
 * @param baud The desired baud rate
 * @param bits number of data bits (5-8)
 * @param par 'n', 'e', 'o', 'm', 's' for none, even, odd, mark or space.
 * @param stopbits The number of stop bits: 1 or 2
 * @param min The minimum number of characters to respond to
 * @param time The time gap value
 */
// static void serial_setup(int fd, int baud, int bits, char par,
                         // int stopbits, int min, int time ) {
  // struct termios termios_p;
  // int bitsflag;

  // if ( fd < 0 ) return;
  // if ( tcgetattr( fd, &termios_p) ) {
    // msg( 2, "Error on tcgetattr: %s", strerror(errno) );
    // return;
  // }
  // termios_p.c_iflag = 0;
  // termios_p.c_lflag &= ~(ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL);
  // termios_p.c_cflag = CLOCAL|CREAD;
  // termios_p.c_oflag &= ~(OPOST);
  // termios_p.c_ispeed = termios_p.c_ospeed = baud;
  // switch (bits) {
    // case 5: bitsflag = CS5; break;
    // case 6: bitsflag = CS6; break;
    // case 7: bitsflag = CS7; break;
    // case 8: bitsflag = CS8; break;
    // default:
      // msg( 3, "Invalid bits value: %d", bits );
  // }
  // termios_p.c_cflag |= bitsflag;
  // switch (par) {
    // case 'n': bitsflag = 0; break;
    // case 'e': bitsflag = PARENB; break;
    // case 'o': bitsflag = PARENB|PARODD; break;
    // case 'm': bitsflag = PARENB|PARODD|PARSTK; break;
    // case 's': bitsflag = PARENB|PARSTK; break;
    // default:
      // msg( 3, "Invalid parity selector: '%c'", par );
  // }
  // termios_p.c_cflag |= bitsflag;
  // switch (stopbits) {
    // case 1: break;
    // case 2: termios_p.c_cflag |= CSTOPB; break;
    // default:
      // msg(3, "Invalid number of stop bits: %d", stopbits );
  // }
  // termios_p.c_cc[VMIN] = min;
  // termios_p.c_cc[VTIME] = time;
  // if ( tcsetattr(fd, TCSANOW, &termios_p) )
    // msg( 2, "Error on tcsetattr: %s", strerror(errno) );
// }

// static void init_serusb(dispatch_t *dpp, int ionotify_pulse,
                          // int timeout_pulse) {
  // struct sigevent timeout_event;
  // sb_fd = open(serusb_port, O_RDWR | O_NONBLOCK);
  // if (sb_fd == -1)
    // msg(3,"Error opening USB subbus: %s", strerror(errno));
  // serial_setup(sb_fd, serusb_baud_rate, 8, 'n', 1, 1, 0);
  // /* flush anything in the input buffer */
  // { int n;
    // char tbuf[256];
    // do {
      // n = read(sb_fd, tbuf, 256);
      // if ( n == -1) {
        // if (errno == EAGAIN) break;
        // else msg( 3, "Error trying to clear ibuf: %s",
          // strerror(errno));
      // }
    // } while (n < 256);
  // }
  // ionotify_event.sigev_notify = SIGEV_PULSE;
  // ionotify_event.sigev_code = ionotify_pulse;
  // ionotify_event.sigev_priority = getprio(0);
  // ionotify_event.sigev_value.sival_int = 0;
  // ionotify_event.sigev_coid =
    // message_connect(dpp, MSG_FLAG_SIDE_CHANNEL);
  // if ( ionotify_event.sigev_coid == -1 )
    // msg(3, "Could not connect to our channel: %s",
      // strerror(errno));
  // timeout_event.sigev_notify = SIGEV_PULSE;
  // timeout_event.sigev_code = timeout_pulse;
  // timeout_event.sigev_priority = getprio(0);
  // timeout_event.sigev_value.sival_int = 0;
  // timeout_event.sigev_coid = ionotify_event.sigev_coid;
  // if ( timer_create( CLOCK_REALTIME, &timeout_event,
          // &timeout_timer ) == -1 )
    // msg(3, "Could not create timer: %s",
      // strerror(errno));
  // timeout_enable.it_value.tv_sec = 0;
  // timeout_enable.it_value.tv_nsec = 100000000L; // 100 msecs
  // timeout_enable.it_interval.tv_sec = 0;
  // timeout_enable.it_interval.tv_nsec = 100000000L;

  // // timeout_enable.it_value.tv_sec = 1; // 1 sec for debugging
  // // timeout_enable.it_value.tv_nsec = 0;
  // // timeout_enable.it_interval.tv_sec = 1;
  // // timeout_enable.it_interval.tv_nsec = 0;

  // timeout_disable.it_value.tv_sec = 0;
  // timeout_disable.it_value.tv_nsec = 0;
  // timeout_disable.it_interval.tv_sec = 0;
  // timeout_disable.it_interval.tv_nsec = 0;

  // /* now arm for input */
  // sb_read_usb();
// }

subbusd_serusb_client::subbusd_serusb_client(DAS_IO::Authenticator *auth, subbusd_serusb *fl)
    : subbusd_client(auth), flavor(fl) {}
subbusd_serusb_client::~subbusd_serusb_client() {}

DAS_IO::Serverside_client *new_subbusd_serusb_client(DAS_IO::Authenticator *auth,
                                DAS_IO::SubService *ss) {
  ss = ss; // not interested
  subbusd_serusb_client *clt =
    new subbusd_serusb_client(auth, (subbusd_serusb*)ss->svc_data);
  return clt;
}

/**
 This is where we serialize the request
 The basic sanity of the incoming message has been
 checked by subbusd_client::protocol_input() before it gets here,
 so we can at least assume that the message was
 big enough to include the specified message type,
 and that the message type is defined.
 */
bool subbusd_serusb_client::incoming_sbreq() {
  // char sreq[SB_SERUSB_MAX_REQUEST];
  int rv, rsize;
  
  switch ( req->sbhdr.command ) {
    case SBC_READCACHE:
#ifdef SUBBUS_CACHE
      rep.hdr.status =
        (sb_cache_read(req->data.d1.data, &rep.data.value) < 0) ?
          SBS_NOACK : SBS_ACK;
      rep.hdr.ret_type = SBRT_US;
      rsize =
        sizeof(subbusd_rep_hdr_t) + sizeof(uint16_t);
      return iwrite((const char *)&rep, rsize);
#endif
    case SBC_READACK:
      snprintf( sreq, SB_SERUSB_MAX_REQUEST, "R%04X\n",
        req->data.d1.data );
      break;
    case SBC_MREAD:
      flavor->enqueue_request(SBDR_TYPE_CLIENT, this, req->data.d4.multread_cmd,
                    &rep, req->data.d4.n_reads);
      return false;
    case SBC_WRITECACHE:
#ifdef SUBBUS_CACHE
      rv = sb_cache_write(req->data.d0.address, req->data.d0.data);
      if (rv != 1) {
        rep.hdr.ret_type = SBRT_NONE;
        rep.hdr.status = (rv == 0) ? SBS_ACK : SBS_NOACK;
        rsize = sizeof(subbusd_rep_hdr_t);
        return iwrite((const char *)&rep, rsize);
      }
#endif
      /* else fall through */
    case SBC_WRITEACK:
      snprintf( sreq, SB_SERUSB_MAX_REQUEST, "W%04X:%04X\n",
        req->data.d0.address, req->data.d0.data );
      break;
    case SBC_SETCMDENBL:
      snprintf(sreq, SB_SERUSB_MAX_REQUEST, "C%c\n",
        req->data.d1.data ? '1' : '0');
      break;
    case SBC_SETCMDSTRB:
      snprintf(sreq, SB_SERUSB_MAX_REQUEST, "S%c\n",
        req->data.d1.data ? '1' : '0');
      break;
    case SBC_SETFAIL:
      snprintf(sreq, SB_SERUSB_MAX_REQUEST, "F%04X\n",
        req->data.d1.data);
      break;
    case SBC_READSW:
      strcpy( sreq, "D\n" ); break;
    case SBC_READFAIL:
      strcpy( sreq, "f\n" ); break;
    case SBC_GETCAPS:
      strcpy( sreq, "V\n" ); break;
    case SBC_TICK:
      strcpy( sreq, "T\n" ); break;
      return false;
    case SBC_DISARM:
      strcpy( sreq, "A\n" ); break;
    case SBC_INTATT:
#ifdef SUBBUS_INTERRUPTS
      rv = int_attach(rcvid, req, sreq);
      if (rv != EOK) {
        status_return(-rv);
        return false; // i.e. don't enqueue
      }
      break;
#else
      return status_return(SBS_NOT_IMPLEMENTED);
#endif
    case SBC_INTDET:
#ifdef SUBBUS_INTERRUPTS
      rv = int_detach(rcvid, req, sreq);
      if (rv != EOK) {
        return status_return(-rv);
      }
      break;
#else
      return status_return(SBS_NOT_IMPLEMENTED);
#endif
    case SBC_QUIT:
      return status_return(SBS_OK);
    default:
      msg(4, "Undefined command in incoming_sbreq!" );
  }
  flavor->enqueue_request(SBDR_TYPE_CLIENT, this, sreq, &rep, 0);
}

void subbusd_serusb_client::request_complete(uint16_t n_bytes) {
  if (n_bytes) {
    iwrite((const char *)&rep, n_bytes);
  } else {
    iwritten(0); // to clear request_pending, nc and set read flag
  }
}

serusb_if::serusb_if(const char *port)
      : DAS_IO::Serial("serusb", SB_SERUSB_MAX_RESPONSE, port,
            O_RDWR | O_NONBLOCK),
        type(0),
        // clt(0),
        // n_reads(0),
        // request(0),
        request_pending(false),
        request_processing(false)
      {}

void serusb_if::enqueue_request(uint16_t type, subbusd_serusb_client *clt,
      const char *request, subbusd_rep_t *repp, uint16_t n_reads) {
  nl_assert(type == SBDR_TYPE_INTERNAL || (clt != 0 && repp != 0));
  reqs.push_back(serusb_request(type, clt, request, repp, n_reads));
  process_requests();
}

/** protocol_input() reviews the response in
   the buffer to determine if it is a suitable
   response to the current request. If so, it
   is returned to the requester.
   process_response() is not responsible for
   advancing to the next request, but it is
   responsible for dequeuing the current
   request if it has been completed.

   Formerly (in arp-das):
   [The string in resp is guaranteed to have had
   a newline at the end, which was replaced with
   a NUL, so we are guaranteed to have a NUL-
   terminated string.]
 */
bool serusb_if::protocol_input() {
  while (nc) {
    for (int lcp = 0; lcp < nc; ++lcp) {
      if (buf[lcp] == '\n') {
        process_response();
        break;
      }
    }
  }
}

bool serusb_if::protocol_timeout() {
  TO.Clear();
  if (request_pending) {
    nl_assert(!reqs.empty());
    serusb_request cur_req = reqs.front();
    msg( 1, "%sUSB request '%c' timed out",
      (cur_req.type == SBDR_TYPE_INTERNAL) ? "Internal " : "",
      cur_req.request[0] );
    dequeue_request(-ETIMEDOUT, 0, 0, 0, "");
  }
}

bool serusb_if::advance_if_char(unsigned char c) {
  if (cp < nc && buf[cp] == c) {
    ++cp;
    return true;
  }
  return false;
}

/**
 Parses the input string for a hexadecimal integer.
 @return true on success.
 */
bool serusb_if::read_hex(uint16_t &arg) {
  return (cp < nc && isxdigit(buf[cp]) && !not_hex(arg));
}

/** process_response() reviews the response in
   the buffer to determine if it is a suitable
   response to the current request. If so, it
   is returned to the requester.
   process_response() is not responsible for
   advancing to the next request, but it is
   responsible for dequeuing the current
   request if it has been completed.

  process_response() is responsible for consume()ing
  the characters it processes. It would not be unreasonable
  to swallow any trailing characters, as they will be
  otherwise reported as unexpected input.
  
  We are guaranteed a newline by protocol_input(), but
  it is not replaced with a NUL as in arp-das.
  
  Except for interrupts, any input is unexpected unless
  request_pending is true.

   Formerly (in arp-das):
   [The string in resp is guaranteed to have had
   a newline at the end, which was replaced with
   a NUL, so we are guaranteed to have a NUL-
   terminated string.]
 */
void serusb_if::process_response() {
  serusb_request cur_req;
  char cur_req_code = '\0';
  int status = RESP_OK;
  uint16_t arg0, arg1;
  int16_t sbs_ok_status = SBS_OK;
  int n_args = 0;
  cp = 0;
  nl_assert(cp < nc);
  char resp_code = buf[cp++];
  nl_assert((request_pending && !reqs.empty()) ||
            (reqs.empty() && !request_pending));
  if (request_pending && !reqs.empty()) {
    cur_req = reqs.front();
    cur_req_code = cur_req.request[0];
  }
  // char resp_code = *s++;
  char exp_req = '\0';
  int exp_args = 0;
  if ( resp_code == 'M' || resp_code == 'm' )  {
    if (cur_req_code == 'M' ) {
      // We have to push the parsing into dequeue_request() because we need
      // direct access to the reply structure.
      dequeue_request(SBS_OK, 4, 0, 0, (const char *)buf);
      consume(nc);
      return;
    } else {
      status = RESP_UNEXP;
    }
  } else {
    if ( resp_code != '\0' ) {
      // We can process args in the general case
      if (read_hex(arg0)) {
        ++n_args;
        if (advance_if_char(':')) {
          if (not_hex(arg1)) {
            status = RESP_INV;
          } else {
            ++n_args;
            if (advance_if_char(':')) {
              ++n_args;
            } else { // 2 args without a 3rd is an error
              status = RESP_INV;
            }
          }
        } else if (!advance_if_char('\n')) {
          status = RESP_INV;
        }
      } else if (!advance_if_char('\n')) {
        status = RESP_INV;
      }
    }
    // Check response for self-consistency
    // Check that response is appropriate for request
    switch (resp_code) {
      case 'R':
        exp_req = 'R';
        exp_args = 1;
        sbs_ok_status = SBS_ACK;
        break;
      case 'r':
        exp_req = 'R';
        exp_args = 1;
        sbs_ok_status = SBS_NOACK;
        break;
      case 'W':
        exp_req = 'W';
        exp_args = 0;
        sbs_ok_status = SBS_ACK;
        break;
      case 'w':
        exp_req = 'W';
        exp_args = 0;
        sbs_ok_status = SBS_NOACK;
        break;
      case 'V':
        exp_req = 'V';
        exp_args = 3;
        break;
      case 'I':
        status = RESP_INTR;
        exp_req = '\0';
        exp_args = 1;
        break;
      case 'A':
      case 'B':
      case 'S':
      case 'C':
      case 'F':
        exp_req = resp_code;
        exp_args = 0;
        break;
      case '0':
        exp_req = '\n';
        exp_args = 0;
        break;
      case 'D':
      case 'f':
      case 'i':
      case 'u':
        exp_req = resp_code;
        exp_args = 1;
        break;
      case 'E': // The old code used on the DACS
      case 'U': // New code, because E is ambiguous in multi-read
        status = RESP_ERR;
        exp_req = '\0';
        exp_args = 1;
        break;
      default:
        status = RESP_UNREC;
        break;
    }
    switch (status) {
      case RESP_OK:
        if (cur_req_code != exp_req) {
          status = RESP_UNEXP;
          break;
        } // fall through
      case RESP_INTR:
      case RESP_ERR:
        if (n_args != exp_args)
          status = RESP_INV;
        break;
    }
  }
  switch (status) {
    case RESP_OK:
      dequeue_request(sbs_ok_status, n_args, arg0, arg1, (const char *)&buf[cp]);
      break;
    case RESP_INTR:
      #ifdef SUBBUS_INTERRUPTS
        process_interrupt(arg0);
        break;
      #endif // with fall through
    case RESP_UNEXP:
      report_err("%s: Unexpected response: '%s'", iname, ascii_escape());
      break;
    case RESP_UNREC:
      report_err("%s: Unrecognized response: '%s'", iname, ascii_escape());
      break;
    case RESP_INV:
      report_err("%s: Invalid response: '%s'", iname, ascii_escape());
      break;
    case RESP_ERR:
      report_err("%s: Error code %s from serusb", iname, ascii_escape() );
      break;
    default:
      msg( 4, "Invalid status: %d", status );
  }
  switch (status) {
    case RESP_OK:
    case RESP_INTR: break;
    default:
      if (request_pending)
        report_err("%s: Current request was: '%s'", iname,
            ::ascii_escape(cur_req.request) );
      else
        report_err("%s: No request was pending", iname);
      break;
  }
  consume(nc);
  // we won't dequeue on error: wait for timeout to handle that
  // that's because we don't know the invalid response was
  // to the current request. It could be noise, or an invalid
  // interrupt response for something.
}

#ifdef SUBBUS_INTERRUPTS
void serusb_if::process_interrupt(unsigned int nb) {
  card_def *cd;
  uint16_t addr;
  unsigned int bn;
  char sreq[8];
  
  for ( cd = carddefs; cd != NULL && cd->bitno != nb; cd = cd->next ) {}
  if ( cd != NULL ) {
    int rv = MsgDeliverEvent( cd->owner, &cd->event );
    if ( rv == -1 ) {
      switch (errno) {
        case EBADF:
        case ESRCH:
          msg( 1,
            "Process attached to '%s' interrupt not found",
            cd->cardID );
          rv = expint_detach( cd->owner, cd->cardID, &addr, &bn );
          nl_assert( rv == EOK );
          nl_assert( nb == bn );
          snprintf( sreq, 8, "u%X\n", addr );
          enqueue_sbreq( SBDR_TYPE_INTERNAL, 0, sreq, 0 );
          break;
        default:
          msg( 4, "Unexpected error %d from MsgDeliverEvent: %s",
              errno, strerror(errno));
      }
    }
  } else {
    msg( 1, "Unexpected interrupt #%d", nb );
    // We don't know the address, so can't disable it.
    // Probably a late hit.
  }
}
#endif

void serusb_if::process_requests() {
  if (request_pending || request_processing || reqs.empty()) {
    msg(MSG_DBG(0), "process_requests() no action: %s",
      request_pending ? "pending" : request_processing ? "processing"
      : "reqs.empty()");
    return;
  }
  request_processing = true;
  while (!request_pending && !reqs.empty()) {
    int cmdlen, nc;
    int no_response = 0;
    serusb_request req = reqs.front();
    
    switch (req.type) {
      case SBDR_TYPE_INTERNAL:
        switch (req.request[0]) {
          case '\n': // NOP
          case 'T':
          case 'V':  // Board Revision
            break;
          default:
            msg( 4, "Invalid internal request" );
        }
        break;
      case SBDR_TYPE_CLIENT:
        switch (req.request[0]) {
          case 'T':
            no_response = 1; break;
          case 'A':
          case 'R':
          case 'M':
          case 'W':
          case 'V':
          case 'S':
          case 'C':
          case 'B':
          case 'i':
          case 'u':
          case 'D':
          case 'F':
          case 'f':
            break;
          default:
            msg( 4, "Invalid client request: '%c'", req.request[0] );
        }
        break;
      default:
        msg(4, "Invalid request type" );
    }
    cmdlen = strlen( req.request );
    msg(-2, "Request: '%*.*s'", cmdlen-1, cmdlen-1, req.request );
    iwrite((const char *)req.request, cmdlen);
    if (no_response) {
      subbusd_serusb_client *clt = req.clt;
      reqs.pop_front(); // dequeue_request( SBS_OK, 0, 0, 0, "" );
      clt->request_complete(0);
    } else {
      request_pending = true;
      TO.Set(1,0); // set_timeout(1);
    }
  }
  return;
}

/**
 * Sends the response to the client (if any) and
 * removes it from the queue. Initiates
 * processing of the next command if one is waiting.
 * Current assumption:
 *    n_args maps 1:1 onto SBRT_ codes
 *    n_args == 3 is only for 'V' request/response
 *    n_args == 4 is only for 'M' request/response
 * We need to parse the 'M' response here rather than in process_response()
 * because we need direct access to the reply structure.
 */
void serusb_if::dequeue_request(int16_t status, int n_args,
    uint16_t arg0, uint16_t arg1, const char *s ) {
  int rv, rsize = 0;
  subbusd_rep_t *repp;
  serusb_request cur_req;

  nl_assert(request_pending && !reqs.empty());
  cur_req = reqs.front();
  TO.Clear();
  if (cur_req.request[0] != 'T') {
    repp = cur_req.repp;
    repp->hdr.status = status;
    switch (n_args) {
      case 0:
        repp->hdr.ret_type = SBRT_NONE;
        rsize = sizeof(subbusd_rep_hdr_t);
        break;
      case 1:
        repp->hdr.ret_type = SBRT_US;
        repp->data.value = arg0;
        rsize = sizeof(subbusd_rep_hdr_t)+sizeof(uint16_t);
        break;
      case 3:
        nl_assert(cur_req.request[0] == 'V');
        switch ( cur_req.type ) {
          case SBDR_TYPE_INTERNAL:
            msg(0, "Features: %d:%03X Version: %s",
              arg0, arg1, s);
            break;
          case SBDR_TYPE_CLIENT:
            repp->hdr.ret_type = SBRT_CAP;
            repp->data.capabilities.subfunc = arg0;
            repp->data.capabilities.features = arg1;
            strncpy(repp->data.capabilities.name, s, SUBBUS_NAME_MAX );
            rsize = sizeof(subbusd_rep_hdr_t) + sizeof(subbusd_cap_t);
            break;
          default: 
            break; // picked up and reported below
        }
        break;
      case 4:
        // 'M' response and request (tested before calling)
        repp->hdr.ret_type = SBRT_MREAD;
        nl_assert(cur_req.request[0] == 'M' && cur_req.n_reads != 0);
        // Look at req n_reads, then parse responses. Don't parse more
        // than n_reads values. If we encounter 'm', switch status to
        // SBS_NOACK. If we encounter 'U', switch status to
        // SBS_RESP_ERROR, report the error code, and return with no
        // data. If we get the wrong number of responses, report
        // SBS_RESP_SYNTAX, complain and return with no data
        { int n_reads = cur_req.n_reads;
          int n_parsed = 0;
          const char *p = s;
          uint16_t errval;

          nl_assert(n_reads > 0 && n_reads <= 500);
          while (n_parsed  < n_reads && rsize == 0) {
            switch ( *p ) {
              case 'm':
                repp->hdr.status = SBS_NOACK; // No acknowledge on at least one read
                // fall through
              case 'M':
                ++p;
                if (!read_hex(repp->data.mread.rvals[n_parsed++])) {
                  report_err("%s: DACS response syntax error", iname);
                  repp->hdr.status = SBS_RESP_SYNTAX; // DACS reply syntax error
                  rsize = sizeof(subbusd_rep_hdr_t);
                  repp->hdr.ret_type = SBRT_NONE;
                  break;
                }
                continue;
              case 'U':
                ++p;
                if (!read_hex(errval)) {
                  report_err("%s: Invalid error in mread response", iname);
                  repp->hdr.status = SBS_RESP_SYNTAX;
                } else {
                  msg(2, "DACS reported error %d on mread", errval );
                  repp->hdr.status = SBS_RESP_ERROR;
                }
                rsize = sizeof(subbusd_rep_hdr_t);
                repp->hdr.ret_type = SBRT_NONE;
                break;
              default:
                break;
            }
            break;
          }
          if (rsize == 0) {
            if (n_parsed > n_reads || *p != '\0' ) {
              // Wrong number of read values returned
              report_err("Expected %d, read %d:", n_reads, n_parsed);
              repp->hdr.status = SBS_RESP_SYNTAX;
              rsize = sizeof(subbusd_rep_hdr_t);
              repp->hdr.ret_type = SBRT_NONE;
            } else {
              repp->data.mread.n_reads = n_parsed;
              rsize = sizeof(subbusd_rep_hdr_t) +
                      (n_parsed+1) * sizeof(uint16_t);
            }
          }
        }
        break;
      case 2:
        msg( 4, "Invalid n_args in dequeue_request" );
    }
  }
  switch( cur_req.type ) {
    case SBDR_TYPE_INTERNAL:
      // rv = 0;
      break;
    case SBDR_TYPE_CLIENT:
      cur_req.clt->request_complete(rsize);
      // rv = MsgReply( cur_req.rcvid, rsize, &rep, rsize );
      break;
    default:
      msg( 4, "Invalid command type in dequeue_request" );
  }
  { int n = strlen(cur_req.request) - 1;
    msg( -2, "Dequeued: '%*.*s'", n, n, cur_req.request ); 
  }
  reqs.pop_front();
  request_pending = false;
  process_requests(); // if one is pending...
}

subbusd_serusb::subbusd_serusb(const char *port, int baud_rate)
    : subbusd_flavor("serusb", new_subbusd_serusb_client) {
  serusb = new serusb_if(port);
  serusb->setup(baud_rate, 8, 'n', 1, 1, 0);
  serusb->flush_input();
}

subbusd_serusb::~subbusd_serusb() {
  if (serusb) {
    delete(serusb);
    serusb = 0;
  }
}

void subbusd_serusb::init_subbus() {
  /* Enqueue initialization requests */
  enqueue_request( SBDR_TYPE_INTERNAL, 0, "\n", 0, 0 );
  enqueue_request( SBDR_TYPE_INTERNAL, 0, "V\n", 0, 0 );
}

void subbusd_serusb::shutdown_subbus(void) {}
