#define NNM_BOUNDS_CHECK_THROW
#include <nnm/nnm.hpp>

#include "test.hpp"

// ReSharper disable once CppDFATimeOver

int main()
{
    test_case("sign");
    {
        ASSERT(nnm::sign(0.0f) == 1.0f);
        ASSERT(nnm::sign(1.0f) == 1.0f);
        ASSERT(nnm::sign(-1.0f) == -1.0f);
        ASSERT(nnm::sign(0) == 1);
        ASSERT(nnm::sign(1) == 1);
        ASSERT(nnm::sign(-1) == -1);
    }

    test_case("abs");
    {
        ASSERT(nnm::abs(0) == 0);
        ASSERT(nnm::abs(1) == 1);
        ASSERT(nnm::abs(-1) == 1);
        ASSERT(nnm::abs(0.0f) == 0.0f);
        ASSERT(nnm::abs(1.0f) == 1.0f);
        ASSERT(nnm::abs(-1.0f) == 1.0f);
    }

    test_case("approx zero");
    {
        ASSERT(nnm::approx_zero(0.0f, 0.01f));
        ASSERT(nnm::approx_zero(0.005f, 0.01f));
        ASSERT(nnm::approx_zero(0.01f, 0.01f));
        ASSERT(nnm::approx_zero(-0.005f, 0.01f));
        ASSERT(nnm::approx_zero(-0.01f, 0.01f));
        ASSERT(nnm::approx_zero(1e-15f, 1e-14f));
        ASSERT_FALSE(nnm::approx_zero(1e-14f, 1e-15f));
        ASSERT(nnm::approx_zero(-1e-15f, 1e-14f));
        ASSERT_FALSE(nnm::approx_zero(-1e-14f, 1e-15f));
        ASSERT_FALSE(nnm::approx_zero(1.0f, 0.0f));
        ASSERT(nnm::approx_zero(0.0f, 0.0f));
    }

    test_case("max");
    {
        ASSERT(nnm::max(5, 10) == 10);
        ASSERT(nnm::max(10, 5) == 10);
        ASSERT(nnm::max(-5, -10) == -5);
        ASSERT(nnm::max(-10, -5) == -5);
        ASSERT(nnm::max(0, 0) == 0);

        ASSERT(nnm::max(5.0f, 10.0f) == 10.0f);
        ASSERT(nnm::max(10.0f, 5.0f) == 10.0f);
        ASSERT(nnm::max(-5.0f, -10.0f) == -5.0f);
        ASSERT(nnm::max(-10.0f, -5.0f) == -5.0f);
        ASSERT(nnm::max(0.0f, 0.0f) == 0.0f);
        ASSERT(nnm::max(3.14159f, 2.71828f) == 3.14159f);
        ASSERT(nnm::max(-3.14159f, -2.71828f) == -2.71828f);
    }

    test_case("approx_lte");
    {
        ASSERT(nnm::approx_lte(1.0f, 1.0f, 0.01f));
        ASSERT(nnm::approx_lte(1.0f, 1.005f, 0.01f));
        ASSERT(nnm::approx_lte(1.0f, 1.01f, 0.01f));
        ASSERT(nnm::approx_lte(1.0f, 1.02f, 0.01f));
        ASSERT(nnm::approx_lte(-1.0f, -1.005f, 0.01f));
        ASSERT(nnm::approx_lte(1.0f, 1.0f, -0.01f));
        ASSERT(nnm::approx_lte(1e-15f, 1e-16f, 1e-14f));
        ASSERT_FALSE(nnm::approx_lte(4.0f, 2.0f, 1e-10f));
    }

    test_case("is_equal_approx");
    {
        ASSERT(nnm::approx_equal(1.0f, 1.0f, 0.01f));
        ASSERT(nnm::approx_equal(1.0f, 1.005f, 0.01f));
        ASSERT(nnm::approx_equal(1.0f, 1.01f, 0.01f));
        ASSERT_FALSE(nnm::approx_equal(1.0f, 1.02f, 0.01f));
        ASSERT(nnm::approx_equal(-1.0f, -1.005f, 0.01f));
        ASSERT(nnm::approx_equal(0.0f, 0.0f, 0.01f));
        ASSERT(nnm::approx_equal(0.0f, 0.005f, 0.01f));
        ASSERT(nnm::approx_equal(0.005f, 0.0f, 0.01f));
        ASSERT(nnm::approx_equal(0.0f, 0.0f, 0.0f));
        ASSERT(nnm::approx_equal(1.0f, 1.005f, -0.01f));
        ASSERT(nnm::approx_equal(1.0e20f, 1.000000000001e20f, 1e-10f));
    }

    test_case("approx_gte");
    {
        ASSERT(nnm::approx_gte(1.0f, 1.0f, 0.01f));
        ASSERT(nnm::approx_gte(1.0f, 0.995f, 0.01f));
        ASSERT(nnm::approx_gte(1.0f, 0.99f, 0.01f));
        ASSERT(nnm::approx_gte(1.0f, 0.98f, 0.01f));
        ASSERT(nnm::approx_gte(-1.0f, -1.005f, 0.01f));
        ASSERT(nnm::approx_gte(1.0f, 1.0f, -0.01f));
        ASSERT(nnm::approx_gte(1e-15f, 1e-16f, 1e-14f));
        ASSERT_FALSE(nnm::approx_gte(2.0f, 4.0f, 1e-14f));
    }

    test_case("ceil");
    {
        ASSERT(nnm::ceil(5.3f) == 6.0f);
        ASSERT(nnm::ceil(5.7f) == 6.0f);
        ASSERT(nnm::ceil(5.0f) == 5.0f);
        ASSERT(nnm::ceil(-5.3f) == -5.0f);
        ASSERT(nnm::ceil(-5.7f) == -5.0f);
        ASSERT(nnm::ceil(-5.0f) == -5.0f);
        ASSERT(nnm::ceil(0.0f) == 0.0f);
        ASSERT(nnm::ceil(1.0e20f) == 1.0e20f);
        ASSERT(nnm::ceil(-1.0e20f) == -1.0e20f);
        ASSERT(nnm::ceil(3.14159f) == 4.0f);
        ASSERT(nnm::ceil(-3.14159f) == -3.0f);
    }

    test_case("clamp");
    {
        ASSERT(nnm::clamp(5, 0, 10) == 5);
        ASSERT(nnm::clamp(-5, 0, 10) == 0);
        ASSERT(nnm::clamp(15, 0, 10) == 10);
        ASSERT(nnm::clamp(5, 5, 5) == 5);
        ASSERT(nnm::clamp(3.5f, 1.0f, 5.0f) == 3.5f);
        ASSERT(nnm::clamp(0.5f, 1.0f, 5.0f) == 1.0f);
        ASSERT(nnm::clamp(6.0f, 1.0f, 5.0f) == 5.0f);
        ASSERT(nnm::clamp(-5, -10, -2) == -5);
        ASSERT(nnm::clamp(-15, -10, -2) == -10);
        ASSERT(nnm::clamp(-3, -5, -1) == -3);
        ASSERT(nnm::clamp(-6, -5, -1) == -5);
    }

    test_case("sqrt");
    {
        ASSERT(nnm::sqrt(4.0f) == 2.0f);
        ASSERT(nnm::sqrt(9.0f) == 3.0f);
        ASSERT(nnm::sqrt(16.0f) == 4.0f);

        ASSERT(nnm::approx_equal(nnm::sqrt(4.0f), 2.0));
        ASSERT(nnm::approx_equal(nnm::sqrt(9.0f), 3.0));
        ASSERT(nnm::approx_equal(nnm::sqrt(16.0f), 4.0));

        ASSERT(nnm::sqrt(0.0f) == 0.0f);

        ASSERT(nnm::approx_equal(nnm::sqrt(1.0e20f), 1.0e10f));
    }

    test_case("pow");
    {
        ASSERT(nnm::pow(2.0f, 3.0f) == 8.0f);
        ASSERT(nnm::pow(3.0f, 2.0f) == 9.0f);
        ASSERT(nnm::pow(4.0f, 0.0f) == 1.0f);

        ASSERT(nnm::approx_equal(nnm::pow(2.0f, 3.0f), 8.0f));
        ASSERT(nnm::approx_equal(nnm::pow(3.0f, 2.0f), 9.0f));
        ASSERT(nnm::approx_equal(nnm::pow(4.0f, 0.0f), 1.0f));

        ASSERT(nnm::approx_equal(nnm::pow(-2.0f, 2.0f), 4.0f));
        ASSERT(nnm::approx_equal(nnm::pow(-3.0f, 2.0f), 9.0f));

        ASSERT(nnm::approx_equal(nnm::pow(-2.0f, 3.0f), -8.0f));
        ASSERT(nnm::approx_equal(nnm::pow(-3.0f, 3.0f), -27.0f));

        ASSERT(nnm::approx_equal(nnm::pow(0.0f, 3.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::pow(0.0f, 0.0f), 1.0f));

        ASSERT(nnm::approx_equal(nnm::pow(0.5f, 2.0f), 0.25f));
        ASSERT(nnm::approx_equal(nnm::pow(0.25f, 0.5f), 0.5f));

        ASSERT(nnm::approx_equal(nnm::pow(10.0f, 10.0f), 1.0e10f));
        ASSERT(nnm::approx_equal(nnm::pow(2.f, 100.0f), 1.2676506002282294e30f));
    }

    test_case("sqrd");
    {
        ASSERT(nnm::sqrd(2) == 4);
        ASSERT(nnm::sqrd(3) == 9);
        ASSERT(nnm::sqrd(-4) == 16);

        ASSERT(nnm::approx_equal(nnm::sqrd(2.0f), 4.0f));
        ASSERT(nnm::approx_equal(nnm::sqrd(3.0f), 9.0f));
        ASSERT(nnm::approx_equal(nnm::sqrd(-4.0f), 16.0f));

        ASSERT(nnm::sqrd(0) == 0);
        ASSERT(nnm::sqrd(0.0f) == 0.0f);

        ASSERT(nnm::approx_equal(nnm::sqrd(1.0e10f), 1.0e20f));
        ASSERT(nnm::approx_equal(nnm::sqrd(-1.0e10f), 1.0e20f));
    }

    test_case("floor");
    {
        ASSERT(nnm::floor(5.3f) == 5.0f);
        ASSERT(nnm::floor(5.7f) == 5.0f);
        ASSERT(nnm::floor(5.0f) == 5.0f);

        ASSERT(nnm::floor(-5.3f) == -6.0f);
        ASSERT(nnm::floor(-5.7f) == -6.0f);
        ASSERT(nnm::floor(-5.0f) == -5.0f);

        ASSERT(nnm::floor(0.0f) == 0.0f);

        ASSERT(nnm::floor(1.0e20f) == 1.0e20f);
        ASSERT(nnm::floor(-1.0e20f) == -1.0e20f);

        ASSERT(nnm::floor(3.14159f) == 3.0f);
        ASSERT(nnm::floor(-3.14159f) == -4.0f);
    }

    test_case("lerp");
    {
        ASSERT(nnm::lerp(0.0f, 10.0f, 0.5f) == 5.0f);
        ASSERT(nnm::lerp(0.0f, 10.0f, 0.25f) == 2.5f);
        ASSERT(nnm::lerp(-5.0f, 5.0f, 0.75f) == 2.5f);

        ASSERT(nnm::lerp(-10.0f, -20.0f, 0.5f) == -15.0f);
        ASSERT(nnm::lerp(-10.0f, -20.0f, 0.25f) == -12.5f);
        ASSERT(nnm::lerp(-15.0f, -25.0f, 0.75f) == -22.5f);

        ASSERT(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);
        ASSERT(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);

        ASSERT(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);
        ASSERT(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);

        ASSERT(nnm::lerp(5.0f, 10.0f, 10.0f) == 10.0f);
        ASSERT(nnm::lerp(5.0f, 10.0f, -10.0f) == 5.0f);

        ASSERT(nnm::unclamped_lerp(5.0f, 10.0f, 10.0f) == 55.0f);
        ASSERT(nnm::unclamped_lerp(5.0f, 10.0f, -10.0f) == -45.0f);
    }

    test_case("sin");
    {
        ASSERT(nnm::approx_equal(nnm::sin(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi / 6.0f), 0.5f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi / 3.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi / 2.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(3.0f * nnm::pi / 2.0f), -1.0f));
        ASSERT(nnm::approx_equal(nnm::sin(2.0f * nnm::pi), 0.0f));

        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi / 6.0f), -0.5f));
        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi / 4.0f), -1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi / 3.0f), -nnm::sqrt(3.0f) / 2.0f));

        ASSERT(nnm::approx_equal(nnm::sin(4.0f * nnm::pi), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(6.0f * nnm::pi), 0.0f));
    }

    test_case("cos");
    {
        ASSERT(nnm::approx_equal(nnm::cos(0.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi / 3.0f), 0.5f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi / 2.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi), -1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(3.0f * nnm::pi / 2.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::cos(2.0f * nnm::pi), 1.0f));

        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi / 3.0f), 0.5f));

        ASSERT(nnm::approx_equal(nnm::cos(4.0f * nnm::pi), 1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(6.0f * nnm::pi), 1.0f));
    }

    test_case("tan");
    {
        ASSERT(nnm::approx_equal(nnm::tan(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi / 4.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi / 6.0f), 1.0f / nnm::sqrt(3.0f)));

        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi / 3.0f), nnm::sqrt(3.0f)));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi / 2.0f - 0.01f), 99.9967f));

        ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi / 3.0f), -nnm::sqrt(3.0f)));
        ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi / 2.0f + 0.01f), -99.9967f));

        ASSERT(nnm::approx_equal(nnm::tan(3.0f * nnm::pi), 0.0f));
        ASSERT(nnm::approx_equal(nnm::tan(6.0f * nnm::pi), 0.0f));
    }

    test_case("round");
    {
        ASSERT(nnm::round(5.3f) == 5.0f);
        ASSERT(nnm::round(5.7f) == 6.0f);
        ASSERT(nnm::round(5.0f) == 5.0f);

        ASSERT(nnm::round(-5.3f) == -5.0f);
        ASSERT(nnm::round(-5.7f) == -6.0f);
        ASSERT(nnm::round(-5.0f) == -5.0f);

        ASSERT(nnm::round(0.0f) == 0.0f);

        ASSERT(nnm::round(3.14159f) == 3.0f);
        ASSERT(nnm::round(-3.14159f) == -3.0f);
    }

    test_case("atan");
    {
        ASSERT(nnm::approx_equal(nnm::atan(0.5f), 0.4636476f));
        ASSERT(nnm::approx_equal(nnm::atan(1.0f), 0.7853981f));
        ASSERT(nnm::approx_equal(nnm::atan(2.0f), 1.1071487f));

        ASSERT(nnm::approx_equal(nnm::atan(-0.5f), -0.4636476f));
        ASSERT(nnm::approx_equal(nnm::atan(-1.0f), -0.7853981f));
        ASSERT(nnm::approx_equal(nnm::atan(-2.0f), -1.1071487f));

        ASSERT(nnm::approx_equal(nnm::atan(0.0f), 0.0f));

        ASSERT(nnm::approx_equal(nnm::atan(1.0e20f), 1.5707963f));
        ASSERT(nnm::approx_equal(nnm::atan(-1.0e20f), -1.5707963f));
    }

    test_case("atan2");
    {
        ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 1.0f), 0.7853981633974483f));
        ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 2.0f), 0.4636476090008061f));

        ASSERT(nnm::approx_equal(nnm::atan2(-1.0f, -1.0f), -2.356194490192345f));
        ASSERT(nnm::approx_equal(nnm::atan2(-1.0f, 2.0f), -0.4636476090008061f));

        ASSERT(nnm::approx_equal(nnm::atan2(0.0f, 1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 0.0f), 1.5707963267948966f));
        ASSERT(nnm::approx_equal(nnm::atan2(0.0f, 0.0f), 0.0f));

        ASSERT(nnm::approx_equal(nnm::atan2(1.0e20f, 1.0e20f), 0.7853981633974483f));
        ASSERT(nnm::approx_equal(nnm::atan2(-1.0e20f, -1.0e20f), -2.356194490192345f));
    }

    test_case("radians");
    {
        ASSERT(nnm::approx_equal(nnm::radians(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::radians(45.0f), nnm::pi / 4.0f));
        ASSERT(nnm::approx_equal(nnm::radians(90.0f), nnm::pi / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(180.0f), nnm::pi));
        ASSERT(nnm::approx_equal(nnm::radians(270.0f), 3.0f * nnm::pi / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(360.0f), 2.0f * nnm::pi));

        ASSERT(nnm::approx_equal(nnm::radians(-45.0f), -nnm::pi / 4.0f));
        ASSERT(nnm::approx_equal(nnm::radians(-90.0f), -nnm::pi / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(-180.0f), -nnm::pi));

        ASSERT(nnm::approx_equal(nnm::radians(720.0f), 4.0f * nnm::pi));
        ASSERT(nnm::approx_equal(nnm::radians(1080.0f), 6.0f * nnm::pi));

        ASSERT(nnm::approx_equal(nnm::radians(180.0f, 3.14159f), 3.14159f));
    }

    test_case("degrees");
    {
        ASSERT(nnm::approx_equal(nnm::degrees(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi / 4.0f), 45.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi / 2.0f), 90.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi), 180.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(3.0f * nnm::pi / 2.0f), 270.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(2.0f * nnm::pi), 360.0f));

        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi / 4.0f), -45.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi / 2.0f), -90.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi), -180.0f));

        ASSERT(nnm::approx_equal(nnm::degrees(4.0f * nnm::pi), 720.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(6.0f * nnm::pi), 1080.0f));

        ASSERT(nnm::approx_equal(nnm::degrees(3.14159f, 3.14159f), 180.0f));
    }

    test_case("asin");
    {
        ASSERT(nnm::approx_equal(nnm::asin(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::asin(0.5f), 0.5235987756f));
        ASSERT(nnm::approx_equal(nnm::asin(-0.5f), -0.5235987756f));
        ASSERT(nnm::approx_equal(nnm::asin(1.0f), 1.570796327f));
        ASSERT(nnm::approx_equal(nnm::asin(-1.0f), -1.570796327f));

        ASSERT(nnm::safe_asin(1.0f).has_value());
        ASSERT(nnm::approx_equal(nnm::safe_asin(1.0f).value(), 1.570796327f));
        ASSERT(nnm::safe_asin(-1.0f).has_value());
        ASSERT(nnm::approx_equal(nnm::safe_asin(-1.0f).value(), -1.570796327f));
        ASSERT_FALSE(nnm::safe_asin(1.1f).has_value());
        ASSERT_FALSE(nnm::safe_asin(-1.1f).has_value());
    }

    test_case("acos");
    {
        ASSERT(nnm::approx_equal(nnm::acos(1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::acos(0.5f), 1.047197551f));
        ASSERT(nnm::approx_equal(nnm::acos(-0.5f), 2.094395102f));
        ASSERT(nnm::approx_equal(nnm::acos(0.0f), 1.570796327f));
        ASSERT(nnm::approx_equal(nnm::acos(-1.0f), 3.141592654f));

        ASSERT(nnm::safe_acos(1.0f).has_value());
        ASSERT(nnm::approx_equal(nnm::safe_acos(1.0f).value(), 0.0f));
        ASSERT(nnm::safe_acos(-1.0f).has_value());
        ASSERT(nnm::approx_equal(nnm::safe_acos(-1.0f).value(), 3.141592654f));
        ASSERT_FALSE(nnm::safe_acos(1.1f).has_value());
        ASSERT_FALSE(nnm::safe_acos(-1.1f).has_value());
    }

    test_case("min");
    {
        ASSERT(nnm::min(1, 2) == 1);
        ASSERT(nnm::min(5, 3) == 3);
        ASSERT(nnm::min(-1, -5) == -5);

        ASSERT(nnm::min(1.0f, 2.0f) == 1.0f);
        ASSERT(nnm::min(5.5f, 3.5f) == 3.5f);
        ASSERT(nnm::min(-1.0f, -5.0f) == -5.0f);

        ASSERT(nnm::min('a', 'b') == 'a');
        ASSERT(nnm::min(3.14f, 2.71f) == 2.71f);
    }

    test_case("log2");
    {
        ASSERT(nnm::approx_equal(nnm::log2(1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::log2(2.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::log2(8.0f), 3.0f));
        ASSERT(nnm::approx_equal(nnm::log2(16.0f), 4.0f));

        ASSERT(nnm::approx_equal(nnm::log2(0.5f), -1.0f));
        ASSERT(nnm::approx_equal(nnm::log2(4.0f), 2.0f));

        ASSERT(nnm::safe_log2(1.0f).has_value());
        ASSERT(nnm::approx_equal(nnm::safe_log2(1.0f).value(), 0.0f));
        ASSERT_FALSE(nnm::safe_log2(0.0f).has_value());
        ASSERT_FALSE(nnm::safe_log2(-10.0f).has_value());
    }

    test_case("Vector2");
    {
        test_section("Default constructor");
        {
            const nnm::Vector2 v;
            ASSERT(v.x == 0.0f);
            ASSERT(v.y == 0.0f);
        }

        test_section("From Vector2i constructor");
        {
            const nnm::Vector2 v(nnm::Vector2i(1, 2));
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == 2.0f);
        }

        test_section("Constructor with params");
        {
            const nnm::Vector2 v(1.0f, 2.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == 2.0f);
        }

        test_section("Static methods");
        {
            const auto all_threes = nnm::Vector2::all(3.0f);
            ASSERT(all_threes.x == 3.0f);
            ASSERT(all_threes.y == 3.0f);

            const auto zero = nnm::Vector2::zero();
            ASSERT(zero.x == 0.0f);
            ASSERT(zero.y == 0.0f);

            const auto one = nnm::Vector2::one();
            ASSERT(one.x == 1.0f);
            ASSERT(one.y == 1.0f);
        }

        test_section("abs");
        {
            const nnm::Vector2 v(1.0f, -2.0f);
            ASSERT(v.abs() == nnm::Vector2(1.0f, 2.0f));
        }

        test_section("aspect_ratio");
        {
            const nnm::Vector2 v(1.0f, -2.0f);
            ASSERT(v.aspect_ratio() == 1.0f / -2.0f);
        }

        test_section("ceil");
        {
            const nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.ceil() == nnm::Vector2(2.0f, -1.0f));
        }

        test_section("clamp");
        {
            const nnm::Vector2 v(1.1f, -3.0f);
            ASSERT(v.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f }) == nnm::Vector2(1.1f, -2.0f));
        }

        test_section("normalize");
        {
            const nnm::Vector2 v(1.1f, -3.0f);
            const auto norm = v.normalize();
            ASSERT(nnm::approx_equal(norm.x, 0.344255f));
            ASSERT(nnm::approx_equal(norm.y, -0.938876f));
        }

        test_section("direction_to");
        {
            const nnm::Vector2 from1(1.0f, 1.0f);
            const nnm::Vector2 to1(2.0f, 2.0f);
            auto direction1 = from1.direction_to(to1);
            ASSERT(nnm::approx_equal(direction1.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction1.y, 0.7071067812f));

            const nnm::Vector2 from2(-1.0f, -1.0f);
            const nnm::Vector2 to2(1.0f, 1.0f);
            auto direction2 = from2.direction_to(to2);
            ASSERT(nnm::approx_equal(direction2.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction2.y, 0.7071067812f));

            const nnm::Vector2 from3(0.0f, 0.0f);
            const nnm::Vector2 to3(1.0f, 0.0f);
            auto direction3 = from3.direction_to(to3);
            ASSERT(nnm::approx_equal(direction3.x, 1.0f));
            ASSERT(nnm::approx_equal(direction3.y, 0.0f));

            const nnm::Vector2 from4(0.0f, 0.0f);
            const nnm::Vector2 to4(0.0f, 1.0f);
            auto direction4 = from4.direction_to(to4);
            ASSERT(nnm::approx_equal(direction4.x, 0.0f));
            ASSERT(nnm::approx_equal(direction4.y, 1.0f));

            const nnm::Vector2 from5(1.0f, 2.0f);
            const nnm::Vector2 to5(1.0f, 2.0f);
            auto direction5 = from5.direction_to(to5);
            ASSERT(nnm::approx_equal(direction5.x, 0.0f));
            ASSERT(nnm::approx_equal(direction5.y, 0.0f));
        }

        test_section("distance_sqrd_to");
        {
            const nnm::Vector2 from1(1.0f, 1.0f);
            const nnm::Vector2 to1(2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from1.distance_sqrd_to(to1), 2.0f));

            const nnm::Vector2 from2(-1.0f, -1.0f);
            const nnm::Vector2 to2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from2.distance_sqrd_to(to2), 8.0f));

            const nnm::Vector2 from3(0.0f, 0.0f);
            const nnm::Vector2 to3(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from3.distance_sqrd_to(to3), 9.0f));

            const nnm::Vector2 from4(0.0f, 0.0f);
            const nnm::Vector2 to4(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from4.distance_sqrd_to(to4), 16.0f));

            const nnm::Vector2 from5(1.0f, 2.0f);
            const nnm::Vector2 to5(1.0f, 2.0f);
            ASSERT(nnm::approx_equal(from5.distance_sqrd_to(to5), 0.0f));
        }

        test_section("distance_to");
        {
            nnm::Vector2 from(1.0f, 1.0f);
            nnm::Vector2 to(2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), nnm::sqrt(2.0f)));

            from = nnm::Vector2(-1.0f, -1.0f);
            to = nnm::Vector2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), nnm::sqrt(8.0f)));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 3.0f));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 4.0f));

            from = nnm::Vector2(1.0f, 2.0f);
            to = nnm::Vector2(1.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 0.0f));
        }

        test_section("floor");
        {
            const nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.floor() == nnm::Vector2(1.0f, -2.0f));
        }

        test_section("length_sqrd");
        {
            nnm::Vector2 v(3.0f, 4.0f);
            ASSERT(nnm::approx_equal(v.length_sqrd(), 25.0f));

            v = nnm::Vector2(-2.0f, 5.0f);
            ASSERT(nnm::approx_equal(v.length_sqrd(), 29.0f));

            v = nnm::Vector2(0.0f, 0.0f);
            ASSERT(nnm::approx_equal(v.length_sqrd(), 0.0f));
        }

        test_section("length");
        {
            nnm::Vector2 v(3.0f, 4.0f);
            ASSERT(nnm::approx_equal(v.length(), 5.0f));

            v = nnm::Vector2(-2.0f, 5.0f);
            ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(29.0f)));

            v = nnm::Vector2(0.0f, 0.0f);
            ASSERT(nnm::approx_equal(v.length(), 0.0f));
        }

        test_section("lerp");
        {
            const nnm::Vector2 from(1.0f, 1.0f);
            const nnm::Vector2 to(3.0f, 5.0f);
            ASSERT(from.lerp(to, 0.0f) == nnm::Vector2(1.0f, 1.0f));
            ASSERT(from.lerp(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
            ASSERT(from.lerp(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
            ASSERT(from.lerp(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
        }

        test_section("min/max_axis");
        {
            nnm::Vector2 v1(3.0f, 4.0f);
            ASSERT(v1.max_axis() == nnm::Axis2::y);
            ASSERT(v1.min_axis() == nnm::Axis2::x);

            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.max_axis() == nnm::Axis2::y);
            ASSERT(v2.min_axis() == nnm::Axis2::x);

            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.max_axis() == nnm::Axis2::x);
            ASSERT(v3.min_axis() == nnm::Axis2::x);
        }

        test_section("approx_equal");
        {
            nnm::Vector2 v1(1.0f, 1.0f);
            nnm::Vector2 v2(1.0f + nnm::epsilon / 2.0f, 1.0f);
            ASSERT(v1.approx_equal(v2));
            nnm::Vector2 v3(1.0f, 1.0f);
            nnm::Vector2 v4(1.0f + 2.0f * nnm::epsilon, 1.0f);
            ASSERT_FALSE(v3.approx_equal(v4));
        }

        test_section("approx_zero");
        {
            nnm::Vector2 v1(0.0f, 0.0f);
            ASSERT(v1.approx_zero());
            nnm::Vector2 v2(nnm::epsilon, 0.0f);
            ASSERT(v2.approx_zero());
            nnm::Vector2 v3(0.0f, nnm::epsilon);
            ASSERT(v3.approx_zero());
            nnm::Vector2 v4(0.1f, 0.1f);
            ASSERT_FALSE(v4.approx_zero());
        }

        test_section("dot");
        {
            nnm::Vector2 v1(2.0f, 3.0f);
            nnm::Vector2 v2(4.0f, 5.0f);
            ASSERT(v1.dot(v2) == 23.0f);
        }

        test_section("reflect");
        {
            nnm::Vector2 incident(3.0f, 4.0f);
            nnm::Vector2 normal(1.0f, 0.0f);
            ASSERT(incident.reflect(normal) == nnm::Vector2(-3.0f, 4.0f));
        }

        test_section("project");
        {
            const nnm::Vector2 v1 { 1.0f, 0.0f };
            const nnm::Vector2 v2 { 0.0f, 1.0f };
            ASSERT(v1.project(v2).approx_equal({ 0.0f, 0.0f }));

            const nnm::Vector2 v3 { 1.0f, 1.0f };
            const nnm::Vector2 v4 { 2.0f, 2.0f };
            ASSERT(v3.project(v4).approx_equal({ 1.0f, 1.0f }));

            const nnm::Vector2 v5 { 1.0f, -2.0f };
            const nnm::Vector2 v6 { -3.0f, 4.0f };
            ASSERT(v5.project(v6).approx_equal({ 1.32f, -1.76f }));
        }

        test_section("rotate");
        {
            nnm::Vector2 v(1.0f, 0.0f);
            ASSERT(v.rotate(nnm::radians(90.0f)).approx_equal(nnm::Vector2(0.0f, 1.0f)));
        }

        test_section("inverse");
        {
            nnm::Vector2 v(2.0f, 3.0f);
            ASSERT(v.inverse().approx_equal(nnm::Vector2(1.0f / 2.0f, 1.0f / 3.0f)));
        }

        test_section("clamp_length");
        {
            ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 5.0f) == nnm::Vector2(3.0f, 4.0f));
            ASSERT(nnm::Vector2(1.0f, 2.0f).clamp_length(0.5f, 3.0f) == nnm::Vector2(1.0f, 2.0f));
            ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 2.0f).approx_equal(nnm::Vector2(1.2f, 1.6f)));
            ASSERT(nnm::approx_equal(nnm::Vector2(1.0f, 1.0f).clamp_length(2.0f, 5.0f).length(), 2.0f));
            ASSERT(nnm::Vector2(5.0f, 6.0f).clamp_length(2.0f, 5.0f).length() == 5.0f);
        }

        test_section("Equality and Inequality Operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            const nnm::Vector2 v2(3.0f, 4.0f);
            const nnm::Vector2 v3(1.0f, 2.0f);
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("Arithmetic Operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            const nnm::Vector2 v2(3.0f, 4.0f);
            ASSERT(v1 * v2 == nnm::Vector2(3.0f, 8.0f));
            ASSERT(v1 * 2.0f == nnm::Vector2(2.0f, 4.0f));
            ASSERT(v2 / v1 == nnm::Vector2(3.0f, 2.0f));
            ASSERT(v2 / 2.0f == nnm::Vector2(1.5f, 2.0f));
            ASSERT(v1 + v2 == nnm::Vector2(4.0f, 6.0f));
            ASSERT(v2 - v1 == nnm::Vector2(2.0f, 2.0f));
            ASSERT(+v1 == v1);
            ASSERT(-v1 == nnm::Vector2(-1.0f, -2.0f));
        }

        test_section("Compound Assignment Operators");
        {
            nnm::Vector2 v1(1.0f, 2.0f);
            nnm::Vector2 v2(3.0f, 4.0f);
            nnm::Vector2 v_copy(v1);

            v1 *= v2;
            ASSERT(v1 == nnm::Vector2(3.0f, 8.0f));
            v1 = v_copy;

            v1 *= 2.0f;
            ASSERT(v1 == nnm::Vector2(2.0f, 4.0f));
            v1 = v_copy;

            v2 /= v1;
            ASSERT(v2 == nnm::Vector2(3.0f, 2.0f));

            v2 /= 2.0f;
            ASSERT(v2 == nnm::Vector2(1.5f, 1.0f));
            v2 = v_copy;

            v1 += v2;
            ASSERT(v1 == nnm::Vector2(2.0f, 4.0f));
            v1 = v_copy;

            v2 -= v1;
            ASSERT(v2 == nnm::Vector2(0.0f, 0.0f));
            v2 = v_copy;
        }

        test_section("Comparison Operator");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            const nnm::Vector2 v2(3.0f, 4.0f);
            ASSERT(v1 < v2);
        }

        test_section("Indexing Operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            ASSERT(v1[0] == 1.0f);
            ASSERT(v1[1] == 2.0f);

            ASSERT(v1[nnm::Axis2::x] == 1.0f);
            ASSERT(v1[nnm::Axis2::y] == 2.0f);
        }

        test_section("Conversion Operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
        }
    }

    test_case("Vector2i");
    {
        test_section("Default constructor");
        {
            const nnm::Vector2i v;
            ASSERT(v.x == 0);
            ASSERT(v.y == 0);
        }

        test_section("Constructor with params");
        {
            const nnm::Vector2i v(1, 2);
            ASSERT(v.x == 1);
            ASSERT(v.y == 2);
        }

        test_section("Static methods");
        {
            const auto all_threes = nnm::Vector2i::all(3);
            ASSERT(all_threes.x == 3);
            ASSERT(all_threes.y == 3);

            const auto zero = nnm::Vector2i::zero();
            ASSERT(zero.x == 0);
            ASSERT(zero.y == 0);

            const auto one = nnm::Vector2i::one();
            ASSERT(one.x == 1);
            ASSERT(one.y == 1);
        }

        test_section("abs");
        {
            ASSERT(nnm::Vector2i(1, -2).abs() == nnm::Vector2i(1, 2));
        }

        test_section("aspect_ratio");
        {
            ASSERT(nnm::Vector2i(1, -2).aspect_ratio() == 1.0f / -2.0f);
        }

        test_section("clamp");
        {
            ASSERT(nnm::Vector2i(1, -3).clamp({ 1, -2 }, { 2, 2 }) == nnm::Vector2i(1, -2));
        }

        test_section("length_sqrd");
        {
            ASSERT(nnm::Vector2i(3, 4).length_sqrd() == 25);
            ASSERT(nnm::Vector2i(-2, 5).length_sqrd() == 29);
            ASSERT(nnm::Vector2i(0, 0).length_sqrd() == 0);
        }

        test_section("length");
        {
            ASSERT(nnm::approx_equal(nnm::Vector2i(3, 4).length(), 5.0f));
            ASSERT(nnm::approx_equal(nnm::Vector2i(-2, 5).length(), nnm::sqrt(29.0f)));
            ASSERT(nnm::approx_equal(nnm::Vector2i(0, 0).length(), 0.0f));
        }

        test_section("min/max_axis");
        {
            nnm::Vector2i v1(3, 4);
            ASSERT(v1.max_axis() == nnm::Axis2::y);
            ASSERT(v1.min_axis() == nnm::Axis2::x);

            nnm::Vector2i v2(2, 5);
            ASSERT(v2.max_axis() == nnm::Axis2::y);
            ASSERT(v2.min_axis() == nnm::Axis2::x);

            nnm::Vector2i v3(0, 0);
            ASSERT(v3.max_axis() == nnm::Axis2::x);
            ASSERT(v3.min_axis() == nnm::Axis2::x);
        }

        test_section("Equality and Inequality Operators");
        {
            const nnm::Vector2i v1(1, 2);
            const nnm::Vector2i v2(3, 4);
            const nnm::Vector2i v3(1, 2);
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("Arithmetic Operators");
        {
            const nnm::Vector2i v1(1, 2);
            const nnm::Vector2i v2(3, 4);
            ASSERT(v1 % v2 == nnm::Vector2i(1, 2));
            ASSERT(v1 % 2 == nnm::Vector2i(1, 0));
            ASSERT(v1 * v2 == nnm::Vector2i(3, 8));
            ASSERT(v1 * 2 == nnm::Vector2i(2, 4));
            ASSERT(v1 + v2 == nnm::Vector2i(4, 6));
            ASSERT(v2 - v1 == nnm::Vector2i(2, 2));
            ASSERT(v2 / v1 == nnm::Vector2i(3, 2));
            ASSERT(v2 / 2 == nnm::Vector2i(1, 2));
            ASSERT(+v1 == v1);
            ASSERT(-v1 == nnm::Vector2i(-1, -2));
        }

        test_section("Compound Assignment Operators");
        {
            nnm::Vector2i v1(1, 2);
            nnm::Vector2i v2(3, 4);
            nnm::Vector2i v_copy(v1);

            v1 *= v2;
            ASSERT(v1 == nnm::Vector2i(3, 8));
            v1 = v_copy;

            v1 *= 2;
            ASSERT(v1 == nnm::Vector2i(2, 4));
            v1 = v_copy;

            v2 /= v1;
            ASSERT(v2 == nnm::Vector2i(3, 2));

            v2 /= 2;
            ASSERT(v2 == nnm::Vector2i(1, 1));
            v2 = v_copy;

            v1 += v2;
            ASSERT(v1 == nnm::Vector2i(2, 4));
            v1 = v_copy;

            v2 -= v1;
            ASSERT(v2 == nnm::Vector2i(0, 0));
            v2 = v_copy;
        }

        test_section("Comparison Operator");
        {
            const nnm::Vector2i v1(1, 2);
            const nnm::Vector2i v2(3, 4);
            ASSERT(v1 < v2);
        }

        test_section("Indexing Operators");
        {
            const nnm::Vector2i v1(1, 2);
            ASSERT(v1[0] == 1);
            ASSERT(v1[1] == 2);

            ASSERT(v1[nnm::Axis2::x] == 1);
            ASSERT(v1[nnm::Axis2::y] == 2);
        }

        test_section("Conversion Operators");
        {
            const nnm::Vector2i v1(1, 2);
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
        }
    }

    test_case("Vector3");
    {
        test_section("Constructors");
        {
            const nnm::Vector3 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);

            const nnm::Vector3 v2(nnm::Vector3i(1, 2, 3));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == 3.0f);

            const nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
            ASSERT(v3.z == 3.0f);
        }

        test_section("Static methods");
        {
            const auto v1 = nnm::Vector3::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);

            const auto v2 = nnm::Vector3::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);

            const auto v3 = nnm::Vector3::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
        }

        test_section("abs");
        {
            ASSERT(nnm::Vector3(0.0f, 1.0f, -2.0f).abs() == nnm::Vector3(0.0f, 1.0f, 2.0f));
        }

        test_section("ceil");
        {
            ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).ceil() == nnm::Vector3(1.0f, -2.0f, 2.0f));
        }

        test_section("clamp");
        {
            const nnm::Vector3 v(0.0f, 10.0f, -2.0f);
            const nnm::Vector3 min(-1.0f, 12.0f, -5.0f);
            const nnm::Vector3 max(1.0f, 12.0f, -3.0f);
            ASSERT(v.clamp(min, max) == nnm::Vector3(0.0f, 12.0f, -3.0f));
        }

        test_section("normalize");
        {
            const nnm::Vector3 v(1.0f, -2.0f, 3.0f);
            ASSERT(v.normalize().approx_equal(nnm::Vector3(0.267261f, -0.534522f, 0.801784f)));
        }

        test_section("direction_to");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            auto direction = from.direction_to(to);
            ASSERT(direction.approx_equal(nnm::Vector3::all(0.57735f)));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            direction = from.direction_to(to);
            ASSERT(direction.approx_equal(nnm::Vector3::all(0.57735f)));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(1.0f, 0.0f, 0.0f);
            direction = from.direction_to(to);
            ASSERT(nnm::approx_equal(direction.x, 1.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 1.0f, 0.0f);
            direction = from.direction_to(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 1.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 0.0f, 1.0f);
            direction = from.direction_to(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 1.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            direction = from.direction_to(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));
        }

        test_section("distance_sqrd_to");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd_to(to), 3.0f));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd_to(to), 12.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(3.0f, 0.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd_to(to), 9.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 4.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd_to(to), 16.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd_to(to), 0.0f));
        }

        test_section("distance_to");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), nnm::sqrt(3.0f)));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), nnm::sqrt(12.0f)));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(3.0f, 0.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 3.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 4.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 4.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(from.distance_to(to), 0.0f));
        }

        test_section("floor");
        {
            ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).floor() == nnm::Vector3(0.0f, -3.0f, 1.0f));
        }

        test_section("length_sqrd");
        {
            const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(v.length_sqrd(), 14.0f));
        }

        test_section("length");
        {
            const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
        }

        test_section("lerp");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(3.0f, 5.0f, -2.0f);
            ASSERT(from.lerp(to, 0.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
            ASSERT(from.lerp(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
            ASSERT(from.lerp(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
            ASSERT(from.lerp(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
        }

        test_section("min/max_axis");
        {
            nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            ASSERT(v1.max_axis() == nnm::Axis3::y);
            ASSERT(v1.min_axis() == nnm::Axis3::z);

            nnm::Vector3 v2(-100.0f, 5.0f, 100.0f);
            ASSERT(v2.max_axis() == nnm::Axis3::z);
            ASSERT(v2.min_axis() == nnm::Axis3::x);

            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.max_axis() == nnm::Axis3::x);
            ASSERT(v3.min_axis() == nnm::Axis3::x);
        }

        test_section("approx_equal");
        {
            nnm::Vector3 v1(1.0f, 1.0f, 1.0f);
            nnm::Vector3 v2(1.0f + nnm::epsilon / 2.0f, 1.0f, 1.0f);
            ASSERT(v1.approx_equal(v2));
            nnm::Vector3 v3(1.0f, 1.0f, 1.0f);
            nnm::Vector3 v4(1.0f + 2.0f * nnm::epsilon, 1.0f, 1.0f);
            ASSERT_FALSE(v3.approx_equal(v4));
        }

        test_section("approx_zero");
        {
            nnm::Vector3 v1(0.0f, 0.0f, 0.0f);
            ASSERT(v1.approx_zero());
            nnm::Vector3 v2(nnm::epsilon, 0.0f, 0.0f);
            ASSERT(v2.approx_zero());
            nnm::Vector3 v3(0.0f, nnm::epsilon, nnm::epsilon);
            ASSERT(v3.approx_zero());
            nnm::Vector3 v4(0.1f, 0.1f, 0.1f);
            ASSERT_FALSE(v4.approx_zero());
        }

        test_section("dot");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            ASSERT(v1.dot(v2) == -28.0f);
        }

        test_section("cross");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            ASSERT(v1.cross(v2) == nnm::Vector3::zero());
            const nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
            const nnm::Vector3 v4(-2.0f, 4.0f, 6.0f);
            ASSERT(v3.cross(v4) == nnm::Vector3(0.0f, -12.0f, 8.0f));
        }

        test_section("reflect");
        {
            nnm::Vector3 incident(1.0f, 1.0f, 1.0f);
            nnm::Vector3 normal(0.0f, 1.0f, 0.0f);
            ASSERT(incident.reflect(normal) == nnm::Vector3(1.0f, -1.0f, 1.0f));
        }

        test_section("inverse");
        {
            nnm::Vector3 v(1.0f, 2.0f, -3.0f);
            ASSERT(v.inverse().approx_equal(nnm::Vector3(1.0f, 0.5f, -1.0f / 3.0f)));
        }

        test_section("clamp_length");
        {
            const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(v.clamp_length(2.0f, 5.0f).approx_equal(nnm::Vector3(1.0f, 2.0f, 3.0f)));
            ASSERT(v.clamp_length(2.0f, 3.0f).approx_equal(nnm::Vector3(0.80178f, 1.603566f, 2.405352f)));
            ASSERT(v.clamp_length(10.0f, 100.0f).approx_equal(nnm::Vector3(2.67261f, 5.34522f, 8.01784f)));
        }

        test_section("round");
        {
            const nnm::Vector3 v(1.1f, -2.8f, 0.0f);
            ASSERT(v.round() == nnm::Vector3(1.0f, -3.0f, 0.0f));
        }

        test_section("angle");
        {
            const nnm::Vector3 v1(1.0f, 0.0f, 0.0f);
            const nnm::Vector3 v2(0.0f, 1.0f, 0.0f);
            const nnm::Vector3 v3(1.0f, 1.0f, 0.0f);
            ASSERT(nnm::approx_equal(v1.angle(v2), nnm::pi / 2.0f));
            ASSERT(nnm::approx_equal(v1.angle(v3), nnm::pi / 4.0f));
            ASSERT(nnm::approx_zero(v1.angle(v1)));
            ASSERT(nnm::approx_zero(v2.angle(v2)));
            ASSERT(nnm::approx_zero(v3.angle(v3)));
        }

        test_section("rotate");
        {
            const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            const nnm::Vector3 axis(0.0f, 0.0f, 1.0f);
            const float angle = nnm::pi / 2.0f;

            ASSERT(v.rotate(axis, angle).approx_equal(nnm::Vector3(-2.0f, 1.0f, 3.0f)));
            ASSERT(v.rotate(axis, 2.0f * angle).approx_equal(nnm::Vector3(-1.0f, -2.0f, 3.0f)));
            ASSERT(v.rotate(axis, 4.0f * angle).approx_equal(v));
            ASSERT(v.rotate(axis, 0.0f).approx_equal(v));
        }

        test_section("rotate by matrix");
        {
            // TODO
        }

        test_section("transform by matrix");
        {
        }

        nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
        nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
        nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

        test_section("Equality and Inequality Operators");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("Arithmetic Operators");
        {
            ASSERT(v1 * v2 == nnm::Vector3(3.0f, 8.0f, -6.0f));
            ASSERT(v1 * 2.0 == nnm::Vector3(2.0f, 4.0f, 6.0f));
            ASSERT(v2 / v1 == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
            ASSERT(v2 / 2.0 == nnm::Vector3(1.5f, 2.0f, -1.0f));
            ASSERT(v1 + v2 == nnm::Vector3(4.0f, 6.0f, 1.0f));
            ASSERT(v2 - v1 == nnm::Vector3(2.0f, 2.0f, -5.0f));
            ASSERT(+v1 == v1);
            ASSERT(-v1 == nnm::Vector3(-1.0f, -2.0f, -3.0f));
        }

        test_section("Compound Assignment Operators");
        {
            nnm::Vector3 v1_copy(v1);
            nnm::Vector3 v2_copy(v2);

            v1 *= v2;
            ASSERT(v1 == nnm::Vector3(3.0f, 8.0f, -6.0f));
            v1 = v1_copy;

            v1 *= 2.0f;
            ASSERT(v1 == nnm::Vector3(2.0f, 4.0f, 6.0f));
            v1 = v1_copy;

            v2 /= v1;
            ASSERT(v2 == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
            v2 = v2_copy;

            v2 /= 2.0f;
            ASSERT(v2 == nnm::Vector3(1.5f, 2.0f, -1.0f));
            v2 = v2_copy;

            v1 += v2;
            ASSERT(v1 == nnm::Vector3(4.0f, 6.0f, 1.0f));
            v1 = v1_copy;

            v2 -= v1;
            ASSERT(v2 == nnm::Vector3(2.0f, 2.0f, -5.0f));
            v2 = v2_copy;
        }

        test_section("Comparison Operator");
        {
            ASSERT(v1 < v2);
        }

        test_section("Indexing Operators");
        {
            ASSERT(v1[0] == 1.0f);
            ASSERT(v1[1] == 2.0f);
            ASSERT(v1[2] == 3.0f);

            ASSERT(v1[nnm::Axis3::x] == 1.0f);
            ASSERT(v1[nnm::Axis3::y] == 2.0f);
            ASSERT(v1[nnm::Axis3::z] == 3.0f);
        }

        test_section("Conversion Operators");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
        }
    }

    test_case("Vector3i");
    {
        test_section("Constructors");
        {
            const nnm::Vector3i v_default;
            ASSERT(v_default.x == 0);
            ASSERT(v_default.y == 0);
            ASSERT(v_default.z == 0);
            const nnm::Vector3i v_with_params(1, -2, 3);
            ASSERT(v_with_params.x == 1);
            ASSERT(v_with_params.y == -2);
            ASSERT(v_with_params.z == 3);
        }

        test_section("Static methods");
        {
            const auto v_all_threes = nnm::Vector3i::all(3);
            ASSERT(v_all_threes.x == 3);
            ASSERT(v_all_threes.y == 3);
            ASSERT(v_all_threes.z == 3);
            const auto v_zero = nnm::Vector3i::zero();
            ASSERT(v_zero.x == 0);
            ASSERT(v_zero.y == 0);
            ASSERT(v_zero.z == 0);
            const auto v_one = nnm::Vector3i::one();
            ASSERT(v_one.x == 1);
            ASSERT(v_one.y == 1);
            ASSERT(v_one.z == 1);
        }

        test_section("abs");
        {
            nnm::Vector3i v(0, -2, 3);
            ASSERT(v.abs() == nnm::Vector3i(0, 2, 3));
        }

        test_section("clamp");
        {
            nnm::Vector3i v(0, -2, 3);
            ASSERT(v.clamp({ -1, -3, -2 }, { 1, 5, 100 }) == nnm::Vector3i(0, -2, 3));
            ASSERT(v.clamp({ 1, 3, 5 }, { 2, 5, 100 }) == nnm::Vector3i(1, 3, 5));
            ASSERT(v.clamp({ -10, -5, -100 }, { -1, -4, 3 }) == nnm::Vector3i(-1, -4, 3));
        }

        test_section("length_sqrd");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.length_sqrd() == 14);
        }

        test_section("length");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
        }

        test_section("min/max axis");
        {
            nnm::Vector3i v1(1, -2, 3);
            ASSERT(v1.min_axis() == nnm::Axis3::y);
            ASSERT(v1.max_axis() == nnm::Axis3::z);
            nnm::Vector3i v2(-1, 2, -3);
            ASSERT(v2.min_axis() == nnm::Axis3::z);
            ASSERT(v2.max_axis() == nnm::Axis3::y);
        }

        nnm::Vector3i v1(1, 2, -3);
        nnm::Vector3i v2(-3, 4, 100);
        nnm::Vector3i v3(1, 2, -3);

        test_section("Equality and Inequality Operators");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("Arithmetic Operators");
        {
            ASSERT(v1 % v2 == nnm::Vector3i(1, 2, -3));
            ASSERT(v1 % 2 == nnm::Vector3i(1, 0, -1));
            ASSERT(v1 * v2 == nnm::Vector3i(-3, 8, -300));
            ASSERT(v1 * 2 == nnm::Vector3i(2, 4, -6));
            ASSERT(v1 + v2 == nnm::Vector3i(-2, 6, 97));
            ASSERT(v2 - v1 == nnm::Vector3i(-4, 2, 103));
            ASSERT(v2 / v1 == nnm::Vector3i(-3, 2, -33));
            ASSERT(v2 / 2 == nnm::Vector3i(-1, 2, 50));
            ASSERT(+v1 == v1);
            ASSERT(-v1 == nnm::Vector3i(-1, -2, 3));
        }

        test_section("Compound Assignment Operators");
        {
            nnm::Vector3i v1_copy(v1);
            nnm::Vector3i v2_copy(v2);

            v1 *= v2;
            ASSERT(v1 == nnm::Vector3i(-3, 8, -300));
            v1 = v1_copy;

            v1 *= 2;
            ASSERT(v1 == nnm::Vector3i(2, 4, -6));
            v1 = v1_copy;

            v2 /= v1;
            ASSERT(v2 == nnm::Vector3i(-3, 2, -33));
            v2 = v2_copy;

            v2 /= 2;
            ASSERT(v2 == nnm::Vector3i(-1, 2, 50));
            v2 = v2_copy;

            v1 += v2;
            ASSERT(v1 == nnm::Vector3i(-2, 6, 97));
            v1 = v1_copy;

            v2 -= v1;
            ASSERT(v2 == nnm::Vector3i(-4, 2, 103));
            v2 = v2_copy;
        }

        test_section("Comparison Operator");
        {
            ASSERT(v2 < v1);
        }

        test_section("Indexing Operators");
        {
            ASSERT(v1[0] == 1);
            ASSERT(v1[1] == 2);
            ASSERT(v1[2] == -3);

            ASSERT(v1[nnm::Axis3::x] == 1);
            ASSERT(v1[nnm::Axis3::y] == 2);
            ASSERT(v1[nnm::Axis3::z] == -3);
        }

        test_section("Conversion Operators");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
        }
    }

    test_case("Matrix2");
    {
        test_section("Constructors");
        {
            const nnm::Matrix2 mat_default;
            ASSERT(mat_default.c0r0 == 1.0f);
            ASSERT(mat_default.c0r1 == 0.0f);
            ASSERT(mat_default.c1r0 == 0.0f);
            ASSERT(mat_default.c1r1 == 1.0f);

            const nnm::Matrix2 mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat_cols.c0r0 == 1.0f);
            ASSERT(mat_cols.c0r1 == -2.0f);
            ASSERT(mat_cols.c1r0 == -3.0f);
            ASSERT(mat_cols.c1r1 == 4.0f);

            const nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
            ASSERT(mat_elements.c0r0 == 1.0f);
            ASSERT(mat_elements.c0r1 == -2.0f);
            ASSERT(mat_elements.c1r0 == -3.0f);
            ASSERT(mat_elements.c1r1 == 4.0f);
        }

        test_section("Static methods");
        {
            const auto mat_all_three = nnm::Matrix2::all(3.0f);
            ASSERT(mat_all_three.c0r0 == 3.0f);
            ASSERT(mat_all_three.c0r1 == 3.0f);
            ASSERT(mat_all_three.c1r0 == 3.0f);
            ASSERT(mat_all_three.c1r1 == 3.0f);

            const auto mat_zero = nnm::Matrix2::zero();
            ASSERT(mat_zero.c0r0 == 0.0f);
            ASSERT(mat_zero.c0r1 == 0.0f);
            ASSERT(mat_zero.c1r0 == 0.0f);
            ASSERT(mat_zero.c1r1 == 0.0f);

            const auto mat_one = nnm::Matrix2::one();
            ASSERT(mat_one.c0r0 == 1.0f);
            ASSERT(mat_one.c0r1 == 1.0f);
            ASSERT(mat_one.c1r0 == 1.0f);
            ASSERT(mat_one.c1r1 == 1.0f);

            const auto mat_identity = nnm::Matrix2::identity();
            ASSERT(mat_identity.c0r0 == 1.0f);
            ASSERT(mat_identity.c0r1 == 0.0f);
            ASSERT(mat_identity.c1r0 == 0.0f);
            ASSERT(mat_identity.c1r1 == 1.0f);
        }

        test_section("trace");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(nnm::approx_equal(mat.trace(), 5.0f));
        }

        test_section("determinant");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(nnm::approx_equal(mat.determinant(), -2.0f));
        }

        test_section("minor");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.minor(0, 0) == 4.0f);
            ASSERT(mat.minor(0, 1) == -3.0f);
            ASSERT(mat.minor(1, 0) == -2.0f);
            ASSERT(mat.minor(1, 1) == 1.0f);
        }

        test_section("cofactor");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.cofactor_at(0, 0) == 4.0f);
            ASSERT(mat.cofactor_at(0, 1) == 3.0f);
            ASSERT(mat.cofactor_at(1, 0) == 2.0f);
            ASSERT(mat.cofactor_at(1, 1) == 1.0f);
            ASSERT(mat.cofactor() == nnm::Matrix2({ 4.0f, 3.0f }, { 2.0f, 1.0f }));
        }

        test_section("transpose");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.transpose() == nnm::Matrix2({ 1.0f, -3.0f }, { -2.0f, 4.0f }));
        }

        test_section("adjugate");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.adjugate() == nnm::Matrix2({ 4.0f, 2.0f }, { 3.0f, 1.0f }));
        }

        test_section("inverse");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            const std::optional<nnm::Matrix2> mat_inv = mat.safe_inverse();
            ASSERT(mat_inv.has_value());
            ASSERT(mat.safe_inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT(mat.inverse().approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT_FALSE(nnm::Matrix2::zero().safe_inverse().has_value());
        }

        test_section("approx");
        {
            const nnm::Matrix2 mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat1.approx_equal({ { 1.00000001f, -1.9999999f }, { -3.00000001f, 3.99999999f } }));
            ASSERT_FALSE(mat1.approx_equal({ { 1.1f, -1.9f }, { -3.1f, 3.9f } }));
            const nnm::Matrix2 mat2({ 0.00000001f, -0.00000001f }, { -0.00000001f, 0.00000001f });
            ASSERT(mat2.approx_zero());
            ASSERT_FALSE(mat1.approx_zero());
        }

        test_section("accessors");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.at(0, 0) == 1.0f);
            ASSERT(mat.at(0, 1) == -2.0f);
            ASSERT(mat.at(1, 0) == -3.0f);
            ASSERT(mat.at(1, 1) == 4.0f);

            ASSERT(mat[0][0] == 1.0f);
            ASSERT(mat[0][1] == -2.0f);
            ASSERT(mat[1][0] == -3.0f);
            ASSERT(mat[1][1] == 4.0f);
        }

        nnm::Matrix2 m1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        nnm::Matrix2 m2({ -4.0f, 3.0f }, { 2.0f, -1.0f });
        nnm::Matrix2 m3({ 1.0f, -2.0f }, { -3.0f, 4.0f });

        test_section("equality and inequality");
        {
            ASSERT(m1 == m3);
            ASSERT_FALSE(m1 != m3);
            ASSERT(m1 != m2);
            ASSERT_FALSE(m1 == m2);
        }

        test_section("arithmetic");
        {
            ASSERT(m1 * m2 == nnm::Matrix2({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
            ASSERT(m1 * 2.0f == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
            ASSERT((m2 / 2.0f).approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));

            ASSERT((nnm::Matrix2::identity() * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(1.0f, 2.0f)));
            ASSERT((m1 * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(-5.0f, 6.0f)));
        }

        test_section("compound assignment");
        {
            nnm::Matrix2 m1_copy(m1);
            nnm::Matrix2 m2_copy(m2);

            m1 *= m2;
            ASSERT(m1 == nnm::Matrix2({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
            m1 = m1_copy;

            m1 *= 2.0f;
            ASSERT(m1 == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
            m1 = m1_copy;

            m2 /= 2.0f;
            ASSERT(m2.approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
            m2 = m2_copy;
        }

        test_section("comparison");
        {
            ASSERT(m2 < m1);
            ASSERT_FALSE(m1 < m2);
        }

        test_section("bool conversion");
        {
            ASSERT(static_cast<bool>(m1));
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix2::zero()));
        }
    }

    test_case("Basis2");
    {
        test_section("constructor");
        {
            const nnm::Basis2 b;
            ASSERT(b.matrix == nnm::Matrix2::identity());
        }

        test_section("from matrix");
        {
            const auto m1 = nnm::Matrix2::identity();
            const auto b1 = nnm::Basis2(m1);
            ASSERT(b1 == nnm::Basis2());
            ASSERT(b1.matrix == nnm::Matrix2::identity());
            const auto m2 = nnm::Matrix2::zero();
            const auto b2 = nnm::Basis2::safe_from_matrix(m2);
            ASSERT_FALSE(b2.has_value());
            const auto b3 = nnm::Basis2::safe_from_matrix(m1);
            ASSERT(b3.has_value());
            ASSERT(b3.value().matrix == nnm::Matrix2::identity());
        }

        test_section("from rotation");
        {
            const auto b1 = nnm::Basis2::from_rotation(0.0f);
            ASSERT(b1.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
            const auto b2 = nnm::Basis2::from_rotation(nnm::pi / 2.0f);
            ASSERT(b2.matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
            const auto b3 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT(b3.matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
            const auto b4 = nnm::Basis2::from_rotation(2.0f * nnm::pi);
            ASSERT(b4.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
        }

        test_section("from scale");
        {
            const auto b1 = nnm::Basis2::safe_from_scale({ 2.0f, -3.0f });
            ASSERT(b1.has_value());
            ASSERT(b1.value().matrix == nnm::Matrix2({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
            const auto b2 = nnm::Basis2::from_scale({ 2.0f, -3.0f });
            ASSERT(b2.matrix == nnm::Matrix2({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
            const auto b3 = nnm::Basis2::safe_from_scale({ 0.0f, 1.0f });
            ASSERT_FALSE(b3.has_value());
            const auto b4 = nnm::Basis2::safe_from_scale({ -1.0f, 0.0f });
            ASSERT_FALSE(b4.has_value());
        }

        test_section("from shear");
        {
            const auto b1 = nnm::Basis2::safe_from_shear({ 2.0f, -3.0f });
            ASSERT(b1.has_value());
            ASSERT(b1.value().matrix == nnm::Matrix2({ 1.0f, 2.0f }, { -3.0f, 1.0f }));
            const auto b2 = nnm::Basis2::from_shear({ 2.0f, -3.0f });
            ASSERT(b2.matrix == nnm::Matrix2({ 1.0f, 2.0f }, { -3.0f, 1.0f }));
            const auto b3 = nnm::Basis2::safe_from_shear({ 1.0f, 1.0f });
            ASSERT_FALSE(b3.has_value());
        }

        test_section("valid");
        {
            const nnm::Basis2 b1;
            const auto b2 = nnm::Basis2(nnm::Matrix2::zero());
            const auto b3 = nnm::Basis2({ { 1.0f, -2.0f }, { 2.0f, -4.0f } });
            ASSERT(b1.valid());
            ASSERT_FALSE(b2.valid());
            ASSERT_FALSE(b3.valid());
        }

        test_section("matrix");
        {
            ASSERT(nnm::Basis2().matrix == nnm::Matrix2::identity());
            ASSERT(nnm::Basis2().matrix == nnm::Matrix2::identity());
        }

        test_section("rotate");
        {
            const nnm::Basis2 b1;
            ASSERT(b1.rotate(0.0f).approx_equal(b1));
            ASSERT(b1.rotate(nnm::pi / 2.0f).matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
            ASSERT(b1.rotate(-nnm::pi / 2.0f).matrix.approx_equal({ { 0.0f, -1.0f }, { 1.0f, 0.0f } }));
            ASSERT(b1.rotate(2.0f * nnm::pi).approx_equal(b1));
            const auto b2 = nnm::Basis2::from_scale({ 2.0f, 0.5f });
            const auto b2_rotated = b2.rotate(nnm::pi / 4.0f).matrix;
            ASSERT(b2_rotated.approx_equal(
                { { nnm::sqrt(2.0f), nnm::sqrt(2.0f) / 4.0f }, { -nnm::sqrt(2.0f), nnm::sqrt(2.0f) / 4.0f } }));
        }

        test_section("scale");
        {
            const nnm::Basis2 b1;
            ASSERT_FALSE(b1.safe_scale({ 0.0f, 0.0f }).has_value());
            ASSERT_FALSE(b1.scale({ 0.0f, 0.0f }).valid());
            ASSERT(b1.scale({ 0.0f, 0.0f }).matrix.approx_equal(nnm::Matrix2::zero()));

            ASSERT(b1.safe_scale({ 2.0f, 2.0f }).has_value());
            ASSERT(b1.safe_scale({ 2.0f, 2.0f }).value().matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 2.0f } }));
            ASSERT(b1.scale({ 2.0f, 2.0f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 2.0f } }));

            ASSERT(b1.safe_scale({ 2.0f, 0.5f }).has_value());
            ASSERT(b1.safe_scale({ 2.0f, 0.5f }).value().matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 0.5f } }));
            ASSERT(b1.scale({ 2.0f, 0.5f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 0.5f } }));

            ASSERT(b1.safe_scale({ -1.0f, -1.0f }).has_value());
            ASSERT(b1.safe_scale({ -1.0f, -1.0f }).value().matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
            ASSERT(b1.scale({ -1.0f, -1.0f }).matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
        }

        test_section("shear");
        {
            const nnm::Basis2 b1;
            ASSERT(b1.safe_shear({ 0.0f, 0.0f }).has_value());
            ASSERT(b1.safe_shear({ 0.0f, 0.0f }).value().matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
            ASSERT(b1.shear({ 0.0f, 0.0f }).matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));

            ASSERT_FALSE(b1.safe_shear({ 1.0f, 1.0f }).has_value());
            ASSERT(b1.shear({ 1.0f, 1.0f }).matrix.approx_equal({ { 1.0f, 1.0f }, { 1.0f, 1.0f } }));

            ASSERT(b1.safe_shear({ 2.0f, -0.5f }).has_value());
            ASSERT(b1.safe_shear({ 2.0f, -0.5f }).value().matrix.approx_equal({ { 1.0f, 2.0f }, { -0.5f, 1.0f } }));
            ASSERT(b1.shear({ 2.0f, -0.5f }).matrix.approx_equal({ { 1.0f, 2.0f }, { -0.5f, 1.0f } }));
        }

        test_section("approx equal");
        {
            const nnm::Basis2 b1;
            ASSERT(b1.approx_equal(nnm::Basis2({ { 1.0000000f, 0.000000001f }, { -0.000000001f, 0.9999999f } })));
            const auto b2 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT_FALSE(b2.approx_equal(nnm::Basis2()));
        }

        test_section("accessors");
        {
            auto b1 = nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b1.at(0, 0) == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
            ASSERT(b1.at(1, 1) == 4.0f);
            ASSERT(b1.at(0, 0) == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
            ASSERT(b1[0] == nnm::Vector2(1.0f, -2.0f));
            ASSERT(b1[1] == nnm::Vector2(-3.0f, 4.0f));
        }

        test_section("equality");
        {
            const nnm::Basis2 b1;
            const nnm::Basis2 b2;
            const auto b3 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT(b1 == b2);
            ASSERT_FALSE(b1 != b2);
            ASSERT(b1 != b3);
            ASSERT_FALSE(b1 == b3);
        }

        test_section("comparison");
        {
            const auto b1 = nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const auto b2 = nnm::Basis2({ { -4.0f, 3.0f }, { 2.0f, -1.0f } });
            ASSERT(b2 < b1);
        }
    }

    test_case("Matrix3");
    {
        test_section("constructors");
        {
            const nnm::Matrix3 default_mat;
            ASSERT(default_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
            ASSERT(default_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
            ASSERT(default_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));

            const nnm::Matrix3 cols(
                nnm::Vector3(1.0f, 2.0f, 3.0f), nnm::Vector3(-1.0f, -2.0f, -3.0f), nnm::Vector3(2.0f, 4.0f, 6.0f));
            ASSERT(cols.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(cols.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(cols.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));

            const nnm::Matrix3 elems(1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, 2.0f, 4.0f, 6.0f);
            ASSERT(elems.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(elems.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(elems.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("static methods");
        {
            const auto threes = nnm::Matrix3::all(3.0f);
            ASSERT(threes.columns[0] == nnm::Vector3::all(3.0f));
            ASSERT(threes.columns[1] == nnm::Vector3::all(3.0f));
            ASSERT(threes.columns[2] == nnm::Vector3::all(3.0f));

            const auto zeros = nnm::Matrix3::zero();
            ASSERT(zeros.columns[0] == nnm::Vector3::zero());
            ASSERT(zeros.columns[1] == nnm::Vector3::zero());
            ASSERT(zeros.columns[2] == nnm::Vector3::zero());

            const auto ones = nnm::Matrix3::one();
            ASSERT(ones.columns[0] == nnm::Vector3::one());
            ASSERT(ones.columns[1] == nnm::Vector3::one());
            ASSERT(ones.columns[2] == nnm::Vector3::one());

            const auto identity_mat = nnm::Matrix3::identity();
            ASSERT(identity_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
            ASSERT(identity_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
            ASSERT(identity_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
        }

        const nnm::Matrix3 m1({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f });

        test_section("trace");
        {
            ASSERT(nnm::approx_equal(m1.trace(), 5.0f));
        }

        test_section("determinant");
        {
            ASSERT(nnm::approx_equal(m1.determinant(), 64.0f));
            ASSERT(nnm::approx_equal(nnm::Matrix3::identity().determinant(), 1.0f));
            ASSERT(nnm::approx_equal(nnm::Matrix3::zero().determinant(), 0.0f));
        }

        test_section("minor");
        {
            const nnm::Matrix3 result({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
            ASSERT(nnm::approx_equal(m1.minor_at(0, 0), result.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.minor_at(1, 2), result.at(1, 2)));
            ASSERT(m1.minor().approx_equal(result));
        }

        test_section("cofactor");
        {
            const nnm::Matrix3 result({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
            ASSERT(nnm::approx_equal(m1.cofactor_at(0, 0), result.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.cofactor_at(1, 2), result.at(1, 2)));
            ASSERT(m1.cofactor().approx_equal(result));
        }

        test_section("transpose");
        {
            const nnm::Matrix3 result({ 1.0f, -3.0f, 2.0f }, { 2.0f, -2.0f, -4.0f }, { 3.0f, -1.0f, 6.0f });
            ASSERT(m1.transpose() == result);
        }

        test_section("adjugate");
        {
            const nnm::Matrix3 result({ -16.0f, -24.0f, 4.0f }, { 16.0f, 0.0f, -8.0f }, { 16.0f, 8.0f, 4.0f });
            ASSERT(m1.adjugate().approx_equal(result));
        }

        test_section("inverse");
        {
            const nnm::Matrix3 result(
                { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
            ASSERT(m1.inverse().approx_equal(result));
            ASSERT(m1.safe_inverse().has_value());
            ASSERT(m1.safe_inverse().value().approx_equal(result));
            ASSERT_FALSE(nnm::Matrix3::zero().safe_inverse().has_value());
        }

        test_section("approx");
        {
            const nnm::Matrix3 almost_ident(
                { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
            const nnm::Matrix3 almost_zero(
                { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
            ASSERT(nnm::Matrix3::identity().approx_equal(almost_ident));
            ASSERT_FALSE(almost_zero.approx_equal(almost_ident));
            ASSERT(nnm::Matrix3::zero().approx_zero());
            ASSERT_FALSE(almost_ident.approx_zero());
        }

        test_section("accessors");
        {
            ASSERT(m1.at(0) == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1.at(1) == nnm::Vector3(-3.0f, -2.0f, -1.0f));
            ASSERT(m1.at(0, 0) == 1.0f);
            ASSERT(m1.at(1, 2) == -1.0f);
            ASSERT(m1[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1[1] == nnm::Vector3(-3.0f, -2.0f, -1.0f));
        }

        test_section("sub matrices");
        {
            ASSERT(m1.sub_matrix2_at(0, 0) == nnm::Matrix2({ 1.0f, 2.0f }, { -3.0f, -2.0f }));
            ASSERT(m1.sub_matrix2_at(1, 1) == nnm::Matrix2({ -2.0f, -1.0f }, { -4.0f, 6.0f }));
            ASSERT(
                m1.sub_matrix2(0, 0, nnm::Matrix2({ 1.0f, 2.0f }, { 3.0f, 4.0f }))
                == nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { 3.0f, 4.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
            ASSERT(
                m1.sub_matrix2(1, 1, nnm::Matrix2({ 1.0f, 2.0f }, { 3.0f, 4.0f }))
                == nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { -3.0f, 1.0f, 2.0f }, { 2.0f, 3.0f, 4.0f }));
        }

        test_section("equality");
        {
            ASSERT(m1 == nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
            ASSERT_FALSE(m1 == nnm::Matrix3::identity());
            ASSERT(m1 != nnm::Matrix3::identity());
            ASSERT_FALSE(m1 != nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
        }

        test_section("comparison");
        {
            ASSERT_FALSE(m1 < nnm::Matrix3::identity());
            ASSERT(m1 < nnm::Matrix3::all(10.0f));
        }

        const nnm::Matrix3 m2({ 3.0f, -6.0f, -9.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 2.0f, 10.0f });

        test_section("arithmetic");
        {
            ASSERT((m1 * nnm::Matrix3::identity()).approx_equal(m1));
            const nnm::Matrix3 m1_m2({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
            ASSERT((m1 * m2).approx_equal(m1_m2));
            nnm::Matrix3 m1_copy = m1;
            m1_copy *= m2;
            ASSERT(m1_copy.approx_equal(m1_m2));

            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            ASSERT((m1 * v1).approx_equal({ 13.0f, -6.0f, 23.0f }));

            const nnm::Matrix3 m1_5({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            ASSERT((m1 * 5.0f).approx_equal(m1_5));
            m1_copy = m1;
            m1_copy *= 5.0f;
            ASSERT(m1_copy.approx_equal(m1_5));

            const nnm::Matrix3 m1_2({ 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
            ASSERT((m1 / 2.0f).approx_equal(m1_2));
            m1_copy = m1;
            m1_copy /= 2.0f;
            ASSERT(m1_copy.approx_equal(m1_2));
        }

        test_section("bool conversion");
        {
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix3::zero()));
            ASSERT(static_cast<bool>(nnm::Matrix3::identity()));
        }
    }
    END_TESTS
}
