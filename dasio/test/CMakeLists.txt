# CMake for dasio/test
add_executable(dasio_test dasio_test.cc)
target_include_directories(dasio_test PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(dasio_test dasio nl gtest)