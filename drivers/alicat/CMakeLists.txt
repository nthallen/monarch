cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(monarch-alicat VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(alicat.oui)
add_executable(alicat main.cc alicat_dev.cc
  modbus_cmd.cc alicatoui.cc)
target_link_libraries(alicat dasio nl pthread)

install(TARGETS alicat RUNTIME DESTINATION bin)

install(FILES alicat.h
  DESTINATION include
)

install(PROGRAMS
  TM/alicat_gen
  DESTINATION share/monarch/modules)
install(FILES
  TM/alicat.agm
  DESTINATION share/monarch/modules)
