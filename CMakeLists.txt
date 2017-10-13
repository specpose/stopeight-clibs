cmake_minimum_required (VERSION 3.1.3)

#if building shared lib:
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(stopeight-clibs)
add_library(${PROJECT_NAME} INTERFACE)
#target_sources(${PROJECT_NAME} INTERFACE
#    include/stopeight-clibs/algo.h
#    include/stopeight-clibs/angle_functions.h
#    include/stopeight-clibs/grapher.h
#    include/stopeight-clibs/mean.h
#    include/stopeight-clibs/preloaderif.h
#    include/stopeight-clibs/shared_types.h
#)
message(${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include/)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_subdirectory(grapher)
add_subdirectory(analyzer)
