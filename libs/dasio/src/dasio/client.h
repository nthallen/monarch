/** @file dasio/client.h */
#ifndef DASIO_CLIENT_H_INCLUDED
#define DASIO_CLIENT_H_INCLUDED

#include "socket.h"

#define CMD_MAX_COMMAND_IN 300  // Maximum command message input length
#define CMD_MAX_COMMAND_OUT 160 // Maximum command message output length

namespace DAS_IO {
  
  class Client : public Socket {
    public:
      typedef enum { Clt_connecting, Clt_negotiating, Clt_negotiated, Clt_negotiation_failed }
                         clt_state_t;
      /**
       * @param iname the interface name
       * @param bufsz the input buffer size
       * @param hostname the remote host we are connecting to over
       *   TCP/IP
       * @param service the remote service name we are connecting to
       * @param sub_service the sub service name (without the
       *   service prefix)
       *
       * If hostname is 0, a Unix Domain socket is created on the
       * local machine, otherwise a TCP socket is used.
       */
      Client(const char *iname, int bufsz, const char *hostname,
             const char *service, const char *sub_service);
      /**
       * @param iname the interface name
       * @param bufsz the input buffer size
       * @param hostname the remote host we are connecting to over
       *   TCP/IP
       * @param service the remote service name we are connecting to
       * @param sub_service the sub service name (without the
       *   service prefix)
       *
       * If hostname is 0, a Unix Domain socket is created on the
       * local machine, otherwise a TCP socket is used.
       */
      Client(const char *iname, const char *function,
             const char *service, const char *sub_service,
             int bufsz);
    
      /**
       * Called via ProcessData() when new data is available to Clients
       * at the application level.
       *
       * See protocol_input() for details about parsing.
       *
       * @return true on an error requiring termination of the driver
       */
      virtual bool app_input();
      
      /**
       * Called when the negotiation is complete. Similar to connected(), but
       * called later in the process.
       *
       * @return true on an error requiring termination of the driver
       */
      virtual bool app_connected();
      
      /**
       * Called on EOF after successful negotiation. The default returns true;
       * @return true if the event loop should exit.
       */
      virtual bool app_process_eof();
      
      /**
       * Called if our login was unsuccessful. The connection will have been
       * closed and the buffer emptied. The default method delivers an error
       * and returns true to exit the loop.
       * @return true to exist the event loop
       */
      virtual bool app_negotiation_failed();
      
      bool protocol_input();
      bool process_eof();
      void close();
      bool connected();
      inline bool is_negotiated() { return clt_state == Clt_negotiated; }
      inline void set_subservice(const char *subs) { sub_service = subs; }
    protected:
      // virtual ~Client();
    private:
      static const int obufsize = 128;
      char obuf[obufsize];
      clt_state_t clt_state;
      const char *sub_service;
  };
  
}

#endif
