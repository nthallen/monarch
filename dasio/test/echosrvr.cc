#include "nl.h"
#include "dasio/socket.h"
#include "dasio/loop.h"
#include "dasio/appid.h"

DAS_IO::AppID_t DAS_IO::AppID("echosrvr", "A demo server", "V1.1");

class echosrvr : public DAS_IO::Socket {
  public:
    echosrvr(const char *iname, int bufsz, const char *service);
    echosrvr(const char *iname, int bufsz, const char *service,
      DAS_IO::Socket::socket_type_t);
    echosrvr(DAS_IO::Socket *orig, const char *iname, int fd);
    ~echosrvr();
    DAS_IO::Socket *new_client(const char *iname, int fd);
    bool protocol_input();
    bool connected();
};

echosrvr::echosrvr(const char *iname, int bufsz, const char *service)
    : DAS_IO::Socket(iname, bufsz, service) {
}

echosrvr::echosrvr(const char *iname, int bufsz, const char *service,
        DAS_IO::Socket::socket_type_t socket_type)
    : DAS_IO::Socket(iname, bufsz, service, socket_type) {
}

echosrvr::echosrvr(DAS_IO::Socket *orig, const char *iname, int fd)
  : DAS_IO::Socket(orig, iname, fd) {}

echosrvr::~echosrvr() {}

bool echosrvr::connected() {
  nl_error(0, "%s: connected. flags = %d", iname, flags);
  return false;
}

// DAS_IO::Socket *echosrvr::new_client(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname) {
  // nl_error(0, "%s: New client connection created. %s fd = %d", this->iname, iname, fd);
  // echosrvr *clt = new echosrvr(iname, bufsz, fd, stype, service, hostname);
  // return clt;
// }

DAS_IO::Socket *echosrvr::new_client(const char *iname, int fd) {
  Socket *rv = new echosrvr(this, iname, fd);
  if (ELoop) ELoop->add_child(rv);
  return rv;
}

bool echosrvr::protocol_input() {
  cp = 0;
  if (cp < nc) {
    switch (buf[cp]) {
      case 'E':
        nl_error(0, "Received '%s'", buf);
        iwrite((const char *)buf, nc, 1);
        report_ok(nc);
        return false;
      case 'Q':
        nl_error(0, "Received Quit command");
        report_ok(nc);
        return true;
      case 'C':
        nl_error(0, "Received Close command");
        report_ok(nc);
        close();
        ELoop->delete_child(this);
        return false;
      case 'A': // Close connection after acknowledge
        nl_error(0, "Received Acknowledge and close");
        iwrite("OK");
        report_ok(nc);
        close();
        ELoop->delete_child(this);
        return false;
      default:
        report_err("Unrecognized input:");
        consume(nc);
        return false;
    }
  }
}

const char *opt_string = "vo:mV";

int main(int argc, char **argv) {
  echosrvr server("IPCserver", 512, "cmd", DAS_IO::Socket::Socket_Unix);
  server.connect();
  DAS_IO::Loop ELoop;
  ELoop.add_child(&server);
  ELoop.event_loop();
  return 0;
}
