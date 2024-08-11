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
        ASSERT(nnm::abs(0.0f) == 0.0f);
        ASSERT(nnm::abs(1.0f) == 1.0f);
        ASSERT(nnm::abs(-1.0f) == 1.0f);
        ASSERT(nnm::abs(0) == 0);
        ASSERT(nnm::abs(1) == 1);
        ASSERT(nnm::abs(-1) == 1);
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

    test_case("clamped_lerp");
    {
        ASSERT(nnm::clamped_lerp(5.0f, 10.0f, 20.0f) == 10.0f);
        ASSERT(nnm::clamped_lerp(5.0f, 10.0f, -20.0f) == 5.0f);
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
        test_section("constructors");
        {
            const nnm::Vector2 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
            const nnm::Vector2 v2(nnm::Vector2i(1, 2));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
            const nnm::Vector2 v3(1.0f, 2.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
        }

        test_section("static methods");
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

        test_section("clamped_lerp");
        {
            const nnm::Vector2 from(1.0f, 1.0f);
            const nnm::Vector2 to(3.0f, 5.0f);
            ASSERT(from.clamped_lerp(to, 0.0f) == nnm::Vector2(1.0f, 1.0f));
            ASSERT(from.clamped_lerp(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.clamped_lerp(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
            ASSERT(from.clamped_lerp(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
            ASSERT(from.clamped_lerp(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
            ASSERT(from.clamped_lerp(to, 5.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.clamped_lerp(to, -5.0f) == nnm::Vector2(1.0f, 1.0f));
        }

        test_section("min/max_index");
        {
            nnm::Vector2 v1(3.0f, 4.0f);
            ASSERT(v1.max_index() == 1);
            ASSERT(v1.min_index() == 0);

            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.max_index() == 1);
            ASSERT(v2.min_index() == 0);

            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
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

        test_section("transform");
        {
            nnm::Basis2 b1;
            nnm::Vector2 v1(2.0f, -1.0f);
            ASSERT(v1.transform(b1).approx_equal({ 2.0f, -1.0f }));
            const auto b2 = nnm::Basis2().rotate(nnm::pi / 2.0f);
            ASSERT(v1.transform(b2).approx_equal({ 1.0f, 2.0f }))
            const auto b3 = nnm::Basis2().rotate(-nnm::pi / 2.0f);
            ASSERT(v1.transform(b3).approx_equal({ -1.0f, -2.0f }))
        }

        test_section("equality operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            const nnm::Vector2 v2(3.0f, 4.0f);
            const nnm::Vector2 v3(1.0f, 2.0f);
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("arithmetic operators");
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

        test_section("compound assignment operators");
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

        test_section("comparison operator");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            const nnm::Vector2 v2(3.0f, 4.0f);
            ASSERT(v1 < v2);
        }

        test_section("indexing operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            ASSERT(v1[0] == 1.0f);
            ASSERT(v1[1] == 2.0f);
            ASSERT(v1.at(0) == 1.0f);
            ASSERT(v1.at(1) == 2.0f);
        }

        test_section("conversion operators");
        {
            const nnm::Vector2 v1(1.0f, 2.0f);
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
        }
    }

    test_case("Vector2i");
    {
        test_section("constructors");
        {
            const nnm::Vector2i v1;
            ASSERT(v1.x == 0);
            ASSERT(v1.y == 0);

            const nnm::Vector2i v2(1, 2);
            ASSERT(v2.x == 1);
            ASSERT(v2.y == 2);
        }

        test_section("static methods");
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

        test_section("min/max_index");
        {
            nnm::Vector2i v1(3, 4);
            ASSERT(v1.max_index() == 1);
            ASSERT(v1.min_index() == 0);

            nnm::Vector2i v2(2, 5);
            ASSERT(v2.max_index() == 1);
            ASSERT(v2.min_index() == 0);

            nnm::Vector2i v3(0, 0);
            ASSERT(v3.max_index() == 0);
            ASSERT(v3.min_index() == 0);
        }

        test_section("equality operators");
        {
            const nnm::Vector2i v1(1, 2);
            const nnm::Vector2i v2(3, 4);
            const nnm::Vector2i v3(1, 2);
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("arithmetic operators");
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

        test_section("compound assignment operators");
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

        test_section("comparison operator");
        {
            const nnm::Vector2i v1(1, 2);
            const nnm::Vector2i v2(3, 4);
            ASSERT(v1 < v2);
        }

        test_section("indexing operators");
        {
            const nnm::Vector2i v1(1, 2);
            ASSERT(v1[0] == 1);
            ASSERT(v1[1] == 2);
            ASSERT(v1.at(0) == 1);
            ASSERT(v1.at(1) == 2);
        }

        test_section("conversion operators");
        {
            const nnm::Vector2i v1(1, 2);
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
        }
    }

    test_case("Vector3");
    {
        test_section("constructors");
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

        test_section("static methods");
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

        test_section("clamped_lerp");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(3.0f, 5.0f, -2.0f);
            ASSERT(from.clamped_lerp(to, 0.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.clamped_lerp(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
            ASSERT(from.clamped_lerp(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
            ASSERT(from.clamped_lerp(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
            ASSERT(from.clamped_lerp(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
            ASSERT(from.clamped_lerp(to, -5.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.clamped_lerp(to, 5.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
        }

        test_section("min/max_index");
        {
            nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            ASSERT(v1.max_index() == 1);
            ASSERT(v1.min_index() == 2);

            nnm::Vector3 v2(-100.0f, 5.0f, 100.0f);
            ASSERT(v2.max_index() == 2);
            ASSERT(v2.min_index() == 0);

            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
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

        test_section("dot");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            ASSERT(v1.dot(v2) == -28.0f);
        }

        test_section("outer");
        {
            const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            const nnm::Matrix3 expected { { -2.0f, 4.0f, -6.0f }, { 4.0f, -8.0f, 12.0f }, { -6.0f, 12.0f, -18.0f } };
            ASSERT(v1.outer(v2).approx_equal(expected));
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
            constexpr float angle = nnm::pi / 2.0f;

            ASSERT(v.rotate(axis, angle).approx_equal(nnm::Vector3(-2.0f, 1.0f, 3.0f)));
            ASSERT(v.rotate(axis, 2.0f * angle).approx_equal(nnm::Vector3(-1.0f, -2.0f, 3.0f)));
            ASSERT(v.rotate(axis, 4.0f * angle).approx_equal(v));
            ASSERT(v.rotate(axis, 0.0f).approx_equal(v));
        }

        nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
        nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
        nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

        test_section("equality operators");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("arithmetic operators");
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

        test_section("compound assignment operators");
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

        test_section("comparison operator");
        {
            ASSERT(v1 < v2);
            ASSERT_FALSE(v2 < v1);
        }

        test_section("indexing operators");
        {
            ASSERT(v1[0] == 1.0f);
            ASSERT(v1[1] == 2.0f);
            ASSERT(v1[2] == 3.0f);
            ASSERT(v1.at(0) == 1.0f);
            ASSERT(v1.at(1) == 2.0f);
            ASSERT(v1.at(2) == 3.0f);
        }

        test_section("conversion operators");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
        }
    }

    test_case("Vector3i");
    {
        test_section("constructors");
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

        test_section("static methods");
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

        test_section("min/max_index");
        {
            nnm::Vector3i v1(1, -2, 3);
            ASSERT(v1.min_index() == 1);
            ASSERT(v1.max_index() == 2);
            nnm::Vector3i v2(-1, 2, -3);
            ASSERT(v2.min_index() == 2);
            ASSERT(v2.max_index() == 1);
        }

        nnm::Vector3i v1(1, 2, -3);
        nnm::Vector3i v2(-3, 4, 100);
        nnm::Vector3i v3(1, 2, -3);

        test_section("equality operators");
        {
            ASSERT(v1 == v3);
            ASSERT_FALSE(v1 != v3);
            ASSERT(v1 != v2);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("arithmetic operators");
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

        test_section("compound assignment operators");
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

        test_section("comparison operator");
        {
            ASSERT(v2 < v1);
            ASSERT_FALSE(v1 < v2);
        }

        test_section("indexing operators");
        {
            ASSERT(v1[0] == 1);
            ASSERT(v1[1] == 2);
            ASSERT(v1[2] == -3);
            ASSERT(v1.at(0) == 1);
            ASSERT(v1.at(1) == 2);
            ASSERT(v1.at(2) == -3);
        }

        test_section("conversion operators");
        {
            ASSERT(static_cast<bool>(v1));
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
        }
    }

    test_case("Vector4");
    {
        test_section("constructors");
        {
            const nnm::Vector4 v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
            ASSERT(v1.z == 0.0f);
            ASSERT(v1.w == 0.0f);

            const nnm::Vector4 v2(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(v2.x == -1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == -3.0f);
            ASSERT(v2.w == 4.0f);
        }

        test_section("static methods");
        {
            const auto v1 = nnm::Vector4::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);
            ASSERT(v1.w == 3.0f);

            const auto v2 = nnm::Vector4::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);
            ASSERT(v2.w == 0.0f);

            const auto v3 = nnm::Vector4::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
            ASSERT(v3.w == 1.0f);
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

        test_section("clamp");
        {
            const nnm::Vector4 v1(-1.0f, 2.0f, 3.0f, -4.0f);
            const nnm::Vector4 v2(2.0f, -3.0f, -2.0f, -3.0f);
            const nnm::Vector4 v3(4.0f, 1.0f, 4.0f, 1.0f);
            ASSERT(v1.clamp(v2, v3) == nnm::Vector4(2.0f, 1.0f, 3.0f, -3.0f));
        }

        test_section("normalize");
        {
            ASSERT(nnm::Vector4().normalize() == nnm::Vector4());
            const nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            const nnm::Vector4 v_expected(-0.182574f, 0.365148f, -0.547723f, 0.730297f);
            ASSERT(v1.normalize().approx_equal(v_expected));
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

        test_section("lerp");
        {
            ASSERT(v1.lerp(v2, 0.0f) == v1);
            ASSERT(v1.lerp(v2, 1.0f) == v2);
            ASSERT(v1.lerp(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
        }

        test_section("clamped_lerp");
        {
            ASSERT(v1.clamped_lerp(v2, 0.0f) == v1);
            ASSERT(v1.clamped_lerp(v2, 1.0f) == v2);
            ASSERT(v1.clamped_lerp(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
            ASSERT(v1.clamped_lerp(v2, -5.0f) == v1);
            ASSERT(v1.clamped_lerp(v2, 5.0f) == v2);
        }

        test_section("min/max_index");
        {
            ASSERT(v1.min_index() == 2);
            ASSERT(v1.max_index() == 3);
            ASSERT(v2.min_index() == 2);
            ASSERT(v2.max_index() == 1);
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

        test_section("dot");
        {
            ASSERT(nnm::approx_equal(v1.dot(v2), 18.0f));
        }

        test_section("inverse");
        {
            const nnm::Vector4 v_expected(-1.0f, 0.5f, -0.33333333f, 0.25f);
            ASSERT(v1.inverse().approx_equal(v_expected));
        }

        test_section("clamp_length");
        {
            ASSERT(v1.clamp_length(0.0f, 1.0f).approx_equal(v1.normalize()));
            ASSERT(v1.clamp_length(2.0f, 3.0f).approx_equal(v1.normalize() * 3.0f));
            ASSERT(v1.clamp_length(10.0f, 50.0f).approx_equal(v1.normalize() * 10.0f));
        }

        test_section("round");
        {
            // TODO
        }
    }

    test_case("Matrix2");
    {
        test_section("Constructors");
        {
            const nnm::Matrix2 mat_default;
            ASSERT(mat_default.col0_row0 == 1.0f);
            ASSERT(mat_default.col0_row1 == 0.0f);
            ASSERT(mat_default.col1_row0 == 0.0f);
            ASSERT(mat_default.col1_row1 == 1.0f);

            const nnm::Matrix2 mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat_cols.col0_row0 == 1.0f);
            ASSERT(mat_cols.col0_row1 == -2.0f);
            ASSERT(mat_cols.col1_row0 == -3.0f);
            ASSERT(mat_cols.col1_row1 == 4.0f);

            const nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
            ASSERT(mat_elements.col0_row0 == 1.0f);
            ASSERT(mat_elements.col0_row1 == -2.0f);
            ASSERT(mat_elements.col1_row0 == -3.0f);
            ASSERT(mat_elements.col1_row1 == 4.0f);
        }

        test_section("Static methods");
        {
            const auto mat_all_three = nnm::Matrix2::all(3.0f);
            ASSERT(mat_all_three.col0_row0 == 3.0f);
            ASSERT(mat_all_three.col0_row1 == 3.0f);
            ASSERT(mat_all_three.col1_row0 == 3.0f);
            ASSERT(mat_all_three.col1_row1 == 3.0f);

            const auto mat_zero = nnm::Matrix2::zero();
            ASSERT(mat_zero.col0_row0 == 0.0f);
            ASSERT(mat_zero.col0_row1 == 0.0f);
            ASSERT(mat_zero.col1_row0 == 0.0f);
            ASSERT(mat_zero.col1_row1 == 0.0f);

            const auto mat_one = nnm::Matrix2::one();
            ASSERT(mat_one.col0_row0 == 1.0f);
            ASSERT(mat_one.col0_row1 == 1.0f);
            ASSERT(mat_one.col1_row0 == 1.0f);
            ASSERT(mat_one.col1_row1 == 1.0f);

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
            const std::optional<nnm::Matrix2> mat_inv = mat.inverse();
            ASSERT(mat_inv.has_value());
            ASSERT(mat.inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT(mat.unchecked_inverse().approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT_FALSE(nnm::Matrix2::zero().inverse().has_value());
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
            const auto b1 = nnm::Basis2::from_scale({ 2.0f, -3.0f });
            ASSERT(b1.matrix == nnm::Matrix2({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
        }

        // TODO
        // test_section("from shear");
        // {
        //     const auto b1 = nnm::Basis2::from_shear({ 2.0f, -3.0f });
        //     ASSERT(b1.matrix == nnm::Matrix2({ 1.0f, 2.0f }, { -3.0f, 1.0f }));
        // }

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
            const auto b2_rotated = b2.rotate(nnm::pi / 4.0f);
            ASSERT(b2_rotated.matrix.approx_equal({ { 1.41421, 1.41421 }, { -0.353553, 0.353553 } }));
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

        // TODO
        // test_section("shear");
        // {
        //     const nnm::Basis2 b1;
        //     ASSERT(b1.shear({ 0.0f, 0.0f }).matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
        //     ASSERT(b1.shear({ 1.0f, 1.0f }).matrix.approx_equal({ { 1.0f, 1.0f }, { 1.0f, 1.0f } }));
        //     ASSERT(b1.shear({ 2.0f, -0.5f }).matrix.approx_equal({ { 1.0f, 2.0f }, { -0.5f, 1.0f } }));
        // }

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
            ASSERT(m1.unchecked_inverse().approx_equal(result));
            ASSERT(m1.inverse().has_value());
            ASSERT(m1.inverse().value().approx_equal(result));
            ASSERT_FALSE(nnm::Matrix3::zero().inverse().has_value());
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

    test_case("Transform2");
    {
        test_section("constructors");
        {
            nnm::Transform2 default_transform;
            ASSERT(default_transform.matrix == nnm::Matrix3::identity());
            nnm::Transform2 transform_matrix(nnm::Matrix3::all(3.0f));
            ASSERT(transform_matrix.matrix == nnm::Matrix3::all(3.0f));
        }

        test_section("static methods");
        {
            const nnm::Basis2 basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
            const nnm::Vector2 pos(-1.0f, 2.0f);
            const auto transform_basis_pos = nnm::Transform2::from_basis_translation(basis, pos);
            ASSERT(
                transform_basis_pos.matrix
                == nnm::Matrix3({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f }));
            const auto transform_pos = nnm::Transform2::from_translation(pos);
            ASSERT(
                transform_pos.matrix
                == nnm::Matrix3({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 2.0f, 1.0f }));
            const auto transform_basis = nnm::Transform2::from_basis(basis);
            ASSERT(
                transform_basis.matrix
                == nnm::Matrix3({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
            const auto transform_rot = nnm::Transform2::from_rotation(nnm::pi / 2.0f);
            ASSERT(transform_rot.matrix.approx_equal(
                nnm::Matrix3({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f })));
            const auto transform_scale = nnm::Transform2::from_scale({ -2.0f, 3.0f });
            ASSERT(
                transform_scale.matrix
                == nnm::Matrix3({ -2.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
            // TODO
            // const auto transform_shear = nnm::Transform2::from_shear({ 1.0f, -2.0f });
            // ASSERT(
            // transform_shear.matrix
            // == nnm::Matrix3({ 1.0f, 1.0f, 0.0f }, { -2.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
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

        // TODO
        // test_section("shear");
        // {
        //     const auto t_sheared = t2.shear({ 1.0f, -2.0f });
        //     const auto t_expected
        //         = nnm::Transform2::from_basis_translation(t2.basis().shear({ 1.0f, -2.0f }), { 5.0f, -1.0f });
        //     ASSERT(t_sheared.approx_equal(t_expected));
        // }

        // TODO
        // test_section("shear_local");
        // {
        //     const auto t_sheared = t2.shear_local({ 1.0f, -2.0f });
        //     const auto t_expected
        //         = nnm::Transform2::from_basis_translation(t2.basis().shear_local({ 1.0f, -2.0f }), { 1.0f, -2.0f });
        //     ASSERT(t_sheared.approx_equal(t_expected));
        // }

        test_section("translate");
        {
            ASSERT(
                t1.translate({ 2.0f, -1.0f })
                == nnm::Transform2::from_basis_translation(t1.basis(), t1.translation() + nnm::Vector2(2.0f, -1.0f)));
        }

        test_section("translate_local");
        {
            const auto t
                = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi / 2.0f), { 1.0f, -2.0f });
            const auto t_translated = t.translate_local({ 3.0f, -4.0f });
            const auto t_expected
                = nnm::Transform2::from_basis_translation(nnm::Basis2::from_rotation(nnm::pi / 2.0f), { 5.0f, 1.0f });
            ASSERT(t_translated.approx_equal(t_expected));
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

        test_section("accessors");
        {
            ASSERT(nnm::approx_equal(t2.at(0, 0), 0.0f));
            ASSERT(nnm::approx_equal(t2.at(1, 2), 0.0f));
            ASSERT(nnm::approx_equal(t2.at(2, 1), -2.0f));
            ASSERT(nnm::approx_equal(t2.at(2, 2), 1.0f));
            ASSERT(nnm::approx_equal(t2[0][0], 0.0f));
            ASSERT(nnm::approx_equal(t2[1][2], 0.0f));
            ASSERT(nnm::approx_equal(t2[2][1], -2.0f));
            ASSERT(nnm::approx_equal(t2[2][2], 1.0f));
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
                { { 1.0f, 0.0f, 0.0f }, { 0.5463024898f, 1.0f, 0.0f }, { -0.1003346721, 0.0f, 1.0f } }));
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

        test_section("tace");
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
            nnm::Basis3 b1({ { 1.000001f, -0.00001f, 0.0f }, { 0.0f, 0.99999999f, 0.000001 }, { 0.0f, 0.0f, 1.0f } });
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
    END_TESTS
}
