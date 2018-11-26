add_library(tm msg.c)
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES msg.h
  DESTINATION include
)
target_include_directories(tm PUBLIC
  ${CMAKE_SOURCE_DIR}/nl/src/)