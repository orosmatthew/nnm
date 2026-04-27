#include "tests.hpp"

void rectangle3_tests()
{
    test_case("Rectangle3");

    test_section("Rectangle3()");
    {
        constexpr nnm::Rectangle3f r1;
        TEST_ASSERT(r1.center.approx_zero());
        TEST_ASSERT(r1.half_span_u.approx_zero());
        TEST_ASSERT(r1.half_span_v.approx_zero());
    }

    test_section("Rectangle3(const Vector3&, const Vector3&, const Vector3&)");
    {
        constexpr nnm::Rectangle3f r1 { { 1.0, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 7.0f, -8.0f, 0.0f } };
        TEST_ASSERT(r1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.half_span_u.approx_equal({ -4.0f, 5.0f, -6.0f }));
        TEST_ASSERT(r1.half_span_v.approx_equal({ 7.0f, -8.0f, 0.0f }));
    }

    test_section("from_xy_offset_size");
    {
        constexpr auto r1 = nnm::Rectangle3f::from_xy_offset_size({ 1.0f, -2.0f, 3.0f }, 2.0f, 3.5f);
        TEST_ASSERT(r1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.half_span_u.approx_equal({ 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r1.half_span_v.approx_equal({ 0.0f, 1.75f, 0.0f }));
    }

    test_section("from_xz_offset_size");
    {
        constexpr auto r1 = nnm::Rectangle3f::from_xz_offset_size({ 1.0f, -2.0f, 3.0f }, 2.0f, 3.5f);
        TEST_ASSERT(r1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.half_span_u.approx_equal({ 1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r1.half_span_v.approx_equal({ 0.0f, 0.0f, 1.75f }));
    }

    test_section("from_yz_offset_size");
    {
        constexpr auto r1 = nnm::Rectangle3f::from_yz_offset_size({ 1.0f, -2.0f, 3.0f }, 2.0f, 3.5f);
        TEST_ASSERT(r1.center.approx_equal({ 1.0f, -2.0f, 3.0f }));
        TEST_ASSERT(r1.half_span_u.approx_equal({ 0.0f, 1.0f, 0.0f }));
        TEST_ASSERT(r1.half_span_v.approx_equal({ 0.0f, 0.0f, 1.75f }));
    }

    constexpr nnm::Rectangle3f r1 { { -2.5f, 1.0f, 1.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } };
    constexpr nnm::Rectangle3f r_degen_line { { -2.5f, 0.0f, 0.0f }, { -1.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    constexpr nnm::Rectangle3f r_degen_point { { -2.5f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

    test_section("collapse_segment");
    {
        constexpr std::optional<nnm::Segment3f> result1 = r1.collapse_segment();
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr std::optional<nnm::Segment3f> result2 = r_degen_line.collapse_segment();
        TEST_ASSERT(
            result2.has_value() && result2.value().coincident({ { -4.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }));
        constexpr std::optional<nnm::Segment3f> result3 = r_degen_point.collapse_segment();
        TEST_ASSERT(
            result3.has_value() && result3.value().approx_equal({ { -2.5f, 1.0f, 1.0f }, { -2.5f, 1.0f, 1.0f } }));
    }

    test_section("collapse_point");
    {
        constexpr std::optional<nnm::Point3f> result1 = r1.collapse_point();
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr std::optional<nnm::Point3f> result2 = r_degen_line.collapse_point();
        TEST_ASSERT_FALSE(result2.has_value());
        constexpr std::optional<nnm::Point3f> result3 = r_degen_point.collapse_point();
        TEST_ASSERT(result3.has_value() && result3.value().approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("valid");
    {
        constexpr nnm::Rectangle3f r2 { { 1.0, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 7.0f, -8.0f, 0.0f } };
        constexpr auto result1 = r2.valid();
        TEST_ASSERT_FALSE(result1);
        constexpr auto r3 = nnm::Rectangle3f::from_yz_offset_size({ 1.0f, -2.0f, 3.0f }, 2.0f, 3.5f);
        constexpr auto result2 = r3.valid();
        TEST_ASSERT(result2);
    }

    test_section("vertex");
    {
        constexpr nnm::Point3f v0 = r1.vertex(0);
        TEST_ASSERT(v0.approx_equal({ -1.0f, 0.0f, 0.0f }));
        constexpr nnm::Point3f v1 = r1.vertex(1);
        TEST_ASSERT(v1.approx_equal({ -1.0f, 2.0f, 2.0f }));
        constexpr nnm::Point3f v2 = r1.vertex(2);
        TEST_ASSERT(v2.approx_equal({ -4.0f, 0.0f, 0.0f }));
        constexpr nnm::Point3f v3 = r1.vertex(3);
        TEST_ASSERT(v3.approx_equal({ -4.0f, 2.0f, 2.0f }));

        TEST_ASSERT(r_degen_line.vertex(0).approx_equal({ -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r_degen_line.vertex(1).approx_equal({ -1.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r_degen_line.vertex(2).approx_equal({ -4.0f, 0.0f, 0.0f }));
        TEST_ASSERT(r_degen_line.vertex(3).approx_equal({ -4.0f, 0.0f, 0.0f }));

        TEST_ASSERT(r_degen_point.vertex(0).approx_equal({ -2.5f, 1.0f, 1.0f }));
        TEST_ASSERT(r_degen_point.vertex(1).approx_equal({ -2.5f, 1.0f, 1.0f }));
        TEST_ASSERT(r_degen_point.vertex(2).approx_equal({ -2.5f, 1.0f, 1.0f }));
        TEST_ASSERT(r_degen_point.vertex(3).approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("edge");
    {
        constexpr nnm::Segment3f e0 = r1.edge(0);
        TEST_ASSERT(e0.coincident({ { -1.0f, 0.0f, 0.0f }, { -1.0f, 2.0f, 2.0f } }));
        constexpr nnm::Segment3f e1 = r1.edge(1);
        TEST_ASSERT(e1.coincident({ { -1.0f, 2.0f, 2.0f }, { -4.0f, 2.0f, 2.0f } }));
        constexpr nnm::Segment3f e2 = r1.edge(2);
        TEST_ASSERT(e2.coincident({ { -4.0f, 2.0f, 2.0f }, { -4.0f, 0.0f, 0.0f } }));
        constexpr nnm::Segment3f e3 = r1.edge(3);
        TEST_ASSERT(e3.coincident({ { -4.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }));

        TEST_ASSERT(r_degen_line.edge(0).coincident({ { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }));
        TEST_ASSERT(r_degen_line.edge(1).coincident({ { -1.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f } }));
        TEST_ASSERT(r_degen_line.edge(2).coincident({ { -4.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f } }));
        TEST_ASSERT(r_degen_line.edge(3).coincident({ { -4.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }));

        TEST_ASSERT(r_degen_point.edge(0).coincident({ { -2.5f, 1.0f, 1.0f }, { -2.5f, 1.0f, 1.0f } }));
        TEST_ASSERT(r_degen_point.edge(1).coincident({ { -2.5f, 1.0f, 1.0f }, { -2.5f, 1.0f, 1.0f } }));
        TEST_ASSERT(r_degen_point.edge(2).coincident({ { -2.5f, 1.0f, 1.0f }, { -2.5f, 1.0f, 1.0f } }));
        TEST_ASSERT(r_degen_point.edge(3).coincident({ { -2.5f, 1.0f, 1.0f }, { -2.5f, 1.0f, 1.0f } }));
    }

    test_section("size_u");
    {
        TEST_ASSERT(nnm::approx_equal(r1.size_u(), 3.0f));
        TEST_ASSERT(nnm::approx_equal(r_degen_line.size_u(), 3.0f));
        TEST_ASSERT(nnm::approx_zero(r_degen_point.size_u()));
    }

    test_section("size_v");
    {
        TEST_ASSERT(nnm::approx_equal(r1.size_v(), 2.8284271247f));
        TEST_ASSERT(nnm::approx_zero(r_degen_line.size_v()));
        TEST_ASSERT(nnm::approx_zero(r_degen_point.size_v()));
    }

    test_section("area");
    {
        TEST_ASSERT(nnm::approx_equal(r1.area(), 8.4852813742f));
        TEST_ASSERT(nnm::approx_zero(r_degen_line.area()));
        TEST_ASSERT(nnm::approx_zero(r_degen_point.area()));
    }

    test_section("perimeter");
    {
        TEST_ASSERT(nnm::approx_equal(r1.perimeter(), 11.6568542494f));
        TEST_ASSERT(nnm::approx_equal(r_degen_line.perimeter(), 6.0f));
        TEST_ASSERT(nnm::approx_zero(r_degen_point.perimeter()));
    }

    test_section("coplanar(const Line3&)");
    {
        constexpr bool result1 = r1.coplanar(nnm::Line3f::axis_x());
        TEST_ASSERT(result1);
        constexpr bool result2 = r1.coplanar(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3 = r1.coplanar(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(result3);
        constexpr bool result4 = r1.coplanar(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT_FALSE(result4);
    }

    test_section("coplanar(const Ray3&)");
    {
        constexpr bool result1 = r1.coplanar(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_x()));
        TEST_ASSERT(result1);
        constexpr bool result2 = r1.coplanar(nnm::Ray3f(nnm::Point3f::zero(), nnm::Vector3f::axis_y()));
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3 = r1.coplanar(nnm::Ray3f({ 0.0f, 1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(result3);
        constexpr bool result4 = r1.coplanar(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(result4);
    }

    test_section("contains");
    {
        constexpr auto result1 = r1.contains(r1.vertex(0));
        TEST_ASSERT(result1);
        constexpr auto result2 = r1.contains({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT(result2);
        constexpr auto result3 = r1.contains({ -2.0f, 0.0f, -2.0f });
        TEST_ASSERT_FALSE(result3);
        constexpr auto result4 = r1.contains({ 0.0f, 1.0f, 1.0f });
        TEST_ASSERT_FALSE(result4);
        constexpr auto result5 = r_degen_line.contains({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6 = r_degen_line.contains({ -2.0f, 0.0f, 0.0f });
        TEST_ASSERT(result6);
        constexpr auto result7 = r_degen_line.contains({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result7);
        constexpr auto result8 = r_degen_point.contains({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT_FALSE(result8);
        constexpr auto result9 = r_degen_point.contains({ -2.5f, 1.0f, 1.0f });
        TEST_ASSERT(result9);
    }

    test_section("distance_sqrd(const Vector3&)");
    {
        constexpr auto result1 = r1.distance_sqrd(r1.vertex(0));
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = r1.distance_sqrd({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3 = r1.distance_sqrd({ -2.0f, 0.0f, 2.0f });
        TEST_ASSERT(nnm::approx_equal(result3, 2.0f));
        constexpr auto result4 = r1.distance_sqrd({ 0.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        constexpr auto result5 = r_degen_line.distance_sqrd({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(result5, 2.0f));
        constexpr auto result6 = r_degen_line.distance_sqrd({ -2.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_zero(result6));
        constexpr auto result7 = r_degen_line.distance_sqrd({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        constexpr auto result8 = r_degen_point.distance_sqrd({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result8, 8.25f));
        constexpr auto result9 = r_degen_point.distance_sqrd({ -2.5f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance_sqrd(const Line3&)");
    {
        constexpr auto result1 = r1.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = r1.distance_sqrd(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3
            = r1.distance_sqrd(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4
            = r1.distance_sqrd(nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        constexpr auto result5
            = r1.distance_sqrd(nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = r_degen_line.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_zero(result6));
        constexpr auto result7 = r_degen_line.distance_sqrd(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        constexpr auto result8 = r_degen_line.distance_sqrd(
            nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result8, 2.0f));
        constexpr auto result9 = r_degen_point.distance_sqrd(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        constexpr auto result10 = r_degen_point.distance_sqrd(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(nnm::approx_zero(result10));
    }

    test_section("distance_sqrd(const Ray3&)");
    {
        constexpr auto result1 = r1.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2 = r1.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3
            = r1.distance_sqrd(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4
            = r1.distance_sqrd(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result4, 2.0f))
        constexpr auto result5
            = r1.distance_sqrd(nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6
            = r_degen_line.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        constexpr auto result7
            = r_degen_line.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8
            = r_degen_line.distance_sqrd(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(result8));
        constexpr auto result9
            = r_degen_line.distance_sqrd(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result9, 4.0f));
        constexpr auto result10
            = r_degen_line.distance_sqrd(nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result10, 9.0f));
        constexpr auto result11
            = r_degen_point.distance_sqrd(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result11, 7.25f));
        constexpr auto result12
            = r_degen_point.distance_sqrd(nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() });
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance_sqrd(const Segment3&)");
    {
        constexpr auto result1 = r1.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2 = r1.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3 = r1.distance_sqrd(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = r1.distance_sqrd(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } });
        TEST_ASSERT(nnm::approx_equal(result4, 2.0f))
        constexpr auto result5 = r1.distance_sqrd(nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6
            = r_degen_line.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        constexpr auto result7
            = r_degen_line.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8
            = r_degen_line.distance_sqrd(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result8));
        constexpr auto result9
            = r_degen_line.distance_sqrd(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result9, 4.0f));
        constexpr auto result10
            = r_degen_line.distance_sqrd(nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } });
        TEST_ASSERT(nnm::approx_equal(result10, 9.0f));
        constexpr auto result11
            = r_degen_point.distance_sqrd(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result11, 7.25f));
        constexpr auto result12
            = r_degen_point.distance_sqrd(nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } });
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance_sqrd(const Plane&)");
    {
        constexpr auto result1 = r1.distance_sqrd(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = r1.distance_sqrd(nnm::PlaneF::yz());
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3 = r1.distance_sqrd(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = r_degen_line.distance_sqrd(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr auto result5 = r_degen_line.distance_sqrd(nnm::PlaneF::yz());
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = r_degen_line.distance_sqrd(nnm::PlaneF::xy_offset(2.0f));
        TEST_ASSERT(nnm::approx_equal(result6, 4.0f));
        constexpr auto result7 = r_degen_line.distance_sqrd(nnm::PlaneF::yz_offset(-3.0f));
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8 = r_degen_point.distance_sqrd(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(result8, 1.0f));
        constexpr auto result9 = r_degen_point.distance_sqrd(nnm::PlaneF::yz_offset(-2.5f));
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance_sqrd(const Triangle3&)");
    {
        constexpr auto result1
            = r1.distance_sqrd(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2
            = r1.distance_sqrd(nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result2));
        constexpr auto result3
            = r1.distance_sqrd(nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = r_degen_line.distance_sqrd(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        constexpr auto result5 = r_degen_line.distance_sqrd(
            nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result5));
        constexpr auto result6 = r_degen_point.distance_sqrd(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result6, 6.75f));
        constexpr auto result8 = r_degen_point.distance_sqrd(
            nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result8));
    }

    constexpr nnm::Rectangle3f r2 { { 1.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, -1.5f, 0.0f } };
    constexpr nnm::Rectangle3f r3 { { -2.5f, -2.0f, 1.0f }, { -0.5f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } };
    constexpr nnm::Rectangle3f r4 { { -2.5f, 0.5f, 1.0f }, { -0.5f, 0.0f, 0.0f }, { 0.0f, 1.5f, 0.0f } };
    constexpr nnm::Rectangle3f r5 { { -1.0f, 0.5f, 1.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, -2.0f, 0.0f } };
    constexpr nnm::Rectangle3f r6 { { -2.0f, 0.5f, 1.0f }, { 3.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f } };
    constexpr nnm::Rectangle3f r7 { { -2.0f, 0.5f, 0.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f } };

    test_section("distance_sqrd(const Rectangle3&)");
    {
        constexpr auto result1 = r1.distance_sqrd(r2);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        constexpr auto result2 = r1.distance_sqrd(r3);
        TEST_ASSERT(nnm::approx_equal(result2, 2.0f));
        constexpr auto result3 = r1.distance_sqrd(r4);
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = r1.distance_sqrd(r5);
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr auto result5 = r1.distance_sqrd(r6);
        TEST_ASSERT(nnm::approx_zero(result5));
        constexpr auto result6 = r_degen_line.distance_sqrd(r2);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        constexpr auto result7 = r_degen_line.distance_sqrd(r7);
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8 = r_degen_point.distance_sqrd(r2);
        TEST_ASSERT(nnm::approx_equal(result8, 7.25f));
        constexpr auto result9 = r_degen_point.distance_sqrd(r6);
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance(const Vector3&)");
    {
        const auto result1 = r1.distance(r1.vertex(0));
        TEST_ASSERT(nnm::approx_zero(result1));
        const auto result2 = r1.distance({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3 = r1.distance({ -2.0f, 0.0f, 2.0f });
        TEST_ASSERT(nnm::approx_equal(result3, 1.4142135624f));
        const auto result4 = r1.distance({ 0.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        const auto result5 = r_degen_line.distance({ -2.0f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_equal(result5, 1.4142135624f));
        const auto result6 = r_degen_line.distance({ -2.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_zero(result6));
        const auto result7 = r_degen_line.distance({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        const auto result8 = r_degen_point.distance({ 0.0f, 0.0f, 0.0f });
        TEST_ASSERT(nnm::approx_equal(result8, 2.8722813233f));
        const auto result9 = r_degen_point.distance({ -2.5f, 1.0f, 1.0f });
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance(const Line3&)");
    {
        const auto result1 = r1.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_zero(result1));
        const auto result2 = r1.distance(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        const auto result3
            = r1.distance(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = r1.distance(nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        const auto result5 = r1.distance(nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = r_degen_line.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_zero(result6));
        const auto result7 = r_degen_line.distance(nnm::Line3f::axis_y());
        TEST_ASSERT(nnm::approx_equal(result7, 1.0f));
        const auto result8
            = r_degen_line.distance(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result8, 1.4142135624f));
        const auto result9 = r_degen_point.distance(nnm::Line3f::axis_x());
        TEST_ASSERT(nnm::approx_equal(result9, 1.4142135624f));
        const auto result10 = r_degen_point.distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(nnm::approx_zero(result10));
    }

    test_section("distance(const Ray3&)");
    {
        const auto result1 = r1.distance(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2 = r1.distance(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3 = r1.distance(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = r1.distance(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result4, 1.4142135624f))
        const auto result5 = r1.distance(nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = r_degen_line.distance(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        const auto result7 = r_degen_line.distance(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(nnm::approx_zero(result7));
        const auto result8 = r_degen_line.distance(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_zero(result8));
        const auto result9 = r_degen_line.distance(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        const auto result10 = r_degen_line.distance(nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result10, 3.0f));
        const auto result11 = r_degen_point.distance(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT(nnm::approx_equal(result11, 2.6925824036f));
        const auto result12 = r_degen_point.distance(nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() });
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance(const Segment3&)");
    {
        const auto result1 = r1.distance(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2 = r1.distance(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3 = r1.distance(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } });
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = r1.distance(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } });
        TEST_ASSERT(nnm::approx_equal(result4, 1.4142135624f))
        const auto result5 = r1.distance(nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } });
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        const auto result6 = r_degen_line.distance(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        const auto result7 = r_degen_line.distance(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result7));
        const auto result8 = r_degen_line.distance(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_zero(result8));
        const auto result9 = r_degen_line.distance(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result9, 2.0f));
        const auto result10 = r_degen_line.distance(nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } });
        TEST_ASSERT(nnm::approx_equal(result10, 3.0f));
        const auto result11 = r_degen_point.distance(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } });
        TEST_ASSERT(nnm::approx_equal(result11, 2.6925824036f));
        const auto result12
            = r_degen_point.distance(nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } });
        TEST_ASSERT(nnm::approx_zero(result12));
    }

    test_section("distance(const Plane&)");
    {
        constexpr auto result1 = r1.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(result1));
        constexpr auto result2 = r1.distance(nnm::PlaneF::yz());
        TEST_ASSERT(nnm::approx_equal(result2, 1.0f));
        constexpr auto result3 = r1.distance(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT(nnm::approx_zero(result3));
        constexpr auto result4 = r_degen_line.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_zero(result4));
        constexpr auto result5 = r_degen_line.distance(nnm::PlaneF::yz());
        TEST_ASSERT(nnm::approx_equal(result5, 1.0f));
        constexpr auto result6 = r_degen_line.distance(nnm::PlaneF::xy_offset(2.0f));
        TEST_ASSERT(nnm::approx_equal(result6, 2.0f));
        constexpr auto result7 = r_degen_line.distance(nnm::PlaneF::yz_offset(-3.0f));
        TEST_ASSERT(nnm::approx_zero(result7));
        constexpr auto result8 = r_degen_point.distance(nnm::PlaneF::xy());
        TEST_ASSERT(nnm::approx_equal(result8, 1.0f));
        constexpr auto result9 = r_degen_point.distance(nnm::PlaneF::yz_offset(-2.5f));
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("distance(const Triangle3&)");
    {
        const auto result1
            = r1.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2
            = r1.distance(nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result2));
        const auto result3
            = r1.distance(nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4
            = r_degen_line.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result4, 1.0f));
        const auto result5 = r_degen_line.distance(
            nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result5));
        const auto result6
            = r_degen_point.distance(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(nnm::approx_equal(result6, 2.5980762114f));
        const auto result8 = r_degen_point.distance(
            nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f }));
        TEST_ASSERT(nnm::approx_zero(result8));
    }

    test_section("distance(const Rectangle3&)");
    {
        const auto result1 = r1.distance(r2);
        TEST_ASSERT(nnm::approx_equal(result1, 1.0f));
        const auto result2 = r1.distance(r3);
        TEST_ASSERT(nnm::approx_equal(result2, 1.4142135624f));
        const auto result3 = r1.distance(r4);
        TEST_ASSERT(nnm::approx_zero(result3));
        const auto result4 = r1.distance(r5);
        TEST_ASSERT(nnm::approx_zero(result4));
        const auto result5 = r1.distance(r6);
        TEST_ASSERT(nnm::approx_zero(result5));
        const auto result6 = r_degen_line.distance(r2);
        TEST_ASSERT(nnm::approx_equal(result6, 1.0f));
        const auto result7 = r_degen_line.distance(r7);
        TEST_ASSERT(nnm::approx_zero(result7));
        const auto result8 = r_degen_point.distance(r2);
        TEST_ASSERT(nnm::approx_equal(result8, 2.6925824036f));
        const auto result9 = r_degen_point.distance(r6);
        TEST_ASSERT(nnm::approx_zero(result9));
    }

    test_section("parallel(const Line3&)");
    {
        constexpr bool result1 = r1.parallel(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT(result1);
        constexpr bool result2 = r1.parallel(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3
            = r1.parallel(nnm::Line3f({ 0.0f, -1.0f, 10.0f }, { 0.0f, 0.70710678118655f, 0.70710678118655f }));
        TEST_ASSERT(result3);
        constexpr bool result4 = r_degen_line.parallel(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT(result4);
        constexpr bool result5 = r_degen_line.parallel(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT_FALSE(result5);
        constexpr bool result6 = r_degen_point.parallel(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT(result6);
        constexpr bool result7 = r_degen_point.parallel(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT(result7);
    }

    test_section("parallel(const Ray3&)");
    {
        constexpr bool result1 = r1.parallel(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(result1);
        constexpr bool result2 = r1.parallel(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(result2);
        constexpr bool result3
            = r1.parallel(nnm::Ray3f({ 0.0f, -1.0f, 10.0f }, { 0.0f, 0.70710678118655f, 0.70710678118655f }));
        TEST_ASSERT(result3);
        constexpr bool result4 = r_degen_line.parallel(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(result4);
        constexpr bool result5 = r_degen_line.parallel(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(result5);
        constexpr bool result6 = r_degen_point.parallel(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(result6);
        constexpr bool result7 = r_degen_point.parallel(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(result7);
    }

    test_section("perpendicular(const Line3&)");
    {
        constexpr bool result1 = r1.perpendicular(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2 = r1.perpendicular(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT_FALSE(result2)
        constexpr bool result3
            = r1.perpendicular(nnm::Line3f(nnm::Point3f::zero(), { 0.0f, 0.70710678118655f, -0.70710678118655f }));
        TEST_ASSERT(result3);
        constexpr bool result4 = r_degen_line.perpendicular(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT_FALSE(result4);
        constexpr bool result5 = r_degen_line.perpendicular(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT(result5);
        constexpr bool result6 = r_degen_point.perpendicular(nnm::Line3f::axis_x_offset(-1.0f, 1.0f));
        TEST_ASSERT(result6);
        constexpr bool result7 = r_degen_point.perpendicular(nnm::Line3f::axis_z_offset(-2.5f, 1.0f));
        TEST_ASSERT(result7);
    }

    test_section("perpendicular(const Ray3&)");
    {
        constexpr bool result1 = r1.perpendicular(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(result1);
        constexpr bool result2 = r1.perpendicular(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT_FALSE(result2)
        constexpr bool result3
            = r1.perpendicular(nnm::Ray3f(nnm::Point3f::zero(), { 0.0f, 0.70710678118655f, -0.70710678118655f }));
        TEST_ASSERT(result3);
        constexpr bool result4 = r_degen_line.perpendicular(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT_FALSE(result4);
        constexpr bool result5 = r_degen_line.perpendicular(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(result5);
        constexpr bool result6
            = r_degen_point.perpendicular(nnm::Ray3f({ 0.0f, -1.0f, 1.0f }, nnm::Vector3f::axis_x()));
        TEST_ASSERT(result6);
        constexpr bool result7
            = r_degen_point.perpendicular(nnm::Ray3f({ -2.5f, 1.0f, 0.0f }, nnm::Vector3f::axis_z()));
        TEST_ASSERT(result7);
    }

    test_section("intersects(const Line3&)");
    {
        constexpr auto result1 = r1.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT(result1);
        constexpr auto result2 = r1.intersects(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3
            = r1.intersects(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(result3);
        constexpr auto result4
            = r1.intersects(nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT_FALSE(result4);
        constexpr auto result5
            = r1.intersects(nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6 = r_degen_line.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT(result6);
        constexpr auto result7 = r_degen_line.intersects(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(result7);
        constexpr auto result8
            = r_degen_line.intersects(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT_FALSE(result8);
        constexpr auto result9 = r_degen_point.intersects(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result9);
        constexpr auto result10 = r_degen_point.intersects(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(result10);
    }

    test_section("intersection(const Line3&)");
    {
        constexpr auto result1 = r1.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr auto result2 = r1.intersection(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(result2.has_value());
        constexpr auto result3
            = r1.intersection(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(result3.has_value() && result3->approx_equal({ -2.0f, 1.0f, 1.0f }));
        constexpr auto result4
            = r1.intersection(nnm::Line3f { { 0.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT_FALSE(result4.has_value());
        constexpr auto result5
            = r1.intersection(nnm::Line3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result5.has_value());
        constexpr auto result6 = r_degen_line.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result6.has_value());
        constexpr auto result7 = r_degen_line.intersection(nnm::Line3f::axis_y());
        TEST_ASSERT_FALSE(result7.has_value());
        constexpr auto result8
            = r_degen_line.intersection(nnm::Line3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT_FALSE(result8.has_value());
        constexpr auto result9 = r_degen_point.intersection(nnm::Line3f::axis_x());
        TEST_ASSERT_FALSE(result9.has_value());
        constexpr auto result10 = r_degen_point.intersection(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
        TEST_ASSERT(result10.has_value() && result10->approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("intersects(const Ray3&)");
    {
        constexpr auto result1 = r1.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = r1.intersects(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(result2);
        constexpr auto result3
            = r1.intersects(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(result3);
        constexpr auto result4
            = r1.intersects(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result4)
        constexpr auto result5
            = r1.intersects(nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6 = r_degen_line.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result6);
        constexpr auto result7 = r_degen_line.intersects(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT(result7);
        constexpr auto result8
            = r_degen_line.intersects(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(result8);
        constexpr auto result9
            = r_degen_line.intersects(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result9);
        constexpr auto result10
            = r_degen_line.intersects(nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result10);
        constexpr auto result11
            = r_degen_point.intersects(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result11);
        constexpr auto result12
            = r_degen_point.intersects(nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() });
        TEST_ASSERT(result12);
    }

    test_section("intersection(const Ray3&)");
    {
        constexpr auto result1 = r1.intersection(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr auto result2 = r1.intersection(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result2.has_value());
        constexpr auto result3
            = r1.intersection(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, 0.7071067812f, -0.7071067812f } });
        TEST_ASSERT(result3.has_value() && result3->approx_equal({ -2.0f, 1.0f, 1.0f }));
        constexpr auto result4
            = r1.intersection(nnm::Ray3f { { -2.0f, 0.0f, 2.0f }, { 0.0f, -0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result4)
        constexpr auto result5
            = r1.intersection(nnm::Ray3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.7071067812f, 0.7071067812f } });
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6
            = r_degen_line.intersection(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result6);
        constexpr auto result7
            = r_degen_line.intersection(nnm::Ray3f { nnm::Point3f::zero(), -nnm::Vector3f::axis_x() });
        TEST_ASSERT_FALSE(result7.has_value());
        constexpr auto result8
            = r_degen_line.intersection(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT(result8.has_value() && result8->approx_equal({ -3.0f, 0.0f, 0.0f }));
        constexpr auto result9
            = r_degen_line.intersection(nnm::Ray3f { { -3.0f, -2.0f, 0.0f }, -nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result9);
        constexpr auto result10
            = r_degen_line.intersection(nnm::Ray3f { { -3.0f, -2.0f, 3.0f }, nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result10);
        constexpr auto result11
            = r_degen_point.intersection(nnm::Ray3f { nnm::Point3f::zero(), nnm::Vector3f::axis_y() });
        TEST_ASSERT_FALSE(result11);
        constexpr auto result12
            = r_degen_point.intersection(nnm::Ray3f { { -2.5f, 1.0f, 20.0f }, -nnm::Vector3f::axis_z() });
        TEST_ASSERT(result12.has_value() && result12->approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("intersects(const Segment3&)");
    {
        constexpr auto result1 = r1.intersects(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = r1.intersects(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(result2);
        constexpr auto result3 = r1.intersects(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } });
        TEST_ASSERT(result3);
        constexpr auto result4 = r1.intersects(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } });
        TEST_ASSERT_FALSE(result4)
        constexpr auto result5 = r1.intersects(nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } });
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6
            = r_degen_line.intersects(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result6);
        constexpr auto result7
            = r_degen_line.intersects(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT(result7);
        constexpr auto result8
            = r_degen_line.intersects(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } });
        TEST_ASSERT(result8);
        constexpr auto result9
            = r_degen_line.intersects(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } });
        TEST_ASSERT_FALSE(result9);
        constexpr auto result10
            = r_degen_line.intersects(nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } });
        TEST_ASSERT_FALSE(result10);
        constexpr auto result11
            = r_degen_point.intersects(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } });
        TEST_ASSERT_FALSE(result11);
        constexpr auto result12
            = r_degen_point.intersects(nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } });
        TEST_ASSERT(result12);
        constexpr auto result13 = r1.intersects(nnm::Segment3f { { -3.5f, 1.5f, 1.5f }, { -1.5f, 0.5f, 0.5f } });
        TEST_ASSERT(result13);
    }

    test_section("intersection(const Segment3&)");
    {
        constexpr auto result1 = r1.intersection(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result1.has_value());
        constexpr auto result2 = r1.intersection(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result2.has_value());
        constexpr auto result3 = r1.intersection(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, 10.0f, -8.0f } });
        TEST_ASSERT(result3.has_value() && result3->approx_equal({ -2.0f, 1.0f, 1.0f }));
        constexpr auto result4 = r1.intersection(nnm::Segment3f { { -2.0f, 0.0f, 2.0f }, { -2.0f, -10.0f, 12.0f } });
        TEST_ASSERT_FALSE(result4.has_value())
        constexpr auto result5 = r1.intersection(nnm::Segment3f { { 0.0f, 1.0f, 1.0f }, { 0.0f, 11.0f, 11.0f } });
        TEST_ASSERT_FALSE(result5.has_value());
        constexpr auto result6
            = r_degen_line.intersection(nnm::Segment3f { nnm::Point3f::zero(), { 10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result6.has_value());
        constexpr auto result7
            = r_degen_line.intersection(nnm::Segment3f { nnm::Point3f::zero(), { -10.0f, 0.0f, 0.0f } });
        TEST_ASSERT_FALSE(result7.has_value());
        constexpr auto result8
            = r_degen_line.intersection(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, 8.0f, 0.0f } });
        TEST_ASSERT(result8.has_value() && result8->approx_equal({ -3.0f, 0.0f, 0.0f }));
        constexpr auto result9
            = r_degen_line.intersection(nnm::Segment3f { { -3.0f, -2.0f, 0.0f }, { -3.0f, -12.0f, 0.0f } });
        TEST_ASSERT_FALSE(result9.has_value());
        constexpr auto result10
            = r_degen_line.intersection(nnm::Segment3f { { -3.0f, -2.0f, 3.0f }, { -3.0f, 8.0f, 3.0f } });
        TEST_ASSERT_FALSE(result10.has_value());
        constexpr auto result11
            = r_degen_point.intersection(nnm::Segment3f { nnm::Point3f::zero(), { 0.0f, 10.0f, 0.0f } });
        TEST_ASSERT_FALSE(result11.has_value());
        constexpr auto result12
            = r_degen_point.intersection(nnm::Segment3f { { -2.5f, 1.0f, 20.0f }, { -2.5f, 1.0f, -20.0f } });
        TEST_ASSERT(result12.has_value() && result12->approx_equal({ -2.5f, 1.0f, 1.0f }));
    }

    test_section("intersects(const Plane&)");
    {
        constexpr auto result1 = r1.intersects(nnm::PlaneF::xy());
        TEST_ASSERT(result1);
        constexpr auto result2 = r1.intersects(nnm::PlaneF::yz());
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3 = r1.intersects(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT(result3);
        constexpr auto result4 = r_degen_line.intersects(nnm::PlaneF::xy());
        TEST_ASSERT(result4);
        constexpr auto result5 = r_degen_line.intersects(nnm::PlaneF::yz());
        TEST_ASSERT_FALSE(result5);
        constexpr auto result6 = r_degen_line.intersects(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT_FALSE(result6);
        constexpr auto result7 = r_degen_line.intersects(nnm::PlaneF::yz_offset(-3.0f));
        TEST_ASSERT(result7);
        constexpr auto result8 = r_degen_point.intersects(nnm::PlaneF::xy());
        TEST_ASSERT_FALSE(result8);
        constexpr auto result9 = r_degen_point.intersects(nnm::PlaneF::yz_offset(-2.5f));
        TEST_ASSERT(result9);
    }

    test_section("edge_intersections(const Plane&)");
    {
        constexpr auto result1 = r1.edge_intersections(nnm::PlaneF::xy());
        TEST_ASSERT(result1.empty());
        constexpr auto result2 = r1.edge_intersections(nnm::PlaneF::yz());
        TEST_ASSERT(result2.empty());
        constexpr auto result3 = r1.edge_intersections(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT(result3.approx_equal({ { -4.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f } }));
        constexpr auto result4 = r_degen_line.edge_intersections(nnm::PlaneF::xy());
        TEST_ASSERT(result4.empty());
        constexpr auto result5 = r_degen_line.edge_intersections(nnm::PlaneF::yz());
        TEST_ASSERT(result5.empty());
        constexpr auto result6 = r_degen_line.edge_intersections(nnm::PlaneF::xy_offset(1.0f));
        TEST_ASSERT(result6.empty());
        constexpr auto result7 = r_degen_line.edge_intersections(nnm::PlaneF::yz_offset(-3.0f));
        TEST_ASSERT(result7.approx_equal({ { -3.0f, 0.0f, 0.0f } }));
        constexpr auto result8 = r_degen_point.edge_intersections(nnm::PlaneF::xy());
        TEST_ASSERT(result8.empty());
        constexpr auto result9 = r_degen_point.edge_intersections(nnm::PlaneF::yz_offset(-2.5f));
        TEST_ASSERT(result9.approx_equal({ { -2.5f, 1.0f, 1.0f } }));
    }

    test_section("intersects(const Triangle3&)");
    {
        constexpr auto result1
            = r1.intersects(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2
            = r1.intersects(nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result2);
        constexpr auto result3
            = r1.intersects(nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result3);
        constexpr auto result4 = r_degen_line.intersects(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result4);
        constexpr auto result5 = r_degen_line.intersects(
            nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result5);
        constexpr auto result6 = r_degen_point.intersects(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT_FALSE(result6);
        constexpr auto result8 = r_degen_point.intersects(
            nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f }));
        TEST_ASSERT(result8);
    }

    test_section("edge_intersections");
    {
        const auto result1
            = r1.edge_intersections(nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(result1.empty());
        const auto result2 = r1.edge_intersections(
            nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result2.approx_equal({ { -3.0f, 1.0f, 1.0f }, { -3.0f, 0.0f, 0.0f } }));
        const auto result3 = r1.edge_intersections(
            nnm::Triangle3f({ -3.0f, -2.0f, 0.5f }, { -3.0f, 1.0f, 0.5f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result3.approx_equal({ { -3.0f, 1.0f, 1.0f }, { -3.0f, 0.5f, 0.5f } }));
        const auto result4 = r_degen_line.edge_intersections(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(result4.empty());
        const auto result5 = r_degen_line.edge_intersections(
            nnm::Triangle3f({ -3.0f, -2.0f, -1.0f }, { -3.0f, 1.0f, -1.0f }, { -3.0f, 1.0f, 3.0f }));
        TEST_ASSERT(result5.approx_equal({ { -3.0f, 0.0f, 0.0f } }));
        const auto result6 = r_degen_point.edge_intersections(
            nnm::Triangle3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
        TEST_ASSERT(result6.empty());
        const auto result8 = r_degen_point.edge_intersections(
            nnm::Triangle3f({ -2.5f, 0.0f, 0.0f }, { -2.5f, 2.0f, 0.0f }, { -2.5f, 2.0f, 3.0f }));
        TEST_ASSERT(result8.approx_equal({ { -2.5f, 1.0f, 1.0f } }));
    }

    test_section("intersects(const Rectangle3&)");
    {
        constexpr auto result1 = r1.intersects(r2);
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = r1.intersects(r3);
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3 = r1.intersects(r4);
        TEST_ASSERT(result3);
        constexpr auto result4 = r1.intersects(r5);
        TEST_ASSERT(result4);
        constexpr auto result5 = r1.intersects(r6);
        TEST_ASSERT(result5);
        constexpr auto result6 = r_degen_line.intersects(r2);
        TEST_ASSERT_FALSE(result6);
        constexpr auto result7 = r_degen_line.intersects(r7);
        TEST_ASSERT(result7);
        constexpr auto result8 = r_degen_point.intersects(r2);
        TEST_ASSERT_FALSE(result8);
        constexpr auto result9 = r_degen_point.intersects(r6);
        TEST_ASSERT(result9);
    }

    test_section("edge_intersections");
    {
        const auto result1 = r1.edge_intersections(r2);
        TEST_ASSERT(result1.empty());
        const auto result2 = r1.edge_intersections(r3);
        TEST_ASSERT(result2.empty());
        const auto result3 = r1.edge_intersections(r4);
        TEST_ASSERT(result3.approx_equal({ { -3.0f, 1.0f, 1.0f }, { -2.0f, 1.0f, 1.0f } }));
        const auto result4 = r1.edge_intersections(r5);
        TEST_ASSERT(result4.approx_equal({ { -2.5f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f } }));
        const auto result5 = r1.edge_intersections(r6);
        TEST_ASSERT(result5.approx_equal({ { -4.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f } }));
        const auto result6 = r_degen_line.edge_intersections(r2);
        TEST_ASSERT(result6.empty());
        const auto result7 = r_degen_line.edge_intersections(r7);
        TEST_ASSERT(result7.approx_equal({ { -3.5f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }));
        const auto result8 = r_degen_point.edge_intersections(r2);
        TEST_ASSERT(result8.empty());
        const auto result9 = r_degen_point.edge_intersections(r6);
        TEST_ASSERT(result9.approx_equal({ { -2.5f, 1.0f, 1.0f } }));
    }

    test_section("translate");
    {
        constexpr nnm::Vector3f offset { 2.0f, -10.0f, 0.5f };
        constexpr auto r1_t = r1.translate(offset);
        TEST_ASSERT(r1_t.approx_equal({ r1.center.translate(offset), r1.half_span_u, r1.half_span_v }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3f origin { 0.5f, 1.5f, -2.0f };
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1_r = r1.rotate_axis_angle_at(origin, axis, angle);
        TEST_ASSERT(r1_r.approx_equal(
            { r1.center.rotate_axis_angle_at(origin, axis, angle),
              r1.half_span_u.rotate_axis_angle(axis, angle),
              r1.half_span_v.rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_axis_angle");
    {
        constexpr auto axis = nnm::Vector3f::axis_y();
        constexpr float angle = 2.0f * nnm::pi<float>() / 3.0f;
        const auto r1_r = r1.rotate_axis_angle(axis, angle);
        TEST_ASSERT(r1_r.approx_equal(
            { r1.center.rotate_axis_angle(axis, angle),
              r1.half_span_u.rotate_axis_angle(axis, angle),
              r1.half_span_v.rotate_axis_angle(axis, angle) }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3f origin { 0.5f, 1.5f, -2.0f };
        constexpr nnm::QuaternionF quat { 0.0f, -0.8660254f, 0.0f, 0.5f };
        constexpr auto r1_r = r1.rotate_quaternion_at(origin, quat);
        TEST_ASSERT(r1_r.approx_equal(
            { r1.center.rotate_quaternion_at(origin, quat),
              r1.half_span_u.rotate_quaternion(quat),
              r1.half_span_v.rotate_quaternion(quat) }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF quat { 0.0f, -0.8660254f, 0.0f, 0.5f };
        constexpr auto r1_r = r1.rotate_quaternion(quat);
        TEST_ASSERT(r1_r.approx_equal(
            { r1.center.rotate_quaternion(quat),
              r1.half_span_u.rotate_quaternion(quat),
              r1.half_span_v.rotate_quaternion(quat) }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3f origin { 0.5f, 1.5f, -2.0f };
        constexpr nnm::Vector3f factor { 3.0f, 0.5f, 2.0f };
        constexpr auto r1_s = r1.scale_at(origin, factor);
        TEST_ASSERT(r1_s.approx_equal(
            { r1.center.scale_at(origin, factor), r1.half_span_u.scale(factor), r1.half_span_v.scale(factor) }));
    }

    test_section("scale");
    {
        constexpr nnm::Vector3f factor { 3.0f, 0.5f, 2.0f };
        constexpr auto r1_s = r1.scale(factor);
        TEST_ASSERT(
            r1_s.approx_equal({ r1.center.scale(factor), r1.half_span_u.scale(factor), r1.half_span_v.scale(factor) }));
    }

    test_section("coincident");
    {
        const auto result1 = r1.coincident(r1);
        TEST_ASSERT(result1);
        const auto result2 = r1.coincident(r2);
        TEST_ASSERT_FALSE(result2);
        const auto result3 = r1.coincident({ { -2.5f, 1.0f, 1.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 1.0f } });
        TEST_ASSERT(result3);
        const auto result4 = r1.coincident({ { -2.5f, 1.0f, 1.0f }, { 1.5f, 0.0f, 0.0f }, { 0.0f, -1.0f, -1.0f } });
        TEST_ASSERT(result4);
    }

    test_section("approx_equal");
    {
        constexpr auto result1 = r1.approx_equal(r1);
        TEST_ASSERT(result1);
        constexpr auto result2 = r1.approx_equal(r2);
        TEST_ASSERT_FALSE(result2);
        constexpr auto result3 = r2.approx_equal(r2);
        TEST_ASSERT(result3);
    }

    test_section("operator==");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result1 = r1 == r1;
        TEST_ASSERT(result1);
        constexpr auto result2 = r1 == r2;
        TEST_ASSERT_FALSE(result2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result3 = r2 == r2;
        TEST_ASSERT(result3);
    }

    test_section("operator!=");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result1 = r1 != r1;
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = r1 != r2;
        TEST_ASSERT(result2);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result3 = r2 != r2;
        TEST_ASSERT_FALSE(result3);
    }

    test_section("operator<");
    {
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result1 = r1 < r1;
        TEST_ASSERT_FALSE(result1);
        constexpr auto result2 = r1 < r2;
        TEST_ASSERT(result2);
        constexpr auto result3 = r2 < r1;
        TEST_ASSERT_FALSE(result3);
        // ReSharper disable once CppIdenticalOperandsInBinaryExpression
        constexpr auto result4 = r2 < r2;
        TEST_ASSERT_FALSE(result4);
    }
}

