#include "nl.h"
#include "sb_driver.h"

SB_driver::SB_driver(const char *service, const char *subservice)
    : subbuspp(service, subservice),
      loaded(false)
{
}

void SB_driver::init()
{
  if (load()) {
    loaded = true;
    msg(MSG, "%s: connected to %s", iname, get_subbus_name());
    setup();
  }
}

void SB_driver::setup()
{
}
