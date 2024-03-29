cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(tmc  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT ${CMAKE_CROSSCOMPILING})

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(TMCScanner yylex.l ${CMAKE_CURRENT_BINARY_DIR}/yylex.c
            COMPILE_FLAGS "-i")
BISON_TARGET(TMCParser tmc.y ${CMAKE_CURRENT_BINARY_DIR}/tmc.c
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h
            COMPILE_FLAGS "-ytl" )
ADD_FLEX_BISON_DEPENDENCY(TMCScanner TMCParser)

add_executable(tmc tmcmain.c parsfunc.c pdecls.c genpcm.c place.c
    pfuncs.c calibr.c postproc.c pointers.c states.c decls.c
    calibr_icvt.c
    ${BISON_TMCParser_OUTPUT_SOURCE}
    ${FLEX_TMCScanner_OUTPUTS})
target_include_directories(tmc PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${monarch_SOURCE_DIR}/libs/dasio/src
  ${monarch_SOURCE_DIR}/libs/nl)
target_link_libraries(tmc nl m)
install(TARGETS tmc RUNTIME
        DESTINATION bin)
install(FILES colmain.skel extmain.skel
        DESTINATION share/monarch/skel)

endif (NOT ${CMAKE_CROSSCOMPILING})
