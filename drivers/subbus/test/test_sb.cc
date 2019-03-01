/** @file test_sb.cc
 * @brief Test interfaces to subbus modules
 */
#include "dasio/appid.h"
#include "oui.h"
#include "subbuspp.h"
#include "nl.h"

DAS_IO::AppID_t DAS_IO::AppID("test_sb", "Subbus Test Program", "V1.0");

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  subbuspp *P = new subbuspp("subbusd", "CAN");
  int subfunc = P->load();
  if (subfunc) {
    msg(0, "Subbus subfunction %d, name %s", subfunc, P->get_subbus_name());
  } else {
    msg(3, "Failed to connect with subbus");
  }
  uint16_t value = P->read_subbus(0x0121);
  msg(0, "Read 0x%04X from 0x0121", value);
  value = P->write_ack(0x0121, 0x55AA);
  if (!value) msg(0, "no ack at 0x0121");
  P->subbus_quit();
}
