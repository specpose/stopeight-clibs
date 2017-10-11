cmake_minimum_required (VERSION 3.4.3)

project(stopeight-clibs-grapher)

aux_source_directory(. SRC_LIST)
#file(GLOB SOURCES "*.cpp")
set(${PROJECT_NAME}_sources
    containers.cpp
    algo.cpp
    grapher.cpp
    mean.cpp
    main.cpp
)

message(${stopeight-clibs_INCLUDE_DIRS})

#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

#include_directories(${stopeight-clibs_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${stopeight-clibs_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
