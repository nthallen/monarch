#include <string>
#include <list>
#include <getopt.h>
#include "dasio/server.h"
#include "dasio/quit.h"
#include "subbusd_int.h"
#include "nl.h"
#include "subbusd_int.h"
#include "nl_assert.h"
#include "oui.h"

// #include <errno.h>
// #include <stdio.h>
// #include <stddef.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/iofunc.h>
// #include <sys/dispatch.h>
// #include <fcntl.h>
// #include <ctype.h>
// #include <signal.h>
// #include "company.h"
// #include "tm.h"

using namespace DAS_IO;

static int SB_Shutdown = 0;

subbusd_flavor::subbusd_flavor(const char *flavor, socket_clone_t cloner)
  : flavor(flavor), cloner(cloner) {}

subbusd_flavor::~subbusd_flavor() {}

void subbusd_flavor::init_subbus() {}
void subbusd_flavor::shutdown_subbus() {}

subbusd_client::subbusd_client(Authenticator *auth, int bufsize)
      : Serverside_client(auth, auth->get_client_app(), bufsize) {
  reply_size = bufsize;
  reply = (reply_size > 0) ? (subbusd_rep_t*)new_memory(reply_size) : 0;
}

subbusd_client::~subbusd_client() {}

bool subbusd_client::error_return(uint16_t err_code) {
    reply->hdr.status = err_code;
    reply->hdr.ret_type = SBRT_NONE;
    iwrite((const char*)reply, sizeof(subbusd_rep_hdr_t));
    return false;
}

bool subbusd_client::app_input() {
  subbusd_req_t *sbdmsg = (subbusd_req_t *)buf;
  unsigned nb_exp;
  
  if ( nc < sizeof(subbusd_req_hdr_t) ||
       sbdmsg->sbhdr.sb_kw != SB_KW) {
    return error_return(SBS_REQ_SYNTAX);
  }
  /* check the size of the incoming message */
  switch ( sbdmsg->sbhdr.command ) {
    case SBC_WRITEACK:
    case SBC_WRITECACHE:
      nb_exp = sizeof(subbusd_req_data0); break;
    case SBC_SETCMDENBL:
    case SBC_SETCMDSTRB:
    case SBC_SETFAIL:
    case SBC_READACK:
    case SBC_READCACHE:
      nb_exp = sizeof(subbusd_req_data1); break;
    case SBC_READSW:
    case SBC_READFAIL:
    case SBC_GETCAPS:
    case SBC_TICK:
    case SBC_DISARM:
      nb_exp = 0; break;
    case SBC_QUIT:
      SB_Shutdown = 1;
      nb_exp = 0; break;
    case SBC_INTATT:
      nb_exp = sizeof(subbusd_req_data2); break;
    case SBC_INTDET:
      nb_exp = sizeof(subbusd_req_data3); break;
    case SBC_MREAD:
      nb_exp = 3*sizeof(uint16_t);
      if ( nc >= nb_exp ) {
        nl_assert( sbdmsg->data.d4.req_len >= nb_exp );
        nb_exp = sbdmsg->data.d4.req_len;
      }
      break;
    default:
      return error_return(SBS_REQ_SYNTAX);
  }
  nb_exp += sizeof(subbusd_req_hdr_t);
  if ( nc < nb_exp )
    msg( 4, "Received short message for command %d: Expected %d received %d",
      sbdmsg->sbhdr.command, nb_exp, nc );
  return incoming_sbreq( sbdmsg );
}

bool subbusd_client::incoming_sbreq(subbusd_req_t *req) {
  return error_return(SBS_NOT_IMPLEMENTED);
}

const char *subbusd_service = "subbusd";
bool subbusd_cmd_quit = false;
subbusd_core *subbusd = 0;

subbusd_core::subbusd_core(const char *service) : srvr(service) {
}

subbusd_core::~subbusd_core() {}

void subbusd_core::register_flavor(subbusd_flavor *fl) {
  std::string ssvc(srvr.get_service());
  ssvc.append("/");
  ssvc.append(fl->flavor);
  srvr.add_subservice(new SubService(ssvc, fl->cloner, (void*)fl));
  devs.push_back(fl);
}

void subbusd_core::Start(Server::Srv_type type) {
  std::list<subbusd_flavor*>::iterator flp;
  
  for (flp = devs.begin(); flp != devs.end(); ++flp) {
    subbusd_flavor *fl = *flp;
    fl->init_subbus();
  }
  subbusd->srvr.Start(type);
  for (flp = devs.begin(); flp != devs.end(); ++flp) {
    subbusd_flavor *fl = *flp;
    fl->shutdown_subbus();
  }
}

static void sigint_handler( int sig ) {
  SB_Shutdown = 1;
}

void subbusd_init_options(int argc, char **argv) {
	int c;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 's':
        subbusd_service = optarg;
        break;
      case 'q':
        subbusd_cmd_quit = true;
        break;
      case '?':
        fprintf( stderr, "Unrecognized option: '-%c'\n", optopt );
        exit(1);
      default: break; // could check for errors
    }
  }
  subbusd = new subbusd_core(subbusd_service);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (subbusd_cmd_quit) {
    Quit *q = new Quit();
    subbusd->srvr.ELoop.add_child(q);
    q->connect();
  }

  signal( SIGINT, sigint_handler );
  signal( SIGHUP, sigint_handler );

  subbusd->Start(Server::Srv_Unix);
  return 0;
}
