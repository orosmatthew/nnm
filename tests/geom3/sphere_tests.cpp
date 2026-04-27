#include "tests.hpp"

void sphere_tests()
{
    test_case("sphere");

    test_section("Sphere()");
    {
        constexpr nnm::SphereF s1 { };
        TEST_ASSERT(s1.center.approx_zero());
        TEST_ASSERT(nnm::approx_equal(s1.radius, 1.0f));
    }

    test_section("Sphere(const Vector3&, Real)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        TEST_ASSERT(s1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(s1.radius, 1.5f));
    }

    test_section("Sphere(const Sphere<Other>&)");
    {
        constexpr nnm::SphereD s1 { { 1.0, -2.0, 3.0 }, 1.5 };
        constexpr nnm::SphereF s2 { s1 };
        TEST_ASSERT(s2.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(s2.radius, 1.5f));
    }

    test_section("from_center_surface_point");
    {
        const auto s1 = nnm::SphereF::from_center_surface_point(
            { 1.0f, -2.0f, 3.0f }, { 1.4199396004f, -2.6830724743f, 4.2676997779f });
        TEST_ASSERT(s1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(s1.radius, 1.5f));
    }

    constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
    constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };

    test_section("collapse_point");
    {
        constexpr std::optional<nnm::Point3f> r1 = s1.collapse_point();
        TEST_ASSERT_FALSE(r1.has_value());
        constexpr std::optional<nnm::Point3f> r2 = s_degen.collapse_point();
        TEST_ASSERT(r2.has_value() && r2.value().approx_equal({ 0.0f, 0.0f, 0.0f }));
    }

    test_section("surface_area");
    {
        constexpr auto r1 = s1.surface_area();
        TEST_ASSERT(nnm::approx_equal(r1, 28.2743338823f));
        constexpr auto r2 = s_degen.surface_area();
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("volume");
    {
        constexpr auto r1 = s1.volume();
        TEST_ASSERT(nnm::approx_equal(r1, 14.1371669412f));
        constexpr auto r2 = s_degen.volume();
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("diameter");
    {
        constexpr auto r1 = s1.diameter();
        TEST_ASSERT(nnm::approx_equal(r1, 3.0f));
        constexpr auto r2 = s_degen.diameter();
        TEST_ASSERT(nnm::approx_zero(r2));
    }

    test_section("contains");
    {
        constexpr auto r1 = s1.contains({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        TEST_ASSERT(r1);
        constexpr auto r2 = s1.contains(s1.center);
        TEST_ASSERT(r2);
        constexpr auto r3 = s1.contains({ 0.75f, -2.1f, 3.25f });
        TEST_ASSERT(r3);
        constexpr auto r4 = s1.contains(nnm::Point3f::zero());
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.contains({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT_FALSE(r5);
        constexpr auto r6 = s_degen.contains(nnm::Point3f::zero());
        TEST_ASSERT(r6);
    }

    test_section("signed_distance");
    {
        const auto r1 = s1.signed_distance(s1.center);
        TEST_ASSERT(nnm::approx_equal(r1, -s1.radius));
        const auto r2 = s1.signed_distance({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        TEST_ASSERT(nnm::approx_zero(r2));
        const auto r3 = s1.signed_distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r3, 2.2416573868f));
        const auto r4 = s_degen.signed_distance({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 1.7320508076f));
        const auto r5 = s_degen.signed_distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Vector3&)");
    {
        const auto r1 = s1.distance(s1.center);
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance({ 1.4199396004f, -2.6830724743f, 4.2676997779f });
        TEST_ASSERT(nnm::approx_zero(r2));
        const auto r3 = s1.distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_equal(r3, 2.2416573868f));
        const auto r4 = s_degen.distance({ 1.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(r4, 1.7320508076f));
        const auto r5 = s_degen.distance(nnm::Point3f::zero());
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Line3&)");
    {
        const auto r1 = s1.distance(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(r2, 2.1055512755f));
        const auto r3 = s1.distance(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        TEST_ASSERT(nnm::approx_zero(r3));
        const auto r4 = s_degen.distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(nnm::approx_equal(r4, 1.4142135624f));
        const auto r5 = s_degen.distance(nnm::Line3f::axis_z());
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Ray3&)");
    {
        const auto r1 = s1.distance(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r2, 1.5f));
        const auto r3 = s1.distance(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r3, 2.1055512755f));
        const auto r4 = s1.distance(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r4, 2.2416573868f));
        const auto r5 = s_degen.distance(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_equal(r5, 1.0f));
        const auto r6 = s_degen.distance(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(nnm::approx_zero(r6));
    }

    test_section("distance(const Segment3&)");
    {
        const auto r1 = s1.distance(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(r2, 1.5f));
        const auto r3 = s1.distance(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_equal(r3, 7.5f));
        const auto r4 = s1.distance(nnm::Segment3f(nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r4, 2.1055512755f));
        const auto r5 = s1.distance(nnm::Segment3f(nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r5, 2.2416573868f));
        const auto r6 = s_degen.distance(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r6, 1.0f));
        const auto r7 = s_degen.distance(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(r7));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto r1 = s1.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(r1, 1.5f));
        constexpr auto r2 = s1.distance(nnm::PlaneF::yz_offset(-0.5f));
        TEST_ASSERT(nnm::approx_zero(r2));
        constexpr auto r3 = s1.distance(nnm::PlaneF::xz_offset(-1.5f));
        TEST_ASSERT(nnm::approx_zero(r3));
        constexpr auto r4 = s_degen.distance(nnm::PlaneF::xy_offset(2.7f));
        TEST_ASSERT(nnm::approx_equal(r4, 2.7f));
        constexpr auto r5 = s_degen.distance(nnm::PlaneF::xz());
        TEST_ASSERT(nnm::approx_zero(r5));
    }

    test_section("distance(const Triangle3&)");
    {
        const auto r1 = s1.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r1, 1.5822070015f));
        const auto r2 = s1.distance(nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 4.0f }));
        TEST_ASSERT(nnm::approx_zero(r2));
        const auto r3
            = s1.distance(nnm::Triangle3f({ 0.0f, -5.0f, 0.0f }, { 0.0f, -2.0f, 4.0f }, { 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(r3));
        const auto r4
            = s1.distance(nnm::Triangle3f({ -0.5f, -5.0f, 0.0f }, { -0.5f, -2.0f, 4.0f }, { -0.5f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(r4));
        const auto r5 = s1.distance(nnm::Triangle3f({ 0.0, 0.0, 6.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -5.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(r5));
        const auto r6 = s1.distance(
            nnm::Triangle3f(
                { 1.4913057739f, -1.194313814f, 3.7420624503f },
                { 1.2924884416f, -2.7911804169f, 3.0f },
                { 1.0f, -1.5f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(r6));
        const auto r7
            = s1.distance(nnm::Triangle3f({ -2.0f, -5.0f, 0.0f }, { -2.0f, -2.0f, 4.0f }, { -2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(r7, 1.5f));
    }

    test_section("distance(const Sphere&)");
    {
        const auto r1 = s1.distance(s1);
        TEST_ASSERT(nnm::approx_zero(r1));
        const auto r2 = s1.distance(nnm::SphereF(nnm::Point3f::zero(), 1.0f));
        TEST_ASSERT(nnm::approx_equal(r2, 1.2416573868f));
        const auto r3 = s1.distance(s1.translate({ 1.5f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_zero(r3));
    }

    test_section("point_at");
    {
        constexpr auto r1 = s1.point_at(nnm::Vector3f::axis_x());
        TEST_ASSERT(r1.approx_equal({ 2.5f, -2.0f, 3.0f }))
    ;}

    test_section("normal_at");
    {
        constexpr auto r1 = s1.normal_at(nnm::Vector3f::axis_x());
        TEST_ASSERT(r1.approx_equal(nnm::Vector3f::axis_x()));
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto r1 = s1.intersects(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        TEST_ASSERT(r1);
        constexpr auto r2 = s1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1.intersects(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        TEST_ASSERT(r3);
        constexpr auto r4 = s_degen.intersects(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.intersects(nnm::Line3f::axis_z());
        TEST_ASSERT(r5);
    }

    test_section("surface_intersections(const Line3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        TEST_ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Line3f::axis_x());
        TEST_ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        TEST_ASSERT(r3.approx_equal({ { 2.5f, -2.0f, 3.0f } }));
        const auto r4 = s_degen.surface_intersections(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(r4.empty());
        const auto r5 = s_degen.surface_intersections(nnm::Line3f::axis_z());
        TEST_ASSERT(r5.approx_equal({ nnm::Point3f::zero() }));
    }

    test_section("intersects(const Ray3&)");
    {
        const auto r1 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r1);
        const auto r2 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r2);
        const auto r3 = s1.intersects(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r3);
        const auto r4 = s1.intersects(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r4);
        const auto r5 = s_degen.intersects(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r5);
        const auto r6 = s_degen.intersects(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r6);
        const auto r7 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r7);
        const auto r8 = s1.intersects(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r8);
    }

    test_section("surface_intersections(const Ray3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(r3.empty());
        const auto r4 = s1.surface_intersections(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r4.empty());
        const auto r5 = s_degen.surface_intersections(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r5.empty());
        const auto r6 = s_degen.surface_intersections(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r6.approx_equal({ nnm::Point3f::zero() }));
        const auto r7 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r7.approx_equal({ { 1.0f, -2.0f, 1.5f } }));
        const auto r8 = s1.surface_intersections(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r8.empty());
    }

    test_section("intersects(const Segment3&)");
    {
        const auto r1 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1);
        const auto r2 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(r2);
        const auto r3 = s1.intersects(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(r3);
        const auto r4 = s1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r4);
        const auto r5 = s1.intersects(nnm::Segment3f(nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r5);
        const auto r6 = s_degen.intersects(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r6);
        const auto r7 = s_degen.intersects(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r7);
        const auto r8 = s1.intersects(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        TEST_ASSERT(r8);
    }

    test_section("surface_intersections(const Segment3&)");
    {
        const auto r1 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.approx_equal({ { -0.5f, -2.0f, 3.0f }, { 2.5f, -2.0f, 3.0f } }));
        const auto r2 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r2.empty());
        const auto r3 = s1.surface_intersections(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r3.empty());
        const auto r4 = s1.surface_intersections(nnm::Segment3f(nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r4.empty());
        const auto r5 = s1.surface_intersections(nnm::Segment3f(nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r5.empty());
        const auto r6 = s_degen.surface_intersections(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r6.empty());
        const auto r7 = s_degen.surface_intersections(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r7.approx_equal({ nnm::Point3f::zero() }));
        const auto r8 = s1.surface_intersections(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        TEST_ASSERT(r8.approx_equal({ { 1.0f, -2.0f, 1.5f } }));
    }

    test_section("intersects(const Sphere&)");
    {
        constexpr auto r1 = s1.intersects(s1);
        TEST_ASSERT(r1);
        constexpr auto r2 = s1.intersects(nnm::SphereF(nnm::Point3f::zero(), 1.0f));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1.intersects(s1.translate({ 1.5f, 0.0f, 0.0f }));
        TEST_ASSERT(r3);
        constexpr auto r4 = s1.intersects(s1.translate({ 3.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r4);
    }

    test_section("intersect_depth(const Sphere&)");
    {
        const auto r1 = s1.intersect_depth(s1);
        TEST_ASSERT(r1.has_value() && nnm::approx_equal(r1->length(), s1.radius * 2.0f));
        const auto r2 = s1.intersect_depth(nnm::SphereF(nnm::Point3f::zero(), 1.0f));
        TEST_ASSERT_FALSE(r2.has_value());
        const auto r3 = s1.intersect_depth(s1.translate({ 1.5f, 0.0f, 0.0f }));
        TEST_ASSERT(r3.has_value() && r3->approx_equal({ 1.5f, 0.0f, 0.0f }));
        const auto r4 = s1.intersect_depth(s1.translate({ 3.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r4.has_value());
    }

    test_section("tangent(const Line3&)");
    {
        constexpr auto r1 = s1.tangent(nnm::Line3f::axis_x_offset(-2.0f, 3.0f));
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = s1.tangent(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1.tangent(nnm::Line3f::axis_y_offset(2.5f, 3.0f));
        TEST_ASSERT(r3);
        constexpr auto r4 = s_degen.tangent(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.tangent(nnm::Line3f::axis_z());
        TEST_ASSERT(r5);
    }

    test_section("tangent(const Ray3&)");
    {
        constexpr auto r1 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1.tangent(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r3);
        constexpr auto r4 = s1.tangent(nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r4);
        constexpr auto r5 = s_degen.tangent(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r5);
        constexpr auto r6 = s_degen.tangent(nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT(r6);
        constexpr auto r7 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(r7);
        constexpr auto r8 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r8);
        constexpr auto r9 = s1.tangent(nnm::Ray3f({ -2.0f, -2.0f, 1.5f }, -nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(r9);
    }

    test_section("tangent(const Segment3&)");
    {
        const auto r1 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { 10.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(r1);
        const auto r2 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 3.0f }, { -10.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(r2);
        const auto r3 = s1.tangent(nnm::Segment3f({ 10.0f, -2.0f, 3.0f }, { 20.0f, -2.0f, 3.0f }));
        TEST_ASSERT_FALSE(r3);
        const auto r4 = s1.tangent(nnm::Segment3f(nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r4);
        const auto r5 = s1.tangent(nnm::Segment3f(nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r5);
        const auto r6 = s_degen.tangent(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r6);
        const auto r7 = s_degen.tangent(nnm::Segment3f({ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r7);
        const auto r8 = s1.tangent(nnm::Segment3f({ -2.0f, -2.0f, 1.5f }, { 5.0f, -2.0f, 1.5f }));
        TEST_ASSERT(r8);
        const auto r9 = s1.tangent(nnm::Segment3f({ -20.0f, -2.0f, 1.5f }, { -50.0f, -2.0f, 1.5f }));
        TEST_ASSERT_FALSE(r9);
    }

    test_section("translate");
    {
        constexpr auto r1 = s1.translate({ -3.0f, 4.5f, -5.0f });
        TEST_ASSERT(r1.approx_equal({ s1.center.translate({ -3.0f, 4.5f, -5.0f }), s1.radius }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 4.5f, -5.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = -2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = s1.rotate_axis_angle_at(origin, axis, angle);
        TEST_ASSERT(r1.approx_equal({ s1.center.rotate_axis_angle_at(origin, axis, angle), s1.radius }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = -2.0f * nnm::pi<float>() / 3.0f;
        const auto r1 = s1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(r1.approx_equal({ s1.center.rotate_axis_angle(axis, angle), s1.radius }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 4.5f, -5.0f };
        constexpr nnm::QuaternionF quat { 0.0f, -0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = s1.rotate_quaternion_at(origin, quat);
        TEST_ASSERT(r1.approx_equal({ s1.center.rotate_quaternion_at(origin, quat), s1.radius }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, -0.866025447f, 0.0f, 0.5f };
        constexpr auto r1 = s1.rotate_quaternion(quat);
        TEST_ASSERT(r1.approx_equal({ s1.center.rotate_quaternion(quat), s1.radius }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3f origin { -3.0f, 4.5f, -5.0f };
        constexpr float factor = 1.25f;
        constexpr auto r1 = s1.scale_at(origin, factor);
        TEST_ASSERT(r1.approx_equal({ s1.center.scale_at(origin, nnm::Vector3f::all(factor)), s1.radius * factor }));
    }

    test_section("scale");
    {
        constexpr float factor = 1.25f;
        constexpr auto r1 = s1.scale(factor);
        TEST_ASSERT(r1.approx_equal({ s1.center.scale(nnm::Vector3f::all(factor)), s1.radius * factor }));
    }

    test_section("approx_equal");
    {
        constexpr auto r1 = s1.approx_equal(s1);
        TEST_ASSERT(r1);
        constexpr auto r2 = s1.approx_equal(s_degen);
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1.approx_equal({ { 1.0f, -2.0f, 3.0f }, 1.5f });
        TEST_ASSERT(r3);
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = s1 == s1;
        TEST_ASSERT(r1);
        constexpr auto r2 = s1 == s_degen;
        TEST_ASSERT_FALSE(r2);
        constexpr auto r3 = s1 == nnm::SphereF({ 1.0f, -2.0f, 3.0f }, 1.5f);
        TEST_ASSERT(r3);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto r1 = s1 != s1;
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = s1 != s_degen;
        TEST_ASSERT(r2);
        constexpr auto r3 = s1 != nnm::SphereF({ 1.0f, -2.0f, 3.0f }, 1.5f);
        TEST_ASSERT_FALSE(r3);
    }

    test_section("operator<");
    {
        constexpr auto r1 = s1 < s_degen;
        TEST_ASSERT_FALSE(r1);
        constexpr auto r2 = s_degen < s1;
        TEST_ASSERT(r2);
    }
}

