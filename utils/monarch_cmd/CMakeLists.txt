cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch_cmd VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_DEFAULT_SOURCE )

include( ../../oui_setup.cmake )

OUI_FILE(monarch_cmd.oui)
add_executable(monarch_cmd monarch_cmd.cc monarch_cmdoui.cc)
target_link_libraries(monarch_cmd dasio nl pthread)
target_include_directories(monarch_cmd PRIVATE
  ${monarch_SOURCE_DIR}/tools/cmdgen)

install(TARGETS monarch_cmd RUNTIME DESTINATION bin)
