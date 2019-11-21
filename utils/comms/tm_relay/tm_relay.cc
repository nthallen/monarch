/** @file tm_relay.cc
 *  To serve as middleman between two points of communication
 *  @date 2019-11-14
 */

#include "dasio/tm.h"
#include "dasio/tm_gen.h"
#include "dasio/tm_client.h"
#include "dasio/msg.h"
#include "dasio/appid.h"
#include "dasio/loop.h"
#include "tm_relay.h"
#include "oui.h"

using namespace DAS_IO;
  
DAS_IO::AppID_t DAS_IO::AppID("tm_relay", "tm_relay", "V1.0");
  
tm_relay::tm_relay() : tm_generator(), tm_client(64, false, "tm_relay") {
  msg(0, "pointless message from tm_relay init");
}

void tm_relay::process_data(mfc_t MFCtr, int mfrow, int nrows) {
  tm_queue::commit_rows(MFCtr, mfrow, nrows);
}

void tm_relay::process_tstamp(mfc_t MFCtr, time_t time) {
  tm_queue::commit_tstamp(MFCtr, time);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  tm_relay new_tm_relay = new tm_relay();
  Loop ELoop;
  ELoop.add_child(&new_tm_relay);
  msg(0, "tm_relay starting");
  new_tm_relay.connect();
  new_tm_relay.Start(Server::server_type);
  ELoop.event_loop();
  msg(0, "tm_relay terminating");
  return 0;
}
