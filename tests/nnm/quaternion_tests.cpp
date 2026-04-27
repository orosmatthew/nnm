#include "tests.hpp"

void quaternion_tests()
{
    test_case("Quaternion");
    test_section("Quaternion()");
    {
        constexpr nnm::QuaternionF q;
        TEST_ASSERT(q.x == 0.0f);
        TEST_ASSERT(q.y == 0.0f);
        TEST_ASSERT(q.z == 0.0f);
        TEST_ASSERT(q.w == 1.0f);
    }

    test_section("Quaternion(const Quaternion<Other>&)");
    {
        constexpr nnm::QuaternionD q1(1.0, -2.0, 3.0, -4.5);
        constexpr nnm::QuaternionF q2(q1);
        TEST_ASSERT(q2.x == 1.0f);
        TEST_ASSERT(q2.y == -2.0f);
        TEST_ASSERT(q2.z == 3.0f);
        TEST_ASSERT(q2.w == -4.5f);
    }

    test_section("Quaternion(const Vector4&)");
    {
        constexpr nnm::Quaternion q(nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
        TEST_ASSERT(q.x == 1.0f);
        TEST_ASSERT(q.y == -2.0f);
        TEST_ASSERT(q.z == 3.0f);
        TEST_ASSERT(q.w == -4.0f);
    }

    test_section("Quaternion(float, float, float, float)");
    {
        constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
        TEST_ASSERT(q.x == 1.0f);
        TEST_ASSERT(q.y == -2.0f);
        TEST_ASSERT(q.z == 3.0f);
        TEST_ASSERT(q.w == -4.0f);
    }

    test_section("identity");
    {
        constexpr auto q = nnm::QuaternionF::identity();
        TEST_ASSERT(q.x == 0.0f);
        TEST_ASSERT(q.y == 0.0f);
        TEST_ASSERT(q.z == 0.0f);
        TEST_ASSERT(q.w == 1.0f);
    }

    test_section("from_axis_angle");
    {
        const auto q = nnm::QuaternionF::from_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi<float>() / 9.0f);
        TEST_ASSERT(q.approx_equal({ 0.1515726f, -0.0757863f, 0.0378931f, 0.9848078f }))
    }

    test_section("from_vector_to_vector");
    {
        constexpr nnm::Vector3 from(1.0f, -2.0f, 3.0f);
        const auto to = from.rotate_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi<float>() / 9.0f);
        const auto q = nnm::QuaternionF::from_vector_to_vector(from, to);
        const auto rotated_from = from.rotate_quaternion(q);
        TEST_ASSERT(rotated_from.approx_equal(to));
    }

    test_section("normalize");
    {
        constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
        TEST_ASSERT(q.normalize().approx_equal({ 0.182574f, -0.365148f, 0.547723f, -0.730297f }));
    }

    test_section("axis_to");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), 0.0f);
        const auto q2 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), nnm::pi<float>() / 4.0f);
        TEST_ASSERT(q1.axis_to(q2).approx_equal(nnm::Vector3f::axis_x()));
        const auto q3 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), nnm::pi<float>() / 9.0f);
        const auto q4 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), -nnm::pi<float>() / 3.0f);
        TEST_ASSERT(q3.axis_to(q4).approx_equal(-nnm::Vector3f::axis_y()));
    }

    test_section("angle_to");
    {
        const auto q1 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), 0.0f);
        const auto q2 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), nnm::pi<float>() / 4.0f);
        TEST_ASSERT(nnm::approx_equal(q1.angle_to(q2), nnm::pi<float>() / 4.0f));
        const auto q3 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), nnm::pi<float>() / 9.0f);
        const auto q4 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), -nnm::pi<float>() / 3.0f);
        TEST_ASSERT(nnm::approx_equal(q3.angle_to(q4), 4.0f * nnm::pi<float>() / 9.0f));
    }

    test_section("axis");
    {
        const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
        constexpr float angle = nnm::pi<float>() / 9.0f;
        const auto q = nnm::QuaternionF::from_axis_angle(axis, angle);
        TEST_ASSERT(q.axis().approx_equal(axis));
    }

    test_section("angle");
    {
        const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
        constexpr float angle = nnm::pi<float>() / 9.0f;
        const auto q = nnm::QuaternionF::from_axis_angle(axis, angle);
        TEST_ASSERT(nnm::approx_equal(q.angle(), angle));
    }

    test_section("inverse");
    {
        constexpr auto q = nnm::Quaternion(1.0f, -2.0f, 3.0f, -4.0f);
        constexpr auto result = q.inverse();
        TEST_ASSERT(result.approx_equal({ -q.x, -q.y, -q.z, q.w }));
    }

    test_section("length_sqrd");
    {
        constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
        constexpr auto result = q.length_sqrd();
        TEST_ASSERT(nnm::approx_equal(result, 30.0f));
    }

    test_section("length");
    {
        constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
        TEST_ASSERT(nnm::approx_equal(q.length(), 5.47723f));
    }

    constexpr auto q1 = nnm::Quaternion(0.151572555f, -0.0757862777f, 0.0378931388f, 0.984807729f);
    constexpr auto q2 = nnm::Quaternion(-0.109108947f, -0.545544684f, 0.436435789f, 0.707106769f);

    test_section("slerp");
    {
        TEST_ASSERT(q1.slerp(q2, 0.75f).approx_equal({ -0.0439172f, -0.4470681f, 0.3514504f, 0.8213915f }));
    }

    test_section("rotate_axis_angle");
    {
        const nnm::Quaternion q3 = q1.rotate_axis_angle({ -1.0f, 2.0f, -0.5f }, -nnm::pi<float>() / 3.0f);
        TEST_ASSERT(q3.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
    }

    test_section("rotate_quaternion");
    {
        constexpr nnm::QuaternionF q3 { 0.21821788f, -0.436435759f, 0.10910894f, 0.866025388f };
        constexpr nnm::Quaternion q4 = q1.rotate_quaternion(q3);
        TEST_ASSERT(q4.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
    }

    test_section("approx_equal");
    {
        constexpr auto result = q1.approx_equal(q2);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(q1.approx_equal(q1));
        constexpr nnm::Quaternion q3(0.15157f, -0.07579f, 0.03789f, 0.98481f);
        TEST_ASSERT(q1.approx_equal(q3));
    }

    test_section("at");
    {
        constexpr nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
        constexpr auto result = q3.at(0);
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(q3.at(1) == -2.0f);
        TEST_ASSERT(q3.at(2) == 3.0f);
        TEST_ASSERT(q3.at(3) == -4.0f);
    }

    test_section("operator[]");
    {
        constexpr nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
        constexpr auto result = q3[0];
        TEST_ASSERT(result == 1.0f);
        TEST_ASSERT(q3[1] == -2.0f);
        TEST_ASSERT(q3[2] == 3.0f);
        TEST_ASSERT(q3[3] == -4.0f);
    }

    test_section("operator==");
    {
        constexpr auto q3 = q1;
        constexpr auto result = q1 == q3;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(q1 == q2);
    }

    test_section("operator!=");
    {
        constexpr auto q3 = q1;
        constexpr auto result = q1 != q3;
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(q1 != q2);
    }

    test_section("operator*");
    {
        constexpr auto result = q1 * q2;
        TEST_ASSERT(result.approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
    }

    test_section("operator*=");
    {
        constexpr auto result = [=] {
            auto q1_copy = q1;
            q1_copy *= q2;
            return q1_copy;
        }();
        TEST_ASSERT(result.approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
    }

    test_section("operator<");
    {
        constexpr auto result = q2 < q1;
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(q1 < q2);
    }

    test_section("operator bool");
    {
        constexpr auto result = static_cast<bool>(q1);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(static_cast<bool>(nnm::Quaternion(nnm::Vector4f::zero())));
    }
}