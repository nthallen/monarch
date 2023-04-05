cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(qclicomp  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# message("Top of qclicomp's CMakeList.txt")

if (NOT ${CMAKE_CROSSCOMPILING})

message("We are not cross compiling")
find_program(ELI_EXE eli DOC "Eli Compiler Construction Tool")
if ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))

add_subdirectory(derived)

else ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))

message("We have found eli: ${ELI_EXE}")
add_subdirectory(elisrc)

endif ((ELI_EXE STREQUAL "ELI_EXE-NOTFOUND"))
endif (NOT ${CMAKE_CROSSCOMPILING})
