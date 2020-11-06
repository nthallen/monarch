add_library(nl nl_error.c nl_verr.c nldbg.c nlresp.c strdup.c newmem.c
  compiler.c compile_opts.c ll_of_str.c opnifile.c skeleton.c mlf.c
  rational.c md5c.c dtoe.c)
target_include_directories(nl PRIVATE
  ${monarch_SOURCE_DIR}/tools/oui/src
)
install(TARGETS nl
  ARCHIVE
  DESTINATION lib
)
install(FILES nl.h nl_assert.h compiler.h mlf.h ll_of_str.h
  rational.h md5.h dtoe.h
  DESTINATION include
)
install (FILES compiler.oui
  DESTINATION share/monarch/oui
)
