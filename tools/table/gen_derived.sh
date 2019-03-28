#! /bin/bash
[ -d derived ] && rm -rf derived
mkdir derived
eli "nctable.specs +(%nflags) :source >derived"

while read row; do
  case $row in
    OBJS*)
      srcs=`echo $row | sed -ne 's/^.*= //' -e 's/\.o\b/.c/gp'`;;
  esac
done <derived/Makefile

{
cat <<EOF
cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(table_derived  VERSION 2.0.0)
EOF
echo "add_executable(nctable $srcs)"
echo "install(TARGETS nctable RUNTIME DESTINATION bin)"
} >derived/CMakeLists.txt
