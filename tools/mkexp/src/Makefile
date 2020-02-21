# Invoking: appgen_module TMbase X 
# Makefile Generated Wed Feb 19 14:38:30 EST 2020
MNC=Demo
SPECFILE=Demo.spec
PCMFILE=Demo.pcm
SRC=base.tmc /usr/local/share/linkeng/tdrift.tmc
SRC+=/usr/local/share/linkeng/cpu_usage.tmc
SRC+=/usr/local/share/linkeng/tmdf.tmc freemem.tmc
SRC+=/usr/local/share/linkeng/flttime.tmc Demo.tbl Demo.tma Demo.doit
SRC+=/usr/local/share/linkeng/root.cmd
SRC+=/usr/local/share/linkeng/getcon.cmd
SRC+=/usr/local/share/linkeng/tdrift_col.tmc
SRC+=/usr/local/share/linkeng/cpu_usage_col.tmc
SRC+=/usr/local/share/linkeng/tmdf_col.tmc
SRC+=/usr/local/share/linkeng/freemem_col.tmc TMbase.genui Demo.pcm
TOOL=Demo.spec Makefile
SCRIPT=
OBJ=Demotblnc.tmc Demodispnc.cc Demodispncoui.cc Demodispnc.o
OBJ+=Demodispncoui.o Demoalgoa.tmc Demoalgo.cc Demoalgooui.cc
OBJ+=Demoalgo.o Demoalgooui.o madedoit.dep Democmd.cc Democmd.dat
OBJ+=Democmd.h Democltnc.o Democltncoui.cc Democltncoui.o Demosrvr.o
OBJ+=Demosrvroui.cc Demosrvroui.o Democol.cc tm.dac Democoloui.cc
OBJ+=Democol.o Democoloui.o Demoengext.cdf Demoengextcdf.oui
OBJ+=Demoengextcdf.tmc Demoengext.cc Demoengextoui.cc Demoengext.o
OBJ+=Demoengextoui.o Demotblnc.tmc.dep
TGT=Demodispnc Demoalgo madedoit Democltnc Demosrvr Democol
TGT+=Demoengext
IGNORE="*.o" "*.exe" "*.stackdump" Makefile
DISTRIB=services interact Demo.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit madedoit
SRCDIST=Demo.tbl Demo.tma base.tmc
SRCDIST+=/usr/local/share/linkeng/tdrift.tmc
SRCDIST+=/usr/local/share/linkeng/cpu_usage.tmc
SRCDIST+=/usr/local/share/linkeng/tmdf.tmc freemem.tmc
SRCDIST+=/usr/local/share/linkeng/flttime.tmc
TMCBASE=base.tmc /usr/local/share/linkeng/tdrift.tmc
TMCBASE+=/usr/local/share/linkeng/cpu_usage.tmc
TMCBASE+=/usr/local/share/linkeng/tmdf.tmc freemem.tmc
TMCBASE+=/usr/local/share/linkeng/flttime.tmc
CMDBASE=/usr/local/share/linkeng/root.cmd
CMDBASE+=/usr/local/share/linkeng/getcon.cmd
COLBASE=/usr/local/share/linkeng/tdrift_col.tmc
COLBASE+=/usr/local/share/linkeng/cpu_usage_col.tmc
COLBASE+=/usr/local/share/linkeng/tmdf_col.tmc
COLBASE+=/usr/local/share/linkeng/freemem_col.tmc
SWSBASE=
QCLIBASE=
GENUIBASE=TMbase.genui
EXTBASE=
SPECDEPBASE=/usr/local/share/linkeng/TMbase.agm
SPECDEPBASE+=/usr/local/share/linkeng/freemem_def.tmc.in
SPECDEPBASE+=/usr/local/share/linkeng/TMbase.genui.in
SPECDEPBASE+=/usr/local/share/linkeng/TMbase.tbl.in
SPECTGTBASE=freemem.tmc TMbase.genui TMbase.tbl
SPECTGTMISS:=$(foreach file,$(SPECTGTBASE),$(if $(wildcard $(file)),,$(file)))
AG_CPPFLAGS=-std=c++11
PHTGT=
SOURCE=$(SRC) $(TOOL) $(SCRIPT)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/Demo
include /usr/local/share/linkeng/appgen.mk

.PHONY : all all-dist extdistribution distribution tidy clean clean-dist check_photon

