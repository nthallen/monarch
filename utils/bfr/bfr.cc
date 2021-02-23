/** @file bfr2.cc
 *  Telemetry Buffer
 *  Ported from ARP-DAS circa 25 March 2019
 *  Rewritten using tm_rcvr starting 26 July 2020
 */

#include <list>
#include <string.h>
#include "rundir.h"
#include "bfr.h"
#include "oui.h"
#include "nl.h"
#include "nl_assert.h"
#include "dasio/msg.h"
#include "dasio/appid.h"

using namespace DAS_IO;

bool bfr2_input_client::tmg_opened = false;
bfr2_input_client *bfr2_input_client::tm_gen;
// ### figure out if these can go into the class
bool blocked_input = false;
std::list<bfr2_output_client*> all_readers;

bfr2_input_client::bfr2_input_client(Authenticator *Auth,
          const char *iname, bool blocking)
    : Serverside_client(Auth, iname, bfr2_input_client_ibufsize),
      tm_rcvr(this),
      tm_queue(),
      blocking(blocking)
{
  rows_dropped = 0;
  rows_forced = 0;
  processing_data = false;
  tm_gen = this;
  n_rows_received = 0;
}

bfr2_input_client::~bfr2_input_client() {
  msg(0, "Total rows received: %d", n_rows_received);
  msg(0, "Rows dropped safely: %d", rows_dropped);
  if (rows_forced)
    msg(1, "Rows dropped unsafely: %d", rows_forced);
}

bool bfr2_input_client::auth_hook(Authenticator *Auth, SubService *SS) {
  // should lock the tm_queue here:
  if (tmg_opened) return false;
  tmg_opened = true;
  return true;
}

bool bfr2_input_client::protocol_input() {
  bool blocked_input_save = blocked_input;
  if (blocked_input) {
    msg(MSG_DBG(0),
      "protocol_input() while blocked: flags=0x%X", flags);
  }
  process_message();
  flags = blocking && blocked_input ? 0 : Fl_Read;
  if (blocked_input_save != blocked_input)
    msg(MSG_DBG(0), "Input %sblocked", blocked_input ? "" : "un");
  return false;
}

// Since we accept data from any frame, we need to copy the incoming
// frame definition into tm_info so tm_client::process_init()
// will be happy.
void bfr2_input_client::process_init() {
  memcpy(&tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t));
  tm_rcvr::process_init();

  lock(__FILE__, __LINE__);
  int total_Qrows = tm_info.nrowminf *
    ( ( tmi(nrowsper) * 60 + tmi(nsecsper)*tm_info.nrowminf - 1 )
        / (tmi(nsecsper)*tm_info.nrowminf) );
  init(total_Qrows);
  commit_tstamp(tm_info.t_stmp.mfc_num, tm_info.t_stmp.secs);
  unlock();
}
void bfr2_input_client::process_tstamp() {
  tm_rcvr::process_tstamp();
  commit_tstamp(tm_info.t_stmp.mfc_num, tm_info.t_stmp.secs);
}

bool bfr2_input_client::process_eof() {
  // This shuts down the listening ports, but it does
  // not shutdown everything. We will continue to process
  // the tm_queue until all clients have received all the data.
  srvr->Shutdown(false);
  commit_quit();
  return false;
}

