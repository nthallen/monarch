/** @file bfr.cc
 *  Telemetry Buffer
 *  est. 25 March 2019
 *  ported from ARP-DAS
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
#include "dasio/tm_queue.h"

using namespace DAS_IO;

bool bfr_input_client::tmg_opened = false;
bool blocked_writer = false;
std::list<bfr_output_client*> all_readers;

bool bfr_input_client::auth_hook(Authenticator *Auth, SubService *SS) {
  // should lock the tm_queue here:
  if (tmg_opened) return false;
  tmg_opened = true;
  return true;
}

bfr_input_client::bfr_input_client(Authenticator *Auth, const char *iname, bool blocking)
    : Serverside_client(Auth, iname, bfr_input_client_ibufsize), blocking(blocking) {
  // data.tmqr = 0;
  // data.n_Qrows = 0;
  state = TM_STATE_HDR;
  bufsize = sizeof(part.hdr);
  set_binary_mode();
  buf = (unsigned char *)&part.hdr;
  write.nbrow_rec = 0;
  write.nbhdr_rec = 0;
  nc = 0;
  write.off_msg = 0;
  write.nb_rec = 0;
  write.off_queue = 0;
  data_state_eval = 0;
}

bfr_input_client::~bfr_input_client() {
  bufsize = 0;
  buf = 0;
}

bool bfr_input_client::process_eof() {
  // Ideally, we should ensure that the tm_queue has been flushed
  srvr->Shutdown();
  return Serverside_client::process_eof();
}

bool bfr_input_client::protocol_input() {
  blocked_writer = false;
  int new_rows = 0; // This might substitute...
  
  // _IO_SET_WRITE_NBYTES( ctp, msg->i.nbytes );
  // Not necessary since we'll handle the return ourselves
  // However, that means we need to store the total message size
  // Use off_msg for total size.
  
  // We loop here as long as we have work to do. We can get out
  // if we've processed all the data in the message (nb_msg == 0)
  // or exhausted all the available space in the DQ (nbdata == 0)
  //------
  // In the porting process on 3/26/19, I will make the following replacements
  //   part.dptr replaced with buf
  //   part.nbdata replaced with bufsize
  //   write.nb_msg replace with nc
  //   ocb->rw. with nothing. See below
  //   ocb-> replace with nothing. I mean, not 'nothing', but nothing
  //   DQD_Queue.last replace with last_tmqr
  while ( nc > 0 && bufsize > 0 ) {
    int nb_read;
    nl_assert(nc <= bufsize + binary_offset);
    if (state == TM_STATE_HDR) {
      if (nc >= sizeof(tm_hdr_t)) {
        if ( part.hdr.s.hdr.tm_id != TMHDR_WORD ) {
          msg(MSG_FATAL, "Invalid Message header" );
          // MsgError( write.rcvid, EINVAL );
          // Scan ahead for TMHDR_WORD
          bufsize = sizeof( part.hdr );
          buf = (unsigned char *)&part.hdr;
          write.off_msg = 0;
          return false;
        }
        switch (part.hdr.s.hdr.tm_type) {
          case TMTYPE_INIT:
            break;
          case TMTYPE_TSTAMP:
            bufsize = sizeof(tm_hdr_t) + sizeof(tstamp_t);
            break;
          case TMTYPE_DATA_T1:
            // bufsize = sizeof(tm_hdr_t) + sizeof(tm_data_t1_t)+1;
            break;
          case TMTYPE_DATA_T2:
            // bufsize = sizeof(tm_hdr_t) + sizeof(tm_data_t2_t)+1;
            break;
          case TMTYPE_DATA_T4:
            // bufsize = sizeof(tm_hdr_t) + sizeof(tm_data_t4_t)+1;
            break;
          case TMTYPE_DATA_T3:
            // bufsize = sizeof(tm_hdr_t) + sizeof(tm_data_t3_t)+1;
            break;
          default:
            msg(4, "Invalid bfr state %d", state);
        }
        state = TM_STATE_HDR2;
      } else {
        return false; // wait for more input
      }
    }
    
    nb_read = nc < bufsize ?
      nc : bufsize;
    // memcpy(buf, &buf[cp], nb_read);
    buf += nb_read;
    bufsize -= nb_read;
    nc -= nb_read;
    write.off_msg += nb_read; // write.off_msg is maybe cp?? except it is persistent
    if ( state == TM_STATE_DATA ) {
      write.nb_rec -= nb_read;
      // write.off_rec += nb_read;
      write.off_queue += nb_read;
    }
    nl_assert(bufsize >= 0);
    if ( bufsize == 0 ) {
      switch ( state ) {
        case TM_STATE_HDR:
          msg(3, "Should not see TM_STATE_HDR here");
        case TM_STATE_HDR2:
          switch ( part.hdr.s.hdr.tm_type ) {
            case TMTYPE_INIT:
              if ( last_tmqr )
                msg(MSG_FATAL, "Second TMTYPE_INIT received" );
              write.off_queue = sizeof(tm_hdrs_t)-sizeof(tm_hdr_t);
              bufsize = sizeof(tm_info) - write.off_queue;
              buf = (unsigned char *)&tm_info;
              memcpy( buf, &part.hdr.raw[sizeof(tm_hdr_t)],
                      write.off_queue );
              buf += write.off_queue;
              state = TM_STATE_INFO;
              break;
            case TMTYPE_TSTAMP:
              if ( last_tmqr == 0 )
                msg(MSG_FATAL, "TMTYPE_TSTAMP received before _INIT" );
              if (write.off_msg >= sizeof(tm_hdr_t)+sizeof(tstamp_t)) {
                lock(__FILE__, __LINE__);
                commit_tstamp(part.hdr.s.u.ts.mfc_num, part.hdr.s.u.ts.secs);
                unlock();
                new_rows++;
                state = TM_STATE_HDR; // already there!
                bufsize = sizeof( part.hdr );
                buf = (unsigned char *)&part.hdr;
                write.off_msg = 0;
              }
              break;
            case TMTYPE_DATA_T1:
            case TMTYPE_DATA_T2:
            case TMTYPE_DATA_T4:
              msg(4,"This state does not exist");
            case TMTYPE_DATA_T3:
              if (write.off_msg >= sizeof(tm_hdr_t)+sizeof(tm_data_t3_t)) {
                if ( last_tmqr == 0 )
                  msg(MSG_FATAL, "Second TMTYPE_DATA* received before _INIT" );
                nl_assert( data_state_eval != 0 );
                nl_assert( part.hdr.s.hdr.tm_type == output_tm_type );
                write.nb_rec = part.hdr.s.u.dhdr.n_rows *
                  write.nbrow_rec;
                write.off_queue = 0;
                new_rows += (this->*data_state_eval)();
                // ### Make sure data_state_eval returns the number
                // of rows that have been completely added to DQ
                if ( write.nb_rec <= 0 ) {
                  state = TM_STATE_HDR;
                  bufsize = sizeof(part.hdr);
                  buf = (unsigned char *)&part.hdr;
                  write.off_msg = 0;
                } // else break out
              }
              break;
            default:
              msg( 4, "Invalid state" );
          }
          break;
        case TM_STATE_INFO:
          // ### Check return value
          if (process_tm_info())
            msg(MSG_FATAL, "We cannot continue with this");
          blocking = false; // nonblock;
          new_rows++;
          state = TM_STATE_HDR; //### Use state-init function?
          bufsize = sizeof(part.hdr);
          buf = (unsigned char *)&part.hdr;
          write.off_msg = 0;
          break;
        case TM_STATE_DATA:
          new_rows += (this->*data_state_eval)();
          if ( write.nb_rec <= 0 ) {
            state = TM_STATE_HDR;
            bufsize = sizeof(part.hdr);
            buf = (unsigned char *)&part.hdr;
            write.off_msg = 0;
          }
          break;
      }
    }
  }
  if ( nc == 0 ) {
    // MsgReply( write.rcvid, write.off_msg, 0, 0 );
    if ( new_rows ) run_read_queue();
    //### Mark us as not blocked: maybe that's nbdata != 0?
  } else {
    // We must have nbdata == 0 meaning we're going to block
    nl_assert(blocking);
    blocked_writer = true;
    run_read_queue();
  }
  return false;
}

/** As soon as tm_info has been received, we can decide what
   data format to output, how much buffer space to allocate
   and in what configuration. We can then create the first
   timestamp record (with the TS in the tm_info) and the
   first dq_descriptor, albeit with no Qrows, but refrencing
   the the first timestamp. Then we can check to see if any
   readers are waiting, and initialize them.
   @return true if the incoming tm_info is insane.
*/
bool bfr_input_client::process_tm_info() {
  char *rowptr;
  int i;

  // Perform sanity checks
  if (tmi(nbminf) == 0 ||
      tmi(nbrow) == 0 ||
      tmi(nrowmajf) == 0 ||
      tmi(nrowsper) == 0 ||
      tmi(nsecsper) == 0 ||
      tmi(mfc_lsb) == tmi(mfc_msb) ||
      tmi(mfc_lsb) >= tmi(nbrow) ||
      tmi(mfc_msb) >= tmi(nbrow) ||
      tmi(nbminf) < tmi(nbrow) ||
      tmi(nbminf) % tmi(nbrow) != 0 ||
      tm_info.nrowminf != tmi(nbminf)/tmi(nbrow)) {
    msg(MSG_ERROR, "Sanity Checks failed on incoming stream" );
    return true;
  }

  // What data format should we output?
  lock(__FILE__, __LINE__);

  int total_Qrows = tm_info.nrowminf *
    ( ( tmi(nrowsper) * 60 + tmi(nsecsper)*tm_info.nrowminf - 1 )
        / (tmi(nsecsper)*tm_info.nrowminf) );

  init(total_Qrows);

  switch (output_tm_type) {
    case TMTYPE_DATA_T1:
      msg(MSG_FATAL, "TMTYPE_DATA_T1 not supported");
      // write.nbhdr_rec = TM_HDR_SIZE_T1;
      // data_state_eval = data_state_T1;
      break;
    case TMTYPE_DATA_T2:
      msg(MSG_FATAL, "TMTYPE_DATA_T2 not supported");
      // write.nbhdr_rec = TM_HDR_SIZE_T2;
      // write.nbrow_rec = tmi(nbrow);
      // data_state_eval = data_state_T2;
      break;
    case TMTYPE_DATA_T3:
      write.nbhdr_rec = TM_HDR_SIZE_T3;
      write.nbrow_rec = tmi(nbrow) - 4;
      data_state_eval = &DAS_IO::bfr_input_client::data_state_T3;
      break;
    default:
      msg(4,"Invalid output_tm_type");
  }
  
  commit_tstamp(tm_info.t_stmp.mfc_num, tm_info.t_stmp.secs);
  unlock();
  return false;
}

