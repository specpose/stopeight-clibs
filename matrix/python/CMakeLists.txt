cmake_minimum_required (VERSION 3.12)

#find_package(stopeight-clibs-matrix)
#if (stopeight-clibs-matrix_FOUND)

find_package(Python COMPONENTS Development Interpreter)
if (Python_Development_FOUND AND Python_Interpreter_FOUND)
find_package(pybind11 CONFIG)
if (pybind11_FOUND)

project(matrix)
pybind11_add_module(${PROJECT_NAME} IFPyMatrix.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE stopeight-clibs-matrix)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../"
)

endif (pybind11_FOUND)
endif (Python_Development_FOUND AND Python_Interpreter_FOUND)

#endif (stopeight-clibs-matrix_FOUND)
