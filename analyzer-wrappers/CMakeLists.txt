cmake_minimum_required (VERSION 3.4.3)

project(analyzer)

pybind11_add_module(${PROJECT_NAME} 
	interfacepython.cpp
)

#set_target_properties(${PROJECT_NAME}
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stopeight"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stopeight"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stopeight"
#)

target_link_libraries(${PROJECT_NAME} PRIVATE stopeight-clibs-analyzer)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../analyzer/include"
    ${stopeight-clibs_INCLUDE_DIRS}
)
