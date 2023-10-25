cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-tm_rf_import VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../../oui_setup.cmake )

OUI_FILE(tm_rf_import.oui)
add_executable(tm_rf_import tm_rf_import.cc tm_rf_importoui.cc)
target_link_libraries(tm_rf_import dasio nl pthread)

if (DEFINED monarch_SOURCE_DIR)
target_include_directories(tm_rf_import PRIVATE
  ${monarch_SOURCE_DIR}/libs/dasio/src)
endif (DEFINED monarch_SOURCE_DIR)

install(TARGETS tm_rf_import RUNTIME DESTINATION bin)
