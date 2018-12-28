/** @file dasio/server.h */
#ifndef DASIO_SERVER_H_INCLUDED
#define DASIO_SERVER_H_INCLUDED

#include <map>
#include <string>
#include "socket.h"

namespace DAS_IO {

  class SubService;
  class Authenticator;
  
  /**
   * Defines a function type for switching interface classes after
   * negotiation. The function can return zero if the connection is
   * refused for reasons beyond the authentication. For example, the
   * TM_server class will refuse a new connection if the specified
   * datum is already being written to by another process.
   * @return Pointer to a Socket subclass or zero if an error occurs.
   */
  typedef Socket *(* socket_clone_t)(Authenticator *, SubService *);
  
  class SubService {
    public:
      /**
       * @param svcs The service/subservice string
       * @param func Factory function to the appropriate Socket subclass
       * @param svc_data subservice-specific data reference
       */
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
      /**
       * @param subservice The service/subservice string
       * @return true if the subservice was removed successfully, false if
       * it was not defined.
       */
      bool rm_subservice(std::string subservice);
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
   *
   * Subsp is a pointer here because we expect the list of SubServices
   * to be shared between two server sockets (Unix & TCP) in many
   * cases.
   */
  class Server : public Socket {
    public:
      Server(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type, SubServices *Subsp);
      ~Server();
      Socket *new_client(const char *iname, int fd);
    protected:
      SubServices *Subsp;
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
      inline const char *get_client_app() { return client_app; }
    protected:
      bool not_word(const char *&w, int &len);
      bool not_svc(const char *&svc, int &len);
      SubServices *Subsp;
      const char *client_app;
  };

}

#endif
