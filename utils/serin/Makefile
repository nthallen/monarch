include /usr/local/share/monarch/appgen.mk
CPPFLAGS=-I/usr/local/include
CXXFLAGS+=-Wall -g
CFLAGS=-Wall -g
LDFLAGS=-L/usr/local/lib -Wl,-rpath -Wl,/usr/local/lib
CXX=g++
LINK.cxx=$(CXX) $(AG_LDFLAGS) $(LDFLAGS)

serin : serin.o serinoui.o
	/bin/rm -f $@; $(LINK.cxx) -o $@ serin.o serinoui.o -ldasio -lnl -lpthread
serinoui.cc : serin.oui
	$(OUI) -o serinoui.cc serin.oui

.PHONY : all clean install
all : serin
install : serin
	@cp -vpu serin /usr/local/bin
clean :
	rm -f *.o serinoui.cc serin FullBuild.*
