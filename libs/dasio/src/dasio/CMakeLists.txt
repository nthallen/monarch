install(FILES ascii_escape.h interface.h serial.h timeout.h
  socket.h modbus_rtu.h client.h server.h appid.h tm.h
  tm_client.h tm_data_sndr.h tm_gen_col.h tm_gen.h
  tm_gen_cmd.h nctable.h
  tm_gen_tmr.h tm_tmr.h
  tm_data_rcvr.h tm_queue.h
  cmd_reader.h cmd_writer.h cmd_version.h cmd_server.h quit.h
  loop.h msg.h tma.h
  csv_file.h tmctime.h nc_tm_client.h tm_rcvr.h
  cpu_usage.h json_srvr.h host_session.h serio_pkt.h
  command_sn.h kbdclt.h
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
  DESTINATION include/dasio
)
find_package(Curses)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h )
