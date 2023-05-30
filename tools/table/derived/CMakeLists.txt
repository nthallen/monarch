cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(table_derived  VERSION 2.0.0)

set_source_files_properties(Include.cc PROPERTIES
       COMPILE_FLAGS "-include unistd.h")

add_executable(nctable driver.cc clpintf.cc clp.cc csm.cc obstack.cc obsave.cc deftbl.cc CoordMap.cc coord.cc source.cc pdl_gen.cc ptg_gen.cc nparam.cc ncbox.cc PtgCommon.cc VoidPtrList.cc clplib.cc envmod.cc BitSet.cc treecon.cc visitmap.cc visitprocs.cc dim.cc table_name.cc ncmodprint.cc Include.cc glahead.cc auxNUL.cc dflteot.cc tabsize.cc idn.cc Cint.cc str.cc auxScanEOL.cc CchStr.cc Ccomment.cc SrcFileStack.cc depfile.cc Strings.cc ColCScope.cc TableCScope.cc nodecode.cc treebuild.cc parser.cc pgs_gen.cc treestack.cc dfltrepar.cc attrmain.cc)

message("Pre-conditional")
if (NOT DEFINED monarch_BINARY_DIR)
  message("no monarch_BINARY_DIR")
  target_link_directories(nctable PRIVATE /usr/local/lib )
else (NOT DEFINED monarch_BINARY_DIR)
  message("monarch_BINARY_DIR is ${monarch_BINARY_DIR}")
  target_include_directories(nctable PRIVATE
    ${monarch_SOURCE_DIR}/tools/oui/src
    ${monarch_SOURCE_DIR}/libs/nl)
endif()

add_definitions(-Dregister=)
target_link_libraries(nctable dasio nl ncurses pthread)
install(TARGETS nctable RUNTIME DESTINATION bin)
