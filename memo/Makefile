MEMO_OBJ=memo.o memooui.o
MSG_OBJ=msg.o msg_internal_oui.o
CXXFLAGS=-I/usr/local/include -g -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-ldasio -ltm -lnl
memo : $(MEMO_OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o memo $(MEMO_OBJ) $(LIBS)
msg : $(MSG_OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o msg $(MSG_OBJ) $(LIBS)
memo.o : memo.cc memo.h
msg.o : msg.cc msg_internal.h
msg_internal_oui.cc : msg_internal.oui
	oui -o msg_internal_oui.cc msg_internal.oui
memooui.cc : memo.oui
	oui -o memooui.cc memo.oui

.PHONY : install clean all
all : memo msg
install : memo msg
	@cp -vp memo msg /usr/local/bin
clean :
	rm -f $(MEMO_OBJ) memo FullBuild.* memooui.cc
	rm -f $(MSG_OBJ) msg FullBuild.* msg_internal_oui.cc
