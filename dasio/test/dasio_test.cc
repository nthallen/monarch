/* dasio_test.cc */
#include <unistd.h>
#include "Timeout.h"
#include "gtest/gtest.h"

class TO_test : public ::testing::Test {
  protected:
    void SetUp() {
      TO.Clear();
	  socket = new socket(/*no clue*/);
    }
    Timeout TO;
	TimeoutAccumulator TA;
	Socket socket;
};

TEST_F(TO_test, StartsClear) {
  EXPECT_FALSE(TO.Set());
}

TEST_F(TO_test, TimesOut) {
  TO.Set(2,0);
  sleep(1);
  EXPECT_FALSE(TO.Expired());
  sleep(2);
  EXPECT_TRUE(TO.Expired());
}

// Code added by Miles on 20 November 2018

// This method tests that the timer Set method instantiates correctly.
TEST_F(TO_test) {
  EXPECT_FALSE(TO.Set());
  TO.Set(2,0);
  EXPECT_TRUE(TO.Set());
  EXPECT_FALSE(TO.Expired());
}

// This method tests the functionality of the Clear method when Set.
TEST_F(TO_test) {
  TO.Set(2,0);
  sleep(1);
  EXPECT_FALSE(TO.Expired());
  TO.Clear();
  EXPECT_TRUE(TO.Expired());
}

// This method tests the functionality of the Set_Min method.
TEST_F(TO_test) {
  TO.Set(2,0);
  TA.Set(TO);
  TO.SET(4,0);
  TA.Set(TO);
  TO.Set(6,0);
  TA.Set(TO);
  EXPECT_FALSE(TA.timeval==2);
  TA.Set_Min();
  EXPECT_TRUE(TA.timeval==2);
}

// This method tests functionality of the socket
TEST_F(TO_test) {
  socket.connect();
  socket.readSockError(0);
  socket.reset();
  socket.readSockError(0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}