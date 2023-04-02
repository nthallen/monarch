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
  }
}

bool SSP_TCP::protocol_input() {
  return false;
}
