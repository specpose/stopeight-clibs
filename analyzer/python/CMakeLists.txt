cmake_minimum_required (VERSION 3.18)

project(analyzer)
find_library(stopeight-clibs-analyzer_FOUND stopeight-clibs-analyzer REQUIRED)
find_path(stopeight-clibs_FOUND stopeight-clibs REQUIRED)

find_package(Python COMPONENTS Development Interpreter Numpy )
if (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
message(FATAL_ERROR,"NumPy headers are required for dtype symbol generation")
endif (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} IFPyAnalyzer.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE stopeight-clibs-analyzer)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../"
)