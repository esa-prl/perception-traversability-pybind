cmake_minimum_required(VERSION 3.12...3.18)
project(traversability_pybind)

# Find packages **************************************************************************************************
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)

# Include **************************************************************************************************
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}/opencv4)
include_directories (${EIGEN3_INCLUDE_DIRS} )
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${pybind11_INCLUDE_DIR})

add_library(traversability perception-traversability/src/traversability.cpp)
target_link_libraries(traversability PUBLIC ${OpenCV_LIBS})

pybind11_add_module(traversability_pybind src/traversability_pybind.cpp)
target_link_libraries(traversability_pybind PUBLIC traversability ${OpenCV_LIBS})

# Alternative implementation for adding traversability_pybind library
# add_library(traversability_pybind src/traversability_pybind.cpp)
# target_link_libraries(traversability_pybind pybind11::module pybind11::lto pybind11::windows_extras ${OpenCV_LIBS})
# pybind11_extension(traversability_pybind)
# pybind11_strip(traversability_pybind)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(traversability_pybind PRIVATE VERSION_INFO=${TRAVERSABILITY_PYBIND_VERSION_INFO})
