cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(cmdgen VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

# Windows now has a sudo program that doesn't work exactly like the Linux version
if (CYGWIN)
set (HAVE_SUDO no)
else (CYGWIN)
find_program(SUDO_EXE sudo)
if (SUDO_EXE)
set(HAVE_SUDO yes)
else (SUDO_EXE)
set(HAVE_SUDO no)
endif (SUDO_EXE)
endif (CYGWIN)

if (NOT ${CMAKE_CROSSCOMPILING})

find_program(SHELL_EXE NAMES bash ksh)
if (NOT SHELL_EXE)
  message( FATAL_ERROR "No shell located")
endif (NOT SHELL_EXE)

configure_file(mkexp.sh.in mkexp.sh @ONLY)
configure_file(mkexpdir.sh.in mkexpdir @ONLY)
configure_file(mkexpactive.sh.in mkexpactive @ONLY)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/mkexp.sh
        DESTINATION /usr/local/share/monarch/setup)
install(PROGRAMS
        ${CMAKE_CURRENT_BINARY_DIR}/mkexpactive
        ${CMAKE_CURRENT_BINARY_DIR}/mkexpdir
        DESTINATION /usr/local/sbin)

endif (NOT ${CMAKE_CROSSCOMPILING})
