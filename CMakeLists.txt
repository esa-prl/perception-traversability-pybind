cmake_minimum_required(VERSION 3.12...3.18)
project(traversability_pybind)

find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories ( ${EIGEN3_INCLUDE_DIRS} )

add_executable(traversability perception-traversability/src/traversability.cpp)
target_link_libraries(traversability ${OpenCV_LIBS})

find_package(pybind11 REQUIRED)
pybind11_add_module(traversability_pybind src/traversability_pybind.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(traversability_pybind PRIVATE VERSION_INFO=${TRAVERSABILITY_PYBIND_VERSION_INFO})