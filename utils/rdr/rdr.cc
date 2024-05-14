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
//#include "dasio/appid.h"

#define RDR_BUFSIZE 16384

using namespace DAS_IO;

static const char *opt_basepath = ".";
static int opt_autostart;
static int opt_regulate;
static int opt_kluge_a;
static int opt_autoquit;
static unsigned long opt_start_file = 1;
static unsigned long opt_end_file = 0;
static bool opt_nonblocking = false;

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

void rdr_mlf::start_event() {
  if (fd == -1) process_eof();
  update_flags();
}

bool rdr_mlf::protocol_input() {
  rdr_ptr->process_message();
  rdr_ptr->manage_queues();
  return false;
}

bool rdr_mlf::process_eof() {
  // Is this ever true? I don't think so!
  if ( fd != -1 ) {
    ::close(fd);
    fd = -1;
  }
  while (fd == -1) {
    if (opt_end_file > 0 && mlf->index >= opt_end_file)
      break;
    int nlrl = set_response(0);
    fd = mlf_next_fd( mlf );
    set_response(nlrl);
    if (fd == -1) {
      if (opt_end_file == 0) break;
      else msg(MSG_ERROR, "Unable to open %s, skipping", mlf->fpath);
    }
  }
  if ( fd == -1 ) {
    if (opt_autoquit) {
      rdr_ptr->set_autoquit(); // event(tmg_event_quit);
    }
    flags = 0;
  } else {
    update_flags();
  }
  return false;
}

/**
 * This function is complicated because the buffer is
 * used by the tm_rcvr from which the Reader class is
 * derived. rdr_mlf's own cp never gets updated.
 * @return true if the input buffer is empty.
 */
bool rdr_mlf::ibuf_empty() {
  return rdr_ptr->rcvr_cp() >= nc;
}

void rdr_mlf::update_flags() {
  flags = (fd < 0 || nc >= bufsize) ? 0 : Interface::Fl_Read;
}

Reader::Reader(int nQrows, rdr_mlf *mlf)
    : tm_generator(),
      tm_rcvr(mlf),
      mlf(mlf),
      managing_queues(false),
      tm_queue_blocked(false),
      auto_quit_requested(false) {
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

void Reader::start() {
  if (autostart) execute("TMc");
  Start(Srv_Function, "tm_gen");
  ELoop.delete_children();
  ELoop.clear_delete_queue(true);
}

void Reader::event(enum tm_gen_event evt) {
  lock(__FILE__,__LINE__);
  switch (evt) {
    case tmg_event_start:
      mlf->start_event();
      break;
    case tmg_event_stop:
      mlf->flags = 0;
      break;
    case tmg_event_quit:
      msg( 0, "Quit event" );
      auto_quit_requested = false;
      break;
    case tmg_event_fast:
      break;
    default:
      break;
  }
  unlock();
  tm_generator::event(evt);
  if (evt == tmg_event_quit) {
    Shutdown(true);
  }
}

void Reader::service_row_timer() {
  if (regulated) {
    transmit_data(true);
    manage_queues();
  }
}

void Reader::manage_queues() {
  if (managing_queues)
    return;
  managing_queues = true;
  bool progressing = false;
  do {
    progressing = false;
    if (!tm_queue_blocked && !mlf->ibuf_empty()) {
      process_message();
    }
    if (!queue_empty() && !regulated)
      transmit_data(false);
    if (tm_queue_blocked && allocate_rows(0)) {
      tm_queue_blocked = false;
      progressing = true;
    }
  } while (progressing);
  mlf->update_flags();
  managing_queues = false;
}

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
unsigned int Reader::process_data() {
  if ( ! have_tstamp ) {
    msg(MSG_WARN, "process_data() without initialization" );
  }
  // tm_data_t3_t *data = &tm_msg->body.data3;
  unsigned char *raw = data_row;
  int n_rows = rows_in_buf;
  unsigned int rows_processed = 0;
  mfc_t MFCtr = buf_mfctr;

  // Can check here for time limits
  // Given mfctr, timestamp, we can calculate the time. We can
  // simply skip the commit_rows() call until the start time
  // is reached, and we could trigger termination if the end
  // time is reached.
  while ( n_rows ) {
    unsigned char *dest;
    lock(__FILE__,__LINE__);
    int n_room = allocate_rows(&dest);
    unlock();
    if ( n_room ) {
      if ( n_room > n_rows ) n_room = n_rows;
      int rawsize = n_room * tm_rcvr::nbQrow;
      memcpy( dest, raw, rawsize );
      commit_rows( MFCtr, 0, n_room );
      raw += rawsize;
      n_rows -= n_room;
      MFCtr += n_room;
      rows_processed += n_room;
    } else {
      break;
    }
  }
  if (n_rows)
    tm_queue_blocked = true;
  return rows_processed;
}

bool Reader::ready_to_quit() {
  manage_queues();
  if (auto_quit_requested &&
      (is_buffering || !queue_empty() || ncc >= toread))
    return false;
  if (tm_generator::ready_to_quit()) {
    Interface::dereference(mlf);
    mlf = 0;
    return true;
  }
  msg(MSG, "Reader::ready_to_quit() but tm_gen is not");
  return false;
}

void Reader::tm_queue_is_empty() {
  msg(MSG_DEBUG,
    "TMQIE: neg:%s ibuf:%s fd:%d buffering:%s",
    bfr->is_negotiated() ? "yes" : "no",
    mlf->ibuf_empty() ? "empty" : "!empty",
    mlf->fd, is_buffering ? "true" : "false");
  if (!mlf->ibuf_empty()) {
    manage_queues();
  } else if (regulated && mlf->ibuf_empty() && mlf->fd < 0) {
    tmr->settime(0);
  }
}

void Reader::bfr_write_completed() {
  if (transmit_blocked && !regulated && !queue_empty()) {
    transmit_data(false);
    manage_queues();
  }
}

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

void Reader::set_autoquit() {
  // we set auto_quit_requested after event()
  // event() will clear auto_quit_requested.
  event(tmg_event_quit);
  auto_quit_requested = true;
}

void tminitfunc() {}

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
      case 'B':
        opt_nonblocking = true;
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
  Reader *rdr = new Reader(nQrows, mlf); 
  rdr->init(nQrows, opt_nonblocking, RDR_BUFSIZE);
  rdr->start();
  msg(0, "Shutdown");
}
