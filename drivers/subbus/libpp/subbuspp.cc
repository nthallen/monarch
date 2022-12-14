/** @file drivers/subbus/libpp/subbuspp.cc
 */
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include "subbuspp.h"
#include "nl.h"
#include "nl_assert.h"
// #include "tm.h"

subbuspp::subbuspp(const char *service, const char *sub_service)
    : Client(service, sizeof(subbusd_rep_t)+1, 0, service, sub_service) {
  conn_fail_reported = true;
}

subbuspp::~subbuspp() {}

bool subbuspp::app_connected() {
  return true;
}

bool subbuspp::app_input() {
  // have we satisfied the request?
  if ( nc < sizeof(subbusd_rep_hdr_t) )
    return false;
  if ( sb_reply->hdr.status < 0 ) 
    expected_type = SBRT_NONE;
  if ( sb_reply->hdr.ret_type != expected_type ) {
    return true;
  }
  switch ( sb_reply->hdr.ret_type ) {
    case SBRT_NONE:
      return ( nc >= sizeof(subbusd_rep_hdr_t));
    case SBRT_US:
      return ( nc >= sizeof(subbusd_rep_hdr_t) + sizeof(uint16_t));
    case SBRT_CAP:
      return ( nc >= sizeof(subbusd_rep_hdr_t) + sizeof(subbusd_cap_t));
    case SBRT_MREAD:
      return true;
    default:
      msg( 4, "Unknown return type: %d", sb_reply->hdr.ret_type );
  }
  return true;
}

int subbuspp::send_to_subbusd( uint16_t command, void *data,
                int data_size, uint16_t exp_type ) {
  if (fd < 0) {
    msg( MSG_DBG(0), "Attempt to access subbusd before initialization" );
    return SBS_NOT_CONNECTED;
  }
  nl_assert(obuf_empty());
  expected_type = exp_type;
  int n_iov = 1;
  sb_req_hdr.sb_kw = SB_KW;
  sb_req_hdr.command = command;
  sb_iov[0].iov_base = &sb_req_hdr;
  sb_iov[0].iov_len = sizeof(sb_req_hdr);
  if ( data_size > 0 ) {
    sb_iov[1].iov_base = data;
    sb_iov[1].iov_len = data_size;
    ++n_iov;
  }
  // Clear the input buffer here, since we're using it to return
  // data directly to the client.
  if (nc) report_ok(nc);
  if (!iwritev(sb_iov, n_iov)) {
    ELoop->event_loop();
  }
  if (fd < 0) return SBS_NOT_CONNECTED;
  nl_assert( nc >= sizeof(subbusd_rep_hdr_t) );
  if ( sb_reply->hdr.status < 0 ) 
    exp_type = SBRT_NONE;
  if ( sb_reply->hdr.ret_type != exp_type ) {
    msg( 4, "Return type for command %u should be %d, is %d",
      command, exp_type, sb_reply->hdr.ret_type );
  }
  switch ( sb_reply->hdr.ret_type ) {
    case SBRT_NONE:
      nl_assert( nc == sizeof(subbusd_rep_hdr_t));
      break;
    case SBRT_US:
      nl_assert( nc == sizeof(subbusd_rep_hdr_t) + sizeof(uint16_t));
      break;
    case SBRT_CAP:
      nl_assert( nc >= sizeof(subbusd_rep_hdr_t) + sizeof(subbusd_cap_t));
      break;
    case SBRT_MREAD:
      break;
    default:
      msg( 4, "Unknown return type: %d", sb_reply->hdr.ret_type );
  }
  return sb_reply->hdr.status;
}

/** Initializes communications with subbusd driver.
    Returns library subfunction on success,
    zero on failure.
 */
int subbuspp::load() {
  int rv;
  if (fd > 0 || ELoop != 0) {
    msg( -2, "Attempt to reload subbus" );
    return subbus_subfunction;
  }
  if (connect()) {
    return 0;
  }
  PELoop.add_child(this);
  ELoop->event_loop(); // should run until connected
  if (fd < 0) {
    msg( -2, "Error opening subbusd: %s", strerror(errno));
    return 0;
  }
  sb_reply = (subbusd_rep_t *)buf;
  rv = send_to_subbusd( SBC_GETCAPS, NULL, 0, SBRT_CAP );
  if ( rv != SBS_OK )
    msg( 4, "Expected SBS_OK while getting capabilities" );
  subbus_subfunction = sb_reply->data.capabilities.subfunc;
  subbus_features = sb_reply->data.capabilities.features;
  strncpy(local_subbus_name, sb_reply->data.capabilities.name, SUBBUS_NAME_MAX);
  local_subbus_name[SUBBUS_NAME_MAX-1] = '\0'; // guarantee nul-term.
  return subbus_subfunction;
}

