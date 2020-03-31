/** @file dasio/quit.h */
#ifndef DASIO_CLIENT_QUIT_H_INCLUDED
#define DASIO_CLIENT_QUIT_H_INCLUDED

#include "cmd_reader.h"
#include "server.h"

namespace DAS_IO {

  /**
   * @brief A client interface to cmd/Quit
   */
  class Quit : public Cmd_reader {
    public:
      /**
       * If the optional Server pointer is provided,
       * a full shutdown will be requested when the
       * quit message is received. Otherwise, the
       * Loop's set_loop_exit() is called.
       * @brief Quit client
       * @param srvr optional pointer to Server
       */
      Quit(Server *srvr = 0);
      bool process_eof();
    protected:
      Server *srvr;
  };
}

#endif
