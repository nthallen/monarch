/** @file negotiate.h */
#ifndef NEGOTIATE_H_INCLUDED
#define NEGOTIATE_H_INCLUDED

#include "dasio_socket.h"

namespace DAS_IO {
  
  class Socket::Negotiate : public Socket {
    public:
      typedef enum { Neg_connecting, Neg_negotiating, Neg_negotiated }
                         neg_state_t;
      Negotiate(const char *iname, int bufsz, const char *service, const char *sub_service);
      Negotiate(const char *iname, int bufsz, const char *hostname, const char *service,
                    const char *sub_service);
      virtual ~Negotiate();
      bool ProcessData(int flag);
      void close();
      bool connected();
      inline bool is_negotiated() { return neg_state == Neg_negotiated; }
    private:
      static const int obufsize = 128;
      char obuf[obufsize];
      neg_state_t neg_state;
      const char *sub_service;
  };
  
}

#endif
