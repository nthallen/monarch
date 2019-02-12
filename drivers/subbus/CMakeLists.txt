cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbus VERSION 2.0.0)

add_subdirectory("${CMAKE_SOURCE_DIR}/drivers/subbus/libpp"
                 "${CMAKE_BINARY_DIR}/drivers/subbus/libpp")
#add_subdirectory("${CMAKE_SOURCE_DIR}/drivers/subbus/subbusd"
#                 "${CMAKE_BINARY_DIR}/drivers/subbus/subbusd")
