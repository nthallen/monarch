OUI_FILE(subbusd.oui)
OUI_FILE(CAN/subbusd_CAN.oui)
OUI_FILE(CAN/subbusd_slcan.oui)
OUI_FILE(serusb/serusb.oui)

include(CheckIncludeFileCXX)
check_include_file_cxx(linux/can.h HAVE_LINUX_CAN_H)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/CAN/subbusd_CAN_config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/subbusd_CAN_config.h )
link_libraries(dasio nl pthread)

add_executable(subbusd subbusd.cc subbusdoui.cc)
add_executable(subbusd_CAN subbusd.cc subbusd_CANoui.cc CAN/subbusd_CAN.cc
               CAN/subbusd_CAN_interface.cc)
target_compile_definitions(subbusd_CAN PUBLIC USE_CAN_SOCKET)
add_executable(subbusd_slcan subbusd.cc subbusd_slcanoui.cc CAN/subbusd_CAN.cc
               CAN/subbusd_CAN_interface.cc)
target_compile_definitions(subbusd_slcan PUBLIC USE_SLCAN)
add_executable(subbusd_serusb subbusd.cc serusboui.cc serusb/serusb.cc)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_BINARY_DIR}
  ${monarch_SOURCE_DIR}/tools/oui/src
  ${monarch_SOURCE_DIR}/libs/nl
  ${monarch_SOURCE_DIR}/libs/dasio/src
)

install(TARGETS subbusd_CAN subbusd_serusb subbusd_slcan
        RUNTIME DESTINATION bin)

