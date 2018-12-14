/** @file appid.cc */
#include <stdlib.h>
#include "dasio/appid.h"

namespace DAS_IO {
  
  AppID_t::AppID_t(const char *name, const char *fullname, const char *rev)
      : name(name), fullname(fullname), rev(rev) {
    Experiment = getenv("Experiment");
    if (Experiment == 0) {
      Experiment = "none";
    }
  }

  AppID_t::~AppID_t() {}
  
}