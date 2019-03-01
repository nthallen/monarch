/** @file test_sb.cc
 * @brief Test interfaces to subbus modules
 */
#include "dasio/appid.h"
#include "oui.h"
#include "subbuspp.h"
#include "nl.h"

DAS_IO::AppID_t DAS_IO::AppID("test_sb", "Subbus Test Program", "V1.0");

typedef struct {
  uint16_t n_words;
  char name[0x40];
} device_name_t;

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
  device_name_t dname;
  subbus_mread_req *mreq = P->pack_mread_request((sizeof(device_name_t)+1)/2, "6|40@7");
  int rv = P->mread_subbus(mreq, (uint16_t*)&dname);
  if (rv < 0) {
    msg(2, "mread_subbus returned error %d", rv);
  } else if (rv == SBS_NOACK) {
    msg(1, "mread_subbus return SBS_NOACK");
  }
  P->subbus_quit();
}
