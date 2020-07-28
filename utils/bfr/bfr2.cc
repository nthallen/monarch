/** @file bfr2.cc
 *  Telemetry Buffer
 *  Ported from ARP-DAS circa 25 March 2019
 *  Rewritten using tm_rcvr starting 26 July 2020
 */

#include <list>
#include <string.h>
#include "rundir.h"
#include "bfr2.h"
#include "oui.h"
#include "nl.h"
#include "nl_assert.h"
#include "dasio/msg.h"
#include "dasio/appid.h"

using namespace DAS_IO;

bool bfr2_input_client::tmg_opened = false;
bfr2_input_client *bfr2_input_client::tm_gen;
// bool blocked_writer = false;
// bool blocked_reader = false;
std::list<bfr2_output_client*> all_readers;

bfr2_input_client::bfr2_input_client(Authenticator *Auth,
          const char *iname, bool blocking)
    : Serverside_client(Auth, iname, bfr2_input_client_ibufsize),
      tm_rcvr(this),
      tm_queue(),
      blocking(blocking)
{
  // state = TM_STATE_HDR;
  // buf = (unsigned char *)&part.hdr;
  // write.nbrow_rec = 0;
  // write.nbhdr_rec = 0;
  // nc = 0;
  // write.off_msg = 0;
  // write.nb_rec = 0;
  // write.off_queue = 0;
  // data_state_eval = 0;
  tm_gen = this;
}

bool bfr2_input_client::auth_hook(Authenticator *Auth, SubService *SS) {
  // should lock the tm_queue here:
  if (tmg_opened) return false;
  tmg_opened = true;
  return true;
}