IGNOREFILE=.gitignore
all : check_photon $(TGT) $(IGNOREFILE)
all-dist : all $(DSTRB) $(SRCDIST) VERSION
Makefile $(SPECTGTMISS) : Demo.spec $(SPECDEPBASE)
	appgen Demo.spec
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
${tab}  cmp -s $$tgt /usr/local/share/linkeng/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \\
${tab}done; true
endif
Demodispnc : Demodispnc.o Demodispncoui.o
	$(LINK.normCXX) Demodispnc.o Demodispncoui.o -ltm -lncurses -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Demodispncoui.cc
Demoalgo : Demoalgo.o Demoalgooui.o
	$(LINK.normCXX) Demoalgo.o Demoalgooui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Demoalgooui.cc
madedoit : Demo.doit
	mkdoit3 -o madedoit  Demo.doit
Democltnc : Democltnc.o Democltncoui.o
	$(LINK.normCXX) Democltnc.o Democltncoui.o -ltm -lncurses -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Democltncoui.cc
Demosrvr : Demosrvr.o Demosrvroui.o
	$(LINK.privCXX) Demosrvr.o Demosrvroui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Demosrvroui.cc
	$(PROMOTE) Demosrvr
Democol : Democol.o Democoloui.o
	$(LINK.privCXX) Democol.o Democoloui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Democoloui.cc
	$(PROMOTE) Democol
Demoengext : Demoengext.o Demoengextoui.o
	$(LINK.normCXX) Demoengext.o Demoengextoui.o -ldasio -lpthread -ltm -lnl
	$(OUIUSE) Demoengextoui.cc
Demotblnc.tmc : Demo.tbl
-include Demotblnc.tmc.dep
Demodispnc.cc : base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demotblnc.tmc VERSION
	$(TMC) base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demotblnc.tmc
Demodispncoui.cc : $(OUIDIR)/nctable.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
Demodispnc.o : Demodispnc.cc
Demodispncoui.o : Demodispncoui.cc
Demoalgoa.tmc : Demo.tma Demosrvr
	$(SERVER) ./Demosrvr
	$(TMCALGO) -V "`./Demosrvr -R`" Demo.tma
Demoalgo.cc : base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demoalgoa.tmc VERSION
	$(TMC) base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demoalgoa.tmc
Demoalgooui.cc : $(OUIDIR)/tma.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
Demoalgo.o : Demoalgo.cc
Demoalgooui.o : Demoalgooui.cc
madedoit.dep : Demo.doit
	mkdoit3 -M -o madedoit  Demo.doit
-include madedoit.dep
Democmd.cc : /usr/local/share/linkeng/root.cmd /usr/local/share/linkeng/getcon.cmd
	cmdgen_version Democmd /usr/local/share/linkeng/root.cmd /usr/local/share/linkeng/getcon.cmd
Democltnc.o : Democmd.cc
	$(COMPILE.cltnc) Democmd.cc
Democltncoui.cc : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
Democltncoui.o : Democltncoui.cc
Demosrvr.o : Democmd.cc
	$(COMPILE.srvr) Democmd.cc
Demosrvroui.cc : $(OUIDIR)/cmd_server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cmd_server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
Demosrvroui.o : Demosrvroui.cc
Democol.cc : base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc /usr/local/share/linkeng/tdrift_col.tmc /usr/local/share/linkeng/cpu_usage_col.tmc /usr/local/share/linkeng/tmdf_col.tmc /usr/local/share/linkeng/freemem_col.tmc VERSION
	$(TMC.col) base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc /usr/local/share/linkeng/tdrift_col.tmc /usr/local/share/linkeng/cpu_usage_col.tmc /usr/local/share/linkeng/tmdf_col.tmc /usr/local/share/linkeng/freemem_col.tmc
Democoloui.cc : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
Democol.o : Democol.cc
Democoloui.o : Democoloui.cc
Demoengext.cdf : TMbase.genui
	$(GENUI2ENG) TMbase.genui
Demoengextcdf.oui : Demoengext.cdf
	$(EDF2OUI) Demoengext.cdf
Demoengextcdf.tmc : Demoengext.cdf
	$(EDF2EXT) Demoengext.cdf
Demoengext.cc : base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demoengextcdf.tmc VERSION
	$(TMC) base.tmc /usr/local/share/linkeng/tdrift.tmc /usr/local/share/linkeng/cpu_usage.tmc /usr/local/share/linkeng/tmdf.tmc freemem.tmc /usr/local/share/linkeng/flttime.tmc Demoengextcdf.tmc
Demoengextoui.cc : Demoengextcdf.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
	$(OUI) Demoengextcdf.oui $(OUIDIR)/tm_client.oui $(OUIDIR)/msg.oui
Demoengext.o : Demoengext.cc
Demoengextoui.o : Demoengextoui.cc

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(IGNORE) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
