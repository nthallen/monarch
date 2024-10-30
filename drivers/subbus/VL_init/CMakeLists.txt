cmake_minimum_required(VERSION 2.8.8...3.20.0)
cmake_policy(SET CMP0048 NEW)
project(monarch-VL_init VERSION 1.0.0)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)
# add_definitions( -D_POSIX_C_SOURCE=200809 )

include( ../../../oui_setup.cmake )

set(PROGRAM_PERMISSIONS_DEFAULT
    OWNER_WRITE OWNER_READ OWNER_EXECUTE SETUID
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

OUI_FILE(VL_init.oui)
add_executable(VL_init VL_init.cc VL_initoui.cc)
target_link_libraries(VL_init dasio nl pthread)
install(TARGETS VL_init RUNTIME DESTINATION bin
  PERMISSIONS ${PROGRAM_PERMISSIONS_DEFAULT})
