cmake_minimum_required (VERSION 3.4.3)

project(stopeight-clibs-analyzer)
aux_source_directory(. SRC_LIST)
set(${PROJECT_NAME}_sources
    turns.cpp
)
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${stopeight-clibs_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
