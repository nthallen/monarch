cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(monarch-tmdf VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(tmdf.oui)
add_executable(tmdf tmdf.cc tmdfoui.cc)
target_link_libraries(tmdf dasio nl pthread)

install(TARGETS tmdf RUNTIME DESTINATION bin)

install(FILES tmdf.h
  DESTINATION include
)

install(FILES
  tmdf.tmc
  tmdf_col.tmc
  DESTINATION share/linkeng)

