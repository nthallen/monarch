LGR_OBJ=lgr.o lgroui.o
CXXFLAGS=-I/usr/local/include -g -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-ldasio -ltm -lnl
.PHONY : install clean all
all : lgr
lgr : $(LGR_OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o lgr $(LGR_OBJ) $(LIBS)
lgr.o : lgr.cc lgr.h
lgroui.cc : lgr.oui
	oui -o lgroui.cc lgr.oui

install : lgr
	@cp -vp lgr /usr/local/bin
clean :
	rm -f $(LGR_OBJ) lgr FullBuild.* lgroui.cc
