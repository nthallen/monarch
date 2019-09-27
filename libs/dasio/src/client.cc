/** @file client.cc */
#include <stdio.h>
#include <stdlib.h>
#include "dasio/client.h"
#include "dasio/appid.h"

namespace DAS_IO {

  Client::Client(const char *iname, int bufsz, const char *hostname, const char *service, const char *sub_service) : DAS_IO::Socket(iname, bufsz, hostname, service), sub_service(sub_service) {
    clt_state = Clt_connecting;
  }

  //Client::Client(const char *iname, int bufsz, const char *service,
  //      const char *sub_service)
  //  : DAS_IO::Socket(iname, bufsz, service), sub_service(sub_service) {
  //  clt_state = Clt_connecting;
  //}
  
  // Client::~Client() {}
  
  bool Client::protocol_input() {
    if (is_negotiated()) return app_input();
    if (not_str("OK\n")) {
      report_err("%s: Negotiation failed", iname);
      consume(nc);
      return true;
    }
    clt_state = Clt_negotiated;
    report_ok(nc);
    return app_connected();
  }
  
  void Client::close() {
    DAS_IO::Socket::close();
    clt_state = Clt_connecting;
  }
  
  bool Client::connected() {
    // Issue the negotiation string
    int req_len;
    const char *Exp = AppID.Experiment;
    if (sub_service && sub_service[0]) {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s %s/%s\n", Exp,
        AppID.name, service, sub_service);
    } else {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s %s\n", Exp,
        AppID.name, service);
    }
    if (iwrite(obuf, req_len)) return true; // don't write the terminating NUL, duh
    clt_state = Clt_negotiating;
    return false;
  }

  bool Client::app_input() { return false; }
  bool Client::app_connected() { return false; }
  
}
