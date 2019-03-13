/**
 * tm_gen_tmr Object definitions
 */
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/neutrino.h> //QNX
#include <sys/netmgr.h> //QNX
#include <sys/iomsg.h> //QNX
#include "dasio/tm.h"
#include "dasio/tm_gen_Resmgr.h"
#include "dasio/tm_gen_cmd.h"
#include "dasio/tm_gen_tmr.h"

int tm_gen_tmr_pulse_func( message_context_t *ctp, int code,
        unsigned flags, void *handle ) {
  tm_gen_tmr *tmr = (tm_gen_tmr *)handle;
  tmr->dg->service_row_timer();
  return 0;
}

tm_gen_tmr::tm_gen_tmr(tm_generator *tm_gen) : tm_gen_dispatch_client() {
  timerid = -1;
  dg = tm_gen;
  struct timespec ts;
  if (clock_getres(CLOCK_REALTIME, &ts))
    nl_error(4, "Error from clock_getres()");
  timer_resolution_nsec = timespec2nsec(&ts);
}

void tm_gen_tmr::attach() {
  struct sigevent tmr_ev;
  int rc;

  pulse_code =
    pulse_attach( dg->dispatch->dpp, MSG_FLAG_ALLOC_PULSE, 0, tm_gen_tmr_pulse_func, this );
  if ( pulse_code < 0 )
    nl_error(3, "Error %d from pulse_attach", errno );
  int coid = message_connect( dg->dispatch->dpp, MSG_FLAG_SIDE_CHANNEL );
  if ( coid == -1 )
    nl_error(3, "Error %d from message_connect", errno );
  tmr_ev.sigev_notify = SIGEV_PULSE;
  tmr_ev.sigev_coid = coid;
  tmr_ev.sigev_priority = getprio(0);
  tmr_ev.sigev_code = pulse_code;
  rc = timer_create( CLOCK_REALTIME, &tmr_ev, &timerid );
  if ( rc < 0 ) nl_error( 3, "Error creating timer" );
  tm_gen_dispatch_client::attach(dg->dispatch);
}

int tm_gen_tmr::ready_to_quit() {
  if ( timerid != -1 ) {
    if ( pulse_detach(dg->dispatch->dpp, pulse_code, 0) == -1 ) {
      nl_error( 2, "pulse_detach returned -1" );
    }
    if ( timer_delete(timerid) == -1 ) {
      nl_error( 2, "timer_delete returned errno %d", errno );
    }
    timerid = -1;
  }
  return 1;
}

tm_gen_tmr::~tm_gen_tmr() {
  nl_error( 0, "Destructing tm_gen_tmr object" );
}

void tm_gen_tmr::settime( int per_sec, int per_nsec ) {
  struct itimerspec itime;

  itime.it_value.tv_sec = itime.it_interval.tv_sec = per_sec;
  itime.it_value.tv_nsec = itime.it_interval.tv_nsec = per_nsec;
  timer_settime(timerid, 0, &itime, NULL);
}

void tm_gen_tmr::settime( uint64_t per_nsec ) {
  struct itimerspec itime;
  nsec2timespec( &itime.it_value, per_nsec );
  itime.it_interval = itime.it_value;
  timer_settime(timerid, 0, &itime, NULL);
}
