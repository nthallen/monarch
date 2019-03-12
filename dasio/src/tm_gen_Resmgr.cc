#include <errno.h>
#include "dasio/tm_gen_Resmgr.h"
#include "nl.h"
#include "nl_assert.h"

/** tm_gen_Resmgr.h Framework for 
*/

tm_gen_dispatch_client::tm_gen_dispatch_client() {
  dispatch = NULL;
}

tm_gen_dispatch_client::~tm_gen_dispatch_client() {
  if ( dispatch != NULL )
    detach();
}

void tm_gen_dispatch_client::attach(tm_gen_dispatch *disp) {
  // assert( disp != NULL );
  dispatch = disp;
  dispatch->client_add(this);
}

void tm_gen_dispatch_client::detach() {
  //assert(dispatch != NULL);
  dispatch->client_rm(this);
  dispatch = NULL;
}

tm_gen_dispatch::tm_gen_dispatch() {
    dpp = dispatch_create();
  if ( dpp == NULL )
    report_err(/* 3, */"Failed to allocate dispatch handle." );
  quit_received = 0;
}

void tm_gen_dispatch::ready_to_quit() {
    quit_received = 1;
}

tm_gen_dispatch::~tm_gen_dispatch() {
    if ( single_ctp != NULL )
        dispatch_context_free(single_ctp);
  dispatch_destroy(dpp);
}

void tm_gen_dispatch::Loop() {
    single_ctp = dispatch_context_alloc(dpp);
  if ( single_ctp == NULL )
    msg(3, "dispatch_context_alloc failed: errno %d", errno );
  dispatch_context_t *ctp = single_ctp;
  while (1) {
    ctp = dispatch_block(ctp);
    if ( ctp == NULL )
      msg( 3, "Block error: %d", errno );
    dispatch_handler(ctp);
    if ( quit_received && ctp->resmgr_context.rcvid == 0
      && all_closed() )
      break;
  }
}

int tm_gen_dispatch::all_closed() {
  int ready = 1;
  int not_ready = 0;
  std::list<tm_gen_dispatch_client *>::iterator pos;
  for ( pos = clients.begin(); pos != clients.end(); ) {
    if ( (*pos)->ready_to_quit() ) clients.remove(*pos++);
    else {
      ready = 0;
      not_ready++;
      ++pos;
    }
  }
  if ( not_ready ) msg( -2, "Waiting on %d clients", not_ready );
  return ready;
}

void tm_gen_dispatch::client_add(tm_gen_dispatch_client *clt) {
  //assert(clt != NULL);
  clients.push_back(clt);
}

void tm_gen_dispatch::client_rm(tm_gen_dispatch_client *clt) {
  //assert(clt != NULL);
  clients.remove(clt);
}
