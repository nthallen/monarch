#include <string>
#include <string.h>
#include <unistd.h>
#include "monarchctl.h"
#include "oui.h"
#include "nl.h"

bool opt_Q = false;
bool opt_S = false;
bool opt_r = false;
const char *restart_script = 0;
const char *flight_host = 0;
const char *gse_host = 0;
bool script_delivered = false;

void monarchctl_init_options(int argc, char **argv) {
  int optltr;

  optind = OPTIND_RESET;
  opterr = 0;
  int nqrs = 0;
  while ((optltr = getopt(argc, argv, opt_string)) != -1) {
    switch (optltr) {
      case 'Q': ++nqrs; opt_Q = true; break;
      case 'r': ++nqrs; opt_r = true; break;
      case 'R': ++nqrs; restart_script = optarg; break;
      case 'S': ++nqrs; opt_S = true; break;
      case 't': flight_host = optarg; break;
      case 'G': gse_host = optarg; break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
      default:
        break;
    }
  }
  if (nqrs > 1) msg(MSG_FATAL, "Only one of options -Q, -r, -R and -S may be selected");
  if (nqrs && gse_host) msg(MSG_FATAL, "-G cannot be combined with options -Q, -r, -R or -S");
  if ((!nqrs) && (!gse_host)) msg(MSG_FATAL, "Must specify one of options -Q, -r, -R, -S or -G");
}

/**
 * Contact the monarchctl service on gse_host to request a script name.
 * We will setup our own Loop.
 */
void query_gse() {
  monarchctlclt_t *clt = new monarchctlclt_t();
  DAS_IO::Loop ELoop;
  ELoop.add_child(clt);
  clt->connect();
  ELoop.event_loop();
  clt->close();
}

monarchctl_t::monarchctl_t(Server *srvr)
  : Client("parent", 80, flight_host, "parent", 0),
    srvr(srvr),
    waiting_for_parent(false) {
  conn_fail_reported = true;
  set_retries(-1, 2, 2);
}

bool monarchctl_t::app_connected() {
  if (opt_Q) {
    msg(0, "Requesting forced shutdown");
    return iwrite("Q\n");
  }
  if (opt_r) {
    msg(0, "Requesting default startup");
    return iwrite("r\n");
  }
  if (restart_script) {
    msg(0, "Requesting startup with script %s", restart_script);
    std::string rs("R");
    rs += restart_script;
    return iwrite(rs);
  }
  if (opt_S) return iwrite("S\n");
  msg(MSG_FATAL, "Expected option Q, r, R or S in app_connected");
  return false; // Never reached
}

bool monarchctl_t::app_input() {
  if (opt_S) {
    // just display the text.
    msg(0, "%s", &buf[0]);
  } else {
    // Check for OK response, and then shutdown
    if (strncasecmp((const char *)(&buf[0]), "OK", 2) != 0) {
      msg(2, "%s", &buf[0]);
    } else {
      msg(0, "Request acknowledged");
    }
  }
  report_ok(nc);
  if (srvr)
    srvr->Shutdown(true);
  return true;
}

bool monarchctl_t::connect_failed() {
  if (!waiting_for_parent) {
    msg(0, "Waiting for parent");
    waiting_for_parent = true;
  }
  return false;
}

/**
 * @brief the Serverside_Client socket
 */
monarchctl_ssclient::monarchctl_ssclient(Authenticator *Auth, const char *iname)
    : Serverside_client(Auth, iname, monarchctl_ssclient_ibufsize) {}

monarchctl_ssclient::~monarchctl_ssclient() {}

bool monarchctl_ssclient::connected() {
  if (restart_script == 0)
    restart_script = "/dev/null";
  msg(0, "Answering server request with script '%s'", restart_script);
  if (!iwrite(restart_script))
    script_delivered = true;
  close();
  srvr->Shutdown(true);
  return false;
}

Serverside_client *new_monarchctl_ssclient(Authenticator *Auth, SubService *SS) {
  SS = SS; // No need for this
  return new monarchctl_ssclient(Auth, Auth->get_client_app());
}


// dasctrlclt_t is the client that talks to a monarchctl server
monarchctlclt_t::monarchctlclt_t()
    : Client("monarchctl", 80, gse_host[0] ? gse_host : 0, "monarchctl", 0) {
  conn_fail_reported = true;
}

bool monarchctlclt_t::app_input() {
  fprintf(stdout, "%s", &buf[0]);
  report_ok(nc);
  return true;
}

bool monarchctlclt_t::connect_failed() {
  msg(MSG_DEBUG, "Unable to connect to monarchctl server");
  exit(0);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (gse_host) query_gse();
  else {
    Server S("monarchctl");
    monarchctl_t *monarchctl = new monarchctl_t(&S);
    S.ELoop.add_child(monarchctl);
    monarchctl->connect();
    if (opt_S) {
      S.ELoop.event_loop();
      S.ELoop.delete_children();
    } else {
      S.add_subservice(new SubService("monarchctl",
	new_monarchctl_ssclient, (void *)0));
      S.Start(flight_host ? Server::Srv_TCP : Server::Srv_Unix);
    }
  }
  return 0;
}
