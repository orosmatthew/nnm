#define NNM_BOUNDS_CHECK
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
        ASSERT(nnm::abs(0.0f) == 0.0f);
        ASSERT(nnm::abs(1.0f) == 1.0f);
        ASSERT(nnm::abs(-1.0f) == 1.0f);
        ASSERT(nnm::abs(0) == 0);
        ASSERT(nnm::abs(1) == 1);
        ASSERT(nnm::abs(-1) == 1);
    }

    test_case("max");
    {
        ASSERT(nnm::max(5.0f, 10.0f) == 10.0f);
        ASSERT(nnm::max(10.0f, 5.0f) == 10.0f);
        ASSERT(nnm::max(-5.0f, -10.0f) == -5.0f);
        ASSERT(nnm::max(-10.0f, -5.0f) == -5.0f);
        ASSERT(nnm::max(0.0f, 0.0f) == 0.0f);
        ASSERT(nnm::max(3.14159f, 2.71828f) == 3.14159f);
        ASSERT(nnm::max(-3.14159f, -2.71828f) == -2.71828f);

        ASSERT(nnm::max(5, 10) == 10);
        ASSERT(nnm::max(10, 5) == 10);
        ASSERT(nnm::max(-5, -10) == -5);
        ASSERT(nnm::max(-10, -5) == -5);
        ASSERT(nnm::max(0, 0) == 0);
    }

    test_case("approx_zero");
    {
        ASSERT(nnm::approx_zero(0.0f));
        ASSERT_FALSE(nnm::approx_zero(0.005f));
        ASSERT_FALSE(nnm::approx_zero(0.01f));
        ASSERT_FALSE(nnm::approx_zero(-0.005f));
        ASSERT_FALSE(nnm::approx_zero(-0.01f));
        ASSERT(nnm::approx_zero(1e-15f));
        ASSERT(nnm::approx_zero(1e-14f));
        ASSERT(nnm::approx_zero(-1e-15f));
        ASSERT(nnm::approx_zero(-1e-14f));
        ASSERT_FALSE(nnm::approx_zero(1.0f));
        ASSERT(nnm::approx_zero(0.0f));
    }

    test_case("approx_equal");
    {
        ASSERT(nnm::approx_equal(1.0f, 1.0f));
        ASSERT_FALSE(nnm::approx_equal(1.0f, 1.005f));
        ASSERT_FALSE(nnm::approx_equal(1.0f, 1.01f));
        ASSERT_FALSE(nnm::approx_equal(1.0f, 1.02f));
        ASSERT_FALSE(nnm::approx_equal(-1.0f, -1.005f));
        ASSERT(nnm::approx_equal(0.0f, 0.0f));
        ASSERT_FALSE(nnm::approx_equal(0.0f, 0.005f));
        ASSERT_FALSE(nnm::approx_equal(0.005f, 0.0f));
        ASSERT(nnm::approx_equal(0.0f, 0.0f));
        ASSERT_FALSE(nnm::approx_equal(1.0f, 1.005f));
        ASSERT(nnm::approx_equal(1.0e20f, 1.000000000001e20f));
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

        ASSERT(nnm::lerp(5.0f, 10.0f, 10.0f) == 55.0f);
        ASSERT(nnm::lerp(5.0f, 10.0f, -10.0f) == -45.0f);
    }

    test_case("lerp_clamped");
    {
        ASSERT(nnm::lerp_clamped(5.0f, 10.0f, 20.0f) == 10.0f);
        ASSERT(nnm::approx_equal(nnm::lerp_clamped(5.0f, 10.0f, 0.5f), 7.5f));
        ASSERT(nnm::lerp_clamped(5.0f, 10.0f, -20.0f) == 5.0f);
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

        ASSERT(nnm::approx_equal(nnm::radians(180.0f), 3.14159f));
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

        ASSERT(nnm::approx_equal(nnm::degrees(3.14159f), 180.0f));
    }

    test_case("asin");
    {
        ASSERT(nnm::approx_equal(nnm::asin(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::asin(0.5f), 0.5235987756f));
        ASSERT(nnm::approx_equal(nnm::asin(-0.5f), -0.5235987756f));
        ASSERT(nnm::approx_equal(nnm::asin(1.0f), 1.570796327f));
        ASSERT(nnm::approx_equal(nnm::asin(-1.0f), -1.570796327f));
    }

    test_case("acos");
    {
        ASSERT(nnm::approx_equal(nnm::acos(1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::acos(0.5f), 1.047197551f));
        ASSERT(nnm::approx_equal(nnm::acos(-0.5f), 2.094395102f));
        ASSERT(nnm::approx_equal(nnm::acos(0.0f), 1.570796327f));
        ASSERT(nnm::approx_equal(nnm::acos(-1.0f), 3.141592654f));
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
    }

    test_case("Vector2");
    {
        test_section("Vector2()");
        {
            const nnm::Vector2 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
        }

        test_section("Vector2(const Vector2i&)");
        {
            const nnm::Vector2 v2(nnm::Vector2i(1, 2));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
        }

        test_section("Vector2(float, float)");
        {
            const nnm::Vector2 v3(1.0f, 2.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
        }

        test_section("all");
        {
            const auto all_threes = nnm::Vector2::all(3.0f);
            ASSERT(all_threes.x == 3.0f);
            ASSERT(all_threes.y == 3.0f);
        }

        test_section("zero");
        {
            const auto zero = nnm::Vector2::zero();
            ASSERT(zero.x == 0.0f);
            ASSERT(zero.y == 0.0f);
        }

        test_section("one");
        {
            const auto one = nnm::Vector2::one();
            ASSERT(one.x == 1.0f);
            ASSERT(one.y == 1.0f);
        }

        test_section("axis_x");
        {
            const auto x = nnm::Vector2::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
        }

        test_section("axis_y");
        {
            const auto y = nnm::Vector2::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
        }

        test_section("abs");
        {
            const nnm::Vector2 v(1.0f, -2.0f);
            ASSERT(v.abs() == nnm::Vector2(1.0f, 2.0f));
        }

        test_section("ceil");
        {
            const nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.ceil() == nnm::Vector2(2.0f, -1.0f));
        }

        test_section("floor");
        {
            const nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.floor() == nnm::Vector2(1.0f, -2.0f));
        }

        test_section("round");
        {
            const nnm::Vector2 v1(1.1f, -1.9f);
            ASSERT(v1.round() == nnm::Vector2(1.0f, -2.0f));
            const nnm::Vector2 v2(1.6f, -1.3f);
            ASSERT(v2.round() == nnm::Vector2(2.0f, -1.0f));
        }

        test_section("aspect_ratio");
        {
            const nnm::Vector2 v(1.0f, -2.0f);
            ASSERT(v.aspect_ratio() == 1.0f / -2.0f);
        }

        test_section("clamp");
        {
            const nnm::Vector2 v(1.1f, -3.0f);
            ASSERT(v.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f }) == nnm::Vector2(1.1f, -2.0f));
        }

        test_section("direction");
        {
            const nnm::Vector2 from1(1.0f, 1.0f);
            const nnm::Vector2 to1(2.0f, 2.0f);
            auto direction1 = from1.direction(to1);
            ASSERT(nnm::approx_equal(direction1.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction1.y, 0.7071067812f));

            const nnm::Vector2 from2(-1.0f, -1.0f);
            const nnm::Vector2 to2(1.0f, 1.0f);
            auto direction2 = from2.direction(to2);
            ASSERT(nnm::approx_equal(direction2.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction2.y, 0.7071067812f));

            const nnm::Vector2 from3(0.0f, 0.0f);
            const nnm::Vector2 to3(1.0f, 0.0f);
            auto direction3 = from3.direction(to3);
            ASSERT(nnm::approx_equal(direction3.x, 1.0f));
            ASSERT(nnm::approx_equal(direction3.y, 0.0f));

            const nnm::Vector2 from4(0.0f, 0.0f);
            const nnm::Vector2 to4(0.0f, 1.0f);
            auto direction4 = from4.direction(to4);
            ASSERT(nnm::approx_equal(direction4.x, 0.0f));
            ASSERT(nnm::approx_equal(direction4.y, 1.0f));

            const nnm::Vector2 from5(1.0f, 2.0f);
            const nnm::Vector2 to5(1.0f, 2.0f);
            auto direction5 = from5.direction(to5);
            ASSERT(nnm::approx_equal(direction5.x, 0.0f));
            ASSERT(nnm::approx_equal(direction5.y, 0.0f));
        }

        test_section("distance_sqrd");
        {
            const nnm::Vector2 from1(1.0f, 1.0f);
            const nnm::Vector2 to1(2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from1.distance_sqrd(to1), 2.0f));

            const nnm::Vector2 from2(-1.0f, -1.0f);
            const nnm::Vector2 to2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from2.distance_sqrd(to2), 8.0f));

            const nnm::Vector2 from3(0.0f, 0.0f);
            const nnm::Vector2 to3(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from3.distance_sqrd(to3), 9.0f));

            const nnm::Vector2 from4(0.0f, 0.0f);
            const nnm::Vector2 to4(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from4.distance_sqrd(to4), 16.0f));

            const nnm::Vector2 from5(1.0f, 2.0f);
            const nnm::Vector2 to5(1.0f, 2.0f);
            ASSERT(nnm::approx_equal(from5.distance_sqrd(to5), 0.0f));
        }

        test_section("distance");
        {
            nnm::Vector2 from(1.0f, 1.0f);
            nnm::Vector2 to(2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(2.0f)));

            from = nnm::Vector2(-1.0f, -1.0f);
            to = nnm::Vector2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(8.0f)));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 3.0f));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 4.0f));

            from = nnm::Vector2(1.0f, 2.0f);
            to = nnm::Vector2(1.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 0.0f));
        }

        test_section("manhattan_distance");
        {
            nnm::Vector2 from(1.0f, 1.0f);
            nnm::Vector2 to(2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 2.0f));

            from = nnm::Vector2(-1.0f, -1.0f);
            to = nnm::Vector2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 4.0f));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 3.0f));

            from = nnm::Vector2(0.0f, 0.0f);
            to = nnm::Vector2(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 4.0f));

            from = nnm::Vector2(1.0f, 2.0f);
            to = nnm::Vector2(1.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 0.0f));
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

        test_section("clamp_length");
        {
            ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 5.0f) == nnm::Vector2(3.0f, 4.0f));
            ASSERT(nnm::Vector2(1.0f, 2.0f).clamp_length(0.5f, 3.0f) == nnm::Vector2(1.0f, 2.0f));
            ASSERT(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 2.0f).approx_equal(nnm::Vector2(1.2f, 1.6f)));
            ASSERT(nnm::approx_equal(nnm::Vector2(1.0f, 1.0f).clamp_length(2.0f, 5.0f).length(), 2.0f));
            ASSERT(nnm::Vector2(5.0f, 6.0f).clamp_length(2.0f, 5.0f).length() == 5.0f);
        }

        test_section("normalize");
        {
            const nnm::Vector2 v(1.1f, -3.0f);
            const auto norm = v.normalize();
            ASSERT(nnm::approx_equal(norm.x, 0.344255f));
            ASSERT(nnm::approx_equal(norm.y, -0.938876f));
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

        test_section("lerp_clamped");
        {
            const nnm::Vector2 from(1.0f, 1.0f);
            const nnm::Vector2 to(3.0f, 5.0f);
            ASSERT(from.lerp_clamped(to, 0.0f) == nnm::Vector2(1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
            ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
            ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
            ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector2(1.0f, 1.0f));
        }

        test_section("dot");
        {
            nnm::Vector2 v1(2.0f, 3.0f);
            nnm::Vector2 v2(4.0f, 5.0f);
            ASSERT(v1.dot(v2) == 23.0f);
        }

        test_section("cross");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            ASSERT(nnm::approx_equal(v1.cross(v2), -2.0f));
        }

        test_section("outer");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            nnm::Matrix2 expected { { -8.0f, 10.0f }, { 12.0f, -15.0f } };
            ASSERT(v1.outer(v2).approx_equal(expected));
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

        test_section("inverse");
        {
            nnm::Vector2 v(2.0f, 3.0f);
            ASSERT(v.inverse().approx_equal(nnm::Vector2(1.0f / 2.0f, 1.0f / 3.0f)));
        }

        test_section("angle");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            ASSERT(nnm::approx_equal(v1.angle(v2), 3.05485f))
        }

        test_section("translate");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            ASSERT(v1.translate(v2).approx_equal({ -2.0f, 2.0f }));
        }

        test_section("rotate");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.rotate(nnm::pi / 4.0f).approx_equal({ 3.53553f, -0.707107f }));
        }

        test_section("scale");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.scale({ 1.5f, -2.0f }).approx_equal({ 3.0f, 6.0f }));
        }

        test_section("shear_x");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.shear_x(nnm::pi / 9.0f).approx_equal({ 0.9080892971f, -3.0f }));
        }

        test_section("shear_y");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.shear_y(-nnm::pi / 9.0f).approx_equal({ 2.0f, -3.7279404686f }));
        }

        test_section("transform(const Basis2&)");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Basis2 basis({ { 1.0f, -2.0f }, { -4.0f, 1.2f } });
            ASSERT(v1.transform(basis).approx_equal({ 14.0f, -7.6f }));
        }

        test_section("transform(const Transform2&, float)");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Transform2 transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
            ASSERT(v1.transform(transform).approx_equal({ 17.0f, -2.8f }));
            ASSERT(v1.transform(transform, 2.3f).approx_equal({ 20.9f, -5.4f }));
        }

        test_section("max_index");
        {
            nnm::Vector2 v1(3.0f, 4.0f);
            ASSERT(v1.max_index() == 1);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.max_index() == 1);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
        }

        test_section("min_index");
        {
            nnm::Vector2 v1(3.0f, 4.0f);
            ASSERT(v1.min_index() == 0);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.min_index() == 0);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.min_index() == 0);
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

        test_section("begin");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.begin() == &v1.x);
        }

        test_section("end");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.end() == &v1.y + 1);
        }

        test_section("at");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.at(0) == 2.0f);
            ASSERT(v1.at(1) == -3.0f);
        }

        test_section("operator[]");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1[0] == 2.0f);
            ASSERT(v1[1] == -3.0f);
        }

        const nnm::Vector2 v1(1.0f, 2.0f);
        const nnm::Vector2 v2(3.0f, 4.0f);
        const nnm::Vector2 v3(1.0f, 2.0f);

        test_section("operator==");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
        }

        const nnm::Vector2 v4(1.0f, 2.0f);
        const nnm::Vector2 v5(3.0f, 4.0f);

        test_section("operator+(const Vector2&)");
        {
            ASSERT(v4 + v5 == nnm::Vector2(4.0f, 6.0f));
        }

        test_section("operator+=");
        {
            nnm::Vector2 v4_copy = v4;
            ASSERT((v4_copy += v5) == nnm::Vector2(4.0f, 6.0f));
        }

        test_section("operator-(const Vector2&)");
        {
            ASSERT(v5 - v4 == nnm::Vector2(2.0f, 2.0f));
        }

        test_section("operator-=");
        {
            nnm::Vector2 v5_copy = v5;
            ASSERT((v5_copy -= v4) == nnm::Vector2(2.0f, 2.0f))
        }

        test_section("operator*(const Vector2&)");
        {
            ASSERT(v4 * v5 == nnm::Vector2(3.0f, 8.0f));
        }

        test_section("operator*=(const Vector2&)");
        {
            nnm::Vector2 v4_copy = v4;
            ASSERT((v4_copy *= v5) == nnm::Vector2(3.0f, 8.0f));
        }

        test_section("operator*(const Matrix2&)");
        {
            nnm::Matrix2 matrix { { 2.0f, -3.0f }, { 1.0f, -0.5f } };
            ASSERT((nnm::Vector2(2.0f, -3.0f) * matrix).approx_equal({ 13.0f, 3.5f }))
        }

        test_section("operator*(float)");
        {
            ASSERT(v4 * 2.0f == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator*(float, const Vector2&)");
        {
            ASSERT(2.0f * v4 == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator*=(float)");
        {
            nnm::Vector2 v4_copy = v4;
            ASSERT((v4_copy *= 2.0f) == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator/(const Vector2&)");
        {
            ASSERT(v5 / v4 == nnm::Vector2(3.0f, 2.0f));
        }

        test_section("operator/=(const Vector2&)");
        {
            nnm::Vector2 v5_copy = v5;
            ASSERT((v5_copy /= v4) == nnm::Vector2(3.0f, 2.0f));
        }

        test_section("operator/(float)");
        {
            ASSERT(v5 / 2.0f == nnm::Vector2(1.5f, 2.0f));
        }

        test_section("operator/(float, const Vector2&)");
        {
            ASSERT((2.0f / v5).approx_equal(nnm::Vector2(0.666666f, 0.5f)));
        }

        test_section("operator/=(float)");
        {
            nnm::Vector2 v5_copy = v5;
            ASSERT((v5_copy /= 2.0f) == nnm::Vector2(1.5f, 2.0f));
        }

        test_section("operator+");
        {
            ASSERT(+v4 == v4);
        }

        test_section("operator-");
        {
            ASSERT(-v4 == nnm::Vector2(-1.0f, -2.0f));
        }

        test_section("operator<");
        {
            const nnm::Vector2 v6(1.0f, 2.0f);
            const nnm::Vector2 v7(3.0f, 4.0f);
            ASSERT(v6 < v7);
            ASSERT_FALSE(v7 < v6);
        }

        test_section("operator bool");
        {
            const nnm::Vector2 v8(1.0f, 2.0f);
            ASSERT(static_cast<bool>(v8));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
        }
    }

    test_case("Vector2i");
    {
        test_section("Vector2i()");
        {
            const nnm::Vector2i v1;
            ASSERT(v1.x == 0);
            ASSERT(v1.y == 0);
        }

        test_section("Vector2i(const Vector2&)");
        {
            const nnm::Vector2i v1(nnm::Vector2(1.1f, -10.7f));
            ASSERT(v1.x == 1);
            ASSERT(v1.y == -10);
        }

        test_section("Vector2i(int, int)");
        {
            const nnm::Vector2i v2(1, 2);
            ASSERT(v2.x == 1);
            ASSERT(v2.y == 2);
        }

        test_section("all");
        {
            const auto all_threes = nnm::Vector2i::all(3);
            ASSERT(all_threes.x == 3);
            ASSERT(all_threes.y == 3);
        }

        test_section("zero");
        {
            const auto zero = nnm::Vector2i::zero();
            ASSERT(zero.x == 0);
            ASSERT(zero.y == 0);
        }

        test_section("one");
        {
            const auto one = nnm::Vector2i::one();
            ASSERT(one.x == 1);
            ASSERT(one.y == 1);
        }

        test_section("axis_x");
        {
            const auto x = nnm::Vector2i::axis_x();
            ASSERT(x.x == 1);
            ASSERT(x.y == 0);
        }

        test_section("axis_y");
        {
            const auto y = nnm::Vector2i::axis_y();
            ASSERT(y.x == 0);
            ASSERT(y.y == 1);
        }

        test_section("abs");
        {
            ASSERT(nnm::Vector2i(1, -2).abs() == nnm::Vector2i(1, 2));
        }

        test_section("clamp");
        {
            ASSERT(nnm::Vector2i(1, -3).clamp({ 1, -2 }, { 2, 2 }) == nnm::Vector2i(1, -2));
        }

        test_section("manhattan_distance");
        {
            nnm::Vector2i from(1, 1);
            nnm::Vector2i to(2, 2);
            ASSERT(from.manhattan_distance(to) == 2);

            from = nnm::Vector2i(-1, -1);
            to = nnm::Vector2i(1, 1);
            ASSERT(from.manhattan_distance(to) == 4);

            from = nnm::Vector2i(0, 0);
            to = nnm::Vector2i(3, 0);
            ASSERT(from.manhattan_distance(to) == 3);

            from = nnm::Vector2i(0, 0);
            to = nnm::Vector2i(0, 4);
            ASSERT(from.manhattan_distance(to) == 4);

            from = nnm::Vector2i(1, 2);
            to = nnm::Vector2i(1, 2);
            ASSERT(from.manhattan_distance(to) == 0);
        }

        test_section("length_sqrd");
        {
            ASSERT(nnm::Vector2i(3, 4).length_sqrd() == 25);
            ASSERT(nnm::Vector2i(-2, 5).length_sqrd() == 29);
            ASSERT(nnm::Vector2i(0, 0).length_sqrd() == 0);
        }

        test_section("max_index");
        {
            nnm::Vector2i v1(3, 4);
            ASSERT(v1.max_index() == 1);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.max_index() == 1);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.max_index() == 0);
        }

        test_section("min_index");
        {
            nnm::Vector2i v1(3, 4);
            ASSERT(v1.min_index() == 0);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.min_index() == 0);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.min_index() == 0);
        }

        test_section("begin");
        {
            nnm::Vector2i v1(2, -3);
            ASSERT(v1.begin() == &v1.x);
        }

        test_section("end");
        {
            nnm::Vector2i v1(2, -3);
            ASSERT(v1.end() == &v1.y + 1);
        }

        test_section("at");
        {
            nnm::Vector2i v1(2, -3);
            ASSERT(v1.at(0) == 2);
            ASSERT(v1.at(1) == -3);
        }

        test_section("operator[]");
        {
            nnm::Vector2i v1(2, -3);
            ASSERT(v1[0] == 2);
            ASSERT(v1[1] == -3);
        }

        const nnm::Vector2i v1(1, 2);
        const nnm::Vector2i v2(3, 4);
        const nnm::Vector2i v3(1, 2);

        test_section("operator==");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
        }

        const nnm::Vector2i v4(1, 2);
        const nnm::Vector2i v5(3, 4);

        test_section("operator+(const Vector2i&)");
        {
            ASSERT(v4 + v5 == nnm::Vector2i(4, 6));
        }

        test_section("operator+=");
        {
            auto v4_copy = v4;
            ASSERT((v4_copy += v5) == nnm::Vector2i(4, 6));
        }

        test_section("operator-(const Vector2i&)");
        {
            ASSERT(v5 - v4 == nnm::Vector2i(2, 2));
        }

        test_section("operator-=");
        {
            auto v5_copy = v5;
            ASSERT((v5_copy -= v4) == nnm::Vector2i(2, 2));
        }

        test_section("operator*(const Vector2i&)");
        {
            ASSERT(v4 * v5 == nnm::Vector2i(3, 8));
        }

        test_section("operator*=(const Vector2i&)");
        {
            auto v4_copy = v4;
            ASSERT((v4_copy *= v5) == nnm::Vector2i(3, 8));
        }

        test_section("operator*(int)");
        {
            ASSERT(v4 * 2 == nnm::Vector2i(2, 4));
        }

        test_section("operator*(int, const Vector2i&)");
        {
            ASSERT(2 * v4 == nnm::Vector2i(2, 4));
        }

        test_section("operator*=(int)");
        {
            auto v4_copy = v4;
            ASSERT((v4_copy *= 2) == nnm::Vector2i(2, 4));
        }

        test_section("operator/(const Vector2i&)");
        {
            ASSERT(v5 / v4 == nnm::Vector2i(3, 2));
        }

        test_section("operator/=(const Vector2i&)");
        {
            auto v5_copy = v5;
            ASSERT((v5_copy /= v4) == nnm::Vector2i(3, 2));
        }

        test_section("operator/(int)");
        {
            ASSERT(v5 / 2 == nnm::Vector2i(1, 2));
        }

        test_section("operator/(int, const Vector2i&)");
        {
            ASSERT(2 / v4 == nnm::Vector2i(2, 1));
        }

        test_section("operator/=(int)");
        {
            auto v5_copy = v5;
            ASSERT((v5_copy /= 2) == nnm::Vector2i(1, 2));
        }

        test_section("operator%(const Vector2i&)");
        {
            ASSERT(v4 % v5 == nnm::Vector2i(1, 2));
        }

        test_section("operator%=(const Vector2i&)");
        {
            auto v4_copy = v4;
            ASSERT((v4_copy %= v5) == nnm::Vector2i(1, 2));
        }

        test_section("operator%(int)");
        {
            ASSERT(v4 % 2 == nnm::Vector2i(1, 0));
        }

        test_section("operator%(int, const Vector2i&)");
        {
            ASSERT(3 % nnm::Vector2i(2, 5) == nnm::Vector2i(1, 3));
        }

        test_section("operator%=(int)");
        {
            auto v4_copy = v4;
            ASSERT((v4_copy % 2) == nnm::Vector2i(1, 0));
        }

        test_section("operator+");
        {
            ASSERT(+v4 == v4);
        }

        test_section("operator-");
        {
            ASSERT(-v4 == nnm::Vector2i(-1, -2));
        }

        test_section("operator<");
        {
            const nnm::Vector2i v7(1, 2);
            const nnm::Vector2i v8(3, 4);
            ASSERT(v7 < v8);
            ASSERT_FALSE(v8 < v7);
        }

        test_section("operator bool");
        {
            const nnm::Vector2i v7(1, 2);
            ASSERT(static_cast<bool>(v7));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
        }
    }

    test_case("Vector3");
    {
        test_section("Vector3()");
        {
            const nnm::Vector3 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
        }

        test_section("Vector3(const Vector3i&)");
        {
            const nnm::Vector3 v2(nnm::Vector3i(1, 2, 3));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == 3.0f);
        }

        test_section("Vector3(const Vector2&, float)");
        {
            const nnm::Vector3 v(nnm::Vector2(1.0f, 2.0f), 3.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == 2.0f);
            ASSERT(v.z == 3.0f);
        }

        test_section("Vector3(float, float, float)");
        {
            const nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
            ASSERT(v3.z == 3.0f);
        }

        test_section("all");
        {
            const auto v1 = nnm::Vector3::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);
        }

        test_section("zero");
        {
            const auto v2 = nnm::Vector3::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);
        }

        test_section("one");
        {
            const auto v3 = nnm::Vector3::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
        }

        test_section("axis_x");
        {
            const auto x = nnm::Vector3::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
            ASSERT(x.z == 0.0f);
        }

        test_section("axis_y");
        {
            const auto y = nnm::Vector3::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
            ASSERT(y.z == 0.0f);
        }

        test_section("axis_z");
        {
            const auto z = nnm::Vector3::axis_z();
            ASSERT(z.x == 0.0f);
            ASSERT(z.y == 0.0f);
            ASSERT(z.z == 1.0f);
        }

        test_section("abs");
        {
            ASSERT(nnm::Vector3(0.0f, 1.0f, -2.0f).abs() == nnm::Vector3(0.0f, 1.0f, 2.0f));
        }

        test_section("ceil");
        {
            ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).ceil() == nnm::Vector3(1.0f, -2.0f, 2.0f));
        }

        test_section("floor");
        {
            ASSERT(nnm::Vector3(0.1f, -2.1f, 1.1f).floor() == nnm::Vector3(0.0f, -3.0f, 1.0f));
        }

        test_section("round");
        {
            const nnm::Vector3 v(1.1f, -2.8f, 0.0f);
            ASSERT(v.round() == nnm::Vector3(1.0f, -3.0f, 0.0f));
        }

        test_section("clamp");
        {
            const nnm::Vector3 v(0.0f, 10.0f, -2.0f);
            const nnm::Vector3 min(-1.0f, 12.0f, -5.0f);
            const nnm::Vector3 max(1.0f, 12.0f, -3.0f);
            ASSERT(v.clamp(min, max) == nnm::Vector3(0.0f, 12.0f, -3.0f));
        }

        test_section("direction");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            auto direction = from.direction(to);
            ASSERT(direction.approx_equal(nnm::Vector3::all(0.57735f)));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            direction = from.direction(to);
            ASSERT(direction.approx_equal(nnm::Vector3::all(0.57735f)));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(1.0f, 0.0f, 0.0f);
            direction = from.direction(to);
            ASSERT(nnm::approx_equal(direction.x, 1.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 1.0f, 0.0f);
            direction = from.direction(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 1.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 0.0f, 1.0f);
            direction = from.direction(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 1.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            direction = from.direction(to);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));
        }

        test_section("distance_sqrd");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd(to), 3.0f));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd(to), 12.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(3.0f, 0.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd(to), 9.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 4.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd(to), 16.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(from.distance_sqrd(to), 0.0f));
        }

        test_section("distance");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(3.0f)));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.distance(to), nnm::sqrt(12.0f)));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(3.0f, 0.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 3.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 4.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 4.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(from.distance(to), 0.0f));
        }

        test_section("manhattan_distance");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 3.0f));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 6.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(3.0f, 0.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 3.0f));

            from = nnm::Vector3(0.0f, 0.0f, 0.0f);
            to = nnm::Vector3(0.0f, 4.0f, 0.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 4.0f));

            from = nnm::Vector3(1.0f, 2.0f, 3.0f);
            to = nnm::Vector3(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(from.manhattan_distance(to), 0.0f));
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

        test_section("clamp_length");
        {
            const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(v.clamp_length(2.0f, 5.0f).approx_equal(nnm::Vector3(1.0f, 2.0f, 3.0f)));
            ASSERT(v.clamp_length(2.0f, 3.0f).approx_equal(nnm::Vector3(0.80178f, 1.603566f, 2.405352f)));
            ASSERT(v.clamp_length(10.0f, 100.0f).approx_equal(nnm::Vector3(2.67261f, 5.34522f, 8.01784f)));
        }

        test_section("normalize");
        {
            const nnm::Vector3 v(1.0f, -2.0f, 3.0f);
            ASSERT(v.normalize().approx_equal(nnm::Vector3(0.267261f, -0.534522f, 0.801784f)));
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

        test_section("lerp_clamped");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(3.0f, 5.0f, -2.0f);
            ASSERT(from.lerp_clamped(to, 0.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
            ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
            ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
            ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
            ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
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

        test_section("outer");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            const nnm::Matrix3 expected { { -2.0f, 4.0f, -6.0f }, { 4.0f, -8.0f, 12.0f }, { -6.0f, 12.0f, -18.0f } };
            ASSERT(v1.outer(v2).approx_equal(expected));
        }

        test_section("reflect");
        {
            nnm::Vector3 incident(1.0f, 1.0f, 1.0f);
            nnm::Vector3 normal(0.0f, 1.0f, 0.0f);
            ASSERT(incident.reflect(normal) == nnm::Vector3(1.0f, -1.0f, 1.0f));
        }

        test_section("project");
        {
            nnm::Vector3 v(1.0f, 2.0f, -3.0f);
            nnm::Vector3 onto(-4.0f, 0.5f, 10.0f);
            nnm::Vector3 expected(1.135483870967742f, -0.141935483870968f, -2.838709677419355f);
            ASSERT(v.project(onto).approx_equal(expected));
        }

        test_section("inverse");
        {
            nnm::Vector3 v(1.0f, 2.0f, -3.0f);
            ASSERT(v.inverse().approx_equal(nnm::Vector3(1.0f, 0.5f, -1.0f / 3.0f)));
        }

        test_section("angle");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            ASSERT(nnm::approx_equal(v1.angle(v2), 2.52872f))
        }

        test_section("translate");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            ASSERT(v1.translate(v2).approx_equal({ -3.0f, 2.5f, 7.0f }))
        }

        test_section("rotate_axis_angle");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 axis = nnm::Vector3(2.0f, 0.5f, -0.8f).normalize();
            ASSERT(v1.rotate_axis_angle(axis, nnm::pi / 5.0f).approx_equal({ 1.2574f, 3.10567f, -1.66545f }))
        }

        test_section("rotate_quaternion");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            auto quaternion = nnm::Quaternion::from_axis_angle(nnm::Vector3(2.0f, 0.5f, -0.8f), nnm::pi / 5.0f);
            ASSERT(v1.rotate_quaternion(quaternion).approx_equal({ 1.2574f, 3.10567f, -1.66545f }));
        }

        test_section("scale");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            ASSERT(v1.scale(v2).approx_equal({ -4.0f, 1.0f, -30.0f }));
        }

        test_section("shear_x");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            ASSERT(v1.shear_x(nnm::pi / 5.0f, -nnm::pi / 6.0f).approx_equal({ 4.18513584f, 2.0f, -3.0f }))
        }

        test_section("shear_y");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            ASSERT(v1.shear_y(nnm::pi / 5.0f, -nnm::pi / 6.0f).approx_equal({ 1.0f, 4.45859337f, -3.0f }));
        }

        test_section("shear_z");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            ASSERT(v1.shear_z(nnm::pi / 5.0f, -nnm::pi / 6.0f).approx_equal({ -1.17962766f, 3.7320509f, -3.0f }));
        }

        test_section("transform(const Basis3&)");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Basis3 basis({ { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } });
            ASSERT(v1.transform(basis).approx_equal({ 9.0f, -12.4f, -30.44f }));
        }

        test_section("transform(const Transform2&)");
        {
            nnm::Vector3 v1(2.0f, -3.0f, 4.0f);
            nnm::Transform2 transform({ { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
            ASSERT(v1.transform(transform).approx_equal({ 26.0f, -8.8f, 1.0f }));
        }

        test_section("transform(const Transform3&, float)");
        {
            nnm::Vector3 v1(2.0f, -3.0f, 4.0f);
            nnm::Transform3 transform({ { 1.0f, 2.0f, -3.0f, 4.0f },
                                        { -10.0f, 0.5f, 20.6f, 0.0f },
                                        { 1.0f, 3.0f, 3.3f, -1.0f },
                                        { 9.9f, -7.54f, 20.0f, 0.1f } });
            ASSERT(v1.transform(transform).approx_equal({ 45.9f, 6.96f, -34.6f }));
            ASSERT(v1.transform(transform, -2.4f).approx_equal({ 12.24f, 32.596f, -102.6f }));
        }

        test_section("max_index");
        {
            nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            ASSERT(v1.max_index() == 1);
            nnm::Vector3 v2(-100.0f, 5.0f, 100.0f);
            ASSERT(v2.max_index() == 2);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
        }

        test_section("min_index");
        {
            nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            ASSERT(v1.min_index() == 2);
            nnm::Vector3 v2(-100.0f, 5.0f, 100.0f);
            ASSERT(v2.min_index() == 0);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.min_index() == 0);
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

        test_section("xy");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            ASSERT(v1.xy() == nnm::Vector2(1.0f, 2.0f));
        }

        test_section("begin");
        {
            nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            ASSERT(v1.begin() == &v1.x);
        }

        test_section("end");
        {
            nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            ASSERT(v1.end() == &v1.z + 1);
        }

        test_section("at");
        {
            nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            ASSERT(v1.at(0) == 1.0f);
            ASSERT(v1.at(1) == -3.0f);
            ASSERT(v1.at(2) == 4.0f);
        }

        test_section("operator[]");
        {
            nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            ASSERT(v1[0] == 1.0f);
            ASSERT(v1[1] == -3.0f);
            ASSERT(v1[2] == 4.0f);
        }

        nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
        nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
        nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

        test_section("operator==");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
        }

        test_section("operator+(const Vector3&)");
        {
            ASSERT(v1 + v2 == nnm::Vector3(4.0f, 6.0f, 1.0f));
        }

        test_section("operator+=");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy += v2) == nnm::Vector3(4.0f, 6.0f, 1.0f));
        }

        test_section("operator-(const Vector3&)");
        {
            ASSERT(v2 - v1 == nnm::Vector3(2.0f, 2.0f, -5.0f));
        }

        test_section("operator-=");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy -= v1) == nnm::Vector3(2.0f, 2.0f, -5.0f));
        }

        test_section("operator*(const Vector3&)");
        {
            ASSERT(v1 * v2 == nnm::Vector3(3.0f, 8.0f, -6.0f));
        }

        test_section("operator*=(const Vector3&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= v2) == nnm::Vector3(3.0f, 8.0f, -6.0f));
        }

        test_section("operator*(const Matrix3&)");
        {
            nnm::Matrix3 matrix { { 1.0f, -3.0f, 4.0f }, { -1.6f, 0.5f, 20.0f }, { 0.0f, 2.0f, 1.0f } };
            ASSERT((v2 * matrix).approx_equal({ -17.0f, -42.8f, 6.0f }))
        }

        test_section("operator*(float)");
        {
            ASSERT(v1 * 2.0f == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator*(float, const Vector3&)");
        {
            ASSERT(2.0f * v1 == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator*=(float)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= 2.0f) == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator/(const Vector3&)");
        {
            ASSERT(v2 / v1 == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        }

        test_section("operator/=(const Vector3&)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= v1) == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        }

        test_section("operator/(float)");
        {
            ASSERT(v2 / 2.0f == nnm::Vector3(1.5f, 2.0f, -1.0f));
        }

        test_section("operator/(float, const Vector3&)");
        {
            ASSERT(2.0f / v2 == nnm::Vector3(0.66666666f, 0.5f, -1.0f));
        }

        test_section("operator/=(float)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= 2.0) == nnm::Vector3(1.5f, 2.0f, -1.0f));
        }

        test_section("operator+");
        {
            ASSERT(+v1 == v1);
        }

        test_section("operator-");
        {
            ASSERT(-v1 == nnm::Vector3(-1.0f, -2.0f, -3.0f));
        }

        test_section("operator<");
        {
            ASSERT(v1 < v2);
            ASSERT_FALSE(v2 < v1);
        }

        test_section("operator bool");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
        }
    }

    test_case("Vector3i");
    {
        test_section("Vector3i()");
        {
            const nnm::Vector3i v_default;
            ASSERT(v_default.x == 0);
            ASSERT(v_default.y == 0);
            ASSERT(v_default.z == 0);
        }

        test_section("Vector3i(const Vector3&)");
        {
            const nnm::Vector3i v(nnm::Vector3(1.1f, 0.2f, -1.6f));
            ASSERT(v.x == 1);
            ASSERT(v.y == 0);
            ASSERT(v.z == -1);
        }

        test_section("Vector3i(const Vector2i&, int)");
        {
            const nnm::Vector3i v(nnm::Vector2i(1, -2), 3);
            ASSERT(v.x == 1);
            ASSERT(v.y == -2);
            ASSERT(v.z == 3);
        }

        test_section("Vector3i(int, int, int)");
        {
            const nnm::Vector3i v_with_params(1, -2, 3);
            ASSERT(v_with_params.x == 1);
            ASSERT(v_with_params.y == -2);
            ASSERT(v_with_params.z == 3);
        }

        test_section("all");
        {
            const auto v_all_threes = nnm::Vector3i::all(3);
            ASSERT(v_all_threes.x == 3);
            ASSERT(v_all_threes.y == 3);
            ASSERT(v_all_threes.z == 3);
        }

        test_section("zero");
        {
            const auto v_zero = nnm::Vector3i::zero();
            ASSERT(v_zero.x == 0);
            ASSERT(v_zero.y == 0);
            ASSERT(v_zero.z == 0);
        }

        test_section("one");
        {
            const auto v_one = nnm::Vector3i::one();
            ASSERT(v_one.x == 1);
            ASSERT(v_one.y == 1);
            ASSERT(v_one.z == 1);
        }

        test_section("axis_x");
        {
            const auto x = nnm::Vector3i::axis_x();
            ASSERT(x.x == 1);
            ASSERT(x.y == 0);
            ASSERT(x.z == 0);
        }

        test_section("axis_y");
        {
            const auto y = nnm::Vector3i::axis_y();
            ASSERT(y.x == 0);
            ASSERT(y.y == 1);
            ASSERT(y.z == 0);
        }

        test_section("axis_z");
        {
            const auto z = nnm::Vector3i::axis_z();
            ASSERT(z.x == 0);
            ASSERT(z.y == 0);
            ASSERT(z.z == 1);
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

        test_section("manhattan_distance");
        {
            nnm::Vector3i from(1, 1, 1);
            nnm::Vector3i to(2, 2, 2);
            ASSERT(from.manhattan_distance(to) == 3);

            from = nnm::Vector3i(-1, -1, -1);
            to = nnm::Vector3i(1, 1, 1);
            ASSERT(from.manhattan_distance(to) == 6);

            from = nnm::Vector3i(0, 0, 0);
            to = nnm::Vector3i(3, 0, 0);
            ASSERT(from.manhattan_distance(to) == 3);

            from = nnm::Vector3i(0, 0, 0);
            to = nnm::Vector3i(0, 4, 0);
            ASSERT(from.manhattan_distance(to) == 4);

            from = nnm::Vector3i(1, 2, 3);
            to = nnm::Vector3i(1, 2, 3);
            ASSERT(from.manhattan_distance(to) == 0);
        }

        test_section("length_sqrd");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.length_sqrd() == 14);
        }

        test_section("max_index");
        {
            nnm::Vector3i v1(1, -2, 3);
            ASSERT(v1.max_index() == 2);
            nnm::Vector3i v2(-1, 2, -3);
            ASSERT(v2.max_index() == 1);
        }

        test_section("min_index");
        {
            nnm::Vector3i v1(1, -2, 3);
            ASSERT(v1.min_index() == 1);
            nnm::Vector3i v2(-1, 2, -3);
            ASSERT(v2.min_index() == 2);
        }

        test_section("xy");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.xy() == nnm::Vector2i(1, -2));
        }

        test_section("begin");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.begin() == &v.x);
        }

        test_section("end");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.end() == &v.z + 1);
        }

        test_section("at");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v.at(0) == 1);
            ASSERT(v.at(1) == -2);
            ASSERT(v.at(2) == 3);
        }

        test_section("operator[]");
        {
            nnm::Vector3i v(1, -2, 3);
            ASSERT(v[0] == 1);
            ASSERT(v[1] == -2);
            ASSERT(v[2] == 3);
        }

        const nnm::Vector3i v1(1, 2, -3);
        const nnm::Vector3i v2(-3, 4, 100);
        const nnm::Vector3i v3(1, 2, -3);

        test_section("operator==");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
        }

        test_section("operator+(const Vector3i&)");
        {
            ASSERT(v1 + v2 == nnm::Vector3i(-2, 6, 97));
        }

        test_section("operator+=(const Vector3i&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy += v2) == nnm::Vector3i(-2, 6, 97));
        }

        test_section("operator-(const Vector3i&)");
        {
            ASSERT(v2 - v1 == nnm::Vector3i(-4, 2, 103));
        }

        test_section("operator-=(const Vector3i&)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy -= v1) == nnm::Vector3i(-4, 2, 103));
        }

        test_section("operator*(const Vector3i&)");
        {
            ASSERT(v1 * v2 == nnm::Vector3i(-3, 8, -300));
        }

        test_section("operator*=(const Vector3i&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= v2) == nnm::Vector3i(-3, 8, -300));
        }

        test_section("operator*(int)");
        {
            ASSERT(v1 * 2 == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator*(int, const Vector3i&)");
        {
            ASSERT(2 * v1 == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator*=(int)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= 2) == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator/(const Vector3i&)");
        {
            ASSERT(v2 / v1 == nnm::Vector3i(-3, 2, -33));
        }

        test_section("operator/=(const Vector3i&)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= v1) == nnm::Vector3i(-3, 2, -33));
        }

        test_section("operator/(int)");
        {
            ASSERT(v2 / 2 == nnm::Vector3i(-1, 2, 50));
        }

        test_section("operator/(int, const Vector3i&)");
        {
            ASSERT(2 / v1 == nnm::Vector3i(2, 1, 0));
        }

        test_section("operator/=(int)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= 2) == nnm::Vector3i(-1, 2, 50));
        }

        test_section("operator%(const Vector3i&)");
        {
            ASSERT(v1 % v2 == nnm::Vector3i(1, 2, -3));
        }

        test_section("operator%=(const Vector3i&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy %= v2) == nnm::Vector3i(1, 2, -3));
        }

        test_section("operator%(int)");
        {
            ASSERT(v1 % 2 == nnm::Vector3i(1, 0, -1));
        }

        test_section("operator%(int, const Vector3i&)");
        {
            ASSERT(3 % v2 == nnm::Vector3i(0, 3, 3));
        }

        test_section("operator%=(int)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy %= 2) == nnm::Vector3i(1, 0, -1));
        }

        test_section("operator+");
        {
            ASSERT(+v1 == v1);
        }

        test_section("operator-");
        {
            ASSERT(-v1 == nnm::Vector3i(-1, -2, 3));
        }

        test_section("operator<");
        {
            ASSERT(v2 < v1);
            ASSERT_FALSE(v1 < v2);
        }

        test_section("operator bool");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
        }
    }

    test_case("Vector4");
    {
        test_section("Vector4()");
        {
            const nnm::Vector4 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
            ASSERT(v1.z == 0.0f);
            ASSERT(v1.w == 0.0f);
        }

        test_section("Vector4(const Vector2&, float, float)");
        {
            const nnm::Vector4 v(nnm::Vector2(1.0f, -2.0f), 3.0f, -4.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == -2.0f);
            ASSERT(v.z == 3.0f);
            ASSERT(v.w == -4.0f);
        }

        test_section("Vector4(const Vector3&, float)");
        {
            const nnm::Vector4 v(nnm::Vector3(1.0f, -2.0f, 3.0f), -4.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == -2.0f);
            ASSERT(v.z == 3.0f);
            ASSERT(v.w == -4.0f);
        }

        test_section("Vector4(float, float, float, float)");
        {
            const nnm::Vector4 v2(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(v2.x == -1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == -3.0f);
            ASSERT(v2.w == 4.0f);
        }

        test_section("all");
        {
            const auto v1 = nnm::Vector4::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);
            ASSERT(v1.w == 3.0f);
        }

        test_section("zero");
        {
            const auto v2 = nnm::Vector4::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);
            ASSERT(v2.w == 0.0f);
        }

        test_section("one");
        {
            const auto v3 = nnm::Vector4::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
            ASSERT(v3.w == 1.0f);
        }

        test_section("axis_x");
        {
            const auto x = nnm::Vector4::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
            ASSERT(x.z == 0.0f);
            ASSERT(x.w == 0.0f);
        }

        test_section("axis_y");
        {
            const auto y = nnm::Vector4::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
            ASSERT(y.z == 0.0f);
            ASSERT(y.w == 0.0f);
        }

        test_section("axis_z");
        {
            const auto z = nnm::Vector4::axis_z();
            ASSERT(z.x == 0.0f);
            ASSERT(z.y == 0.0f);
            ASSERT(z.z == 1.0f);
            ASSERT(z.w == 0.0f);
        }

        test_section("axis_w");
        {
            const auto w = nnm::Vector4::axis_w();
            ASSERT(w.x == 0.0f);
            ASSERT(w.y == 0.0f);
            ASSERT(w.z == 0.0f);
            ASSERT(w.w == 1.0f);
        }

        test_section("abs");
        {
            const nnm::Vector4 v1(-1.0f, 2.0f, -3.0, 4.0f);
            const nnm::Vector4 v_expected(1.0f, 2.0f, 3.0f, 4.0f);
            ASSERT(v1.abs() == v_expected);
        }

        test_section("ceil");
        {
            const nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            const nnm::Vector4 v_expected(-1.0f, 1.0f, 0.0f, 2.0f);
            ASSERT(v1.ceil() == v_expected);
        }

        test_section("floor");
        {
            const nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            const nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 1.0f);
            ASSERT(v1.floor() == v_expected);
        }

        test_section("round");
        {
            const nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            const nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 2.0f);
            ASSERT(v1.round() == v_expected);
        }

        test_section("clamp");
        {
            const nnm::Vector4 v1(-1.0f, 2.0f, 3.0f, -4.0f);
            const nnm::Vector4 v2(2.0f, -3.0f, -2.0f, -3.0f);
            const nnm::Vector4 v3(4.0f, 1.0f, 4.0f, 1.0f);
            ASSERT(v1.clamp(v2, v3) == nnm::Vector4(2.0f, 1.0f, 3.0f, -3.0f));
        }

        test_section("length_sqrd");
        {
            const nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(nnm::approx_equal(v1.length_sqrd(), 30.0f));
        }

        test_section("length");
        {
            const nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(nnm::approx_equal(v1.length(), nnm::sqrt(30.0f)));
        }

        const nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        const nnm::Vector4 v2(4.0f, 5.0f, -2.0f, 1.5f);

        test_section("clamp_length");
        {
            ASSERT(v1.clamp_length(0.0f, 1.0f).approx_equal(v1.normalize()));
            ASSERT(v1.clamp_length(2.0f, 3.0f).approx_equal(v1.normalize() * 3.0f));
            ASSERT(v1.clamp_length(10.0f, 50.0f).approx_equal(v1.normalize() * 10.0f));
        }

        test_section("normalize");
        {
            ASSERT(nnm::Vector4().normalize() == nnm::Vector4());
            const nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);
            const nnm::Vector4 v_expected(-0.182574f, 0.365148f, -0.547723f, 0.730297f);
            ASSERT(v3.normalize().approx_equal(v_expected));
        }

        test_section("lerp");
        {
            ASSERT(v1.lerp(v2, 0.0f) == v1);
            ASSERT(v1.lerp(v2, 1.0f) == v2);
            ASSERT(v1.lerp(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
        }

        test_section("lerp_clamped");
        {
            ASSERT(v1.lerp_clamped(v2, 0.0f) == v1);
            ASSERT(v1.lerp_clamped(v2, 1.0f) == v2);
            ASSERT(v1.lerp_clamped(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
            ASSERT(v1.lerp_clamped(v2, -5.0f) == v1);
            ASSERT(v1.lerp_clamped(v2, 5.0f) == v2);
        }

        test_section("dot");
        {
            ASSERT(nnm::approx_equal(v1.dot(v2), 18.0f));
        }

        test_section("outer");
        {
            nnm::Matrix4 expected { { -4.0f, -5.0f, 2.0f, -1.5f },
                                    { 8.0f, 10.0f, -4.0f, 3.0f },
                                    { -12.0f, -15.0f, 6.0f, -4.5f },
                                    { 16.0f, 20.0f, -8.0f, 6.0f } };
            ASSERT(v1.outer(v2).approx_equal(expected));
        }

        test_section("inverse");
        {
            const nnm::Vector4 v_expected(-1.0f, 0.5f, -0.33333333f, 0.25f);
            ASSERT(v1.inverse().approx_equal(v_expected));
        }

        test_section("transform");
        {
            nnm::Transform3 transform({ { 1.0f, 2.0f, -3.0f, 4.0f },
                                        { -10.0f, 0.5f, 20.6f, 0.0f },
                                        { 1.0f, 3.0f, 3.3f, -1.0f },
                                        { 9.9f, -7.54f, 20.0f, 0.1f } });
            ASSERT(v1.transform(transform).approx_equal({ 15.6f, -40.16f, 114.3f, -0.6f }))
        }

        test_section("max_index");
        {
            ASSERT(v1.max_index() == 3);
            ASSERT(v2.max_index() == 1);
        }

        test_section("min_index");
        {
            ASSERT(v1.min_index() == 2);
            ASSERT(v2.min_index() == 2);
        }

        test_section("approx_equal");
        {
            const nnm::Vector4 v1_almost(-0.99999999f, 2.0f, -3.00000001f, 3.99999f);
            ASSERT(v1.approx_equal(v1_almost));
            ASSERT_FALSE(v1.approx_equal(v2));
        }

        test_section("approx_zero");
        {
            const nnm::Vector4 almost_zero(0.00001f, -0.000001f, 0.0f, 0.00000001f);
            ASSERT(almost_zero.approx_zero());
        }

        test_section("xy");
        {
            ASSERT(v1.xy() == nnm::Vector2(-1.0f, 2.0f));
        }

        test_section("xyz");
        {
            ASSERT(v1.xyz() == nnm::Vector3(-1.0f, 2.0f, -3.0f));
        }

        test_section("begin");
        {
            ASSERT(v1.begin() == &v1.x);
        }

        test_section("end");
        {
            ASSERT(v1.end() == &v1.w + 1);
        }

        test_section("at");
        {
            ASSERT(v1.at(0) == -1.0f);
            ASSERT(v1.at(1) == 2.0f);
            ASSERT(v1.at(2) == -3.0f);
            ASSERT(v1.at(3) == 4.0f);
        }

        test_section("operator[]");
        {
            ASSERT(v1[0] == -1.0f);
            ASSERT(v1[1] == 2.0f);
            ASSERT(v1[2] == -3.0f);
            ASSERT(v1[3] == 4.0f);
        }

        // const nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        // const nnm::Vector4 v2(4.0f, 5.0f, -2.0f, 1.5f);
        const nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);

        test_section("operator==");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 != v3);
        }

        test_section("operator+(const Vector4&)");
        {
            ASSERT((v1 + v2).approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
        }

        test_section("operator+=(const Vector4&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy += v2).approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
        }

        test_section("operator-(const Vector4&)");
        {
            ASSERT((v1 - v2).approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
        }

        test_section("operator-=(const Vector4&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy -= v2).approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
        }

        test_section("operator*(const Vector4&)");
        {
            ASSERT((v1 * v2).approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
        }

        test_section("operator*=(const Vector4&)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= v2).approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
        }

        test_section("operator*(const Matrix4&)");
        {
            const nnm::Matrix4 matrix { { 1.0f, 2.0f, 3.0f, 4.0f },
                                        { -1.0f, -2.0f, -3.0f, -4.0f },
                                        { 1.0f, 3.0f, 2.0f, 4.0f },
                                        { -4.0f, -2.0f, -3.0f, -1.0f } };
            ASSERT((v1 * matrix).approx_equal({ 10.0f, -10.0f, 15.0f, 5.0f }))
        }

        test_section("operator*(float)");
        {
            ASSERT((v1 * 2.0f).approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator*(float, const Vector4&)");
        {
            ASSERT((2.0f * v1).approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator*=(float)");
        {
            auto v1_copy = v1;
            ASSERT((v1_copy *= 2.0f).approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator/(const Vector4&)");
        {
            ASSERT((v2 / v1).approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
        }

        test_section("operator/=(const Vector4&)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= v1).approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
        }

        test_section("operator/(float)");
        {
            ASSERT((v2 / 2.0f).approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
        }

        test_section("operator/=(float)");
        {
            auto v2_copy = v2;
            ASSERT((v2_copy /= 2.0f).approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
        }

        test_section("operator<(const Vector4&)");
        {
            ASSERT(v1 < v2);
            ASSERT_FALSE(v2 < v1);
        }

        test_section("operator+");
        {
            ASSERT(+v1 == v1);
        }

        test_section("operator-");
        {
            ASSERT(-v1 == nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
        }

        test_section("operator bool");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector4::zero()));
        }
    }

    test_case("Quaternion");
    {
        test_section("Quaternion()");
        {
            nnm::Quaternion q;
            ASSERT(q.x == 0.0f);
            ASSERT(q.y == 0.0f);
            ASSERT(q.z == 0.0f);
            ASSERT(q.w == 1.0f);
        }

        test_section("Quaternion(const Vector4&)");
        {
            nnm::Quaternion q(nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
            ASSERT(q.x == 1.0f);
            ASSERT(q.y == -2.0f);
            ASSERT(q.z == 3.0f);
            ASSERT(q.w == -4.0f);
        }

        test_section("Quaternion(float, float, float, float)");
        {
            nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q.x == 1.0f);
            ASSERT(q.y == -2.0f);
            ASSERT(q.z == 3.0f);
            ASSERT(q.w == -4.0f);
        }

        test_section("identity");
        {
            const auto q = nnm::Quaternion::identity();
            ASSERT(q.x == 0.0f);
            ASSERT(q.y == 0.0f);
            ASSERT(q.z == 0.0f);
            ASSERT(q.w == 1.0f);
        }

        test_section("from_axis_angle");
        {
            const auto q = nnm::Quaternion::from_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi / 9.0f);
            ASSERT(q.approx_equal({ 0.1515726f, -0.0757863f, 0.0378931f, 0.9848078f }))
        }

        test_section("from_vector_to_vector");
        {
            const nnm::Vector3 from(1.0f, -2.0f, 3.0f);
            const auto to = from.rotate_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi / 9.0f);
            const auto q = nnm::Quaternion::from_vector_to_vector(from, to);
            const auto rotated_from = from.rotate_quaternion(q);
            ASSERT(rotated_from.approx_equal(to));
        }

        test_section("normalize");
        {
            const nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q.normalize().approx_equal({ 0.182574f, -0.365148f, 0.547723f, -0.730297f }));
        }

        test_section("axis");
        {
            const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
            constexpr float angle = nnm::pi / 9.0f;
            const auto q = nnm::Quaternion::from_axis_angle(axis, angle);
            ASSERT(q.axis().approx_equal(axis));
        }

        test_section("angle");
        {
            const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
            constexpr float angle = nnm::pi / 9.0f;
            const auto q = nnm::Quaternion::from_axis_angle(axis, angle);
            ASSERT(nnm::approx_equal(q.angle(), angle));
        }

        test_section("inverse");
        {
            const auto q = nnm::Quaternion(1.0f, -2.0f, 3.0f, -4.0f).normalize();
            ASSERT(q.inverse().approx_equal({ -q.x, -q.y, -q.z, q.w }));
        }

        test_section("length_sqrd");
        {
            const nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(nnm::approx_equal(q.length_sqrd(), 30.0f));
        }

        test_section("length");
        {
            const nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(nnm::approx_equal(q.length(), 5.47723f));
        }

        const auto q1 = nnm::Quaternion::from_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi / 9.0f);
        const auto q2 = nnm::Quaternion::from_axis_angle({ 2.0f, 10.0f, -8.0f }, -nnm::pi / 2.0f);

        test_section("slerp");
        {
            ASSERT(q1.slerp(q2, 0.75f).approx_equal({ -0.0439172f, -0.4470681f, 0.3514504f, 0.8213915f }));
        }

        test_section("rotate_axis_angle");
        {
            const nnm::Quaternion q3 = q1.rotate_axis_angle({ -1.0f, 2.0f, -0.5f }, -nnm::pi / 3.0f);
            ASSERT(q3.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
        }

        test_section("rotate_quaternion");
        {
            const auto q3 = nnm::Quaternion::from_axis_angle({ -1.0f, 2.0f, -0.5f }, -nnm::pi / 3.0f);
            const nnm::Quaternion q4 = q1.rotate_quaternion(q3);
            ASSERT(q4.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
        }

        test_section("approx_equal");
        {
            ASSERT_FALSE(q1.approx_equal(q2));
            ASSERT(q1.approx_equal(q1));
            const nnm::Quaternion q3(0.15157f, -0.07579f, 0.03789f, 0.98481f);
            ASSERT(q1.approx_equal(q3));
        }

        test_section("at");
        {
            const nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q3.at(0) == 1.0f);
            ASSERT(q3.at(1) == -2.0f);
            ASSERT(q3.at(2) == 3.0f);
            ASSERT(q3.at(3) == -4.0f);
        }

        test_section("operator[]");
        {
            const nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q3[0] == 1.0f);
            ASSERT(q3[1] == -2.0f);
            ASSERT(q3[2] == 3.0f);
            ASSERT(q3[3] == -4.0f);
        }

        test_section("operator==");
        {
            const auto q3 = q1;
            ASSERT(q1 == q3);
            ASSERT_FALSE(q1 == q2);
        }

        test_section("operator!=");
        {
            const auto q3 = q1;
            ASSERT_FALSE(q1 != q3);
            ASSERT(q1 != q2);
        }

        test_section("operator*");
        {
            ASSERT((q1 * q2).approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
        }

        test_section("operator*=");
        {
            auto q1_copy = q1;
            ASSERT((q1_copy *= q2).approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
        }

        test_section("operator<");
        {
            ASSERT(q2 < q1);
            ASSERT_FALSE(q1 < q2);
        }

        test_section("operator bool");
        {
            ASSERT(static_cast<bool>(q1));
            ASSERT_FALSE(static_cast<bool>(nnm::Quaternion(nnm::Vector4::zero())));
        }
    }

    test_case("Matrix2");
    {
        test_section("Matrix2()");
        {
            const nnm::Matrix2 mat_default;
            ASSERT(mat_default.col0_row0 == 1.0f);
            ASSERT(mat_default.col0_row1 == 0.0f);
            ASSERT(mat_default.col1_row0 == 0.0f);
            ASSERT(mat_default.col1_row1 == 1.0f);
        }

        test_section("Matrix2(const Vector2&, const Vector2&)");
        {
            const nnm::Matrix2 mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat_cols.col0_row0 == 1.0f);
            ASSERT(mat_cols.col0_row1 == -2.0f);
            ASSERT(mat_cols.col1_row0 == -3.0f);
            ASSERT(mat_cols.col1_row1 == 4.0f);
        }

        test_section("Matrix2(float, float, float, float)");
        {
            const nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
            ASSERT(mat_elements.col0_row0 == 1.0f);
            ASSERT(mat_elements.col0_row1 == -2.0f);
            ASSERT(mat_elements.col1_row0 == -3.0f);
            ASSERT(mat_elements.col1_row1 == 4.0f);
        }

        test_section("all");
        {
            const auto mat_all_three = nnm::Matrix2::all(3.0f);
            ASSERT(mat_all_three.col0_row0 == 3.0f);
            ASSERT(mat_all_three.col0_row1 == 3.0f);
            ASSERT(mat_all_three.col1_row0 == 3.0f);
            ASSERT(mat_all_three.col1_row1 == 3.0f);
        }

        test_section("zero");
        {
            const auto mat_zero = nnm::Matrix2::zero();
            ASSERT(mat_zero.col0_row0 == 0.0f);
            ASSERT(mat_zero.col0_row1 == 0.0f);
            ASSERT(mat_zero.col1_row0 == 0.0f);
            ASSERT(mat_zero.col1_row1 == 0.0f);
        }

        test_section("one");
        {
            const auto mat_one = nnm::Matrix2::one();
            ASSERT(mat_one.col0_row0 == 1.0f);
            ASSERT(mat_one.col0_row1 == 1.0f);
            ASSERT(mat_one.col1_row0 == 1.0f);
            ASSERT(mat_one.col1_row1 == 1.0f);
        }

        test_section("identity");
        {
            const auto mat_identity = nnm::Matrix2::identity();
            ASSERT(mat_identity.col0_row0 == 1.0f);
            ASSERT(mat_identity.col0_row1 == 0.0f);
            ASSERT(mat_identity.col1_row0 == 0.0f);
            ASSERT(mat_identity.col1_row1 == 1.0f);
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

        test_section("minor_at");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.minor_at(0, 0) == 4.0f);
            ASSERT(mat.minor_at(0, 1) == -3.0f);
            ASSERT(mat.minor_at(1, 0) == -2.0f);
            ASSERT(mat.minor_at(1, 1) == 1.0f);
        }

        test_section("minor");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            const nnm::Matrix2 minor = mat.minor();
            ASSERT(minor.approx_equal({ { 4.0f, -3.0f }, { -2.0f, 1.0f } }));
        }

        test_section("cofactor_at");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.cofactor_at(0, 0) == 4.0f);
            ASSERT(mat.cofactor_at(0, 1) == 3.0f);
            ASSERT(mat.cofactor_at(1, 0) == 2.0f);
            ASSERT(mat.cofactor_at(1, 1) == 1.0f);
        }

        test_section("cofactor");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
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

        test_section("unchecked_inverse");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.unchecked_inverse().approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
        }

        test_section("inverse");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            const std::optional<nnm::Matrix2> mat_inv = mat.inverse();
            ASSERT(mat_inv.has_value());
            ASSERT(mat.inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT_FALSE(nnm::Matrix2::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            const nnm::Matrix2 mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat1.approx_equal({ { 1.00000001f, -1.9999999f }, { -3.00000001f, 3.99999999f } }));
            ASSERT_FALSE(mat1.approx_equal({ { 1.1f, -1.9f }, { -3.1f, 3.9f } }));
        }

        test_section("approx_zero");
        {
            const nnm::Matrix2 mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            const nnm::Matrix2 mat2({ 0.00000001f, -0.00000001f }, { -0.00000001f, 0.00000001f });
            ASSERT(mat2.approx_zero());
            ASSERT_FALSE(mat1.approx_zero());
        }

        test_section("at");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.at(0, 0) == 1.0f);
            ASSERT(mat.at(0, 1) == -2.0f);
            ASSERT(mat.at(1, 0) == -3.0f);
            ASSERT(mat.at(1, 1) == 4.0f);
        }

        test_section("begin");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.begin() == mat.data);
        }

        test_section("end");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.end() == mat.data + 4);
        }

        test_section("operator[]");
        {
            const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat[0][0] == 1.0f);
            ASSERT(mat[0][1] == -2.0f);
            ASSERT(mat[1][0] == -3.0f);
            ASSERT(mat[1][1] == 4.0f);
        }

        const nnm::Matrix2 m1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        const nnm::Matrix2 m2({ -4.0f, 3.0f }, { 2.0f, -1.0f });
        const nnm::Matrix2 m3({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        const nnm::Matrix2 m4({ 10.0f, -2.5f }, { 37.0f, -24.0f });

        test_section("operator==");
        {
            ASSERT(m1 == m3);
            ASSERT_FALSE(m1 == m2);
        }

        test_section("operator!=");
        {
            ASSERT_FALSE(m1 != m3);
            ASSERT(m1 != m2);
        }

        test_section("operator+");
        {
            ASSERT((m1 + m4).approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
        }

        test_section("operator+=");
        {
            auto m1_copy = m1;
            ASSERT((m1_copy += m4).approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
        }

        test_section("operator-");
        {
            ASSERT((m1 - m4).approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
        }

        test_section("operator-=");
        {
            auto m1_copy = m1;
            ASSERT((m1_copy -= m4).approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
        }

        test_section("operator*(const Matrix2&)");
        {
            ASSERT(m1 * m2 == nnm::Matrix2({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
            ASSERT((nnm::Matrix2::identity() * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(1.0f, 2.0f)));
        }

        test_section("operator*=(const Matrix2&)");
        {
            auto m1_copy = m1;
            ASSERT((m1_copy *= m2) == nnm::Matrix2({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
        }

        test_section("operator*(const Vector2&)");
        {
            ASSERT((m1 * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(-5.0f, 6.0f)));
        }

        test_section("operator*(float)");
        {
            ASSERT(m1 * 2.0f == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator*(float, const Matrix2&)");
        {
            ASSERT(2.0f * m1 == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator*=(float)");
        {
            auto m1_copy = m1;
            ASSERT((m1_copy *= 2.0f) == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator/(float)");
        {
            ASSERT((m2 / 2.0f).approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
        }

        test_section("operator/(float, const Matrix2&)");
        {
            ASSERT((2.0f / m2).approx_equal(nnm::Matrix2({ -0.5f, 0.666666666f }, { 1.0f, -2.0f })));
        }

        test_section("operator/=");
        {
            auto m2_copy = m2;
            ASSERT((m2_copy /= 2.0f).approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
        }

        test_section("operator<");
        {
            ASSERT(m2 < m1);
            ASSERT_FALSE(m1 < m2);
        }

        test_section("operator bool");
        {
            ASSERT(static_cast<bool>(m1));
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix2::zero()));
        }
    }

    test_case("Basis2");
    {
        test_case("Basis()");
        {
            const nnm::Basis2 b;
            ASSERT(b.matrix == nnm::Matrix2::identity());
        }

        test_section("Basis2(const Matrix2&)");
        {
            const auto m1 = nnm::Matrix2::identity();
            const auto b1 = nnm::Basis2(m1);
            ASSERT(b1 == nnm::Basis2());
            ASSERT(b1.matrix == nnm::Matrix2::identity());
        }

        test_section("from_rotation");
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

        test_section("from_scale");
        {
            const auto b1 = nnm::Basis2::from_scale({ 2.0f, -3.0f });
            ASSERT(b1.matrix == nnm::Matrix2({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
        }

        test_section("from_shear_x");
        {
            const auto b = nnm::Basis2::from_shear_x(nnm::pi / 4.5f);
            ASSERT(b.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.8390996312f, 1.0f } }));
        }

        test_section("from_shear_y");
        {
            const auto b = nnm::Basis2::from_shear_y(-nnm::pi / 3.1f);
            ASSERT(b.matrix.approx_equal({ { 1.0f, -1.6043516022f }, { 0.0f, 1.0f } }))
        }

        test_section("trace");
        {
            const nnm::Basis2 b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b.trace() == b.matrix.trace());
        }

        test_section("determinant");
        {
            const nnm::Basis2 b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b.determinant() == b.matrix.determinant());
        }

        test_section("unchecked_inverse");
        {
            const nnm::Basis2 b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b.unchecked_inverse().matrix == b.matrix.unchecked_inverse());
        }

        test_section("inverse");
        {
            const nnm::Basis2 b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const auto inv = b.inverse();
            ASSERT(inv.has_value() && inv.value().matrix == b.matrix.inverse().value());
            ASSERT_FALSE(nnm::Basis2(nnm::Matrix2::zero()).inverse().has_value());
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

        test_section("rotate");
        {
            const nnm::Basis2 b1;
            ASSERT(b1.rotate(0.0f).approx_equal(b1));
            ASSERT(b1.rotate(nnm::pi / 2.0f).matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
            ASSERT(b1.rotate(-nnm::pi / 2.0f).matrix.approx_equal({ { 0.0f, -1.0f }, { 1.0f, 0.0f } }));
            ASSERT(b1.rotate(2.0f * nnm::pi).approx_equal(b1));
            const auto b2 = nnm::Basis2::from_scale({ 2.0f, 0.5f });
            const auto b2_rotated = b2.rotate(nnm::pi / 4.0f);
            ASSERT(b2_rotated.matrix.approx_equal({ { 1.41421f, 1.41421f }, { -0.353553f, 0.353553f } }));
        }

        test_section("rotate_local");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { 1.96575f, -3.24747f }, { -2.47706f, 3.07473f } });
            ASSERT(b1.rotate_local(-nnm::pi / 9.0f).approx_equal(expected));
        }

        test_section("scale");
        {
            const nnm::Basis2 b1;
            ASSERT_FALSE(b1.scale({ 0.0f, 0.0f }).valid());
            ASSERT(b1.scale({ 0.0f, 0.0f }).matrix.approx_equal(nnm::Matrix2::zero()));
            ASSERT(b1.scale({ 2.0f, 2.0f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 2.0f } }));
            ASSERT(b1.scale({ 2.0f, 0.5f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 0.5f } }));
            ASSERT(b1.scale({ -1.0f, -1.0f }).matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
        }

        test_section("scale_local");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { 2.0f, -4.0f }, { 1.5f, -2.0f } });
            ASSERT(b1.scale_local({ 2.0f, -0.5f }).approx_equal(expected));
        }

        test_section("shear_x");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { -0.285322f, -2.0f }, { -0.429356f, 4.0f } });
            ASSERT(b1.shear_x(nnm::pi / 5.5f).approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { 1.0f, -2.0f }, { -2.35734f, 2.71468f } });
            ASSERT(b1.shear_x_local(nnm::pi / 5.5f).approx_equal(expected));
        }

        test_section("shear_y");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { 1.0f, -2.8391f }, { -3.0f, 6.5173f } });
            ASSERT(b1.shear_y(-nnm::pi / 4.5f).approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 expected({ { 3.5173f, -5.3564f }, { -3.0f, 4.0f } });
            ASSERT(b1.shear_y_local(-nnm::pi / 4.5f).approx_equal(expected));
        }

        test_section("transform");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
            const nnm::Basis2 expected({ { 7.75f, 17.5f }, { -16.25f, -55.0f } });
            ASSERT(b1.transform(b2).approx_equal(expected));
        }

        test_section("transform_local");
        {
            const nnm::Basis2 b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const nnm::Basis2 b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
            const nnm::Basis2 expected({ { -59.25f, 78.5f }, { -7.25f, 12.0f } });
            ASSERT(b1.transform_local(b2).approx_equal(expected));
        }

        test_section("approx equal");
        {
            const nnm::Basis2 b1;
            ASSERT(b1.approx_equal(nnm::Basis2({ { 1.0000000f, 0.000000001f }, { -0.000000001f, 0.9999999f } })));
            const auto b2 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT_FALSE(b2.approx_equal(nnm::Basis2()));
        }

        test_section("at");
        {
            auto b1 = nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b1.at(0, 0) == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
            ASSERT(b1.at(1, 1) == 4.0f);
            ASSERT(b1.at(0, 0) == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
        }

        test_section("operator[]");
        {
            auto b1 = nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            ASSERT(b1[0] == nnm::Vector2(1.0f, -2.0f));
            ASSERT(b1[1] == nnm::Vector2(-3.0f, 4.0f));
        }

        test_section("operator==");
        {
            const nnm::Basis2 b1;
            const nnm::Basis2 b2;
            const auto b3 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT(b1 == b2);
            ASSERT_FALSE(b1 == b3);
        }

        test_section("operator!=");
        {
            const nnm::Basis2 b1;
            const nnm::Basis2 b2;
            const auto b3 = nnm::Basis2::from_rotation(nnm::pi);
            ASSERT_FALSE(b1 != b2);
            ASSERT(b1 != b3);
        }

        test_section("operator<");
        {
            const auto b1 = nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            const auto b2 = nnm::Basis2({ { -4.0f, 3.0f }, { 2.0f, -1.0f } });
            ASSERT(b2 < b1);
        }
    }

    test_case("Matrix3");
    {
        test_section("Matrix3()");
        {
            const nnm::Matrix3 default_mat;
            ASSERT(default_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
            ASSERT(default_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
            ASSERT(default_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
        }

        test_section("Matrix3(const Vector3&, const Vector3&, const Vector3&)");
        {
            const nnm::Matrix3 cols(
                nnm::Vector3(1.0f, 2.0f, 3.0f), nnm::Vector3(-1.0f, -2.0f, -3.0f), nnm::Vector3(2.0f, 4.0f, 6.0f));
            ASSERT(cols.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(cols.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(cols.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("Matrix3(float, float, float, float, float, float, float, float, float)");
        {
            const nnm::Matrix3 elems(1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, 2.0f, 4.0f, 6.0f);
            ASSERT(elems.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(elems.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(elems.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("all");
        {
            const auto threes = nnm::Matrix3::all(3.0f);
            ASSERT(threes.columns[0] == nnm::Vector3::all(3.0f));
            ASSERT(threes.columns[1] == nnm::Vector3::all(3.0f));
            ASSERT(threes.columns[2] == nnm::Vector3::all(3.0f));
        }

        test_section("zero");
        {
            const auto zeros = nnm::Matrix3::zero();
            ASSERT(zeros.columns[0] == nnm::Vector3::zero());
            ASSERT(zeros.columns[1] == nnm::Vector3::zero());
            ASSERT(zeros.columns[2] == nnm::Vector3::zero());
        }

        test_section("one");
        {
            const auto ones = nnm::Matrix3::one();
            ASSERT(ones.columns[0] == nnm::Vector3::one());
            ASSERT(ones.columns[1] == nnm::Vector3::one());
            ASSERT(ones.columns[2] == nnm::Vector3::one());
        }

        test_section("identity");
        {
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

        test_section("minor_matrix_at");
        {
            ASSERT(m1.minor_matrix_at(0, 0).approx_equal({ { -2.0f, -1.0f }, { -4.0f, 6.0f } }));
            ASSERT(m1.minor_matrix_at(1, 2).approx_equal({ { 1.0f, 2.0f }, { 2.0f, -4.0f } }));
        }

        test_section("minor_at");
        {
            const nnm::Matrix3 result({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
            ASSERT(nnm::approx_equal(m1.minor_at(0, 0), result.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.minor_at(1, 2), result.at(1, 2)));
        }

        test_section("minor");
        {
            const nnm::Matrix3 expected({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
            ASSERT(m1.minor().approx_equal(expected));
        }

        test_section("cofactor_at");
        {
            const nnm::Matrix3 result({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
            ASSERT(nnm::approx_equal(m1.cofactor_at(0, 0), result.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.cofactor_at(1, 2), result.at(1, 2)));
        }

        test_section("cofactor");
        {
            const nnm::Matrix3 expected({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
            ASSERT(m1.cofactor().approx_equal(expected));
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

        test_section("unchecked_inverse");
        {
            const nnm::Matrix3 result(
                { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
            ASSERT(m1.unchecked_inverse().approx_equal(result));
        }

        test_section("inverse");
        {
            const nnm::Matrix3 result(
                { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
            ASSERT(m1.inverse().has_value());
            ASSERT(m1.inverse().value().approx_equal(result));
            ASSERT_FALSE(nnm::Matrix3::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            const nnm::Matrix3 almost_ident(
                { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
            const nnm::Matrix3 almost_zero(
                { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });

            ASSERT(nnm::Matrix3::identity().approx_equal(almost_ident));
            ASSERT_FALSE(almost_zero.approx_equal(almost_ident));
        }

        test_section("approx_zero");
        {
            const nnm::Matrix3 almost_ident(
                { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
            const nnm::Matrix3 almost_zero(
                { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
            ASSERT(nnm::Matrix3::zero().approx_zero());
            ASSERT_FALSE(almost_ident.approx_zero());
            ASSERT(almost_zero.approx_zero());
        }

        test_section("at");
        {
            ASSERT(m1.at(0) == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1.at(1) == nnm::Vector3(-3.0f, -2.0f, -1.0f));
            ASSERT(m1.at(0, 0) == 1.0f);
            ASSERT(m1.at(1, 2) == -1.0f);
        }

        test_section("begin");
        {
            ASSERT(m1.begin() == &m1.col0_row0);
        }

        test_section("end");
        {
            ASSERT(m1.end() == &m1.col2_row2 + 1);
        }

        test_section("operator[]");
        {
            ASSERT(m1[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1[1] == nnm::Vector3(-3.0f, -2.0f, -1.0f));
        }

        test_section("operator==");
        {
            ASSERT(m1 == nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
            ASSERT_FALSE(m1 == nnm::Matrix3::identity());
        }

        test_section("operator!=");
        {
            ASSERT(m1 != nnm::Matrix3::identity());
            ASSERT_FALSE(m1 != nnm::Matrix3({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
        }

        const nnm::Matrix3 m2({ 3.0f, -6.0f, -9.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 2.0f, 10.0f });

        test_section("operator+");
        {
            const nnm::Matrix3 expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
            ASSERT((m1 + m2).approx_equal(expected));
        }

        test_section("operator+=");
        {
            auto m1_copy = m1;
            const nnm::Matrix3 expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
            ASSERT((m1_copy += m2).approx_equal(expected));
        }

        test_section("operator-");
        {
            const nnm::Matrix3 expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
            ASSERT((m1 - m2).approx_equal(expected));
        }

        test_section("operator-=");
        {
            auto m1_copy = m1;
            const nnm::Matrix3 expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
            ASSERT((m1_copy -= m2).approx_equal(expected));
        }

        test_section("operator*(const Matrix3&)");
        {
            const nnm::Matrix3 expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
            ASSERT((m1 * m2).approx_equal(expected));
        }

        test_section("operator*=(const Matrix3&)");
        {
            auto m1_copy = m1;
            const nnm::Matrix3 expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
            ASSERT((m1_copy *= m2).approx_equal(expected));
        }

        test_section("operator*(const Vector3&)");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            ASSERT((m1 * v1).approx_equal({ 13.0f, -6.0f, 23.0f }));
        }

        test_section("operator*(float)");
        {
            const nnm::Matrix3 expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            ASSERT((m1 * 5.0f).approx_equal(expected));
        }

        test_section("operator*(float, const Matrix3&)");
        {
            const nnm::Matrix3 expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            ASSERT((5.0f * m1).approx_equal(expected));
        }

        test_section("operator*=(float)");
        {
            auto m1_copy = m1;
            const nnm::Matrix3 expected({ 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            ASSERT((m1_copy *= 5.0f).approx_equal(expected));
        }

        test_section("operator/(float)");
        {
            const nnm::Matrix3 expected(
                { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
            ASSERT((m1 / 2.0f).approx_equal(expected));
        }

        test_section("operator/(float, const Matrix3&)");
        {
            const nnm::Matrix3 expected(
                { 2.0f, 1.0f, 0.666666f }, { -0.6666666f, -1.0f, -2.0f }, { 1.0f, -0.5f, 0.3333333f });
            ASSERT((2.0f / m1).approx_equal(expected));
        }

        test_section("operator/=");
        {
            auto m1_copy = m1;
            const nnm::Matrix3 expected(
                { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
            ASSERT((m1_copy /= 2.0f).approx_equal(expected));
        }

        test_section("operator<");
        {
            ASSERT_FALSE(m1 < nnm::Matrix3::identity());
            ASSERT(m1 < nnm::Matrix3::all(10.0f));
        }

        test_section("operator bool");
        {
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix3::zero()));
            ASSERT(static_cast<bool>(nnm::Matrix3::identity()));
        }
    }

    test_case("Transform2");
    {
        test_section("Transform2");
        {
            nnm::Transform2 default_transform;
            ASSERT(default_transform.matrix == nnm::Matrix3::identity());
        }

        test_section("Transform2(const Matrix3&)");
        {
            nnm::Transform2 transform_matrix(nnm::Matrix3::all(3.0f));
            ASSERT(transform_matrix.matrix == nnm::Matrix3::all(3.0f));
        }

        test_section("from_basis_translation");
        {
            const nnm::Basis2 basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
            const nnm::Vector2 pos(-1.0f, 2.0f);
            const auto transform_basis_pos = nnm::Transform2::from_basis_translation(basis, pos);
            const nnm::Matrix3 expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
            ASSERT(transform_basis_pos.matrix.approx_equal(expected));
        }

        test_section("from_basis");
        {
            const nnm::Basis2 basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
            const nnm::Matrix3 expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            const auto transform_basis = nnm::Transform2::from_basis(basis);
            ASSERT(transform_basis.matrix.approx_equal(expected));
        }

        test_section("from_translation");
        {
            const nnm::Vector2 pos(-1.0f, 2.0f);
            const auto transform_pos = nnm::Transform2::from_translation(pos);
            const nnm::Matrix3 expected({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
            ASSERT(transform_pos.matrix.approx_equal(expected));
        }

        test_section("from_rotation");
        {
            const auto transform_rot = nnm::Transform2::from_rotation(nnm::pi / 2.0f);
            const nnm::Matrix3 expected({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            ASSERT(transform_rot.matrix.approx_equal(expected));
        }

        test_section("from_scale");
        {
            const auto transform_scale = nnm::Transform2::from_scale({ -2.0f, 3.0f });
            const nnm::Matrix3 expected({ -2.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            ASSERT(transform_scale.matrix.approx_equal(expected));
        }

        test_section("from_shear_x");
        {
            const auto t = nnm::Transform2::from_shear_x(nnm::pi / 9.0f);
            const nnm::Transform2 expected(
                { { 1.0f, 0.0f, 0.0f }, { 0.3639702343f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_shear_y");
        {
            const auto t = nnm::Transform2::from_shear_y(-nnm::pi / 8.0f);
            const nnm::Transform2 expected(
                { { 1.0f, -0.4142135624f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("trace");
        {
            const nnm::Transform2 t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            ASSERT(nnm::approx_equal(t.trace(), 12.0f));
        }

        test_section("determinant");
        {
            const nnm::Transform2 t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            ASSERT(nnm::approx_equal(t.determinant(), -54.925f));
        }

        test_section("unchecked_inverse");
        {
            const nnm::Transform2 t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            const nnm::Transform2 expected({ { -0.254893f, -0.0345926f, 0.819299f },
                                             { -0.559854f, -0.00455166f, 0.37096f },
                                             { 0.270369f, 0.0509786f, -0.154756f } });
            ASSERT(t.unchecked_inverse().approx_equal(expected));
        }

        test_section("inverse");
        {
            const nnm::Transform2 t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            const nnm::Transform2 expected({ { -0.254893f, -0.0345926f, 0.819299f },
                                             { -0.559854f, -0.00455166f, 0.37096f },
                                             { 0.270369f, 0.0509786f, -0.154756f } });
            ASSERT(t.inverse().has_value() && t.inverse().value().approx_equal(expected));
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3::zero()).inverse().has_value());
        }

        test_section("valid");
        {
            ASSERT(nnm::Transform2(nnm::Matrix3::identity()).valid());
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3::zero()).valid());
        }

        test_section("affine");
        {
            ASSERT(nnm::Transform2(nnm::Matrix3::identity()).affine());
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3::zero()).affine());
        }

        const nnm::Transform2 t1({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f } });

        test_section("basis");
        {
            ASSERT(t1.basis() == nnm::Basis2({ { 1.0f, -2.0f }, { -3.0f, 4.0f } }));
        }

        test_section("translation");
        {
            ASSERT(t1.translation() == nnm::Vector2(-1.0f, 2.0f));
        }

        test_section("translate");
        {
            const nnm::Transform2 expected({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 0.0f, -0.5f, 1.0f } });
            const nnm::Transform2 t2 = t1.translate({ 1.0f, -2.5f });
            ASSERT(t2.approx_equal(expected));
        }

        test_section("translate_local");
        {
            const nnm::Transform2 expected({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 7.5f, -10.0f, 1.0f } });
            const nnm::Transform2 t2 = t1.translate_local({ 1.0f, -2.5f });
            ASSERT(t2.approx_equal(expected));
        }

        test_section("rotate");
        {
            const auto t = nnm::Transform2::from_basis_translation(nnm::Basis2(), { 1.0f, -2.0f });
            const auto t_rotated = t.rotate(nnm::pi / 2.0f);
            const auto t_expected
                = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi / 2.0f), { 2.0f, 1.0f });
            ASSERT(t_rotated.approx_equal(t_expected));
        }

        test_section("rotate_local");
        {
            const auto t = nnm::Transform2::from_basis_translation(nnm::Basis2(), { 1.0f, -2.0f });
            const auto t_rotated = t.rotate_local(nnm::pi / 2.0f);
            const auto t_expected
                = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi / 2.0f), { 1.0f, -2.0f });
            ASSERT(t_rotated.approx_equal(t_expected));
        }

        const auto t2
            = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi / 2.0f), { 1.0f, -2.0f });
        const auto t3 = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi), { -3.0f, 4.0f });

        test_section("scale");
        {
            const auto t_scaled = t2.scale({ 2.0f, -3.0f });
            const auto t_expected
                = nnm::Transform2::from_basis_translation(t2.basis().scale({ 2.0f, -3.0f }), { 2.0f, 6.0f });
            ASSERT(t_scaled.approx_equal(t_expected));
        }

        test_section("scale_local");
        {
            const auto t_scaled = t2.scale_local({ 2.0f, -3.0f });
            const auto t_expected
                = nnm::Transform2::from_basis_translation(t2.basis().scale_local({ 2.0f, -3.0f }), { 1.0f, -2.0f });
            ASSERT(t_scaled.approx_equal(t_expected));
        }

        test_section("shear_x");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            const nnm::Transform2 expected(
                { { 0.27206f, -2.0f, 3.0f }, { -1.54412f, 4.0f, -2.0f }, { -0.27206f, 2.0f, 1.0f } });
            ASSERT(t4.shear_x(nnm::pi / 9.0f).approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            const nnm::Transform2 expected(
                { { 1.0f, -2.0f, 3.0f }, { -2.63603f, 3.27206f, -0.908089f }, { -1.0f, 2.0f, 1.0f } });
            ASSERT(t4.shear_x_local(nnm::pi / 9.0f).approx_equal(expected));
        }

        test_section("shear_y");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            const nnm::Transform2 expected(
                { { 1.0f, -2.3874f, 3.0f }, { -3.0f, 5.16221f, -2.0f }, { -1.0f, 2.3874f, 1.0f } });
            ASSERT(t4.shear_y(-nnm::pi / 8.5f).approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            const nnm::Transform2 expected(
                { { 2.16221f, -3.54961f, 3.7748f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            ASSERT(t4.shear_y_local(-nnm::pi / 8.5f).approx_equal(expected));
        }

        test_section("transform");
        {
            const auto t_transformed = t2.transform(t3);
            const auto t_expected = nnm::Transform2::from_basis_translation(
                nnm::Basis2::from_rotation(3.0f * nnm::pi / 2.0f), { -4.0f, 6.0f });
            ASSERT(t_transformed.approx_equal(t_expected));
        }

        test_section("transform_local");
        {
            const auto t_transformed = t2.transform_local(t3);
            const auto t_expected = nnm::Transform2::from_basis_translation(
                nnm::Basis2::from_rotation(3.0f * nnm::pi / 2.0f), { -3.0f, -5.0f });
            ASSERT(t_transformed.approx_equal(t_expected));
        }

        test_section("approx_equal");
        {
            nnm::Transform2 t(
                { { 0.999999f, 0.0000001f, -0.0000001f }, { 0.0f, 1.00000001f, 0.0f }, { 0.0f, -0.0000001f, 1.0f } });
            ASSERT(t.approx_equal(nnm::Transform2()));
        }

        test_section("at");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            ASSERT(t4.at(0, 0) == 1.0f);
            ASSERT(t4.at(1, 2) == -2.0f);
            ASSERT(t4.at(2, 2) == 1.5f);
        }

        test_section("operator[]");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            ASSERT(t4[0] == nnm::Vector3(1.0f, -2.0f, 3.0f));
            ASSERT(t4[1] == nnm::Vector3(-3.0f, 4.0f, -2.0f));
            ASSERT(t4[2] == nnm::Vector3(-1.0f, 2.0f, 1.5f));
        }

        test_section("operator==");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            const nnm::Transform2 t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            const nnm::Transform2 t6 = t4;
            ASSERT(t4 == t6);
            ASSERT_FALSE(t4 == t5);
        }

        test_section("operator!=");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            const nnm::Transform2 t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            const nnm::Transform2 t6 = t4;
            ASSERT(t4 != t5);
            ASSERT_FALSE(t4 != t6);
        }

        test_section("operator<");
        {
            const nnm::Transform2 t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            const nnm::Transform2 t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            ASSERT(t5 < t4);
            ASSERT_FALSE(t4 < t5);
        }
    }

    test_case("Matrix4");
    {
        test_section("constructors");
        {
            const nnm::Matrix4 m1;
            ASSERT(m1.col0_row0 == 1.0f);
            ASSERT(m1.col0_row1 == 0.0f);
            ASSERT(m1.col0_row2 == 0.0f);
            ASSERT(m1.col0_row3 == 0.0f);
            ASSERT(m1.col1_row0 == 0.0f);
            ASSERT(m1.col1_row1 == 1.0f);
            ASSERT(m1.col1_row2 == 0.0f);
            ASSERT(m1.col1_row3 == 0.0f);
            ASSERT(m1.col2_row0 == 0.0f);
            ASSERT(m1.col2_row1 == 0.0f);
            ASSERT(m1.col2_row2 == 1.0f);
            ASSERT(m1.col2_row3 == 0.0f);
            ASSERT(m1.col3_row0 == 0.0f);
            ASSERT(m1.col3_row1 == 0.0f);
            ASSERT(m1.col3_row2 == 0.0f);
            ASSERT(m1.col3_row3 == 1.0f);
            const nnm::Matrix4 m2 { 1.0f, 2.0f, 3.0f, 4.0f, -1.0f, -2.0f, -3.0f, -4.0f,
                                    4.0f, 3.0f, 2.0f, 1.0f, -4.0f, -3.0f, -2.0f, -1.0f };
            ASSERT(m2.col0_row0 == 1.0f);
            ASSERT(m2.col0_row1 == 2.0f);
            ASSERT(m2.col0_row2 == 3.0f);
            ASSERT(m2.col0_row3 == 4.0f);
            ASSERT(m2.col1_row0 == -1.0f);
            ASSERT(m2.col1_row1 == -2.0f);
            ASSERT(m2.col1_row2 == -3.0f);
            ASSERT(m2.col1_row3 == -4.0f);
            ASSERT(m2.col2_row0 == 4.0f);
            ASSERT(m2.col2_row1 == 3.0f);
            ASSERT(m2.col2_row2 == 2.0f);
            ASSERT(m2.col2_row3 == 1.0f);
            ASSERT(m2.col3_row0 == -4.0f);
            ASSERT(m2.col3_row1 == -3.0f);
            ASSERT(m2.col3_row2 == -2.0f);
            ASSERT(m2.col3_row3 == -1.0f);
            const nnm::Matrix4 m3 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                    { -1.0f, -2.0f, -3.0f, -4.0f },
                                    { 4.0f, 3.0f, 2.0f, 1.0f },
                                    { -4.0f, -3.0f, -2.0f, -1.0f } };
            ASSERT(m3.col0_row0 == 1.0f);
            ASSERT(m3.col0_row1 == 2.0f);
            ASSERT(m3.col0_row2 == 3.0f);
            ASSERT(m3.col0_row3 == 4.0f);
            ASSERT(m3.col1_row0 == -1.0f);
            ASSERT(m3.col1_row1 == -2.0f);
            ASSERT(m3.col1_row2 == -3.0f);
            ASSERT(m3.col1_row3 == -4.0f);
            ASSERT(m3.col2_row0 == 4.0f);
            ASSERT(m3.col2_row1 == 3.0f);
            ASSERT(m3.col2_row2 == 2.0f);
            ASSERT(m3.col2_row3 == 1.0f);
            ASSERT(m3.col3_row0 == -4.0f);
            ASSERT(m3.col3_row1 == -3.0f);
            ASSERT(m3.col3_row2 == -2.0f);
            ASSERT(m3.col3_row3 == -1.0f);
        }

        test_section("static methods");
        {
            const auto m1 = nnm::Matrix4::all(3.0f);
            ASSERT(m1.col0_row0 == 3.0f);
            ASSERT(m1.col0_row1 == 3.0f);
            ASSERT(m1.col0_row2 == 3.0f);
            ASSERT(m1.col0_row3 == 3.0f);
            ASSERT(m1.col1_row0 == 3.0f);
            ASSERT(m1.col1_row1 == 3.0f);
            ASSERT(m1.col1_row2 == 3.0f);
            ASSERT(m1.col1_row3 == 3.0f);
            ASSERT(m1.col2_row0 == 3.0f);
            ASSERT(m1.col2_row1 == 3.0f);
            ASSERT(m1.col2_row2 == 3.0f);
            ASSERT(m1.col2_row3 == 3.0f);
            ASSERT(m1.col3_row0 == 3.0f);
            ASSERT(m1.col3_row1 == 3.0f);
            ASSERT(m1.col3_row2 == 3.0f);
            ASSERT(m1.col3_row3 == 3.0f);

            const auto m2 = nnm::Matrix4::zero();
            ASSERT(m2.col0_row0 == 0.0f);
            ASSERT(m2.col0_row1 == 0.0f);
            ASSERT(m2.col0_row2 == 0.0f);
            ASSERT(m2.col0_row3 == 0.0f);
            ASSERT(m2.col1_row0 == 0.0f);
            ASSERT(m2.col1_row1 == 0.0f);
            ASSERT(m2.col1_row2 == 0.0f);
            ASSERT(m2.col1_row3 == 0.0f);
            ASSERT(m2.col2_row0 == 0.0f);
            ASSERT(m2.col2_row1 == 0.0f);
            ASSERT(m2.col2_row2 == 0.0f);
            ASSERT(m2.col2_row3 == 0.0f);
            ASSERT(m2.col3_row0 == 0.0f);
            ASSERT(m2.col3_row1 == 0.0f);
            ASSERT(m2.col3_row2 == 0.0f);
            ASSERT(m2.col3_row3 == 0.0f);

            const auto m3 = nnm::Matrix4::one();
            ASSERT(m3.col0_row0 == 1.0f);
            ASSERT(m3.col0_row1 == 1.0f);
            ASSERT(m3.col0_row2 == 1.0f);
            ASSERT(m3.col0_row3 == 1.0f);
            ASSERT(m3.col1_row0 == 1.0f);
            ASSERT(m3.col1_row1 == 1.0f);
            ASSERT(m3.col1_row2 == 1.0f);
            ASSERT(m3.col1_row3 == 1.0f);
            ASSERT(m3.col2_row0 == 1.0f);
            ASSERT(m3.col2_row1 == 1.0f);
            ASSERT(m3.col2_row2 == 1.0f);
            ASSERT(m3.col2_row3 == 1.0f);
            ASSERT(m3.col3_row0 == 1.0f);
            ASSERT(m3.col3_row1 == 1.0f);
            ASSERT(m3.col3_row2 == 1.0f);
            ASSERT(m3.col3_row3 == 1.0f);

            const auto m4 = nnm::Matrix4::identity();
            ASSERT(m4.col0_row0 == 1.0f);
            ASSERT(m4.col0_row1 == 0.0f);
            ASSERT(m4.col0_row2 == 0.0f);
            ASSERT(m4.col0_row3 == 0.0f);
            ASSERT(m4.col1_row0 == 0.0f);
            ASSERT(m4.col1_row1 == 1.0f);
            ASSERT(m4.col1_row2 == 0.0f);
            ASSERT(m4.col1_row3 == 0.0f);
            ASSERT(m4.col2_row0 == 0.0f);
            ASSERT(m4.col2_row1 == 0.0f);
            ASSERT(m4.col2_row2 == 1.0f);
            ASSERT(m4.col2_row3 == 0.0f);
            ASSERT(m4.col3_row0 == 0.0f);
            ASSERT(m4.col3_row1 == 0.0f);
            ASSERT(m4.col3_row2 == 0.0f);
            ASSERT(m4.col3_row3 == 1.0f);
        }

        const nnm::Matrix4 m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                { -1.0f, -3.0f, -2.0f, -4.0f },
                                { 3.0f, 2.0f, -1.0f, -4.0f },
                                { -4.0f, 1.0f, -3.0f, 0.0f } };

        test_section("trace");
        {
            ASSERT(m1.trace() == -3.0f);
        }

        test_section("minor_matrix_at");
        {
            const nnm::Matrix3 m2 = m1.minor_matrix_at(0, 0);
            ASSERT(m2 == nnm::Matrix3({ -3.0f, -2.0f, -4.0f }, { 2.0f, -1.0f, -4.0f }, { 1.0f, -3.0f, 0.0f }));

            const nnm::Matrix3 m3 = m1.minor_matrix_at(1, 2);
            ASSERT(m3 == nnm::Matrix3({ 1.0f, 2.0f, 4.0f }, { 3.0f, 2.0f, -4.0f }, { -4.0f, 1.0f, 0.0f }));
        }

        test_section("minor_at");
        {
            ASSERT(nnm::approx_equal(m1.minor_at(0, 0), 64.0f));
            ASSERT(nnm::approx_equal(m1.minor_at(1, 2), 80.0f));
        }

        test_section("determinant");
        {
            ASSERT(nnm::approx_equal(m1.determinant(), -64.0f));
        }

        test_section("cofactor_at");
        {
            ASSERT(nnm::approx_equal(m1.cofactor_at(0, 0), 64.0f));
            ASSERT(nnm::approx_equal(m1.cofactor_at(2, 1), -16.0f));
        }

        test_section("cofactor");
        {
            const nnm::Matrix4 expected { { 64.0f, -32.0f, -96.0f, 56.0f },
                                          { 56.0f, -16.0f, -80.0f, 54.0f },
                                          { 8.0f, -16.0f, -16.0f, 18.0f },
                                          { 24.0f, -16.0f, -16.0f, 14.0f } };
            ASSERT(m1.cofactor().approx_equal(expected))
        }

        test_section("transpose");
        {
            const nnm::Matrix4 expected { { 1.0f, -1.0f, 3.0f, -4.0f },
                                          { 2.0f, -3.0f, 2.0f, 1.0f },
                                          { 3.0f, -2.0f, -1.0f, -3.0f },
                                          { 4.0f, -4.0f, -4.0f, 0.0f } };
            ASSERT(m1.transpose() == expected);
        }

        test_section("adjugate");
        {
            const nnm::Matrix4 expected { { 64.0f, 56.0f, 8.0f, 24.0f },
                                          { -32.0f, -16.0f, -16.0f, -16.0f },
                                          { -96.0f, -80.0f, -16.0f, -16.0f },
                                          { 56.0f, 54.0f, 18.0f, 14.0f } };
            ASSERT(m1.adjugate().approx_equal(expected));
        }

        test_section("inverse");
        {
            const nnm::Matrix4 expected { { -1.0f, -0.875f, -0.125f, -0.375f },
                                          { 0.5f, 0.25f, 0.25f, 0.25f },
                                          { 1.5f, 1.25f, 0.25f, 0.25f },
                                          { -0.875f, -0.84375f, -0.28125f, -0.21875f } };
            ASSERT(m1.inverse().has_value() && m1.inverse().value().approx_equal(expected));
            ASSERT(m1.unchecked_inverse().approx_equal(expected));

            ASSERT_FALSE(nnm::Matrix4::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            const nnm::Matrix4 m2 { { 1.000001f, 2.0f, 3.0f, 4.000001f },
                                    { -0.999999f, -3.0f, -2.0f, -4.0f },
                                    { 3.0f, 1.999999f, -1.0f, -4.0f },
                                    { -4.0f, 1.0f, -2.999999f, 0.0f } };
            ASSERT(m1.approx_equal(m2));
        }

        test_section("approx_zero");
        {
            const nnm::Matrix4 m2 { { 0.000001f, 0.0f, 0.0f, 0.0f },
                                    { -0.000001f, -0.0f, -0.0f, 0.0f },
                                    { 0.0f, 0.000001f, 0.0f, 0.0f },
                                    { 0.0f, 0.0f, 0.0f, 0.0f } };
            ASSERT(m2.approx_zero());
        }

        // const nnm::Matrix4 m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
        //                         { -1.0f, -3.0f, -2.0f, -4.0f },
        //                         { 3.0f, 2.0f, -1.0f, -4.0f },
        //                         { -4.0f, 1.0f, -3.0f, 0.0f } };

        test_section("accessors");
        {
            ASSERT(m1[0][0] == 1.0f);
            ASSERT(m1.at(0, 0) == 1.0f);
            ASSERT(m1[1][2] == -2.0f);
            ASSERT(m1.at(1, 2) == -2.0f);
            ASSERT(m1[3][3] == 0.0f);
            ASSERT(m1.at(3, 3) == 0.0f);
            ASSERT(m1.at(0) == nnm::Vector4(1.0f, 2.0f, 3.0f, 4.0f))
            ASSERT(m1.at(2) == nnm::Vector4(3.0f, 2.0f, -1.0f, -4.0f))
        }

        const nnm::Matrix4 m2 { { 1.5f, 3.0f, -3.0f, 4.0f },
                                { -1.0f, 100.0f, -2.0f, -4.0f },
                                { 0.0f, 29.0f, -129.0f, -4293.0f },
                                { -4.0f, 100.3f, -3.0f, 0.0f } };

        test_section("equality");
        {
            ASSERT(m1 == m1);
            ASSERT_FALSE(m1 != m1);
            ASSERT(m1 != m2);
            ASSERT_FALSE(m1 == m2);
            ASSERT(m2 == m2);
            ASSERT_FALSE(m2 != m2);
        }

        test_section("comparison");
        {
            ASSERT(m1 < m2);
            ASSERT_FALSE(m2 < m1);
        }

        test_section("multiplication");
        {
            const nnm::Matrix4 expected1 { { -26.5f, -8.0f, -10.5f, 6.0f },
                                           { -91.0f, -310.0f, -189.0f, -396.0f },
                                           { 16756.0f, -4638.0f, 12950.0f, 400.0f },
                                           { -113.3f, -314.9f, -209.6f, -405.2f } };
            ASSERT((m1 * m2).approx_equal(expected1));
            auto m1_copy = m1;
            ASSERT((m1_copy *= m2).approx_equal(expected1))

            const nnm::Vector4 v1 { 1.0f, -2.0f, 3.0f, -4.0f };
            const nnm::Vector4 expected2 { 28.0f, 10.0f, 16.0f, 0.0f };
            ASSERT((m1 * v1).approx_equal(expected2));

            const nnm::Matrix4 expected3 { { -2.0, -4.0f, -6.0f, -8.0f },
                                           { 2.0f, 6.0f, 4.0f, 8.0f },
                                           { -6.0f, -4.0f, 2.0f, 8.0f },
                                           { 8.0f, -2.0f, 6.0f, 0.0f } };
            ASSERT((m1 * -2.0f).approx_equal(expected3));
            m1_copy = m1;
            ASSERT((m1_copy *= -2.0f).approx_equal(expected3));
        }

        test_section("division");
        {
            const nnm::Matrix4 expected1 { { -0.25, -0.5f, -0.75f, -1.0f },
                                           { 0.25f, 0.75f, 0.5f, 1.0f },
                                           { -0.75f, -0.5f, 0.25f, 1.0f },
                                           { 1.0f, -0.25f, 0.75f, 0.0f } };
            ASSERT((m1 / -4.0f).approx_equal(expected1));
            auto m1_copy = m1;
            ASSERT((m1_copy /= -4.0f).approx_equal(expected1));
        }

        test_section("bool conversion");
        {
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix4::zero()));
            ASSERT(static_cast<bool>(nnm::Matrix4::identity()));
            ASSERT(static_cast<bool>(m1));
        }
    }

    test_case("Basis3");
    {
        test_section("constructors");
        {
            nnm::Basis3 b1;
            ASSERT(b1.matrix == nnm::Matrix3::identity());
            nnm::Matrix3 m1 { { 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 3.0f, -8.0f, 1.0f } };
            nnm::Basis3 b2(m1);
            ASSERT(b2.matrix == m1);
        }

        test_section("from_rotation_axis_angle");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, nnm::pi);
            ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }))
            auto b2 = nnm::Basis3::from_rotation_axis_angle({ 2.0f, 0.0f, 0.0f }, nnm::pi / 4.0f);
            ASSERT(b2.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.707107f, 0.707107f }, { 0.0f, -0.707107f, 0.707107f } }));
        }

        test_section("from_shear_x");
        {
            auto b1 = nnm::Basis3::from_shear_x(0.5f, -0.1f);
            ASSERT(b1.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 0.5463024898f, 1.0f, 0.0f }, { -0.1003346721f, 0.0f, 1.0f } }));
        }

        test_section("from_scale");
        {
            auto b1 = nnm::Basis3::from_scale({ -1.0f, 2.0f, 3.0f });
            ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f, 3.0f } }));
        }

        test_section("valid");
        {
            nnm::Basis3 b1(nnm::Matrix3::zero());
            ASSERT_FALSE(b1.valid());
            nnm::Basis3 b2;
            ASSERT(b2.valid());
            nnm::Basis3 b3({ { 1.0f, 2.0f, 3.0f }, { 2.0f, 4.0f, 6.0f }, { 3.0f, 6.0f, 9.0f } });
            ASSERT_FALSE(b3.valid());
            nnm::Basis3 b4({ { 1.0f, 2.0f, 3.0f }, { 3.0f, 1.0f, 3.0f }, { -2.0f, 3.0f, 1.0f } });
            ASSERT(b4.valid());
        }

        test_section("rotate_axis_angle");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi / 2.0f);
            nnm::Basis3 b1_rot = b1.rotate_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi / 4.0f);
            ASSERT(b1_rot.matrix.approx_equal(
                { { 0.707107f, 0.0f, -0.707107f }, { 0.707107f, 0.0f, 0.707107f }, { 0.0f, -1.0f, 0.0f } }));
        }

        test_section("rotate_axis_angle_local");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, -nnm::pi / 4.0f);
            nnm::Basis3 b1_rot = b1.rotate_axis_angle_local({ 0.0f, 0.0f, 3.0f }, nnm::pi / 2.0f);
            ASSERT(b1_rot.matrix.approx_equal(
                { { 0.0f, 1.0f, 0.0f }, { -0.707107f, 0.0f, -0.707107f }, { -0.707107f, 0.0f, 0.707107f } }))
        }

        test_section("scale");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, nnm::pi / 2.0f);
            nnm::Basis3 b1_scaled = b1.scale({ 2.0f, -1.0f, 0.4f });
            ASSERT(
                b1_scaled.matrix.approx_equal({ { 0.0f, 0.0f, -0.4f }, { 0.0f, -1.0f, 0.0f }, { 2.0f, 0.0f, 0.0f } }));
        }

        test_section("scale_local");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 0.0f, 0.0f, 1.0f }, -nnm::pi / 4.0f);
            nnm::Basis3 b1_scaled = b1.scale_local({ 0.6f, 2.0f, -1.5f });
            ASSERT(b1_scaled.matrix.approx_equal(
                { { 0.424264f, -0.424264f, 0.0f }, { 1.41421f, 1.41421f, 0.0f }, { 0.0f, 0.0f, -1.5f } }));
        }

        test_section("shear_x");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_x(1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { -14.1014204f, -1.0f, 0.0f }, { 0.10034f, 0.0f, -1.0f } }))
        }

        test_section("shear_x_local");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_x_local(1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 14.1014f, -1.0f, 0.0f }, { -0.10033f, 0.0f, -1.0f } }))
        }

        test_section("shear_y");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_y(-1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, -14.1014204f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.10033f, -1.0f } }))
        }

        test_section("shear_y_local");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_y_local(1.3f, 0.3f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, -3.6021f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -0.30934f, -1.0f } }))
        }

        test_section("shear_z");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_z(1.2f, -0.8f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { -2.57215f, 1.02964f, -1.0f } }))
        }

        test_section("shear_z_local");
        {
            auto b1 = nnm::Basis3::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi);
            auto b1_sheared = b1.shear_z_local(-1.2f, 0.8f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { -2.57215f, -1.02964f, -1.0f } }))
        }

        test_section("transform");
        {
            nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
            nnm::Basis3 b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
            auto b3 = b1.transform(b2);
            ASSERT(
                b3.matrix.approx_equal({ { 34.0f, 11.5f, -111.0f }, { 2.0f, -2.8f, 5.5f }, { 13.0f, 4.25f, -35.0f } }))
        }

        test_section("transform_local");
        {
            nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
            nnm::Basis3 b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
            auto b3 = b1.transform_local(b2);
            ASSERT(b3.matrix.approx_equal({ { 5.0f, -0.5f, 6.15f }, { 0.5f, -4.0f, 0.2f }, { -38.5f, 14.0f, -4.8f } }))
        }

        test_section("inverse");
        {
            nnm::Basis3 b1(nnm::Matrix3::zero());
            ASSERT_FALSE(b1.inverse().has_value());
            nnm::Basis3 b2({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
            std::optional<nnm::Basis3> b2_inv = b2.inverse();
            nnm::Basis3 expected({ { -0.441176f, -0.294118f, 1.35294f },
                                   { -0.272059f, -0.514706f, 0.867647f },
                                   { 0.661765f, 0.441176f, -1.02941f } });
            ASSERT(b2_inv.has_value() && b2_inv.value().approx_equal(expected))
            ASSERT(b2.unchecked_inverse().approx_equal(expected));
        }

        test_section("trace");
        {
            nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 0.2f } });
            ASSERT(nnm::approx_equal(b1.trace(), -1.8f));
        }

        test_section("determinant");
        {
            nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 0.2f } });
            ASSERT(nnm::approx_equal(b1.determinant(), 12.4f))
        }

        test_section("approx_equal");
        {
            nnm::Basis3 b1({ { 1.000001f, -0.00001f, 0.0f }, { 0.0f, 0.99999999f, 0.000001f }, { 0.0f, 0.0f, 1.0f } });
            ASSERT(b1.approx_equal(nnm::Basis3()));
        }

        const nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
        const nnm::Basis3 b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });

        test_section("accessors");
        {
            ASSERT(b1.at(1, 2) == 0.1f);
            ASSERT(b1[1] == nnm::Vector3(2.0f, -3.0f, 0.1f));
            ASSERT(b1.at(1) == nnm::Vector3(2.0f, -3.0f, 0.1f));
        }

        test_section("equality");
        {
            ASSERT(b1 == b1);
            ASSERT_FALSE(b1 != b1);
            ASSERT_FALSE(b1 == b2);
            ASSERT(b1 != b2);
        }

        test_section("comparison");
        {
            ASSERT(b1 < b2);
            ASSERT_FALSE(b2 < b1);
        }
    }

    test_case("Transform3");
    {
        test_section("constructors");
        {
            nnm::Transform3 t1;
            ASSERT(t1.matrix == nnm::Matrix4::identity());

            nnm::Matrix4 m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                              { 5.0f, 6.0f, 7.0f, 8.0f },
                              { 9.0f, 10.0f, 11.0f, 12.0f },
                              { 13.0f, 14.0f, 15.0f, 16.0f } };
            nnm::Transform3 t2(m1);
            ASSERT(t2.matrix == m1);
        }

        test_section("static methods");
        {
            nnm::Basis3 b1({ { 1.0f, 2.0f, 3.0f }, { -4.0f, -1.0f, 3.5f }, { 1.0f, 0.0f, 1.0f } });
            auto t1 = nnm::Transform3::from_basis_translation(b1, { 1.0f, -2.0f, 3.0f });
            nnm::Matrix4 expected1 { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -4.0f, -1.0f, 3.5f, 0.0f },
                                     { 1.0f, 0.0f, 1.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t1.matrix == expected1);

            auto t2 = nnm::Transform3::from_translation({ 1.0f, -2.0f, 3.0f });
            nnm::Matrix4 expected2 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                     { 0.0f, 1.0f, 0.0f, 0.0f },
                                     { 0.0f, 0.0f, 1.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t2.matrix == expected2);

            auto t3 = nnm::Transform3::from_basis(b1);
            nnm::Matrix4 expected3 { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -4.0f, -1.0f, 3.5f, 0.0f },
                                     { 1.0f, 0.0f, 1.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t3.matrix == expected3);
        }

        test_section("from_rotation_axis_angle");
        {
            auto t1 = nnm::Transform3::from_rotation_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi / 9.0f);
            nnm::Matrix4 expected1 { { 0.9396926f, 0.0f, -0.3420202f, 0.0f },
                                     { 0.0f, 1.0f, 0.0f, 0.0f },
                                     { 0.3420202f, 0.0f, 0.9396926f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_scale");
        {
            auto t1 = nnm::Transform3::from_scale({ 0.2f, -0.3f, 2.1f });
            nnm::Matrix4 expected1 { { 0.2f, 0.0f, 0.0f, 0.0f },
                                     { 0.0f, -0.3f, 0.0f, 0.0f },
                                     { 0.0f, 0.0f, 2.1f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_x");
        {
            auto t1 = nnm::Transform3::from_shear_x(1.2f, -0.2f);
            nnm::Matrix4 expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                     { 2.5721516221f, 1.0f, 0.0f, 0.0f },
                                     { -0.2027100355f, 0.0f, 1.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_y");
        {
            auto t1 = nnm::Transform3::from_shear_y(-0.2f, 1.2f);
            nnm::Matrix4 expected1 { { 1.0f, -0.2027100355f, 0.0f, 0.0f },
                                     { 0.0f, 1.0f, 0.0f, 0.0f },
                                     { 0.0f, 2.5721516221f, 1.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_z");
        {
            auto t1 = nnm::Transform3::from_shear_z(1.5f, -0.3f);
            nnm::Matrix4 expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                     { 0.0f, 1.0f, 0.0f, 0.0f },
                                     { 14.1014199472f, -0.3093362496f, 1.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        auto t1 = nnm::Transform3({ { 1.0f, 2.0f, 3.0f, 0.0f },
                                    { -0.5f, 2.0f, 3.0f, 0.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } });

        auto t2 = nnm::Transform3({ { 1.0f, 2.0f, 3.0f, 4.0f },
                                    { -0.5f, 2.0f, 3.0f, -3.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } });

        test_section("basis");
        {
            nnm::Basis3 expected({ { 1.0f, 2.0f, 3.0f }, { -0.5f, 2.0f, 3.0f }, { 0.0f, 0.0f, 2.0f } });
            ASSERT(t2.basis() == expected);
        }

        test_section("valid");
        {
            ASSERT_FALSE(nnm::Transform3(nnm::Matrix4::zero()).valid());
            ASSERT(t1.valid());
            ASSERT(t2.valid());
        }

        test_section("affine");
        {
            ASSERT_FALSE(nnm::Transform3(nnm::Matrix4::zero()).affine());
            ASSERT(t1.affine());
            ASSERT_FALSE(t2.affine());
            ASSERT(nnm::Transform3().affine());
        }

        test_section("translation");
        {
            ASSERT(nnm::Transform3(nnm::Matrix4::zero()).translation() == nnm::Vector3(0.0f, 0.0f, 0.0f));
            ASSERT(t1.translation() == nnm::Vector3(1.0f, -2.0f, 3.0f));
            ASSERT(nnm::Transform3().translation() == nnm::Vector3(0.0f, 0.0f, 0.0f));
        }

        test_section("rotate_axis_angle");
        {
            auto t3 = t1.rotate_axis_angle({ 0.0f, 0.0f, 1.0f }, -nnm::pi / 9.0f);
            nnm::Matrix4 expected { { 1.62373f, 1.53737f, 3.0f, 0.0f },
                                    { 0.214194f, 2.0504f, 3.0f, 0.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 0.255652f, -2.22141f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("rotate_axis_angle_local");
        {
            auto t3 = t1.rotate_axis_angle_local({ 0.0f, 0.0f, 1.0f }, -nnm::pi / 9.0f);
            nnm::Matrix4 expected { { 1.1107f, 1.19534f, 1.79302f, 0.0f },
                                    { -0.127826f, 2.56343f, 3.84514f, 0.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("scale");
        {
            auto t3 = t1.scale({ 0.2f, -2.1f, 1.2f });
            nnm::Matrix4 expected { { 0.2f, -4.2f, 3.6f, 0.0f },
                                    { -0.1f, -4.2f, 3.6f, 0.0f },
                                    { 0.0f, 0.0f, 2.4f, 0.0f },
                                    { 0.2f, 4.2f, 3.6f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("scale_local");
        {
            auto t3 = t1.scale_local({ 0.2f, -2.1f, 1.2f });
            nnm::Matrix4 expected { { 0.2f, 0.4f, 0.6f, 0.0f },
                                    { 1.05f, -4.2f, -6.3f, 0.0f },
                                    { 0.0f, 0.0f, 2.4f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_x");
        {
            auto t3 = t1.shear_x(0.2f, -1.3f);
            nnm::Matrix4 expected { { -9.40089f, 2.0f, 3.0f, 0.0f },
                                    { -10.9009f, 2.0f, 3.0f, 0.0f },
                                    { -7.2042f, 0.0f, 2.0f, 0.0f },
                                    { -10.2117f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            auto t3 = t1.shear_x_local(0.2f, -1.3f);
            nnm::Matrix4 expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                    { -0.29729f, 2.40542f, 3.60813f, 0.0f },
                                    { -3.6021f, -7.2042f, -8.8063f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_y");
        {
            auto t3 = t1.shear_y(1.1f, -0.4f);
            nnm::Matrix4 expected { { 1.0f, 2.69638f, 3.0f, 0.0f },
                                    { -0.5f, -0.25076f, 3.0f, 0.0f },
                                    { 0.0f, -0.845586f, 2.0f, 0.0f },
                                    { 1.0f, -1.30362f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            auto t3 = t1.shear_y_local(1.1f, -0.4f);
            nnm::Matrix4 expected { { 0.0176201f, 5.92952f, 8.89428f, 0.0f },
                                    { -0.5f, 2.0f, 3.0f, 0.0f },
                                    { 0.211397f, -0.845586f, 0.73162f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_z");
        {
            auto t3 = t1.shear_z(-1.25f, 0.45f);
            nnm::Matrix4 expected { { -8.02871f, 3.44917f, 3.0f, 0.0f },
                                    { -9.52871f, 3.44917f, 3.0f, 0.0f },
                                    { -6.01914f, 0.96611f, 2.0f, 0.0f },
                                    { -8.02871f, -0.550835f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_z_local");
        {
            auto t3 = t1.shear_z_local(-1.25f, 0.45f);
            nnm::Matrix4 expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                    { -0.5f, 2.0f, 3.0f, 0.0f },
                                    { -3.2511f, -5.05303f, -5.57954f, 0.0f },
                                    { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("translate");
        {
            auto t3 = t1.translate({ 3.0f, -1.5f, 1.0f });
            nnm::Matrix4 expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                    { -0.5f, 2.0f, 3.0f, 0.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 4.0f, -3.5f, 4.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("translate_local");
        {
            auto t3 = t1.translate_local({ 3.0f, -1.5f, 1.0f });
            nnm::Matrix4 expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                    { -0.5f, 2.0f, 3.0f, 0.0f },
                                    { 0.0f, 0.0f, 2.0f, 0.0f },
                                    { 4.75f, 1.0f, 9.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("transform");
        {
            auto t3 = t1.transform(nnm::Transform3(
                { { 4.0f, 3.0f, 4.0f, 0.0f },
                  { 2.0f, -1.0f, -2.0f, 0.0f },
                  { 0.0f, 2.0f, -3.5f, 0.0f },
                  { 10.0f, -5.5f, 25.0f, 1.0f } }));
            nnm::Matrix4 expected { { 8.0f, 7.0f, -10.5f, 0.0f },
                                    { 2.0f, 2.5f, -16.5f, 0.0f },
                                    { 0.0f, 4.0f, -7.0f, 0.0f },
                                    { 10.0f, 5.5f, 22.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("transform_local");
        {
            auto t3 = t1.transform_local(nnm::Transform3(
                { { 4.0f, 3.0f, 4.0f, 0.0f },
                  { 2.0f, -1.0f, -2.0f, 0.0f },
                  { 0.0f, 2.0f, -3.5f, 0.0f },
                  { 10.0f, -5.5f, 25.0f, 1.0f } }));
            nnm::Matrix4 expected { { 2.5f, 14.0f, 29.0f, 0.0f },
                                    { 2.5f, 2.0f, -1.0f, 0.0f },
                                    { -1.0f, 4.0f, -1.0f, 0.0f },
                                    { 13.75f, 7.0f, 66.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("approx_equal");
        {
            auto t3 = nnm::Transform3({ { 1.0000001f, 2.0f, 3.0000001f, 0.0f },
                                        { -0.5f, 1.999999f, 3.0f, -0.0000001f },
                                        { 0.0f, 0.0f, 2.0f, 0.0f },
                                        { 1.0f, -1.999999f, 3.0f, 0.999999f } });
            ASSERT(t1.approx_equal(t3));
        }

        test_section("accessors");
        {
            ASSERT(t1.at(1, 2) == 3.0f);
            ASSERT(t1.at(1) == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
            ASSERT(t1[1] == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
        }

        test_section("equality");
        {
            ASSERT(t1 == t1);
            ASSERT(t1 != t2);
        }

        test_section("comparison");
        {
            ASSERT(t1 < t2);
            ASSERT_FALSE(t2 < t1);
        }
    }

    END_TESTS
}
