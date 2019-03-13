/** @file test_sb.cc
 * @brief Test interfaces to subbus modules
 */
#include <stdio.h>
#include "dasio/appid.h"
#include "oui.h"
#include "subbuspp.h"
#include "nl.h"

DAS_IO::AppID_t DAS_IO::AppID("test_sb", "Subbus Test Program", "V1.0");

typedef struct {
  uint16_t n_words;
  char name[0x40];
} device_name_t;

void test_mread(subbuspp *P, int nreads, const char *str) {
  uint16_t rvals[80], nread;
  char msgbuf[80];
  int nc = 0;
  
  subbus_mread_req *mreq = P->pack_mread_request(nreads, str);
  msg(0, "mread(0x%X,'%s')", nreads, str);
  int rv = P->mread_subbus_nw(mreq, &rvals[0], &nread);
  if (rv < 0) {
    msg(2, "mread_subbus returned error %d", rv);
  } else if (rv == SBS_NOACK) {
    msg(1, "mread_subbus return SBS_NOACK");
  }
  if (nread != nreads)
    msg(1, "mread returned %d/%d words", nread, nreads);
  if (nread > 0) {
    for (int i = 0; i < nread; ++i) {
      nc += snprintf(&msgbuf[nc], 80-nc, " 0x%04X", rvals[i]);
    }
    msg(0, "mread returned:%s", msgbuf);
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  subbuspp *P = new subbuspp("subbusd", "CAN");
  int subfunc = P->load();
  if (subfunc) {
    msg(0, "Subbus subfunction %d, name %s", subfunc, P->get_subbus_name());
  } else {
    msg(3, "Failed to connect with subbus");
  }
  msg(0,"read_subbus(0x0121)");
  uint16_t value = P->read_subbus(0x0121);
  msg(0, "Read 0x%04X from 0x0121", value);
  msg(0, "write_ack(0x0121, 0x55AA)");
  value = P->write_ack(0x0121, 0x55AA);
  if (!value) msg(0, "no ack at 0x0121");
  test_mread(P, 0x21, "106|20@107");
  test_mread(P, 8, "105,106,107,108,109,10A,10B,10C");
  test_mread(P, 8, "105:1:10C");
  test_mread(P, 4, "105:2:10C");
  test_mread(P, 6, "105,107,10A:2:110");
  test_mread(P, 9, "105,107,10A:1:110");
  // device_name_t dname;
  // subbus_mread_req *mreq1 = P->pack_mread_request((sizeof(device_name_t)+1)/2, "106|20@107");
  // msg(0, "mread('6|20@7')");
  // int rv = P->mread_subbus(mreq1, (uint16_t*)&dname);
  P->subbus_quit();
}
