cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(cmdgen VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

if (NOT ${CMAKE_CROSSCOMPILING})

find_program(SHELL_EXE NAMES ksh bash)
if (NOT SHELL_EXE)
  message( FATAL_ERROR "No shell located")
endif (NOT SHELL_EXE)

configure_file(mkexp.sh.in mkexp.sh @ONLY)
configure_file(mkexpdir.sh.in mkexpdir @ONLY)
configure_file(mkexpactive.sh.in mkexpactive @ONLY)

install(PROGRAMS mkexp.sh
        DESTINATION /usr/local/share/linkeng/setup)
install(PROGRAMS mkexpactive mkexpdir
        DESTINATION /usr/local/sbin/mkexpdir)

endif (NOT ${CMAKE_CROSSCOMPILING})
