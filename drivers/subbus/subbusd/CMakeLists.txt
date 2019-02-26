OUI_FILE(subbusd.oui)
OUI_FILE(CAN/subbusd_CAN.oui)

add_executable(subbusd subbusd.cc subbusdoui.cc)
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
)
target_link_libraries(subbusd_CAN dasio nl)
