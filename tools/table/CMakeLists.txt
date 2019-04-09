cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(table  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# message("Top of table's CMakeList.txt")

if (NOT ${CMAKE_CROSSCOMPILING})

message("We are not cross compiling")
find_program(ELI_EXE eli DOC "Eli Compiler Construction Tool")
if ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))

add_subdirectory(derived)

else ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))

message("We have found eli: ${ELI_EXE}")
ADD_CUSTOM_COMMAND(
  OUTPUT nctable.exe
  COMMAND ./gen_nctable.sh ${ELI_EXE} nctable.specs ${CMAKE_CURRENT_BINARY_DIR}/nctable.exe
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS
    nctable.specs
    ntable.clp
    ntable.con
    ntable.gla
    nctable.lido
    mod.lido
    nctable.HEAD.phi
    table.INIT.phi
    table.FINL.phi
    ntable.map
    dim.c
    dim.h
    dimfunc.h
    depfile.c
    depfile.h
    table_name.c
    table_name.h
    ncbox.c
    ncbox.h
    nparam.c
    param.h
    ncmodprint.c
    ncmodprint.h
    ntable.pdl
    nctable.ptg
)
add_custom_target(gen_nctable ALL DEPENDS nctable.exe)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/nctable.exe
        DESTINATION bin)

endif ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))
endif (NOT ${CMAKE_CROSSCOMPILING})
