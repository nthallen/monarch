#ifndef CMD_RELAY_H_INCLUDED
#define CMD_RELAY_H_INCLUDED
#include "dasio/cmd_server.h"
#include "dasio/cmd_reader.h"
#include "dasio/cmd_writer.h"

using namespace DAS_IO;

class cmd_relay : public Cmd_reader {
  public:
    cmd_relay();
    ~cmd_relay();
    bool app_input();
    Cmd_writer *rxsrvr;
    static const char *txExp, *rxExp;
  protected:
    cmd_hdr_parser CHP;
    bool dropping_tx_cmds;
    int n_tx_cmds_dropped;
    int total_tx_cmds_dropped;
};

#endif
