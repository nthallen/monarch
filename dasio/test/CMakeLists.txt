# CMake for dasio/test
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 )

add_executable(dasio_test dasio_test.cc)
target_include_directories(dasio_test PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(dasio_test dasio nl gtest)

add_executable(test_socket test_socket.cc)
target_include_directories(test_socket PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_socket dasio nl tm gtest)

add_executable(test_unix_name test_unix_name.cc)
target_include_directories(test_unix_name PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_unix_name dasio nl tm gtest)
