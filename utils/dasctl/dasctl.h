#ifndef DASCTL_H_INCLUDED
#define DASCTL_H_INCLUDED
#include "dasio/server.h"
#include "dasio/client.h"

void dasctl_init_options(int argc, char **argv);

using namespace DAS_IO;

class dasctl_ssclient : public Serverside_client {
  public:
    dasctl_ssclient(Authenticator *Auth, const char *iname);
    // Specify how big the ibuf needs to be:
    static const int dasctl_ssclient_ibufsize = 80;
    // Include whatever virtual function overrides you need here
    bool connected();
  protected:
    ~dasctl_ssclient();
    // Include any local data here
};

/**
 * Class to send commands to a parent server
 */
class dasctl_t : public Client {
  public:
    dasctl_t(Server *srvr);
    bool app_connected();
    bool app_input();
  protected:
    bool connect_failed();
    Server *srvr;
    bool waiting_for_parent;
};

/**
 * Class to query a dasctl server
 */
class dasctlclt_t : public Client {
  public:
    dasctlclt_t();
  protected:
    bool app_input();
    bool connect_failed();
};

#endif

