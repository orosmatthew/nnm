#include "tests.hpp"

void rectangle2_tests()
{
    test_case("Rectangle2");

    test_section("Rectangle2()");
    {
        constexpr nnm::Rectangle2f r { };
        TEST_ASSERT(r.center == nnm::Point2f::zero());
        TEST_ASSERT(r.size == nnm::Vector2f::zero());
        TEST_ASSERT(r.angle == 0.0f);
    }

    test_section("Rectangle2(const Vector2&, const Vector2&, Real)");
    {
        constexpr nnm::Rectangle2f r { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        TEST_ASSERT(r.center == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(r.size == nnm::Vector2f(3.0f, 4.0f));
        TEST_ASSERT(r.angle == nnm::pi<float>() / 3.0f);
    }

    test_section("Rectangle(const Rectangle<Other>&)");
    {
        constexpr nnm::Rectangle2d r1 { { 1.0, -2.0 }, { 3.0, 4.0 }, nnm::pi<double>() / 3.0 };
        constexpr nnm::Rectangle2f r2 { r1 };
        TEST_ASSERT(r2.center.approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(r2.size.approx_equal({ 3.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_equal(r2.angle, nnm::pi<float>() / 3.0f));
    }

    constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
    constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
    constexpr nnm::Rectangle2f r3 { { 4.0f, -3.0f }, { 1.0f, 5.0f }, -nnm::pi<float>() / 2.0f };

    test_section("vertex_nx_ny");
    {
        TEST_ASSERT(r1.vertex_nx_ny().approx_equal({ 1.9820508f, -4.299038f }));
        TEST_ASSERT(r2.vertex_nx_ny().approx_equal({ -2.5f, 0.0f }));
        TEST_ASSERT(r3.vertex_nx_ny().approx_equal({ 1.5f, -2.5f }));
    }

    test_section("vertex_nx_py");
    {
        TEST_ASSERT(r1.vertex_nx_py().approx_equal({ -1.48205081f, -2.29903811f }));
        TEST_ASSERT(r2.vertex_nx_py().approx_equal({ -2.5f, 4.0f }));
        TEST_ASSERT(r3.vertex_nx_py().approx_equal({ 6.5f, -2.5f }));
    }

    test_section("vertex_px_ny");
    {
        TEST_ASSERT(r1.vertex_px_ny().approx_equal({ 3.48205081f, -1.7009619f }));
        TEST_ASSERT(r2.vertex_px_ny().approx_equal({ 0.5f, 0.0f }));
        TEST_ASSERT(r3.vertex_px_ny().approx_equal({ 1.5f, -3.5f }));
    }

    test_section("vertex_px_py");
    {
        TEST_ASSERT(r1.vertex_px_py().approx_equal({ 0.01794919f, 0.29903811f }));
        TEST_ASSERT(r2.vertex_px_py().approx_equal({ 0.5f, 4.0f }));
        TEST_ASSERT(r3.vertex_px_py().approx_equal({ 6.5f, -3.5f }));
    }

    test_section("edge_nx");
    {
        TEST_ASSERT(r1.edge_nx().coincident({ { -1.48205081f, -2.29903811f }, { 1.98205081f, -4.29903811f } }));
        TEST_ASSERT(r2.edge_nx().coincident({ { -2.5f, 4.0f }, { -2.5f, 0.0f } }));
        TEST_ASSERT(r3.edge_nx().coincident({ { 1.5f, -2.5f }, { 6.5f, -2.5f } }));
    }

    test_section("edge_ny");
    {
        TEST_ASSERT(r1.edge_ny().coincident({ { 1.98205081f, -4.29903811f }, { 3.482051f, -1.700962f } }));
        TEST_ASSERT(r2.edge_ny().coincident({ { -2.5f, 0.0f }, { 0.5f, 0.0f } }));
        TEST_ASSERT(r3.edge_ny().coincident({ { 1.5f, -2.5f }, { 1.5f, -3.5f } }));
    }

    test_section("edge_px");
    {
        TEST_ASSERT(r1.edge_px().coincident({ { 3.482051f, -1.700962f }, { 0.01794919f, 0.2990381f } }));
        TEST_ASSERT(r2.edge_px().coincident({ { 0.5f, 4.0f }, { 0.5f, 0.0f } }));
        TEST_ASSERT(r3.edge_px().coincident({ { 1.5f, -3.5f }, { 6.5f, -3.5f } }));
    }

    test_section("edge_py");
    {
        TEST_ASSERT(r1.edge_py().coincident({ { -1.48205081f, -2.29903811f }, { 0.01794919f, 0.2990381f } }));
        TEST_ASSERT(r2.edge_py().coincident({ { -2.5f, 4.0f }, { 0.5f, 4.0f } }));
        TEST_ASSERT(r3.edge_py().coincident({ { 6.5f, -2.5f }, { 6.5f, -3.5f } }));
    }

    test_section("normal_nx");
    {
        TEST_ASSERT(r1.normal_nx().approx_equal({ -0.5f, -0.8660254f }));
        TEST_ASSERT(r2.normal_nx().approx_equal({ -1.0f, 0.0f }));
    }

    test_section("normal_ny");
    {
        TEST_ASSERT(r1.normal_ny().approx_equal({ 0.8660254f, -0.5f }));
        TEST_ASSERT(r2.normal_ny().approx_equal({ 0.0f, -1.0f }));
    }

    test_section("normal_px");
    {
        TEST_ASSERT(r1.normal_px().approx_equal({ 0.5f, 0.8660254f }));
        TEST_ASSERT(r2.normal_px().approx_equal({ 1.0f, 0.0f }));
    }

    test_section("normal_py");
    {
        TEST_ASSERT(r1.normal_py().approx_equal({ -0.8660254f, 0.5f }));
        TEST_ASSERT(r2.normal_py().approx_equal({ 0.0f, 1.0f }));
    }

    test_section("area");
    {
        constexpr auto result = r1.area();
        TEST_ASSERT(nnm::approx_equal(result, 12.0f));
        TEST_ASSERT(nnm::approx_equal(r2.area(), 12.0f));
        TEST_ASSERT(nnm::approx_equal(r3.area(), 5.0f));
    }

    test_section("perimeter");
    {
        constexpr auto result = r1.perimeter();
        TEST_ASSERT(nnm::approx_equal(result, 14.0f));
        TEST_ASSERT(nnm::approx_equal(r2.perimeter(), 14.0f));
        TEST_ASSERT(nnm::approx_equal(r3.perimeter(), 12.0f));
    }

    test_section("contains(const Vector2&)");
    {
        TEST_ASSERT(r1.contains(nnm::Point2f::zero()));
        TEST_ASSERT_FALSE(r1.contains(nnm::Point2f(2.0f, -0.5f)));
        TEST_ASSERT(r1.contains(nnm::Point2f(1.5f, -3.5f)));
        TEST_ASSERT(r2.contains(nnm::Point2f(0.0f, 2.0f)));
        TEST_ASSERT(r2.contains(nnm::Point2f(-2.0, 3.5f)));
        TEST_ASSERT_FALSE(r2.contains(nnm::Point2f(2.0, 0.5f)));
        TEST_ASSERT(r3.contains(nnm::Point2f(5.5f, -3.0f)));
        TEST_ASSERT_FALSE(r3.contains(nnm::Point2f(4.0f, -2.0f)));
    }

    test_section("signed_distance");
    {
        TEST_ASSERT(nnm::approx_equal(r1.signed_distance({ 0.0f, 0.0f }), -0.133974656f));
        TEST_ASSERT(nnm::approx_equal(r1.signed_distance({ 2.0f, -0.5f }), 0.299038023f));
        TEST_ASSERT(nnm::approx_equal(r1.signed_distance({ 1.5f, -3.5f }), -0.450961769f));
        TEST_ASSERT(nnm::approx_equal(r2.signed_distance({ 0.0f, 2.0f }), -0.5f));
        TEST_ASSERT(nnm::approx_equal(r2.signed_distance({ 2.0f, 3.5f }), 1.5f));
        TEST_ASSERT(nnm::approx_equal(r3.signed_distance({ 7.5f, -0.5f }), 2.23606798f));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_zero(r1.distance({ 0.0f, 0.0f })));
        TEST_ASSERT(nnm::approx_equal(r1.distance({ 2.0f, -0.5f }), 0.299038023f));
        TEST_ASSERT(nnm::approx_zero(r1.distance({ 1.5f, -3.5f })));
        TEST_ASSERT(nnm::approx_zero(r2.distance({ 0.0f, 2.0f })));
        TEST_ASSERT(nnm::approx_equal(r2.distance({ 2.0f, 3.5f }), 1.5f));
        TEST_ASSERT(nnm::approx_equal(r3.distance({ 7.5f, -0.5f }), 2.23606798f));
    }

    test_section("distance(const Line2&)");
    {
        TEST_ASSERT(nnm::approx_zero(r1.distance(nnm::Line2f::from_points({ 2.0f, 2.0f }, { 1.0f, 1.0f }))));
        TEST_ASSERT(
            nnm::approx_equal(r1.distance(nnm::Line2f::from_points({ 3.0f, 0.5f }, { 2.0f, 2.0f })), 0.819783329f));
        TEST_ASSERT(nnm::approx_equal(r2.distance(nnm::Line2f({ 1.0f, 1.0f }, { 0.0f, 1.0f })), 0.5f));
    }

    test_section("distance(const Ray2&)");
    {
        TEST_ASSERT(nnm::approx_zero(r1.distance(nnm::Ray2f::from_point_to_point({ 0.5f, -1.5f }, { 1.0f, -1.0f }))));
        const auto d1 = r1.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 0.5f }, { 3.0f, -1.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 0.271538854f));
        TEST_ASSERT(nnm::approx_equal(r2.distance(nnm::Ray2f({ 1.0f, 0.5f }, { 0.0f, 1.0f })), 0.5f));
        const auto d2 = r2.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 4.5f }, { 1.5f, 5.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.7071067812f));
    }

    test_section("distance(const Segment2&)");
    {
        TEST_ASSERT(nnm::approx_zero(r1.distance(nnm::Segment2f({ 0.5f, -1.0f }, { 1.0f, -1.5f }))));
        TEST_ASSERT(nnm::approx_equal(r1.distance(nnm::Segment2f({ 1.0f, 1.0f }, { 1.5f, 0.5f })), 0.91506344f));
        TEST_ASSERT(nnm::approx_equal(r1.distance(nnm::Segment2f({ 4.5f, -2.0f }, { 3.5f, -0.5f })), 0.681108176f));
        TEST_ASSERT(nnm::approx_equal(r2.distance(nnm::Segment2f({ 1.0f, 3.0f }, { 1.0f, -10.0f })), 0.5f));
        TEST_ASSERT(nnm::approx_equal(r2.distance(nnm::Segment2f({ 2.5f, 5.0f }, { 1.0f, 4.5f })), 0.7071067812f));
    }

    test_section("distance(const Circle2&)");
    {
        const auto d1 = r1.distance(nnm::Circle2f({ 3.0f, -0.5f }, 1.0f));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = r1.distance(nnm::Circle2f({ 3.0f, -0.5f }, 0.5f));
        TEST_ASSERT(nnm::approx_equal(d2, 0.299038053f));
        const auto d3 = r2.distance(nnm::Circle2f({ 1.0f, 5.0f }, 0.5f));
        TEST_ASSERT(nnm::approx_equal(d3, 0.618034005f));
        const auto d4 = r2.distance(nnm::Circle2f({ -0.5f, 3.0f }, 0.5f));
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Triangle2&)");
    {
        const auto d1 = r1.distance(nnm::Triangle2f({ 1.5f, 0.5f }, { 3.0f, -0.5f }, { 1.5f, -1.5f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = r1.distance(nnm::Triangle2f({ 1.5f, 0.5f }, { 3.0f, -0.5f }, { 2.0f, -0.5f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.299038023f));
        const auto d3 = r2.distance(nnm::Triangle2f({ 2.0f, 1.0f }, { 1.0f, 1.5f }, { 1.0f, 2.5f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
        const auto d4 = r2.distance(nnm::Triangle2f({ 0.5f, 5.5f }, { 1.5f, 4.0f }, { 0.5f, 4.5f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.447214f));
    }

    test_section("distance(const Rectangle2&)");
    {
        const auto d1 = r1.distance(nnm::Rectangle2f({ 2.25f, -0.25f }, { 1.5f, 1.5f }, 0.0f));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = r1.distance(nnm::Rectangle2f({ 2.5f, 0.25f }, { 1.0f, 1.5f }, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 0.299038023f));
        const auto d3 = r2.distance(nnm::Rectangle2f({ 1.5f, 2.25f }, { 1.0f, 1.5f }, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
        const auto d4 = r2.distance(nnm::Rectangle2f({ 1.75f, 4.75f }, { 1.5f, 0.5f }, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Rectangle2f({ 1.0f, 1.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = nnm::Rectangle2f({ 2.0f, 4.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
    }

    test_section("intersects(const Line2&)");
    {
        TEST_ASSERT(r1.intersects(nnm::Line2f::axis_x()));
        TEST_ASSERT(r1.intersects(nnm::Line2f::axis_y()));
        TEST_ASSERT_FALSE(r1.intersects(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f })));
        TEST_ASSERT(r2.intersects(nnm::Line2f::axis_y()));
        TEST_ASSERT_FALSE(r2.intersects(nnm::Line2f::axis_x_offset(-1.0f)));
        TEST_ASSERT_FALSE(r3.intersects(nnm::Line2f::axis_x_offset(-2.0f)));
        TEST_ASSERT(r3.intersects(nnm::Line2f::axis_x_offset(-3.0f)));
        TEST_ASSERT(r3.intersects(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f })));
    }

    test_section("edge_intersections(const Line2&)");
    {
        const auto i1 = r1.edge_intersections(nnm::Line2f::axis_x());
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f }, { 0.535898447f, 0.0f } }));
        const auto i2 = r1.edge_intersections(nnm::Line2f::axis_y());
        TEST_ASSERT(i2.approx_equal({ { 0.0f, -3.15470052f }, { 0.0f, 0.267949343f } }));
        const auto i3 = r1.edge_intersections(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }));
        TEST_ASSERT(i3.empty());
        const auto i4 = r2.edge_intersections(nnm::Line2f::axis_y());
        TEST_ASSERT(i4.approx_equal({ { 0.0f, 0.0f }, { 0.0f, 4.0f } }));
        const auto i5 = r2.edge_intersections(nnm::Line2f::axis_x_offset(-1.0f));
        TEST_ASSERT(i5.empty());
        const auto i6 = r3.edge_intersections(nnm::Line2f::axis_x_offset(-2.0f));
        TEST_ASSERT(i6.empty());
        const auto i7 = r3.edge_intersections(nnm::Line2f::axis_x_offset(-3.0f));
        TEST_ASSERT(i7.approx_equal({ { 1.5f, -3.0f }, { 6.5f, -3.0f } }));
        const auto i8 = r3.edge_intersections(nnm::Line2f::from_points({ 1.0f, 0.5f }, { 3.0f, -1.0f }));
        TEST_ASSERT(i8.approx_equal({ { 5.0f, -2.5f }, { 6.333333f, -3.5f } }));
    }

    test_section("intersects(const Ray2&)");
    {
        TEST_ASSERT(r1.intersects(nnm::Ray2f({ -0.5f, 0.0f }, { 1.0f, 0.0f })));
        TEST_ASSERT_FALSE(r1.intersects(nnm::Ray2f({ 2.0f, -0.5f }, { 1.0f, 0.0f })));
        TEST_ASSERT(r2.intersects(nnm::Ray2f({ -1.5f, 3.0f }, { -1.0f, 0.0f })));
        TEST_ASSERT(r3.intersects(nnm::Ray2f({ 4.0f, 0.0f }, { 0.0f, -1.0f })));
        TEST_ASSERT_FALSE(r3.intersects(nnm::Ray2f({ 4.0f, -2.0f }, { 0.0f, 1.0f })));
    }

    test_section("edge_intersections(const Ray2&)");
    {
        const auto i1 = r1.edge_intersections(nnm::Ray2f({ -0.5f, 0.0f }, { 1.0f, 0.0f }));
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f }, { 0.535898447f, 0.0f } }));
        const auto i2 = r1.edge_intersections(nnm::Ray2f({ 2.0f, -0.5f }, { 1.0f, 0.0f }));
        TEST_ASSERT(i2.empty());
        const auto i3 = r2.edge_intersections(nnm::Ray2f({ -1.5f, 3.0f }, { 1.0f, 0.0f }));
        TEST_ASSERT(i3.approx_equal({ { 0.5f, 3.0f } }));
        const auto i4 = r3.edge_intersections(nnm::Ray2f({ 4.0f, 0.0f }, { 0.0f, -1.0f }));
        TEST_ASSERT(i4.approx_equal({ { 4.0f, -3.5f }, { 4.0f, -2.5f } }));
        const auto i5 = r3.edge_intersections(nnm::Ray2f({ 4.0f, -2.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(i5.empty());
    }

    test_section("intersects(const Segment2&)");
    {
        TEST_ASSERT(r1.intersects(nnm::Segment2f({ -0.5f, 0.0f }, { 0.0f, 0.0f })));
        TEST_ASSERT(r1.intersects(nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f })));
        TEST_ASSERT_FALSE(r1.intersects(nnm::Segment2f({ 1.5f, -0.5f }, { 3.0f, -1.0f })));
        TEST_ASSERT(r2.intersects(nnm::Segment2f({ -2.0f, 0.5f }, { 0.0f, 3.5f })));
        TEST_ASSERT(r3.intersects(nnm::Segment2f({ 4.0f, -2.0f }, { 4.0f, -5.0 })));
        TEST_ASSERT_FALSE(r3.intersects(nnm::Segment2f({ 5.0f, -0.5f }, { 5.0f, -2.0f })));
    }

    test_section("edge_intersections(const Segment2&)");
    {
        const auto i1 = r1.edge_intersections(nnm::Segment2f({ -0.5f, 0.0f }, { 0.0f, 0.0f }));
        TEST_ASSERT(i1.approx_equal({ { -0.154700637f, 0.0f } }));
        const auto i2 = r1.edge_intersections(nnm::Segment2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }));
        TEST_ASSERT(i2.approx_equal({ { 0.535898447f, 0.0f } }));
        const auto i3 = r1.edge_intersections(nnm::Segment2f({ 1.5f, -0.5f }, { 3.0f, -1.0f }));
        TEST_ASSERT(i3.empty());
        const auto i4 = r2.edge_intersections(nnm::Segment2f({ -2.0f, 0.5f }, { 0.0f, 3.5f }));
        TEST_ASSERT(i4.empty());
        const auto i5 = r3.edge_intersections(nnm::Segment2f({ 4.0f, -2.0f }, { 4.0f, -5.0f }));
        TEST_ASSERT(i5.approx_equal({ { 4.0f, -3.5f }, { 4.0f, -2.5f } }));
        const auto i6 = r3.edge_intersections(nnm::Segment2f({ 5.0f, -0.5f }, { 5.0f, -2.0f }));
        TEST_ASSERT(i6.empty());
    }

    test_section("intersects(const Circle2&)");
    {
        TEST_ASSERT(r1.intersects(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f)));
        TEST_ASSERT_FALSE(r1.intersects(nnm::Circle2f({ 2.5f, 0.5f }, 1.0f)));
        TEST_ASSERT(r2.intersects(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f)));
        TEST_ASSERT(r2.intersects(nnm::Circle2f({ -1.0f, 2.0f }, 1.0f)));
        TEST_ASSERT(r2.intersects(nnm::Circle2f({ -1.5f, 3.0f }, 0.5f)));
        TEST_ASSERT_FALSE(r3.intersects(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f)));
        TEST_ASSERT(r3.intersects(nnm::Circle2f({ 5.0f, -4.0f }, 4.0f)));
    }

    test_section("intersect_depth(const Circle2&)");
    {
        const auto d1 = r1.intersect_depth(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f));
        TEST_ASSERT(d1.has_value() && d1->approx_equal({ 0.41746816f, 0.723076164f }));
        const auto d2 = r1.intersect_depth(nnm::Circle2f({ 2.5f, 0.5f }, 1.0f));
        TEST_ASSERT_FALSE(d2.has_value());
        const auto d3 = r2.intersect_depth(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f));
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ 0.5f, 0.0f }));
        const auto d4 = r2.intersect_depth(nnm::Circle2f({ -1.0f, 2.0f }, 1.0f));
        TEST_ASSERT(d4.has_value() && (d4->approx_equal({ 2.5f, 0.0f }) || d4->approx_equal({ -2.5f, 0.0f })));
        const auto d5 = r2.intersect_depth(nnm::Circle2f({ -1.5f, 3.0f }, 0.5f));
        TEST_ASSERT(d5.has_value() && (d5->approx_equal({ -1.5f, 0.0f }) || d5->approx_equal({ 0.0f, 1.5f })));
        const auto d6 = r2.intersect_depth(nnm::Circle2f({ -2.0f, 2.5f }, 1.0f));
        TEST_ASSERT(d6.has_value() && d6->approx_equal({ -1.5f, 0.0f }));
        const auto d7 = r3.intersect_depth(nnm::Circle2f({ 2.0f, 0.5f }, 2.0f));
        TEST_ASSERT_FALSE(d7.has_value());
        const auto d8 = r3.intersect_depth(nnm::Circle2f({ 5.0f, -4.0f }, 4.0f));
        TEST_ASSERT(d8.has_value() && d8->approx_equal({ 0.0f, -3.5f }));
    }

    test_section("intersects(const Triangle2&)");
    {
        TEST_ASSERT_FALSE(r2.intersects(nnm::Triangle2f({ 1.0f, 1.5f }, { 1.0f, 3.0f }, { 2.0f, 2.5f })));
        TEST_ASSERT(r2.intersects(nnm::Triangle2f({ -0.5f, 2.0f }, { 1.0f, 2.5f }, { 1.0f, 1.5f })));
        TEST_ASSERT(r2.intersects(nnm::Triangle2f({ 1.0f, 3.0f }, { -0.5f, 4.5f }, { 1.5f, 5.0f })));
        TEST_ASSERT(r2.intersects(nnm::Triangle2f({ -0.5f, 2.0f }, { -2.0f, 2.5f }, { -1.0f, 3.5f })));
        TEST_ASSERT(r1.intersects(nnm::Triangle2f({ 3.0f, -0.5f }, { 4.0f, -2.0f }, { 3.0f, -2.0f })));
        TEST_ASSERT_FALSE(r1.intersects(nnm::Triangle2f({ 5.2f, -1.8f }, { 3.8f, -1.2f }, { 4.2f, -1.8f })));
        TEST_ASSERT(r2.intersects(nnm::Triangle2f({ -2.0f, -7.0f }, { -4.0f, 5.0f }, { 3.0f, 5.0f })));
    }

    test_section("intersect_depth(const Triangle2&)");
    {
        const auto d1 = r2.intersect_depth(nnm::Triangle2f({ 1.0f, 1.5f }, { 1.0f, 3.0f }, { 2.0f, 2.5f }));
        TEST_ASSERT_FALSE(d1.has_value());
        const auto d2 = r2.intersect_depth(nnm::Triangle2f({ -0.5f, 2.0f }, { 1.0f, 2.5f }, { 1.0f, 1.5f }));
        TEST_ASSERT(d2.has_value() && d2->approx_equal({ 1.0f, 0.0f }));
        const auto d3 = r2.intersect_depth(nnm::Triangle2f({ 1.0f, 3.0f }, { -0.5f, 4.5f }, { 1.5f, 5.0f }));
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ 0.25f, 0.25f }));
        const auto d4 = r2.intersect_depth(nnm::Triangle2f({ -0.5f, 2.0f }, { -2.0f, 2.5f }, { -1.0f, 3.5f }));
        TEST_ASSERT(d4.has_value() && (d4->approx_equal({ 0.0f, 2.0f }) || d4->approx_equal({ -2.0f, 0.0f })))
        ;const auto d5 = r1.intersect_depth(nnm::Triangle2f({ 3.0f, -0.5f }, { 4.0f, -2.0f }, { 3.0f, -2.0f }));
        TEST_ASSERT(d5.has_value() && d5->approx_equal({ 0.482050896f, 0.0f }));
        const auto d6 = r1.intersect_depth(nnm::Triangle2f({ 5.2f, -1.8f }, { 3.8f, -1.2f }, { 4.2f, -1.8f }));
        TEST_ASSERT_FALSE(d6.has_value());
    }

    test_section("intersects(const Rectangle2&)");
    {
        TEST_ASSERT(r1.intersects(r2));
        TEST_ASSERT(r2.intersects(r1));
        TEST_ASSERT(r1.intersects(r3));
        TEST_ASSERT(r3.intersects(r1));
        TEST_ASSERT_FALSE(r2.intersects(r3));
        TEST_ASSERT_FALSE(r3.intersects(r2));
        TEST_ASSERT(r2.intersects(nnm::Rectangle2f({ -0.5f, -0.5f }, { 5.0f, 11.0f }, 0.0f)));
        TEST_ASSERT(nnm::Rectangle2f({ -0.5f, -0.5f }, { 5.0f, 11.0f }, 0.0f).intersects(r2));
    }

    test_section("intersect_depth(const Rectangle2&)");
    {
        const auto d1 = r1.intersect_depth(r2);
        TEST_ASSERT(d1.has_value() && d1->approx_equal({ 0.0f, 0.299038172f }));
        const auto d2 = r2.intersect_depth(r1);
        TEST_ASSERT(d2.has_value() && d2->approx_equal({ 0.0f, -0.299038172f }));
        const auto d3 = r1.intersect_depth(r3);
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ 1.14054465f, -0.658493757f }));
        const auto d4 = r3.intersect_depth(r1);
        TEST_ASSERT(d4.has_value() && d4->approx_equal({ -1.14054465f, 0.658493757f }));
        const auto d5 = r2.intersect_depth(r3);
        TEST_ASSERT_FALSE(d5.has_value());
        const auto d6 = r3.intersect_depth(r2);
        TEST_ASSERT_FALSE(d6.has_value());
        const auto d7 = r2.intersect_depth(nnm::Rectangle2f({ -0.5f, -0.5f }, { 5.0f, 11.0f }, 0.0f));
        TEST_ASSERT(d7.has_value() && d7->approx_equal({ 3.5f, 0.0f }));
        const auto d8 = nnm::Rectangle2f({ -0.5f, -0.5f }, { 5.0f, 11.0f }, 0.0f).intersect_depth(r2);
        TEST_ASSERT(d8.has_value() && d8->approx_equal({ -3.5f, 0.0f }));
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT_FALSE(nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersects(a1));
        TEST_ASSERT(nnm::Rectangle2f({ 1.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersects(a1));
        TEST_ASSERT(nnm::Rectangle2f({ 1.0f, 3.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersects(a1));
        TEST_ASSERT(nnm::Rectangle2f({ -1.0f, 0.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersects(a1));
    }

    test_section("intersect_depth(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto i1 = nnm::Rectangle2f({ 3.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersect_depth(a1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Rectangle2f({ 1.0f, 1.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersect_depth(a1);
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f }));
        const auto i3 = nnm::Rectangle2f({ 1.0f, 3.0f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersect_depth(a1);
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0f, -0.5f }));
        const auto i4 = nnm::Rectangle2f({ -1.0f, 0.5f }, { 1.0f, 2.0f }, nnm::pi<float>() / 2.0f).intersect_depth(a1);
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ 2.0f, 0.0f }));
    }

    test_section("translate");
    {
        constexpr auto t1 = r1.translate({ 1.0f, -2.0f });
        TEST_ASSERT(t1.approx_equal({ { 2.0f, -4.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f }));
    }

    test_section("rotate_at");
    {
        const auto t1 = r1.rotate_at({ 1.0f, -1.0f }, -nnm::pi<float>() / 4.0f);
        TEST_ASSERT(t1.approx_equal({ { 0.292893231f, -1.70710683f }, { 3.0f, 4.0f }, nnm::pi<float>() / 12.0f }));
    }

    test_section("rotate");
    {
        const auto t1 = r1.rotate(nnm::pi<float>());
        TEST_ASSERT(t1.approx_equal({ { -1.0f, 2.0f }, { 3.0f, 4.0f }, -2.0f * nnm::pi<float>() / 3.0f }))
    ;}

    test_section("scale_at");
    {
        constexpr auto t1 = r1.scale_at({ 1.0f, -1.0f }, { -1.5f, 2.0f });
        TEST_ASSERT(t1.approx_equal({ { 1.0f, -3.0f }, { -4.5f, 8.0f }, nnm::pi<float>() / 3.0f }));
    }

    test_section("scale");
    {
        constexpr auto t1 = r1.scale({ 2.0f, -0.5f });
        TEST_ASSERT(t1.approx_equal({ { 2.0f, 1.0f }, { 6.0f, -2.0f }, nnm::pi<float>() / 3.0f }));
    }

    test_section("coincident");
    {
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f)));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { -3.0f, 4.0f }, 0.0f)));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { 3.0f, -4.0f }, 0.0f)));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { -3.0f, -4.0f }, 0.0f)));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { 3.0f, 4.0f }, nnm::pi<float>())));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { -3.0f, 4.0f }, nnm::pi<float>())));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { 3.0f, -4.0f }, nnm::pi<float>())));
        TEST_ASSERT(r2.coincident(nnm::Rectangle2f({ -1.0f, 2.0f }, { -3.0f, -4.0f }, nnm::pi<float>())));
    }

    test_section("approx_equal");
    {
        constexpr auto result = r1.approx_equal(r1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1.approx_equal(r2));
        TEST_ASSERT_FALSE(r2.approx_equal(r3));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = r1 == r1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1 == r2);
    }

    test_section("operator!=");
    {
        constexpr auto result = r1 != r2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r2 != r2);
    }

    test_section("operator<");
    {
        constexpr auto result = r2 < r1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1 < r2);
        TEST_ASSERT_FALSE(r1 < r1);
        TEST_ASSERT_FALSE(r2 < r2);
    }
}

