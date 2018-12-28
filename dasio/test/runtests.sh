#! /bin/bash
builddirs=$1
if [ -z "$builddirs" ]; then
  srcdir=`dirname $0`
  echo srcddir is $srcdir
  builddirs=`ls -d $srcdir/../../build*/dasio/test`
  echo builddirs are $builddirs
fi
for builddir in $builddirs; do
  PASSED=''
  FAILED=''
  cd $builddir
  for i in test_*; do
    echo $i
    if ./$i; then
      PASSED="$PASSED $i"
    else
      FAILED="$FAILED $i"
    fi
  done
  cd -

  echo
  echo "Results for $builddir:"
  if [ -n "$FAILED" ]; then
    echo "PASSED:$PASSED"
    echo "FAILED:$FAILED"
  else
    echo "All tests PASSED"
  fi
done
