#include "tests.hpp"

void line3_tests()
{
    test_case("Line3");

    test_section("Line3()");
    {
        constexpr nnm::Line3f l { };
        TEST_ASSERT(l.origin == nnm::Point3f::zero());
        TEST_ASSERT(l.direction == nnm::Vector3f::axis_x());
    }

    test_section("Line3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Line3f l { { -1.0f, 2.0f, 3.0f }, { 5.0f, 6.0f, -7.0f } };
        TEST_ASSERT(l.origin == nnm::Point3f(-1.0f, 2.0f, 3.0f));
        TEST_ASSERT(l.direction == nnm::Vector3f(5.0f, 6.0f, -7.0f));
    }

    test_section("Line3(const Line3<Other>&)");
    {
        constexpr nnm::Line3f l1 { { -1.0, 2.0, 3.0 }, { 5.0, 6.0, -7.0 } };
        constexpr nnm::Line3d l2 { l1 };
        TEST_ASSERT(l2.origin.approx_equal({ -1.0f, 2.0f, 3.0f }));
        TEST_ASSERT(l2.direction.approx_equal({ 5.0f, 6.0f, -7.0f }));
    }

    test_section("from_points");
    {
        const auto l = nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { 4.0f, -5.0f, 7.0f });
        TEST_ASSERT(l.has_value() && l->origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(l.has_value() && l->direction.approx_equal({ 0.5144957554f, -0.5144957554f, 0.6859943406f }));
        const auto l2 = nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f });
        TEST_ASSERT_FALSE(l2.has_value());
    }

    test_section("from_segment");
    {
        const auto l = nnm::Line3f::from_segment(nnm::Segment3f { { 1.0f, -2.0f, 3.0f }, { 4.0f, -5.0f, 7.0f } });
        TEST_ASSERT(l.has_value() && l->origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(l.has_value() && l->direction.approx_equal({ 0.5144957554f, -0.5144957554f, 0.6859943406f }));
        const auto l2 = nnm::Line3f::from_segment(nnm::Segment3f { { 1.0f, -2.0f, 3.0f }, { 1.0f, -2.0f, 3.0f } });
        TEST_ASSERT_FALSE(l2.has_value());
    }

    test_section("from_ray");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f } };
        constexpr auto l1 = nnm::Line3f::from_ray(r1);
        TEST_ASSERT(l1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(l1.direction.approx_equal({ -5.0f, 6.0f, -7.0f }));
    }

    test_section("axis_x");
    {
        constexpr auto l = nnm::Line3f::axis_x();
        TEST_ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("axis_y");
    {
        constexpr auto l = nnm::Line3f::axis_y();
        TEST_ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
    }

    test_section("axis_z");
    {
        constexpr auto l = nnm::Line3f::axis_z();
        TEST_ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
    }

    test_section("axis_x_offset");
    {
        constexpr auto l = nnm::Line3f::axis_x_offset(-1.0f, 2.0f);
        TEST_ASSERT(l.origin.approx_equal({ 0.0f, -1.0f, 2.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("axis_y_offset");
    {
        constexpr auto l = nnm::Line3f::axis_y_offset(-1.0f, 2.0f);
        TEST_ASSERT(l.origin.approx_equal({ -1.0f, 0.0f, 2.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
    }

    test_section("axis_z_offset");
    {
        constexpr auto l = nnm::Line3f::axis_z_offset(-1.0f, 2.0f);
        TEST_ASSERT(l.origin.approx_equal({ -1.0f, 2.0f, 0.0f }));
        TEST_ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
    }

    constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

    test_section("valid");
    {
        constexpr bool r1 = l1.valid();
        TEST_ASSERT(r1);
        constexpr nnm::Line3f degen_point { { 1.0f, -2.0f, 3.0f }, nnm::Vector3f::zero() };
        constexpr bool r2 = degen_point.valid();
        TEST_ASSERT_FALSE(r2);
    }

    test_section("parallel_containing");
    {
        constexpr auto l = l1.parallel_containing({ -5.0f, 6.0f, -7.0f });
        TEST_ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
        TEST_ASSERT(l.direction.approx_equal(l1.direction));
    }

    test_section("arbitrary_perpendicular_containing");
    {
        constexpr auto l = l1.arbitrary_perpendicular_containing({ -5.0f, 6.0f, -7.0f });
        TEST_ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
        TEST_ASSERT(l.direction.perpendicular(l1.direction));
    }

    test_section("perpendicular_plane_parallel");
    {
        nnm::PlaneF p { { 1.0f, 1.0f, 1.0f }, nnm::Vector3f(1.0f, -2.0f, 3.0f).normalize() };
        const auto result = l1.perpendicular_plane_parallel(p);
        TEST_ASSERT(result.perpendicular(l1) && p.parallel(result));
    }

    test_section("collinear(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        TEST_ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f })->collinear(r1));
        constexpr auto result = nnm::Line3f::axis_x().collinear(r1);
        TEST_ASSERT_FALSE(result);
    }

    test_section("collinear(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto result = nnm::Line3f::axis_x().collinear(s1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(nnm::Line3f::from_points({ 2.0f, -1.0f, 4.0f }, { -3.0f, 6.0f, -5.0f })->collinear(s1));
        TEST_ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })->collinear(s1));
        TEST_ASSERT(nnm::Line3f::from_points({ -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f })->collinear(s1));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr auto result = l1.coplanar(l1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(l1.coplanar(nnm::Line3f::axis_x()));
        auto l2 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(l1.coplanar(*l2));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr auto result = l1.coplanar(nnm::Ray3f(l1.origin, l1.direction));
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(l1.coplanar(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x())));
        auto r1 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(l1.coplanar(r1));
    }

    test_section("coplanar(const Segment3&)");
    {
        TEST_ASSERT(l1.coplanar(nnm::Segment3f(l1.origin, l1.origin + l1.direction)));
        TEST_ASSERT_FALSE(l1.coplanar(nnm::Segment3f(nnm::Point3f::zero(), { 1.0f, 0.0f, 0.0f })));
        auto s1 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(l1.coplanar(s1));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = l1.coplanar(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(l1.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        TEST_ASSERT_FALSE(
            l1.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        TEST_ASSERT(l1.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("coplanar(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr bool result1 = nnm::Line3f::axis_x().coplanar(r1);
        TEST_ASSERT(result1);
        constexpr bool result2 = nnm::Line3f::axis_y().coplanar(r1);
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).coplanar(r1);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).coplanar(r1);
        TEST_ASSERT_FALSE(result4);
    }

    test_section("contains");
    {
        constexpr auto result = l1.contains({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(l1.contains({ -2.0f, 1.0f, 0.0f }));
        TEST_ASSERT(l1.contains({ -0.8f, -0.2f, 1.2f }));
        TEST_ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).contains({ 0.0f, 0.0f, 0.0f }));
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr auto d1 = l1.distance_sqrd({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2 = l1.distance_sqrd({ -2.0f, 1.0f, 0.0f });
        TEST_ASSERT(nnm::approx_zero(d2));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto d1 = l1.distance_sqrd(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_equal(d1, 0.5f));
        constexpr auto d2 = nnm::Line3f::axis_x().distance_sqrd(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 2.0f));
        constexpr auto d3 = l1.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d3, 0.5f));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto d1 = nnm::Line3f::axis_x().distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.09756112942397f));
        constexpr auto d2 = nnm::Line3f::axis_x_offset(-4.0f, 5.0f).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d2, 8.0f));
        constexpr auto d3 = nnm::Line3f::axis_z_offset(-2.0f, 2.0f).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = nnm::Line3f::from_ray(r1).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto d1 = nnm::Line3f::axis_x().distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.06923076776146f));
        constexpr auto d2 = nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d2, 20.0f));
        constexpr auto d3 = nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d3, 8.0f));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Line3f::axis_x().distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2 = nnm::Line3f::axis_z().distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d3, 18.0f));
        constexpr auto d4 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr auto d1 = nnm::Line3f::axis_y().distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = nnm::Line3f::axis_y_offset(-1.0f, 0.0f).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.43103448761878f));
        constexpr nnm::Triangle3f t2 { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr auto d3 = nnm::Line3f::axis_x_offset(10.0f, 0.0f).distance_sqrd(t2);
        TEST_ASSERT(nnm::approx_equal(d3, 100.0f));
        constexpr auto d4 = nnm::Line3f::axis_z_offset(5.0f, 0.0f).distance_sqrd(t2);
        TEST_ASSERT(nnm::approx_equal(d4, 16.0f));
    }

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::Line3f::axis_x().distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = nnm::Line3f::axis_y().distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4
            = nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        constexpr auto result5
            = nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = nnm::Line3f::axis_x().distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result6));
        constexpr auto result7 = nnm::Line3f::axis_y().distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        constexpr auto result8
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance_sqrd(
                r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result8, 2.0f));
        constexpr auto result9 = nnm::Line3f::axis_x().distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        constexpr auto result10 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result10));
    }

    test_section("distance_sqrd(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float r1 = nnm::Line3f::axis_x().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2 = nnm::Line3f::axis_z().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("distance_sqrd(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float r1 = nnm::Line3f::axis_x().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5183982895123f));
        constexpr float r2 = nnm::Line3f::axis_y_offset(0.0f, 1.5f).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 0.07169918465782f));
        constexpr float r3 = nnm::Line3f::axis_z_offset(0.0f, -1.0f).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = l1.distance({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 1.41421342f));
        const auto d2 = l1.distance({ -2.0f, 1.0f, 0.0f });
        TEST_ASSERT(nnm::approx_zero(d2));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = l1.distance(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_equal(d1, 0.7071067812f));
        const auto d2 = nnm::Line3f::axis_x().distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 1.4142135624f));
        const auto d3 = l1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d3, 0.7071067812f));
    }

    test_section("distance(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        const auto d1 = nnm::Line3f::axis_x().distance(r1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.31234777f));
        const auto d2 = nnm::Line3f::axis_x_offset(-4.0f, 5.0f).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d2, 2.82842708f));
        const auto d3 = nnm::Line3f::axis_z_offset(-2.0f, 2.0f).distance(r1);
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = nnm::Line3f::from_ray(r1).distance(r1);
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        const auto d1 = nnm::Line3f::axis_x().distance(s1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.263117403f));
        const auto d2 = nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d2, 4.472135955f));
        const auto d3 = nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d3, 2.8284271247f));
    }

    test_section("distance(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Line3f::axis_x().distance(p2);
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = nnm::Line3f::axis_z().distance(p2);
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d3, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d4 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        const auto d1 = nnm::Line3f::axis_y().distance(t1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = nnm::Line3f::axis_y_offset(-1.0f, 0.0f).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.656532168f));
        constexpr nnm::Triangle3f t2 { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        const auto d3 = nnm::Line3f::axis_x_offset(10.0f, 0.0f).distance(t2);
        TEST_ASSERT(nnm::approx_equal(d3, 10.0f));
        const auto d4 = nnm::Line3f::axis_z_offset(5.0f, 0.0f).distance(t2);
        TEST_ASSERT(nnm::approx_equal(d4, 4.0f));
    }

    test_section("distance(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        const auto result1 = nnm::Line3f::axis_x().distance(r1);
        TEST_ASSERT(nnm::approx_zero(result1));
        const auto result2 = nnm::Line3f::axis_y().distance(r1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        const auto result3
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance(r1);
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        const auto result5 = nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.distance(r1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = nnm::Line3f::axis_x().distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result6));
        const auto result7 = nnm::Line3f::axis_y().distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        const auto result8
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result8, 1.4142135624f));
        const auto result9 = nnm::Line3f::axis_x().distance(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result9, 1.4142135624f));
        const auto result10 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).distance(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result10));
    }

    test_section("distance(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        const auto r1 = nnm::Line3f::axis_x_offset(-2.0f, 3.0f).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = nnm::Line3f::axis_x().distance(s1);
        TEST_ASSERT(nnm::approx_equal(r2, 2.1055512755f));
        const auto r3 = nnm::Line3f::axis_y_offset(2.5f, 3.0f).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r3));
        const auto r4 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).distance(s_degen);
        TEST_ASSERT(nnm::approx_equal(r4, 1.4142135624f));
        const auto r5 = nnm::Line3f::axis_z().distance(s_degen);
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        const float r1 = nnm::Line3f::axis_x().distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        const float r2 = nnm::Line3f::axis_z().distance(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("distance(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        const float r1 = nnm::Line3f::axis_x().distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        const float r2 = nnm::Line3f::axis_y_offset(0.0f, 1.5f).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r2, 0.2677670343f));
        const float r3 = nnm::Line3f::axis_z_offset(0.0f, -1.0f).distance(b1);
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = l1.parallel(l1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(l1.parallel(*nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
        TEST_ASSERT(nnm::Line3f::axis_x().parallel(nnm::Line3f::axis_x_offset(2.0f, -3.0f)));
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().parallel(r1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })->parallel(r1));
    }

    test_section("parallel(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto result = nnm::Line3f::axis_x().parallel(s1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })->parallel(s1))
        ;TEST_ASSERT(nnm::Line3f::from_points({ 3.0f, 0.0f, 5.0f }, { -2.0f, 7.0f, -4.0f })->parallel(s1))
    ;}

    test_section("parallel(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto r1 = nnm::Line3f::axis_x().parallel(p2);
        TEST_ASSERT(r1);
        constexpr auto r2 = nnm::Line3f::axis_z().parallel(p2);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.parallel(p2);
        TEST_ASSERT(r3);
        constexpr auto r4 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() }.parallel(p2);
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.parallel(p2);
        TEST_ASSERT_FALSE(r5);
    }

    test_section("parallel(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr nnm::Triangle3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };
        constexpr bool r1 = nnm::Line3f::axis_x().parallel(t1);
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = nnm::Line3f(nnm::Point3f::zero(), { -0.801783f, -0.534522f, 0.267261f }).parallel(t1);
        TEST_ASSERT(r2);
        constexpr bool r3 = nnm::Line3f::axis_x().parallel(degen_line);
        TEST_ASSERT(r3);
        constexpr bool r4 = nnm::Line3f::axis_y().parallel(degen_line);
        TEST_ASSERT_FALSE(r4);
        constexpr bool r5 = nnm::Line3f::axis_x().parallel(degen_point);
        TEST_ASSERT(r5);
        constexpr bool r6 = nnm::Line3f::axis_y().parallel(degen_point);
        TEST_ASSERT(r6);
    }

    test_section("parallel(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr bool result1 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).parallel(r1);
        TEST_ASSERT(result1);
        constexpr bool result2 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).parallel(r1);
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3
            = nnm::Line3f({ 0.0f, -1.0f, 10.0f }, { 0.0f, 0.70710678118655f, 0.70710678118655f }).parallel(r1);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).parallel(r_degen_line);
        TEST_ASSERT(result4);
        constexpr bool result5 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).parallel(r_degen_line);
        TEST_ASSERT_FALSE(result5);
        constexpr bool result6 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).parallel(r_degen_point);
        TEST_ASSERT(result6);
        constexpr bool result7 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).parallel(r_degen_point);
        TEST_ASSERT(result7);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = l1.perpendicular(l1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::axis_x().perpendicular(nnm::Line3f::axis_y_offset(2.0f, -3.0f)));
        TEST_ASSERT(nnm::Line3f::axis_z_offset(10.0f, -20.0f).perpendicular(nnm::Line3f::axis_y()));
        TEST_ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                ->perpendicular(*nnm::Line3f::from_points({ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().perpendicular(r1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })->perpendicular(r1));
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto result = nnm::Line3f::axis_x().perpendicular(s1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })
                ->perpendicular(s1));
    }

    test_section("perpendicular(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto r1 = nnm::Line3f::axis_x().perpendicular(p2);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = nnm::Line3f { nnm::Point3f::zero(), p2.normal }.perpendicular(p2);
        TEST_ASSERT(r2);
        constexpr auto r3 = nnm::Line3f { nnm::Point3f::zero(), -p2.normal }.perpendicular(p2);
        TEST_ASSERT(r3);
        constexpr auto r4 = nnm::Line3f::axis_z().perpendicular(p2);
        TEST_ASSERT_FALSE(r4);
    }

    test_section("perpendicular(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr nnm::Triangle3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };
        constexpr bool r1 = nnm::Line3f::axis_x().perpendicular(t1);
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = nnm::Line3f({ 100.0f, 0.0f, 0.0f }, { 0.271607f, -0.724286f, -0.63375f }).perpendicular(t1);
        TEST_ASSERT(r2);
        constexpr bool r3 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).perpendicular(degen_line);
        TEST_ASSERT_FALSE(r3);
        constexpr bool r4 = nnm::Line3f::axis_z_offset(-10.0f, 10.0f).perpendicular(degen_line);
        TEST_ASSERT(r4);
        constexpr bool r5 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).perpendicular(degen_point);
        TEST_ASSERT(r5);
        constexpr bool r6 = nnm::Line3f::axis_z_offset(-10.0f, 10.0f).perpendicular(degen_point);
        TEST_ASSERT(r6);
    }

    test_section("perpendicular(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr bool result1 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).perpendicular(r1);
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).perpendicular(r1);
        TEST_ASSERT_FALSE(result2)
        ;constexpr bool result3
            = nnm::Line3f(nnm::Point3f::zero(), { 0.0f, 0.70710678118655f, -0.70710678118655f }).perpendicular(r1);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).perpendicular(r_degen_line);
        TEST_ASSERT_FALSE(result4);
        constexpr bool result5 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).perpendicular(r_degen_line);
        TEST_ASSERT(result5);
        constexpr bool result6 = nnm::Line3f::axis_x_offset(-1.0f, 1.0f).perpendicular(r_degen_point);
        TEST_ASSERT(result6);
        constexpr bool result7 = nnm::Line3f::axis_z_offset(-2.5f, 1.0f).perpendicular(r_degen_point);
        TEST_ASSERT(result7);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = l1.intersects(l1);
        TEST_ASSERT(result);
        TEST_ASSERT(l1.intersects(*nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f })));
        TEST_ASSERT_FALSE(l1.intersects(nnm::Line3f::axis_z()));
        TEST_ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).intersects(nnm::Line3f::axis_x()));
        TEST_ASSERT_FALSE(l1.intersects(nnm::Line3f::axis_x_offset(1.0f, -2.0f)));
        TEST_ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })->intersects(nnm::Line3f::axis_x()));
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto result = nnm::Line3f::axis_x().intersects(r1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f })->intersects(r1));
        TEST_ASSERT(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f })->intersects(r1));
        TEST_ASSERT_FALSE(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f })->intersects(r1));
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto result = nnm::Line3f::axis_x().intersects(s1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f })->intersects(s1));
        TEST_ASSERT_FALSE(
            nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f })
                ->intersects(s1));
        TEST_ASSERT_FALSE(
            nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f })
                ->intersects(s1));
        TEST_ASSERT(nnm::Line3f(s1.start, s1.direction()).intersects(s1));
    }

    test_section("intersects(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto r1 = nnm::Line3f::axis_x().intersects(p2);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = nnm::Line3f::axis_z().intersects(p2);
        TEST_ASSERT(r2);
        constexpr auto r3 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.intersects(p2);
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() }.intersects(p2);
        TEST_ASSERT(r4);
        constexpr auto r5 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.intersects(p2);
        TEST_ASSERT(r5);
        constexpr auto r6 = nnm::Line3f::axis_x_offset(-2.0f, 0.0f).intersects(p2);
        TEST_ASSERT(r6);
    }

    test_section("intersects(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr auto r1 = nnm::Line3f({ 1.0f, -2.0f, 3.0f }, { -0.329293f, 0.548821f, -0.76835f }).intersects(t1);
        TEST_ASSERT(r1);
        constexpr auto r2 = nnm::Line3f::axis_x().intersects(t1);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = nnm::Line3f::axis_y().intersects(t1);
        TEST_ASSERT(r3);
        constexpr auto r4 = nnm::Line3f::axis_y().intersects(degen_line);
        TEST_ASSERT(r4);
        constexpr auto r5 = nnm::Line3f::axis_z_offset(-1.0f, 1.0f).intersects(degen_line);
        TEST_ASSERT_FALSE(r5);
    }

    test_section("intersects(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::Line3f::axis_x().intersects(r1);
        TEST_ASSERT(result1);
        constexpr auto result2 = nnm::Line3f::axis_y().intersects(r1);
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersects(r1);
        TEST_ASSERT(result3);
        constexpr auto result4
            = nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersects(r1);
        TEST_ASSERT_FALSE(result4);
        constexpr auto result5
            = nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.intersects(r1);
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6 = nnm::Line3f::axis_x().intersects(r_degen_line);
        TEST_ASSERT(result6);
        constexpr auto result7 = nnm::Line3f::axis_y().intersects(r_degen_line);
        TEST_ASSERT_FALSE(result7);
        constexpr auto result8
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersects(r_degen_line);
        TEST_ASSERT_FALSE(result8);
        constexpr auto result9 = nnm::Line3f::axis_x().intersects(r_degen_point);
        TEST_ASSERT_FALSE(result9);
        constexpr auto result10 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).intersects(r_degen_point);
        TEST_ASSERT(result10);
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        constexpr auto r1 = nnm::Line3f::axis_x_offset(-2.0f, 3.0f).intersects(s1);
        TEST_ASSERT(r1);
        constexpr auto r2 = nnm::Line3f::axis_x().intersects(s1);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = nnm::Line3f::axis_y_offset(2.5f, 3.0f).intersects(s1);
        TEST_ASSERT(r3);
        constexpr auto r4 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).intersects(s_degen);
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = nnm::Line3f::axis_z().intersects(s_degen);
        TEST_ASSERT(r5);
    }

    test_section("intersects(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr auto r1 = nnm::Line3f::axis_x().intersects(b1);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = nnm::Line3f::axis_z().intersects(b1);
        TEST_ASSERT(r2);
    }

    test_section("intersects(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr auto r1 = nnm::Line3f::axis_x().intersects(b1);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = nnm::Line3f::axis_z().intersects(b1);
        TEST_ASSERT(r2);
    }

    test_section("intersects(const Frustum&)");
    {
        constexpr nnm::FrustumF f1 {
            nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
            nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })
        };
        constexpr bool r1 = nnm::Line3f::axis_x().intersects(f1);
        TEST_ASSERT_FALSE(r1);
        constexpr bool r2 = nnm::Line3f::axis_z().intersects(f1);
        TEST_ASSERT(r2);
        constexpr bool r3 = nnm::Line3f::axis_y_offset(1.0f, 3.0f).intersects(f1);
        TEST_ASSERT(r3);
        constexpr bool r4 = nnm::Line3f::axis_z_offset(0.0f, 2.0f).intersects(f1);
        TEST_ASSERT(r4);
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = l1.intersection(l1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = l1.intersection(*nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f }));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f, 1.0f }));
        constexpr auto i3 = l1.intersection(nnm::Line3f::axis_z());
        TEST_ASSERT_FALSE(i3.has_value());
        constexpr auto i4 = nnm::Line3f::axis_x_offset(1.0f, -2.0f).intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(i4.has_value());
        constexpr auto i5 = l1.intersection(nnm::Line3f::axis_x_offset(1.0f, -2.0f));
        TEST_ASSERT_FALSE(i5.has_value());
        const auto i6
            = nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })->intersection(nnm::Line3f::axis_x());
        TEST_ASSERT(i6.has_value() && i6.value().approx_equal({ 0.0f, 0.0f, 0.0f }));
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr auto i1 = nnm::Line3f::axis_x().intersection(r1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f })->intersection(r1);
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i3 = nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f })->intersection(r1);
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f })->intersection(r1);
        TEST_ASSERT_FALSE(i4.has_value());
    }

    test_section("intersection(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto i1 = nnm::Line3f::axis_x().intersection(s1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f })->intersection(s1);
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
        const auto i3
            = nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f })
                  ->intersection(s1);
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4
            = nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f })
                  ->intersection(s1);
        TEST_ASSERT_FALSE(i4.has_value());
        const auto i5 = nnm::Line3f(s1.start, s1.direction()).intersection(s1);
        TEST_ASSERT_FALSE(i5.has_value());
    }

    test_section("intersection(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto i1 = nnm::Line3f::axis_x().intersection(p2);
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = nnm::Line3f::axis_z().intersection(p2);
        TEST_ASSERT(i2.has_value() && i2->approx_equal({ 0.0f, 0.0f, -2.0f }));
        constexpr auto i3 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.intersection(p2);
        TEST_ASSERT_FALSE(i3.has_value());
        constexpr auto i4 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() }.intersection(p2);
        TEST_ASSERT(i4.has_value() && i4->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i5 = nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.intersection(p2);
        TEST_ASSERT(i5.has_value() && i5->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i6 = nnm::Line3f::axis_x_offset(-2.0f, 0.0f).intersection(p2);
        TEST_ASSERT_FALSE(i6.has_value());
    }

    test_section("intersection(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        const auto i1 = nnm::Line3f::from_segment(t1.edge(0))->intersection(t1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = nnm::Line3f::axis_x().intersection(t1);
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = nnm::Line3f::axis_y().intersection(t1);
        TEST_ASSERT(i3.has_value() && i3->approx_equal({ 0.0f, 0.25f, 0.0f }));
        const auto r4 = nnm::Line3f::axis_y().intersection(degen_line);
        TEST_ASSERT(r4.has_value() && r4->approx_equal({ 0.0f, 0.0f, 0.0f }));
        const auto r5 = nnm::Line3f::axis_z_offset(-1.0f, 1.0f).intersection(degen_line);
        TEST_ASSERT_FALSE(r5.has_value());
    }

    test_section("intersection(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::Line3f::axis_x().intersection(r1);
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr auto result2 = nnm::Line3f::axis_y().intersection(r1);
        TEST_ASSERT_FALSE(result2.has_value());
        constexpr auto result3
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersection(r1);
        TEST_ASSERT(result3.has_value() && result3->approx_equal({ -2.0f, 1.0f, 1.0f }));
        constexpr auto result4
            = nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersection(r1);
        TEST_ASSERT_FALSE(result4.has_value());
        constexpr auto result5
            = nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.intersection(r1);
        TEST_ASSERT_FALSE(result5.has_value());
        constexpr auto result6 = nnm::Line3f::axis_x().intersection(r_degen_line);
        TEST_ASSERT_FALSE(result6.has_value());
        constexpr auto result7 = nnm::Line3f::axis_y().intersection(r_degen_line);
        TEST_ASSERT_FALSE(result7.has_value());
        constexpr auto result8
            = nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.intersection(r_degen_line);
        TEST_ASSERT_FALSE(result8.has_value());
        constexpr auto result9 = nnm::Line3f::axis_x().intersection(r_degen_point);
        TEST_ASSERT_FALSE(result9.has_value());
        constexpr auto result10 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).intersection(r_degen_point);
        TEST_ASSERT(result10.has_value() && result10->approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("surface_intersections(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        const auto r1 = nnm::Line3f::axis_x_offset(-2.0f, 3.0f).surface_intersections(s1);
        TEST_ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = nnm::Line3f::axis_x().surface_intersections(s1);
        TEST_ASSERT(r2.empty());
        const auto r3 = nnm::Line3f::axis_y_offset(2.5f, 3.0f).surface_intersections(s1);
        TEST_ASSERT(r3.approx_equal({ { 2.5f, -2.0f, 3.0f } }));
        const auto r4 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).surface_intersections(s_degen);
        TEST_ASSERT(r4.empty());
        const auto r5 = nnm::Line3f::axis_z().surface_intersections(s_degen);
        TEST_ASSERT(r5.approx_equal({ nnm::Point3f::zero() }));
    }

    test_section("surface_intersections(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = nnm::Line3f::axis_x().surface_intersections(b1);
        TEST_ASSERT(r1.empty())
        ;constexpr nnm::PointSet<nnm::Point3f, 2> r2 = nnm::Line3f::axis_z().surface_intersections(b1);
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 4.0f } }));
    }

    test_section("surface_intersections(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = nnm::Line3f::axis_y().surface_intersections(b1);
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2 = nnm::Line3f::axis_z().surface_intersections(b1);
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 3.414213613f }, { 0.0f, 0.0f, 1.8786797787f } }));
        constexpr nnm::PointSet<nnm::Point3f, 2> r4
            = nnm::Line3f({ 0.0f, -2.0f, 5.0f }, { 0.7071067812f, 0.0f, -0.7071067812f }).surface_intersections(b1);
        TEST_ASSERT(
            r4.approx_equal({ { 0.7928931935f, -2.0f, 4.2071068282f }, { 2.2071068358f, -2.0f, 2.7928932245f } }));
    }

    test_section("surface_intersections(const Frustum&)");
    {
        constexpr nnm::FrustumF f1 {
            nnm::PlaneF({ 1.0f, -1.0f, 3.0f }, nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 1.0f, 2.0f, 3.0f }, -nnm::Vector3f::axis_y()),
            nnm::PlaneF({ 0.0f, -1.0f, 3.0f }, { 0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 2.0f, -1.0f, 3.0f }, { -0.7071067812f, 0.7071067812f, 0.0f }),
            nnm::PlaneF({ 1.0f, -1.0f, 2.5f }, { 0.0f, 0.4472135955f, 0.8944271910f }),
            nnm::PlaneF({ 1.0f, -1.0f, 3.5f }, { 0.0f, 0.4472135955f, -0.8944271910f })
        };
        constexpr nnm::PointSet<nnm::Point3f, 2> r1 = nnm::Line3f::axis_x().surface_intersections(f1);
        TEST_ASSERT(r1.empty());
        constexpr nnm::PointSet<nnm::Point3f, 2> r2 = nnm::Line3f::axis_z().surface_intersections(f1);
        TEST_ASSERT(r2.approx_equal({ { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 4.0f } }));
    }

    test_section("project_point");
    {
        constexpr auto p1 = l1.project({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(p1.approx_equal({ -1.0f, 0.0f, 1.0f }));
        constexpr auto p2 = l1.project({ 0.0f, -1.0f, 2.0f });
        TEST_ASSERT(p2.approx_equal({ 0.0f, -1.0f, 2.0f }));
    }

    test_section("coincident");
    {
        TEST_ASSERT(l1.coincident(l1));
        TEST_ASSERT_FALSE(l1.coincident(nnm::Line3f::axis_x()));
        TEST_ASSERT_FALSE(nnm::Line3f::axis_y().coincident(nnm::Line3f::axis_y_offset(1.0f, -2.0f)));
        TEST_ASSERT(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                ->coincident(*nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
    }

    test_section("tangent(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        constexpr auto r1 = nnm::Line3f::axis_x_offset(-2.0f, 3.0f).tangent(s1);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = nnm::Line3f::axis_x().tangent(s1);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = nnm::Line3f::axis_y_offset(2.5f, 3.0f).tangent(s1);
        TEST_ASSERT(r3);
        constexpr auto r4 = nnm::Line3f::axis_x_offset(1.0f, 1.0f).tangent(s_degen);
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = nnm::Line3f::axis_z().tangent(s_degen);
        TEST_ASSERT(r5);
    }

    test_section("translate");
    {
        constexpr auto t1 = l1.translate({ 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, l1.direction }));
    }

    test_section("scale");
    {
        const auto s1 = l1.scale({ 0.5f, -2.0f, 3.0f }, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
        const auto s2 = l1.scale({ 0.5f, -2.0f, 3.0f });
        TEST_ASSERT(s2.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("rotate_axis_angle");
    {
        const auto r1 = l1.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        const auto r2 = l1.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        TEST_ASSERT(r2.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r1 = l1.rotate_quaternion(q1, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        const auto r2 = l1.rotate_quaternion(q1);
        TEST_ASSERT(r2.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("shear_x");
    {
        const auto s1 = l1.shear_x(0.5f, -0.5f, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
        const auto s2 = l1.shear_x(0.5f, -0.5f);
        TEST_ASSERT(s2.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_y");
    {
        const auto s1 = l1.shear_y(0.5f, -0.5f, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
        const auto s2 = l1.shear_y(0.5f, -0.5f);
        TEST_ASSERT(s2.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_z");
    {
        const auto s1 = l1.shear_z(0.5f, -0.5f, { 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
        const auto s2 = l1.shear_z(0.5f, -0.5f);
        TEST_ASSERT(s2.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("approx_equal");
    {
        TEST_ASSERT(l1.approx_equal(l1));
        TEST_ASSERT_FALSE(l1.approx_equal(nnm::Line3f::axis_x()));
        TEST_ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_equal(nnm::Line3f::axis_x()));
        TEST_ASSERT_FALSE(
            nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                ->approx_equal(*nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
    }

    test_section("operator==");
    {
        TEST_ASSERT(l1 == l1);
        TEST_ASSERT_FALSE(l1 == nnm::Line3f::axis_x());
    }

    test_section("operator!=");
    {
        TEST_ASSERT(l1 != nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(l1 != l1);
    }

    test_section("operator<");
    {
        TEST_ASSERT(nnm::Line3f::axis_x() < l1);
        TEST_ASSERT_FALSE(l1 < l1);
        TEST_ASSERT_FALSE(l1 < nnm::Line3f::axis_x());
    }
}

