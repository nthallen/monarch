cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(qclicomp_derived  VERSION 2.0.0)
set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

#set_source_files_properties(Include.cc PROPERTIES
#       COMPILE_FLAGS "-include unistd.h")

add_executable(qclicomp driver.c clpintf.c clp.c csm.c obstack.c obsave.c deftbl.c err.c source.c coord.c pdl_gen.c VoidPtrList.c clplib.c envmod.c BitSet.c treecon.c nodecode.c treebuild.c parser.c glahead.c auxNUL.c auxEOF.c dflteot.c tabsize.c idn.c Cint.c auxScanEOL.c str.c Ccomment.c pgs_gen.c treestack.c dfltrepar.c attrmain.c visitprocs.c pickres.c ptg_gen.c linepos.c PtgCommon.c Strings.c visitmap.c CScope.c)
target_link_libraries(qclicomp m)

message("Pre-conditional")
if (NOT DEFINED monarch_BINARY_DIR)
  message("no monarch_BINARY_DIR")
  # target_link_directories(qclicomp PRIVATE /usr/local/lib)
else (NOT DEFINED monarch_BINARY_DIR)
  message("monarch_BINARY_DIR is ${monarch_BINARY_DIR}")
  # target_include_directories(qclicomp PRIVATE
  #   ${monarch_SOURCE_DIR}/tools/oui/src)
endif()

install(TARGETS qclicomp RUNTIME DESTINATION bin)
