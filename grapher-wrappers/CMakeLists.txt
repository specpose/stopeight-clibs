cmake_minimum_required (VERSION 3.4.3)

find_package(stopeight-clibs-grapher)
if (stopeight-clibs-grapher_FOUND)

project(grapher)
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

endif (stopeight-clibs-grapher_FOUND)
