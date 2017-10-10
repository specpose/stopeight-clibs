cmake_minimum_required (VERSION 3.1.3)

#set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
#set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

project(stopeight-clibs)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
    algo.h
    angle_functions.h
    grapher.h
    mean.h
    preloaderif.h
    shared_types.h
)
target_include_directories(${PROJECT_NAME} INTERFACE stopeight-clibs/)
install(DIRECTORY stopeight-clibs/ DESTINATION include/stopeight-clibs)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_subdirectory(grapher)
