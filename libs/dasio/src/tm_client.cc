/** \file tm_client.cc
 * TM Client Clases
 */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
// #include <process.h>
#include "dasio/tm_client.h"
#include "dasio/msg.h"
#include "dasio/tm.h"
#include "dasio/rundir.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {

unsigned int tm_client::next_minor_frame;
unsigned int tm_client::minf_row;
unsigned int tm_client::majf_row;
char *tm_client::srcnode = NULL;

void tm_set_srcnode(char *nodename) {
  tm_client::srcnode = nodename;
}

/**
 * Constructor method.
 */
tm_client::tm_client(int bufsize, bool fast) 
  : DAS_IO::Client("tm_client", bufsize, "tm_bfr", (fast ? "fast" : "optimized")) {
    nl_assert(buf);
    nc = 0;
    next_minor_frame = 0;
    majf_row = 0;
    minf_row = 0;
    tm_expect_hdr();
    tm_info_ready = false;
    tm_quit = false;
    tm_msg = (tm_msg_t *)buf;
  }

tm_client::~tm_client() {}

/**
 * Added 2019 April 3
 * This function creates the PID file.
 */
bool tm_client::app_connected() {
  int nb1, nb2;
  char *filename;
  FILE *fp;
  const char *Exp = getenv("Experiment");
  if (Exp == NULL) Exp = "none";
  nb1 = snprintf(NULL, 0, "%s/%s/%d", RUNDIR_TMC, Exp, getpid());
  filename = (char *)new_memory(nb1+1);
  nb2 = snprintf(filename, nb1+1, "%s/%s/%d", RUNDIR_TMC, Exp, getpid());
  nl_assert(nb1 == nb2);
  fp = fopen( filename, "w" );
  if (fp) fclose(fp);
  else msg(2,"Unable to create run file '%s'", filename);
  return false;
}

bool tm_client::process_eof() {
  tm_quit = true;
  return true;
}

/** 
 *  Edited 2019 March 7 for le-dasng
 */
bool tm_client::app_input() {
  if (tm_quit) return true;
  /* int nb;
  do {
    nb = (bfr_fd == -1) ? 0 :
        ::read( bfr_fd, buf + nc, bufsize-nc);
    if ( nb == -1 ) {
      if ( errno == EAGAIN ) return; // must be non-blocking
      else report_err( 1, "tm_client::read error from read(): %s",
        strerror(errno));
    }
    if (nb <= 0) {
      nc = 0;
      tm_expect_hdr();
      // toread = sizeof(tm_hdr_t);
      if ( process_eof() ) return;
    }
    if ( tm_quit ) return; // possible if set from an outside command
  } while (nb == 0 );
  nc += nb; */
  if ( nc >= toread ) {
    if (tm_msg->hdr.tm_id != TMHDR_WORD) {
      seek_tmid();
    } else {
      process_message();
    }
  }
  return false;
}

/* *
 * Internal function to establish input_tm_type.
 */
void tm_client::init_tm_type() {
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

void tm_client::process_init() {
  if ( memcmp( &tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t) ) )
    report_err(/*3, */"tm_dac differs");
  tm_info.nrowminf = tm_msg->body.init.nrowminf;
  tm_info.max_rows = tm_msg->body.init.max_rows;
  tm_info.t_stmp = tm_msg->body.init.t_stmp;
  init_tm_type();
}

void tm_client::process_tstamp() {
  tm_info.t_stmp = tm_msg->body.ts;
}

const char *tm_client::context() {
  return "";
}

void tm_client::tm_expect_hdr() {
  tm_state = TM_STATE_HDR;
  toread = sizeof(tm_hdr_t);
}

void tm_client::seek_tmid() {
  tm_hdrw_t *tm_id;
  unsigned char *ubuf = (unsigned char *)buf;
  int i;
  for (i = 1; i < nc; ++i) {
    if (ubuf[i] == (TMHDR_WORD & 0xFF)) {
      if (i+1 == nc || ubuf[i+1] == ((TMHDR_WORD>>8)&0xFF)) {
        msg(1, "%sDiscarding %d bytes in seek_tmid()", context(), i);
        memmove(buf, buf+i, nc - i);
        nc -= i;
        tm_expect_hdr();
        return;
      }
    }
  }
  msg(1, "%sDiscarding %d bytes (to EOB) in seek_tmid()",
    context(), nc);
  nc = 0;
  tm_expect_hdr();
}
  
void tm_client::process_message() {
  while ( nc >= toread ) {
    switch ( tm_state ) {
      case TM_STATE_HDR:
        switch ( tm_msg->hdr.tm_type ) {
          case TMTYPE_INIT:
            if ( tm_info_ready )
              msg(3, "%sReceived redundant TMTYPE_INIT", context());
            toread += sizeof(tm_info);
            break;
          case TMTYPE_TSTAMP:
            if ( !tm_info_ready )
              msg( 3, "%sExpected TMTYPE_INIT, received TMTYPE_TSTAMP", context());
            toread += sizeof(tstamp_t);
            break;
          case TMTYPE_DATA_T1:
          case TMTYPE_DATA_T2:
          case TMTYPE_DATA_T3:
          case TMTYPE_DATA_T4:
            if ( !tm_info_ready )
              msg(3, "%sExpected TMTYPE_INIT, received TMTYPE_DATA_Tn",
                context());
            if ( tm_msg->hdr.tm_type != input_tm_type )
              msg(3, "%sInvalid data type: %04X", context(),
                tm_msg->hdr.tm_type );
            toread = nbDataHdr + nbQrow * tm_msg->body.data1.n_rows;
            break;
          default:
            msg(2, "%sInvalid TMTYPE: %04X", context(),
              tm_msg->hdr.tm_type );
            seek_tmid();
            return;
        }
        tm_state = tm_state_DATA;
        if ( toread > bufsize )
          msg( 3, "%sRecord size %d exceeds allocated buffer size %d",
            context(), toread, bufsize );
        break;
      case tm_state_DATA:
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
          memmove(buf, buf+toread, nc - toread);
          nc -= toread;
        } else if ( nc == toread ) {
          nc = 0;
        }
        tm_expect_hdr();
        break;
      default: msg(4, "%sInvalid tm_state %d", context(), tm_state);
    }
  }
}

// void tm_client::resize_buffer( int bufsize ) {
  // delete buf;
  // bufsize = bufsize;
  // buf = new char[bufsize];
  // if ( buf == 0)
    // report_err(/* 3,
       // */"Memory allocation failure in tm_client::resize_buffer");
// }

void tm_client::load_tmdac(char *path) {
  ::load_tmdac(path);
  init_tm_type();
}

}
