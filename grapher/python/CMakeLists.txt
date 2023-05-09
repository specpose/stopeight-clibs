cmake_minimum_required (VERSION 3.12)

#find_package(stopeight-clibs-grapher)
#find_package(stopeight-clibs-matrix)
#if (stopeight-clibs-grapher_FOUND AND stopeight-clibs-matrix_FOUND)

find_package(Python COMPONENTS Development Interpreter)
if (Python_Development_FOUND AND Python_Interpreter_FOUND)
find_package(pybind11 CONFIG)
if (pybind11_FOUND)

project(grapher)
pybind11_add_module(${PROJECT_NAME} IFPyGrapher.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE stopeight-clibs-matrix
    PRIVATE stopeight-clibs-grapher
)
target_include_directories(${PROJECT_NAME} PRIVATE ${stopeight-clibs_INCLUDE_DIRS})

endif (pybind11_FOUND)
endif (Python_Development_FOUND AND Python_Interpreter_FOUND)

#endif (stopeight-clibs-grapher_FOUND AND stopeight-clibs-matrix_FOUND)
