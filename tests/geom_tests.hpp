#pragma once

#include <nnm/geom.hpp>

#include <algorithm>
#include <functional>

#include "test.hpp"

// ReSharper disable CppUseStructuredBinding
// ReSharper disable CppDFATimeOver

inline void geom_tests()
{
    test_case("Line2");
    {
        test_section("Line2()");
        {
            constexpr nnm::Line2f line {};
            ASSERT(line.origin == nnm::Vector2f::zero());
            ASSERT(line.direction == nnm::Vector2f(1.0f, 0.0f));
        }

        test_section("Line2(const Vector2&, const Vector2&)");
        {
            constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { 1.0f, -3.0f } };
            ASSERT(line1.origin == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(line1.direction.approx_equal({ 1.0f, -3.0f }));
        }

        test_section("from_points");
        {
            constexpr nnm::Vector2f p1 { 1.0f, -2.0f };
            constexpr nnm::Vector2f p2 { -4.0f, 10.0f };
            const auto line = nnm::Line2f::from_points(p1, p2);
            ASSERT(line.approx_contains(p1));
            ASSERT(line.approx_contains(p2));
        }

        test_section("from_segment");
        {
            constexpr nnm::Segment2f s { { -1.0f, 2.0f }, { -4.0f, 10.0f } };
            const auto line = nnm::Line2f::from_segment(s);
            ASSERT(line.origin == nnm::Vector2f(-1.0f, 2.0f));
            ASSERT(line.direction.approx_equal({ -0.3511234416f, 0.9363291776f }));
        }

        test_section("from_ray");
        {
            constexpr nnm::Ray2f r { { -1.0f, 2.0f }, { -0.3713906764f, 0.9284766909f } };
            constexpr auto line = nnm::Line2f::from_ray(r);
            ASSERT(line.origin == nnm::Vector2f(-1.0f, 2.0f));
            ASSERT(line.direction.approx_equal({ -0.3713906764f, 0.9284766909f }))
        }

        test_section("from_tangent_at");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            const auto l1 = nnm::Line2f::from_tangent_at(c1, 0.0f);
            ASSERT(l1.origin.approx_equal({ 7.0f, -3.0f }));
            ASSERT(nnm::approx_zero(l1.direction.cross({ 0.0f, 1.0f })));
            ASSERT(l1.approx_tangent(c1));
            const auto l2 = nnm::Line2f::from_tangent_at(c1, nnm::pi() / 3.0f);
            ASSERT(l2.origin.approx_equal({ 4.5f, 1.330127f }));
            ASSERT(l2.direction.approx_parallel(
                nnm::Line2f::from_point_slope({ 0.0f, 3.9282032f }, -0.5773503f).direction));
            ASSERT(l2.approx_tangent(c1));
        }

        test_section("axis_x");
        {
            constexpr auto line = nnm::Line2f::axis_x();
            ASSERT(line.origin == nnm::Vector2f::zero());
            ASSERT(line.direction == nnm::Vector2f::axis_x());
        }

        test_section("axis_y");
        {
            constexpr auto line = nnm::Line2f::axis_y();
            ASSERT(line.origin == nnm::Vector2f::zero());
            ASSERT(line.direction == nnm::Vector2f::axis_y());
        }

        test_section("axis_x_offset");
        {
            constexpr auto line = nnm::Line2f::axis_x_offset(3.0f);
            ASSERT(line.origin.approx_equal({ 0.0f, 3.0f }));
            ASSERT(line.direction.approx_equal(nnm::Vector2f::axis_x()));
        }

        test_section("axis_y_offset");
        {
            constexpr auto line = nnm::Line2f::axis_y_offset(-2.0f);
            ASSERT(line.origin.approx_equal({ -2.0f, 0.0f }));
            ASSERT(line.direction.approx_equal(nnm::Vector2f::axis_y()));
        }

        test_section("from_point_slope");
        {
            const auto line = nnm::Line2f::from_point_slope({ 1.0f, -2.0f }, -1.5f);
            ASSERT(line.origin == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(line.direction.approx_equal({ 0.5547f, -0.83205f }));
        }

        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };

        test_section("parallel_containing");
        {
            constexpr nnm::Line2f line2 = line1.parallel_containing({ -6.0f, -5.0f });
            ASSERT(line2.approx_contains({ -6.0f, -5.0f }));
            ASSERT(line2.approx_parallel({ line1 }));
        }

        test_section("arbitrary_perpendicular_containing");
        {
            constexpr nnm::Line2f line2 = line1.arbitrary_perpendicular_containing({ -6.0f, -5.0f });
            ASSERT(line2.approx_contains({ -6.0f, -5.0f }));
            ASSERT(line2.approx_perpendicular({ line1 }));
        }

        test_section("normalize");
        {
            const auto line2 = nnm::Line2f { { 1.0f, -2.0f }, { -10.0f, 8.0f } }.normalize();
            ASSERT(line2.origin == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(line2.direction.approx_equal(nnm::Vector2f { -10.0f, 8.0f }.normalize()));
        }

        test_section("approx_contains");
        {
            constexpr auto result = line1.approx_contains({ 1.0f, -2.0f });
            ASSERT(result);
            ASSERT(line1.approx_contains({ 0.999999f, -2.0000001f }));
            ASSERT_FALSE(line1.approx_contains({ 20.0f, 2.0f }));
        }

        constexpr nnm::Line2f line2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };

        test_section("distance");
        {
            constexpr auto result = line2.distance({ 0.0f, 0.0f });
            ASSERT(nnm::approx_equal(result, 2.1213203436f));
            ASSERT(nnm::approx_equal(line2.distance({ -3.0f, 5.0f }), 7.7781745931f));
            ASSERT(nnm::approx_equal(line2.distance({ 5.0f, 0.0f }), 1.4142135624f));
        }

        test_section("signed_distance");
        {
            constexpr auto result = line2.signed_distance({ 0.0f, 0.0f });
            ASSERT(nnm::approx_equal(result, 2.1213203436f));
            ASSERT(nnm::approx_equal(line2.signed_distance({ -3.0f, 5.0f }), 7.7781745931f));
            ASSERT(nnm::approx_equal(line2.signed_distance({ 5.0f, 0.0f }), -1.4142135624f));
        }

        test_section("distance(const Line2&)");
        {
            constexpr auto result = line1.distance(line2);
            ASSERT(nnm::approx_zero(result));
            ASSERT(nnm::approx_zero(line2.distance(line1)));
            constexpr nnm::Line2f line3 { { 1.0f, 0.0f }, { -0.70710678f, -0.70710678f } };
            ASSERT(nnm::approx_zero(line1.distance(line2)));
            ASSERT(nnm::approx_equal(line2.distance(line3), 1.4142135624f));
            ASSERT(nnm::approx_equal(line3.distance(line2), 1.4142135624f));
        }

        test_section("distance(const Ray2&)");
        {
            constexpr nnm::Ray2f ray2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT(nnm::approx_zero(nnm::Line2f::axis_x_offset(1.0f).distance(ray2)));
            ASSERT(nnm::approx_equal(
                nnm::Line2f::from_points({ 2.0f, 1.0f }, { 1.0f, 0.0f }).distance(ray2), 1.4142135624f));
            ASSERT(nnm::approx_equal(
                nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, -1.0f }).distance(ray2), 1.4142135624f));
        }

        test_section("distance(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr auto result = nnm::Line2f::axis_x_offset(2.0f).distance(s1);
            ASSERT(nnm::approx_zero(result));
            ASSERT(nnm::approx_equal(
                nnm::Line2f::from_points({ 0.0f, 3.0f }, { 1.0f, 2.0f }).distance(s1), 1.4142135624f));
            ASSERT(nnm::approx_equal(nnm::Line2f::axis_y_offset(2.0f).distance(s1), 1.0f));
            ASSERT(nnm::approx_equal(
                nnm::Line2f::from_points({ 2.0f, 0.0f }, { 0.0f, 3.0f }).distance(s1), 1.9414506868f));
        }

        test_section("approx_parallel(const Line2&)");
        {
            constexpr auto result = line1.approx_parallel(line2);
            ASSERT_FALSE(result);
            ASSERT(line2.approx_parallel(nnm::Line2f { { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
            ASSERT(line2.approx_parallel(nnm::Line2f { { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
        }

        test_section("approx_parallel(const Ray2&)");
        {
            constexpr auto result
                = line1.approx_parallel(nnm::Ray2f { { 100.0f, -100.0f }, { -0.384615391f, 0.923076928f } });
            ASSERT(result);
            ASSERT(line1.approx_parallel(nnm::Ray2f { { 100.0f, -100.0f }, { 0.384615391f, -0.923076928f } }))
            ASSERT_FALSE(line1.approx_parallel(nnm::Ray2f {
                { 1.0f, -2.0f },
                {
                    0.923076928f,
                    0.384615391f,
                } }));
        }

        test_section("approx_parallel(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Line2f l1 { { 100.0f, -100.0f }, { -0.5547001962f, 0.8320502943f } };
            constexpr auto result = l1.approx_parallel(s1);
            ASSERT(result);
            constexpr nnm::Line2f l2 { { -100.0f, 100.0f }, { 0.5547001962f, -0.8320502943f } };
            ASSERT(l2.approx_parallel(s1));
            constexpr nnm::Line2f l3 { { 1.0f, -2.0f }, { 0.8320502943f, 0.5547001962f } };
            ASSERT_FALSE(l3.approx_parallel(s1));
        }

        test_section("approx_perpendicular(const Line2&)");
        {
            constexpr auto result = line1.approx_perpendicular(line2);
            ASSERT_FALSE(result);
            ASSERT(line2.approx_perpendicular(nnm::Line2f { { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
            ASSERT(line2.approx_perpendicular(nnm::Line2f { { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
        }

        test_section("approx_perpendicular(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr auto result
                = nnm::Line2f { { -100.0f, 100.0f }, { -0.923076928f, -0.384615391f } }.approx_perpendicular(ray1);
            ASSERT(result);
            ASSERT(nnm::Line2f({ -100.0f, 100.0f }, { 0.923076928f, 0.384615391f }).approx_perpendicular(ray1));
            ASSERT_FALSE(nnm::Line2f({ 1000.0f, 0.0f }, { -0.384615391f, 0.923076928f }).approx_perpendicular(ray1));
        }

        test_section("approx_perpendicular(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Line2f l1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
            constexpr auto result = l1.approx_perpendicular(s1);
            ASSERT(result);
            constexpr nnm::Line2f l2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(l2.approx_perpendicular(s1));
        }

        test_section("unchecked_intersection");
        {
            constexpr auto result = line1.unchecked_intersection(line2);
            ASSERT(result.approx_equal({ 1.0f, -2.0f }));
        }

        test_section("intersection(const Line2&)");
        {
            constexpr auto result = line1.intersection(line2);
            ASSERT(result.has_value());
            ASSERT(line1.intersection(line2).value().approx_equal({ 1.0f, -2.0f }));
            constexpr nnm::Line2f line3 { { 100.0f, -5.0f }, { -0.70710678f, -0.70710678f } };
            ASSERT_FALSE(line2.intersection(line3).has_value());
        }

        test_section("intersects(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = line3.intersects(ray1);
            ASSERT(result);
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(line4.intersects(ray1));
        }

        test_section("intersection(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = line3.intersection(ray1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(line4.intersection(ray1).has_value());
        }

        test_section("intersects(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Line2f line3 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
            constexpr auto result = line3.intersects(s1);
            ASSERT(result);
            constexpr nnm::Line2f line4 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            ASSERT_FALSE(line4.intersects(s1));
        }

        test_section("intersection(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Line2f line3 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
            constexpr auto result = line3.intersection(s1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
            constexpr nnm::Line2f line4 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            ASSERT_FALSE(line4.intersection(s1).has_value());
        }

        test_section("intersects(const Circle2&");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Line2f l1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            constexpr auto result = l1.intersects(c1);
            ASSERT(result);
            constexpr nnm::Line2f l2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(l2.intersects(c1));
            ASSERT(nnm::Line2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersects(c1));
            ASSERT_FALSE(nnm::Line2f({ 0.0f, 100.0f }, { 1.0f, 0.0f }).intersects(c1));
        }

        test_section("intersections(const Circle2&)");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Line2f l1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result1 = l1.intersections(c1);
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result1)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Line2f l2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(l2.intersections(c1).has_value());
            const auto result2 = nnm::Line2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersections(c1);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 0.0f, -7.58257294f })
                && (*result2)[1].approx_equal({ 0.0f, 1.58257294f }));
        }

        test_section("intersects(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            constexpr auto result = nnm::Line2f::axis_x().intersects(tri1);
            ASSERT(result);
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            ASSERT(nnm::Line2f::axis_x().intersects(tri2));
            ASSERT(nnm::Line2f::axis_y().intersects(tri1));
            ASSERT(nnm::Line2f::axis_y().intersects(tri2));
            ASSERT_FALSE(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersects(tri1));
            ASSERT_FALSE(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersects(tri2));
            ASSERT(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersects(tri1));
            ASSERT(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersects(tri2));
        }

        test_section("intersections(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            const auto result1 = nnm::Line2f::axis_x().intersections(tri1);
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -3.666667f, 0.0f })
                && (*result1)[1].approx_equal({ -1.0f, 0.0f }));
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            const auto result2 = nnm::Line2f::axis_x().intersections(tri2);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -3.666667f, 0.0f })
                && (*result2)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result3 = nnm::Line2f::axis_y().intersections(tri1);
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ 0.0f, 2.0f })
                && (*result3)[1].approx_equal({ 0.0f, 3.6f }));
            const auto result4 = nnm::Line2f::axis_y().intersections(tri2);
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ 0.0f, 2.0f })
                && (*result4)[1].approx_equal({ 0.0f, 3.6f }));
            const auto result5 = nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersections(tri1);
            ASSERT_FALSE(result5.has_value());
            const auto result6 = nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }).intersections(tri2);
            ASSERT_FALSE(result6.has_value());
            const auto result7 = nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersections(tri1);
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ -3.0f, 2.4f })
                && (*result7)[1].approx_equal({ -0.538461548f, 0.923076923f }));
            const auto result8 = nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }).intersections(tri2);
            ASSERT(
                result8.has_value() && (*result8)[0].approx_equal({ -3.0f, 2.4f })
                && (*result8)[1].approx_equal({ -0.538461548f, 0.923076923f }));
        }

        test_section("approx_tangent");
        {
            constexpr nnm::Circle2f circle { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Line2f line3 { { -2.0f, 2.0f }, { -1.0f, 0.0f } };
            constexpr auto result = line3.approx_tangent(circle);
            ASSERT(result);
            ASSERT_FALSE(line1.approx_tangent(circle));
        }

        test_section("project_point_scalar");
        {
            constexpr auto result = line1.project_point_scalar({ 5.0f, 3.0f });
            ASSERT(nnm::approx_equal(result, 3.076923076f));
        }

        test_section("project_point");
        {
            constexpr auto result = line1.project_point({ 5.0f, 3.0f });
            ASSERT(result.approx_equal({ -0.18343f, 0.84024f }));
        }

        test_section("unchecked_slope");
        {
            constexpr auto result = line1.unchecked_slope();
            ASSERT(nnm::approx_equal(result, -2.4f));
        }

        test_section("slope");
        {
            constexpr auto result = line1.slope();
            ASSERT(result.has_value() && nnm::approx_equal(result.value(), -2.4f));
            ASSERT_FALSE(nnm::Line2f::axis_y_offset(-3.0f).slope().has_value());
        }

        test_section("approx_coincident");
        {
            constexpr auto result = line1.approx_coincident(line2);
            ASSERT_FALSE(result);
            constexpr nnm::Line2f line3 { { 0.0f, -3.0f }, { -0.70710678f, -0.70710678f } };
            ASSERT(line2.approx_coincident(line3));
        }

        constexpr nnm::Line2f line3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

        test_section("translate");
        {
            const nnm::Line2f result = line3.translate({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
            ASSERT(result.direction.approx_equal(line3.direction));
        }

        test_section("scale_at");
        {
            const auto result = line3.scale_at({ -2.0f, 3.0f }, { 3.0f, -0.5f });
            ASSERT(result.origin.approx_equal({ 13.0f, 5.0f }));
            ASSERT(result.direction.approx_equal({ 0.986394f, -0.164399f }));
        }

        test_section("scale");
        {
            const nnm::Line2f result = line3.scale({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("shear_x_at");
        {
            const auto result = line3.shear_x_at({ -2.0f, 3.0f }, nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 0.09383f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.865334f, 0.501195f }))
        }

        test_section("shear_x");
        {
            const nnm::Line2f result = line3.shear_x(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 1.26794919f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_y_at");
        {
            const auto result = line3.shear_y_at({ -2.0f, 3.0f }, nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, 2.632713f }));
            ASSERT(result.direction.approx_equal({ 0.501195f, 0.865334f }));
        }

        test_section("shear_y");
        {
            const nnm::Line2f result = line3.shear_y(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -3.17963f }));
            ASSERT(result.direction.approx_equal({ 0.964585f, 0.263773f }));
        }

        test_section("operator<");
        {
            ASSERT(line1 < line2);
            ASSERT_FALSE(line2 < line1);
        }

        test_section("operator==");
        {
            ASSERT_FALSE(line1 == line2);
            ASSERT(line1 == line1);
        }

        test_section("operator!=");
        {
            ASSERT(line1 != line2);
            ASSERT_FALSE(line1 != line1);
        }
    }

    test_case("Ray2");
    {
        test_section("Line2()");
        {
            constexpr nnm::Ray2f ray {};
            ASSERT(ray.origin == nnm::Vector2f::zero());
            ASSERT(ray.direction == nnm::Vector2f(1.0f, 0.0f));
        }

        test_section("Ray2(const Vector2&, const Vector2&)");
        {
            constexpr nnm::Ray2f ray { { 1.0f, -2.0f }, { 1.0f, -3.0f } };
            ASSERT(ray.origin == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(ray.direction.approx_equal({ 1.0f, -3.0f }));
        }

        test_section("from_point_to_point");
        {
            constexpr nnm::Vector2f p1 { 1.0f, -2.0f };
            constexpr nnm::Vector2f p2 { -4.0f, 10.0f };
            const auto ray = nnm::Ray2f::from_point_to_point(p1, p2);
            ASSERT(ray.approx_contains(p1));
            ASSERT(ray.approx_contains(p2));
        }

        constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };

        test_section("normalize");
        {
            const auto ray2 = nnm::Ray2f { { 1.0f, -2.0f }, { -10.0f, 8.0f } }.normalize();
            ASSERT(ray2.origin == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(ray2.direction.approx_equal(nnm::Vector2f { -10.0f, 8.0f }.normalize()));
        }

        test_section("approx_contains");
        {
            constexpr auto result = ray1.approx_contains({ 1.0f, -2.0f });
            ASSERT(result);
            ASSERT(ray1.approx_contains({ 0.999999f, -2.0000001f }));
            ASSERT_FALSE(ray1.approx_contains({ 20.0f, 2.0f }));
            ASSERT_FALSE(ray1.approx_contains({ 2.25f, -5.0f }));
        }

        constexpr nnm::Ray2f ray2 { { 3.0f, 0.0f }, { 0.70710678f, 0.70710678f } };

        test_section("signed_distance(const Vector2&)");
        {
            ASSERT(nnm::approx_equal(ray2.signed_distance({ 0.0f, 0.0f }), 3.0f));
            ASSERT(nnm::approx_equal(ray2.signed_distance({ -3.0f, 5.0f }), 7.8102496759f));
            ASSERT(nnm::approx_equal(ray2.signed_distance({ 5.0f, 0.0f }), -1.4142135624f));
        }

        test_section("distance(const Vector2&)");
        {
            ASSERT(nnm::approx_equal(ray2.distance({ 0.0f, 0.0f }), 3.0f));
            ASSERT(nnm::approx_equal(ray2.distance({ -3.0f, 5.0f }), 7.8102496759f));
            ASSERT(nnm::approx_equal(ray2.distance({ 5.0f, 0.0f }), 1.4142135624f));
        }

        test_section("distance(const Line2&)");
        {
            ASSERT(nnm::approx_zero(ray2.distance(nnm::Line2f::axis_x_offset(1.0f))));
            ASSERT(nnm::approx_equal(
                ray2.distance(nnm::Line2f::from_points({ 2.0f, 1.0f }, { 1.0f, 0.0f })), 1.4142135624f));
            ASSERT(nnm::approx_equal(
                ray2.distance(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, -1.0f })), 1.4142135624f));
        }

        test_section("distance(const Ray2&)");
        {
            ASSERT(nnm::approx_zero(ray2.distance(nnm::Ray2f { { 0.0f, 1.0f }, { 1.0f, 0.0f } })));
            ASSERT(nnm::approx_equal(
                ray2.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 2.0f, 1.0f })), 1.4142135624f));
            ASSERT(nnm::approx_equal(
                ray2.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, -1.0f })), 2.0f));
            ASSERT(nnm::approx_equal(
                ray2.distance(nnm::Ray2f::from_point_to_point({ 3.0f, 2.0f }, { 1.0f, 2.0f })), 1.4142135624f));
        }

        test_section("distance(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            ASSERT(nnm::approx_zero(nnm::Ray2f { { 1.0f, 2.0f }, { -1.0f, 0.0f } }.distance(s1)));
            ASSERT(nnm::approx_equal(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, -1.0f } }.distance(s1), 1.0f));
            ASSERT(nnm::approx_equal(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, 1.0f } }.distance(s1), 3.60555127f));
            ASSERT(nnm::approx_equal(nnm::Ray2f { { 1.0f, 5.0f }, { -1.0f, 0.0f } }.distance(s1), 1.0f))
            ASSERT(nnm::approx_equal(nnm::Ray2f { { 1.0f, 5.0f }, { 1.0f, 0.0f } }.distance(s1), 3.88290137f));
            ASSERT(nnm::approx_equal(
                nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { 3.0f, -1.0f }).distance(s1), 2.21880078f))
            ASSERT(nnm::approx_equal(
                nnm::Ray2f::from_point_to_point({ 3.0f, -2.0f }, { 4.0f, -3.0f }).distance(s1), 2.0f));
            ASSERT(nnm::approx_equal(
                nnm::Ray2f::from_point_to_point({ -4.0f, 5.0f }, { -5.0f, 4.0f }).distance(s1), 1.4142135624f));
        }

        test_section("approx_parallel(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Ray2f r1 { { 100.0f, -100.0f }, { -0.384615391f, 0.923076928f } };
            constexpr auto result = r1.approx_parallel(line1);
            ASSERT(result);
            constexpr nnm::Ray2f r2 { { 100.0f, -100.0f }, { 0.384615391f, -0.923076928f } };
            ASSERT(r2.approx_parallel(line1))
            constexpr nnm::Ray2f r3 { { 1.0f, -2.0f },
                                      {
                                          0.923076928f,
                                          0.384615391f,
                                      } };
            ASSERT_FALSE(r3.approx_parallel(line1));
        }

        test_section("approx_parallel(const Ray2&)");
        {
            constexpr auto result = ray1.approx_parallel(ray2);
            ASSERT_FALSE(result);
            ASSERT(ray2.approx_parallel(nnm::Ray2f { { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
            ASSERT(ray2.approx_parallel(nnm::Ray2f { { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
        }

        test_section("approx_parallel(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Ray2f r1 { { 0.0f, 4.0f }, { 0.554699f, -0.832051f } };
            constexpr auto result = r1.approx_parallel(s1);
            ASSERT(result);
            constexpr nnm::Ray2f r2 { { -0.2f, -0.2f }, { -0.554699f, -0.832051f } };
            ASSERT_FALSE(r2.approx_parallel(s1));
        }

        test_section("approx_perpendicular(const Line2&)");
        {
            constexpr auto result
                = ray1.approx_perpendicular(nnm::Line2f { { -100.0f, 100.0f }, { -0.923076928f, -0.384615391f } });
            ASSERT(result);
            ASSERT(ray1.approx_perpendicular(nnm::Line2f { { -100.0f, 100.0f }, { 0.923076928f, 0.384615391f } }));
            ASSERT_FALSE(ray1.approx_perpendicular(nnm::Line2f { { 1000.0f, 0.0f }, { -0.384615391f, 0.923076928f } }));
        }

        test_section("approx_perpendicular(const Ray2&)");
        {
            constexpr auto result = ray1.approx_perpendicular(ray2);
            ASSERT_FALSE(result);
            ASSERT(ray2.approx_perpendicular(nnm::Ray2f { { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
            ASSERT(ray2.approx_perpendicular(nnm::Ray2f { { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
        }

        test_section("approx_perpendicular(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Ray2f r1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
            constexpr auto result = r1.approx_perpendicular(s1);
            ASSERT(result);
            constexpr nnm::Ray2f r2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(r2.approx_perpendicular(s1));
        }

        test_section("intersects(const Line2&)");
        {
            constexpr nnm::Ray2f ray3 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray3.intersects(line3);
            ASSERT(result);
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray3.intersects(line4));
        }

        test_section("intersection(const Line2&)");
        {
            constexpr nnm::Ray2f ray4 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray4.intersection(line3);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray4.intersection(line4).has_value());
        }

        test_section("intersects(const Ray2&)");
        {
            constexpr auto result = ray1.intersects(ray2);
            ASSERT_FALSE(result);
            constexpr nnm::Ray2f ray3 { { 0.0f, 10.0f }, { 0.70710678f, -0.70710678f } };
            ASSERT(ray2.intersects(ray3));
        }

        test_section("intersection(const Ray2&)");
        {
            constexpr auto result = ray1.intersection(ray2);
            ASSERT_FALSE(result.has_value());
            constexpr nnm::Ray2f ray3 { { 0.0f, 10.0f }, { 0.70710678f, -0.70710678f } };
            ASSERT(ray2.intersection(ray3).has_value());
            ASSERT(ray2.intersection(ray3).value().approx_equal({ 6.5f, 3.5f }));
        }

        test_section("intersects(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Ray2f ray3 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
            constexpr auto result = ray3.intersects(s1);
            ASSERT(result);
            constexpr nnm::Ray2f ray4 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(ray4.intersects(s1));
        }

        test_section("intersection(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            constexpr nnm::Ray2f ray3 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
            constexpr auto result = ray3.intersection(s1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
            constexpr nnm::Ray2f ray4 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(ray4.intersection(s1).has_value());
        }

        test_section("intersects(const Circle2&)");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Ray2f r1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result = r1.intersects(c1);
            ASSERT_FALSE(result);
            constexpr nnm::Ray2f r2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
            ASSERT(r2.intersects(c1));
            constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(ray3.intersects(c1));
            ASSERT_FALSE(nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersects(c1));
            ASSERT(nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, -1.0f }).intersects(c1));
            ASSERT_FALSE(nnm::Ray2f({ 0.0f, 100.0f }, { 1.0f, .0f }).intersects(c1));
            constexpr nnm::Ray2f ray4 { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } };
            ASSERT(ray4.intersects(c1));
        }

        test_section("intersections(const Circle2&)");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Ray2f r1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result1 = r1.intersections(c1);
            ASSERT_FALSE(result1.has_value());
            constexpr nnm::Ray2f r2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
            const auto result2 = r2.intersections(c1);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result2)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            const auto result3 = ray3.intersections(c1);
            ASSERT_FALSE(result3.has_value());
            const auto result4 = nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, 1.0f }).intersections(c1);
            ASSERT_FALSE(result4.has_value());
            const auto result5 = nnm::Ray2f({ 0.0f, 100.0f }, { 0.0f, -1.0f }).intersections(c1);
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ 0.0f, -7.58257294f })
                && (*result5)[1].approx_equal({ 0.0f, 1.58257294f }));
            const auto result6 = nnm::Ray2f({ 0.0f, 100.0f }, { 1.0f, 0.0f }).intersections(c1);
            ASSERT_FALSE(result6.has_value());
            const auto result7 = nnm::Ray2f({ 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f }).intersections(c1);
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ 6.0f, -6.0f })
                && (*result7)[1].approx_equal({ 6.0f, -6.0f }));
        }

        test_section("intersects(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            constexpr auto result = nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }.intersects(tri1);
            ASSERT(result);
            ASSERT(nnm::Ray2f({ -3.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri2));
            ASSERT(nnm::Ray2f({ 0.0f, 0.0f }, { -1.0f, 0.0f }).intersects(tri1));
            ASSERT(nnm::Ray2f({ 0.0f, 0.0f }, { -1.0f, 0.0f }).intersects(tri2));
            ASSERT(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }).intersects(tri1));
            ASSERT(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }).intersects(tri2));
            ASSERT(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri1));
            ASSERT(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri2));
            ASSERT_FALSE(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri1));
            ASSERT_FALSE(nnm::Ray2f({ 0.0f, 0.0f }, { 1.0f, 0.0f }).intersects(tri2));
        }

        test_section("intersections(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            const auto result1 = nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }.intersections(tri1);
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -1.0f, 0.0f })
                && (*result1)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result2 = nnm::Ray2f({ -3.0f, 0.0f }, { 1.0f, 0.0f }).intersections(tri2);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -1.0f, 0.0f })
                && (*result2)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result3 = nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }.intersections(tri1);
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ -3.6666667f, 0.0f })
                && (*result3)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result4 = nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }).intersections(tri1);
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ -1.8571429f, 2.8571429f })
                && (*result4)[1].approx_equal({ -0.3333333f, 1.3333333f }));
            const auto result5 = nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }).intersections(tri2);
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ -3.9411765f, 1.64705882f })
                && (*result5)[1].approx_equal({ -0.7142857f, 0.57142857f }));
            const auto result6 = nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersections(tri1);
            ASSERT(
                result6.has_value() && (*result6)[0].approx_equal({ 1.0f, 4.0f })
                && (*result6)[1].approx_equal({ 1.0f, 4.0f }));
            const auto result7 = nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersections(tri2);
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ 1.0f, 4.0f })
                && (*result7)[1].approx_equal({ 1.0f, 4.0f }));
            const auto result8 = nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }.intersections(tri1);
            ASSERT_FALSE(result8.has_value());
            const auto result9 = nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }.intersections(tri2);
            ASSERT_FALSE(result9.has_value());
        }

        test_section("approx_tangent");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Ray2f r1 { { 0.0f, 2.0f }, { 1.0f, 0.0f } };
            constexpr auto result = r1.approx_tangent(c1);
            ASSERT(result);
            constexpr nnm::Ray2f r2 { { 0.0f, 2.0f }, { -1.0f, 0.0f } };
            ASSERT_FALSE(r2.approx_tangent(c1));
            const auto r3 = nnm::Ray2f::from_point_to_point({ 0.0f, 2.0f }, { 2.0f, 0.0f });
            ASSERT_FALSE(r3.approx_tangent(c1));
            constexpr nnm::Ray2f r4 { { 2.0f, 2.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(r4.approx_tangent(c1));
            constexpr nnm::Ray2f r5 { { 2.0f, 2.0f }, { 0.0f, -1.0f } };
            ASSERT_FALSE(r5.approx_tangent(c1));
        }

        test_section("project_point_scalar");
        {
            constexpr nnm::Ray2f r { { 1.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            constexpr auto result = r.project_point_scalar({ 2.0f, 3.0f });
            ASSERT(nnm::approx_equal(result, 3.6055512755f));
            ASSERT(nnm::approx_zero(r.project_point_scalar({ 5.0f, -5.0f })));
        }

        test_section("project_point");
        {
            constexpr nnm::Ray2f r { { 1.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            constexpr auto result = r.project_point({ 2.0f, 3.0f });
            ASSERT(result.approx_equal({ -1.0f, 1.0f }));
            ASSERT(r.project_point({ 5.0f, -5.0f }).approx_equal({ 1.0f, -2.0f }));
        }

        constexpr nnm::Ray2f ray3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

        test_section("translate");
        {
            const nnm::Ray2f result = ray3.translate({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
            ASSERT(result.direction.approx_equal(ray3.direction));
        }
        test_section("scale_at");
        {
            const auto result = ray3.scale_at({ 2.0f, -1.5f }, { -2.0f, 0.7f });
            ASSERT(result.origin.approx_equal({ 0.0f, -1.15f }));
            ASSERT(result.direction.approx_equal({ -0.943858f, 0.330351f }));
        }

        test_section("scale");
        {
            const nnm::Ray2f result = ray3.scale({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("rotate_at");
        {
            const auto result = ray3.rotate_at({ 2.0f, -1.5f }, nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 2.515124f, -0.507706f }));
            ASSERT(result.direction.approx_equal({ 0.156434f, 0.987688f }));
        }

        test_section("rotate");
        {
            const auto result = ray3.rotate(nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.01484f, 0.954339f }));
            ASSERT(result.direction.approx_equal({ 0.156434f, 0.987688f }));
        }

        test_section("shear_x_at");
        {
            const auto result = ray3.shear_x_at({ 2.0f, -1.5f }, nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.36327f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.865334f, 0.501195f }));
        }

        test_section("shear_x");
        {
            const nnm::Ray2f result = ray3.shear_x(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 1.26794919f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_y_at");
        {
            const auto result = ray3.shear_y_at({ 2.0f, -1.5f }, nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -0.27346f }));
            ASSERT(result.direction.approx_equal({ 0.501195f, 0.865334f }));
        }

        test_section("shear_y");
        {
            const nnm::Ray2f result = ray3.shear_y(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -3.17963f }));
            ASSERT(result.direction.approx_equal({ 0.964585f, 0.263773f }));
        }

        test_section("operator<");
        {
            ASSERT(ray1 < ray2);
            ASSERT_FALSE(ray2 < ray1);
        }

        test_section("operator==");
        {
            ASSERT_FALSE(ray1 == ray2);
            ASSERT(ray1 == ray1);
        }

        test_section("operator!=");
        {
            ASSERT(ray1 != ray2);
            ASSERT_FALSE(ray1 != ray1);
        }
    }

    test_case("Segment2");
    {
        test_section("Segment2()");
        {
            constexpr nnm::Segment2f s {};
            ASSERT(s.from == nnm::Vector2f::zero());
            ASSERT(s.to == nnm::Vector2f::zero());
        }

        test_section("Segment2(const Vector2&, const Vector2&)");
        {
            constexpr nnm::Segment2f s { { 1.0f, -2.0f }, { -3.0f, 4.0f } };
            ASSERT(s.from == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(s.to == nnm::Vector2f(-3.0f, 4.0f));
        }

        constexpr nnm::Segment2f s1 { { 1.0f, -2.0f }, { -3.0f, 4.0f } };

        test_section("approx_collinear(const Vector2&)");
        {
            constexpr auto result = s1.approx_collinear({ 0.0f, -0.5f });
            ASSERT(result);
            ASSERT_FALSE(s1.approx_collinear({ 0.0f, 0.0f }));
            ASSERT(s1.approx_collinear({ -5.0f, 7.0f }));
            ASSERT(s1.approx_collinear({ 3.0f, -5.0f }));
        }

        test_section("approx_collinear(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 0.0f, -0.5f }, { -0.5547f, 0.83205f } };
            constexpr auto result = s1.approx_collinear(line1);
            ASSERT(result);
            constexpr nnm::Line2f line2 { { 3.0f, -0.5f }, { -0.5547f, 0.83205f } };
            ASSERT_FALSE(s1.approx_collinear(line2));
        }

        test_section("approx_collinear(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 3.0f, -5.0f }, { -0.5547f, 0.83205f } };
            constexpr auto result = s1.approx_collinear(ray1);
            ASSERT(result);
            constexpr nnm::Ray2f ray2 { { 0.0f, -0.5f }, { 0.5547f, -0.83205f } };
            ASSERT(s1.approx_collinear(ray2));
            constexpr nnm::Ray2f ray3 { { 3.0f, -0.5f }, { 0.5547f, -0.83205f } };
            ASSERT_FALSE(s1.approx_collinear(ray3));
        }

        test_section("approx_collinear(const Segment2&)");
        {
            constexpr nnm::Segment2f s2 { { -0.3333333f, 0.0f }, { 0.0f, -0.5f } };
            constexpr auto result = s1.approx_collinear(s2);
            ASSERT(result);
            constexpr nnm::Segment2f s3 { { 7.0f, -11.0f }, { 3.0f, -5.0f } };
            ASSERT(s1.approx_collinear(s3));
            constexpr nnm::Segment2f s4 { { 6.0f, -10.0f }, { 5.0f, -5.0f } };
            ASSERT_FALSE(s1.approx_collinear(s4));
        }

        test_section("approx_contains");
        {
            constexpr auto result = s1.approx_contains({ 0.0f, -0.5f });
            ASSERT(result);
            ASSERT(s1.approx_contains({ 1.0f, -2.0f }));
            ASSERT(s1.approx_contains({ -3.0f, 4.0f }));
            ASSERT(s1.approx_contains({ 0.0f, -0.5f }));
            ASSERT_FALSE(s1.approx_contains({ 1.0f, 1.0f }));
            ASSERT_FALSE(s1.approx_contains({ 3.0f, -5.0f }));
            ASSERT_FALSE(s1.approx_contains({ -5.0f, 7.0f }));
        }

        test_section("distance");
        {
            ASSERT(nnm::approx_equal(s1.distance({ 2.0f, 3.0f }), 3.6055512755f));
            ASSERT(nnm::approx_equal(s1.distance({ 3.0f, -5.0f }), 3.6055512755f));
            ASSERT(nnm::approx_equal(s1.distance({ -4.0f, 4.0f }), 1.0f));
        }

        test_section("distance(const Line2&)");
        {
            constexpr auto result = s1.distance(nnm::Line2f::axis_x_offset(2.0f));
            ASSERT(nnm::approx_zero(result));
            ASSERT(nnm::approx_equal(
                s1.distance(nnm::Line2f::from_points({ 0.0f, 3.0f }, { 1.0f, 2.0f })), 1.4142135624f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Line2f::axis_y_offset(2.0f)), 1.0f));
            ASSERT(nnm::approx_equal(
                s1.distance(nnm::Line2f::from_points({ 2.0f, 0.0f }, { 0.0f, 3.0f })), 1.9414506868f));
        }

        test_section("distance(const Ray2&)");
        {
            ASSERT(nnm::approx_zero(s1.distance(nnm::Ray2f { { 1.0f, 2.0f }, { -1.0f, 0.0f } })));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, -1.0f } }), 1.0f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 2.0f, 3.0f }, { 0.0f, 1.0f } }), 3.60555127f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 1.0f, 5.0f }, { -1.0f, 0.0f } }), 1.0f))
            ASSERT(nnm::approx_equal(s1.distance(nnm::Ray2f { { 1.0f, 5.0f }, { 1.0f, 0.0f } }), 3.88290137f));
            ASSERT(nnm::approx_equal(
                s1.distance(nnm::Ray2f::from_point_to_point({ 1.0f, 2.0f }, { 3.0f, -1.0f })), 2.21880078f))
            ASSERT(nnm::approx_equal(
                s1.distance(nnm::Ray2f::from_point_to_point({ 3.0f, -2.0f }, { 4.0f, -3.0f })), 2.0f));
            ASSERT(nnm::approx_equal(
                s1.distance(nnm::Ray2f::from_point_to_point({ -4.0f, 5.0f }, { -5.0f, 4.0f })), 1.4142135624f));
        }

        test_section("distance(const Segment2&)");
        {
            ASSERT(nnm::approx_zero(s1.distance(s1)));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { -1.0f, 4.0f }, { 1.0f, 1.0f } }), 1.66410059f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { 1.0f, 5.0f }, { 1.0f, 1.0f } }), 1.66410059f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { 3.0f, 3.0f }, { 2.0f, -2.0f } }), 1.0f));
            ASSERT(nnm::approx_equal(s1.distance(nnm::Segment2f { { -4.0f, 5.0f }, { -5.0f, 7.0f } }), 1.4142135624f));
            ASSERT(nnm::approx_zero(s1.distance(nnm::Segment2f { { -1.0f, 3.0f }, { -2.0f, 0.0f } })));
        }

        test_section("signed_distance");
        {
            ASSERT(nnm::approx_equal(s1.signed_distance({ 2.0f, 3.0f }), -3.6055512755f));
            ASSERT(nnm::approx_equal(s1.signed_distance({ 3.0f, -5.0f }), 3.6055512755f));
            ASSERT(nnm::approx_equal(s1.signed_distance({ -4.0f, 4.0f }), 1.0f));
        }

        test_section("direction");
        {
            ASSERT(s1.direction().approx_equal({ -0.5547f, 0.83205f }));
        }

        constexpr nnm::Segment2f s2 { { 0.0f, 4.0f }, { 4.0f, -2.0f } };
        constexpr nnm::Segment2f s3 { { 5.0f, 5.0f }, { 5.0f, 0.0f } };

        test_section("approx_parallel(const Line2&)");
        {
            constexpr auto result
                = s1.approx_parallel(nnm::Line2f { { 100.0f, -100.0f }, { -0.5547001962f, 0.8320502943f } });
            ASSERT(result);
            ASSERT(s1.approx_parallel(nnm::Line2f { { -100.0f, 100.0f }, { 0.5547001962f, -0.8320502943f } }));
            ASSERT_FALSE(s1.approx_parallel(nnm::Line2f {
                { 1.0f, -2.0f },
                {
                    0.8320502943f,
                    0.5547001962f,
                } }));
        }

        test_section("approx_parallel(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 0.0f, 4.0f }, { 0.554699f, -0.832051f } };
            constexpr auto result = s1.approx_parallel(ray1);
            ASSERT(result);
            constexpr nnm::Ray2f ray2 { { -0.2f, -0.2f }, { -0.554699f, -0.832051f } };
            ASSERT_FALSE(s1.approx_parallel(ray2));
        }

        test_section("approx_parallel(const Segment2&)");
        {
            constexpr auto result = s1.approx_parallel(s2);
            ASSERT(result);
            ASSERT_FALSE(s2.approx_parallel(s3));
        }

        test_section("approx_perpendicular(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
            constexpr auto result = s1.approx_perpendicular(line1);
            ASSERT(result);
            constexpr nnm::Line2f line2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(s1.approx_perpendicular(line2));
        }

        test_section("approx_perpendicular(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 2.0f, 3.0f }, { -0.8320502943f, -0.5547001962f } };
            constexpr auto result = s1.approx_perpendicular(ray1);
            ASSERT(result);
            constexpr nnm::Ray2f ray2 { { 5.0f, 0.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(s1.approx_perpendicular(ray2));
        }

        test_section("approx_perpendicular(const Segment2&)");
        {
            constexpr nnm::Segment2f s4 { { 2.0f, 3.0f }, { -1.0f, 1.0f } };
            constexpr auto result = s1.approx_perpendicular(s4);
            ASSERT(result);
            ASSERT_FALSE(s1.approx_perpendicular(s2));
        }

        test_section("intersects(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
            constexpr auto result = s1.intersects(line1);
            ASSERT(result);
            constexpr nnm::Line2f line2 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            ASSERT_FALSE(s1.intersects(line2));
        }

        test_section("intersection(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 5.0f, 5.0f }, { 0.7071067812f, 0.7071067812f } };
            constexpr auto result = s1.intersection(line1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
            constexpr nnm::Line2f line2 { { 4.0f, -2.0f }, { -0.5547001962f, 0.8320502943f } };
            ASSERT_FALSE(s1.intersection(line2).has_value());
        }

        test_section("intersects(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
            constexpr auto result = s1.intersects(ray1);
            ASSERT(result);
            constexpr nnm::Ray2f ray2 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(s1.intersects(ray2));
        }

        test_section("intersection(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 5.0f, 5.0f }, { -0.7071067812f, -0.7071067812f } };
            constexpr auto result = s1.intersection(ray1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
            constexpr nnm::Ray2f ray2 { { 5.0f, 5.0f }, { -0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(s1.intersection(ray2).has_value());
        }

        test_section("intersects(const Segment2&)");
        {
            constexpr nnm::Segment2f s4 { { 5.0f, 5.0f }, { -5.0f, -5.0f } };
            constexpr auto result = s1.intersects(s4);
            ASSERT(result);
            constexpr nnm::Segment2f s5 { { 5.0f, 5.0f }, { 1.6f, 1.6f } };
            ASSERT_FALSE(s1.intersects(s5));
        }

        test_section("intersection(const Segment2&)");
        {
            constexpr nnm::Segment2f s4 { { 5.0f, 5.0f }, { -5.0f, -5.0f } };
            constexpr auto result = s1.intersection(s4);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ -0.2f, -0.2f }));
            constexpr nnm::Segment2f s5 { { 5.0f, 5.0f }, { 1.6f, 1.6f } };
            ASSERT_FALSE(s1.intersection(s5).has_value());
        }

        test_section("intersects(const Circle2&)");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Segment2f seg1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
            ASSERT_FALSE(seg1.intersects(c1));
            constexpr nnm::Segment2f seg2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
            ASSERT(seg2.intersects(c1));
            constexpr nnm::Segment2f seg3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
            ASSERT(seg3.intersects(c1));
            constexpr nnm::Segment2f seg4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
            ASSERT(seg4.intersects(c1));
        }

        test_section("intersections(const Circle2&)");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Segment2f seg1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
            const auto result1 = seg1.intersections(c1);
            ASSERT_FALSE(result1.has_value());
            constexpr nnm::Segment2f seg2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
            const auto result2 = seg2.intersections(c1);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result2)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Segment2f seg3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
            const auto result3 = seg3.intersections(c1);
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result3)[1].approx_equal({ 1.08452405f, 1.9154759f }));
            constexpr nnm::Segment2f seg4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
            const auto result4 = seg4.intersections(c1);
            ASSERT_FALSE(result4.has_value());
        }

        test_section("intersects(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            constexpr auto result = nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }.intersects(tri1);
            ASSERT(result);
            ASSERT(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersects(tri2));
            ASSERT(nnm::Segment2f({ 2.0f, 2.0f }, { -3.0f, 0.0f }).intersects(tri1))
            ASSERT(nnm::Segment2f({ 2.0f, 2.0f }, { -3.0f, 0.0f }).intersects(tri2))
            ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
            ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
            ASSERT(nnm::Segment2f({ -1.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
            ASSERT(nnm::Segment2f({ -1.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
            ASSERT(nnm::Segment2f({ -5.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri1));
            ASSERT(nnm::Segment2f({ -5.0f, 0.0f }, { 2.0f, 2.0f }).intersects(tri2));
        }

        test_section("intersections(const Triangle2&)");
        {
            constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
            constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };
            ASSERT_FALSE(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersections(tri1).has_value());
            ASSERT_FALSE(nnm::Segment2f({ -3.0f, 0.0f }, { -1.0f, 2.0f }).intersections(tri2).has_value());
            const auto result1 = nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }.intersections(tri1);
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -0.5f, 1.0f })
                && (*result1)[1].approx_equal({ -0.5f, 1.0f }));
            const auto result2 = nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }.intersections(tri2);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -0.5f, 1.0f })
                && (*result2)[1].approx_equal({ -0.5f, 1.0f }));
            ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersections(tri1).has_value());
            ASSERT_FALSE(nnm::Segment2f({ 0.0f, 0.0f }, { 2.0f, 2.0f }).intersections(tri2).has_value());
            const auto result3 = nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }.intersections(tri1);
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ -1.0f, 0.0f })
                && (*result3)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result4 = nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }.intersections(tri2);
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ -1.0f, 0.0f })
                && (*result4)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result5 = nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }.intersections(tri1);
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ -3.7272727f, 0.36363636f })
                && (*result5)[1].approx_equal({ -0.33333333f, 1.3333333f }));
            const auto result6 = nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }.intersections(tri2);
            ASSERT(
                result6.has_value() && (*result6)[0].approx_equal({ -3.7272727f, 0.36363636f })
                && (*result6)[1].approx_equal({ -0.33333333f, 1.3333333f }));
        }

        test_section("approx_tangent");
        {
            constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Segment2f seg1 { { 0.0f, 2.0f }, { 1.0f, 2.0f } };
            constexpr auto result = seg1.approx_tangent(c1);
            ASSERT_FALSE(result);
            constexpr nnm::Segment2f seg2 { { 0.0f, 2.0f }, { 4.0f, 2.0f } };
            ASSERT(seg2.approx_tangent(c1));
            constexpr nnm::Segment2f seg3 { { 2.0f, 2.0f }, { 4.0f, 4.0f } };
            ASSERT_FALSE(seg3.approx_tangent(c1));
            constexpr nnm::Segment2f seg4 { { 2.0f, 2.0f }, { 4.0f, 0.0f } };
            ASSERT_FALSE(seg4.approx_tangent(c1));
        }

        test_section("project_point");
        {
            constexpr auto result = s1.project_point({ 2.0f, 3.0f });
            ASSERT(result.approx_equal({ -1.0f, 1.0f }));
            ASSERT(s1.project_point({ 5.0f, -5.0f }).approx_equal({ 1.0f, -2.0f }));
            ASSERT(s1.project_point({ -5.0f, 5.0f }).approx_equal({ -3.0f, 4.0f }));
        }

        test_section("unchecked_slope");
        {
            constexpr auto result = s1.unchecked_slope();
            ASSERT(nnm::approx_equal(result, -1.5f));
            ASSERT(nnm::approx_equal(s2.unchecked_slope(), -1.5f));
        }

        test_section("slope");
        {
            constexpr auto result = s1.slope();
            ASSERT(result.has_value() && nnm::approx_equal(result.value(), -1.5f));
            ASSERT_FALSE(s3.slope().has_value());
        }

        test_section("length_sqrd");
        {
            constexpr auto result = s1.length_sqrd();
            ASSERT(nnm::approx_equal(result, 52.0f));
            ASSERT(nnm::approx_equal(s3.length_sqrd(), 25.0f));
        }

        test_section("length");
        {
            ASSERT(nnm::approx_equal(s1.length(), 7.2111025509f));
            ASSERT(nnm::approx_equal(s3.length(), 5.0f));
        }

        test_section("midpoint");
        {
            ASSERT(s1.midpoint().approx_equal({ -1.0f, 1.0f }));
            ASSERT(s3.midpoint().approx_equal({ 5.0f, 2.5f }));
        }

        test_section("translate");
        {
            const auto result = s1.translate({ -3.0f, 3.0f });
            ASSERT(result.from.approx_equal({ -2.0f, 1.0f }));
            ASSERT(result.to.approx_equal({ -6.0f, 7.0f }));
        }

        test_section("scale_at");
        {
            const auto result = s1.scale_at({ 1.0f, 2.0f }, { -1.0f, 3.0f });
            ASSERT(result.from.approx_equal({ 1.0f, -10.0f }));
            ASSERT(result.to.approx_equal({ 5.0f, 8.0f }));
        }

        test_section("scale");
        {
            const auto result = s1.scale({ -1.0f, 3.0f });
            ASSERT(result.from.approx_equal({ -1.0f, -6.0f }));
            ASSERT(result.to.approx_equal({ 3.0f, 12.0f }));
        }

        test_section("rotate_at");
        {
            const auto result = s1.rotate_at({ 1.0f, 2.0f }, nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ 3.35115f, -1.23607f }));
            ASSERT(result.to.approx_equal({ -3.41164f, 1.266893f }));
        }

        test_section("rotate");
        {
            const auto result = s1.rotate(nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ 1.98459f, -1.03025f }));
            ASSERT(result.to.approx_equal({ -4.77819f, 1.47271f }));
        }

        test_section("shear_x_at");
        {
            const auto result = s1.shear_x_at({ 1.0f, 2.0f }, nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ -1.90617f, -2.0f }));
            ASSERT(result.to.approx_equal({ -1.54691f, 4.0f }));
        }

        test_section("shear_x");
        {
            const auto result = s1.shear_x(nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ -0.453085f, -2.0f }));
            ASSERT(result.to.approx_equal({ -0.0938299f, 4.0f }));
        }

        test_section("shear_y_at");
        {
            const auto result = s1.shear_y_at({ 1.0f, 2.0f }, nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ 1.0f, -2.0f }));
            ASSERT(result.to.approx_equal({ -3.0f, 1.09383f }));
        }

        test_section("shear_y");
        {
            const auto result = s1.shear_y(nnm::pi() / 5.0f);
            ASSERT(result.from.approx_equal({ 1.0f, -1.27346f }));
            ASSERT(result.to.approx_equal({ -3.0f, 1.82037f }));
        }

        test_section("operator==");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = s1 == s1;
            ASSERT(result);
            ASSERT_FALSE(s1 == s2);
        }

        test_section("operator!=");
        {
            constexpr auto result = s1 != s2;
            ASSERT(result);
            ASSERT_FALSE(s2 != s2);
        }

        test_section("operator<");
        {
            ASSERT(s2 < s1);
            ASSERT_FALSE(s1 < s2);
        }
    }

    test_case("Circle2");
    {
        test_section("Circle2()");
        {
            constexpr nnm::Circle2f c {};
            ASSERT(c.center == nnm::Vector2f(0.0f, 0.0f));
            ASSERT(c.radius == 1.0f);
        }

        test_section("Circle2(const Vector2&, Real)");
        {
            constexpr nnm::Circle2f c { { 2.0f, -3.0f }, 5.0f };
            ASSERT(c.center == nnm::Vector2f(2.0f, -3.0f));
            ASSERT(c.radius == 5.0f);
        }

        constexpr nnm::Circle2f c1 { { 2.0f, -3.0f }, 5.0f };

        test_section("circumference");
        {
            constexpr auto result = c1.circumference();
            ASSERT(nnm::approx_equal(result, 31.4159265359f));
        }

        test_section("perimeter");
        {
            constexpr auto result = c1.perimeter();
            ASSERT(nnm::approx_equal(result, 31.4159265359f));
        }

        test_section("area");
        {
            constexpr auto result = c1.area();
            ASSERT(nnm::approx_equal(result, 78.5398163397f));
        }

        test_section("diameter");
        {
            constexpr auto result = c1.diameter();
            ASSERT(nnm::approx_equal(result, 10.0f));
        }

        test_section("contains");
        {
            constexpr auto result = c1.contains({ 2.0f, -3.0f });
            ASSERT(result);
            ASSERT(c1.contains({ 4.0f, -4.0f }));
            ASSERT_FALSE(c1.contains({ 7.0f, 0.0f }));
        }

        test_section("point_at");
        {
            ASSERT(c1.point_at(0.0f).approx_equal({ 7.0f, -3.0f }));
            ASSERT(c1.point_at(nnm::pi()).approx_equal({ -3.0f, -3.0f }));
            ASSERT(c1.point_at(nnm::pi() / 2.0f).approx_equal({ 2.0f, 2.0f }));
            ASSERT(c1.point_at(nnm::pi() / 3.0f).approx_equal({ 4.5f, 1.330127f }));
        }

        test_section("signed_distance");
        {
            ASSERT(nnm::approx_equal(c1.signed_distance({ -3.0f, 1.0f }), 1.403124237f));
            ASSERT(nnm::approx_equal(c1.signed_distance({ 0.0f, 0.0f }), -1.39444872f));
            ASSERT_FALSE(nnm::approx_equal(c1.signed_distance({ 1.0f, 1.0f }), -1.39444872f));
        }

        test_section("distance");
        {
            ASSERT(nnm::approx_equal(c1.distance({ -3.0f, 1.0f }), 1.403124237f));
            ASSERT(nnm::approx_equal(c1.distance({ 0.0f, 0.0f }), 0.0f));
            ASSERT_FALSE(nnm::approx_equal(c1.distance({ 1.0f, 1.0f }), 1.0f));
            ASSERT_FALSE(nnm::approx_equal(c1.distance({ 10.0f, 10.0f }), 1.0f));
        }

        test_section("intersects(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            constexpr auto result = c1.intersects(line1);
            ASSERT(result);
            constexpr nnm::Line2f line2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(c1.intersects(line2));
            ASSERT(c1.intersects(nnm::Line2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } }));
            ASSERT_FALSE(c1.intersects(nnm::Line2f { { 0.0f, 100.0f }, { 1.0f, .0f } }));
        }

        test_section("intersections(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result1 = c1.intersections(line1);
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result1)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Line2f line2 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(c1.intersections(line2).has_value());
            const auto result2 = c1.intersections(nnm::Line2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } });
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 0.0f, -7.58257294f })
                && (*result2)[1].approx_equal({ 0.0f, 1.58257294f }));
        }

        test_section("intersects(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result = c1.intersects(ray1);
            ASSERT_FALSE(result);
            constexpr nnm::Ray2f ray2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
            ASSERT(c1.intersects(ray2));
            constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            ASSERT_FALSE(c1.intersects(ray3));
            ASSERT_FALSE(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } }));
            ASSERT(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, -1.0f } }));
            ASSERT_FALSE(c1.intersects(nnm::Ray2f { { 0.0f, 100.0f }, { 1.0f, .0f } }));
            constexpr nnm::Ray2f ray4 { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } };
            ASSERT(c1.intersects(ray4));
        }

        test_section("intersections(const Ray2&)");
        {
            constexpr nnm::Ray2f ray1 { { 0.0f, 3.0f }, { -0.7071067812f, 0.7071067812f } };
            const auto result1 = c1.intersections(ray1);
            ASSERT_FALSE(result1.has_value());
            constexpr nnm::Ray2f ray2 { { 0.0f, 3.0f }, { 0.7071067812f, -0.7071067812f } };
            const auto result2 = c1.intersections(ray2);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result2)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Ray2f ray3 { { 0.0f, 3.0f }, { 0.7071067812f, 0.7071067812f } };
            const auto result3 = c1.intersections(ray3);
            ASSERT_FALSE(result3.has_value());
            const auto result4 = c1.intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, 1.0f } });
            ASSERT_FALSE(result4.has_value());
            const auto result5 = c1.intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 0.0f, -1.0f } });
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ 0.0f, -7.58257294f })
                && (*result5)[1].approx_equal({ 0.0f, 1.58257294f }));
            const auto result6 = c1.intersections(nnm::Ray2f { { 0.0f, 100.0f }, { 1.0f, 0.0f } });
            ASSERT_FALSE(result6.has_value());
            const auto result7 = c1.intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 0.7071067812f, -0.7071067812f } });
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ 6.0f, -6.0f })
                && (*result7)[1].approx_equal({ 6.0f, -6.0f }));
        }

        test_section("intersects(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
            ASSERT_FALSE(c1.intersects(s1));
            constexpr nnm::Segment2f s2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
            ASSERT(c1.intersects(s2));
            constexpr nnm::Segment2f s3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
            ASSERT(c1.intersects(s3));
            constexpr nnm::Segment2f s4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
            ASSERT(c1.intersects(s4));
        }

        test_section("intersections(const Segment2&)");
        {
            constexpr nnm::Segment2f s1 { { 0.0f, 3.0f }, { 1.0f, 2.0f } };
            const auto result1 = c1.intersections(s1);
            ASSERT_FALSE(result1.has_value());
            constexpr nnm::Segment2f s2 { { 0.0f, 3.0f }, { 9.0f, -6.0f } };
            const auto result2 = c1.intersections(s2);
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result2)[1].approx_equal({ 6.9154759f, -3.9154759f }));
            constexpr nnm::Segment2f s3 { { 5.0f, -2.0f }, { 0.0f, 3.0f } };
            const auto result3 = c1.intersections(s3);
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ 1.08452405f, 1.9154759f })
                && (*result3)[1].approx_equal({ 1.08452405f, 1.9154759f }));
            constexpr nnm::Segment2f s4 { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
            const auto result4 = c1.intersections(s4);
            ASSERT_FALSE(result4.has_value());
        }

        test_section("intersects(const Circle2&)");
        {
            constexpr auto result = c1.intersects(c1);
            ASSERT(result);
            constexpr nnm::Circle2f c2 { { 1.0f, -4.0f }, 2.0f };
            ASSERT(c1.intersects(c2));
            ASSERT_FALSE(c1.intersects(nnm::Circle2 { { 0.0f, 100.0f }, 2.0f }));
            ASSERT(c1.intersects(nnm::Circle2f { { -4.0f, -4.0f }, 2.0f }));
        }

        test_section("intersect_depth");
        {
            const auto result1 = c1.intersect_depth(c1);
            ASSERT(result1.approx_equal({ 0.0f, 0.0f }));
            const auto result2 = c1.intersect_depth({ { 1.0f, -4.0f }, 2.0f });
            ASSERT(result2.approx_equal({ -3.9497474683f, -3.9497474683f }));
            const auto result3 = c1.intersect_depth(nnm::Circle2f { { 0.0f, 100.0f }, 2.0f });
            ASSERT(result3.approx_equal({ 1.86410332f, -96.0013198f }));
            const auto result4 = c1.intersect_depth(nnm::Circle2f { { -4.0f, -4.0f }, 2.0f });
            ASSERT(result4.approx_equal({ -0.9047574669f, -0.1507929111f }));
        }

        test_section("approx_tangent(const Line2&)");
        {
            constexpr nnm::Circle2f circle { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Line2f line3 { { -2.0f, 2.0f }, { -1.0f, 0.0f } };
            constexpr auto result = circle.approx_tangent(line3);
            ASSERT(result);
            constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            ASSERT_FALSE(circle.approx_tangent(line1));
        }

        test_section("approx_tangent(const Ray2&)");
        {
            constexpr nnm::Circle2f c2 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Ray2f r1 { { 0.0f, 2.0f }, { 1.0f, 0.0f } };
            constexpr auto result = c2.approx_tangent(r1);
            ASSERT(result);
            constexpr nnm::Ray2f r2 { { 0.0f, 2.0f }, { -1.0f, 0.0f } };
            ASSERT_FALSE(c2.approx_tangent(r2));
            const auto r3 = nnm::Ray2f::from_point_to_point({ 0.0f, 2.0f }, { 2.0f, 0.0f });
            ASSERT_FALSE(c2.approx_tangent(r3));
            constexpr nnm::Ray2f r4 { { 2.0f, 2.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(c2.approx_tangent(r4));
            constexpr nnm::Ray2f r5 { { 2.0f, 2.0f }, { 0.0f, -1.0f } };
            ASSERT_FALSE(c2.approx_tangent(r5));
        }

        test_section("approx_tangent(const Segment2&");
        {
            constexpr nnm::Circle2f c2 { { 2.0f, -3.0f }, 5.0f };
            constexpr nnm::Segment2f seg1 { { 0.0f, 2.0f }, { 1.0f, 2.0f } };
            constexpr auto result = c2.approx_tangent(seg1);
            ASSERT_FALSE(result);
            constexpr nnm::Segment2f seg2 { { 0.0f, 2.0f }, { 4.0f, 2.0f } };
            ASSERT(c2.approx_tangent(seg2));
            constexpr nnm::Segment2f seg3 { { 2.0f, 2.0f }, { 4.0f, 4.0f } };
            ASSERT_FALSE(c2.approx_tangent(seg3));
            constexpr nnm::Segment2f seg4 { { 2.0f, 2.0f }, { 4.0f, 0.0f } };
            ASSERT_FALSE(c2.approx_tangent(seg4));
        }

        test_section("approx_tangent(const Circle2&)");
        {
            constexpr nnm::Circle2f c2 { { 8.0f, -3.0f }, 1.0f };
            constexpr auto result = c1.approx_tangent(c2);
            ASSERT(result);
            constexpr nnm::Circle2f c3 { { 6.0f, 2.0f }, 1.403124237f };
            ASSERT(c1.approx_tangent(c3));
            constexpr nnm::Circle2f c4 { { 2.0f, -6.0f }, 2.0f };
            ASSERT(c1.approx_tangent(c4));
            constexpr nnm::Circle2f c5 { { 0.0f, 100.0f }, 45.0f };
            ASSERT_FALSE(c1.approx_tangent(c5));
            constexpr nnm::Circle2f c6 { { 2.0f, 0.0f }, 4.0f };
            ASSERT_FALSE(c1.approx_tangent(c6));
            ASSERT_FALSE(c1.approx_tangent(c1));
        }

        test_section("translate");
        {
            ASSERT(c1.translate({ 0.0f, 0.0f }).approx_equal(c1));
            ASSERT(c1.translate({ -20.0f, 30.0f }).approx_equal({ { -18.0f, 27.0f }, 5.0f }))
            ASSERT_FALSE(c1.translate({ -20.0f, 100.0f }).approx_equal({ { -18.0f, 27.0f }, 5.0f }));
        }

        constexpr nnm::Vector2f origin { -3.0f, 1.0f };

        test_section("rotate_at");
        {
            ASSERT(c1.rotate_at(origin, nnm::pi() / 3.0f).approx_equal({ { 2.964101615f, 3.330127f }, 5.0f }));
            ASSERT_FALSE(
                c1.rotate_at({ -2.0f, 10.0f }, nnm::pi() / 4.0f).approx_equal({ { 2.964101615f, 3.330127f }, 5.0f }))
        }

        test_section("rotate");
        {
            ASSERT(c1.rotate(nnm::pi() / 3.0f).approx_equal({ { 3.5980762f, 0.2320508f }, 5.0f }));
            ASSERT_FALSE(c1.rotate(-nnm::pi() / 10.0f).approx_equal({ { 3.5980762f, 0.2320508f }, 5.0f }));
        }

        test_section("scale_at");
        {
            ASSERT(c1.scale_at(origin, 4.0f).approx_equal({ { 17.0f, -15.0f }, 20.0f }));
            ASSERT_FALSE(c1.scale_at({ -10.0f, 200.0f }, 2.0f).approx_equal({ { 17.0f, -15.0f }, 20.0f }));
        }

        test_section("scale");
        {
            ASSERT(c1.scale(-3.0f).approx_equal({ { -6.0f, 9.0f }, 15.0f }));
            ASSERT_FALSE(c1.scale(2.0f).approx_equal({ { -6.0f, 9.0f }, 15.0f }));
        }

        test_section("approx_equal");
        {
            constexpr auto result = c1.approx_equal(c1);
            ASSERT(result);
            ASSERT_FALSE(c1.approx_equal(nnm::Circle2f { { -1.0f, -100.0f }, 10.0f }));
            ASSERT(c1.approx_equal(nnm::Circle2f { { 2.00000001f, -3.000000000001f }, 4.999999f }));
        }

        test_section("operator==");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = c1 == c1;
            ASSERT(result);
            ASSERT_FALSE(c1 == nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
            ASSERT_FALSE(c1 == nnm::Circle2f({ 2.00000001f, -3.0001f }, 4.999999f));
        }

        test_section("operator!=");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = c1 != c1;
            ASSERT_FALSE(result);
            ASSERT(c1 != nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
            ASSERT(c1 != nnm::Circle2f({ 2.00000001f, -3.0001f }, 4.999999f));
        }

        test_section("operator<");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = c1 < c1;
            ASSERT_FALSE(result);
            ASSERT_FALSE(c1 < nnm::Circle2f({ -1.0f, -100.0f }, 10.0f));
            ASSERT(c1 < nnm::Circle2f({ 2.000001f, -3.0001f }, 4.999999f))
        }
    }

    test_case("Triangle2");
    {
        test_section("Triangle()");
        {
            constexpr nnm::Triangle2f t;
            ASSERT(t.vertices[0] == nnm::Vector2f::zero());
            ASSERT(t.vertices[1] == nnm::Vector2f::zero());
            ASSERT(t.vertices[2] == nnm::Vector2f::zero());
        }

        test_section("Triangle2(const Vector2&, const Vector2&, const Vector2&)");
        {
            constexpr nnm::Triangle2f t { { 1.0f, -2.0f }, { -3.0f, 4.0f }, { 5.0f, 6.0f } };
            ASSERT(t.vertices[0] == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(t.vertices[1] == nnm::Vector2f(-3.0f, 4.0f));
            ASSERT(t.vertices[2] == nnm::Vector2f(5.0f, 6.0f));
        }

        constexpr nnm::Triangle2f tri1 { { -4.0f, 2.0f }, { -3.0f, -4.0f }, { 1.0f, 4.0f } };
        constexpr nnm::Triangle2f tri2 { { -3.0f, -4.0f }, { 1.0f, 4.0f }, { -4.0f, 2.0f } };

        test_section("centroid");
        {
            constexpr auto result = tri1.centroid();
            ASSERT(result.approx_equal({ -2.0f, 0.666666667f }));
            ASSERT(tri2.centroid().approx_equal({ -2.0f, 0.666666667f }));
        }

        test_section("circumcenter");
        {
            constexpr auto result = tri1.circumcenter();
            ASSERT(result.approx_equal({ -0.125f, -0.4375f }));
            ASSERT(tri2.circumcenter().approx_equal({ -0.125f, -0.4375f }));
        }

        test_section("incenter");
        {
            ASSERT(tri1.incenter().approx_equal({ -2.2461969f, 1.01306745f }));
            ASSERT(tri2.incenter().approx_equal({ -2.2461969f, 1.01306745f }));
        }

        test_section("orthocenter");
        {
            const auto result = tri1.orthocenter();
            ASSERT(result.approx_equal({ -5.75f, 2.875f }));
            ASSERT(tri2.orthocenter().approx_equal({ -5.75f, 2.875f }));
        }

        test_section("area");
        {
            constexpr auto result = tri1.area();
            ASSERT(nnm::approx_equal(result, 16.0f));
            ASSERT(nnm::approx_equal(tri2.area(), 16.0f));
        }

        test_section("median");
        {
            constexpr auto result = tri1.median(0);
            ASSERT(result.approx_equal({ { -4.0f, 2.0f }, { -1.0f, 0.0f } }));
            ASSERT(tri1.median(1).approx_equal({ { -3.0f, -4.0f }, { -1.5f, 3.0f } }));
            ASSERT(tri1.median(2).approx_equal({ { 1.0f, 4.0f }, { -3.5f, -1.0f } }));
            ASSERT(tri2.median(0).approx_equal({ { -3.0f, -4.0f }, { -1.5f, 3.0f } }));
            ASSERT(tri2.median(1).approx_equal({ { 1.0f, 4.0f }, { -3.5f, -1.0f } }));
            ASSERT(tri2.median(2).approx_equal({ { -4.0f, 2.0f }, { -1.0f, 0.0f } }));
        }

        test_section("perpendicular_bisector");
        {
            ASSERT(tri1.perpendicular_bisector(0).approx_coincident(
                nnm::Line2f::from_point_slope({ -3.5f, -1.0f }, 0.166666667f)));
            ASSERT(tri1.perpendicular_bisector(1).approx_coincident(
                nnm::Line2f::from_point_slope({ -1.0f, 0.0f }, -0.5f)));
            ASSERT(
                tri1.perpendicular_bisector(2).approx_coincident(nnm::Line2f::from_point_slope({ -1.5f, 3.0f }, -2.5f)))
            ASSERT(tri2.perpendicular_bisector(0).approx_coincident(
                nnm::Line2f::from_point_slope({ -1.0f, 0.0f }, -0.5f)));
            ASSERT(tri2.perpendicular_bisector(1).approx_coincident(
                nnm::Line2f::from_point_slope({ -1.5f, 3.0f }, -2.5f)));
            ASSERT(tri2.perpendicular_bisector(2).approx_coincident(
                nnm::Line2f::from_point_slope({ -3.5f, -1.0f }, 0.166666667f)));
        }

        test_section("angle");
        {
            ASSERT(nnm::approx_equal(tri1.angle(0), nnm::radians(102.339087f)));
            ASSERT(nnm::approx_equal(tri1.angle(1), nnm::radians(36.02737339f)));
            ASSERT(nnm::approx_equal(tri1.angle(2), nnm::radians(41.6335393f)));
            ASSERT(nnm::approx_equal(tri2.angle(0), nnm::radians(36.02737339f)));
            ASSERT(nnm::approx_equal(tri2.angle(1), nnm::radians(41.6335393f)));
            ASSERT(nnm::approx_equal(tri2.angle(2), nnm::radians(102.339087f)));
        }

        test_section("angle_bisector");
        {
            ASSERT(
                tri1.angle_bisector(0).approx_coincident(nnm::Line2f::from_point_slope({ -4.0f, 2.0f }, -0.56273853f)));
            ASSERT(tri1.angle_bisector(1).approx_coincident(
                nnm::Line2f::from_point_slope({ -3.0f, -4.0f }, 6.650367627f)));
            ASSERT(
                tri1.angle_bisector(2).approx_coincident(nnm::Line2f::from_point_slope({ 1.0f, 4.0f }, 0.92013288f)));
            ASSERT(tri2.angle_bisector(0).approx_coincident(
                nnm::Line2f::from_point_slope({ -3.0f, -4.0f }, 6.650367627f)));
            ASSERT(
                tri2.angle_bisector(1).approx_coincident(nnm::Line2f::from_point_slope({ 1.0f, 4.0f }, 0.92013288f)));
            ASSERT(
                tri2.angle_bisector(2).approx_coincident(nnm::Line2f::from_point_slope({ -4.0f, 2.0f }, -0.56273853f)));
        }

        test_section("altitude");
        {
        }

        test_section("lerp_point");
        {
            constexpr auto result = tri1.lerp_point({ 0.5f, 0.1f, 0.4f });
            ASSERT(result.approx_equal({ -1.9f, 2.2f }));
            ASSERT(tri2.lerp_point({ 0.1f, 0.4f, 0.5f }).approx_equal({ -1.9f, 2.2f }));
            ASSERT(tri1.lerp_point({ 0.5f, -1.5f, 100.0f }).approx_equal({ 102.5f, 407.0f }));
            ASSERT(tri2.lerp_point({ -1.5f, 100.0f, 0.5f }).approx_equal({ 102.5f, 407.0f }));
        }

        test_section("barycentric");
        {
            constexpr auto r1 = tri1.barycentric({ 0.0f, 0.0f });
            ASSERT(tri1.lerp_point(r1).approx_equal({ 0.0f, 0.0f }));
            ASSERT(tri2.lerp_point(tri2.barycentric({ -2.0f, 1.0f })).approx_equal({ -2.0f, 1.0f }));
        }

        test_section("contains");
        {
            constexpr auto result = tri1.contains({ 0.0f, 0.0f });
            ASSERT_FALSE(result);
            ASSERT_FALSE(tri2.contains({ 0.0f, 0.0f }));
            ASSERT(tri1.contains({ -2.0f, 1.0f }));
            ASSERT(tri2.contains({ -2.0f, 1.0f }));
            ASSERT(tri1.contains({ 1.0f, 4.0f }));
            ASSERT(tri2.contains({ 1.0f, 4.0f }));
            ASSERT(tri1.contains({ -1.0f, 0.0f }));
            ASSERT(tri2.contains({ -1.0f, 0.0f }));
        }

        test_section("intersects(const Triangle2&)");
        {
            ASSERT(tri1.intersects(tri1));
            ASSERT(tri1.intersects(tri2));
            ASSERT(tri2.intersects(tri2));
            ASSERT(tri2.intersects(tri1));
            constexpr nnm::Triangle2f tri3 { { 1.0f, 2.0f }, { 4.0f, 5.0f }, { 2.0f, -3.0f } };
            ASSERT_FALSE(tri1.intersects(tri3));
            ASSERT_FALSE(tri3.intersects(tri1));
            ASSERT_FALSE(tri2.intersects(tri3));
            ASSERT_FALSE(tri3.intersects(tri2));
            constexpr nnm::Triangle2f tri4 { { 4.0f, 5.0f }, { -2.0f, 1.0f }, { 2.0f, -3.0f } };
            ASSERT(tri1.intersects(tri4));
            ASSERT(tri4.intersects(tri1));
            ASSERT(tri2.intersects(tri4));
            ASSERT(tri4.intersects(tri2));
            constexpr nnm::Triangle2f tri5 { { 2.0f, -3.0f }, { -5.0f, -1.0f }, { 4.0f, 5.0f } };
            ASSERT(tri1.intersects(tri5));
            ASSERT(tri5.intersects(tri1));
            ASSERT(tri2.intersects(tri5));
            ASSERT(tri5.intersects(tri1));
        }

        test_section("intersects(const Line2&)");
        {
            constexpr auto result = tri1.intersects(nnm::Line2f::axis_x());
            ASSERT(result);
            ASSERT(tri2.intersects(nnm::Line2f::axis_x()));
            ASSERT(tri1.intersects(nnm::Line2f::axis_y()));
            ASSERT(tri2.intersects(nnm::Line2f::axis_y()));
            ASSERT_FALSE(tri1.intersects(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f })));
            ASSERT_FALSE(tri2.intersects(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f })));
            ASSERT(tri1.intersects(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f })));
            ASSERT(tri2.intersects(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f })));
        }

        test_section("intersections(const Line2&)");
        {
            const auto result1 = tri1.intersections(nnm::Line2f::axis_x());
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -3.666667f, 0.0f })
                && (*result1)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result2 = tri2.intersections(nnm::Line2f::axis_x());
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -3.666667f, 0.0f })
                && (*result2)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result3 = tri1.intersections(nnm::Line2f::axis_y());
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ 0.0f, 2.0f })
                && (*result3)[1].approx_equal({ 0.0f, 3.6f }));
            const auto result4 = tri2.intersections(nnm::Line2f::axis_y());
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ 0.0f, 2.0f })
                && (*result4)[1].approx_equal({ 0.0f, 3.6f }));
            const auto result5 = tri1.intersections(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }));
            ASSERT_FALSE(result5.has_value());
            const auto result6 = tri2.intersections(nnm::Line2f::from_points({ 1.0f, 0.0f }, { 2.0f, 4.0f }));
            ASSERT_FALSE(result6.has_value());
            const auto result7 = tri1.intersections(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }));
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ -3.0f, 2.4f })
                && (*result7)[1].approx_equal({ -0.538461548f, 0.923076923f }));
            const auto result8 = tri2.intersections(nnm::Line2f::from_points({ -4.0f, 3.0f }, { 1.0f, 0.0f }));
            ASSERT(
                result8.has_value() && (*result8)[0].approx_equal({ -3.0f, 2.4f })
                && (*result8)[1].approx_equal({ -0.538461548f, 0.923076923f }));
        }

        test_section("intersects(const Ray2&)");
        {
            constexpr auto result = tri1.intersects(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
            ASSERT(result);
            ASSERT(tri2.intersects(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } }));
            ASSERT(tri1.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }));
            ASSERT(tri2.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } }));
            ASSERT(tri1.intersects(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f })));
            ASSERT(tri2.intersects(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f })));
            ASSERT(tri1.intersects(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f })));
            ASSERT(tri2.intersects(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f })));
            ASSERT_FALSE(tri1.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }));
            ASSERT_FALSE(tri2.intersects(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } }));
        }

        test_section("intersections(const Ray2&)");
        {
            const auto result1 = tri1.intersections(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -1.0f, 0.0f })
                && (*result1)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result2 = tri2.intersections(nnm::Ray2f { { -3.0f, 0.0f }, { 1.0f, 0.0f } });
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -1.0f, 0.0f })
                && (*result2)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result3 = tri1.intersections(nnm::Ray2f { { 0.0f, 0.0f }, { -1.0f, 0.0f } });
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ -3.6666667f, 0.0f })
                && (*result3)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result4 = tri1.intersections(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { 0.0f, 1.0f }));
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ -1.8571429f, 2.8571429f })
                && (*result4)[1].approx_equal({ -0.3333333f, 1.3333333f }));
            const auto result5 = tri2.intersections(nnm::Ray2f::from_point_to_point({ 1.0f, 0.0f }, { -2.0f, 1.0f }));
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ -3.9411765f, 1.64705882f })
                && (*result5)[1].approx_equal({ -0.7142857f, 0.57142857f }));
            const auto result6 = tri1.intersections(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }));
            ASSERT(
                result6.has_value() && (*result6)[0].approx_equal({ 1.0f, 4.0f })
                && (*result6)[1].approx_equal({ 1.0f, 4.0f }));
            const auto result7 = tri2.intersections(nnm::Ray2f::from_point_to_point({ -3.0f, 0.0f }, { -1.0f, 2.0f }));
            ASSERT(
                result7.has_value() && (*result7)[0].approx_equal({ 1.0f, 4.0f })
                && (*result7)[1].approx_equal({ 1.0f, 4.0f }));
            const auto result8 = tri1.intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } });
            ASSERT_FALSE(result8.has_value());
            const auto result9 = tri2.intersections(nnm::Ray2f { { 0.0f, 0.0f }, { 1.0f, 0.0f } });
            ASSERT_FALSE(result9.has_value());
        }

        test_section("intersects(const Segment2&)");
        {
            constexpr auto result = tri1.intersects(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } });
            ASSERT(result);
            ASSERT(tri2.intersects(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }));
            ASSERT(tri1.intersects(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }))
            ASSERT(tri2.intersects(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } }))
            ASSERT_FALSE(tri1.intersects(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }));
            ASSERT_FALSE(tri2.intersects(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }));
            ASSERT(tri1.intersects(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }));
            ASSERT(tri2.intersects(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } }));
            ASSERT(tri1.intersects(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }));
            ASSERT(tri2.intersects(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } }));
        }

        test_section("intersections(const Segment2&)");
        {
            ASSERT_FALSE(tri1.intersections(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }).has_value());
            ASSERT_FALSE(tri2.intersections(nnm::Segment2f { { -3.0f, 0.0f }, { -1.0f, 2.0f } }).has_value());
            const auto result1 = tri1.intersections(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } });
            ASSERT(
                result1.has_value() && (*result1)[0].approx_equal({ -0.5f, 1.0f })
                && (*result1)[1].approx_equal({ -0.5f, 1.0f }));
            const auto result2 = tri2.intersections(nnm::Segment2f { { 2.0f, 2.0f }, { -3.0f, 0.0f } });
            ASSERT(
                result2.has_value() && (*result2)[0].approx_equal({ -0.5f, 1.0f })
                && (*result2)[1].approx_equal({ -0.5f, 1.0f }));
            ASSERT_FALSE(tri1.intersections(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }).has_value());
            ASSERT_FALSE(tri2.intersections(nnm::Segment2f { { 0.0f, 0.0f }, { 2.0f, 2.0f } }).has_value());
            const auto result3 = tri1.intersections(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } });
            ASSERT(
                result3.has_value() && (*result3)[0].approx_equal({ -1.0f, 0.0f })
                && (*result3)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result4 = tri2.intersections(nnm::Segment2f { { -1.0f, 0.0f }, { 2.0f, 2.0f } });
            ASSERT(
                result4.has_value() && (*result4)[0].approx_equal({ -1.0f, 0.0f })
                && (*result4)[1].approx_equal({ -1.0f, 0.0f }));
            const auto result5 = tri1.intersections(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } });
            ASSERT(
                result5.has_value() && (*result5)[0].approx_equal({ -3.7272727f, 0.36363636f })
                && (*result5)[1].approx_equal({ -0.33333333f, 1.3333333f }));
            const auto result6 = tri2.intersections(nnm::Segment2f { { -5.0f, 0.0f }, { 2.0f, 2.0f } });
            ASSERT(
                result6.has_value() && (*result6)[0].approx_equal({ -3.7272727f, 0.36363636f })
                && (*result6)[1].approx_equal({ -0.33333333f, 1.3333333f }));
        }

        test_section("approx_equilateral");
        {
            constexpr auto result = tri1.approx_equilateral();
            ASSERT_FALSE(result);
            constexpr nnm::Triangle2f tri3 { { 2.0f, -4.0f }, { 4.0f, -0.535898385f }, { 6.0f, -4.0f } };
            ASSERT(tri3.approx_equilateral());
            constexpr nnm::Triangle2f tri4 { { -4.0f, 4.0f }, { 4.0f, 4.0f }, { -4.0f, 8.0f } };
            ASSERT_FALSE(tri4.approx_equilateral());
        }

        test_section("approx_right");
        {
            ASSERT_FALSE(tri1.approx_right())
            constexpr nnm::Triangle2f tri3 { { 2.0f, -4.0f }, { 4.0f, -0.535898385f }, { 6.0f, -4.0f } };
            ASSERT_FALSE(tri3.approx_right());
            constexpr nnm::Triangle2f tri4 { { -4.0f, 4.0f }, { 4.0f, 4.0f }, { -4.0f, 8.0f } };
            ASSERT(tri4.approx_right());
        }
    }
}