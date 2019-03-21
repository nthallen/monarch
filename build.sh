#! /bin/bash
function nl_error {
  echo "build.sh: $*" >&2
  exit 1
}
function msg {
  echo "build.sh: $*" >&2
}

if [ "$1" = "cross" ]; then
  crname='-cross'
  crargs=" -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake"
else
  crname=''
  crargs=''
fi

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
branch=`git rev-parse --abbrev-ref HEAD`
builddir="../build$crname-$branch$subdir"
if [ ! -d $builddir ]; then
  msg Creating build $builddir
  mkdir -p $builddir
  cd $builddir
  cmake -DCMAKE_BUILD_TYPE=Debug $crargs $relsrcroot$subdir && make
else
  msg Using existing $builddir
  cd $builddir
  make
fi
