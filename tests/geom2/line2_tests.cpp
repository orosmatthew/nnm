#include "tests.hpp"

void line2_tests()
{
    test_case("Line2");

    test_section("Line2()");
    {
        constexpr nnm::Line2f line { };
        TEST_ASSERT(line.origin == nnm::Point2f::zero());
        TEST_ASSERT(line.direction == nnm::Vector2f(1.0f, 0.0f));
    }

    test_section("Line2(const Vector2&, const Vector2&)");
    {
        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { 1.0f, -3.0f } };
        TEST_ASSERT(line1.origin == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(line1.direction.approx_equal({ 1.0f, -3.0f }));
    }

    test_section("Line2(const Line2<Other>&)");
    {
        constexpr nnm::Line2d line1 { { 1.0, -2.0 }, { 1.0, -3.0 } };
        constexpr nnm::Line2f line2 { line1 };
        TEST_ASSERT(line1.origin.approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(line2.direction.approx_equal({ 1.0f, -3.0f }));
    }

    test_section("from_points");
    {
        constexpr nnm::Point2f p1 { 1.0f, -2.0f };
        constexpr nnm::Point2f p2 { -4.0f, 10.0f };
        const auto line = nnm::Line2f::from_points(p1, p2);
        TEST_ASSERT(line.contains(p1));
        TEST_ASSERT(line.contains(p2));
    }

    test_section("from_segment");
    {
        constexpr nnm::Segment2f s { { -1.0f, 2.0f }, { -4.0f, 10.0f } };
        const auto line = nnm::Line2f::from_segment(s);
        TEST_ASSERT(line.origin == nnm::Point2f(-1.0f, 2.0f));
        TEST_ASSERT(line.direction.approx_equal({ -0.3511234416f, 0.9363291776f }));
    }

    test_section("from_ray");
    {
        constexpr nnm::Ray2f r { { -1.0f, 2.0f }, { -0.3713906764f, 0.9284766909f } };
        constexpr auto line = nnm::Line2f::from_ray(r);
        TEST_ASSERT(line.origin == nnm::Point2f(-1.0f, 2.0f));
        TEST_ASSERT(line.direction.approx_equal({ -0.3713906764f, 0.9284766909f }))
    ;}

    test_section("from_tangent(const Circle&, Real)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        const auto l1 = nnm::Line2f::from_tangent(c1, 0.0f);
        TEST_ASSERT(l1.origin.approx_equal({ 7.0f, -3.0f }));
        TEST_ASSERT(nnm::approx_zero(l1.direction.cross({ 0.0f, 1.0f })));
        TEST_ASSERT(l1.tangent(c1));
        const auto l2 = nnm::Line2f::from_tangent(c1, nnm::pi<float>() / 3.0f);
        TEST_ASSERT(l2.origin.approx_equal({ 4.5f, 1.330127f }));
        TEST_ASSERT(l2.direction.parallel(nnm::Line2f::from_point_slope({ 0.0f, 3.9282032f }, -0.5773503f).direction));
        TEST_ASSERT(l2.tangent(c1));
    }

    test_section("axis_x");
    {
        constexpr auto line = nnm::Line2f::axis_x();
        TEST_ASSERT(line.origin == nnm::Point2f::zero());
        TEST_ASSERT(line.direction == nnm::Vector2f::axis_x());
    }

    test_section("axis_y");
    {
        constexpr auto line = nnm::Line2f::axis_y();
        TEST_ASSERT(line.origin == nnm::Point2f::zero());
        TEST_ASSERT(line.direction == nnm::Vector2f::axis_y());
    }

    test_section("axis_x_offset");
    {
        constexpr auto line = nnm::Line2f::axis_x_offset(3.0f);
        TEST_ASSERT(line.origin.approx_equal({ 0.0f, 3.0f }));
        TEST_ASSERT(line.direction.approx_equal(nnm::Vector2f::axis_x()));
    }

    test_section("axis_y_offset");
    {
        constexpr auto line = nnm::Line2f::axis_y_offset(-2.0f);
        TEST_ASSERT(line.origin.approx_equal({ -2.0f, 0.0f }));
        TEST_ASSERT(line.direction.approx_equal(nnm::Vector2f::axis_y()));
    }

    test_section("from_point_slope");
    {
        const auto line = nnm::Line2f::from_point_slope({ 1.0f, -2.0f }, -1.5f);
        TEST_ASSERT(line.origin == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(line.direction.approx_equal({ 0.5547f, -0.83205f }));
    }

    constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };

    test_section("parallel_containing");
    {
        constexpr nnm::Line2f line2 = line1.parallel_containing({ -6.0f, -5.0f });
        TEST_ASSERT(line2.contains({ -6.0f, -5.0f }));
        TEST_ASSERT(line2.parallel({ line1 }));
    }

    test_section("arbitrary_perpendicular_containing");
    {
        constexpr nnm::Line2f line2 = line1.arbitrary_perpendicular_containing({ -6.0f, -5.0f });
        TEST_ASSERT(line2.contains({ -6.0f, -5.0f }));
        TEST_ASSERT(line2.perpendicular({ line1 }));
    }

    test_section("normalize");
    {
        const auto line2 = nnm::Line2f { { 1.0f, -2.0f }, { -10.0f, 8.0f } }.normalize();
        TEST_ASSERT(line2.origin == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(line2.direction.approx_equal(nnm::Vector2f { -10.0f, 8.0f }.normalize()));
    }

    constexpr nnm::Line2f line2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };

    test_section("collinear(const Ray2&)");
    {
        constexpr auto result = line2.collinear(nnm::Ray2f { { 5.0f, 2.0f }, { -0.70710678f, -0.70710678f } });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(line1.collinear(nnm::Ray2f { { 5.0f, 2.0f }, { -0.70710678f, -0.70710678f } }));
        TEST_ASSERT_FALSE(line2.collinear(nnm::Ray2f { { 5.0f, 2.0f }, { 0.0f, 1.0f } }));
        TEST_ASSERT_FALSE(line2.collinear(nnm::Ray2f { { 3.0f, 3.0f }, { -0.70710678f, -0.70710678f } }));
    }

    test_section("collinear(const Segment2&)");
    {
        constexpr auto result = line2.collinear(nnm::Segment2f { { 4.0f, 1.0f }, { 6.0f, 3.0f } });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(line1.collinear(nnm::Segment2f { { 4.0f, 1.0f }, { 6.0f, 3.0f } }));
        TEST_ASSERT_FALSE(line2.collinear(nnm::Segment2f { { 4.0f, 1.0f }, { 6.0f, 5.0f } }));
        TEST_ASSERT_FALSE(line2.collinear(nnm::Segment2f { { 4.0f, 3.0f }, { 6.0f, 5.0f } }));
    }

    test_section("contains");
    {
        constexpr auto result = line1.contains({ 1.0f, -2.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(line1.contains({ 0.999999f, -2.0000001f }));
        TEST_ASSERT_FALSE(line1.contains({ 20.0f, 2.0f }));
    }

    test_section("distance(const Vector2&)");
    {
        constexpr auto result = line2.distance({ 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result, 2.1213203436f));
        TEST_ASSERT(nnm::approx_equal(line2.distance({ -3.0f, 5.0f }), 7.7781745931f));
        TEST_ASSERT(nnm::approx_equal(line2.distance({ 5.0f, 0.0f }), 1.4142135624f));
    }

    test_section("signed_distance");
    {
        constexpr auto result = line2.signed_distance({ 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result, 2.1213203436f));
        TEST_ASSERT(nnm::approx_equal(line2.signed_distance({ -3.0f, 5.0f }), 7.7781745931f));
        TEST_ASSERT(nnm::approx_equal(line2.signed_distance({ 5.0f, 0.0f }), -1.4142135624f));
    }

    test_section("distance(const Line2&)");
    {
        constexpr auto result = line1.distance(line2);
        TEST_ASSERT(nnm::approx_zero(result));
        TEST_ASSERT(nnm::approx_zero(line2.distance(line1)));
        constexpr nnm::Line2f line3 { { 1.0f, 0.0f }, { -0.70710678f, -0.70710678f } };
        TEST_ASSERT(nnm::approx_zero(line1.distance(line2)));
        TEST_ASSERT(nnm::approx_equal(line2.distance(line3), 1.4142135624f));
        TEST_ASSERT(nnm::approx_equal(line3.distance(line2), 1.4142135624f));
    }

    test_section("distance(const Ray2&)");
    {
        constexpr nnm::Ray2f ray2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };
        TEST_ASSERT(nnm::approx_zero(nnm::Line2f::axis_x_offset(1.0f).distance(ray2)));
        TEST_ASSERT(
            nnm::approx_equal(nnm::Line2f::from_points({ 2.0f, 1.0f }, { 1.0f, 0.0f }).distance(ray2), 1.4142135624f));
        TEST_ASSERT(
            nnm::approx_equal(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, -1.0f }).distance(ray2), 1.4142135624f));
    }

    test_section("distance(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr auto result = nnm::Line2f::axis_x_offset(2.0f).distance(s1);
        TEST_ASSERT(nnm::approx_zero(result));
        TEST_ASSERT(
            nnm::approx_equal(nnm::Line2f::from_points({ 0.0f, 3.0f }, { 1.0f, 2.0f }).distance(s1), 1.4142135624f));
        TEST_ASSERT(nnm::approx_equal(nnm::Line2f::axis_y_offset(2.0f).distance(s1), 1.0f));
        TEST_ASSERT(
            nnm::approx_equal(nnm::Line2f::from_points({ 2.0f, 0.0f }, { 0.0f, 3.0f }).distance(s1), 1.9414506868f));
    }

    test_section("distance(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Line2f::axis_x().distance(c1)));
        TEST_ASSERT(nnm::approx_zero(nnm::Line2f::axis_y().distance(c1)));
        TEST_ASSERT(nnm::approx_equal(nnm::Line2f::axis_x_offset(3.0f).distance(c1), 1.0f));
    }

    test_section("distance(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        const auto d1 = nnm::Line2f::from_points({ -2.0f, 2.0f }, { 1.0f, 1.0f }).distance(tri1);
        const auto d1n = nnm::Line2f::from_points({ -2.0f, 2.0f }, { 1.0f, 1.0f }).distance(tri2);
        TEST_ASSERT(nnm::approx_zero(d1));
        TEST_ASSERT(nnm::approx_zero(d1n));
        const auto d2 = nnm::Line2f::from_points({ 1.0f, 2.0f }, { 0.0f, -2.0f }).distance(tri1);
        const auto d2n = nnm::Line2f::from_points({ 1.0f, 2.0f }, { 0.0f, -2.0f }).distance(tri2);
        TEST_ASSERT(nnm::approx_equal(d2, 0.485071272f));
        TEST_ASSERT(nnm::approx_equal(d2n, 0.485071272f));
        const auto d3 = nnm::Line2f::from_points({ 0.0f, 0.0f }, { 1.0f, 2.0f }).distance(tri1);
        const auto d3n = nnm::Line2f::from_points({ 0.0f, 0.0f }, { 1.0f, 2.0f }).distance(tri2);
        TEST_ASSERT(nnm::approx_equal(d3, 0.894427f));
        TEST_ASSERT(nnm::approx_equal(d3n, 0.894427f));
    }

    test_section("distance(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Line2f::from_points({ 2.0f, 2.0f }, { 1.0f, 1.0f }).distance(r1)));
        TEST_ASSERT(
            nnm::approx_equal(nnm::Line2f::from_points({ 3.0f, 0.5f }, { 2.0f, 2.0f }).distance(r1), 0.819783329f));
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        TEST_ASSERT(nnm::approx_equal(nnm::Line2f({ 1.0f, 1.0f }, { 0.0f, 1.0f }).distance(r2), 0.5f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Line2f::axis_y_offset(2.0f).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Line2f::from_points({ 1.0f, 4.0f }, { 2.0f, 1.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.3162278f));
        const auto d3 = nnm::Line2f::from_points({ 2.0f, 1.0f }, { -2.0f, 4.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d3));
    }

    test_section("parallel(const Line2&)");
    {
        constexpr auto result = line1.parallel(line2);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(line2.parallel(nnm::Line2f { { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
        TEST_ASSERT(line2.parallel(nnm::Line2f { { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
    }

    test_section("parallel(const Ray2&)");
    {
        constexpr auto result = line1.parallel(nnm::Ray2f { { 100.0f, -100.0f }, { -0.384615391f, 0.923076928f } });
        TEST_ASSERT(result);
        TEST_ASSERT(line1.parallel(nnm::Ray2f { { 100.0f, -100.0f }, { 0.384615391f, -0.923076928f } }))
        ;TEST_ASSERT_FALSE(line1.parallel(
            nnm::Ray2f { { 1.0f, -2.0f },
                         {
                             0.923076928f,
                             0.384615391f,
                         } }));
    }

    test_section("parallel(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Line2f l1 { { 100.0f, -100.0f }, { -0.5547001962f, 0.8320502943f } };
        constexpr auto result = l1.parallel(s1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f l2 { { -100.0f, 100.0f }, { 0.5547001962f, -0.8320502943f } };
        TEST_ASSERT(l2.parallel(s1));
        constexpr nnm::Line2f l3 { { 1.0f, -2.0f }, { 0.8320502943f, 0.5547001962f } };
        TEST_ASSERT_FALSE(l3.parallel(s1));
    }

    test_section("perpendicular(const Line2&)");
    {
        constexpr auto result = line1.perpendicular(line2);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(line2.perpendicular(nnm::Line2f { { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
        TEST_ASSERT(line2.perpendicular(nnm::Line2f { { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
    }

    test_section("perpendicular(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr auto result
            = nnm::Line2f { { -100.0f, 100.0f }, { -0.923076928f, -0.384615391f } }.perpendicular(ray1);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::Line2f({ -100.0f, 100.0f }, { 0.923076928f, 0.384615391f }).perpendicular(ray1));
        TEST_ASSERT_FALSE(nnm::Line2f({ 1000.0f, 0.0f }, { -0.384615391f, 0.923076928f }).perpendicular(ray1));
    }

    test_section("perpendicular(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Line2f l1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
        constexpr auto result = l1.perpendicular(s1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f l2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(l2.perpendicular(s1));
    }

    test_section("unchecked_intersection");
    {
        constexpr auto result = line1.unchecked_intersection(line2);
        TEST_ASSERT(result.approx_equal({ 1.0f, -2.0f }));
    }

    test_section("intersection(const Line2&)");
    {
        constexpr auto result = line1.intersection(line2);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(line1.intersection(line2).value().approx_equal({ 1.0f, -2.0f }));
        constexpr nnm::Line2f line3 { { 100.0f, -5.0f }, { -0.70710678f, -0.70710678f } };
        TEST_ASSERT_FALSE(line2.intersection(line3).has_value());
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
        constexpr auto result = line3.intersects(ray1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
        TEST_ASSERT_FALSE(line4.intersects(ray1));
    }

    test_section("intersection(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
        constexpr auto result = line3.intersection(ray1);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
        constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
        TEST_ASSERT_FALSE(line4.intersection(ray1).has_value());
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Line2f line3 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
        constexpr auto result = line3.intersects(s1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line4 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
        TEST_ASSERT_FALSE(line4.intersects(s1));
    }

    test_section("intersection(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        constexpr nnm::Line2f line3 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
        constexpr auto result = line3.intersection(s1);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
        constexpr nnm::Line2f line4 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
        TEST_ASSERT_FALSE(line4.intersection(s1).has_value());
    }

    test_section("intersects(const Circle2&");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Line2f l1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        constexpr auto result = l1.intersects(c1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f l2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(l2.intersects(c1));
        TEST_ASSERT(nnm::Line2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersects(c1));
        TEST_ASSERT_FALSE(nnm::Line2f({ 0.0f, 100.0f }, { 1.0f, 0.0f }).intersects(c1));
    }

    test_section("edge_intersections(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Line2f l1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result1 = l1.edge_intersections(c1);
        TEST_ASSERT(result1.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Line2f l2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT(l2.edge_intersections(c1).empty());
        const auto result2 = nnm::Line2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).edge_intersections(c1);
        TEST_ASSERT(result2.approx_equal({ { 0.0f, -7.58257294f }, { 0.0f, 1.58257294f } }));
    }

    test_section("intersects(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr auto result = nnm::Line2f::axis_x().intersects(tri1);
        TEST_ASSERT(result);
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        TEST_ASSERT(nnm::Line2f::axis_x().intersects(tri2));
        TEST_ASSERT(nnm::Line2f::axis_y().intersects(tri1));
        TEST_ASSERT(nnm::Line2f::axis_y().intersects(tri2));
        TEST_ASSERT_FALSE(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersects(tri1));
        TEST_ASSERT_FALSE(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersects(tri2));
    }

    test_section("edge_intersections(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        const auto result1 = nnm::Line2f::axis_x().edge_intersections(tri1);
        TEST_ASSERT(result1.approx_equal({ { -3.666667f, 0.0f }, { -1.0f, 0.0f } }));
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        const auto result2 = nnm::Line2f::axis_x().edge_intersections(tri2);
        TEST_ASSERT(result2.approx_equal({ { -3.666667f, 0.0f }, { -1.0f, 0.0f } }));
        const auto result3 = nnm::Line2f::axis_y().edge_intersections(tri1);
        TEST_ASSERT(result3.approx_equal({ { 0.0f, 2.0f }, { 0.0f, 3.6f } }));
        const auto result4 = nnm::Line2f::axis_y().edge_intersections(tri2);
        TEST_ASSERT(result4.approx_equal({ { 0.0f, 2.0f }, { 0.0f, 3.6f } }));
        const auto result5 = nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).edge_intersections(tri1);
        TEST_ASSERT(result5.empty());
        const auto result6 = nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).edge_intersections(tri2);
        TEST_ASSERT(result6.empty());
        const auto result7 = nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).edge_intersections(tri1);
        TEST_ASSERT(result7.approx_equal({ { -3.0f, 2.4f }, { -0.538461548f, 0.923076923f } }));
        const auto result8 = nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).edge_intersections(tri2);
        TEST_ASSERT(result8.approx_equal({ { -3.0f, 2.4f }, { -0.538461548f, 0.923076923f } }));
    }

    test_section("intersects(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        TEST_ASSERT(nnm::Line2f::axis_x().intersects(r1));
        TEST_ASSERT(nnm::Line2f::axis_y().intersects(r1));
        TEST_ASSERT_FALSE(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }).intersects(r1));
        TEST_ASSERT(nnm::Line2f::axis_y().intersects(r2));
        TEST_ASSERT_FALSE(nnm::Line2f::axis_x_offset(-1.0f).intersects(r2));
        TEST_ASSERT_FALSE(nnm::Line2f::axis_x_offset(-2.0f).intersects(r3));
        TEST_ASSERT(nnm::Line2f::axis_x_offset(-3.0f).intersects(r3));
        TEST_ASSERT(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }).intersects(r3));
    }

    test_section("edge_intersections(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        const auto i1 = nnm::Line2f::axis_x().edge_intersections(r1);
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f }, { 0.535898447f, 0.0f } }));
        const auto i2 = nnm::Line2f::axis_y().edge_intersections(r1);
        TEST_ASSERT(i2.approx_equal({ { 0.0f, -3.15470052f }, { 0.0f, 0.267949343f } }));
        const auto i3 = nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }).edge_intersections(r1);
        TEST_ASSERT(i3.empty());
        const auto i4 = nnm::Line2f::axis_y().edge_intersections(r2);
        TEST_ASSERT(i4.approx_equal({ { 0.0f, 0.0f }, { 0.0f, 4.0f } }));
        const auto i5 = nnm::Line2f::axis_x_offset(-1.0f).edge_intersections(r2);
        TEST_ASSERT(i5.empty());
        const auto i6 = nnm::Line2f::axis_x_offset(-2.0f).edge_intersections(r3);
        TEST_ASSERT(i6.empty());
        const auto i7 = nnm::Line2f::axis_x_offset(-3.0f).edge_intersections(r3);
        TEST_ASSERT(i7.approx_equal({ { 1.5f, -3.0f }, { 6.5f, -3.0f } }));
        const auto i8 = nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }).edge_intersections(r3);
        TEST_ASSERT(i8.approx_equal({ { 5.0f, -2.5f }, { 6.333333f, -3.5f } }));
    }

    test_section("tangent(const Circle2&)");
    {
        constexpr nnm::Circle2f circle { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Line2f line3 { { -2.0f, 2.0f }, { -1.0f, 0.0f } };
        constexpr auto result = line3.tangent(circle);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(line1.tangent(circle));
    }

    test_section("project");
    {
        constexpr auto result = line1.project({ 5.0f, 3.0f });
        TEST_ASSERT(result.approx_equal({ -0.18343f, 0.84024f }));
    }

    test_section("unchecked_slope");
    {
        constexpr auto result = line1.unchecked_slope();
        TEST_ASSERT(nnm::approx_equal(result, -2.4f));
    }

    test_section("slope");
    {
        constexpr auto result = line1.slope();
        TEST_ASSERT(result.has_value() && nnm::approx_equal(result.value(), -2.4f));
        TEST_ASSERT_FALSE(nnm::Line2f::axis_y_offset(-3.0f).slope().has_value());
    }

    test_section("coincident");
    {
        constexpr auto result = line1.coincident(line2);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Line2f line3 { { 0.0f, -3.0f }, { -0.70710678f, -0.70710678f } };
        TEST_ASSERT(line2.coincident(line3));
    }

    constexpr nnm::Line2f line3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

    test_section("translate");
    {
        constexpr nnm::Line2f result = line3.translate({ -2.0f, 3.0f });
        TEST_ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
        TEST_ASSERT(result.direction.approx_equal(line3.direction));
    }

    test_section("scale_at");
    {
        const auto result = line3.scale_at({ -2.0f, 3.0f }, { 3.0f, -0.5f });
        TEST_ASSERT(result.origin.approx_equal({ 13.0f, 5.0f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.986394f, -0.164399f }));
    }

    test_section("scale");
    {
        const nnm::Line2f result = line3.scale({ -2.0f, 3.0f });
        TEST_ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
        TEST_ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
    }

    test_section("rotate_at");
    {
        const nnm::Line2f result = line3.rotate_at({ -1.5f, 2.0f }, nnm::pi<float>() / 3.0f);
        TEST_ASSERT(result.origin == line3.origin.rotate_at({ -1.5f, 2.0f }, nnm::pi<float>() / 3.0f));
        TEST_ASSERT(result.direction == line3.direction.rotate(nnm::pi<float>() / 3.0f));
    }

    test_section("rotate");
    {
        const nnm::Line2f result = line3.rotate(nnm::pi<float>() / 3.0f);
        TEST_ASSERT(result.origin == line3.origin.rotate(nnm::pi<float>() / 3.0f));
        TEST_ASSERT(result.direction == line3.direction.rotate(nnm::pi<float>() / 3.0f));
    }

    test_section("shear_x_at");
    {
        const auto result = line3.shear_x_at({ -2.0f, 3.0f }, 0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 1.0f, -1.0f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.83205f, 0.5547f }))
    ;}

    test_section("shear_x");
    {
        const nnm::Line2f result = line3.shear_x(0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 2.5f, -1.0f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.83205f, 0.5547f }));
    }

    test_section("shear_y_at");
    {
        const auto result = line3.shear_y_at({ -2.0f, 3.0f }, 0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 3.0f, 1.5f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.5547f, 0.83205f }));
    }

    test_section("shear_y");
    {
        const nnm::Line2f result = line3.shear_y(0.5f);
        TEST_ASSERT(result.origin.approx_equal({ 3.0f, 0.5f }));
        TEST_ASSERT(result.direction.approx_equal({ 0.5547f, 0.83205f }));
    }

    test_section("operator<");
    {
        constexpr auto result = line1 < line2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(line2 < line1);
    }

    test_section("operator==");
    {
        constexpr auto result = line1 == line2;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(line1 == line1);
    }

    test_section("operator!=");
    {
        constexpr auto result = line1 != line2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(line1 != line1);
    }
}

