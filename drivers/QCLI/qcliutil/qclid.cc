/* qclisrvr.c
  Manages access to the QCLI through the Analog I/O board.
*/
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/select.h>
#include "dasio/appid.h"
#include "dasio/tm_data_sndr.h"
#include "nl.h"
#include "nl_assert.h"
#include "qcliutil.h"
#include "oui.h"
#include "qclidacsd.h"
#include "qclid.h"

using namespace DAS_IO;

QCLI_Command::qcli_cmd_def QCLI_Command::qcli_cmds[] = {
  { SW, "SW", 1, 0 },
  { RW, "RW", 0, 0 },
  { ST, "ST", 0, 0 },
  { CE, "CE", 0, 0 },
  { TN, "TN", 1, 0 },
  { TF, "TF", 1, 0 },
  { TP, "TP", 1, 0 },
  { D0, "D0", 1, 0 },
  { D1, "D1", 1, 0 },
  { D2, "D2", 1, 0 },
  { D3, "D3", 1, 0 },
  { QU, "QU", 0, 0 },
  { XX, NULL, 0, 0 }
};

QCLI_Command::QCLI_Command(qcli_dacs *qcli, const char *qcli_name)
    : Cmd_reader("Cmd", 40, qcli_name),
      qcli(qcli),
      qcli_name(qcli_name) {
}

/**
 * Handling the EOF case (read returns 0) will be external to parse_cmd(). Here we are given
 * a NUL-terminated string, and we'll just complain if it is malformed. 
 */

QCLI_Command::qcli_cmd_defp QCLI_Command::parse_cmd(unsigned char *cmd) {
  unsigned char *s = cmd;
  int i;
  qcli_cmd_def *cd;
  
  while ( isspace(*s) ) ++s;
  for ( i = 0; qcli_cmds[i].cmd; i++ ) {
    const char *mcmd = qcli_cmds[i].cmd;
    if ( s[0] == mcmd[0] && s[1] == mcmd[1] ) break;
  }
  cd = &qcli_cmds[i];
  if ( cd->index == XX ) {
    msg( 2, "Unrecognized command: '%s'", cmd );
  } else if ( cd->takes_arg ) {
    if ( s[2] != ':' ) {
      msg( 2, "Command '%s' requires argument. Received '%s'", cd->cmd, cmd );
    } else {
      unsigned char *arg;
      s += 3;
      arg = s;
      if ( *s == '-' ) ++s;
      if ( ! isdigit(*s) ) {
        msg( 2, "Command '%s' requires numeric argument. Received '%s'",
                cd->cmd, cmd );
      } else {
        cd->value = atoi((char*)arg);
        return cd;
      }
    }
  } else if ( s[2] == ':' ) {
    msg( 2, "Command '%s' does not take an argument. Received '%s'",
              cd->cmd, cmd );
  } else if ( s[2] != '\0' && !isspace(s[2]) ) {
    msg( 2, "Unrecognized command: '%s'", cmd );
  } else return cd;
  return NULL;
}

qcli_data_t qcli_data;

bool QCLI_Command::app_input() {
  qcli_cmd_defp cd;
  cd = parse_cmd(buf);
  if ( cd != NULL ) {
    switch ( cd->index ) {
      case SW:
        qcli->wr_stop_qcli( QCLI_SELECT_WAVEFORM + cd->value + 8 );
        qcli_data.qcli_wave = cd->value;
        break;
      case RW:
        qcli->wr_stop_qcli( QCLI_RUN_WAVEFORM );
        break;
      case ST:
        qcli->wr_stop_qcli( QCLI_STOP );
        break;
      case CE:
        qcli->wr_stop_qcli( QCLI_CLEAR_ERROR );
        break;
      case TN:
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_TON + (cd->value & 0xFF) );
        break;
      case TF:
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_TOFF + (cd->value & 0xFF) );
        break;
      case TP:
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_TPRE + (cd->value & 0xFF) );
        break;
      case D0:
        qcli->write_qcli( QCLI_SELECT_DAC + 0 );
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_DAC + (cd->value & 0xFF) );
        break;
      case D1:
        qcli->write_qcli( QCLI_SELECT_DAC + 1 );
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_DAC + (cd->value & 0xFF) );
        break;
      case D2:
        qcli->write_qcli( QCLI_SELECT_DAC + 2 );
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_DAC + (cd->value & 0xFF) );
        break;
      case D3:
        qcli->write_qcli( QCLI_SELECT_DAC + 3 );
        qcli->write_qcli( QCLI_LOAD_MSB + ((cd->value >> 8) & 0xFF) );
        qcli->wr_stop_qcli( QCLI_WRITE_DAC + (cd->value & 0xFF) );
        break;
      case QU:
        return true;
      default: msg( 4, "Unknown command" );
    }
  }
  return false;
}

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  const char *qcli_name = AppID.name;
  
  { qcli_dacs *qcli = new qcli_dacs();
    if (qcli->diags(0)) /* for now, ignore the result, just log */
      msg(0,"QCLI Passed Diagnostics");

    Loop ELoop;
    
    // open connections to cmd server and collection
    QCLI_Command *Cmd = new QCLI_Command(qcli, qcli_name);
    Cmd->connect();
    ELoop.add_child(Cmd);

    TM_data_sndr *TM = new TM_data_sndr("TM", 0, qcli_name,
            &qcli_data, sizeof(qcli_data));
    TM->connect();
    ELoop.add_child(TM);

    ELoop.event_loop();
    ELoop.delete_children();
    ELoop.clear_delete_queue();
  }

  AppID.report_shutdown();
  return 0;
}
