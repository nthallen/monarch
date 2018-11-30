/** @file test_socket.cc */
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <process.h>
#include "dasio.h"
#include "nl.h"
#include "dasio_socket.h"
#include "gtest/gtest.h"

int select_once(DAS_IO::Interface *P) {
  fd_set readfds, writefds, exceptfds;
  int width = 0;
  // Timeout TO;
  TimeoutAccumulator TA;
  // TO.Set(0,100);
  TA.Set(0);
  FD_ZERO(&readfds);
  FD_ZERO(&writefds);
  FD_ZERO(&exceptfds);
  if (P->flags & P->Fl_Read) FD_SET(P->fd, &readfds);
  if (P->flags & P->Fl_Write) FD_SET(P->fd, &writefds);
  if (P->flags & P->Fl_Except) FD_SET(P->fd, &exceptfds);
  if (P->flags & P->Fl_Timeout) TA.Set_Min( P->GetTimeout() );
  if (width <= P->fd) width = P->fd+1;
  int rc = select(width, &readfds, &writefds, &exceptfds, TA.timeout_val());
  int flags = 0;
  if (rc == 0) {
    flags = P->Fl_Timeout;
  } else if (rc < 0) {
    if (errno == EBADF || errno == EHOSTDOWN) {
      flags = P->Fl_Except;
    } else {
      nl_error(3,
        "DAS_IO::Loop::event_loop(): Unexpected error from select: %s",
        strerror(errno));
    }
  } else {
      if ( FD_ISSET(P->fd, &readfds) )
        flags |= P->Fl_Read;
      if ( FD_ISSET(P->fd, &writefds) )
        flags |= P->Fl_Write;
      if ( FD_ISSET(P->fd, &exceptfds) )
        flags |= P->Fl_Except;
      flags &= P->flags;
  }
  return flags;
}

class echosrvr : public DAS_IO::Socket {
  public:
    echosrvr(const char *iname, int bufsz, const char *service, bool server=false);
    echosrvr(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname = 0);
    ~echosrvr();
    DAS_IO::Socket *new_client(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname=0);
    bool protocol_input();
};

echosrvr::echosrvr(const char *iname, int bufsz, const char *service,
  bool server) : DAS_IO::Socket(iname, bufsz, service, server) {
}

echosrvr::echosrvr(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname)
    : DAS_IO::Socket(iname, bufsz, fd, stype, service, hostname) {
}
echosrvr::~echosrvr() {}

DAS_IO::Socket *echosrvr::new_client(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname) {
  echosrvr *clt = new echosrvr(iname, bufsz, fd, stype, service, hostname);
  return clt;
}

bool echosrvr::protocol_input() {
  cp = 0;
  if (cp < nc) {
    switch (buf[cp]) {
      case 'E':
        iwrite((const char *)buf, nc, 1);
        report_ok(nc);
        return false;
      case 'Q':
        report_ok(nc);
        return true;
      case 'C':
        report_ok(nc);
        close();
        ELoop->delete_child(this);
        return false;
      default:
        report_err("Unrecognized input:");
        consume(nc);
        return false;
    }
  }
}

const char *opt_string = "vo:mV";

TEST(SocketTest,ClientSetup) {
  int flags, exp_flags;
  
  DAS_IO::Socket client("IPCclient", 512, "cmd", false);
  client.set_retries(2, 1, 5);
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connecting);
  flags = select_once(&client);
  exp_flags = client.Fl_Read;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connected);
}

void child_process() {
  echosrvr server("IPCserver", 512, "cmd", true);
  DAS_IO::Loop ELoop;
  ELoop.add_child(&server);
  ELoop.event_loop();
}

int main(int argc, char **argv) {
  pid_t child = fork();
  if (child == 0) {
    child_process();
  } else {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}
