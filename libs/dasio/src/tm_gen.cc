/** @file tm_gen.cc */
#include <errno.h>
#include <sys/uio.h>
#include "nl.h"
#include "nl_assert.h"
#include "dasio/tm_gen.h"
#include "dasio/msg.h"
#include "dasio/tm.h"

namespace DAS_IO {

tm_gen_bfr::tm_gen_bfr(bool collection)
  : Client("bfr", 80, "tm_bfr", collection ? "input-nb" : "input") {}

tm_gen_bfr::~tm_gen_bfr() {}

bool tm_gen_bfr::app_connected() {
  tm_hdr_t hdr = { TMHDR_WORD, TMTYPE_INIT };
  struct iovec iov[2];
  SETIOV(&iov[0], &hdr, sizeof(hdr));
  SETIOV(&iov[1], &tm_info, sizeof(tm_info));
  return iwritev( iov, 2, "Sending tm_info");
}

bool tm_gen_bfr::iwritev(struct iovec *iov, int nparts, const char *where) {
  nl_assert(is_negotiated());
  bool rv = Interface::iwritev(iov, nparts);
  if (!obuf_empty()) {
    msg(MSG_FATAL, "%s: Incomplete write %s", iname, where);
  }
  return rv;
}

tm_generator *tm_generator::TM_server;

tm_generator::tm_generator()
    : tm_queue(), Server("tm_gen") {
  bfr = 0;
  tmr = 0;
  cur_tsp = 0;
  quit = false;
  started = false;
  regulated = false;
  regulation_optional = true;
  autostart = false;
}

tm_generator::~tm_generator() {}

/**
 * Assumes tm_info is defined
 */
void tm_generator::init(int nQrows, int low_water, bool collection) {
  tm_queue::init(nQrows, low_water);
  tm_gen_cmd::attach(this); // defines the subservice
  bfr = new tm_gen_bfr(collection);
  bfr->connect();
  ELoop.add_child(bfr);
  tmr = new tm_gen_tmr(this);
  row_period_nsec_default = tmi(nsecsper)*(uint64_t)1000000000L/tmi(nrowsper);
  row_period_nsec_current = row_period_nsec_default;
}

void tm_generator::transmit_data( bool single_row ) {
  // We can read from the queue without locking
  // But we need to lock when we reference tmg_bfr_fd
  tmq_ref *tmqdr;
  // msg( 0, "transmit_data(%s)", single_row ? "single" : "all" );
  int rc;
  tm_hdrs_t hdrs;
  hdrs.s.hdr.tm_id = TMHDR_WORD;
  struct iovec iov[3];
  while ( first_tmqr ) {
    if (first_tmqr->tsp != cur_tsp) {
      cur_tsp = first_tmqr->tsp;
      hdrs.s.hdr.tm_type = TMTYPE_TSTAMP;
      SETIOV(&iov[0], &hdrs, sizeof(tm_hdr_t));
      SETIOV(&iov[1], &cur_tsp->TS, sizeof(cur_tsp->TS));
      lock(__FILE__, __LINE__);
      if ( bfr ) {
        bfr->iwritev(iov, 2, "transmitting tstamp");
      }
      unlock();
    }
    tmqdr = first_tmqr;
    if (tmqdr->n_Qrows == 0) {
      if (tmqdr->next_tmqr) retire_rows(tmqdr, 0);
      else return;
    } else {
      hdrs.s.hdr.tm_type = output_tm_type;
      int n_rows = single_row ? 1 : tmqdr->n_Qrows;
      hdrs.s.u.dhdr.n_rows = n_rows;
      hdrs.s.u.dhdr.mfctr = tmqdr->MFCtr_start;
      hdrs.s.u.dhdr.rownum = tmqdr->row_start;
      SETIOV(&iov[0], &hdrs, nbDataHdr);
      int n_iov;
      if ( tmqdr->Qrow + n_rows < total_Qrows ) {
        SETIOV(&iov[1], row[tmqdr->Qrow], n_rows * nbQrow );
        n_iov = 2;
      } else {
        int n_rows1 = total_Qrows - tmqdr->Qrow;
        SETIOV(&iov[1], row[tmqdr->Qrow], n_rows1 * nbQrow );
        int n_rows2 = n_rows - n_rows1;
        SETIOV(&iov[2], row[0], n_rows2 * nbQrow );
        n_iov = 3;
      }
      lock(__FILE__,__LINE__);
      if ( bfr ) {
        bfr->iwritev(iov, n_iov, "transmitting data");
        unlock();
      } else unlock();
      retire_rows(tmqdr, n_rows);
      if ( single_row ) return;
    }
  }
}

/**
 * Control initialization
 * This is how 
 */
/* void tm_generator::operate() {
  if ( autostart ) tm_start(1);
  dispatch->Loop();
} */

/**
  Interperet data generator commands: I need to abstract the "signal handlers" operation.
  It appears that the key notifications are:
 
      Start
      Stop
      Quit
      Change to unregulated output (fast forward)
     
      TM start: "TMc"
        Set start condition
        If regulated, program timer
        else stop timer
        if ext_stop, signal handlers
      TM end/stop "TMe"
        Set stop condition
        stop timer
        if ext_time, signal handlers
      Quit: ""
        Set stop and quit conditions
        stop timer
        if ext_stop or ext_time, signal handlers
      TM play "TM>"
        set regulated
        set row_rate to default
        if stopped, do start
        else reprogram timer
      TM fast forward "TM}"
        if regulation_optional
          stop timer
          set unregulated
          if stopped, do start
          else if ext_time, signal handlers
      TM faster/slower "TM+" "TM-"
        if regulation_optional
          if stopped
            do play
          else if regulated
            increase/decrease row_rate
            program timer
      TM single step "TMs"

      Command Summary:
        "" Quit
        "TMc" TM Start
        "TMe" TM End/Stop/Pause
        "TMs" Single Step
        "TM>" Play
        "TM+" Faster
        "TM-" Slower
        "TM}" Fast Forward
      
      Still need to add the search functions:
        TM Advance to MFCtr
        TM Advance to Time
 */
int tm_generator::execute(const char *cmd) {
  if (cmd[0] == '\0') {
    tmr->settime(0);
    lock(__FILE__,__LINE__);
    started = false;
    quit = true;
    bfr->close();
    unlock();
    msg( MSG_DEBUG, "Received Quit" );
    //dispatch->ready_to_quit();
    msg( MSG_ERROR, "Implement Server shutdown!" );
    event(tmg_event_quit);
    return 1;
  }
  if ( cmd[0] == 'T' && cmd[1] == 'M' ) {
    switch ( cmd[2] ) {
      case 'c': tm_start(1); break;
      case 'e': tm_stop(); break;
      case 's':
        lock(__FILE__,__LINE__);
        if (!started) {
          regulated = true;
          row_period_nsec_current = 0;
          tm_start(0);
        } else {
          regulated = true;
          if ( row_period_nsec_current ) {
            row_period_nsec_current = 0;
            tmr->settime(0);
          }
          unlock();
        }
        service_row_timer(); /* single_step(); */
        break;
      case '>': tm_play(); break; // play
      case '+':
        if (regulation_optional) {
          lock(__FILE__,__LINE__);
          if (!started || ( regulated && row_period_nsec_current == 0) )
            tm_play(0);
          else if ( regulated ) {
            row_period_nsec_current = row_period_nsec_current * 2 / 3;
            if ( row_period_nsec_current < tmr->timer_resolution_nsec ) {
              regulated = false;
              tmr->settime(0);
              unlock();
              event(tmg_event_fast);
            } else {
              tmr->settime(row_period_nsec_current);
              unlock();
            }
          } else unlock();
        }
        break;
      case '-': // slower
        if (regulation_optional) {
          lock(__FILE__,__LINE__);
          if (!started) tm_play(0);
          else {
            row_period_nsec_current = row_period_nsec_current * 3 / 2;
            tmr->settime(row_period_nsec_current);
            regulated = true;
            unlock();
          }
        }
        break;
      case '}': // fast forward
        if (regulation_optional) {
          lock(__FILE__,__LINE__);
          tmr->settime(0);
          regulated = false;
          if (started) {
            unlock();
            event(tmg_event_fast);
          } else tm_start(0);
        }
        break;
      default:
        msg(MSG_ERROR,"Invalid TM command in tm_generator::execute: '%s'", cmd );
        break;
    }
  } else msg(MSG_ERROR, "Invalid command in tm_generator::execute: '%s'", cmd );
  return 0;
}

void tm_generator::event(enum tm_gen_event evt) {}

void tm_generator::tm_start(int lock_needed) {
  if (lock_needed) lock(__FILE__,__LINE__);
  started = true;
  if ( regulated ) tmr->settime(row_period_nsec_current);
  else tmr->settime( 0 );
  unlock();
  event( tmg_event_start );
}

void tm_generator::tm_play(int lock_needed) {
  if (lock_needed) lock(__FILE__,__LINE__);
  regulated = true;
  row_period_nsec_current = row_period_nsec_default;
  if ( started ) {
    tmr->settime(row_period_nsec_current);
    unlock();
  } else tm_start(0); // don't need to re-lock(), but will unlock()
}

void tm_generator::tm_stop() {
  lock(__FILE__,__LINE__);
  started = false;
  unlock();
  tmr->settime(0);
  event(tmg_event_stop);
}

}
