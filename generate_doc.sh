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
generate tools/tmc

cd ../dox

cat >index.html <<EOF
<!DOCTYPE html>
<html lang="en">
<head>
<title>Doxygen Archives</title>
</head>
<body>
<h1>Doxygen Archives</h1>
<ul>
EOF

find . -mindepth 2 -name index.html | xargs grep "<title>" |
  sed -e 's/^\(.*\):<title>\(.*\)<\/title>/<li><a href="\1">\2<\/a><\/li>/' >>index.html

cat >>index.html <<EOF
</ul>
</body>
</html>
EOF
