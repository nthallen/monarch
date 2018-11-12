add_library(nl nl_error.c nl_verr.c nldbg.c nlresp.c strdup.c)
install(TARGETS nl
  ARCHIVE
  DESTINATION lib
)
install(FILES nl.h nl_assert.h
  PUBLIC_HEADER
  DESTINATION include
)
