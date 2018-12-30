/* TM server example */
#include "dasio/tm_server.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "TMtest.h"
#include "nl.h"

using namespace DAS_IO;

TMtest_t TMtest;
TM_data_rcvr_def TMtest_def("TMtest", &TMtest, sizeof(TMtest));

const char *opt_string = "vo:mV";

AppID_t DAS_IO::AppID("tmsrvr", "Demo TM Server", "V1.0");

class myserver : public Server {
  public:
    myserver(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type, SubServices *Subsp);
    ~myserver();
    void connect();
    bool protocol_timeout();
};

myserver::myserver(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type, SubServices *Subsp)
        : Server(iname, bufsz, service, socket_type, Subsp) {}

myserver::~myserver() {}
        
void myserver::connect() {
  nl_error(0, "%s: In connect()", iname);
  Server::connect();
  if (socket_state == Socket::Socket_listening) {
    TO.Set(1, 0);
  } else {
    nl_error(1, "%s: Timeout not initiated. socket_state = %d",
      iname, socket_state);
  }
  flags |= Fl_Timeout;
}

bool myserver::protocol_timeout() {
  TMtest_def.synch();
  TO.Set(1,0);
  nl_error(0, "%s: Count: %d Stale: %d", iname, TMtest.count, TMtest_def.Stale(31));
  return false;
}

int main(int argc, char **argv) {
  SubServices Subs;
  Loop ELoop;
  Subs.add_subservice(
    new SubService(
      "DG/data/TMtest",
      (socket_clone_t)TM_data_rcvr::new_tm_data_rcvr,
      &TMtest_def
      // new TM_data_rcvr_def("TMtest", &TMtest, sizeof(TMtest))
    )
  );
  myserver S("listen", 128, "DG", Socket::Socket_Unix, &Subs);
  ELoop.add_child(&S);
  nl_error(0, "%s %s Starting", AppID.name, AppID.rev);
  S.connect();
  ELoop.event_loop();
  nl_error(0, "Terminating");
  return 0;
}
