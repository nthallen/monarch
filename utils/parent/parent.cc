#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "nl.h"
#include "parent.h"
#include "oui.h"

int quit_when_childless = 0;
int parent_timeout = 0;
pid_t monitor_pid = 0;
bool have_children = true;
const char *script_file = 0;
const char *status_string = 0;

/**
 * @brief the Serverside_Client socket
 * The parent client will support a couple commands:
 * NoOp: (actually not a command, but useful simply to connect as an
 * indication that the node is up and parent is running.
 * Status: Dump useful information about what is running
 * Quit: Shutdown
 */
parent_ssclient::parent_ssclient(Authenticator *Auth, const char *iname)
    : Serverside_client(Auth, iname, parent_ssclient_ibufsize),
      shutdown_when_closed(false) {}


Serverside_client *new_parent_ssclient(Authenticator *Auth, SubService *SS) {
  SS = SS; // No need for this
  return new parent_ssclient(Auth, Auth->get_client_app());
}

void parent_ssclient::write_script_file(const char *script) {
  if (script == 0)
    script = "/dev/null";
  if (script_file != 0) {
    FILE *fp = fopen(script_file, "w");
    if (fp == 0) {
      msg(MSG_ERROR, "Cannot write to script file %s", script_file);
    } else {
      fprintf(fp, "%s\n", script);
      fclose(fp);
    }
  }
}

/**
 * @return true if shutdown is requested
 */
bool parent_ssclient::protocol_input() {
  char obuf[100];

  switch (buf[0]) {
    case 'Q': // Quit unconditionally
      write_script_file(0);
      iwrite("OK\n");
      report_ok(nc);
      break;
    case 'r': // Quit if childless
    case 'R':
      if (have_children) return iwrite("NOK: Subprocesses running, quit first\n");
      if (buf[0] == 'R') {
        write_script_file((const char *)(&buf[1]));
      }
      iwrite("OK\n");
      report_ok(nc);
      break;
    case 'S': // Request status
      if (status_string == 0)
      	status_string = "OK";
      snprintf(obuf, 100, "Status: %s: %ssubprocesses\n",
      	status_string, have_children ?
          "" : "no ");
      iwrite(obuf);
      report_ok(nc);
      return false;
    default:
      report_err("%s: Invalid command", iname);
      iwrite("NOK\n");
      consume(nc);
      return false;
  }
  // srvr->Shutdown(true);
  // return true;
  TO.Set(1,0);
  shutdown_when_closed = true;
  return false;
}

bool parent_ssclient::process_eof() {
  if (shutdown_when_closed) {
    TO.Clear();
    srvr->Shutdown(true);
    return true;
  }
  return false;
}

bool parent_ssclient::protocol_timeout() {
  if (shutdown_when_closed) {
    TO.Clear();
    msg(MSG_ERROR, "%s: Timed out waiting for socket close", iname);
    srvr->Shutdown(true);
    return true;
  }
  return false;
}

parent_sigif::parent_sigif(Server *srvr)
      : Interface("ParSig",0),
        srvr(srvr),
        handled_INT(false),
        handled_timeout(false) {
  if (monitor_pid && !parent_timeout)
    parent_timeout = 3;
  if (parent_timeout && !monitor_pid) {
    TO.Set(parent_timeout,0);
    flags |= Fl_Timeout;
  }
}

bool parent_sigif::serialized_signal_handler(uint32_t signals_seen) {
  if (saw_signal(signals_seen, SIGCHLD)) {
    while (true) {
      int status;
      pid_t pid;
      pid = waitpid( -1, &status, WNOHANG );
      switch (pid) {
        case 0:
          // msg( 0, "Still have children: none have died" );
          break;
        case -1:
          switch (errno) {
            case ECHILD:
              have_children = false;
              msg( 0, "parent: No more children");
              break;
            case EINTR:
              msg( 0, "parent: signal received during waitpid()" );
              break;
            default:
              msg( 2, "parent: Unexpected error from waitpid(): %s",
                strerror(errno));
          }
          break;
        default:
          msg( 0, "parent: Process %d terminated: status: %04X", pid, status );
          if (monitor_pid && pid == monitor_pid) {
            flags |= Fl_Timeout;
            TO.Set(parent_timeout,0);
          }
          continue; // make sure there are no more
      }
      break;
    }
  }
  if (saw_signal(signals_seen, SIGINT)) {
    handled_INT = 1;
    quit_when_childless = 1;
    if ( have_children ) {
      msg( 0, "parent: Received SIGINT, signaling children");
      killpg(getpgid(getpid()), SIGHUP);
      TO.Set(3,0);
      flags |= Fl_Timeout;
    } else {
      msg( 0, "parent: Received SIGINT");
    }
  }
  if (quit_when_childless && !have_children) {
    if (srvr)
      srvr->Shutdown(true);
  }
  return false;
}

bool parent_sigif::protocol_timeout() {
  TO.Clear();
  if ( handled_INT )
    msg( 3, "parent: Timed out waiting for children after INT");
  if ( handled_timeout )
    msg( 3, "parent: Timed out waiting for children after timeout");
  if (have_children) {
    msg( 0, "parent: Received timeout, calling killpg()");
    handled_timeout = 1;
    killpg(getpgid(getpid()), SIGHUP);
    TO.Set(3,0);
    return false;
  } else {
    msg(0, "parent: Timed out");
    return true;
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  Server S("parent");
  S.add_subservice(new SubService("parent", new_parent_ssclient, (void *)0));
  parent_sigif *psi = new parent_sigif(&S);
  S.ELoop.add_child(psi);
  psi->signal(SIGCHLD);
  psi->signal(SIGINT);
  psi->signal(SIGHUP); // Need to handle (ignore) HUP or I'll see my own
  // invoke signal handler to decide if we have children:
  psi->serialized_signal_handler(1 << (SIGCHLD-1));
  S.Start(Server::server_type);
  return 0;
}

