#include "nl_assert.h"
#include "../subbusd_int.h"
#include "subbusd_CAN.h"

using namespace DAS_IO;

subbusd_CAN_client::subbusd_CAN_client(DAS_IO::Authenticator *auth, int bufsize)
    : subbusd_client(auth, bufsize) {}
subbusd_CAN_client::~subbusd_CAN_client() {}

Serverside_client *new_subbusd_CAN_client(Authenticator *auth, SubService *ss) {
  ss = ss; // not interested
  subbusd_CAN_client *clt =
    new subbusd_CAN_client(auth, subbusd_CAN_client::subbusd_CAN_max_msg_size);
  return clt;
}

bool subbusd_CAN_client::incoming_sbreq(subbusd_req_t *req) {
  return error_return(SBS_NOT_IMPLEMENTED);
}

subbusd_CAN::subbusd_CAN() : subbusd_flavor("CAN", new_subbusd_CAN_client) {}
subbusd_CAN::~subbusd_CAN() {}

void subbusd_CAN::init_subbus() {
  // setup socket
}

void subbusd_CAN::shutdown_subbus() {
  // teardown socket
}

subbusd_CAN *subbusd_CAN::CAN = 0;

void subbusd_CAN_init_options(int argc, char **argv) {
  argc = argc;
  argv = argv;
  subbusd_CAN::CAN = new subbusd_CAN();
  nl_assert(subbusd_core::subbusd);
  subbusd_core::subbusd->register_flavor(subbusd_CAN::CAN);
}
