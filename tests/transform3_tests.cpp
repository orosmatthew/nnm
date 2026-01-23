#include "tests.hpp"

void transform3_tests()
{
    test_case("Transform3");
    test_section("Transform3()");
    {
        constexpr nnm::Transform3f t1;
        TEST_ASSERT(t1.matrix == nnm::Matrix4f::identity());
    }

    test_section("Transform3(const Transform3<Other>&)");
    {
        constexpr nnm::Transform3d t1(
            { { 1.0, 2.0, 3.0, 4.0 },
              { -0.5, 0.75, 0.6, 0.1 },
              { -100.0, -88.0, 28.0, 0.0 },
              { 1.0, 29.0, -89.0, 67.0 } });
        constexpr nnm::Transform3f t2(t1);
        TEST_ASSERT(t2.matrix.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
        TEST_ASSERT(t2.matrix.columns[1] == nnm::Vector4f(-0.5f, 0.75f, 0.6f, 0.1f));
        TEST_ASSERT(t2.matrix.columns[2] == nnm::Vector4f(-100.0f, -88.0f, 28.0f, 0.0f));
        TEST_ASSERT(t2.matrix.columns[3] == nnm::Vector4f(1.0f, 29.0f, -89.0f, 67.0f));
    }

    test_section("Transform3(const Matrix4&)");
    {
        constexpr nnm::Matrix4f m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                     { 5.0f, 6.0f, 7.0f, 8.0f },
                                     { 9.0f, 10.0f, 11.0f, 12.0f },
                                     { 13.0f, 14.0f, 15.0f, 16.0f } };
        constexpr nnm::Transform3f t2(m1);
        TEST_ASSERT(t2.matrix == m1);
    }

    test_section("from_basis_translation");
    {
        constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { -4.0f, -1.0f, 3.5f }, { 1.0f, 0.0f, 1.0f } });
        constexpr auto t1 = nnm::Transform3f::from_basis_translation(b1, { 1.0f, -2.0f, 3.0f });
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { -4.0f, -1.0f, 3.5f, 0.0f },
                                 { 1.0f, 0.0f, 1.0f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t1.matrix == expected);
    }

    test_section("from_basis");
    {
        constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { -4.0f, -1.0f, 3.5f }, { 1.0f, 0.0f, 1.0f } });
        constexpr auto t3 = nnm::Transform3f::from_basis(b1);
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { -4.0f, -1.0f, 3.5f, 0.0f },
                                 { 1.0f, 0.0f, 1.0f, 0.0f },
                                 { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t3.matrix == expected);
    }

    test_section("from_translation");
    {
        constexpr auto t2 = nnm::Transform3f::from_translation({ 1.0f, -2.0f, 3.0f });
        nnm::Matrix4f expected { { 1.0f, 0.0f, 0.0f, 0.0f },
                                 { 0.0f, 1.0f, 0.0f, 0.0f },
                                 { 0.0f, 0.0f, 1.0f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t2.matrix == expected);
    }

    test_section("from_rotation_axis_angle");
    {
        auto t1 = nnm::Transform3f::from_rotation_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi<float>() / 9.0f);
        nnm::Matrix4f expected1 { { 0.9396926f, 0.0f, -0.3420202f, 0.0f },
                                  { 0.0f, 1.0f, 0.0f, 0.0f },
                                  { 0.3420202f, 0.0f, 0.9396926f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t1.matrix.approx_equal(expected1));
    }

    test_section("from_rotation_quaternion");
    {
        constexpr auto t = nnm::Transform3f::from_rotation_quaternion(
            nnm::Quaternion(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f));
        constexpr nnm::Transform3f expected(
            { { 0.9980918f, -0.0213389f, -0.0579437f, 0.0f },
              { 0.0335516f, 0.9751930f, 0.2187989f, 0.0f },
              { 0.0518374f, -0.2203254f, 0.9740480f, 0.0f },
              { 0.0f, 0.0f, 0.0f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_scale");
    {
        constexpr auto t1 = nnm::Transform3f::from_scale({ 0.2f, -0.3f, 2.1f });
        nnm::Matrix4f expected1 { { 0.2f, 0.0f, 0.0f, 0.0f },
                                  { 0.0f, -0.3f, 0.0f, 0.0f },
                                  { 0.0f, 0.0f, 2.1f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t1.matrix.approx_equal(expected1));
    }

    test_section("from_shear_x");
    {
        constexpr auto t1 = nnm::Transform3f::from_shear_x(1.2f, -0.2f);
        nnm::Matrix4f expected1 { { 1.0f, 1.2f, -0.2f, 0.0f },
                                  { 0.0f, 1.0f, 0.0f, 0.0f },
                                  { 0.0f, 0.0f, 1.0f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t1.matrix.approx_equal(expected1));
    }

    test_section("from_shear_y");
    {
        constexpr auto t1 = nnm::Transform3f::from_shear_y(-0.2f, 1.2f);
        nnm::Matrix4f expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                  { -0.2f, 1.0f, 1.2f, 0.0f },
                                  { 0.0f, 0.0f, 1.0f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t1.matrix.approx_equal(expected1));
    }

    test_section("from_shear_z");
    {
        constexpr auto t1 = nnm::Transform3f::from_shear_z(1.5f, -0.3f);
        nnm::Matrix4f expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                  { 0.0f, 1.0f, 0.0f, 0.0f },
                                  { 1.5f, -0.3f, 1.0f, 0.0f },
                                  { 0.0f, 0.0f, 0.0f, 1.0f } };
        TEST_ASSERT(t1.matrix.approx_equal(expected1));
    }

    test_section("from_perspective_left_hand_neg1to1");
    {
        const auto t
            = nnm::Transform3f::from_perspective_left_hand_neg1to1(nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
        constexpr nnm::Transform3f expected(
            { { 0.5625f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 1.0f, 0.0f, 0.0f },
              { 0.0f, 0.0f, -1.002f, -1.0f },
              { 0.0f, 0.0f, -0.2002f, 0.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_perspective_left_hand_0to1");
    {
        const auto t
            = nnm::Transform3f::from_perspective_left_hand_0to1(nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
        constexpr nnm::Transform3f expected(
            { { 0.5625f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 1.0f, 0.0f, 0.0f },
              { 0.0f, 0.0f, -1.001f, -1.0f },
              { 0.0f, 0.0f, -0.1001f, 0.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_perspective_right_hand_neg1to1");
    {
        const auto t = nnm::Transform3f::from_perspective_right_hand_neg1to1(
            nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
        constexpr nnm::Transform3f expected(
            { { 0.5625f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 1.0f, 0.0f, 0.0f },
              { 0.0f, 0.0f, 1.002f, 1.0f },
              { 0.0f, 0.0f, -0.2002f, 0.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_perspective_right_hand_0to1");
    {
        const auto t
            = nnm::Transform3f::from_perspective_right_hand_0to1(nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
        constexpr nnm::Transform3f expected(
            { { 0.5625f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 1.0f, 0.0f, 0.0f },
              { 0.0f, 0.0f, 1.001f, 1.0f },
              { 0.0f, 0.0f, -0.1001f, 0.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_orthographic_left_hand_neg1to1");
    {
        constexpr auto t = nnm::Transform3f::from_orthographic_left_hand_neg1to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
        constexpr nnm::Transform3f expected(
            { { 0.25f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 0.3333333f, 0.0f, 0.0f },
              { 0.0f, 0.0f, -0.040404f, 0.0f },
              { -0.25f, -0.333333f, -1.020202f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_orthographic_left_hand_0to1");
    {
        constexpr auto t = nnm::Transform3f::from_orthographic_left_hand_0to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
        constexpr nnm::Transform3f expected(
            { { 0.25f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 0.3333333f, 0.0f, 0.0f },
              { 0.0f, 0.0f, -0.020202f, 0.0f },
              { -0.25f, -0.333333f, -0.010101f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_orthographic_right_hand_neg1to1");
    {
        constexpr auto t
            = nnm::Transform3f::from_orthographic_right_hand_neg1to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
        constexpr nnm::Transform3f expected(
            { { 0.25f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 0.333333f, 0.0f, 0.0f },
              { 0.0f, 0.0f, 0.040404f, 0.0f },
              { -0.25f, -0.3333333f, -1.020202f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_orthographic_right_hand_0to1");
    {
        constexpr auto t = nnm::Transform3f::from_orthographic_right_hand_0to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
        constexpr nnm::Transform3f expected(
            { { 0.25f, 0.0f, 0.0f, 0.0f },
              { 0.0f, 0.333333f, 0.0f, 0.0f },
              { 0.0f, 0.0f, 0.020202f, 0.0f },
              { -0.25f, -0.3333333f, -0.010101f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    constexpr auto t1 = nnm::Transform3f(
        { { 1.0f, 2.0f, 3.0f, 0.0f },
          { -0.5f, 2.0f, 3.0f, 0.0f },
          { 0.0f, 0.0f, 2.0f, 0.0f },
          { 1.0f, -2.0f, 3.0f, 1.0f } });

    constexpr auto t2 = nnm::Transform3f(
        { { 1.0f, 2.0f, 3.0f, 4.0f },
          { -0.5f, 2.0f, 3.0f, -3.0f },
          { 0.0f, 0.0f, 2.0f, 0.0f },
          { 1.0f, -2.0f, 3.0f, 1.0f } });

    test_section("trace");
    {
        constexpr auto result = t1.trace();
        TEST_ASSERT(nnm::approx_equal(result, 6.0f));
    }

    test_section("determinant");
    {
        constexpr auto result = t1.determinant();
        TEST_ASSERT(nnm::approx_equal(result, 6.0f));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Transform3f expected(
            { { 0.666666f, -0.6666666f, 0.0f, 0.0f },
              { 0.16666666f, 0.3333333f, -0.75f, 0.0f },
              { 0.0f, 0.0f, 0.5f, 0.0f },
              { -0.33333333f, 1.33333333f, -3.0f, 1.0f } });
        constexpr auto result = t1.unchecked_inverse();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Transform3f expected(
            { { 0.666666f, -0.6666666f, 0.0f, 0.0f },
              { 0.16666666f, 0.3333333f, -0.75f, 0.0f },
              { 0.0f, 0.0f, 0.5f, 0.0f },
              { -0.33333333f, 1.33333333f, -3.0f, 1.0f } });
        constexpr auto result = t1.inverse();
        TEST_ASSERT(result.has_value() && result.value().approx_equal(expected));
        TEST_ASSERT_FALSE(nnm::Transform3(nnm::Matrix4f::zero()).inverse().has_value());
    }

    test_section("valid");
    {
        constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).valid();
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(t1.valid());
        TEST_ASSERT(t2.valid());
    }

    test_section("affine");
    {
        constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).affine();
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(t1.affine());
        TEST_ASSERT_FALSE(t2.affine());
        TEST_ASSERT(nnm::Transform3f().affine());
    }

    test_section("basis");
    {
        nnm::Basis3f expected({ { 1.0f, 2.0f, 3.0f }, { -0.5f, 2.0f, 3.0f }, { 0.0f, 0.0f, 2.0f } });
        constexpr auto result = t2.basis();
        TEST_ASSERT(result == expected);
    }

    test_section("translation");
    {
        constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).translation();
        TEST_ASSERT(result == nnm::Vector3(0.0f, 0.0f, 0.0f));
        TEST_ASSERT(t1.translation() == nnm::Vector3(1.0f, -2.0f, 3.0f));
        TEST_ASSERT(nnm::Transform3f().translation() == nnm::Vector3f(0.0f, 0.0f, 0.0f));
    }

    test_section("translate");
    {
        constexpr auto t3 = t1.translate({ 3.0f, -1.5f, 1.0f });
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { -0.5f, 2.0f, 3.0f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 4.0f, -3.5f, 4.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("translate_local");
    {
        constexpr auto t3 = t1.translate_local({ 3.0f, -1.5f, 1.0f });
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { -0.5f, 2.0f, 3.0f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 4.75f, 1.0f, 9.5f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("rotate_axis_angle");
    {
        auto t3 = t1.rotate_axis_angle({ 0.0f, 0.0f, 1.0f }, -nnm::pi<float>() / 9.0f);
        nnm::Matrix4f expected { { 1.62373f, 1.53737f, 3.0f, 0.0f },
                                 { 0.214194f, 2.0504f, 3.0f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 0.255652f, -2.22141f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("rotate_axis_angle_local");
    {
        auto t3 = t1.rotate_axis_angle_local({ 0.0f, 0.0f, 1.0f }, -nnm::pi<float>() / 9.0f);
        nnm::Matrix4f expected { { 1.1107f, 1.19534f, 1.79302f, 0.0f },
                                 { -0.127826f, 2.56343f, 3.84514f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
        constexpr nnm::Transform3f expected(
            { { 1.22071f, 1.26807f, 3.3018f, 4.0f },
              { -0.27643f, 1.30008f, 3.38871f, -3.0f },
              { 0.103675f, -0.440651f, 1.9481f, 0.0f },
              { 1.0865f, -2.6327f, 2.4266f, 1.0f } });
        constexpr auto result = t2.rotate_quaternion(q);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("rotate_quaternion_local");
    {
        constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
        constexpr nnm::Transform3f expected(
            { { 1.00876f, 1.95351f, 2.81437f, 4.05638f },
              { -0.454045f, 2.01749f, 3.46383f, -2.79137f },
              { 0.162f, -0.336976f, 1.44263f, 0.868326f },
              { 1.0f, -2.0f, 3.0f, 1.0f } });
        constexpr auto result = t2.rotate_quaternion_local(q);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("scale");
    {
        constexpr auto t3 = t1.scale({ 0.2f, -2.1f, 1.2f });
        nnm::Matrix4f expected { { 0.2f, -4.2f, 3.6f, 0.0f },
                                 { -0.1f, -4.2f, 3.6f, 0.0f },
                                 { 0.0f, 0.0f, 2.4f, 0.0f },
                                 { 0.2f, 4.2f, 3.6f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("scale_local");
    {
        constexpr auto t3 = t1.scale_local({ 0.2f, -2.1f, 1.2f });
        nnm::Matrix4f expected { { 0.2f, 0.4f, 0.6f, 0.0f },
                                 { 1.05f, -4.2f, -6.3f, 0.0f },
                                 { 0.0f, 0.0f, 2.4f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_x");
    {
        constexpr auto t3 = t1.shear_x(0.2f, -1.3f);
        nnm::Matrix4f expected { { 1.0f, 2.2f, 1.7f, 0.0f },
                                 { -0.5f, 1.9f, 3.65f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 1.0f, -1.8f, 1.7f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_x_local");
    {
        constexpr auto t3 = t1.shear_x_local(0.2f, -1.3f);
        nnm::Matrix4f expected { { 0.9f, 2.4f, 1.0f, 0.0f },
                                 { -0.5f, 2.0f, 3.0f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_y");
    {
        constexpr auto t3 = t1.shear_y(1.1f, -0.4f);
        nnm::Matrix4f expected { { 3.2f, 2.0f, 2.2f, 0.0f },
                                 { 1.7f, 2.0f, 2.2f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { -1.2f, -2.0f, 3.8f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_y_local");
    {
        constexpr auto t3 = t1.shear_y_local(1.1f, -0.4f);
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { 0.6f, 4.2f, 5.5f, 0.0f },
                                 { 0.0f, 0.0f, 2.0f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_z");
    {
        constexpr auto t3 = t1.shear_z(-1.25f, 0.45f);
        nnm::Matrix4f expected { { -2.75f, 3.35f, 3.0f, 0.0f },
                                 { -4.25f, 3.35f, 3.0f, 0.0f },
                                 { -2.5f, 0.9f, 2.0f, 0.0f },
                                 { -2.75f, -0.65f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("shear_z_local");
    {
        constexpr auto t3 = t1.shear_z_local(-1.25f, 0.45f);
        nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                 { -0.5f, 2.0f, 3.0f, 0.0f },
                                 { -1.475f, -1.6f, -0.4f, 0.0f },
                                 { 1.0f, -2.0f, 3.0f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("transform");
    {
        constexpr auto t3 = t1.transform(
            nnm::Transform3f(
                { { 4.0f, 3.0f, 4.0f, 0.0f },
                  { 2.0f, -1.0f, -2.0f, 0.0f },
                  { 0.0f, 2.0f, -3.5f, 0.0f },
                  { 10.0f, -5.5f, 25.0f, 1.0f } }));
        nnm::Matrix4f expected { { 8.0f, 7.0f, -10.5f, 0.0f },
                                 { 2.0f, 2.5f, -16.5f, 0.0f },
                                 { 0.0f, 4.0f, -7.0f, 0.0f },
                                 { 10.0f, 5.5f, 22.5f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("transform_local");
    {
        constexpr auto t3 = t1.transform_local(
            nnm::Transform3f(
                { { 4.0f, 3.0f, 4.0f, 0.0f },
                  { 2.0f, -1.0f, -2.0f, 0.0f },
                  { 0.0f, 2.0f, -3.5f, 0.0f },
                  { 10.0f, -5.5f, 25.0f, 1.0f } }));
        nnm::Matrix4f expected { { 2.5f, 14.0f, 29.0f, 0.0f },
                                 { 2.5f, 2.0f, -1.0f, 0.0f },
                                 { -1.0f, 4.0f, -1.0f, 0.0f },
                                 { 13.75f, 7.0f, 66.5f, 1.0f } };
        TEST_ASSERT(t3.matrix.approx_equal(expected));
    }

    test_section("approx_equal");
    {
        constexpr auto t3 = nnm::Transform3f(
            { { 1.0000001f, 2.0f, 3.0000001f, 0.0f },
              { -0.5f, 1.999999f, 3.0f, -0.0000001f },
              { 0.0f, 0.0f, 2.0f, 0.0f },
              { 1.0f, -1.999999f, 3.0f, 0.999999f } });
        constexpr auto result = t1.approx_equal(t3);
        TEST_ASSERT(result);
    }

    test_section("at");
    {
        constexpr auto result = t1.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(t1.at(1, 2) == 3.0f);
        TEST_ASSERT(t1.at(3, 3) == 1.0f);
        TEST_ASSERT(t1.at(1) == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
    }

    test_section("operator[]");
    {
        constexpr auto result = t1[1];
        TEST_ASSERT(result == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = t1 == t1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t1 == t2);
    }

    test_section("operator!=");
    {
        constexpr auto result = t1 != t2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t1 != t1);
    }

    test_section("operator<");
    {
        constexpr auto result = t1 < t2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t2 < t1);
    }
}