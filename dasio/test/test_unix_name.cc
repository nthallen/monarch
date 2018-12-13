/** @file test_unix_name.cc */
#include <stdlib.h>
#include "dasio/socket.h"
#include "gtest/gtest.h"

const char *opt_string = "vo:mV";

/* This method tests functionality of the unix_name constructor, and whether I know how to invoke it */
TEST(NameTest,UnixNameBadService1) {
  DAS_IO::Socket::unix_name_t unix_name;
  EXPECT_FALSE(unix_name.set_service("bad service name"));
}

TEST(NameTest,UnixNameBadService2) {
  DAS_IO::Socket::unix_name_t unix_name;
  EXPECT_FALSE(unix_name.set_service(
    "A123456789" "A123456789" "A123456789" "A123456789" "A123456789"
    "A123456789" "A123456789" "A123456789" "A123456789" "A123456789"));
}

TEST(NameTest,UnixNameGoodService) {
  DAS_IO::Socket::unix_name_t unix_name;
  EXPECT_TRUE(unix_name.set_service("cmd"));
}

/* This method tests functionality of the unix_name constructor, and whether I know how to invoke it */
TEST(NameTest,ExpNameSetup) {
  DAS_IO::Socket::unix_name_t unix_name;
  putenv((char*)"Experiment=A bad experiment");
  EXPECT_FALSE(unix_name.set_service("cmd"));
  putenv((char*)"Experiment=Also/bad/experiment");
  EXPECT_FALSE(unix_name.set_service("cmd"));
  putenv((char*)"Experiment=SCoPEx");
  EXPECT_TRUE(unix_name.set_service("cmd"));
}

/* This method tests functionality of the lock function */
TEST(NameTest,UnixNameLockSetup) {
  DAS_IO::Socket::unix_name_t unix_name;
  putenv((char*)"Experiment=Locker"); // /var/run/Locker.lock
  EXPECT_TRUE(unix_name.set_service("cmd"));
  EXPECT_TRUE(unix_name.lock());
  EXPECT_TRUE(unix_name.is_locked());
  EXPECT_TRUE(unix_name.lock()); // locking twice is OK
  unix_name.unlock();
  EXPECT_FALSE(unix_name.is_locked());
}

/* This method tests functionality of the lock function */
TEST(NameTest,LockChecks) {
  DAS_IO::Socket::unix_name_t unix_name1, unix_name2;
  putenv((char*)"Experiment=Locker"); // /var/run/Locker.lock
  EXPECT_TRUE(unix_name1.set_service("cmd"));
  EXPECT_TRUE(unix_name2.set_service("cmd"));
  EXPECT_TRUE(unix_name1.lock());
  EXPECT_TRUE(unix_name1.is_locked());
  EXPECT_FALSE(unix_name2.lock());
  unix_name1.unlock();
  EXPECT_TRUE(unix_name2.lock());
  unix_name2.unlock();
}

/* This method tests functionality of the claim_server function */
TEST(NameTest,ClaimServer) {
  DAS_IO::Socket::unix_name_t unix_name;
  putenv((char*)"Experiment=Locker"); // /var/run/Locker.lock
  EXPECT_FALSE(unix_name.is_server());
  EXPECT_TRUE(unix_name.set_service("cmd"));
  EXPECT_FALSE(unix_name.is_locked());
  EXPECT_TRUE(unix_name.lock());
  EXPECT_TRUE(unix_name.is_locked());
  EXPECT_TRUE(unix_name.claim_server());
  EXPECT_FALSE(unix_name.is_locked());
  EXPECT_TRUE(unix_name.is_server());
  // Let's check to see if files exist:
  //   /var/run/Locker directory
  //   /var/run/Locker.lock
  //   /var/run/Locker/cmd.pid
  //   /var/run/Locker/cmd   the socket
  unix_name.release_server();
  // Let's check to see that these files do not exist:
  //   /var/run/Locker directory
  //   /var/run/Locker.lock
  //   /var/run/Locker/cmd.pid
  //   /var/run/Locker/cmd   the socket
  EXPECT_FALSE(unix_name.is_server());
}

/* Test ClaimServer Failure */
TEST(NameTest,ClaimServerConflict) {
  DAS_IO::Socket::unix_name_t unix_name1, unix_name2;
  putenv((char*)"Experiment=Locker"); // /var/run/Locker.lock
  EXPECT_FALSE(unix_name1.is_server());
  EXPECT_TRUE(unix_name1.set_service("cmd"));
  EXPECT_FALSE(unix_name1.is_locked());
  EXPECT_TRUE(unix_name1.lock());
  EXPECT_TRUE(unix_name1.is_locked());
  EXPECT_TRUE(unix_name1.claim_server());
  EXPECT_FALSE(unix_name1.is_locked());
  EXPECT_TRUE(unix_name1.is_server());

  EXPECT_FALSE(unix_name2.is_server());
  EXPECT_TRUE(unix_name2.set_service("cmd"));
  EXPECT_FALSE(unix_name2.is_locked());
  EXPECT_TRUE(unix_name2.lock());
  EXPECT_TRUE(unix_name2.is_locked());
  EXPECT_FALSE(unix_name2.claim_server());
  EXPECT_FALSE(unix_name2.is_locked());
  EXPECT_FALSE(unix_name2.is_server());
  // Let's check to see if files exist:
  //   /var/run/Locker directory
  //   /var/run/Locker.lock
  //   /var/run/Locker/cmd.pid
  //   /var/run/Locker/cmd   the socket
  unix_name1.release_server();
  // Let's check to see that these files do not exist:
  //   /var/run/Locker directory
  //   /var/run/Locker.lock
  //   /var/run/Locker/cmd.pid
  //   /var/run/Locker/cmd   the socket
  EXPECT_FALSE(unix_name1.is_server());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
