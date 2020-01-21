cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das_utils_flight VERSION 2.0.0)

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

configure_file(flight.sh.in flight.sh @ONLY)

install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/flight.sh
  DESTINATION sbin)

if (NOT CMAKE_CROSSCOMPILING)

else (NOT CMAKE_CROSSCOMPILING)

endif (NOT CMAKE_CROSSCOMPILING)

