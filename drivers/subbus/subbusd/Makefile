CXXFLAGS=-I/usr/local/include -I../ -g -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-ldasio -lnl
BIN=
OBJ=*.o *.stackdump

.PHONY : install clean all

all : subbusd

SUBBUSD_OBJ=subbusd.o subbusdoui.o
OBJ+=subbusd subbusdoui.cc
subbusd : $(SUBBUSD_OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o subbusd $(SUBBUSD_OBJ) $(LIBS)
subbusd.o : subbusd.cc subbusd.h
subbusdoui.cc : subbusd.oui
	oui -o subbusdoui.cc subbusd.oui

install : $(BIN)
	@cp -vp $(BIN) /usr/local/bin
clean :
	rm -f $(OBJ)
