#ifndef TM_GEN_TMR_H
#define TM_GEN_TMR_H

#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <time.h>
#include <stdint.h>
#include "tm_gen_Resmgr.h"
#include "nl.h"
#include "tm_gen.h"

class tm_generator;

class tm_gen_tmr : public tm_gen_dispatch_client {
  public:
    tm_gen_tmr(tm_generator *tm_gen);
    ~tm_gen_tmr();
    void attach();
    void settime( int per_sec, int per_nsec );
    void settime( uint64_t nsecs );
    int ready_to_quit();
    tm_generator *tmg;
    uint64_t timer_resolution_nsec;
  private:
    int timerid; // set to -1 before initialization and after cleanup
    int pulse_code;
};

extern "C" {
    int tm_gen_tmr_pulse_func( message_context_t *ctp, int code,
        unsigned flags, void *handle );
}

#endif

