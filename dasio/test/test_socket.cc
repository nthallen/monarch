/** @file test_socket.cc */
#include "dasio_socket.h"
#include "mock_socket.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

TEST(SocketTest,ServerSetup) {
  MockSocket socket("IPC", 512, "cmd", true);
  socket.set_retries(0, 1, 5);
  EXPECT_CALL(socket, connected()).Times(0);
  EXPECT_CALL(socket, connect_failed()).Times(0);
  socket.connect();
  socket.close();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
