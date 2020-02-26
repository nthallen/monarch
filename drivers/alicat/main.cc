/** @file main.cc */
#include "dasio/tm_data_sndr.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "modbus_cmd.h"
#include "alicat_int.h"
#include "alicat.h"
#include "oui.h"
#include "nl.h"

alicat_t Alicat;
const char *Alicat_port = "/dev/ttyUSB0";

using namespace DAS_IO;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  Loop ELoop;
  TM_data_sndr *TM =
    new TM_data_sndr("TM", "Alicat", 0, (void *)&Alicat, sizeof(Alicat));
  Modbus::RTU *MB = new Modbus::RTU("RTU", 80, Alicat_port);
  MB->setup(115200, 8, 'n', 1, 5, 1);
  MB->flush_input();
  MB->add_device(new Modbus::alicat_device("AC1", 0x01, &(Alicat.Dev[0])));
  MB->add_device(new Modbus::alicat_device("AC2", 0x02, &(Alicat.Dev[1])));
  Modbus::modbus_cmd *Cmd = new Modbus::modbus_cmd("alicat", MB);
  Cmd->connect();
  TM->connect();
  ELoop.add_child(Cmd);
  ELoop.add_child(TM);
  ELoop.add_child(MB);
  msg(0, "%s %s Starting", DAS_IO::AppID.fullname, DAS_IO::AppID.rev);
  ELoop.event_loop();
  ELoop.delete_children();
  msg(0, "%s Terminating", DAS_IO::AppID.name);
  return 0;
}
