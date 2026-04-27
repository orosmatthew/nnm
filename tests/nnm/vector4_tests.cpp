#include "tests.hpp"

void vector4_tests()
{
    test_case("Vector4");
    test_section("Vector4()");
    {
        constexpr nnm::Vector4f v1;
        TEST_ASSERT(v1.x == 0.0f);
        TEST_ASSERT(v1.y == 0.0f);
        TEST_ASSERT(v1.z == 0.0f);
        TEST_ASSERT(v1.w == 0.0f);
    }

    test_section("Vector4(const Vector4<Other>&)");
    {
        constexpr nnm::Vector4d v1(1.0, -2.0, 0.5, -0.75);
        constexpr nnm::Vector4f v2(v1);
        TEST_ASSERT(v2.x == 1.0f);
        TEST_ASSERT(v2.y == -2.0f);
        TEST_ASSERT(v2.z == 0.5f);
        TEST_ASSERT(v2.w == -0.75f);
    }

    test_section("Vector4(const Vector2&, float, float)");
    {
        constexpr nnm::Vector4 v(nnm::Vector2(1.0f, -2.0f), 3.0f, -4.0f);
        TEST_ASSERT(v.x == 1.0f);
        TEST_ASSERT(v.y == -2.0f);
        TEST_ASSERT(v.z == 3.0f);
        TEST_ASSERT(v.w == -4.0f);
    }

    test_section("Vector4(const Vector3&, float)");
    {
        constexpr nnm::Vector4 v(nnm::Vector3(1.0f, -2.0f, 3.0f), -4.0f);
        TEST_ASSERT(v.x == 1.0f);
        TEST_ASSERT(v.y == -2.0f);
        TEST_ASSERT(v.z == 3.0f);
        TEST_ASSERT(v.w == -4.0f);
    }

    test_section("Vector4(float, float, float, float)");
    {
        constexpr nnm::Vector4 v2(-1.0f, 2.0f, -3.0f, 4.0f);
        TEST_ASSERT(v2.x == -1.0f);
        TEST_ASSERT(v2.y == 2.0f);
        TEST_ASSERT(v2.z == -3.0f);
        TEST_ASSERT(v2.w == 4.0f);
    }

    test_section("all");
    {
        constexpr auto v1 = nnm::Vector4f::all(3.0f);
        TEST_ASSERT(v1.x == 3.0f);
        TEST_ASSERT(v1.y == 3.0f);
        TEST_ASSERT(v1.z == 3.0f);
        TEST_ASSERT(v1.w == 3.0f);
    }

    test_section("zero");
    {
        constexpr auto v2 = nnm::Vector4f::zero();
        TEST_ASSERT(v2.x == 0.0f);
        TEST_ASSERT(v2.y == 0.0f);
        TEST_ASSERT(v2.z == 0.0f);
        TEST_ASSERT(v2.w == 0.0f);
    }

    test_section("one");
    {
        constexpr auto v3 = nnm::Vector4f::one();
        TEST_ASSERT(v3.x == 1.0f);
        TEST_ASSERT(v3.y == 1.0f);
        TEST_ASSERT(v3.z == 1.0f);
        TEST_ASSERT(v3.w == 1.0f);
    }

    test_section("axis_x");
    {
        constexpr auto x = nnm::Vector4f::axis_x();
        TEST_ASSERT(x.x == 1.0f);
        TEST_ASSERT(x.y == 0.0f);
        TEST_ASSERT(x.z == 0.0f);
        TEST_ASSERT(x.w == 0.0f);
    }

    test_section("axis_y");
    {
        constexpr auto y = nnm::Vector4f::axis_y();
        TEST_ASSERT(y.x == 0.0f);
        TEST_ASSERT(y.y == 1.0f);
        TEST_ASSERT(y.z == 0.0f);
        TEST_ASSERT(y.w == 0.0f);
    }

    test_section("axis_z");
    {
        constexpr auto z = nnm::Vector4f::axis_z();
        TEST_ASSERT(z.x == 0.0f);
        TEST_ASSERT(z.y == 0.0f);
        TEST_ASSERT(z.z == 1.0f);
        TEST_ASSERT(z.w == 0.0f);
    }

    test_section("axis_w");
    {
        constexpr auto w = nnm::Vector4f::axis_w();
        TEST_ASSERT(w.x == 0.0f);
        TEST_ASSERT(w.y == 0.0f);
        TEST_ASSERT(w.z == 0.0f);
        TEST_ASSERT(w.w == 1.0f);
    }

    test_section("abs");
    {
        constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        constexpr nnm::Vector4 v_expected(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr auto result = v1.abs();
        TEST_ASSERT(result == v_expected);
    }

    test_section("ceil");
    {
        constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
        constexpr nnm::Vector4 v_expected(-1.0f, 1.0f, 0.0f, 2.0f);
        TEST_ASSERT(v1.ceil() == v_expected);
    }

    test_section("floor");
    {
        constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
        constexpr nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 1.0f);
        TEST_ASSERT(v1.floor() == v_expected);
    }

    test_section("round");
    {
        constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
        constexpr nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 2.0f);
        TEST_ASSERT(v1.round() == v_expected);
    }

    test_section("clamp");
    {
        constexpr nnm::Vector4 v1(-1.0f, 2.0f, 3.0f, -4.0f);
        constexpr nnm::Vector4 v2(2.0f, -3.0f, -2.0f, -3.0f);
        constexpr nnm::Vector4 v3(4.0f, 1.0f, 4.0f, 1.0f);
        constexpr auto result = v1.clamp(v2, v3);
        TEST_ASSERT(result == nnm::Vector4(2.0f, 1.0f, 3.0f, -3.0f));
    }

    test_section("length_sqrd");
    {
        constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        constexpr auto result = v1.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(result, 30.0f));
    }

    test_section("length");
    {
        constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        TEST_ASSERT(nnm::approx_equal(v1.length(), nnm::sqrt(30.0f)));
    }

    constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
    constexpr nnm::Vector4 v2(4.0f, 5.0f, -2.0f, 1.5f);

    test_section("clamp_length");
    {
        TEST_ASSERT(v1.clamp_length(0.0f, 1.0f).approx_equal(v1.normalize()));
        TEST_ASSERT(v1.clamp_length(2.0f, 3.0f).approx_equal(v1.normalize() * 3.0f));
        TEST_ASSERT(v1.clamp_length(10.0f, 50.0f).approx_equal(v1.normalize() * 10.0f));
    }

    test_section("normalize");
    {
        TEST_ASSERT(nnm::Vector4f().normalize() == nnm::Vector4f());
        constexpr nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);
        constexpr nnm::Vector4 v_expected(-0.182574f, 0.365148f, -0.547723f, 0.730297f);
        TEST_ASSERT(v3.normalize().approx_equal(v_expected));
    }

    test_section("lerp");
    {
        constexpr auto result = v1.lerp(v2, 0.0f);
        TEST_ASSERT(result == v1);
        TEST_ASSERT(v1.lerp(v2, 1.0f) == v2);
        TEST_ASSERT(v1.lerp(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
    }

    test_section("lerp_clamped");
    {
        constexpr auto result = v1.lerp_clamped(v2, 0.0f);
        TEST_ASSERT(result == v1);
        TEST_ASSERT(v1.lerp_clamped(v2, 1.0f) == v2);
        TEST_ASSERT(v1.lerp_clamped(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
        TEST_ASSERT(v1.lerp_clamped(v2, -5.0f) == v1);
        TEST_ASSERT(v1.lerp_clamped(v2, 5.0f) == v2);
    }

    test_section("dot");
    {
        constexpr auto result = v1.dot(v2);
        TEST_ASSERT(nnm::approx_equal(result, 18.0f));
    }

    test_section("outer");
    {
        nnm::Matrix4f expected { { -4.0f, -5.0f, 2.0f, -1.5f },
                                 { 8.0f, 10.0f, -4.0f, 3.0f },
                                 { -12.0f, -15.0f, 6.0f, -4.5f },
                                 { 16.0f, 20.0f, -8.0f, 6.0f } };
        constexpr auto result = v1.outer(v2);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Vector4 v_expected(-1.0f, 0.5f, -0.33333333f, 0.25f);
        constexpr auto result = v1.inverse();
        TEST_ASSERT(result.approx_equal(v_expected));
    }

    test_section("transform");
    {
        constexpr nnm::Transform3f transform(
            { { 1.0f, 2.0f, -3.0f, 4.0f },
              { -10.0f, 0.5f, 20.6f, 0.0f },
              { 1.0f, 3.0f, 3.3f, -1.0f },
              { 9.9f, -7.54f, 20.0f, 0.1f } });
        constexpr auto result = v1.transform(transform);
        TEST_ASSERT(result.approx_equal({ 15.6f, -40.16f, 114.3f, -0.6f }))
    }

    test_section("transform_at");
    {
        constexpr nnm::Transform3f transform { { { 1.0f, 2.0f, -3.0f, 4.0f },
                                                 { -10.0f, 0.5f, 20.6f, 0.0f },
                                                 { 1.0f, 3.0f, 3.3f, -1.0f },
                                                 { 9.9f, -7.54f, 20.0f, 0.1f } } };
        constexpr auto result = v1.transform_at({ -3.0f, 1.5f, 10.0f }, transform);
        TEST_ASSERT(result.approx_equal({ 20.6f, -63.41f, 51.4f, 21.4f }));
    }

    test_section("max");
    {
        constexpr auto result = v1.max();
        TEST_ASSERT(result == 4.0f);
        TEST_ASSERT(v2.max() == 5.0f);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.max() == 4.0f);
    }

    test_section("abs_max");
    {
        constexpr auto result = v1.abs_max();
        TEST_ASSERT(result == 4.0f);
        TEST_ASSERT(v2.abs_max() == 5.0f);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.abs_max() == -5.0f);
    }

    test_section("min");
    {
        constexpr auto result = v1.min();
        TEST_ASSERT(result == -3.0f);
        TEST_ASSERT(v2.min() == -2.0f);
        constexpr nnm::Vector4f v3 { -2.0f, 2.0f, 3.0f, -1.0f };
        TEST_ASSERT(v3.min() == -2.0f);
        constexpr nnm::Vector4f v4 { -2.0f, 2.0f, 3.0f, -10.0f };
        TEST_ASSERT(v4.min() == -10.0f);
    }

    test_section("abs_min");
    {
        constexpr auto result = v1.abs_min();
        TEST_ASSERT(result == -1.0f);
        TEST_ASSERT(v2.abs_min() == 1.5f);
        constexpr nnm::Vector4f v3 { -2.0f, 2.0f, 3.0f, -1.0f };
        TEST_ASSERT(v3.abs_min() == -1.0f);
        constexpr nnm::Vector4f v4 { -2.0f, 2.0f, 3.0f, -10.0f };
        TEST_ASSERT(v4.abs_min() == -2.0f);
    }

    test_section("max_index");
    {
        constexpr auto result = v1.max_index();
        TEST_ASSERT(result == 3);
        TEST_ASSERT(v2.max_index() == 1);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.max_index() == 3);
    }

    test_section("abs_max_index");
    {
        constexpr auto result = v1.abs_max_index();
        TEST_ASSERT(result == 3);
        TEST_ASSERT(v2.abs_max_index() == 1);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.abs_max_index() == 1);
    }

    test_section("min_index");
    {
        constexpr auto result = v1.min_index();
        TEST_ASSERT(result == 2);
        TEST_ASSERT(v2.min_index() == 2);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.min_index() == 1);
    }

    test_section("abs_min_index");
    {
        constexpr auto result = v1.abs_min_index();
        TEST_ASSERT(result == 0);
        TEST_ASSERT(v2.abs_min_index() == 3);
        constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
        TEST_ASSERT(v3.abs_min_index() == 0);
    }

    test_section("approx_equal");
    {
        constexpr nnm::Vector4 v1_almost(-0.99999999f, 2.0f, -3.00000001f, 3.99999f);
        constexpr auto result = v1.approx_equal(v1_almost);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1.approx_equal(v2));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Vector4 almost_zero(0.00001f, -0.000001f, 0.0f, 0.00000001f);
        constexpr auto result = almost_zero;
        TEST_ASSERT(result);
    }

    test_section("xy");
    {
        constexpr auto result = v1.xy();
        TEST_ASSERT(result == nnm::Vector2(-1.0f, 2.0f));
    }

    test_section("xyz");
    {
        constexpr auto result = v1.xyz();
        TEST_ASSERT(result == nnm::Vector3(-1.0f, 2.0f, -3.0f));
    }

    test_section("begin");
    {
        TEST_ASSERT(v1.begin() == &v1.x);
    }

    test_section("end");
    {
        TEST_ASSERT(v1.end() == &v1.w + 1);
    }

    test_section("at");
    {
        constexpr auto result = v1.at(0);
        TEST_ASSERT(result == -1.0f);
        TEST_ASSERT(v1.at(1) == 2.0f);
        TEST_ASSERT(v1.at(2) == -3.0f);
        TEST_ASSERT(v1.at(3) == 4.0f);
    }

    test_section("operator[]");
    {
        constexpr auto result = v1[0];
        TEST_ASSERT(result == -1.0f);
        TEST_ASSERT(v1[1] == 2.0f);
        TEST_ASSERT(v1[2] == -3.0f);
        TEST_ASSERT(v1[3] == 4.0f);
    }

    constexpr nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);

    test_section("operator==");
    {
        constexpr auto result = v1 == v3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 == v2);
    }

    test_section("operator!=");
    {
        constexpr auto result = v1 != v2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 != v3);
    }

    test_section("operator+(const Vector4&)");
    {
        constexpr auto result = v1 + v2;
        TEST_ASSERT(result.approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
    }

    test_section("operator+=(const Vector4&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy += v2;
            return v1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
    }

    test_section("operator-(const Vector4&)");
    {
        constexpr auto result = v1 - v2;
        TEST_ASSERT(result.approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
    }

    test_section("operator-=(const Vector4&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy -= v2;
            return v1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
    }

    test_section("operator*(const Vector4&)");
    {
        constexpr auto result = v1 * v2;
        TEST_ASSERT(result.approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
    }

    test_section("operator*=(const Vector4&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= v2;
            return v1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
    }

    test_section("operator*(const Matrix4&)");
    {
        constexpr nnm::Matrix4f matrix { { 1.0f, 2.0f, 3.0f, 4.0f },
                                         { -1.0f, -2.0f, -3.0f, -4.0f },
                                         { 1.0f, 3.0f, 2.0f, 4.0f },
                                         { -4.0f, -2.0f, -3.0f, -1.0f } };
        constexpr auto result = v1 * matrix;
        TEST_ASSERT(result.approx_equal({ 10.0f, -10.0f, 15.0f, 5.0f }))
    }

    test_section("operator*(float)");
    {
        constexpr auto result = v1 * 2.0f;
        TEST_ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
    }

    test_section("operator*(float, const Vector4&)");
    {
        constexpr auto result = 2.0f * v1;
        TEST_ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= 2.0f;
            return v1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
    }

    test_section("operator/(const Vector4&)");
    {
        constexpr auto result = v2 / v1;
        TEST_ASSERT(result.approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
    }

    test_section("operator/=(const Vector4&)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= v1;
            return v2_copy;
        }();
        TEST_ASSERT(result.approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
    }

    test_section("operator/(float)");
    {
        constexpr auto result = v2 / 2.0f;
        TEST_ASSERT(result.approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
    }

    test_section("operator/=(float)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= 2.0f;
            return v2_copy;
        }();
        TEST_ASSERT(result.approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
    }

    test_section("operator<(const Vector4&)");
    {
        constexpr auto result = v1 < v2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v2 < v1);
    }

    test_section("operator+");
    {
        constexpr auto result = +v1;
        TEST_ASSERT(result == v1);
    }

    test_section("operator-");
    {
        constexpr auto result = -v1;
        TEST_ASSERT(result == nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(v1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Vector4f::zero()));
    }
}