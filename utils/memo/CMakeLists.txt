cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-memo VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(memo.oui)
add_executable(memo memo.cc memooui.cc)
target_link_libraries(memo dasio nl pthread)

OUI_FILE(msg_internal.oui)
add_executable(msg msg.cc msg_internaloui.cc)
target_link_libraries(msg dasio nl pthread)

install(TARGETS memo msg RUNTIME DESTINATION bin)
