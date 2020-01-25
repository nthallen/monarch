/** @file cmd_reader.h */
#ifndef CMD_READER_H_INCLUDED
#define CMD_READER_H_INCLUDED

#include "dasio/client.h"

namespace DAS_IO {

  class Cmd_reader : public Client {
    public:
      inline Cmd_reader(const char *iname, int bufsize, const char *cmdchannel)
          : Client(iname, bufsize, CmdServerNode, "cmd", cmdchannel) {
        flags = Interface::Fl_Read;
      }
      static const char *CmdServerNode;
    protected:
  };

}

#endif
