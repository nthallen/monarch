#ifndef TM_GEN_CMD_H
#define TM_GEN_CMD_H

#include <signal.h>
#include "server.h"
#include "tm_gen.h"

namespace DAS_IO {
  
class tm_generator;

class tm_gen_cmd : public DAS_IO::Serverside_client {
  public:
    tm_gen_cmd(Authenticator *Auth, const char *iname,
              tm_generator *tm_gen);
    bool protocol_input();
    bool process_eof();
    static int const tm_gen_CMD_BUFSIZE = 80;
    static void attach(tm_generator *tmgp); // add to dispatch list
  protected:
    virtual ~tm_gen_cmd();
  private:
    tm_generator *tmg;
};

Serverside_client *new_tm_gen_cmd(Authenticator *Auth, SubService *SS);

}

#endif

