add_library(tm msg.c)
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES msg.h
  DESTINATION include
)
