cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbuspp VERSION 2.0.0)

add_library(subbuspp subbuspp.cc)
target_include_directories(subbuspp PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
install(TARGETS subbuspp
  ARCHIVE
  DESTINATION lib
)
