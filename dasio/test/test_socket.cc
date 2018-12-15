/** @file test_socket.cc */
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <process.h>
#include "nl.h"
#include "dasio/socket.h"
#include "dasio/timeout.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "gtest/gtest.h"

DAS_IO::AppID_t DAS_IO::AppID("test_socket", "Tests of socket functions", "V1.1");

int select_once(DAS_IO::Interface *P) {
  fd_set readfds, writefds, exceptfds;
  int width = 0;
  // Timeout TO;
  DAS_IO::TimeoutAccumulator TA;
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
    echosrvr(const char *iname, int bufsz, const char *service);
    echosrvr(const char *iname, int bufsz, const char *service,
      DAS_IO::Socket::socket_type_t);
    echosrvr(Socket *orig, const char *iname, int fd);
    ~echosrvr();
    DAS_IO::Socket *new_client(const char *iname, int fd);
    bool protocol_input();
    bool connected();
};

echosrvr::echosrvr(const char *iname, int bufsz, const char *service,
        DAS_IO::Socket::socket_type_t socket_type)
    : DAS_IO::Socket(iname, bufsz, service, socket_type) {
}

echosrvr::echosrvr(const char *iname, int bufsz, const char *service)
    : DAS_IO::Socket(iname, bufsz, service) {
}

echosrvr::echosrvr(DAS_IO::Socket *orig, const char *iname, int fd)
  : DAS_IO::Socket(orig, iname, fd) {}  

echosrvr::~echosrvr() {
  nl_error(-2, "echosrvr shutting down");
}

bool echosrvr::connected() {
  nl_error(-2, "%s: connected. flags = %d", iname, flags);
  return false;
}

// DAS_IO::Socket *echosrvr::new_client(const char *iname, int bufsz, int fd,
      // socket_type_t stype, const char *service, const char *hostname) {
  // nl_error(-2, "%s: New client connection created. %s fd = %d", this->iname, iname, fd);
  // echosrvr *clt = new echosrvr(iname, bufsz, fd, stype, service, hostname);
  // return clt;
// }

DAS_IO::Socket *echosrvr::new_client(const char *iname, int fd) {
  nl_error(-2, "%s: New client connection created. %s fd = %d", this->iname, iname, fd);
  echosrvr *clt = new echosrvr(this, iname, fd);
  if (ELoop) ELoop->add_child(clt);
  return clt;
}

bool echosrvr::protocol_input() {
  cp = 0;
  if (cp < nc) {
    switch (buf[cp]) {
      case 'E':
        nl_error(-2, "Received '%s'", buf);
        iwrite((const char *)buf, nc, 1);
        report_ok(nc);
        return false;
      case 'Q':
        nl_error(-2, "Received Quit command");
        report_ok(nc);
        return true;
      case 'C':
        nl_error(-2, "Received Close command");
        report_ok(nc);
        close();
        ELoop->delete_child(this);
        return false;
      case 'A': // Close connection after acknowledge
        nl_error(-2, "Received Acknowledge and close");
        iwrite("OK");
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

class clientsocket : public DAS_IO::Socket {
  public:
    inline clientsocket() : DAS_IO::Socket("IPCclient", 512, "cmd") {}
    ~clientsocket();
    void transmit(const char *cmd);
    bool protocol_input();
};

clientsocket::~clientsocket() {}
void clientsocket::transmit(const char *cmd) {
  iwrite(cmd);
}
bool clientsocket::protocol_input() {
  cp = 0;
  if (nc > 0) {
    //nl_error(0, "%s: Received '%s'", iname, buf);
    report_ok(nc);
  }
  return false;
}

TEST(SocketTest,ClientSetup) {
  int flags, exp_flags;
  
  clientsocket client; // ("IPCclient", 512, "cmd", false);
  client.set_retries(2, 1, 5);
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_disconnected);
  client.connect();
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connecting);
  flags = select_once(&client) & client.Fl_Write;
  exp_flags = client.Fl_Write;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  ASSERT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connected);
  client.transmit("EHello");
  nl_error(0, "Transmitted EHello. flags = %d", client.flags);
  flags = select_once(&client);
  exp_flags = client.Fl_Read;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  ASSERT_TRUE(client.fd >= 0);
  client.transmit("C"); // Close the connection on the remote end
  flags = select_once(&client);
  exp_flags = client.Fl_Read;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_TRUE(client.ProcessData(flags));
  EXPECT_EQ(client.fd, -1);
}

TEST(SocketTest,ConnClosedOnWrite) {
  int flags, exp_flags;
  
  clientsocket client; // ("IPCclient", 512, "cmd", false);
  client.set_retries(2, 1, 5);
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_disconnected);
  client.connect();
  ASSERT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connecting);
  flags = select_once(&client) & client.Fl_Write;
  exp_flags = client.Fl_Write;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  ASSERT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connected);
  client.transmit("A");
  flags = select_once(&client);
  exp_flags = client.Fl_Read;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  client.transmit("EHello");
  flags = select_once(&client);
  exp_flags = client.Fl_Read;
  EXPECT_EQ(flags, exp_flags);
  if (client.ProcessData(flags)) {
    EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_disconnected);
    // will not reconnect on its own. error was seen as a regular close
    client.connect();
  } else {
    EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_disconnected);
    flags = select_once(&client);
    exp_flags = client.Fl_Timeout;
    EXPECT_EQ(flags, exp_flags);
    EXPECT_FALSE(client.ProcessData(flags));
  }
  EXPECT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connecting);
  flags = select_once(&client);
  exp_flags = client.Fl_Write;
  EXPECT_EQ(flags, exp_flags);
  EXPECT_FALSE(client.ProcessData(flags));
  ASSERT_EQ(client.get_socket_state(), DAS_IO::Socket::Socket_connected);
  client.transmit("Q");
}

void child_process() {
  echosrvr server("IPCserver", 512, "cmd", DAS_IO::Socket::Socket_Unix);
  server.connect();
  DAS_IO::Loop ELoop;
  ELoop.add_child(&server);
  ELoop.event_loop();
}

int main(int argc, char **argv) {
  pid_t child = fork();
  if (child == 0) {
    child_process();
  } else {
    sleep(1); // give the server a chance to start up
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}
