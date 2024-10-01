#pragma once

#include <nnm/geom.hpp>

#include "test.hpp"

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

        constexpr nnm::Line2f line1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };

        test_section("parallel_containing");
        {
            constexpr nnm::Line2f line2 = line1.parallel_containing({ -6.0f, -5.0f });
            ASSERT(line2.approx_contains({ -6.0f, -5.0f }));
            ASSERT(line2.approx_parallel({ line1 }));
        }

        test_section("perpendicular_containing");
        {
            constexpr nnm::Line2f line2 = line1.perpendicular_containing({ -6.0f, -5.0f });
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

        test_section("approx_parallel");
        {
            constexpr auto result = line1.approx_parallel(line2);
            ASSERT_FALSE(result);
            ASSERT(line2.approx_parallel({ { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
            ASSERT(line2.approx_parallel({ { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
        }

        test_section("approx_perpendicular");
        {
            constexpr auto result = line1.approx_perpendicular(line2);
            ASSERT_FALSE(result);
            ASSERT(line2.approx_perpendicular({ { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
            ASSERT(line2.approx_perpendicular({ { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
        }

        test_section("unchecked_intersection");
        {
            constexpr auto result = line1.unchecked_intersection(line2);
            ASSERT(result.approx_equal({ 1.0f, -2.0f }));
        }

        test_section("intersection");
        {
            constexpr auto result = line1.intersection(line2);
            ASSERT(result.has_value());
            ASSERT(line1.intersection(line2).value().approx_equal({ 1.0f, -2.0f }));
            constexpr nnm::Line2f line3 { { 100.0f, -5.0f }, { -0.70710678f, -0.70710678f } };
            ASSERT_FALSE(line2.intersection(line3).has_value());
        }

        test_section("intersects");
        {
            constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray1.intersects(line3);
            ASSERT(result);
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray1.intersects(line4));
        }

        test_section("intersection");
        {
            constexpr nnm::Ray2f ray1 { { 1.0f, -2.0f }, { -0.384615391f, 0.923076928f } };
            constexpr nnm::Line2f line3 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray1.intersection(line3);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
            constexpr nnm::Line2f line4 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray1.intersection(line4).has_value());
        }

        test_section("project_point");
        {
            constexpr auto result = line1.project_point({ 5.0f, 3.0f });
            ASSERT(result.approx_equal({ -0.18343f, 0.84024f }));
        }

        test_section("unchecked_intercept_x");
        {
            constexpr auto result = line1.unchecked_intercept_x();
            ASSERT(nnm::approx_equal(result, 0.1666667f));
            ASSERT(nnm::approx_equal(line2.unchecked_intercept_x(), 3.0f));
        }

        test_section("intercept_x");
        {
            constexpr auto result = line1.intercept_x();
            ASSERT(result.has_value())
            ASSERT(nnm::approx_equal(result.value(), 0.1666667f));
            ASSERT(line2.intercept_x().has_value());
            ASSERT(nnm::approx_equal(line2.intercept_x().value(), 3.0f));
            constexpr nnm::Line2f line3 { { -20.0f, 27.0f }, { 1.0f, 0.0f } };
            ASSERT_FALSE(line3.intercept_x().has_value());
            constexpr nnm::Line2f line4 { { -20.0f, 27.0f }, { -1.0f, 0.0f } };
            ASSERT_FALSE(line4.intercept_x().has_value());
        }

        test_section("unchecked_intercept_y");
        {
            constexpr auto result = line1.unchecked_intercept_y();
            ASSERT(nnm::approx_equal(result, 0.4f));
            ASSERT(nnm::approx_equal(line2.unchecked_intercept_y(), -3.0f));
        }

        test_section("intercept_y");
        {
            constexpr auto result = line1.intercept_y();
            ASSERT(result.has_value())
            ASSERT(nnm::approx_equal(result.value(), 0.4f));
            ASSERT(line2.intercept_y().has_value());
            ASSERT(nnm::approx_equal(line2.intercept_y().value(), -3.0f));
            constexpr nnm::Line2f line3 { { -20.0f, 27.0f }, { 0.0f, 1.0f } };
            ASSERT_FALSE(line3.intercept_y().has_value());
            constexpr nnm::Line2f line4 { { -20.0f, 27.0f }, { 0.0f, -1.0f } };
            ASSERT_FALSE(line4.intercept_y().has_value());
        }

        test_section("approx_coincident");
        {
            constexpr auto result = line1.approx_coincident(line2);
            ASSERT_FALSE(result);
            constexpr nnm::Line2f line3 { { 0.0f, -3.0f }, { -0.70710678f, -0.70710678f } };
            ASSERT(line2.approx_coincident(line3));
        }

        constexpr nnm::Line2f line3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

        test_section("transform(const Basis2&)");
        {
            constexpr nnm::Basis2f basis { { { 1.0f, 2.0f }, { -3.0f, 4.0f } } };
            const nnm::Line2f result = line3.transform(basis);
            ASSERT(result.origin.approx_equal({ 6.0f, 2.0f }));
            ASSERT(result.direction.approx_equal({ -0.316227f, 0.948684f }));
        }

        test_section("transform_local(const Basis2&)");
        {
            constexpr nnm::Basis2f basis { { { 1.0f, 2.0f }, { -3.0f, 4.0f } } };
            const nnm::Line2f result = line3.transform_local(basis);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ -0.316227f, 0.948684f }));
        }

        test_section("transform(const Transform2&)");
        {
            constexpr nnm::Transform2f t { { { 1.0f, 2.0f, -3.0f }, { 4.0f, -10.0f, 0.0f }, { 1.0f, -2.0f, 9.0f } } };
            const nnm::Line2f result = line3.transform(t);
            ASSERT(result.origin.approx_equal({ 0.0f, 14.0f }));
            ASSERT(result.direction.approx_equal({ 0.529999f, -0.847998f }));
        }

        test_section("transform_local(const Transform2&)");
        {
            constexpr nnm::Transform2f t { { { 1.0f, 2.0f, -3.0f }, { 4.0f, -10.0f, 0.0f }, { 1.0f, -2.0f, 9.0f } } };
            const nnm::Line2f result = line3.transform_local(t);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.529999f, -0.847998f }));
        }

        test_section("translate");
        {
            const nnm::Line2f result = line3.translate({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
            ASSERT(result.direction.approx_equal(line3.direction));
        }

        test_section("scale");
        {
            const nnm::Line2f result = line3.scale({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("scale_local");
        {
            const nnm::Line2f result = line3.scale_local({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("shear_x");
        {
            const nnm::Line2f result = line3.shear_x(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 1.26794919f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_x_local");
        {
            const nnm::Line2f result = line3.shear_x_local(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_y");
        {
            const nnm::Line2f result = line3.shear_y(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -3.17963f }));
            ASSERT(result.direction.approx_equal({ 0.964585f, 0.263773f }));
        }

        test_section("shear_y_local");
        {
            const nnm::Line2f result = line3.shear_y_local(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
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

        test_section("distance");
        {
            ASSERT(nnm::approx_equal(ray2.distance({ 0.0f, 0.0f }), 3.0f));
            ASSERT(nnm::approx_equal(ray2.distance({ -3.0f, 5.0f }), 7.8102496759f));
            ASSERT(nnm::approx_equal(ray2.distance({ 5.0f, 0.0f }), 1.4142135624f));
        }

        test_section("approx_parallel");
        {
            constexpr auto result = ray1.approx_parallel(ray2);
            ASSERT_FALSE(result);
            ASSERT(ray2.approx_parallel({ { -100.0f, 20.0f }, { 0.70710678f, 0.70710678f } }));
            ASSERT(ray2.approx_parallel({ { -100.0f, 20.0f }, { -0.70710678f, -0.70710678f } }));
        }

        test_section("approx_perpendicular");
        {
            constexpr auto result = ray1.approx_perpendicular(ray2);
            ASSERT_FALSE(result);
            ASSERT(ray2.approx_perpendicular({ { -100.0f, 20.0f }, { -0.70710678f, 0.70710678f } }));
            ASSERT(ray2.approx_perpendicular({ { -100.0f, 20.0f }, { 0.70710678f, -0.70710678f } }));
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

        test_section("intersects(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray1.intersects(line1);
            ASSERT(result);
            constexpr nnm::Line2f line2 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray1.intersects(line2));
        }

        test_section("intersection(const Line2&)");
        {
            constexpr nnm::Line2f line1 { { 0.0, -2.0f }, { 0.70710678f, 0.70710678f } };
            constexpr auto result = ray1.intersection(line1);
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal({ 0.70588f, -1.29412f }));
            constexpr nnm::Line2f line2 { { 0.0, -4.0f }, { 0.70710678f, 0.70710678f } };
            ASSERT_FALSE(ray1.intersection(line2).has_value());
        }

        constexpr nnm::Ray2f ray3 { { 3.0f, -1.0f }, { 0.70710678f, 0.70710678f } };

        test_section("transform(const Basis2&)");
        {
            constexpr nnm::Basis2f basis { { { 1.0f, 2.0f }, { -3.0f, 4.0f } } };
            const nnm::Ray2f result = ray3.transform(basis);
            ASSERT(result.origin.approx_equal({ 6.0f, 2.0f }));
            ASSERT(result.direction.approx_equal({ -0.316227f, 0.948684f }));
        }

        test_section("transform_local(const Basis2&)");
        {
            constexpr nnm::Basis2f basis { { { 1.0f, 2.0f }, { -3.0f, 4.0f } } };
            const nnm::Ray2f result = ray3.transform_local(basis);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ -0.316227f, 0.948684f }));
        }

        test_section("transform(const Transform2&)");
        {
            constexpr nnm::Transform2f t { { { 1.0f, 2.0f, -3.0f }, { 4.0f, -10.0f, 0.0f }, { 1.0f, -2.0f, 9.0f } } };
            const nnm::Ray2f result = ray3.transform(t);
            ASSERT(result.origin.approx_equal({ 0.0f, 14.0f }));
            ASSERT(result.direction.approx_equal({ 0.529999f, -0.847998f }));
        }

        test_section("transform_local(const Transform2&)");
        {
            constexpr nnm::Transform2f t { { { 1.0f, 2.0f, -3.0f }, { 4.0f, -10.0f, 0.0f }, { 1.0f, -2.0f, 9.0f } } };
            const nnm::Ray2f result = ray3.transform_local(t);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.529999f, -0.847998f }));
        }

        test_section("translate");
        {
            const nnm::Ray2f result = ray3.translate({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 1.0f, 2.0f }));
            ASSERT(result.direction.approx_equal(ray3.direction));
        }

        test_section("scale");
        {
            const nnm::Ray2f result = ray3.scale({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ -6.0f, -3.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("scale_local");
        {
            const nnm::Ray2f result = ray3.scale_local({ -2.0f, 3.0f });
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ -0.5547f, 0.83205f }));
        }

        test_section("shear_x");
        {
            const nnm::Ray2f result = ray3.shear_x(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 1.26794919f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_x_local");
        {
            const nnm::Ray2f result = ray3.shear_x_local(nnm::pi() / 3.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
            ASSERT(result.direction.approx_equal({ 0.939071f, 0.343724f }));
        }

        test_section("shear_y");
        {
            const nnm::Ray2f result = ray3.shear_y(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -3.17963f }));
            ASSERT(result.direction.approx_equal({ 0.964585f, 0.263773f }));
        }

        test_section("shear_y_local");
        {
            const nnm::Ray2f result = ray3.shear_y_local(-nnm::pi() / 5.0f);
            ASSERT(result.origin.approx_equal({ 3.0f, -1.0f }));
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
}