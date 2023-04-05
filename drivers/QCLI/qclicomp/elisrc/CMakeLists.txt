cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(qclicomp  VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

ADD_CUSTOM_COMMAND(
  OUTPUT qclicomp
  COMMAND ./gen_qclicomp.sh ${ELI_EXE} qclicomp.specs ${CMAKE_CURRENT_BINARY_DIR}/qclicomp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS
    qclicomp.specs
    qclicomp.clp
    qclicomp.con
    qclicomp.gla
    qclicomp.lido
    qclicomp.pdl
    qclicomp.ptg
    qclicomp.h
    qclicomp.head.phi
    qclicomp.ptg.phi
    qclicomp.init.phi
    qclicomp.finl.phi
    linepos.c
    pickres.c
)
add_custom_target(gen_qclicomp ALL DEPENDS qclicomp)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/qclicomp
        DESTINATION bin)
