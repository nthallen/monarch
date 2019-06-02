/** \file rdr.cc
 * \brief Reads TM log files and writes to TMbfr
 */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "rdr.h"
#include "nl.h"
#include "oui.h"
#include "nl_assert.h"
#include "dasio/tm_gen.h"
#include "dasio/appid.h"

#define RDR_BUFSIZE 16384

using namespace DAS_IO;

DAS_IO::AppID_t DAS_IO::AppID("rdr", "Telemetry Reader", "V2.0");

static const char *opt_basepath = ".";
static int opt_autostart;
static int opt_regulate;
static int opt_kluge_a;
static int opt_autoquit;
static unsigned long opt_start_file = 1;
static unsigned long opt_end_file = ULONG_MAX;

//  opt_basepath = "/home/tilde/raw/flight/080908.4";

/** Options we need to support:

        -A : autostart without regulation
        -a : autostart with regulation
        -F index : Starting log file index
        -L index : Ending log file index 
        -T time : Starting time/Ending time
        -P path : path to log directories
        -k : invoke kluge to work around lgr bug
        -q : autoquit

 */

rdr_mlf::rdr_mlf(const char *path)
      : DAS_IO::Interface("rdr", 4096*3),
        rdr_ptr(0) {
  set_binary_mode();
  char mlf_base[PATH_MAX];
  snprintf(mlf_base, PATH_MAX, "%s/LOG", path );
  mlf = mlf_init( 3, 60, 0, mlf_base, "dat", NULL );
  mlf_set_index( mlf, opt_start_file );
  flags = 0;
}

bool rdr_mlf::protocol_input() {
  rdr_ptr->process_message();
  return false;
}

// Return non-zero where there is nothing else to read
// This is absolutely a first cut. It will stop at the first sign of trouble (i.e. a missing file)
// What I will want is a record of first file and last file and/or first time/last time
bool rdr_mlf::process_eof() {
  if ( fd != -1 ) {
    ::close(fd);
    fd = -1;
  }
  if (mlf->index < opt_end_file ) {
    int nlrl = set_response(0);
    fd = mlf_next_fd( mlf );
    set_response(nlrl);
  }
  // need to alter, as tm_client::bfr_fd isn't being used anymore
  if ( fd == -1 ) {
    if ( opt_autoquit ) {
      rdr_ptr->Shutdown(false);
      return true;
    }
    flags = 0;
  }
  return false;
}

bool Reader::ready_to_quit() {
  // check the tm_queue. If it is empty return true
  if (first_tmqr == 0 ||
      (first_tmqr == last_tmqr && first_tmqr->n_Qrows == 0)) {
    return true;
  }
  return false;
}

void rdr_init( int argc, char **argv ) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'A':
        opt_autostart = 1;
        opt_regulate = 0;
        break;
      case 'a':
        opt_autostart = 1;
        opt_regulate = 1;
        break;
      case 'P':
        opt_basepath = optarg;
        break;
      case 'k':
        opt_kluge_a = 1;
        break;
      case 'q':
        opt_autoquit = 1;
        break;
      case 'F':
        opt_start_file = strtoul(optarg, NULL, 10);
        break;
      case 'L':
        opt_end_file = strtoul(optarg, NULL, 10);
        break;
      case '?':
        msg(MSG_FATAL, "Unrecognized Option -%c", optopt);
    }
  }
}

int main( int argc, char **argv ) {
  oui_init_options( argc, argv );
  msg(0, "Startup");
  load_tmdac(opt_basepath);
  int nQrows = RDR_BUFSIZE/tmi(nbrow);
  if (nQrows < 2) nQrows = 2;
  rdr_mlf *mlf = new rdr_mlf(opt_basepath);
  Reader *rdr = new Reader(nQrows, nQrows/2, RDR_BUFSIZE, mlf);
  
  /* Added arguments: low_water=0, collection=false */
  rdr->init(nQrows, 0, false);
  rdr->Start(Server::Srv_Unix);
  msg(0, "Shutdown");
}

