cmake_minimum_required (VERSION 3.4.3)

project(grapher)
#aux_source_directory(. SRC_LIST)
#set(${PROJECT_NAME}_sources
#    IFPyGrapher.cpp
#)
pybind11_add_module(${PROJECT_NAME} IFPyGrapher.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stopeight-clibs-grapher
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../grapher"
    ${stopeight-clibs_INCLUDE_DIRS}
    "../cmake-git-version-tracking/better-example"
)
