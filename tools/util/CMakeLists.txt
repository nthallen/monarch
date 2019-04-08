cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das_tools_util VERSION 2.0.0)

install(PROGRAMS appgen appgen_module
  DESTINATION bin)

install(FILES appgen.mk
  DESTINATION share/linkeng)
