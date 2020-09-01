# Invoking: appgen_module TMbase X 
# Makefile Generated Wed Feb 19 14:38:30 EST 2020
MNC=@DEMO@
SPECFILE=@DEMO@.spec
PCMFILE=@DEMO@.pcm
SRC=base.tmc /usr/local/share/monarch/modules/tdrift.tmc
SRC+=/usr/local/share/monarch/modules/cpu_usage.tmc
SRC+=/usr/local/share/monarch/modules/tmdf.tmc freemem.tmc
SRC+=/usr/local/share/monarch/modules/flttime.tmc @DEMO@.tbl @DEMO@.tma @DEMO@.doit
SRC+=/usr/local/share/monarch/modules/root.cmd
SRC+=/usr/local/share/monarch/modules/getcon.cmd
SRC+=/usr/local/share/monarch/modules/tdrift_col.tmc
SRC+=/usr/local/share/monarch/modules/cpu_usage_col.tmc
SRC+=/usr/local/share/monarch/modules/tmdf_col.tmc
SRC+=/usr/local/share/monarch/modules/freemem_col.tmc TMbase.genui @DEMO@.pcm
TOOL=@DEMO@.spec Makefile
SCRIPT=
OBJ=@DEMO@tblnc.tmc @DEMO@dispnc.cc @DEMO@dispncoui.cc @DEMO@dispnc.o
OBJ+=@DEMO@dispncoui.o @DEMO@algoa.tmc @DEMO@algo.cc @DEMO@algooui.cc
OBJ+=@DEMO@algo.o @DEMO@algooui.o madedoit.dep @DEMO@cmd.cc @DEMO@cmd.dat
OBJ+=@DEMO@cmd.h @DEMO@cltnc.o @DEMO@cltncoui.cc @DEMO@cltncoui.o @DEMO@srvr.o
OBJ+=@DEMO@srvroui.cc @DEMO@srvroui.o @DEMO@col.cc tm.dac @DEMO@coloui.cc
OBJ+=@DEMO@col.o @DEMO@coloui.o @DEMO@engext.cdf @DEMO@engextcdf.oui
OBJ+=@DEMO@engextcdf.tmc @DEMO@engext.cc @DEMO@engextoui.cc @DEMO@engext.o
OBJ+=@DEMO@engextoui.o @DEMO@tblnc.tmc.dep
TGT=@DEMO@dispnc @DEMO@algo madedoit @DEMO@cltnc @DEMO@srvr @DEMO@col
TGT+=@DEMO@engext
IGNORE="*.o" "*.exe" "*.stackdump" Makefile
DISTRIB=services interact @DEMO@.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit madedoit
SRCDIST=@DEMO@.tbl @DEMO@.tma base.tmc
SRCDIST+=/usr/local/share/monarch/modules/tdrift.tmc
SRCDIST+=/usr/local/share/monarch/modules/cpu_usage.tmc
SRCDIST+=/usr/local/share/monarch/modules/tmdf.tmc freemem.tmc
SRCDIST+=/usr/local/share/monarch/modules/flttime.tmc
TMCBASE=base.tmc /usr/local/share/monarch/modules/tdrift.tmc
TMCBASE+=/usr/local/share/monarch/modules/cpu_usage.tmc
TMCBASE+=/usr/local/share/monarch/modules/tmdf.tmc freemem.tmc
TMCBASE+=/usr/local/share/monarch/modules/flttime.tmc
CMDBASE=/usr/local/share/monarch/modules/root.cmd
CMDBASE+=/usr/local/share/monarch/modules/getcon.cmd
COLBASE=/usr/local/share/monarch/modules/tdrift_col.tmc
COLBASE+=/usr/local/share/monarch/modules/cpu_usage_col.tmc
COLBASE+=/usr/local/share/monarch/modules/tmdf_col.tmc
COLBASE+=/usr/local/share/monarch/modules/freemem_col.tmc
SWSBASE=
QCLIBASE=
GENUIBASE=TMbase.genui
EXTBASE=
SPECDEPBASE=/usr/local/share/monarch/modules/TMbase.agm
SPECDEPBASE+=/usr/local/share/monarch/modules/freemem_def.tmc.in
SPECDEPBASE+=/usr/local/share/monarch/modules/TMbase.genui.in
SPECDEPBASE+=/usr/local/share/monarch/modules/TMbase.tbl.in
SPECTGTBASE=freemem.tmc TMbase.genui TMbase.tbl
SPECTGTMISS:=$(foreach file,$(SPECTGTBASE),$(if $(wildcard $(file)),,$(file)))
AG_CPPFLAGS=-std=c++11
PHTGT=
SOURCE=$(SRC) $(TOOL) $(SCRIPT)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/@DEMO@
include /usr/local/share/monarch/appgen.mk

.PHONY : all all-dist extdistribution distribution tidy clean clean-dist check_photon

IGNOREFILE=.gitignore
all : check_photon $(TGT) $(IGNOREFILE)
all-dist : all $(DSTRB) $(SRCDIST) VERSION
Makefile $(SPECTGTMISS) : @DEMO@.spec $(SPECDEPBASE)
	appgen @DEMO@.spec
VERSION=`cat VERSION`
extdistribution : all-dist
	@distribute_check $(TGTDIR)/bin/$(VERSION) $(PCMFILE)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
