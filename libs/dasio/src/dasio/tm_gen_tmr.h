#ifndef TM_GEN_TMR_H
#define TM_GEN_TMR_H

#include <time.h>
#include <stdint.h>
#include "nl.h"
#include "tm_gen.h"
#include "interface.h"

namespace DAS_IO {
class tm_generator;

class tm_gen_tmr : public Interface {
  public:
    tm_gen_tmr(tm_generator *tm_gen);
    // void attach();
    void settime( int per_sec, int per_nsec );
    void settime( uint64_t nsecs );
    tm_generator *tmg;
    uint64_t timer_resolution_nsec;
    uint64_t n_expirations;
    // uint64_t padding; // To prevent fillbuf from overwriting the buffer
  protected:
    virtual ~tm_gen_tmr();
    bool protocol_input();
};

}

#endif

