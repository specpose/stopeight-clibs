cmake_minimum_required (VERSION 3.23)

project(stopeight-clibs-matrix)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PRIVATE ${stopeight-clibs_INCLUDE_DIRS})
target_sources(${PROJECT_NAME}
    PUBLIC
      Matrix.cpp
    PUBLIC
      FILE_SET lib_headers
      TYPE HEADERS
      FILES
        stopeight-clibs-matrix/Matrix.h
)
install(TARGETS ${PROJECT_NAME} FILE_SET lib_headers)