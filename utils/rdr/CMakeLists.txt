cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(monarch-rdr VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(rdr.oui)
add_executable(rdr rdr.cc rdroui.cc)
target_link_libraries(rdr dasio nl pthread)

install(TARGETS rdr RUNTIME DESTINATION bin)
