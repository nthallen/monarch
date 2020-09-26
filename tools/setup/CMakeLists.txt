cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(monarch_utils_setup VERSION 1.0.0)

install(PROGRAMS
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch_setup.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch_reset.sh
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch-win-setup.ps1
  DESTINATION share/monarch/setup)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/monarch.service services
  DESTINATION share/monarch/setup)
