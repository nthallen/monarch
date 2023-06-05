#include <math.h>
#include "dasio/host_session.h"
#include "sspint.h"
#include "nl.h"
#include "mlf.h"

SSP_UDP::SSP_UDP(mlf_def_t *mlf, TM_data_sndr *tm_amp_data)
    : Interface("UDP", SSP_CLIENT_BUF_LENGTH*sizeof(uint32_t)),
      state(FD_IDLE),
      mlf(mlf),
      tm_amp_data(tm_amp_data),
      do_amp(false) {
  scan_buf = (uint32_t*)buf;
}

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

  flags = Fl_Read;
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
  msg(MSG_DBG(1), "%s: p_i() in  nc=%-5u cur_word=%d\n", iname, nc, cur_word);
  if (nc >= cur_word*4+4 && scan_buf[cur_word] & SSP_FRAG_FLAG) {
    uint32_t fraghdr = scan_buf[cur_word];
    msg(MSG_DBG(1), "%s: Frag Last:%s SN:%-5u Off:%u", iname,
      (fraghdr & SSP_LAST_FRAG_FLAG) ? "yes" : "no ",
      (fraghdr >> 16) & 0x3FFF,
      fraghdr & 0xFFFF);
  }
  if ( cur_word == 0 && !(*scan_buf & SSP_FRAG_FLAG) ) {
    if ( nc == scan_size ) {
      output_scan(scan_buf);
      report_ok(nc);
    } else {
      report_err("%s: Expected %d bytes, received %d", iname, scan_size, nc );
      consume(nc);
    }
    cur_word = 0;
    scan_OK = 1;
  } else if ( !( scan_buf[cur_word] & SSP_FRAG_FLAG ) ) {
    report_err("%s: Expected scan fragment", iname);
    cur_word = 0;
    scan_OK = 1;
    consume(nc);
  } else {
    int frag_hdr = scan_buf[cur_word];
    int frag_offset = frag_hdr & 0xFFFFL;
    int frag_sn;
    int cur_frag_bytes = nc - (cur_word * sizeof(uint32_t));
    if ( frag_offset != cur_word ) {
      if ( frag_offset == 0 ) {
        consume(cur_word*sizeof(uint32_t));
        if ( scan_OK ) report_err("%s: Lost end of scan.", iname);
        cur_word = 0;
        scan_OK = 1;
      } else if ( scan_OK ) {
        report_err("%s: Lost fragment", iname);
        scan_OK = 0;
      }
    }
    frag_sn = frag_hdr & 0x3FFF0000L;
    if ( cur_word == 0 ) scan_serial_number = frag_sn;
    else {
      scan_buf[cur_word] = frag_hold;
      if ( scan_OK && scan_serial_number != frag_sn ) {
        scan_OK = 0;
        report_err("%s: Lost data: SN skip", iname);
      }
    }
    cur_word = frag_offset + (cur_frag_bytes/sizeof(uint32_t)) - 1;
    if ( frag_hdr & SSP_LAST_FRAG_FLAG ) {
      if ( scan_OK ) {
        if ( cur_word == raw_length ) {
          output_scan(scan_buf+1);
          report_ok(nc);
        } else {
          report_err("%s: Scan length error: expected %d words, received %d",
            iname, raw_length, cur_word );
          consume(nc);
        }
      } else {
        report_err("%s: Unexpected SSP_LAST_FRAG_FLAG", iname);
        consume(nc);
      }
      cur_word = 0;
      scan_OK = 1;
    } else {
      frag_hold = scan_buf[cur_word];
    }
    if ( cur_word + SSP_MAX_FRAG_LENGTH > SSP_CLIENT_BUF_LENGTH ) {
      report_err("%s: Bad fragment offset: %d(%d)", iname, frag_offset, nc );
      consume(nc);
      cur_word = 0;
      scan_OK = 1;
    }
  }
  msg(MSG_DBG(1), "%s: p_i() out nc=%u\n", iname, nc);
  return false;
}

/**
 * Noise calculation:
 *   May 2, 2022 (DCOTSS Integration Year 2)
 *   The existing calculation assumed it was possible to find a level scan region,
 *   which was true on the relevant system at the time. Now we clearly need to
 *   detrend the signal before calculating the noise.
 *
 *   Basic problem: {Xi,Yi}. To detrend, we want m, b such that  Y = mX + b
 *   minimizes the sum of the  squares  of  the residuals. Practically, this
 *   calculation can be more accurately performed when mean(X) and mean(Y) are
 *   zero, and for  our purposes, there is no problem with subtracting this mean.
 *
 *   i ranges from NN to MM, so there  are N = MM-NN+1 samples. With no loss of
 *   generality, we will assume i ranges  from 1 to  N, and Xi = i.
 *   Then mean(Xi) = (N+1)/2.
 *   Define X'i = Xi - mean(Xi) = i-(N+1)/2. mean(X'i) = 0, and
 *   sum(X'i^2) = (N^3)/12 - N/12
 *
 *   Define Y'i = Yi - mean(Yi). Then m = sum(X'i * Y'i)/sum(X'i^2) and b = 0.
 *   Note that sum(X'i^2) is a constant, so the only thing we need to calculate
 *   is  sum(X'i* Y'i).
 *
 *   The detreneded residual values are Y'i - m X'i, and the mean of the residual
 *   is zero. (TBD: prove that last assertion, and it is not exactly
 *   true in MATLAB simulation due to roundoff) So all we need to do is calculate
 *   noise = sqrt(sum((Y'i-mX'i)^2))/N and presumably  noise_percent = noise/mean(Yi)
 */
