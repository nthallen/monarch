/* dasio_test.cc */
#include <unistd.h>
#include "Timeout.h"
#include "gtest/gtest.h"

class TO_test : public ::testing::Test {
  protected:
    void SetUp() {
      TO.Clear();
    }
    Timeout TO;
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}