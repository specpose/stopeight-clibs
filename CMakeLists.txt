cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(stopeight-clibs)
include(${PROJECT_SOURCE_DIR}/Package.cmake)

include(${PROJECT_SOURCE_DIR}/InstallHeaders.cmake)
include(${PROJECT_SOURCE_DIR}/Includes.cmake)
add_subdirectory(matrix)
add_subdirectory(analyzer)
add_subdirectory(grapher)
add_subdirectory(legacy)
