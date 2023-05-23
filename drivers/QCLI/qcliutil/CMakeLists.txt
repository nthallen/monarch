cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(qcliutil  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# message("Top of qcliutil's CMakeList.txt")

#if (NOT ${CMAKE_CROSSCOMPILING})
#message("We are not cross compiling: build development tools")
#endif (NOT ${CMAKE_CROSSCOMPILING})

# TARGET=qclisd qclisprog qclistest qclidacsd qclidprog qclidtest
# I will skip the serial versions

include( ../../../oui_setup.cmake )
# OUI_FILE(qclidacsd.oui)
# add_executable(qclidacsd qclid.cc qcliutil.cc qclidacs.cc qclidacsdoui.cc)
# target_link_libraries(qclidacsd dasio nl pthread subbuspp)

# OUI_FILE(qclidprog.oui)
# add_executable(qclidprog qcliprog.cc qcliutil.cc qclidacs.cc qclidprogoui.cc)
# target_link_libraries(qclidprog dasio nl pthread subbuspp)

OUI_FILE(qclisd.oui)
add_executable(qclisd qclid.cc qclisdoui.cc qcliutil.cc qcliser.cc qcliver.cc)
target_link_libraries(qclisd dasio nl pthread)

OUI_FILE(qclisprog.oui)
add_executable(qclisprog qcliprog.cc qcliutil.cc qcliser.cc qclisprogoui.cc qcliver.cc)
target_link_libraries(qclisprog dasio nl pthread)
#add_executable(qclidtest qclitest.cc qcliutil.cc qclidacs.cc qclidtestoui.cc)

install(TARGETS
# qclidacsd
# qclidprog
  qclisd
  qclisprog
  RUNTIME DESTINATION bin)
install(FILES
  hsatod.h
  qclid.h
  TM/qclisspcmd.h
  DESTINATION include)
install(FILES
  TM/QCLI.agm
  TM/qcli.tmc.in
  TM/qcli_col.tmc.in
  TM/qcli_conv.tmc.in
  TM/qcli_types.tmc
  TM/qclia.cmd
  TM/qclis.cmd.in
  TM/qcli.tbl.in
  TM/qcli.genui.in
  TM/ssp_amp.AB3R.tmc.in
  TM/ssp_noise.AB3R.tmc.in
  TM/ssp_amp.genui.in
  TM/ssp_noise.genui.in
  TM/ssp_amp_col.tmc.in
  DESTINATION share/monarch/modules/QCLI)
