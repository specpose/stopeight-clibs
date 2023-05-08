include(${PROJECT_SOURCE_DIR}/Includes.cmake)
find_package(Git)
if(Git_FOUND)
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --long --dirty OUTPUT_VARIABLE __VERSION__)
  string(STRIP ${__VERSION__} __VERSION__)
  message(STATUS "${PROJECT_NAME} Library build __VERSION__ from git commit is \"${__VERSION__}\"")
endif()

find_package(Python COMPONENTS Interpreter Development)
if (Python_Interpreter_FOUND AND Python_Development_FOUND)
add_subdirectory(${PROJECT_SOURCE_DIR}/pybind11)
endif (Python_Interpreter_FOUND AND Python_Development_FOUND)
