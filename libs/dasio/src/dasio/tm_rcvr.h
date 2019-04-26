/**
 * @file tm_rcvr.h
 */

class tm_rcvr {
  tm_msg_t tm_msg;
  
  virtual void tm_rcvr::process_tstamp() = 0;
  virtual const char *tm_rcvr::context() = 0;
}