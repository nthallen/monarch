/** @file test_socket.cc */
#include "dasio_socket.h"
// #include "mock_socket.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

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
  ASSERT_EQ(socket.get_socket_state(), DAS_IO::Socket::Socket_listening);
  socket.close();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
