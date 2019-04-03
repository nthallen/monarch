/**
 * tm_gen_tmr Object definitions
 */
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include "dasio/tm.h"
#include "dasio/tm_gen_cmd.h"
#include "dasio/tm_gen_tmr.h"
#include "nl.h"

namespace DAS_IO {

tm_gen_tmr::tm_gen_tmr(tm_generator *tm_gen)
    : Interface("tmr", 8), tmg(tm_gen) {
  struct timespec ts;
  if (clock_getres(CLOCK_REALTIME, &ts))
    msg(MSG_EXIT_ABNORM, "Error from clock_getres()");
  timer_resolution_nsec =
    ts.tv_sec * (uint64_t)1000000000L + ts.tv_nsec;
  fd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
  if (fd < 0) {
    msg(MSG_FATAL, "timerfd_create returned error %d: %s",
      errno, strerror(errno));
  }
  flags = 0;
  tmg->ELoop.add_child(this);
}

tm_gen_tmr::~tm_gen_tmr() {
  msg( 0, "Destructing tm_gen_tmr object" );
}

bool tm_gen_tmr::protocol_input() {
  // could look at buf and make sure only
  // one timer expiration has occurred.
  report_ok(nc);
  tmg->service_row_timer();
  return 0;
}

// int tm_gen_tmr::ready_to_quit() {
  // if ( timerid != -1 ) {
    // if ( pulse_detach(dg->dispatch->dpp, pulse_code, 0) == -1 ) {
      // msg(MSG_ERROR, "pulse_detach returned -1" );
    // }
    // if ( timer_delete(timerid) == -1 ) {
      // msg(MSG_ERROR, "timer_delete returned errno %d", errno );
    // }
    // timerid = -1;
  // }
  // return 1;
// }

void tm_gen_tmr::settime( int per_sec, int per_nsec ) {
  // ### Change this to start on the second
  struct itimerspec itime;

  itime.it_value.tv_sec = itime.it_interval.tv_sec = per_sec;
  itime.it_value.tv_nsec = itime.it_interval.tv_nsec = per_nsec;
  timerfd_settime(fd, 0, &itime, NULL);
  flags = (per_sec || per_nsec) ? Fl_Read : 0;
}

void tm_gen_tmr::settime( uint64_t per_nsec ) {
  // ### Change this to start on the second
  struct itimerspec itime;
  itime.it_value.tv_sec = per_nsec / (uint64_t)1000000000;
  itime.it_value.tv_nsec = per_nsec % (uint64_t)1000000000;
  // nsec2timespec( &itime.it_value, per_nsec );
  itime.it_interval = itime.it_value;
  timerfd_settime(fd, 0, &itime, NULL);
  flags = per_nsec ? Fl_Read : 0;
}

}
