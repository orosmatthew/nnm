#include "tests.hpp"

void segment2_tests()
{
    test_case("Segment2");

    test_section("Segment2()");
    {
        constexpr nnm::Segment2f s { };
        TEST_ASSERT(s.start == nnm::Point2f::zero());
        TEST_ASSERT(s.end == nnm::Point2f::zero());
    }

    test_section("Segment2(const Vector2&, const Vector2&)");
    {
        constexpr nnm::Segment2f s { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
        TEST_ASSERT(s.start == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(s.end == nnm::Point2f(-3.0f, 4.0f));
    }

    test_section("Segment2(const Segment2<Other>&)");
    {
        constexpr nnm::Segment2d s1 { { 1.0, -2.0 }, { -3.0, 4.0 } };
        constexpr nnm::Segment2f s2 { s1 };
        TEST_ASSERT(s2.start.approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(s2.end.approx_equal({ -3.0f, 4.0f }));
    }

    constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
    constexpr nnm::Segment2f s_degen { { 1.0f, 2.0f }, { 1.0f, 2.0f } };

    test_section("collinear(const Vector2&)");
    {
        constexpr auto result = s1.collinear({ 0.0f, -0.5f });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1.collinear({ 0.0f, 0.0f }));
        TEST_ASSERT(s1.collinear({ -5.0f, 7.0f }));
        TEST_ASSERT(s1.collinear({ 3.0f, -5.0f }));
        TEST_ASSERT(s_degen.collinear({ 0.0f, 0.0f }));
        TEST_ASSERT(s_degen.collinear({ 1.0f, 2.0f }));
    }

    test_section("collinear(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 0.0f, -0.5f }, { -0.5547f, 0.83205f } };
        constexpr auto result = s1.collinear(line1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line2 { { 3.0f, -0.5f }, { -0.5547f, 0.83205f } };
        TEST_ASSERT_FALSE(s1.collinear(line2));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, -0.5f }, { 0.0f, -0.5f }).collinear(line1));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 0.0f, -0.5f }, { 0.0f, -0.5f }).collinear(line2));
    }

    test_section("collinear(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 3.0f, -5.0f }, { -0.5547f, 0.83205f } };
        constexpr auto result = s1.collinear(ray1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f ray2 { { 0.0f, -0.5f }, { 0.5547f, -0.83205f } };
        TEST_ASSERT(s1.collinear(ray2));
        constexpr nnm::Ray2f ray3 { { 3.0f, -0.5f }, { 0.5547f, -0.83205f } };
        TEST_ASSERT_FALSE(s1.collinear(ray3));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, -0.5f }, { 0.0f, -0.5f }).collinear(ray2));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 0.0f, -0.5f }, { 0.0f, -0.5f }).collinear(ray3));
    }

    test_section("collinear(const Segment2&)");
    {
        constexpr nnm::Segment2f s2 { { -0.3333333f, 0.0f }, { 0.0f, -0.5f } };
        constexpr auto result = s1.collinear(s2);
        TEST_ASSERT(result);
        constexpr nnm::Segment2f s3 { { 7.0f, -11.0f }, { 3.0f, -5.0f } };
        TEST_ASSERT(s1.collinear(s3));
        constexpr nnm::Segment2f s4 { { 6.0f, -10.0f }, { 5.0f, -5.0f } };
        TEST_ASSERT_FALSE(s1.collinear(s4));
        TEST_ASSERT(nnm::Segment2f({ 7.0f, -11.0f }, { 7.0f, -11.0f }).collinear(s3));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 7.0f, -11.0f }, { 7.0f, -11.0f }).collinear(s4));
        TEST_ASSERT(nnm::Segment2f({ 7.0f, -11.0f }, { 7.0f, -11.0f }).collinear(s_degen));
    }

    test_section("contains");
    {
        constexpr auto result = s1.contains({ 0.0f, -0.5f });
        TEST_ASSERT(result);
        TEST_ASSERT(s1.contains({ 1.0f, -2.0f }));
        TEST_ASSERT(s1.contains({ -3.0f, 4.0f }));
        TEST_ASSERT(s1.contains({ 0.0f, -0.5f }));
        TEST_ASSERT_FALSE(s1.contains({ 1.0f, 1.0f }));
        TEST_ASSERT_FALSE(s1.contains({ 3.0f, -5.0f }));
        TEST_ASSERT_FALSE(s1.contains({ -5.0f, 7.0f }));
        TEST_ASSERT_FALSE(s_degen.contains({ 0.0f, 0.0f }));
        TEST_ASSERT(s_degen.contains({ 1.0f, 2.0f }));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(s1.distance({ 2.0f, 3.0f }), 3.6055512755f));
        TEST_ASSERT(nnm::approx_equal(s1.distance({ 3.0f, -5.0f }), 3.6055512755f));
        TEST_ASSERT(nnm::approx_equal(s1.distance({ -4.0f, 4.0f }), 1.0f));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance({ 2.0f, 2.0f }), 1.0f));
        TEST_ASSERT(nnm::approx_zero(s_degen.distance({ 1.0f, 2.0f })));
    }

    test_section("distance(const Line2&)");
    {
        constexpr auto result = s1.distance(nnm::Line2f::axis_x_offset(2.0f));
        TEST_ASSERT(nnm::approx_zero(result));
        TEST_ASSERT(
            nnm::approx_equal(s1.distance(nnm::Line2f::from_points({ 0.0f, 3.0f }, { 1.0f, 2.0f })), 1.4142135624f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Line2f::axis_y_offset(2.0f)), 1.0f));
        TEST_ASSERT(
            nnm::approx_equal(s1.distance(nnm::Line2f::from_points({ 2.0f, 0.0f }, { 0.0f, 3.0f })), 1.9414506868f));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance(nnm::Line2f::axis_x()), 2.0f));
    }

    test_section("distance(const Ray2&)");
    {
        TEST_ASSERT(nnm::approx_zero(s1.distance(nnm::Ray2f { { 1.0f, 2.0f }, { -1.0f, 0.0f } })));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, -1.0f } }), 1.0f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, 1.0f } }), 3.60555127f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 1.0f, 5.0f }, { -1.0f, 0.0f } }), 1.0f))
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 1.0f, 5.0f }, { 1.0f, 0.0f } }), 3.88290137f));
        TEST_ASSERT(
            nnm::approx_equal(
                s1.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { 3.0f, -1.0f })), 2.21880078f))
        TEST_ASSERT(
            nnm::approx_equal(s1.distance(nnm::Ray2f::from_point_to_point({ 3.0f, -2.0f }, { 4.0f, -3.0f })), 2.0f));
        TEST_ASSERT(
            nnm::approx_equal(
                s1.distance(nnm::Ray2f::from_point_to_point({ -4.0f, 5.0f }, { -5.0f, 4.0f })), 1.4142135624f));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f })), 2.0f));
    }

    test_section("distance(const Segment2&)");
    {
        TEST_ASSERT(nnm::approx_zero(s1.distance(s1)));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { -1.0f, 4.0f }, { 1.0f, 1.0f } }), 1.66410059f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { 1.0f, 5.0f }, { 1.0f, 1.0f } }), 1.66410059f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { 3.0f, 3.0f }, { 2.0f, -2.0f } }), 1.0f));
        TEST_ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { -4.0f, 5.0f }, { -5.0f, 7.0f } }), 1.4142135624f));
        TEST_ASSERT(nnm::approx_zero(s1.distance(nnm::Segment2f { { -1.0f, 3.0f }, { -2.0f, 0.0f } })));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance(nnm::Segment2f({ 0.0f, 0.0f }, { 100.0f, 0.0f })), 2.0f));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance(nnm::Segment2f({ 1.0f, 0.0f }, { 1.0f, 0.0f })), 2.0f));
    }

    test_section("distance(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_zero(nnm::Segment2f({ 0.0f, 0.0f }, { 8.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_zero(nnm::Segment2f({ -8.0f, 0.0f }, { 0.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_zero(nnm::Segment2f({ -8.0f, 0.0f }, { 8.0f, 0.0f }).distance(c1)));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 0.0f, 3.0f }, { 3.0f, 3.0f }).distance(c1), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 0.0f, 3.0f }, { 1.0f, 3.0f }).distance(c1), 1.0827625f));
        TEST_ASSERT(nnm::approx_equal(s_degen.distance(c1), 0.0990195f));
    }

    test_section("distance(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        const auto d1 = nnm::Segment2f({ 0.5f, 1.0f }, { -1.5f, 1.5f }).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Segment2f({ 0.5f, 2.0f }, { 0.5f, 1.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.447214f));
        const auto d3 = nnm::Segment2f({ 0.5f, 1.0f }, { 1.0f, 2.0f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.89442719f));
        const auto d4 = nnm::Segment2f({ -3.5f, -4.5f }, { -2.5f, -4.5f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d4, 0.5f));
        const auto d5 = nnm::Segment2f({ -2.0f, -4.5f }, { -2.5f, -4.5f }).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.7071067812f));
    }

    test_section("distance(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        TEST_ASSERT(nnm::approx_zero(nnm::Segment2f({ 0.5f, -1.0f }, { 1.0f, -1.5f }).distance(r1)));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 1.0f, 1.0f }, { 1.5f, 0.5f }).distance(r1), 0.91506344f));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 4.5f, -2.0f }, { 3.5f, -0.5f }).distance(r1), 0.681108176f));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 1.0f, 3.0f }, { 1.0f, -10.0f }).distance(r2), 0.5f));
        TEST_ASSERT(nnm::approx_equal(nnm::Segment2f({ 2.5f, 5.0f }, { 1.0f, 4.5f }).distance(r2), 0.7071067812f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Segment2f({ 2.0f, 1.0f }, { 3.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d2, 1.0f));
        const auto d3 = nnm::Segment2f({ -3.0f, 1.0f }, { 3.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Segment2f({ 2.0f, 3.0f }, { 1.0f, 4.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
        const auto d5 = nnm::Segment2f({ -1.0f, 2.0f }, { 0.0f, 1.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("signed_distance");
    {
        TEST_ASSERT(nnm::approx_equal(s1.signed_distance({ 2.0f, 3.0f }), -3.6055512755f));
        TEST_ASSERT(nnm::approx_equal(s1.signed_distance({ 3.0f, -5.0f }), 3.6055512755f));
        TEST_ASSERT(nnm::approx_equal(s1.signed_distance({ -4.0f, 4.0f }), 1.0f));
    }

    test_section("direction_unnormalized");
    {
        constexpr auto result = s1.direction_unnormalized();
        TEST_ASSERT(result.approx_equal({ -4.0f, 6.0f }));
    }

    test_section("direction");
    {
        TEST_ASSERT(s1.direction().approx_equal({ -0.5547f, 0.83205f }));
    }

    constexpr nnm::Segment2f s2 { { 0.0f, 4.0f }, { 4.0f, -2.0f } };
    constexpr nnm::Segment2f s3 { { 5.0f, 5.0f }, { 5.0f, 0.0f } };

    test_section("parallel(const Line2&)");
    {
        constexpr auto result = s1.parallel(nnm::Line2f { { 100.0f, -100.0f }, { -0.5547001962f, 0.8320502943f } });
        TEST_ASSERT(result);
        TEST_ASSERT(s1.parallel(nnm::Line2f { { -100.0f, 100.0f }, { 0.5547001962f, -0.8320502943f } }));
        TEST_ASSERT_FALSE(s1.parallel(
            nnm::Line2f { { 1.0f, -2.0f },
                          {
                              0.8320502943f,
                              0.5547001962f,
                          } }));
    }

    test_section("parallel(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 0.0f, 4.0f }, { 0.554699f, -0.832051f } };
        constexpr auto result = s1.parallel(ray1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f ray2 { { -0.2f, -0.2f }, { -0.554699f, -0.832051f } };
        TEST_ASSERT_FALSE(s1.parallel(ray2));
    }

    test_section("parallel(const Segment2&)");
    {
        constexpr auto result = s1.parallel(s2);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s2.parallel(s3));
    }

    test_section("perpendicular(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
        constexpr auto result = s1.perpendicular(line1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(s1.perpendicular(line2));
    }

    test_section("perpendicular(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
        constexpr auto result = s1.perpendicular(ray1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f ray2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(s1.perpendicular(ray2));
    }

    test_section("perpendicular(const Segment2&)");
    {
        constexpr nnm::Segment2f s4 { { 2.0f, 3.0f }, { -1.0f, 1.0f } };
        constexpr auto result = s1.perpendicular(s4);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1.perpendicular(s2));
    }

    test_section("intersects(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
        constexpr auto result = s1.intersects(line1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line2 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
        TEST_ASSERT_FALSE(s1.intersects(line2));
    }

    test_section("intersection(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
        constexpr auto result = s1.intersection(line1);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
        constexpr nnm::Line2f line2 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
        TEST_ASSERT_FALSE(s1.intersection(line2).has_value());
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
        constexpr auto result = s1.intersects(ray1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f ray2 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(s1.intersects(ray2));
    }

    test_section("intersection(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
        constexpr auto result = s1.intersection(ray1);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
        constexpr nnm::Ray2f ray2 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(s1.intersection(ray2).has_value());
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr nnm::Segment2f s4 { { 5.0f, 5.0f }, { -5.0f, -5.0f } };
        constexpr auto result = s1.intersects(s4);
        TEST_ASSERT(result);
        constexpr nnm::Segment2f s5 { { 5.0f, 5.0f }, { 1.6f, 1.6f } };
        TEST_ASSERT_FALSE(s1.intersects(s5));
    }

    test_section("intersection(const Segment2&)");
    {
        constexpr nnm::Segment2f s4 { { 5.0f, 5.0f }, { -5.0f, -5.0f } };
        constexpr auto result = s1.intersection(s4);
        TEST_ASSERT(result.has_value());
        TEST_ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
        constexpr nnm::Segment2f s5 { { 5.0f, 5.0f }, { 1.6f, 1.6f } };
        TEST_ASSERT_FALSE(s1.intersection(s5).has_value());
    }

    test_section("intersects(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Segment2f seg1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
        TEST_ASSERT_FALSE(seg1.intersects(c1));
        constexpr nnm::Segment2f seg2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
        TEST_ASSERT(seg2.intersects(c1));
        constexpr nnm::Segment2f seg3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
        TEST_ASSERT(seg3.intersects(c1));
        constexpr nnm::Segment2f seg4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
        TEST_ASSERT(seg4.intersects(c1));
    }

    test_section("edge_intersections(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Segment2f seg1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
        const auto result1 = seg1.edge_intersections(c1);
        TEST_ASSERT(result1.empty());
        constexpr nnm::Segment2f seg2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
        const auto result2 = seg2.edge_intersections(c1);
        TEST_ASSERT(result2.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Segment2f seg3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
        const auto result3 = seg3.edge_intersections(c1);
        TEST_ASSERT(result3.approx_equal({ { 1.08452405f, 1.9154759f } }));
        constexpr nnm::Segment2f seg4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
        const auto result4 = seg4.edge_intersections(c1);
        TEST_ASSERT(result4.empty());
    }

    test_section("intersects(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        constexpr auto result = nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }.intersects(tri1);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Segment2f({ 2.0f, 2.0f }, { -3.0f, 0.0f }).intersects(tri1))
        TEST_ASSERT(nnm::Segment2f({ 2.0f, 2.0f }, { -3.0f, 0.0f }).intersects(tri2))
        TEST_ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Segment2f({ -1.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Segment2f({ -1.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
        TEST_ASSERT(nnm::Segment2f({ -5.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
        TEST_ASSERT(nnm::Segment2f({ -5.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
    }

    test_section("edge_intersections(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        TEST_ASSERT(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).edge_intersections(tri1).empty());
        TEST_ASSERT(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).edge_intersections(tri2).empty());
        const auto result1 = nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result1.approx_equal({ { -0.5f, 1.0f } }));
        const auto result2 = nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }.edge_intersections(tri2);
        TEST_ASSERT(result2.approx_equal({ { -0.5f, 1.0f } }));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).edge_intersections(tri1).empty());
        TEST_ASSERT(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).edge_intersections(tri2).empty());
        const auto result3 = nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result3.approx_equal({ { -1.0f, 0.0f } }));
        const auto result4 = nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }.edge_intersections(tri2);
        TEST_ASSERT(result4.approx_equal({ { -1.0f, 0.0f } }));
        const auto result5 = nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }.edge_intersections(tri1);
        TEST_ASSERT(result5.approx_equal({ { -3.7272727f, 0.36363636f }, { -0.33333333f, 1.3333333f } }));
        const auto result6 = nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }.edge_intersections(tri2);
        TEST_ASSERT(result6.approx_equal({ { -3.7272727f, 0.36363636f }, { -0.33333333f, 1.3333333f } }));
    }

    test_section("intersects(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        TEST_ASSERT(nnm::Segment2f({ -0.5f, 0.0f }, { 0.0f, 0.0f }).intersects(r1));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).intersects(r1));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 1.5f, -0.5f }, { 3.0f, -1.0f }).intersects(r1));
        TEST_ASSERT(nnm::Segment2f({ -2.0f, 0.5f }, { 0.0f, 3.5f }).intersects(r2));
        TEST_ASSERT(nnm::Segment2f({ 4.0f, -2.0f }, { 4.0f, -5.0 }).intersects(r3));
        TEST_ASSERT_FALSE(nnm::Segment2f({ 5.0f, -0.5f }, { 5.0f, -2.0f }).intersects(r3));
    }

    test_section("edge_intersections(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        const auto i1 = nnm::Segment2f({ -0.5f, 0.0f }, { 0.0f, 0.0f }).edge_intersections(r1);
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f } }));
        const auto i2 = nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).edge_intersections(r1);
        TEST_ASSERT(i2.approx_equal({ { 0.535898447f, 0.0f } }));
        const auto i3 = nnm::Segment2f({ 1.5f, -0.5f }, { 3.0f, -1.0f }).edge_intersections(r1);
        TEST_ASSERT(i3.empty());
        const auto i4 = nnm::Segment2f({ -2.0f, 0.5f }, { 0.0f, 3.5f }).edge_intersections(r2);
        TEST_ASSERT(i4.empty());
        const auto i5 = nnm::Segment2f({ 4.0f, -2.0f }, { 4.0f, -5.0f }).edge_intersections(r3);
        TEST_ASSERT(i5.approx_equal({ { 4.0f, -3.5f }, { 4.0f, -2.5f } }));
        const auto i6 = nnm::Segment2f({ 5.0f, -0.5f }, { 5.0f, -2.0f }).edge_intersections(r3);
        TEST_ASSERT(i6.empty());
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT_FALSE(nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }).intersects(a1));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, 2.0f }, { 2.0f, 1.0f }).intersects(a1));
        TEST_ASSERT(nnm::Segment2f({ 2.0f, 1.0f }, { -3.0f, 2.0f }).intersects(a1));
        TEST_ASSERT(nnm::Segment2f({ 0.0f, 1.0f }, { -1.0f, 2.0f }).intersects(a1));
    }

    test_section("edge_intersections(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto i1 = nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }).edge_intersections(a1);
        TEST_ASSERT(i1.empty());
        const auto i2 = nnm::Segment2f({ 0.0f, 2.0f }, { 2.0f, 1.0f }).edge_intersections(a1);
        TEST_ASSERT(i2.approx_equal({ { 1.0f, 1.5f } }));
        const auto i3 = nnm::Segment2f({ 2.0f, 1.0f }, { -3.0f, 2.0f }).edge_intersections(a1);
        TEST_ASSERT(i3.approx_equal({ { -2.0f, 1.8f }, { 1.0f, 1.2f } }));
        const auto i4 = nnm::Segment2f({ 0.0f, 1.0f }, { -1.0f, 2.0f }).edge_intersections(a1);
        TEST_ASSERT(i4.empty());
    }

    test_section("tangent(const Circle2&)");
    {
        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Segment2f seg1 { { 0.0f, 2.0f }, { 1.0f, 2.0f } };
        constexpr auto result = seg1.tangent(c1);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Segment2f seg2 { { 0.0f, 2.0f }, { 4.0f, 2.0f } };
        TEST_ASSERT(seg2.tangent(c1));
        constexpr nnm::Segment2f seg3 { { 2.0f, 2.0f }, { 4.0f, 4.0f } };
        TEST_ASSERT_FALSE(seg3.tangent(c1));
        constexpr nnm::Segment2f seg4 { { 2.0f, 2.0f }, { 4.0f, 0.0f } };
        TEST_ASSERT_FALSE(seg4.tangent(c1));
    }

    test_section("project");
    {
        constexpr auto result = s1.project({ 2.0f, 3.0f });
        TEST_ASSERT(result.approx_equal({ -1.0f, 1.0f }));
        TEST_ASSERT(s1.project({ 5.0f, -5.0f }).approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(s1.project({ -5.0f, 5.0f }).approx_equal({ -3.0f, 4.0f }));
    }

    test_section("unchecked_slope");
    {
        constexpr auto result = s1.unchecked_slope();
        TEST_ASSERT(nnm::approx_equal(result, -1.5f));
        TEST_ASSERT(nnm::approx_equal(s2.unchecked_slope(), -1.5f));
    }

    test_section("slope");
    {
        constexpr auto result = s1.slope();
        TEST_ASSERT(result.has_value() && nnm::approx_equal(result.value(), -1.5f));
        TEST_ASSERT_FALSE(s3.slope().has_value());
    }

    test_section("length_sqrd");
    {
        constexpr auto result = s1.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(result, 52.0f));
        TEST_ASSERT(nnm::approx_equal(s3.length_sqrd(), 25.0f));
    }

    test_section("length");
    {
        TEST_ASSERT(nnm::approx_equal(s1.length(), 7.2111025509f));
        TEST_ASSERT(nnm::approx_equal(s3.length(), 5.0f));
    }

    test_section("midpoint");
    {
        TEST_ASSERT(s1.midpoint().approx_equal({ -1.0f, 1.0f }));
        TEST_ASSERT(s3.midpoint().approx_equal({ 5.0f, 2.5f }));
    }

    test_section("translate");
    {
        constexpr auto result = s1.translate({ -3.0f, 3.0f });
        TEST_ASSERT(result.start.approx_equal({ -2.0f, 1.0f }));
        TEST_ASSERT(result.end.approx_equal({ -6.0f, 7.0f }));
    }

    test_section("scale_at");
    {
        constexpr auto result = s1.scale_at({ 1.0f, 2.0f }, { -1.0f, 3.0f });
        TEST_ASSERT(result.start.approx_equal({ 1.0f, -10.0f }));
        TEST_ASSERT(result.end.approx_equal({ 5.0f, 8.0f }));
    }

    test_section("scale");
    {
        constexpr auto result = s1.scale({ -1.0f, 3.0f });
        TEST_ASSERT(result.start.approx_equal({ -1.0f, -6.0f }));
        TEST_ASSERT(result.end.approx_equal({ 3.0f, 12.0f }));
    }

    test_section("rotate_at");
    {
        const auto result = s1.rotate_at({ 1.0f, 2.0f }, nnm::pi<float>() / 5.0f);
        TEST_ASSERT(result.start.approx_equal({ 3.35115f, -1.23607f }));
        TEST_ASSERT(result.end.approx_equal({ -3.41164f, 1.266893f }));
    }

    test_section("rotate");
    {
        const auto result = s1.rotate(nnm::pi<float>() / 5.0f);
        TEST_ASSERT(result.start.approx_equal({ 1.98459f, -1.03025f }));
        TEST_ASSERT(result.end.approx_equal({ -4.77819f, 1.47271f }));
    }

    test_section("shear_x_at");
    {
        constexpr auto result = s1.shear_x_at({ 1.0f, 2.0f }, 0.5f);
        TEST_ASSERT(result.start.approx_equal({ -1.0f, -2.0f }));
        TEST_ASSERT(result.end.approx_equal({ -2.0f, 4.0f }));
    }

    test_section("shear_x");
    {
        constexpr auto result = s1.shear_x(0.5f);
        TEST_ASSERT(result.start.approx_equal({ 0.0f, -2.0f }));
        TEST_ASSERT(result.end.approx_equal({ -1.0f, 4.0f }));
    }

    test_section("shear_y_at");
    {
        constexpr auto result = s1.shear_y_at({ 1.0f, 2.0f }, 0.5f);
        TEST_ASSERT(result.start.approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(result.end.approx_equal({ -3.0f, 2.0f }));
    }

    test_section("shear_y");
    {
        constexpr auto result = s1.shear_y(0.5f);
        TEST_ASSERT(result.start.approx_equal({ 1.0f, -1.5f }));
        TEST_ASSERT(result.end.approx_equal({ -3.0f, 2.5f }));
    }

    test_section("coincident");
    {
        constexpr auto result = s1.coincident(s1);
        TEST_ASSERT(result);
        TEST_ASSERT(s1.coincident({ { -3.0f, 4.0f }, { 1.0f, -2.0f } }));
        TEST_ASSERT_FALSE(s1.coincident({ { 5.0f, 10.0f }, { 1.0f, -2.0f } }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = s1.approx_equal(s1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1.approx_equal({ { -3.0f, 4.0f }, { 1.0f, -2.0f } }));
        TEST_ASSERT_FALSE(s1.approx_equal({ { 5.0f, 10.0f }, { 1.0f, -2.0f } }));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = s1 == s1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1 == s2);
    }

    test_section("operator!=");
    {
        constexpr auto result = s1 != s2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s2 != s2);
    }

    test_section("operator<");
    {
        constexpr auto result = s2 < s1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(s1 < s2);
    }
}

