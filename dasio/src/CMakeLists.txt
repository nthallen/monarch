#cmake_minimum_required(VERSION 2.8.8)
#cmake_policy(SET CMP0048 NEW)
#project(dasio_proj VERSION 2.0.0)
add_library(dasio interface.cc ascii_escape.cc not_parsed.cc dasio_serial.cc Timeout.cc)
target_include_directories(dasio PUBLIC ../../nl/src ../../tm/src)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
install(FILES dasio.h dasio_serial.h Timeout.h
  DESTINATION include
)
