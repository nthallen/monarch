#cmake_minimum_required(VERSION 2.8.8)
#cmake_policy(SET CMP0048 NEW)
#project(dasio_proj VERSION 2.0.0)
add_library(dasio interface.cc ascii_escape.cc not_parsed.cc serial.cc
  timeout.cc loop.cc socket.cc unix_name.cc modbus_rtu.cc
  client.cc server.cc appid.cc tm_data_sndr.cc tm_server.cc
  #tm_gen.cc tm_gen_cmd.cc tm_gen_data.cc tm_gen_Resmgr.cc
  #tm_gen_tmr.cc
  tm_queue.cc tm_client.cc tmdac.cc tm_info.cc
  cmd_writer.cc cmd_version.cc cmd_version_def.cc msg.cc
  cic_transmit.cc cmd_server.cc quit.cc get_baud_code.cc)
target_include_directories(dasio PUBLIC
  ${CMAKE_BINARY_DIR}/dasio/src
  ${CMAKE_SOURCE_DIR}/dasio/src
  ${CMAKE_SOURCE_DIR}/tm/src
  ${CMAKE_SOURCE_DIR}/nl/src
  ${CMAKE_SOURCE_DIR}/cmdgen
)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
install(FILES cmd_version.oui cmd_writer.oui msg.oui
  tm_client.oui
  DESTINATION share/oui
)
add_subdirectory("${CMAKE_SOURCE_DIR}/dasio/src/dasio"
                 "${CMAKE_BINARY_DIR}/dasio/src/dasio")
