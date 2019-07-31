cmake_minimum_required(VERSION 3.8)
project(pybind11_project_example)

set(CMAKE_CXX_STANDARD 11)


find_package(PythonInterp REQUIRED)
find_package(PythonLibs "${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}" REQUIRED )
if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    message("Using default python version: " ${PYTHONLIBS_VERSION_STRING})
endif()


add_subdirectory(external/pybind11)
include_directories(SYSTEM external/pybind11/include)

file(GLOB_RECURSE SOURCES src/**.cpp)
add_library(cpp_library SHARED ${SOURCES})
target_include_directories(cpp_library PUBLIC ./include)

file(GLOB_RECURSE BINDING_SOURCES cpp_library_bindings/**.cpp)
pybind11_add_module(cpp_library_bindings MODULE ${BINDING_SOURCES})
target_link_libraries(cpp_library_bindings PRIVATE cpp_library)