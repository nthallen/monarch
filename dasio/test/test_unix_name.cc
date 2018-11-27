/** @file test_unix_name.cc */
#include "dasio_socket.h"
// #include "mock_socket.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

// Must lock before calling claim_server()

class MockSocket : public DAS_IO::Socket {
  public:
    inline MockSocket(const char *iname, int bufsz, const char *service, bool server = false) :
      DAS_IO::Socket(iname, bufsz, service, server) {}
    inline ~MockSocket() {};
    void connected();  
};

void MockSocket::connected() {}

TEST(SocketTest,ServerSetup) {
  MockSocket socket("IPC", 512, "cmd", true);
  socket.set_retries(0, 1, 5);
  // EXPECT_CALL(socket, connected()).Times(0);
  // EXPECT_CALL(socket, connect_failed()).Times(0);
  socket.connect();
  ASSERT_EQ(socket.get_socket_state(), DAS_IO::Socket::Socket_listening);
  socket.close();
}

/* This method tests functionality of the unix_name constructor, and whether I know how to invoke it */
TEST(SocketTest,UnixNameSetup) {
  MockSocket socket("IPC", 512, "cmd", true);
  socket->unix_name.~unix_name_t();
  const char *service = 'bad_service_name';
  EXPECT_FALSE(socket->unix_name.set_service(&service));
  *service = '/var/run/SCOPEX/?';
  EXPECT_TRUE(unix_name.set_service(&service));
  socket.set_retries(0, 1, 5);
  socket.connect();
}

/* This method tests functionality of the lock function */
TEST(SocketTest,UnixNameLockSetup) {
  MockSocket socket("IPC", 512, "/var/run/SCOPEX/?/", true);
  socket.set_retries(0, 1, 5);
  socket.connect();
  EXPECT_TRUE(socket->unix_name.lock());
  EXPECT_TRUE(socket->unix_name.is_locked());
  EXPECT_FALSE(socket->unix_name.lock());
  socket->unix_name.unlock();
  EXPECT_FALSE(socket->unix_name.is_locked());
}

/* This method tests functionality of the claim_server function */
TEST(SocketTest,UnixNameLockSetup) {
  MockSocket socket("IPC", 512, "/var/run/SCOPEX/?/", true);
  socket.set_retries(0, 1, 5);
  socket.connect();
  socket->unix_name.lock();
  EXPECT_TRUE(socket->unix_name.claim_server());
  EXPECT_TRUE(socket->unix_name.is_server());
  socket->unix_name.release_server();
  EXPECT_FALSE(socket->unix_name.is_server());
  EXPECT_FALSE(socket->unix_name.is_locked());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
