#include "tests.hpp"

void point2_tests()
{
    test_case("Point2");

    test_section("Point2()");
    {
        constexpr nnm::Point2f p1;
        TEST_ASSERT(p1.x == 0.0f);
        TEST_ASSERT(p1.y == 0.0f);
    }

    test_section("Point2(const Point2<Other>&)");
    {
        constexpr nnm::Point2d p1 { 1.0, -3.0 };
        constexpr auto p2 = nnm::Point2f { p1 };
        TEST_ASSERT(nnm::approx_equal(p2.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(p2.y, -3.0f));
    }

    test_section("Point2(Real, Real)");
    {
        constexpr nnm::Point2f p1 { 1.0f, -3.0f };
        TEST_ASSERT(nnm::approx_equal(p1.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(p1.y, -3.0f));
    }

    test_section("from_vector");
    {
        constexpr nnm::Vector2f v1 { 1.0f, -3.0f };
        constexpr auto p1 = nnm::Point2f::from_vector(v1);
        TEST_ASSERT(p1.approx_equal({ 1.0f, -3.0 }));
    }

    test_section("all");
    {
        constexpr auto p1 = nnm::Point2f::all(3.5f);
        TEST_ASSERT(p1.approx_equal({ 3.5f, 3.5f }));
    }

    test_section("zero");
    {
        constexpr auto p1 = nnm::Point2f::zero();
        TEST_ASSERT(p1.x == 0.0f);
        TEST_ASSERT(p1.y == 0.0f);
    }

    test_section("to_vector");
    {
        constexpr nnm::Point2f p1 { 1.0f, -3.0f };
        constexpr nnm::Vector2f v1 = p1.to_vector();
        TEST_ASSERT(v1.approx_equal({ 1.0f, -3.0f }));
    }

    test_section("abs");
    {
        constexpr nnm::Point2f p1 { 1.0f, -3.0f };
        constexpr nnm::Point2f r1 = p1.abs();
        TEST_ASSERT(r1.approx_equal({ 1.0f, 3.0f }));
        constexpr nnm::Point2f p2 { -1.0f, 3.0f };
        constexpr nnm::Point2f r2 = p2.abs();
        TEST_ASSERT(r2.approx_equal({ 1.0f, 3.0f }));
    }

    test_section("ceil");
    {
        constexpr nnm::Point2f p1 { 1.1f, -3.7f };
        const nnm::Point2f r1 = p1.ceil();
        TEST_ASSERT(r1.approx_equal({ 2.0f, -3.0f }));
        constexpr nnm::Point2f p2 { 1.6f, -3.2f };
        const nnm::Point2f r2 = p2.ceil();
        TEST_ASSERT(r2.approx_equal({ 2.0f, -3.0f }));
    }

    test_section("floor");
    {
        constexpr nnm::Point2f p1 { 1.1f, -3.7f };
        const nnm::Point2f r1 = p1.floor();
        TEST_ASSERT(r1.approx_equal({ 1.0f, -4.0f }));
        constexpr nnm::Point2f p2 { 1.6f, -3.2f };
        const nnm::Point2f r2 = p2.floor();
        TEST_ASSERT(r2.approx_equal({ 1.0f, -4.0f }));
    }

    test_section("round");
    {
        constexpr nnm::Point2f p1 { 1.1f, -3.7f };
        const nnm::Point2f r1 = p1.round();
        TEST_ASSERT(r1.approx_equal({ 1.0f, -4.0f }));
        constexpr nnm::Point2f p2 { 1.6f, -3.2f };
        const nnm::Point2f r2 = p2.round();
        TEST_ASSERT(r2.approx_equal({ 2.0f, -3.0f }));
    }

    test_section("clamp");
    {
        constexpr nnm::Point2 p1 { 1.1f, -3.0f };
        constexpr auto result = p1.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f });
        TEST_ASSERT(result.approx_equal({ 1.1f, -2.0f }));
    }

    test_section("direction");
    {
        constexpr nnm::Point2 from1(1.0f, 1.0f);
        constexpr nnm::Point2 to1(2.0f, 2.0f);
        auto direction1 = from1.direction(to1);
        TEST_ASSERT(nnm::approx_equal(direction1.x, 0.7071067812f));
        TEST_ASSERT(nnm::approx_equal(direction1.y, 0.7071067812f));

        constexpr nnm::Point2 from2(-1.0f, -1.0f);
        constexpr nnm::Point2 to2(1.0f, 1.0f);
        auto direction2 = from2.direction(to2);
        TEST_ASSERT(nnm::approx_equal(direction2.x, 0.7071067812f));
        TEST_ASSERT(nnm::approx_equal(direction2.y, 0.7071067812f));

        constexpr nnm::Point2 from3(0.0f, 0.0f);
        constexpr nnm::Point2 to3(1.0f, 0.0f);
        auto direction3 = from3.direction(to3);
        TEST_ASSERT(nnm::approx_equal(direction3.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(direction3.y, 0.0f));

        constexpr nnm::Point2 from4(0.0f, 0.0f);
        constexpr nnm::Point2 to4(0.0f, 1.0f);
        auto direction4 = from4.direction(to4);
        TEST_ASSERT(nnm::approx_equal(direction4.x, 0.0f));
        TEST_ASSERT(nnm::approx_equal(direction4.y, 1.0f));

        constexpr nnm::Point2 from5(1.0f, 2.0f);
        constexpr nnm::Point2 to5(1.0f, 2.0f);
        auto direction5 = from5.direction(to5);
        TEST_ASSERT(nnm::approx_equal(direction5.x, 0.0f));
        TEST_ASSERT(nnm::approx_equal(direction5.y, 0.0f));
    }

    test_section("direction_unnormalized");
    {
        constexpr nnm::Point2 from1(1.0f, 1.0f);
        constexpr nnm::Point2 to1(2.0f, 2.0f);
        constexpr auto direction1 = from1.direction_unnormalized(to1);
        TEST_ASSERT(nnm::approx_equal(direction1.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(direction1.y, 1.0f));

        constexpr nnm::Point2 from2(-1.0f, -1.0f);
        constexpr nnm::Point2 to2(1.0f, 1.0f);
        auto direction2 = from2.direction_unnormalized(to2);
        TEST_ASSERT(nnm::approx_equal(direction2.x, 2.0f));
        TEST_ASSERT(nnm::approx_equal(direction2.y, 2.0f));

        constexpr nnm::Point2 from3(0.0f, 0.0f);
        constexpr nnm::Point2 to3(1.0f, 0.0f);
        auto direction3 = from3.direction_unnormalized(to3);
        TEST_ASSERT(nnm::approx_equal(direction3.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(direction3.y, 0.0f));

        constexpr nnm::Point2 from4(0.0f, 0.0f);
        constexpr nnm::Point2 to4(0.0f, 1.0f);
        auto direction4 = from4.direction_unnormalized(to4);
        TEST_ASSERT(nnm::approx_equal(direction4.x, 0.0f));
        TEST_ASSERT(nnm::approx_equal(direction4.y, 1.0f));

        constexpr nnm::Point2 from5(1.0f, 2.0f);
        constexpr nnm::Point2 to5(1.0f, 2.0f);
        auto direction5 = from5.direction_unnormalized(to5);
        TEST_ASSERT(nnm::approx_equal(direction5.x, 0.0f));
        TEST_ASSERT(nnm::approx_equal(direction5.y, 0.0f));
    }

    test_section("distance_sqrd");
    {
        constexpr nnm::Point2 from1(1.0f, 1.0f);
        constexpr nnm::Point2 to1(2.0f, 2.0f);
        constexpr auto result = from1.distance_sqrd(to1);
        TEST_ASSERT(nnm::approx_equal(result, 2.0f));

        constexpr nnm::Point2 from2(-1.0f, -1.0f);
        constexpr nnm::Point2 to2(1.0f, 1.0f);
        TEST_ASSERT(nnm::approx_equal(from2.distance_sqrd(to2), 8.0f));

        constexpr nnm::Point2 from3(0.0f, 0.0f);
        constexpr nnm::Point2 to3(3.0f, 0.0f);
        TEST_ASSERT(nnm::approx_equal(from3.distance_sqrd(to3), 9.0f));

        constexpr nnm::Point2 from4(0.0f, 0.0f);
        constexpr nnm::Point2 to4(0.0f, 4.0f);
        TEST_ASSERT(nnm::approx_equal(from4.distance_sqrd(to4), 16.0f));

        constexpr nnm::Point2 from5(1.0f, 2.0f);
        constexpr nnm::Point2 to5(1.0f, 2.0f);
        TEST_ASSERT(nnm::approx_equal(from5.distance_sqrd(to5), 0.0f));
    }

    test_section("distance");
    {
        nnm::Point2 from(1.0f, 1.0f);
        nnm::Point2 to(2.0f, 2.0f);
        TEST_ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(2.0f)));

        from = nnm::Point2(-1.0f, -1.0f);
        to = nnm::Point2(1.0f, 1.0f);
        TEST_ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(8.0f)));

        from = nnm::Point2(0.0f, 0.0f);
        to = nnm::Point2(3.0f, 0.0f);
        TEST_ASSERT(nnm::approx_equal(from.distance(to), 3.0f));

        from = nnm::Point2(0.0f, 0.0f);
        to = nnm::Point2(0.0f, 4.0f);
        TEST_ASSERT(nnm::approx_equal(from.distance(to), 4.0f));

        from = nnm::Point2(1.0f, 2.0f);
        to = nnm::Point2(1.0f, 2.0f);
        TEST_ASSERT(nnm::approx_equal(from.distance(to), 0.0f));
    }

    test_section("manhattan_distance");
    {
        constexpr nnm::Point2 from1(1.0f, 1.0f);
        constexpr nnm::Point2 to1(2.0f, 2.0f);
        constexpr auto result = from1.manhattan_distance(to1);
        TEST_ASSERT(nnm::approx_equal(result, 2.0f));

        auto from = nnm::Point2(-1.0f, -1.0f);
        auto to = nnm::Point2(1.0f, 1.0f);
        TEST_ASSERT(nnm::approx_equal(from.manhattan_distance(to), 4.0f));

        from = nnm::Point2(0.0f, 0.0f);
        to = nnm::Point2(3.0f, 0.0f);
        TEST_ASSERT(nnm::approx_equal(from.manhattan_distance(to), 3.0f));

        from = nnm::Point2(0.0f, 0.0f);
        to = nnm::Point2(0.0f, 4.0f);
        TEST_ASSERT(nnm::approx_equal(from.manhattan_distance(to), 4.0f));

        from = nnm::Point2(1.0f, 2.0f);
        to = nnm::Point2(1.0f, 2.0f);
        TEST_ASSERT(nnm::approx_equal(from.manhattan_distance(to), 0.0f));
    }

    test_section("lerp");
    {
        constexpr nnm::Point2f from { 1.0f, 1.0f };
        constexpr nnm::Point2f to { 3.0f, 5.0f };
        constexpr auto result = from.lerp(to, 0.0f);
        TEST_ASSERT(result.approx_equal({ 1.0f, 1.0f }));
        TEST_ASSERT(from.lerp(to, 1.0f).approx_equal({ 3.0f, 5.0f }));
        TEST_ASSERT(from.lerp(to, 0.5f).approx_equal({ 2.0f, 3.0f }));
        TEST_ASSERT(from.lerp(to, 0.25f).approx_equal({ 1.5f, 2.0f }));
        TEST_ASSERT(from.lerp(to, 0.75f).approx_equal({ 2.5f, 4.0f }));
    }

    test_section("lerp_clamped");
    {
        constexpr nnm::Point2 from { 1.0f, 1.0f };
        constexpr nnm::Point2 to { 3.0f, 5.0f };
        constexpr auto result = from.lerp_clamped(to, 0.0f);
        TEST_ASSERT(result.approx_equal({ 1.0f, 1.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 1.0f).approx_equal({ 3.0f, 5.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 0.5f).approx_equal({ 2.0f, 3.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 0.25f).approx_equal({ 1.5f, 2.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 0.75f).approx_equal({ 2.5f, 4.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 5.0f).approx_equal({ 3.0f, 5.0f }));
        TEST_ASSERT(from.lerp_clamped(to, -5.0f).approx_equal({ 1.0f, 1.0f }));
    }

    test_section("angle_to");
    {
        nnm::Point2 p1 { 2.0f, -3.0f };
        nnm::Point2 p2 { -4.0f, 5.0f };
        TEST_ASSERT(nnm::approx_equal(p1.angle_to(p2), 2.21429744f));
    }

    test_section("translate");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr nnm::Vector2 v1 { -4.0f, 5.0f };
        constexpr auto result = p1.translate(v1);
        TEST_ASSERT(result.approx_equal({ -2.0f, 2.0f }));
    }

    constexpr nnm::Point2 origin { -3.0f, 1.0f };

    test_section("scale");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        constexpr auto result = p1.scale({ 1.5f, -2.0f });
        TEST_ASSERT(result.approx_equal({ 3.0f, 6.0f }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr auto result = p1.scale_at(origin, { 1.5f, -2.0f });
        TEST_ASSERT(result.approx_equal({ 4.5f, 9.0f }));
    }

    test_section("rotate");
    {
        nnm::Point2 p1 { 2.0f, -3.0f };
        TEST_ASSERT(p1.rotate(nnm::pi<float>() / 4.0f).approx_equal({ 3.53553f, -0.707107f }));
    }

    test_section("rotate_at");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        TEST_ASSERT(p1.rotate_at(origin, nnm::pi<float>() / 4.0f).approx_equal({ 3.36396f, 1.707107f }));
    }

    test_section("shear_x");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        constexpr auto result = p1.shear_x(0.5f);
        TEST_ASSERT(result.approx_equal({ 0.5f, -3.0f }));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr auto result = p1.shear_x_at(origin, 0.5f);
        TEST_ASSERT(result.approx_equal({ 0.0f, -3.0f }));
    }

    test_section("shear_y");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr auto result = p1.shear_y(-0.5f);
        TEST_ASSERT(result.approx_equal({ 2.0f, -4.0f }));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr auto result = p1.shear_y_at(origin, -0.5f);
        TEST_ASSERT(result.approx_equal({ 2.0f, -5.5f }));
    }

    test_section("transform(const Basis2&)");
    {
        constexpr nnm::Point2f v1 { 2.0f, -3.0f };
        constexpr nnm::Basis2f basis({ { 1.0f, -2.0f }, { -4.0f, 1.2f } });
        constexpr auto result = v1.transform(basis);
        TEST_ASSERT(result.approx_equal({ 14.0f, -7.6f }));
    }

    test_section("transform_at(const Vector2&, const Basis2&)");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr nnm::Basis2f basis { { { 1.0f, -2.0f }, { -4.0f, 1.2f } } };
        constexpr auto result = p1.transform_at(origin, basis);
        TEST_ASSERT(result.approx_equal({ 18.0f, -13.8f }));
    }

    test_section("transform(const Transform2&)");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        constexpr nnm::Transform2f transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
        constexpr auto result = p1.transform(transform);
        TEST_ASSERT(result.approx_equal({ 17.0f, -2.8f }));
    }

    test_section("transform_at(const Vector3&, const Transform2&, Real)");
    {
        constexpr nnm::Point2 p1 { 2.0f, -3.0f };
        constexpr nnm::Transform2f transform { { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } } };
        constexpr auto result = p1.transform_at(origin, transform);
        TEST_ASSERT(result.approx_equal({ 21.0f, 2.6f }));
    }

    test_section("approx_equal");
    {
        constexpr nnm::Point2f p1 { 1.0f, 1.0f };
        constexpr nnm::Point2f p2 { 1.0f + nnm::epsilon<float>() / 2.0f, 1.0f };
        constexpr auto result = p1.approx_equal(p2);
        TEST_ASSERT(result);
        nnm::Point2f p3 { 1.0f, 1.0f };
        nnm::Point2f p4 { 1.0f + 2.0f * nnm::epsilon<float>(), 1.0f };
        TEST_ASSERT_FALSE(p3.approx_equal(p4));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Point2f p1 { 0.0f, 0.0f };
        constexpr auto result = p1.approx_zero();
        TEST_ASSERT(result);
        nnm::Point2f p2 { nnm::epsilon<float>(), 0.0f };
        TEST_ASSERT(p2.approx_zero());
        nnm::Point2f p3 { 0.0f, nnm::epsilon<float>() };
        TEST_ASSERT(p3.approx_zero());
        nnm::Point2f p4 { 0.1f, 0.1f };
        TEST_ASSERT_FALSE(p4.approx_zero());
    }

    test_section("begin");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        TEST_ASSERT(p1.begin() == &p1.x);
    }

    test_section("end");
    {
        nnm::Point2f p1 { 2.0f, -3.0f };
        TEST_ASSERT(p1.end() == &p1.y + 1);
    }

    test_section("at");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        constexpr auto result = p1.at(0);
        TEST_ASSERT(result == 2.0f);
        TEST_ASSERT(p1.at(1) == -3.0f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Point2f p1 { 2.0f, -3.0f };
        constexpr auto result = p1[0];
        TEST_ASSERT(result == 2.0f);
        TEST_ASSERT(p1[1] == -3.0f);
    }

    constexpr nnm::Point2f p1 { 1.0f, 2.0f };
    constexpr nnm::Point2f p2 { 3.0f, 4.0f };
    constexpr nnm::Point2f p3 { 1.0f, 2.0f };

    test_section("operator==");
    {
        constexpr auto result = p1 == p3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(p1 == p2);
    }

    test_section("operator!=");
    {
        constexpr auto result = p1 != p3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(p1 != p2);
    }

    test_section("operator+");
    {
        constexpr nnm::Point2f p { 1.0f, -2.0f };
        constexpr nnm::Vector2f v { -4.0f, 3.0f };
        constexpr nnm::Point2f result = p + v;
        TEST_ASSERT(result.approx_equal({ -3.0f, 1.0f }));
    }

    test_section("operator+=");
    {
        nnm::Point2f p { 1.0f, -2.0f };
        constexpr nnm::Vector2f v { -4.0f, 3.0f };
        p += v;
        TEST_ASSERT(p.approx_equal({ -3.0f, 1.0f }));
    }

    test_section("operator-");
    {
        constexpr nnm::Point2f p4 { 1.0f, -2.0f };
        constexpr nnm::Point2f p5 { -4.0f, 3.0f };
        constexpr nnm::Vector2f result = p4 - p5;
        TEST_ASSERT(result.approx_equal({ 5.0f, -5.0f }));
    }

    test_section("operator-(const Vector2&)");
    {
        constexpr nnm::Point2f p { 1.0f, -2.0f };
        constexpr nnm::Vector2f v { -4.0f, 3.0f };
        constexpr nnm::Point2f result = p - v;
        TEST_ASSERT(result.approx_equal({ 5.0f, -5.0f }));
    }

    test_section("operator-=");
    {
        nnm::Point2f p { 1.0f, -2.0f };
        constexpr nnm::Vector2f v { -4.0f, 3.0f };
        p -= v;
        TEST_ASSERT(p.approx_equal({ 5.0f, -5.0f }));
    }

    test_section("operator<");
    {
        constexpr nnm::Point2f a { 1.0f, 2.0f };
        constexpr nnm::Point2f b { 3.0f, 4.0f };
        constexpr nnm::Point2f c { 1.0f, 5.0f };
        TEST_ASSERT(a < b);
        TEST_ASSERT(a < c);
        TEST_ASSERT_FALSE(c < a);
        TEST_ASSERT_FALSE(b < a);
    }

    test_section("operator bool");
    {
        constexpr nnm::Point2f p { 1.0f, 2.0f };
        constexpr auto result = static_cast<bool>(p);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Point2f(0.0f, 0.0f)));
    }

    test_section("to_vector explicit conversion path");
    {
        constexpr nnm::Point2f p { 1.0f, -2.0f };
        constexpr nnm::Vector2f result = p.to_vector();
        TEST_ASSERT(result.approx_equal({ 1.0f, -2.0f }));
    }

    test_section("mutable begin/end");
    {
        nnm::Point2f p { 2.0f, -3.0f };
        TEST_ASSERT(p.begin() == &p.x);
        TEST_ASSERT(p.end() == &p.y + 1);
    }

    test_section("mutable at/operator[]");
    {
        nnm::Point2f p { 2.0f, -3.0f };
        p.at(0) = 4.0f;
        p[1] = -5.0f;
        TEST_ASSERT(p.approx_equal({ 4.0f, -5.0f }));
    }
}
