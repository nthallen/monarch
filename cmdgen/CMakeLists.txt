# project(cmdgen)

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
        COMMAND ${YACC_EXE} -d -t -l
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
        COMMAND ${LEX_EXE} -i
                -o${_basename}.c
                ${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
        DEPENDS ${_filename} )
ENDMACRO(LEX_FILE)

YACC_FILE(yyparse.y)
LEX_FILE(yylex.l)
set(CURSES_NEED_NCURSES, TRUE)
find_package(Curses)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/cmdalgo.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmdalgo.h )

add_executable(cmdgen cmdgen.c dstructs.c interfaces.c prompts.c
    rules.c states.c trie.c vunion.c yyparse.c yylex.c)
target_include_directories(cmdgen PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${le_das_SOURCE_DIR}/nl/src)
target_link_libraries(cmdgen nl)
install(TARGETS cmdgen RUNTIME
        DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmdalgo.h
        DESTINATION include)
install(FILES cmdgen.skel
        DESTINATION share/linkeng)
