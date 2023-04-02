#include <dasio/host_session.h>
#include "sspint.h"
#include "nl.h"
#include "mlf.h"

SSP_UDP::SSP_UDP(mlf_def_t *mlf, TM_data_sndr *tm_amp_data)
    : Interface("UDP", SSP_CLIENT_BUF_LENGTH),
      state(FD_IDLE),
      mlf(mlf),
      tm_amp_data(tm_amp_data),
      do_amp(false) {}

int SSP_UDP::connect() {
  this->do_amp =
    tm_amp_data->get_socket_state() ==
      Socket::socket_state_t::Socket_connected;
  /* First check to make sure the configuration is valid */
  if ( ssp_config.NS == 0 || ssp_config.NE == 0 ) {
    return 0;
  }
  switch ( ssp_config.NE ) {
    case 1: case 2: case 4: n_channels = 1; break;
    case 3: case 5: case 6: n_channels = 2; break;
    case 7: n_channels = 3; break;
    default:
      msg( 2, "Invalid NE configuration: %d", ssp_config.NE );
      return -1;
  }
  raw_length = (7 + ssp_config.NS*n_channels);
  scan_size = raw_length*sizeof(uint32_t);
  scan1 = (ssp_config.NS << 16) + n_channels;

  const char *interface = hs_registry::query_host("UDP");
	const char *service = "0";
	struct addrinfo hints, *results, *p;
  int err;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// don't care IPv4 of v6
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICHOST;

	err = getaddrinfo(interface,
						service,
						&hints,
						&results);
	if (err)
    msg(MSG_FATAL, "SSP_UDP::Bind: getaddrinfo error: %s", gai_strerror(err) );
	for(p=results; p!= NULL; p=p->ai_next) {
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (fd < 0)
      msg(MSG_ERROR, "SSP_UDP::Bind: socket error: %s", strerror(errno) );
		else if ( bind(fd, p->ai_addr, p->ai_addrlen) < 0 )
      msg(MSG_ERROR, "SSP_UDP::Bind: bind error: %s", strerror(errno) );
		else break;
	}
  if (fd < 0)
    msg(MSG_FATAL, "Unable to bind UDP socket");
  freeaddrinfo(results);

  struct sockaddr_in servAddr;
  socklen_t servAddr_len = sizeof(servAddr);
  err = getsockname(fd, (struct sockaddr *)&servAddr,
    &servAddr_len);
  port = ntohs(servAddr.sin_port);
  state = FD_READ;
  cur_word = 0;
  scan_OK = 1;

  int ioflags = fcntl(fd, F_GETFL, 0);
  if (ioflags != -1)
    ioflags = fcntl(fd, F_SETFL, ioflags | O_NONBLOCK);
  if (ioflags == -1)
    msg(MSG_FATAL, "Error setting O_NONBLOCK on UDP socket: %s",
      strerror(errno));

  return port;
}

void SSP_UDP::disconnect() {
  close();
  state = FD_IDLE;
}

/* bool SSP_UDP::fillbuf() {
	struct sockaddr_storage from;
	socklen_t fromlen = sizeof(from);
	int rv = recvfrom(fd, &buf[nc],	bufsize - nc - 1, 0,
						(struct sockaddr*)&from, &fromlen);

	if (rv == -1) {
    if ( errno == EWOULDBLOCK ) {
      ++n_eagain;
    } else if (errno == EINTR) {
      ++n_eintr;
    } else {
      msg(MSG_ERROR, "SSP_UDP::fillbuf: recvfrom error: %s", strerror(errno));
      return true;
    }
    return false;
  }
  nc += rv;
  return false;
}
 */

bool SSP_UDP::protocol_input() {
  if ( cur_word == 0 && !(*scan_buf & SSP_FRAG_FLAG) ) {
    if ( nc == scan_size ) output_scan(scan_buf);
    else msg( 2, "Expected %d bytes, received %d", scan_size, nc );
  } else if ( !( scan_buf[cur_word] & SSP_FRAG_FLAG ) ) {
    msg( -3, "Expected scan fragment" );
  } else {
    int frag_hdr = scan_buf[cur_word];
    int frag_offset = frag_hdr & 0xFFFFL;
    int frag_sn;
    if ( frag_offset != cur_word ) {
      if ( frag_offset == 0 ) {
        memmove( scan_buf, scan_buf+cur_word, nc );
        if ( scan_OK ) msg( -3, "Lost end of scan." );
        cur_word = 0;
        scan_OK = 1;
      } else if ( scan_OK ) {
        msg( -3, "Lost fragment" );
        scan_OK = 0;
      }
    }
    frag_sn = frag_hdr & 0x3FFF0000L;
    if ( cur_word == 0 ) scan_serial_number = frag_sn;
    else {
      scan_buf[cur_word] = frag_hold;
      if ( scan_OK && scan_serial_number != frag_sn ) {
        scan_OK = 0;
        msg( -3, "Lost data: SN skip" );
      }
    }
    cur_word = frag_offset + (nc/sizeof(long)) - 1;
    if ( frag_hdr & SSP_LAST_FRAG_FLAG ) {
      if ( scan_OK ) {
        if ( cur_word == raw_length )
          output_scan(scan_buf+1);
        else msg( 2, "Scan length error: expected %d words, received %d",
          raw_length, cur_word );
      }
      cur_word = 0;
      scan_OK = 1;
    } else {
      frag_hold = scan_buf[cur_word];
    }
    if ( cur_word + SSP_MAX_FRAG_LENGTH > SSP_CLIENT_BUF_LENGTH ) {
      msg( 2, "Bad fragment offset: %d(%d)", frag_offset, nc );
      cur_word = 0;
      scan_OK = 1;
    }
  }
  return false;
}

void SSP_UDP::output_scan(uint32_t *scan) {
}


