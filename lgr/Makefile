CFLAGS=-Wall -g
CXXFLAGS=-Wall -g
# I specify these two to:
#  a) override the setting CXX=cc in appgen.mk
#  b) use g++ to link instead of $(CC)=cc, which ties into a different library
LINK.cxx=$(CXX) $(AG_LDFLAGS) $(LDFLAGS)

lgr : lgr.o lgroui.o
	$(LINK.cxx) -o lgr lgr.o lgroui.o -ldasio -lnl
lgr.o : lgr.cc
lgroui.c : lgr.oui
	oui -o lgroui.c lgr.oui
.PHONY : all install clean
all : lgr
install : lgr
	cp -vf lgr /usr/local/bin
clean :
	rm -f *.o lgr lgroui.c FullBuild.*