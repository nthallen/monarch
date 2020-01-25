/** @file dasio/quit.h */
#ifndef DASIO_CLIENT_QUIT_H_INCLUDED
#define DASIO_CLIENT_QUIT_H_INCLUDED

#include "cmd_reader.h"

namespace DAS_IO {

  /**
   * @brief A client interface to cmd/Quit
   */
  class Quit : public Cmd_reader {
    public:
      /**
       * @brief Quit client
       */
      Quit();
      bool process_eof();
  };
}

#endif
