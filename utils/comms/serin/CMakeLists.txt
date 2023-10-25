cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-serin VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../../oui_setup.cmake )

OUI_FILE(serin.oui)
add_executable(serin serin.cc serinoui.cc)
target_link_libraries(serin dasio nl pthread)

if (DEFINED monarch_SOURCE_DIR)
target_include_directories(serin PRIVATE
  ${monarch_SOURCE_DIR}/libs/dasio/src)
endif (DEFINED monarch_SOURCE_DIR)

install(TARGETS serin RUNTIME DESTINATION bin)
