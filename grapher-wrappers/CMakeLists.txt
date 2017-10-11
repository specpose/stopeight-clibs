#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required (VERSION 3.4.3)

project(stopeight-clibs-grapher-wrappers)
aux_source_directory(. SRC_LIST)
set(${PROJECT_NAME}_sources
    interfacepython.cpp
)
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../grapher"
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
