cmake_minimum_required (VERSION 3.4.3)

project(legacy)
pybind11_add_module(${PROJECT_NAME} 
    interfacepython.cpp
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stopeight-clibs-legacy
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../legacy/include"
    "../include"
    "../cmake-git-version-tracking/better-example"
)

project(finders)
pybind11_add_module(${PROJECT_NAME} 
    IFPyFinders.cpp
    IFPyShared.cpp
)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stopeight-clibs-legacy
    Qt5::Core
    Qt5::Gui
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../legacy/include"
    "../include"
    "./"
    "../cmake-git-version-tracking/better-example"
)

project(getters)
pybind11_add_module(${PROJECT_NAME}
    IFPyGetters.cpp
    IFPyShared.cpp
)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stopeight-clibs-legacy
    Qt5::Core
    Qt5::Gui
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "../legacy/include"
    "../include"
    "./"
    "../cmake-git-version-tracking/better-example"
)
