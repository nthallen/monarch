cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-meo VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# This should somehow be put into a module
find_program(OUI_EXE oui)
if(OUI_EXE STREQUAL "OUI_EXE-NOTFOUND")
    message(FATAL_ERROR "oui not found!")
endif(OUI_EXE STREQUAL "OUI_EXE-NOTFOUND")
# reuseable cmake macro for oui
MACRO(OUI_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
        COMMAND ${OUI_EXE}
                -o${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${_filename} )
ENDMACRO(OUI_FILE)

if (${CMAKE_CROSSCOMPILING})
  link_directories( /opt/linkeng/am335x/lib )
  include_directories( /opt/linkeng/am335x/include )
else (${CMAKE_CROSSCOMPILING})
  link_directories( /usr/local/lib )
  include_directories( /usr/local/include )
endif (${CMAKE_CROSSCOMPILING})

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

OUI_FILE(memo.oui)
add_executable(memo memo.cc memooui.cc)
target_link_libraries(memo dasio nl)

OUI_FILE(msg_internal.oui)
add_executable(msg msg.cc msg_internaloui.cc)
target_link_libraries(msg dasio nl)

install(TARGETS memo msg RUNTIME DESTINATION bin)
