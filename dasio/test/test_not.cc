/** @file test_not.cc */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "dasio/interface.h"
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
    inline bool not_int32(int &val) {
      return DAS_IO::Interface::not_int32(val);
    }
	inline bool not_ISO8601(double &Time, bool w_hyphens) {
      return DAS_IO::Interface::not_ISO8601(Time, w_hyphens);
    }
	inline bool not_nfloat(float *value, float NaNval) {
		return DAS_IO::Interface::not_nfloat(value, NaNval);
	}
	inline bool not_uint8(uint8_t &val) {
		return DAS_IO::Interface::not_uint8(val);
	}
	inline bool not_uint16(uint16_t &val) {
		return DAS_IO::Interface::not_uint16(val);
	}
	inline bool not_ndigits(int n, int &value) {
		return DAS_IO::Interface::not_ndigits(n, value);
	}
	inline bool not_str( const char *str_in, unsigned int len ) {
		return DAS_IO::Interface::not_str(str_in, len);
	}
	inline bool not_bin(int nbits, uint16_t &word) {
		return DAS_IO::Interface::not_bin(nbits, word);
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
  EXPECT_TRUE(nt.get_nc() == 0);
  /* printf(" >>str is %d\n", strlen(wrong_string));
  printf(" >> nc is %d\n", nt.get_nc());
  printf(" >> cp is %d\n", nt.get_cp());
  printf("\n"); */
  //EXPECT_TRUE(nt.get_cp() <= nt.get_nc());
  EXPECT_TRUE(nt.seed_buf(right_string));
  EXPECT_TRUE(nt.get_nc() == strlen(right_string));
  //EXPECT_TRUE(nt.get_cp() <= strlen(right_string));
  /* printf(" >>str is %d\n", strlen(right_string));
  printf(" >> nc is %d\n", nt.get_nc());
  printf(" >> cp is %d\n", nt.get_cp());
  printf("\n"); */
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

/* This method tests functionality of not_int32() */
TEST(NotTest, NotIntTest) {
  not_tester nt = not_tester("NotTesterInstance",15);
  nt.seed_buf("233");
  int true_int;
  EXPECT_FALSE(nt.not_int32(true_int));
  nt.seed_buf("NotInt");
  EXPECT_TRUE(nt.not_int32(true_int));
  /* Haven't added the part yet where we build the number into an int64_t */
  //nt.seed_buf("4294967296");
  //EXPECT_TRUE(nt.not_int32(true_int));
}

/* This method tests functionality of not_ISO8601() */
TEST(NotTest, NotISO8601Test) {
  not_tester nt = not_tester("NotTesterInstance",45);
  nt.seed_buf("2019-01-07T13:57:00.000");
  bool w_hyphens = true;
  double time;
  double new_time;
  
  EXPECT_FALSE(nt.not_ISO8601(time, w_hyphens));
  time_t proper_time = (int32_t) time;
  
  /* printf("\n>test output:\n");
  printf(" >>time           is %lf\n",time);
  printf(" >>(int32_t) time is %d\n",(int32_t) time);
  printf(" >>proper_time    is %d\n",proper_time); */
  
  struct tm * fixed_time = gmtime(&proper_time);
  char ptr[45];
  strftime(ptr, 45, "%FT%T.000", fixed_time);
  //printf(" >>fixed_time     is %s\n\n",ptr);
  nt.seed_buf(ptr);
  
  EXPECT_FALSE(nt.not_ISO8601(new_time, w_hyphens));
}

/* This method tests functionality of not_nfloat() */
/* It segfaults, I don't know why, don't uncomment it lest ye be saddled with doom */
/* TEST(NotTest, NotNFloatTest) {
  not_tester nt = not_tester("NotTesterInstance",45);
  float *test_float;
  float NaNval = 99999;
  float *NaNval_2 = (float*) 99999;
  nt.seed_buf(",");
  EXPECT_FALSE(nt.not_nfloat(test_float, NaNval));
  nt.seed_buf("NaN");
  EXPECT_FALSE(nt.not_nfloat(test_float, NaNval));
  nt.seed_buf("45.45");
  EXPECT_FALSE(nt.not_nfloat(test_float, NaNval));
  nt.seed_buf("4545");
  EXPECT_TRUE(nt.not_nfloat(test_float, NaNval));
  EXPECT_FLOAT_EQ(*NaNval_2, *test_float);
} */

/* Tests functionality of not_uint8() */
TEST(NotTest, NotUint8Test) {
  not_tester nt = not_tester("NotTesterInstance",45);
  uint8_t val = 0;
  nt.seed_buf("0");
  EXPECT_FALSE(nt.not_uint8(val));
  nt.seed_buf("255");
  EXPECT_FALSE(nt.not_uint8(val));
  nt.seed_buf("256");
  EXPECT_TRUE(nt.not_uint8(val));
}

/* Tests functionality of not_uint16() */
TEST(NotTest, NotUint16Test) {
  not_tester nt = not_tester("NotTesterInstance",45);
  uint16_t val = 0;
  nt.seed_buf("0");
  EXPECT_FALSE(nt.not_uint16(val));
  nt.seed_buf("65535");
  EXPECT_FALSE(nt.not_uint16(val));
  nt.seed_buf("65536");
  EXPECT_TRUE(nt.not_uint16(val));
}

/* Tests functionality of not_ndigits() */
TEST(NotTest, NotNDigitsTest) {
  not_tester nt = not_tester("NotTesterInstance",45);
  int n = 9;
  int value;
  nt.seed_buf("987654321");
  EXPECT_FALSE(nt.not_ndigits(n, value));
  nt.seed_buf("987654321");
  n = 12;
  EXPECT_TRUE(nt.not_ndigits(n, value));
}

/* Tests functionality of not_str() */
TEST(NotTest, NotStrTest) {
  not_tester nt = not_tester("NotTesterInstance",45);
  const char *comparison = "Match";
  int len = 5;
  nt.seed_buf("Matchbook");
  EXPECT_FALSE(nt.not_str(comparison,len));
  len = 10;
  EXPECT_TRUE(nt.not_str(comparison,len));
  EXPECT_EQ(nt.get_cp(),5);
  nt.seed_buf("March");
  EXPECT_TRUE(nt.not_str(comparison, len));
  EXPECT_EQ(nt.get_cp(),2);
}

/* Tests functionality of not_bin() */
TEST(NotTest, NotBinTest) {
  not_tester nt = not_tester("NotTesterInstance",45);
  int nbits = 4;
  uint16_t word = 0;
  uint16_t answer = 15;
  nt.seed_buf("1111");
  EXPECT_FALSE(nt.not_bin(nbits,word));
  EXPECT_EQ(word, answer);
}

/* Main method */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}