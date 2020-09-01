#! /bin/bash
[ -d derived ] && rm -rf derived
mkdir derived
eli "nctable.specs +(%nflags) :source >derived"

while read row; do
  case $row in
    OBJS*)
      srcs=`echo $row | sed -ne 's/^.*= //' -e 's/\.o\b/.cc/gp'`;;
  esac
done <derived/Makefile

for src in $srcs; do
  mv derived/${src%c} derived/$src
done

{
cat <<EOF
cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(table_derived  VERSION 2.0.0)

set_source_files_properties(Include.cc PROPERTIES
       COMPILE_FLAGS "-include unistd.h")

add_executable(nctable $srcs)

message("Pre-conditional")
if (NOT DEFINED monarch_BINARY_DIR)
  message("no monarch_BINARY_DIR")
  link_directories( /usr/local/lib )
else (NOT DEFINED monarch_BINARY_DIR)
  message("monarch_BINARY_DIR is \${monarch_BINARY_DIR}")
  target_include_directories(nctable PRIVATE
    \${monarch_SOURCE_DIR}/tools/oui/src)
endif()

target_link_libraries(nctable dasio nl ncurses pthread)
install(TARGETS nctable RUNTIME DESTINATION bin)
EOF
} >derived/CMakeLists.txt

perl -i.bak -pe 's/^CFLAGS/CXXFLAGS/; s/\.c/.cc/g' derived/Makefile
rm -f derived/Makefile.bak
