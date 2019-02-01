#ifndef MEMO_H
#define MEMO_H

#define DRBFR_NPARTS_MAX 5
#define DRBFR_MSG_MAX 16384

#include "dasio/server.h"
#include "dasio/loop.h"

using namespace DAS_IO;

class MemoServer {
    public:
      MemoServer(const char *service, int bufsz); // bufsz to be phased out
      ~MemoServer();
      typedef enum { Srv_Unix = 1, Srv_TCP = 2, Srv_Both = 3 } Srv_type;
      void Start(Srv_type which);
      SubServices Subs;
      Server_socket *Unix;
      Server_socket *TCP;
      Loop ELoop;
      inline const char *get_service() { return service; }
    protected:
      const char *service;
      int bufsz; // going away
};

/* I have group related members into structs here purely
   to help make clear which members are related.
   If you don't like this approach, let me know.
*/

class memo_socket : public DAS_IO::Socket {
  public:
    inline memo_socket(Authenticator *Auth, const char *iname) : Socket(Auth, iname, Auth->fd) {}
    ~memo_socket();
  protected:
    bool protocol_input();
};
void memo_init_options( int argc, char **argv );

memo_socket *new_memo_socket(Authenticator *Auth, SubService *SS);

#endif

