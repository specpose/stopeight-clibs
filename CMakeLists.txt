cmake_minimum_required (VERSION 3.1.3)

project(stopeight-clibs)
add_library(stopeight-clibs INTERFACE)
target_sources(stopeight-clibs INTERFACE
    algo.h
    angle_functions.h
    grapher.h
    mean.h
    preloaderif.h
    shared_types.h
)
target_include_directories(stopeight-clibs INTERFACE shared-include/)
install(DIRECTORY shared-include/ DESTINATION include/stopeight-clibs)
