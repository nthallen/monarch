/** @file tcp.cc */
#include "sspint.h"
#include "nl.h"

using namespace DAS_IO;

SSP_TCP::SSP_TCP()
    : Socket("SSP", "SSP", "SSP", RECV_BUF_SIZE),
      state(FD_IDLE) {
  Q.full = false;
  Q.front = 0;
  Q.back = 0;
}

bool SSP_TCP::connected() {
  state = empty() ? FD_IDLE : FD_WRITE;
  ssp_data.Status = SSP_STATUS_READY;
  msg(0, "TCP connected");
  return false;
}

void SSP_TCP::enqueue(const unsigned char *cmd) {
  int nb;
  if ( Q.full )
    msg(3, "TCP queue overflow" );
  nb = snprintf((char *)Q.q[Q.back], TCP_SEND_SIZE, "%s\r\n", cmd);
  if ( nb >= TCP_SEND_SIZE )
    msg(2, "TCP queue command too long: %s", cmd );
  else {
    if ( ++Q.back == TCP_QSIZE )
      Q.back = 0;
    if ( Q.back == Q.front )
      Q.full = true;
  }
  if (state == FD_IDLE) {
    state = FD_WRITE;
    send();
  }
}

void SSP_TCP::send() {
  if (state != FD_WRITE) return;
  if (empty()) {
    state = FD_IDLE;
    return;
  }
  char *cmd = (char*)Q.q[Q.front];
  int cmdlen = strlen(cmd);
  iwrite(cmd, cmdlen);
  state = FD_READ;
  TO.Set(1,0);
  flags |= Fl_Timeout;
}

bool SSP_TCP::protocol_input() {
  if (state != FD_READ) {
    report_err("%s: Unexpected input in state %d", iname, state);
    consume(nc);
    return false;
  }
  uint16_t rv;
  if (not_uint16(rv)) {
    if (cp < nc) {
      report_err("%s: Invalid response", iname);
      consume(nc);
    } else {
      consume(cp);
    }
  } else {
    msg(MSG_DBG(0), "%s: returning %d from command %s",
      iname, rv, Q.q[Q.front]); 
    Q.full = false;
    if (++Q.front == TCP_QSIZE)
      Q.front = 0;
    if (empty()) {
      state = FD_IDLE;
    } else {
      state = FD_WRITE;
      send();
    }
  }
  return false;
}

bool SSP_TCP::protocol_timeout() {
  if (empty() || state != FD_READ) {
    report_err("%s: Unexpected timeout without command pending", iname);
  } else {
    msg(1, "%s: timeout on command %s",
      iname, Q.q[Q.front]); 
    Q.full = false;
    if (++Q.front == TCP_QSIZE)
      Q.front = 0;
    if (empty()) {
      state = FD_IDLE;
    } else {
      state = FD_WRITE;
      send();
    }
  }
  return false;
}
