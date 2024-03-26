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
  : Client("bfr", "bfr-input", "tm_bfr",
           collection ? "input-nb" : "input", 80),
    buffering(true)
    {}

bool tm_gen_bfr::iwritev(struct iovec *iov, int nparts, const char *where) {
  nl_assert(is_negotiated());
  bool rv = Client::iwritev(iov, nparts);
  if (!buffering && !obuf_empty()) {
    buffering = true;
    tm_generator::TM_server->buffering(true);
  }
  return rv;
}

bool tm_gen_bfr::process_eof() {
  msg(MSG_FATAL, "Lost connection to bfr");
  return true;
}

bool tm_gen_bfr::connect_failed() {
  msg(MSG_FATAL, "Connect to bfr failed");
  return true;
}

bool tm_gen_bfr::app_connected() {
  tm_hdr_t hdr = { TMHDR_WORD, TMTYPE_INIT };
  SETIOV(&bfr_iov[0], &hdr, sizeof(hdr));
  SETIOV(&bfr_iov[1], &tm_info, sizeof(tm_info));
  return iwritev( bfr_iov, 2, "Sending tm_info");
}

bool tm_gen_bfr::iwritten(int nb) {
  if (buffering && is_negotiated() && obuf_empty()) {
    buffering = false;
    tm_generator::TM_server->buffering(false);
  }
  if (is_negotiated() && obuf_empty())
    tm_generator::TM_server->bfr_write_completed();
  return false;
}

tm_generator *tm_generator::TM_server;

tm_generator::tm_generator()
    : tm_queue(),
      Server("tm_gen"),
      bfr(0),
      tmr(0),
      cur_tsp(0),
      quit(false),
      started(false),
      regulated(false),
      regulation_optional(true),
      autostart(false),
      is_buffering(true),
      transmit_blocked(false)
{
  nl_assert(TM_server == 0);
  TM_server = this;
}

tm_generator::~tm_generator() {}

/**
 * Assumes tm_info is defined
 */
void tm_generator::init(int nQrows, bool collection, int obufsize) {
  tm_queue::init(nQrows);
  collecting = collection;
  tm_gen_cmd::attach(this); // defines the subservice
  bfr = new tm_gen_bfr(collection);
  bfr->set_obufsize(obufsize);
  bfr->reference();
  bfr->connect();
  ELoop.add_child(bfr);
  tmr = new tm_gen_tmr(this);
  tmr->reference();
  row_period_nsec_default = tmi(nsecsper)*(uint64_t)1000000000L/tmi(nrowsper);
  row_period_nsec_current = row_period_nsec_default;
}

void tm_generator::transmit_data( bool single_row ) {
  if (is_buffering) {
    transmit_blocked = true;
    return;
  }
  transmit_blocked = false;
  // We can read from the queue without locking
  // But we need to lock when we reference tmg_bfr_fd
  int rc;
  tm_hdrs_t hdrs;
  hdrs.s.hdr.tm_id = TMHDR_WORD;
  tmq_ref *tmqdr = 0;
  next_tmqr(&tmqdr);
  while ( tmqdr ) {
    if (tmqdr->n_Qrows == 0) {
      // No longer calling retire_rows(tmqdr,0);
      if (!next_tmqr(&tmqdr)) break;
      // tmqdr = tmqdr->next_tmqr;
    } else {
      if (tmqdr->tsp != cur_tsp) {
        cur_tsp = tmqdr->tsp;
        hdrs.s.hdr.tm_type = TMTYPE_TSTAMP;
        SETIOV(&pvt_iov[0], &hdrs, sizeof(tm_hdr_t));
        SETIOV(&pvt_iov[1], &cur_tsp->TS, sizeof(cur_tsp->TS));
        lock(__FILE__, __LINE__);
        if ( bfr ) {
          bfr->iwritev(pvt_iov, 2, "transmitting tstamp");
        }
        unlock();
      }
      hdrs.s.hdr.tm_type = output_tm_type;
      int n_rows = single_row ? 1 : tmqdr->n_Qrows;
      hdrs.s.u.dhdr.n_rows = n_rows;
      hdrs.s.u.dhdr.mfctr = tmqdr->MFCtr_start;
      hdrs.s.u.dhdr.rownum = tmqdr->row_start;
      SETIOV(&pvt_iov[0], &hdrs, nbDataHdr);
      int n_iov;
      if ( tmqdr->Qrow + n_rows <= total_Qrows ) {
        SETIOV(&pvt_iov[1], row[tmqdr->Qrow], n_rows * nbQrow );
        n_iov = 2;
      } else {
        int n_rows1 = total_Qrows - tmqdr->Qrow;
        SETIOV(&pvt_iov[1], row[tmqdr->Qrow], n_rows1 * nbQrow );
        int n_rows2 = n_rows - n_rows1;
        SETIOV(&pvt_iov[2], row[0], n_rows2 * nbQrow );
        n_iov = 3;
      }
      lock(__FILE__,__LINE__);
      if ( bfr ) {
        bfr->iwritev(pvt_iov, n_iov, "transmitting data");
      }
      unlock();
      retire_rows(first_tmqr, n_rows);
      if ( single_row ) break;
    }
  }
  if (tmqdr) tmqdr->dereference(false);
  if (queue_empty())
    tm_queue_is_empty();
}

void tm_generator::tm_queue_is_empty() {}

void tm_generator::bfr_write_completed() {
}

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
      TM Unlock optional regulation "TMU"
        This is for debugging
      TM Interface Report
        Also for debugging

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
bool tm_generator::execute(const char *cmd) {
  if (cmd[0] == '\0' || (cmd[0] == 'Q')) {
    msg( MSG_DEBUG, "Received %s Quit",
      cmd[0] ? "Explicit" : "Implicit");
    event(tmg_event_quit);
    return true;
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
          transmit_data(false);
        }
        break;
      case 'U': // Unlock optional regulation
        regulation_optional = true;
        break;
      default:
        msg(MSG_ERROR,"Invalid TM command in tm_generator::execute: '%s'", cmd );
        break;
    }
  } else msg(MSG_ERROR, "Invalid command in tm_generator::execute: '%s'", cmd );
  return false;
}

void tm_generator::event(enum tm_gen_event evt) {
  switch (evt) {
    case tmg_event_stop:
      lock(__FILE__,__LINE__);
      started = false;
      unlock();
      if (tmr)
        tmr->settime(0);
      break;
    case tmg_event_quit:
      event(tmg_event_stop);
      lock(__FILE__,__LINE__);
      started = false; // redundant
      quit = true;
      unlock();
      if (tmr) {
        Interface::dereference(tmr);
        tmr = 0;
      }
      Shutdown();
      break;
  } 
}

void tm_generator::buffering(bool bfring) {
  is_buffering = bfring;
}

bool tm_generator::ready_to_quit() {
  // Shut down listeners
  Server::ready_to_quit();
  // Empty the queue except when regulated and !collecting
  while ((!regulated || collecting) && !queue_empty()) {
    if (is_buffering) return false;
    transmit_data(false);
  }
  if (is_buffering) return false;
  if (!tm_gen_quit)
    commit_quit();
  if (is_buffering) return false;
  if (bfr) {
    Interface::dereference(bfr);
    bfr = 0;
  }
  return true;
}

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
  event(tmg_event_stop);
}

}
