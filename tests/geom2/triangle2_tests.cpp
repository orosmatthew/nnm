#include "tests.hpp"

void triangle2_tests()
{
    test_case("Triangle2");

    test_section("Triangle()");
    {
        constexpr nnm::Triangle2f t;
        TEST_ASSERT(t.vertices[0] == nnm::Point2f::zero());
        TEST_ASSERT(t.vertices[1] == nnm::Point2f::zero());
        TEST_ASSERT(t.vertices[2] == nnm::Point2f::zero());
    }

    test_section("Triangle2(const Vector2&, const Vector2&, const Vector2&)");
    {
        constexpr nnm::Triangle2f t { { 1.0f, -2.0f }, { -3.0f, 4.0f }, { 5.0f, 6.0f } };
        TEST_ASSERT(t.vertices[0] == nnm::Point2f(1.0f, -2.0f));
        TEST_ASSERT(t.vertices[1] == nnm::Point2f(-3.0f, 4.0f));
        TEST_ASSERT(t.vertices[2] == nnm::Point2f(5.0f, 6.0f));
    }

    test_section("Triangle2(const Triangle2<Other>&)");
    {
        constexpr nnm::Triangle2d t1 { { 1.0, -2.0 }, { -3.0, 4.0 }, { 5.0, 6.0 } };
        constexpr nnm::Triangle2f t2 { t1 };
        TEST_ASSERT(t2.vertices[0].approx_equal({ 1.0f, -2.0f }));
        TEST_ASSERT(t2.vertices[1].approx_equal({ -3.0f, 4.0f }));
        TEST_ASSERT(t2.vertices[2].approx_equal({ 5.0f, 6.0f }));
    }

    constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
    constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
    constexpr nnm::Triangle2f tri3 { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } };
    constexpr nnm::Triangle2f tri4 { { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };

    test_section("edge");
    {
        constexpr auto e0 = tri1.edge(0);
        TEST_ASSERT(e0.approx_equal({ { -4.0f, 2.0f }, { -3.0f, -4.0f } }));
        constexpr auto e1 = tri1.edge(1);
        TEST_ASSERT(e1.approx_equal({ { -3.0f, -4.0f }, { 1.0f, 4.0f } }));
        constexpr auto e2 = tri1.edge(2);
        TEST_ASSERT(e2.approx_equal({ { 1.0f, 4.0f }, { -4.0f, 2.0f } }));
    }

    test_section("centroid");
    {
        constexpr auto result = tri1.centroid();
        TEST_ASSERT(result.approx_equal({ -2.0f, 0.666666667f }));
        TEST_ASSERT(tri2.centroid().approx_equal({ -2.0f, 0.666666667f }));
        TEST_ASSERT(tri3.centroid().approx_equal({ 0.0f, 0.0f }));
    }

    test_section("circumcenter");
    {
        const auto c1 = tri1.circumcenter();
        TEST_ASSERT(c1.has_value() && c1->approx_equal({ -0.125f, -0.4375f }));
        const auto c2 = tri2.circumcenter();
        TEST_ASSERT(c2.has_value() && c2->approx_equal({ -0.125f, -0.4375f }));
        const auto c3 = tri3.circumcenter();
        TEST_ASSERT_FALSE(c3.has_value());
        const auto c4 = tri4.circumcenter();
        TEST_ASSERT_FALSE(c4.has_value());
    }

    test_section("perimeter");
    {
        TEST_ASSERT(nnm::approx_equal(tri1.perimeter(), 20.412199f));
        TEST_ASSERT(nnm::approx_equal(tri2.perimeter(), 20.412199f));
        TEST_ASSERT(nnm::approx_equal(tri3.perimeter(), 4.0f));
    }

    test_section("incenter");
    {
        const auto i1 = tri1.incenter();
        TEST_ASSERT(i1.has_value() && i1->approx_equal({ -2.2461969f, 1.01306745f }));
        const auto i2 = tri2.incenter();
        TEST_ASSERT(i2.has_value() && i2->approx_equal({ -2.2461969f, 1.01306745f }));
        const auto i3 = tri3.incenter();
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = tri4.incenter();
        TEST_ASSERT_FALSE(i4.has_value());
    }

    test_section("orthocenter");
    {
        const auto o1 = tri1.orthocenter();
        TEST_ASSERT(o1.has_value() && o1->approx_equal({ -5.75f, 2.875f }));
        const auto o2 = tri2.orthocenter();
        TEST_ASSERT(o2.has_value() && o2->approx_equal({ -5.75f, 2.875f }));
        const auto o3 = tri3.orthocenter();
        TEST_ASSERT_FALSE(o3.has_value());
        const auto o4 = tri4.orthocenter();
        TEST_ASSERT_FALSE(o4.has_value());
    }

    test_section("area");
    {
        constexpr auto result = tri1.area();
        TEST_ASSERT(nnm::approx_equal(result, 16.0f));
        TEST_ASSERT(nnm::approx_equal(tri2.area(), 16.0f));
    }

    test_section("median");
    {
        constexpr auto result = tri1.median(0);
        TEST_ASSERT(result.approx_equal({ { -4.0f, 2.0f }, { -1.0f, 0.0f } }));
        TEST_ASSERT(tri1.median(1).approx_equal({ { -3.0f, -4.0f }, { -1.5f, 3.0f } }));
        TEST_ASSERT(tri1.median(2).approx_equal({ { 1.0f, 4.0f }, { -3.5f, -1.0f } }));
        TEST_ASSERT(tri2.median(0).approx_equal({ { -3.0f, -4.0f }, { -1.5f, 3.0f } }));
        TEST_ASSERT(tri2.median(1).approx_equal({ { 1.0f, 4.0f }, { -3.5f, -1.0f } }));
        TEST_ASSERT(tri2.median(2).approx_equal({ { -4.0f, 2.0f }, { -1.0f, 0.0f } }));
    }

    test_section("perpendicular_bisector");
    {
        TEST_ASSERT(
            tri1.perpendicular_bisector(0).coincident(nnm::Line2f::from_point_slope({ -3.5f, -1.0f }, 0.166666667f)));
        TEST_ASSERT(tri1.perpendicular_bisector(1).coincident(nnm::Line2f::from_point_slope({ -1.0f, 0.0f }, -0.5f)));
        TEST_ASSERT(tri1.perpendicular_bisector(2).coincident(nnm::Line2f::from_point_slope({ -1.5f, 3.0f }, -2.5f)))
        TEST_ASSERT(tri2.perpendicular_bisector(0).coincident(nnm::Line2f::from_point_slope({ -1.0f, 0.0f }, -0.5f)));
        TEST_ASSERT(tri2.perpendicular_bisector(1).coincident(nnm::Line2f::from_point_slope({ -1.5f, 3.0f }, -2.5f)));
        TEST_ASSERT(
            tri2.perpendicular_bisector(2).coincident(nnm::Line2f::from_point_slope({ -3.5f, -1.0f }, 0.166666667f)));
    }

    test_section("angle");
    {
        TEST_ASSERT(nnm::approx_equal(tri1.angle(0), nnm::radians(102.339087f)));
        TEST_ASSERT(nnm::approx_equal(tri1.angle(1), nnm::radians(36.02737339f)));
        TEST_ASSERT(nnm::approx_equal(tri1.angle(2), nnm::radians(41.6335393f)));
        TEST_ASSERT(nnm::approx_equal(tri2.angle(0), nnm::radians(36.02737339f)));
        TEST_ASSERT(nnm::approx_equal(tri2.angle(1), nnm::radians(41.6335393f)));
        TEST_ASSERT(nnm::approx_equal(tri2.angle(2), nnm::radians(102.339087f)));
        TEST_ASSERT(nnm::approx_zero(tri3.angle(0)));
        TEST_ASSERT(nnm::approx_zero(tri4.angle(0)));
    }

    test_section("angle_bisector");
    {
        TEST_ASSERT(tri1.angle_bisector(0).coincident(nnm::Line2f::from_point_slope({ -4.0f, 2.0f }, -0.56273853f)));
        TEST_ASSERT(tri1.angle_bisector(1).coincident(nnm::Line2f::from_point_slope({ -3.0f, -4.0f }, 6.650367627f)));
        TEST_ASSERT(tri1.angle_bisector(2).coincident(nnm::Line2f::from_point_slope({ 1.0f, 4.0f }, 0.92013288f)));
        TEST_ASSERT(tri2.angle_bisector(0).coincident(nnm::Line2f::from_point_slope({ -3.0f, -4.0f }, 6.650367627f)));
        TEST_ASSERT(tri2.angle_bisector(1).coincident(nnm::Line2f::from_point_slope({ 1.0f, 4.0f }, 0.92013288f)));
        TEST_ASSERT(tri2.angle_bisector(2).coincident(nnm::Line2f::from_point_slope({ -4.0f, 2.0f }, -0.56273853f)));
    }

    test_section("normal");
    {
        TEST_ASSERT(tri1.normal(0).approx_equal({ -0.9863939238f, -0.1643989873f }));
        TEST_ASSERT(tri1.normal(1).approx_equal({ 0.894427191f, -0.4472135955f }));
        TEST_ASSERT(tri1.normal(2).approx_equal({ -0.3713906764f, 0.9284766909f }));

        TEST_ASSERT(tri2.normal(0).approx_equal({ 0.894427191f, -0.4472135955f }));
        TEST_ASSERT(tri2.normal(1).approx_equal({ -0.3713906764f, 0.9284766909f }));
        TEST_ASSERT(tri2.normal(2).approx_equal({ -0.9863939238f, -0.1643989873f }));
    }

    test_section("altitude");
    {
        const auto a1 = tri1.altitude(0);
        TEST_ASSERT(a1.has_value() && a1->approx_equal({ { -4.0f, 2.0f }, { -0.8f, 0.4f } }));
        const auto a2 = tri1.altitude(1);
        TEST_ASSERT(a2.has_value() && a2->approx_equal({ { -3.0f, -4.0f }, { -5.2069f, 1.51724f } }));
        const auto a3 = tri1.altitude(2);
        TEST_ASSERT(a3.has_value() && a3->approx_equal({ { 1.0f, 4.0f }, { -4.189189f, 3.135131f } }));

        const auto a4 = tri2.altitude(0);
        TEST_ASSERT(a4.has_value() && a4->approx_equal({ { -3.0f, -4.0f }, { -5.2069f, 1.51724f } }));
        const auto a5 = tri2.altitude(1);
        TEST_ASSERT(a5.has_value() && a5->approx_equal({ { 1.0f, 4.0f }, { -4.189189f, 3.135131f } }));
        const auto a6 = tri2.altitude(2);
        TEST_ASSERT(a6.has_value() && a6->approx_equal({ { -4.0f, 2.0f }, { -0.8f, 0.4f } }));

        const auto a7 = tri3.altitude(0);
        TEST_ASSERT(a7.has_value() && a7->approx_equal({ { -1.0f, 0.0f }, { -1.0f, 0.0f } }));
        const auto a8 = tri3.altitude(1);
        TEST_ASSERT(a8.has_value() && a8->approx_equal({ { 0.0f, 0.0f }, { 0.0f, 0.0f } }));
        const auto a9 = tri3.altitude(2);
        TEST_ASSERT(a9.has_value() && a9->approx_equal({ { 1.0f, 0.0f }, { 1.0f, 0.0f } }))

        TEST_ASSERT_FALSE(tri4.altitude(0).has_value());
        TEST_ASSERT_FALSE(tri4.altitude(1).has_value());
        TEST_ASSERT_FALSE(tri4.altitude(2).has_value());
    }

    test_section("lerp_point");
    {
        constexpr auto result = tri1.lerp_point({ 0.5f, 0.1f, 0.4f });
        TEST_ASSERT(result.approx_equal({ -1.9f, 2.2f }));
        TEST_ASSERT(tri2.lerp_point({ 0.1f, 0.4f, 0.5f }).approx_equal({ -1.9f, 2.2f }));
        TEST_ASSERT(tri1.lerp_point({ 0.5f, -1.5f, 100.0f }).approx_equal({ 102.5f, 407.0f }));
        TEST_ASSERT(tri2.lerp_point({ -1.5f, 100.0f, 0.5f }).approx_equal({ 102.5f, 407.0f }));
    }

    test_section("barycentric_unchecked");
    {
        constexpr auto r1 = tri1.barycentric_unchecked({ 0.0f, 0.0f });
        TEST_ASSERT(tri1.lerp_point(r1).approx_equal({ 0.0f, 0.0f }));
        constexpr auto r2 = tri2.barycentric_unchecked({ -2.0f, 1.0f });
        TEST_ASSERT(tri2.lerp_point(r2).approx_equal({ -2.0f, 1.0f }));
    }

    test_section("barycentric");
    {
        constexpr auto b1 = tri1.barycentric({ 0.0f, 0.0f });
        TEST_ASSERT_FALSE(b1.has_value());
        constexpr auto b2 = tri2.barycentric({ -2.0f, 1.0f });
        TEST_ASSERT(b2.has_value() && tri2.lerp_point(*b2).approx_equal({ -2.0f, 1.0f }));
        constexpr auto b3 = tri3.barycentric({ 0.0f, 1.0f });
        TEST_ASSERT_FALSE(b3.has_value());
        constexpr auto b4 = tri3.barycentric({ 0.5f, 0.0f });
        TEST_ASSERT_FALSE(b4.has_value());
    }

    test_section("circumcircle");
    {
        const auto c1 = tri1.circumcircle();
        TEST_ASSERT(c1.has_value() && c1->approx_equal({ { -0.125f, -0.4375f }, 4.577885f }));
        const auto c2 = tri2.circumcircle();
        TEST_ASSERT(c2.has_value() && c2->approx_equal({ { -0.125f, -0.4375f }, 4.577885f }));
        const auto c3 = nnm::Triangle2f({ -4.0f, 4.0f }, { -4.0f, 8.0f }, { 4.0f, 4.0f }).circumcircle();
        TEST_ASSERT(c3.has_value() && c3->approx_equal({ { 0.0f, 6.0f }, 4.47213595f }));
        const auto c4 = tri3.circumcircle();
        TEST_ASSERT_FALSE(c4.has_value());
        const auto c5 = tri4.circumcircle();
        TEST_ASSERT_FALSE(c5.has_value());
    }

    test_section("incircle");
    {
        const auto i1 = tri1.incircle();
        TEST_ASSERT(i1.has_value() && i1->approx_equal({ { -2.24619675f, 1.01306748f }, 1.5676899f }));
        const auto i2 = tri2.incircle();
        TEST_ASSERT(i2.has_value() && i2->approx_equal({ { -2.24619675f, 1.01306748f }, 1.5676899f }));
        const auto i3 = nnm::Triangle2f({ -4.0f, 4.0f }, { -4.0f, 8.0f }, { 4.0f, 4.0f }).incircle();
        TEST_ASSERT(i3.has_value() && i3->approx_equal(nnm::Circle2f { { -2.47213595f, 5.52786405f }, 1.52786398f }));
        const auto i4 = tri3.incircle();
        TEST_ASSERT_FALSE(i4.has_value());
    }

    test_section("collinear");
    {
        constexpr auto result = tri1.collinear();
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(tri2.collinear());
        TEST_ASSERT(tri3.collinear());
        TEST_ASSERT(tri4.collinear());
    }

    test_section("contains");
    {
        constexpr auto result = tri1.contains({ 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(tri2.contains({ 0.0f, 0.0f }));
        TEST_ASSERT(tri1.contains({ -2.0f, 1.0f }));
        TEST_ASSERT(tri2.contains({ -2.0f, 1.0f }));
        TEST_ASSERT(tri1.contains({ 1.0f, 4.0f }));
        TEST_ASSERT(tri2.contains({ 1.0f, 4.0f }));
        TEST_ASSERT(tri1.contains({ -1.0f, 0.0f }));
        TEST_ASSERT(tri2.contains({ -1.0f, 0.0f }));
        TEST_ASSERT_FALSE(tri3.contains({ 0.0f, 1.0f }));
        TEST_ASSERT(tri3.contains({ -0.5f, 0.0f }));
        TEST_ASSERT_FALSE(tri4.contains({ 1.0f, 1.0f }));
        TEST_ASSERT(tri4.contains({ 0.0f, 0.0f }));
    }

    test_section("signed_distance");
    {
        TEST_ASSERT(nnm::approx_equal(tri1.signed_distance({ -1.0f, 2.0f }), -0.894427f));
        TEST_ASSERT(nnm::approx_equal(tri2.signed_distance({ -1.0f, 2.0f }), -0.894427f));
        TEST_ASSERT(nnm::approx_equal(tri1.signed_distance({ 1.0f, 2.0f }), 0.894427f));
        TEST_ASSERT(nnm::approx_equal(tri2.signed_distance({ 1.0f, 2.0f }), 0.894427f));
        TEST_ASSERT(nnm::approx_zero(tri1.signed_distance({ -1.0f, 0.0f })));
        TEST_ASSERT(nnm::approx_zero(tri2.signed_distance({ -1.0f, 0.0f })));
        TEST_ASSERT(nnm::approx_equal(tri3.signed_distance({ 0.0f, 1.0f }), 1.0f));
        TEST_ASSERT(nnm::approx_zero(tri3.signed_distance({ -0.5f, 0.0f })));
        TEST_ASSERT(nnm::approx_equal(tri4.signed_distance({ 1.0f, 0.0f }), 1.0f));
        TEST_ASSERT(nnm::approx_zero(tri4.signed_distance({ 0.0f, 0.0f })));
    }

    test_section("distance(const Vector2&)");
    {
        TEST_ASSERT(nnm::approx_equal(tri1.distance({ -1.0f, 2.0f }), 0.0f));
        TEST_ASSERT(nnm::approx_equal(tri2.distance({ -1.0f, 2.0f }), 0.0f));
        TEST_ASSERT(nnm::approx_equal(tri1.distance({ 1.0f, 2.0f }), 0.894427f));
        TEST_ASSERT(nnm::approx_equal(tri2.distance({ 1.0f, 2.0f }), 0.894427f));
        TEST_ASSERT(nnm::approx_zero(tri1.distance({ -1.0f, 0.0f })));
        TEST_ASSERT(nnm::approx_zero(tri2.distance({ -1.0f, 0.0f })));
    }

    test_section("distance(const Line2&)");
    {
        const auto d1 = tri1.distance(nnm::Line2f::from_points({ -2.0f, 2.0f }, { 1.0f, 1.0f }));
        const auto d1n = tri2.distance(nnm::Line2f::from_points({ -2.0f, 2.0f }, { 1.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        TEST_ASSERT(nnm::approx_zero(d1n));
        const auto d2 = tri1.distance(nnm::Line2f::from_points({ 1.0f, 2.0f }, { 0.0f, -2.0f }));
        const auto d2n = tri2.distance(nnm::Line2f::from_points({ 1.0f, 2.0f }, { 0.0f, -2.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.485071272f));
        TEST_ASSERT(nnm::approx_equal(d2n, 0.485071272f));
        const auto d3 = tri1.distance(nnm::Line2f::from_points({ 0.0f, 0.0f }, { 1.0f, 2.0f }));
        const auto d3n = tri2.distance(nnm::Line2f::from_points({ 0.0f, 0.0f }, { 1.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.894427f));
        TEST_ASSERT(nnm::approx_equal(d3n, 0.894427f));
    }

    test_section("distance(const Ray2&)");
    {
        const auto d1 = tri1.distance(nnm::Ray2f::from_point_to_point({ -2.0f, 1.0f }, { 1.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = tri1.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { -2.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = tri1.distance(nnm::Ray2f::from_point_to_point({ 0.0f, 1.0f }, { 1.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.447214f));
        const auto d4 = tri1.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 1.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = tri1.distance(nnm::Ray2f::from_point_to_point({ -4.0f, -5.0f }, { -2.0f, -4.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 0.447214f));
        const auto d6 = tri1.distance(nnm::Ray2f::from_point_to_point({ -3.0f, -4.5f }, { -2.5f, -5.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 0.5f));
    }

    test_section("distance(const Segment2&)");
    {
        const auto d1 = tri1.distance(nnm::Segment2f({ 0.5f, 1.0f }, { -1.5f, 1.5f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = tri1.distance(nnm::Segment2f({ 0.5f, 2.0f }, { 0.5f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.447214f));
        const auto d3 = tri1.distance(nnm::Segment2f({ 0.5f, 1.0f }, { 1.0f, 2.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.89442719f));
        const auto d4 = tri1.distance(nnm::Segment2f({ -3.5f, -4.5f }, { -2.5f, -4.5f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.5f));
        const auto d5 = tri1.distance(nnm::Segment2f({ -2.0f, -4.5f }, { -2.5f, -4.5f }));
        TEST_ASSERT(nnm::approx_equal(d5, 0.7071067812f));
    }

    test_section("distance(const Circle2&)");
    {
        const auto d1 = tri1.distance(nnm::Circle2f({ 1.0f, 2.0f }, 1.0f));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = tri1.distance(nnm::Circle2f({ 2.0f, 1.0f }, 1.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 1.23606798f));
        const auto d3 = tri1.distance(nnm::Circle2f({ -3.0f, -5.0f }, 0.5f));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
        const auto d4 = tri1.distance(nnm::Circle2f({ -2.0f, 1.0f }, 1.0f));
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Triangle2&)");
    {
        const auto d1 = tri1.distance(nnm::Triangle2f({ -1.0f, 2.0f }, { 1.0f, 2.0f }, { 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = tri1.distance(nnm::Triangle2f({ 1.0f, 2.0f }, { 3.0f, 2.0f }, { 2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.894427f));
        const auto d3 = tri1.distance(nnm::Triangle2f({ 2.0f, 1.0f }, { 1.0f, 2.0f }, { 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.894427f));
        const auto d4 = tri1.distance(nnm::Triangle2f({ -2.0f, -6.0f }, { -5.0f, -6.0f }, { -4.0f, -4.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.7071067812f));
    }

    test_section("distance(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        const auto d1 = nnm::Triangle2f({ 1.5f, 0.5f }, { 3.0f, -0.5f }, { 1.5f, -1.5f }).distance(r1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Triangle2f({ 1.5f, 0.5f }, { 3.0f, -0.5f }, { 2.0f, -0.5f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.299038023f));
        const auto d3 = nnm::Triangle2f({ 2.0f, 1.0f }, { 1.0f, 1.5f }, { 1.0f, 2.5f }).distance(r2);
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
        const auto d4 = nnm::Triangle2f({ 0.5f, 5.5f }, { 1.5f, 4.0f }, { 0.5f, 4.5f }).distance(r2);
        TEST_ASSERT(nnm::approx_equal(d4, 0.447214f));
    }

    test_section("distance(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto d1 = nnm::Triangle2f({ 3.0f, 2.0f }, { 2.0f, 2.0f }, { 2.0f, 1.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.0f));
        const auto d2 = nnm::Triangle2f({ 0.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = nnm::Triangle2f({ 2.0f, 2.0f }, { 3.0f, 2.0f }, { 1.0f, 4.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.4472136f));
        const auto d4 = nnm::Triangle2f({ 2.0f, 4.0f }, { 3.0f, 5.0f }, { 3.0f, 4.0f }).distance(a1);
        TEST_ASSERT(nnm::approx_equal(d4, 1.4142135624f));
    }

    test_section("intersects(const Triangle2&)");
    {
        TEST_ASSERT(tri1.intersects(tri1));
        TEST_ASSERT(tri1.intersects(tri2));
        TEST_ASSERT(tri2.intersects(tri2));
        TEST_ASSERT(tri2.intersects(tri1));
        constexpr nnm::Triangle2f tri5 { { 1.0f, 2.0f }, { 4.0f, 5.0f }, { 2.0f, -3.0f } };
        TEST_ASSERT_FALSE(tri1.intersects(tri5));
        TEST_ASSERT_FALSE(tri5.intersects(tri1));
        TEST_ASSERT_FALSE(tri2.intersects(tri5));
        TEST_ASSERT_FALSE(tri5.intersects(tri2));
        constexpr nnm::Triangle2f tri6 { { 4.0f, 5.0f }, { -2.0f, 1.0f }, { 2.0f, -3.0f } };
        TEST_ASSERT(tri1.intersects(tri6));
        TEST_ASSERT(tri6.intersects(tri1));
        TEST_ASSERT(tri2.intersects(tri6));
        TEST_ASSERT(tri6.intersects(tri2));
        constexpr nnm::Triangle2f tri7 { { 2.0f, -3.0f }, { -5.0f, -1.0f }, { 4.0f, 5.0f } };
        TEST_ASSERT(tri1.intersects(tri7));
        TEST_ASSERT(tri7.intersects(tri1));
        TEST_ASSERT(tri2.intersects(tri7));
        TEST_ASSERT(tri7.intersects(tri1));
        TEST_ASSERT(tri1.intersects(nnm::Triangle2f({ -6.0f, 3.0f }, { 4.0f, 5.0f }, { -3.0f, -6.0f })));
        TEST_ASSERT(nnm::Triangle2f({ -6.0f, 3.0f }, { 4.0f, 5.0f }, { -3.0f, -6.0f }).intersects(tri1));
    }

    test_section("intersect_depth(const Triangle2&)");
    {
        const auto d1 = tri1.intersect_depth(tri1);
        TEST_ASSERT(d1.has_value() && (d1->approx_equal({ 3.2f, -1.6f }) || d1->approx_equal({ -3.2f, 1.6f })));
        const auto d2 = tri1.intersect_depth(tri2);
        TEST_ASSERT(d2.has_value() && (d2->approx_equal({ 3.2f, -1.6f }) || d2->approx_equal({ -3.2f, 1.6f })));
        constexpr nnm::Triangle2f tri5 { { 1.0f, 2.0f }, { 4.0f, 5.0f }, { 2.0f, -3.0f } };
        TEST_ASSERT_FALSE(tri1.intersect_depth(tri5).has_value());
        TEST_ASSERT_FALSE(tri5.intersect_depth(tri1).has_value());
        TEST_ASSERT_FALSE(tri2.intersect_depth(tri5).has_value());
        TEST_ASSERT_FALSE(tri5.intersect_depth(tri2).has_value());
        constexpr nnm::Triangle2f tri6 { { 4.0f, 5.0f }, { -2.0f, 1.0f }, { 2.0f, -3.0f } };
        const auto d3 = tri1.intersect_depth(tri6);
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ 1.2f, -0.6f }));
        const auto d4 = tri6.intersect_depth(tri2);
        TEST_ASSERT(d4.has_value() && d4->approx_equal({ -1.2f, 0.6f }));
        constexpr nnm::Triangle2f tri7 { { 2.0f, -3.0f }, { -5.0f, -1.0f }, { 4.0f, 5.0f } };
        const auto d5 = tri1.intersect_depth(tri7);
        TEST_ASSERT(d5.has_value() && d5->approx_equal({ 2.8f, -1.4f }));
        const auto d6 = tri7.intersect_depth(tri2);
        TEST_ASSERT(d6.has_value() && d6->approx_equal({ -2.8f, 1.4f }));
    }

    test_section("intersects(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        TEST_ASSERT_FALSE(nnm::Triangle2f({ 1.0f, 1.5f }, { 1.0f, 3.0f }, { 2.0f, 2.5f }).intersects(r2));
        TEST_ASSERT(nnm::Triangle2f({ -0.5f, 2.0f }, { 1.0f, 2.5f }, { 1.0f, 1.5f }).intersects(r2));
        TEST_ASSERT(nnm::Triangle2f({ 1.0f, 3.0f }, { -0.5f, 4.5f }, { 1.5f, 5.0f }).intersects(r2));
        TEST_ASSERT(nnm::Triangle2f({ -0.5f, 2.0f }, { -2.0f, 2.5f }, { -1.0f, 3.5f }).intersects(r2));
        TEST_ASSERT(nnm::Triangle2f({ 3.0f, -0.5f }, { 4.0f, -2.0f }, { 3.0f, -2.0f }).intersects(r1));
        TEST_ASSERT_FALSE(nnm::Triangle2f({ 5.2f, -1.8f }, { 3.8f, -1.2f }, { 4.2f, -1.8f }).intersects(r1));
        TEST_ASSERT(nnm::Triangle2f({ -2.0f, -7.0f }, { -4.0f, 5.0f }, { 3.0f, 5.0f }).intersects(r2));
    }

    test_section("intersect_depth(const Rectangle2&)");
    {
        constexpr nnm::Rectangle2f r1 { { 1.0f, -2.0f }, { 3.0f, 4.0f }, nnm::pi<float>() / 3.0f };
        constexpr nnm::Rectangle2f r2 { { -1.0f, 2.0f }, { 3.0f, 4.0f }, 0.0f };
        const auto d1 = nnm::Triangle2f({ 1.0f, 1.5f }, { 1.0f, 3.0f }, { 2.0f, 2.5f }).intersect_depth(r2);
        TEST_ASSERT_FALSE(d1.has_value());
        const auto d2 = nnm::Triangle2f({ -0.5f, 2.0f }, { 1.0f, 2.5f }, { 1.0f, 1.5f }).intersect_depth(r2);
        TEST_ASSERT(d2.has_value() && d2->approx_equal({ -1.0f, 0.0f }));
        const auto d3 = nnm::Triangle2f({ 1.0f, 3.0f }, { -0.5f, 4.5f }, { 1.5f, 5.0f }).intersect_depth(r2);
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ -0.25f, -0.25f }));
        const auto d4 = nnm::Triangle2f({ -0.5f, 2.0f }, { -2.0f, 2.5f }, { -1.0f, 3.5f }).intersect_depth(r2);
        TEST_ASSERT(d4.has_value() && (d4->approx_equal({ 0.0f, -2.0f }) || d4->approx_equal({ 2.0f, 0.0f })))
        const auto d5 = nnm::Triangle2f({ 3.0f, -0.5f }, { 4.0f, -2.0f }, { 3.0f, -2.0f }).intersect_depth(r1);
        TEST_ASSERT(d5.has_value() && d5->approx_equal({ -0.482050896f, 0.0f }));
        const auto d6 = nnm::Triangle2f({ 5.2f, -1.8f }, { 3.8f, -1.2f }, { 4.2f, -1.8f }).intersect_depth(r1);
        TEST_ASSERT_FALSE(d6.has_value());
    }

    test_section("intersects(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        TEST_ASSERT_FALSE(nnm::Triangle2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }).intersects(a1));
        TEST_ASSERT(nnm::Triangle2f({ 2.0f, 1.0f }, { 0.0f, 2.0f }, { 3.0f, 2.0f }).intersects(a1));
        TEST_ASSERT(nnm::Triangle2f({ -3.0f, 1.0f }, { 0.0f, 4.0f }, { -3.0f, 4.0f }).intersects(a1));
        TEST_ASSERT(nnm::Triangle2f({ -1.5f, -0.5f }, { -1.5f, -1.0f }, { -1.0f, -1.0f }).intersects(a1));
    }

    test_section("intersect_depth(const AlignedRectangle2&)");
    {
        constexpr nnm::AlignedRectangle2f a1 { { -2.0f, -2.0f }, { 1.0f, 3.0f } };
        const auto i1 = nnm::Triangle2f({ 2.0f, 1.0f }, { 2.0f, 2.0f }, { 3.0f, 2.0f }).intersect_depth(a1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Triangle2f({ 2.0f, 1.0f }, { 0.0f, 2.0f }, { 3.0f, 2.0f }).intersect_depth(a1);
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f }));
        const auto i3 = nnm::Triangle2f({ -3.0f, 1.0f }, { 0.0f, 4.0f }, { -3.0f, 4.0f }).intersect_depth(a1);
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ 0.5f, -0.5f }));
        const auto i4 = nnm::Triangle2f({ -1.5f, -0.5f }, { -1.5f, -1.0f }, { -1.0f, -1.0f }).intersect_depth(a1);
        TEST_ASSERT(i4.has_value() && i4.value().approx_equal({ 1.0f, 0.0f }));
    }

    test_section("intersects(const Line2&)");
    {
        constexpr auto result = tri1.intersects(nnm::Line2f::axis_x());
        TEST_ASSERT(result);
        TEST_ASSERT(tri2.intersects(nnm::Line2f::axis_x()));
        TEST_ASSERT(tri1.intersects(nnm::Line2f::axis_y()));
        TEST_ASSERT(tri2.intersects(nnm::Line2f::axis_y()));
        TEST_ASSERT_FALSE(tri1.intersects(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f })));
        TEST_ASSERT_FALSE(tri2.intersects(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f })));
        TEST_ASSERT(tri1.intersects(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f })));
        TEST_ASSERT(tri2.intersects(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f })));
    }

    test_section("edge_intersections(const Line2&)");
    {
        const auto result1 = tri1.edge_intersections(nnm::Line2f::axis_x());
        TEST_ASSERT(result1.approx_equal({ { -3.666667f, 0.0f }, { -1.0f, 0.0f } }));
        const auto result2 = tri2.edge_intersections(nnm::Line2f::axis_x());
        TEST_ASSERT(result2.approx_equal({ { -3.666667f, 0.0f }, { -1.0f, 0.0f } }));
        const auto result3 = tri1.edge_intersections(nnm::Line2f::axis_y());
        TEST_ASSERT(result3.approx_equal({ { 0.0f, 2.0f }, { 0.0f, 3.6f } }));
        const auto result4 = tri2.edge_intersections(nnm::Line2f::axis_y());
        TEST_ASSERT(result4.approx_equal({ { 0.0f, 2.0f }, { 0.0f, 3.6f } }));
        const auto result5 = tri1.edge_intersections(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }));
        TEST_ASSERT(result5.empty());
        const auto result6 = tri2.edge_intersections(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }));
        TEST_ASSERT(result6.empty());
        const auto result7 = tri1.edge_intersections(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }));
        TEST_ASSERT(result7.approx_equal({ { -3.0f, 2.4f }, { -0.538461548f, 0.923076923f } }));
        const auto result8 = tri2.edge_intersections(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }));
        TEST_ASSERT(result8.approx_equal({ { -3.0f, 2.4f }, { -0.538461548f, 0.923076923f } }));
    }

    test_section("intersects(const Ray2&)");
    {
        constexpr auto result = tri1.intersects(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result);
        TEST_ASSERT(tri2.intersects(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }));
        TEST_ASSERT(tri1.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }));
        TEST_ASSERT(tri2.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }));
        TEST_ASSERT(tri1.intersects(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f })));
        TEST_ASSERT(tri2.intersects(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f })));
        TEST_ASSERT(tri1.intersects(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f })));
        TEST_ASSERT(tri2.intersects(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f })));
        TEST_ASSERT_FALSE(tri1.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }));
        TEST_ASSERT_FALSE(tri2.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }));
    }

    test_section("edge_intersections(const Ray2&)");
    {
        const auto result1 = tri1.edge_intersections(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result1.approx_equal({ { -1.0f, 0.0f } }));
        const auto result2 = tri2.edge_intersections(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result2.approx_equal({ { -1.0f, 0.0f } }));
        const auto result3 = tri1.edge_intersections(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } });
        TEST_ASSERT(result3.approx_equal({ { -3.6666667f, 0.0f }, { -1.0f, 0.0f } }));
        const auto result4 = tri1.edge_intersections(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }));
        TEST_ASSERT(result4.approx_equal({ { -1.8571429f, 2.8571429f }, { -0.3333333f, 1.3333333f } }));
        const auto result5 = tri2.edge_intersections(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }));
        TEST_ASSERT(result5.approx_equal({ { -3.9411765f, 1.64705882f }, { -0.7142857f, 0.57142857f } }));
        const auto result6 = tri1.edge_intersections(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }));
        TEST_ASSERT(result6.approx_equal({ { 1.0f, 4.0f } }));
        const auto result7 = tri2.edge_intersections(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }));
        TEST_ASSERT(result7.approx_equal({ { 1.0f, 4.0f } }));
        const auto result8 = tri1.edge_intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result8.empty());
        const auto result9 = tri2.edge_intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } });
        TEST_ASSERT(result9.empty());
    }

    test_section("intersects(const Segment2&)");
    {
        constexpr auto result = tri1.intersects(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } });
        TEST_ASSERT(result);
        TEST_ASSERT(tri2.intersects(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }));
        TEST_ASSERT(tri1.intersects(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }))
        TEST_ASSERT(tri2.intersects(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }))
        TEST_ASSERT_FALSE(tri1.intersects(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }));
        TEST_ASSERT_FALSE(tri2.intersects(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }));
        TEST_ASSERT(tri1.intersects(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }));
        TEST_ASSERT(tri2.intersects(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }));
        TEST_ASSERT(tri1.intersects(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }));
        TEST_ASSERT(tri2.intersects(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }));
    }

    test_section("edge_intersections(const Segment2&)");
    {
        TEST_ASSERT(tri1.edge_intersections(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }).empty());
        TEST_ASSERT(tri2.edge_intersections(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }).empty());
        const auto result1 = tri1.edge_intersections(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } });
        TEST_ASSERT(result1.approx_equal({ { -0.5f, 1.0f } }));
        const auto result2 = tri2.edge_intersections(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } });
        TEST_ASSERT(result2.approx_equal({ { -0.5f, 1.0f } }));
        TEST_ASSERT(tri1.edge_intersections(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }).empty());
        TEST_ASSERT(tri2.edge_intersections(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }).empty());
        const auto result3 = tri1.edge_intersections(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } });
        TEST_ASSERT(result3.approx_equal({ { -1.0f, 0.0f } }));
        const auto result4 = tri2.edge_intersections(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } });
        TEST_ASSERT(result4.approx_equal({ { -1.0f, 0.0f } }));
        const auto result5 = tri1.edge_intersections(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } });
        TEST_ASSERT(result5.approx_equal({ { -3.7272727f, 0.36363636f }, { -0.33333333f, 1.3333333f } }));
        const auto result6 = tri2.edge_intersections(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } });
        TEST_ASSERT(result6.approx_equal({ { -3.7272727f, 0.36363636f }, { -0.33333333f, 1.3333333f } }));
    }

    test_section("intersects(const Circle2&)");
    {
        TEST_ASSERT(tri1.intersects(nnm::Circle2f({ -2.0f, 1.0f }, 1.0f)));
        TEST_ASSERT(tri1.intersects(nnm::Circle2f({ -2.0f, 1.0f }, 6.0f)));
        TEST_ASSERT_FALSE(tri1.intersects(nnm::Circle2f({ 1.0f, 1.0f }, 1.0f)));
        TEST_ASSERT(tri1.intersects(nnm::Circle2f({ 1.0f, 1.0f }, 3.0f)));
        TEST_ASSERT(tri1.intersects(nnm::Circle2f({ 1.0f, 2.0f }, 9.0f)));
    }

    test_section("intersect_depth(const Circle2&)");
    {
        const auto d1 = tri1.intersect_depth(nnm::Circle2f({ 1.0f, 2.0f }, 2.0f));
        TEST_ASSERT(d1.has_value() && d1->approx_equal({ 0.988854374f, -0.494427187f }));
        const auto d2 = tri2.intersect_depth(nnm::Circle2f({ 1.0f, 2.0f }, 2.0f));
        TEST_ASSERT(d2.has_value() && d2->approx_equal({ 0.988854374f, -0.494427187f }));
        const auto d3 = tri1.intersect_depth(nnm::Circle2f({ -2.0f, 1.0f }, 1.0f));
        TEST_ASSERT(d3.has_value() && d3->approx_equal({ 2.094427191f, -1.0472135955f }));
        const auto d4 = tri2.intersect_depth(nnm::Circle2f({ -2.0f, 1.0f }, 1.0f));
        TEST_ASSERT(d4.has_value() && d4->approx_equal({ 2.094427191f, -1.0472135955f }));
        const auto d5 = tri2.intersect_depth(nnm::Circle2f({ -3.0f, -5.0f }, 2.0f));
        TEST_ASSERT(d5.has_value() && d5->approx_equal({ 0.0f, -1.0f }));
        const auto d6 = tri1.intersect_depth(nnm::Circle2f({ -3.0f, -4.0f }, 1.0f));
        TEST_ASSERT(d6.has_value() && (d6->approx_equal(tri1.normal(0)) || d6->approx_equal(tri1.normal(1))));
        const auto d7 = tri1.intersect_depth(nnm::Circle2f({ -3.0f, -4.0f }, 1.0f));
        TEST_ASSERT(d7.has_value() && (d7->approx_equal(tri2.normal(0)) || d7->approx_equal(tri2.normal(2))));
        const auto d8 = tri1.intersect_depth(nnm::Circle2f({ -1.0f, 0.0f }, 1.0f));
        TEST_ASSERT(d8.has_value() && d8->approx_equal({ 0.894427191f, -0.4472135955f }));
        const auto d9 = tri2.intersect_depth(nnm::Circle2f({ -1.0f, 0.0f }, 1.0f));
        TEST_ASSERT(d9.has_value() && d9->approx_equal({ 0.894427191f, -0.4472135955f }));
        const auto d10 = tri1.intersect_depth(nnm::Circle2f({ -1.5f, 3.0f }, 2.0f));
        TEST_ASSERT(d10.has_value() && d10->approx_equal({ -0.7427813525f, 1.8569533819f }));
        const auto d11 = tri1.intersect_depth(nnm::Circle2f({ -1.5f, 3.0f }, 2.0f));
        TEST_ASSERT(d11.has_value() && d11->approx_equal({ -0.7427813525f, 1.8569533819f }));
        const auto d12 = tri1.intersect_depth(nnm::Circle2f({ 1.0f, 0.0f }, 1.0f));
        TEST_ASSERT_FALSE(d12.has_value());
        const auto d13 = tri2.intersect_depth(nnm::Circle2f({ 1.0f, 0.0f }, 1.0f));
        TEST_ASSERT_FALSE(d13.has_value());
    }

    test_section("equilateral");
    {
        constexpr auto result = tri1.equilateral();
        TEST_ASSERT_FALSE(result);
        constexpr nnm::Triangle2f tri5 { { 2.0f, -4.0f }, { 4.0f, -0.535898385f }, { 6.0f, -4.0f } };
        TEST_ASSERT(tri5.equilateral());
        constexpr nnm::Triangle2f tri6 { { -4.0f, 4.0f }, { 4.0f, 4.0f }, { -4.0f, 8.0f } };
        TEST_ASSERT_FALSE(tri6.equilateral());
        TEST_ASSERT_FALSE(tri3.equilateral());
        TEST_ASSERT(tri4.equilateral());
    }

    test_section("similar");
    {
        TEST_ASSERT(tri1.similar(tri1));
        TEST_ASSERT(tri1.similar(tri2));
        TEST_ASSERT(tri2.similar(tri1));
        TEST_ASSERT(tri2.similar(tri2));
        TEST_ASSERT_FALSE(tri1.similar(nnm::Triangle2f({ 4.0f, 4.0f }, { -4.0f, 4.0f }, { -4.0f, 8.0f })));
        TEST_ASSERT_FALSE(tri2.similar(nnm::Triangle2f({ 4.0f, 4.0f }, { -4.0f, 4.0f }, { -4.0f, 8.0f })));
        TEST_ASSERT(tri1.similar(nnm::Triangle2f({ 4.0f, -3.0f }, { -2.0f, -4.0f }, { -4.0f, 1.0f })));
        TEST_ASSERT(tri2.similar(nnm::Triangle2f({ 4.0f, -3.0f }, { -2.0f, -4.0f }, { -4.0f, 1.0f })));
        TEST_ASSERT(tri1.similar(
            nnm::Triangle2f(
                { 4.0f / 2.0f, -3.0f / 2.0f }, { -2.0f / 2.0f, -4.0f / 2.0f }, { -4.0f / 2.0f, 1.0f / 2.0f })));
        TEST_ASSERT(tri2.similar(
            nnm::Triangle2f(
                { 4.0f / 2.0f, -3.0f / 2.0f }, { -2.0f / 2.0f, -4.0f / 2.0f }, { -4.0f / 2.0f, 1.0f / 2.0f })));
        TEST_ASSERT_FALSE(tri1.similar(nnm::Triangle2f({ -2.0f, -4.0f }, { -2.0f, 1.0f }, { 4.0f, -3.0f })));
        TEST_ASSERT_FALSE(tri2.similar(nnm::Triangle2f({ -2.0f, -4.0f }, { -2.0f, 1.0f }, { 4.0f, -3.0f })));
    }

    test_section("right");
    {
        TEST_ASSERT_FALSE(tri1.right())
        constexpr nnm::Triangle2f tri5 { { 2.0f, -4.0f }, { 4.0f, -0.535898385f }, { 6.0f, -4.0f } };
        TEST_ASSERT_FALSE(tri5.right());
        constexpr nnm::Triangle2f tri6 { { -4.0f, 4.0f }, { 4.0f, 4.0f }, { -4.0f, 8.0f } };
        TEST_ASSERT(tri6.right());
        TEST_ASSERT_FALSE(tri3.right());
        TEST_ASSERT_FALSE(tri4.right());
    }

    test_section("translate");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].translate({ -1.0f, 2.0f }),
                                             tri1.vertices[1].translate({ -1.0f, 2.0f }),
                                             tri1.vertices[2].translate({ -1.0f, 2.0f }) };
        constexpr auto result = tri1.translate({ -1.0f, 2.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("rotate_at");
    {
        const nnm::Triangle2f expected { tri1.vertices[0].rotate_at({ -1.0f, 2.0f }, nnm::pi<float>() / 5.0f),
                                         tri1.vertices[1].rotate_at({ -1.0f, 2.0f }, nnm::pi<float>() / 5.0f),
                                         tri1.vertices[2].rotate_at({ -1.0f, 2.0f }, nnm::pi<float>() / 5.0f) };
        TEST_ASSERT(tri1.rotate_at({ -1.0f, 2.0f }, nnm::pi<float>() / 5.0f).approx_equal(expected));
    }

    test_section("rotate");
    {
        const nnm::Triangle2f expected { tri1.vertices[0].rotate(-nnm::pi<float>() / 3.0f),
                                         tri1.vertices[1].rotate(-nnm::pi<float>() / 3.0f),
                                         tri1.vertices[2].rotate(-nnm::pi<float>() / 3.0f) };
        TEST_ASSERT(tri1.rotate(-nnm::pi<float>() / 3.0f).approx_equal(expected));
    }

    test_section("scale_at");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].scale_at({ -2.0f, 3.0f }, { 0.5f, -3.0f }),
                                             tri1.vertices[1].scale_at({ -2.0f, 3.0f }, { 0.5f, -3.0f }),
                                             tri1.vertices[2].scale_at({ -2.0f, 3.0f }, { 0.5f, -3.0f }) };
        constexpr auto result = tri1.scale_at({ -2.0f, 3.0f }, { 0.5f, -3.0f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("scale");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].scale({ 3.0f, -0.5f }),
                                             tri1.vertices[1].scale({ 3.0f, -0.5f }),
                                             tri1.vertices[2].scale({ 3.0f, -0.5f }) };
        constexpr auto result = tri1.scale({ 3.0f, -0.5f });
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].shear_x_at({ 3.0f, -0.5f }, nnm::pi<float>() / 7.0f),
                                             tri1.vertices[1].shear_x_at({ 3.0f, -0.5f }, nnm::pi<float>() / 7.0f),
                                             tri1.vertices[2].shear_x_at({ 3.0f, -0.5f }, nnm::pi<float>() / 7.0f) };
        constexpr auto result = tri1.shear_x_at({ 3.0f, -0.5f }, nnm::pi<float>() / 7.0f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_x");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].shear_x(-nnm::pi<float>() / 7.0f),
                                             tri1.vertices[1].shear_x(-nnm::pi<float>() / 7.0f),
                                             tri1.vertices[2].shear_x(-nnm::pi<float>() / 7.0f) };
        constexpr auto result = tri1.shear_x(-nnm::pi<float>() / 7.0f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].shear_y_at({ 4.0f, -6.7f }, -nnm::pi<float>() / 6.0f),
                                             tri1.vertices[1].shear_y_at({ 4.0f, -6.7f }, -nnm::pi<float>() / 6.0f),
                                             tri1.vertices[2].shear_y_at({ 4.0f, -6.7f }, -nnm::pi<float>() / 6.0f) };
        constexpr auto result = tri1.shear_y_at({ 4.0f, -6.7f }, -nnm::pi<float>() / 6.0f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("shear_y");
    {
        constexpr nnm::Triangle2f expected { tri1.vertices[0].shear_y(nnm::pi<float>() / 6.0f),
                                             tri1.vertices[1].shear_y(nnm::pi<float>() / 6.0f),
                                             tri1.vertices[2].shear_y(nnm::pi<float>() / 6.0f) };
        constexpr auto result = tri1.shear_y(nnm::pi<float>() / 6.0f);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("coincident");
    {
        constexpr auto result = tri1.coincident(tri1);
        TEST_ASSERT(result);
        TEST_ASSERT(tri1.coincident(tri2));
        TEST_ASSERT(tri2.coincident(tri1));
        TEST_ASSERT(tri2.coincident(tri2));
        TEST_ASSERT_FALSE(tri1.coincident({ { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 5.0f } }));
        TEST_ASSERT_FALSE(tri2.coincident({ { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 5.0f } }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = tri1.approx_equal(tri1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(tri1.approx_equal(tri2));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = tri1 == tri1;
        TEST_ASSERT(result);
        TEST_ASSERT(tri2 == tri2);
        TEST_ASSERT_FALSE(tri1 == tri2);
        TEST_ASSERT_FALSE(tri2 == tri1);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = tri1 != tri1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(tri2 != tri2);
        TEST_ASSERT(tri1 != tri2);
        TEST_ASSERT(tri2 != tri1);
    }

    test_section("operator<");
    {
        constexpr auto result = tri1 < tri2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(tri2 < tri1);
        TEST_ASSERT_FALSE(tri1 < tri1);
        TEST_ASSERT_FALSE(tri2 < tri2);
    }
}

