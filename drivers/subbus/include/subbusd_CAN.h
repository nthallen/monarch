#ifndef SUBBUSD_CAN_H_INCLUDED
#define SUBBUSD_CAN_H_INCLUDED
#include "dasio/server.h"
#include "subbusd_int.h"

extern void subbusd_CAN_init_options(int argc, char **argv);
class subbusd_CAN;

class subbusd_CAN_client : public subbusd_client {
  public:
    subbusd_CAN_client(DAS_IO::Authenticator *orig, int bufsize, subbusd_CAN *fl);
    ~subbusd_CAN_client();
    bool incoming_sbreq(subbusd_req_t *req);
    void enqueue_canreq();
    static const int subbusd_CAN_max_req_size = 512;
    static const int subbusd_CAN_max_rep_size = 512;
  private:
    subbusd_CAN *flavor;
    uint8_t req_buf[subbusd_CAN_max_req_size];
    int req_nc;
    uint8_t rep_buf[subbusd_CAN_max_rep_size];
    int CAN
};

class subbusd_CAN : public subbusd_flavor {
  public:
    subbusd_CAN();
    ~subbusd_CAN();
    void init_subbus();
    void shutdown_subbus();
    // static subbusd_CAN *CAN;
  private:
    // CAN sockets, states, etc.
};

#endif
