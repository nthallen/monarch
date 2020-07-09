#! /bin/bash
pause=no
iterations=20
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
  echo "Running under screen"
  echo "Experiment is '$Experiment'"
  echo "TMBINDIR is '$TMBINDIR'"
  echo "BINDIR is '$BINDIR'"
  clean_runfiles
  hit_any_key
  
  screen -t memo memo -o TEST.log -V -l0
  screen -X select 0
  echo "memo has been started"
  hit_any_key

  count=0  
  while [ $count -lt $iterations ]; do
    let count=count+1
    for scenario in 1 2 11 12 13; do #
      # Now we can loop through tests
      screen -t server $BINDIR/test_server -s Unix
      screen -X select 0
      echo "server has been started, will wait for name"
      waitfor /var/run/linkeng/$Experiment/test 5
      hit_any_key
      
      $BINDIR/test_client -S $scenario
      # now check on the status. Has the server terminated?
      clean_runfiles
      if [ -e /var/run/linkeng/$Experiment/test ]; then
        msg "[ERROR] Server has not terminated"
        kill -9 `cat /var/run/linkeng/$Experiment/test.pid`
      fi
      # End of the loop(s)
    done
  done
  
  # Shut down memo (crudely)
  clean_runfiles -k
  hit_any_key
fi
