cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-bfr VERSION 2.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(bfr.oui)
add_executable(bfr bfr.cc bfroui.cc rundir.cc)
target_link_libraries(bfr dasio nl pthread)

install(TARGETS bfr RUNTIME DESTINATION bin)
