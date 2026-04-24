#include "tests.hpp"

void function_tests()
{
    test_case("sign");
    {
        constexpr auto result1 = nnm::sign(0.0f);
        TEST_ASSERT(result1 == 1.0f);
        TEST_ASSERT(nnm::sign(1.0f) == 1.0f);
        TEST_ASSERT(nnm::sign(-1.0f) == -1.0f);
        constexpr auto result2 = nnm::sign(0);
        TEST_ASSERT(result2 == 1);
        TEST_ASSERT(nnm::sign(1) == 1);
        TEST_ASSERT(nnm::sign(-1) == -1);
    }

    test_case("abs");
    {
        constexpr auto result1 = nnm::abs(0.0f);
        TEST_ASSERT(result1 == 0.0f);
        TEST_ASSERT(nnm::abs(1.0f) == 1.0f);
        TEST_ASSERT(nnm::abs(-1.0f) == 1.0f);
        constexpr auto result2 = nnm::abs(0);
        TEST_ASSERT(result2 == 0);
        TEST_ASSERT(nnm::abs(1) == 1);
        TEST_ASSERT(nnm::abs(-1) == 1);
    }

    test_case("max(Num, Num)");
    {
        constexpr auto result1 = nnm::max(5.0f, 10.0f);
        TEST_ASSERT(result1 == 10.0f);
        TEST_ASSERT(nnm::max(10.0f, 5.0f) == 10.0f);
        TEST_ASSERT(nnm::max(-5.0f, -10.0f) == -5.0f);
        TEST_ASSERT(nnm::max(-10.0f, -5.0f) == -5.0f);
        TEST_ASSERT(nnm::max(0.0f, 0.0f) == 0.0f);
        TEST_ASSERT(nnm::max(3.14159f, 2.71828f) == 3.14159f);
        TEST_ASSERT(nnm::max(-3.14159f, -2.71828f) == -2.71828f);

        constexpr auto result2 = nnm::max(5, 10);
        TEST_ASSERT(result2 == 10);
        TEST_ASSERT(nnm::max(10, 5) == 10);
        TEST_ASSERT(nnm::max(-5, -10) == -5);
        TEST_ASSERT(nnm::max(-10, -5) == -5);
        TEST_ASSERT(nnm::max(0, 0) == 0);
    }

    test_case("max(Num, Rest...)");
    {
        constexpr auto result1 = nnm::max(5.0f, 10.0f, -1.0f);
        TEST_ASSERT(result1 == 10.0f);
        TEST_ASSERT(nnm::max(10.0f, 5.0f, -1.0f) == 10.0f);
        TEST_ASSERT(nnm::max(-5.0f, -10.0f, 100.0f) == 100.0f);
        TEST_ASSERT(nnm::max(-10.0f, -5.0f, -7.0f) == -5.0f);
        TEST_ASSERT(nnm::max(0.0f, 0.0f, 0.0f) == 0.0f);
        TEST_ASSERT(nnm::max(3.14159f, 2.71828f, 1.1234f) == 3.14159f);
        TEST_ASSERT(nnm::max(-3.14159f, -2.71828f, -1.1234f) == -1.1234f);

        constexpr auto result2 = nnm::max(5, 10, -1);
        TEST_ASSERT(result2 == 10);
        TEST_ASSERT(nnm::max(10, 5, -1) == 10);
        TEST_ASSERT(nnm::max(-5, -10, 100) == 100);
        TEST_ASSERT(nnm::max(-10, -5, -7) == -5);
        TEST_ASSERT(nnm::max(0, 0, 0) == 0);
    }

    test_case("approx_zero");
    {
        constexpr auto result = nnm::approx_zero(0.0f);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(nnm::approx_zero(0.005f));
        TEST_ASSERT_FALSE(nnm::approx_zero(0.01f));
        TEST_ASSERT_FALSE(nnm::approx_zero(-0.005f));
        TEST_ASSERT_FALSE(nnm::approx_zero(-0.01f));
        TEST_ASSERT(nnm::approx_zero(1e-15f));
        TEST_ASSERT(nnm::approx_zero(1e-14f));
        TEST_ASSERT(nnm::approx_zero(-1e-15f));
        TEST_ASSERT(nnm::approx_zero(-1e-14f));
        TEST_ASSERT_FALSE(nnm::approx_zero(1.0f));
        TEST_ASSERT(nnm::approx_zero(0.0f));
    }

    test_case("approx_equal");
    {
        constexpr auto result = nnm::approx_equal(1.0f, 1.0f);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(nnm::approx_equal(1.0f, 1.005f));
        TEST_ASSERT_FALSE(nnm::approx_equal(1.0f, 1.01f));
        TEST_ASSERT_FALSE(nnm::approx_equal(1.0f, 1.02f));
        TEST_ASSERT_FALSE(nnm::approx_equal(-1.0f, -1.005f));
        TEST_ASSERT(nnm::approx_equal(0.0f, 0.0f));
        TEST_ASSERT_FALSE(nnm::approx_equal(0.0f, 0.005f));
        TEST_ASSERT_FALSE(nnm::approx_equal(0.005f, 0.0f));
        TEST_ASSERT(nnm::approx_equal(0.0f, 0.0f));
        TEST_ASSERT_FALSE(nnm::approx_equal(1.0f, 1.005f));
        TEST_ASSERT(nnm::approx_equal(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_less");
    {
        constexpr auto result = nnm::approx_less(0.5f, 1.0f);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::approx_less(1.0f, 1.005f));
        TEST_ASSERT_FALSE(nnm::approx_less(1.005f, 1.0f));
        TEST_ASSERT(nnm::approx_less(1.0f, 1.01f));
        TEST_ASSERT_FALSE(nnm::approx_less(1.01f, 1.0f));
        TEST_ASSERT_FALSE(nnm::approx_less(-1.0f, -1.005f));
        TEST_ASSERT(nnm::approx_less(-1.0005f, -1.0f));
        TEST_ASSERT_FALSE(nnm::approx_less(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater");
    {
        constexpr auto result = nnm::approx_greater(0.5f, 1.0f);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(nnm::approx_greater(1.0f, 1.005f));
        TEST_ASSERT(nnm::approx_greater(1.005f, 1.0f));
        TEST_ASSERT_FALSE(nnm::approx_greater(1.0f, 1.01f));
        TEST_ASSERT(nnm::approx_greater(1.01f, 1.0f));
        TEST_ASSERT(nnm::approx_greater(-1.0f, -1.005f));
        TEST_ASSERT_FALSE(nnm::approx_greater(-1.0005f, -1.0f));
        TEST_ASSERT_FALSE(nnm::approx_greater(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater");
    {
        constexpr auto result = nnm::approx_less_equal(0.5f, 1.0f);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::approx_less_equal(1.0f, 1.005f));
        TEST_ASSERT_FALSE(nnm::approx_less_equal(1.005f, 1.0f));
        TEST_ASSERT(nnm::approx_less_equal(1.0f, 1.01f));
        TEST_ASSERT_FALSE(nnm::approx_less_equal(1.01f, 1.0f));
        TEST_ASSERT_FALSE(nnm::approx_less_equal(-1.0f, -1.005f));
        TEST_ASSERT(nnm::approx_less_equal(-1.0005f, -1.0f));
        TEST_ASSERT(nnm::approx_less_equal(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater_equal");
    {
        constexpr auto result = nnm::approx_greater_equal(0.5f, 1.0f);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(nnm::approx_greater_equal(1.0f, 1.005f));
        TEST_ASSERT(nnm::approx_greater_equal(1.005f, 1.0f));
        TEST_ASSERT_FALSE(nnm::approx_greater_equal(1.0f, 1.01f));
        TEST_ASSERT(nnm::approx_greater_equal(1.01f, 1.0f));
        TEST_ASSERT(nnm::approx_greater_equal(-1.0f, -1.005f));
        TEST_ASSERT_FALSE(nnm::approx_greater_equal(-1.0005f, -1.0f));
        TEST_ASSERT(nnm::approx_greater_equal(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_less_zero");
    {
        constexpr auto result = nnm::approx_less_zero(0.0f);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_FALSE(nnm::approx_less_zero(0.005f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(0.01f));
        TEST_ASSERT(nnm::approx_less_zero(-0.005f));
        TEST_ASSERT(nnm::approx_less_zero(-0.01f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(1e-15f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(1e-14f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(-1e-15f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(-1e-14f));
        TEST_ASSERT_FALSE(nnm::approx_less_zero(1.0f));
    }

    test_case("approx_greater_zero");
    {
        constexpr auto result = nnm::approx_greater_zero(0.0f);
        TEST_ASSERT_FALSE(result);
        TEST_ASSERT(nnm::approx_greater_zero(0.005f));
        TEST_ASSERT(nnm::approx_greater_zero(0.01f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(-0.005f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(-0.01f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(1e-15f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(1e-14f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(-1e-15f));
        TEST_ASSERT_FALSE(nnm::approx_greater_zero(-1e-14f));
        TEST_ASSERT(nnm::approx_greater_zero(1.0f));
    }

    test_case("approx_less_equal_zero");
    {
        constexpr auto result = nnm::approx_less_equal_zero(0.0f);
        TEST_ASSERT(result);
        TEST_ASSERT_FALSE(nnm::approx_less_equal_zero(0.005f));
        TEST_ASSERT_FALSE(nnm::approx_less_equal_zero(0.01f));
        TEST_ASSERT(nnm::approx_less_equal_zero(-0.005f));
        TEST_ASSERT(nnm::approx_less_equal_zero(-0.01f));
        TEST_ASSERT(nnm::approx_less_equal_zero(1e-15f));
        TEST_ASSERT(nnm::approx_less_equal_zero(1e-14f));
        TEST_ASSERT(nnm::approx_less_equal_zero(-1e-15f));
        TEST_ASSERT(nnm::approx_less_equal_zero(-1e-14f));
        TEST_ASSERT_FALSE(nnm::approx_less_equal_zero(1.0f));
    }

    test_case("approx_greater_equal_zero");
    {
        constexpr auto result = nnm::approx_greater_equal_zero(0.0f);
        TEST_ASSERT(result);
        TEST_ASSERT(nnm::approx_greater_equal_zero(0.005f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(0.01f));
        TEST_ASSERT_FALSE(nnm::approx_greater_equal_zero(-0.005f));
        TEST_ASSERT_FALSE(nnm::approx_greater_equal_zero(-0.01f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(1e-15f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(1e-14f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(-1e-15f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(-1e-14f));
        TEST_ASSERT(nnm::approx_greater_equal_zero(1.0f));
    }

    test_case("ceil");
    {
        TEST_ASSERT(nnm::ceil(5.3f) == 6.0f);
        TEST_ASSERT(nnm::ceil(5.7f) == 6.0f);
        TEST_ASSERT(nnm::ceil(5.0f) == 5.0f);
        TEST_ASSERT(nnm::ceil(-5.3f) == -5.0f);
        TEST_ASSERT(nnm::ceil(-5.7f) == -5.0f);
        TEST_ASSERT(nnm::ceil(-5.0f) == -5.0f);
        TEST_ASSERT(nnm::ceil(0.0f) == 0.0f);
        TEST_ASSERT(nnm::ceil(1.0e20f) == 1.0e20f);
        TEST_ASSERT(nnm::ceil(-1.0e20f) == -1.0e20f);
        TEST_ASSERT(nnm::ceil(3.14159f) == 4.0f);
        TEST_ASSERT(nnm::ceil(-3.14159f) == -3.0f);
    }

    test_case("clamp");
    {
        constexpr auto result1 = nnm::clamp(5, 0, 10);
        TEST_ASSERT(result1 == 5);
        TEST_ASSERT(nnm::clamp(-5, 0, 10) == 0);
        TEST_ASSERT(nnm::clamp(15, 0, 10) == 10);
        TEST_ASSERT(nnm::clamp(5, 5, 5) == 5);
        constexpr auto result2 = nnm::clamp(3.5f, 1.0f, 5.0f);
        TEST_ASSERT(result2 == 3.5f);
        TEST_ASSERT(nnm::clamp(0.5f, 1.0f, 5.0f) == 1.0f);
        TEST_ASSERT(nnm::clamp(6.0f, 1.0f, 5.0f) == 5.0f);
        TEST_ASSERT(nnm::clamp(-5, -10, -2) == -5);
        TEST_ASSERT(nnm::clamp(-15, -10, -2) == -10);
        TEST_ASSERT(nnm::clamp(-3, -5, -1) == -3);
        TEST_ASSERT(nnm::clamp(-6, -5, -1) == -5);
    }

    test_case("sqrt");
    {
        TEST_ASSERT(nnm::sqrt(4.0f) == 2.0f);
        TEST_ASSERT(nnm::sqrt(9.0f) == 3.0f);
        TEST_ASSERT(nnm::sqrt(16.0f) == 4.0f);

        TEST_ASSERT(nnm::approx_equal(nnm::sqrt(4.0f), 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sqrt(9.0f), 3.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sqrt(16.0f), 4.0f));

        TEST_ASSERT(nnm::sqrt(0.0f) == 0.0f);

        TEST_ASSERT(nnm::approx_equal(nnm::sqrt(1.0e20f), 1.0e10f));
    }

    test_case("pow");
    {
        TEST_ASSERT(nnm::pow(2.0f, 3.0f) == 8.0f);
        TEST_ASSERT(nnm::pow(3.0f, 2.0f) == 9.0f);
        TEST_ASSERT(nnm::pow(4.0f, 0.0f) == 1.0f);

        TEST_ASSERT(nnm::approx_equal(nnm::pow(2.0f, 3.0f), 8.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(3.0f, 2.0f), 9.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(4.0f, 0.0f), 1.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::pow(-2.0f, 2.0f), 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(-3.0f, 2.0f), 9.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::pow(-2.0f, 3.0f), -8.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(-3.0f, 3.0f), -27.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::pow(0.0f, 3.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(0.0f, 0.0f), 1.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::pow(0.5f, 2.0f), 0.25f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(0.25f, 0.5f), 0.5f));

        TEST_ASSERT(nnm::approx_equal(nnm::pow(10.0f, 10.0f), 1.0e10f));
        TEST_ASSERT(nnm::approx_equal(nnm::pow(2.f, 100.0f), 1.2676506002282294e30f));
    }

    test_case("sqrd");
    {
        constexpr auto result1 = nnm::sqrd(2);
        TEST_ASSERT(result1 == 4);
        TEST_ASSERT(nnm::sqrd(3) == 9);
        TEST_ASSERT(nnm::sqrd(-4) == 16);

        constexpr auto result2 = nnm::sqrd(2.0f);
        TEST_ASSERT(nnm::approx_equal(result2, 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sqrd(3.0f), 9.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sqrd(-4.0f), 16.0f));

        TEST_ASSERT(nnm::sqrd(0) == 0);
        TEST_ASSERT(nnm::sqrd(0.0f) == 0.0f);

        TEST_ASSERT(nnm::approx_equal(nnm::sqrd(1.0e10f), 1.0e20f));
        TEST_ASSERT(nnm::approx_equal(nnm::sqrd(-1.0e10f), 1.0e20f));
    }

    test_case("modf");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::modf(0.0f, 1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::modf(0.0f, -1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::modf(5.0f, 3.0f), 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::modf(-5.0f, 3.0f), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::modf(5.0f, -3.0f), -1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::modf(-5.0f, -3.0f), -2.0f));
    }

    test_case("mod");
    {
        constexpr auto result = nnm::mod(0, 1);
        TEST_ASSERT(nnm::approx_equal(result, 0));
        TEST_ASSERT(nnm::approx_equal(nnm::mod(0, -1), 0));
        TEST_ASSERT(nnm::approx_equal(nnm::mod(5, 3), 2));
        TEST_ASSERT(nnm::approx_equal(nnm::mod(-5, 3), 1));
        TEST_ASSERT(nnm::approx_equal(nnm::mod(5, -3), -1));
        TEST_ASSERT(nnm::approx_equal(nnm::mod(-5, -3), -2));
    }

    test_case("remf");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::remf(0.0f, 1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::remf(0.0f, -1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::remf(5.0f, 3.0f), 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::remf(-5.0f, 3.0f), -2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::remf(5.0f, -3.0f), 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::remf(-5.0f, -3.0f), -2.0f));
    }

    test_case("rem");
    {
        constexpr auto result = nnm::rem(0, 1);
        TEST_ASSERT(nnm::approx_equal(result, 0));
        TEST_ASSERT(nnm::approx_equal(nnm::rem(0, -1), 0));
        TEST_ASSERT(nnm::approx_equal(nnm::rem(5, 3), 2));
        TEST_ASSERT(nnm::approx_equal(nnm::rem(-5, 3), -2));
        TEST_ASSERT(nnm::approx_equal(nnm::rem(5, -3), 2));
        TEST_ASSERT(nnm::approx_equal(nnm::rem(-5, -3), -2));
    }

    test_case("normalize_angle");
    {
        TEST_ASSERT(nnm::approx_zero(nnm::normalize_angle(0.0f)));

        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(nnm::pi<float>() / 4.0f), nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(2.0f * nnm::pi<float>() / 3.0f), 2.0f * nnm::pi<float>() / 3.0f));
        TEST_ASSERT(
            nnm::approx_equal(nnm::normalize_angle(5.0f * nnm::pi<float>() / 4.0f), -3.0f * nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(7.0f * nnm::pi<float>() / 4.0f), -nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_zero(nnm::normalize_angle(2.0f * nnm::pi<float>())));
        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(8.0f * nnm::pi<float>() / 3.0f), 2.0f * nnm::pi<float>() / 3.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(-nnm::pi<float>() / 4.0f), -nnm::pi<float>() / 4.0f));
        TEST_ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-2.0f * nnm::pi<float>() / 3.0f), -2.0f * nnm::pi<float>() / 3.0f));
        TEST_ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-5.0f * nnm::pi<float>() / 4.0f), 3.0f * nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::normalize_angle(-7.0f * nnm::pi<float>() / 4.0f), nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_zero(nnm::normalize_angle(-2.0f * nnm::pi<float>())));
        TEST_ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-8.0f * nnm::pi<float>() / 3.0f), -2.0f * nnm::pi<float>() / 3.0f));
    }

    test_case("floor");
    {
        TEST_ASSERT(nnm::floor(5.3f) == 5.0f);
        TEST_ASSERT(nnm::floor(5.7f) == 5.0f);
        TEST_ASSERT(nnm::floor(5.0f) == 5.0f);

        TEST_ASSERT(nnm::floor(-5.3f) == -6.0f);
        TEST_ASSERT(nnm::floor(-5.7f) == -6.0f);
        TEST_ASSERT(nnm::floor(-5.0f) == -5.0f);

        TEST_ASSERT(nnm::floor(0.0f) == 0.0f);

        TEST_ASSERT(nnm::floor(1.0e20f) == 1.0e20f);
        TEST_ASSERT(nnm::floor(-1.0e20f) == -1.0e20f);

        TEST_ASSERT(nnm::floor(3.14159f) == 3.0f);
        TEST_ASSERT(nnm::floor(-3.14159f) == -4.0f);
    }

    test_case("lerp");
    {
        constexpr auto result = nnm::lerp(0.0f, 10.0f, 0.5f);
        TEST_ASSERT(result == 5.0f);
        TEST_ASSERT(nnm::lerp(0.0f, 10.0f, 0.25f) == 2.5f);
        TEST_ASSERT(nnm::lerp(-5.0f, 5.0f, 0.75f) == 2.5f);

        TEST_ASSERT(nnm::lerp(-10.0f, -20.0f, 0.5f) == -15.0f);
        TEST_ASSERT(nnm::lerp(-10.0f, -20.0f, 0.25f) == -12.5f);
        TEST_ASSERT(nnm::lerp(-15.0f, -25.0f, 0.75f) == -22.5f);

        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);
        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);

        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);
        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);

        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, 10.0f) == 55.0f);
        TEST_ASSERT(nnm::lerp(5.0f, 10.0f, -10.0f) == -45.0f);
    }

    test_case("lerp_clamped");
    {
        constexpr auto result = nnm::lerp_clamped(5.0f, 10.0f, 20.0f);
        TEST_ASSERT(result == 10.0f);
        TEST_ASSERT(nnm::approx_equal(nnm::lerp_clamped(5.0f, 10.0f, 0.5f), 7.5f));
        TEST_ASSERT(nnm::lerp_clamped(5.0f, 10.0f, -20.0f) == 5.0f);
    }

    test_case("sin");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::sin(0.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 6.0f), 0.5f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 3.0f), nnm::sqrt(3.0f) / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 2.0f), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>()), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(3.0f * nnm::pi<float>() / 2.0f), -1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(2.0f * nnm::pi<float>()), 0.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 6.0f), -0.5f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 4.0f), -1.0f / nnm::sqrt(2.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 3.0f), -nnm::sqrt(3.0f) / 2.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::sin(4.0f * nnm::pi<float>()), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::sin(6.0f * nnm::pi<float>()), 0.0f));
    }

    test_case("cos");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::cos(0.0f), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 3.0f), 0.5f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 2.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>()), -1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(3.0f * nnm::pi<float>() / 2.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(2.0f * nnm::pi<float>()), 1.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 3.0f), 0.5f));

        TEST_ASSERT(nnm::approx_equal(nnm::cos(4.0f * nnm::pi<float>()), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::cos(6.0f * nnm::pi<float>()), 1.0f));
    }

    test_case("tan");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::tan(0.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 4.0f), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 6.0f), 1.0f / nnm::sqrt(3.0f)));

        TEST_ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 3.0f), nnm::sqrt(3.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 2.0f - 0.01f), 99.9967f));

        TEST_ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi<float>() / 3.0f), -nnm::sqrt(3.0f)));
        TEST_ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi<float>() / 2.0f + 0.01f), -99.9967f));

        TEST_ASSERT(nnm::approx_equal(nnm::tan(3.0f * nnm::pi<float>()), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::tan(6.0f * nnm::pi<float>()), 0.0f));
    }

    test_case("round");
    {
        TEST_ASSERT(nnm::round(5.3f) == 5.0f);
        TEST_ASSERT(nnm::round(5.7f) == 6.0f);
        TEST_ASSERT(nnm::round(5.0f) == 5.0f);

        TEST_ASSERT(nnm::round(-5.3f) == -5.0f);
        TEST_ASSERT(nnm::round(-5.7f) == -6.0f);
        TEST_ASSERT(nnm::round(-5.0f) == -5.0f);

        TEST_ASSERT(nnm::round(0.0f) == 0.0f);

        TEST_ASSERT(nnm::round(3.14159f) == 3.0f);
        TEST_ASSERT(nnm::round(-3.14159f) == -3.0f);
    }

    test_case("atan");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::atan(0.5f), 0.4636476f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan(1.0f), 0.7853981f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan(2.0f), 1.1071487f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan(-0.5f), -0.4636476f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan(-1.0f), -0.7853981f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan(-2.0f), -1.1071487f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan(0.0f), 0.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan(1.0e20f), 1.5707963f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan(-1.0e20f), -1.5707963f));
    }

    test_case("atan2");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 1.0f), 0.7853981633974483f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 2.0f), 0.4636476090008061f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan2(-1.0f, -1.0f), -2.356194490192345f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(-1.0f, 2.0f), -0.4636476090008061f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan2(0.0f, 1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(1.0f, 0.0f), 1.5707963267948966f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(0.0f, 0.0f), 0.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::atan2(1.0e20f, 1.0e20f), 0.7853981633974483f));
        TEST_ASSERT(nnm::approx_equal(nnm::atan2(-1.0e20f, -1.0e20f), -2.356194490192345f));
    }

    test_case("radians");
    {
        constexpr auto result = nnm::radians(0.0f);
        TEST_ASSERT(nnm::approx_equal(result, 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(45.0f), nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(90.0f), nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(180.0f), nnm::pi<float>()));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(270.0f), 3.0f * nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(360.0f), 2.0f * nnm::pi<float>()));

        TEST_ASSERT(nnm::approx_equal(nnm::radians(-45.0f), -nnm::pi<float>() / 4.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(-90.0f), -nnm::pi<float>() / 2.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(-180.0f), -nnm::pi<float>()));

        TEST_ASSERT(nnm::approx_equal(nnm::radians(720.0f), 4.0f * nnm::pi<float>()));
        TEST_ASSERT(nnm::approx_equal(nnm::radians(1080.0f), 6.0f * nnm::pi<float>()));

        TEST_ASSERT(nnm::approx_equal(nnm::radians(180.0f), 3.14159f));
    }

    test_case("degrees");
    {
        constexpr auto result = nnm::degrees(0.0f);
        TEST_ASSERT(nnm::approx_equal(result, 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>() / 4.0f), 45.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>() / 2.0f), 90.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>()), 180.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(3.0f * nnm::pi<float>() / 2.0f), 270.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(2.0f * nnm::pi<float>()), 360.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>() / 4.0f), -45.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>() / 2.0f), -90.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>()), -180.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::degrees(4.0f * nnm::pi<float>()), 720.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::degrees(6.0f * nnm::pi<float>()), 1080.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::degrees(3.14159f), 180.0f));
    }

    test_case("asin");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::asin(0.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::asin(0.5f), 0.5235987756f));
        TEST_ASSERT(nnm::approx_equal(nnm::asin(-0.5f), -0.5235987756f));
        TEST_ASSERT(nnm::approx_equal(nnm::asin(1.0f), 1.570796327f));
        TEST_ASSERT(nnm::approx_equal(nnm::asin(-1.0f), -1.570796327f));
    }

    test_case("acos");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::acos(1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::acos(0.5f), 1.047197551f));
        TEST_ASSERT(nnm::approx_equal(nnm::acos(-0.5f), 2.094395102f));
        TEST_ASSERT(nnm::approx_equal(nnm::acos(0.0f), 1.570796327f));
        TEST_ASSERT(nnm::approx_equal(nnm::acos(-1.0f), 3.141592654f));
    }

    test_case("min(Num, Num)");
    {
        constexpr auto result1 = nnm::min(1, 2);
        TEST_ASSERT(result1 == 1);
        TEST_ASSERT(nnm::min(5, 3) == 3);
        TEST_ASSERT(nnm::min(-1, -5) == -5);
        TEST_ASSERT(nnm::min(3, 3) == 3);

        constexpr auto result2 = nnm::min(1.0f, 2.0f);
        TEST_ASSERT(result2 == 1.0f);
        TEST_ASSERT(nnm::min(5.5f, 3.5f) == 3.5f);
        TEST_ASSERT(nnm::min(-1.0f, -5.0f) == -5.0f);
        TEST_ASSERT(nnm::min(3.0f, 3.0f) == 3.0f);

        TEST_ASSERT(nnm::min('a', 'b') == 'a');
        TEST_ASSERT(nnm::min(3.14f, 2.71f) == 2.71f);
    }

    test_case("min(Num, Rest...)");
    {
        constexpr auto result1 = nnm::min(1, 2, 3);
        TEST_ASSERT(result1 == 1);
        TEST_ASSERT(nnm::min(5, 3, 1) == 1);
        TEST_ASSERT(nnm::min(-1, -5, 2) == -5);
        TEST_ASSERT(nnm::min(3, 3, 3) == 3);

        constexpr auto result2 = nnm::min(1.0f, 2.0f, 3.0f);
        TEST_ASSERT(result2 == 1.0f);
        TEST_ASSERT(nnm::min(5.5f, 3.5f, 100.0f) == 3.5f);
        TEST_ASSERT(nnm::min(-1.0f, -5.0f, -100.0f) == -100.0f);
        TEST_ASSERT(nnm::min(3.0f, 3.0f, 3.0f) == 3.0f);

        TEST_ASSERT(nnm::min('a', 'b', 'c') == 'a');
        TEST_ASSERT(nnm::min(3.14f, 2.71f, 1.123f) == 1.123f);
    }

    test_case("log2");
    {
        TEST_ASSERT(nnm::approx_equal(nnm::log2(1.0f), 0.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::log2(2.0f), 1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::log2(8.0f), 3.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::log2(16.0f), 4.0f));

        TEST_ASSERT(nnm::approx_equal(nnm::log2(0.5f), -1.0f));
        TEST_ASSERT(nnm::approx_equal(nnm::log2(4.0f), 2.0f));
    }
}
