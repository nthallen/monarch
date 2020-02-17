#ifndef MEMO_H
#define MEMO_H

#define DRBFR_NPARTS_MAX 5
#define DRBFR_MSG_MAX 16384

#include "dasio/server.h"
#include "dasio/loop.h"
#include "nl.h"

using namespace DAS_IO;

class memo_sigif : public server_sigif {
  public:
    inline memo_sigif(Server *srvr) : server_sigif(srvr) {}
    bool serialized_signal_handler(uint32_t signals_seen);
};

/* I have group related members into structs here purely
   to help make clear which members are related.
   If you don't like this approach, let me know.
*/

class memo_socket : public DAS_IO::Serverside_client {
  public:
    inline memo_socket(Authenticator *Auth, const char *iname) : DAS_IO::Serverside_client(Auth, iname, 1000) {}
    ~memo_socket();
  protected:
    bool protocol_input();
};

extern int memo_quit_threshold;

void memo_init_options( int argc, char **argv );

memo_socket *new_memo_socket(Authenticator *Auth, SubService *SS);

#endif
