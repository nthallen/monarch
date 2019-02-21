cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbuspp VERSION 2.0.0)

add_library(subbuspp subbuspp.cc)
target_include_directories(subbuspp PUBLIC
  ${CMAKE_SOURCE_DIR}/dasio/src
# ${CMAKE_SOURCE_DIR}/tm/src
  ${CMAKE_SOURCE_DIR}/nl/src
  ${CMAKE_SOURCE_DIR}/drivers/subbus
  ${CMAKE_SOURCE_DIR}/drivers/subbus/subbusd
# ${CMAKE_SOURCE_DIR}/cmdgen
)
install(TARGETS subbuspp
  ARCHIVE
  DESTINATION lib
)
install(FILES subbuspp.h
  DESTINATION include
)
