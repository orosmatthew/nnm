#include "tests.hpp"

void matrix3_tests()
{
    test_case("Matrix3");
    test_section("Matrix3()");
    {
        constexpr nnm::Matrix3f default_mat;
        TEST_ASSERT(default_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
        TEST_ASSERT(default_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
        TEST_ASSERT(default_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
    }

    test_section("Matrix3(const Matrix3<Other>&)");
    {
        constexpr nnm::Matrix3d m1({ 1.0, -2.0, 3.0 }, { 0.5, 0.75, -0.1 }, { 0.0, 2.0, -4.0 });
        constexpr nnm::Matrix3f m2(m1);
        TEST_ASSERT(m2.columns[0] == nnm::Vector3f(1.0f, -2.0f, 3.0f));
        TEST_ASSERT(m2.columns[1] == nnm::Vector3f(0.5f, 0.75f, -0.1f));
        TEST_ASSERT(m2.columns[2] == nnm::Vector3f(0.0f, 2.0f, -4.0f));
    }

    test_section("Matrix3(const Vector3&, const Vector3&, const Vector3&)");
    {
        constexpr nnm::Matrix3 cols(
            nnm::Vector3(1.0f, 2.0f, 3.0f), nnm::Vector3(-1.0f, -2.0f, -3.0f), nnm::Vector3(2.0f, 4.0f, 6.0f));
        TEST_ASSERT(cols.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(cols.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
        TEST_ASSERT(cols.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
    }

    test_section(
        "Matrix3(float, float, float, float, float, float, float, "
        "float, float)");
    {
        constexpr nnm::Matrix3 elems(1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, 2.0f, 4.0f, 6.0f);
        TEST_ASSERT(elems.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(elems.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
        TEST_ASSERT(elems.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
    }

    test_section("all");
    {
        constexpr auto threes = nnm::Matrix3f::all(3.0f);
        TEST_ASSERT(threes.columns[0] == nnm::Vector3f::all(3.0f));
        TEST_ASSERT(threes.columns[1] == nnm::Vector3f::all(3.0f));
        TEST_ASSERT(threes.columns[2] == nnm::Vector3f::all(3.0f));
    }

    test_section("zero");
    {
        constexpr auto zeros = nnm::Matrix3f::zero();
        TEST_ASSERT(zeros.columns[0] == nnm::Vector3f::zero());
        TEST_ASSERT(zeros.columns[1] == nnm::Vector3f::zero());
        TEST_ASSERT(zeros.columns[2] == nnm::Vector3f::zero());
    }

    test_section("one");
    {
        constexpr auto ones = nnm::Matrix3f::one();
        TEST_ASSERT(ones.columns[0] == nnm::Vector3f::one());
        TEST_ASSERT(ones.columns[1] == nnm::Vector3f::one());
        TEST_ASSERT(ones.columns[2] == nnm::Vector3f::one());
    }

    test_section("identity");
    {
        constexpr auto identity_mat = nnm::Matrix3f::identity();
        TEST_ASSERT(identity_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
        TEST_ASSERT(identity_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
        TEST_ASSERT(identity_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
    }

    constexpr nnm::Matrix3f m1({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f });

    test_section("trace");
    {
        constexpr auto result = m1.trace();
        TEST_ASSERT(nnm::approx_equal(result, 5.0f));
    }

    test_section("determinant");
    {
        constexpr auto result = m1.determinant();
        TEST_ASSERT(nnm::approx_equal(result, 64.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::Matrix3f::identity().determinant(), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::Matrix3f::zero().determinant(), 0.0f));
    }

    test_section("minor_matrix_at");
    {
        constexpr auto result = m1.minor_matrix_at(0, 0);
        TEST_ASSERT(result.approx_equal({ { -2.0f, -1.0f }, { -4.0f, 6.0f } }));
        TEST_ASSERT(m1.minor_matrix_at(1, 2).approx_equal({ { 1.0f, 2.0f }, { 2.0f, -4.0f } }));
    }

    test_section("minor_at");
    {
        constexpr nnm::Matrix3f expected({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
        constexpr auto result = m1.minor_at(0, 0);
        TEST_ASSERT(nnm::approx_equal(result, expected.at(0, 0)));
        TEST_ASSERT(nnm::approx_equal(m1.minor_at(1, 2), expected.at(1, 2)));
    }

    test_section("minor");
    {
        constexpr nnm::Matrix3f expected({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
        constexpr auto result = m1.minor();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("cofactor_at");
    {
        constexpr nnm::Matrix3f expected({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
        constexpr auto result = m1.cofactor_at(0, 0);
        TEST_ASSERT(nnm::approx_equal(result, expected.at(0, 0)));
        TEST_ASSERT(nnm::approx_equal(m1.cofactor_at(1, 2), expected.at(1, 2)));
    }

    test_section("cofactor");
    {
        constexpr nnm::Matrix3f expected({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
        constexpr auto result = m1.cofactor();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("transpose");
    {
        constexpr nnm::Matrix3f expected({ 1.0f, -3.0f, 2.0f }, { 2.0f, -2.0f, -4.0f }, { 3.0f, -1.0f, 6.0f });
        constexpr auto result = m1.transpose();
        TEST_ASSERT(result == expected);
    }

    test_section("adjugate");
    {
        constexpr nnm::Matrix3f expected({ -16.0f, -24.0f, 4.0f }, { 16.0f, 0.0f, -8.0f }, { 16.0f, 8.0f, 4.0f });
        constexpr auto result = m1.adjugate();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("unchecked_inverse");
    {
        constexpr nnm::Matrix3f expected(
            { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
        constexpr auto result = m1.unchecked_inverse();
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Matrix3f expected(
            { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
        constexpr auto result = m1.inverse();
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal(expected));
        TEST_ASSERT_FALSE(nnm::Matrix3f::zero().inverse().has_value());
    }

    test_section("approx_equal");
    {
        constexpr nnm::Matrix3f almost_ident(
            { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
        constexpr nnm::Matrix3f almost_zero(
            { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
        constexpr auto result = nnm::Matrix3f::identity().approx_equal(almost_ident);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(almost_zero.approx_equal(almost_ident));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Matrix3f almost_ident(
            { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
        constexpr nnm::Matrix3f almost_zero(
            { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
        constexpr auto result = nnm::Matrix3f::zero().approx_zero();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(almost_ident.approx_zero());
        TEST_ASSERT(almost_zero.approx_zero());
    }

    test_section("at");
    {
        constexpr auto result = m1.at(0);
        TEST_ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(m1.at(1) == nnm::Vector3(-3.0f, -2.0f, -1.0f));
        TEST_ASSERT(m1.at(0, 0) == 1.0f);
        TEST_ASSERT(m1.at(1, 2) == -1.0f);
    }

    test_section("begin");
    {
        TEST_ASSERT(m1.begin() == &m1.columns[0].x);
    }

    test_section("end");
    {
        TEST_ASSERT(m1.end() == &m1.columns[2].z + 1);
    }

    test_section("operator[]");
    {
        constexpr auto result = m1[0];
        TEST_ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
        TEST_ASSERT(m1[1] == nnm::Vector3(-3.0f, -2.0f, -1.0f));
    }

    test_section("operator==");
    {
        constexpr auto result
            = m1 == nnm::Matrix3f({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m1 == nnm::Matrix3f::identity());
    }

    test_section("operator!=");
    {
        constexpr auto result = m1 != nnm::Matrix3f::identity();
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(m1 != nnm::Matrix3f({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
    }

    constexpr nnm::Matrix3f m2({ 3.0f, -6.0f, -9.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 2.0f, 10.0f });

    test_section("operator+");
    {
        constexpr nnm::Matrix3f expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
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
        constexpr nnm::Matrix3f expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator-");
    {
        constexpr nnm::Matrix3f expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
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
        constexpr nnm::Matrix3f expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(const Matrix3&)");
    {
        constexpr nnm::Matrix3f expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
        constexpr auto result = m1 * m2;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*=(const Matrix3&)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= m2;
            return m1_copy;
        }();
        constexpr nnm::Matrix3f expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(const Vector3&)");
    {
        constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        constexpr auto result = m1 * v1;
        TEST_ASSERT(result.approx_equal({ 13.0f, -6.0f, 23.0f }));
    }

    test_section("operator*(float)");
    {
        constexpr nnm::Matrix3f expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
        constexpr auto result = m1 * 5.0f;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*(float, const Matrix3&)");
    {
        constexpr nnm::Matrix3f expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
        constexpr auto result = 5.0f * m1;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy *= 5.0f;
            return m1_copy;
        }();
        constexpr nnm::Matrix3f expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator/(float)");
    {
        constexpr nnm::Matrix3f expected(
            { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
        constexpr auto result = m1 / 2.0f;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator/(float, const Matrix3&)");
    {
        constexpr nnm::Matrix3f expected(
            { 2.0f, 1.0f, 0.666666f }, { -0.6666666f, -1.0f, -2.0f }, { 1.0f, -0.5f, 0.3333333f });
        constexpr auto result = 2.0f / m1;
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator/=");
    {
        constexpr auto result = [=] {
            auto m1_copy = m1;
            m1_copy /= 2.0f;
            return m1_copy;
        }();
        constexpr nnm::Matrix3f expected(
            { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("operator<");
    {
        constexpr auto result = m1 < nnm::Matrix3f::identity();
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(m1 < nnm::Matrix3f::all(10.0f));
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(nnm::Matrix3f::zero());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(static_cast<bool>(nnm::Matrix3f::identity()));
    }
}