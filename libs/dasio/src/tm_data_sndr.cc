/** @file tm_data_sndr.cc */
#include "dasio/tm_data_sndr.h"
#include "dasio/loop.h"
#include "nl.h"

namespace DAS_IO {
  
TM_data_sndr::TM_data_sndr(const char *iname, const char *datum, const char *data,
        uint16_t size)
    : Client(iname, 10, "tm_gen", 0),
      data(data), data_len(size) {
  snprintf(sub_service, subsvc_len, "data/%s", datum);
  set_subservice(sub_service);
}

// TM_data_sndr::TM_data_sndr(const char *iname, const char *hostname, const char *datum,
        // const char *data, uint16_t size) {
  // snprintf(sub_service, subsvc_len, "data/%s", datum);
  // Client(iname, 10, hostname, "DG", sub_service);
// }

TM_data_sndr::~TM_data_sndr() {}

bool TM_data_sndr::app_input() {
  // msg(0, "%s: TM_data_sndr::app_input(%d)", iname, nc);
  report_ok(nc);
  if (iwrite(data, data_len)) return true;
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

bool TM_data_sndr::app_connected() {
  // msg(0, "TM_data_sndr::app_connected()");
  if (iwrite(data, data_len)) return true;
  if (ELoop) ELoop->set_gflag(0);
  return false;
}

}
