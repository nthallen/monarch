/** @file dasio_tm.cc */
#include "dasio/tm_client.h"
#include "dasio/loop.h"
#include "nl.h"

namespace DAS_IO {
  
TM_client::TM_client(const char *iname, const char *datum, const char *data,
        uint16_t size)
    : Client(iname, 10, "DG", 0),
      data(data), data_len(size) {
  snprintf(sub_service, subsvc_len, "data/%s", datum);
  set_subservice(sub_service);
}

// TM_client::TM_client(const char *iname, const char *hostname, const char *datum,
        // const char *data, uint16_t size) {
  // snprintf(sub_service, subsvc_len, "data/%s", datum);
  // Client(iname, 10, hostname, "DG", sub_service);
// }

TM_client::~TM_client() {}

bool TM_client::app_input() {
  report_ok(nc);
  if (iwrite(data, data_len)) return true;
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

bool TM_client::app_connected() {
  nl_error(0, "TM_client::app_connected()");
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

}
