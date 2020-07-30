/** @file tm_rcvr.cc 
 *  To abstract some functionality from tm_client and rdr, among others.
 *  @date 2019-04-26
 */

#include <string.h>
#include "dasio/tm_rcvr.h"
#include "nl.h"

namespace DAS_IO {
  
  /* Use currently ambiguous. */
  unsigned int tm_rcvr::next_minor_frame;
  unsigned int tm_rcvr::minf_row;
  unsigned int tm_rcvr::majf_row;

  /* Constructor method */
  tm_rcvr::tm_rcvr(Interface* interface) : interface(interface) {
    ncc = cp = 0;
    tm_info_ready = false;
    interface->set_binary_mode();
    tm_expect_hdr();
  }

  tm_rcvr::~tm_rcvr() {}

  void tm_rcvr::load_tmdac(char *path) {
    ::load_tmdac(path);
    init_tm_type();
  }

  void tm_rcvr::process_message() {
    ncc = interface->nc - cp;
    while ( ncc >= toread ) {
      switch ( tm_state ) {
        case TM_STATE_HDR:
          if (tm_msg->hdr.tm_id != TMHDR_WORD) {
            seek_tmid();
            continue;
          }
          switch ( tm_msg->hdr.tm_type ) {
            case TMTYPE_INIT:
              if ( tm_info_ready )
                msg(MSG_FATAL, "%sReceived redundant TMTYPE_INIT", context());
              toread += sizeof(tm_info);
              tm_state = TM_STATE_INIT;
              break;
            case TMTYPE_TSTAMP:
              if ( !tm_info_ready )
                msg( MSG_FATAL, "%sExpected TMTYPE_INIT, received TMTYPE_TSTAMP", context());
              toread += sizeof(tstamp_t);
              tm_state = TM_STATE_TSTAMP;
              break;
            case TMTYPE_DATA_T1:
            case TMTYPE_DATA_T2:
            case TMTYPE_DATA_T3:
            case TMTYPE_DATA_T4:
              if ( !tm_info_ready )
                msg(MSG_FATAL, "%sExpected TMTYPE_INIT, received TMTYPE_DATA_Tn",
                  context());
              if ( tm_msg->hdr.tm_type != input_tm_type )
                msg(MSG_FATAL, "%sInvalid data type: %04X", context(),
                  tm_msg->hdr.tm_type );
              toread = nbDataHdr;
              tm_state = TM_STATE_DATA_HDR;
              break;
            default:
              msg(MSG_ERROR, "%sInvalid TMTYPE: %04X", context(),
                tm_msg->hdr.tm_type );
              seek_tmid();
              return;
          }
          break;
        case TM_STATE_INIT:
          process_init();
          cp += toread;
          ncc -= toread;
          tm_expect_hdr();
          break;
        case TM_STATE_TSTAMP:
          process_tstamp();
          cp += toread;
          ncc -= toread;
          tm_expect_hdr();
          break;
        case TM_STATE_DATA_HDR:
          buf_mfctr = tm_msg->body.data3.mfctr;
          cp += toread;
          ncc -= toread;
          rows_left_in_msg = tm_msg->body.data1.n_rows;
          toread = nbQrow;
          tm_state = TM_STATE_DATA;
          break;
        case TM_STATE_DATA:
          rows_in_buf = ncc / nbQrow;
          if (rows_left_in_msg < rows_in_buf)
            rows_in_buf = rows_left_in_msg;
          data_row = &interface->buf[cp];
          // Will process rows_in_buf
          { unsigned int rows_processed = process_data();
            buf_mfctr += rows_processed;
            rows_in_buf -= rows_processed;
            rows_left_in_msg -= rows_processed;
            cp += rows_processed * nbQrow;
            ncc -= rows_processed * nbQrow;
          }
          if (rows_left_in_msg == 0) {
            tm_expect_hdr();
          }
          break;
        default:
          msg(MSG_EXIT_ABNORM, "%sInvalid tm_state %d", context(), tm_state);
      }
    }
    if (cp > 0 && toread > interface->bufsize - cp) {
      interface->consume(cp); 
      cp = 0;
      tm_msg = (tm_msg_t *)&interface->buf[cp];
      ncc = interface->nc - cp;
    }
    if ( toread > interface->bufsize )
      msg( MSG_FATAL, "%sRecord size %d exceeds allocated buffer size %d",
        context(), toread, interface->bufsize );
  }

  void tm_rcvr::process_init() {
    if ( memcmp( &tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t) ) )
      msg(MSG_FATAL, "tm_dac differs");
    tm_info.nrowminf = tm_msg->body.init.nrowminf;
    tm_info.max_rows = tm_msg->body.init.max_rows;
    tm_info.t_stmp = tm_msg->body.init.t_stmp;
    init_tm_type();
  }

  /* *
   * Internal function to establish input_tm_type.
   */
  void tm_rcvr::init_tm_type() {
    if ( tmi(mfc_lsb) == 0 && tmi(mfc_msb) == 1
         && tm_info.nrowminf == 1 ) {
      input_tm_type = TMTYPE_DATA_T3;
      nbQrow = tmi(nbrow) - 4;
      nbDataHdr = 8;
    } else if ( tm_info.nrowminf == 1 ) {
      input_tm_type = TMTYPE_DATA_T1;
      nbQrow = tmi(nbrow);
      nbDataHdr = 6;
    } else {
      input_tm_type = TMTYPE_DATA_T2;
      nbQrow = tmi(nbrow);
      nbDataHdr = 10;
    }
    tm_info_ready = true;
  }

  void tm_rcvr::process_tstamp() {
    tm_info.t_stmp = tm_msg->body.ts;
  }

  void tm_rcvr::seek_tmid() {
    tm_hdrw_t *tm_id;
    unsigned char *ubuf = (unsigned char *)interface->buf;
    int i;
    for (i = cp+1; i < interface->nc; ++i) {
      if (ubuf[i] == (TMHDR_WORD & 0xFF)) {
        if (i+1 == interface->nc ||
            ubuf[i+1] == ((TMHDR_WORD>>8)&0xFF)) {
          msg(MSG_WARN, "%sDiscarding %d bytes in seek_tmid()", context(), i-cp);
          interface->consume(i);
          cp = 0;
          tm_expect_hdr();
          ncc = interface->nc - cp;
          return;
        }
      }
    }
    msg(MSG_WARN, "%sDiscarding %d bytes (to EOB) in seek_tmid()",
      context(), interface->nc - cp);
    interface->consume(interface->nc);
    tm_expect_hdr();
    tm_msg = (tm_msg_t*)interface->buf;
    ncc = interface->nc - cp;
  }

  void tm_rcvr::tm_expect_hdr() {
    tm_state = TM_STATE_HDR;
    toread = sizeof(tm_hdr_t);
    tm_msg = (tm_msg_t*)&interface->buf[cp];
  }

  const char *tm_rcvr::context() {
    return "";
  }
}
