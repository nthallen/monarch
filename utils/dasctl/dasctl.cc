#include <string>
#include <string.h>
#include <unistd.h>
#include "dasctl.h"
#include "oui.h"
#include "nl.h"

bool opt_Q = false;
bool opt_S = false;
bool opt_r = false;
const char *restart_script = 0;
const char *flight_host = 0;
const char *gse_host = 0;
bool script_delivered = false;

void dasctl_init_options(int argc, char **argv) {
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
 * Contact the dasctl service on gse_host to request a script name.
 * We will setup our own Loop.
 */
void query_gse() {
  dasctlclt_t *clt = new dasctlclt_t();
  DAS_IO::Loop ELoop;
  ELoop.add_child(clt);
  clt->connect();
  ELoop.event_loop();
  clt->close();
}

dasctl_t::dasctl_t(Server *srvr)
  : Client("parent", 80, flight_host, "parent", 0),
    srvr(srvr),
    waiting_for_parent(false) {
  conn_fail_reported = true;
  set_retries(-1, 2, 2);
}

bool dasctl_t::app_connected() {
  if (opt_Q) return iwrite("Q\n");
  if (opt_r) return iwrite("r\n");
  if (restart_script) {
    std::string rs("R");
    rs += restart_script;
    return iwrite(rs);
  }
  if (opt_S) return iwrite("S\n");
  msg(MSG_FATAL, "Expected option Q, r, R or S in app_connected");
  return false; // Never reached
}

bool dasctl_t::app_input() {
  if (opt_S) {
    // just display the text.
    msg(0, "%s", &buf[0]);
  } else {
    // Check for OK response, and then shutdown
    if (strncasecmp((const char *)(&buf[0]), "OK", 2) != 0) {
      msg(2, "%s", &buf[0]);
    }
  }
  report_ok(nc);
  if (srvr)
    srvr->Shutdown(true);
  return true;
}

bool dasctl_t::connect_failed() {
  if (!waiting_for_parent) {
    msg(0, "Waiting for parent");
    waiting_for_parent = true;
  }
  return false;
}

/**
 * @brief the Serverside_Client socket
 */
dasctl_ssclient::dasctl_ssclient(Authenticator *Auth, const char *iname)
    : Serverside_client(Auth, iname, dasctl_ssclient_ibufsize) {}

dasctl_ssclient::~dasctl_ssclient() {}

bool dasctl_ssclient::connected() {
  if (restart_script == 0)
    restart_script = "/dev/null";
  msg(0, "Answering server request with script '%s'", restart_script);
  if (!iwrite(restart_script))
    script_delivered = true;
  close();
  srvr->Shutdown(true);
  return false;
}

Serverside_client *new_dasctl_ssclient(Authenticator *Auth, SubService *SS) {
  SS = SS; // No need for this
  return new dasctl_ssclient(Auth, Auth->get_client_app());
}


// dasctrlclt_t is the client that talks to a dasctl server
dasctlclt_t::dasctlclt_t()
    : Client("dasctl", 80, gse_host[0] ? gse_host : 0, "dasctl", 0) {
  conn_fail_reported = true;
}

bool dasctlclt_t::app_input() {
  fprintf(stdout, "%s", &buf[0]);
  report_ok(nc);
  return true;
}

bool dasctlclt_t::connect_failed() {
  msg(MSG_DEBUG, "Unable to connect to dasctl server");
  exit(0);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (gse_host) query_gse();
  else {
    Server S("dasctl");
    dasctl_t *dasctl = new dasctl_t(&S);
    S.ELoop.add_child(dasctl);
    dasctl->connect();
    if (opt_S) {
      S.ELoop.event_loop();
      S.ELoop.delete_children();
    } else {
      S.add_subservice(new SubService("dasctl",
	new_dasctl_ssclient, (void *)0));
      S.Start(flight_host ? Server::Srv_TCP : Server::Srv_Unix);
    }
  }
  return 0;
}
