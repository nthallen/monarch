cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-drivers-agilent VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(agilent.oui)
add_executable(agilent agilentDriver.cc agilentoui.cc)
target_link_libraries(agilent dasio nl pthread)

install(TARGETS agilent RUNTIME DESTINATION bin)

install(FILES agilent.h
  DESTINATION include
)

# install(PROGRAMS
  # TM/alicat_gen
  # DESTINATION share/monarch/modules)
install(FILES
    TM/Agilent.agm
    TM/agilent.genui.in
    TM/agilent_base.tbl.in
    TM/agilent.tmc.in
    TM/agilent_col.tmc
  DESTINATION share/monarch/modules/Agilent)
