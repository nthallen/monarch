# This file provides setup for compiling and linking in directories
# under the le-dasng source root, including rules for running
# oui. This should work for native and cross-compiling, and it
# should also work whether included as part of the base build
# or when building independently.
#
# The assumption when cross-compiling or building separately
# from the base build is that the native build
# and install has already been done, so oui and libraries can
# be located in their installed locations.
#
# When building within the base build and not cross-compiling
# we use the tools (currently only oui) and libraries in the
# build tree.

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if (CMAKE_CROSSCOMPILING)
  link_directories( ${CMAKE_STAGING_PREFIX}/lib )
  include_directories( ${CMAKE_STAGING_PREFIX}/include )
else (CMAKE_CROSSCOMPILING)
  if (NOT DEFINED le_das_SOURCE_DIR)
    link_directories(/usr/local/lib)
  endif (NOT DEFINED le_das_SOURCE_DIR)
endif (CMAKE_CROSSCOMPILING)

if (DEFINED le_das_SOURCE_DIR)
  include_directories(
    ${le_das_SOURCE_DIR}/tools/oui/src
    ${le_das_SOURCE_DIR}/libs/nl
  )
  set(le_das_OUI_PATH
    -I${le_das_SOURCE_DIR}/libs/dasio/src
    -I${le_das_SOURCE_DIR}/libs/nl
    -I${le_das_SOURCE_DIR}/tools/oui/src
  )
endif (DEFINED le_das_SOURCE_DIR)

if (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)
  set(OUI_EXE /usr/local/bin/oui)
else (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)
  set(OUI_EXE ${le_das_BINARY_DIR}/tools/oui/src/oui)
endif (CMAKE_CROSSCOMPILING OR NOT DEFINED le_das_SOURCE_DIR)

set(OUI_VERBOSITY "" CACHE STRING "Verbosity level for OUI: set to '-v' or higher")

function(OUI_FILE _filename)
    IF (NOT ARGC GREATER 1)
      SET(ARGV1 cc)
    ENDIF(NOT ARGC GREATER 1)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.${ARGV1}
        COMMAND ${OUI_EXE}
                -o${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.${ARGV1}
                ${le_das_OUI_PATH} ${OUI_VERBOSITY}
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${_filename} ${OUI_EXE} )
endfunction(OUI_FILE)
