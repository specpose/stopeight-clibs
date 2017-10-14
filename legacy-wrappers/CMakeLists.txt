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
)
