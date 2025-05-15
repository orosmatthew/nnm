#pragma once

#include <nnm/geom3.hpp>

#include <functional>

#include "test.hpp"

// ReSharper disable CppDFATimeOver

inline void line3_tests()
{
    test_case("Line3");
    {
        test_section("Line3()");
        {
            constexpr nnm::Line3f l {};
            ASSERT(l.origin == nnm::Vector3f::zero());
            ASSERT(l.direction == nnm::Vector3f::axis_x());
        }

        test_section("Line3(const Vector3&, const Vector3&)");
        {
            constexpr nnm::Line3f l { { -1.0f, 2.0f, 3.0f }, { 5.0f, 6.0f, -7.0f } };
            ASSERT(l.origin == nnm::Vector3f(-1.0f, 2.0f, 3.0f));
            ASSERT(l.direction == nnm::Vector3f(5.0f, 6.0f, -7.0f));
        }

        test_section("from_points");
        {
            const auto l = nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { 4.0f, -5.0f, 7.0f });
            ASSERT(l.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(l.direction.approx_equal({ 0.5144957554f, -0.5144957554f, 0.6859943406f }));
        }

        test_section("from_ray");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f } };
            const auto l1 = nnm::Line3f::from_ray(r1);
            ASSERT(l1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(l1.direction.approx_equal({ -5.0f, 6.0f, -7.0f }));
        }

        test_section("axis_x");
        {
            constexpr auto l = nnm::Line3f::axis_x();
            ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
            ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
        }

        test_section("axis_y");
        {
            constexpr auto l = nnm::Line3f::axis_y();
            ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
            ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
        }

        test_section("axis_z");
        {
            constexpr auto l = nnm::Line3f::axis_z();
            ASSERT(l.origin.approx_equal({ 0.0f, 0.0f, 0.0f }));
            ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
        }

        test_section("axis_x_offset");
        {
            constexpr auto l = nnm::Line3f::axis_x_offset(-1.0f, 2.0f);
            ASSERT(l.origin.approx_equal({ 0.0f, -1.0f, 2.0f }));
            ASSERT(l.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
        }

        test_section("axis_y_offset");
        {
            constexpr auto l = nnm::Line3f::axis_y_offset(-1.0f, 2.0f);
            ASSERT(l.origin.approx_equal({ -1.0f, 0.0f, 2.0f }));
            ASSERT(l.direction.approx_equal({ 0.0f, 1.0f, 0.0f }));
        }

        test_section("axis_z_offset");
        {
            constexpr auto l = nnm::Line3f::axis_z_offset(-1.0f, 2.0f);
            ASSERT(l.origin.approx_equal({ -1.0f, 2.0f, 0.0f }));
            ASSERT(l.direction.approx_equal({ 0.0f, 0.0f, 1.0f }));
        }

        constexpr nnm::Line3f l1 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

        test_section("parallel_containing");
        {
            constexpr auto l = l1.parallel_containing({ -5.0f, 6.0f, -7.0f });
            ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
            ASSERT(l.direction.approx_equal(l1.direction));
        }

        test_section("arbitrary_perpendicular_containing");
        {
            constexpr auto l = l1.arbitrary_perpendicular_containing({ -5.0f, 6.0f, -7.0f });
            ASSERT(l.origin.approx_equal({ -5.0f, 6.0f, -7.0f }));
            ASSERT(l.direction.approx_perpendicular(l1.direction));
        }

        test_section("normalize");
        {
            const auto l = nnm::Line3f { { 1.0f, -2.0f, 3.0f }, { 1.0f, -1.0f, 1.0f } }.normalize();
            ASSERT(l.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(l.direction.approx_equal({ 0.5773502692f, -0.5773502692f, 0.5773502692f }));
        }

        test_section("approx_collinear(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            ASSERT(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f }).approx_collinear(r1));
            ASSERT_FALSE(nnm::Line3f::axis_x().approx_collinear(r1));
        }

        test_section("approx_contains");
        {
            ASSERT_FALSE(l1.approx_contains({ 0.0f, 0.0f, 0.0f }));
            ASSERT(l1.approx_contains({ -2.0f, 1.0f, 0.0f }));
            ASSERT(l1.approx_contains({ -0.8f, -0.2f, 1.2f }));
            ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_contains({ 0.0f, 0.0f, 0.0f }));
        }

        test_section("distance(const Vector3&)");
        {
            const auto d1 = l1.distance({ 0.0f, 0.0f, 0.0f });
            ASSERT(nnm::approx_equal(d1, 1.41421342f));
            const auto d2 = l1.distance({ -2.0f, 1.0f, 0.0f });
            ASSERT(nnm::approx_zero(d2));
        }

        test_section("distance(const Line3&)");
        {
            const auto d1 = l1.distance(nnm::Line3f::axis_z());
            ASSERT(nnm::approx_equal(d1, 0.7071067812f));
            const auto d2 = nnm::Line3f::axis_x().distance(nnm::Line3f::axis_x_offset(1.0f, 1.0f));
            ASSERT(nnm::approx_equal(d2, 1.4142135624f));
            const auto d3 = l1.distance(nnm::Line3f::axis_x());
            ASSERT(nnm::approx_equal(d3, 0.7071067812f));
        }

        test_section("distance(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            const auto d1 = nnm::Line3f::axis_x().distance(r1);
            ASSERT(nnm::approx_equal(d1, 0.31234777f));
            const auto d2 = nnm::Line3f::axis_x_offset(-4.0f, 5.0f).distance(r1);
            ASSERT(nnm::approx_equal(d2, 2.82842708f));
            const auto d3 = nnm::Line3f::axis_z_offset(-2.0f, 2.0f).distance(r1);
            ASSERT(nnm::approx_zero(d3));
            const auto d4 = nnm::Line3f::from_ray(r1).distance(r1);
            ASSERT(nnm::approx_zero(d4));
        }

        test_section("approx_parallel(const Line3&)");
        {
            ASSERT(l1.approx_parallel(l1));
            ASSERT_FALSE(l1.approx_parallel(nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
            ASSERT(nnm::Line3f::axis_x().approx_parallel(nnm::Line3f::axis_x_offset(2.0f, -3.0f)));
        }

        test_section("approx_parallel(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            ASSERT_FALSE(nnm::Line3f::axis_x().approx_parallel(r1));
            ASSERT(nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f }).approx_parallel(r1));
        }

        test_section("approx_perpendicular(const Line3&)");
        {
            ASSERT_FALSE(l1.approx_perpendicular(l1));
            ASSERT(nnm::Line3f::axis_x().approx_perpendicular(nnm::Line3f::axis_y_offset(2.0f, -3.0f)));
            ASSERT(nnm::Line3f::axis_z_offset(10.0f, -20.0f).approx_perpendicular(nnm::Line3f::axis_y()));
            ASSERT(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                    .approx_perpendicular(nnm::Line3f::from_points({ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
        }

        test_section("approx_perpendicular(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            ASSERT_FALSE(nnm::Line3f::axis_x().approx_perpendicular(r1));
            ASSERT(nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f }).approx_perpendicular(r1));
        }

        test_section("approx_intersects(const Line3&)");
        {
            ASSERT(l1.approx_intersects(l1));
            ASSERT(l1.approx_intersects(nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f })));
            ASSERT_FALSE(l1.approx_intersects(nnm::Line3f::axis_z()));
            ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_intersects(nnm::Line3f::axis_x()));
            ASSERT_FALSE(l1.approx_intersects(nnm::Line3f::axis_x_offset(1.0f, -2.0f)));
            ASSERT(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                    .approx_intersects(nnm::Line3f::axis_x()));
        }

        test_section("approx_intersection(const Line3&)");
        {
            const auto i1 = l1.approx_intersection(l1);
            ASSERT_FALSE(i1.has_value());
            const auto i2
                = l1.approx_intersection(nnm::Line3f::from_points({ 0.0f, 0.0f, 1.0f }, { -2.0f, 0.0f, 1.0f }));
            ASSERT(i2.has_value() && i2.value().approx_equal({ -1.0f, 0.0f, 1.0f }));
            const auto i3 = l1.approx_intersection(nnm::Line3f::axis_z());
            ASSERT_FALSE(i3.has_value());
            const auto i4 = nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_intersection(nnm::Line3f::axis_x());
            ASSERT_FALSE(i4.has_value());
            const auto i5 = l1.approx_intersection(nnm::Line3f::axis_x_offset(1.0f, -2.0f));
            ASSERT_FALSE(i5.has_value());
            const auto i6 = nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                                .approx_intersection(nnm::Line3f::axis_x());
            ASSERT(i6.has_value() && i6.value().approx_equal({ 0.0f, 0.0f, 0.0f }));
        }

        test_section("approx_intersects(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            ASSERT_FALSE(nnm::Line3f::axis_x().approx_intersects(r1));
            ASSERT(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }).approx_intersects(r1));
            ASSERT(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }).approx_intersects(r1));
            ASSERT_FALSE(
                nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }).approx_intersects(r1));
        }

        test_section("approx_intersection(const Ray3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
            const auto i1 = nnm::Line3f::axis_x().approx_intersection(r1);
            ASSERT_FALSE(i1.has_value());
            const auto i2
                = nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }).approx_intersection(r1);
            ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
            const auto i3
                = nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }).approx_intersection(r1);
            ASSERT_FALSE(i3.has_value());
            const auto i4
                = nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }).approx_intersection(r1);
            ASSERT_FALSE(i4.has_value());
        }

        test_section("project_point");
        {
            const auto p1 = l1.project_point({ 0.0f, 0.0f, 0.0f });
            ASSERT(p1.approx_equal({ -1.0f, 0.0f, 1.0f }));
            const auto p2 = l1.project_point({ 0.0f, -1.0f, 2.0f });
            ASSERT(p2.approx_equal({ 0.0f, -1.0f, 2.0f }));
        }

        test_section("approx_coincident");
        {
            ASSERT(l1.approx_coincident(l1));
            ASSERT_FALSE(l1.approx_coincident(nnm::Line3f::axis_x()));
            ASSERT_FALSE(nnm::Line3f::axis_y().approx_coincident(nnm::Line3f::axis_y_offset(1.0f, -2.0f)));
            ASSERT(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                    .approx_coincident(nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
        }

        test_section("translate");
        {
            const auto t1 = l1.translate({ 5.0f, 6.0f, -7.0f });
            ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, l1.direction }));
        }

        test_section("scale_at");
        {
            const auto s1 = l1.scale_at({ 5.0f, 6.0f, -7.0f }, { 0.5f, -2.0f, 3.0f });
            ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
        }

        test_section("scale");
        {
            const auto s1 = l1.scale({ 0.5f, -2.0f, 3.0f });
            ASSERT(s1.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
        }

        test_section("rotate_axis_angle_at");
        {
            const auto r1
                = l1.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_axis_angle");
        {
            const auto r1 = l1.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion_at");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            const auto r1 = l1.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
            ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            const auto r1 = l1.rotate_quaternion(q1);
            ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("shear_x_at");
        {
            const auto s1 = l1.shear_x_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
        }

        test_section("shear_x");
        {
            const auto s1 = l1.shear_x(0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
        }

        test_section("shear_y_at");
        {
            const auto s1 = l1.shear_y_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
        }

        test_section("shear_y");
        {
            const auto s1 = l1.shear_y(0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
        }

        test_section("shear_z_at");
        {
            const auto s1 = l1.shear_z_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
        }

        test_section("shear_z");
        {
            const auto s1 = l1.shear_z(0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
        }

        test_section("approx_equal");
        {
            ASSERT(l1.approx_equal(l1));
            ASSERT_FALSE(l1.approx_equal(nnm::Line3f::axis_x()));
            ASSERT_FALSE(nnm::Line3f::axis_x_offset(1.0f, -2.0f).approx_equal(nnm::Line3f::axis_x()));
            ASSERT_FALSE(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                    .approx_equal(nnm::Line3f::from_points({ -1.0f, -1.0f, -1.0f }, { 2.0f, 2.0f, 2.0f })));
        }

        test_section("operator==");
        {
            ASSERT(l1 == l1);
            ASSERT_FALSE(l1 == nnm::Line3f::axis_x());
        }

        test_section("operator!=");
        {
            ASSERT(l1 != nnm::Line3f::axis_x());
            ASSERT_FALSE(l1 != l1);
        }

        test_section("operator<");
        {
            ASSERT(nnm::Line3f::axis_x() < l1);
            ASSERT_FALSE(l1 < l1);
            ASSERT_FALSE(l1 < nnm::Line3f::axis_x());
        }
    }
}

inline void ray3_tests()
{
    test_case("Ray3");
    {
        test_section("Ray3()");
        {
            constexpr nnm::Ray3f r1 {};
            ASSERT(r1.origin.approx_zero());
            ASSERT(r1.direction.approx_equal({ 1.0f, 0.0f, 0.0f }));
        }

        test_section("Ray3(const Vector3&, const Vector3&)");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
            ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(r1.direction.approx_equal({ -4.0f, 5.0f, -6.0f }));
        }

        test_section("from_point_to_point");
        {
            const auto r1 = nnm::Ray3f::from_point_to_point({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f });
            ASSERT(r1.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(r1.direction.approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
        }

        test_section("normalize");
        {
            constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -5.0f, 7.0f, -9.0f } };
            const auto r2 = r1.normalize();
            ASSERT(r2.origin.approx_equal({ 1.0f, -2.0f, 3.0f }));
            ASSERT(r2.direction.approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
        }

        constexpr nnm::Ray3f r1 { { 1.0f, -2.0f, 3.0f }, { -0.424264073f, 0.565685451f, -0.707106769f } };
        constexpr nnm::Ray3f r2 { { 1.0f, -2.0f, 3.0f }, { 0.5773502692f, -0.5773502692f, 0.5773502692f } };

        test_section("approx_collinear(const Vector3&)");
        {
            ASSERT(r1.approx_collinear({ -2.0f, 2.0f, -2.0f }));
            ASSERT_FALSE(r1.approx_collinear({ 0.0f, 0.0f, 0.0f }));
            ASSERT(r1.approx_collinear({ 4.0f, -6.0f, 8.0f }));
        }

        test_section("approx_collinear(const Line3&)");
        {
            ASSERT(r1.approx_collinear(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -5.0f, 6.0f, -7.0f })));
            ASSERT_FALSE(r1.approx_collinear(nnm::Line3f::axis_x()));
        }

        test_section("approx_collinear(const Ray3&)");
        {
            ASSERT(r1.approx_collinear(r1));
            ASSERT_FALSE(
                r1.approx_collinear(nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 10.0f, 20.0f, -0.5f })))
            ASSERT(r1.approx_collinear(
                nnm::Ray3f::from_point_to_point({ 4.0f, -6.0f, 8.0f }, { 5.8099f, -8.4132f, 11.0165f })));
            ASSERT(r1.approx_collinear(
                nnm::Ray3f::from_point_to_point({ 5.8099f, -8.4132f, 11.0165f }, { 4.0f, -6.0f, 8.0f })));
        }

        test_section("approx_contains");
        {
            ASSERT(r1.approx_contains({ -0.2f, -0.4f, 1.0f }));
            ASSERT(r1.approx_contains({ -2.0f, 2.0f, -2.0f }));
            ASSERT_FALSE(r1.approx_contains({ 0.0f, 0.0f, 0.0f }));
            ASSERT_FALSE(r1.approx_contains({ 1.54f, -2.72f, 3.9f }));
        }

        test_section("distance(const Vector3&)");
        {
            const auto d1 = r1.distance({ 0.0f, 0.0f, 0.0f });
            ASSERT(nnm::approx_equal(d1, 0.692820311f));
            const auto d2 = r1.distance({ -2.0f, 2.0f, -2.0f });
            ASSERT(nnm::approx_zero(d2));
            const auto d3 = r1.distance({ 4.0f, -6.0f, 8.0f });
            ASSERT(nnm::approx_equal(d3, 7.0711f));
            const auto d4 = r1.distance({ 4.0f, -5.0f, 9.0f });
            ASSERT(nnm::approx_equal(d4, 7.3485f));
        }

        test_section("distance(const Line3&)");
        {
            const auto d1 = r1.distance(nnm::Line3f::axis_x());
            ASSERT(nnm::approx_equal(d1, 0.31234777f));
            const auto d2 = r1.distance(nnm::Line3f::axis_x_offset(-4.0f, 5.0f));
            ASSERT(nnm::approx_equal(d2, 2.82842708f));
            const auto d3 = r1.distance(nnm::Line3f::axis_z_offset(-2.0f, 2.0f));
            ASSERT(nnm::approx_zero(d3));
            const auto d4 = r1.distance(nnm::Line3f::from_ray(r1));
            ASSERT(nnm::approx_zero(d4));
        }

        test_section("distance(const Ray3&)");
        {
            const auto d1 = r1.distance(r1);
            ASSERT(nnm::approx_zero(d1));
            const auto d2 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d2, 0.692820311f));
            const auto d3 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }).distance(r1);
            ASSERT(nnm::approx_equal(d3, 0.692820311f));
            const auto d4 = r1.distance(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d4, 0.31234777f));
            const auto d5 = nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }).distance(r1);
            ASSERT(nnm::approx_equal(d5, 0.31234777f));
            const auto d6 = r1.distance(nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }));
            ASSERT(nnm::approx_equal(d6, 3.4641f));
            const auto d7 = nnm::Ray3f::from_point_to_point({ 3.0f, -4.0f, 5.0f }, { 4.0f, -4.0f, 5.0f }).distance(r1);
            ASSERT(nnm::approx_equal(d7, 3.4641f));
            const auto d8 = r1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }));
            ASSERT(nnm::approx_equal(d8, 2.4495f));
            const auto d9 = nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { 8.0f, -8.0f, 10.0f }).distance(r1);
            ASSERT(nnm::approx_equal(d9, 2.4495f));
        }

        test_section("project_point");
        {
            const auto p1 = r1.project_point({ 2.0f, 0.0f, 0.0f });
            ASSERT(p1.approx_equal({ -0.2f, -0.4f, 1.0f }));
            const auto p2 = r1.project_point({ 6.0f, -4.0f, 6.0f });
            ASSERT(p2.approx_equal({ 1.0f, -2.0f, 3.0f }));
            const auto p3 = r1.project_point({ -2.0f, 2.0f, -2.0f });
            ASSERT(p3.approx_equal({ -2.0f, 2.0f, -2.0f }));
        }

        test_section("approx_parallel(const Line3&)");
        {
            ASSERT_FALSE(r1.approx_parallel(nnm::Line3f::axis_x()));
            ASSERT(r1.approx_parallel(nnm::Line3f::from_points({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
        }

        test_section("approx_parallel(const Ray3&)");
        {
            ASSERT_FALSE(
                r1.approx_parallel(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
            ASSERT(r1.approx_parallel(nnm::Ray3f::from_point_to_point({ 0.0f, 2.0f, -6.0f }, { 3.0f, -2.0f, -1.0f })));
        }

        test_section("approx_perpendicular(const Line3&)");
        {
            ASSERT_FALSE(r1.approx_perpendicular(nnm::Line3f::axis_x()));
            ASSERT(r1.approx_perpendicular(nnm::Line3f::from_points({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
        }

        test_section("approx_perpendicular(const Ray3&)");
        {
            ASSERT_FALSE(
                r1.approx_perpendicular(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
            ASSERT(
                r1.approx_perpendicular(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 3.0f }, { -0.2f, -0.4f, 4.0f })));
        }

        test_section("approx_intersects(const Line3&)");
        {
            ASSERT_FALSE(r1.approx_intersects(nnm::Line3f::axis_x()));
            ASSERT(r1.approx_intersects(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f })));
            ASSERT(r1.approx_intersects(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f })));
            ASSERT_FALSE(
                r1.approx_intersects(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f })));
        }

        test_section("approx_intersection(const Line3&)");
        {
            const auto i1 = r1.approx_intersection(nnm::Line3f::axis_x());
            ASSERT_FALSE(i1.has_value());
            const auto i2
                = r1.approx_intersection(nnm::Line3f::from_points({ -0.2f, -0.4f, 1.0f }, { 2.0f, 0.0f, 0.0f }));
            ASSERT(i2.has_value() && i2.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
            const auto i3
                = r1.approx_intersection(nnm::Line3f::from_points({ -2.0f, 2.0f, -2.0f }, { -0.2f, -0.4f, 1.0f }));
            ASSERT_FALSE(i3.has_value());
            const auto i4
                = r1.approx_intersection(nnm::Line3f::from_points({ 1.54f, -2.72f, 3.9f }, { -2.0f, -4.0f, 5.0f }));
            ASSERT_FALSE(i4.has_value());
        }

        test_section("approx_intersects(const Ray3&)");
        {
            ASSERT(r1.approx_intersects(r1));
            ASSERT_FALSE(
                r1.approx_intersects(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
            ASSERT(r1.approx_intersects(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f })));
            ASSERT_FALSE(
                r1.approx_intersects(nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f })));
        }

        test_section("approx_intersection(const Ray3&)");
        {
            const auto i1 = r1.approx_intersection(r1);
            ASSERT_FALSE(i1.has_value());
            const auto i2
                = r1.approx_intersection(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
            ASSERT_FALSE(i2.has_value());
            const auto i3
                = r1.approx_intersection(nnm::Ray3f::from_point_to_point({ 2.0f, 0.0f, 0.0f }, { -0.2f, -0.4f, 1.0f }));
            ASSERT(i3.has_value() && i3.value().approx_equal({ -0.2f, -0.4f, 1.0f }));
            const auto i4 = r1.approx_intersection(
                nnm::Ray3f::from_point_to_point({ -2.0f, -4.0f, 5.0f }, { 1.54f, -2.72f, 3.9f }));
            ASSERT_FALSE(i4.has_value());
        }

        test_section("translate");
        {
            const auto t1 = r2.translate({ 5.0f, 6.0f, -7.0f });
            ASSERT(t1.approx_equal({ { 6.0f, 4.0f, -4.0f }, r2.direction }));
        }

        test_section("scale_at");
        {
            const auto s1 = r2.scale_at({ 5.0f, 6.0f, -7.0f }, { 0.5f, -2.0f, 3.0f });
            ASSERT(s1.approx_equal({ { 3.0f, 22.0f, 23.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
        }

        test_section("scale");
        {
            const auto s1 = r2.scale({ 0.5f, -2.0f, 3.0f });
            ASSERT(s1.approx_equal({ { 0.5f, 4.0f, 9.0f }, { 0.137361f, 0.549442f, 0.824163f } }));
        }

        test_section("rotate_axis_angle_at");
        {
            const auto r1r
                = r2.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(r1r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_axis_angle");
        {
            const auto r1r = r2.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(r1r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion_at");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            const auto r = r2.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
            ASSERT(r.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            const auto r = r2.rotate_quaternion(q1);
            ASSERT(r.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("shear_x_at");
        {
            const auto s1 = r2.shear_x_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 1.0f, -4.0f, 5.0f }, { 0.816497f, -0.408248f, 0.408248f } }));
        }

        test_section("shear_x");
        {
            const auto s1 = r2.shear_x(0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 1.0f, -1.5f, 2.5f }, { 0.816497f, -0.408248f, 0.408248f } }));
        }

        test_section("shear_y_at");
        {
            const auto s1 = r2.shear_y_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { -3.0f, -2.0f, 7.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
        }

        test_section("shear_y");
        {
            const auto s1 = r2.shear_y(0.5, -0.5f);
            ASSERT(s1.approx_equal({ { 0.0f, -2.0f, 4.0f }, { 0.267261f, -0.534522f, 0.801784f } }));
        }

        test_section("shear_z_at");
        {
            const auto s1 = r2.shear_z_at({ 5.0f, 6.0f, -7.0f }, 0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 6.0f, -7.0f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
        }

        test_section("shear_z");
        {
            const auto s1 = r2.shear_z(0.5f, -0.5f);
            ASSERT(s1.approx_equal({ { 2.5f, -3.5f, 3.0f }, { 0.639602f, -0.639602f, 0.426401f } }));
        }

        test_section("approx_equal");
        {
            ASSERT(r1.approx_equal(r1));
            ASSERT(r2.approx_equal(r2));
            ASSERT_FALSE(r1.approx_equal(r2));
            ASSERT_FALSE(r2.approx_equal(r1));
        }

        test_section("operator=");
        {
            ASSERT(r1 == r1);
            ASSERT(r2 == r2);
            ASSERT_FALSE(r1 == r2);
            ASSERT_FALSE(r2 == r1);
        }

        test_section("operator!=");
        {
            ASSERT(r1 != r2);
            ASSERT(r2 != r1);
            ASSERT_FALSE(r1 != r1);
            ASSERT_FALSE(r2 != r2);
        }

        test_section("operator<");
        {
            ASSERT_FALSE(r1 < r1);
            ASSERT(r1 < r2);
            ASSERT_FALSE(r2 < r1);
        }
    }
}

inline void segment3_tests()
{
    test_case("Segment3");
    {
        test_section("Segment3()");
        {
            constexpr nnm::Segment3f s {};
            ASSERT(s.start == nnm::Vector3f::zero());
            ASSERT(s.end == nnm::Vector3f::axis_x());
        }

        test_section("Segment3(const Vector3&, const Vector3&)");
        {
            constexpr nnm::Segment3f s { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };
            ASSERT(s.start == nnm::Vector3f(1.0f, -2.0f, 3.0f));
            ASSERT(s.end == nnm::Vector3f(-4.0f, 5.0f, -6.0f));
        }

        constexpr nnm::Segment3f s1 { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f } };

        test_section("approx_collinear(const Vector3&)");
        {
            ASSERT(s1.approx_collinear({ 2.9833236933f, -4.7766531707f, 6.569982648f }));
            ASSERT_FALSE(s1.approx_collinear({ 0.0f, 0.0f, 0.0f }));
            ASSERT(s1.approx_collinear({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
            ASSERT(s1.approx_collinear({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
        }

        test_section("approx_collinear(const Line3&)");
        {
            ASSERT_FALSE(s1.approx_collinear(nnm::Line3f::axis_x()));
            ASSERT_FALSE(s1.approx_collinear(nnm::Line3f::from_points({ 2.0f, -1.0f, 4.0f }, { -3.0f, 6.0f, -5.0f })));
            ASSERT(s1.approx_collinear(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })));
            ASSERT(s1.approx_collinear(nnm::Line3f::from_points({ -4.0f, 5.0f, -6.0f }, { 1.0f, -2.0f, 3.0f })));
        }

        test_section("approx_collinear(const Ray3&)");
        {
            ASSERT_FALSE(
                s1.approx_collinear(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, s1.end.direction(s1.start))));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ 2.9833236933f, -4.7766531707f, 6.569982648f }, s1.start.direction(s1.end))));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.end.direction(s1.start))));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ -1.4205585602f, 1.3887819843f, -1.3570054084f }, s1.start.direction(s1.end))));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.end.direction(s1.start))));
            ASSERT(s1.approx_collinear(
                nnm::Ray3f({ -6.1127619882f, 7.9578667834f, -9.8029715787f }, s1.start.direction(s1.end))));
        }

        test_section("approx_collinear(const Segment3&)");
        {
            ASSERT_FALSE(s1.approx_collinear(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f })));
            ASSERT(s1.approx_collinear(s1));
            ASSERT(s1.approx_collinear(
                nnm::Segment3f(
                    { 2.9833236933f, -4.7766531707f, 6.569982648f },
                    { 4.5074673515f, -6.9104542922f, 9.3134412328f })));
            ASSERT(s1.approx_collinear(
                nnm::Segment3f(
                    { -6.1127619882f, 7.9578667834f, -9.8029715787f },
                    { -9.0362240787f, 12.0507137102f, -15.0652033417f })));
            ASSERT_FALSE(s1.approx_collinear(nnm::Segment3f({ 0.0f, -3.0f, 2.0f }, { -5.0f, 4.0f, -7.0f })))
        }

        test_section("approx_contains(const Vector3&)");
        {
            ASSERT_FALSE(s1.approx_contains({ 0.0f, 0.0f, 0.0f }));
            ASSERT_FALSE(s1.approx_contains({ 2.9833236933f, -4.7766531707f, 6.569982648f }));
            ASSERT(s1.approx_contains({ -1.4205585602f, 1.3887819843f, -1.3570054084f }));
            ASSERT_FALSE(s1.approx_contains({ -6.1127619882f, 7.9578667834f, -9.8029715787f }));
        }

        test_section("distance(const Vector3&)");
        {
            const auto d1 = s1.distance({ 0.0f, 0.0f, 0.0f });
            ASSERT(nnm::approx_equal(d1, 0.5902432522f));
            const auto d2 = s1.distance({ -5.0f, 7.0f, -7.0f });
            ASSERT(nnm::approx_equal(d2, 2.4494897428f));
            const auto d3 = s1.distance({ 0.0f, -5.0f, 3.0f });
            ASSERT(nnm::approx_equal(d3, 3.1622776602f));
            const auto d4 = s1.distance({ -1.4205585602f, 1.3887819843f, -1.3570054084f });
            ASSERT(nnm::approx_zero(d4));
        }

        test_section("distance(const Line3&)");
        {
            const auto d1 = s1.distance(nnm::Line3f::axis_x());
            ASSERT(nnm::approx_equal(d1, 0.263117403f));
            const auto d2 = s1.distance(nnm::Line3f({ -6.0f, -4.0f, 7.0f }, { 1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d2, 4.472135955f));
            const auto d3 = s1.distance(nnm::Line3f({ -6.0f, 7.0f, -7.0f }, { 0.0f, 0.0f, -1.0f }));
            ASSERT(nnm::approx_equal(d3, 2.8284271247f));
        }

        test_section("distance(const Ray3&)");
        {
            const auto d1 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d1, 0.5902432522f));
            const auto d2 = s1.distance(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d2, 0.263117403f));
            const auto d3 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 3.0f, -5.0f, 4.0f }));
            ASSERT(nnm::approx_equal(d3, 2.2360679775f));
            const auto d4 = s1.distance(nnm::Ray3f::from_point_to_point({ 2.0f, -4.0f, 3.0f }, { 1.0f, -3.0f, 2.0f }));
            ASSERT(nnm::approx_equal(d4, 1.2247448f));
            const auto d5
                = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -6.0f, 9.0f, -7.0f }));
            ASSERT(nnm::approx_equal(d5, 2.4494897428f));
            const auto d6
                = s1.distance(nnm::Ray3f::from_point_to_point({ -5.0f, 7.0f, -7.0f }, { -1.0f, 2.0f, -2.0f }));
            ASSERT(nnm::approx_equal(d6, 0.593442202f));
            const auto d7 = s1.distance(
                nnm::Ray3f::from_point_to_point(
                    { 0.0f, 0.0f, 0.0f }, { -1.3814812713f, 1.3340737798f, -1.2866662883f }));
            ASSERT(nnm::approx_zero(d7));
        }

        test_section("distance(const Segment3&)");
        {
            const auto d1 = s1.distance(s1);
            ASSERT(nnm::approx_zero(d1));
            const auto d2 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d2, 0.5902432522f));
            const auto d3 = s1.distance(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d3, 0.263117403f));
            const auto d4 = s1.distance(nnm::Segment3f({ -2.0f, 0.0f, 0.0f }, { -8.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_equal(d4, 1.3295645661f));
            const auto d5 = s1.distance(nnm::Segment3f({ 4.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
            ASSERT(nnm::approx_equal(d5, 4.6904157598f));
            const auto d6 = s1.distance(nnm::Segment3f({ -5.0f, -4.0f, 6.0f }, { 5.0f, -4.0f, 6.0f }));
            ASSERT(nnm::approx_equal(d6, 3.6055512755f));
            const auto d7 = s1.distance(nnm::Segment3f({ -3.0f, -4.0f, 6.0f }, { -5.0f, -4.0f, 6.0f }));
            ASSERT(nnm::approx_equal(d7, 5.3851648071f));
            const auto d8 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -2.0f }, { -5.0f, 7.0f, -1.0f }));
            ASSERT(nnm::approx_equal(d8, 4.582575695f));
            const auto d9 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -10.0f }, { -5.0f, 7.0f, -1.0f }));
            ASSERT(nnm::approx_equal(d9, 2.2360679775f));
            const auto d10 = s1.distance(nnm::Segment3f({ -5.0f, 7.0f, -8.0f }, { -5.0f, 7.0f, -9.0f }));
            ASSERT(nnm::approx_equal(d10, 3.0f));
            const auto d11
                = s1.distance(nnm::Segment3f({ 1.3429285263f, 1.4817304819f, -0.7047254731f }, { -2.0f, 0.0f, 0.0f }));
            ASSERT(nnm::approx_zero(d11));
        }

        test_section("direction_unnormalized");
        {
            ASSERT(s1.direction_unnormalized().approx_equal({ -5.0f, 7.0f, -9.0f }));
        }

        test_section("direction");
        {
            ASSERT(s1.direction().approx_equal({ -0.4016096645f, 0.5622535302f, -0.7228973960f }));
        }

        test_section("approx_parallel(const Line3&)");
        {
            ASSERT_FALSE(s1.approx_parallel(nnm::Line3f::axis_x()));
            ASSERT(s1.approx_parallel(nnm::Line3f::from_points({ 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f })))
            ASSERT(s1.approx_parallel(nnm::Line3f::from_points({ 3.0f, 0.0f, 5.0f }, { -2.0f, 7.0f, -4.0f })))
        }

        test_section("approx_parallel(const Ray3&)");
        {
            ASSERT_FALSE(s1.approx_parallel(nnm::Ray3f({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
            ASSERT(s1.approx_parallel(nnm::Ray3f::from_point_to_point(s1.start, s1.end)));
            ASSERT(s1.approx_parallel(nnm::Ray3f(s1.start + nnm::Vector3f(2.0f, -3.0f, 10.0f), -s1.direction())));
        }

        test_section("approx_parallel(const Segment3&)");
        {
            ASSERT_FALSE(s1.approx_parallel(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, -2.0f })));
            ASSERT(s1.approx_parallel(s1));
            ASSERT(s1.approx_parallel(
                nnm::Segment3f(
                    s1.start + nnm::Vector3f(2.0f, -2.0f, 5.0f), s1.end + nnm::Vector3f(2.0f, -2.0f, 5.0f))));
        }

        test_section("approx_perpendicular(const Line3&)");
        {
            ASSERT_FALSE(s1.approx_perpendicular(nnm::Line3f::axis_x()));
            ASSERT(s1.approx_perpendicular(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
        }

        test_section("approx_perpendicular(const Ray3&)");
        {
            ASSERT_FALSE(s1.approx_perpendicular(
                nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, -1.0f, -1.0f })));
            const auto r1 = nnm::Ray3f::from_point_to_point(
                { 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f });
            ASSERT(s1.approx_perpendicular(r1));
            ASSERT(s1.approx_perpendicular(nnm::Ray3f(r1.origin, -r1.direction)));
        }

        test_section("approx_perpendicular(const Segment3&)");
        {
            ASSERT_FALSE(s1.approx_perpendicular(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
            ASSERT(s1.approx_perpendicular(
                nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.1918502675f, 0.1906960428f, 0.8104581819f })));
            ASSERT(s1.approx_perpendicular(
                nnm::Segment3f({ -1.1918502675f, 0.1906960428f, 0.8104581819f }, { 0.0f, 0.0f, 0.0f })));
        }

        test_section("approx_intersects(const Line3&)");
        {
            ASSERT_FALSE(s1.approx_intersects(nnm::Line3f::axis_x()));
            ASSERT(s1.approx_intersects(nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f })));
            ASSERT(s1.approx_intersects(nnm::Line3f(s1.start, s1.direction())));
        }

        test_section("approx_intersection(const Line3&)");
        {
            const auto i1 = s1.approx_intersection(nnm::Line3f::axis_x());
            ASSERT_FALSE(i1.has_value());
            const auto i2
                = s1.approx_intersection(nnm::Line3f::from_points({ 1, 2, 3 }, { -0.666667f, -3.0476f, 0.0f }));
            ASSERT(i2.has_value() && i2.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
            const auto i3 = s1.approx_intersection(
                nnm::Line3f::from_points({ -6.3161401722f, -5.0466531233f, 6.9171254442f }, { 5.0f, -2.0f, 3.0f }));
            ASSERT_FALSE(i3.has_value());
            const auto i4 = s1.approx_intersection(
                nnm::Line3f::from_points({ 6.340530911f, 6.2880512604f, -11.4095884147f }, { -7.0f, 5.0f, -5.0f }));
            ASSERT_FALSE(i4.has_value());
            const auto i5 = s1.approx_intersection(nnm::Line3f(s1.start, s1.direction()));
            ASSERT_FALSE(i5.has_value());
        }

        test_section("approx_intersects(const Ray3&)");
        {
            ASSERT_FALSE(
                s1.approx_intersects(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f })));
            ASSERT(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f })));
            ASSERT(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { 3.1803758203f, -5.0525261484f, 6.9246764765f },
                    { 2.2353232409f, -3.7294525373f, 5.2235818337f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Ray3f::from_point_to_point(
                    { 2.2353232409f, -3.7294525373f, 5.2235818337f },
                    { 3.1803758203f, -5.0525261484f, 6.9246764765f })));
        }

        test_section("approx_intersection(const Ray3&)");
        {
            const auto i1
                = s1.approx_intersection(nnm::Ray3f::from_point_to_point({ 0.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }));
            ASSERT_FALSE(i1.has_value());
            const auto i2 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point({ 1.0f, 2.0f, 3.0f }, { 2.0323377426f, 5.126508592f, 4.8582079368f }));
            ASSERT_FALSE(i2.has_value());
            const auto i3 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point({ 2.0323377426f, 5.126508592f, 4.8582079368f }, { 1.0f, 2.0f, 3.0f }));
            ASSERT(i3.has_value() && i3.value().approx_equal({ 0.0967741935f, -0.735483871f, 1.3741935484f }));
            const auto i4 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { 5.0f, -2.0f, 3.0f }, { 8.4624090164f, -1.0678129571f, 1.801473802f }));
            ASSERT_FALSE(i4.has_value());
            const auto i5 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { 8.4624090164f, -1.0678129571f, 1.801473802f }, { 5.0f, -2.0f, 3.0f }));
            ASSERT_FALSE(i5.has_value());
            const auto i6 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { -7.0f, 5.0f, -5.0f }, { -10.7888017215f, 4.6341846614f, -3.1796331959f }));
            ASSERT_FALSE(i6.has_value());
            const auto i7 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { -10.7888017215f, 4.6341846614f, -3.1796331959f }, { -7.0f, 5.0f, -5.0f }));
            ASSERT_FALSE(i7.has_value());
            const auto i8 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { 3.1803758203f, -5.0525261484f, 6.9246764765f },
                    { 2.2353232409f, -3.7294525373f, 5.2235818337f }));
            ASSERT_FALSE(i8.has_value());
            const auto i9 = s1.approx_intersection(
                nnm::Ray3f::from_point_to_point(
                    { 2.2353232409f, -3.7294525373f, 5.2235818337f },
                    { 3.1803758203f, -5.0525261484f, 6.9246764765f }));
            ASSERT_FALSE(i9.has_value());
        }

        test_section("approx_intersects(const Segment3&)");
        {
            ASSERT_FALSE(s1.approx_intersects(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f })));
            ASSERT(s1.approx_intersects(s1));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f))));
            ASSERT(s1.approx_intersects(
                nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f(
                    { -1.3947151596f, 0.2231544255f, 0.9484063085f },
                    { -2.477689579f, 0.3964303326f, 1.6848289137f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f(
                    { 2.9228521743f, -3.1715789131f, 4.9407197828f },
                    { 4.4763315545f, -2.5022944544f, 4.8928270762f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f(
                    { -4.3190323788f, 3.7446637121f, -8.843567106f },
                    { -4.5930027693f, 5.0543673254f, -8.1018537201f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f })));
            ASSERT_FALSE(s1.approx_intersects(
                nnm::Segment3f(
                    { -2.8239641345f, 2.3324335277f, -6.0781648164f },
                    { -3.5475337817f, 1.7462055396f, -10.8183445985f })));
        }

        test_section("approx_intersection(const Segment3&");
        {
            const auto i1 = s1.approx_intersection(nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }));
            ASSERT_FALSE(i1.has_value());
            const auto i2 = s1.approx_intersection(s1);
            ASSERT_FALSE(i2.has_value());
            const auto i3 = s1.approx_intersection(
                nnm::Segment3f(s1.start + nnm::Vector3f(1.0f, 1.0f, 1.0f), s1.end + nnm::Vector3f(1.0f, 1.0f, 1.0f)));
            ASSERT_FALSE(i3.has_value());
            const auto i4 = s1.approx_intersection(
                nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { -1.3947151596f, 0.2231544255f, 0.9484063085f }));
            ASSERT(i4.has_value() && i4.value().approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }));
            const auto i5 = s1.approx_intersection(
                nnm::Segment3f({ 0.0f, 0.0f, 0.0f }, { 0.8903860212f, -0.1424617634f, -0.6054624944f }));
            ASSERT_FALSE(i5.has_value());
            const auto i6 = s1.approx_intersection(
                nnm::Segment3f(
                    { -1.3947151596f, 0.2231544255f, 0.9484063085f }, { -2.477689579f, 0.3964303326f, 1.6848289137f }));
            ASSERT_FALSE(i6.has_value());
            const auto i7 = s1.approx_intersection(
                nnm::Segment3f(
                    { 2.9228521743f, -3.1715789131f, 4.9407197828f },
                    { 4.4763315545f, -2.5022944544f, 4.8928270762f }));
            ASSERT_FALSE(i7.has_value());
            const auto i8 = s1.approx_intersection(
                nnm::Segment3f({ 2.9228521743f, -3.1715789131f, 4.9407197828f }, { 1.0f, -4.0f, 5.0f }));
            ASSERT_FALSE(i8.has_value());
            const auto i9 = s1.approx_intersection(
                nnm::Segment3f({ 1.0f, -4.0f, 5.0f }, { -0.2324762036f, -4.5309868797f, 5.0379963983f }));
            ASSERT_FALSE(i9.has_value());
            const auto i10 = s1.approx_intersection(
                nnm::Segment3f(
                    { -4.3190323788f, 3.7446637121f, -8.843567106f },
                    { -4.5930027693f, 5.0543673254f, -8.1018537201f }));
            ASSERT_FALSE(i10.has_value());
            const auto i11 = s1.approx_intersection(
                nnm::Segment3f({ -4.5930027693f, 5.0543673254f, -8.1018537201f }, { -5.0f, 7.0f, -7.0f }));
            ASSERT_FALSE(i11.has_value());
            const auto i12 = s1.approx_intersection(
                nnm::Segment3f({ -5.0f, 7.0f, -7.0f }, { -5.5960814905f, 9.8495418077f, -5.3862430547f }));
            ASSERT_FALSE(i12.has_value());
            const auto i13 = s1.approx_intersection(
                nnm::Segment3f({ -1.3071995174f, 3.5612991571f, 3.8583174565f }, { -2.0f, 3.0f, -0.6802903382f }));
            ASSERT_FALSE(i13.has_value());
            const auto i14 = s1.approx_intersection(
                nnm::Segment3f(
                    { -2.8239641345f, 2.3324335277f, -6.0781648164f },
                    { -3.5475337817f, 1.7462055396f, -10.8183445985f }));
            ASSERT_FALSE(i14.has_value());
        }

        test_section("project_point");
        {
            const auto p1 = s1.project_point({ 0.0f, 0.0f, 0.0f });
            ASSERT(p1.approx_equal({ -0.4838709677f, 0.0774193548f, 0.3290322581f }))
            const auto p2 = s1.project_point({ 2.0f, -3.0f, 4.0f });
            ASSERT(p2.approx_equal(s1.start));
            const auto p3 = s1.project_point({ -5.0f, 7.0f, -7.0f });
            ASSERT(p3.approx_equal(s1.end));
        }

        test_section("length_sqrd");
        {
            constexpr auto l = s1.length_sqrd();
            ASSERT(nnm::approx_equal(l, 155.0f));
        }

        test_section("length");
        {
            ASSERT(nnm::approx_equal(s1.length(), 12.449899598f));
        }

        test_section("midpoint");
        {
            ASSERT(s1.midpoint().approx_equal({ -1.5f, 1.5f, -1.5f }));
        }
    }
}

// ReSharper disable once CppDFATimeOver
inline void geom3_tests()
{
    line3_tests();
    ray3_tests();
    segment3_tests();
}
