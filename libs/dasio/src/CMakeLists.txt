cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(dasio_src VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 )

add_library(dasio interface.cc ascii_escape.cc not_parsed.cc serial.cc
  timeout.cc loop.cc socket.cc unix_name.cc modbus_rtu.cc
  client.cc server.cc appid.cc tm_data_sndr.cc tm_server.cc
  #tm_gen.cc tm_gen_cmd.cc tm_gen_data.cc tm_gen_Resmgr.cc
  #tm_gen_tmr.cc
  tm_queue.cc tm_client.cc tmdac.cc tm_info.cc
  cmd_writer.cc cmd_version.cc cmd_version_def.cc msg.cc
  cic_transmit.cc cmd_server.cc quit.cc get_baud_code.cc)
target_include_directories(dasio PUBLIC
  ${dasio_src_BINARY_DIR}
  ${dasio_src_SOURCE_DIR}
)
target_include_directories(dasio PRIVATE
  ${le_das_libs_SOURCE_DIR}/tm
  ${le_das_libs_SOURCE_DIR}/nl
  ${le_das_SOURCE_DIR}/tools/cmdgen
)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
install(FILES cmd_version.oui cmd_writer.oui msg.oui
  tm_client.oui
  DESTINATION share/oui
)
add_subdirectory(dasio)
