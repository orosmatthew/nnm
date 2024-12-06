#pragma once

#include <nnm/geom3.hpp>

#include <algorithm>
#include <functional>

#include "test.hpp"

inline void geom3_tests()
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

        test_section("approx_parallel");
        {
            ASSERT(l1.approx_parallel(l1));
            ASSERT_FALSE(l1.approx_parallel(nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })));
            ASSERT(nnm::Line3f::axis_x().approx_parallel(nnm::Line3f::axis_x_offset(2.0f, -3.0f)));
        }

        test_section("approx_perpendicular");
        {
            ASSERT_FALSE(l1.approx_perpendicular(l1));
            ASSERT(nnm::Line3f::axis_x().approx_perpendicular(nnm::Line3f::axis_y_offset(2.0f, -3.0f)));
            ASSERT(nnm::Line3f::axis_z_offset(10.0f, -20.0f).approx_perpendicular(nnm::Line3f::axis_y()));
            ASSERT(
                nnm::Line3f::from_points({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
                    .approx_perpendicular(nnm::Line3f::from_points({ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
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
            const auto r1 = l1.rotate_axis_angle_at({ 5.0f, 6.0f, -7.0f }, { 1.0f, 0.0f, 0.0f }, nnm::pi() / 4.0f);
            ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_axis_angle");
        {
            const auto r1 = l1.rotate_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi() / 4.0f);
            ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion_at");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi() / 4.0f);
            const auto r1 = l1.rotate_quaternion_at({ 5.0f, 6.0f, -7.0f }, q1);
            ASSERT(r1.approx_equal({ { 1.0f, -6.72792244f, -5.58578634f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("rotate_quaternion");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi() / 4.0f);
            const auto r1 = l1.rotate_quaternion(q1);
            ASSERT(r1.approx_equal({ { 1.0f, -3.5355f, 0.7071f }, { 0.577350318f, -0.816496611f, 0.0f } }));
        }

        test_section("shear_x_at");
        {
            const auto s1 = l1.shear_x_at({ 5.0f, 6.0f, -7.0f }, nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { -10.5858f, -2.0f, 3.0f }, { -0.210089f, -0.691326f, 0.69132f } }));
        }

        test_section("shear_x");
        {
            const auto s1 = l1.shear_x(nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { -2.18514f, -2.0f, 3.0f }, { -0.210089f, -0.691326f, 0.69132f } }));
        }

        test_section("shear_y_at");
        {
            const auto s1 = l1.shear_y_at({ 5.0f, 6.0f, -7.0f }, nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { 1.0f, -10.6796f, 3.0f }, { 0.605908f, -0.515511f, 0.605908f } }));
        }

        test_section("shear_y");
        {
            const auto s1 = l1.shear_y(nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { 1.0f, -3.00551f, 3.0f }, { 0.605908f, -0.515511f, 0.605908f } }));
        }

        test_section("shear_z_at");
        {
            const auto s1 = l1.shear_z_at({ 5.0f, 6.0f, -7.0f }, nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { 1.0f, -2.0f, 4.7126f }, { 0.369916f, -0.369916f, 0.852246f } }));
        }

        test_section("shear_z");
        {
            const auto s1 = l1.shear_z(nnm::pi() / 5.0f, -nnm::pi() / 6.0f);
            ASSERT(s1.approx_equal({ { 1.0f, -2.0f, 4.88124275f }, { 0.369916f, -0.369916f, 0.852246f } }));
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
    }
}
