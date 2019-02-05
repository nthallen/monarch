MEMO_OBJ=memo.o memooui.o
CFLAGS=-I/usr/local/include -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-ldasio -ltm -lnl
memo : $(MEMO_OBJ)
	$(CXX) $(LDFLAGS) -o memo $(MEMO_OBJ) $(LIBS)
memo.o : memo.cc memo.h
memooui.cc : memo.oui
	oui -o memooui.cc memo.oui

.PHONY : install clean all
all : memo
install : memo
	@cp -vp memo /usr/local/bin
clean :
	rm -f $(MEMO_OBJ) memo FullBuild.*
