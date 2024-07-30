#ifndef SB_DRIVER_H_INCLUDED
#define SB_DRIVER_H_INCLUDED

#include "subbuspp.h"

class SB_driver : public subbuspp {
  public:
    SB_driver(const char *service, const char *subservice);
    void init();
    virtual void setup();
  protected:
    bool loaded;
};

#endif
