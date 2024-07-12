#include "subbuspp.h"

class SB_driver : public subbuspp {
  public:
    SB_driver(const char *service, const char *subservice);
    void init();
    virtual void setup();
  protected:
};
