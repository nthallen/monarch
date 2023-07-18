/** @file cmd_reader.h */
#ifndef CMD_READER_H_INCLUDED
#define CMD_READER_H_INCLUDED

#include "client.h"

namespace DAS_IO {

  /**
   * @brief
   * Virtual base class for reading commands from the command
   * server for a specific command channel.
   *
   * A subclass must
   * override Client::app_input() to parse the incoming commands.
   * Note that overriding protocol_input() instead will cause
   * Client connection to the server to fail.
   *
   * Commands are text-based and generally structured to be
   * easy to parse. The cmdgen language is used to translate
   * between the relatively verbose command server inputs and
   * the fairly terse commands output to the command channels.
   *
   * Every command channel receives "Q\n" when the server quits,
   * and the subclass should recognize this command and terminate
   * when it is received. It is often useful to include a command
   * within the cmdgen specification to explicitly send the quit
   * command to this command channel if for no other reason
   * to verify that it terminates properly.
   *
   * Within cmdgen, a command channel is defined using the syntax
   * '%INTERFACE <cmdchannel>' (for a channel named 'cmdchannel').
   * Within the cmdgen source, commands can be written to the
   * channel using the syntax: if_cmdchannel.Turf(fmt, args ...)
   * where cmdchannel is replaced with the channel name, and fmt
   * and args are standard printf-style arguments.
   */
  class Cmd_reader : public Client {
    public:
      /**
       * @param iname Interface mnemonic
       * @param bufsize Size of the input buffer
       * @param cmdchannel The label specifying which commands to receive
       * @param function Optional function name for Client connection
       * Defaults to "srvr"
       *
       * iname is arbitrary and used only in log messages to help
       * clarify which interface is involved.
       *
       * cmdchannel matches the corresponding cmdgen %INTERFACE definition.
       *
       * function only needs to be specified to differentiate access
       * between more than on command server. This is true for a command
       * relay application, or for any program that needs to address
       * both a local (session) server and a remote command server.
       */
      inline Cmd_reader(const char *iname, int bufsize,
                        const char *cmdchannel,
                        const char *function = "srvr")
          : Client(iname, function, "cmd",
                   cmdchannel, bufsize) {
        flags = Interface::Fl_Read;
      }
    protected:
  };

}

#endif
