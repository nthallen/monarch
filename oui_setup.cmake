
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if (CMAKE_CROSSCOMPILING)
  link_directories( /opt/linkeng/am335x/lib )
  include_directories( /opt/linkeng/am335x/include )
else (CMAKE_CROSSCOMPILING)
  if (NOT DEFINED le_das_SOURCE_DIR)
    link_directories(/usr/local/lib)
  endif (NOT DEFINED le_das_SOURCE_DIR)
endif (CMAKE_CROSSCOMPILING)

if (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)
  set(OUI_EXE /usr/local/bin/oui)
else (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)
  set(OUI_EXE ${le_das_BINARY_DIR}/tools/oui/src/oui)
  include_directories(
    ${le_das_SOURCE_DIR}/tools/oui/src
    ${le_das_SOURCE_DIR}/libs/nl
  )
endif (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)

MACRO(OUI_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
        COMMAND ${OUI_EXE}
                -o${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
                ${le_das_OUI_PATH}
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${_filename} ${OUI_EXE} )
ENDMACRO(OUI_FILE)
