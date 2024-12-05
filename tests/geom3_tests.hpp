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
    }
}
