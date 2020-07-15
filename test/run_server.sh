#! /bin/bash
# run_server.sh
# This script is charged with running all things on the
# server side of this client/server test. This script is
# designed to run on both the local machine and the remote
# machine (when a remote machine is involved).
#
# ./run_server.sh local start_server_memo
#    If FlightNode is defined, ssh to FlightNode
#    and run ./run_server.sh start_server_memo
# ./run_server.sh start_server_memo
#    Start memo
# ./run_server.sh local start_server
#    If FlightNode is defined, ssh to FlightNode
#    and run ./run_server.sh start_server
#    Otherwise, start the server as if local were not defined
# ./run_server.sh start_server "Run Description"
#    Run the server, then monitor netstat -na | grep :3500 for
#    TIME_WAIT, reporting an error if it is present and waiting
#    until it is clear before ending.
# ./run_server.sh local stop_server_memo
#    Same as start_server_memo but for stopping
#
# In all non-local cases, this script must establish the
# environment by setting the PATH and cd-ing to the appropriate
# run directory. Additional configuration values will be read
# from Experiment.config
#
# On the remote machine, Experiment.config and this script must be
# copied into the login directory, and HomeDir should point to the
# location where source code is. The actual server executable is
# located in another directory that should be specified with a
# nonstandard BINDIR value.
#   HomeDir should apply to the source directory on remote node.
#   BINDIR ideally should work for either node.

function nl_error {
  echo "run_server: [ERROR] $*" >&2
  exit 1
}

[ -z "$1" ] && nl_error "Must specify args"

export PATH=/bin:/usr/bin:/usr/local/bin
. /usr/local/libexec/load_exconfig.sh
[ -n "$CFG_ERROR" ] && nl_error "$CFG_ERROR"
[ -n "$BINDIR" ] && PATH=$PATH:$BINDIR
if [ "$1" != "local" ]; then
  cd $HomeDir
fi

if [ "$1" = "local" ]; then
  shift 1
  if [ -n "$FlightNode" ]; then
    [ -n "$rmtHomeDir" ] || nl_error "No rmtHomeDir defined"
    case "$1" in
      start_server)
        saw_err=no
        ssh -t $FlightNode $rmtHomeDir/run_server.sh $* 2>&1 | tee start_server.tmp.log
        sed -n -e 's/\r//' -e '/ERROR\|WARNING/ s/^[^\[]*//p' start_server.tmp.log |
          while read errline; do
            msg -n rmt "$errline"
            saw_err=yes
          done
        [ $saw_err = yes ] && cp start_server.tmp.log start_server.$$.log
        mv start_server.tmp.log start_server.log
        exit 0;;
      *)
        ssh -t $FlightNode $HomeDir/run_server.sh $*
        exit 0;;
    esac
  else
    case "$1" in
      start_server_memo) exit 0;;
      start_server) ;;
      stop_server_memo) exit 0;;
      *) nl_error "Invalid command: '$1'";;
    esac
    # Fall through to run test below
  fi
fi

# Here we are either running on the remote server
# or there is no remote server. We should not get
# here on the local server if the command is start_server_*

[ "$1" != "start_server" -a -z "$FlightNode" ] && nl_error "server_memo command in local mode"
case "$1" in
  start_server_memo)
    memo -o run_server.log -V -l0
    exit 0;;
  stop_server_memo)
    clean_runfiles -k
    exit 0;;
  start_server)
    ;;
  *) nl_error "Invalid command #2: '$1'";;
esac
shift 1
srvrmode=-mV
[ -n "$FlightNode" ] && srvrmode="$srvrmode -sTCP"
msg start_server $*
test_server $srvrmode
TW=`netstat -na | grep ':3500 .* TIME_WAIT' | sed -e 's/\r//'`
if [ -n "$TW" ]; then
  msg -mV "[ERROR] $TW"
  TWcount=0
  while [ -n "$TW" ]; do
    TW=`netstat -na | grep ':3500 .* TIME_WAIT'`
    if [ -n "$TW" ]; then
      if [ $TWcount -lt 30 ]; then
        let TWcount=TWcount+1
      else
        msg "Still waiting on TIME_WAIT"
        TWcount=0
      fi
      sleep 1
    fi
  done
  msg "TIME_WAIT cleared"
fi
# Create start_server.log to signal run_test that server
# has terminated, but only in the local case.
# This file needs to be created on the local machine.
[ -z "$FlightNode" ] && touch start_server.log
