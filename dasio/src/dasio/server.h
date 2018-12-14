/** @file dasio/server.h */
#ifndef DASIO_SERVER_H_INCLUDED
#define DASIO_SERVER_H_INCLUDED

#include <map>
#include <string>
#include "socket.h"

namespace DAS_IO {

  class SubService;
  class Authenticator;
  
  typedef Socket *(* socket_clone_t)(Authenticator *, SubService *);
  
  class SubService {
    public:
      SubService(std::string name, socket_clone_t func, void *svc_data);
      ~SubService();
      std::string name;
      socket_clone_t func;
      void *svc_data;
  };
  
  class SubServices {
    public:
      SubServices();
      ~SubServices();
      /**
       * @return true if the subservice was added successfully, false if
       * it was already defined.
       */
      bool add_subservice(SubService *def);
      SubService *find_subservice(std::string subservice);
    private:
      std::map<std::string,SubService *> subs;
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
      Socket *new_client(const char *iname, int fd);
      bool add_subservice(SubService *);
    protected:
      SubServices Subs;
  };

  class Authenticator : public Socket {
    public:
      Authenticator(Server *orig, const char *iname, int fd, SubServices *SS);
      ~Authenticator();
      /**
       * Currently processes a single line of input, and either accepts
       * or rejects.
       * @return true if the server's event loop should terminate
       */
      bool protocol_input();
    protected:
      bool not_word(const char *&w, int len);
      bool not_svc(const char *&svc, int len);
      SubServices *Subsp;
  };

}

#endif
