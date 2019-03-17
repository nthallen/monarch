cmake_minimum_required(VERSION 2.8.8)
cmake_policy(SET CMP0048 NEW)
project(oui VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT ${CMAKE_CROSSCOMPILING})

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(OUI_Scanner yylex.l ${CMAKE_CURRENT_BINARY_DIR}/yylex.c
            COMPILE_FLAGS "-i -L")
BISON_TARGET(OUI_Parser ouigrmr.y ${CMAKE_CURRENT_BINARY_DIR}/ouigrmr.c)
ADD_FLEX_BISON_DEPENDENCY(OUI_Scanner OUI_Parser)

add_executable(oui llop.c opnifile.c ouiinit.c ouimain.c
      output.c sortpkg.c
      ${BISON_OUI_Parser_OUTPUT_SOURCE}
      ${FLEX_OUI_Scanner_OUTPUTS})

target_compile_definitions(oui PRIVATE
  -DPKGDATADIR="${CMAKE_INSTALL_PREFIX}/share/oui")
target_include_directories(oui PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${le_das_SOURCE_DIR}/libs/nl)
target_link_libraries(oui nl)
install(TARGETS oui RUNTIME DESTINATION bin)
install (FILES oui.oui DESTINATION share/oui)

endif (NOT ${CMAKE_CROSSCOMPILING})

install(FILES oui.h DESTINATION include)

# ouiinit.c is generated via oui
# oui -o ouiinit.c ouiinit.oui
