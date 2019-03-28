cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(table  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# message("Top of table's CMakeList.txt")

if (NOT ${CMAKE_CROSSCOMPILING})

add_subdirectory(derived)

# message("We are not cross compiling")
# find_program(ELI_EXE eli DOC "Eli Compiler Construction Tool")
# if (NOT (${ELI_EXE} EQUAL ELI_EXE-NOTFOUND))

# message("We have found eli")
# ADD_CUSTOM_COMMAND(
  # OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/nctable
  # COMMAND ${ELI_EXE} "${CMAKE_CURRENT_SOURCE_DIR}/nctable.specs +(%nflags) :exe >nctable.exe"
  # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  # DEPENDS
    # nctable.specs
    # ntable.clp
    # ntable.con
    # ntable.gla
    # nctable.lido
    # mod.lido
    # nctable.HEAD.phi
    # table.INIT.phi
    # table.FINL.phi
    # ntable.map
    # dim.c
    # depfile.c
    # table_name.c
    # ncbox.c
    # nparam.c
    # ncmodprint.c
    # ntable.pdl
    # nctable.ptg
# )

# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nctable
        # DESTINATION bin)

# endif (NOT (${ELI_EXE} EQUAL ELI_EXE-NOTFOUND))
endif (NOT ${CMAKE_CROSSCOMPILING})
