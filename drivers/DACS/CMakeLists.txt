cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch_drivers_DACS VERSION 2.0.0)

install(FILES
  DACS.agm
  DACS_col.tmc
  DESTINATION share/monarch/modules/DACS)
