/** @file tmclt.cc */
#include "dasio/tm_data_sndr.h"
#include "dasio/appid.h"
#include "dasio/loop.h"
#include "dasio/msg.h"
#include "TMtest.h"
#include "nl.h"

using namespace DAS_IO;

TMtest_t TMtest;

AppID_t DAS_IO::AppID("tmclient", "Demo TM Client", "V1.0");

const char *opt_string = "vo:mV";

class myTMclt : public TM_data_sndr {
  public:
    inline myTMclt(const char *iname, const char *datum, const char *data, uint16_t size)
      : TM_data_sndr(iname, datum, data, size) {}
    inline ~myTMclt() {}
    bool app_connected() override;
    bool tm_sync() override;
};

bool myTMclt::app_connected() {
  msg(0, "myTMclt::app_connected()");
  TM_data_sndr::app_connected();
  flags |= gflag(0);
  return false;
}

bool myTMclt::tm_sync() {
  ++TMtest.count;
  return false;
}

int main(int argc, char **argv) {
  myTMclt TMclt("client", "TMtest", (const char *)&TMtest, sizeof(TMtest));
  TMclt.connect();
  Loop ELoop;
  ELoop.add_child(&TMclt);
  msg(0, "%s %s Starting", AppID.name, AppID.rev);
  ELoop.event_loop();
  msg(0, "Terminating");
  return 0;
}
