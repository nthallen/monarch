cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(monarch-dasctl VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_definitions( -D_POSIX_C_SOURCE=200809 -D_BSD_SOURCE )
add_definitions( -D_DEFAULT_SOURCE )

include( ../../oui_setup.cmake )

OUI_FILE(dasctl.oui)
add_executable(dasctl dasctl.cc dasctloui.cc)
target_link_libraries(dasctl dasio nl pthread)

install(TARGETS dasctl RUNTIME DESTINATION bin)
