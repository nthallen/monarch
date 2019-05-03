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
    tm_expect_hdr();
    tm_info_ready = false;
    tm_msg = (tm_msg_t *)interface->buf;
  }

  tm_rcvr::~tm_rcvr() {}

  void tm_rcvr::load_tmdac(char *path) {
    ::load_tmdac(path);
    init_tm_type();
  }

  void tm_rcvr::process_message() {
    nc = interface->nc;
    if ( nc >= toread ) {
      if (tm_msg->hdr.tm_id != TMHDR_WORD) {
        seek_tmid();
      }
    }
    while ( nc >= toread ) {
      switch ( tm_state ) {
        case TM_STATE_HDR:
          switch ( tm_msg->hdr.tm_type ) {
            case TMTYPE_INIT:
              if ( tm_info_ready )
                msg(MSG_FATAL, "%sReceived redundant TMTYPE_INIT", context());
              toread += sizeof(tm_info);
              break;
            case TMTYPE_TSTAMP:
              if ( !tm_info_ready )
                msg( MSG_FATAL, "%sExpected TMTYPE_INIT, received TMTYPE_TSTAMP", context());
              toread += sizeof(tstamp_t);
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
              toread = nbDataHdr + nbQrow * tm_msg->body.data1.n_rows;
              break;
            default:
              msg(MSG_ERROR, "%sInvalid TMTYPE: %04X", context(),
                tm_msg->hdr.tm_type );
              seek_tmid();
              return;
          }
          tm_state = TM_STATE_DATA;
          if ( toread > interface->bufsize )
            msg( MSG_FATAL, "%sRecord size %d exceeds allocated buffer size %d",
              context(), toread, interface->bufsize );
          break;
        case TM_STATE_DATA:
          switch ( tm_msg->hdr.tm_type ) {
            case TMTYPE_INIT:
              process_init();
              break;
            case TMTYPE_TSTAMP:
              process_tstamp();
              break;
            case TMTYPE_DATA_T1:
            case TMTYPE_DATA_T2:
            case TMTYPE_DATA_T3:
            case TMTYPE_DATA_T4:
              process_data();
              break;
          }
          if ( nc > toread ) {
            interface->consume(toread);
          } else if ( nc == toread ) {
            interface->consume(nc);
          }
          tm_expect_hdr();
          break;
        default: msg(MSG_EXIT_ABNORM, "%sInvalid tm_state %d", context(), tm_state);
      }
    }
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
    for (i = 1; i < nc; ++i) {
      if (ubuf[i] == (TMHDR_WORD & 0xFF)) {
        if (i+1 == nc || ubuf[i+1] == ((TMHDR_WORD>>8)&0xFF)) {
          msg(MSG_WARN, "%sDiscarding %d bytes in seek_tmid()", context(), i);
          interface->consume(i);
          tm_expect_hdr();
          return;
        }
      }
    }
    msg(MSG_WARN, "%sDiscarding %d bytes (to EOB) in seek_tmid()",
      context(), nc);
    interface->consume(nc);
    tm_expect_hdr();
  }

  void tm_rcvr::tm_expect_hdr() {
    tm_state = TM_STATE_HDR;
    toread = sizeof(tm_hdr_t);
  }

  const char *tm_rcvr::context() {
    return "";
  }
}
