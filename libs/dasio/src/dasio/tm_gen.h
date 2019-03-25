#ifndef TM_GEN_H_INCLUDED
#define TM_GEN_H_INCLUDED

#include "client.h"
#include "server.h"
#include "tm_queue.h"
#include "tm_gen_cmd.h"
#include "tm_gen_tmr.h"

namespace DAS_IO {

enum tm_gen_event { tmg_event_start, tmg_event_stop, tmg_event_fast, tmg_event_quit };

class tm_gen_cmd;
class tm_gen_tmr;

class tm_gen_bfr : public Client {
  public:
    tm_gen_bfr();
    ~tm_gen_bfr();
    inline bool iwritev(struct iovec *iov, int nparts, const char *where);
    inline bool obuf_empty() {
      return Interface::obuf_empty();
    }
  protected:
};

class tm_generator : public tm_queue, public Server {
  public:
    tm_generator(int nQrows, int low_water);
    virtual ~tm_generator();
    void init( int collection );
    int execute(const char *cmd);
    virtual void event(enum tm_gen_event evt);
    virtual void service_row_timer() = 0;
    static tm_generator *TM_server;
  protected:
    bool quit; // non-zero means we are terminating
    bool started; // True while running
    bool regulated; // True whenever data flow is time-based
    bool autostart;
    bool regulation_optional;

    // virtual void single_step() = 0;
    void transmit_data( int single_row );
    tm_gen_bfr *bfr;
    tm_gen_tmr *tmr;
  private:
    void tm_start(int lock_needed = 1);
    void tm_play(int lock_needed = 1);
    void tm_stop();
    uint64_t row_period_nsec_default;
    uint64_t row_period_nsec_current;
};

#define SETIOV(x,y,z) ((x)->iov_base = y, (x)->iov_len = z)
}

#endif
