cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-getcon VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_definitions( -D_POSIX_C_SOURCE=200809 -D_BSD_SOURCE )

include( ../../oui_setup.cmake )

OUI_FILE(getcon.oui)
add_executable(getcon getcon.cc getconoui.cc)
target_link_libraries(getcon dasio nl pthread)
target_include_directories(getcon PRIVATE
  ${monarch_SOURCE_DIR}/tools/cmdgen)

install(TARGETS getcon RUNTIME DESTINATION sbin)
install(FILES
  getcon.cmd
  DESTINATION share/monarch/modules
)
