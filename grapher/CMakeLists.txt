cmake_minimum_required (VERSION 3.12)

project(stopeight-clibs-grapher)

aux_source_directory(. SRC_LIST)
set(${PROJECT_NAME}_sources
    containers.cpp
    algo.cpp
    grapher.cpp
    mean.cpp
    main.cpp
)

#add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${stopeight-clibs_INCLUDE_DIRS}
)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)