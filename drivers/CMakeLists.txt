cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le-das-drivers VERSION 2.0.0)

link_directories( /usr/local/lib )
add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus"
                 "${le-das-drivers_BINARY_DIR}/subbus")
