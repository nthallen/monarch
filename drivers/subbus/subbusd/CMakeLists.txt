OUI_FILE(subbusd.oui)
OUI_FILE(CAN/subbusd_CAN.oui)

include(CheckIncludeFileCXX)
check_include_file_cxx(linux/can.h HAVE_LINUX_CAN_H)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/CAN/subbusd_CAN_config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/subbusd_CAN_config.h )

add_executable(subbusd subbusd.cc subbusdoui.cc)


# As an independent project, I assume dasio, nl an oui are
# already installed
target_include_directories(subbusd PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
#  ${le_das_SOURCE_DIR}/dasio/src
#  ${le_das_SOURCE_DIR}/nl/src
#  ${le_das_SOURCE_DIR}/oui/src
)

target_link_libraries(subbusd dasio nl)

add_executable(subbusd_CAN subbusd.cc subbusd_CANoui.cc CAN/subbusd_CAN.cc)
target_include_directories(subbusd_CAN PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(subbusd_CAN dasio nl)
