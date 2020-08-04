cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(test_cltsrv VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 )

include ( ../oui_setup.cmake )

link_libraries(dasio nl pthread)
add_executable(test_client test_client.cc test_clientoui.cc)
add_executable(test_server test_server.cc test_serveroui.cc)

OUI_FILE(test_client.oui)
OUI_FILE(test_server.oui)

if (DEFINED le_das_SOURCE_DIR)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${le_das_SOURCE_DIR}/tools/oui/src
    ${le_das_SOURCE_DIR}/libs/nl
    ${le_das_SOURCE_DIR}/libs/dasio/src
  )
else (DEFINED le_das_SOURCE_DIR)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif (DEFINED le_das_SOURCE_DIR)
