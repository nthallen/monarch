cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-cmd_relay VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../../oui_setup.cmake )

OUI_FILE(cmd_relay.oui)
add_executable(cmd_relay cmd_relay.cc cmd_relayoui.cc)
target_link_libraries(cmd_relay dasio nl pthread)

install(TARGETS cmd_relay RUNTIME DESTINATION bin)
