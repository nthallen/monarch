/** @file tm_rcvr.cc 
 *  To abstract some functionality from tm_client.
 *  @date 2019-04-26
 */

#include "dasio/tm_rcvr.h"

/*
To be copied:
tm_client::process_message()?
tm_client::seek_tmid()?
tm_client::app_input()?

Reader::process_data() / tm_client::process_message() ?
Reader::context() / tm_client::context() ?


*/

tm_rcvr::process_raw_tm() {
  if ( nc >= toread ) {
    if (tm_msg->hdr.tm_id != TMHDR_WORD) {
      seek_tmid();
    } else {
      process_message();
    }
  }
  return false;
}
