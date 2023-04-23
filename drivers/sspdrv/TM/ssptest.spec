tmcbase = base.tmc waves1.tmc
cmdbase = ssp.cmd qcli.cmd
cmdbase = waves1.cmd

OBJ = waves1.cmd waves1.out waves1.tmc waves1.m waves1.log

Module TMbase

TGTDIR = /home/ssptest
SCRIPT = interact
SRCDIST = waves1.m
SRCDIST = waves1.qcli
IDISTRIB = doit Experiment.config
IGNORE = Makefile

ssptestsrvr : 
ssptestcol : sspcol.tmc
sspdisp : sspflags.tmc ssp.tbl

%%

waves1.cmd waves1.out waves1.tmc waves1.m : waves1.qcli
	qclicomp -o waves1.out -c waves1.cmd -d waves1.tmc -v waves1.log -m waves1.m waves1.qcli
