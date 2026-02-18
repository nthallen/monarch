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
#include "dasio/quit.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {

char *tm_client::srcnode = NULL;
bool tm_client::opt_Q = false;

void tm_set_srcnode(char *nodename) {
  tm_client::srcnode = nodename;
}

/**
 * Constructor method.
 */
tm_client::tm_client(int bufsize, bool fast) 
  : DAS_IO::Client("tm_client", "bfr", "tm_bfr",
        (fast ? "fast" : "optimized"), bufsize),
    tm_rcvr(this)
{
  nl_assert(buf);
}

void tm_client::adopted() {
  if (opt_Q) {
    Quit *Q = new Quit(0, 0, "Qsrvr");
    ELoop->add_child(Q);
    Q->connect();
  }
}

/**
 * Added 2019 April 3
 * This function creates the PID file.
 */
static char *pidfilename = 0;

void tm_client_delete_pid_file() {
  if (pidfilename) {
    unlink(pidfilename);
    nl_free_memory(pidfilename);
    pidfilename = 0;
  }
}

bool tm_client::app_connected() {
  int nb1, nb2;
  FILE *fp;
  const char *Exp = getenv("Experiment");
  if (Exp == NULL) Exp = "none";
  nb1 = snprintf(NULL, 0, "%s/%s/%d", RUNDIR_TMC, Exp, getpid());
  pidfilename = (char *)new_memory(nb1+1);
  nb2 = snprintf(pidfilename, nb1+1, "%s/%s/%d", RUNDIR_TMC, Exp, getpid());
  nl_assert(nb1 == nb2);
  fp = fopen( pidfilename, "w" );
  if (fp) fclose(fp);
  else msg(MSG_ERROR,"Unable to create run file '%s'", pidfilename);
  atexit(&tm_client_delete_pid_file);
  return false;
}

bool tm_client::process_eof() {
  // tm_quit = true;
  return true;
}

/** 
 *  Edited 2019 March 7 for monarch
 */
bool tm_client::app_input() {
  process_message();
  return false;
}

}
