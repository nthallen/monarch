#! /bin/bash
function nl_error {
  echo "build.sh: $*" >&2
  exit 1
}
function msg {
  echo "build.sh: $*" >&2
}

function print_usage {
cat  <<EOF
$0 [cross]
EOF
}

if [ "$1" = "--help" -o "$1" = "-h" ]; then
  print_usage
  exit 0
fi

crargs=''
crname=''
install=''
buildtests=''
while [ -n "$1" ]; do
  if [ "$1" = "cross" ]; then
    shift
    crname='-cross'
  elif [ "$1" = "install" ]; then
    shift
    install=install
  elif [ "$1" = "BUILD_TESTS" ]; then
    shift
    buildtests="-DBUILD_TESTS=ON"	  
  else
    msg "Unrecognized option: '$1'"
    print_usage
    exit 0
  fi
done

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
  [ -f monarch-doxygen.css ] || nl_error Not in the correct source tree
fi
branch=`git rev-parse --abbrev-ref HEAD`
if [ -n "$crname" ]; then
  crargs=" -DCMAKE_TOOLCHAIN_FILE=$relsrcroot/arm-toolchain.cmake"
  crargs+=" -DCMAKE_STAGING_PREFIX=/opt/monarch/am335x-$branch"
fi
builddir="../build$crname-$branch$subdir"
if [ ! -d $builddir ]; then
  msg Creating build $builddir
  mkdir -p $builddir
  cd $builddir
  echo cmake -DCMAKE_BUILD_TYPE=Debug $crargs $buildtests $relsrcroot$subdir
  cmake -DCMAKE_BUILD_TYPE=Debug $crargs $buildtests $relsrcroot$subdir ||
    nl_error "cmake failed. You will probably need to delete the build directory"
else
  msg Using existing $builddir
  cd $builddir
fi
make $install || nl_error "'make $install' failed"
if [ "$install" = "install" -a  -d ../git ]; then
  cd ../git
  ./build_playback && ./build_playback install
fi
