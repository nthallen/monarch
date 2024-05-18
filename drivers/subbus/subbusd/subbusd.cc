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

using namespace DAS_IO;

static int SB_Shutdown = 0;

subbusd_flavor::subbusd_flavor(const char *flavor, socket_clone_t cloner)
  : flavor(flavor), cloner(cloner) {}

subbusd_flavor::~subbusd_flavor() {}

void subbusd_flavor::init_subbus() {}
void subbusd_flavor::shutdown_subbus() {}

subbusd_client::subbusd_client(Authenticator *auth)
      : Serverside_client(auth, auth->get_client_app(), sizeof(subbusd_req_t)+1),
        request_pending(false) {}

subbusd_client::~subbusd_client() {}

bool subbusd_client::status_return(uint16_t err_code) {
    rep.hdr.status = err_code;
    rep.hdr.ret_type = SBRT_NONE;
    iwrite((const char*)(&rep), sizeof(subbusd_rep_hdr_t));
    return false;
}

bool subbusd_client::protocol_input() {
  req = (subbusd_req_t *)buf;
  unsigned nb_exp;
  
  nl_assert(!request_pending);
  request_pending = true;
  flags &= ~DAS_IO::Interface::Fl_Read;
  if ( nc < sizeof(subbusd_req_hdr_t) ||
       req->sbhdr.sb_kw != SB_KW) {
    return status_return(SBS_REQ_SYNTAX);
  }
  /* check the size of the incoming message */
  switch ( req->sbhdr.command ) {
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
      subbusd_core::subbusd->srvr.Shutdown(false);
      nb_exp = 0; break;
    case SBC_INTATT:
      nb_exp = sizeof(subbusd_req_data2); break;
    case SBC_INTDET:
      nb_exp = sizeof(subbusd_req_data3); break;
    case SBC_MREAD:
      nb_exp = 3*sizeof(uint16_t);
      if ( nc >= nb_exp ) {
        nl_assert( req->data.d4.req_len >= nb_exp );
        nb_exp = req->data.d4.req_len;
      }
      break;
    default:
      return status_return(SBS_REQ_SYNTAX);
  }
  nb_exp += sizeof(subbusd_req_hdr_t);
  if ( nc < nb_exp )
    msg( 4, "Received short message for command %d: Expected %d received %d",
      req->sbhdr.command, nb_exp, nc );
  return incoming_sbreq();
}

bool subbusd_client::iwritten(int nb) {
  if (obuf_empty()) {
    consume(nc);
    request_pending = false;
    flags |= DAS_IO::Interface::Fl_Read;
  }
  return false;
}

bool subbusd_client::incoming_sbreq() {
  return status_return(SBS_NOT_IMPLEMENTED);
}

const char *subbusd_service = "subbusd";
bool subbusd_cmd_quit = false;
subbusd_core *subbusd_core::subbusd = 0;

subbusd_core::subbusd_core(const char *service) : srvr(service) {
}

subbusd_core::~subbusd_core() {}

void subbusd_core::register_flavor(subbusd_flavor *fl) {
  std::string ssvc(srvr.get_service());
  ssvc.append("/");
  ssvc.append(fl->flavor);
  srvr.add_subservice(new SubService(ssvc, fl->cloner, (void*)fl));
  devs.push_back(fl);
  msg(MSG_DEBUG, "Registering svc/ssvc %s/%s",
    srvr.get_service(), fl->flavor);
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
  subbusd->srvr.ELoop.delete_children();
  subbusd->srvr.ELoop.clear_delete_queue(true);
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
  nl_assert(subbusd_core::subbusd == 0);
  subbusd_core::subbusd = new subbusd_core(subbusd_service);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_assert(subbusd_core::subbusd != 0);
  if (subbusd_cmd_quit) {
    Quit *q = new Quit(&subbusd_core::subbusd->srvr, false);
    subbusd_core::subbusd->srvr.ELoop.add_child(q);
    q->connect_later(3);
  }
  subbusd_core::subbusd->srvr.signal(SIGINT);
  subbusd_core::subbusd->srvr.signal(SIGHUP);

  subbusd_core::subbusd->Start(Server::Srv_Unix);
  return 0;
}