/**
 * Returns the hardware name string as originally retrieved from
 * subbusd during load_subbus().
 */
const char *subbuspp::get_subbus_name() {
  if ( fd < 0 )
    msg( 4, "Attempt to read subbus_name before initialization" );
  return( local_subbus_name );
}

/**
 @return non-zero if hardware read acknowledge was observed.
 */
int subbuspp::read_ack( uint16_t addr, uint16_t *data ) {
  int rv, rc;
  subbusd_req_data1 rdata;

  rdata.data = addr;
  rv = send_to_subbusd( SBC_READACK, &rdata, sizeof(rdata), SBRT_US );
  *data = sb_reply->data.value;
  switch ( rv ) {
    case SBS_ACK: rc = 1; break;
    case -ETIMEDOUT:
    case SBS_NOT_CONNECTED:
    case SBS_NOACK: rc = 0; break;
    default:
      msg( 4, "Invalid status response to read_ack(): %d", rv );
  }
  return rc;
}

uint16_t subbuspp::read_subbus(uint16_t addr) {
  uint16_t data;
  if (!read_ack(addr, &data)) {
    data = 0;
  }
  return data;
}

int subbuspp::write_ack(uint16_t addr, uint16_t data) {
  int rv, rc;
  subbusd_req_data0 wdata;

  wdata.address = addr;
  wdata.data = data;
  rv = send_to_subbusd( SBC_WRITEACK, &wdata, sizeof(wdata), SBRT_NONE );
  switch (rv ) {
    case SBS_ACK: rc = 1; break;
    case -ETIMEDOUT:
    case SBS_NOT_CONNECTED:
    case SBS_NOACK: rc = 0; break;
    default:
      msg( 4, "Invalid status response to write_ack(): %d",
          rv );
  }
  return rc;
}

int subbuspp::send_CSF( uint16_t command, uint16_t val ) {
  int rv;
  subbusd_req_data1 csf_data;

  switch ( command ) {
    case SBC_SETCMDENBL:
    case SBC_SETCMDSTRB:
    case SBC_SETFAIL:
      break;
    default:
      msg( 4, "Invalid command in set_CSF: %d", command );
  }
  csf_data.data = val;
  rv = send_to_subbusd( command, &csf_data, sizeof(csf_data), SBRT_NONE );
  return( (rv == SBS_OK) ? 1 : 0 );
}

#ifdef SUBBUS_INTERRUPTS
  int subbuspp::subbus_int_attach( char *cardID, uint16_t address,
        uint16_t region, struct sigevent *event ) {
    subbusd_req_data2 idata;
    nl_assert(cardID != NULL);
    strncpy( idata.cardID, cardID, 8);//possibly not nul-terminated
    idata.address = address;
    idata.region = region;
    idata.event = *event;
    return send_to_subbusd( SBC_INTATT, &idata, sizeof(idata), SBRT_US );
  }

  int subbuspp::subbus_int_detach( char *cardID ) {
    subbusd_req_data3 idata;
    nl_assert(cardID != NULL);
    strncpy( idata.cardID, cardID, 8);//possibly not non-terminated
    return send_to_subbusd( SBC_INTDET, &idata, sizeof(idata), SBRT_US );
  }
#endif // SUBBUS_INTERRUPTS

int subbuspp::tick_sic() {
  if ( fd < 0 ) return 0;
  return send_to_subbusd( SBC_TICK, NULL, 0, SBRT_NONE );
}
/**
 If system controller is associated with a watchdog timer
 that can reboot the system, this command disables that
 timer.
 */
int subbuspp::disarm_sic() {
  return send_to_subbusd(SBC_DISARM, NULL, 0, SBRT_NONE);
}

/**
 * Requests subbusd to terminate. subbusd will wait until
 * all connections are closed.
 * @return SBS_OK on success.
 */
int subbuspp::subbus_quit() {
  if ( fd < 0 ) return 0;
  return send_to_subbusd( SBC_QUIT, NULL, 0, SBRT_NONE );
}

