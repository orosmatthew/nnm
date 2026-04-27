#include "tests.hpp"

void plane_tests()
{
    test_case("Plane");

    test_section("Plane()");
    {
        constexpr nnm::PlaneF p;
        TEST_ASSERT(p.origin.approx_equal(nnm::Point3f::zero()));
        TEST_ASSERT(p.normal.approx_equal(nnm::Vector3f::axis_x()));
    }

    test_section("Plane(const Vector3&, const Vector3&)");
    {
        constexpr nnm::PlaneF p { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        TEST_ASSERT(p.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(p.normal.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    test_section("Plane(const Plane<Other>&)");
    {
        constexpr nnm::PlaneD p1 { { 1.0, -2.0, 3.0 }, { -4.0, 5.0, -6.0 } };
        constexpr nnm::PlaneF p2 { p1 };
        TEST_ASSERT(p2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
    }

    test_section("from_points_unchecked");
    {
        const auto p
            = nnm::PlaneF::from_points_unchecked({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f });
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        TEST_ASSERT(p.normal.approx_equal(n) || p.normal.approx_equal(-n));
        TEST_ASSERT(p.contains({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(p.contains({ -4.0f, 5.0f, -6.0f }));
        TEST_ASSERT(p.contains({ -2.0f, -3.0f, 4.0f }));
    }

    test_section("from_points");
    {
        const auto p1 = nnm::PlaneF::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f });
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        TEST_ASSERT(p1.has_value() && (p1->normal.approx_equal(n) || p1->normal.approx_equal(-n)))
        ;TEST_ASSERT(p1.has_value() && p1->contains({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(p1.has_value() && p1->contains({ -4.0f, 5.0f, -6.0f }));
        TEST_ASSERT(p1.has_value() && p1->contains({ -2.0f, -3.0f, 4.0f }));
        const auto p2 = nnm::PlaneF::from_points(nnm::Point3f::zero(), nnm::Point3f::zero(), nnm::Point3f::zero());
        TEST_ASSERT_FALSE(p2.has_value());
        const auto p3 = nnm::PlaneF::from_points({ -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(p3.has_value());
    }

    test_section("from_triangle_unchecked");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f } };
        const auto p = nnm::PlaneF::from_triangle_unchecked(t1);
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        TEST_ASSERT(p.normal.approx_equal(n) || p.normal.approx_equal(-n));
        TEST_ASSERT(p.contains({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(p.contains({ -4.0f, 5.0f, -6.0f }));
        TEST_ASSERT(p.contains({ -2.0f, -3.0f, 4.0f }));
    }

    test_section("from_triangle");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -2.0f, -3.0f, 4.0f } };
        const auto p1 = nnm::PlaneF::from_triangle(t1);
        constexpr nnm::Vector3f n { -0.0484501608f, 0.775202572f, 0.629852057f };
        TEST_ASSERT(p1.has_value() && (p1->normal.approx_equal(n) || p1->normal.approx_equal(-n)))
        ;TEST_ASSERT(p1.has_value() && p1->contains({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(p1.has_value() && p1->contains({ -4.0f, 5.0f, -6.0f }));
        TEST_ASSERT(p1.has_value() && p1->contains({ -2.0f, -3.0f, 4.0f }));
        constexpr nnm::Triangle3f t2 { nnm::Point3f::zero(), nnm::Point3f::zero(), nnm::Point3f::zero() };
        const auto p2 = nnm::PlaneF::from_triangle(t2);
        TEST_ASSERT_FALSE(p2.has_value());
        constexpr nnm::Triangle3f t3 { { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
        const auto p3 = nnm::PlaneF::from_triangle(t3);
        TEST_ASSERT_FALSE(p3.has_value());
    }

    test_section("xy");
    {
        constexpr auto p = nnm::PlaneF::xy();
        TEST_ASSERT(p.origin.approx_zero());
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_z()));
    }

    test_section("xy_offset");
    {
        constexpr auto p = nnm::PlaneF::xy_offset(3.0f);
        TEST_ASSERT(p.origin.approx_equal({ 0.0f, 0.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_z()));
    }

    test_section("xz");
    {
        constexpr auto p = nnm::PlaneF::xz();
        TEST_ASSERT(p.origin.approx_zero());
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_y()));
    }

    test_section("xz_offset");
    {
        constexpr auto p = nnm::PlaneF::xz_offset(3.0f);
        TEST_ASSERT(p.origin.approx_equal({ 0.0f, 3.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_y()));
    }

    test_section("yz");
    {
        constexpr auto p = nnm::PlaneF::yz();
        TEST_ASSERT(p.origin.approx_zero());
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_x()));
    }

    test_section("yz_offset");
    {
        constexpr auto p = nnm::PlaneF::yz_offset(3.0f);
        TEST_ASSERT(p.origin.approx_equal({ 3.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(p.normal.length(), 1.0f));
        TEST_ASSERT(p.normal.parallel(nnm::Vector3f::axis_x()));
    }

    test_section("normalize");
    {
        constexpr nnm::PlaneF p { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        const auto norm = p.normalize();
        TEST_ASSERT(norm.origin.approx_equal(p.origin));
        TEST_ASSERT(norm.normal.approx_equal({ -0.455844f, 0.569805f, -0.683766f }));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(l1);
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(plane.coplanar(l1));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr nnm::Ray3f r2 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(r2);
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(plane.coplanar(r2));
    }

    test_section("coplanar(const Segment3&)");
    {
        constexpr nnm::Segment3f s4 { { 1.0f, -2.0f, 3.0f }, { 2.0f, -3.0f, 4.0f } };
        constexpr auto result = nnm::PlaneF::xy().coplanar(s4);
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(plane.coplanar(s4));
    }

    constexpr nnm::PlaneF p1 { { 1.0f, -2.0f, 3.0f }, { -0.455844f, 0.569805f, -0.683766f } };

    test_section("coplanar(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { p1.origin, -p1.normal };
        constexpr auto result = p1.coplanar(p2);
        TEST_ASSERT(result);
        constexpr nnm::PlaneF p3 { nnm::Point3f::zero(), nnm::Vector3f::axis_z() };
        constexpr nnm::PlaneF p4 { { 1.0f, 2.0f, 0.0f }, -nnm::Vector3f::axis_z() };
        TEST_ASSERT(p3.coplanar(p4));
        TEST_ASSERT(p4.coplanar(p3));
        TEST_ASSERT_FALSE(p1.coplanar(p4));
    }

    test_section("coplanar(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f t2 { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        const bool r1 = nnm::PlaneF::from_triangle_unchecked(t1).coplanar(t1);
        TEST_ASSERT(r1);
        const bool r2 = nnm::PlaneF::xy().coplanar(t1);
        TEST_ASSERT_FALSE(r2);
        const bool r3 = nnm::PlaneF::xy().coplanar(t2);
        TEST_ASSERT(r3);
        const bool r4 = nnm::PlaneF::xz().coplanar(t2);
        TEST_ASSERT(r4);
        const bool r5 = nnm::PlaneF::yz().coplanar(t2);
        TEST_ASSERT_FALSE(r5);
        const bool r6 = nnm::PlaneF::xz_offset(100.0f).coplanar(t2);
        TEST_ASSERT_FALSE(r6);
    }

    constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };

    test_section("contains");
    {
        constexpr auto result = p2.contains({ -1.89f, -3.46f, 1.46f });
        TEST_ASSERT(result);
        TEST_ASSERT(p2.contains({ 1.0f, -2.0f, 0.0f }));
        TEST_ASSERT_FALSE(p2.contains({ 1.0f, -2.0f, 1.0f }));
        TEST_ASSERT_FALSE(p2.contains({ 5.0f, -20.0f, -100.0f }));
    }

    test_section("signed_distance)");
    {
        constexpr auto result = p2.signed_distance({ -1.89f, -3.46f, 1.46f });
        TEST_ASSERT(nnm::approx_zero(result));
        TEST_ASSERT(nnm::approx_equal(p2.signed_distance({ -1.89f, -2.752893f, 2.167107f }), 1.0f));
        TEST_ASSERT(nnm::approx_equal(p2.signed_distance({ 100.0f, -6.995535f, -2.075535f }), -5.0f));
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr auto result1 = p2.distance_sqrd({ -1.89f, -3.46f, 1.46f });
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = p2.distance_sqrd({ -1.89f, -2.752893f, 2.167107f });
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3 = p2.distance_sqrd({ 100.0f, -6.995535f, -2.075535f });
        TEST_ASSERT(nnm::approx_equal(result3, 25.0f));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto d1 = p2.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2 = p2.distance_sqrd(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance_sqrd(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d3, 18.0f));
        constexpr auto d4 = p2.distance_sqrd(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance_sqrd(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr auto d1 = p2.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2
            = p2.distance_sqrd(nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } });
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d3, 2.0f));
        constexpr auto d4 = p2.distance_sqrd(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(d4, 18.0f));
        constexpr auto d5 = p2.distance_sqrd(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d5, 18.0f));
        constexpr auto d6 = p2.distance_sqrd(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() });
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr auto d1 = p2.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { 3.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d1, 2.0f));
        constexpr auto d2 = p2.distance_sqrd(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } });
        TEST_ASSERT(nnm::approx_equal(d2, 18.0f));
        constexpr auto d3 = p2.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { -100.0f, -4.0f, -4.0f } });
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = p2.distance_sqrd(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Point3f::zero() });
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 3.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d5, 2.0f));
        constexpr auto d6 = p2.distance_sqrd(nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Point3f::zero() });
        TEST_ASSERT(nnm::approx_equal(d6, 2.0f));
        constexpr auto d7 = p2.distance_sqrd(nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d7, 2.0f));
        constexpr auto d8 = p2.distance_sqrd(nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d8, 2.0f));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr auto d1 = p2.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = p2.distance(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
        constexpr auto d4
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        TEST_ASSERT(nnm::approx_equal(d4, 1.0f));
        constexpr auto d5 = p1.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d5));
        constexpr auto d6 = p2.distance(p1);
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr auto d1 = nnm::PlaneF::xy().distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = nnm::PlaneF::xy_offset(5.0f).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 4.0f));
        constexpr auto d3 = nnm::PlaneF::yz_offset(5.0f).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
    }

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::PlaneF::xy().distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = nnm::PlaneF::yz().distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3 = nnm::PlaneF::xy_offset(1.0f).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = nnm::PlaneF::xy().distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr auto result5 = nnm::PlaneF::yz().distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = nnm::PlaneF::xy_offset(2.0f).distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 4.0f));
        constexpr auto result7 = nnm::PlaneF::yz_offset(-3.0f).distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8 = nnm::PlaneF::xy().distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result8, 1.0f));
        constexpr auto result9 = nnm::PlaneF::yz_offset(-2.5f).distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance_sqrd(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float r1 = nnm::PlaneF::xy().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.25f));
        constexpr float r2 = nnm::PlaneF::xz().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = nnm::PlaneF({ -3.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 4.0f));
    }

    test_section("distance_sqrd(const Box&)");
    {

        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float r1 = nnm::PlaneF::xy().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5183982895123f));
        constexpr float r2 = nnm::PlaneF::yz().distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = nnm::PlaneF::yz_offset(-2.0f).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 1.51839843245134f));
    }

    test_section("distance(const Vector3&)");
    {
        constexpr auto result = p2.distance({ -1.89f, -3.46f, 1.46f });
        TEST_ASSERT(nnm::approx_zero(result));
        TEST_ASSERT(nnm::approx_equal(p2.distance({ -1.89f, -2.752893f, 2.167107f }), 1.0f));
        TEST_ASSERT(nnm::approx_equal(p2.distance({ 100.0f, -6.995535f, -2.075535f }), 5.0f));
    }

    test_section("distance(const Line3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d3, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d4 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(d5));
    }

    test_section("distance(const Ray3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } });
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = p2.distance(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d3, nnm::sqrt(2.0f)));
        constexpr auto d4 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(d4, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d5 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(d5, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d6 = p2.distance(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() });
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance(const Segment3&)");
    {
        constexpr auto d1 = p2.distance(nnm::Segment3f { nnm::Point3f::zero(), { 3.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = p2.distance(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } });
        TEST_ASSERT(nnm::approx_equal(d2, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d3 = p2.distance(nnm::Segment3f { nnm::Point3f::zero(), { -100.0f, -4.0f, -4.0f } });
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = p2.distance(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Point3f::zero() });
        TEST_ASSERT(nnm::approx_zero(d4));
        constexpr auto d5 = p2.distance(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 3.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d5, nnm::sqrt(2.0f)));
        constexpr auto d6 = p2.distance(nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Point3f::zero() });
        TEST_ASSERT(nnm::approx_equal(d6, nnm::sqrt(2.0f)));
        constexpr auto d7 = p2.distance(nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d7, nnm::sqrt(2.0f)));
        constexpr auto d8 = p2.distance(nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(d8, nnm::sqrt(2.0f)));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto d1 = p2.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = p2.distance(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
        constexpr auto d4
            = p2.distance(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        TEST_ASSERT(nnm::approx_equal(d4, 1.0f));
        constexpr auto d5 = p1.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d5));
        constexpr auto d6 = p2.distance(p1);
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr auto d1 = nnm::PlaneF::xy().distance(t1);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = nnm::PlaneF::xy_offset(5.0f).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d2, 2.0f));
        constexpr auto d3 = nnm::PlaneF::yz_offset(5.0f).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d3, 1.0f));
    }

    test_section("distance(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::PlaneF::xy().distance(r1);
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = nnm::PlaneF::yz().distance(r1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3 = nnm::PlaneF::xy_offset(1.0f).distance(r1);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = nnm::PlaneF::xy().distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr auto result5 = nnm::PlaneF::yz().distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = nnm::PlaneF::xy_offset(2.0f).distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 2.0f));
        constexpr auto result7 = nnm::PlaneF::yz_offset(-3.0f).distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8 = nnm::PlaneF::xy().distance(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result8, 1.0f));
        constexpr auto result9 = nnm::PlaneF::yz_offset(-2.5f).distance(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        constexpr auto r1 = nnm::PlaneF::xy().distance(s1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.5f));
        constexpr auto r2 = nnm::PlaneF::yz_offset(-0.5f).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr auto r3 = nnm::PlaneF::xz_offset(-1.5f).distance(s1);
        TEST_ASSERT(nnm::approx_zero(r3));
        constexpr auto r4 = nnm::PlaneF::xy_offset(2.7f).distance(s_degen);
        TEST_ASSERT(nnm::approx_equal(r4, 2.7f));
        constexpr auto r5 = nnm::PlaneF::xz().distance(s_degen);
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float r1 = nnm::PlaneF::xy().distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 0.5f));
        constexpr float r2 = nnm::PlaneF::xz().distance(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = nnm::PlaneF({ -3.0f, 100.0f, -100.0f }, nnm::Vector3f::axis_x()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 2.0f));
    }

    test_section("distance(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float r1 = nnm::PlaneF::xy().distance(b1);
        TEST_ASSERT(nnm::approx_equal(r1, 1.23223305f));
        constexpr float r2 = nnm::PlaneF::yz().distance(b1);
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr float r3 = nnm::PlaneF::yz_offset(-2.0f).distance(b1);
        TEST_ASSERT(nnm::approx_equal(r3, 1.232233108f));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::Line3f::axis_z());
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(r3);
        constexpr auto r4 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r5);
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.parallel(nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } });
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = p2.parallel(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(r3);
        constexpr auto r4 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_x() });
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.parallel(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() });
        TEST_ASSERT_FALSE(r6);
    }

    test_section("parallel(const Segment&)");
    {
        constexpr auto r1 = p2.parallel(nnm::Segment3f { nnm::Point3f::zero(), { 3.0f, 0.0f, 0.0f } });
        TEST_ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, { 200.0f, -4.0f, -4.0f } });
        TEST_ASSERT(r2);
        constexpr auto r3 = p2.parallel(nnm::Segment3f { nnm::Point3f::zero(), { -100.0f, -4.0f, -4.0f } });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = p2.parallel(nnm::Segment3f { { -100.0f, -4.0f, -4.0f }, nnm::Point3f::zero() });
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = p2.parallel(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 3.0f, 0.0f } });
        TEST_ASSERT_FALSE(r5);
        constexpr auto r6 = p2.parallel(nnm::Segment3f { { 0.0f, 3.0f, 0.0f }, nnm::Point3f::zero() });
        TEST_ASSERT_FALSE(r6);
        constexpr auto r7 = p2.parallel(nnm::Segment3f { { 0.0f, -4.0f, 0.0f }, { 0.0f, -8.0f, 0.0f } });
        TEST_ASSERT_FALSE(r7);
        constexpr auto r8 = p2.parallel(nnm::Segment3f { { 0.0f, -8.0f, 0.0f }, { 0.0f, -4.0f, 0.0f } });
        TEST_ASSERT_FALSE(r8);
    }

    test_section("parallel(const Plane&)");
    {
        constexpr auto r1 = p2.parallel(p2);
        TEST_ASSERT(r1);
        constexpr auto r2 = p2.parallel(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        TEST_ASSERT(r2);
        constexpr auto r3
            = p2.parallel(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        TEST_ASSERT(r3);
        constexpr auto r4
            = p2.parallel(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        TEST_ASSERT(r4);
        constexpr auto r5 = p1.parallel(p2);
        TEST_ASSERT_FALSE(r5);
        constexpr auto r6 = p2.parallel(p1);
        TEST_ASSERT_FALSE(r6);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Line3f { nnm::Point3f::zero(), p2.normal });
        TEST_ASSERT(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Line3f { nnm::Point3f::zero(), -p2.normal });
        TEST_ASSERT(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Line3f::axis_z());
        TEST_ASSERT_FALSE(r4);
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Ray3f { nnm::Point3f::zero(), p2.normal });
        TEST_ASSERT(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Ray3f { nnm::Point3f::zero(), -p2.normal });
        TEST_ASSERT(r4);
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr auto r1 = p2.perpendicular(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 1.0f, 0.0f } });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.perpendicular(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, -100.0f, 0.0f } });
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = p2.perpendicular(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = p2.perpendicular(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 100.0f, 100.0f } });
        TEST_ASSERT(r4);
        constexpr auto r5 = p2.perpendicular(nnm::Segment3f { { 0.0f, 100.0f, 100.0f }, nnm::Point3f::zero() });
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.perpendicular(nnm::Segment3f { { 0.0f, 100.0f, 100.0f }, { 0.0f, -100.0, -100.0f } });
        TEST_ASSERT(r6);
    }

    test_section("perpendicular(const Plane&)");
    {
        constexpr auto r1 = p2.perpendicular(p2);
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2
            = p2.perpendicular(nnm::PlaneF { { 100.0f, -20.0f, 0.5f }, p2.normal.arbitrary_perpendicular() });
        TEST_ASSERT(r2);
        constexpr auto r3 = p1.perpendicular(p2);
        TEST_ASSERT_FALSE(r3);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Line3f::axis_z());
        TEST_ASSERT(r2);
        constexpr auto r3 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(r4);
        constexpr auto r5 = p2.intersects(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Line3f::axis_x_offset(-2.0f, 0.0f));
        TEST_ASSERT(r6);
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Line3f::axis_z());
        TEST_ASSERT(i2.has_value() && i2->approx_equal({ 0.0f, 0.0f, -2.0f }));
        constexpr auto i3 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(i3.has_value());
        constexpr auto i4 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(i4.has_value() && i4->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i5 = p2.intersection(nnm::Line3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(i5.has_value() && i5->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i6 = p2.intersection(nnm::Line3f::axis_x_offset(-2.0f, 0.0f));
        TEST_ASSERT_FALSE(i6.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_z() });
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = p2.intersects(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_z() });
        TEST_ASSERT(r3);
        constexpr auto r4 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(r6);
        constexpr auto r7 = p2.intersects(nnm::Ray3f { { 0.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT(r7);
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_z() });
        TEST_ASSERT_FALSE(i2.has_value());
        constexpr auto i3 = p2.intersection(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_z() });
        TEST_ASSERT(i3.has_value() && i3->approx_equal({ 0.0f, 0.0f, -2.0f }));
        constexpr auto i4 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(i4.has_value());
        constexpr auto i5 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(i5.has_value() && i5->approx_equal({ -100.0f, 2.0f, -4.0f }));
        constexpr auto i6 = p2.intersection(nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = p2.intersection(nnm::Ray3f { { 0.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto r1 = p2.intersects(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 1.0f, 0.0f } });
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = p2.intersects(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, -100.0f, 0.0f } });
        TEST_ASSERT(r2);
        constexpr auto r3 = p2.intersects(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = p2.intersects(nnm::Segment3f { { -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f } });
        TEST_ASSERT(r4);
        constexpr auto r5 = p2.intersects(nnm::Segment3f { { 100.0f, 100.0f, 100.0f }, { -100.0f, -100.0f, -100.0f } });
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.intersects(nnm::Segment3f { { -10.0f, -10.0f, 0.0f }, { -10.0f, -10.0, -10.0f } });
        TEST_ASSERT_FALSE(r6);
        constexpr auto r7 = p2.intersects(nnm::Segment3f { { 0.0f, -2.0f, 0.0f }, { 100.0f, -2.0f, 0.0f } });
        TEST_ASSERT(r7);
    }

    test_section("intersection(const Segment3&)");
    {
        constexpr auto i1 = p2.intersection(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 1.0f, 0.0f } });
        TEST_ASSERT_FALSE(i1.has_value());
        constexpr auto i2 = p2.intersection(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, -100.0f, 0.0f } });
        TEST_ASSERT(i2.has_value() && i2->approx_equal({ 0.0f, -2.0f, 0.0f }));
        constexpr auto i3 = p2.intersection(nnm::Segment3f { { -100.0f, 10.0f, 10.0f }, { 100.0f, 10.0f, 10.0f } });
        TEST_ASSERT_FALSE(i3.has_value());
        constexpr auto i4
            = p2.intersection(nnm::Segment3f { { -100.0f, -100.0f, -100.0f }, { 100.0f, 100.0f, 100.0f } });
        TEST_ASSERT(i4.has_value() && i4->approx_equal({ -1.0f, -1.0f, -1.0f }));
        constexpr auto i5
            = p2.intersection(nnm::Segment3f { { 100.0f, 100.0f, 100.0f }, { -100.0f, -100.0f, -100.0f } });
        TEST_ASSERT(i5.has_value() && i5->approx_equal({ -1.0f, -1.0f, -1.0f }));
        constexpr auto i6 = p2.intersection(nnm::Segment3f { { -10.0f, -10.0f, 0.0f }, { -10.0f, -10.0, -10.0f } });
        TEST_ASSERT_FALSE(i6.has_value());
        constexpr auto i7 = p2.intersection(nnm::Segment3f { { 0.0f, -2.0f, 0.0f }, { 100.0f, -2.0f, 0.0f } });
        TEST_ASSERT_FALSE(i7.has_value());
    }

    test_section("intersects(const Plane&)");
    {
        constexpr auto r1 = p2.intersects(p2);
        TEST_ASSERT(r1);
        constexpr auto r2 = p2.intersects(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        TEST_ASSERT(r2);
        constexpr auto r3
            = p2.intersects(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4
            = p2.intersects(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = p1.intersects(p2);
        TEST_ASSERT(r5);
        constexpr auto r6 = p2.intersects(p1);
        TEST_ASSERT(r6);
    }

    test_section("intersection(const Plane&)");
    {
        const auto i1 = p2.intersection(p2);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = p2.intersection(nnm::PlaneF { p2.origin.translate({ 100.0f, 0.0f, 0.0f }), -p2.normal });
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3
            = p2.intersection(nnm::PlaneF { p2.origin.translate({ -100.0f, 0.707107f, 0.707107f }), p2.normal });
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4
            = p2.intersection(nnm::PlaneF { p2.origin.translate({ -100.0f, -0.707107f, -0.707107f }), p2.normal });
        TEST_ASSERT_FALSE(i4.has_value());
        const auto i5 = p1.intersection(p2);
        TEST_ASSERT(
            i5.has_value() && p1.contains(i5->origin) && p2.contains(i5->origin) && p1.parallel(*i5)
            && p2.parallel(*i5));
        const auto i6 = p2.intersection(p1);
        TEST_ASSERT(
            i6.has_value() && p2.contains(i6->origin) && p2.contains(i6->origin) && p2.parallel(*i6)
            && p2.parallel(*i6));
        constexpr nnm::PlaneF p3 { nnm::Point3f::zero(), nnm::Vector3f::axis_z() };
        const auto i7 = p2.intersection(p3);
        TEST_ASSERT(
            i7.has_value() && p2.contains(i7->origin) && p3.contains(i7->origin) && p2.parallel(*i7)
            && p3.parallel(*i7));
    }

    test_section("project");
    {
        constexpr nnm::Point3f pt1 = p2.project({ 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(pt1.approx_equal({ 1.0f, -3.5f, 1.5f }));
        constexpr nnm::Point3f pt2 = p2.project({ 0.0f, -2.0f, 0.0f });
        TEST_ASSERT(pt2.approx_equal({ 0.0f, -2.0f, 0.0f }));
        constexpr nnm::Point3f pt3 = p2.project({ 3.0f, -4.0f, -2.0f });
        TEST_ASSERT(pt3.approx_equal({ 3.0f, -2.0f, 0.0f }));
    }

    test_section("translate");
    {
        constexpr nnm::PlaneF p2t = p2.translate({ 1.0f, -2.0f, 3.0f });
        TEST_ASSERT(p2t.approx_equal({ { 2.0f, -4.0f, 3.0f }, p2.normal }));
    }

    test_section("scale_at");
    {
        const nnm::PlaneF p2s = p2.scale_at({ -3.0f, 2.0f, -1.0f }, { 0.5f, 1.0f, -2.0f });
        TEST_ASSERT(p2s.approx_equal({ { -1.0f, -2.0f, -3.0f }, { 0.0f, 0.447214f, -0.89442f } }));
    }

    test_section("scale");
    {
        const nnm::PlaneF p2s = p2.scale({ 0.5f, 1.0f, -2.0f });
        TEST_ASSERT(p2s.approx_equal({ { 0.5f, -2.0f, 0.0f }, { 0.0f, 0.447214f, -0.89442f } }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, -1.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr auto angle = nnm::pi<float>() / 5.0f;
        const nnm::PlaneF p2r = p2.rotate_axis_angle_at(origin, axis, angle);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_axis_angle_at(origin, axis, angle),
                                         p2.normal.rotate_axis_angle(axis, angle).normalize() };
        TEST_ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_z();
        constexpr auto angle = -nnm::pi<float>() / 5.0f;
        const nnm::PlaneF p2r = p2.rotate_axis_angle(axis, angle);
        const nnm::PlaneF p2r_expected { p2.origin.rotate_axis_angle(axis, angle),
                                         p2.normal.rotate_axis_angle(axis, angle).normalize() };
        TEST_ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, -1.0f };
        constexpr nnm::QuaternionF quat { 0.0f, -0.7071068f, 0.0f, -0.7071068f };
        constexpr nnm::PlaneF p2r = p2.rotate_quaternion_at(origin, quat);
        constexpr nnm::PlaneF p2r_expected { p2.origin.rotate_quaternion_at(origin, quat),
                                             p2.normal.rotate_quaternion(quat) };
        TEST_ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, -0.7071068f, 0.0f, -0.7071068f };
        constexpr nnm::PlaneF p2r = p2.rotate_quaternion(quat);
        constexpr nnm::PlaneF p2r_expected { p2.origin.rotate_quaternion(quat), p2.normal.rotate_quaternion(quat) };
        TEST_ASSERT(p2r.approx_equal(p2r_expected));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_y = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_x_at(origin, factor_y, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_x_at(origin, factor_y, factor_z),
                                         p2.normal.shear_x(factor_y, factor_z).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_x");
    {
        constexpr float factor_y = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_x(factor_y, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_x(factor_y, factor_z),
                                         p2.normal.shear_x(factor_y, factor_z).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_x = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_y_at(origin, factor_x, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_y_at(origin, factor_x, factor_z),
                                         p2.normal.shear_y(factor_x, factor_z).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_y");
    {
        constexpr float factor_x = 2.0f;
        constexpr float factor_z = -0.5f;
        const nnm::PlaneF p2s = p2.shear_y(factor_x, factor_z);
        const nnm::PlaneF p2s_expected { p2.origin.shear_y(factor_x, factor_z),
                                         p2.normal.shear_y(factor_x, factor_z).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 2.0f, -1.0f };
        constexpr float factor_x = 2.0f;
        constexpr float factor_y = -0.5f;
        const nnm::PlaneF p2s = p2.shear_z_at(origin, factor_x, factor_y);
        const nnm::PlaneF p2s_expected { p2.origin.shear_z_at(origin, factor_x, factor_y),
                                         p2.normal.shear_z(factor_x, factor_y).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("shear_z");
    {
        constexpr float factor_x = 2.0f;
        constexpr float factor_y = -0.5f;
        const nnm::PlaneF p2s = p2.shear_z(factor_x, factor_y);
        const nnm::PlaneF p2s_expected { p2.origin.shear_z(factor_x, factor_y),
                                         p2.normal.shear_z(factor_x, factor_y).normalize() };
        TEST_ASSERT(p2s.approx_equal(p2s_expected));
    }

    test_section("approx_equal");
    {
        constexpr auto result = p2.approx_equal(p2);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(p2.approx_equal(p1));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = p2 == p2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(p1 == p2);
    }

    test_section("operator!=");
    {
        constexpr auto result = p1 != p2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(p2 != p2);
    }

    test_section("operator<");
    {
        constexpr auto result = p2 < p1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(p1 < p2);
    }
}

