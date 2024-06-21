cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(sb_driver VERSION 1.0.0)

install(FILES
  sb_cmd_driver.cc.tmpl
  sb_cmd_driver.h.tmpl
  sb_cmd_driver.oui.tmpl
  sb_col_driver.cc.tmpl
  sb_col_driver.h.tmpl
  sb_col_driver.oui.tmpl
  sb_driver.agm
  sb_driver.cc
  sb_driver.h
  DESTINATION share/monarch/modules/sb_driver
)
