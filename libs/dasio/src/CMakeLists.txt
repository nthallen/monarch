cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(dasio_src VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200809)

add_library(dasio interface.cc ascii_escape.cc cpu_usage.cc not_parsed.cc
  serial.cc timeout.cc loop.cc socket.cc unix_name.cc modbus_rtu.cc
  client.cc server.cc appid.cc tm_data_sndr.cc tm_data_rcvr.cc
  tm_gen_col.cc tm_gen.cc tm_gen_cmd.cc tm_tmr.cc tm_gen_tmr.cc
  nctable.cc json_srvr.cc
  tm_queue.cc tm_client.cc tmdac.cc tm_info.cc nc_tm_client.cc tma.cc
  cmd_client.cc cmd_writer.cc cmd_version.cc cmd_version_def.cc msg.cc
  cic_transmit.cc cmd_server.cc quit.cc get_baud_code.cc csv_file.cc
  timetext.cc tm_rcvr.cc host_session.cc)
target_include_directories(dasio PUBLIC
  ${dasio_src_BINARY_DIR}
  ${dasio_src_SOURCE_DIR}
)
target_include_directories(dasio PRIVATE
  ${monarch_libs_SOURCE_DIR}/nl
  ${monarch_SOURCE_DIR}/tools/cmdgen
  ${monarch_SOURCE_DIR}/tools/oui/src
)
install(TARGETS dasio
  ARCHIVE
  DESTINATION lib
)
install(FILES
  cmd_server.oui
  cmd_version.oui
  cmd_client.oui
  cmd_reader.oui
  cmd_writer.oui
  collect.oui
  funcs_defined.oui
  host_session.oui
  kbdclt.oui
  msg.oui
  nctable.oui
  no_appid.oui
  server.oui
  seteuid.oui
  tm_client.oui
  tma.oui
  DESTINATION share/monarch/oui
)
add_subdirectory(dasio)
