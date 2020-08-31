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
  ${monarch_libs_SOURCE_DIR}/nl
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_socket dasio nl tm gtest)

add_executable(test_unix_name test_unix_name.cc)
target_include_directories(test_unix_name PUBLIC
  ../src
  ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_unix_name dasio nl tm gtest)

add_executable(test_not test_not.cc)
target_include_directories(test_not PRIVATE
  ../src
  ${monarch_SOURCE_DIR}/libs/tm
  ${monarch_SOURCE_DIR}/libs/nl
  ${monarch_BINARY_DIR}/googletest-src/googletest/include)
target_link_libraries(test_not dasio nl gtest)

add_executable(echosrvr echosrvr.cc)
target_include_directories(echosrvr PUBLIC
  ../src
  ${monarch_SOURCE_DIR}/libs/nl)
target_link_libraries(echosrvr dasio nl tm pthread)

add_executable(tmsrvr tmsrvr.cc)
target_include_directories(tmsrvr PUBLIC
  ${monarch_SOURCE_DIR}/libs/dasio/src
  ${monarch_SOURCE_DIR}/libs/nl)
target_link_libraries(tmsrvr dasio nl tm pthread)

add_executable(tmclt tmclt.cc)
target_include_directories(tmclt PUBLIC
  ${monarch_SOURCE_DIR}/libs/dasio/src
  ${monarch_SOURCE_DIR}/libs/nl)
target_link_libraries(tmclt dasio nl tm pthread)