void SSP_UDP::output_scan(uint32_t *scan) {
  FILE *ofp;
  ssp_scan_header_t *hdr = (ssp_scan_header_t *)scan;
  uint32_t *idata = (uint32_t*)(scan+hdr->NWordsHdr);
  float fdata[SSP_MAX_CHANNELS][SSP_MAX_SAMPLES];
  // time_t now;
  // static time_t last_rpt = 0;
  float divisor = 1/(hdr->NCoadd * (float)(hdr->NAvg+1));
  int my_scan_length = hdr->NSamples * hdr->NChannels;

  // scan is guaranteed to be raw_length words long. Want to
  // verify that NSamples*NChannels + NWordsHdr + 1 == raw_length
  if ( hdr->NWordsHdr != scan0 ) {
    msg( 2, "NWordsHdr(%u) != %u", hdr->NWordsHdr, scan0 );
    return;
  }
  if ( hdr->FormatVersion > 1 ) {
    msg( 2, "Unsupported FormatVersion: %u", hdr->FormatVersion );
    return;
  }
  if ( my_scan_length + 7 != raw_length ) {
    msg( 2, "Header reports NS:%u NC:%u -- raw_length is %d",
      hdr->NSamples, hdr->NChannels, raw_length );
    return;
  }
  if (ssp_config.LE || do_amp) {
    int i, j, nchans = hdr->NChannels;
    for ( j = 0; j < hdr->NChannels; ++j ) {
      uint32_t *id = &idata[j];
      float minv = 0, maxv = 0;
      for ( i = 0; i < hdr->NSamples; ++i ) {
        float sampleval = (*id) * divisor;
        fdata[j][i] = sampleval;
        id += nchans;
        if (do_amp) {
          if (i == 0) {
            minv = maxv = sampleval;
          } else if (sampleval < minv) {
            minv = sampleval;
          } else if (sampleval > maxv) {
            maxv = sampleval;
          }
        }
      }
      ssp_amp_data.amplitude[j] = maxv - minv;
    }
    for (j = hdr->NChannels; j < SSP_MAX_CHANNELS; ++j) {
      ssp_amp_data.amplitude[j] = 0;
      ssp_amp_data.noise[j] = 0;
      ssp_amp_data.noise_percent[j] = 0;
    }
  }
  if (noise_config.NZ) {
    int i, j;
    for (j = 0; j < hdr->NChannels; ++j) {
      float zero, amplitude, noise, meanY, sumXY, m;
      
      // Determine zero
      zero = 0;
      for (i = 0; i < noise_config.NZ; ++i) {
        zero += fdata[j][i];
      }
      zero /= noise_config.NZ;
      
      // Determine amplitude, meanY
      amplitude = 0;
      for (i = noise_config.NN; i <= noise_config.NM; ++i) {
        amplitude += fdata[j][i];
      }
      meanY = amplitude/noise_config.NSamp;
      amplitude = meanY - zero;

      // Calculate slope m
      sumXY = 0;
      for (i = 1; i <= noise_config.NSamp; ++i) {
        int ii = i+noise_config.NN-1;
        float Xi = i - noise_config.meanX;
        float Yi = fdata[j][ii] - meanY;
        sumXY += Xi*Yi;
      }
      m = sumXY / noise_config.sumX2;

      // Calculate std of residual
      noise = 0;
      for (i = 1; i < noise_config.NSamp; ++i) {
        int ii = i+noise_config.NN-1;
        float Xi = i - noise_config.meanX;
        float dev = fdata[j][ii] - meanY - m*Xi;
        noise += dev*dev;
      }
      noise = sqrtf(noise/noise_config.NSamp);
      
      ssp_amp_data.amplitude[j] = amplitude;
      ssp_amp_data.noise[j] = noise;
      ssp_amp_data.noise_percent[j] = 100 * noise / amplitude;
    }
  }
  if (ssp_config.LE) {
    ofp = mlf_next_file(mlf);
    fwrite(hdr, sizeof(ssp_scan_header_t), 1, ofp);
    fwrite(&scan[raw_length-1], sizeof(uint32_t), 1, ofp);
    { int NCh = hdr->NChannels, j;
      for ( j = 0; j < NCh; j++ ) {
        fwrite( fdata[j], sizeof(float), hdr->NSamples, ofp);
      }
    }
    fclose(ofp);
  }

  ssp_data.index = ssp_amp_data.index = mlf->index;
  ssp_data.Flags |= (unsigned short)(scan[raw_length-1]);
  ssp_data.Total_Skip += hdr->NSkL + hdr->NSkP;
  ssp_data.ScanNum = hdr->ScanNum;
  if ( hdr->FormatVersion > 0 ) {
    ssp_data.T_FPGA = hdr->T_FPGA;
    ssp_data.T_HtSink = hdr->T_HtSink;
  }
  
  // Perform some sanity checks on the inbound scan
  if ( (scan[1] & 0xFFFF00FF) != scan1 )
    msg( 1, "%lu: scan[1] = %08lX (not %08lX)\n", mlf->index, scan[1], scan1 );
  if ( hdr->FormatVersion == 0 && scan[5] != scan5 )
    msg( 1, "%lu: scan[5] = %08lX (not %08lX)\n", mlf->index, scan[5], scan5 );
}


