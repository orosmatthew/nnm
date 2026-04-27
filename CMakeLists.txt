cmake_minimum_required(VERSION 3.10)

project(nnm VERSION 0.5.0)

option(NNM_BUILD_TESTS "NNM Build Tests" OFF)

set(CMAKE_CXX_STANDARD 17)

add_library(nnm INTERFACE)
target_include_directories(nnm INTERFACE include)

if (NNM_BUILD_TESTS)
    add_executable(nnm_tests
            tests/main.cpp
            tests/test_helper.cpp
            tests/nnm/core_tests.cpp
            tests/nnm/vector2_tests.cpp
            tests/nnm/point2_tests.cpp
            tests/nnm/vector2i_tests.cpp
            tests/nnm/vector3_tests.cpp
            tests/nnm/point3_tests.cpp
            tests/nnm/vector3i_tests.cpp
            tests/nnm/vector4_tests.cpp
            tests/nnm/quaternion_tests.cpp
            tests/nnm/matrix2_tests.cpp
            tests/nnm/basis2_tests.cpp
            tests/nnm/matrix3_tests.cpp
            tests/nnm/transform2_tests.cpp
            tests/nnm/basis3_tests.cpp
            tests/nnm/matrix4_tests.cpp
            tests/nnm/transform3_tests.cpp
            tests/nnm/point_set_tests.cpp
            tests/geom2/line2_tests.cpp
            tests/geom2/ray2_tests.cpp
            tests/geom2/segment2_tests.cpp
            tests/geom2/circle2_tests.cpp
            tests/geom2/triangle2_tests.cpp
            tests/geom2/rectangle2_tests.cpp
            tests/geom2/aligned_rectangle2_tests.cpp
            tests/geom3/line3_tests.cpp
            tests/geom3/ray3_tests.cpp
            tests/geom3/segment3_tests.cpp
            tests/geom3/plane_tests.cpp
            tests/geom3/triangle3_tests.cpp
            tests/geom3/rectangle3_tests.cpp
            tests/geom3/sphere_tests.cpp
            tests/geom3/aligned_box_tests.cpp
            tests/geom3/box_tests.cpp
            tests/geom3/frustum_tests.cpp
    )
    target_link_libraries(nnm_tests PRIVATE nnm)
endif ()
