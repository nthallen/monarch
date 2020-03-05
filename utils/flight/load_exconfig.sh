#----------------------------------------------------------------
# load_exconfig.sh: Load Experiment.config and draw some basic
# conclusions
#
# Variables defined include:
# CFG_ERROR: Defined with a string defining a serious complaint
# Experiment: Must be defined in Experiment.config
# HomeDir: Must be defined in Experiment.config
# FltNode_Access: Either 'Local' or 'Remote'
# SERVICE: Either 'Installed' or 'AdHoc'
# TM_OPT: Options to access tm_bfr on the flight node
# CMD_OPT: Options to access cmd on the flight node
# VERSION: Read from the VERSION file or defaults to 1.0
# TMBINDIR: Where the experiment-specific binaries are located
# PATH is updated to include TMBINDIR
#
# Experiment and TMBINDIR are exported as required by virtually
# all the dasio-cognizent programs
#----------------------------------------------------------------
export PATH=:/bin:/usr/bin:/usr/local/bin
umask g+w

#----------------------------------------------------------------
# This is where we will decide what experiment we are
#----------------------------------------------------------------
cfile=Experiment.config
unset Experiment HomeDir FlightNode CFG_ERROR
unset FltNode_Access TM_OPT CMD_OPT
if [ -f "$cfile" -a -r "$cfile" ]; then
  . $cfile
  if [ -n "$Experiment" -a -n "$HomeDir" -a -d "$HomeDir" ]; then
    cd $HomeDir
  else
    CFG_ERROR="Experiment or HomeDir undefined or non-existant"
  fi
else
  CFG_ERROR="missing or unreadable $cfile: stopping"
fi

export Experiment

# Determine whether we are running on the FlightNode (local) or
# on a separate GSE (remote)
FltNode_Access=Local
if [ -n "$FlightNode" -a ! /home/flight/Experiment.config -ef $cfile ]; then
  FltNode_Access=Remote
fi

echo "load_exconfig: FltNode_Access: [$FltNode_Access]"
echo "load_exconfig: TM_OPT: [$TM_OPT]"

if [ $FltNode_Access = Remote ]; then
  TM_OPT='-t $FlightNode'
  CMD_OPT='-C $FlightNode'
  SERVICE=Installed
elif [ -e /var/run/linkeng/$Experiment/parent -a \
       -e /var/run/linkeng/$Experiment/parent.pid ] &&
     [ -e /proc/`cat /var/run/linkeng/$Experiment/parent.pid` ]; then
  SERVICE=Installed
else
  SERVICE=AdHoc
fi

VERSION=1.0
[ -f VERSION ] && VERSION=`cat VERSION`
if [ -d bin/$VERSION/ ]; then
  TMBINDIR=$PWD/bin/$VERSION
  PATH=$TMBINDIR:$PATH
else
  TMBINDIR='.'
fi
export TMBINDIR
