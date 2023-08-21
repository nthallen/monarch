/** @file client.cc */
#include <stdio.h>
#include <stdlib.h>
#include "dasio/client.h"
#include "dasio/appid.h"
#include "nl.h"

namespace DAS_IO {

  Client::Client(const char *iname, int bufsz,
        const char *hostname, const char *service,
        const char *sub_service) :
    DAS_IO::Socket(iname, bufsz, hostname, service),
    sub_service(sub_service),
    cross_exp(0)
  {
    clt_state = Clt_connecting;
  }

  Client::Client(const char *iname, const char *function,
                 const char *service, const char *sub_service,
                 int bufsz)
    : DAS_IO::Socket(iname, function, service, bufsz),
      sub_service(sub_service),
      cross_exp(0)
  {
    clt_state = Clt_connecting;
  }

  bool Client::protocol_input() {
    if (is_negotiated()) return app_input();
    if (not_str("OK\n")) {
      if (cp < nc) {
        report_err("%s: Unexpected response in negotiation", iname);
        consume(nc);
        close();
        return app_negotiation_failed();
      }
      return false;
    }
    clt_state = Clt_negotiated;
    report_ok(nc);
    return app_connected();
  }

  bool Client::process_eof() {
    if (clt_state == Clt_negotiation_failed) {
      clt_state = Clt_connecting;
      return app_negotiation_failed();
    } else return app_process_eof();
  }

  bool Client::app_negotiation_failed() {
    msg(MSG_ERROR, "%s: Negotiation failed", iname);
    return reset();
  }

  bool Client::app_process_eof() {
    return true;
  }

  void Client::close() {
    DAS_IO::Socket::close();
    clt_state = is_negotiated() ? Clt_connecting :
      Clt_negotiation_failed;
  }

  bool Client::connected() {
    // Issue the negotiation string
    int req_len;
    const char *Exp = cross_exp ? cross_exp : AppID.Experiment;
    if (sub_service && sub_service[0]) {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s %s/%s\n", Exp,
        AppID.name, service, sub_service);
    } else {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s %s\n", Exp,
        AppID.name, service);
    }
    if (iwrite(obuf, req_len)) return true;
    clt_state = Clt_negotiating;
    return false;
  }

  bool Client::app_input() { return false; }
  bool Client::app_connected() {
    if (conn_fail_reported) {
      msg(0, "%s: Connected", iname);
      conn_fail_reported = false;
    }
    return false;
  }

}
