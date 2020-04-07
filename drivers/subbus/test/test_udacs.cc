#include "dasio/appid.h"
#include "subbuspp.h"
#include "dasio/msg.h"
#include "oui.h"

typedef struct {
  subbuspp *SB;
  const char *name;
  subbus_mread_req *mreq;
  uint16_t *rvals;
  bool saw_nack;
} uDACS_mreq;

uDACS_mreq uDACS_A;
uint16_t uDACS_A_rvals[0x16];

bool uDACS_mread(uDACS_mreq &mreq) {
  uint16_t nwords;
  int rv = mreq.SB->mread_subbus_nw(mreq.mreq, mreq.rvals, &nwords);
  if (rv < 0) {
    msg(2, "mread_subbus_nw(%s) returned error %d", mreq.name, rv);
    return false;
  }
  if (nwords != mreq.mreq->n_reads) {
    msg(2, "mread_subbus_nw(%s) returned %d words, expected %d",
          mreq.name, nwords, mreq.mreq->n_reads);
    return false;
  }
  switch (rv) {
    case SBS_OK:
    case SBS_ACK:
      if (mreq.saw_nack) {
        msg(0, "%s recovered from NACK", mreq.name);
        mreq.saw_nack = false;
      }
      return true;
    case SBS_NOACK:
      if (!mreq.saw_nack) {
        msg(2, "%s reported NACK on read", mreq.name);
        mreq.saw_nack = true;
      }
      return true;
    default:
      if (!mreq.saw_nack) {
        msg(2, "%s unexpected return code %d",
            mreq.name, rv);
        mreq.saw_nack = true;
      }
      return true;
  }
}

void identify_board(subbuspp *SB, const char *which) {
  uint16_t values[0x2D];
  uint16_t nread;
  subbus_mread_req *mreq = SB->pack_mread_request(0x2D, "2:1:5,8|28@9");
  int rv = SB->mread_subbus_nw(mreq, values, &nread);
  free_memory(mreq);
  if (rv == SBS_OK) {
    const char *desc = (const char *)&values[5];
    msg(0, "  Board ID:%d Build:%d S/N:%d Instrument:%d",
      values[0], values[1], values[2], values[3]);
    msg(0, "  Len: %d Desc: %s", values[4], desc);
  } else if (rv == SBS_NOACK) {
    msg(2, "NACK received from identify_board() request for %s", rv, which);
  } else {
    msg(2, "Error %d from identify_board() request for %s", rv, which);
  }
}

void uDACS_init() {
  msg(0, "uDACS_init()");
  uDACS_A.SB = new subbuspp("uDACS_A", "serusb");
  uDACS_A.name = "uDACS_A";
  uDACS_A.rvals = &uDACS_A_rvals[0];
  uDACS_A.saw_nack = false;
  msg(0, "uDACS_A->load()");
  int subfunc = uDACS_A.SB->load();
  if (subfunc == 0)
    msg(3, "load() failed");
  if (subfunc != 9)
    msg(2, "Expected Subfunction 9 for uDACS, was %d", subfunc);
  msg(0, "uDACS_A->identify_board();");
  identify_board(uDACS_A.SB, "uDACS_A");
  uDACS_A.mreq = uDACS_A.SB->pack_mread_request(0x16, "10:1:25");
}

int main(int argc, char **argv) {
  int count = 0;
  oui_init_options(argc, argv);
  uDACS_init();
  msg(0, "Attempting to tick");
  uDACS_A.SB->tick_sic();
  msg(0, "tick_sic() returned successfully");
  for (;;) {
    if (uDACS_mread(uDACS_A)) {
      msg(0, "%5d: N: %5u", ++count, uDACS_A_rvals[21]);
    }
  }
}

DAS_IO::AppID_t DAS_IO::AppID("test_udacs", "uDACS Test Program", "V1.0");

