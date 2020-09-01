#ifndef MONARCHCTL_H_INCLUDED
#define MONARCHCTL_H_INCLUDED
#include "dasio/server.h"
#include "dasio/client.h"

void monarchctl_init_options(int argc, char **argv);

using namespace DAS_IO;

class monarchctl_ssclient : public Serverside_client {
  public:
    monarchctl_ssclient(Authenticator *Auth, const char *iname);
    // Specify how big the ibuf needs to be:
    static const int monarchctl_ssclient_ibufsize = 80;
    // Include whatever virtual function overrides you need here
    bool connected();
  protected:
    ~monarchctl_ssclient();
    // Include any local data here
};

/**
 * Class to send commands to a parent server
 */
class monarchctl_t : public Client {
  public:
    monarchctl_t(Server *srvr);
    bool app_connected();
    bool app_input();
  protected:
    bool connect_failed();
    Server *srvr;
    bool waiting_for_parent;
};

/**
 * Class to query a monarchctl server
 */
class monarchctlclt_t : public Client {
  public:
    monarchctlclt_t();
  protected:
    bool app_input();
    bool connect_failed();
};

#endif

