add_library(tm msg.c nctable.c)
# cic.c cicf.c cictrans.c
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES msg.h nctable.h cic.h
  DESTINATION include
)
install(FILES nctable.oui cic.oui
  DESTINATION share/oui
)
target_include_directories(tm PUBLIC
  ${CMAKE_SOURCE_DIR}/nl/src/)
