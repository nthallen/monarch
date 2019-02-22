#! /bin/bash
function nl_error {
  echo "build.sh: $*" >&2
  exit 1
}
function msg {
  echo "build.sh: $*" >&2
}

branch=`git rev-parse --abbrev-ref HEAD`
if [ ! -d .git ]; then
  msg Not running in the source root
  while [ ! -d .git ]; do
    cd ..
  done
  [ -d .git ] || nl_error Unable to locate source root
  [ -f le-dasng-doxygen.css ] || nl_error Not in the correct source tree
fi
if [ ! -d build-$branch ]; then
  msg Creating build build-$branch
  mkdir build-$branch
  cd build-$branch
  cmake -DCMAKE_BUILD_TYPE=Debug .. && make
else
  msg Using existing build-$branch
  cd build-$branch
  make
fi
