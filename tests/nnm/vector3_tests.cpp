#include "tests.hpp"

void vector3_tests()
{
    test_case("Vector3");
    test_section("Vector3()");
    {
        constexpr nnm::Vector3f v1;
        TEST_ASSERT(v1.x == 0.0f);
        TEST_ASSERT(v1.y == 0.0f);
    }

    test_section("Vector3(const Vector3i&)");
    {
        constexpr nnm::Vector3f v2(nnm::Vector3i(1, 2, 3));
        TEST_ASSERT(v2.x == 1.0f);
        TEST_ASSERT(v2.y == 2.0f);
        TEST_ASSERT(v2.z == 3.0f);
    }

    test_section("Vector3(const Vector3<Other>&)");
    {
        constexpr nnm::Vector3d v1(1.0, -2.0, 0.5);
        constexpr nnm::Vector3f v2(v1);
        TEST_ASSERT(v2.x == 1.0f);
        TEST_ASSERT(v2.y == -2.0f);
        TEST_ASSERT(v2.z == 0.5f);
    }

    test_section("Vector3(const Vector2&, float)");
    {
        constexpr nnm::Vector3 v(nnm::Vector2(1.0f, 2.0f), 3.0f);
        TEST_ASSERT(v.x == 1.0f);
        TEST_ASSERT(v.y == 2.0f);
        TEST_ASSERT(v.z == 3.0f);
    }

    test_section("Vector3(float, float, float)");
    {
        constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
        TEST_ASSERT(v3.x == 1.0f);
        TEST_ASSERT(v3.y == 2.0f);
        TEST_ASSERT(v3.z == 3.0f);
    }

    test_section("all");
    {
        constexpr auto v1 = nnm::Vector3f::all(3.0f);
        TEST_ASSERT(v1.x == 3.0f);
        TEST_ASSERT(v1.y == 3.0f);
        TEST_ASSERT(v1.z == 3.0f);
    }

    test_section("zero");
    {
        constexpr auto v2 = nnm::Vector3f::zero();
        TEST_ASSERT(v2.x == 0.0f);
        TEST_ASSERT(v2.y == 0.0f);
        TEST_ASSERT(v2.z == 0.0f);
    }

    test_section("one");
    {
        constexpr auto v3 = nnm::Vector3f::one();
        TEST_ASSERT(v3.x == 1.0f);
        TEST_ASSERT(v3.y == 1.0f);
        TEST_ASSERT(v3.z == 1.0f);
    }

    test_section("axis_x");
    {
        constexpr auto x = nnm::Vector3f::axis_x();
        TEST_ASSERT(x.x == 1.0f);
        TEST_ASSERT(x.y == 0.0f);
        TEST_ASSERT(x.z == 0.0f);
    }

    test_section("axis_y");
    {
        constexpr auto y = nnm::Vector3f::axis_y();
        TEST_ASSERT(y.x == 0.0f);
        TEST_ASSERT(y.y == 1.0f);
        TEST_ASSERT(y.z == 0.0f);
    }

    test_section("axis_z");
    {
        constexpr auto z = nnm::Vector3f::axis_z();
        TEST_ASSERT(z.x == 0.0f);
        TEST_ASSERT(z.y == 0.0f);
        TEST_ASSERT(z.z == 1.0f);
    }

    test_section("abs");
    {
        constexpr auto result = nnm::Vector3(0.0f, 1.0f, -2.0f).abs();
        TEST_ASSERT(result == nnm::Vector3(0.0f, 1.0f, 2.0f));
    }

    test_section("ceil");
    {
        TEST_ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).ceil() == nnm::Vector3(1.0f, -2.0f, 2.0f));
    }

    test_section("floor");
    {
        TEST_ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).floor() == nnm::Vector3(0.0f, -3.0f, 1.0f));
    }

    test_section("round");
    {
        constexpr nnm::Vector3 v(1.1f, -2.8f, 0.0f);
        TEST_ASSERT(v.round() == nnm::Vector3(1.0f, -3.0f, 0.0f));
    }

    test_section("clamp");
    {
        constexpr nnm::Vector3 v(0.0f, 10.0f, -2.0f);
        constexpr nnm::Vector3 min(-1.0f, 12.0f, -5.0f);
        constexpr nnm::Vector3 max(1.0f, 12.0f, -3.0f);
        constexpr auto result = v.clamp(min, max);
        TEST_ASSERT(result == nnm::Vector3(0.0f, 12.0f, -3.0f));
    }

    test_section("length_sqrd");
    {
        constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        constexpr auto result = v.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(result, 14.0f));
    }

    test_section("length");
    {
        constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        TEST_ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
    }

    test_section("clamp_length");
    {
        constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        TEST_ASSERT(v.clamp_length(2.0f, 5.0f).approx_equal(nnm::Vector3(1.0f, 2.0f, 3.0f)));
        TEST_ASSERT(v.clamp_length(2.0f, 3.0f).approx_equal(nnm::Vector3(0.80178f, 1.603566f, 2.405352f)));
        TEST_ASSERT(v.clamp_length(10.0f, 100.0f).approx_equal(nnm::Vector3(2.67261f, 5.34522f, 8.01784f)));
    }

    test_section("normalize");
    {
        constexpr nnm::Vector3 v(1.0f, -2.0f, 3.0f);
        TEST_ASSERT(v.normalize().approx_equal(nnm::Vector3(0.267261f, -0.534522f, 0.801784f)));
    }

    test_section("lerp");
    {
        constexpr nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        constexpr nnm::Vector3 to(3.0f, 5.0f, -2.0f);
        constexpr auto result = from.lerp(to, 0.0f);
        TEST_ASSERT(result == nnm::Vector3(1.0f, 1.0f, 1.0f));
        TEST_ASSERT(from.lerp(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
        TEST_ASSERT(from.lerp(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
        TEST_ASSERT(from.lerp(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
        TEST_ASSERT(from.lerp(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
    }

    test_section("lerp_clamped");
    {
        constexpr nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        constexpr nnm::Vector3 to(3.0f, 5.0f, -2.0f);
        constexpr auto result = from.lerp_clamped(to, 0.0f);
        TEST_ASSERT(result == nnm::Vector3(1.0f, 1.0f, 1.0f));
        TEST_ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
        TEST_ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
        TEST_ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
        TEST_ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
        TEST_ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
        TEST_ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
    }

    test_section("dot");
    {
        constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
        constexpr auto result = v1.dot(v2);
        TEST_ASSERT(result == -28.0f);
    }

    test_section("cross");
    {
        constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
        constexpr auto result = v1.cross(v2);
        TEST_ASSERT(result == nnm::Vector3f::zero());
        constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
        constexpr nnm::Vector3 v4(-2.0f, 4.0f, 6.0f);
        TEST_ASSERT(v3.cross(v4) == nnm::Vector3(0.0f, -12.0f, 8.0f));
    }

    test_section("outer");
    {
        constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
        constexpr nnm::Matrix3f expected { { -2.0f, 4.0f, -6.0f }, { 4.0f, -8.0f, 12.0f }, { -6.0f, 12.0f, -18.0f } };
        constexpr auto result = v1.outer(v2);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("reflect");
    {
        constexpr nnm::Vector3 incident(1.0f, 1.0f, 1.0f);
        constexpr nnm::Vector3 normal(0.0f, 1.0f, 0.0f);
        constexpr auto result = incident.reflect(normal);
        TEST_ASSERT(result == nnm::Vector3(1.0f, -1.0f, 1.0f));
    }

    test_section("project");
    {
        constexpr nnm::Vector3 v(1.0f, 2.0f, -3.0f);
        constexpr nnm::Vector3 onto(-4.0f, 0.5f, 10.0f);
        constexpr nnm::Vector3 expected(1.135483870967742f, -0.141935483870968f, -2.838709677419355f);
        constexpr auto result = v.project(onto);
        TEST_ASSERT(result.approx_equal(expected));
    }

    test_section("inverse");
    {
        constexpr nnm::Vector3 v(1.0f, 2.0f, -3.0f);
        constexpr auto result = v.inverse();
        TEST_ASSERT(result.approx_equal(nnm::Vector3(1.0f, 0.5f, -1.0f / 3.0f)));
    }

    test_section("angle");
    {
        nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
        TEST_ASSERT(nnm::approx_equal(v1.angle(v2), 2.52872f))
    ;}

    test_section("parallel");
    {
        constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = v1.parallel({ 2.0f, 4.0f, -6.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(v1.parallel(v1));
        TEST_ASSERT(v1.parallel({ -3.0f, -6.0f, 9.0f }));
        TEST_ASSERT_FALSE(v1.parallel({ 1.0f, 2.0f, 3.0f }));
    }

    test_section("perpendicular");
    {
        constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = v1.perpendicular({ 30.0f, 0.0f, 10.0f });
        TEST_ASSERT(result);
        TEST_ASSERT(v1.perpendicular({ 0.0f, -6.0f, -4.0f }));
        TEST_ASSERT_FALSE(v1.perpendicular(v1));
        TEST_ASSERT_FALSE(v1.perpendicular({ 1.0f, 2.0f, 3.0f }));
    }

    test_section("arbitrary_perpendicular");
    {
        constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = v1.arbitrary_perpendicular();
        TEST_ASSERT(result.perpendicular(v1));
    }

    test_section("rotate_axis_angle");
    {
        nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        nnm::Vector3 axis = nnm::Vector3(2.0f, 0.5f, -0.8f).normalize();
        TEST_ASSERT(v1.rotate_axis_angle(axis, nnm::pi<float>() / 5.0f).approx_equal({ 1.2574f, 3.10567f, -1.66545f }))
    ;}

    test_section("rotate_quaternion");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr nnm::QuaternionF quaternion { 0.27948463f, 0.0698711574f, -0.111793853f, 0.95105654f };
        constexpr auto result = v1.rotate_quaternion(quaternion);
        TEST_ASSERT(result.approx_equal({ 1.2574f, 3.10567f, -1.66545f }));
    }

    test_section("scale");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
        constexpr auto result = v1.scale(v2);
        TEST_ASSERT(result.approx_equal({ -4.0f, 1.0f, -30.0f }));
    }

    test_section("shear_x");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr auto result = v1.shear_x(0.5f, -0.5f);
        TEST_ASSERT(result.approx_equal({ 1.0f, 2.5f, -3.5f }));
    }

    test_section("shear_y");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr auto result = v1.shear_y(0.5f, -0.5f);
        TEST_ASSERT(result.approx_equal({ 2.0f, 2.0f, -4.0f }));
    }

    test_section("shear_z");
    {
        constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = v1.shear_z(0.5f, -0.5f);
        TEST_ASSERT(result.approx_equal({ -0.5f, 3.5f, -3.0f }));
    }

    test_section("transform(const Basis3&)");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr nnm::Basis3f basis({ { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } });
        constexpr auto result = v1.transform(basis);
        TEST_ASSERT(result.approx_equal({ 9.0f, -12.4f, -30.44f }));
    }

    test_section("transform(const Transform2&)");
    {
        constexpr nnm::Vector3 v1(2.0f, -3.0f, 4.0f);
        constexpr nnm::Transform2f transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
        constexpr auto result = v1.transform(transform);
        TEST_ASSERT(result.approx_equal({ 26.0f, -8.8f, 1.0f }));
    }

    test_section("transform(const Transform3&, Real)");
    {
        constexpr nnm::Vector3 v1(2.0f, -3.0f, 4.0f);
        constexpr nnm::Transform3f transform(
            { { 1.0f, 2.0f, -3.0f, 4.0f },
              { -10.0f, 0.5f, 20.6f, 0.0f },
              { 1.0f, 3.0f, 3.3f, -1.0f },
              { 9.9f, -7.54f, 20.0f, 0.1f } });
        constexpr auto result = v1.transform(transform);
        TEST_ASSERT(result.approx_equal({ 36.0f, 14.5f, -54.6f }));
        TEST_ASSERT(v1.transform(transform, 0.0f).approx_equal(result));
    }

    test_section("max");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.max();
        TEST_ASSERT(result == 4.0);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.max() == 100.0f);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.max() == 0.0f);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.max() == 100.0f);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.max() == 100.0f);
    }

    test_section("abs_max");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.abs_max();
        TEST_ASSERT(result == 4.0);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.abs_max() == -200.0f);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.abs_max() == 0.0f);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.abs_max() == -200.0f);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.abs_max() == -200.0f);
    }

    test_section("min");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.min();
        TEST_ASSERT(result == -2.0f);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.min() == -200.0f);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.min() == 0.0f);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.min() == -200.0f);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.min() == -200.0f);
    }

    test_section("abs_min");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.abs_min();
        TEST_ASSERT(result == -2.0f);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.abs_min() == 5.0f);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.abs_min() == 0.0f);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.abs_min() == 5.0f);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.abs_min() == 5.0f);
    }

    test_section("max_index");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.max_index() == 2);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.max_index() == 0);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.max_index() == 2);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.max_index() == 1);
    }

    test_section("abs_max_index");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.abs_max_index();
        TEST_ASSERT(result == 1);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.abs_max_index() == 0);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.abs_max_index() == 0);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.abs_max_index() == 1);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.abs_max_index() == 2);
    }

    test_section("min_index");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.min_index();
        TEST_ASSERT(result == 2);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.min_index() == 0);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.min_index() == 0);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.min_index() == 1);
        nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
        TEST_ASSERT(v5.min_index() == 2);
    }

    test_section("abs_min_index");
    {
        constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        constexpr auto result = v1.abs_min_index();
        TEST_ASSERT(result == 2);
        nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
        TEST_ASSERT(v2.abs_min_index() == 1);
        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        TEST_ASSERT(v3.abs_min_index() == 0);
        nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
        TEST_ASSERT(v4.abs_min_index() == 0);
        nnm::Vector3 v5(-200.0f, 100.0f, 5.0f);
        TEST_ASSERT(v5.abs_min_index() == 2);
        nnm::Vector3 v6(10.0f, -3.0f, 100.0f);
        TEST_ASSERT(v6.abs_min_index() == 1);
        nnm::Vector3 v7(-1.0f, -100.0f, -50.0f);
        TEST_ASSERT(v7.abs_min_index() == 0);
    }

    test_section("approx_equal");
    {
        constexpr nnm::Vector3 v1(1.0f, 1.0f, 1.0f);
        constexpr nnm::Vector3 v2(1.0f + nnm::epsilon<float>() / 2.0f, 1.0f, 1.0f);
        constexpr auto result = v1.approx_equal(v2);
        TEST_ASSERT(result);
        nnm::Vector3 v3(1.0f, 1.0f, 1.0f);
        nnm::Vector3 v4(1.0f + 2.0f * nnm::epsilon<float>(), 1.0f, 1.0f);
        TEST_ASSERT_FALSE(v3.approx_equal(v4));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Vector3 v1(0.0f, 0.0f, 0.0f);
        constexpr auto result = v1.approx_zero();
        TEST_ASSERT(result);
        nnm::Vector3 v2(nnm::epsilon<float>(), 0.0f, 0.0f);
        TEST_ASSERT(v2.approx_zero());
        nnm::Vector3 v3(0.0f, nnm::epsilon<float>(), nnm::epsilon<float>());
        TEST_ASSERT(v3.approx_zero());
        nnm::Vector3 v4(0.1f, 0.1f, 0.1f);
        TEST_ASSERT_FALSE(v4.approx_zero());
    }

    test_section("xy");
    {
        constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
        constexpr auto result = v1.xy();
        TEST_ASSERT(result == nnm::Vector2(1.0f, 2.0f));
    }

    test_section("begin");
    {
        nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
        TEST_ASSERT(v1.begin() == &v1.x);
    }

    test_section("end");
    {
        nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
        TEST_ASSERT(v1.end() == &v1.z + 1);
    }

    test_section("at");
    {
        constexpr nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
        constexpr auto result = v1.at(0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(v1.at(1) == -3.0f);
        TEST_ASSERT(v1.at(2) == 4.0f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
        constexpr auto result = v1[0];
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(v1[1] == -3.0f);
        TEST_ASSERT(v1[2] == 4.0f);
    }

    constexpr nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
    constexpr nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
    constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

    test_section("operator==");
    {
        constexpr auto result = v1 == v3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v1 == v2);
    }

    test_section("operator!=");
    {
        constexpr auto result = v1 != v3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(v1 != v2);
    }

    test_section("operator+(const Vector3&)");
    {
        constexpr auto result = v1 + v2;
        TEST_ASSERT(result == nnm::Vector3(4.0f, 6.0f, 1.0f));
    }

    test_section("operator+=");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy += v2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(4.0f, 6.0f, 1.0f));
    }

    test_section("operator-(const Vector3&)");
    {
        constexpr auto result = v2 - v1;
        TEST_ASSERT(result == nnm::Vector3(2.0f, 2.0f, -5.0f));
    }

    test_section("operator-=");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy -= v1;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(2.0f, 2.0f, -5.0f));
    }

    test_section("operator*(const Vector3&)");
    {
        constexpr auto result = v1 * v2;
        TEST_ASSERT(result == nnm::Vector3(3.0f, 8.0f, -6.0f));
    }

    test_section("operator*=(const Vector3&)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= v2;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(3.0f, 8.0f, -6.0f));
    }

    test_section("operator*(const Matrix3&)");
    {
        constexpr nnm::Matrix3f matrix { { 1.0f, -3.0f, 4.0f }, { -1.6f, 0.5f, 20.0f }, { 0.0f, 2.0f, 1.0f } };
        constexpr auto result = v2 * matrix;
        TEST_ASSERT(result.approx_equal({ -17.0f, -42.8f, 6.0f }))
    ;}

    test_section("operator*(float)");
    {
        constexpr auto result = v1 * 2.0f;
        TEST_ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
    }

    test_section("operator*(float, const Vector3&)");
    {
        constexpr auto result = 2.0f * v1;
        TEST_ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
    }

    test_section("operator*=(float)");
    {
        constexpr auto result = [=] {
            auto v1_copy = v1;
            v1_copy *= 2.0f;
            return v1_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
    }

    test_section("operator/(const Vector3&)");
    {
        constexpr auto result = v2 / v1;
        TEST_ASSERT(result == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
    }

    test_section("operator/=(const Vector3&)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= v1;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
    }

    test_section("operator/(float)");
    {
        constexpr auto result = v2 / 2.0f;
        TEST_ASSERT(result == nnm::Vector3(1.5f, 2.0f, -1.0f));
    }

    test_section("operator/(float, const Vector3&)");
    {
        constexpr auto result = 2.0f / v2;
        TEST_ASSERT(result == nnm::Vector3(0.66666666f, 0.5f, -1.0f));
    }

    test_section("operator/=(float)");
    {
        constexpr auto result = [=] {
            auto v2_copy = v2;
            v2_copy /= 2.0f;
            return v2_copy;
        }();
        TEST_ASSERT(result == nnm::Vector3(1.5f, 2.0f, -1.0f));
    }

    test_section("operator+");
    {
        constexpr auto result = +v1;
        TEST_ASSERT(result == v1);
    }

    test_section("operator-");
    {
        constexpr auto result = -v1;
        TEST_ASSERT(result == nnm::Vector3(-1.0f, -2.0f, -3.0f));
    }

    test_section("operator<");
    {
        constexpr auto result = v1 < v2;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(v2 < v1);
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(v1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
    }
}
