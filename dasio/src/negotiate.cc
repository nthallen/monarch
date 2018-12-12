/** @file negotiate.cc */
#include <stdio.h>
#include <stdlib.h>
#include "negotiate.h"

namespace DAS_IO {

  Socket::Negotiate::Negotiate(const char *iname, int bufsz, const char *service,
        const char *sub_service)
    : DAS_IO::Socket(iname, bufsz, service), sub_service(sub_service) {
    neg_state = Neg_connecting;
  }
  
  Socket::Negotiate::~Negotiate() {}
  
  bool Socket::Negotiate::ProcessData(int flag) {
    switch (socket_state) {
      case Neg_connecting:
      case Neg_negotiated:
        return DAS_IO::Socket::ProcessData(flag);
      case Neg_negotiating:
        if (fillbuf()) return true;
        cp = 0;
        if (not_str("OK\n")) {
          report_err("%s: Negotiation failed", iname);
          consume(nc);
          return true;
        }
        neg_state = Neg_negotiated;
        report_ok(nc);
        return false;
    }
  }
  
  void Socket::Negotiate::close() {
    DAS_IO::Socket::close();
    neg_state = Neg_connecting;
  }
  
  bool Socket::Negotiate::connected() {
    // Issue the negotiation string
    int req_len;
    const char *Exp = getenv("Experiment");
    if (Exp == 0) {
      Exp = "none";
    }
    if (sub_service && sub_service[0]) {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s/%s\n", Exp, service,
        sub_service);
    } else {
      req_len = snprintf(obuf, obufsize, "AuthLE %s %s\n", Exp, service);
    }
    if (iwrite(obuf, req_len)) return true; // don't write the terminating NUL, duh
    neg_state = Neg_negotiating;
    return false;
  }
  
}