bool subbuspp::connect_failed() {
  TO.Clear();
  flags &= ~Fl_Timeout;
  return true;
}

int subbuspp::mread_subbus( subbus_mread_req *req, uint16_t *data) {
  // rv should be the number of bytes retuned from subbusd into sb_reply.
  int rv;
  uint16_t nw;
  if ( req == NULL ) return 200;
  rv = mread_subbus_nw(req, data, &nw);
  if (nw < req->n_reads && nl_response > 0)
    msg(MSG_WARN, "mread returned %d/%d words", nw, req->n_reads);
  return rv;
}

int subbuspp::mread_subbus_nw(subbus_mread_req *req, uint16_t *data,
            uint16_t *nwords) {
  int rv;
  int nw = 0;
  if ( req == NULL ) return 200;
  rv = send_to_subbusd( SBC_MREAD, req, req->req_len, SBRT_MREAD );
  if ( rv >= 0 ) {
    int i;
    nw = sb_reply->data.mread.n_reads;
    if (nw > req->n_reads) {
      msg(MSG_ERROR, "mread expected %d words, returned %d",
        req->n_reads, nw);
      nw = req->n_reads;
    }
    for ( i = 0; i < nw; ++i ) {
      data[i] = sb_reply->data.mread.rvals[i];
    }
  }
  if (nwords != 0)
    *nwords = nw;
  return rv;
}

subbus_mread_req *subbuspp::pack_mread( int req_len, int n_reads,
        const char *req_str ) {
  int req_size = 2*sizeof(uint16_t) + req_len + 1;
  subbus_mread_req *req = (subbus_mread_req *)new_memory(req_size);
  req->req_len = req_size;
  req->n_reads = n_reads;
  strcpy( req->multread_cmd, req_str );
  return req;
}

subbus_mread_req *subbuspp::pack_mread_requests( unsigned int addr, ... ) {
  uint16_t addrs[50];
  int n_reads = 0;
  
  { unsigned int val = addr;
    va_list va;
    if ( addr == 0 ) return NULL;
    va_start( va, addr );
    while ( val != 0 && n_reads < 50 ) {
      addrs[n_reads++] = (uint16_t) val;
      val =  va_arg(va, unsigned int);
    }
    va_end(va);
  }
  { char buf[256];
    int nc = 0;
    int space = 256;
    int i = 0;
    int nb;

    nb = snprintf( buf, space, "M%X#", n_reads );
    nl_assert(nb < space);
    nc += nb;
    space -= nb;
    while ( i < n_reads ) {
      nb = 0;
      if (i+2 < n_reads &&
          addrs[i] <= addrs[i+1] &&
          addrs[i+1] <= addrs[i+2] ) {
        unsigned d1 = addrs[i+1]-addrs[i];
        unsigned d2 = addrs[i+2]-addrs[i+1];
        if ( d1 == d2 ) {
          // We'll use either the s:i:e syntax or the n@a syntax.
          int j;
          for ( j = 2; i+j+1 < n_reads; ++j) {
            if ( addrs[i+j] + d1 != addrs[i+j+1] )
              break;
          }
          // Now we'll handle samples from i to i+j
          if ( d1 == 0 ) {
            nb = snprintf( buf+nc, space, "%X@%X,", j-i+1, addrs[i] );
          } else {
            nb = snprintf( buf+nc, space, "%X:%X:%X,",
              addrs[i], d1, addrs[i+j] );
          }
          i += j+1;
        }
      }
      if (nb == 0) {
        // We did not use an optimization, so just output an address
        nb = snprintf( buf+nc, space, "%X,", addrs[i++] );
      }
      if ( nb >= space ) {
        msg( 2, "Buffer overflow in pack_mread_requests()" );
        return NULL;
      }
      nc += nb;
      space -= nb;
    }
    // replace the trailing comma with a newline:
    buf[nc-1] = '\n';
    return pack_mread( nc, n_reads, buf );
  }
}

subbus_mread_req *subbuspp::pack_mread_request( int n_reads, const char *req ) {
  char buf[256];
  int space = 256;
  int nb;

  nb = snprintf( buf, space, "M%X#%s\n", n_reads, req );
  if ( nb >= space ) {
    msg( 2, "Buffer overflow in pack_mread_request()" );
    return NULL;
  }
  return pack_mread( nb, n_reads, buf );
}
