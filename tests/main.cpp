#include "tests.hpp"

#include "test_helper.hpp"

int main()
{
    function_tests();
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

    END_TESTS
}
