#ifndef RDR_H_INCLUDED
#define RDR_H_INCLUDED

#include <pthread.h>
#include <semaphore.h>
#include "mlf.h"

#ifdef __cplusplus
#include "dasio/tm_gen_col.h"
#include "dasio/tm_client.h"
#include "dasio/tm_gen.h"

using namespace DAS_IO;

//class Rdr_quit_pulse;
class Reader;

class rdr_mlf : public Interface {
  public:
    rdr_mlf(const char *path);
    inline void set_reader(Reader *rdr) { rdr_ptr = rdr; }
    bool process_eof();
  protected:
    bool protocol_input();
    Reader* rdr_ptr;
    mlf_def_t *mlf;
};

class Reader : public tm_generator, public tm_rcvr {
  friend class rdr_mlf;
  public:
    Reader(int nQrows, int low_water, int bufsize, rdr_mlf *mlf);
    void event(enum tm_gen_event evt);
    void service_row_timer();
    /** Handles autostart and then calls Start(Srv_Unix) */
    void start();
    // void *input_thread();
    // void *output_thread();
    // void control_loop();
  protected:
    void process_tstamp();
    void process_data();
    inline void process_message() { tm_rcvr::process_message(); }
    void lock(const char *by = 0, int line = -1);
    void unlock();
    // const char *context();
    // int it_blocked;
    // sem_t it_sem;
    // int ot_blocked;
    // sem_t ot_sem;
    pthread_mutex_t tmq_mutex;
    bool have_tstamp;
    bool ready_to_quit();
  private:
    //Rdr_quit_pulse *RQP;
    const char *locked_by_file;
    int locked_by_line;
    rdr_mlf* mlf;
};

/* class Rdr_quit_pulse : public tmg_dispatch_client {
  public:
    Rdr_quit_pulse(Reader *rdr_ptr);
    ~Rdr_quit_pulse();
    void pulse();
    void attach();
    int ready_to_quit();
    Reader *rdr;
  private:
    int pulse_code;
    int coid;
}; */

extern "C" {
#endif

  // void *input_thread(void *Reader_ptr);
  // void *output_thread(void *Reader_ptr);
  void rdr_init( int argc, char **argv );

#ifdef __cplusplus
};
#endif

// #define OT_BLOCKED_STOPPED 1
// #define OT_BLOCKED_TIME 2
// #define OT_BLOCKED_DATA 3
// #define IT_BLOCKED_DATA 1
// #define IT_BLOCKED_EOF 2

#endif
