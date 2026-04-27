#include "tests.hpp"

void transform2_tests()
{
    test_case("Transform2");
    test_section("Transform2()");
    {
        constexpr nnm::Transform2f default_transform;
        TEST_ASSERT(default_transform.matrix == nnm::Matrix3f::identity());
    }

    test_section("Transform2(const Transform2<Other>&)");
    {
        constexpr nnm::Transform2d t1({ { 1.0, 2.0, 3.0 }, { -0.5, -0.75, 0.1 }, { 4.0, 28.0, 100.0 } });
        constexpr nnm::Transform2f t2(t1);
        TEST_ASSERT(t2.matrix.columns[0] == nnm::Vector3f(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(t2.matrix.columns[1] == nnm::Vector3f(-0.5f, -0.75f, 0.1f));
        TEST_ASSERT(t2.matrix.columns[2] == nnm::Vector3f(4.0f, 28.0f, 100.0f));
    }

    test_section("Transform2(const Matrix3&)");
    {
        constexpr nnm::Transform2 transform_matrix(nnm::Matrix3f::all(3.0f));
        TEST_ASSERT(transform_matrix.matrix == nnm::Matrix3f::all(3.0f));
    }

    test_section("from_basis_translation");
    {
        constexpr nnm::Basis2f basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
        constexpr nnm::Vector2 pos(-1.0f, 2.0f);
        constexpr auto transform_basis_pos = nnm::Transform2f::from_basis_translation(basis, pos);
        constexpr nnm::Matrix3f expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
        TEST_ASSERT(transform_basis_pos.matrix.approx_equal(expected));
    }

    test_section("from_basis");
    {
        constexpr nnm::Basis2f basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
        constexpr nnm::Matrix3f expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
        constexpr auto transform_basis = nnm::Transform2f::from_basis(basis);
        TEST_ASSERT(transform_basis.matrix.approx_equal(expected));
    }

    test_section("from_translation");
    {
        constexpr nnm::Vector2 pos(-1.0f, 2.0f);
        constexpr auto transform_pos = nnm::Transform2f::from_translation(pos);
        constexpr nnm::Matrix3f expected({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
        TEST_ASSERT(transform_pos.matrix.approx_equal(expected));
    }

    test_section("from_rotation");
    {
        const auto transform_rot = nnm::Transform2f::from_rotation(nnm::pi<float>() / 2.0f);
        constexpr nnm::Matrix3f expected({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
        TEST_ASSERT(transform_rot.matrix.approx_equal(expected));
    }

    test_section("from_scale");
    {
        constexpr auto transform_scale = nnm::Transform2f::from_scale({ -2.0f, 3.0f });
        constexpr nnm::Matrix3f expected({ -2.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
        TEST_ASSERT(transform_scale.matrix.approx_equal(expected));
    }

    test_section("from_shear_x");
    {
        constexpr auto t = nnm::Transform2f::from_shear_x(0.5f);
        constexpr nnm::Transform2f expected({ { 1.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("from_shear_y");
    {
        constexpr auto t = nnm::Transform2f::from_shear_y(-0.5f);
        constexpr nnm::Transform2f expected({ { 1.0f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
        TEST_ASSERT(t.approx_equal(expected));
    }

    test_section("trace");
    {
        constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr auto result = t.trace();
        TEST_ASSERT(nnm::approx_equal(result, 12.0f));
    }

    test_section("determinant");
    {
        constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr auto result = t.determinant();
        TEST_ASSERT(nnm::approx_equal(result, -54.925f));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Transform2f expected(
            { { -0.254893f, -0.0345926f, 0.819299f },
              { -0.559854f, -0.00455166f, 0.37096f },
              { 0.270369f, 0.0509786f, -0.154756f } });
        constexpr auto result = t.unchecked_inverse();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
        constexpr nnm::Transform2f expected(
            { { -0.254893f, -0.0345926f, 0.819299f },
              { -0.559854f, -0.00455166f, 0.37096f },
              { 0.270369f, 0.0509786f, -0.154756f } });
        constexpr auto result = t.inverse();
        TEST_ASSERT(result.has_value() && result.value().approx_equal(expected));
        TEST_ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).inverse().has_value());
    }

    test_section("valid");
    {
        constexpr auto result = nnm::Transform2(nnm::Matrix3f::identity()).valid();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).valid());
    }

    test_section("affine");
    {
        constexpr auto result = nnm::Transform2(nnm::Matrix3f::identity()).affine();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).affine());
    }

    constexpr nnm::Transform2f t1({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f } });

    test_section("basis");
    {
        constexpr auto result = t1.basis();
        TEST_ASSERT(result == nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } }));
    }

    test_section("translation");
    {
        constexpr auto result = t1.translation();
        TEST_ASSERT(result == nnm::Vector2(-1.0f, 2.0f));
    }

    test_section("translate");
    {
        constexpr nnm::Transform2f expected({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 0.0f, -0.5f, 1.0f } });
        constexpr nnm::Transform2f t2 = t1.translate({ 1.0f, -2.5f });
        TEST_ASSERT(t2.approx_equal(expected));
    }

    test_section("translate_local");
    {
        constexpr nnm::Transform2f expected({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 7.5f, -10.0f, 1.0f } });
        constexpr nnm::Transform2f t2 = t1.translate_local({ 1.0f, -2.5f });
        TEST_ASSERT(t2.approx_equal(expected));
    }

    test_section("rotate");
    {
        constexpr auto t = nnm::Transform2f::from_basis_translation(nnm::Basis2f(), { 1.0f, -2.0f });
        const auto t_rotated = t.rotate(nnm::pi<float>() / 2.0f);
        const auto t_expected = nnm::Transform2f::from_basis_translation(
            nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f), { 2.0f, 1.0f });
        TEST_ASSERT(t_rotated.approx_equal(t_expected));
    }

    test_section("rotate_local");
    {
        constexpr auto t = nnm::Transform2f::from_basis_translation(nnm::Basis2f(), { 1.0f, -2.0f });
        const auto t_rotated = t.rotate_local(nnm::pi<float>() / 2.0f);
        const auto t_expected = nnm::Transform2f::from_basis_translation(
            nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f), { 1.0f, -2.0f });
        TEST_ASSERT(t_rotated.approx_equal(t_expected));
    }

    constexpr nnm::Transform2f t2 { { { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, -2.0f, 1.0f } } };
    constexpr nnm::Transform2f t3 { { { -1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { -3.0f, 4.0f, 1.0f } } };

    test_section("scale");
    {
        constexpr auto t_scaled = t2.scale({ 2.0f, -3.0f });
        constexpr auto t_expected
            = nnm::Transform2f::from_basis_translation(t2.basis().scale({ 2.0f, -3.0f }), { 2.0f, 6.0f });
        TEST_ASSERT(t_scaled.approx_equal(t_expected));
    }

    test_section("scale_local");
    {
        constexpr auto t_scaled = t2.scale_local({ 2.0f, -3.0f });
        constexpr auto t_expected
            = nnm::Transform2f::from_basis_translation(t2.basis().scale_local({ 2.0f, -3.0f }), { 1.0f, -2.0f });
        TEST_ASSERT(t_scaled.approx_equal(t_expected));
    }

    test_section("shear_x");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
        constexpr nnm::Transform2f expected({ { 0.0f, -2.0f, 3.0f }, { -1.0f, 4.0f, -2.0f }, { 0.0f, 2.0f, 1.0f } });
        constexpr auto result = t4.shear_x(0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_x_local");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
        constexpr nnm::Transform2f expected({ { 1.0f, -2.0f, 3.0f }, { -2.5f, 3.0f, -0.5f }, { -1.0f, 2.0f, 1.0f } });
        constexpr auto result = t4.shear_x_local(0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
        constexpr nnm::Transform2f expected({ { 1.0f, -2.5f, 3.0f }, { -3.0f, 5.5f, -2.0f }, { -1.0f, 2.5f, 1.0f } });
        constexpr auto result = t4.shear_y(-0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y_local");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
        constexpr nnm::Transform2f expected({ { 2.5f, -4.0f, 4.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
        constexpr auto result = t4.shear_y_local(-0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("transform");
    {
        constexpr auto t_transformed = t2.transform(t3);
        const auto t_expected = nnm::Transform2f::from_basis_translation(
            nnm::Basis2f::from_rotation(3.0f * nnm::pi<float>() / 2.0f), { -4.0f, 6.0f });
        TEST_ASSERT(t_transformed.approx_equal(t_expected));
    }

    test_section("transform_local");
    {
        constexpr auto t_transformed = t2.transform_local(t3);
        const auto t_expected = nnm::Transform2f::from_basis_translation(
            nnm::Basis2f::from_rotation(3.0f * nnm::pi<float>() / 2.0f), { -3.0f, -5.0f });
        TEST_ASSERT(t_transformed.approx_equal(t_expected));
    }

    test_section("approx_equal");
    {
        constexpr nnm::Transform2f t(
            { { 0.999999f, 0.0000001f, -0.0000001f }, { 0.0f, 1.00000001f, 0.0f }, { 0.0f, -0.0000001f, 1.0f } });
        constexpr auto result = t.approx_equal(nnm::Transform2f());
        TEST_ASSERT(result);
    }

    test_section("at");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
        constexpr auto result = t4.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(t4.at(1, 2) == -2.0f);
        TEST_ASSERT(t4.at(2, 2) == 1.5f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
        constexpr auto result = t4[0];
        TEST_ASSERT(result == nnm::Vector3(1.0f, -2.0f, 3.0f));
        TEST_ASSERT(t4[1] == nnm::Vector3(-3.0f, 4.0f, -2.0f));
        TEST_ASSERT(t4[2] == nnm::Vector3(-1.0f, 2.0f, 1.5f));
    }

    test_section("operator==");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
        constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
        constexpr nnm::Transform2f t6 = t4;
        constexpr auto result = t4 == t6;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t4 == t5);
    }

    test_section("operator!=");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
        constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
        constexpr nnm::Transform2f t6 = t4;
        constexpr auto result = t4 != t5;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t4 != t6);
    }

    test_section("operator<");
    {
        constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
        constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
        constexpr auto result = t5 < t4;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(t4 < t5);
    }
}