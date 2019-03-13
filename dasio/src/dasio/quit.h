/** @file dasio/quit.h */
#ifndef DASIO_CLIENT_QUIT_H_INCLUDED
#define DASIO_CLIENT_QUIT_H_INCLUDED

#include "client.h"

namespace DAS_IO {

  /**
   * @brief A client interface to cmd/Quit
   */
  class Quit : public Client {
    public:
      /**
       * @brief Quit client via Unix Domain socket
       */
      Quit();
      /**
       * @brief Quit client via TCP
       */
      Quit(const char *hostname);
      ~Quit();
      bool process_eof();
  };
}

#endif
