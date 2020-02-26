/** @file main.cc */
#include "dasio/tm_data_sndr.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "modbus_cmd.h"
#include "alicat_int.h"
#include "alicat.h"
#include "oui.h"
#include "nl.h"

alicat_tm_t *Alicat;
board_id_t *board_id;
const char *Alicat_port = "/dev/ttyUSB0";
const char *address_opts;
int n_drives;

using namespace DAS_IO;

void configure_devices(Modbus::RTU *MB) {
  const char *s = address_opts;
  n_drives = 0;
  // First make a crude pass through the addresses
  // to count the number of devices. We'll complain
  // about syntax problems if any on the second pass.
  while (*s) {
    ++n_drives;
    while (*s && *s != ',') ++s;
  }
  
  Alicat = (alicat_tm_t *)new_memory(n_drives * sizeof(alicat_tm_t));
  board_id = (board_id_t *)new_memory(n_drives * sizeof(board_id_t));
  
  int index = 0;
  s = address_opts;
  while (*s) {
    int address = 0;
    while (isdigit(*s)) {
      address = address*10 + (*s++) - '0';
    }
    if (address < ALICAT_MIN_ADDRESS || address > ALICAT_MAX_ADDRESS) {
      msg(MSG_FATAL,"Invalid device address %d in option string '%s'",
        address, address_opts);
    }
    board_id[index].device_index = index;
    board_id[index].device_address = address;
    if (*s == ':') {
      int i;
      ++s;
      for (i = 0; i < MNEM_LEN-1 && *s && isalnum(*s); ++i) {
        board_id[index].mnemonic[i] = *s++;
      }
      board_id[index].mnemonic[i] = '\0';
    } else board_id[index].mnemonic[0] = '\0';
    ++index;
    if (*s == ',') ++s;
    else if (*s == '\0') break;
    else msg(MSG_FATAL,
      "Invalid character in address option string after %d address(es): '%s'",
      index, address_opts);
  }
  msg(0, "Addressing %d drives", n_drives);
  for (index = 0; index < n_drives; ++index) {
    MB->add_device(new Modbus::alicat_device(
      board_id[index].mnemonic, board_id[index].device_address,
      &Alicat[index]));
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  Loop ELoop;
  Modbus::RTU *MB = new Modbus::RTU("RTU", 80, Alicat_port);
  MB->setup(115200, 8, 'n', 1, 5, 1);
  MB->flush_input();
  configure_devices(MB);

  Modbus::modbus_cmd *Cmd = new Modbus::modbus_cmd("alicat", MB);
  Cmd->connect();
  ELoop.add_child(Cmd);

  TM_data_sndr *TM =
    new TM_data_sndr("TM", "Alicat", 0, (void *)Alicat,
      n_drives * sizeof(alicat_tm_t));
  TM->connect();
  ELoop.add_child(TM);

  ELoop.add_child(MB);
  msg(0, "%s %s Starting", DAS_IO::AppID.fullname, DAS_IO::AppID.rev);
  ELoop.event_loop();
  ELoop.delete_children();
  msg(0, "%s Terminating", DAS_IO::AppID.name);
  return 0;
}
