cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbus VERSION 2.0.0)

find_program(OUI_EXE
    oui
)
if(OUI_EXE STREQUAL "OUI_EXE-NOTFOUND")
    message(FATAL_ERROR "oui not found!")
endif(OUI_EXE STREQUAL "OUI_EXE-NOTFOUND")

# reuseable cmake macro for lex
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

add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus/libpp"
                 "${le-das-drivers_BINARY_DIR}/subbus/libpp")
add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus/subbusd"
                 "${le-das-drivers_BINARY_DIR}/subbus/subbusd")
add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus/test"
                 "${le-das-drivers_BINARY_DIR}/subbus/test")
