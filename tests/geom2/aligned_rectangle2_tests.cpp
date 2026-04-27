#include "tests.hpp"

void aligned_rectangle2_tests()
{
    test_case("AlignedRectangle2");

    test_section("AlignedRectangle2()");
    {
        constexpr nnm::AlignedRectangle2f a1 { };
        TEST_ASSERT(a1.min.approx_zero());
        TEST_ASSERT(a1.max.approx_zero());
    }

    test_section("AlignedRectangle2(const Vector2&, const Vector2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT(a1.min.approx_equal({ -2.0f, -2.0f }));
        TEST_ASSERT(a1.max.approx_equal({ 1.0f, 3.0f }));
    }

    test_section("AlignedRectangle2(const AlignedRectangle<Other>&)");
    {
        constexpr nnm::AlignedRectangle2d a1 { { -2.0, -2.0 }, { 1.0, 3.0 } };
        constexpr nnm::AlignedRectangle2f a2 { a1 };
        TEST_ASSERT(a2.min.approx_equal({ -2.0f, -2.0f }));
        TEST_ASSERT(a2.max.approx_equal({ 1.0f, 3.0f }));
    }

    test_section("from_bounding_points");
    {
        constexpr auto a = nnm::AlignedRectangle2f::from_bounding_points({ -1.0f, 2.0f }, { 2.0f, -1.0f });
        TEST_ASSERT(a.approx_equal({ { -1.0f, -1.0f }, { 2.0f, 2.0f } }));
    }

    test_section("from_bounding_segment");
    {
        constexpr auto a = nnm::AlignedRectangle2f::from_bounding_segment({ { 3.0f, 0.0f }, { -1.0f, 1.0f } });
        TEST_ASSERT(a.approx_equal({ { -1.0f, 0.0f }, { 3.0f, 1.0f } }));
    }

    test_section("from_bounding_circle");
    {
        constexpr auto a = nnm::AlignedRectangle2f::from_bounding_circle({ { 2.0f, 1.0f }, 2.0f });
        TEST_ASSERT(a.approx_equal({ { 0.0f, -1.0f }, { 4.0f, 3.0f } }));
    }

    test_section("from_bounding_triangle");
    {
        constexpr auto a
            = nnm::AlignedRectangle2f::from_bounding_triangle({ { 0.0f, -1.0f }, { -3.0f, 1.0f }, { 2.0f, 2.0f } });
        TEST_ASSERT(a.approx_equal({ { -3.0f, -1.0f }, { 2.0f, 2.0f } }));
    }

    test_section("from_bounding_rectangle");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        const auto a = nnm::AlignedRectangle2f::from_bounding_rectangle(r1);
        TEST_ASSERT(a.approx_equal({ { -1.4820509f, -4.29903793f }, { 3.4820509f, 0.299038172f } }));
    }

    constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };

    test_section("vertex_nx_ny");
    {
        constexpr auto result = a1.vertex_nx_ny();
        TEST_ASSERT(result.approx_equal({ -2.0f, -2.0f }));
    }

    test_section("vertex_nx_py");
    {
        constexpr auto result = a1.vertex_nx_py();
        TEST_ASSERT(result.approx_equal({ -2.0f, 3.0f }));
    }

    test_section("vertex_px_ny");
    {
        constexpr auto result = a1.vertex_px_ny();
        TEST_ASSERT(result.approx_equal({ 1.0f, -2.0f }));
    }

    test_section("vertex_px_py");
    {
        constexpr auto result = a1.vertex_px_py();
        TEST_ASSERT(result.approx_equal({ 1.0f, 3.0f }));
    }

    test_section("edge_nx");
    {
        constexpr auto result = a1.edge_nx();
        TEST_ASSERT(result.coincident(nnm::Segment2f({ -2.0f, 3.0f }, { -2.0f, -2.0f })));
    }

    test_section("edge_ny");
    {
        constexpr auto result = a1.edge_ny();
        TEST_ASSERT(result.coincident(nnm::Segment2f({ -2.0f, -2.0f }, { 1.0f, -2.0f })));
    }

    test_section("edge_px");
    {
        constexpr auto result = a1.edge_px();
        TEST_ASSERT(result.coincident(nnm::Segment2f({ 1.0f, 3.0f }, { 1.0f, -2.0f })));
    }

    test_section("edge_py");
    {
        constexpr auto result = a1.edge_py();
        TEST_ASSERT(result.coincident(nnm::Segment2f({ -2.0f, 3.0f }, { 1.0f, 3.0f })));
    }

    test_section("normal_nx");
    {
        constexpr auto result = a1.normal_nx();
        TEST_ASSERT(result.approx_equal({ -1.0f, 0.0f }));
    }

    test_section("normal_ny");
    {
        constexpr auto result = a1.normal_ny();
        TEST_ASSERT(result.approx_equal({ 0.0f, -1.0f }));
    }

    test_section("normal_px");
    {
        constexpr auto result = a1.normal_px();
        TEST_ASSERT(result.approx_equal({ 1.0f, 0.0f }));
    }

    test_section("normal_py");
    {
        constexpr auto result = a1.normal_py();
        TEST_ASSERT(result.approx_equal({ 0.0f, 1.0f }));
    }

    test_section("size");
    {
        constexpr auto result = a1.size();
        TEST_ASSERT(result.approx_equal({ 3.0f, 5.0f }));
    }

    test_section("area");
    {
        constexpr auto result = a1.area();
        TEST_ASSERT(nnm::approx_equal(result, 15.0f));
    }

    test_section("perimeter");
    {
        constexpr auto result = a1.perimeter();
        TEST_ASSERT(nnm::approx_equal(result, 16.0f));
    }

    test_section("contains");
    {
        constexpr auto result = a1.contains({ 2.0f, 4.0f });
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.contains({ 0.0f, 2.0f }));
        TEST_ASSERT_FALSE(a1.contains({ -1.0f, -3.0f }));
        TEST_ASSERT(a1.contains({ -1.0f, -1.0f }));
    }

    test_section("signed_distance");
    {
        TEST_ASSERT(nnm::approx_equal(a1.signed_distance({ 2.0f, 4.0f }), 1.4142135624f));
        TEST_ASSERT(nnm::approx_equal(a1.signed_distance({ 0.0f, 2.0f }), -1.0f));
        TEST_ASSERT(nnm::approx_equal(a1.signed_distance({ -1.0f, 4.0f }), 1.0f));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(a1.distance({ 2.0f, 4.0f }), 1.4142135624f));
        TEST_ASSERT(nnm::approx_zero(a1.distance({ 0.0f, 2.0f })));
        TEST_ASSERT(nnm::approx_equal(a1.distance({ -1.0f, 4.0f }), 1.0f));
    }

    test_section("distance(const Line2&)");
    {
        const auto d1 = a1.distance(nnm::Line2f::axis_y_offset(2.0f));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Line2f::from_points({ 1.0f, 4.0f }, { 2.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.3162278f));
        const auto d3 = a1.distance(nnm::Line2f::from_points({ 2.0f, 1.0f }, { -2.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_zero(d3));
    }

    test_section("distance(const Ray2&)");
    {
        const auto d1 = a1.distance(nnm::Ray2f::from_point_to_point({ 2.0f, 1.0f }, { 2.f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Ray2f::from_point_to_point({ 2.0f, 2.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 1.0f));
        const auto d3 = a1.distance(nnm::Ray2f::from_point_to_point({ 3.0f, 2.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = a1.distance(nnm::Ray2f::from_point_to_point({ 2.0f, 3.0f }, { 1.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
    }

    test_section("distance(const Segment2&)");
    {
        const auto d1 = a1.distance(nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Segment2f({ 2.0f, 1.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 1.0f));
        const auto d3 = a1.distance(nnm::Segment2f({ -3.0f, 1.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = a1.distance(nnm::Segment2f({ 2.0f, 3.0f }, { 1.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
        const auto d5 = a1.distance(nnm::Segment2f({ -1.0f, 2.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance(const Circle2&)");
    {
        const auto d1 = a1.distance(nnm::Circle2f({ 3.0f, 1.0f }, 1.0f));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Circle2f({ 2.0f, 1.0f }, 2.0f));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = a1.distance(nnm::Circle2f({ 0.0f, 1.0f }, 0.5f));
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = a1.distance(nnm::Circle2f({ -1.0f, 1.0f }, 4.0f));
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = a1.distance(nnm::Circle2f({ 3.0f, 5.0f }, 1.0f));
        TEST_ASSERT(nnm::approx_equal(d5, 1.82842712f));
    }

    test_section("distance(const Triangle2&)");
    {
        const auto d1 = a1.distance(nnm::Triangle2f({ 3.0f, 2.0f }, { 2.0f, 2.0f }, { 2.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Triangle2f({ 0.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = a1.distance(nnm::Triangle2f({ 2.0f, 2.0f }, { 3.0f, 2.0f }, { 1.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.4472136f));
        const auto d4 = a1.distance(nnm::Triangle2f({ 2.0f, 4.0f }, { 3.0f, 5.0f }, { 3.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 1.4142135624f));
    }

    test_section("distance(const Rectangle2&)");
    {
        const auto d1 = a1.distance(nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::Rectangle2f({ 1.0f, 1.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = a1.distance(nnm::Rectangle2f({ 2.0f, 4.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        const auto d1 = a1.distance(nnm::AlignedRectangle2f({ 2.0f, 1.0f }, { 4.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = a1.distance(nnm::AlignedRectangle2f({ 0.0f, 1.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = a1.distance(nnm::AlignedRectangle2f({ 1.0f, 3.5f }, { 3.0f, 4.5f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
    }

    test_section("intersects(const Line2&)");
    {
        constexpr auto result = a1.intersects(nnm::Line2f({ 2.0f, 1.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::Line2f::from_points({ -3.0f, 2.0f }, { 2.0f, 1.0f })));
    }

    test_section("edge_intersections(const Line2&)");
    {
        constexpr auto i1 = a1.edge_intersections(nnm::Line2f({ 2.0f, 1.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(i1.empty());
        const auto i2 = a1.edge_intersections(nnm::Line2f::from_points({ -3.0f, 2.0f }, { 2.0f, 1.0f }));
        TEST_ASSERT(i2.approx_equal({ { -2.0f, 1.8f }, { 1.0f, 1.2f } }));
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr auto result = a1.intersects(nnm::Ray2f({ 2.0f, 1.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::Ray2f::from_point_to_point({ -3.0f, 2.0f }, { 2.0f, 1.0f })));
        TEST_ASSERT(a1.intersects(nnm::Ray2f::from_point_to_point({ -1.0f, 1.0f }, { -1.0f, 2.0f })));
    }

    test_section("edge_intersections(const Ray2&)");
    {
        constexpr auto i1 = a1.edge_intersections(nnm::Ray2f({ 2.0f, 1.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(i1.empty());
        const auto i2 = a1.edge_intersections(nnm::Ray2f::from_point_to_point({ -3.0f, 2.0f }, { 2.0f, 1.0f }));
        TEST_ASSERT(i2.approx_equal({ { -2.0f, 1.8f }, { 1.0f, 1.2f } }));
        const auto i3 = a1.edge_intersections(nnm::Ray2f::from_point_to_point({ -1.0f, 1.0f }, { -1.0f, 2.0f }));
        TEST_ASSERT(i3.approx_equal({ { -1.0f, 3.0f } }));
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr auto result = a1.intersects(nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::Segment2f({ 0.0f, 2.0f }, { 2.0f, 1.0f })));
        TEST_ASSERT(a1.intersects(nnm::Segment2f({ 2.0f, 1.0f }, { -3.0f, 2.0f })));
        TEST_ASSERT(a1.intersects(nnm::Segment2f({ 0.0f, 1.0f }, { -1.0f, 2.0f })));
    }

    test_section("edge_intersections(const Segment2&)");
    {
        constexpr auto i1 = a1.edge_intersections(nnm::Segment2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT(i1.empty());
        const auto i2 = a1.edge_intersections(nnm::Segment2f({ 0.0f, 2.0f }, { 2.0f, 1.0f }));
        TEST_ASSERT(i2.approx_equal({ { 1.0f, 1.5f } }));
        const auto i3 = a1.edge_intersections(nnm::Segment2f({ 2.0f, 1.0f }, { -3.0f, 2.0f }));
        TEST_ASSERT(i3.approx_equal({ { -2.0f, 1.8f }, { 1.0f, 1.2f } }));
        constexpr auto i4 = a1.edge_intersections(nnm::Segment2f({ 0.0f, 1.0f }, { -1.0f, 2.0f }));
        TEST_ASSERT(i4.empty());
    }

    test_section("intersects(const Circle2&)");
    {
        constexpr auto result = a1.intersects(nnm::Circle2f({ 3.0f, 1.0f }, 1.0f));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::Circle2f({ 2.0f, 1.0f }, 2.0f)));
        TEST_ASSERT(a1.intersects(nnm::Circle2f({ -1.0f, 1.0f }, 0.5f)));
        TEST_ASSERT(a1.intersects(nnm::Circle2f({ 1.0f, 3.0f }, 1.0f)));
    }

    test_section("intersect_depth(const Circle2&)");
    {
        constexpr auto i1 = a1.intersect_depth(nnm::Circle2f({ 3.0f, 1.0f }, 1.0f));
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = a1.intersect_depth(nnm::Circle2f({ 2.0f, 1.0f }, 2.0f));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 1.0f, 0.0f }));
        constexpr auto i3 = a1.intersect_depth(nnm::Circle2f({ -1.0f, 1.0f }, 0.5f));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ -1.5f, 0.0f }));
        constexpr auto i4 = a1.intersect_depth(nnm::Circle2f({ 1.0f, 3.0f }, 1.0f));
        TEST_ASSERT(
            i4.has_value() && (i4.value().approx_equal({ 1.0f, 0.0f }) || i4.value().approx_equal({ 0.0f, 1.0f })));
    }

    test_section("intersects(const Triangle2&)");
    {
        constexpr auto result = a1.intersects(nnm::Triangle2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::Triangle2f({ 2.0f, 1.0f }, { 0.0f, 2.0f }, { 3.0f, 2.0f })));
        TEST_ASSERT(a1.intersects(nnm::Triangle2f({ -3.0f, 1.0f }, { 0.0f, 4.0f }, { -3.0f, 4.0f })));
        TEST_ASSERT(a1.intersects(nnm::Triangle2f({ -1.5f, -0.5f }, { -1.5f, -1.0f }, { -1.0f, -1.0f })));
    }

    test_section("intersect_depth(const Triangle2&)");
    {
        const auto i1 = a1.intersect_depth(nnm::Triangle2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = a1.intersect_depth(nnm::Triangle2f({ 2.0f, 1.0f }, { 0.0f, 2.0f }, { 3.0f, 2.0f }));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 1.0f, 0.0f }));
        const auto i3 = a1.intersect_depth(nnm::Triangle2f({ -3.0f, 1.0f }, { 0.0f, 4.0f }, { -3.0f, 4.0f }));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ -0.5f, 0.5f }));
        const auto i4 = a1.intersect_depth(nnm::Triangle2f({ -1.5f, -0.5f }, { -1.5f, -1.0f }, { -1.0f, -1.0f }));
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ -1.0f, 0.0f }));
    }

    test_section("intersects(const Rectangle2&)");
    {
        TEST_ASSERT_FALSE(a1.intersects(nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f)));
        TEST_ASSERT(a1.intersects(nnm::Rectangle2f({ 1.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f)));
        TEST_ASSERT(a1.intersects(nnm::Rectangle2f({ 1.0f, 3.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f)));
        TEST_ASSERT(a1.intersects(nnm::Rectangle2f({ -1.0f, 0.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f)));
    }

    test_section("intersect_depth(const Rectangle2&)");
    {
        const auto i1 = a1.intersect_depth(nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = a1.intersect_depth(nnm::Rectangle2f({ 1.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 1.0f, 0.0f }));
        const auto i3 = a1.intersect_depth(nnm::Rectangle2f({ 1.0f, 3.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0f, 0.5f }));
        const auto i4 = a1.intersect_depth(nnm::Rectangle2f({ -1.0f, 0.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f));
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ -2.0f, 0.0f }));
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr auto result = a1.intersects(nnm::AlignedRectangle2f({ 2.0f, 1.0f }, { 4.0f, 2.0f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1.intersects(nnm::AlignedRectangle2f({ 0.0f, 1.0f }, { 2.0f, 2.0f })));
        TEST_ASSERT(a1.intersects(nnm::AlignedRectangle2f({ 0.0f, 2.5f }, { 2.0f, 3.5f })));
        TEST_ASSERT(a1.intersects(nnm::AlignedRectangle2f({ -2.0f, 0.0f }, { 0.0f, 1.0f })));
    }

    test_section("intersect_depth(const AlignedRectangle2&)");
    {
        constexpr auto i1 = a1.intersect_depth(nnm::AlignedRectangle2f({ 2.0f, 1.0f }, { 4.0f, 2.0f }));
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = a1.intersect_depth(nnm::AlignedRectangle2f({ 0.0f, 1.0f }, { 2.0f, 2.0f }));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 1.0f, 0.0f }));
        constexpr auto i3 = a1.intersect_depth(nnm::AlignedRectangle2f({ 0.0f, 2.5f }, { 2.0f, 3.5f }));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0f, 0.5f }));
        constexpr auto i4 = a1.intersect_depth(nnm::AlignedRectangle2f({ -2.0f, 0.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ -2.0f, 0.0f }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = a1.approx_equal(a1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(a1.approx_equal({ { 1.0f, -2.0f }, { 3.0f, 6.0f } }));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = a1 == a1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(a1 == nnm::AlignedRectangle2f({ -2.0f, 3.0f }, { 10.0f, 20.0f }));
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = a1 != a1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1 != nnm::AlignedRectangle2f({ -2.0f, 3.0f }, { 10.0f, 20.0f }))
    ;}

    test_section("operator<");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = a1 < a1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(a1 < nnm::AlignedRectangle2f({ -2.0f, 3.0f }, { 10.0f, 20.0f }));
        TEST_ASSERT_FALSE(nnm::AlignedRectangle2f({ -2.0f, 3.0f }, { 10.0f, 20.0f }) < a1);
    }
}

