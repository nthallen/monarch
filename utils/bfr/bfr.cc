/** @file bfr.cc
 *  Telemetry Buffer
 *  est. 25 March 2019
 *  ported from ARP-DAS
 */

#include <list>
#include "rundir.h"
#include "bfr.h"
#include "oui.h"
#include "nl.h"
#include "dasio/msg.h"

using namespace DAS_IO;

AppID_t DAS_IO::AppID("bfr", "bfr server", "V1.0");

std::list<bfr_output_client*> all_readers;

int min_reader( dq_descriptor_t *dqd ) {
  if ( dqd != DQD_Queue.first ) return 0;
  int min = dqd->Qrows_expired + dqd->n_Qrows;
  for ( ocb = all_readers; ocb != 0; ocb = ocb->next_ocb ) {
    if ( ocb->data.dqd == dqd && ocb->data.n_Qrows < min )
      min = ocb->data.n_Qrows;
  }
  return min;
}

bfr_input_client::bfr_input_client(Authenticator *Auth, const char *iname)
    : Serverside_client(Auth, iname, bfr_input_client_ibufsize) {}

bfr_input_client::~bfr_input_client() {}

bfr_output_client::bfr_output_client(Authenticator *Auth, const char *iname, bool is_fast)
    : Serverside_client(Auth, iname, bfr_output_client_ibufsize), is_fast(is_fast) {
      all_readers.push_back(this);
    }

bfr_output_client::~bfr_output_client() {
  all_readers.remove(this);
}

Serverside_client *new_bfr_input_client(Authenticator *Auth, SubService *SS) {
  return new bfr_input_client(Auth, Auth->get_client_app());
}

Serverside_client *new_bfr_output_client(Authenticator *Auth, SubService *SS) {
  bool is_fast = (SS->name == "tm_bfr/fast");
  return new bfr_output_client(Auth, Auth->get_client_app(), is_fast);
}

void add_subservices(Server *S) {
  S->add_subservice(new SubService("tm_bfr/input", new_bfr_input_client, (void *)(0)));
  S->add_subservice(new SubService("tm_bfr/optimized", new_bfr_output_client, (void *)(0)));
  S->add_subservice(new SubService("tm_bfr/fast", new_bfr_output_client, (void *)(0)));
}

/* Main method */
int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  setup_rundir();
  
  Server S("tm_bfr");
  add_subservices(&S);
  S.Start(Server::Srv_Unix);
  return 0;
}