Reader::Reader(int nQrows, int low_water, int bufsize, rdr_mlf *mlf) :
    tm_rcvr(mlf) {
  // it_blocked = 0;
  // ot_blocked = 0;
  // if ( sem_init( &it_sem, 0, 0) || sem_init( &ot_sem, 0, 0 ) )
    // msg( MSG_FATAL, "Semaphore initialization failed" );
  int rv = pthread_mutex_init( &tmq_mutex, NULL );
  if ( rv )
    msg( MSG_FATAL, "Mutex initialization failed: %s",
            strerror(errno));
  init_tm_type();
  nl_assert(input_tm_type == TMTYPE_DATA_T3);
  regulated = opt_regulate;
  autostart = opt_autostart;
  locked_by_file = 0;
  locked_by_line = 0;
  mlf->set_reader(this);
  mlf->reference();
  if (mlf->process_eof()) {
    msg( MSG_FATAL, "No input data found." );
  }
  ELoop.add_child(mlf);
}

/* static void pt_create( void *(*func)(void *), pthread_t *thread, void *arg ) {
  int rv = pthread_create( thread, NULL, func, arg );
  if ( rv != 0 )
    msg(MSG_FATAL,"pthread_create failed: %s", strerror(errno));
} */

/* static void pt_join( pthread_t thread, const char *which ) {
  void *value;
  int rv = pthread_join(thread, &value);
  if ( rv != 0 )
    msg( MSG_ERROR, "pthread_join(%d, %s) returned %d: %s",
       thread, which, rv, strerror(rv) );
  else if ( value != 0 )
    msg( MSG_ERROR, "pthread_join(%s) returned non-zero value", which );
  else msg( MSG_DEBUG, "%s shutdown", which );
} */

// void Reader::control_loop() {
  // pthread_t ot, it;
  // if ( opt_autoquit ) {
    // //RQP = new Rdr_quit_pulse(this);
    // //RQP->attach();
  // }
  // pt_create( ::output_thread, &ot, this );
  // pt_create( ::input_thread, &it, this );
  // //must be replaced
  // //tm_generator::operate();
  // Start(Srv_Unix);
  // pt_join( it, "input_thread" );
  // pt_join( ot, "output_thread" );
// }

void Reader::lock(const char *by, int line) {
  int rv = pthread_mutex_lock(&tmq_mutex);
  if (rv)
    msg( MSG_FATAL, "Mutex lock failed: %s",
            strerror(rv));
  locked_by_file = by;
  locked_by_line = line;
}

void Reader::unlock() {
  int rv = pthread_mutex_unlock(&tmq_mutex);
  if (rv)
    msg( MSG_FATAL, "Mutex unlock failed: %s",
            strerror(rv));
}

void Reader::service_row_timer() {
  if (regulated) transmit_data(true);
}

void Reader::event(enum tm_gen_event evt) {
  lock(__FILE__,__LINE__);
  switch (evt) {
    case tmg_event_start:
      mlf->flags = Interface::Fl_Read;
      if (mlf->fd == -1) mlf->process_eof();
      break;
    case tmg_event_stop:
      mlf->flags = 0;
      break;
    case tmg_event_quit:
      msg( 0, "Quit event" );
      tmr->settime(0);
      lock(__FILE__,__LINE__);
      started = false;
      quit = true;
      unlock();
      Shutdown(false);
      break;
    case tmg_event_fast:
      break;
    default:
      break;
  }
  unlock();
}

// void *input_thread(void *Reader_ptr ) {
  // Reader *DGr = (Reader *)Reader_ptr;
  // return DGr->input_thread();
// }

// void *Reader::input_thread() {
  // //commented out for compilation
  // //while (!tm_quit)
  // //  read();
  // return NULL;
// }

// void *output_thread(void *Reader_ptr ) {
  // Reader *DGr = (Reader *)Reader_ptr;
  // return DGr->output_thread();
// }

