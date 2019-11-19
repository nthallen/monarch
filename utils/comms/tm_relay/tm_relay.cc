/** @file tm_relay.cc
 *  To serve as middleman between two points of communication
 *  @date 2019-11-14
 */

#include "tm.h"
#include "tm_gen.h"
#include "tm_client.h"

using namespace DAS_IO {

tm_relay::tm_relay() : tm_generator(), tm_client(64, false, "tm_relay") {}

void tm_relay::process_data() {
  commit_rows();
}

void tm_relay::process_tstamp() {
  commit_tstamp();
}

}
