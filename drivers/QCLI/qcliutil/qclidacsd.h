#ifndef QCLIDACSD_H_INCLUDED
#define QCLIDACSD_H_INCLUDED
#include "dasio/cmd_reader.h"
#include "qcliutil.h"

using namespace DAS_IO;

class QCLI_Command : public Cmd_reader {
  public:
    QCLI_Command(qcli_dacs *qcli, const char *qcli_name);
    bool app_input();
  protected:

    enum qcli_cmd { SW, RW, ST, CE, TN, TF, TP, D0, D1, D2, D3, QU, XX };

    typedef struct {
      enum qcli_cmd index;
      const char *cmd;
      int takes_arg;
      int value;
    } qcli_cmd_def, *qcli_cmd_defp;

    qcli_cmd_defp parse_cmd(unsigned char *cmd);
    qcli_dacs *qcli;
    const char *qcli_name;
    static qcli_cmd_def qcli_cmds[];
};

#endif
