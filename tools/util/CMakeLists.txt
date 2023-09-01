cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch_tools_util VERSION 2.0.0)

find_program(SUDO_EXE sudo)
if (SUDO_EXE)
set(HAVE_SUDO yes)
else (SUDO_EXE)
set(HAVE_SUDO no)
endif (SUDO_EXE)

find_program(SHELL_EXE NAMES bash ksh)
if (NOT SHELL_EXE)
  message( FATAL_ERROR "No shell located")
endif (NOT SHELL_EXE)

configure_file(distribute_check.in distribute_check @ONLY)

if (NOT CMAKE_CROSSCOMPILING)

configure_file(appgen.in appgen @ONLY)
configure_file(distribute.in distribute)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/appgen
  appgen_module
  ${CMAKE_CURRENT_BINARY_DIR}/distribute
  ${CMAKE_CURRENT_BINARY_DIR}/distribute_check
  genui
  genui_chk
  mkdoit3
  swscomp
  waitfor
  DESTINATION bin)

install(FILES
  appgen.mk
  edf2ext.awk
  edf2oui.awk
  DESTINATION share/monarch)

install(FILES
  Version.agm
  loop.cmd
  Command_SN.agm
  command_sn.cmd
  command_sn_col.tmc
  command_sn.tmc.in
  command_sn.genui.in
  command_sn.tbl.in
  DESTINATION share/monarch/modules)

else (NOT CMAKE_CROSSCOMPILING)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/distribute_check
  DESTINATION bin)

endif (NOT CMAKE_CROSSCOMPILING)

