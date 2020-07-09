#! /bin/bash
pause=no
iterations=2
# available scenarios are 1 2 11 12 13
scenarios="11 12 13"
srvrname=127.0.0.1
srvrmode=''
cltlocal=''
export PATH=$PATH:/cygdrive/c/WINDOWS/system32
ns=netstat
if [ -n "$srvrname" ]; then
  cltlocal="-t $srvrname"
  srvrmode='-s TCP'
else
  srvrmode='-s Unix'
fi
  
function hit_any_key {
  if [ $pause = yes ]; then
    echo Hit any key to continue:
    read j
  fi
}

echo "\$0 is '$0'"
if [ -z "$STY" ]; then
  . /usr/local/libexec/load_exconfig.sh
  [ -n "$CFG_ERROR" ] && exit 0
  export TMBINDIR=.
  export BINDIR=../../build-quit_change/test
  screen $0
  clear # after exiting screen
else
  # echo "Running under screen"
  echo "Experiment is '$Experiment'"
  echo "TMBINDIR is '$TMBINDIR'"
  echo "BINDIR is '$BINDIR'"
  # echo "PATH is:"
  # echo $PATH | sed -e 's/:/\n  /g' -e 's/^/  /'
  clean_runfiles
  hit_any_key
  
  screen -t memo memo -o TEST.log -V -l0
  screen -X select 0
  echo "memo has been started"
  waitfor /var/run/linkeng/$Experiment/memo 15
  hit_any_key

  count=0  
  while [ $count -lt $iterations ]; do
    let count=count+1
    for scenario in $scenarios; do #
      echo "Iteration $count Scenario $scenario"
      msg "Iteration $count Scenario $scenario"
      # Now we can loop through tests
      screen -t server $BINDIR/test_server $srvrmode
      screen -X select 0
      if [ -z "$srvrname" ]; then
        echo "server has been started, will wait for name"
        waitfor /var/run/linkeng/$Experiment/test 5
      else
        # echo "server has been started"
        sleep 1
      fi
      hit_any_key
      
      $BINDIR/test_client -S $scenario $cltlocal
      # now check on the status. Has the server terminated?
      clean_runfiles >/dev/null
      if [ -z "$srvrname" -a -e /var/run/linkeng/$Experiment/test ]; then
        msg "[ERROR] Server has not terminated"
        kill -9 `cat /var/run/linkeng/$Experiment/test.pid`
      fi
      
      if [ -n "$srvrname" ]; then
        TW=`$ns -na | grep ':3500 .* TIME_WAIT' | sed -e 's/\r//'`
        if [ -n "$TW" ]; then
          msg "[ERROR] $TW"
          TWcount=0
          while [ -n "$TW" ]; do
            TW=`$ns -na | grep ':3500 .* TIME_WAIT'`
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
      fi
      
      # End of the loop(s)
    done
  done
  
  # Shut down memo (crudely)
  clean_runfiles -k
  hit_any_key
fi
