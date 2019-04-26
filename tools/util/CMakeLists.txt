cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das_tools_util VERSION 2.0.0)

find_program(SUDO_EXE sudo)
if (SUDO_EXE)
set(HAVE_SUDO yes)
else (SUDO_EXE)
set(HAVE_SUDO no)
endif (SUDO_EXE)

find_program(SHELL_EXE NAMES ksh bash)
if (NOT SHELL_EXE)
  message( FATAL_ERROR "No shell located")
endif (NOT SHELL_EXE)

configure_file(distribute_check.in distribute_check @ONLY)

if (NOT CMAKE_CROSSCOMPILING)

configure_file(distribute.in distribute)

install(PROGRAMS
  appgen
  appgen_module
  ${CMAKE_CURRENT_BINARY_DIR}/distribute
  ${CMAKE_CURRENT_BINARY_DIR}/distribute_check
  genui
  genui_chk
  DESTINATION bin)

install(FILES
  appgen.mk
  edf2ext.awk
  edf2oui.awk
  flttime.tmc
  loop.cmd
  root.cmd
  DESTINATION share/linkeng)

else (NOT CMAKE_CROSSCOMPILING)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/distribute_check
  DESTINATION bin)

endif (NOT CMAKE_CROSSCOMPILING)

