include /usr/local/share/linkeng/appgen.mk
CPPFLAGS=-I/usr/local/include
CXXFLAGS=-Wall -g
CFLAGS=-Wall -g
LDFLAGS=-L/usr/local/lib -Wl,-rpath -Wl,/usr/local/lib
CXX=g++
LINK.cxx=$(CXX) $(AG_LDFLAGS) $(LDFLAGS)

rdr : rdr.o rdroui.o
	/bin/rm -f $@; $(LINK.cxx) -o $@ rdr.o rdroui.o -ldasio -lnl -lpthread
rdroui.cc : rdr.oui
	$(OUI) -o rdroui.cc rdr.oui

.PHONY : all clean install
all : rdr
install : rdr
	@cp -vpu rdr /usr/local/bin
clean :
	rm -f *.o rdroui.cc rdr FullBuild.*
