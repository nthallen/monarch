cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-sspdrv VERSION 2.0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D__POSIX_VISIBLE=200112 )

include( ../../oui_setup.cmake )

OUI_FILE(sspdrv.oui)
add_executable(sspdrv sspdrv.cc udp.cc tcp.cc sspdrvoui.cc)
target_link_libraries(sspdrv dasio nl pthread)

install(TARGETS sspdrv RUNTIME DESTINATION bin)

install(FILES sspdrv.h
  DESTINATION include
)

# install(PROGRAMS
  # TM/sspdrv_gen
  # DESTINATION share/monarch/modules)
# install(FILES
  # TM/sspdrv.agm
  # DESTINATION share/monarch/modules)
