cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(subbus VERSION 2.0.0)

add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus/libpp"
                 "${le-das-drivers_BINARY_DIR}/subbus/libpp")
add_subdirectory("${le-das-drivers_SOURCE_DIR}/subbus/subbusd"
                 "${le-das-drivers_BINARY_DIR}/subbus/subbusd")
