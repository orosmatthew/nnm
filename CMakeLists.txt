cmake_minimum_required(VERSION 3.5)

project(nnm VERSION 0.5.0)

option(NNM_BUILD_TESTS "NNM Build Tests" OFF)

set(CMAKE_CXX_STANDARD 17)

add_library(nnm INTERFACE)
target_include_directories(nnm INTERFACE include)

if (NNM_BUILD_TESTS)
    add_executable(nnm_tests tests/main.cpp
            tests/test.hpp)
    target_link_libraries(nnm_tests PRIVATE nnm)
endif ()