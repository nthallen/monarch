cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch_utils_flight VERSION 2.0.0)

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

configure_file(flight.sh.in flight.sh @ONLY)
configure_file(extract.in extract @ONLY)
configure_file(reduce.in reduce @ONLY)
configure_file(mlf_find.in mlf_find @ONLY)
configure_file(saverun.in saverun @ONLY)
configure_file(clean_runfiles.in clean_runfiles @ONLY)
configure_file(locate_rundir.in locate_rundir @ONLY)
configure_file(getrun.in getrun @ONLY)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/clean_runfiles
  ${CMAKE_CURRENT_BINARY_DIR}/extract
  ${CMAKE_CURRENT_BINARY_DIR}/locate_rundir
  ${CMAKE_CURRENT_BINARY_DIR}/reduce
  ${CMAKE_CURRENT_BINARY_DIR}/mlf_find
  ${CMAKE_CURRENT_BINARY_DIR}/saverun
  ${CMAKE_CURRENT_BINARY_DIR}/getrun
  ${CMAKE_CURRENT_SOURCE_DIR}/dircksum
  ${CMAKE_CURRENT_SOURCE_DIR}/dircompare
  DESTINATION bin)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/flight.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/load_exconfig.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/setup_getrun.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/usb_enum
  DESTINATION libexec)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/dump_exconfig.sh
  DESTINATION sbin)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/TMC_debug.gdb
  DESTINATION share/monarch/gdb)

if (NOT CMAKE_CROSSCOMPILING)

else (NOT CMAKE_CROSSCOMPILING)

endif (NOT CMAKE_CROSSCOMPILING)

