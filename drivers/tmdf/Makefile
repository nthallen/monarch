LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L/usr/local/lib
CPPFLAGS=-I/usr/local/include
CXXFLAGS=-Wall -g
CFLAGS=-Wall -g
LIBS=-ldasio -lnl
BINDIR=/usr/local/bin
HUARPDIR=/usr/local/share/huarp
INCDIR=/usr/local/include

OBJ = tmdf.o tmdfoui.o
.PHONY : clean all install

all : tmdf

tmdf : $(OBJ)
	$(LINK.cc) -o tmdf $(OBJ) $(LIBS)
tmdfoui.cc : tmdf.oui
	oui -o tmdfoui.cc tmdf.oui

clean :
	@rm -f *.o tmdfoui.cc tmdf FullBuild*

install : tmdf tmdf.tmc tmdf_col.tmc
	@cp -vn tmdf $(BINDIR)
	@cp -vn tmdf.h $(INCDIR)
	@cp -vn tmdf.tmc tmdf_col.tmc $(HUARPDIR)
