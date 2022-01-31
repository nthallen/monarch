cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-lgr VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(lgr.oui)
add_executable(lgr lgr.cc lgroui.cc)
target_link_libraries(lgr dasio nl pthread)

install(TARGETS lgr RUNTIME DESTINATION bin)
