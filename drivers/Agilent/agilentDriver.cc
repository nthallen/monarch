#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "agilent_int.h"
#include "oui.h"
#include "dasio/msg.h"
#include "dasio/quit.h"
#include "dasio/appid.h"

using namespace DAS_IO;

const int agilent_ctrl::BUFFER_SIZE = 10000;
const int agilent_ctrl::devicePort = 5025;
const char *agilent_ctrl::hostname = "agilent.arp.harvard.edu";
agilent_t Agilent;

agilent_ctrl::agilent_ctrl(TM_data_sndr *TM)
    : Socket("Agnt", BUFFER_SIZE, hostname, "agilent"),
      TM(TM),
      state(ctrl_idle),
      saveCount(0) {
  flags |= Fl_Read;
}

void agilent_ctrl::Request() {
  if (state == ctrl_idle) {
    iwrite( "READ?\n");
    TO.Set(10,0);
    msg(MSG_DEBUG, "READ?" );
    state = ctrl_read;
  }
}

bool agilent_ctrl::connected() {
  state = ctrl_info;
  iwrite( "SYST:COMM:LAN:TELN:WMES?\n");
  TO.Set(0,200);
  return false;
}

bool agilent_ctrl::protocol_input() {
  int count = 0;
  switch (state) {
    case ctrl_read:
      // Skip any echos or garbage at the beginning
      while (cp < nc && buf[cp] != '+' && buf[cp] != '-')
        ++cp;

      for (;;) {
        double val;
        if (not_double(val)) {
          if (cp < nc) {
            report_err("%s: syntax error on Read?:", iname);
            consume(nc);
            state = ctrl_idle;
            break;
          } else return false; // partial record: wait
        }
        Agilent.data[count++] = val;
        if (cp >= nc) return false; // partial record: wait
        if (buf[cp] == '\n') {
          if (saveCount == 0) {
            saveCount = count;
            msg(MSG, "%s: Number of data points is: %d", saveCount);
            for (int i = saveCount; i < 20; i++ )
                    Agilent.data[i] = 0;
          }
          if (saveCount != count) {
            msg(MSG_ERROR, "Number of data points changed from %d to %d",
              saveCount, count);
            saveCount = count;
            for (int i = saveCount; i < 20; i++ )
                    Agilent.data[i] = 0;
          }
          Agilent.stale = 0;
          Agilent.count = count;
          break;
        } else if (buf[cp] != ',') {
          report_err("%s: syntax error after double", iname);
          consume(nc);
          state = ctrl_idle;
          break;
        }
      }
      if (state == ctrl_read) {
        report_ok(cp);
        TM->Send();
        state = ctrl_idle;
      }
      break;
    case ctrl_info:
      msg(MSG, "%s", buf);
      state = ctrl_idle;
      break;
    case ctrl_idle:
      report_err("%s: Unexpected input", iname);
      consume(nc);
      break;
    default:
      msg(MSG_ERROR, "%s: Invalid state: %d", iname, state);
      state = ctrl_idle;
      break;
  }
  Request();
  return false;
}

bool agilent_ctrl::protocol_timeout() {
  switch (state) {
    case ctrl_idle:
      break;
    case ctrl_info:
      msg(MSG_ERROR, "%s: Timeout on info request", iname);
      break;
    case ctrl_read:
      report_err("%s: timeout on Read", iname);
      break;
  }
  state = ctrl_idle;
  Request();
  return false;
}

bool agilent_ctrl::protocol_gflag(int flag) {
  ++Agilent.stale;
  return false;
}

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  { Loop ELoop;
    Quit *Q = new Quit;
    Q->connect();
    ELoop.add_child(Q);
    
    TM_data_sndr *TM =
      new TM_data_sndr("TM",0,"Agilent",&Agilent,sizeof(Agilent));
    TM->connect();
    ELoop.add_child(TM);
    
    agilent_ctrl *AC = new agilent_ctrl(TM);
    AC->connect();
    ELoop.add_child(AC);
    
    msg(0, "%s %s Starting", DAS_IO::AppID.fullname, DAS_IO::AppID.rev);
    ELoop.event_loop();
    ELoop.delete_children();
    ELoop.clear_delete_queue();
  }
  msg(0, "%s Terminating", DAS_IO::AppID.name);
  return 0;
}
