# CMake for dasio/test
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions( -D_POSIX_SOURCE=1 -D_XOPEN_SOURCE=500 )

add_executable(test_timeout test_timeout.cc)
target_include_directories(test_timeout PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_timeout dasio nl gtest)

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

add_executable(test_not test_not.cc)
target_include_directories(test_not PUBLIC
  ../src
  ${CMAKE_SOURCE_DIR}/tm/src
  ${CMAKE_SOURCE_DIR}/nl/src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_not dasio nl tm gtest)

add_executable(echosrvr echosrvr.cc)
target_include_directories(echosrvr PUBLIC
  ../src
  ${CMAKE_SOURCE_DIR}/nl/src)
target_link_libraries(echosrvr dasio nl tm)

add_executable(tmsrvr tmsrvr.cc)
target_include_directories(tmsrvr PUBLIC
  ${CMAKE_SOURCE_DIR}/dasio/src
  ${CMAKE_SOURCE_DIR}/nl/src)
target_link_libraries(tmsrvr dasio nl tm)

add_executable(tmclt tmclt.cc)
target_include_directories(tmclt PUBLIC
  ${CMAKE_SOURCE_DIR}/dasio/src
  ${CMAKE_SOURCE_DIR}/nl/src)
target_link_libraries(tmclt dasio nl tm)
