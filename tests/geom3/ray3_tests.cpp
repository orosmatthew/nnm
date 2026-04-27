#include "tests.hpp"

void ray3_tests()
{
    test_case("Ray3");

    test_section("Ray3()");
    {
        constexpr nnm::Ray3f r1 { };
        TEST_ASSERT(r1.origin.approx_zero());
        TEST_ASSERT(r1.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
    }

    test_section("Ray3(const Vector3&, const Vector3&)");
    {
        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        TEST_ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.direction.approx_equal({ -4.0f, 5.0f, -6.0f }));
    }

    test_section("Ray3(const Ray3<Other>&)");
    {
        constexpr nnm::Ray3d r1 { { 1.0, -2.0, 3.0 }, { 4.0, 5.0, -6.0 } };
        constexpr nnm::Ray3f r2 { r1 };
        TEST_ASSERT(r2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r2.direction.approx_equal({ 4.0f, 5.0f, -6.0f }));
    }

    test_section("from_point_to_point");
    {
        const auto r1 = nnm::Ray3f::from_point_to_point({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f });
        TEST_ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.direction.approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
    }

    constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
    constexpr nnm::Ray3f r2 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

    test_section("valid");
    {
        constexpr bool result1 = r1.valid();
        TEST_ASSERT(result1);
        constexpr nnm::Ray3f degen_point { { 1.0f, -2.0f, 3.0f }, nnm::Vector3f::zero() };
        constexpr bool result2 = degen_point.valid();
        TEST_ASSERT_FALSE(result2);
    }

    test_section("collinear(const Vector3&)");
    {
        constexpr auto result = r1.collinear({ -2.0f, 2.0f, -2.0f });
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1.collinear({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r1.collinear({ 4.0f, -6.0f, 8.0f }));
    }

    test_section("collinear(const Line3&)");
    {
        TEST_ASSERT(r1.collinear(*nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f })));
        constexpr auto result = r1.collinear(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
    }

    test_section("collinear(const Ray3&)");
    {
        constexpr auto result = r1.collinear(r1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1.collinear(nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 10.0f, 20.0f, -0.5f })))
        ;TEST_ASSERT(
            r1.collinear(nnm::Ray3f::from_point_to_point({ 4.0f, -6.0f, 8.0f }, { 5.8099f, -8.4132f, 11.0165f })));
        TEST_ASSERT(
            r1.collinear(nnm::Ray3f::from_point_to_point({ 5.8099f, -8.4132f, 11.0165f }, { 4.0f, -6.0f, 8.0f })));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr auto result = r2.coplanar(nnm::Line3f::from_ray(r2));
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r2.coplanar(nnm::Line3f::axis_x()));
        auto l1 = nnm::Line3f::from_points(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(r2.coplanar(*l1));
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr auto result = r2.coplanar(r2);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r2.coplanar(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x())));
        auto r3 = nnm::Ray3f::from_point_to_point(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(r2.coplanar(r3));
    }

    test_section("coplanar(const Segment3&)");
    {
        TEST_ASSERT(r2.coplanar(nnm::Segment3f(r2.origin, r2.origin + r2.direction)));
        TEST_ASSERT_FALSE(r2.coplanar(nnm::Segment3f(nnm::Point3f::zero(), { 1.0f, 0.0f, 0.0f })));
        auto s1 = nnm::Segment3f(
            { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { -0.003134965f, -3.0097031925f, 4.5129127318f });
        TEST_ASSERT(r2.coplanar(s1));
    }

    test_section("coplanar(const Plane&)");
    {
        constexpr auto result = r2.coplanar(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(result);
        nnm::PlaneF plane { { -4.7984678398f, -1.8092603063f, 4.2111923428f }, { 0.154303f, 0.771517f, 0.617213f } };
        TEST_ASSERT(r2.coplanar(plane));
    }

    test_section("coplanar(const Triangle3&)");
    {
        TEST_ASSERT_FALSE(
            r2.coplanar(nnm::Triangle3f({ 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })));
        TEST_ASSERT(r2.coplanar(
            nnm::Triangle3f(
                { -4.7984678398f, -1.8092603063f, 4.2111923428f },
                { -0.003134965f, -3.0097031925f, 4.5129127318f },
                { -4.5435928528f, -3.1536294284f, 5.8279349987f })));
    }

    test_section("coplanar(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f rect { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr bool result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).coplanar(rect);
        TEST_ASSERT(result1);
        constexpr bool result2 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()).coplanar(rect);
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3 = nnm::Ray3f({ 0.0f, 1.0f, 1.0f }, nnm::Vector3f::axis_x()).coplanar(rect);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).coplanar(rect);
        TEST_ASSERT_FALSE(result4);
    }

    test_section("contains");
    {
        constexpr auto result = r1.contains({ -0.2f, -0.4f, 1.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(r1.contains({ -2.0f, 2.0f, -2.0f }));
        TEST_ASSERT_FALSE(r1.contains({ 0.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(r1.contains({ 1.54f, -2.72f, 3.9f }));
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr auto d1 = r1.distance_sqrd({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 0.48f));
        constexpr auto d2 = r1.distance_sqrd({ -2.0f, 2.0f, -2.0f });
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = r1.distance_sqrd({ 4.0f, -6.0f, 8.0f });
        TEST_ASSERT(nnm::approx_equal(d3, 50.0f));
        constexpr auto d4 = r1.distance_sqrd({ 4.0f, -5.0f, 9.0f });
        TEST_ASSERT(nnm::approx_equal(d4, 54.0f));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto d1 = r1.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, 0.09756112942397f));
        constexpr auto d2 = r1.distance_sqrd(nnm::Line3f::axis_x_offset(-4.0f, 5.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 8.0f));
        constexpr auto d3 = r1.distance_sqrd(nnm::Line3f::axis_z_offset(-2.0f, 2.0f));
        TEST_ASSERT(nnm::approx_zero(d3));
        constexpr auto d4 = r1.distance_sqrd(nnm::Line3f::from_ray(r1));
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr auto d1 = r1.distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_zero(d1));
        constexpr auto d2 = r1.distance_sqrd(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.48f));
        constexpr auto d3 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.48f));
        constexpr auto d4 = r1.distance_sqrd(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.09756112942397f));
        constexpr auto d5 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.09756112942397f));
        constexpr auto d6 = r1.distance_sqrd(nnm::Ray3f({ 3.0f, -4.0f, 5.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 12.0f));
        constexpr auto d7 = nnm::Ray3f({ 3.0f, -4.0f, 5.0f }, { 1.0f, 0.0f, 0.0f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d7, 12.0f));
        constexpr auto d8 = r1.distance_sqrd(nnm::Ray3f({ 2.0f, 0.0f, 0.0f }, { -0.424264f, 0.565685f, -0.707107f }));
        TEST_ASSERT(nnm::approx_equal(d8, 6.0f));
        constexpr auto d9 = nnm::Ray3f({ 2.0f, 0.0f, 0.0f }, { -0.424264f, 0.565685f, -0.707107f }).distance_sqrd(r1);
        TEST_ASSERT(nnm::approx_equal(d9, 6.0f));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto d1 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.34838709676763f));
        constexpr auto d2 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.06923076776146f));
        constexpr auto d3 = nnm::Ray3f({ 2.0f, -4.0f, 3.0f }, { 0.57735f, -0.57735f, 0.57735f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d3, 5.0f));
        constexpr auto d4 = nnm::Ray3f({ 2.0f, -4.0f, 3.0f }, { -0.57735f, 0.57735f, -0.57735f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d4, 1.5f));
        constexpr auto d5 = nnm::Ray3f({ -5.0f, 7.0f, -7.0f }, { -0.447214f, 0.894427f, 0.0f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d5, 6.0f));
        constexpr auto d6 = nnm::Ray3f({ -5.0f, 7.0f, -7.0f }, { 0.492366f, -0.615457f, 0.615457f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_equal(d6, 0.35217364711461f));
        constexpr auto d7 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -0.597615f, 0.577107f, -0.556599f }).distance_sqrd(s1);
        TEST_ASSERT(nnm::approx_zero(d7));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d1, 2.0F));
        constexpr auto d2
            = nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d3, 2.0F));
        constexpr auto d4 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d4, 18.0f));
        constexpr auto d5 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_equal(d5, 18.0f));
        constexpr auto d6 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() }.distance_sqrd(p2);
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr auto d1 = nnm::Ray3f({ -1.0f, 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d1, 2.36885245894616f));
        constexpr auto d2 = nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance_sqrd(t1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.29508196726188f));
    }

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f rect { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr auto result1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance_sqrd(rect);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2 = nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() }.distance_sqrd(rect);
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3
            = nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance_sqrd(rect);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4
            = nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } }.distance_sqrd(rect);
        TEST_ASSERT(nnm::approx_equal(result4, 2.0f))
        ;constexpr auto result5
            = nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.distance_sqrd(rect);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6
            = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        constexpr auto result7
            = nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8
            = nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result8));
        constexpr auto result9
            = nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result9, 4.0f));
        constexpr auto result10
            = nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() }.distance_sqrd(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result10, 9.0f));
        constexpr auto result11
            = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() }.distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result11, 7.25f));
        constexpr auto result12
            = nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() }.distance_sqrd(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance_sqrd(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        constexpr float result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result1, 0.25f));
        constexpr float result2 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr float result3 = nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result3, 0.25f));
    }

    test_section("distance_sqrd(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        constexpr float result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.5183982895123f));
        constexpr float result2 = nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.9362916305822f));
        constexpr float result3 = nnm::Ray3f({ 0.0f, 0.0f, 1.5f }, nnm::Vector3f::axis_y()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result3, 0.07169918465782f));
        constexpr float result4 = nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, nnm::Vector3f::axis_z()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr float result5 = nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, -nnm::Vector3f::axis_z()).distance_sqrd(b1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.9362916305822f));
    }

    test_section("distance(const Vector3&)");
    {
        const auto d1 = r1.distance({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(d1, 0.692820311f));
        const auto d2 = r1.distance({ -2.0f, 2.0f, -2.0f });
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = r1.distance({ 4.0f, -6.0f, 8.0f });
        TEST_ASSERT(nnm::approx_equal(d3, 7.0711f));
        const auto d4 = r1.distance({ 4.0f, -5.0f, 9.0f });
        TEST_ASSERT(nnm::approx_equal(d4, 7.3485f));
    }

    test_section("distance(const Line3&)");
    {
        const auto d1 = r1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(d1, 0.31234777f));
        const auto d2 = r1.distance(nnm::Line3f::axis_x_offset(-4.0f, 5.0f));
        TEST_ASSERT(nnm::approx_equal(d2, 2.82842708f));
        const auto d3 = r1.distance(nnm::Line3f::axis_z_offset(-2.0f, 2.0f));
        TEST_ASSERT(nnm::approx_zero(d3));
        const auto d4 = r1.distance(nnm::Line3f::from_ray(r1));
        TEST_ASSERT(nnm::approx_zero(d4));
    }

    test_section("distance(const Ray3&)");
    {
        const auto d1 = r1.distance(r1);
        TEST_ASSERT(nnm::approx_zero(d1));
        const auto d2 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d2, 0.692820311f));
        const auto d3 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.692820311f));
        const auto d4 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(nnm::approx_equal(d4, 0.31234777f));
        const auto d5 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d5, 0.31234777f));
        const auto d6 = r1.distance(nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }));
        TEST_ASSERT(nnm::approx_equal(d6, 3.4641f));
        const auto d7 = nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d7, 3.4641f));
        const auto d8 = r1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }));
        TEST_ASSERT(nnm::approx_equal(d8, 2.4495f));
        const auto d9 = nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }).distance(r1);
        TEST_ASSERT(nnm::approx_equal(d9, 2.4495f));
    }

    test_section("distance(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        const auto d1 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d1, 0.5902432522f));
        const auto d2 = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d2, 0.263117403f));
        const auto d3 = nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 3.0f, -5.0f, 4.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d3, 2.2360679775f));
        const auto d4 = nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 1.0f, -3.0f, 2.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d4, 1.2247448f));
        const auto d5 = nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -6.0f, 9.0f, -7.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d5, 2.4494897428f));
        const auto d6 = nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -1.0f, 2.0f, -2.0f }).distance(s1);
        TEST_ASSERT(nnm::approx_equal(d6, 0.593442202f));
        const auto d7
            = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.3814812713f, 1.3340737798f, -1.2866662883f })
                  .distance(s1);
        TEST_ASSERT(nnm::approx_zero(d7));
    }

    test_section("distance(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto d1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d1, nnm::sqrt(2.0f)));
        constexpr auto d2 = nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d2));
        constexpr auto d3 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d3, nnm::sqrt(2.0f)));
        constexpr auto d4 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d4, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d5 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_x() }.distance(p2);
        TEST_ASSERT(nnm::approx_equal(d5, 3.0f * nnm::sqrt(2.0f)));
        constexpr auto d6 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() }.distance(p2);
        TEST_ASSERT(nnm::approx_zero(d6));
    }

    test_section("distance(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        const auto d1 = nnm::Ray3f({ -1.0f, 2.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d1, 1.5391076827f));
        const auto d2 = nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_zero(d2));
        const auto d3 = nnm::Ray3f({ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }).distance(t1);
        TEST_ASSERT(nnm::approx_equal(d3, 0.5432144763f));
    }

    test_section("distance(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f rect { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        const auto result1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance(rect);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2 = nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() }.distance(rect);
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3
            = nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } }.distance(rect);
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4
            = nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } }.distance(rect);
        TEST_ASSERT(nnm::approx_equal(result4, 1.4142135624f))
        ;const auto result5 = nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } }.distance(rect);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        const auto result7 = nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result7));
        const auto result8 = nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_zero(result8));
        const auto result9 = nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        const auto result10 = nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() }.distance(r_degen_line);
        TEST_ASSERT(nnm::approx_equal(result10, 3.0f));
        const auto result11 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() }.distance(r_degen_point);
        TEST_ASSERT(nnm::approx_equal(result11, 2.6925824036f));
        const auto result12 = nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() }.distance(r_degen_point);
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance(const Sphere&)");
    {
        constexpr nnm::SphereF s1 { { 1.0f, -2.0f, 3.0f }, 1.5f };
        constexpr nnm::SphereF s_degen { { 0.0f, 0.0f, 0.0f }, 0.0f };
        const auto result1 = nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_x()).distance(s1);
        TEST_ASSERT(nnm::approx_zero(result1));
        const auto result2 = nnm::Ray3f({ -2.0f, -2.0f, 3.0f }, -nnm::Vector3f::axis_x()).distance(s1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.5f));
        const auto result3 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).distance(s1);
        TEST_ASSERT(nnm::approx_equal(result3, 2.1055512755f));
        const auto result4 = nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()).distance(s1);
        TEST_ASSERT(nnm::approx_equal(result4, 2.2416573868f));
        const auto result5 = nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, nnm::Vector3f::axis_x()).distance(s_degen);
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = nnm::Ray3f({ 1.0f, 0.0f, 0.0f }, -nnm::Vector3f::axis_x()).distance(s_degen);
        TEST_ASSERT(nnm::approx_zero(result6));
    }

    test_section("distance(const AlignedBox&)");
    {
        constexpr nnm::AlignedBoxF b1 { { -1.0f, -3.0f, 0.5f }, { 2.0f, 2.0f, 4.0f } };
        const float result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result1, 0.5f));
        const float result2 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_z()).distance(b1);
        TEST_ASSERT(nnm::approx_zero(result2));
        const float result3 = nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_z()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result3, 0.5f));
    }

    test_section("distance(const Box&)");
    {
        constexpr nnm::BoxF b1 { { 1.0f, -2.0f, 3.0f },
                                 { 0.707106769f, 0.0f, -0.707106769f },
                                 { 0.0f, 2.0f, 0.0f },
                                 { 1.06066012f, 0.0f, 1.06066012f } };
        const float result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result1, 1.23223305f));
        const float result2 = nnm::Ray3f(nnm::Point3f::zero(), -nnm::Vector3f::axis_x()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result2, 1.3915069639f));
        const float result3 = nnm::Ray3f({ 0.0f, 0.0f, 1.5f }, nnm::Vector3f::axis_y()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result3, 0.2677670343f));
        const float result4 = nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, nnm::Vector3f::axis_z()).distance(b1);
        TEST_ASSERT(nnm::approx_zero(result4));
        const float result5 = nnm::Ray3f({ 0.0f, -1.0f, 0.0f }, -nnm::Vector3f::axis_z()).distance(b1);
        TEST_ASSERT(nnm::approx_equal(result5, 1.3915069639f));
    }

    test_section("project");
    {
        constexpr auto p1 = r1.project({ 2.0f, 0.0f, 0.0f });
        TEST_ASSERT(p1.approx_equal({ -0.2f, -0.4f, 1.0f }));
        constexpr auto p2 = r1.project({ 6.0f, -4.0f, 6.0f });
        TEST_ASSERT(p2.approx_equal({ 1.0f, -2.0f, 3.0f }));
        constexpr auto p3 = r1.project({ -2.0f, 2.0f, -2.0f });
        TEST_ASSERT(p3.approx_equal({ -2.0f, 2.0f, -2.0f }));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr auto result = r1.parallel(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1.parallel(*nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr auto result = r1.parallel(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.57735f, 0.57735f, 0.57735f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1.parallel(nnm::Ray3f::from_point_to_point({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
    }

    test_section("parallel(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        constexpr auto result = nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }).parallel(s1);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::Ray3f::from_point_to_point(s1.start, s1.end).parallel(s1));
        TEST_ASSERT(nnm::Ray3f(s1.start + nnm::Vector3f(2.0f, -3.0f, 10.0f), -s1.direction()).parallel(s1));
    }

    test_section("parallel(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto result1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() }.parallel(p2);
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2
            = nnm::Ray3f { nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() } }.parallel(p2);
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.parallel(p2);
        TEST_ASSERT(result3);
        constexpr auto result4 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_y() }.parallel(p2);
        TEST_ASSERT_FALSE(result4);
        constexpr auto result5 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, -nnm::Vector3f::axis_x() }.parallel(p2);
        TEST_ASSERT(result5);
        constexpr auto result6 = nnm::Ray3f { { -100.0f, -4.0f, -4.0f }, nnm::Vector3f::axis_z() }.parallel(p2);
        TEST_ASSERT_FALSE(result6);
    }

    test_section("parallel(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr nnm::Triangle3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };
        constexpr bool result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).parallel(t1);
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2 = nnm::Ray3f(nnm::Point3f::zero(), { -0.801783f, -0.534522f, 0.267261f }).parallel(t1);
        TEST_ASSERT(result2);
        constexpr bool result3 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).parallel(degen_line);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()).parallel(degen_line);
        TEST_ASSERT_FALSE(result4);
        constexpr bool result5 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).parallel(degen_point);
        TEST_ASSERT(result5);
        constexpr bool result6 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()).parallel(degen_point);
        TEST_ASSERT(result6);
    }

    test_section("parallel(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f rect { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr bool result1 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).parallel(rect);
        TEST_ASSERT(result1);
        constexpr bool result2 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).parallel(rect);
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3
            = nnm::Ray3f({ 0.0f, -1.0f, 10.0f }, { 0.0f, 0.70710678118655f, 0.70710678118655f }).parallel(rect);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).parallel(r_degen_line);
        TEST_ASSERT(result4);
        constexpr bool result5 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).parallel(r_degen_line);
        TEST_ASSERT_FALSE(result5);
        constexpr bool result6 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).parallel(r_degen_point);
        TEST_ASSERT(result6);
        constexpr bool result7 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).parallel(r_degen_point);
        TEST_ASSERT(result7);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr auto result = r1.perpendicular(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1.perpendicular(*nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr auto result = r1.perpendicular(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.57735f, 0.57735f, 0.57735f }));
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1.perpendicular(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
    }

    test_section("perpendicular(const Segment3&)");
    {
        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
        TEST_ASSERT_FALSE(
            nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, -1.0f }).perpendicular(s1));
        constexpr auto r3 = nnm::Ray3f { { 0.0f, 0.0f, 0.0f }, { -0.819782316f, 0.131165162f, 0.557451963f } };
        TEST_ASSERT(r3.perpendicular(s1));
        constexpr auto result = nnm::Ray3f(r3.origin, -r3.direction).perpendicular(s1);
        TEST_ASSERT(result);
    }

    test_section("perpendicular(const Plane&)");
    {
        constexpr nnm::PlaneF p2 { { 1.0f, -2.0f, 0.0f }, { 0, 0.707107f, 0.707107f } };
        constexpr auto result1 = nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() }.perpendicular(p2);
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_y() }.perpendicular(p2);
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3 = nnm::Ray3f { nnm::Point3f::zero(), p2.normal }.perpendicular(p2);
        TEST_ASSERT(result3);
        constexpr auto result4 = nnm::Ray3f { nnm::Point3f::zero(), -p2.normal }.perpendicular(p2);
        TEST_ASSERT(result4);
    }

    test_section("perpendicular(const Triangle3&)");
    {
        constexpr nnm::Triangle3f t1 { { 1.0f, -2.0f, 3.0f }, { -2.0f, 3.0f, -4.0f }, { 4.0f, 0.0f, 2.0f } };
        constexpr nnm::Triangle3f degen_line { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
        constexpr nnm::Triangle3f degen_point { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };
        constexpr bool result1 = nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()).perpendicular(t1);
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2
            = nnm::Ray3f({ 100.0f, 0.0f, 0.0f }, { 0.271607f, -0.724286f, -0.63375f }).perpendicular(t1);
        TEST_ASSERT(result2);
        constexpr bool result3 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).perpendicular(degen_line);
        TEST_ASSERT_FALSE(result3);
        constexpr bool result4 = nnm::Ray3f({ -10.0f, 10.0f, 0.0f }, nnm::Vector3f::axis_z()).perpendicular(degen_line);
        TEST_ASSERT(result4);
        constexpr bool result5 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).perpendicular(degen_point);
        TEST_ASSERT(result5);
        constexpr bool result6
            = nnm::Ray3f({ -10.0f, 10.0f, 0.0f }, nnm::Vector3f::axis_z()).perpendicular(degen_point);
        TEST_ASSERT(result6);
    }

    test_section("perpendicular(const Rectangle3&)");
    {
        constexpr nnm::Rectangle3f rect { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
        constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
        constexpr bool result1 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).perpendicular(rect);
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).perpendicular(rect);
        TEST_ASSERT_FALSE(result2)
        ;constexpr bool result3
            = nnm::Ray3f(nnm::Point3f::zero(), { 0.0f, 0.70710678118655f, -0.70710678118655f }).perpendicular(rect);
        TEST_ASSERT(result3);
        constexpr bool result4 = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).perpendicular(r_degen_line);
        TEST_ASSERT_FALSE(result4);
        constexpr bool result5 = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).perpendicular(r_degen_line);
        TEST_ASSERT(result5);
        constexpr bool result6
            = nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()).perpendicular(r_degen_point);
        TEST_ASSERT(result6);
        constexpr bool result7
            = nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()).perpendicular(r_degen_point);
        TEST_ASSERT(result7);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result = r1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1.intersects(*nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f })));
        TEST_ASSERT(r1.intersects(*nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f })));
        TEST_ASSERT_FALSE(r1.intersects(*nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f })));
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto i1 = r1.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = r1.intersection(*nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }));
        TEST_ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i3 = r1.intersection(*nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }));
        TEST_ASSERT_FALSE(i3.has_value());
        const auto i4 = r1.intersection(*nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }));
        TEST_ASSERT_FALSE(i4.has_value());
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto result = r1.intersects(r1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(r1.intersects(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
        TEST_ASSERT(r1.intersects(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f })));
        TEST_ASSERT_FALSE(
            r1.intersects(nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f })));
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr auto i1 = r1.intersection(r1);
        TEST_ASSERT_FALSE(i1.has_value());
        const auto i2 = r1.intersection(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT_FALSE(i2.has_value());
        const auto i3 = r1.intersection(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f }));
        TEST_ASSERT(i3.has_value() && i3.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
        const auto i4
            = r1.intersection(nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f }));
        TEST_ASSERT_FALSE(i4.has_value());
    }

    test_section("translate");
    {
        constexpr auto t1 = r2.translate({ 5.0f, 6.0f, -7.0f });
        TEST_ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, r2.direction }));
    }

    test_section("scale_at");
    {
        const auto s1 = r2.scale_at({ 5.0f, 6.0f, -7.0f }, { 0.5f, -2.0f, 3.0f });
        TEST_ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("scale");
    {
        const auto s1 = r2.scale({ 0.5f, -2.0f, 3.0f });
        TEST_ASSERT(s1.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
    }

    test_section("rotate_axis_angle_at");
    {
        const auto r1r = r2.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        TEST_ASSERT(r1r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_axis_angle");
    {
        const auto r1r = r2.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        TEST_ASSERT(r1r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion_at");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r = r2.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
        TEST_ASSERT(r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("rotate_quaternion");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
        const auto r = r2.rotate_quaternion(q1);
        TEST_ASSERT(r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
    }

    test_section("shear_x_at");
    {
        const auto s1 = r2.shear_x_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_x");
    {
        const auto s1 = r2.shear_x(0.5f, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
    }

    test_section("shear_y_at");
    {
        const auto s1 = r2.shear_y_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_y");
    {
        const auto s1 = r2.shear_y(0.5, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
    }

    test_section("shear_z_at");
    {
        const auto s1 = r2.shear_z_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("shear_z");
    {
        const auto s1 = r2.shear_z(0.5f, -0.5f);
        TEST_ASSERT(s1.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = r1.approx_equal(r1);
        TEST_ASSERT(result);
        TEST_ASSERT(r2.approx_equal(r2));
        TEST_ASSERT_FALSE(r1.approx_equal(r2));
        TEST_ASSERT_FALSE(r2.approx_equal(r1));
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = r1 == r1;
        TEST_ASSERT(result);
        TEST_ASSERT(r2 == r2);
        TEST_ASSERT_FALSE(r1 == r2);
        TEST_ASSERT_FALSE(r2 == r1);
    }

    test_section("operator!=");
    {
        constexpr auto result = r1 != r2;
        TEST_ASSERT(result);
        TEST_ASSERT(r2 != r1);
        TEST_ASSERT_FALSE(r1 != r1);
        TEST_ASSERT_FALSE(r2 != r2);
    }

    test_section("operator<");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result = r1 < r1;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(r1 < r2);
        TEST_ASSERT_FALSE(r2 < r1);
    }
}

