/** \file tm_client.cc
 * TM Client Classes
 * @date 2019-05-03 (date gutted)
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

const char *DAS_IO::tm_client::tm_client_hostname = 0;

char *tm_client::srcnode = NULL;

void tm_set_srcnode(char *nodename) {
  tm_client::srcnode = nodename;
}

/**
 * Constructor method.
 */
tm_client::tm_client(int bufsize, bool fast, const char *hostname) 
  : DAS_IO::Client("tm_client", bufsize, hostname, "tm_bfr", (fast ? "fast" : "optimized")), tm_rcvr(this) {
    tm_client_hostname = hostname;
    nl_assert(buf);
    // nc = 0;
    // tm_quit = false;
  }

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
  // tm_quit = true;
  return true;
}

/** 
 *  Edited 2019 March 7 for le-dasng
 */
bool tm_client::app_input() {
  process_message();
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

}
