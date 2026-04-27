#include "tests.hpp"

void vector2_tests()
{
    test_case("Vector2");

    test_section("Vector2()");
    {
        constexpr nnm::Vector2f v1;
        TEST_ASSERT(v1.x == 0.0f);
        TEST_ASSERT(v1.y == 0.0f);
    }

    test_section("Vector2(const Vector2i&)");
    {
        constexpr nnm::Vector2f v2(nnm::Vector2i(1, 2));
        TEST_ASSERT(v2.x == 1.0f);
        TEST_ASSERT(v2.y == 2.0f);
    }

    test_section("Vector2(const Vector2<Other>&)");
    {
        constexpr nnm::Vector2d v1(1.0, -2.0);
        constexpr nnm::Vector2f v2(v1);
        TEST_ASSERT(v2.x == 1.0f);
        TEST_ASSERT(v2.y == -2.0f);
    }

    test_section("Vector2(float, float)");
    {
        constexpr nnm::Vector2 v3(1.0f, 2.0f);
        TEST_ASSERT(v3.x == 1.0f);
        TEST_ASSERT(v3.y == 2.0f);
    }

    test_section("all");
    {
        constexpr auto all_threes = nnm::Vector2f::all(3.0f);
        TEST_ASSERT(all_threes.x == 3.0f);
        TEST_ASSERT(all_threes.y == 3.0f);
    }

    test_section("zero");
    {
        constexpr auto zero = nnm::Vector2f::zero();
        TEST_ASSERT(zero.x == 0.0f);
        TEST_ASSERT(zero.y == 0.0f);
    }

    test_section("one");
    {
        constexpr auto one = nnm::Vector2f::one();
        TEST_ASSERT(one.x == 1.0f);
        TEST_ASSERT(one.y == 1.0f);
    }

    test_section("axis_x");
    {
        constexpr auto x = nnm::Vector2f::axis_x();
        TEST_ASSERT(x.x == 1.0f);
        TEST_ASSERT(x.y == 0.0f);
    }

    test_section("axis_y");
    {
        constexpr auto y = nnm::Vector2f::axis_y();
        TEST_ASSERT(y.x == 0.0f);
        TEST_ASSERT(y.y == 1.0f);
    }

    test_section("abs");
    {
        constexpr nnm::Vector2 v(1.0f, -2.0f);
        constexpr auto result = v.abs();
        TEST_ASSERT(result == nnm::Vector2(1.0f, 2.0f));
    }

    test_section("ceil");
    {
        constexpr nnm::Vector2 v(1.1f, -1.9f);
        TEST_ASSERT(v.ceil() == nnm::Vector2(2.0f, -1.0f));
    }

    test_section("floor");
    {
        constexpr nnm::Vector2 v(1.1f, -1.9f);
        TEST_ASSERT(v.floor() == nnm::Vector2(1.0f, -2.0f));
    }

    test_section("round");
    {
        constexpr nnm::Vector2 v1(1.1f, -1.9f);
        TEST_ASSERT(v1.round() == nnm::Vector2(1.0f, -2.0f));
        constexpr nnm::Vector2 v2(1.6f, -1.3f);
        TEST_ASSERT(v2.round() == nnm::Vector2(2.0f, -1.0f));
    }

    test_section("aspect_ratio");
    {
        constexpr nnm::Vector2 v(1.0f, -2.0f);
        constexpr auto result = v.aspect_ratio();
        TEST_ASSERT(result == 1.0f / -2.0f);
    }

    test_section("clamp");
    {
        constexpr nnm::Vector2 v(1.1f, -3.0f);
        constexpr auto result = v.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f });
        TEST_ASSERT(result == nnm::Vector2(1.1f, -2.0f));
    }

    test_section("length_sqrd");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(result, 25.0f));

        auto v = nnm::Vector2(-2.0f, 5.0f);
        TEST_ASSERT(nnm::approx_equal(v.length_sqrd(), 29.0f));

        v = nnm::Vector2(0.0f, 0.0f);
        TEST_ASSERT(nnm::approx_equal(v.length_sqrd(), 0.0f));
    }

    test_section("length");
    {
        nnm::Vector2 v(3.0f, 4.0f);
        TEST_ASSERT(nnm::approx_equal(v.length(), 5.0f));

        v = nnm::Vector2(-2.0f, 5.0f);
        TEST_ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(29.0f)));

        v = nnm::Vector2(0.0f, 0.0f);
        TEST_ASSERT(nnm::approx_equal(v.length(), 0.0f));
    }

    test_section("clamp_length");
    {
        TEST_ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 5.0f) == nnm::Vector2(3.0f, 4.0f));
        TEST_ASSERT(nnm::Vector2(1.0f, 2.0f).clamp_length(0.5f, 3.0f) == nnm::Vector2(1.0f, 2.0f));
        TEST_ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 2.0f).approx_equal(nnm::Vector2(1.2f, 1.6f)));
        TEST_ASSERT(nnm::approx_equal(nnm::Vector2(1.0f, 1.0f).clamp_length(2.0f, 5.0f).length(), 2.0f));
        TEST_ASSERT(nnm::Vector2(5.0f, 6.0f).clamp_length(2.0f, 5.0f).length() == 5.0f);
    }

    test_section("normalize");
    {
        constexpr nnm::Vector2 v(1.1f, -3.0f);
        const auto norm = v.normalize();
        TEST_ASSERT(nnm::approx_equal(norm.x, 0.344255f));
        TEST_ASSERT(nnm::approx_equal(norm.y, -0.938876f));
    }

    test_section("lerp");
    {
        constexpr nnm::Vector2 from(1.0f, 1.0f);
        constexpr nnm::Vector2 to(3.0f, 5.0f);
        constexpr auto result = from.lerp(to, 0.0f);
        TEST_ASSERT(result == nnm::Vector2(1.0f, 1.0f));
        TEST_ASSERT(from.lerp(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
        TEST_ASSERT(from.lerp(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
        TEST_ASSERT(from.lerp(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
        TEST_ASSERT(from.lerp(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
    }

    test_section("lerp_clamped");
    {
        constexpr nnm::Vector2 from(1.0f, 1.0f);
        constexpr nnm::Vector2 to(3.0f, 5.0f);
        constexpr auto result = from.lerp_clamped(to, 0.0f);
        TEST_ASSERT(result == nnm::Vector2(1.0f, 1.0f));
        TEST_ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
        TEST_ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
        TEST_ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
        TEST_ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
        TEST_ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector2(3.0f, 5.0f));
        TEST_ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector2(1.0f, 1.0f));
    }

    test_section("dot");
    {
        constexpr nnm::Vector2 v1(2.0f, 3.0f);
        constexpr nnm::Vector2 v2(4.0f, 5.0f);
        constexpr auto result = v1.dot(v2);
        TEST_ASSERT(result == 23.0f);
    }

    test_section("cross");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr nnm::Vector2 v2(-4.0f, 5.0f);
        constexpr auto result = v1.cross(v2);
        TEST_ASSERT(nnm::approx_equal(result, -2.0f));
    }

    test_section("outer");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr nnm::Vector2 v2(-4.0f, 5.0f);
        nnm::Matrix2f expected { { -8.0f, 10.0f }, { 12.0f, -15.0f } };
        constexpr auto result = v1.outer(v2);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("reflect");
    {
        constexpr nnm::Vector2 incident(3.0f, 4.0f);
        constexpr nnm::Vector2 normal(1.0f, 0.0f);
        constexpr auto result = incident.reflect(normal);
        TEST_ASSERT(result == nnm::Vector2(-3.0f, 4.0f));
    }

    test_section("project");
    {
        constexpr nnm::Vector2 v1 { 1.0f, 0.0f };
        constexpr nnm::Vector2 v2 { 0.0f, 1.0f };
        constexpr auto result = v1.project(v2);
        TEST_ASSERT(result.approx_equal({ 0.0f, 0.0f }));

        constexpr nnm::Vector2 v3 { 1.0f, 1.0f };
        constexpr nnm::Vector2 v4 { 2.0f, 2.0f };
        TEST_ASSERT(v3.project(v4).approx_equal({ 1.0f, 1.0f }));

        constexpr nnm::Vector2 v5 { 1.0f, -2.0f };
        constexpr nnm::Vector2 v6 { -3.0f, 4.0f };
        TEST_ASSERT(v5.project(v6).approx_equal({ 1.32f, -1.76f }));
    }

    test_section("inverse");
    {
        constexpr nnm::Vector2 v(2.0f, 3.0f);
        constexpr auto result = v.inverse();
        TEST_ASSERT(result.approx_equal(nnm::Vector2(1.0f / 2.0f, 1.0f / 3.0f)));
    }

    test_section("angle_between");
    {
        nnm::Vector2 v1(2.0f, -3.0f);
        nnm::Vector2 v2(-4.0f, 5.0f);
        TEST_ASSERT(nnm::approx_equal(v1.angle_between(v2), -3.05485f))
        ;TEST_ASSERT(nnm::approx_equal(v2.angle_between(v1), 3.05485f));
    }

    test_section("parallel");
    {
        constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
        TEST_ASSERT(v1.parallel(v1));
        constexpr nnm::Vector2f v2 { -2.0f, 4.0f };
        constexpr auto result = v1.parallel(v2);
        TEST_ASSERT(result);
        constexpr nnm::Vector2f v3 { 1.0f, -5.0f };
        TEST_ASSERT_FALSE(v1.parallel(v3));
    }

    test_section("perpendicular");
    {
        constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
        constexpr nnm::Vector2f v2 { 4.0f, 2.0f };
        constexpr auto result = v1.perpendicular(v2);
        TEST_ASSERT(result);
        constexpr nnm::Vector2f v3 { -4.0f, -2.0f };
        TEST_ASSERT(v1.perpendicular(v3));
    }

    test_section("arbitrary_perpendicular");
    {
        constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
        constexpr auto result = v1.arbitrary_perpendicular();
        TEST_ASSERT(v1.perpendicular(result));
        constexpr nnm::Vector2f v2 { 1.0f, 0.0f };
        TEST_ASSERT(v2.perpendicular(v2.arbitrary_perpendicular()));
    }

    test_section("rotate");
    {
        nnm::Vector2 v1(2.0f, -3.0f);
        TEST_ASSERT(v1.rotate(nnm::pi<float>() / 4.0f).approx_equal({ 3.53553f, -0.707107f }));
    }

    test_section("scale");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr auto result = v1.scale({ 1.5f, -2.0f });
        TEST_ASSERT(result.approx_equal({ 3.0f, 6.0f }));
    }

    test_section("shear_x");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr auto result = v1.shear_x(0.5f);
        TEST_ASSERT(result.approx_equal({ 0.5f, -3.0f }));
    }

    test_section("shear_y");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr auto result = v1.shear_y(-0.5f);
        TEST_ASSERT(result.approx_equal({ 2.0f, -4.0f }));
    }

    test_section("transform(const Basis2&)");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr nnm::Basis2f basis({ { 1.0f, -2.0f }, { -4.0f, 1.2f } });
        constexpr auto result = v1.transform(basis);
        TEST_ASSERT(result.approx_equal({ 14.0f, -7.6f }));
    }

    test_section("transform(const Transform2&)");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr nnm::Transform2f transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
        constexpr auto result = v1.transform(transform);
        TEST_ASSERT(result.approx_equal({ 14.0f, -0.8f }));
    }

    test_section("max");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.max();
        TEST_ASSERT(result == 4.0f);
        nnm::Vector2 v2(5.0f, 2.0f);
        TEST_ASSERT(v2.max() == 5.0f);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.max() == 0.0f);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.max() == 1.0f);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.max() == 1.0f);
    }

    test_section("abs_max");
    {
        constexpr nnm::Vector2f v1 { 3.0f, 4.0f };
        constexpr auto result = v1.abs_max();
        TEST_ASSERT(result == 4.0f);
        nnm::Vector2f v2 { 5.0f, 2.0f };
        TEST_ASSERT(v2.abs_max() == 5.0f);
        nnm::Vector2f v3 { 0.0f, 0.0f };
        TEST_ASSERT(v3.abs_max() == 0.0f);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.abs_max() == -2.0f);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.abs_max() == -2.0f);
    }

    test_section("min");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.min();
        TEST_ASSERT(result == 3.0f);
        nnm::Vector2 v2(5.0f, 2.0f);
        TEST_ASSERT(v2.min() == 2.0f);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.min() == 0.0f);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.min() == -2.0f);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.min() == -2.0f);
    }

    test_section("abs_min");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.abs_min();
        TEST_ASSERT(result == 3.0f);
        nnm::Vector2 v2(5.0f, 2.0f);
        TEST_ASSERT(v2.abs_min() == 2.0f);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.abs_min() == 0.0f);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.abs_min() == 1.0f);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.abs_min() == 1.0f);
    }

    test_section("max_index");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector2 v2(2.0f, 5.0f);
        TEST_ASSERT(v2.max_index() == 1);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.max_index() == 0);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.max_index() == 1);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.max_index() == 0);
    }

    test_section("abs_max_index");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.abs_max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector2 v2(2.0f, 5.0f);
        TEST_ASSERT(v2.abs_max_index() == 1);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.abs_max_index() == 0);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.abs_max_index() == 0);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.abs_max_index() == 1);
    }

    test_section("min_index");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.min_index();
        TEST_ASSERT(result == 0);
        nnm::Vector2 v2(2.0f, 5.0f);
        TEST_ASSERT(v2.min_index() == 0);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.min_index() == 0);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.min_index() == 0);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.min_index() == 1);
    }

    test_section("abs_min_index");
    {
        constexpr nnm::Vector2 v1(3.0f, 4.0f);
        constexpr auto result = v1.abs_min_index();
        TEST_ASSERT(result == 0);
        nnm::Vector2 v2(2.0f, 5.0f);
        TEST_ASSERT(v2.abs_min_index() == 0);
        nnm::Vector2 v3(0.0f, 0.0f);
        TEST_ASSERT(v3.abs_min_index() == 0);
        nnm::Vector2f v4 { -2.0f, 1.0f };
        TEST_ASSERT(v4.abs_min_index() == 1);
        nnm::Vector2f v5 { 1.0f, -2.0f };
        TEST_ASSERT(v5.abs_min_index() == 0);
    }

    test_section("approx_equal");
    {
        constexpr nnm::Vector2 v1(1.0f, 1.0f);
        constexpr nnm::Vector2 v2(1.0f + nnm::epsilon<float>() / 2.0f, 1.0f);
        constexpr auto result = v1.approx_equal(v2);
        TEST_ASSERT(result);
        nnm::Vector2 v3(1.0f, 1.0f);
        nnm::Vector2 v4(1.0f + 2.0f * nnm::epsilon<float>(), 1.0f);
        TEST_ASSERT_FALSE(v3.approx_equal(v4));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Vector2 v1(0.0f, 0.0f);
        constexpr auto result = v1.approx_zero();
        TEST_ASSERT(result);
        nnm::Vector2 v2(nnm::epsilon<float>(), 0.0f);
        TEST_ASSERT(v2.approx_zero());
        nnm::Vector2 v3(0.0f, nnm::epsilon<float>());
        TEST_ASSERT(v3.approx_zero());
        nnm::Vector2 v4(0.1f, 0.1f);
        TEST_ASSERT_FALSE(v4.approx_zero());
    }

    test_section("begin");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        TEST_ASSERT(v1.begin() == &v1.x);
    }

    test_section("end");
    {
        nnm::Vector2 v1(2.0f, -3.0f);
        TEST_ASSERT(v1.end() == &v1.y + 1);
    }

    test_section("at");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr auto result = v1.at(0);
        TEST_ASSERT(result == 2.0f);
        TEST_ASSERT(v1.at(1) == -3.0f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Vector2 v1(2.0f, -3.0f);
        constexpr auto result = v1[0];
        TEST_ASSERT(result == 2.0f);
        TEST_ASSERT(v1[1] == -3.0f);
    }

    constexpr nnm::Vector2 v1(1.0f, 2.0f);
    constexpr nnm::Vector2 v2(3.0f, 4.0f);
    constexpr nnm::Vector2 v3(1.0f, 2.0f);

    test_section("operator==");
    {
        constexpr auto result = v1 == v3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 == v2);
    }

    test_section("operator!=");
    {
        constexpr auto result = v1 != v3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(v1 != v2);
    }

    constexpr nnm::Vector2 v4(1.0f, 2.0f);
    constexpr nnm::Vector2 v5(3.0f, 4.0f);

    test_section("operator+(const Vector2&)");
    {
        constexpr auto result = v4 + v5;
        TEST_ASSERT(result == nnm::Vector2(4.0f, 6.0f));
    }

    test_section("operator+=");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v4_copy(1.0f, 2.0f);
            v4_copy += v5;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(4.0f, 6.0f));
    }

    test_section("operator-(const Vector2&)");
    {
        constexpr auto result = v5 - v4;
        TEST_ASSERT(result == nnm::Vector2(2.0f, 2.0f));
    }

    test_section("operator-=");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v5_copy = v5;
            v5_copy -= v4;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(2.0f, 2.0f))
    ;}

    test_section("operator*(const Vector2&)");
    {
        constexpr auto result = v4 * v5;
        TEST_ASSERT(result == nnm::Vector2(3.0f, 8.0f));
    }

    test_section("operator*=(const Vector2&)");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v4_copy = v4;
            v4_copy *= v5;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(3.0f, 8.0f));
    }

    test_section("operator*(const Matrix2&)");
    {
        constexpr nnm::Matrix2f matrix { { 2.0f, -3.0f }, { 1.0f, -0.5f } };
        constexpr auto result = nnm::Vector2(2.0f, -3.0f) * matrix;
        TEST_ASSERT(result.approx_equal({ 13.0f, 3.5f }))
    ;}

    test_section("operator*(float)");
    {
        constexpr auto result = v4 * 2.0f;
        TEST_ASSERT(result == nnm::Vector2(2.0f, 4.0f));
    }

    test_section("operator*(float, const Vector2&)");
    {
        constexpr auto result = 2.0f * v4;
        TEST_ASSERT(result == nnm::Vector2(2.0f, 4.0f));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v4_copy = v4;
            v4_copy *= 2.0f;
            return v4_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(2.0f, 4.0f));
    }

    test_section("operator/(const Vector2&)");
    {
        constexpr auto result = v5 / v4;
        TEST_ASSERT(result == nnm::Vector2(3.0f, 2.0f));
    }

    test_section("operator/=(const Vector2&)");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v5_copy = v5;
            v5_copy /= v4;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(3.0f, 2.0f));
    }

    test_section("operator/(float)");
    {
        constexpr auto result = v5 / 2.0f;
        TEST_ASSERT(result == nnm::Vector2(1.5f, 2.0f));
    }

    test_section("operator/(float, const Vector2&)");
    {
        constexpr auto result = 2.0f / v5;
        TEST_ASSERT(result.approx_equal(nnm::Vector2(0.666666f, 0.5f)));
    }

    test_section("operator/=(float)");
    {
        constexpr auto result = [=] {
            nnm::Vector2 v5_copy = v5;
            v5_copy /= 2.0f;
            return v5_copy;
        }();
        TEST_ASSERT(result == nnm::Vector2(1.5f, 2.0f));
    }

    test_section("operator+");
    {
        constexpr auto result = +v4;
        TEST_ASSERT(result == v4);
    }

    test_section("operator-");
    {
        constexpr auto result = -v4;
        TEST_ASSERT(result == nnm::Vector2(-1.0f, -2.0f));
    }

    test_section("operator<");
    {
        constexpr nnm::Vector2 v6(1.0f, 2.0f);
        constexpr nnm::Vector2 v7(3.0f, 4.0f);
        constexpr auto result = v6 < v7;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v7 < v6);
    }

    test_section("operator bool");
    {
        constexpr nnm::Vector2 v8(1.0f, 2.0f);
        constexpr auto result = static_cast<bool>(v8);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
    }
}