cmake_minimum_required (VERSION 3.0.2)

project(stopeight-clibs)
add_library(stopeight-clibs INTERFACE)
target_include_directories(stopeight-clibs INTERFACE shared-include/)
install(DIRECTORY shared-include/ DESTINATION include/stopeight-clibs)
