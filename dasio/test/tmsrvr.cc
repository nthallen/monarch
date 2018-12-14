/* TM server example */
#include "dasio/tm_server.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "TMtest.h"
#include "nl.h"

using namespace DAS_IO;

TMtest_t TMtest;

const char *opt_string = "vo:mV";

AppID_t DAS_IO::AppID("tmsrvr", "Demo TM Server", "V1.0");

int main(int argc, char **argv) {
  SubServices Subs;
  Loop ELoop;
  Subs.add_subservice(
    new SubService(
      "DG/data/TMtest",
      (socket_clone_t)TM_server::new_tm_server,
      new TM_server_def("TMtest", &TMtest, sizeof(TMtest))
    )
  );
  Server S("listen", 128, "DG", Socket::Socket_Unix, &Subs);
  ELoop.add_child(&S);
  nl_error(0, "%s %s Starting", AppID.name, AppID.rev);
  ELoop.event_loop();
  nl_error(0, "Terminating");
  return 0;
}