// The job of data_state_eval is to decide how big the next
// chunk of data should be and where it should go.
// This involves finding space in the data queue and
// setting part.dptr and part.nbdata. We may need to expire
// rows from the data queue, but if we aren't nonblocking, we
// might block to allow the readers to handle what we've already
// got.
// data_state_eval() does not transfer any data via ReadMessage,
// but allocate_qrows() will copy any bytes from the hdr if
// ocb->state == TM_STATE_HDR
//
// Returns the number of rows that have been completed in the
// data queue.

// First check the data we've already moved into the queue
// The rows we read in will always begin at Data_Queue.last,
// which should be consistent with the end of the current
// tmqr data set. The number of rows is also guaranteed to
// fit within the Data_Queue without wrapping, so it should
// be safe to add nrrecd to Data_Queue.last, though it may
// be necessary to set last to zero afterwards.
//   T1->T1 just add to current tmqr without checks
//   T2->T2 Copy straight in, then verify continuity with previous
// records.
//   T3->T3 Copy straight in. Verify consecutive, etc.

int bfr_input_client::data_state_T3() {
  lock(__FILE__,__LINE__);
  
  int nrrecd = write.off_queue/nbQrow;
  nl_assert(bufsize == 0);
  nl_assert(write.off_queue == nrrecd*nbQrow); // Not sure about this

  if (state == TM_STATE_DATA) {
    commit_rows(part.hdr.s.u.dhdr.mfctr, 0, nrrecd);
    part.hdr.s.u.dhdr.mfctr += nrrecd;
  }
  tmq_retire_check();
  int nrowsfree = allocate_rows(&buf);
  bufsize = nrowsfree * write.nbrow_rec;
  if (nrowsfree > 0 && state == TM_STATE_HDR2) {
    // copy from hdr into buf, update accordingly
    write.off_queue = sizeof(tm_hdrs_t) - write.nbhdr_rec;
    // This could actually happen, but it shouldn't
    nl_assert( write.off_queue <= bufsize );
    bufsize -= write.off_queue;
    memcpy( buf,
            &part.hdr.raw[write.nbhdr_rec],
            write.off_queue );
    buf += write.off_queue;
    write.nb_rec -= write.off_queue;
    state = TM_STATE_DATA;
  }
  // Cannot override previous bufsize unless write.nb_rec < bufsize
  if (write.nb_rec < bufsize)
    bufsize = write.nb_rec;
  unlock();
  return nrrecd;
}

