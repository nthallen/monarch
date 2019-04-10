/** @file template_client.cc
 * @brief Template for a simple client
 *
 * Replace boerf with a suitable name.
 */
#include "dasio/appid.h"
#include "dasio/client.h"
#include "dasio/msg.h"
#include "oui.h"

using namespace DAS_IO;

AppID_t DAS_IO::AppID("boerfc", "boerf client", "V1.0");

class boerf_client : public Client {
  public:
    boerf_client(const char *iname = "boerfc");
    // Specify the buffer size:
    static const int boerf_client_ibufsize = 80;
    // Override any relevant methods:
    bool app_connected();
  protected:
    ~boerf_client();
  private:
    // My private data
};

boerf_client::boerf_client(const char *iname)
  : Client(iname, boerf_client_ibufsize, "boerf", "") {}

boerf_client::~boerf_client() {}

bool boerf_client::app_connected() {
  msg(0, "Client connected successfully");
  // By returning true, we should cause the client to terminate
  return true;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  boerf_client C;
  Loop ELoop;
  ELoop.add_child(&C);
  msg(0, "%s %s Starting", AppID.fullname, AppID.rev);
  C.connect();
  ELoop.event_loop();
  msg(0, "Terminating");
}
