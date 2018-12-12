/** @file test_not.cc */
#include <stdlib.h>
#include "dasio.h"
#include "nl.h"
#include "msg.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

/* A class for testing of the not_ functions */
class not_tester : public DAS_IO::Interface {
  public:
    not_tester(const char *str, int buf_size);
    ~not_tester();
	int get_cp();
	int get_nc();
    bool seed_buf(const char *str);
	inline bool not_float(float &val) {
	  return DAS_IO::Interface::not_float(val);
	}
	inline bool not_found(unsigned char c) {
	  return DAS_IO::Interface::not_found(c);
	}
	inline bool not_hex(uint16_t &hexval) {
	  return DAS_IO::Interface::not_hex(hexval);
	}
	inline bool not_int(int &val) {
	  return DAS_IO::Interface::not_int(val);
	}
};

/* Constructor method */
not_tester::not_tester(const char *str, int bufsz) 
  : DAS_IO::Interface::Interface(str, bufsz) {
}

/* Destructor method */
not_tester::~not_tester() {
  /* no clue what to do here */
};

/* This function returns the counter from DAS_IO. */
int not_tester::get_cp() {
  return DAS_IO::Interface::cp;
}

/* This function returns the counter from DAS_IO. */
int not_tester::get_nc() {
  return DAS_IO::Interface::nc;
}

/* This method fills the buffer with a given string. */
bool not_tester::seed_buf(const char *str) {
  int length = strlen(str);
  if (length < DAS_IO::Interface::bufsize) {
    strncpy((char *)DAS_IO::Interface::buf, str, length);
	cp = 0;
	nc = length;
    return true;
  } else {
    return false;
  }
};

/* This method tests functionality of the constructor */
TEST(NotTest, NotTesterTest) {
  not_tester nt = not_tester("NotTesterInstance",8);
  const char *wrong_string = "FarFarFarTooBig";
  const char *right_string = "Correct";
  EXPECT_FALSE(nt.seed_buf(wrong_string));
  EXPECT_TRUE(nt.get_cp() <= nt.get_nc());
  EXPECT_TRUE(nt.seed_buf(right_string));
  EXPECT_TRUE(nt.get_cp() <= strlen(right_string));
}

/* This method tests functionality of not_float() */
TEST(NotTest, NotFloatTest) {
  not_tester nt = not_tester("NotTesterInstance",15);
  nt.seed_buf("NotAFloat");
  float proper_float;
  EXPECT_TRUE(nt.not_float(proper_float));
  nt.seed_buf("5.3");
  EXPECT_FALSE(nt.not_float(proper_float));
  EXPECT_NEAR(proper_float, 5.3,0.001);
}

/* This method tests functionality of not_found() */
TEST(NotTest, NotFoundTest) {
  not_tester nt = not_tester("NotTesterInstance",15);
  nt.seed_buf("NotFound");
  unsigned char c = 'F';
  EXPECT_FALSE(nt.not_found(c));
  nt.seed_buf("NotFound");
  c = 'c';
  EXPECT_TRUE(nt.not_found(c));
}

/* This method tests functionality of not_hex() */
TEST(NotTest, NotHexTest) {
  not_tester nt = not_tester("NotTesterInstance",15);
  nt.seed_buf("0xE9");
  uint16_t hexval;
  EXPECT_FALSE(nt.not_hex(hexval));
  nt.seed_buf("NotHex");
  EXPECT_TRUE(nt.not_hex(hexval));
}

/* This method tests functionality of not_int() */
TEST(NotTest, NotIntTest) {
  not_tester nt = not_tester("NotTesterInstance",15);
  nt.seed_buf("233");
  int true_int;
  EXPECT_FALSE(nt.not_int(true_int));
  nt.seed_buf("NotInt");
  EXPECT_TRUE(nt.not_int(true_int));
}

/* Main method */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}