void bfr_input_client::tmq_retire_check() {
  while (first_tmqr && first_tmqr->ref_count == 0 &&
         first_tmqr->next_tmqr && first_tmqr->n_Qrows == 0) {
    retire_rows(first_tmqr, 0);
  }
  tmq_ref *tmqr = first_tmqr;
  if (!tmqr) return;
  nl_assert(tmqr->ref_count >= 0);
  // Now look for Qrows we can retire
  int min_Qrow = min_reader(tmqr);
  if (min_Qrow > tmqr->Qrows_retired)
    retire_rows(tmqr, min_Qrow - tmqr->Qrows_retired);
  // return tmqr;
}

int bfr_input_client::min_reader( tmq_ref *tmqr ) {
  if ( tmqr != first_tmqr ) return 0;
  int min = tmqr->Qrows_retired + tmqr->n_Qrows;
  std::list<bfr_output_client *>::iterator ocbp;
  for ( ocbp = all_readers.begin(); ocbp != all_readers.end(); ++ocbp ) {
    bfr_output_client *ocb = *ocbp;
    if ( ocb->data.tmqr == tmqr && ocb->data.n_Qrows < min )
      min = ocb->data.n_Qrows;
  }
  return min;
}

void bfr_input_client::run_read_queue() {
  std::list<bfr_output_client*>::iterator ocbi;
  for (lock(__FILE__,__LINE__), ocbi = all_readers.begin(), unlock();
       ocbi != all_readers.end();
       lock(__FILE__,__LINE__), ++ocbi, unlock()) {
    bfr_output_client *ocb = *ocbi;
    if (ocb->read.ready) {
      ocb->read.ready = false;
      read_reply(ocb);
    }
  }
  run_write_queue();
}

