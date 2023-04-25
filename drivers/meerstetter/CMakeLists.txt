cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(meerstetter  VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# message("Top of meerstetter's CMakeList.txt")

#if (NOT ${CMAKE_CROSSCOMPILING})
#message("We are not cross compiling: build development tools")
#endif (NOT ${CMAKE_CROSSCOMPILING})

# TARGET=qclisd qclisprog qclistest qclidacsd qclidprog qclidtest
# I will skip the serial versions

include( ../../oui_setup.cmake )
OUI_FILE(meerstetter.oui)
add_executable(meerstetter crc16xmodem.cc me_ser.cc main.cc me_cmd.cc
  me_query.cc meerstetteroui.cc)
target_link_libraries(meerstetter dasio nl pthread)

#add_executable(qclidtest qclitest.cc qcliutil.cc qclidacs.cc qclidtestoui.cc)

install(TARGETS
  meerstetter
  RUNTIME DESTINATION bin)
install(FILES
  meerstetter.h
  DESTINATION include)
install(FILES
  TM/Meerstetter.agm
  DESTINATION share/monarch/modules/Meerstetter)
install(PROGRAMS
  TM/Meerstetter_gen
  DESTINATION share/monarch/modules/Meerstetter)
