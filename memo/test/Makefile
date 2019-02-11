TEST_MSG_OBJ=test_msg.o test_msgoui.o
CFLAGS=-I/usr/local/include -Wall
CXXFLAGS=-g
LDFLAGS=-L ~/sw/le-dasng/build-native/dasio/src -L/usr/local/lib
LIBS=-ldasio -ltm -lnl
test_msg : $(TEST_MSG_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test_msg $(TEST_MSG_OBJ) $(LIBS)
test_msg.o : test_msg.cc
test_msgoui.cc : test_msg.oui
	oui -o test_msgoui.cc test_msg.oui

.PHONY : install clean all
all : test_msg
clean :
	rm -f $(TEST_MSG_OBJ) test_msg FullBuild.*
