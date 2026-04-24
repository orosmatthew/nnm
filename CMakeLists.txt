cmake_minimum_required(VERSION 3.5)

project(nnm VERSION 0.5.0)

option(NNM_BUILD_TESTS "NNM Build Tests" OFF)

set(CMAKE_CXX_STANDARD 17)

add_library(nnm INTERFACE)
target_include_directories(nnm INTERFACE include)

if (NNM_BUILD_TESTS)
    add_executable(nnm_tests
            tests/main.cpp
            tests/test_helper.cpp
            tests/function_tests.cpp
            tests/vector2_tests.cpp
            tests/point2_tests.cpp
            tests/vector2i_tests.cpp
            tests/vector3_tests.cpp
            tests/point3_tests.cpp
            tests/vector3i_tests.cpp
            tests/vector4_tests.cpp
            tests/quaternion_tests.cpp
            tests/matrix2_tests.cpp
            tests/basis2_tests.cpp
            tests/matrix3_tests.cpp
            tests/transform2_tests.cpp
            tests/basis3_tests.cpp
            tests/matrix4_tests.cpp
            tests/transform3_tests.cpp)
    target_link_libraries(nnm_tests PRIVATE nnm)
endif ()
