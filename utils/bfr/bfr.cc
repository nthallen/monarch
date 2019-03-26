/** @file bfr.cc
 *  Telemetry Buffer
 *  est. 25 March 2019
 *  ported from ARP-DAS
 */

#include <list>
#include "rundir.h"
#include "bfr.h"
#include "oui.h"
#include "nl.h"
#include "dasio/msg.h"

using namespace DAS_IO;

AppID_t DAS_IO::AppID("bfr", "bfr server", "V1.0");

bool bfr_input_client::tmg_opened = false;
bfr_input_client *blocked_writer;
std::list<bfr_output_client*> all_readers;

int min_reader( dq_descriptor_t *dqd ) {
  if ( dqd != DQD_Queue.first ) return 0;
  int min = dqd->Qrows_expired + dqd->n_Qrows;
  for ( ocb = all_readers; ocb != 0; ocb = ocb->next_ocb ) {
    if ( ocb->data.dqd == dqd && ocb->data.n_Qrows < min )
      min = ocb->data.n_Qrows;
  }
  return min;
}

bool bfr_input_client::auth_hook(Authenticator *Auth, SubService *SS) {
  // should lock the tm_queue here:
  if (tmg_opened) return false;
  tmg_opened = true;
  return true;
}

bfr_input_client::bfr_input_client(Authenticator *Auth, const char *iname, bool blocking)
    : Serverside_client(Auth, iname, bfr_input_client_ibufsize), blocking(blocking) {
  data.dqd = 0;
  data.n_Qrows = 0;
  state = TM_STATE_HDR;
  part.nbdata = sizeof(part.hdr);
  part.dptr = (char *)&part.hdr;
  write.buf = 0;
  write.nbrow_rec = 0;
  write.nbhdr_rec = 0;
  write.nb_msg = 0;
  write.off_msg = 0;
  write.nb_rec = 0;
  write.off_queue = 0;
}

bfr_input_client::~bfr_input_client() {}

bool bfr_input_client::protocol_input() {
  blocked_writer = 0;
  write.nb_msg = nc;
  
  // _IO_SET_WRITE_NBYTES( ctp, msg->i.nbytes );
  // Not necessary since we'll handle the return ourselves
  // However, that means we need to store the total message size
  // Use off_msg for total size.
  
  // We loop here as long as we have work to do. We can get out
  // if we've processed all the data in the message (nb_msg == 0)
  // or exhausted all the available space in the DQ (nbdata == 0)
  while ( write.nb_msg > 0 && part.nbdata > 0 ) {
    int nb_read;
    nb_read = write.nb_msg < part.nbdata ?
      write.nb_msg : part.nbdata;
    memcpy(part.dptr, &buf[cp], nb_read);
    part.dptr += nb_read;
    part.nbdata -= nb_read;
    write.nb_msg -= nb_read;
    write.off_msg += nb_read; // write.off_msg is maybe cp?? except it is persistent
    if ( state == TM_STATE_DATA ) {
      write.nb_rec -= nb_read;
      // write.off_rec += nb_read;
      write.off_queue += nb_read;
    }
    assert(part.nbdata >= 0);
    if ( part.nbdata == 0 ) {
      switch ( state ) {
        case TM_STATE_HDR:
          if ( part.hdr.s.hdr.tm_id != TMHDR_WORD ) {
            msg(MSG_FATAL, "Invalid Message header" );
            // MsgError( write.rcvid, EINVAL );
            // Scan ahead for TMHDR_WORD
            part.nbdata = sizeof( part.hdr );
            part.dptr = (char *)&part.hdr;
            return;
          }
          switch ( part.hdr.s.hdr.tm_type ) {
            case TMTYPE_INIT:
              if ( DQD_Queue.last )
                msg(MSG_FATAL, "Second TMTYPE_INIT received" );
              write.off_queue = sizeof(tm_hdrs_t)-sizeof(tm_hdr_t);
              part.nbdata = sizeof(tm_info) - write.off_queue;
              part.dptr = (char *)&tm_info;
              memcpy( part.dptr, &part.hdr.raw[sizeof(tm_hdr_t)],
                      write.off_queue );
              part.dptr += write.off_queue;
              state = TM_STATE_INFO;
              break;
            case TMTYPE_TSTAMP:
              if ( DQD_Queue.last == 0 )
                msg(MSG_FATAL, "TMTYPE_TSTAMP received before _INIT" );
              lock_dq();
              queue_tstamp( &part.hdr.s.u.ts );
              unlock_dq();
              new_rows++;
              // state = TM_STATE_HDR; // already there!
              part.nbdata = sizeof( part.hdr );
              part.dptr = (char *)&part.hdr;
              break;
            case TMTYPE_DATA_T1:
            case TMTYPE_DATA_T2:
            case TMTYPE_DATA_T3:
            case TMTYPE_DATA_T4:
              if ( DQD_Queue.last == 0 )
                msg(MSG_FATAL, "Second TMTYPE_DATA* received before _INIT" );
              assert( data_state_eval != 0 );
              assert( part.hdr.s.hdr.tm_type == Data_Queue.output_tm_type );
              write.nb_rec = part.hdr.s.u.dhdr.n_rows *
                write.nbrow_rec;
              write.off_queue = 0;
              new_rows += data_state_eval(ocb, nonblock);
              // ### Make sure data_state_eval returns the number
              // of rows that have been completely added to DQ
              if ( write.nb_rec <= 0 ) {
                state = TM_STATE_HDR;
                part.nbdata = sizeof(part.hdr);
                part.dptr = (char *)&part.hdr;
              } // else break out
              break;
            default:
              msg( 4, "Invalid state" );
          }
          break;
        case TM_STATE_INFO:
          // ### Check return value
          process_tm_info(ocb);
          Data_Queue.nonblocking = 1; // nonblock;
          new_rows++;
          state = TM_STATE_HDR; //### Use state-init function?
          part.nbdata = sizeof(part.hdr);
          part.dptr = (char *)&part.hdr;
          break;
        case TM_STATE_DATA:
          new_rows += data_state_eval(ocb, nonblock);
          if ( write.nb_rec <= 0 ) {
            state = TM_STATE_HDR;
            part.nbdata = sizeof(part.hdr);
            part.dptr = (char *)&part.hdr;
          }
          break;
      }
    }
  }
  if ( write.nb_msg == 0 ) {
    // MsgReply( write.rcvid, write.off_msg, 0, 0 );
    if ( new_rows ) run_read_queue();
    //### Mark us as not blocked: maybe that's nbdata != 0?
  } else {
    // We must have nbdata == 0 meaning we're going to block
    assert(blocking);
    blocked_writer = this;
    run_read_queue();
  }
}

bfr_output_client::bfr_output_client(Authenticator *Auth, const char *iname, bool is_fast)
    : Serverside_client(Auth, iname, bfr_output_client_ibufsize), is_fast(is_fast) {
  data.dqd = 0;
  data.n_Qrows = 0;
  state = TM_STATE_HDR;
  part.nbdata = 0;
  part.dptr = 0;
  read.buf = 0;
  read.nbyte = 0;
  read.maxQrows = 0;
  read.rows_missing = 0;
  all_readers.push_back(this);
}

bfr_output_client::~bfr_output_client() {
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
  S.Start(Server::Srv_Unix);
  return 0;
}