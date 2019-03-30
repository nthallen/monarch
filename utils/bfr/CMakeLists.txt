cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-bfr VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (DEFINED CMAKE_CROSSCOMPILING)
  set(OUI_EXE /usr/local/bin/oui)
else (${CMAKE_CROSSCOMPILING})
  set(OUI_EXE ${le_das_BINARY_DIR}/tools/oui/src/oui)
endif (DEFINED CMAKE_CROSSCOMPILING)

MACRO(OUI_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
        COMMAND ${OUI_EXE}
                -o${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
                -I${le_das_SOURCE_DIR}/libs/dasio/src
                -I${le_das_SOURCE_DIR}/tools/oui/src
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${_filename} ${OUI_EXE} )
ENDMACRO(OUI_FILE)

if (DEFINED CMAKE_CROSSCOMPILING)
  link_directories( /opt/linkeng/am335x/lib )
  include_directories( /opt/linkeng/am335x/include )
endif (DEFINED CMAKE_CROSSCOMPILING)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${le_das_SOURCE_DIR}/tools/oui/src
  ${le_das_SOURCE_DIR}/libs/nl
)

OUI_FILE(bfr.oui)
add_executable(bfr bfr.cc bfroui.cc rundir.cc)
target_link_libraries(bfr dasio nl)

install(TARGETS bfr RUNTIME DESTINATION bin)
