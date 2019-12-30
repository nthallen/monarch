cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-parent VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions( -D_POSIX_C_SOURCE=200809 -D_BSD_SOURCE )

include( ../../oui_setup.cmake )

OUI_FILE(parent.oui)
add_executable(parent parent.cc parentoui.cc)
target_link_libraries(parent dasio nl pthread)

install(TARGETS parent RUNTIME DESTINATION bin)
