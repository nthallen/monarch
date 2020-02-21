tmcbase = base.tmc

Module TMbase

TGTDIR = $(TGTNODE)/home/Demo
IGNORE = "*.o" "*.exe" "*.stackdump" Makefile
DISTRIB = services interact
IDISTRIB = doit

Demodisp : Demo.tbl
Demoalgo : Demo.tma
madedoit : Demo.doit
