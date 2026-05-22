#include "tests.hpp"

void matrix2_tests()
{
    test_case("Matrix2");
    test_section("Matrix2()");
    {
        constexpr nnm::Matrix2f mat_default;
        TEST_ASSERT(mat_default.columns[0] == nnm::Vector2f(1.0f, 0.0f));
        TEST_ASSERT(mat_default.columns[1] == nnm::Vector2f(0.0f, 1.0f));
    }

    test_section("Matrix2(const Matrix2<Other>&)");
    {
        constexpr nnm::Matrix2d m1({ 1.0, -2.0 }, { 3.0, -4.5 });
        constexpr nnm::Matrix2f m2(m1);
        TEST_ASSERT(m2.columns[0] == nnm::Vector2f(1.0f, -2.0f));
        TEST_ASSERT(m2.columns[1] == nnm::Vector2f(3.0f, -4.5f));
    }

    test_section("Matrix2(const Vector2&, const Vector2&)");
    {
        constexpr nnm::Matrix2f mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        TEST_ASSERT(mat_cols.columns[0] == nnm::Vector2f(1.0f, -2.0f));
        TEST_ASSERT(mat_cols.columns[1] == nnm::Vector2f(-3.0f, 4.0f));
    }

    test_section("Matrix2(float, float, float, float)");
    {
        constexpr nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
        TEST_ASSERT(mat_elements.columns[0] == nnm::Vector2f(1.0f, -2.0f));
        TEST_ASSERT(mat_elements.columns[1] == nnm::Vector2f(-3.0f, 4.0f));
    }

    test_section("all");
    {
        constexpr auto mat_all_three = nnm::Matrix2f::all(3.0f);
        TEST_ASSERT(mat_all_three.columns[0] == nnm::Vector2f(3.0f, 3.0f));
        TEST_ASSERT(mat_all_three.columns[1] == nnm::Vector2f(3.0f, 3.0f));
    }

    test_section("zero");
    {
        constexpr auto mat_zero = nnm::Matrix2f::zero();
        TEST_ASSERT(mat_zero.columns[0] == nnm::Vector2f::zero());
        TEST_ASSERT(mat_zero.columns[1] == nnm::Vector2f::zero());
    }

    test_section("one");
    {
        constexpr auto mat_one = nnm::Matrix2f::one();
        TEST_ASSERT(mat_one.columns[0] == nnm::Vector2f::one());
        TEST_ASSERT(mat_one.columns[1] == nnm::Vector2f::one());
    }

    test_section("identity");
    {
        constexpr auto mat_identity = nnm::Matrix2f::identity();
        TEST_ASSERT(mat_identity.columns[0] == nnm::Vector2f(1.0f, 0.0f));
        TEST_ASSERT(mat_identity.columns[1] == nnm::Vector2f(0.0f, 1.0f));
    }

    test_section("trace");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.trace();
        TEST_ASSERT(nnm::approx_equal(result, 5.0f));
    }

    test_section("determinant");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.determinant();
        TEST_ASSERT(nnm::approx_equal(result, -2.0f));
    }

    test_section("minor_at");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.minor_at(0, 0);
        TEST_ASSERT(result == 4.0f);
        TEST_ASSERT(mat.minor_at(0, 1) == -3.0f);
        TEST_ASSERT(mat.minor_at(1, 0) == -2.0f);
        TEST_ASSERT(mat.minor_at(1, 1) == 1.0f);
    }

    test_section("minor");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr nnm::Matrix2f minor = mat.minor();
        TEST_ASSERT(minor.approx_equal({ { 4.0f, -3.0f }, { -2.0f, 1.0f } }));
    }

    test_section("cofactor_at");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.cofactor_at(0, 0);
        TEST_ASSERT(result == 4.0f);
        TEST_ASSERT(mat.cofactor_at(0, 1) == 3.0f);
        TEST_ASSERT(mat.cofactor_at(1, 0) == 2.0f);
        TEST_ASSERT(mat.cofactor_at(1, 1) == 1.0f);
    }

    test_section("cofactor");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.cofactor();
        TEST_ASSERT(result == nnm::Matrix2f({ 4.0f, 3.0f }, { 2.0f, 1.0f }));
    }

    test_section("transpose");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.transpose();
        TEST_ASSERT(result == nnm::Matrix2f({ 1.0f, -3.0f }, { -2.0f, 4.0f }));
    }

    test_section("adjugate");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.adjugate();
        TEST_ASSERT(result == nnm::Matrix2f({ 4.0f, 2.0f }, { 3.0f, 1.0f }));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.unchecked_inverse();
        TEST_ASSERT(result.approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
    }

    test_section("inverse");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr std::optional<nnm::Matrix2f> mat_inv = mat.inverse();
        TEST_ASSERT(mat_inv.has_value());
        TEST_ASSERT(mat.inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
        TEST_ASSERT_FALSE(nnm::Matrix2f::zero().inverse().has_value());
    }

    test_section("approx_equal");
    {
        constexpr nnm::Matrix2f mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat1.approx_equal({ { 1.00000001f, -1.9999999f }, { -3.00000001f, 3.99999999f } });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(mat1.approx_equal({ { 1.1f, -1.9f }, { -3.1f, 3.9f } }));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Matrix2f mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr nnm::Matrix2f mat2({ 0.00000001f, -0.00000001f }, { -0.00000001f, 0.00000001f });
        constexpr auto result = mat2.approx_zero();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(mat1.approx_zero());
    }

    test_section("at");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat.at(0, 0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(mat.at(0, 1) == -2.0f);
        TEST_ASSERT(mat.at(1, 0) == -3.0f);
        TEST_ASSERT(mat.at(1, 1) == 4.0f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr auto result = mat[0][0];
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(mat[0][1] == -2.0f);
        TEST_ASSERT(mat[1][0] == -3.0f);
        TEST_ASSERT(mat[1][1] == 4.0f);
    }

    test_section("begin");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        TEST_ASSERT(mat.begin() == &mat.columns[0].x);
    }

    test_section("end");
    {
        constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        TEST_ASSERT(mat.end() == &mat.columns[1].y + 1);
    }

    constexpr nnm::Matrix2f m1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
    constexpr nnm::Matrix2f m2({ -4.0f, 3.0f }, { 2.0f, -1.0f });
    constexpr nnm::Matrix2f m3({ 1.0f, -2.0f }, { -3.0f, 4.0f });
    constexpr nnm::Matrix2f m4({ 10.0f, -2.5f }, { 37.0f, -24.0f });

    test_section("operator==");
    {
        constexpr auto result = m1 == m3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m1 == m2);
    }

    test_section("operator!=");
    {
        constexpr auto result = m1 != m3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(m1 != m2);
    }

    test_section("operator+");
    {
        constexpr auto result = m1 + m4;
        TEST_ASSERT(result.approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
    }

    test_section("operator+=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy += m4;
            return m1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
    }

    test_section("operator-");
    {
        constexpr auto result = m1 - m4;
        TEST_ASSERT(result.approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
    }

    test_section("operator-=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy -= m4;
            return m1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
    }

    test_section("operator*(const Matrix2&)");
    {
        constexpr auto result = m1 * m2;
        TEST_ASSERT(result == nnm::Matrix2f({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
        TEST_ASSERT((nnm::Matrix2f::identity() * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(1.0f, 2.0f)));
    }

    test_section("operator*=(const Matrix2&)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= m2;
            return m1_copy;
        }();
        TEST_ASSERT(result == nnm::Matrix2f({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
    }

    test_section("operator*(const Vector2&)");
    {
        constexpr auto result = m1 * nnm::Vector2(1.0f, 2.0f);
        TEST_ASSERT(result.approx_equal(nnm::Vector2(-5.0f, 6.0f)));
    }

    test_section("operator*(float)");
    {
        constexpr auto result = m1 * 2.0f;
        TEST_ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
    }

    test_section("operator*(float, const Matrix2&)");
    {
        constexpr auto result = 2.0f * m1;
        TEST_ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= 2.0f;
            return m1_copy;
        }();
        TEST_ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
    }

    test_section("operator/(float)");
    {
        constexpr auto result = m2 / 2.0f;
        TEST_ASSERT(result.approx_equal(nnm::Matrix2f({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
    }

    test_section("operator/(float, const Matrix2&)");
    {
        TEST_ASSERT((2.0f / m2).approx_equal(nnm::Matrix2f({ -0.5f, 0.666666666f }, { 1.0f, -2.0f })));
    }

    test_section("operator/=");
    {
        constexpr auto result = [=] {
            auto m2_copy = m2;
            m2_copy /= 2.0f;
            return m2_copy;
        }();
        TEST_ASSERT(result.approx_equal(nnm::Matrix2f({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
    }

    test_section("operator<");
    {
        constexpr auto result = m2 < m1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m1 < m2);
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(m1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Matrix2f::zero()));
    }
}