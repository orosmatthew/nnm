#include "nnm/tests.hpp"

#include "geom2/tests.hpp"
#include "geom3/tests.hpp"

// ReSharper disable once CppDFATimeOver
int main()
{
    core_tests();
    vector2_tests();
    point2_tests();
    vector2i_tests();
    vector3_tests();
    point3_tests();
    vector3i_tests();
    vector4_tests();
    quaternion_tests();
    matrix2_tests();
    basis2_tests();
    matrix3_tests();
    transform2_tests();
    basis3_tests();
    matrix4_tests();
    transform3_tests();
    point_set_tests();
    line2_tests();
    ray2_tests();
    segment2_tests();
    circle2_tests();
    triangle2_tests();
    rectangle2_tests();
    aligned_rectangle2_tests();
    line3_tests();
    ray3_tests();
    segment3_tests();
    plane_tests();
    triangle3_tests();
    rectangle3_tests();
    sphere_tests();
    aligned_box_tests();
    box_tests();
    frustum_tests();

    END_TESTS
}
