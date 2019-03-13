add_library(tm nctable.cc)
# cic.c cicf.c cictrans.c
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES nctable.h
  DESTINATION include
)
install(FILES nctable.oui
  DESTINATION share/oui
)
target_include_directories(tm PUBLIC
  ${CMAKE_BINARY_DIR}/dasio/src/
  ${CMAKE_SOURCE_DIR}/nl/src/
  ${CMAKE_SOURCE_DIR}/tools/cmdgen/
  ${CMAKE_SOURCE_DIR}/dasio/src/)
