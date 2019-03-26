/* TM server example */
#include "dasio/tm_data_rcvr.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "dasio/msg.h"
#include "TMtest.h"
#include "nl.h"

using namespace DAS_IO;

TMtest_t TMtest;
TM_data_rcvr_def TMtest_def("TMtest", &TMtest, sizeof(TMtest));

const char *opt_string = "vo:mV";

AppID_t DAS_IO::AppID("tmsrvr", "Demo TM Server", "V1.0");

int main(int argc, char **argv) {
  Server S("DG");
  S.set_passive_exit_threshold(1);
  S.add_subservice(
    new SubService(
      "DG/data/TMtest",
      TM_data_rcvr::new_tm_data_rcvr,
      &TMtest_def
      // new TM_data_rcvr_def("TMtest", &TMtest, sizeof(TMtest))
    )
  );
  S.Start(DAS_IO::Server::Srv_Unix);
  return 0;
}
