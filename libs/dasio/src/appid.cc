/** @file appid.cc */
#include <stdlib.h>
#include "dasio/appid.h"
#include "nl.h"

namespace DAS_IO {
  
  AppID_t::AppID_t(const char *name, const char *fullname, const char *rev)
      : name(name), fullname(fullname), rev(rev) {
    Experiment = getenv("Experiment");
    if (Experiment == 0) {
      Experiment = "none";
    }
  }

  AppID_t::~AppID_t() {}

  void AppID_t::report_startup() {
    msg(0, "%s %s Starting", DAS_IO::AppID.fullname, DAS_IO::AppID.rev);
  }

  void AppID_t::report_shutdown() {
    msg(0, "Terminating");
  }
}
