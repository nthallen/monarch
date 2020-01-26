/* getcon utility.
   Similar to the QNX4 utility of the same name, the
   purpose of getcon is to hold a console open until
   a display program is launched on it. This version
   will also report the console's ttyname in order to
   facilitate the subsequent launch.

   getcon <windowname> <pid>

   creates pty.<windowname>.<pid>.tmp
   invokes the ttyname() function and writes the result
   to the file.
   closes the file and renames it to pty.<windowname>.<pid>
   Listens on the "quit" channel for the signal to
   shutdown. Also listens for SIGHUP and SIGINT.
*/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include "getcon.h"
#include "nl.h"
#include "oui.h"
#include "nl_assert.h"

using namespace DAS_IO;

static char *winname, *pid;
static bool has_pid = false;
bool opt_end_session = false;
const char *command_node = 0;

static void wait_for_quit(void) {
  Cmd_reader *CR = new getcon_cmd();
  Loop ELoop;
  CR->connect();
  ELoop.add_child(CR);
  CR->signal(SIGCHLD);
  CR->signal(SIGINT);
  CR->signal(SIGHUP);
  ELoop.event_loop();
}

static void end_session() {
  if (cic_init()) {
    msg(MSG_ERROR, "Unable to connect to command server");
  } else {
    int rv = ci_sendfcmd(Cmd_Send, "getcon end session %s\n", pid);
    if (rv) {
      msg(MSG_ERROR, "Command server returned error %d", rv);
    }
  }
}

getcon_cmd::getcon_cmd()
    : Cmd_reader("cmd_getcon", 80, pid ? "getcon" : "Quit"),
      tried_quit(pid == 0) {
  set_retries(-1, 4, 60);
  conn_fail_reported = true;
}

/**
 * Handle EOF on the command server connection. We expect this
 * to occur if there is no getcon %INTERFACE on the command
 * server, in which case we wish to fall back to using the
 * Quit %INTERFACE.
 *
 * This will also occur on a full Quit, in which case, we
 * should terminate
 */
bool getcon_cmd::app_process_eof() {
  return true;
}

bool getcon_cmd::app_negotiation_failed() {
  if (!tried_quit) { 
    set_subservice("Quit");
    connect();
    tried_quit = true;
  } else {
    msg(2, "%s: No quit channel at command server!", iname);
  }
  return false;
}

/**
 * Handle the case where we are unable to reach the command server
 * at all. In this case, we will just wait for a signal.
 */
bool getcon_cmd::connect_failed() {
  msg(MSG_DEBUG, "%s: No server found", iname);
  return false;
}

/**
 * Process response from the command interface. We expect either
 */
bool getcon_cmd::app_input() {
  bool rv = true;
  if (pid != 0) {
    int pidlen = strlen(pid);
    rv = nc == pidlen+1 &&
          strncmp((const char *)buf, pid, pidlen) == 0 &&
          buf[pidlen] == '\n';
  } else rv = true;
  report_ok(nc);
  return rv;
}

void getcon_args( char *arg ) {
  nl_assert(arg != NULL);
  if ( winname == NULL && !opt_end_session ) {
    winname = arg;
  } else if ( pid == NULL ) {
    has_pid = true;
    pid = arg;
  } else msg( 3, "Too many arguments" );
}

int main( int argc, char **argv ) {
  char fname1[PATH_MAX], fname2[PATH_MAX];
  char *tty;
  FILE *fp;

  oui_init_options( argc, argv );
  if ( winname == NULL )
    msg( 3, "Must specify a window name" );
  if ( has_pid ) {
    snprintf( fname1, PATH_MAX, "pty.%s.%s.tmp", winname, pid );
    snprintf( fname2, PATH_MAX, "pty.%s.%s", winname, pid );
  } else {
    snprintf( fname1, PATH_MAX, "pty.%s.tmp", winname );
    snprintf( fname2, PATH_MAX, "pty.%s", winname );
  }
  tty = ttyname( STDOUT_FILENO );
  if (tty == NULL)
    msg( 3, "ttyname(1) returned error %d", errno );
  fp = fopen( fname1, "w" );
  if ( fp == NULL )
    msg( 3, "Unable to write to %s", fname1 );
  fprintf( fp, "%s\n", tty );
  fclose( fp );
  if ( rename( fname1, fname2 ) != 0 )
    msg( 3, "rename returned error %d", errno );
  if (opt_end_session) {
    end_session();
  } else {
    wait_for_quit();
  }
  return 0;
}

