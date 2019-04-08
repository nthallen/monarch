cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das_tools_util VERSION 2.0.0)

install(PROGRAMS
  appgen
  appgen_module
  genui
  genui_chk
  DESTINATION bin)

install(FILES
  appgen.mk
  edf2ext.awk
  edf2oui.awk
  DESTINATION share/linkeng)
