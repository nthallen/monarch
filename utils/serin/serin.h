#ifndef SERIN_H_INCLUDED
#define SERIN_H_INCLUDED
#include "dasio/tm_gen.h"
#include "dasio/server.h"

using namespace DAS_IO;

class serin : public tm_generator {
  public:
    serin();
    void start();
    void service_row_timer();
};

class serin_serin : public Serverside_client {
  public:
    serin_serin(Authenticator *auth, const char *iname, serin *tm);
    /** Adds serin subservice to the server */
    static void attach(serin *srvr);
    static Serverside_client *new_serin_serin(
              Authenticator *auth, SubService *SS);
    static const int serin_bufsize = 400;
  protected:
    bool protocol_input();
    serin *srvr;
};

#endif
