cmake_minimum_required (VERSION 3.18)

project(legacy)
find_package(Qt5 COMPONENTS Core REQUIRED)

find_library(stopeight-clibs-legacy_FOUND stopeight-clibs-legacy REQUIRED)

find_package(Python COMPONENTS Development Interpreter)
if (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND))
message(FATAL_ERROR,"Python development headers and/or interpreter not found")
endif (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND))
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} 
    interfacepython.cpp
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE stopeight-clibs-legacy
    PRIVATE Qt5::Core
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../../include"
    ${Qt5_Core_INCLUDE_DIRS}
#ubuntu includes/qt5/
)

project(finders)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)

find_library(stopeight-clibs-legacy_FOUND stopeight-clibs-legacy REQUIRED)
find_path(stopeight-clibs_FOUND stopeight-clibs REQUIRED)

find_package(Python COMPONENTS Development Interpreter Numpy )
if (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
message(FATAL_ERROR,"NumPy headers are required for dtype symbol generation")
endif (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} 
    IFPyFinders.cpp
    IFPyShared.cpp
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE stopeight-clibs-legacy
    PRIVATE stopeight-clibs-matrix
    PRIVATE Qt5::Core
    PRIVATE Qt5::Gui
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../../include"
    "./"
    ${Qt5_Core_INCLUDE_DIRS}
)

project(getters)
find_package(Qt5 COMPONENTS Core REQUIRED)

find_library(stopeight-clibs-legacy_FOUND stopeight-clibs-legacy REQUIRED)
find_library(stopeight-clibs-matrix_FOUND stopeight-clibs-matrix REQUIRED)
find_path(stopeight-clibs_FOUND stopeight-clibs REQUIRED)

find_package(Python COMPONENTS Development Interpreter Numpy )
if (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
message(FATAL_ERROR,"NumPy headers are required for dtype symbol generation")
endif (NOT (Python_Development_FOUND AND Python_Interpreter_FOUND AND Python_NumPy_FOUND))
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME}
    IFPyGetters.cpp
    IFPyShared.cpp
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE stopeight-clibs-legacy
    PRIVATE stopeight-clibs-matrix
    PRIVATE Qt5::Core
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../include"
    "../../include"
    "./"
    ${Qt5_Core_INCLUDE_DIRS}
)