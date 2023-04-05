SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obstack.o obsave.o deftbl.o \
	err.o source.o coord.o pdl_gen.o VoidPtrList.o clplib.o \
	envmod.o BitSet.o treecon.o nodecode.o treebuild.o parser.o \
	glahead.o auxNUL.o auxEOF.o dflteot.o tabsize.o idn.o \
	Cint.o auxScanEOL.o str.o Ccomment.o pgs_gen.o treestack.o \
	dfltrepar.o attrmain.o visitprocs.o pickres.o ptg_gen.o \
	linepos.o PtgCommon.o Strings.o visitmap.o CScope.o

EXE	= qclicomp.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h coord.h \
		clp.h envmod.h deftbl.h BitSet.h Strings.h CScope.h \
		ptg_gen.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h PtgCommon.h source.h qclicomp.h clplib.h \
		csm.h obstack.h ptg.h VoidPtr.h VoidPtrFunctionTypes.h \
		nodeptr.h

clpintf.o:	clpintf.c clplib.h clpintf.h eliproto.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h qclicomp.h err.h ptg_gen.h \
		coord.h obstack.h ptg.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

csm.o:	csm.c csm.h csmtbl.h obsave.h obstack.h eliproto.h

obstack.o:	obstack.c obstack.h gettext.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h \
		coord.h

err.o:	err.c err.h source.h eliproto.h coord.h

source.o:	source.c source.h

coord.o:	coord.c coord.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h qclicomp.h eliproto.h err.h \
		csm.h ptg_gen.h coord.h obstack.h ptg.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h coord.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h eliproto.h \
		coord.h deftbl.h BitSet.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h coord.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h \
		coord.h clp.h envmod.h deftbl.h BitSet.h Strings.h CScope.h \
		ptg_gen.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h PtgCommon.h source.h qclicomp.h clplib.h \
		csm.h ptg.h VoidPtr.h VoidPtrFunctionTypes.h

nodecode.o:	nodecode.c nodecode.h

treebuild.o:	treebuild.c eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h qclicomp.h err.h ptg_gen.h coord.h \
		obstack.h ptg.h clplib.h DefTableKeyList.h VoidPtrList.h \
		VoidPtr.h VoidPtrFunctionTypes.h

parser.o:	parser.c err.h gla.h gsdescr.h reparatur.h pgs_gen.h \
		eliproto.h coord.h parsops.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h \
		coord.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h coord.h

Cint.o:	Cint.c err.h eliproto.h coord.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h \
		coord.h

str.o:	str.c csm.h obstack.h eliproto.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h coord.h

pgs_gen.o:	pgs_gen.c gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h coord.h nodeptr.h clp.h envmod.h deftbl.h \
		BitSet.h Strings.h CScope.h ptg_gen.h pdl_gen.h treecon.h \
		DefTableKeyList.h VoidPtrList.h PtgCommon.h source.h \
		qclicomp.h clplib.h csm.h obstack.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h

treestack.o:	treestack.c err.h treestack.h eliproto.h coord.h nodeptr.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h coord.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h err.h \
		eliproto.h coord.h HEAD.h node.h treecon.h clp.h envmod.h \
		deftbl.h BitSet.h Strings.h CScope.h ptg_gen.h pdl_gen.h \
		DefTableKeyList.h VoidPtrList.h PtgCommon.h source.h \
		qclicomp.h clplib.h csm.h obstack.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		CScope.h ptg_gen.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h PtgCommon.h source.h qclicomp.h clplib.h \
		eliproto.h csm.h coord.h obstack.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h nodeptr.h

pickres.o:	pickres.c qclicomp.h err.h csm.h ptg_gen.h eliproto.h \
		coord.h obstack.h ptg.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

linepos.o:	linepos.c ptg_gen.h qclicomp.h eliproto.h ptg.h err.h csm.h \
		coord.h obstack.h

PtgCommon.o:	PtgCommon.c PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		obstack.h

Strings.o:	Strings.c Strings.h csm.h obstack.h eliproto.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		CScope.h err.h ptg_gen.h pdl_gen.h DefTableKeyList.h \
		VoidPtrList.h PtgCommon.h source.h qclicomp.h clplib.h \
		csm.h coord.h obstack.h ptg.h VoidPtr.h \
		VoidPtrFunctionTypes.h nodeptr.h

CScope.o:	CScope.c CScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

