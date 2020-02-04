add_library(tm nctable.cc)
install(TARGETS tm
  ARCHIVE
  DESTINATION lib
)
install(FILES nctable.h
  DESTINATION include
)
install(FILES nctable.oui tma.oui
  DESTINATION share/oui
)
target_include_directories(tm PRIVATE
  ${le_das_libs_BINARY_DIR}/dasio/src/
  ${le_das_libs_SOURCE_DIR}/dasio/src/
  ${le_das_libs_SOURCE_DIR}/nl/
  ${le_das_SOURCE_DIR}/tools/cmdgen/
)
