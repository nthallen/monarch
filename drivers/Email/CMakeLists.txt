cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(savelog VERSION 1.0.0)

# Removed obsolete .dist files
file(GLOB MY_FILES  ${CMAKE_INSTALL_PREFIX}/share/monarch/modules/Email/*.dist)
if (MY_FILES)
    file (REMOVE ${MY_FILES})
endif()

install(FILES
  account.pm.tmpl
  doreport.pm.tmpl
  doreport.in
  Email.agm
  Email.cmd
  DESTINATION share/monarch/modules/Email)
