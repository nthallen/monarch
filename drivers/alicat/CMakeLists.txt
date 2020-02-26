cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-alicat VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(alicat.oui)
add_executable(alicat main.cc alicat_dev.cc
  modbus_cmd.cc alicatoui.cc)
target_link_libraries(alicat dasio nl pthread)

install(TARGETS alicat RUNTIME DESTINATION bin)

install(FILES alicat.h
  DESTINATION include
)

# If/when I add the Module definitions
#install(FILES
#  alicat.tmc
#  alicat_col.tmc
#  DESTINATION share/linkeng)
