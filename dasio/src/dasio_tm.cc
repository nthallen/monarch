/** @file dasio_tm.cc */
#include "dasio/client.h"

namespace DAS_IO {
  
TM::TM(const char *iname, const char *datum, const char *data,
        uint16_t size)
    : Client(iname, 10, "DG", 0),
      data(data), data_len(size) {
  snprintf(sub_service, subsvc_len, "data/%s", datum);
  set_subservice(sub_service);
}

// TM::TM(const char *iname, const char *hostname, const char *datum,
        // const char *data, uint16_t size) {
  // snprintf(sub_service, subsvc_len, "data/%s", datum);
  // Client(iname, 10, hostname, "DG", sub_service);
// }

TM::~TM() {}

bool TM::app_input() {
  report_ok(nc);
  if (iwrite(data, data_len)) return true;
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

bool TM::app_connected() {
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

}
