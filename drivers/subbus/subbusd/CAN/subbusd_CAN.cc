// #undef HAVE_CAN_H
#ifdef HAVE_CAN_H
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#endif
#include "nl_assert.h"
#include "subbusd_int.h"
#include "subbusd_CAN.h"

using namespace DAS_IO;

subbusd_CAN_client::subbusd_CAN_client(DAS_IO::Authenticator *auth, int bufsize, subbusd_CAN *fl)
    : subbusd_client(auth, bufsize), flavor(fl) {}
subbusd_CAN_client::~subbusd_CAN_client() {}

Serverside_client *new_subbusd_CAN_client(Authenticator *auth, SubService *ss) {
  ss = ss; // not interested
  subbusd_CAN_client *clt =
    new subbusd_CAN_client(auth, subbusd_CAN_client::subbusd_CAN_max_req_size,
          (subbusd_CAN*)ss->svc_data);
  return clt;
}

bool subbusd_CAN_client::incoming_sbreq(subbusd_req_t *req) {
  char sreq[subbusd_CAN_max_req_size];
  subbusd_rep_t rep;
  int rv, rsize;
  uint8_t device_id, addr;
  req_nc = 0;
  
  switch ( req->sbhdr.command ) {
    case SBC_READACK:
      device_id = (req->data.dl.data >> 8) & 0xFF;
      addr = req->data.dl.data & 0xFF;
      enqueue_canreq(device_id, 
      snprintf( sreq, subbusd_CAN_max_req_size, "R%04X\n",
        req->data.d1.data );
      break;
    case SBC_MREAD:
      // Need to decode this and enqueue multiple requests
      // enqueue_sbreq(device_id, req->data.d4.multread_cmd,
      //              req->data.d4.n_reads);
      return;
    case SBC_WRITEACK:
      snprintf( sreq, subbusd_CAN_max_req_size, "W%04X:%04X\n",
        req->data.d0.address, req->data.d0.data );
      break;
    case SBC_GETCAPS:
      strcpy( sreq, "V\n" ); break;
    case SBC_QUIT:
      status_return(SBS_OK);
      return true; // Is this sufficient?
    default:
      return status_return(SBS_NOT_IMPLEMENTED);
  }
  enqueue_sbreq( SBDR_TYPE_CLIENT, sreq, 0 );
  return false;
}

subbusd_CAN::subbusd_CAN() : subbusd_flavor("CAN", new_subbusd_CAN_client) {}
subbusd_CAN::~subbusd_CAN() {}

void subbusd_CAN::init_subbus() {
  // setup socket
}

void subbusd_CAN::shutdown_subbus() {
  // teardown socket
}

// subbusd_CAN *subbusd_CAN::CAN = 0;

void subbusd_CAN_init_options(int argc, char **argv) {
  argc = argc;
  argv = argv;
  subbusd_CAN *CAN = new subbusd_CAN();
  nl_assert(subbusd_core::subbusd);
  subbusd_core::subbusd->register_flavor(CAN);
}
