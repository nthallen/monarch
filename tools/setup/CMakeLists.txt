cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch_utils_setup VERSION 1.0.0)

set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS
  ssh_agent.sh
  monarch-install.sh.in
  cygwin-monarch-install.ps1.in
)

set(EXP_HOMEBASE "")
set(EXP_GIT_URL "")
set(FLTUSER "flight")
set(FLTGRP "flight")
file(READ ssh_agent.sh SSH_AGENT)
configure_file(monarch-install.sh.in monarch-install.sh @ONLY)
file(READ ${CMAKE_CURRENT_BINARY_DIR}/monarch-install.sh MONARCH_EXP_SETUP)
configure_file(cygwin-monarch-install.ps1.in cygwin-monarch-install.ps1 @ONLY)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch_setup.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch_reset.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch-win-setup.ps1
  ${CMAKE_CURRENT_BINARY_DIR}/cygwin-monarch-install.ps1
  ${CMAKE_CURRENT_BINARY_DIR}/monarch-install.sh
  DESTINATION share/monarch/setup)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/mk_installers
  DESTINATION bin)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch_add_user
  DESTINATION sbin)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch.service services
  DESTINATION share/monarch/setup)
