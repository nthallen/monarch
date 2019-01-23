install(FILES interface.h serial.h timeout.h socket.h modbus_rtu.h
  client.h server.h appid.h tm_data_sndr.h tm_server.h cmd_writer.h
  cmd_version.h cmd_server.h loop.h quit.h
   ${CMAKE_CURRENT_BINARY_DIR}/config.h
  DESTINATION include/dasio
)
find_package(Curses)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h )
