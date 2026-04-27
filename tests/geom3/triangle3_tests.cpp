#include "tests.hpp"

void triangle3_tests()
{
    test_case("Triangle3");

    test_section("Triangle3()");
    {
        constexpr nnm::Triangle3f t1;
        TEST_ASSERT(t1.vertices[0].approx_equal(nnm::Point3f::zero()));
        TEST_ASSERT(t1.vertices[1].approx_equal(nnm::Point3f::zero()));
        TEST_ASSERT(t1.vertices[2].approx_equal(nnm::Point3f::zero()));
    }

    test_section("Triangle3(const Vector3&, const Vector3&, const Vector3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        TEST_ASSERT(t1.vertices[1].approx_equal({ -2.0f, 3.0f, -4.0f }));
        TEST_ASSERT(t1.vertices[0].approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(t1.vertices[2].approx_equal({ 4.0f, 0.0f, 2.0f }));
    }

    test_section("Triangle3(const Triangle3<Other>&)");
    {
        constexpr nnm::Triangle3d t1 { { 1.0, -2.0, 3.0 }, { -2.0, 3.0, -4.0 }, { 4.0, 0.0, 2.0 } };
        constexpr nnm::Triangle3f t2 { t1 };
        TEST_ASSERT(t2.vertices[1].approx_equal({ -2.0f, 3.0f, -4.0f }));
        TEST_ASSERT(t2.vertices[0].approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(t2.vertices[2].approx_equal({ 4.0f, 0.0f, 2.0f }));
    }

    constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
    constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
    constexpr nnm::Triangle3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };

    test_section("collapse_segment");
    {
        constexpr std::optional<nnm::Segment3f> r1 = t1.collapse_segment();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Segment3f> r2 = degen_line.collapse_segment();
        TEST_ASSERT(r2.has_value() && r2.value().coincident({ { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }));
        constexpr std::optional<nnm::Segment3f> r3 = degen_point.collapse_segment();
        TEST_ASSERT(r3.has_value() && r3.value().coincident({ { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } }));
    }

    test_section("collapse_point");
    {
        constexpr std::optional<nnm::Point3f> r1 = t1.collapse_point();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Point3f> r2 = degen_line.collapse_point();
        TEST_ASSERT_FALSE(r2.has_value());
        constexpr std::optional<nnm::Point3f> r3 = degen_point.collapse_point();
        TEST_ASSERT(r3.has_value() && r3.value().approx_equal({ 1.0f, 1.0f, 1.0f }));
    }

    test_section("edge");
    {
        constexpr nnm::Segment3f e0 = t1.edge(0);
        constexpr nnm::Segment3f e1 = t1.edge(1);
        constexpr nnm::Segment3f e2 = t1.edge(2);
        TEST_ASSERT(e0.approx_equal({ { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f } }));
        TEST_ASSERT(e1.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } }));
        TEST_ASSERT(e2.approx_equal({ { 4.0f, 0.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } }));
    }

    test_section("centroid");
    {
        constexpr nnm::Point3f c = t1.centroid();
        constexpr nnm::Point3f average = nnm::Point3f::from_vector(
            (t1.vertices[0].to_vector() + t1.vertices[1].to_vector() + t1.vertices[2].to_vector()) / 3.0f);
        TEST_ASSERT(c.approx_equal(average));
    }

    test_section("circumcenter");
    {
        const std::optional<nnm::Point3f> c1 = t1.circumcenter();
        TEST_ASSERT(c1.has_value() && c1->approx_equal({ 0.245901704f, 0.844262301f, -0.573770523f }));
        const std::optional<nnm::Point3f> c2 = degen_line.circumcenter();
        TEST_ASSERT_FALSE(c2.has_value());
    }

    test_section("perimeter");
    {
        const float p1 = t1.perimeter();
        TEST_ASSERT(nnm::approx_equal(p1, 21.85209097f));
        const float p2 = degen_line.perimeter();
        TEST_ASSERT(nnm::approx_equal(p2, 4.0f));
    }

    test_section("incenter");
    {
        const auto result = t1.incenter();
        TEST_ASSERT(result.has_value() && result->approx_equal({ 1.7370612086f, -0.3100402543f, 1.3845008086f }));
        TEST_ASSERT_FALSE(degen_line.incenter().has_value());
    }

    test_section("orthocenter");
    {
        const std::optional<nnm::Point3f> c1 = t1.orthocenter();
        TEST_ASSERT(c1.has_value() && c1->approx_equal({ 2.50819683f, -0.688524485f, 2.14754105f }));
        const std::optional<nnm::Point3f> c2 = degen_line.orthocenter();
        TEST_ASSERT_FALSE(c2.has_value());
    }

    constexpr nnm::Triangle3f t3 { { 4.0f, 0.0f, 2.0f }, { -2.0f, 3.0f, -4.0f }, { 1.0f, -2.0f, 3.0f } };

    test_section("area");
    {
        const float a1 = t1.area();
        TEST_ASSERT(nnm::approx_equal(a1, 16.5680415258f));
        const float a2 = degen_line.area();
        TEST_ASSERT(nnm::approx_zero(a2));
        const float a3 = t3.area();
        TEST_ASSERT(nnm::approx_equal(a3, 16.5680415258f));
    }

    test_section("median");
    {
        constexpr nnm::Segment3f m0 = t1.median(0);
        TEST_ASSERT(m0.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 1.0f, 1.5f, -1.0f } }));
        constexpr nnm::Segment3f m1 = t1.median(1);
        TEST_ASSERT(m1.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 2.5f, -1.0f, 2.5f } }));
        constexpr nnm::Segment3f m2 = t1.median(2);
        TEST_ASSERT(m2.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.5f, 0.5f, -0.5f } }));
    }

    test_section("perpendicular_bisector");
    {
        const std::optional<nnm::Line3f> pb0 = t1.perpendicular_bisector(0);
        TEST_ASSERT(
            pb0.has_value()
            && pb0->approx_equal({ { -0.5f, 0.5f, -0.5f }, { -0.904320657f, -0.417378753f, 0.0894383192f } }));
        const std::optional<nnm::Line3f> pb1 = t1.perpendicular_bisector(1);
        TEST_ASSERT(
            pb1.has_value()
            && pb1->approx_equal({ { 1.0f, 1.5f, -1.0f }, { 0.694107413f, 0.603571713f, -0.392321587f } }));
        const std::optional<nnm::Line3f> pb2 = t1.perpendicular_bisector(2);
        TEST_ASSERT(
            pb2.has_value()
            & pb2->approx_equal({ { 2.5f, -1.0f, 2.5f }, { 0.532327354f, -0.435540527f, 0.725900888f } }));
        const std::optional<nnm::Line3f> pb3 = degen_line.perpendicular_bisector(0);
        TEST_ASSERT_FALSE(pb3.has_value());
        const std::optional<nnm::Line3f> pb4 = degen_line.perpendicular_bisector(1);
        TEST_ASSERT_FALSE(pb4.has_value());
        const std::optional<nnm::Line3f> pb5 = degen_line.perpendicular_bisector(2);
        TEST_ASSERT_FALSE(pb5.has_value());
    }

    test_section("angle");
    {
        const float a0 = t1.angle(0);
        TEST_ASSERT(nnm::approx_equal(a0, 1.3339009374f));
        const float a1 = t1.angle(1);
        TEST_ASSERT(nnm::approx_equal(a1, 0.4160259987f));
        const float a2 = t1.angle(2);
        TEST_ASSERT(nnm::approx_equal(a2, 1.3916657175f));
        const float a3 = t3.angle(0);
        TEST_ASSERT(nnm::approx_equal(a3, 1.3916657175f));
        const float a4 = t3.angle(1);
        TEST_ASSERT(nnm::approx_equal(a4, 0.4160259987f));
        const float a5 = t3.angle(2);
        TEST_ASSERT(nnm::approx_equal(a5, 1.3339009374f));
    }

    test_section("angle_bisector");
    {
        const nnm::Line3f l1 = t1.angle_bisector(0);
        TEST_ASSERT(l1.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 0.300677031f, 0.689402819f, -0.659027338f } }));
        const nnm::Line3f l2 = t1.angle_bisector(1);
        TEST_ASSERT(l2.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 0.508951068f, -0.450794995f, 0.733316183f } }));
        const nnm::Line3f l3 = t1.angle_bisector(2);
        TEST_ASSERT(l3.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.956620216f, -0.131064415f, -0.260192215f } }));
        const nnm::Line3f l4 = t3.angle_bisector(0);
        TEST_ASSERT(l4.approx_equal({ { 4.0f, 0.0f, 2.0f }, { -0.956620216f, -0.131064415f, -0.260192215f } }));
        const nnm::Line3f l5 = t3.angle_bisector(1);
        TEST_ASSERT(l5.approx_equal({ { -2.0f, 3.0f, -4.0f }, { 0.508951068f, -0.450794995f, 0.733316183f } }));
        const nnm::Line3f l6 = t3.angle_bisector(2);
        TEST_ASSERT(l6.approx_equal({ { 1.0f, -2.0f, 3.0f }, { 0.300677031f, 0.689402819f, -0.659027338f } }));
    }

    test_section("altitude");
    {
        const std::optional<nnm::Segment3f> a1 = t1.altitude(0);
        TEST_ASSERT(
            a1.has_value() && a1->approx_equal({ { 1.0f, -2.0f, 3.0f }, { 3.55555534f, 0.22222209f, 1.5555557f } }));
        const std::optional<nnm::Segment3f> a2 = t1.altitude(1);
        TEST_ASSERT(
            a2.has_value()
            && a2->approx_equal({ { -2.0f, 3.0f, -4.0f }, { 2.71428585f, -0.857142687f, 2.42857122f } }));
        const std::optional<nnm::Segment3f> a3 = t1.altitude(2);
        TEST_ASSERT(
            a3.has_value() && a3->approx_equal({ { 4.0f, 0.0f, 2.0f }, { 0.710843325f, -1.51807225f, 2.32530117f } }));
        const std::optional<nnm::Segment3f> a4 = degen_line.altitude(0);
        TEST_ASSERT_FALSE(a4.has_value());
        const std::optional<nnm::Segment3f> a5 = degen_line.altitude(1);
        TEST_ASSERT_FALSE(a5.has_value());
        const std::optional<nnm::Segment3f> a6 = degen_line.altitude(2);
        TEST_ASSERT_FALSE(a6.has_value());
    }

    test_section("lerp_point");
    {
        constexpr nnm::Point3f p1 = t1.lerp_point({ 0.3f, 0.1f, 0.6f });
        constexpr nnm::Point3f expected1 = nnm::Point3f::from_vector(
            t1.vertices[0].to_vector() * 0.3f + t1.vertices[1].to_vector() * 0.1f + t1.vertices[2].to_vector() * 0.6f);
        TEST_ASSERT(p1.approx_equal(expected1));
        constexpr nnm::Point3f p2 = t3.lerp_point({ 0.25f, 0.56f, 0.19f });
        constexpr nnm::Point3f expected2 = nnm::Point3f::from_vector(
            t3.vertices[0].to_vector() * 0.25f + t3.vertices[1].to_vector() * 0.56f
            + t3.vertices[2].to_vector() * 0.19f);
        TEST_ASSERT(p2.approx_equal(expected2));
    }

    test_section("barycentric_unchecked");
    {
        const nnm::Vector3f w1 = t1.barycentric_unchecked({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(w1.approx_equal({ 0.3f, 0.1f, 0.6f }));
        const nnm::Vector3f w2 = t3.barycentric_unchecked({ 0.07f, 1.3f, -1.17f });
        TEST_ASSERT(w2.approx_equal({ 0.25f, 0.56f, 0.19f }));
    }

    test_section("barycentric");
    {
        const std::optional<nnm::Vector3f> w1 = t1.barycentric({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(w1.has_value() && w1->approx_equal({ 0.3f, 0.1f, 0.6f }));
        const std::optional<nnm::Vector3f> w2 = t3.barycentric({ 0.07f, 1.3f, -1.17f });
        TEST_ASSERT(w2.has_value() && w2->approx_equal({ 0.25f, 0.56f, 0.19f }));
        const std::optional<nnm::Vector3f> w3 = degen_line.barycentric(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(w3.has_value());
    }

    test_section("contains");
    {
        constexpr bool r1 = t1.contains({ 3.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.contains({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(r2);
        constexpr bool r3 = degen_line.contains({ 0.5f, 0.0f, 0.0f });
        TEST_ASSERT(r3);
        constexpr bool r4 = degen_line.contains({ 0.0f, 1.0f, 0.0f });
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = t1.contains({ 3.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(r5);
        constexpr bool r6 = t1.contains({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(r6);
        constexpr bool r7 = t1.contains(t1.vertices[2]);
        TEST_ASSERT(r7);
        constexpr bool r8 = t3.contains(t3.edge(1).midpoint());
        TEST_ASSERT(r8);
        constexpr bool r9 = degen_line.contains({ 0.0f, -100.0f, 0.0f });
        TEST_ASSERT_FALSE(r9);
    }

    test_section("contains_projected");
    {
        const bool r1 = t1.contains_projected({ 3.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(r1);
        const bool r2 = t1.contains_projected({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(r2);
        const bool r3 = degen_line.contains_projected({ 0.5f, 0.0f, 0.0f });
        TEST_ASSERT(r3);
        const bool r4 = degen_line.contains_projected({ 0.0f, 1.0f, 0.0f });
        TEST_ASSERT(r4);
        const bool r5 = t1.contains_projected({ 3.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(r5);
        const bool r6 = t1.contains_projected({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(r6);
        const bool r7 = t1.contains_projected(t1.vertices[2]);
        TEST_ASSERT(r7);
        const bool r8 = t3.contains_projected(t3.edge(1).midpoint());
        TEST_ASSERT(r8);
        const bool r9 = degen_line.contains_projected({ 0.0f, -100.0f, 0.0f });
        TEST_ASSERT(r9);
    }

    test_section("vertices_collinear");
    {
        constexpr bool r1 = t1.vertices_collinear();
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = degen_line.vertices_collinear();
        TEST_ASSERT(r2);
        constexpr bool r3 = t3.vertices_collinear();
        TEST_ASSERT_FALSE(r3);
    }

    test_section("coplanar(const Vector3&)");
    {
        const bool r1 = t1.coplanar(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar({ 2.5f, -0.3f, 1.7f });
        TEST_ASSERT(r2);
        const bool r3 = t1.coplanar({ 5.0009826255f, 0.9973796652f, 1.2891300792f });
        TEST_ASSERT(r3);
        const bool r4 = degen_line.coplanar({ 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(r4);
        const bool r5 = degen_line.coplanar({ 100.0f, 0.0f, 0.0f });
        TEST_ASSERT(r5);
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr bool r1 = t1.coplanar(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar(*nnm::Line3f::from_segment(t1.edge(0)));
        TEST_ASSERT(r2);
        const bool r3 = t1.coplanar(*nnm::Line3f::from_points(
            { 5.6279295263f, 0.2174812388f, 2.4491340955f }, { 3.7355435221f, 2.8096960263f, -1.3244196634f }));
        TEST_ASSERT(r3);
        constexpr bool r4 = degen_line.coplanar(nnm::Line3f::axis_x_offset(100.0f, -100.0f));
        TEST_ASSERT(r4);
        constexpr bool r5 = degen_line.coplanar(nnm::Line3f::axis_y());
        TEST_ASSERT(r5);
        constexpr bool r6 = degen_line.coplanar(nnm::Line3f::axis_y_offset(-100.0f, 100.0f));
        TEST_ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Ray3&)");
    {
        const bool r1 = t1.coplanar(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r1);
        const bool r2 = t1.coplanar(nnm::Ray3f::from_point_to_point(t1.edge(0).start, t1.edge(0).end));
        TEST_ASSERT(r2);
        const bool r3 = t1.coplanar(
            nnm::Ray3f::from_point_to_point(
                { 5.6279295263f, 0.2174812388f, 2.4491340955f }, { 3.7355435221f, 2.8096960263f, -1.3244196634f }));
        TEST_ASSERT(r3);
        const bool r4 = degen_line.coplanar(nnm::Ray3f { { 0.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(r4);
        const bool r5 = degen_line.coplanar(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT(r5);
        const bool r6 = degen_line.coplanar(nnm::Ray3f { { -100.0f, 0.0f, 100.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Segment3&)");
    {
        constexpr bool r1 = t1.coplanar(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.coplanar(nnm::Segment3f { t1.edge(0).start, t1.edge(0).end });
        TEST_ASSERT(r2);
        constexpr bool r3 = t1.coplanar(
            nnm::Segment3f { { 5.6279295263f, 0.2174812388f, 2.4491340955f },
                             { 3.7355435221f, 2.8096960263f, -1.3244196634f } });
        TEST_ASSERT(r3);
        constexpr bool r4
            = degen_line.coplanar(nnm::Segment3f { { 0.0f, 100.0f, -100.0f }, { 1.0f, 100.0f, -100.0f } });
        TEST_ASSERT(r4);
        constexpr bool r5 = degen_line.coplanar(nnm::Segment3f { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } });
        TEST_ASSERT(r5);
        constexpr bool r6
            = degen_line.coplanar(nnm::Segment3f { { -100.0f, 0.0f, 100.0f }, { -100.0f, 1.0f, 100.0f } });
        TEST_ASSERT_FALSE(r6);
    }

    test_section("coplanar(const Plane&)");
    {
        const bool r1 = t1.coplanar(nnm::PlaneF::from_triangle_unchecked(t1));
        TEST_ASSERT(r1);
        const bool r2 = t1.coplanar(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(r2);
        const bool r3 = degen_line.coplanar(nnm::PlaneF::xy());
        TEST_ASSERT(r3);
        const bool r4 = degen_line.coplanar(nnm::PlaneF::xz());
        TEST_ASSERT(r4);
        const bool r5 = degen_line.coplanar(nnm::PlaneF::yz());
        TEST_ASSERT_FALSE(r5);
        const bool r6 = degen_line.coplanar(nnm::PlaneF::xz_offset(100.0f));
        TEST_ASSERT_FALSE(r6);
    }

    test_section("project");
    {
        constexpr auto p1 = t1.project({ -1.5f, 3.5f, 3.0f });
        TEST_ASSERT(p1.approx_equal({ -0.2336065574f, 0.1229508197f, 0.0450819672f }))
        ;constexpr auto p2 = t1.project({ -1.0f, 1.0f, 3.0f });
        TEST_ASSERT(p2.approx_equal({ 0.2409638554f, -0.734939759f, 1.2289156627f }));
        constexpr auto p3 = t1.project({ 0.8632112627f, -3.9685633672f, -1.3474929463f });
        TEST_ASSERT(p3.approx_equal({ 0.2409638554f, -0.734939759f, 1.2289156627f }));
        constexpr auto p4 = degen_line.project({ 0.5f, 100.0f, 0.0f });
        TEST_ASSERT(p4.approx_equal({ 0.5f, 0.0f, 0.0f }));
        constexpr auto p5 = degen_line.project({ 100.0f, -100.0f, 0.0f });
        TEST_ASSERT(p5.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        const auto d1 = t1.distance_sqrd({ 0.0f, 3.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 15.1557377046977f));
        const auto d2 = t1.distance_sqrd({ -3.0f, 4.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d2, 30.7469879516482f));
        const auto d3 = t1.distance_sqrd(t1.vertices[1]);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = degen_line.distance_sqrd({ 0.5f, 0.0, 100.0f });
        TEST_ASSERT(nnm::approx_equal(d4, 10000.0f));
        const auto d5 = degen_line.distance_sqrd({ 100.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d5, 9801.0f));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto d1 = t1.distance_sqrd(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = t1.distance_sqrd(nnm::Line3f::axis_y_offset(-1.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 0.43103448761878f));
        constexpr auto d3 = degen_line.distance_sqrd(nnm::Line3f::axis_x_offset(10.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 100.0f));
        constexpr auto d4 = degen_line.distance_sqrd(nnm::Line3f::axis_z_offset(5.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d4, 16.0f));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr auto d1 = t1.distance_sqrd(nnm::Ray3f({ -1.0f, 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 2.36885245894616f));
        constexpr auto d2 = t1.distance_sqrd(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = t1.distance_sqrd(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.29508196726188f));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr auto d1 = t1.distance_sqrd(nnm::Segment3f({ -1.0f, 2.0f, 0.0f }, { -1.0f, 3.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 2.36885245894616f));
        constexpr auto d2 = t1.distance_sqrd(nnm::Segment3f({ -1.0f, 3.0f, 0.0f }, { -1.0f, 2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 2.36885245894616f));
        constexpr auto d3 = t1.distance_sqrd(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = t1.distance_sqrd(nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = t1.distance_sqrd(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 0.29508196726188f));
        constexpr auto d6 = t1.distance_sqrd(nnm::Segment3f({ 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 0.29508196726188f));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr auto d1 = t1.distance_sqrd(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = t1.distance_sqrd(nnm::PlaneF::xy_offset(5.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 4.0f));
        constexpr auto d3 = t1.distance_sqrd(nnm::PlaneF::yz_offset(5.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr auto d1
            = t1.distance_sqrd(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { 0.0, 3.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2
            = t1.distance_sqrd(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.4918700472262f));
        constexpr auto d3
            = t1.distance_sqrd(t1.translate(nnm::Vector3f(0.27160725f, -0.724286019f, -0.633750259f) * 3.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 9.0f));
    }

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2
            = nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3
            = nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })
                                     .distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        constexpr auto result5 = nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f })
                                     .distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result5));
        constexpr auto result6 = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })
                                     .distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result6, 6.75f));
        constexpr auto result8 = nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f })
                                     .distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result8));
    }

    test_section("distance_sqrd(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float r1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, -2.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2
            = nnm::Triangle3f({ -3.0f, 0.0f, 1.0f }, { -3.0f, -2.0f, 1.0f }, { -3.0f, 0.0f, 3.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 4.0f));
        constexpr float r3
            = nnm::Triangle3f({ 10.0f, 0.0f, 1.0f }, { 0.0f, -10.0f, 1.0f }, { -10.0f, 0.0f, 1.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("distance_sqrd(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float r1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5183982895123f));
        constexpr float r2
            = nnm::Triangle3f({ 1.0f, 10.0f, 0.0f }, { 1.0f, -2.0f, 10.0f }, { 1.0f, -10.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3
            = nnm::Triangle3f({ -0.5f, -1.0f, 1.5f }, { -1.0f, 0.0f, 1.0f }, { 1.0f, -5.0f, 0.0f }).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.38603907872361f));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = t1.distance({ 0.0f, 3.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 3.8930370798f));
        const auto d2 = t1.distance({ -3.0f, 4.0f, 3.0f });
        TEST_ASSERT(nnm::approx_equal(d2, 5.5449966593f));
        const auto d3 = t1.distance(t1.vertices[1]);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = degen_line.distance({ 0.5f, 0.0, 100.0f });
        TEST_ASSERT(nnm::approx_equal(d4, 100.0f));
        const auto d5 = degen_line.distance({ 100.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d5, 99.0f));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = t1.distance(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = t1.distance(nnm::Line3f::axis_y_offset(-1.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 0.656532168f));
        const auto d3 = degen_line.distance(nnm::Line3f::axis_x_offset(10.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 10.0f));
        const auto d4 = degen_line.distance(nnm::Line3f::axis_z_offset(5.0f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(d4, 4.0f));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = t1.distance(nnm::Ray3f({ -1.0f, 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = t1.distance(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = t1.distance(nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d3, 0.5432144763f));
    }

    test_section("distance(const Segment3&)");
    {
        const auto d1 = t1.distance(nnm::Segment3f({ -1.0f, 2.0f, 0.0f }, { -1.0f, 3.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = t1.distance(nnm::Segment3f({ -1.0f, 3.0f, 0.0f }, { -1.0f, 2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 1.5391076827f));
        const auto d3 = t1.distance(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = t1.distance(nnm::Segment3f({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d4));
        const auto d5 = t1.distance(nnm::Segment3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d5, 0.5432144763f));
        const auto d6 = t1.distance(nnm::Segment3f({ 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 0.5432144763f));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto d1 = t1.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = t1.distance(nnm::PlaneF::xy_offset(5.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 2.0f));
        constexpr auto d3 = t1.distance(nnm::PlaneF::yz_offset(5.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
    }

    test_section("distance(const Triangle3&)");
    {
        const auto d1 = t1.distance(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { 0.0, 3.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2
            = t1.distance(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.701334476f));
        const auto d3 = t1.distance(t1.translate(nnm::PlaneF::from_triangle_unchecked(t1).normal * 3.0f));
        TEST_ASSERT(nnm::approx_equal(d3, 3.0f));
    }

    test_section("distance(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        const auto result1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2
            = nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3
            = nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }).distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        const auto result5 = nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f })
                                 .distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result5));
        const auto result6
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }).distance(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result6, 2.5980762114f));
        const auto result8 = nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f })
                                 .distance(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result8));
    }

    test_section("distance(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        const auto r1 = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5822070015f));
        const auto r2 = nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 4.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r2));
        const auto r3
            = nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, -2.0f, 4.0f }, { 0.0f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r3));
        const auto r4
            = nnm::Triangle3f({ -0.5f, -5.0f, 0.0f }, { -0.5f, -2.0f, 4.0f }, { -0.5f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r4));
        const auto r5 = nnm::Triangle3f({ 0.0, 0.0, 6.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -5.0f, 3.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r5));
        const auto r6 = nnm::Triangle3f(
                            { 1.4913057739f, -1.194313814f, 3.7420624503f },
                            { 1.2924884416f, -2.7911804169f, 3.0f },
                            { 1.0f, -1.5f, 3.0f })
                            .distance(s1);
        TEST_ASSERT(nnm::approx_zero(r6));
        const auto r7
            = nnm::Triangle3f({ -2.0f, -5.0f, 0.0f }, { -2.0f, -2.0f, 4.0f }, { -2.0f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(r7, 1.5f));
    }

    test_section("distance(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        const float r1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, -2.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2
            = nnm::Triangle3f({ -3.0f, 0.0f, 1.0f }, { -3.0f, -2.0f, 1.0f }, { -3.0f, 0.0f, 3.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 2.0f));
        const float r3
            = nnm::Triangle3f({ 10.0f, 0.0f, 1.0f }, { 0.0f, -10.0f, 1.0f }, { -10.0f, 0.0f, 1.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("distance(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        const float r1
            = nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2
            = nnm::Triangle3f({ 1.0f, 10.0f, 0.0f }, { 1.0f, -2.0f, 10.0f }, { 1.0f, -10.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        const float r3
            = nnm::Triangle3f({ -0.5f, -1.0f, 1.5f }, { -1.0f, 0.0f, 1.0f }, { 1.0f, -5.0f, 0.0f }).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 0.6213204316f));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr bool r1 = t1.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.parallel(nnm::Line3f(nnm::Point3f::zero(), { -0.801783f, -0.534522f, 0.267261f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = degen_line.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT(r3);
        constexpr bool r4 = degen_line.parallel(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = degen_point.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT(r5);
        constexpr bool r6 = degen_point.parallel(nnm::Line3f::axis_y());
        TEST_ASSERT(r6);
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr bool r1 = t1.parallel(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.parallel(nnm::Ray3f(nnm::Point3f::zero(), { -0.801783f, -0.534522f, 0.267261f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = degen_line.parallel(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(r3);
        constexpr bool r4 = degen_line.parallel(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = degen_point.parallel(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(r5);
        constexpr bool r6 = degen_point.parallel(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()));
        TEST_ASSERT(r6);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr bool r1 = t1.perpendicular(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.perpendicular(nnm::Line3f({ 100.0f, 0.0f, 0.0f }, { 0.271607f, -0.724286f, -0.63375f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = degen_line.perpendicular(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = degen_line.perpendicular(nnm::Line3f::axis_z_offset(-10.0f, 10.0f));
        TEST_ASSERT(r4);
        constexpr bool r5 = degen_point.perpendicular(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT(r5);
        constexpr bool r6 = degen_point.perpendicular(nnm::Line3f::axis_z_offset(-10.0f, 10.0f));
        TEST_ASSERT(r6);
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr bool r1 = t1.perpendicular(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = t1.perpendicular(nnm::Ray3f({ 100.0f, 0.0f, 0.0f }, { 0.271607f, -0.724286f, -0.63375f }));
        TEST_ASSERT(r2);
        constexpr bool r3 = degen_line.perpendicular(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = degen_line.perpendicular(nnm::Ray3f({ -10.0f, 10.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(r4);
        constexpr bool r5 = degen_point.perpendicular(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r5);
        constexpr bool r6 = degen_point.perpendicular(nnm::Ray3f({ -10.0f, 10.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(r6);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = t1.intersects(nnm::Line3f({ 1.0f, -2.0f, 3.0f }, { -0.329293f, 0.548821f, -0.76835f }));
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = t1.intersects(nnm::Line3f::axis_y());
        TEST_ASSERT(r3);
        constexpr auto r4 = degen_line.intersects(nnm::Line3f::axis_y());
        TEST_ASSERT(r4);
        constexpr auto r5 = degen_line.intersects(nnm::Line3f::axis_z_offset(-1.0f, 1.0f));
        TEST_ASSERT_FALSE(r5);
    }

    test_section("intersection(const Line3&)");
    {
        const auto i1 = t1.intersection(*nnm::Line3f::from_segment(t1.edge(0)));
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Line3f::axis_y());
        TEST_ASSERT(i3.has_value() && i3->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto r4 = degen_line.intersection(nnm::Line3f::axis_y());
        TEST_ASSERT(r4.has_value() && r4->approx_equal({ 0.0f, 0.0f, 0.0f }));
        const auto r5 = degen_line.intersection(nnm::Line3f::axis_z_offset(-1.0f, 1.0f));
        TEST_ASSERT_FALSE(r5.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = t1.intersects(nnm::Ray3f({ 1.0f, -2.0f, 3.0f }, { -0.329293f, 0.548821f, -0.76835f }));
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.intersects(nnm::Ray3f({ -2.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = t1.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = t1.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        TEST_ASSERT(r4);
        constexpr auto r5 = degen_line.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(r5)
        ;constexpr auto r6 = degen_line.intersects(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        TEST_ASSERT(r6)
        ;constexpr auto r7 = degen_line.intersects(nnm::Ray3f({ -1.0f, 1.0f, 1.0f }, -nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(r7);
    }

    test_section("intersection(const Ray3&)");
    {
        const auto i1 = t1.intersection(nnm::Ray3f::from_point_to_point(t1.edge(0).start, t1.edge(1).end));
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Ray3f({ -2.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = t1.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        TEST_ASSERT(i4.has_value() && i4->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto i5 = degen_line.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(i5.has_value());
        const auto i6 = degen_line.intersection(nnm::Ray3f({ 0.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_y()));
        TEST_ASSERT(i6.has_value() && i6->approx_zero());
        const auto i7 = degen_line.intersection(nnm::Ray3f({ -1.0f, 1.0f, 1.0f }, -nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto r1 = t1.intersects(t1.edge(0));
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.intersects(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = t1.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = t1.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(r4);
        constexpr auto r5 = t1.intersects(nnm::Segment3f({ 0.0f, -2.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }));
        TEST_ASSERT_FALSE(r5);
        constexpr auto r6 = degen_line.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT_FALSE(r6);
        constexpr auto r7 = degen_line.intersects(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(r7);
        constexpr auto r8 = degen_line.intersects(nnm::Segment3f({ -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -10.0f }));
        TEST_ASSERT_FALSE(r8);
    }

    test_section("intersection(const Segment3&)");
    {
        const auto i1 = t1.intersection(t1.edge(0));
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = t1.intersection(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = t1.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = t1.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(i4.has_value() && i4->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto i5 = t1.intersection(nnm::Segment3f({ 0.0f, -2.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }));
        TEST_ASSERT_FALSE(i5.has_value());
        const auto i6 = degen_line.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }));
        TEST_ASSERT_FALSE(i6.has_value());
        const auto i7 = degen_line.intersection(nnm::Segment3f({ 0.0f, 2.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(i7.has_value() && i7->approx_zero());
        const auto i8 = degen_line.intersection(nnm::Segment3f({ -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, -10.0f }));
        TEST_ASSERT_FALSE(i8.has_value());
    }

    test_section("intersects(const Plane&)");
    {
        constexpr auto p1 = nnm::PlaneF({ 1.0f, -2.0f, 3.0f }, { 0.27160725f, -0.724286019f, -0.633750259f });
        constexpr auto r1 = t1.intersects(p1);
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.intersects(p1.translate(p1.normal * 3.0f));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = t1.intersects(nnm::PlaneF::xy());
        TEST_ASSERT(r3);
        constexpr auto r4 = t1.intersects(nnm::PlaneF::yz_offset(4.0f));
        TEST_ASSERT(r4);
        constexpr auto r5 = degen_line.intersects(nnm::PlaneF::yz());
        TEST_ASSERT(r5);
        constexpr auto r6 = degen_line.intersects(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT_FALSE(r6);
    }

    test_section("intersection(const Plane&)");
    {
        constexpr auto p1 = nnm::PlaneF({ 1.0f, -2.0f, 3.0f }, { 0.27160725f, -0.724286019f, -0.633750259f });
        constexpr auto i1 = t1.intersection(p1);
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = t1.intersection(p1.translate(p1.normal * 3.0f));
        TEST_ASSERT_FALSE(i2);
        constexpr auto i3 = t1.intersection(nnm::PlaneF::xy());
        TEST_ASSERT(
            i3.has_value() && i3->coincident({ { 2.0f, 1.0f, 0.0f }, { -0.2857142857f, 0.1428571429f, 0.0f } }));
        constexpr auto i4 = t1.intersection(nnm::PlaneF::yz_offset(4.0f));
        TEST_ASSERT(i4.has_value() && i4->coincident({ { 4.0f, 0.0f, 2.0f }, { 4.0f, 0.0f, 2.0f } }));
        constexpr auto i5 = degen_line.intersection(nnm::PlaneF::yz());
        TEST_ASSERT(i5.has_value() && i5->coincident({ nnm::Point3f::zero(), nnm::Point3f::zero() }))
        ;constexpr auto i6 = degen_line.intersection(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT_FALSE(i6.has_value());
    }

    test_section("intersects(const Triangle3&)");
    {
        constexpr auto r1 = t1.intersects(t1);
        TEST_ASSERT(r1);
        constexpr auto r2
            = t1.intersects(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3
            = t1.intersects(nnm::Triangle3f({ 2.0f, 2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(r3);
        constexpr auto r4
            = t1.intersects(nnm::Triangle3f({ -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 3.0f, 2.0f, 0.0f }));
        TEST_ASSERT(r4);
        constexpr auto r5
            = t1.intersects(nnm::Triangle3f({ 1.0f, 3.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r5);
    }

    test_section("intersection(const Triangle3&)");
    {
        const auto i1 = t1.intersection(t1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2
            = t1.intersection(nnm::Triangle3f({ 0.0f, -2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { -2.0f, 2.0f, 0.0f }));
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3
            = t1.intersection(nnm::Triangle3f({ 2.0f, 2.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(
            i3.has_value()
            && i3->coincident({ { -0.2857142857f, 0.1428571429f, 0.0f }, { 1.3846153846f, 0.7692307692f, 0.0f } }));
        const auto i4
            = t1.intersection(nnm::Triangle3f({ -3.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 3.0f, 2.0f, 0.0f }));
        TEST_ASSERT(
            i4.has_value() && i4->coincident({ { 2.0f, 1.0f, 0.0f }, { -0.2857142857f, 0.1428571429f, 0.0f } }));
        const auto i5
            = t1.intersection(nnm::Triangle3f({ 1.0f, 3.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(
            i5.has_value()
            && i5->coincident({ { 1.7037037037f, 0.8888888889f, 0.0f }, { 0.4864864865f, 0.4324324324f, 0.0f } }));
    }

    test_section("coincident");
    {
        constexpr auto r1 = t1.coincident(t1);
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.coincident(degen_line);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = degen_line.coincident(t1);
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = degen_line.coincident(degen_line);
        TEST_ASSERT(r4);
        constexpr auto r5 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 1.0f, -2.0f, 3.0f }, { 4.0f, 0.0f, 2.0f } });
        TEST_ASSERT(r5);
        constexpr auto r6 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } });
        TEST_ASSERT(r6);
        constexpr auto r7 = t1.coincident({ { -2.0f, 3.0f, -4.0f }, { 4.0f, 1.0f, 2.0f }, { 1.0f, -2.0f, 3.0f } });
        TEST_ASSERT_FALSE(r7);
        constexpr auto r8 = t1.coincident({ { -2.0f, 3.0f, -4.1f }, { 1.0f, -2.0f, 3.0f }, { 4.0f, 0.0f, 2.0f } });
        TEST_ASSERT_FALSE(r8);
    }

    test_section("transform_at(const Vector3&, const Basis3&)");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::Basis3f basis { { { 1.0f, -2.0f, 3.0f }, { 4.0f, 1.5f, 0.0f }, { -2.0f, 0.2f, 10.0f } } };
        constexpr auto r1 = t1.transform_at(origin, basis);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].transform_at(origin, basis),
              t1.vertices[1].transform_at(origin, basis),
              t1.vertices[2].transform_at(origin, basis) }));
    }

    test_section("transform(const Basis3&)");
    {
        constexpr nnm::Basis3f basis { { { 1.0f, -2.0f, 3.0f }, { 4.0f, 1.5f, 0.0f }, { -2.0f, 0.2f, 10.0f } } };
        constexpr auto r1 = t1.transform(basis);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].transform(basis), t1.vertices[1].transform(basis), t1.vertices[2].transform(basis) }));
    }

    test_section("transform_at(const Vector3&, const Transform3&)");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::Transform3f transform { { { 1.0f, -2.0f, 3.0f, -0.2f },
                                                 { 4.0f, 1.5f, 0.0f, 5.0f },
                                                 { -2.0f, 0.2f, 10.0f, 1.0f },
                                                 { 0.0f, 0.0f, 0.0f, 1.0f } } };
        constexpr auto r1 = t1.transform_at(origin, transform);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].transform_at(origin, transform),
              t1.vertices[1].transform_at(origin, transform),
              t1.vertices[2].transform_at(origin, transform) }));
    }

    test_section("transform(const Transform3&)");
    {
        constexpr nnm::Transform3f transform { { { 1.0f, -2.0f, 3.0f, -0.2f },
                                                 { 4.0f, 1.5f, 0.0f, 5.0f },
                                                 { -2.0f, 0.2f, 10.0f, 1.0f },
                                                 { 0.0f, 0.0f, 0.0f, 1.0f } } };
        constexpr auto r1 = t1.transform(transform);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].transform(transform),
              t1.vertices[1].transform(transform),
              t1.vertices[2].transform(transform) }));
    }

    test_section("translate");
    {
        constexpr auto r1 = t1.translate({ 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].translate({ 1.0f, -2.0f, 3.0f }),
              t1.vertices[1].translate({ 1.0f, -2.0f, 3.0f }),
              t1.vertices[2].translate({ 1.0f, -2.0f, 3.0f }) }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.scale_at(origin, { 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].scale_at(origin, { 1.0f, -2.0f, 3.0f }),
              t1.vertices[1].scale_at(origin, { 1.0f, -2.0f, 3.0f }),
              t1.vertices[2].scale_at(origin, { 1.0f, -2.0f, 3.0f }) }));
    }

    test_section("scale");
    {
        constexpr auto r1 = t1.scale({ 2.0f, -10.0f, 0.5f });
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].scale({ 2.0f, -10.0f, 0.5f }),
              t1.vertices[1].scale({ 2.0f, -10.0f, 0.5f }),
              t1.vertices[2].scale({ 2.0f, -10.0f, 0.5f }) }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = t1.rotate_axis_angle_at(origin, axis, angle);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_axis_angle_at(origin, axis, angle),
              t1.vertices[1].rotate_axis_angle_at(origin, axis, angle),
              t1.vertices[2].rotate_axis_angle_at(origin, axis, angle) }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = t1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_axis_angle(axis, angle),
              t1.vertices[1].rotate_axis_angle(axis, angle),
              t1.vertices[2].rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = t1.rotate_quaternion_at(origin, quat);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_quaternion_at(origin, quat),
              t1.vertices[1].rotate_quaternion_at(origin, quat),
              t1.vertices[2].rotate_quaternion_at(origin, quat) }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, 0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = t1.rotate_quaternion(quat);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].rotate_quaternion(quat),
              t1.vertices[1].rotate_quaternion(quat),
              t1.vertices[2].rotate_quaternion(quat) }));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_x_at(origin, -1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_x_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_x_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_x_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_x");
    {
        constexpr auto r1 = t1.shear_x(-1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_x(-1.3f, 0.2f),
              t1.vertices[1].shear_x(-1.3f, 0.2f),
              t1.vertices[2].shear_x(-1.3f, 0.2f) }));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_y_at(origin, -1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_y_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_y_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_y_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_y");
    {
        constexpr auto r1 = t1.shear_y(-1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_y(-1.3f, 0.2f),
              t1.vertices[1].shear_y(-1.3f, 0.2f),
              t1.vertices[2].shear_y(-1.3f, 0.2f) }));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Point3f origin { 2.0f, -10.0f, 0.5f };
        constexpr auto r1 = t1.shear_z_at(origin, -1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_z_at(origin, -1.3f, 0.2f),
              t1.vertices[1].shear_z_at(origin, -1.3f, 0.2f),
              t1.vertices[2].shear_z_at(origin, -1.3f, 0.2f) }));
    }

    test_section("shear_z");
    {
        constexpr auto r1 = t1.shear_z(-1.3f, 0.2f);
        TEST_ASSERT(r1.approx_equal(
            { t1.vertices[0].shear_z(-1.3f, 0.2f),
              t1.vertices[1].shear_z(-1.3f, 0.2f),
              t1.vertices[2].shear_z(-1.3f, 0.2f) }));
    }

    test_section("approx_equal");
    {
        constexpr auto r1 = t1.approx_equal(t1);
        TEST_ASSERT(r1);
        constexpr auto r2 = t1.approx_equal(degen_line);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = degen_line.approx_equal(t1);
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = degen_line.approx_equal(degen_line);
        TEST_ASSERT(r4);
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = t1 == t1;
        TEST_ASSERT(r1);
        constexpr auto r2 = t1 == degen_line;
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = degen_line == t1;
        TEST_ASSERT_FALSE(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = degen_line == degen_line;
        TEST_ASSERT(r4);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = t1 != t1;
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = t1 != degen_line;
        TEST_ASSERT(r2);
        constexpr auto r3 = degen_line != t1;
        TEST_ASSERT(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = degen_line != degen_line;
        TEST_ASSERT_FALSE(r4);
    }

    test_section("operator<");
    {
        constexpr auto r1 = t1 < degen_line;
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = degen_line < t1;
        TEST_ASSERT(r2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r3 = t1 < t1;
        TEST_ASSERT_FALSE(r3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r4 = degen_line < degen_line;
        TEST_ASSERT_FALSE(r4);
    }
}

