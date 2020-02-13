cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das_drivers_TMbase VERSION 1.0.0)

install(FILES
  cpu_usage.tmc
  cpu_usage_col.tmc
  flttime.tmc
  freemem_col.tmc
  freemem_def.tmc.in
  root.cmd
  tdrift.tmc
  tdrift_col.tmc
  TMbase.agm
  TMbase.genui.in
  TMbase.tbl.in
  DESTINATION share/linkeng)
