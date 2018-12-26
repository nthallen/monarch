#! /bin/bash

PASSED=''
FAILED=''
for i in test_*; do
  echo $i
  if ./$i; then
    PASSED="$PASSED $i"
  else
    FAILED="$FAILED $i"
  fi
done

if [ -n "$FAILED" ]; then
  echo "PASSED:$PASSED"
  echo "FAILED:$FAILED"
else
  echo "All tests PASSED"
fi

  