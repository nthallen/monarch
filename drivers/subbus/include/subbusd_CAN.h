#ifndef SUBBUSD_CAN_H_INCLUDED
#define SUBBUSD_CAN_H_INCLUDED
#include "dasio/server.h"
#include "subbusd_int.h"

extern void subbusd_CAN_init_options(int argc, char **argv);

class subbusd_CAN_client : public subbusd_client {
  public:
    subbusd_CAN_client(DAS_IO::Authenticator *orig, int bufsize);
    ~subbusd_CAN_client();
    bool incoming_sbreq(subbusd_req_t *req);
    static const int subbusd_CAN_max_msg_size = 512;
};

class subbusd_CAN : public subbusd_flavor {
  public:
    subbusd_CAN();
    ~subbusd_CAN();
    void init_subbus();
    void shutdown_subbus();
    static subbusd_CAN *CAN;
  private:
    // CAN sockets, states, etc.
};

#endif