unsigned int bfr2_input_client::process_data() {
  if (processing_data) return 0;
  processing_data = true;
  unsigned char *raw = data_row;
  unsigned int rows_processed = 0;
  int n_rows = rows_in_buf;
  int n_rows_when_blocked = n_rows;
  mfc_t MFCtr = buf_mfctr;
  int n_times_stuck = 0;
  static int n_times_stuck_global = 0;

  if (blocked_input) {
    msg(MSG_DBG(0), "Entering process_data() blocked n_rows=%d",
      n_rows);
  }
  while ( n_rows ) {
    unsigned char *dest;
    lock(__FILE__,__LINE__);
    tmq_retire_check();
    int n_room = allocate_rows(&dest);
    if ( n_room ) {
      unlock();
      if ( n_room > n_rows ) n_room = n_rows;
      int rawsize = n_room * tm_rcvr::nbQrow;
      memcpy( dest, raw, rawsize );
      commit_rows( MFCtr, 0, n_room );
      n_rows_received += n_room;
      raw += rawsize;
      n_rows -= n_room;
      MFCtr += n_room;
      rows_processed += n_room;
    } else {
      unlock();
      if (n_rows == rows_in_buf && !blocking) {
        int min_Qrow = min_reader(first_tmqr, true);
        if (min_Qrow > first_tmqr->Qrows_retired) {
          // force early retirement
          ++rows_dropped;
        } else {
          ++rows_forced;
        }
        retire_rows(first_tmqr, 1);
      } else {
        if (!blocked_input) {
          msg(MSG_DBG(0), "Input blocked in process_data()");
          blocked_input = true;
          flags &= ~Fl_Read;
          n_rows_when_blocked = n_rows;
        } else if (blocked_input && n_rows == n_rows_when_blocked) {
          ++n_times_stuck_global;
          if (++n_times_stuck == 2)
            msg(MSG_WARN,
            "Stuck in process_data %d/%d", n_times_stuck,
            n_times_stuck_global);
        }
      }
    }
    if (run_output_queue(false)) break;
  }
  if (blocked_input) {
    if (n_rows == 0) {
      msg(MSG_DBG(0), "Input unblocked in process_data()");
      blocked_input = false;
      flags |= Fl_Read;
    } else {
      msg(MSG_DBG(0), "Leaving process_data() with Input blocked");
    }
  }
  processing_data = false;
  return rows_processed;
}

void bfr2_input_client::process_quit() {
  msg(MSG_ERROR, "%s: Unexpected call to process_quit()", iname);
}

void bfr2_input_client::tmq_retire_check() {
  while (first_tmqr && first_tmqr->ref_count == 0 &&
         first_tmqr->next_tmqr && first_tmqr->n_Qrows == 0) {
    retire_rows(first_tmqr, 0);
  }
  tmq_ref *tmqr = first_tmqr;
  if (!tmqr) return;
  nl_assert(tmqr->ref_count >= 0);
  // Now look for Qrows we can retire
  int min_Qrow = min_reader(tmqr, false);
  if (min_Qrow > tmqr->Qrows_retired)
    retire_rows(tmqr, min_Qrow - tmqr->Qrows_retired);
  // return tmqr;
}

// The number here determines which rows are absolutely
// safe to retire. A different calculation is required
// to determine which rows can be retired that might be
// currently tied up in output buffers.
int bfr2_input_client::min_reader(tmq_ref *tmqr, bool forcing) {
  if ( tmqr != first_tmqr ) return 0;
  int min = tmqr->Qrows_retired + tmqr->n_Qrows;
  std::list<bfr2_output_client *>::iterator ocp;
  for ( ocp = all_readers.begin(); ocp != all_readers.end(); ++ocp ) {
    bfr2_output_client *oc = *ocp;
    if ( oc->data.tmqr == tmqr && oc->data.n_Qrows < min &&
         (!forcing || !oc->obuf_empty()))
      min = oc->data.n_Qrows;
  }
  return min;
}

void bfr2_input_client::run_input_queue() {
  if (blocked_input) {
    // blocked_input = false;
    // flags |= Fl_Read;
    msg(MSG_DBG(0), "Calling process_message() in run_input_queue()");
    process_message();
  }
}

bool bfr2_input_client::run_output_queue(bool quitting) {
  bool blocked_output = false;
  std::list<bfr2_output_client*>::iterator oci;
  for (lock(__FILE__,__LINE__), oci = all_readers.begin(), unlock();
       oci != all_readers.end();
       lock(__FILE__,__LINE__), ++oci, unlock()) {
    bfr2_output_client *oc = *oci;
    oc->transmit(quitting);
    if (!oc->obuf_empty())
      blocked_output = true;
  }
  return blocked_output;
}

