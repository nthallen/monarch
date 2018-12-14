/** @file dasio/tm_server.h */
#ifndef DASIO_TM_SERVER_H_INCLUDED
#define DASIO_TM_SERVER_H_INCLUDED

#include "server.h"

namespace DAS_IO {
  
  class TM_server;
  
  class TM_server_def {
    friend class TM_server;
    public:
      inline TM_server_def(const char *datum, void *data, int size)
        : datum(datum), data(data), size(size),
          interface(0), stale_count(0) {}
      void sync();
      uint16_t Stale(uint16_t limit = 0xFFFF);
      void close();
      const char *datum;
      void *data;
      int size;
    protected:
      TM_server *interface;
      uint16_t stale_count;
  };
  
  class TM_server : public Socket {
    public:
      TM_server(Authenticator *auth, const char *iname, TM_server_def *def);
      ~TM_server();
      static TM_server *new_tm_server(Authenticator *auth, SubService *ss);
      bool protocol_input();
      void close();
      void sync();
    protected:
      TM_server_def *def;
  };
  
}

#endif
