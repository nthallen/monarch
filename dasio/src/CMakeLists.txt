#cmake_minimum_required(VERSION 2.8.8)
#cmake_policy(SET CMP0048 NEW)
#project(dasio_proj VERSION 2.0.0)
add_library(dasio interface.cc ascii_escape.cc not_parsed.cc dasio_serial.cc
  Timeout.cc loop.cc dasio_socket.cc unix_name.cc modbus_rtu.cc
  client.cc dasio_tm.cc server.cc appid.cc)
target_include_directories(dasio PUBLIC
  $(CMAKE_SOURCE_DIR)/dasio/src
  ${CMAKE_SOURCE_DIR}/tm/src
  ${CMAKE_SOURCE_DIR}/nl/src
)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
