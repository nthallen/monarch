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
    void seed_buf(const char *str);
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

/* This method tests functionality of not_float() */
TEST(NotTest, NotFloatTest) {
  not_tester::not_tester("NotTesterInstance",5);
  not_tester::seed_buf("NotFloat");
  EXPECT_TRUE(DAS_IO::Interface::not_float());
}

/* Main method */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
