#! /bin/bash
drvd=../derived
[ -d $drvd ] && rm -rf $drvd
mkdir $drvd
eli "qclicomp.specs :source >$drvd"

while read row; do
  case $row in
    OBJS*)
      srcs=`echo $row | sed -ne 's/^.*= //' -e 's/\.o\b/.c/gp'`;;
  esac
done <$drvd/Makefile

#for src in $srcs; do
#  mv $drvd/${src%c} $drvd/$src
#done

{
cat <<EOF
cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(qclicomp_derived  VERSION 2.0.0)
set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

#set_source_files_properties(Include.cc PROPERTIES
#       COMPILE_FLAGS "-include unistd.h")

add_executable(qclicomp $srcs)
target_link_libraries(qclicomp m)

message("Pre-conditional")
if (NOT DEFINED monarch_BINARY_DIR)
  message("no monarch_BINARY_DIR")
  link_directories( /usr/local/lib )
else (NOT DEFINED monarch_BINARY_DIR)
  message("monarch_BINARY_DIR is \${monarch_BINARY_DIR}")
  target_include_directories(nctable PRIVATE
    \${monarch_SOURCE_DIR}/tools/oui/src)
endif()

# target_link_libraries(qclicomp)
install(TARGETS qclicomp RUNTIME DESTINATION bin)
EOF
} >$drvd/CMakeLists.txt

#perl -i.bak -pe 's/^CFLAGS/CXXFLAGS/; s/\.c/.cc/g' $drvd/Makefile
#rm -f $drvd/Makefile.bak
