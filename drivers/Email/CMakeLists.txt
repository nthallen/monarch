cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(savelog VERSION 1.0.0)

install(FILES
  account.pm.dist
  doreport.pm.dist
  doreport.in
  Email.agm
  Email.cmd
  DESTINATION share/monarch/modules/Email)
