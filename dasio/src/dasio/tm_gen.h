#ifndef TM_GEN_H_INCLUDED
#define TM_GEN_H_INCLUDED

#include "tm_queue.h"
#include "tm_gen_client.h"
#include "tm_gen_cmd.h"
#include "tm_gen_tmr.h"

enum tm_gen_event { tm_gen_event_start, tm_gen_event_stop, tm_gen_event_fast, tm_gen_event_quit };

class tm_gen_cmd;
class tm_gen_tmr;

class tm_generator : public DAS_IO::tm_queue {
  public:
    tm_generator(int nQrows, int low_water);
    virtual ~tm_generator();
    void init( int collection );
    //void operate(); // event loop
    int execute(const char *cmd);
    virtual void event(enum tm_gen_event evt);
    //tm_gen_dispatch *dispatch;
    virtual void service_row_timer() = 0;
  protected:
    bool quit; // non-zero means we are terminating
    bool started; // True while running
    bool regulated; // True whenever data flow is time-based
    bool autostart;
    bool regulation_optional;

    // virtual void single_step() = 0;
    void transmit_data( int single_row );
    int tm_gen_bfr_fd;
    tm_gen_cmd *cmd;
    tm_gen_tmr *tmr;
  private:
    void tm_start(int lock_needed = 1);
    void tm_play(int lock_needed = 1);
    void tm_stop();
    uint64_t row_period_nsec_default;
    uint64_t row_period_nsec_current;
    void check_writev( int rc, int wr_size, const char *where );
};

#endif
