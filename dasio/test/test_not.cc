/** @file test_not.cc */
#include <stdlib.h>
#include "dasio_socket.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

/* A class for testing of the not_ functions */
class not_tester : public DAS_IO::Interface {
  public:
    not_tester(const char *str, int buf_size);
    ~not_tester();
    bool seed_buf(const char *str);
}

/* Constructor method */
not_tester::not_tester(const char *str, int bufsz) {
  DAS_IO::Interface(&str, bufsz);
}

/* Destructor method */
not_tester::~not_tester() {
  /* no clue what to do here */
}

/* This method fills the buffer with a given string. */
bool not_tester::seed_buf(const char *str) {
  int length = strlen(&str);
  if (length < buf_size) {
    strncpy(DAS_IO::Interface::buf, &str, length);
    return true;
  } else {
    return false;
  }
}

/* This method tests functionality of the constructor */
TEST(NotTest, NotFloatTest) {
  not_tester::not_tester("NotTesterInstance",8);
  EXPECT_FALSE(not_tester::seed_buf("FarFarFarTooBig"));
  EXPECT_TRUE(not_tester::seed_buf("Correct"));
}

/* This method tests functionality of not_float() */
TEST(NotTest, NotFloatTest) {
  not_tester::not_tester("NotTesterInstance",15);
  not_tester::seed_buf("NotAFloat");
  EXPECT_TRUE(DAS_IO::Interface::not_float());
  not_tester::seed_buf("8.15");
  EXPECT_FALSE(DAS_IO::Interface::not_float());
}

/* Main method */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
