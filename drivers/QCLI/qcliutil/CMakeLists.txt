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
OUI_FILE(qclidacsd.oui)
add_executable(qclidacsd qclid.cc qcliutil.cc qclidacs.cc qclidacsdoui.cc)

#add_executable(qclidprog qcliprog.cc qcliutil.cc qclidacs.cc qclidprogoui.cc)
#add_executable(qclidtest qclitest.cc qcliutil.cc qclidacs.cc qclidtestoui.cc)
