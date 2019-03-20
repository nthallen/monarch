#! /bin/bash
function nl_error {
  echo "generate_doc: $*" >&2
  exit 1
}

[ -d .git -a ../git -ef . ] || nl_error "Must run in source base directory"
[ -d ../dox ] || mkdir ../dox
for i in tags libs tools utils; do
  [ -d ../dox/$i ] || mkdir ../dox/$i
done

function generate {
  cd $1
  doxygen || nl_error "doxygen failed in $1"
  cd -
  [ -d .git -a ../git -ef . ] || nl_error "cd - did not returns us to source base directory"
}

generate libs/tm
generate libs/nl
generate libs/dasio
generate tools/cmdgen
