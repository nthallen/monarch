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
#
# Determination of the SERVICE status is heuristic and based on
# circumstantial evidence. Anytime FlightNode is defined it is
# assumed the service is installed on the FlightNode, which is
# reasonable. It is entirely possible to imagine running a remote
# instrument via ssh similar to the way we would start up a local
# AdHoc instrument, but we would need a separate variable to mark
# the FlightNode as being AdHoc, since it may not be accessible
# when the decisions are being made.
#
# Similarly, when FlightNode is not defined, the presence of
# parent registered for this Experiment
# is deemed strong enough evidence that the service is installed.
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

# echo "load_exconfig: FltNode_Access: [$FltNode_Access]"
# echo "load_exconfig: TM_OPT: [$TM_OPT]"

if [ $FltNode_Access = Remote ]; then
  TM_OPT="-t $FlightNode"
  CMD_OPT="-C $FlightNode"
  SSH_CMD="ssh -t flight@$FlightNode"
  SSH_TAR_CMD="ssh -T flight@$FlightNode"
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

msgVdefault='-V'
[ -z "$msgProgram" ] && msgProgram='load_exconfig.sh'
msgDebug=-1

function msgf {
  msgV=$msgVdefault
  if [ "$1" = '-V' ]; then
    msgV=-V
    shift
  fi
  code=$1
  excode=''
  case $code in
    1) prefix='[Warn]';;
    2) prefix='[Error]';;
    3) prefix='[Fatal]'; excode=1;;
    4) prefix='[Internal]'; excode=1;;
    -1) excode=0;;
    *) prefix='';;
  esac
  shift
  if [ $code -ge $msgDebug ]; then
    /usr/local/bin/msg $msgV -n $msgProgram "$*"
  fi
  [ -n "$excode" ] && exit $excode
}

function set_have {
  name=$1
  value=$2
  if [ "${name#-}" = "$name" ]; then
    eval have_$name=$value
  fi
}

function Launch {
  name=$1
  shortname=$name
  set_have $shortname no
  shift
  [ -n "$launch_error" ] && return 1
  mkdir -p /var/run/linkeng/run/$Experiment
  if { $* & }; then
    Launch_pid=$!
    msgf -V 0 "Launch: $Launch_pid $*"
    if [ "$name" != "-" ]; then
      [ "$name" = "-TMC-" ] && name="/var/run/linkeng/run/$Experiment/$!"
      [ "${name#/}" = "$name" ] && name="/var/run/linkeng/$Experiment/$name"
      waitfor $name 20 || {
        msgf 2 "Launch namewait failure: $*"
        launch_error=yes
        return 1
      }
    fi
    [ $name = memo ] && msgVdefault=''
    set_have $shortname yes
  else
    msgf 2 "Launch Error: $*"
    launch_error=yes
    return 1
  fi
  return 0
}