/** TODO: Probably want to rename this function since we are
   writing, not replying to a read request.
   
   read_reply(ocb) is called when we know we have
   something to return on a read request.
   First determine either the largest complete record that is less
   than the requested size or the smallest complete record. If the
   smallest record is larger than the request size, allocate the
   partial buffer and copy the record into it.
   Partial buffer size, if allocated, should be the larger of the size
   of the tm_info message or a one-row data message (based on the
   assumption that if a small request comes in, the smallest full
   message will be chosen for output)

   It is assumed that ocb has already been removed from whatever wait
   queue it might have been on.
*/
void bfr_input_client::read_reply(bfr_output_client *ocb) {
  // struct iovec iov[3];
  // int nb;
  
  if (! ocb->obuf_empty()) return;
  
  if ( ocb->data.tmqr == 0 ) {
    lock(__FILE__,__LINE__);
    if (next_tmqr(&ocb->data.tmqr)) {
      ocb->data.n_Qrows = 0;
    
      ocb->state = TM_STATE_HDR; // delete
      ocb->part.hdr.s.hdr.tm_id = TMHDR_WORD;
      ocb->part.hdr.s.hdr.tm_type = TMTYPE_INIT;
      
      ocb->data.tsp = ocb->data.tmqr->tsp;

      // Message consists of
      //   tm_hdr_t (TMHDR_WORD, TMTYPE_INIT)
      //   tm_info_t with the current timestamp
      ocb->iov[0].iov_base = &ocb->part.hdr.s.hdr;
      ocb->iov[0].iov_len = sizeof(ocb->part.hdr.s.hdr);
      // SETIOV( &ocb->iov[0], &ocb->part.hdr.s.hdr,
        // sizeof(ocb->part.hdr.s.hdr) );
      ocb->iov[1].iov_base = &tm_info;
      ocb->iov[1].iov_len = sizeof(tm_info)-sizeof(tstamp_t);
      // SETIOV( &ocb->iov[1], &tm_info, sizeof(tm_info)-sizeof(tstamp_t) );
      ocb->iov[2].iov_base = &ocb->data.tsp->TS; // &ocb->data.tmqr->TSq->TS;
      ocb->iov[2].iov_len = sizeof(tstamp_t);
      // SETIOV( &ocb->iov[2], &ocb->data.tmqr->TSq->TS, sizeof(tstamp_t) );
      int nb = sizeof(tm_hdr_t) + sizeof(tm_info_t);
      do_read_reply( ocb, nb, ocb->iov, 3 );
    } else ocb->read.ready = true; // enqueue_read( ocb, nonblock );
    unlock();
  } else {
    /* I've handled ocb->data.n_Qrows */
    tmq_ref *tmqr = ocb->data.tmqr;

    lock(__FILE__,__LINE__);
    while (tmqr) {
      int nQrows_ready;
      
      /* DQD has a total of tmqr->Qrows_retired + tmqr->n_Qrows */
      if ( ocb->data.n_Qrows < tmqr->Qrows_retired ) {
        // then we've missed some data: make a note and set
        int n_missed = tmqr->Qrows_retired - ocb->data.n_Qrows;
        ocb->read.rows_missing += n_missed;
        ocb->data.n_Qrows = tmqr->Qrows_retired;
      }
      nQrows_ready = tmqr->n_Qrows + tmqr->Qrows_retired
                      - ocb->data.n_Qrows;
      if (nQrows_ready < 0) {
        msg(MSG_ERROR, "nQrows_ready=%d (< 0)", nQrows_ready);
        nQrows_ready = 0;
      }
      assert( nQrows_ready >= 0 );
      if ( nQrows_ready > 0 ) {
        if ( !blocked_writer && srvr_has_shutdown() &&
             // dg_opened < 2 &&
             tmqr->next_tmqr == 0 && nQrows_ready < ocb->read.maxQrows
             // && ocb->hdr.attr->node_type == TM_DCo
             && !ocb->is_fast) {
          // enqueue_read(ocb);
          // wait for more data
        } else {
          int XRow_Num, NMinf, Row_Num_start, n_iov;
          mfc_t MFCtr_start;
          int Qrow_start, nQ1, nQ2;
          
          if ( nQrows_ready > ocb->read.maxQrows )
            nQrows_ready = ocb->read.maxQrows;
          ocb->part.hdr.s.hdr.tm_id = TMHDR_WORD;
          ocb->part.hdr.s.hdr.tm_type = output_tm_type;
          ocb->part.hdr.s.u.dhdr.n_rows = nQrows_ready;
          XRow_Num = tmqr->row_start + ocb->data.n_Qrows - tmqr->Qrows_retired;
          NMinf = XRow_Num/tm_info.nrowminf;
          MFCtr_start = tmqr->MFCtr_start + NMinf;
          Row_Num_start = XRow_Num % tm_info.nrowminf;
          switch ( output_tm_type ) {
            case TMTYPE_DATA_T1: break;
            case TMTYPE_DATA_T2:
              ocb->part.hdr.s.u.dhdr.mfctr = MFCtr_start;
              ocb->part.hdr.s.u.dhdr.rownum = Row_Num_start;
              break;
            case TMTYPE_DATA_T3:
              ocb->part.hdr.s.u.dhdr.mfctr = MFCtr_start;
              break;
            default:
              msg(4,"Invalid output_tm_type" );
          }
          //SETIOV( &ocb->iov[0], &ocb->part.hdr.s.hdr, nbDataHdr );
          ocb->iov[0].iov_base = &ocb->part.hdr.s.hdr;
          ocb->iov[0].iov_len  = nbDataHdr;
          Qrow_start = tmqr->Qrow + ocb->data.n_Qrows -
                          tmqr->Qrows_retired;
          if ( Qrow_start > total_Qrows )
            Qrow_start -= total_Qrows;
          nQ1 = nQrows_ready;
          nQ2 = Qrow_start + nQ1 - total_Qrows;
          if ( nQ2 > 0 ) {
            nQ1 -= nQ2;
            // SETIOV( &ocb->iov[2], row[0], nQ2 * nbQrow );
            ocb->iov[2].iov_base = row[0];
            ocb->iov[2].iov_len  = nQ2 * nbQrow;
            n_iov = 3;
          } else n_iov = 2;
          // SETIOV( &ocb->iov[1], row[Qrow_start],
                      // nQ1 * nbQrow );
          ocb->iov[1].iov_base = row[Qrow_start];
          ocb->iov[1].iov_len  = nQ1 * nbQrow;
          ocb->data.n_Qrows += nQrows_ready;
          do_read_reply( ocb,
            nbDataHdr + nQrows_ready * nbQrow,
            ocb->iov, n_iov );
        }
        break; // out of while(tmqr)
      } else if ( tmqr->next_tmqr ) {
        bool do_TS = tmqr->tsp != tmqr->next_tmqr->tsp;
        tmqr = tmqr->dereference(true);
        nl_assert(tmqr);
        ocb->data.tmqr = tmqr;
        ocb->data.tsp = tmqr->tsp;
        ocb->data.n_Qrows = 0;
        if ( do_TS ) {
          ocb->part.hdr.s.hdr.tm_id = TMHDR_WORD;
          ocb->part.hdr.s.hdr.tm_type = TMTYPE_TSTAMP;
          // SETIOV( &ocb->iov[0], &ocb->part.hdr.s.hdr, sizeof(tm_hdr_t) );
          ocb->iov[0].iov_base = &ocb->part.hdr.s.hdr;
          ocb->iov[0].iov_len  = sizeof(tm_hdr_t);
          //SETIOV( &ocb->iov[1], &tmqr->TSq->TS, sizeof(tstamp_t) );
          ocb->iov[1].iov_base = &tmqr->tsp->TS;
          ocb->iov[1].iov_len  = sizeof(tstamp_t);
          do_read_reply( ocb, sizeof(tm_hdr_t)+sizeof(tstamp_t),
            ocb->iov, 2 );
          break;
        } // else loop through again
      } else {
        // enqueue_read(ocb);
        break;
      }
    }
    unlock();
  }
}

