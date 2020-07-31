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
    Reader(int nQrows, rdr_mlf *mlf);
    /** Handles autostart and then calls Start(Srv_Unix) */
    void start();
    void event(enum tm_gen_event evt);
    void service_row_timer();
    inline bool get_buffering() { return is_buffering; }
  protected:
    void process_tstamp();
    unsigned int process_data();
    inline void process_message() { tm_rcvr::process_message(); }
    bool ready_to_quit();
    void lock(const char *by = 0, int line = -1);
    void unlock();
    void buffering(bool bfring);
    pthread_mutex_t tmq_mutex;
    bool have_tstamp;
  private:
    //Rdr_quit_pulse *RQP;
    const char *locked_by_file;
    int locked_by_line;
    rdr_mlf* mlf;
    bool is_buffering;
};

extern "C" {
#endif

  void rdr_init( int argc, char **argv );

#ifdef __cplusplus
};
#endif

#endif
