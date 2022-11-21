cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-tmdiag VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include( ../../oui_setup.cmake )

OUI_FILE(tmdiag.oui)
add_executable(tmdiag tmdiag.cc tmdiagoui.cc)
target_link_libraries(tmdiag dasio nl pthread)

install(TARGETS tmdiag RUNTIME DESTINATION bin)
