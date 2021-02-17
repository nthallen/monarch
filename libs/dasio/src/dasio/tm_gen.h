#ifndef TM_GEN_H_INCLUDED
#define TM_GEN_H_INCLUDED

#include <sys/uio.h>
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
    /**
     * @param collection If true, uses non-blocking connection to tm_bfr.
     */
    tm_gen_bfr(bool collection);
    inline bool iwritev(struct iovec *iov, int nparts, const char *where);
  protected:
    bool process_eof();
    bool connect_failed();
    bool app_connected();
    bool iwritten(int nb);
  private:
    struct iovec bfr_iov[2];
    /** true if the last write was not completed */
    bool buffering;
};

class tm_generator : public tm_queue, public Server {
  friend class tm_gen_bfr;
  public:
    tm_generator();
    virtual ~tm_generator();
    /**
     * @param nQrows The number of rows in the tm_queue
     * @param collection If true, uses non-blocking connection to tm_bfr.
     * @param obufsize Size of tm_gen_bfr's output buffer, if any
     */
    void init(int nQrows, bool collection, int obufsize = 0);
    bool execute(const char *cmd);
    virtual void event(enum tm_gen_event evt);
    virtual void service_row_timer() = 0;
    static tm_generator *TM_server;
  protected:
    bool quit; //< non-zero means we are terminating
    bool started; //< True while running
    bool regulated; //< True whenever data flow is time-based
    bool autostart; //< autostart is implemented in rdr
    bool regulation_optional; //< True when not regulating is OK
    /**
     * Called when the tm_gen_bfr Interface switches between
     * buffered and unbuffered modes. The buffered mode indicates
     * that the source is generating data faster than the bfr can
     * process it, so the caller will need to consider some sort
     * of throttling scheme.
     * @param bfring true if tm_gen_bfr is now in buffering mode
     */
    virtual void buffering(bool bfring);

    void transmit_data(bool single_row);
    tmq_tstamp_ref *cur_tsp;
    tm_gen_bfr *bfr;
    tm_gen_tmr *tmr;
  private:
    void tm_start(int lock_needed = 1);
    void tm_play(int lock_needed = 1);
    void tm_stop();
    uint64_t row_period_nsec_default;
    uint64_t row_period_nsec_current;
    struct iovec pvt_iov[3];
};

#define SETIOV(x,y,z) ((x)->iov_base = y, (x)->iov_len = z)
}

#endif
