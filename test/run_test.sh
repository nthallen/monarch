#! /bin/bash
pause=no
iterations=2
# available scenarios are 1 2 11 12 13
scenarios="1 2 11 12 13"
srvrmode=''
export PATH=$PATH:/cygdrive/c/WINDOWS/system32
ns=netstat

function hit_any_key {
  if [ $pause = yes ]; then
    echo Hit any key to continue:
    read j
  fi
}

echo "\$0 is '$0'"
if [ -z "$STY" ]; then
  . /usr/local/libexec/load_exconfig.sh
  [ -n "$CFG_ERROR" ] && echo "$CFG_ERROR" >&2 && exit 1
  [ -n "$FlightNode" ] && export FlightNode
  [ -n "$BINDIR" ] && export BINDIR
  [ -n "$rmtHomeDir" ] && export rmtHomeDir
  screen $0
  clear # after exiting screen
  echo "run_test.sh completed, screen closed"
else
  # echo "Running under screen"
  echo "Experiment is '$Experiment'"
  echo "TMBINDIR is '$TMBINDIR'"
  echo "BINDIR is '$BINDIR'"
  # echo "PATH is:"
  # echo $PATH | sed -e 's/:/\n  /g' -e 's/^/  /'
  cltlocal=''
  [ -n "$FlightNode" ] && cltlocal="-t $FlightNode"

  clean_runfiles
  hit_any_key
  
  screen -t memo memo -o TEST.log -V -l0
  screen -X select 0
  waitfor /var/run/linkeng/$Experiment/memo 15
  echo "local memo has been started"
  
  screen -t rmemo ./run_server.sh local start_server_memo
  sleep 2
  screen -X select 0
  echo "remote memo has been started"
  hit_any_key

  count=0  
  while [ $count -lt $iterations ]; do
    let count=count+1
    for scenario in $scenarios; do #
      desc="Iteration $count Scenario $scenario"
      echo $desc
      # Now we can loop through tests
      rm -f start_server.tmp.log start_server.log
      screen -t server ./run_server.sh local start_server "$desc"
      # screen -t server $BINDIR/test_server $srvrmode
      if [ -z "$FlightNode" ]; then
        screen -X select 0
        echo "server has been started, will wait for name"
        waitfor /var/run/linkeng/$Experiment/test 5
      else
        screen -X select 0
        echo "Remote server starting"
        waitfor start_server.tmp.log forever
        echo "Remote server presumably started"
      fi
      hit_any_key
      
      $BINDIR/test_client -S $scenario $cltlocal
      # now check on the status. Has the server terminated?
      clean_runfiles >/dev/null
      if [ ! -f start_server.log ]; then
        if [ -f start_server.tmp.log ]; then
          msg "[ERROR] Server has not terminated"
          waitfor -q start_server.log forever
        else
          msg "[ERROR] 'No start_server*.log found'"
        fi
      fi
      
      # End of the loop(s)
    done
  done
  
  # Shut down memo (crudely)
  ./run_server.sh local stop_server_memo
  clean_runfiles -k
  hit_any_key
fi
