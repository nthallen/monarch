/** @file tm_relay.cc
 *  To serve as middleman between two points of communication
 *  @date 2019-11-14
 */

#include "tm.h"
#include "tm_gen.h"
#include "tm_client.h"

using namespace DAS_IO {
  
DAS_IO::AppID_t DAS_IO::AppID("tm_relay", "tm_relay", "V1.0");
  
tm_relay::tm_relay() : tm_generator(), tm_client(64, false, "tm_relay") {}

void tm_relay::process_data() {
  commit_rows();
}

void tm_relay::process_tstamp() {
  commit_tstamp();
}

int main() {
  tm_relay::tm_relay new_tm_relay();
  Loop ELoop;
  ELoop.add_child(new_tm_relay);
  msg(0, "tm_relay starting");
  new_tm_relay.connect();
  ELoop.event_loop();
  new_tm_relay.Start();
  msg(0, "tm_relay terminating");
  return 0;
}
  
}
