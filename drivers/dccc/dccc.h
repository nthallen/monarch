#ifndef DCCC_H_INCLUDED
#define DCCC_H_INCLUDED

#include "dasio/server.h"
#include "disc_cmd.h"

using namespace "dasio";

/*	dccc receives msgs of maximum size MAX_DCCC_MSG_SZ.
        they can be of the following form, each 1 byte:

                DASCMD DCT_QUIT DCV_QUIT
                DASCMD DCT_DCCC STROBEcmd/STEPcmd
                DC_MULTCMD #cmds STROBEcmd ...
                DC_MULTCMD #cmds STEPcmd ...
                DC_MULTCMD #cmds SETcmd hi-byte-value lo-byte-value ...
                DC_MULTCMD #cmds SELECTcmd hi-byte-value lo-byte-value ...
*/

class dccc_ssclient : public Serverside_client {
  public:
    inline dccc_ssclient(DAS_IO::Authenticator *orig, const char *iname) :
      Serverside_client(orig, iname, DCCC_MAX_CMD_BUF) {}
  protected:
    ~dccc_ssclient();
    bool protocol_input();
};

inline dccc_ssclient *new_dccc_ssclient(
    DAS_IO::Authenticator *Auth, DAS_IO::SubService *SS) {
  return new dccc_ssclient(Auth, SS);
}

#endif
