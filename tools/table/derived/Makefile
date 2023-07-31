SHELL   = /bin/sh

CC	= g++
CXXFLAGS	= -g -I/usr/local/include -Wl,-rpath -Wl,/usr/local/lib \
	-Dregister=
LIBS	= -L/usr/local/lib -ldasio -lnl -lncurses -lpthread

OBJS	= driver.o clpintf.o clp.o csm.o obstack.o obsave.o deftbl.o \
	CoordMap.o coord.o source.o pdl_gen.o ptg_gen.o nparam.o \
	ncbox.o PtgCommon.o VoidPtrList.o clplib.o envmod.o \
	BitSet.o treecon.o visitmap.o visitprocs.o dim.o \
	table_name.o ncmodprint.o Include.o idn.o SrcFileStack.o \
	glahead.o auxNUL.o dflteot.o tabsize.o Cint.o str.o \
	auxScanEOL.o CchStr.o Ccomment.o depfile.o Strings.o \
	ColCScope.o TableCScope.o nodecode.o treebuild.o parser.o \
	pgs_gen.o treestack.o dfltrepar.o attrmain.o

EXE	= nctable.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.cc err.h HEAD.h INIT.h FINL.h eliproto.h coord.h \
		clp.h envmod.h deftbl.h BitSet.h Strings.h SrcFileStack.h \
		CoordMap.h ColCScope.h TableCScope.h Include.h ptg_gen.h \
		pdl_gen.h treecon.h DefTableKeyList.h VoidPtrList.h \
		depfile.h source.h csm.h dim.h dimfunc.h ncmodprint.h \
		ncbox.h param.h table_name.h ncparam.h PtgCommon.h clplib.h \
		ptg.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h nodeptr.h

clpintf.o:	clpintf.cc clplib.h clpintf.h eliproto.h

clp.o:	clp.cc clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h dim.h ptg_gen.h ptg.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h

csm.o:	csm.cc csm.h csmtbl.h obsave.h obstack.h eliproto.h

obstack.o:	obstack.cc obstack.h gettext.h

obsave.o:	obsave.cc obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.cc err.h deftbl.h obstack.h obsave.h eliproto.h \
		coord.h

CoordMap.o:	CoordMap.cc obstack.h source.h csm.h err.h CoordMap.h \
		eliproto.h coord.h

coord.o:	coord.cc coord.h eliproto.h

source.o:	source.cc source.h

pdl_gen.o:	pdl_gen.cc pdl_gen.h deftbl.h dim.h ptg_gen.h eliproto.h \
		ptg.h

ptg_gen.o:	ptg_gen.cc ptg_gen.h obstack.h eliproto.h ptg.h

nparam.o:	nparam.cc param.h ncparam.h ncbox.h dim.h ptg_gen.h \
		eliproto.h ptg.h

ncbox.o:	ncbox.cc csm.h err.h ncbox.h ncmodprint.h obstack.h \
		eliproto.h coord.h ptg_gen.h ptg.h

PtgCommon.o:	PtgCommon.cc PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		obstack.h

VoidPtrList.o:	VoidPtrList.cc VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h coord.h

clplib.o:	clplib.cc csm.h clplib.h obstack.h eliproto.h

envmod.o:	envmod.cc err.h obstack.h envmod.h obsave.h eliproto.h \
		coord.h deftbl.h BitSet.h

BitSet.o:	BitSet.cc obstack.h err.h BitSet.h eliproto.h coord.h

treecon.o:	treecon.cc node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h \
		coord.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		SrcFileStack.h CoordMap.h ColCScope.h TableCScope.h \
		Include.h ptg_gen.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h depfile.h source.h csm.h dim.h dimfunc.h \
		ncmodprint.h ncbox.h param.h table_name.h ncparam.h \
		PtgCommon.h clplib.h ptg.h VoidPtr.h VoidPtrFunctionTypes.h

visitmap.o:	visitmap.cc visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		SrcFileStack.h CoordMap.h ColCScope.h err.h TableCScope.h \
		Include.h ptg_gen.h pdl_gen.h DefTableKeyList.h \
		VoidPtrList.h depfile.h source.h csm.h dim.h dimfunc.h \
		ncmodprint.h ncbox.h param.h table_name.h ncparam.h \
		PtgCommon.h clplib.h ptg.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h coord.h nodeptr.h

