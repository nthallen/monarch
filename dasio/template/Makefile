CXXFLAGS=-Wall -g
LDFLAGS=-L/usr/local/lib
LIBS=-ldasio -lnl

.PHONY : all clean

TARGETS = template_server1 template_server2
all : $(TARGETS)
OBJ = $(TARGETS)

TS1OBJ=template_server1.o template_serveroui.o
template_server1 : $(TS1OBJ)
	$(CXX) -o template_server1 $(CXXFLAGS) $(LDFLAGS) $(TS1OBJ) $(LIBS)
OBJ += $(TS1OBJ)

TS2OBJ=template_server2.o template_serveroui.o
template_server2 : $(TS2OBJ)
	$(CXX) -o template_server1 $(CXXFLAGS) $(LDFLAGS) $(TS2OBJ) $(LIBS)
OBJ += $(TS2OBJ)

template_serveroui.o : template_serveroui.cc
template_serveroui.cc : template_server.oui
	oui -o template_serveroui.cc template_server.oui
OBJ += template_serveroui.cc

clean :
	rm $(OBJ)
