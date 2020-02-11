LDFLAGS = -L/usr/local/lib
CXXFLAGS = -I/usr/local/include -g -Wall
LIBS = -ldasio -lnl
testmem : testmem.o
	$(CXX) -o testmem $(LDFLAGS) testmem.o $(LIBS)
