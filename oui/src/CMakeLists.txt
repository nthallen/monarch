# project(oui)

find_program(LEX_EXE
    flex
)
if(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")
    message(FATAL_ERROR "dear user, plase install flex!")
endif(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")

find_program(YACC_EXE
    bison
)
if(YACC_EXE STREQUAL "YACC_EXE-NOTFOUND")
    message(FATAL_ERROR "dear user, plase install bison!")
endif(YACC_EXE STREQUAL "YACC_EXE-NOTFOUND")

# reuseable cmake macro for yacc
MACRO(YACC_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.c
                ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.h
        COMMAND ${YACC_EXE} -d
                --output=${_basename}.c
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        DEPENDS ${_filename}
    )
ENDMACRO(YACC_FILE)

# reuseable cmake macro for lex
MACRO(LEX_FILE _filename)
    GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
    ADD_CUSTOM_COMMAND(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.c
        COMMAND ${LEX_EXE} -i -L
                -o${_basename}.c
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        DEPENDS ${_filename} )
ENDMACRO(LEX_FILE)

YACC_FILE(ouigrmr.y)
LEX_FILE(yylex.l)

add_executable(oui llop.c opnifile.c ouigrmr.c ouiinit.c ouimain.c
      output.c sortpkg.c yylex.c)

target_compile_definitions(oui PRIVATE
  -DPKGDATADIR="${CMAKE_INSTALL_PREFIX}/share/oui")
target_include_directories(oui PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/nl/src)
target_link_libraries(oui nl)
install(TARGETS oui RUNTIME DESTINATION bin)
install(FILES oui.h DESTINATION include)

# ouiinit.c is generated via oui
# oui -o ouiinit.c ouiinit.oui
