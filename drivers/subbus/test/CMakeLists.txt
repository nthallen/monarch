link_libraries(subbuspp dasio nl pthread)
add_executable(test_sb test_sb.cc test_sboui.cc)
add_executable(test_can test_can.cc test_sboui.cc)
add_executable(test_bmm test_bmm.cc test_sboui.cc)
add_executable(test_serusb test_serusb.cc test_sboui.cc)
add_executable(test_ir test_ir.cc test_iroui.cc)
add_executable(test_udacs test_udacs.cc test_sboui.cc)

OUI_FILE(test_sb.oui)
OUI_FILE(test_ir.oui)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${le_das_SOURCE_DIR}/tools/oui/src
  ${le_das_SOURCE_DIR}/libs/nl
  ${le_das_SOURCE_DIR}/libs/dasio/src
)
