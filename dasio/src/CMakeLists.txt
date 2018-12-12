#cmake_minimum_required(VERSION 2.8.8)
#cmake_policy(SET CMP0048 NEW)
#project(dasio_proj VERSION 2.0.0)
add_library(dasio interface.cc ascii_escape.cc not_parsed.cc dasio_serial.cc
  Timeout.cc loop.cc dasio_socket.cc unix_name.cc modbus_rtu.cc
  negotiate.cc)
target_include_directories(dasio PUBLIC ../../nl/src ../../tm/src)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
install(FILES dasio.h dasio_serial.h Timeout.h dasio_socket.h modbus_rtu.h
  negotiate.h
  DESTINATION include
)
