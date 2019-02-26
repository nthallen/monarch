add_executable(test_sb test_sb.cc test_sboui.cc)
OUI_FILE(test_sb.oui)

target_include_directories(test_sb PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(test_sb subbuspp dasio nl)
