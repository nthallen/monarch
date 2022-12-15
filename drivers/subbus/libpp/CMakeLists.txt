cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(subbuspp VERSION 2.0.0)

add_library(subbuspp subbuspp.cc subbus_mig.cc)
target_include_directories(subbuspp PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${monarch_SOURCE_DIR}/libs/dasio/src
  ${monarch_SOURCE_DIR}/libs/nl
)
install(TARGETS subbuspp
  ARCHIVE
  DESTINATION lib
)
install(FILES subbus_mig.oui
  DESTINATION share/monarch/oui
)
