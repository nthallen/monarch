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
  
branch=`git rev-parse --abbrev-ref HEAD`
if [ ! -d .git ]; then
  msg Not running in the source root
  while [ `pwd` != '/' && ! -d .git ]; do
    cd ..
  done
  [ -d .git ] || nl_error Unable to locate source root
  [ -f le-dasng-doxygen.css ] || nl_error Not in the correct source tree
fi
builddir="build$crname-$branch"
if [ ! -d $builddir ]; then
  msg Creating build $builddir
  mkdir $builddir
  cd $builddir
  cmake -DCMAKE_BUILD_TYPE=Debug $crargs .. && make
else
  msg Using existing $builddir
  cd $builddir
  make
fi
