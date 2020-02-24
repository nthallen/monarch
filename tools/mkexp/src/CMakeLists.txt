cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(cmdgen VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT ${CMAKE_CROSSCOMPILING})

install(FILES Demo.doit Demo.pcm Demo.tbl Demo.tma
        doit doit.dep Experiment.config freemem.tmc interact
        Makefile services TMbase.genui TMbase.tbl VERSION
        DESTINATION /usr/local/share/linkeng/setup/src)

endif (NOT ${CMAKE_CROSSCOMPILING})
