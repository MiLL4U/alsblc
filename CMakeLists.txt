set(MODULE_NAME "alsblc")

cmake_minimum_required(VERSION 3.4...3.18)
project(${MODULE_NAME})

add_subdirectory(pybind11)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(test src/test.cpp src/asymleastsquare.cpp)
# pybind11_add_module(${MODULE_NAME} src/main.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
# target_compile_definitions(${MODULE_NAME}
#                            PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
