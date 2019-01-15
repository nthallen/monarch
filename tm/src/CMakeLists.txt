add_library(tm msg.c nctable.cc)
# cic.c cicf.c cictrans.c
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES msg.h nctable.h
  DESTINATION include
)
install(FILES nctable.oui
  DESTINATION share/oui
)
target_include_directories(tm PUBLIC
  ${CMAKE_SOURCE_DIR}/nl/src/
  ${CMAKE_SOURCE_DIR}/cmdgen/
  ${CMAKE_SOURCE_DIR}/dasio/src/)
