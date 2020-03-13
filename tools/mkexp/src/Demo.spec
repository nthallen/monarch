tmcbase = base.tmc
genuibase = @DEMO@.genui

Module TMbase

TGTDIR = $(TGTNODE)/home/@DEMO@
IGNORE = "*.o" "*.exe" "*.stackdump" Makefile
DISTRIB = services interact
IDISTRIB = doit

@DEMO@disp : @DEMO@.tbl
@DEMO@algo : @DEMO@.tma
madedoit : @DEMO@.doit
