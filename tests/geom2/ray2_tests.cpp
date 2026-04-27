#include "tests.hpp"

void ray2_tests()
{
    test_case("Ray2");

    test_section("Line2()");
    {
        constexpr nnm::Ray2f ray { };
        TEST_ASSERT(ray.origin == nnm::Point2f::zero());
        TEST_ASSERT(ray.direction == nnm::Vector2f(1.0f, 0.0f));
    }

    test_section("Ray2(const Vector2&, const Vector2&)");
    {
        constexpr nnm::Ray2f ray { { 1.0f, -2.0f }, { 1.0f, -3.0f } };
        TEST_ASSERT(ray.origin == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(ray.direction.approx_equal({ 1.0f, -3.0f }));
    }

    test_section("Ray2(const Ray2<Other>&)");
    {
        constexpr nnm::Ray2d ray1 { { 1.0, -2.0 }, { 1.0, -3.0 } };
        constexpr nnm::Ray2f ray2 { ray1 };
        TEST_ASSERT(ray2.origin.approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(ray2.direction.approx_equal({ 1.0f, -3.0f }));
    }

    test_section("from_point_to_point");
    {
        constexpr nnm::Point2f p1 { 1.0f, -2.0f };
        constexpr nnm::Point2f p2 { -4.0f, 10.0f };
        const auto ray = nnm::Ray2f::from_point_to_point(p1, p2);
        TEST_ASSERT(ray.contains(p1));
        TEST_ASSERT(ray.contains(p2));
    }

    constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };

    test_section("normalize");
    {
        const auto ray2 = nnm::Ray2f { { 1.0f, -2.0f }, { -10.0f, 8.0f } }.normalize();
        TEST_ASSERT(ray2.origin == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(ray2.direction.approx_equal(nnm::Vector2f { -10.0f, 8.0f }.normalize()));
    }

    constexpr nnm::Ray2f ray2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };

    test_section("collinear(const Vector2&)");
    {
        constexpr auto result = ray2.collinear({ 5.0f, 2.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(ray2.collinear({ 2.0f, -1.0f }));
        TEST_ASSERT_FALSE(ray1.collinear({ 5.0f, 2.0f }));
    }

    test_section("collinear(const Line2&)");
    {
        constexpr nnm::Line2f line2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };
        constexpr auto result = nnm::Ray2f { { 5.0f, 2.0f }, { -0.70710678f, -0.70710678f } }.collinear(line2);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        TEST_ASSERT_FALSE(nnm::Ray2f({ 5.0f, 2.0f }, { -0.70710678f, -0.70710678f }).collinear(line1));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 5.0f, 2.0f }, { 0.0f, 1.0f }).collinear(line2));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 3.0f, 3.0f }, { -0.70710678f, -0.70710678f }).collinear(line2));
    }

    test_section("collinear(const Ray2&)");
    {
        constexpr auto result = ray2.collinear(nnm::Ray2f { { 6.0f, 3.0f }, { -0.70710678f, -0.70710678f } });
        TEST_ASSERT(result);
        TEST_ASSERT(ray2.collinear(nnm::Ray2f { { 2.0f, -1.0f }, { -0.70710678f, -0.70710678f } }))
        TEST_ASSERT_FALSE(ray2.collinear(ray1));
        TEST_ASSERT_FALSE(ray2.collinear(nnm::Ray2f { { 2.0f, -1.0f }, { 0.70710678f, -0.70710678f } }));
        TEST_ASSERT_FALSE(ray2.collinear(nnm::Ray2f { { 2.0f, -3.0f }, { -0.70710678f, -0.70710678f } }));
    }

    test_section("collinear(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Ray2f r1 { { 3.0f, -5.0f }, { -0.5547f, 0.83205f } };
        constexpr auto result = r1.collinear(s1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { 0.0f, -0.5f }, { 0.5547f, -0.83205f } };
        TEST_ASSERT(r2.collinear(s1));
        constexpr nnm::Ray2f r3 { { 3.0f, -0.5f }, { 0.5547f, -0.83205f } };
        TEST_ASSERT_FALSE(r3.collinear(s1));
    }

    test_section("contains");
    {
        constexpr auto result = ray1.contains({ 1.0f, -2.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(ray1.contains({ 0.999999f, -2.0000001f }));
        TEST_ASSERT_FALSE(ray1.contains({ 20.0f, 2.0f }));
        TEST_ASSERT_FALSE(ray1.contains({ 2.25f, -5.0f }));
    }

    test_section("signed_distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(ray2.signed_distance({ 0.0f, 0.0f }), 3.0f));
        TEST_ASSERT(nnm::approx_equal(ray2.signed_distance({ -3.0f, 5.0f }), 7.8102496759f));
        TEST_ASSERT(nnm::approx_equal(ray2.signed_distance({ 5.0f, 0.0f }), -1.4142135624f));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(ray2.distance({ 0.0f, 0.0f }), 3.0f));
        TEST_ASSERT(nnm::approx_equal(ray2.distance({ -3.0f, 5.0f }), 7.8102496759f));
        TEST_ASSERT(nnm::approx_equal(ray2.distance({ 5.0f, 0.0f }), 1.4142135624f));
    }

    test_section("distance(const Line2&)");
    {
        TEST_ASSERT(nnm::approx_zero(ray2.distance(nnm::Line2f::axis_x_offset(1.0f))));
        TEST_ASSERT(
            nnm::approx_equal(ray2.distance(nnm::Line2f::from_points({ 2.0f, 1.0f }, { 1.0f, 0.0f })), 1.4142135624f));
        TEST_ASSERT(
            nnm::approx_equal(ray2.distance(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, -1.0f })), 1.4142135624f));
    }

    test_section("distance(const Ray2&)");
    {
        TEST_ASSERT(nnm::approx_zero(ray2.distance(nnm::Ray2f { { 0.0f, 1.0f }, { 1.0f, 0.0f } })));
        TEST_ASSERT(
            nnm::approx_equal(
                ray2.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 2.0f, 1.0f })), 1.4142135624f));
        TEST_ASSERT(
            nnm::approx_equal(ray2.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, -1.0f })), 2.0f));
        TEST_ASSERT(
            nnm::approx_equal(
                ray2.distance(nnm::Ray2f::from_point_to_point({ 3.0f, 2.0f }, { 1.0f, 2.0f })), 1.4142135624f));
    }

    test_section("distance(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        TEST_ASSERT(nnm::approx_zero(nnm::Ray2f { { 1.0f, 2.0f }, { -1.0f, 0.0f } }.distance(s1)));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, -1.0f } }.distance(s1), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, 1.0f } }.distance(s1), 3.60555127f));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f { { 1.0f, 5.0f }, { -1.0f, 0.0f } }.distance(s1), 1.0f))
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f { { 1.0f, 5.0f }, { 1.0f, 0.0f } }.distance(s1), 3.88290137f));
        TEST_ASSERT(
            nnm::approx_equal(
                nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { 3.0f, -1.0f }).distance(s1), 2.21880078f))
        TEST_ASSERT(
            nnm::approx_equal(nnm::Ray2f::from_point_to_point({ 3.0f, -2.0f }, { 4.0f, -3.0f }).distance(s1), 2.0f));
        TEST_ASSERT(
            nnm::approx_equal(
                nnm::Ray2f::from_point_to_point({ -4.0f, 5.0f }, { -5.0f, 4.0f }).distance(s1), 1.4142135624f));
    }

    test_section("distance(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_zero(nnm::Ray2f({ -4.0f, 0.0f }, { 1.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f({ -4.0f, 0.0f }, { -1.0f, 0.0f }).distance(c1), 1.7082039f));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f({ 0.0f, 3.0f }, { 1.0f, 0.0f }).distance(c1), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f({ 0.0f, 3.0f }, { -1.0f, 0.0f }).distance(c1), 1.32455532f));
    }

    test_section("distance(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        const auto d1 = nnm::Ray2f::from_point_to_point({ -2.0f, 1.0f }, { 1.0f, 2.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { -2.0f, 1.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = nnm::Ray2f::from_point_to_point({ 0.0f, 1.0f }, { 1.0f, 1.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.447214f));
        const auto d4 = nnm::Ray2f::from_point_to_point({ 1.0f, 1.0f }, { 0.0f, 1.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = nnm::Ray2f::from_point_to_point({ -4.0f, -5.0f }, { -2.0f, -4.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.447214f));
        const auto d6 = nnm::Ray2f::from_point_to_point({ -3.0f, -4.5f }, { -2.5f, -5.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d6, 0.5f));
    }

    test_section("distance(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Ray2f::from_point_to_point({ 0.5f, -1.5f }, { 1.0f, -1.0f }).distance(r1)));
        const auto d1 = nnm::Ray2f::from_point_to_point({ 1.0f, 0.5f }, { 3.0f, -1.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.271538854f));
        TEST_ASSERT(nnm::approx_equal(nnm::Ray2f({ 1.0f, 0.5f }, { 0.0f, 1.0f }).distance(r2), 0.5f));
        const auto d2 = nnm::Ray2f::from_point_to_point({ 1.0f, 4.5f }, { 1.5f, 5.0f }).distance(r2);
        TEST_ASSERT(nnm::approx_equal(d2, 0.7071067812f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Ray2f::from_point_to_point({ 2.0f, 1.0f }, { 2.f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Ray2f::from_point_to_point({ 2.0f, 2.0f }, { 3.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d2, 1.0f));
        const auto d3 = nnm::Ray2f::from_point_to_point({ 3.0f, 2.0f }, { 2.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Ray2f::from_point_to_point({ 2.0f, 3.0f }, { 1.0f, 4.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
    }

    test_section("parallel(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr nnm::Ray2f r1 { { 100.0f, -100.0f }, { -0.384615391f, 0.923076928f } };
        constexpr auto result = r1.parallel(line1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { 100.0f, -100.0f }, { 0.384615391f, -0.923076928f } };
        TEST_ASSERT(r2.parallel(line1))
        constexpr nnm::Ray2f r3 { { 1.0f, -2.0f }, { 0.923076928f, 0.384615391f } };
        TEST_ASSERT_FALSE(r3.parallel(line1));
    }

    test_section("parallel(const Ray2&)");
    {
        constexpr auto result = ray1.parallel(ray2);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(ray2.parallel(nnm::Ray2f { { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
        TEST_ASSERT(ray2.parallel(nnm::Ray2f { { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
    }

    test_section("parallel(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Ray2f r1 { { 0.0f, 4.0f }, { 0.554699f, -0.832051f } };
        constexpr auto result = r1.parallel(s1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { -0.2f, -0.2f }, { -0.554699f, -0.832051f } };
        TEST_ASSERT_FALSE(r2.parallel(s1));
    }

    test_section("perpendicular(const Line2&)");
    {
        constexpr auto result
            = ray1.perpendicular(nnm::Line2f { { -100.0f, 100.0f }, { -0.923076928f, -0.384615391f } });
        TEST_ASSERT(result);
        TEST_ASSERT(ray1.perpendicular(nnm::Line2f { { -100.0f, 100.0f }, { 0.923076928f, 0.384615391f } }));
        TEST_ASSERT_FALSE(ray1.perpendicular(nnm::Line2f { { 1000.0f, 0.0f }, { -0.384615391f, 0.923076928f } }));
    }

    test_section("perpendicular(const Ray2&)");
    {
        constexpr auto result = ray1.perpendicular(ray2);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(ray2.perpendicular(nnm::Ray2f { { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
        TEST_ASSERT(ray2.perpendicular(nnm::Ray2f { { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
    }

    test_section("perpendicular(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Ray2f r1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
        constexpr auto result = r1.perpendicular(s1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(r2.perpendicular(s1));
    }

    test_section("intersects(const Line2&)");
    {
        constexpr nnm::Ray2f ray3 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
        constexpr auto result = ray3.intersects(line3);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
        TEST_ASSERT_FALSE(ray3.intersects(line4));
    }

    test_section("intersection(const Line2&)");
    {
        constexpr nnm::Ray2f ray4 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
        constexpr auto result = ray4.intersection(line3);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
        constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
        TEST_ASSERT_FALSE(ray4.intersection(line4).has_value());
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr auto result = ray1.intersects(ray2);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Ray2f ray3 { { 0.0f, 10.0f }, { 0.70710678f, -0.70710678f } };
        TEST_ASSERT(ray2.intersects(ray3));
    }

    test_section("intersection(const Ray2&)");
    {
        constexpr auto result = ray1.intersection(ray2);
        TEST_ASSERT_FALSE(result.has_value());
        constexpr nnm::Ray2f ray3 { { 0.0f, 10.0f }, { 0.70710678f, -0.70710678f } };
        TEST_ASSERT(ray2.intersection(ray3).has_value());
        TEST_ASSERT(ray2.intersection(ray3).value().approx_equal({ 6.5f, 3.5f }));
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Ray2f ray3 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
        constexpr auto result = ray3.intersects(s1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f ray4 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(ray4.intersects(s1));
    }

    test_section("intersection(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Ray2f ray3 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
        constexpr auto result = ray3.intersection(s1);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
        constexpr nnm::Ray2f ray4 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(ray4.intersection(s1).has_value());
    }

    test_section("intersects(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Ray2f r1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result = r1.intersects(c1);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Ray2f r2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
        TEST_ASSERT(r2.intersects(c1));
        constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(ray3.intersects(c1));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersects(c1));
        TEST_ASSERT(nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, -1.0f }).intersects(c1));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 0.0f, 100.0f }, { 1.0f, .0f }).intersects(c1));
        constexpr nnm::Ray2f ray4 { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } };
        TEST_ASSERT(ray4.intersects(c1));
    }

    test_section("edge_intersections(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Ray2f r1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result1 = r1.edge_intersections(c1);
        TEST_ASSERT(result1.empty());
        constexpr nnm::Ray2f r2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
        const auto result2 = r2.edge_intersections(c1);
        TEST_ASSERT(result2.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        const auto result3 = ray3.edge_intersections(c1);
        TEST_ASSERT(result3.empty());
        const auto result4 = nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).edge_intersections(c1);
        TEST_ASSERT(result4.empty());
        const auto result5 = nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, -1.0f }).edge_intersections(c1);
        TEST_ASSERT(result5.approx_equal({ { 0.0f, -7.58257294f }, { 0.0f, 1.58257294f } }));
        const auto result6 = nnm::Ray2f({ 0.0f, 100.0f }, { 1.0f, 0.0f }).edge_intersections(c1);
        TEST_ASSERT(result6.empty());
        const auto result7 = nnm::Ray2f({ 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f }).edge_intersections(c1);
        TEST_ASSERT(result7.approx_equal({ { 6.0f, -6.0f } }));
    }

    test_section("intersects(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        constexpr auto result = nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }.intersects(tri1);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::Ray2f({ -3.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Ray2f({ 0.0f, 0.0f }, { -1.0f, 0.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Ray2f({ 0.0f, 0.0f }, { -1.0f, 0.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri2));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri1));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri2));
    }

    test_section("edge_intersections(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        const auto result1 = nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result1.approx_equal({ { -1.0f, 0.0f } }));
        const auto result2 = nnm::Ray2f({ -3.0f, 0.0f }, { 1.0f, 0.0f }).edge_intersections(tri2);
        TEST_ASSERT(result2.approx_equal({ { -1.0f, 0.0f } }));
        const auto result3 = nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result3.approx_equal({ { -3.6666667f, 0.0f }, { -1.0f, 0.0f } }));
        const auto result4 = nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }).edge_intersections(tri1);
        TEST_ASSERT(result4.approx_equal({ { -1.8571429f, 2.8571429f }, { -0.3333333f, 1.3333333f } }));
        const auto result5 = nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }).edge_intersections(tri2);
        TEST_ASSERT(result5.approx_equal({ { -3.9411765f, 1.64705882f }, { -0.7142857f, 0.57142857f } }));
        const auto result6 = nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).edge_intersections(tri1);
        TEST_ASSERT(result6.approx_equal({ { 1.0f, 4.0f } }));
        const auto result7 = nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).edge_intersections(tri2);
        TEST_ASSERT(result7.approx_equal({ { 1.0f, 4.0f } }));
        const auto result8 = nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result8.empty());
        const auto result9 = nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }.edge_intersections(tri2);
        TEST_ASSERT(result9.empty());
    }

    test_section("intersects(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        TEST_ASSERT(nnm::Ray2f({ -0.5f, 0.0f }, { 1.0f, 0.0f }).intersects(r1));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 2.0f, -0.5f }, { 1.0f, 0.0f }).intersects(r1));
        TEST_ASSERT(nnm::Ray2f({ -1.5f, 3.0f }, { -1.0f, 0.0f }).intersects(r2));
        TEST_ASSERT(nnm::Ray2f({ 4.0f, 0.0f }, { 0.0f, -1.0f }).intersects(r3));
        TEST_ASSERT_FALSE(nnm::Ray2f({ 4.0f, -2.0f }, { 0.0f, 1.0f }).intersects(r3));
    }

    test_section("edge_intersections(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        const auto i1 = nnm::Ray2f({ -0.5f, 0.0f }, { 1.0f, 0.0f }).edge_intersections(r1);
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f }, { 0.535898447f, 0.0f } }));
        const auto i2 = nnm::Ray2f({ 2.0f, -0.5f }, { 1.0f, 0.0f }).edge_intersections(r1);
        TEST_ASSERT(i2.empty());
        const auto i3 = nnm::Ray2f({ -1.5f, 3.0f }, { 1.0f, 0.0f }).edge_intersections(r2);
        TEST_ASSERT(i3.approx_equal({ { 0.5f, 3.0f } }));
        const auto i4 = nnm::Ray2f({ 4.0f, 0.0f }, { 0.0f, -1.0f }).edge_intersections(r3);
        TEST_ASSERT(i4.approx_equal({ { 4.0f, -3.5f }, { 4.0f, -2.5f } }));
        const auto i5 = nnm::Ray2f({ 4.0f, -2.0f }, { 0.0f, 1.0f }).edge_intersections(r3);
        TEST_ASSERT(i5.empty());
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT_FALSE(nnm::Ray2f::from_point_to_point({ 2.0f, 1.0f }, { 2.0f, 2.0f }).intersects(a1));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ -3.0f, 2.0f }, { 2.0f, 1.0f }).intersects(a1));
        TEST_ASSERT(nnm::Ray2f::from_point_to_point({ -1.0f, 1.0f }, { -1.0f, 2.0f }).intersects(a1));
    }

    test_section("edge_intersections(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto i1 = nnm::Ray2f::from_point_to_point({ 2.0f, 1.0f }, { 2.0f, 2.0f }).edge_intersections(a1);
        TEST_ASSERT(i1.empty());
        const auto i2 = nnm::Ray2f::from_point_to_point({ -3.0f, 2.0f }, { 2.0f, 1.0f }).edge_intersections(a1);
        TEST_ASSERT(i2.approx_equal({ { -2.0f, 1.8f }, { 1.0f, 1.2f } }));
        const auto i3 = nnm::Ray2f::from_point_to_point({ -1.0f, 1.0f }, { -1.0f, 2.0f }).edge_intersections(a1);
        TEST_ASSERT(i3.approx_equal({ { -1.0f, 3.0f } }));
    }

    test_section("tangent(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Ray2f r1 { { 0.0f, 2.0f }, { 1.0f, 0.0f } };
        constexpr auto result = r1.tangent(c1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { 0.0f, 2.0f }, { -1.0f, 0.0f } };
        TEST_ASSERT_FALSE(r2.tangent(c1));
        const auto r3 = nnm::Ray2f::from_point_to_point({ 0.0f, 2.0f }, { 2.0f, 0.0f });
        TEST_ASSERT_FALSE(r3.tangent(c1));
        constexpr nnm::Ray2f r4 { { 2.0f, 2.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(r4.tangent(c1));
        constexpr nnm::Ray2f r5 { { 2.0f, 2.0f }, { 0.0f, -1.0f } };
        TEST_ASSERT_FALSE(r5.tangent(c1));
    }

    test_section("project");
    {
        constexpr nnm::Ray2f r { { 1.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
        constexpr auto result = r.project({ 2.0f, 3.0f });
        TEST_ASSERT(result.approx_equal({ -1.0f, 1.0f }));
        TEST_ASSERT(r.project({ 5.0f, -5.0f }).approx_equal({ 1.0f, -2.0f }));
    }

    constexpr nnm::Ray2f ray3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

    test_section("translate");
    {
        constexpr nnm::Ray2f result = ray3.translate({ -2.0f, 3.0f });
        TEST_ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
        TEST_ASSERT(result.direction.approx_equal(ray3.direction));
    }
    test_section("scale_at");
    {
        const auto result = ray3.scale_at({ 2.0f, -1.5f }, { -2.0f, 0.7f });
        TEST_ASSERT(result.origin.approx_equal({ 0.0f, -1.15f }));
        TEST_ASSERT(result.direction.approx_equal({ -0.943858f, 0.330351f }));
    }

    test_section("scale");
    {
        const nnm::Ray2f result = ray3.scale({ -2.0f, 3.0f });
        TEST_ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
        TEST_ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
    }

    test_section("rotate_at");
    {
        const auto result = ray3.rotate_at({ 2.0f, -1.5f }, nnm::pi<float>() / 5.0f);
        TEST_ASSERT(result.origin.approx_equal({ 2.515124f, -0.507706f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.156434f, 0.987688f }));
    }

    test_section("rotate");
    {
        const auto result = ray3.rotate(nnm::pi<float>() / 5.0f);
        TEST_ASSERT(result.origin.approx_equal({ 3.01484f, 0.954339f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.156434f, 0.987688f }));
    }

    test_section("shear_x_at");
    {
        const auto result = ray3.shear_x_at({ 2.0f, -1.5f }, 0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 3.25f, -1.0f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.83205f, 0.5547f }));
    }

    test_section("shear_x");
    {
        const nnm::Ray2f result = ray3.shear_x(0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 2.5f, -1.0f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.83205f, 0.5547f }));
    }

    test_section("shear_y_at");
    {
        const auto result = ray3.shear_y_at({ 2.0f, -1.5f }, 0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 3.0f, -0.5f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.5547f, 0.83205f }));
    }

    test_section("shear_y");
    {
        const nnm::Ray2f result = ray3.shear_y(0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 3.0f, 0.5f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.5547f, 0.83205f }));
    }

    test_section("operator<");
    {
        constexpr auto result = ray1 < ray2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(ray2 < ray1);
    }

    test_section("operator==");
    {
        constexpr auto result = ray1 == ray2;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(ray1 == ray1);
    }

    test_section("operator!=");
    {
        constexpr auto result = ray1 != ray2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(ray1 != ray1);
    }
}

