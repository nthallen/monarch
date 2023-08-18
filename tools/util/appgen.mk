# make include files for monarch appgen

# CXX and CXXLINK are used for compiling and linking c++ apps
# We need to use the same compiler that is used in building
# our c++ libs (tmpp, disp)
# CXX=g++ # (this is the GNU Make default
CXXLINK=$(CXX)

# If our c++ libraries (tmpp, disp) are built using cc, we can use these
# definitions:
# CXX=cc
# CXXLINK=cc -lang-c++

# AG_LDFLAGS=-L/usr/local/lib -Wl,-rpath -Wl,/usr/local/lib -L/usr/pkg/lib -Wl,-rpath -Wl,/usr/pkg/lib
ifdef CROSS_COMPILE
ifdef CROSS_STAGE
CPPFLAGS=-I$(CROSS_STAGE)/include $(AG_CPPFLAGS)
AG_LIBDIR=$(CROSS_STAGE)/lib
else
CPPFLAGS=-I/opt/monarch/am335x/include $(AG_CPPFLAGS)
AG_LIBDIR=/opt/monarch/am335x/lib
endif
else
CPPFLAGS=-I/usr/local/include $(AG_CPPFLAGS)
AG_LIBDIR=/usr/local/lib
endif
AG_LDFLAGS=-L$(AG_LIBDIR)

CXXFLAGS+=$(CPPFLAGS)
LINK.args=$(CPPFLAGS) $(CXXFLAGS) $(AG_LDFLAGS) $(LDFLAGS) -o $@
LINK.norm=$(CC) $(LINK.args)
LINK.priv=/bin/rm -f $@; $(LINK.norm)
LINK.normCXX=$(CXXLINK) $(LINK.args)
LINK.privCXX=/bin/rm -f $@; $(LINK.normCXX)
TMCREV=tmc
TMC=$(TMCREV) -s -o $@ $(TMCFLAGS)
TMC.col=name=$@; $(TMC) -p -V $${name%col.cc}.pcm -c -D tm.dac $(COLFLAGS)
OUIDIR=/usr/local/share/monarch/oui
OUI=oui -o $@
OUIUSE=echo usemsg $@
LIBSRC=/usr/local/share/monarch
CMDGEN=cmdgen -o $@
COMPILE.clt=$(COMPILE.cc) -o $@ -D CLIENT
COMPILE.cltnc=$(COMPILE.cc) -o $@ -D CLIENT -D NCT_INTERFACE=1
COMPILE.srvr=$(COMPILE.cc) -o $@ -D SERVER
COMPILE.txsrvr=$(COMPILE.cc) -o $@ -D SERVER -D TRANSMITTING
COMPILE.sws=swscomp -o $@ -p SWData -A
COMPILE.tbl=phtable
COMPILE.tblnc=nctable
AWK=awk > $@ -f $(LIBSRC)
FLD2DISP=$(AWK)/fld2disp.awk
EDF2EXT=$(AWK)/edf2ext.awk
# PROMOTE was a semi-secure way of making an executable setuid root.
# It has not been necessary in Monarch. I have repurposed the stub
# here as a hack to work around a Cygwin timing issue. The first
# time a program is run after being compiled, Cygwin has to perform
# a rebase operation which takes several seconds. This is a problem
# if we are waiting for a server to indicate it is alive. Instead
# of waiting for that to happen later in the build (when compiling
# the algorithm), I run it here with -h to take care of the rebase.
# PROMOTE=echo promote /usr/local/sbin/promote
PROMOTE=cygrebase() { echo "Rebasing $$1"; ./$$1 -h >/dev/null; }; cygrebase
SLP2CMD=$(AWK)/slp2cmd.awk
SLP2SOL=$(AWK)/slp2sol.awk
EDF2OUI=$(AWK)/edf2oui.awk
TMG2TMC=tmg2tmc > $@
CYCLE=cycle > $@
TABLE=phtable > $@
NCTABLE=nctable > $@
DATAATTR=data_attr > $@
SERVER=srvr() { $$1 -V 2>/dev/null & waitfor /var/run/monarch/none/cmd 3 || { echo $$1 failed >&2; return 1; }; }; srvr
TMAREV=tmcalgo
TMCALGO=$(TMAREV) -o $@
# SOLFMT=sft () { cat $$* >$@tmp; solfmt -o$@ $@tmp; rm $@tmp; }; sft
SOLFMT=solfmt -o$@
GENUI_ENG_DIR=../eng
GENUI2ENG=genui -d $(GENUI_ENG_DIR) -o $@ -c
GENUI2JSON=genui -d $(GENUI_ENG_DIR) -o $@ -j
GENUI2CSV=genui -o $@ -c

# PHOTON Test:
# If /dev/photon is not writable, phtable will fail, but we also
# probably don't need the photon versions of display programs.
# If the generated .tmc file is empty, the executable will still
# link and run, but won't do anything useful. So if /dev/photon
# is not writable, we'll just generate an empty output file.
# Then when we make, if /dev/photon is writable and these output
# files are empty, we'll remove them, forcing a remake.
WPHOTON := $(shell [ -w /dev/photon ] && echo YES)
%tbl.tmc : %.tbl
ifeq ($(WPHOTON),YES)
	$(COMPILE.tbl) -o $@.tmp -d $@.dep.tmp $<
	mv $@.tmp $@
	{ echo -n "$@ :"; cat $@.dep.tmp; } > $@.dep
	rm $@.dep.tmp
else
	cat $(LIBSRC)/nulltbl.tmc > $@
endif

%tblnc.tmc : %.tbl
	$(COMPILE.tblnc) -o $@.tmp -d $@.dep.tmp $<
	mv $@.tmp $@
	{ echo -n "$@ :"; cat $@.dep.tmp; } > $@.dep
	rm $@.dep.tmp