void bfr_input_client::do_read_reply( bfr_output_client *ocb, int nb,
                        struct iovec *iov, int n_parts ) {
  nl_assert(ocb->obuf_empty());
  ocb->iwritev(iov, n_parts);
}


void bfr_input_client::run_write_queue() {
  if ( blocked_writer ) {
    // log_event(3);
    int new_rows = (this->*data_state_eval)();
    if ( bufsize > 0 ) {
      blocked_writer = false;
      flags |= Fl_Read;
      // log_event(4);
      // do_write(blocked_writer, 0, new_rows);
    }
  }
}

bool bfr_output_client::iwritten(int ntr) {
  if (obuf_empty()) read.ready = true;
  return false;
}

bfr_output_client::bfr_output_client(Authenticator *Auth, const char *iname, bool is_fast)
    : Serverside_client(Auth, iname, bfr_output_client_ibufsize), is_fast(is_fast) {
  data.tmqr = 0;
  data.n_Qrows = 0;
  state = TM_STATE_HDR;
  part.nbdata = 0;
  part.dptr = 0;
  read.buf = 0;
  read.maxQrows = 1; // We need to figure out a better solution here.
  read.rows_missing = 0;
  read.ready = true;
  all_readers.push_back(this);
}

bfr_output_client::~bfr_output_client() {
  if (data.tmqr)
    data.tmqr = data.tmqr->dereference(false);
  all_readers.remove(this);
}

