#! /bin/bash

function msg {
  code=$1
  excode=''
  case $code in
    1) prefix='[Warn]';;
    2) prefix='[Error]';;
    3) prefix='[Fatal]'; excode=1;;
    4) prefix='[Internal]'; excode=1;;
    *) prefix='';;
  esac
  shift
  /usr/local/bin/msg -Vn dump_exconfig "$*"
  [ -n "$excode" ] && exit $excode
}

. /usr/local/libexec/load_exconfig.sh

msg 0 Experiment=$Experiment
msg 0 HomeDir=$HomeDir
[ -n "$CFG_ERROR" ] &&
  msg 2 CFG_ERROR=$CFG_ERROR
msg 0 FlightNode=$FlightNode
msg 0 FltNode_Access=$FltNode_Access
msg 0 SERVICE=$SERVICE
msg 0 "TM_OPT='$TM_OPT'"
msg 0 "CMD_OPT='$CMD_OPT'"
msg 0 "MC_OPT='$MC_OPT'"
msg 0 "SSH_CMD='$SSH_CMD'"
msg 0 "VERSION=$VERSION"
msg 0 "TMBINDIR=$TMBINDIR"

