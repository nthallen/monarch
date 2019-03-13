cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-drivers VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_CROSSCOMPILING})
  link_directories( /opt/linkeng/am335x/lib )
  include_directories( /opt/linkeng/am335x/include )
else (${CMAKE_CROSSCOMPILING})
  link_directories( /usr/local/lib )
  include_directories( /usr/local/include )
endif (${CMAKE_CROSSCOMPILING})

add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus"
                 "${le-das-drivers_BINARY_DIR}/subbus")
