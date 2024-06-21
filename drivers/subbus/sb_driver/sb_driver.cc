#include "nl.h"
#include "sb_driver.h"

SB_driver::SB_driver(const char *service, const char *subservice)
    : subbuspp(service, subservice) {
}