check_photon :
ifeq ($(WPHOTON),YES)
${tab}@for tgt in $(PHTGT); do \\
${tab}  cmp -s $$tgt /usr/local/share/monarch/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \\
${tab}done; true
endif
@DEMO@dispnc : @DEMO@dispnc.o @DEMO@dispncoui.o
	$(LINK.normCXX) @DEMO@dispnc.o @DEMO@dispncoui.o -ltm -lncurses -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@dispncoui.cc
@DEMO@algo : @DEMO@algo.o @DEMO@algooui.o
	$(LINK.normCXX) @DEMO@algo.o @DEMO@algooui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@algooui.cc
madedoit : @DEMO@.doit
	mkdoit3 -o madedoit  @DEMO@.doit
@DEMO@cltnc : @DEMO@cltnc.o @DEMO@cltncoui.o
	$(LINK.normCXX) @DEMO@cltnc.o @DEMO@cltncoui.o -ltm -lncurses -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@cltncoui.cc
@DEMO@srvr : @DEMO@srvr.o @DEMO@srvroui.o
	$(LINK.privCXX) @DEMO@srvr.o @DEMO@srvroui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@srvroui.cc
	$(PROMOTE) @DEMO@srvr
@DEMO@col : @DEMO@col.o @DEMO@coloui.o
	$(LINK.privCXX) @DEMO@col.o @DEMO@coloui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@coloui.cc
	$(PROMOTE) @DEMO@col
@DEMO@engext : @DEMO@engext.o @DEMO@engextoui.o
	$(LINK.normCXX) @DEMO@engext.o @DEMO@engextoui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) @DEMO@engextoui.cc
@DEMO@tblnc.tmc : @DEMO@.tbl
-include @DEMO@tblnc.tmc.dep
@DEMO@dispnc.cc : base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@tblnc.tmc VERSION
	$(TMC) base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@tblnc.tmc
@DEMO@dispncoui.cc : $(OUIDIR)/nctable.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
@DEMO@dispnc.o : @DEMO@dispnc.cc
@DEMO@dispncoui.o : @DEMO@dispncoui.cc
@DEMO@algoa.tmc : @DEMO@.tma @DEMO@srvr
	$(SERVER) ./@DEMO@srvr
	$(TMCALGO) -V "`./@DEMO@srvr -R`" @DEMO@.tma
@DEMO@algo.cc : base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@algoa.tmc VERSION
	$(TMC) base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@algoa.tmc
@DEMO@algooui.cc : $(OUIDIR)/tma.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
@DEMO@algo.o : @DEMO@algo.cc
@DEMO@algooui.o : @DEMO@algooui.cc
madedoit.dep : @DEMO@.doit
	mkdoit3 -M -o madedoit  @DEMO@.doit
-include madedoit.dep
@DEMO@cmd.cc : /usr/local/share/monarch/modules/root.cmd /usr/local/share/monarch/modules/getcon.cmd
	cmdgen_version @DEMO@cmd /usr/local/share/monarch/modules/root.cmd /usr/local/share/monarch/modules/getcon.cmd
@DEMO@cltnc.o : @DEMO@cmd.cc
	$(COMPILE.cltnc) @DEMO@cmd.cc
@DEMO@cltncoui.cc : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
@DEMO@cltncoui.o : @DEMO@cltncoui.cc
@DEMO@srvr.o : @DEMO@cmd.cc
	$(COMPILE.srvr) @DEMO@cmd.cc
@DEMO@srvroui.cc : $(OUIDIR)/cmd_server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cmd_server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
@DEMO@srvroui.o : @DEMO@srvroui.cc
@DEMO@col.cc : base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc /usr/local/share/monarch/modules/tdrift_col.tmc /usr/local/share/monarch/modules/cpu_usage_col.tmc /usr/local/share/monarch/modules/tmdf_col.tmc /usr/local/share/monarch/modules/freemem_col.tmc VERSION
	$(TMC.col) base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc /usr/local/share/monarch/modules/tdrift_col.tmc /usr/local/share/monarch/modules/cpu_usage_col.tmc /usr/local/share/monarch/modules/tmdf_col.tmc /usr/local/share/monarch/modules/freemem_col.tmc
@DEMO@coloui.cc : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
@DEMO@col.o : @DEMO@col.cc
@DEMO@coloui.o : @DEMO@coloui.cc
@DEMO@engext.cdf : TMbase.genui
	$(GENUI2ENG) TMbase.genui
@DEMO@engextcdf.oui : @DEMO@engext.cdf
	$(EDF2OUI) @DEMO@engext.cdf
@DEMO@engextcdf.tmc : @DEMO@engext.cdf
	$(EDF2EXT) @DEMO@engext.cdf
@DEMO@engext.cc : base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@engextcdf.tmc VERSION
	$(TMC) base.tmc /usr/local/share/monarch/modules/tdrift.tmc /usr/local/share/monarch/modules/cpu_usage.tmc /usr/local/share/monarch/modules/tmdf.tmc freemem.tmc /usr/local/share/monarch/modules/flttime.tmc @DEMO@engextcdf.tmc
@DEMO@engextoui.cc : @DEMO@engextcdf.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) @DEMO@engextcdf.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
@DEMO@engext.o : @DEMO@engext.cc
@DEMO@engextoui.o : @DEMO@engextoui.cc

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(IGNORE) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
