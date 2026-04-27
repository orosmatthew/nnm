#include "tests.hpp"

void point3_tests()
{
    test_case("Point3");

    test_section("Point3()");
    {
        constexpr nnm::Point3f p1;
        TEST_ASSERT(p1.x == 0.0f);
        TEST_ASSERT(p1.y == 0.0f);
        TEST_ASSERT(p1.z == 0.0f);
    }

    test_section("Point3(const Point3<Other>&)");
    {
        constexpr nnm::Point3d p1 { 1.0, -3.0, 0.5 };
        constexpr auto p2 = nnm::Point3f { p1 };
        TEST_ASSERT(nnm::approx_equal(p2.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(p2.y, -3.0f));
        TEST_ASSERT(nnm::approx_equal(p2.z, 0.5f));
    }

    test_section("Point3(Real, Real, Real)");
    {
        constexpr nnm::Point3f p1 { 1.0f, -3.0f, 0.5f };
        TEST_ASSERT(nnm::approx_equal(p1.x, 1.0f));
        TEST_ASSERT(nnm::approx_equal(p1.y, -3.0f));
        TEST_ASSERT(nnm::approx_equal(p1.z, 0.5f));
    }

    test_section("from_vector");
    {
        constexpr nnm::Vector3f v1 { 1.0f, -3.0f, 0.5f };
        constexpr auto p1 = nnm::Point3f::from_vector(v1);
        TEST_ASSERT(p1.approx_equal({ 1.0f, -3.0f, 0.5f }));
    }

    test_section("all");
    {
        constexpr auto p1 = nnm::Point3f::all(3.5f);
        TEST_ASSERT(p1.approx_equal({ 3.5f, 3.5f, 3.5f }));
    }

    test_section("zero");
    {
        constexpr auto p1 = nnm::Point3f::zero();
        TEST_ASSERT(p1.x == 0.0f);
        TEST_ASSERT(p1.y == 0.0f);
        TEST_ASSERT(p1.z == 0.0f);
    }

    test_section("to_vector");
    {
        constexpr nnm::Point3f p1 { 1.0f, -3.0f, 0.5f };
        constexpr nnm::Vector3f v1 = p1.to_vector();
        TEST_ASSERT(v1.approx_equal({ 1.0f, -3.0f, 0.5f }));
    }

    test_section("abs");
    {
        constexpr nnm::Point3f p1 { 1.0f, -3.0f, 0.5f };
        TEST_ASSERT(p1.abs().approx_equal({ 1.0f, 3.0f, 0.5f }));
    }

    test_section("ceil");
    {
        const nnm::Point3f result = nnm::Point3f(1.1f, -3.7f, 0.2f).ceil();
        TEST_ASSERT(result.approx_equal({ 2.0f, -3.0f, 1.0f }));
    }

    test_section("floor");
    {
        const nnm::Point3f result = nnm::Point3f(1.1f, -3.7f, 0.8f).floor();
        TEST_ASSERT(result.approx_equal({ 1.0f, -4.0f, 0.0f }));
    }

    test_section("round");
    {
        const nnm::Point3f result = nnm::Point3f(1.1f, -3.7f, 0.8f).round();
        TEST_ASSERT(result.approx_equal({ 1.0f, -4.0f, 1.0f }));
    }

    test_section("clamp");
    {
        constexpr nnm::Point3 p1 { 1.1f, -3.0f, 3.0f };
        constexpr auto result = p1.clamp({ 1.0f, -2.0f, 0.0f }, { 2.0f, 2.0f, 2.5f });
        TEST_ASSERT(result.approx_equal({ 1.1f, -2.0f, 2.5f }));
    }

    test_section("direction");
    {
        constexpr nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3 to { 2.0f, 2.0f, 2.0f };
        TEST_ASSERT(from.direction(to).approx_equal(nnm::Vector3f::all(0.57735f)));
        TEST_ASSERT(nnm::Point3(1.0f, 2.0f, 3.0f).direction({ 1.0f, 2.0f, 3.0f }).approx_equal(nnm::Vector3f::zero()));
    }

    test_section("direction_unnormalized");
    {
        constexpr nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3 to { 2.0f, 2.0f, 2.0f };
        TEST_ASSERT(from.direction_unnormalized(to).approx_equal({ 1.0f, 1.0f, 1.0f }));
    }

    test_section("distance_sqrd");
    {
        constexpr nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3 to { 2.0f, 2.0f, 2.0f };
        TEST_ASSERT(nnm::approx_equal(from.distance_sqrd(to), 3.0f));
    }

    test_section("distance");
    {
        nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        nnm::Point3 to { 2.0f, 2.0f, 2.0f };
        TEST_ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(3.0f)));
    }

    test_section("manhattan_distance");
    {
        constexpr nnm::Point3 from { -1.0f, -1.0f, -1.0f };
        constexpr nnm::Point3 to { 1.0f, 1.0f, 1.0f };
        TEST_ASSERT(nnm::approx_equal(from.manhattan_distance(to), 6.0f));
    }

    test_section("lerp");
    {
        constexpr nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3 to { 3.0f, 5.0f, -2.0f };
        TEST_ASSERT(from.lerp(to, 0.5f).approx_equal({ 2.0f, 3.0f, -0.5f }));
    }

    test_section("lerp_clamped");
    {
        constexpr nnm::Point3 from { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3 to { 3.0f, 5.0f, -2.0f };
        TEST_ASSERT(from.lerp_clamped(to, -1.0f).approx_equal({ 1.0f, 1.0f, 1.0f }));
        TEST_ASSERT(from.lerp_clamped(to, 2.0f).approx_equal({ 3.0f, 5.0f, -2.0f }));
    }

    constexpr nnm::Point3f origin { -3.0f, 1.5f, 10.0f };

    test_section("translate");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = p1.translate({ -4.0f, 0.5f, 10.0f });
        TEST_ASSERT(result.approx_equal({ -3.0f, 2.5f, 7.0f }));
    }

    test_section("rotate_axis_angle");
    {
        nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        nnm::Vector3 axis = nnm::Vector3(2.0f, 0.5f, -0.8f).normalize();
        TEST_ASSERT(p1.rotate_axis_angle(axis, nnm::pi<float>() / 5.0f).approx_equal({ 1.2574f, 3.10567f, -1.66545f }));
    }

    test_section("rotate_axis_angle_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        const auto axis = nnm::Vector3 { 2.0f, 0.5f, -0.8f }.normalize();
        TEST_ASSERT(p1.rotate_axis_angle_at(origin, axis, nnm::pi<float>() / 5.0f)
                        .approx_equal({ 0.071436f, 8.32907f, -1.36574f }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr nnm::QuaternionF q { 0.27948463f, 0.0698711574f, -0.111793853f, 0.95105654f };
        TEST_ASSERT(p1.rotate_quaternion(q).approx_equal({ 1.2574f, 3.10567f, -1.66545f }));
    }

    test_section("rotate_quaternion_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr nnm::QuaternionF q { 0.27948463f, 0.0698711574f, -0.111793853f, 0.95105654f };
        TEST_ASSERT(p1.rotate_quaternion_at(origin, q).approx_equal({ 0.071436f, 8.32907f, -1.36574f }));
    }

    test_section("scale");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = p1.scale({ -4.0f, 0.5f, 10.0f });
        TEST_ASSERT(result.approx_equal({ -4.0f, 1.0f, -30.0f }));
    }

    test_section("scale_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr auto result = p1.scale_at(origin, { -4.0f, 0.5f, 10.0f });
        TEST_ASSERT(result.approx_equal({ -19.0f, 1.75f, -120.0f }));
    }

    test_section("shear_x");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_x(0.5f, -0.5f).approx_equal({ 1.0f, 2.5f, -3.5f }));
    }

    test_section("shear_x_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_x_at(origin, 0.5f, -0.5f).approx_equal({ 1.0f, 4.0f, -5.0f }));
    }

    test_section("shear_y");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_y(0.5f, -0.5f).approx_equal({ 2.0f, 2.0f, -4.0f }));
    }

    test_section("shear_y_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_y_at(origin, 0.5f, -0.5f).approx_equal({ 1.25f, 2.0f, -3.25f }));
    }

    test_section("shear_z");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_z(0.5f, -0.5f).approx_equal({ -0.5f, 3.5f, -3.0f }));
    }

    test_section("shear_z_at");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        TEST_ASSERT(p1.shear_z_at(origin, 0.5f, -0.5f).approx_equal({ -5.5f, 8.5f, -3.0f }));
    }

    test_section("transform(const Basis3&)");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr nnm::Basis3f basis({ { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } });
        TEST_ASSERT(p1.transform(basis).approx_equal({ 9.0f, -12.4f, -30.44f }));
    }

    test_section("transform_at(const Point3&, const Basis3&)");
    {
        constexpr nnm::Point3 p1 { 1.0f, 2.0f, -3.0f };
        constexpr nnm::Basis3f basis { { { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } } };
        TEST_ASSERT(p1.transform_at(origin, basis).approx_equal({ 3.0f, -47.15f, -127.61f }));
    }

    test_section("transform(const Transform2&)");
    {
        constexpr nnm::Point3 p1 { 2.0f, -3.0f, 4.0f };
        constexpr nnm::Transform2f transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
        TEST_ASSERT(p1.transform(transform).approx_equal({ 26.0f, -8.8f, 1.0f }));
    }

    test_section("transform_at(const Point2&, const Transform2&)");
    {
        constexpr nnm::Point3 p1 { 2.0f, -3.0f, 4.0f };
        constexpr nnm::Transform2f transform { { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } } };
        TEST_ASSERT(p1.transform_at(nnm::Point2f { -10.0f, 0.5f }, transform).approx_equal({ 28.0f, 10.9f, 29.5f }));
    }

    test_section("transform(const Transform3&, Real)");
    {
        constexpr nnm::Point3 p1 { 2.0f, -3.0f, 4.0f };
        constexpr nnm::Transform3f transform(
            { { 1.0f, 2.0f, -3.0f, 4.0f },
              { -10.0f, 0.5f, 20.6f, 0.0f },
              { 1.0f, 3.0f, 3.3f, -1.0f },
              { 9.9f, -7.54f, 20.0f, 0.1f } });
        TEST_ASSERT(p1.transform(transform).approx_equal({ 45.9f, 6.96f, -34.6f }));
        TEST_ASSERT(p1.transform(transform, -2.4f).approx_equal({ 12.24f, 32.596f, -102.6f }));
    }

    test_section("transform_at(const Point3&, const Transform3&, Real)");
    {
        constexpr nnm::Point3 p1 { 2.0f, -3.0f, 4.0f };
        constexpr nnm::Transform3f transform { { { 1.0f, 2.0f, -3.0f, 4.0f },
                                                 { -10.0f, 0.5f, 20.6f, 0.0f },
                                                 { 1.0f, 3.0f, 3.3f, -1.0f },
                                                 { 9.9f, -7.54f, 20.0f, 0.1f } } };
        TEST_ASSERT(p1.transform_at(origin, transform).approx_equal({ 50.9f, -16.29f, -97.5f }));
        TEST_ASSERT(p1.transform_at(origin, transform, -2.4f).approx_equal({ 17.24f, 9.346f, -165.5f }));
    }

    test_section("approx_equal");
    {
        constexpr nnm::Point3f p1 { 1.0f, 1.0f, 1.0f };
        constexpr nnm::Point3f p2 { 1.0f + nnm::epsilon<float>() / 2.0f, 1.0f, 1.0f };
        TEST_ASSERT(p1.approx_equal(p2));
    }

    test_section("approx_zero");
    {
        constexpr nnm::Point3f p1 { 0.0f, 0.0f, 0.0f };
        TEST_ASSERT(p1.approx_zero());
        TEST_ASSERT_FALSE(nnm::Point3f(0.1f, 0.0f, 0.0f).approx_zero());
    }

    test_section("begin/end");
    {
        nnm::Point3f p1 { 2.0f, -3.0f, 4.0f };
        TEST_ASSERT(p1.begin() == &p1.x);
        TEST_ASSERT(p1.end() == &p1.z + 1);
    }

    test_section("at/operator[]");
    {
        nnm::Point3f p1 { 2.0f, -3.0f, 4.0f };
        TEST_ASSERT(p1.at(0) == 2.0f);
        TEST_ASSERT(p1[1] == -3.0f);
        p1.at(2) = 5.0f;
        p1[0] = 1.0f;
        TEST_ASSERT(p1.approx_equal({ 1.0f, -3.0f, 5.0f }));
    }

    constexpr nnm::Point3f p1 { 1.0f, 2.0f, 3.0f };
    constexpr nnm::Point3f p2 { 3.0f, 4.0f, -2.0f };
    constexpr nnm::Point3f p3 { 1.0f, 2.0f, 3.0f };

    test_section("operator==");
    {
        TEST_ASSERT(p1 == p3);
        TEST_ASSERT_FALSE(p1 == p2);
    }

    test_section("operator!=");
    {
        TEST_ASSERT_FALSE(p1 != p3);
        TEST_ASSERT(p1 != p2);
    }

    test_section("operator+(const Vector3&)");
    {
        constexpr auto result = p1 + nnm::Vector3f { 2.0f, 2.0f, -5.0f };
        TEST_ASSERT(result.approx_equal({ 3.0f, 4.0f, -2.0f }));
    }

    test_section("operator+=");
    {
        nnm::Point3f p = p1;
        p += nnm::Vector3f { 2.0f, 2.0f, -5.0f };
        TEST_ASSERT(p.approx_equal({ 3.0f, 4.0f, -2.0f }));
    }

    test_section("operator-(const Point3&)");
    {
        constexpr nnm::Vector3f result = p2 - p1;
        TEST_ASSERT(result.approx_equal({ 2.0f, 2.0f, -5.0f }));
    }

    test_section("operator-(const Vector3&)");
    {
        constexpr auto result = p2 - nnm::Vector3f { 2.0f, 2.0f, -5.0f };
        TEST_ASSERT(result.approx_equal({ 1.0f, 2.0f, 3.0f }));
    }

    test_section("operator-=");
    {
        nnm::Point3f p = p2;
        p -= nnm::Vector3f { 2.0f, 2.0f, -5.0f };
        TEST_ASSERT(p.approx_equal({ 1.0f, 2.0f, 3.0f }));
    }

    test_section("operator<");
    {
        TEST_ASSERT(p1 < p2);
        TEST_ASSERT_FALSE(p2 < p1);
    }

    test_section("operator bool");
    {
        TEST_ASSERT(static_cast<bool>(p1));
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Point3f::zero()));
    }
}
