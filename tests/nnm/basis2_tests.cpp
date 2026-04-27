#include "tests.hpp"

void basis2_tests()
{
    test_case("Basis2");
    test_section("Basis()");
    {
        constexpr nnm::Basis2f b;
        TEST_ASSERT(b.matrix == nnm::Matrix2f::identity());
    }

    test_section("Basis2(const Basis2<Other>&)");
    {
        constexpr nnm::Basis2d b1({ { 1.0, -2.0 }, { 3.0, -4.5 } });
        constexpr nnm::Basis2f b2(b1);
        TEST_ASSERT(b2.matrix.columns[0] == nnm::Vector2f(1.0f, -2.0f));
        TEST_ASSERT(b2.matrix.columns[1] == nnm::Vector2f(3.0f, -4.5f));
    }

    test_section("Basis2(const Matrix2&)");
    {
        constexpr auto m1 = nnm::Matrix2f::identity();
        constexpr auto b1 = nnm::Basis2(m1);
        TEST_ASSERT(b1 == nnm::Basis2f());
        TEST_ASSERT(b1.matrix == nnm::Matrix2f::identity());
    }

    test_section("from_rotation");
    {
        const auto b1 = nnm::Basis2f::from_rotation(0.0f);
        TEST_ASSERT(b1.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
        const auto b2 = nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f);
        TEST_ASSERT(b2.matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
        const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
        TEST_ASSERT(b3.matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
        const auto b4 = nnm::Basis2f::from_rotation(2.0f * nnm::pi<float>());
        TEST_ASSERT(b4.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
    }

    test_section("from_scale");
    {
        constexpr auto b1 = nnm::Basis2f::from_scale({ 2.0f, -3.0f });
        TEST_ASSERT(b1.matrix == nnm::Matrix2f({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
    }

    test_section("from_shear_x");
    {
        constexpr auto b = nnm::Basis2f::from_shear_x(0.5f);
        TEST_ASSERT(b.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.5f, 1.0f } }));
    }

    test_section("from_shear_y");
    {
        constexpr auto b = nnm::Basis2f::from_shear_y(-0.5f);
        TEST_ASSERT(b.matrix.approx_equal({ { 1.0f, -0.5f }, { 0.0f, 1.0f } }))
    ;}

    test_section("trace");
    {
        constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b.trace();
        TEST_ASSERT(result == b.matrix.trace());
    }

    test_section("determinant");
    {
        constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b.determinant();
        TEST_ASSERT(result == b.matrix.determinant());
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b.unchecked_inverse();
        TEST_ASSERT(result.matrix == b.matrix.unchecked_inverse());
    }

    test_section("inverse");
    {
        constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto inv = b.inverse();
        TEST_ASSERT(inv.has_value() && inv.value().matrix == b.matrix.inverse().value());
        TEST_ASSERT_FALSE(nnm::Basis2(nnm::Matrix2f::zero()).inverse().has_value());
    }

    test_section("valid");
    {
        constexpr nnm::Basis2f b1;
        constexpr auto b2 = nnm::Basis2(nnm::Matrix2f::zero());
        constexpr auto b3 = nnm::Basis2f({ { 1.0f, -2.0f }, { 2.0f, -4.0f } });
        constexpr auto result = b1.valid();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(b2.valid());
        TEST_ASSERT_FALSE(b3.valid());
    }

    test_section("rotate");
    {
        constexpr nnm::Basis2f b1;
        TEST_ASSERT(b1.rotate(0.0f).approx_equal(b1));
        TEST_ASSERT(b1.rotate(nnm::pi<float>() / 2.0f).matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
        TEST_ASSERT(b1.rotate(-nnm::pi<float>() / 2.0f).matrix.approx_equal({ { 0.0f, -1.0f }, { 1.0f, 0.0f } }));
        TEST_ASSERT(b1.rotate(2.0f * nnm::pi<float>()).approx_equal(b1));
        constexpr auto b2 = nnm::Basis2f::from_scale({ 2.0f, 0.5f });
        const auto b2_rotated = b2.rotate(nnm::pi<float>() / 4.0f);
        TEST_ASSERT(b2_rotated.matrix.approx_equal({ { 1.41421f, 1.41421f }, { -0.353553f, 0.353553f } }));
    }

    test_section("rotate_local");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 1.96575f, -3.24747f }, { -2.47706f, 3.07473f } });
        TEST_ASSERT(b1.rotate_local(-nnm::pi<float>() / 9.0f).approx_equal(expected));
    }

    test_section("scale");
    {
        constexpr nnm::Basis2f b1;
        constexpr auto result = b1.scale({ 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result.valid());
        TEST_ASSERT(b1.scale({ 0.0f, 0.0f }).matrix.approx_equal(nnm::Matrix2f::zero()));
        TEST_ASSERT(b1.scale({ 2.0f, 2.0f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 2.0f } }));
        TEST_ASSERT(b1.scale({ 2.0f, 0.5f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 0.5f } }));
        TEST_ASSERT(b1.scale({ -1.0f, -1.0f }).matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
    }

    test_section("scale_local");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 2.0f, -4.0f }, { 1.5f, -2.0f } });
        constexpr auto result = b1.scale_local({ 2.0f, -0.5f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_x");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 0.0f, -2.0f }, { -1.0f, 4.0f } });
        constexpr auto result = b1.shear_x(0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_x_local");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 1.0f, -2.0f }, { -2.5f, 3.0f } });
        constexpr auto result = b1.shear_x_local(0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 1.0f, -2.5f }, { -3.0f, 5.5f } });
        constexpr auto result = b1.shear_y(-0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y_local");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f expected({ { 2.5f, -4.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b1.shear_y_local(-0.5f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("transform");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
        constexpr nnm::Basis2f expected({ { 7.75f, 17.5f }, { -16.25f, -55.0f } });
        constexpr auto result = b1.transform(b2);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("transform_local");
    {
        constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr nnm::Basis2f b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
        constexpr nnm::Basis2f expected({ { -59.25f, 78.5f }, { -7.25f, 12.0f } });
        constexpr auto result = b1.transform_local(b2);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("approx_equal");
    {
        constexpr nnm::Basis2f b1;
        constexpr auto result
            = b1.approx_equal(nnm::Basis2f({ { 1.0000000f, 0.000000001f }, { -0.000000001f, 0.9999999f } }));
        TEST_ASSERT(result);
        const auto b2 = nnm::Basis2f::from_rotation(nnm::pi<float>());
        TEST_ASSERT_FALSE(b2.approx_equal(nnm::Basis2f()));
    }

    test_section("at");
    {
        constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b1.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(b1.at(0, 1) == -2.0f);
        TEST_ASSERT(b1.at(1, 0) == -3.0f);
        TEST_ASSERT(b1.at(1, 1) == 4.0f);
        TEST_ASSERT(b1.at(0, 0) == 1.0f);
        TEST_ASSERT(b1.at(0, 1) == -2.0f);
        TEST_ASSERT(b1.at(1, 0) == -3.0f);
    }

    test_section("operator[]");
    {
        constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto result = b1[0];
        TEST_ASSERT(result == nnm::Vector2(1.0f, -2.0f));
        TEST_ASSERT(b1[1] == nnm::Vector2(-3.0f, 4.0f));
    }

    test_section("operator==");
    {
        constexpr nnm::Basis2f b1;
        constexpr nnm::Basis2f b2;
        const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
        constexpr auto result = b1 == b2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(b1 == b3);
    }

    test_section("operator!=");
    {
        constexpr nnm::Basis2f b1;
        constexpr nnm::Basis2f b2;
        const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
        constexpr auto result = b1 != b2;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(b1 != b3);
    }

    test_section("operator<");
    {
        constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
        constexpr auto b2 = nnm::Basis2f({ { -4.0f, 3.0f }, { 2.0f, -1.0f } });
        constexpr auto result = b2 < b1;
        TEST_ASSERT(result);
    }
}