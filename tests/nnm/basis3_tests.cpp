#include "tests.hpp"

void basis3_tests()
{
    test_case("Basis3");
    test_section("Basis3()");
    {
        constexpr nnm::Basis3f b1;
        TEST_ASSERT(b1.matrix == nnm::Matrix3f::identity());
    }

    test_section("Basis3(const Basis3<Other>&)");
    {
        constexpr nnm::Basis3d b1({ { 1.0, 2.0, 3.0 }, { -0.5, -0.75, 0.1 }, { 2.0, 88.0, -101.0 } });
        constexpr nnm::Basis3f b2(b1);
        TEST_ASSERT(b2.matrix.columns[0] == nnm::Vector3f(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(b2.matrix.columns[1] == nnm::Vector3f(-0.5f, -0.75f, 0.1f));
        TEST_ASSERT(b2.matrix.columns[2] == nnm::Vector3f(2.0f, 88.0f, -101.0f));
    }

    test_section("Basis3(const Matrix3&)");
    {
        constexpr nnm::Matrix3f m1 { { 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 3.0f, -8.0f, 1.0f } };
        constexpr nnm::Basis3f b2(m1);
        TEST_ASSERT(b2.matrix == m1);
    }

    test_section("from_rotation_axis_angle");
    {
        auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, nnm::pi<float>());
        TEST_ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }))
        auto b2 = nnm::Basis3f::from_rotation_axis_angle({ 2.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        TEST_ASSERT(b2.matrix.approx_equal(
            { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.707107f, 0.707107f }, { 0.0f, -0.707107f, 0.707107f } }));
    }

    test_section("from_rotation_quaternion");
    {
        constexpr auto b
            = nnm::Basis3f::from_rotation_quaternion(nnm::Quaternion(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f));
        constexpr nnm::Basis3f expected(
            { { 0.9980918f, -0.0213389f, -0.0579437f },
              {
                  0.0335516f,
                  0.9751930f,
                  0.2187989f,
              },
              { 0.0518374f, -0.2203254f, 0.9740480f } });
        TEST_ASSERT(b.approx_equal(expected));
    }

    test_section("from_scale");
    {
        constexpr auto b1 = nnm::Basis3f::from_scale({ -1.0f, 2.0f, 3.0f });
        TEST_ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f, 3.0f } }));
    }

    test_section("from_shear_x");
    {
        constexpr auto b1 = nnm::Basis3f::from_shear_x(0.5f, -0.1f);
        TEST_ASSERT(b1.matrix.approx_equal({ { 1.0f, 0.5f, -0.1f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }));
    }

    test_section("from_shear_y");
    {
        constexpr auto b1 = nnm::Basis3f::from_shear_y(0.5f, -0.1f);
        TEST_ASSERT(b1.approx_equal(nnm::Basis3f({ { 1.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, -0.1f }, { 0.0f, 0.0f, 1.0f } })));
    }

    test_section("from_shear_z");
    {
        constexpr auto b1 = nnm::Basis3f::from_shear_z(0.5f, -0.1f);
        TEST_ASSERT(b1.approx_equal(nnm::Basis3f({ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, -0.1f, 1.0f } })));
    }

    test_section("trace");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr auto result = b.trace();
        TEST_ASSERT(nnm::approx_equal(result, 12.0f));
    }

    test_section("determinant");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr auto result = b.determinant();
        TEST_ASSERT(nnm::approx_equal(result, -54.925f));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Basis3f expected(
            { { -0.254893f, -0.0345926f, 0.819299f },
              { -0.559854f, -0.00455166f, 0.37096f },
              { 0.270369f, 0.0509786f, -0.154756f } });
        constexpr auto result = b.unchecked_inverse();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Basis3f expected(
            { { -0.254893f, -0.0345926f, 0.819299f },
              { -0.559854f, -0.00455166f, 0.37096f },
              { 0.270369f, 0.0509786f, -0.154756f } });
        constexpr auto result = b.inverse();
        TEST_ASSERT(result.has_value() && result.value().approx_equal(expected));
        TEST_ASSERT_FALSE(nnm::Basis3(nnm::Matrix3f::zero()).inverse().has_value());
    }

    test_section("valid");
    {
        constexpr nnm::Basis3 b1(nnm::Matrix3f::zero());
        constexpr auto result = b1.valid();
        TEST_ASSERT_FALSE(result);
        nnm::Basis3f b2;
        TEST_ASSERT(b2.valid());
        nnm::Basis3f b3({ { 1.0f, 2.0f, 3.0f }, { 2.0f, 4.0f, 6.0f }, { 3.0f, 6.0f, 9.0f } });
        TEST_ASSERT_FALSE(b3.valid());
        nnm::Basis3f b4({ { 1.0f, 2.0f, 3.0f }, { 3.0f, 1.0f, 3.0f }, { -2.0f, 3.0f, 1.0f } });
        TEST_ASSERT(b4.valid());
    }

    test_section("rotate_axis_angle");
    {
        auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 2.0f);
        nnm::Basis3 b1_rot = b1.rotate_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        TEST_ASSERT(b1_rot.matrix.approx_equal(
            { { 0.707107f, 0.0f, -0.707107f }, { 0.707107f, 0.0f, 0.707107f }, { 0.0f, -1.0f, 0.0f } }));
    }

    test_section("rotate_axis_angle_local");
    {
        auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, -nnm::pi<float>() / 4.0f);
        nnm::Basis3 b1_rot = b1.rotate_axis_angle_local({ 0.0f, 0.0f, 3.0f }, nnm::pi<float>() / 2.0f);
        TEST_ASSERT(b1_rot.matrix.approx_equal(
            { { 0.0f, 1.0f, 0.0f }, { -0.707107f, 0.0f, -0.707107f }, { -0.707107f, 0.0f, 0.707107f } }))
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
        constexpr nnm::Basis3f expected(
            { { 0.956907f, -2.08189f, -0.0085175f },
              { 0.623695f, 5.36143f, 21.7124f },
              { 1.54226f, -0.447372f, 0.843373f } });
        constexpr auto result = b.rotate_quaternion(q);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("rotate_quaternion_local");
    {
        constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
        constexpr nnm::Basis3f expected(
            { { 0.92718f, -2.19798f, 0.0143242f },
              { -0.369645f, 9.64107f, 19.7394f },
              { 1.67815f, -2.50174f, -3.40654f } });
        constexpr auto result = b.rotate_quaternion_local(q);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("scale");
    {
        constexpr nnm::Basis3f b1 { { { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } } };
        constexpr nnm::Basis3f b1_scaled = b1.scale({ 2.0f, -1.0f, 0.4f });
        TEST_ASSERT(b1_scaled.matrix.approx_equal({ { 0.0f, 0.0f, -0.4f }, { 0.0f, -1.0f, 0.0f }, { 2.0f, 0.0f, 0.0f } }));
    }

    test_section("scale_local");
    {
        constexpr nnm::Basis3f b1 {
            { { 0.707106769f, -0.707106769f, 0.0f }, { 0.707106769f, 0.707106769f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
        };
        constexpr nnm::Basis3f b1_scaled = b1.scale_local({ 0.6f, 2.0f, -1.5f });
        TEST_ASSERT(b1_scaled.matrix.approx_equal(
            { { 0.424264f, -0.424264f, 0.0f }, { 1.41421f, 1.41421f, 0.0f }, { 0.0f, 0.0f, -1.5f } }));
    }

    test_section("shear_x");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } } };
        constexpr auto b1_sheared = b1.shear_x(1.5f, -0.1f);
        TEST_ASSERT(b1_sheared.matrix.approx_equal(
            { { 1.0f, -0.5f, 0.4f }, { -0.75f, 8.875f, 20.075f }, { 1.5f, 2.05f, 0.85f } }));
    }

    test_section("shear_x_local");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } } };
        constexpr auto b1_sheared = b1.shear_x_local(1.5f, -0.1f);
        TEST_ASSERT(b1_sheared.matrix.approx_equal(
            { { -0.275f, 13.02f, 30.4f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } }));
    }

    test_section("shear_y");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
        constexpr auto b1_sheared = b1.shear_y(-1.5f, -0.1f);
        TEST_ASSERT(
            b1_sheared.matrix.approx_equal({ { 4.0f, -2.0f, 3.2f }, { -11.5f, 5.0f, -6.5f }, { -1.5f, 1.0f, -3.1f } }));
    }

    test_section("shear_y_local");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
        constexpr auto b1_sheared = b1.shear_y_local(1.3f, 0.3f);
        TEST_ASSERT(b1_sheared.matrix.approx_equal({ { 1.0f, -2.0f, 3.0f }, { -2.7f, 2.7f, -3.0f }, { 0.0f, 1.0f, -3.0f } }))
    }

    test_section("shear_z");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
        constexpr auto b1_sheared = b1.shear_z(1.2f, -0.8f);
        TEST_ASSERT(
            b1_sheared.matrix.approx_equal({ { 4.6f, -4.4f, 3.0f }, { -11.2f, 9.8f, -6.0f }, { -3.6f, 3.4f, -3.0f } }))
    }

    test_section("shear_z_local");
    {
        constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
        constexpr auto b1_sheared = b1.shear_z_local(-1.2f, 0.8f);
        TEST_ASSERT(
            b1_sheared.matrix.approx_equal({ { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -4.4f, 7.4f, -11.4f } }));
    }

    test_section("transform");
    {
        constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
        constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
        constexpr auto b3 = b1.transform(b2);
        TEST_ASSERT(b3.matrix.approx_equal({ { 34.0f, 11.5f, -111.0f }, { 2.0f, -2.8f, 5.5f }, { 13.0f, 4.25f, -35.0f } }))
    }

    test_section("transform_local");
    {
        constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
        constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
        constexpr auto b3 = b1.transform_local(b2);
        TEST_ASSERT(b3.matrix.approx_equal({ { 5.0f, -0.5f, 6.15f }, { 0.5f, -4.0f, 0.2f }, { -38.5f, 14.0f, -4.8f } }))
    }

    test_section("approx_equal");
    {
        constexpr nnm::Basis3f b1(
            { { 1.000001f, -0.00001f, 0.0f }, { 0.0f, 0.99999999f, 0.000001f }, { 0.0f, 0.0f, 1.0f } });
        constexpr auto result = b1.approx_equal(nnm::Basis3f());
        TEST_ASSERT(result);
    }

    constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
    constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });

    test_section("at");
    {
        constexpr auto result = b1.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(b1.at(1, 2) == 0.1f);
        TEST_ASSERT(b2.at(2, 2) == -35.0f);
    }

    test_section("operator[]");
    {
        constexpr auto result = b1[0];
        TEST_ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(b1[1] == nnm::Vector3(2.0f, -3.0f, 0.1f));
        TEST_ASSERT(b2[2] == nnm::Vector3(10.0f, 2.0f, -35.0f));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = b1 == b1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(b1 == b2);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = b1 != b1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(b1 != b2);
    }

    test_section("operator<");
    {
        constexpr auto result = b1 < b2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(b2 < b1);
    }
}