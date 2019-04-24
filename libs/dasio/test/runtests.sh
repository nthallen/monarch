#! /bin/bash
subdir=''
relsrcroot='../git'
if [ ! -d .git ]; then
  # Not running in the source root
  while [ `pwd` != '/' -a ! -d .git ]; do
    subdir="/`basename $PWD`$subdir"
    relsrcroot="../$relsrcroot"
    cd ..
  done
  [ -d .git -a ../git -ef . ] || nl_error Unable to locate source root
  [ -f le-dasng-doxygen.css ] || nl_error Not in the correct source tree
fi
# if [ -n "$crname" ]; then
  # crargs=" -DCMAKE_TOOLCHAIN_FILE=$relsrcroot/arm-toolchain.cmake"
# fi
branch=`git rev-parse --abbrev-ref HEAD`
builddir="../build$crname-$branch$subdir"
builddirs=$builddir
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
