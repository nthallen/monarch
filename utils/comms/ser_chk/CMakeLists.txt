cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-ser_chk VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../../oui_setup.cmake )

OUI_FILE(ser_chk.oui)
add_executable(ser_chk ser_chk.cc ser_chkoui.cc)
target_link_libraries(ser_chk dasio nl pthread)

install(TARGETS ser_chk RUNTIME DESTINATION bin)
