find_program(OUI_EXE
    oui
    HINTS ${le_das_BINARY_DIR}/oui/src
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
                -o${_basename}oui.cc
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        DEPENDS ${_filename} )
ENDMACRO(OUI_FILE)

OUI_FILE(subbusd.oui)
OUI_FILE(CAN/subbusd_CAN.oui)

add_executable(subbusd subbusd.cc subbusdoui.cc)
target_include_directories(subbusd PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
#  ${le_das_SOURCE_DIR}/dasio/src
#  ${le_das_SOURCE_DIR}/nl/src
#  ${le_das_SOURCE_DIR}/oui/src
)

target_link_libraries(subbusd dasio nl)

add_executable(subbusd_CAN subbusd.cc subbusd_CANoui.cc)
target_include_directories(subbusd_CAN PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(subbusd_CAN dasio nl)
