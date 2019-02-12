cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(le_das VERSION 2.0.0)

add_subdirectory("${CMAKE_SOURCE_DIR}/drivers/subbus"
                 "${CMAKE_BINARY_DIR}/drivers/subbus")
