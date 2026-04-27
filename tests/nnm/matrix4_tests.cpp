#include "tests.hpp"

void matrix4_tests()
{
    test_case("Matrix4");
    test_section("Matrix4()");
    {
        constexpr nnm::Matrix4f m1;
        TEST_ASSERT(m1.columns[0] == nnm::Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
        TEST_ASSERT(m1.columns[1] == nnm::Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
        TEST_ASSERT(m1.columns[2] == nnm::Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
        TEST_ASSERT(m1.columns[3] == nnm::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
    }

    test_section("Matrix4(const Matrix4<Other>&)");
    {
        constexpr nnm::Matrix4d m1(
            { 1.0, 2.0, 3.0, 4.0 }, { -0.5, 0.75, 0.6, 0.1 }, { -100.0, -88.0, 28.0, 0.0 }, { 1.0, 29.0, -89.0, 67.0 });
        constexpr nnm::Matrix4f m2(m1);
        TEST_ASSERT(m2.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
        TEST_ASSERT(m2.columns[1] == nnm::Vector4f(-0.5f, 0.75f, 0.6f, 0.1f));
        TEST_ASSERT(m2.columns[2] == nnm::Vector4f(-100.0f, -88.0f, 28.0f, 0.0f));
        TEST_ASSERT(m2.columns[3] == nnm::Vector4f(1.0f, 29.0f, -89.0f, 67.0f));
    }

    test_section(
        "Matrix4(const Vector4&, const Vector4&, const Vector4&, "
        "const Vector4&)");
    {
        constexpr nnm::Matrix4f m3 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                     { -1.0f, -2.0f, -3.0f, -4.0f },
                                     { 4.0f, 3.0f, 2.0f, 1.0f },
                                     { -4.0f, -3.0f, -2.0f, -1.0f } };
        TEST_ASSERT(m3.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
        TEST_ASSERT(m3.columns[1] == nnm::Vector4f(-1.0f, -2.0f, -3.0f, -4.0f));
        TEST_ASSERT(m3.columns[2] == nnm::Vector4f(4.0f, 3.0f, 2.0f, 1.0f));
        TEST_ASSERT(m3.columns[3] == nnm::Vector4f(-4.0f, -3.0f, -2.0f, -1.0f));
    }

    test_section(
        "Matrix4(float, float, float, float, float, float, float, "
        "float, float, float, float, float, "
        "float, float, float, float)");
    {
        constexpr nnm::Matrix4 m2 { 1.0f, 2.0f, 3.0f, 4.0f, -1.0f, -2.0f, -3.0f, -4.0f,
                                    4.0f, 3.0f, 2.0f, 1.0f, -4.0f, -3.0f, -2.0f, -1.0f };
        TEST_ASSERT(m2.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
        TEST_ASSERT(m2.columns[1] == nnm::Vector4f(-1.0f, -2.0f, -3.0f, -4.0f));
        TEST_ASSERT(m2.columns[2] == nnm::Vector4f(4.0f, 3.0f, 2.0f, 1.0f));
        TEST_ASSERT(m2.columns[3] == nnm::Vector4f(-4.0f, -3.0f, -2.0f, -1.0f));
    }

    test_section("all");
    {
        constexpr auto m1 = nnm::Matrix4f::all(3.0f);
        TEST_ASSERT(m1.columns[0] == nnm::Vector4f::all(3.0f));
        TEST_ASSERT(m1.columns[1] == nnm::Vector4f::all(3.0f));
        TEST_ASSERT(m1.columns[2] == nnm::Vector4f::all(3.0f));
        TEST_ASSERT(m1.columns[3] == nnm::Vector4f::all(3.0f));
    }

    test_section("zero");
    {
        constexpr auto m2 = nnm::Matrix4f::zero();
        TEST_ASSERT(m2.columns[0] == nnm::Vector4f::zero());
        TEST_ASSERT(m2.columns[1] == nnm::Vector4f::zero());
        TEST_ASSERT(m2.columns[2] == nnm::Vector4f::zero());
        TEST_ASSERT(m2.columns[3] == nnm::Vector4f::zero());
    }

    test_section("one");
    {
        constexpr auto m3 = nnm::Matrix4f::one();
        TEST_ASSERT(m3.columns[0] == nnm::Vector4f::one());
        TEST_ASSERT(m3.columns[1] == nnm::Vector4f::one());
        TEST_ASSERT(m3.columns[2] == nnm::Vector4f::one());
        TEST_ASSERT(m3.columns[3] == nnm::Vector4f::one());
    }

    test_section("identity");
    {
        constexpr auto m4 = nnm::Matrix4f::identity();
        TEST_ASSERT(m4.columns[0] == nnm::Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
        TEST_ASSERT(m4.columns[1] == nnm::Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
        TEST_ASSERT(m4.columns[2] == nnm::Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
        TEST_ASSERT(m4.columns[3] == nnm::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
    }

    constexpr nnm::Matrix4f m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                 { -1.0f, -3.0f, -2.0f, -4.0f },
                                 { 3.0f, 2.0f, -1.0f, -4.0f },
                                 { -4.0f, 1.0f, -3.0f, 0.0f } };

    test_section("trace");
    {
        constexpr auto result = m1.trace();
        TEST_ASSERT(result == -3.0f);
    }

    test_section("determinant");
    {
        constexpr auto result = m1.determinant();
        TEST_ASSERT(nnm::approx_equal(result, -64.0f));
    }

    test_section("minor_matrix_at");
    {
        constexpr nnm::Matrix3 m2 = m1.minor_matrix_at(0, 0);
        TEST_ASSERT(m2 == nnm::Matrix3f({ -3.0f, -2.0f, -4.0f }, { 2.0f, -1.0f, -4.0f }, { 1.0f, -3.0f, 0.0f }));

        constexpr nnm::Matrix3 m3 = m1.minor_matrix_at(1, 2);
        TEST_ASSERT(m3 == nnm::Matrix3f({ 1.0f, 2.0f, 4.0f }, { 3.0f, 2.0f, -4.0f }, { -4.0f, 1.0f, 0.0f }));
    }

    test_section("minor_at");
    {
        constexpr auto result = m1.minor_at(0, 0);
        TEST_ASSERT(nnm::approx_equal(result, 64.0f));
        TEST_ASSERT(nnm::approx_equal(m1.minor_at(1, 2), 80.0f));
    }

    test_section("minor");
    {
        nnm::Matrix4f expected(
            { 64.0f, 32.0f, -96.0f, -56.0f },
            { -56.0f, -16.0f, 80.0f, 54.0f },
            { 8.0f, 16.0f, -16.0f, -18.0f },
            { -24.0f, -16.0f, 16.0f, 14.0f });
        constexpr auto result = m1.minor();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("cofactor_at");
    {
        constexpr auto result = m1.cofactor_at(0, 0);
        TEST_ASSERT(nnm::approx_equal(result, 64.0f));
        TEST_ASSERT(nnm::approx_equal(m1.cofactor_at(2, 1), -16.0f));
    }

    test_section("cofactor");
    {
        constexpr nnm::Matrix4f expected { { 64.0f, -32.0f, -96.0f, 56.0f },
                                           { 56.0f, -16.0f, -80.0f, 54.0f },
                                           { 8.0f, -16.0f, -16.0f, 18.0f },
                                           { 24.0f, -16.0f, -16.0f, 14.0f } };
        constexpr auto result = m1.cofactor();
        TEST_ASSERT(result.approx_equal(expected))
    }

    test_section("transpose");
    {
        constexpr nnm::Matrix4f expected { { 1.0f, -1.0f, 3.0f, -4.0f },
                                           { 2.0f, -3.0f, 2.0f, 1.0f },
                                           { 3.0f, -2.0f, -1.0f, -3.0f },
                                           { 4.0f, -4.0f, -4.0f, 0.0f } };
        constexpr auto result = m1.transpose();
        TEST_ASSERT(result == expected);
    }

    test_section("adjugate");
    {
        constexpr nnm::Matrix4f expected { { 64.0f, 56.0f, 8.0f, 24.0f },
                                           { -32.0f, -16.0f, -16.0f, -16.0f },
                                           { -96.0f, -80.0f, -16.0f, -16.0f },
                                           { 56.0f, 54.0f, 18.0f, 14.0f } };
        constexpr auto result = m1.adjugate();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Matrix4f expected { { -1.0f, -0.875f, -0.125f, -0.375f },
                                           { 0.5f, 0.25f, 0.25f, 0.25f },
                                           { 1.5f, 1.25f, 0.25f, 0.25f },
                                           { -0.875f, -0.84375f, -0.28125f, -0.21875f } };
        constexpr auto result = m1.unchecked_inverse();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Matrix4f expected { { -1.0f, -0.875f, -0.125f, -0.375f },
                                           { 0.5f, 0.25f, 0.25f, 0.25f },
                                           { 1.5f, 1.25f, 0.25f, 0.25f },
                                           { -0.875f, -0.84375f, -0.28125f, -0.21875f } };
        constexpr auto result = m1.inverse();
        TEST_ASSERT(result.has_value() && result.value().approx_equal(expected));
        TEST_ASSERT_FALSE(nnm::Matrix4f::zero().inverse().has_value());
    }

    test_section("approx_equal");
    {
        constexpr nnm::Matrix4f m2 { { 1.000001f, 2.0f, 3.0f, 4.000001f },
                                     { -0.999999f, -3.0f, -2.0f, -4.0f },
                                     { 3.0f, 1.999999f, -1.0f, -4.0f },
                                     { -4.0f, 1.0f, -2.999999f, 0.0f } };
        constexpr auto result = m1.approx_equal(m2);
        TEST_ASSERT(result);
    }

    test_section("approx_zero");
    {
        constexpr nnm::Matrix4f m2 { { 0.000001f, 0.0f, 0.0f, 0.0f },
                                     { -0.000001f, -0.0f, -0.0f, 0.0f },
                                     { 0.0f, 0.000001f, 0.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 0.0f } };
        constexpr auto result = m2.approx_zero();
        TEST_ASSERT(result);
    }

    test_section("at");
    {
        constexpr auto result = m1.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(m1.at(1, 2) == -2.0f);
        TEST_ASSERT(m1.at(3, 3) == 0.0f);
        TEST_ASSERT(m1.at(0) == nnm::Vector4(1.0f, 2.0f, 3.0f, 4.0f))
        TEST_ASSERT(m1.at(2) == nnm::Vector4(3.0f, 2.0f, -1.0f, -4.0f))
    }

    test_section("begin");
    {
        TEST_ASSERT(m1.begin() == &m1.columns[0].x);
    }

    test_section("end");
    {
        TEST_ASSERT(m1.end() == &m1.columns[3].w + 1);
    }

    test_section("operator[]");
    {
        constexpr auto result = m1[0][0];
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(m1[1][2] == -2.0f);
        TEST_ASSERT(m1[3][3] == 0.0f);
    }

    constexpr nnm::Matrix4f m2 { { 1.5f, 3.0f, -3.0f, 4.0f },
                                 { -1.0f, 100.0f, -2.0f, -4.0f },
                                 { 0.0f, 29.0f, -129.0f, -4293.0f },
                                 { -4.0f, 100.3f, -3.0f, 0.0f } };

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = m1 == m1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m1 == m2);
        TEST_ASSERT(m2 == m2);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = m1 != m1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(m1 != m2);
        TEST_ASSERT_FALSE(m2 != m2);
    }

    test_section("operator+");
    {
        nnm::Matrix4f expected(
            { 2.5f, 5.0f, 0.0f, 8.0f },
            { -2.0f, 97.0f, -4.0f, -8.0f },
            { 3.0f, 31.0f, -130.0f, -4297.0f },
            { -8.0f, 101.3f, -6.0f, 0.0f });
        constexpr auto result = m1 + m2;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator+=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy += m2;
            return m1_copy;
        }();
        nnm::Matrix4f expected(
            { 2.5f, 5.0f, 0.0f, 8.0f },
            { -2.0f, 97.0f, -4.0f, -8.0f },
            { 3.0f, 31.0f, -130.0f, -4297.0f },
            { -8.0f, 101.3f, -6.0f, 0.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator-");
    {
        nnm::Matrix4f expected(
            { -0.5f, -1.0f, 6.0f, 0.0f },
            { 0.0f, -103.0f, 0.0f, 0.0f },
            { 3.0f, -27.0f, 128.0f, 4289.0f },
            { 0.0f, -99.3f, 0.0f, 0.0f });
        constexpr auto result = m1 - m2;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator-=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy -= m2;
            return m1_copy;
        }();
        nnm::Matrix4f expected(
            { -0.5f, -1.0f, 6.0f, 0.0f },
            { 0.0f, -103.0f, 0.0f, 0.0f },
            { 3.0f, -27.0f, 128.0f, 4289.0f },
            { 0.0f, -99.3f, 0.0f, 0.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(const Matrix4&)");
    {
        constexpr nnm::Matrix4f expected { { -26.5f, -8.0f, -10.5f, 6.0f },
                                           { -91.0f, -310.0f, -189.0f, -396.0f },
                                           { 16756.0f, -4638.0f, 12950.0f, 400.0f },
                                           { -113.3f, -314.9f, -209.6f, -405.2f } };
        constexpr auto result = m1 * m2;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*=(const Matrix4&)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= m2;
            return m1_copy;
        }();
        constexpr nnm::Matrix4f expected { { -26.5f, -8.0f, -10.5f, 6.0f },
                                           { -91.0f, -310.0f, -189.0f, -396.0f },
                                           { 16756.0f, -4638.0f, 12950.0f, 400.0f },
                                           { -113.3f, -314.9f, -209.6f, -405.2f } };
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(const Vector4&)");
    {
        constexpr nnm::Vector4 v { 1.0f, -2.0f, 3.0f, -4.0f };
        constexpr nnm::Vector4 expected { 28.0f, 10.0f, 16.0f, 0.0f };
        constexpr auto result = m1 * v;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(float)");
    {
        constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                           { 2.0f, 6.0f, 4.0f, 8.0f },
                                           { -6.0f, -4.0f, 2.0f, 8.0f },
                                           { 8.0f, -2.0f, 6.0f, 0.0f } };
        constexpr auto result = m1 * -2.0f;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(float, const Matrix4&)");
    {
        constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                           { 2.0f, 6.0f, 4.0f, 8.0f },
                                           { -6.0f, -4.0f, 2.0f, 8.0f },
                                           { 8.0f, -2.0f, 6.0f, 0.0f } };
        constexpr auto result = -2.0f * m1;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= -2.0f;
            return m1_copy;
        }();
        constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                           { 2.0f, 6.0f, 4.0f, 8.0f },
                                           { -6.0f, -4.0f, 2.0f, 8.0f },
                                           { 8.0f, -2.0f, 6.0f, 0.0f } };
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator/(float)");
    {
        constexpr nnm::Matrix4f expected { { -0.25, -0.5f, -0.75f, -1.0f },
                                           { 0.25f, 0.75f, 0.5f, 1.0f },
                                           { -0.75f, -0.5f, 0.25f, 1.0f },
                                           { 1.0f, -0.25f, 0.75f, 0.0f } };
        constexpr auto result = m1 / -4.0f;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator(float, const Matrix4&)");
    {
        constexpr nnm::Matrix4f m3 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                     { -1.0f, -3.0f, -2.0f, -4.0f },
                                     { 3.0f, 2.0f, -1.0f, -4.0f },
                                     { -4.0f, 1.0f, -3.0f, 1.5f } };
        constexpr nnm::Matrix4f expected { { -4.0f, -2.0f, -1.333333f, -1.0f },
                                           { 4.0f, 1.333333f, 2.0f, 1.0f },
                                           { -1.333333f, -2.0f, 4.0f, 1.0f },
                                           { 1.0f, -4.0f, 1.33333f, -2.6666666f } };
        constexpr auto result = -4.0f / m3;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator/=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy /= -4.0f;
            return m1_copy;
        }();
        constexpr nnm::Matrix4f expected { { -0.25, -0.5f, -0.75f, -1.0f },
                                           { 0.25f, 0.75f, 0.5f, 1.0f },
                                           { -0.75f, -0.5f, 0.25f, 1.0f },
                                           { 1.0f, -0.25f, 0.75f, 0.0f } };
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator<");
    {
        constexpr auto result = m1 < m2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m2 < m1);
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(nnm::Matrix4f::zero());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(static_cast<bool>(nnm::Matrix4f::identity()));
        TEST_ASSERT(static_cast<bool>(m1));
    }
}