/** @file dasio/server.h */
#ifndef DASIO_SERVER_H_INCLUDED
#define DASIO_SERVER_H_INCLUDED

#include <map>
#include "socket.h"

namespace DAS_IO {

  class Authenticator;
  
  typedef Socket *(* socket_clone_t)(Authenticator *);
  
  class SubServices {
    public:
      SubServices();
      ~SubServices();
      /**
       * @return true if the subservice was added successfully, false if
       * it was already defined.
       */
      bool add_subservice(const char *subservice, socket_clone_t func);
      socket_clone_t find_subservice(const char *subservice);
    private:
      std::map<std::string,socket_clone_t> subs;
  };
  
  /**
   * A Server object sets up a listener of the designated socket_type_t.
   * When a connection is accepted, it creates and Authenticator
   * object to handle the negotiation. The Authenticator uses
   * subservice information from the negotiation to decide what type
   * of object to transform into.
   *
   * A server application then needs to provide socket_clone_t
   * function(s) that do what is necessary.
   */
  class Server : public Socket {
    public:
      Server(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type = Socket_Unix);
      ~Server();
      class Authenticator : public Socket {
        public:
          Authenticator(Server *orig, const char *iname, int fd);
          ~Authenticator();
          bool protocol_input();
      };
      bool add_subservice(const char *subservice, socket_clone_t);
    protected:
      SubServices Subs;
  };

}

#endif
