#ifndef TM_GEN_TMR_H
#define TM_GEN_TMR_H

#include <time.h>
#include <stdint.h>
#include "nl.h"
#include "tm_gen.h"
#include "tm_tmr.h"
#include "interface.h"

namespace DAS_IO {
class tm_generator;

class tm_gen_tmr : public tm_tmr {
  public:
    tm_gen_tmr(tm_generator *tm_gen);
    tm_generator *tmg;
  protected:
    bool protocol_input();
};

}

#endif

