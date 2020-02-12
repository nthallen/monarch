LDFLAGS = -L/usr/local/lib
CXXFLAGS = -I/usr/local/include -g -Wall
LIBS = -ldasio -lnl -lpthread

.PHONY : all clean
all : testmem testcpu
testmem : testmem.o
	$(CXX) -o testmem $(LDFLAGS) testmem.o $(LIBS)
testcpu : testcpu.o
	$(CXX) -o testcpu $(LDFLAGS) testcpu.o $(LIBS)
clean :
	rm -f *.o testcpu testmem
