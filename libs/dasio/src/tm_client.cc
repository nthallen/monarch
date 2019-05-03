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
  else msg(MSG_ERROR,"Unable to create run file '%s'", filename);
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
