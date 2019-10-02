cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(tmcalgo  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT ${CMAKE_CROSSCOMPILING})

include( ../../oui_setup.cmake )
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(TMAScanner yylex.l ${CMAKE_CURRENT_BINARY_DIR}/yylex.c
            COMPILE_FLAGS "-i")
BISON_TARGET(TMAParser grammar.y ${CMAKE_CURRENT_BINARY_DIR}/grammar.c
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h
            COMPILE_FLAGS "-ytl" )
ADD_FLEX_BISON_DEPENDENCY(TMAScanner TMAParser)

OUI_FILE(tmcalgo.oui c)

add_executable(tmcalgo tmcalgo.c states.c commands.c tmcalgooui.c dot.c
    tma_appid.cc
    ${BISON_TMAParser_OUTPUT_SOURCE}
    ${FLEX_TMAScanner_OUTPUTS})
    
if (DEFINED le_das_BINARY_DIR)
target_include_directories(tmcalgo PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${le_das_SOURCE_DIR}/libs/dasio/src
  ${le_das_tools_SOURCE_DIR}/cmdgen)
else (DEFINED le_das_BINARY_DIR)
target_include_directories(tmcalgo PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR})
endif (DEFINED le_das_BINARY_DIR)

target_link_libraries(tmcalgo dasio nl pthread)
install(TARGETS tmcalgo RUNTIME
        DESTINATION bin)

endif (NOT ${CMAKE_CROSSCOMPILING})