bool bfr2_input_client::ready_to_quit() {
  while (!queue_empty()) {
    tmq_retire_check();
    if (run_output_queue(false))
      return false;
  }
  run_output_queue(true); // send Quit and set TO
  return all_readers.empty();
}

bfr2_output_client::bfr2_output_client(Authenticator *Auth,
          const char *iname, bool is_fast)
    : Serverside_client(Auth, iname, bfr2_output_client_ibufsize),
      is_fast(is_fast) {
  quit_sent = false;
  data.tsp = 0;
  data.tmqr = 0;
  data.n_Qrows = 0;
  data.n_Qrows_pending = 0;
  output.maxQrows = 0; // Set in first read_reply()
  output.rows_missing = 0;
  output.rows_output = 0;
  output.ready = true;
  all_readers.push_back(this);
}

bfr2_output_client::~bfr2_output_client() {
  msg(0, "%s: Total rows output: %d", iname, output.rows_output);
  if (output.rows_missing)
    msg(1, "%s: %d rows dropped", iname, output.rows_missing);
  if (data.tmqr)
    data.tmqr = data.tmqr->dereference(false);
  all_readers.remove(this);
}

/**
   transmit() is called when we know we have something to send to a
   tm_client.
   First determine either the largest complete record that is less
   than the requested size or the smallest complete record. If the
   smallest record is larger than the request size, allocate the
   partial buffer and copy the record into it.
   Partial buffer size, if allocated, should be the larger of the size
   of the tm_info message or a one-row data message (based on the
   assumption that if a small request comes in, the smallest full
   message will be chosen for output)

   It is assumed that oc has already been removed from whatever wait
   queue it might have been on.
*/
void bfr2_output_client::transmit(bool quitting) {
  nl_assert(!quitting || obuf_empty());
  if (! obuf_empty() || (quitting && quit_sent))
    return;
  nl_assert(data.n_Qrows_pending == 0);
  if (output.maxQrows == 0) {
    output.maxQrows = bfr2_input_client::tm_gen->total_Qrows;
  }
  
  if (quitting) {
    hdr.s.hdr.tm_id = TMHDR_WORD;
    hdr.s.hdr.tm_type = TMTYPE_QUIT;
    iwrite((const char *)&hdr.s.hdr, sizeof(hdr.s.hdr));
    TO.Set(1, 0);
    quit_sent = true;
    flags |= Fl_Timeout;
    return;
  }
  if ( data.tmqr == 0 ) {
    // First output to this client, so send tm_init
    bfr2_input_client::tm_gen->lock(__FILE__,__LINE__);
    if (bfr2_input_client::tm_gen->next_tmqr(&data.tmqr)) {
      data.n_Qrows = 0;
    
      hdr.s.hdr.tm_id = TMHDR_WORD;
      hdr.s.hdr.tm_type = TMTYPE_INIT;
      data.tsp = data.tmqr->tsp;

      // Message consists of
      //   tm_hdr_t (TMHDR_WORD, TMTYPE_INIT)
      //   tm_info_t with the current timestamp
      iov[0].iov_base = &hdr.s.hdr;
      iov[0].iov_len = sizeof(hdr.s.hdr);
      // SETIOV( &iov[0], &hdr.s.hdr, sizeof(hdr.s.hdr) );
      iov[1].iov_base = &tm_info;
      iov[1].iov_len = sizeof(tm_info)-sizeof(tstamp_t);
      // SETIOV( &iov[1], &tm_info, sizeof(tm_info)-sizeof(tstamp_t) );
      iov[2].iov_base = &data.tsp->TS; // &data.tmqr->TSq->TS;
      iov[2].iov_len = sizeof(tstamp_t);
      // SETIOV( &iov[2], &data.tmqr->TSq->TS, sizeof(tstamp_t) );
      int nb = sizeof(tm_hdr_t) + sizeof(tm_info_t);
      iwritev(iov, 3);
      // do_read_reply( oc, nb, iov, 3 );
    } else output.ready = true; // enqueue_read( oc, nonblock );
    bfr2_input_client::tm_gen->unlock();
  } else {
    /* I've handled data.n_Qrows */
    tmq_ref *tmqr = data.tmqr;

    bfr2_input_client::tm_gen->lock(__FILE__,__LINE__);
    while (tmqr) {
      int nQrows_ready;
      
      /* DQD has a total of tmqr->Qrows_retired + tmqr->n_Qrows */
      if ( data.n_Qrows < tmqr->Qrows_retired ) {
        // then we've missed some data: make a note and set
        int n_missed = tmqr->Qrows_retired - data.n_Qrows;
        output.rows_missing += n_missed;
        data.n_Qrows = tmqr->Qrows_retired;
      }
      nQrows_ready = tmqr->n_Qrows + tmqr->Qrows_retired
                      - data.n_Qrows;
      if (nQrows_ready < 0) {
        msg(MSG_ERROR, "nQrows_ready=%d (< 0)", nQrows_ready);
        nQrows_ready = 0;
      }
      assert( nQrows_ready >= 0 );
      if ( nQrows_ready > 0 ) {
        if ( !blocked_input && (!srvr_has_shutdown()) &&
             tmqr->next_tmqr == 0 && nQrows_ready < output.maxQrows
             && (!is_fast)) {
          // wait for more data
        } else {
          int XRow_Num, NMinf, Row_Num_start, n_iov;
          mfc_t MFCtr_start;
          int Qrow_start, nQ1, nQ2;
          
          hdr.s.hdr.tm_id = TMHDR_WORD;
          hdr.s.hdr.tm_type = bfr2_input_client::tm_gen->output_tm_type;
          hdr.s.u.dhdr.n_rows = nQrows_ready;
          XRow_Num = tmqr->row_start + data.n_Qrows -
                      tmqr->Qrows_retired;
          NMinf = XRow_Num/tm_info.nrowminf;
          MFCtr_start = tmqr->MFCtr_start + NMinf;
          Row_Num_start = XRow_Num % tm_info.nrowminf;
          switch ( bfr2_input_client::tm_gen->output_tm_type ) {
            case TMTYPE_DATA_T1: break;
            case TMTYPE_DATA_T2:
              hdr.s.u.dhdr.mfctr = MFCtr_start;
              hdr.s.u.dhdr.rownum = Row_Num_start;
              break;
            case TMTYPE_DATA_T3:
              hdr.s.u.dhdr.mfctr = MFCtr_start;
              break;
            default:
              msg(4,"Invalid output_tm_type" );
          }
          //SETIOV( &iov[0], &hdr.s.hdr, nbDataHdr );
          iov[0].iov_base = &hdr.s.hdr;
          iov[0].iov_len  =
            bfr2_input_client::tm_gen->tm_queue::nbDataHdr;
          Qrow_start = tmqr->Qrow + data.n_Qrows -
                          tmqr->Qrows_retired;
          if ( Qrow_start >= bfr2_input_client::tm_gen->total_Qrows )
            Qrow_start -= bfr2_input_client::tm_gen->total_Qrows;
          nl_assert(Qrow_start >= 0 &&
            Qrow_start < bfr2_input_client::tm_gen->total_Qrows);
          nQ1 = nQrows_ready;
          nQ2 = Qrow_start + nQ1 -
                bfr2_input_client::tm_gen->total_Qrows;
          if ( nQ2 > 0 ) {
            nQ1 -= nQ2;
            // SETIOV( &iov[2], row[0], nQ2 * nbQrow );
            iov[2].iov_base = bfr2_input_client::tm_gen->row[0];
            iov[2].iov_len  =
              nQ2 * bfr2_input_client::tm_gen->tm_queue::nbQrow;
            n_iov = 3;
          } else n_iov = 2;
          // SETIOV( &iov[1], row[Qrow_start],
                      // nQ1 * nbQrow );
          iov[1].iov_base = bfr2_input_client::tm_gen->row[Qrow_start];
          iov[1].iov_len  =
            nQ1 * bfr2_input_client::tm_gen->tm_queue::nbQrow;
          data.n_Qrows_pending += nQrows_ready;
          // Cannot update n_Qrows until the write is
          // completed, else we'll get buffer corruption
          // data.n_Qrows += nQrows_ready;
          iwritev(iov, n_iov);
        }
        break; // out of while(tmqr)
      } else if (bfr2_input_client::tm_gen->next_tmqr(&tmqr)) {
        nl_assert(tmqr);
        bool do_TS = tmqr->tsp != data.tsp;
        // tmqr = tmqr->dereference(true);
        data.tmqr = tmqr;
        data.tsp = tmqr->tsp;
        data.n_Qrows = 0;
        data.n_Qrows_pending = 0;
        if ( do_TS ) {
          hdr.s.hdr.tm_id = TMHDR_WORD;
          hdr.s.hdr.tm_type = TMTYPE_TSTAMP;
          // SETIOV( &iov[0], &hdr.s.hdr, sizeof(tm_hdr_t) );
          iov[0].iov_base = &hdr.s.hdr;
          iov[0].iov_len  = sizeof(tm_hdr_t);
          //SETIOV( &iov[1], &tmqr->TSq->TS, sizeof(tstamp_t) );
          iov[1].iov_base = &tmqr->tsp->TS;
          iov[1].iov_len  = sizeof(tstamp_t);
          iwritev(iov, 2);
          // do_read_reply( oc, sizeof(tm_hdr_t)+sizeof(tstamp_t),
            // iov, 2 );
          break;
        } // else loop through again to evaluate actual data
      } else {
        break;
      }
    }
    bfr2_input_client::tm_gen->unlock();
  }
}

