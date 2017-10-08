#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required (VERSION 3.4.3)

project(stopeight-clibs-grapher)
aux_source_directory(. SRC_LIST)
#file(GLOB SOURCES "*.cpp")
set(${PROJECT_NAME}_sources
    shared-include/angle_functions.cpp
    shared-include/containers.cpp
    shared-include/preloaderif.cpp
    shared-include/shared_types.cpp
    algo.cpp
    grapher.cpp
    mean.cpp
    main.cpp
)
#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "shared-include"
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
