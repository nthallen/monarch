cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-drivers-dccc VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(dccc.oui)
add_executable(dccc dccc.cc dccc_if.cc dc_read.cc dcccoui.cc)
target_link_libraries(dccc dasio nl pthread subbuspp)
target_include_directories(dccc PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../subbus/include
  ${monarch_SOURCE_DIR}/libs/dasio/src
  ${monarch_SOURCE_DIR}/libs/nl
)

install(TARGETS dccc RUNTIME DESTINATION bin)

#install(FILES dccc.h
#  DESTINATION include
#)

# install(FILES
    # TM/dccc.agm
    # TM/dccc.genui.in
    # TM/dccc_base.tbl.in
    # TM/dccc.tmc.in
    # TM/dccc_col.tmc
  # DESTINATION share/monarch/modules/dccc)
