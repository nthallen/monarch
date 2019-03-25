CXXFLAGS=-g -I/usr/local/include -Wall
LDFLAGS=-g -L /usr/local/lib -Wl,-rpath -Wl,/usr/local/lib
LDLIBS=-ldasio -lnl -ltm
BFR_OBJ=bfr.o bfroui.o rundir.o
bfr : $(BFR_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o bfr $(BFR_OBJ) $(LDLIBS)
bfr.o : bfr.cc bfr.h rundir.h
rundir.o : rundir.cc rundir.h
bfroui.cc : bfr.oui
	oui -o bfroui.cc bfr.oui

.PHONY : clean
clean :
	rm -f bfr bfr.o bfroui.o bfroui.cc FullBuild.*
