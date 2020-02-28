cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(cmdgen VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT ${CMAKE_CROSSCOMPILING})

install(FILES base.tmc Demo.doit Demo.spec Demo.tbl Demo.tma
        doit Experiment.config interact services VERSION
        DESTINATION /usr/local/share/linkeng/setup/src)

endif (NOT ${CMAKE_CROSSCOMPILING})