// void *Reader::output_thread() {
  // for (;;) {
    // lock(__FILE__,__LINE__);
    // //commented out for compilation
    // if ( quit /* || tm_quit */ ) {
      // unlock();
      // break;
    // }
    // if ( ! started ) {
      // ot_blocked = OT_BLOCKED_STOPPED;
      // unlock();
      // sem_wait(&ot_sem);
    // } else {
      // if ( regulated ) {
        // // timed loop
        // for (;;) {
          // int nr;
          // ot_blocked = OT_BLOCKED_TIME;
          // unlock();
          // sem_wait(&ot_sem);
          // lock(__FILE__,__LINE__);
          // //commented out for compilation
          // int breakout = !started || !regulated /* || tm_quit */;
          // unlock();
          // if (breakout) break;
          // transmit_data(1); // only one row
          // nr = allocate_rows(NULL);
          // // if (allocate_rows(NULL) >= tmq_low_water) {
          // // The problem with this is that when the
          // // queue is wrapping, the largest contiguous
          // // block does not change.
          // if ( (nr >= tmq_low_water) ||
               // (nr > 0 && first <= last) ) {
            // lock(__FILE__,__LINE__);
            // if ( it_blocked == IT_BLOCKED_DATA ) {
              // it_blocked = 0;
              // sem_post(&it_sem);
            // }
            // unlock();
          // }
          // lock(__FILE__,__LINE__); /* needed in the inner loop */
        // }
      // } else {
        // // untimed loop
        // for (;;) {
          // //commented out for compilation
          // int breakout = !started /* || tm_quit */ || regulated;
          // if ( it_blocked == IT_BLOCKED_DATA ) {
            // it_blocked = 0;
            // sem_post(&it_sem);
          // }
          // unlock();
          // if (breakout) break;
          // transmit_data(0);
          // lock(__FILE__,__LINE__);
        // }
      // }
    // }
  // }
  // // signal parent thread that we are quitting
  // return NULL;
// }

void Reader::process_tstamp() {
  if ( tm_info.t_stmp.mfc_num == tm_msg->body.ts.mfc_num &&
       tm_info.t_stmp.secs == tm_msg->body.ts.secs )
    return; // redundant tstamp (beginning of each new file)
  tm_info.t_stmp = tm_msg->body.ts;
  have_tstamp = true;
  commit_tstamp( tm_info.t_stmp.mfc_num, tm_info.t_stmp.secs );
}

/**
 \brief Handles incoming data records
 
 Currently, lgr can only write out data in T3 format, so
 rdr here assumes the incoming data is T3 format. This is
 checked by an assertion in Reader::Reader().
 */
void Reader::process_data() {
  static int nrows_full_rec = 0;
  static int last_rec_full = 1;
  static unsigned short frac_MFCtr;

  if ( ! have_tstamp ) {
    msg(MSG_WARN, "process_data() without initialization" );
    return;
  }
  tm_data_t3_t *data = &tm_msg->body.data3;
  unsigned char *raw = &data->data[0];
  int n_rows = data->n_rows;
  unsigned short MFCtr = data->mfctr;
  // This is a work-around for a lgr bug which generated
  // corrupted log files.
  if ( opt_kluge_a ) {
    if ( nrows_full_rec == 0 )
      nrows_full_rec = n_rows;
    if ( n_rows == nrows_full_rec ) {
      last_rec_full = 1;
    } else {
      if ( n_rows * 2 < nrows_full_rec ||
          ((!last_rec_full) && n_rows*2 == nrows_full_rec )) {
        // We won't use this record, but we might record
        // the MFCtr
        if ( last_rec_full ) frac_MFCtr = MFCtr;
        last_rec_full = 0;
        return;
      } else {
        // We'll use this record, but may need to get
        // MFCtr from the previous fragment
        if ( !last_rec_full ) MFCtr = frac_MFCtr;
        last_rec_full = 0;
      }
    }
  }

  // Can check here for time limits
  // Given MFCtr, timestamp, we can calculate the time. We can
  // simply skip the commit_rows() call until the start time
  // is reached, and we could trigger termination if the end
  // time is reached.
  while ( n_rows ) {
    unsigned char *dest;
    lock(__FILE__,__LINE__);
    //commented out for compilation
    //if ( tm_quit ) {
    //  unlock();
    //  return;
    //}
    int n_room = allocate_rows(&dest);
    if ( n_room ) {
      unlock();
      if ( n_room > n_rows ) n_room = n_rows;
      int rawsize = n_room*tm_rcvr::nbQrow;
      memcpy( dest, raw, rawsize );
      commit_rows( MFCtr, 0, n_room );
      raw += rawsize;
      n_rows -= n_room;
      MFCtr += n_room;
    } else {
      // it_blocked = IT_BLOCKED_DATA;
      unlock();
      // sem_wait(&it_sem);
    }
    if (!regulated) transmit_data(false);
  }
}

// const char *Reader::context() {
  // static char buf[80];
  // if (mlf->fd == -1) return "";
  // snprintf(buf, 80, "%s: ", mlf->fpath);
  // return &buf[0];
// }

void tminitfunc() {}
