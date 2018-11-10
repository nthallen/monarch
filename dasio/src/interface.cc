/**
 * \file interface.cc
 */
#include "dasio.h"

/**
 * I am assuming here that this level is low enough that I don't
 * need to have two separate invocations, once for deferred
 * initialization.
 * I am currently choosing to avoid providing an output buffer
 * here.
 * @param name An identifier for the interface to be used when
 * reporting statistics.
 * @param bufsz The size of the input buffer
 */
DAS_IO_Interface::DAS_IO_Interface(const char *name, int bufsz) {
  this->name = name;
  nc = cp = 0;
}

DAS_IO_Interface::~DAS_IO_Interface() {
  // clean up children
}
