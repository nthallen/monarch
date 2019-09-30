cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbus VERSION 2.0.0)

if (${CMAKE_CROSSCOMPILING})
  set(OUI_EXE /usr/local/bin/oui)
else (${CMAKE_CROSSCOMPILING})
  set(OUI_EXE ${le_das_BINARY_DIR}/tools/oui/src/oui)
endif (${CMAKE_CROSSCOMPILING})

# reuseable cmake macro for lex
include ( ../../oui_setup.cmake )
# MACRO(OUI_FILE _filename)
    # GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    # ADD_CUSTOM_COMMAND(
        # OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
        # COMMAND ${OUI_EXE}
                # -o${CMAKE_CURRENT_BINARY_DIR}/${_basename}oui.cc
                # -I${le_das_SOURCE_DIR}/libs/dasio/src
                # -I${le_das_SOURCE_DIR}/tools/oui/src
                # ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        # DEPENDS ${_filename} $(OUI_EXE) )
# ENDMACRO(OUI_FILE)

add_subdirectory(libpp)
add_subdirectory(subbusd)
add_subdirectory(include)
add_subdirectory(test)