visitprocs.o:	visitprocs.cc HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		SrcFileStack.h CoordMap.h ColCScope.h TableCScope.h \
		Include.h ptg_gen.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h depfile.h source.h csm.h dim.h dimfunc.h \
		ncmodprint.h ncbox.h param.h table_name.h ncparam.h \
		PtgCommon.h clplib.h eliproto.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h coord.h nodeptr.h

dim.o:	dim.cc dim.h err.h pdl_gen.h dimfunc.h eliproto.h coord.h \
		deftbl.h ptg_gen.h ptg.h

table_name.o:	table_name.cc table_name.h csm.h pdl_gen.h obstack.h \
		eliproto.h deftbl.h dim.h ptg_gen.h ptg.h

ncmodprint.o:	ncmodprint.cc ncmodprint.h ptg_gen.h csm.h eliproto.h ptg.h \
		obstack.h

Include.o:	Include.cc Include.h obstack.h err.h csm.h idn.h gla.h \
		SrcFileStack.h CoordMap.h clp.h eliproto.h source.h coord.h \
		clplib.h pdl_gen.h DefTableKeyList.h deftbl.h dim.h \
		ptg_gen.h ptg.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

idn.o:	idn.cc err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h coord.h

SrcFileStack.o:	SrcFileStack.cc obstack.h

glahead.o:	glahead.cc err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h \
		coord.h

auxNUL.o:	auxNUL.cc source.h coord.h eliproto.h

dflteot.o:	dflteot.cc 

tabsize.o:	tabsize.cc 

Cint.o:	Cint.cc err.h eliproto.h coord.h

str.o:	str.cc csm.h obstack.h eliproto.h

auxScanEOL.o:	auxScanEOL.cc eliproto.h err.h gla.h source.h ScanProc.h \
		coord.h

CchStr.o:	CchStr.cc err.h source.h gla.h csm.h tabsize.h ScanProc.h \
		eliproto.h coord.h obstack.h

Ccomment.o:	Ccomment.cc err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h coord.h

depfile.o:	depfile.cc depfile.h err.h clp.h csm.h clplib.h pdl_gen.h \
		DefTableKeyList.h eliproto.h deftbl.h dim.h ptg_gen.h ptg.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h \
		coord.h

Strings.o:	Strings.cc Strings.h csm.h obstack.h eliproto.h

ColCScope.o:	ColCScope.cc ColCScope.h envmod.h deftbl.h obstack.h \
		BitSet.h eliproto.h

TableCScope.o:	TableCScope.cc TableCScope.h envmod.h deftbl.h obstack.h \
		BitSet.h eliproto.h

nodecode.o:	nodecode.cc nodecode.h

treebuild.o:	treebuild.cc eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h dim.h ptg_gen.h ptg.h obstack.h clplib.h \
		DefTableKeyList.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

parser.o:	parser.cc err.h gla.h gsdescr.h reparatur.h pgs_gen.h \
		eliproto.h coord.h parsops.h

pgs_gen.o:	pgs_gen.cc gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h coord.h nodeptr.h clp.h envmod.h deftbl.h \
		BitSet.h Strings.h SrcFileStack.h CoordMap.h ColCScope.h \
		TableCScope.h Include.h ptg_gen.h pdl_gen.h treecon.h \
		DefTableKeyList.h VoidPtrList.h depfile.h source.h csm.h \
		dim.h dimfunc.h ncmodprint.h ncbox.h param.h table_name.h \
		ncparam.h PtgCommon.h clplib.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

treestack.o:	treestack.cc err.h treestack.h eliproto.h coord.h nodeptr.h

dfltrepar.o:	dfltrepar.cc err.h reparatur.h eliproto.h coord.h

attrmain.o:	attrmain.cc treestack.h visitprocs.h nodeptr.h err.h \
		eliproto.h coord.h HEAD.h node.h treecon.h clp.h envmod.h \
		deftbl.h BitSet.h Strings.h SrcFileStack.h CoordMap.h \
		ColCScope.h TableCScope.h Include.h ptg_gen.h pdl_gen.h \
		DefTableKeyList.h VoidPtrList.h depfile.h source.h csm.h \
		dim.h dimfunc.h ncmodprint.h ncbox.h param.h table_name.h \
		ncparam.h PtgCommon.h clplib.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

