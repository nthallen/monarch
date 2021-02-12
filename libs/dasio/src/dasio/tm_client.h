/** \file tm_client.h
 * TM Client Classes
 */
#ifndef TM_CLIENT_H_INCLUDED
#define TM_CLIENT_H_INCLUDED
#include <stdio.h>
#include "tm.h"
#include "tm_rcvr.h"
#include "client.h"

#ifdef __cplusplus

namespace DAS_IO {

/**
 * @brief tm_client is a pure virtual class for receiving
 * telemetry data from tm_bfr. At a minimum, a subclass must
 * implement tm_rcvr's process_data() method.
 */
class tm_client : public DAS_IO::Client, public DAS_IO::tm_rcvr {
  public:
    tm_client(int bufsize, bool fast = true, const char *hostname = 0);
    // void resize_buffer(int bufsize_in);
    static char *srcnode;
    static const char *tm_client_hostname;
  protected:
    // int bfr_fd;
    bool app_input();
    bool app_connected();
    // bool tm_quit;
    virtual bool process_eof();
};

class ext_tm_client : public tm_client {
  public:
    inline ext_tm_client(int bufsize_in, bool fast = false, const char *hostname = 0) :
      tm_client(bufsize_in, fast, hostname) {}
  protected:
    unsigned int process_data();
};

}

extern "C" {
#endif

/* This is all that is exposed to a C module */
extern void tm_set_srcnode(char *nodename);

#ifdef __cplusplus
};
#endif

#endif