Serverside_client *new_bfr_input_client(Authenticator *Auth, SubService *SS) {
  bool blocking = (SS->name == "tm_bfr/input");
  return new bfr_input_client(Auth, Auth->get_client_app(), blocking);
}

Serverside_client *new_bfr_output_client(Authenticator *Auth, SubService *SS) {
  bool is_fast = (SS->name == "tm_bfr/fast");
  return new bfr_output_client(Auth, Auth->get_client_app(), is_fast);
}

void add_subservices(Server *S) {
  S->add_subservice(new SubService("tm_bfr/input", new_bfr_input_client,
      (void *)(0), bfr_input_client::auth_hook));
  S->add_subservice(new SubService("tm_bfr/input-nb", new_bfr_input_client,
      (void *)(0), bfr_input_client::auth_hook));
  S->add_subservice(new SubService("tm_bfr/optimized", new_bfr_output_client, (void *)(0)));
  S->add_subservice(new SubService("tm_bfr/fast", new_bfr_output_client, (void *)(0)));
}

/* Main method */
int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  setup_rundir();
  
  Server S("tm_bfr");
  add_subservices(&S);
  msg(0, "%s %s Starting", AppID.fullname, AppID.rev);
  S.Start(Server::server_type);
  msg(0, "Terminating");
  return 0;
}