bool bfr2_output_client::iwritten(int ntr) {
  if (obuf_empty()) {
    if (data.n_Qrows_pending) {
      data.n_Qrows += data.n_Qrows_pending;
      output.rows_output += data.n_Qrows_pending;
      data.n_Qrows_pending = 0;
    }
    output.ready = true;
    if (blocked_input && bfr2_input_client::tm_gen) {
      msg(MSG_DBG(0), "%s: Calling run_input_queue", iname);
      bfr2_input_client::tm_gen->run_input_queue();
    }
  }
  return false;
}

bool bfr2_output_client::protocol_timeout() {
  if (quit_sent) {
    msg(MSG_WARN, "%s: Timeout expecting EOF", iname);
    ELoop->delete_child(this);
  }
  return false;
}

Serverside_client *new_bfr_input_client(Authenticator *Auth, SubService *SS) {
  bool blocking = (SS->name == "tm_bfr/input");
  return new bfr2_input_client(Auth, Auth->get_client_app(), blocking);
}

Serverside_client *new_bfr_output_client(Authenticator *Auth, SubService *SS) {
  bool is_fast = (SS->name == "tm_bfr/fast");
  return new bfr2_output_client(Auth, Auth->get_client_app(), is_fast);
}


void bfr::add_subservices() {
  add_subservice(new SubService("tm_bfr/input", new_bfr_input_client,
      (void *)(0), bfr2_input_client::auth_hook));
  add_subservice(new SubService("tm_bfr/input-nb",
      new_bfr_input_client,
      (void *)(0), bfr2_input_client::auth_hook));
  add_subservice(new SubService("tm_bfr/optimized",
      new_bfr_output_client, (void *)(0)));
  add_subservice(new SubService("tm_bfr/fast",
      new_bfr_output_client, (void *)(0)));
}

bool bfr::ready_to_quit() {
  if (!has_shutdown_b)
    Server::ready_to_quit();
  if (bfr2_input_client::tm_gen) {
    return bfr2_input_client::tm_gen->ready_to_quit();
  }
  return true;
}

/* Main method */
int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  setup_rundir();
  
  bfr S;
  S.add_subservices();
  msg(0, "%s %s Starting", AppID.fullname, AppID.rev);
  S.Start(Server::Srv_Function, "bfr");
  S.ELoop.delete_children();
  S.ELoop.clear_delete_queue(true);
  msg(0, "Terminating");
  return 0;
}
