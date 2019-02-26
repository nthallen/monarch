CXXFLAGS=-I/usr/local/include -I../include -g -Wall
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
subbusd.o : subbusd.cc ../include/subbusd.h
subbusdoui.cc : subbusd.oui
	oui -o subbusdoui.cc subbusd.oui


CAN_OBJ=subbusd.o subbusd_CAN.o subbusd_CANoui.o
OBJ+=subbusd_CAN subbusd_CANoui.cc
subbusd_CAN : $(CAN_OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o subbusd_CAN $(CAN_OBJ) $(LIBS)
subbusd_CAN.o : CAN/subbusd_CAN.cc CAN/subbusd_CAN.h ../include/subbusd_int.h ../include/subbusd.h
	$(CXX) $(CXXFLAGS) -c CAN/subbusd_CAN.cc
subbusd_CANoui.cc : CAN/subbusd_CAN.oui subbusd.oui
	oui -o subbusd_CANoui.cc CAN/subbusd_CAN.oui


install : $(BIN)
	@cp -vp $(BIN) /usr/local/bin
clean :
	rm -f $(OBJ)

subbusdoui.o : subbusdoui.cc
	g++ \
	-I/home/nort/SW/le-dasng/drivers/subbus/subbusd/../include -I/home/nort/SW/le-dasng/dasio/src \
	-I/home/nort/SW/le-dasng/nl/src -I/home/nort/SW/le-dasng/oui/src \
	-I/home/nort/SW/le-dasng/build-CAN/dasio/src -I/home/nort/SW/le-dasng/dasio/src -I/home/nort/SW/le-dasng/tm/src \
	-I/home/nort/SW/le-dasng/nl/src -I/home/nort/SW/le-dasng/cmdgen  -g -o subbusdoui.o -c \
	subbusdoui.cc
	
#	/usr/bin/c++.exe   -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 \
#	-I/home/nort/SW/le-dasng/drivers/subbus/subbusd/../include -I/home/nort/SW/le-dasng/drivers/dasio/src \
#	-I/home/nort/SW/le-dasng/drivers/nl/src -I/home/nort/SW/le-dasng/drivers/oui/src \
#	-I/home/nort/SW/le-dasng/build-CAN/dasio/src -I/home/nort/SW/le-dasng/dasio/src -I/home/nort/SW/le-dasng/tm/src \
#	-I/home/nort/SW/le-dasng/nl/src -I/home/nort/SW/le-dasng/cmdgen  -g -std=c++11 -o subbusdoui.o -c \
#	subbusdoui.cc
