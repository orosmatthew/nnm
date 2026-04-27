#include "tests.hpp"

void circle2_tests()
{
    test_case("Circle2");

    test_section("Circle2()");
    {
        constexpr nnm::Circle2f c { };
        TEST_ASSERT(c.center == nnm::Point2f(0.0f, 0.0f));
        TEST_ASSERT(c.radius == 1.0f);
    }

    test_section("Circle2(const Vector2&, Real)");
    {
        constexpr nnm::Circle2f c { { 2.0f, -3.0f }, 5.0f };
        TEST_ASSERT(c.center == nnm::Point2f(2.0f, -3.0f));
        TEST_ASSERT(c.radius == 5.0f);
    }

    test_section("Circle2(const Circle2<Other>&)");
    {
        constexpr nnm::Circle2d c1 { { 2.0, -3.0 }, 5.0 };
        constexpr nnm::Circle2f c2 { c1 };
        TEST_ASSERT(c2.center.approx_equal({ 2.0f, -3.0f }));
        TEST_ASSERT(nnm::approx_equal(c2.radius, 5.0f));
    }

    test_section("from_center_point");
    {
        TEST_ASSERT(
            nnm::Circle2f::from_center_point({ -2.0f, 2.0f }, { -1.0f, 0.0f })
                .approx_equal({ { -2.0f, 2.0f }, 2.236067977f }));
        TEST_ASSERT(
            nnm::Circle2f::from_center_point({ -2.0f, -1.0f }, { 1.0f, -1.0f })
                .approx_equal({ { -2.0f, -1.0f }, 3.0f }));
    }

    test_section("from_points_unchecked");
    {
        TEST_ASSERT(
            nnm::Circle2f::from_points_unchecked({ -2.0f, 2.0f }, { 1.0f, 3.0f }, { 1.0f, -1.0f })
                .approx_equal({ { 0.0f, 1.0f }, 2.236067977f }));
    }

    test_section("from_points");
    {
        const auto c1 = nnm::Circle2f::from_points({ -2.0f, 2.0f }, { 1.0f, 3.0f }, { 1.0f, -1.0f });
        TEST_ASSERT(c1.has_value() && c1->approx_equal({ { 0.0f, 1.0f }, 2.236067977f }));
        TEST_ASSERT_FALSE(nnm::Circle2f::from_points({ -2.0f, 2.0f }, { 1.0f, -1.0f }, { 0.0f, 0.0f }).has_value());
        TEST_ASSERT_FALSE(nnm::Circle2f::from_points({ -2.0f, 2.0f }, { -2.0f, 2.0f }, { 0.0f, 0.0f }).has_value());
        TEST_ASSERT_FALSE(nnm::Circle2f::from_points({ -2.0f, 2.0f }, { -2.0f, 2.0f }, { -2.0f, 2.0f }).has_value());
    }

    constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };

    test_section("circumference");
    {
        constexpr auto result = c1.circumference();
        TEST_ASSERT(nnm::approx_equal(result, 31.4159265359f));
    }

    test_section("perimeter");
    {
        constexpr auto result = c1.perimeter();
        TEST_ASSERT(nnm::approx_equal(result, 31.4159265359f));
    }

    test_section("area");
    {
        constexpr auto result = c1.area();
        TEST_ASSERT(nnm::approx_equal(result, 78.5398163397f));
    }

    test_section("diameter");
    {
        constexpr auto result = c1.diameter();
        TEST_ASSERT(nnm::approx_equal(result, 10.0f));
    }

    test_section("contains");
    {
        constexpr auto result = c1.contains({ 2.0f, -3.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(c1.contains({ 4.0f, -4.0f }));
        TEST_ASSERT_FALSE(c1.contains({ 7.0f, 0.0f }));
    }

    test_section("point_at");
    {
        TEST_ASSERT(c1.point_at(0.0f).approx_equal({ 7.0f, -3.0f }));
        TEST_ASSERT(c1.point_at(nnm::pi<float>()).approx_equal({ -3.0f, -3.0f }));
        TEST_ASSERT(c1.point_at(nnm::pi<float>() / 2.0f).approx_equal({ 2.0f, 2.0f }));
        TEST_ASSERT(c1.point_at(nnm::pi<float>() / 3.0f).approx_equal({ 4.5f, 1.330127f }));
    }

    test_section("normal_at");
    {
        TEST_ASSERT(c1.normal_at(0.0f).approx_equal({ 1.0f, 0.0f }));
        TEST_ASSERT(c1.normal_at(nnm::pi<float>()).approx_equal({ -1.0f, 0.0f }));
        TEST_ASSERT(c1.normal_at(nnm::pi<float>() / 2.0f).approx_equal({ 0.0f, 1.0f }));
        TEST_ASSERT(c1.normal_at(nnm::pi<float>() / 3.0f).approx_equal({ 0.5f, 0.8660254038f }));
    }

    test_section("signed_distance");
    {
        TEST_ASSERT(nnm::approx_equal(c1.signed_distance({ -3.0f, 1.0f }), 1.403124237f));
        TEST_ASSERT(nnm::approx_equal(c1.signed_distance({ 0.0f, 0.0f }), -1.39444872f));
        TEST_ASSERT_FALSE(nnm::approx_equal(c1.signed_distance({ 1.0f, 1.0f }), -1.39444872f));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(c1.distance({ -3.0f, 1.0f }), 1.403124237f));
        TEST_ASSERT(nnm::approx_equal(c1.distance({ 0.0f, 0.0f }), 0.0f));
        TEST_ASSERT_FALSE(nnm::approx_equal(c1.distance({ 1.0f, 1.0f }), 1.0f));
        TEST_ASSERT_FALSE(nnm::approx_equal(c1.distance({ 10.0f, 10.0f }), 1.0f));
    }

    test_section("distance(const Line2&)");
    {
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Line2f::axis_x())));
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Line2f::axis_y())));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Line2f::axis_x_offset(3.0f)), 1.0f));
    }

    test_section("distance(const Ray2&)");
    {
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Ray2f({ -4.0f, 0.0f }, { 1.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Ray2f({ -4.0f, 0.0f }, { -1.0f, 0.0f })), 1.7082039f));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Ray2f({ 0.0f, 3.0f }, { 1.0f, 0.0f })), 1.0f));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Ray2f({ 0.0f, 3.0f }, { -1.0f, 0.0f })), 1.32455532f));
    }

    test_section("distance(const Segment2&)");
    {
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Segment2f({ 0.0f, 0.0f }, { 8.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Segment2f({ -8.0f, 0.0f }, { 0.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_zero(c1.distance(nnm::Segment2f({ -8.0f, 0.0f }, { 8.0f, 0.0f }))));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Segment2f({ 0.0f, 3.0f }, { 3.0f, 3.0f })), 1.0f));
        TEST_ASSERT(nnm::approx_equal(c1.distance(nnm::Segment2f({ 0.0f, 3.0f }, { 1.0f, 3.0f })), 1.0827625f));
    }

    test_section("distance(const Circle2&)");
    {
        TEST_ASSERT(nnm::approx_zero(c1.distance(c1)));
        const auto d1 = c1.distance(nnm::Circle2f({ 8.0f, 0.0f }, 2.0f));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = c1.distance(nnm::Circle2f({ 10.0f, -4.0f }, 2.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 1.0622577f));
    }

    test_section("distance(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        const auto d1 = nnm::Circle2f({ 1.0f, 2.0f }, 1.0f).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Circle2f({ 2.0f, 1.0f }, 1.0f).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d2, 1.23606798f));
        const auto d3 = nnm::Circle2f({ -3.0f, -5.0f }, 0.5f).distance(tri1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
        const auto d4 = nnm::Circle2f({ -2.0f, 1.0f }, 1.0f).distance(tri1);
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        const auto d1 = nnm::Circle2f({ 3.0f, -0.5f }, 1.0f).distance(r1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Circle2f({ 3.0f, -0.5f }, 0.5f).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.299038053f));
        const auto d3 = nnm::Circle2f({ 1.0f, 5.0f }, 0.5f).distance(r2);
        TEST_ASSERT(nnm::approx_equal(d3, 0.618034005f));
        const auto d4 = nnm::Circle2f({ -0.5f, 3.0f }, 0.5f).distance(r2);
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Circle2f({ 3.0f, 1.0f }, 1.0f).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Circle2f({ 2.0f, 1.0f }, 2.0f).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = nnm::Circle2f({ 0.0f, 1.0f }, 0.5f).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Circle2f({ -1.0f, 1.0f }, 4.0f).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = nnm::Circle2f({ 3.0f, 5.0f }, 1.0f).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d5, 1.82842712f));
    }

    test_section("intersects(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        constexpr auto result = c1.intersects(line1);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(c1.intersects(line2));
        TEST_ASSERT(c1.intersects(nnm::Line2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } }));
        TEST_ASSERT_FALSE(c1.intersects(nnm::Line2f { { 0.0f, 100.0f }, { 1.0f, .0f } }));
    }

    test_section("edge_intersections(const Line2&)");
    {
        constexpr nnm::Line2f line1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result1 = c1.edge_intersections(line1);
        TEST_ASSERT(result1.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Line2f line2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT(c1.edge_intersections(line2).empty());
        const auto result2 = c1.edge_intersections(nnm::Line2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } });
        TEST_ASSERT(result2.approx_equal({ { 0.0f, -7.58257294f }, { 0.0f, 1.58257294f } }));
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result = c1.intersects(ray1);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Ray2f ray2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
        TEST_ASSERT(c1.intersects(ray2));
        constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        TEST_ASSERT_FALSE(c1.intersects(ray3));
        TEST_ASSERT_FALSE(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } }));
        TEST_ASSERT(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, -1.0f } }));
        TEST_ASSERT_FALSE(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 1.0f, .0f } }));
        constexpr nnm::Ray2f ray4 { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } };
        TEST_ASSERT(c1.intersects(ray4));
    }

    test_section("edge_intersections(const Ray2&)");
    {
        constexpr nnm::Ray2f ray1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
        const auto result1 = c1.edge_intersections(ray1);
        TEST_ASSERT(result1.empty());
        constexpr nnm::Ray2f ray2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
        const auto result2 = c1.edge_intersections(ray2);
        TEST_ASSERT(result2.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
        const auto result3 = c1.edge_intersections(ray3);
        TEST_ASSERT(result3.empty());
        const auto result4 = c1.edge_intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } });
        TEST_ASSERT(result4.empty());
        const auto result5 = c1.edge_intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, -1.0f } });
        TEST_ASSERT(result5.approx_equal({ { 0.0f, -7.58257294f }, { 0.0f, 1.58257294f } }));
        const auto result6 = c1.edge_intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result6.empty());
        const auto result7 = c1.edge_intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(result7.approx_equal({ { 6.0f, -6.0f } }));
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
        TEST_ASSERT_FALSE(c1.intersects(s1));
        constexpr nnm::Segment2f s2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
        TEST_ASSERT(c1.intersects(s2));
        constexpr nnm::Segment2f s3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
        TEST_ASSERT(c1.intersects(s3));
        constexpr nnm::Segment2f s4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
        TEST_ASSERT(c1.intersects(s4));
    }

    test_section("edge_intersections(const Segment2&)");
    {
        constexpr nnm::Segment2f s1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
        const auto result1 = c1.edge_intersections(s1);
        TEST_ASSERT(result1.empty());
        constexpr nnm::Segment2f s2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
        const auto result2 = c1.edge_intersections(s2);
        TEST_ASSERT(result2.approx_equal({ { 1.08452405f, 1.9154759f }, { 6.9154759f, -3.9154759f } }));
        constexpr nnm::Segment2f s3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
        const auto result3 = c1.edge_intersections(s3);
        TEST_ASSERT(result3.approx_equal({ { 1.08452405f, 1.9154759f } }));
        constexpr nnm::Segment2f s4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
        const auto result4 = c1.edge_intersections(s4);
        TEST_ASSERT(result4.empty());
    }

    test_section("intersects(const Circle2&)");
    {
        constexpr auto result = c1.intersects(c1);
        TEST_ASSERT(result);
        constexpr nnm::Circle2f c2 { { 1.0f, -4.0f }, 2.0f };
        TEST_ASSERT(c1.intersects(c2));
        TEST_ASSERT_FALSE(c1.intersects(nnm::Circle2 { { 0.0f, 100.0f }, 2.0f }));
        TEST_ASSERT(c1.intersects(nnm::Circle2f { { -4.0f, -4.0f }, 2.0f }));
    }

    test_section("intersect_depth");
    {
        const auto result1 = c1.intersect_depth(c1);
        TEST_ASSERT(result1.has_value() && nnm::approx_equal(result1->length(), 10.0f));
        const auto result2 = c1.intersect_depth({ { 1.0f, -4.0f }, 2.0f });
        TEST_ASSERT(result2.has_value() && result2->approx_equal({ -3.9497474683f, -3.9497474683f }));
        const auto result3 = c1.intersect_depth(nnm::Circle2f { { 0.0f, 100.0f }, 2.0f });
        TEST_ASSERT_FALSE(result3.has_value());
        const auto result4 = c1.intersect_depth(nnm::Circle2f { { -4.0f, -4.0f }, 2.0f });
        TEST_ASSERT(result4.has_value() && result4->approx_equal({ -0.9047574669f, -0.1507929111f }));
        const auto result5 = c1.intersect_depth(nnm::Circle2f({ 2.0f, -3.0f }, 1.0f));
        TEST_ASSERT(result5.has_value() && nnm::approx_equal(result5->length(), 6.0f));
    }

    test_section("intersects(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        TEST_ASSERT(nnm::Circle2f({ -2.0f, 1.0f }, 1.0f).intersects(tri1));
        TEST_ASSERT(nnm::Circle2f({ -2.0f, 1.0f }, 6.0f).intersects(tri1));
        TEST_ASSERT_FALSE(nnm::Circle2f({ 1.0f, 1.0f }, 1.0f).intersects(tri1));
        TEST_ASSERT(nnm::Circle2f({ 1.0f, 1.0f }, 3.0f).intersects(tri1));
        TEST_ASSERT(nnm::Circle2f({ 1.0f, 2.0f }, 9.0f).intersects(tri1));
    }

    test_section("intersect_depth(const Triangle2&)");
    {
        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
        const auto d1 = nnm::Circle2f({ 1.0f, 2.0f }, 2.0f).intersect_depth(tri1);
        TEST_ASSERT(d1.has_value() && d1->approx_equal({ -0.988854374f, 0.494427187f }));
        const auto d2 = nnm::Circle2f({ 1.0f, 2.0f }, 2.0f).intersect_depth(tri2);
        TEST_ASSERT(d2.has_value() && d2->approx_equal({ -0.988854374f, 0.494427187f }));
        const auto d3 = nnm::Circle2f({ -2.0f, 1.0f }, 1.0f).intersect_depth(tri1);
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ -2.094427191f, 1.0472135955f }));
        const auto d4 = nnm::Circle2f({ -2.0f, 1.0f }, 1.0f).intersect_depth(tri2);
        TEST_ASSERT(d4.has_value() && d4->approx_equal({ -2.094427191f, 1.0472135955f }));
        const auto d5 = nnm::Circle2f({ -3.0f, -5.0f }, 2.0f).intersect_depth(tri2);
        TEST_ASSERT(d5.has_value() && d5->approx_equal({ 0.0f, 1.0f }));
        const auto d6 = nnm::Circle2f({ -3.0f, -4.0f }, 1.0f).intersect_depth(tri1);
        TEST_ASSERT(d6.has_value() && (d6->approx_equal(-tri1.normal(0)) || d6->approx_equal(-tri1.normal(1))));
        const auto d7 = nnm::Circle2f({ -3.0f, -4.0f }, 1.0f).intersect_depth(tri1);
        TEST_ASSERT(d7.has_value() && (d7->approx_equal(-tri2.normal(0)) || d7->approx_equal(-tri2.normal(2))));
        const auto d8 = nnm::Circle2f({ -1.0f, 0.0f }, 1.0f).intersect_depth(tri1);
        TEST_ASSERT(d8.has_value() && d8->approx_equal({ -0.894427191f, 0.4472135955f }));
        const auto d9 = nnm::Circle2f({ -1.0f, 0.0f }, 1.0f).intersect_depth(tri2);
        TEST_ASSERT(d9.has_value() && d9->approx_equal({ -0.894427191f, 0.4472135955f }));
        const auto d10 = nnm::Circle2f({ -1.5f, 3.0f }, 2.0f).intersect_depth(tri1);
        TEST_ASSERT(d10.has_value() && d10->approx_equal({ 0.7427813525f, -1.8569533819f }));
        const auto d11 = nnm::Circle2f({ -1.5f, 3.0f }, 2.0f).intersect_depth(tri1);
        TEST_ASSERT(d11.has_value() && d11->approx_equal({ 0.7427813525f, -1.8569533819f }));
        const auto d12 = nnm::Circle2f({ 1.0f, 0.0f }, 1.0f).intersect_depth(tri1);
        TEST_ASSERT_FALSE(d12.has_value());
        const auto d13 = nnm::Circle2f({ 1.0f, 0.0f }, 1.0f).intersect_depth(tri2);
        TEST_ASSERT_FALSE(d13.has_value());
    }

    test_section("intersects(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        TEST_ASSERT(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersects(r1));
        TEST_ASSERT_FALSE(nnm::Circle2f({ 2.5f, 0.5f }, 1.0f).intersects(r1));
        TEST_ASSERT(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersects(r2));
        TEST_ASSERT(nnm::Circle2f({ -1.0f, 2.0f }, 1.0f).intersects(r2));
        TEST_ASSERT(nnm::Circle2f({ -1.5f, 3.0f }, 0.5f).intersects(r2));
        TEST_ASSERT_FALSE(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersects(r3));
        TEST_ASSERT(nnm::Circle2f({ 5.0f, -4.0f }, 4.0f).intersects(r3));
    }

    test_section("intersect_depth(const Rectangle&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };
        const auto d1 = nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersect_depth(r1);
        TEST_ASSERT(d1.has_value() && d1->approx_equal({ -0.41746816f, -0.723076164f }));
        const auto d2 = nnm::Circle2f({ 2.5f, 0.5f }, 1.0f).intersect_depth(r1);
        TEST_ASSERT_FALSE(d2.has_value());
        const auto d3 = nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersect_depth(r2);
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ -0.5f, 0.0f }));
        const auto d4 = nnm::Circle2f({ -1.0f, 2.0f }, 1.0f).intersect_depth(r2);
        TEST_ASSERT(d4.has_value() && (d4->approx_equal({ -2.5f, 0.0f }) || d4->approx_equal({ 2.5f, 0.0f })));
        const auto d5 = nnm::Circle2f({ -1.5f, 3.0f }, 0.5f).intersect_depth(r2);
        TEST_ASSERT(d5.has_value() && (d5->approx_equal({ 1.5f, 0.0f }) || d5->approx_equal({ 0.0f, -1.5f })));
        const auto d6 = nnm::Circle2f({ -2.0f, 2.5f }, 1.0f).intersect_depth(r2);
        TEST_ASSERT(d6.has_value() && d6->approx_equal({ 1.5f, 0.0f }));
        const auto d7 = nnm::Circle2f({ 2.0f, 0.5f }, 2.0f).intersect_depth(r3);
        TEST_ASSERT_FALSE(d7.has_value());
        const auto d8 = nnm::Circle2f({ 5.0f, -4.0f }, 4.0f).intersect_depth(r3);
        TEST_ASSERT(d8.has_value() && d8->approx_equal({ 0.0f, 3.5f }));
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT_FALSE(nnm::Circle2f({ 3.0f, 1.0f }, 1.0f).intersects(a1));
        TEST_ASSERT(nnm::Circle2f({ 2.0f, 1.0f }, 2.0f).intersects(a1));
        TEST_ASSERT(nnm::Circle2f({ -1.0f, 1.0f }, 0.5f).intersects(a1));
        TEST_ASSERT(nnm::Circle2f({ 1.0f, 3.0f }, 1.0f).intersects(a1));
    }

    test_section("intersect_depth(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto i1 = nnm::Circle2f({ 3.0f, 1.0f }, 1.0f).intersect_depth(a1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Circle2f({ 2.0f, 1.0f }, 2.0f).intersect_depth(a1);
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f }));
        const auto i3 = nnm::Circle2f({ -1.0f, 1.0f }, 0.5f).intersect_depth(a1);
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 1.5f, 0.0f }));
        const auto i4 = nnm::Circle2f({ 1.0f, 3.0f }, 1.0f).intersect_depth(a1);
        TEST_ASSERT(
            i4.has_value() && (i4.value().approx_equal({ -1.0f, 0.0f }) || i4.value().approx_equal({ 0.0f, -1.0f })));
    }

    test_section("tangent(const Line2&)");
    {
        constexpr nnm::Circle2f circle { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Line2f line3 { { -2.0f, 2.0f }, { -1.0f, 0.0f } };
        constexpr auto result = circle.tangent(line3);
        TEST_ASSERT(result);
        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
        TEST_ASSERT_FALSE(circle.tangent(line1));
    }

    test_section("tangent(const Ray2&)");
    {
        constexpr nnm::Circle2f c2 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Ray2f r1 { { 0.0f, 2.0f }, { 1.0f, 0.0f } };
        constexpr auto result = c2.tangent(r1);
        TEST_ASSERT(result);
        constexpr nnm::Ray2f r2 { { 0.0f, 2.0f }, { -1.0f, 0.0f } };
        TEST_ASSERT_FALSE(c2.tangent(r2));
        const auto r3 = nnm::Ray2f::from_point_to_point({ 0.0f, 2.0f }, { 2.0f, 0.0f });
        TEST_ASSERT_FALSE(c2.tangent(r3));
        constexpr nnm::Ray2f r4 { { 2.0f, 2.0f }, { 0.0f, 1.0f } };
        TEST_ASSERT_FALSE(c2.tangent(r4));
        constexpr nnm::Ray2f r5 { { 2.0f, 2.0f }, { 0.0f, -1.0f } };
        TEST_ASSERT_FALSE(c2.tangent(r5));
    }

    test_section("tangent(const Segment2&");
    {
        constexpr nnm::Circle2f c2 { { 2.0f, -3.0f }, 5.0f };
        constexpr nnm::Segment2f seg1 { { 0.0f, 2.0f }, { 1.0f, 2.0f } };
        constexpr auto result = c2.tangent(seg1);
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Segment2f seg2 { { 0.0f, 2.0f }, { 4.0f, 2.0f } };
        TEST_ASSERT(c2.tangent(seg2));
        constexpr nnm::Segment2f seg3 { { 2.0f, 2.0f }, { 4.0f, 4.0f } };
        TEST_ASSERT_FALSE(c2.tangent(seg3));
        constexpr nnm::Segment2f seg4 { { 2.0f, 2.0f }, { 4.0f, 0.0f } };
        TEST_ASSERT_FALSE(c2.tangent(seg4));
    }

    test_section("tangent(const Circle2&)");
    {
        constexpr nnm::Circle2f c2 { { 8.0f, -3.0f }, 1.0f };
        constexpr auto result = c1.tangent(c2);
        TEST_ASSERT(result);
        constexpr nnm::Circle2f c3 { { 6.0f, 2.0f }, 1.403124237f };
        TEST_ASSERT(c1.tangent(c3));
        constexpr nnm::Circle2f c4 { { 2.0f, -6.0f }, 2.0f };
        TEST_ASSERT(c1.tangent(c4));
        constexpr nnm::Circle2f c5 { { 0.0f, 100.0f }, 45.0f };
        TEST_ASSERT_FALSE(c1.tangent(c5));
        constexpr nnm::Circle2f c6 { { 2.0f, 0.0f }, 4.0f };
        TEST_ASSERT_FALSE(c1.tangent(c6));
        TEST_ASSERT_FALSE(c1.tangent(c1));
    }

    test_section("translate");
    {
        constexpr auto result = c1.translate({ 0.0f, 0.0f });
        TEST_ASSERT(result.approx_equal(c1));
        TEST_ASSERT(c1.translate({ -20.0f, 30.0f }).approx_equal({ { -18.0f, 27.0f }, 5.0f }))
        TEST_ASSERT_FALSE(c1.translate({ -20.0f, 100.0f }).approx_equal({ { -18.0f, 27.0f }, 5.0f }));
    }

    constexpr nnm::Point2f origin { -3.0f, 1.0f };

    test_section("rotate_at");
    {
        TEST_ASSERT(c1.rotate_at(origin, nnm::pi<float>() / 3.0f).approx_equal({ { 2.964101615f, 3.330127f }, 5.0f }));
        TEST_ASSERT_FALSE(
            c1.rotate_at({ -2.0f, 10.0f }, nnm::pi<float>() / 4.0f).approx_equal({ { 2.964101615f, 3.330127f }, 5.0f }))
    }

    test_section("rotate");
    {
        TEST_ASSERT(c1.rotate(nnm::pi<float>() / 3.0f).approx_equal({ { 3.5980762f, 0.2320508f }, 5.0f }));
        TEST_ASSERT_FALSE(c1.rotate(-nnm::pi<float>() / 10.0f).approx_equal({ { 3.5980762f, 0.2320508f }, 5.0f }));
    }

    test_section("scale_at");
    {
        constexpr auto result = c1.scale_at(origin, 4.0f);
        TEST_ASSERT(result.approx_equal({ { 17.0f, -15.0f }, 20.0f }));
        TEST_ASSERT_FALSE(c1.scale_at({ -10.0f, 200.0f }, 2.0f).approx_equal({ { 17.0f, -15.0f }, 20.0f }));
    }

    test_section("scale");
    {
        constexpr auto result = c1.scale(-3.0f);
        TEST_ASSERT(result.approx_equal({ { -6.0f, 9.0f }, 15.0f }));
        TEST_ASSERT_FALSE(c1.scale(2.0f).approx_equal({ { -6.0f, 9.0f }, 15.0f }));
    }

    test_section("coincident");
    {
        constexpr auto result = c1.coincident(c1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(c1.coincident(nnm::Circle2f { { -1.0f, -100.0f }, 10.0f }));
        TEST_ASSERT(c1.coincident(nnm::Circle2f { { 2.00000001f, -3.000000000001f }, 4.999999f }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = c1.approx_equal(c1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(c1.approx_equal(nnm::Circle2f { { -1.0f, -100.0f }, 10.0f }));
        TEST_ASSERT(c1.approx_equal(nnm::Circle2f { { 2.00000001f, -3.000000000001f }, 4.999999f }));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = c1 == c1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(c1 == nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
        TEST_ASSERT_FALSE(c1 == nnm::Circle2f({ 2.00000001f, -3.0001f }, 4.999999f));
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = c1 != c1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(c1 != nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
        TEST_ASSERT(c1 != nnm::Circle2f({ 2.00000001f, -3.0001f }, 4.999999f));
    }

    test_section("operator<");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = c1 < c1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(c1 < nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
        TEST_ASSERT(c1 < nnm::Circle2f({ 2.000001f, -3.0001f }, 4.999999f))
    }
}

