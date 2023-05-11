cmake_minimum_required(VERSION 3.18)

project(grapher)
find_library(stopeight-clibs-grapher_FOUND stopeight-clibs-grapher REQUIRED)
find_library(stopeight-clibs-matrix_FOUND stopeight-clibs-matrix REQUIRED)
find_path(stopeight-clibs_FOUND stopeight-clibs REQUIRED)

find_package(Python COMPONENTS Development Interpreter Numpy )
if (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
message(FATAL_ERROR,"NumPy headers are required for dtype symbol generation")
endif (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} IFPyGrapher.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE stopeight-clibs-matrix
    PRIVATE stopeight-clibs-grapher
)
target_include_directories(${PROJECT_NAME} PRIVATE ${stopeight-clibs_INCLUDE_DIRS})