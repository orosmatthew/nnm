#pragma once

#include "test.hpp"

// ReSharper disable CppDFATimeOver

inline void nnm_tests()
{
    test_case("sign");
    {
        constexpr auto result1 = nnm::sign(0.0f);
        ASSERT(result1 == 1.0f);
        ASSERT(nnm::sign(1.0f) == 1.0f);
        ASSERT(nnm::sign(-1.0f) == -1.0f);
        constexpr auto result2 = nnm::sign(0);
        ASSERT(result2 == 1);
        ASSERT(nnm::sign(1) == 1);
        ASSERT(nnm::sign(-1) == -1);
    }

    test_case("abs");
    {
        constexpr auto result1 = nnm::abs(0.0f);
        ASSERT(result1 == 0.0f);
        ASSERT(nnm::abs(1.0f) == 1.0f);
        ASSERT(nnm::abs(-1.0f) == 1.0f);
        constexpr auto result2 = nnm::abs(0);
        ASSERT(result2 == 0);
        ASSERT(nnm::abs(1) == 1);
        ASSERT(nnm::abs(-1) == 1);
    }

    test_case("max(Num, Num)");
    {
        constexpr auto result1 = nnm::max(5.0f, 10.0f);
        ASSERT(result1 == 10.0f);
        ASSERT(nnm::max(10.0f, 5.0f) == 10.0f);
        ASSERT(nnm::max(-5.0f, -10.0f) == -5.0f);
        ASSERT(nnm::max(-10.0f, -5.0f) == -5.0f);
        ASSERT(nnm::max(0.0f, 0.0f) == 0.0f);
        ASSERT(nnm::max(3.14159f, 2.71828f) == 3.14159f);
        ASSERT(nnm::max(-3.14159f, -2.71828f) == -2.71828f);

        constexpr auto result2 = nnm::max(5, 10);
        ASSERT(result2 == 10);
        ASSERT(nnm::max(10, 5) == 10);
        ASSERT(nnm::max(-5, -10) == -5);
        ASSERT(nnm::max(-10, -5) == -5);
        ASSERT(nnm::max(0, 0) == 0);
    }

    test_case("max(Num, Rest...)");
    {
        constexpr auto result1 = nnm::max(5.0f, 10.0f, -1.0f);
        ASSERT(result1 == 10.0f);
        ASSERT(nnm::max(10.0f, 5.0f, -1.0f) == 10.0f);
        ASSERT(nnm::max(-5.0f, -10.0f, 100.0f) == 100.0f);
        ASSERT(nnm::max(-10.0f, -5.0f, -7.0f) == -5.0f);
        ASSERT(nnm::max(0.0f, 0.0f, 0.0f) == 0.0f);
        ASSERT(nnm::max(3.14159f, 2.71828f, 1.1234f) == 3.14159f);
        ASSERT(nnm::max(-3.14159f, -2.71828f, -1.1234f) == -1.1234f);

        constexpr auto result2 = nnm::max(5, 10, -1);
        ASSERT(result2 == 10);
        ASSERT(nnm::max(10, 5, -1) == 10);
        ASSERT(nnm::max(-5, -10, 100) == 100);
        ASSERT(nnm::max(-10, -5, -7) == -5);
        ASSERT(nnm::max(0, 0, 0) == 0);
    }

    test_case("approx_zero");
    {
        constexpr auto result = nnm::approx_zero(0.0f);
        ASSERT(result);
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
        constexpr auto result = nnm::approx_equal(1.0f, 1.0f);
        ASSERT(result);
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

    test_case("approx_less");
    {
        constexpr auto result = nnm::approx_less(0.5f, 1.0f);
        ASSERT(result);
        ASSERT(nnm::approx_less(1.0f, 1.005f));
        ASSERT_FALSE(nnm::approx_less(1.005f, 1.0f));
        ASSERT(nnm::approx_less(1.0f, 1.01f));
        ASSERT_FALSE(nnm::approx_less(1.01f, 1.0f));
        ASSERT_FALSE(nnm::approx_less(-1.0f, -1.005f));
        ASSERT(nnm::approx_less(-1.0005f, -1.0f));
        ASSERT_FALSE(nnm::approx_less(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater");
    {
        constexpr auto result = nnm::approx_greater(0.5f, 1.0f);
        ASSERT_FALSE(result);
        ASSERT_FALSE(nnm::approx_greater(1.0f, 1.005f));
        ASSERT(nnm::approx_greater(1.005f, 1.0f));
        ASSERT_FALSE(nnm::approx_greater(1.0f, 1.01f));
        ASSERT(nnm::approx_greater(1.01f, 1.0f));
        ASSERT(nnm::approx_greater(-1.0f, -1.005f));
        ASSERT_FALSE(nnm::approx_greater(-1.0005f, -1.0f));
        ASSERT_FALSE(nnm::approx_greater(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater");
    {
        constexpr auto result = nnm::approx_less_equal(0.5f, 1.0f);
        ASSERT(result);
        ASSERT(nnm::approx_less_equal(1.0f, 1.005f));
        ASSERT_FALSE(nnm::approx_less_equal(1.005f, 1.0f));
        ASSERT(nnm::approx_less_equal(1.0f, 1.01f));
        ASSERT_FALSE(nnm::approx_less_equal(1.01f, 1.0f));
        ASSERT_FALSE(nnm::approx_less_equal(-1.0f, -1.005f));
        ASSERT(nnm::approx_less_equal(-1.0005f, -1.0f));
        ASSERT(nnm::approx_less_equal(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_greater_equal");
    {
        constexpr auto result = nnm::approx_greater_equal(0.5f, 1.0f);
        ASSERT_FALSE(result);
        ASSERT_FALSE(nnm::approx_greater_equal(1.0f, 1.005f));
        ASSERT(nnm::approx_greater_equal(1.005f, 1.0f));
        ASSERT_FALSE(nnm::approx_greater_equal(1.0f, 1.01f));
        ASSERT(nnm::approx_greater_equal(1.01f, 1.0f));
        ASSERT(nnm::approx_greater_equal(-1.0f, -1.005f));
        ASSERT_FALSE(nnm::approx_greater_equal(-1.0005f, -1.0f));
        ASSERT(nnm::approx_greater_equal(1.0e20f, 1.000000000001e20f));
    }

    test_case("approx_less_zero");
    {
        constexpr auto result = nnm::approx_less_zero(0.0f);
        ASSERT_FALSE(result);
        ASSERT_FALSE(nnm::approx_less_zero(0.005f));
        ASSERT_FALSE(nnm::approx_less_zero(0.01f));
        ASSERT(nnm::approx_less_zero(-0.005f));
        ASSERT(nnm::approx_less_zero(-0.01f));
        ASSERT_FALSE(nnm::approx_less_zero(1e-15f));
        ASSERT_FALSE(nnm::approx_less_zero(1e-14f));
        ASSERT_FALSE(nnm::approx_less_zero(-1e-15f));
        ASSERT_FALSE(nnm::approx_less_zero(-1e-14f));
        ASSERT_FALSE(nnm::approx_less_zero(1.0f));
    }

    test_case("approx_greater_zero");
    {
        constexpr auto result = nnm::approx_greater_zero(0.0f);
        ASSERT_FALSE(result);
        ASSERT(nnm::approx_greater_zero(0.005f));
        ASSERT(nnm::approx_greater_zero(0.01f));
        ASSERT_FALSE(nnm::approx_greater_zero(-0.005f));
        ASSERT_FALSE(nnm::approx_greater_zero(-0.01f));
        ASSERT_FALSE(nnm::approx_greater_zero(1e-15f));
        ASSERT_FALSE(nnm::approx_greater_zero(1e-14f));
        ASSERT_FALSE(nnm::approx_greater_zero(-1e-15f));
        ASSERT_FALSE(nnm::approx_greater_zero(-1e-14f));
        ASSERT(nnm::approx_greater_zero(1.0f));
    }

    test_case("approx_less_equal_zero");
    {
        constexpr auto result = nnm::approx_less_equal_zero(0.0f);
        ASSERT(result);
        ASSERT_FALSE(nnm::approx_less_equal_zero(0.005f));
        ASSERT_FALSE(nnm::approx_less_equal_zero(0.01f));
        ASSERT(nnm::approx_less_equal_zero(-0.005f));
        ASSERT(nnm::approx_less_equal_zero(-0.01f));
        ASSERT(nnm::approx_less_equal_zero(1e-15f));
        ASSERT(nnm::approx_less_equal_zero(1e-14f));
        ASSERT(nnm::approx_less_equal_zero(-1e-15f));
        ASSERT(nnm::approx_less_equal_zero(-1e-14f));
        ASSERT_FALSE(nnm::approx_less_equal_zero(1.0f));
    }

    test_case("approx_greater_equal_zero");
    {
        constexpr auto result = nnm::approx_greater_equal_zero(0.0f);
        ASSERT(result);
        ASSERT(nnm::approx_greater_equal_zero(0.005f));
        ASSERT(nnm::approx_greater_equal_zero(0.01f));
        ASSERT_FALSE(nnm::approx_greater_equal_zero(-0.005f));
        ASSERT_FALSE(nnm::approx_greater_equal_zero(-0.01f));
        ASSERT(nnm::approx_greater_equal_zero(1e-15f));
        ASSERT(nnm::approx_greater_equal_zero(1e-14f));
        ASSERT(nnm::approx_greater_equal_zero(-1e-15f));
        ASSERT(nnm::approx_greater_equal_zero(-1e-14f));
        ASSERT(nnm::approx_greater_equal_zero(1.0f));
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
        constexpr auto result1 = nnm::clamp(5, 0, 10);
        ASSERT(result1 == 5);
        ASSERT(nnm::clamp(-5, 0, 10) == 0);
        ASSERT(nnm::clamp(15, 0, 10) == 10);
        ASSERT(nnm::clamp(5, 5, 5) == 5);
        constexpr auto result2 = nnm::clamp(3.5f, 1.0f, 5.0f);
        ASSERT(result2 == 3.5f);
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

        ASSERT(nnm::approx_equal(nnm::sqrt(4.0f), 2.0f));
        ASSERT(nnm::approx_equal(nnm::sqrt(9.0f), 3.0f));
        ASSERT(nnm::approx_equal(nnm::sqrt(16.0f), 4.0f));

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
        constexpr auto result1 = nnm::sqrd(2);
        ASSERT(result1 == 4);
        ASSERT(nnm::sqrd(3) == 9);
        ASSERT(nnm::sqrd(-4) == 16);

        constexpr auto result2 = nnm::sqrd(2.0f);
        ASSERT(nnm::approx_equal(result2, 4.0f));
        ASSERT(nnm::approx_equal(nnm::sqrd(3.0f), 9.0f));
        ASSERT(nnm::approx_equal(nnm::sqrd(-4.0f), 16.0f));

        ASSERT(nnm::sqrd(0) == 0);
        ASSERT(nnm::sqrd(0.0f) == 0.0f);

        ASSERT(nnm::approx_equal(nnm::sqrd(1.0e10f), 1.0e20f));
        ASSERT(nnm::approx_equal(nnm::sqrd(-1.0e10f), 1.0e20f));
    }

    test_case("modf");
    {
        ASSERT(nnm::approx_equal(nnm::modf(0.0f, 1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::modf(0.0f, -1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::modf(5.0f, 3.0f), 2.0f));
        ASSERT(nnm::approx_equal(nnm::modf(-5.0f, 3.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::modf(5.0f, -3.0f), -1.0f));
        ASSERT(nnm::approx_equal(nnm::modf(-5.0f, -3.0f), -2.0f));
    }

    test_case("mod");
    {
        constexpr auto result = nnm::mod(0, 1);
        ASSERT(nnm::approx_equal(result, 0));
        ASSERT(nnm::approx_equal(nnm::mod(0, -1), 0));
        ASSERT(nnm::approx_equal(nnm::mod(5, 3), 2));
        ASSERT(nnm::approx_equal(nnm::mod(-5, 3), 1));
        ASSERT(nnm::approx_equal(nnm::mod(5, -3), -1));
        ASSERT(nnm::approx_equal(nnm::mod(-5, -3), -2));
    }

    test_case("remf");
    {
        ASSERT(nnm::approx_equal(nnm::remf(0.0f, 1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::remf(0.0f, -1.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::remf(5.0f, 3.0f), 2.0f));
        ASSERT(nnm::approx_equal(nnm::remf(-5.0f, 3.0f), -2.0f));
        ASSERT(nnm::approx_equal(nnm::remf(5.0f, -3.0f), 2.0f));
        ASSERT(nnm::approx_equal(nnm::remf(-5.0f, -3.0f), -2.0f));
    }

    test_case("rem");
    {
        constexpr auto result = nnm::rem(0, 1);
        ASSERT(nnm::approx_equal(result, 0));
        ASSERT(nnm::approx_equal(nnm::rem(0, -1), 0));
        ASSERT(nnm::approx_equal(nnm::rem(5, 3), 2));
        ASSERT(nnm::approx_equal(nnm::rem(-5, 3), -2));
        ASSERT(nnm::approx_equal(nnm::rem(5, -3), 2));
        ASSERT(nnm::approx_equal(nnm::rem(-5, -3), -2));
    }

    test_case("normalize_angle");
    {
        ASSERT(nnm::approx_zero(nnm::normalize_angle(0.0f)));

        ASSERT(nnm::approx_equal(nnm::normalize_angle(nnm::pi<float>() / 4.0f), nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_equal(nnm::normalize_angle(2.0f * nnm::pi<float>() / 3.0f), 2.0f * nnm::pi<float>() / 3.0f));
        ASSERT(
            nnm::approx_equal(nnm::normalize_angle(5.0f * nnm::pi<float>() / 4.0f), -3.0f * nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_equal(nnm::normalize_angle(7.0f * nnm::pi<float>() / 4.0f), -nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_zero(nnm::normalize_angle(2.0f * nnm::pi<float>())));
        ASSERT(nnm::approx_equal(nnm::normalize_angle(8.0f * nnm::pi<float>() / 3.0f), 2.0f * nnm::pi<float>() / 3.0f));

        ASSERT(nnm::approx_equal(nnm::normalize_angle(-nnm::pi<float>() / 4.0f), -nnm::pi<float>() / 4.0f));
        ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-2.0f * nnm::pi<float>() / 3.0f), -2.0f * nnm::pi<float>() / 3.0f));
        ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-5.0f * nnm::pi<float>() / 4.0f), 3.0f * nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_equal(nnm::normalize_angle(-7.0f * nnm::pi<float>() / 4.0f), nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_zero(nnm::normalize_angle(-2.0f * nnm::pi<float>())));
        ASSERT(
            nnm::approx_equal(nnm::normalize_angle(-8.0f * nnm::pi<float>() / 3.0f), -2.0f * nnm::pi<float>() / 3.0f));
    }

    test_case("angle_in_range");
    {
        ASSERT(nnm::angle_in_range(0.0f, 0.0f, 0.0f));

        ASSERT_FALSE(nnm::angle_in_range(nnm::pi<float>() / 4.0f, 0.0f, nnm::pi<float>() / 5.0f));
        ASSERT_FALSE(nnm::angle_in_range(nnm::pi<float>() / 4.0f, nnm::pi<float>() / 5.0f, 0.0f));
        ASSERT(nnm::angle_in_range(nnm::pi<float>() / 4.0f, 0.0f, nnm::pi<float>() / 3.0f));
        ASSERT(nnm::angle_in_range(nnm::pi<float>() / 4.0f, nnm::pi<float>() / 3.0f, 0.0f));
        ASSERT(nnm::angle_in_range(4.0f * nnm::pi<float>() / 3.0f, nnm::pi<float>(), 2.0f * nnm::pi<float>()));
        ASSERT(nnm::angle_in_range(4.0f * nnm::pi<float>() / 3.0f, 2.0f * nnm::pi<float>(), nnm::pi<float>()));
        ASSERT(nnm::angle_in_range(0.0f, nnm::pi<float>(), 7.0f * nnm::pi<float>() / 3.0f));

        ASSERT_FALSE(nnm::angle_in_range(-nnm::pi<float>() / 4.0f, 0.0f, -nnm::pi<float>() / 5.0f));
        ASSERT_FALSE(nnm::angle_in_range(-nnm::pi<float>() / 4.0f, -nnm::pi<float>() / 5.0f, 0.0f));
        ASSERT(nnm::angle_in_range(-nnm::pi<float>() / 4.0f, 0.0f, -nnm::pi<float>() / 3.0f));
        ASSERT(nnm::angle_in_range(-nnm::pi<float>() / 4.0f, -nnm::pi<float>() / 3.0f, 0.0f));
        ASSERT(nnm::angle_in_range(-4.0f * nnm::pi<float>() / 3.0f, -nnm::pi<float>(), -2.0f * nnm::pi<float>()));
        ASSERT(nnm::angle_in_range(-4.0f * nnm::pi<float>() / 3.0f, -2.0f * nnm::pi<float>(), -nnm::pi<float>()));
        ASSERT(nnm::angle_in_range(0.0f, -nnm::pi<float>(), -7.0f * nnm::pi<float>() / 3.0f));

        ASSERT(nnm::angle_in_range(0.0f, -nnm::pi<float>() / 4.0f, nnm::pi<float>() / 4.0f));
        ASSERT(nnm::angle_in_range(0.0f, nnm::pi<float>() / 4.0f, -nnm::pi<float>() / 4.0f));
        ASSERT(
            nnm::angle_in_range(
                2.0f * nnm::pi<float>() / 3.0f, -3.0f * nnm::pi<float>() / 2.0f, nnm::pi<float>() / 7.0f));
        ASSERT(
            nnm::angle_in_range(
                2.0f * nnm::pi<float>() / 3.0f, nnm::pi<float>() / 7.0f, -3.0f * nnm::pi<float>() / 2.0f));
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
        constexpr auto result = nnm::lerp(0.0f, 10.0f, 0.5f);
        ASSERT(result == 5.0f);
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
        constexpr auto result = nnm::lerp_clamped(5.0f, 10.0f, 20.0f);
        ASSERT(result == 10.0f);
        ASSERT(nnm::approx_equal(nnm::lerp_clamped(5.0f, 10.0f, 0.5f), 7.5f));
        ASSERT(nnm::lerp_clamped(5.0f, 10.0f, -20.0f) == 5.0f);
    }

    test_case("sin");
    {
        ASSERT(nnm::approx_equal(nnm::sin(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 6.0f), 0.5f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 3.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>() / 2.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::sin(nnm::pi<float>()), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(3.0f * nnm::pi<float>() / 2.0f), -1.0f));
        ASSERT(nnm::approx_equal(nnm::sin(2.0f * nnm::pi<float>()), 0.0f));

        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 6.0f), -0.5f));
        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 4.0f), -1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::sin(-nnm::pi<float>() / 3.0f), -nnm::sqrt(3.0f) / 2.0f));

        ASSERT(nnm::approx_equal(nnm::sin(4.0f * nnm::pi<float>()), 0.0f));
        ASSERT(nnm::approx_equal(nnm::sin(6.0f * nnm::pi<float>()), 0.0f));
    }

    test_case("cos");
    {
        ASSERT(nnm::approx_equal(nnm::cos(0.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 3.0f), 0.5f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>() / 2.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::cos(nnm::pi<float>()), -1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(3.0f * nnm::pi<float>() / 2.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::cos(2.0f * nnm::pi<float>()), 1.0f));

        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 6.0f), nnm::sqrt(3.0f) / 2.0f));
        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 4.0f), 1.0f / nnm::sqrt(2.0f)));
        ASSERT(nnm::approx_equal(nnm::cos(-nnm::pi<float>() / 3.0f), 0.5f));

        ASSERT(nnm::approx_equal(nnm::cos(4.0f * nnm::pi<float>()), 1.0f));
        ASSERT(nnm::approx_equal(nnm::cos(6.0f * nnm::pi<float>()), 1.0f));
    }

    test_case("tan");
    {
        ASSERT(nnm::approx_equal(nnm::tan(0.0f), 0.0f));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 4.0f), 1.0f));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 6.0f), 1.0f / nnm::sqrt(3.0f)));

        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 3.0f), nnm::sqrt(3.0f)));
        ASSERT(nnm::approx_equal(nnm::tan(nnm::pi<float>() / 2.0f - 0.01f), 99.9967f));

        ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi<float>() / 3.0f), -nnm::sqrt(3.0f)));
        ASSERT(nnm::approx_equal(nnm::tan(-nnm::pi<float>() / 2.0f + 0.01f), -99.9967f));

        ASSERT(nnm::approx_equal(nnm::tan(3.0f * nnm::pi<float>()), 0.0f));
        ASSERT(nnm::approx_equal(nnm::tan(6.0f * nnm::pi<float>()), 0.0f));
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
        constexpr auto result = nnm::radians(0.0f);
        ASSERT(nnm::approx_equal(result, 0.0f));
        ASSERT(nnm::approx_equal(nnm::radians(45.0f), nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_equal(nnm::radians(90.0f), nnm::pi<float>() / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(180.0f), nnm::pi<float>()));
        ASSERT(nnm::approx_equal(nnm::radians(270.0f), 3.0f * nnm::pi<float>() / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(360.0f), 2.0f * nnm::pi<float>()));

        ASSERT(nnm::approx_equal(nnm::radians(-45.0f), -nnm::pi<float>() / 4.0f));
        ASSERT(nnm::approx_equal(nnm::radians(-90.0f), -nnm::pi<float>() / 2.0f));
        ASSERT(nnm::approx_equal(nnm::radians(-180.0f), -nnm::pi<float>()));

        ASSERT(nnm::approx_equal(nnm::radians(720.0f), 4.0f * nnm::pi<float>()));
        ASSERT(nnm::approx_equal(nnm::radians(1080.0f), 6.0f * nnm::pi<float>()));

        ASSERT(nnm::approx_equal(nnm::radians(180.0f), 3.14159f));
    }

    test_case("degrees");
    {
        constexpr auto result = nnm::degrees(0.0f);
        ASSERT(nnm::approx_equal(result, 0.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>() / 4.0f), 45.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>() / 2.0f), 90.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(nnm::pi<float>()), 180.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(3.0f * nnm::pi<float>() / 2.0f), 270.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(2.0f * nnm::pi<float>()), 360.0f));

        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>() / 4.0f), -45.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>() / 2.0f), -90.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(-nnm::pi<float>()), -180.0f));

        ASSERT(nnm::approx_equal(nnm::degrees(4.0f * nnm::pi<float>()), 720.0f));
        ASSERT(nnm::approx_equal(nnm::degrees(6.0f * nnm::pi<float>()), 1080.0f));

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

    test_case("min(Num, Num)");
    {
        constexpr auto result1 = nnm::min(1, 2);
        ASSERT(result1 == 1);
        ASSERT(nnm::min(5, 3) == 3);
        ASSERT(nnm::min(-1, -5) == -5);
        ASSERT(nnm::min(3, 3) == 3);

        constexpr auto result2 = nnm::min(1.0f, 2.0f);
        ASSERT(result2 == 1.0f);
        ASSERT(nnm::min(5.5f, 3.5f) == 3.5f);
        ASSERT(nnm::min(-1.0f, -5.0f) == -5.0f);
        ASSERT(nnm::min(3.0f, 3.0f) == 3.0f);

        ASSERT(nnm::min('a', 'b') == 'a');
        ASSERT(nnm::min(3.14f, 2.71f) == 2.71f);
    }

    test_case("min(Num, Rest...)");
    {
        constexpr auto result1 = nnm::min(1, 2, 3);
        ASSERT(result1 == 1);
        ASSERT(nnm::min(5, 3, 1) == 1);
        ASSERT(nnm::min(-1, -5, 2) == -5);
        ASSERT(nnm::min(3, 3, 3) == 3);

        constexpr auto result2 = nnm::min(1.0f, 2.0f, 3.0f);
        ASSERT(result2 == 1.0f);
        ASSERT(nnm::min(5.5f, 3.5f, 100.0f) == 3.5f);
        ASSERT(nnm::min(-1.0f, -5.0f, -100.0f) == -100.0f);
        ASSERT(nnm::min(3.0f, 3.0f, 3.0f) == 3.0f);

        ASSERT(nnm::min('a', 'b', 'c') == 'a');
        ASSERT(nnm::min(3.14f, 2.71f, 1.123f) == 1.123f);
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
            constexpr nnm::Vector2f v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
        }

        test_section("Vector2(const Vector2i&)");
        {
            constexpr nnm::Vector2f v2(nnm::Vector2i(1, 2));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
        }

        test_section("Vector2(const Vector2<Other>&)");
        {
            constexpr nnm::Vector2d v1(1.0, -2.0);
            constexpr nnm::Vector2f v2(v1);
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == -2.0f);
        }

        test_section("Vector2(float, float)");
        {
            constexpr nnm::Vector2 v3(1.0f, 2.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
        }

        test_section("all");
        {
            constexpr auto all_threes = nnm::Vector2f::all(3.0f);
            ASSERT(all_threes.x == 3.0f);
            ASSERT(all_threes.y == 3.0f);
        }

        test_section("zero");
        {
            constexpr auto zero = nnm::Vector2f::zero();
            ASSERT(zero.x == 0.0f);
            ASSERT(zero.y == 0.0f);
        }

        test_section("one");
        {
            constexpr auto one = nnm::Vector2f::one();
            ASSERT(one.x == 1.0f);
            ASSERT(one.y == 1.0f);
        }

        test_section("axis_x");
        {
            constexpr auto x = nnm::Vector2f::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
        }

        test_section("axis_y");
        {
            constexpr auto y = nnm::Vector2f::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
        }

        test_section("abs");
        {
            constexpr nnm::Vector2 v(1.0f, -2.0f);
            constexpr auto result = v.abs();
            ASSERT(result == nnm::Vector2(1.0f, 2.0f));
        }

        test_section("ceil");
        {
            constexpr nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.ceil() == nnm::Vector2(2.0f, -1.0f));
        }

        test_section("floor");
        {
            constexpr nnm::Vector2 v(1.1f, -1.9f);
            ASSERT(v.floor() == nnm::Vector2(1.0f, -2.0f));
        }

        test_section("round");
        {
            constexpr nnm::Vector2 v1(1.1f, -1.9f);
            ASSERT(v1.round() == nnm::Vector2(1.0f, -2.0f));
            constexpr nnm::Vector2 v2(1.6f, -1.3f);
            ASSERT(v2.round() == nnm::Vector2(2.0f, -1.0f));
        }

        test_section("aspect_ratio");
        {
            constexpr nnm::Vector2 v(1.0f, -2.0f);
            constexpr auto result = v.aspect_ratio();
            ASSERT(result == 1.0f / -2.0f);
        }

        test_section("clamp");
        {
            constexpr nnm::Vector2 v(1.1f, -3.0f);
            constexpr auto result = v.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f });
            ASSERT(result == nnm::Vector2(1.1f, -2.0f));
        }

        test_section("direction");
        {
            constexpr nnm::Vector2 from1(1.0f, 1.0f);
            constexpr nnm::Vector2 to1(2.0f, 2.0f);
            auto direction1 = from1.direction(to1);
            ASSERT(nnm::approx_equal(direction1.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction1.y, 0.7071067812f));

            constexpr nnm::Vector2 from2(-1.0f, -1.0f);
            constexpr nnm::Vector2 to2(1.0f, 1.0f);
            auto direction2 = from2.direction(to2);
            ASSERT(nnm::approx_equal(direction2.x, 0.7071067812f));
            ASSERT(nnm::approx_equal(direction2.y, 0.7071067812f));

            constexpr nnm::Vector2 from3(0.0f, 0.0f);
            constexpr nnm::Vector2 to3(1.0f, 0.0f);
            auto direction3 = from3.direction(to3);
            ASSERT(nnm::approx_equal(direction3.x, 1.0f));
            ASSERT(nnm::approx_equal(direction3.y, 0.0f));

            constexpr nnm::Vector2 from4(0.0f, 0.0f);
            constexpr nnm::Vector2 to4(0.0f, 1.0f);
            auto direction4 = from4.direction(to4);
            ASSERT(nnm::approx_equal(direction4.x, 0.0f));
            ASSERT(nnm::approx_equal(direction4.y, 1.0f));

            constexpr nnm::Vector2 from5(1.0f, 2.0f);
            constexpr nnm::Vector2 to5(1.0f, 2.0f);
            auto direction5 = from5.direction(to5);
            ASSERT(nnm::approx_equal(direction5.x, 0.0f));
            ASSERT(nnm::approx_equal(direction5.y, 0.0f));
        }

        test_section("direction_unnormalized");
        {
            constexpr nnm::Vector2 from1(1.0f, 1.0f);
            constexpr nnm::Vector2 to1(2.0f, 2.0f);
            constexpr auto direction1 = from1.direction_unnormalized(to1);
            ASSERT(nnm::approx_equal(direction1.x, 1.0f));
            ASSERT(nnm::approx_equal(direction1.y, 1.0f));

            constexpr nnm::Vector2 from2(-1.0f, -1.0f);
            constexpr nnm::Vector2 to2(1.0f, 1.0f);
            auto direction2 = from2.direction_unnormalized(to2);
            ASSERT(nnm::approx_equal(direction2.x, 2.0f));
            ASSERT(nnm::approx_equal(direction2.y, 2.0f));

            constexpr nnm::Vector2 from3(0.0f, 0.0f);
            constexpr nnm::Vector2 to3(1.0f, 0.0f);
            auto direction3 = from3.direction_unnormalized(to3);
            ASSERT(nnm::approx_equal(direction3.x, 1.0f));
            ASSERT(nnm::approx_equal(direction3.y, 0.0f));

            constexpr nnm::Vector2 from4(0.0f, 0.0f);
            constexpr nnm::Vector2 to4(0.0f, 1.0f);
            auto direction4 = from4.direction_unnormalized(to4);
            ASSERT(nnm::approx_equal(direction4.x, 0.0f));
            ASSERT(nnm::approx_equal(direction4.y, 1.0f));

            constexpr nnm::Vector2 from5(1.0f, 2.0f);
            constexpr nnm::Vector2 to5(1.0f, 2.0f);
            auto direction5 = from5.direction_unnormalized(to5);
            ASSERT(nnm::approx_equal(direction5.x, 0.0f));
            ASSERT(nnm::approx_equal(direction5.y, 0.0f));
        }

        test_section("distance_sqrd");
        {
            constexpr nnm::Vector2 from1(1.0f, 1.0f);
            constexpr nnm::Vector2 to1(2.0f, 2.0f);
            constexpr auto result = from1.distance_sqrd(to1);
            ASSERT(nnm::approx_equal(result, 2.0f));

            constexpr nnm::Vector2 from2(-1.0f, -1.0f);
            constexpr nnm::Vector2 to2(1.0f, 1.0f);
            ASSERT(nnm::approx_equal(from2.distance_sqrd(to2), 8.0f));

            constexpr nnm::Vector2 from3(0.0f, 0.0f);
            constexpr nnm::Vector2 to3(3.0f, 0.0f);
            ASSERT(nnm::approx_equal(from3.distance_sqrd(to3), 9.0f));

            constexpr nnm::Vector2 from4(0.0f, 0.0f);
            constexpr nnm::Vector2 to4(0.0f, 4.0f);
            ASSERT(nnm::approx_equal(from4.distance_sqrd(to4), 16.0f));

            constexpr nnm::Vector2 from5(1.0f, 2.0f);
            constexpr nnm::Vector2 to5(1.0f, 2.0f);
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
            constexpr nnm::Vector2 from1(1.0f, 1.0f);
            constexpr nnm::Vector2 to1(2.0f, 2.0f);
            constexpr auto result = from1.manhattan_distance(to1);
            ASSERT(nnm::approx_equal(result, 2.0f));

            auto from = nnm::Vector2(-1.0f, -1.0f);
            auto to = nnm::Vector2(1.0f, 1.0f);
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
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.length_sqrd();
            ASSERT(nnm::approx_equal(result, 25.0f));

            auto v = nnm::Vector2(-2.0f, 5.0f);
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
            constexpr nnm::Vector2 v(1.1f, -3.0f);
            const auto norm = v.normalize();
            ASSERT(nnm::approx_equal(norm.x, 0.344255f));
            ASSERT(nnm::approx_equal(norm.y, -0.938876f));
        }

        test_section("lerp");
        {
            constexpr nnm::Vector2 from(1.0f, 1.0f);
            constexpr nnm::Vector2 to(3.0f, 5.0f);
            constexpr auto result = from.lerp(to, 0.0f);
            ASSERT(result == nnm::Vector2(1.0f, 1.0f));
            ASSERT(from.lerp(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
            ASSERT(from.lerp(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
            ASSERT(from.lerp(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
        }

        test_section("lerp_clamped");
        {
            constexpr nnm::Vector2 from(1.0f, 1.0f);
            constexpr nnm::Vector2 to(3.0f, 5.0f);
            constexpr auto result = from.lerp_clamped(to, 0.0f);
            ASSERT(result == nnm::Vector2(1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
            ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
            ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
            ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector2(3.0f, 5.0f));
            ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector2(1.0f, 1.0f));
        }

        test_section("dot");
        {
            constexpr nnm::Vector2 v1(2.0f, 3.0f);
            constexpr nnm::Vector2 v2(4.0f, 5.0f);
            constexpr auto result = v1.dot(v2);
            ASSERT(result == 23.0f);
        }

        test_section("cross");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr nnm::Vector2 v2(-4.0f, 5.0f);
            constexpr auto result = v1.cross(v2);
            ASSERT(nnm::approx_equal(result, -2.0f));
        }

        test_section("outer");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr nnm::Vector2 v2(-4.0f, 5.0f);
            nnm::Matrix2f expected { { -8.0f, 10.0f }, { 12.0f, -15.0f } };
            constexpr auto result = v1.outer(v2);
            ASSERT(result.approx_equal(expected));
        }

        test_section("reflect");
        {
            constexpr nnm::Vector2 incident(3.0f, 4.0f);
            constexpr nnm::Vector2 normal(1.0f, 0.0f);
            constexpr auto result = incident.reflect(normal);
            ASSERT(result == nnm::Vector2(-3.0f, 4.0f));
        }

        test_section("project");
        {
            constexpr nnm::Vector2 v1 { 1.0f, 0.0f };
            constexpr nnm::Vector2 v2 { 0.0f, 1.0f };
            constexpr auto result = v1.project(v2);
            ASSERT(result.approx_equal({ 0.0f, 0.0f }));

            constexpr nnm::Vector2 v3 { 1.0f, 1.0f };
            constexpr nnm::Vector2 v4 { 2.0f, 2.0f };
            ASSERT(v3.project(v4).approx_equal({ 1.0f, 1.0f }));

            constexpr nnm::Vector2 v5 { 1.0f, -2.0f };
            constexpr nnm::Vector2 v6 { -3.0f, 4.0f };
            ASSERT(v5.project(v6).approx_equal({ 1.32f, -1.76f }));
        }

        test_section("inverse");
        {
            constexpr nnm::Vector2 v(2.0f, 3.0f);
            constexpr auto result = v.inverse();
            ASSERT(result.approx_equal(nnm::Vector2(1.0f / 2.0f, 1.0f / 3.0f)));
        }

        test_section("angle_between");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            ASSERT(nnm::approx_equal(v1.angle_between(v2), -3.05485f))
            ASSERT(nnm::approx_equal(v2.angle_between(v1), 3.05485f));
        }

        test_section("angle_to");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            nnm::Vector2 v2(-4.0f, 5.0f);
            ASSERT(nnm::approx_equal(v1.angle_to(v2), 2.21429744f));
        }

        test_section("parallel");
        {
            constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
            ASSERT(v1.parallel(v1));
            constexpr nnm::Vector2f v2 { -2.0f, 4.0f };
            constexpr auto result = v1.parallel(v2);
            ASSERT(result);
            constexpr nnm::Vector2f v3 { 1.0f, -5.0f };
            ASSERT_FALSE(v1.parallel(v3));
        }

        test_section("perpendicular");
        {
            constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
            constexpr nnm::Vector2f v2 { 4.0f, 2.0f };
            constexpr auto result = v1.perpendicular(v2);
            ASSERT(result);
            constexpr nnm::Vector2f v3 { -4.0f, -2.0f };
            ASSERT(v1.perpendicular(v3));
        }

        test_section("arbitrary_perpendicular");
        {
            constexpr nnm::Vector2f v1 { 1.0f, -2.0f };
            constexpr auto result = v1.arbitrary_perpendicular();
            ASSERT(v1.perpendicular(result));
            constexpr nnm::Vector2f v2 { 1.0f, 0.0f };
            ASSERT(v2.perpendicular(v2.arbitrary_perpendicular()));
        }

        test_section("translate");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr nnm::Vector2 v2(-4.0f, 5.0f);
            constexpr auto result = v1.translate(v2);
            ASSERT(result.approx_equal({ -2.0f, 2.0f }));
        }

        test_section("rotate");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.rotate(nnm::pi<float>() / 4.0f).approx_equal({ 3.53553f, -0.707107f }));
        }

        constexpr nnm::Vector2f origin { -3.0f, 1.0f };

        test_section("rotate_at");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.rotate_at(origin, nnm::pi<float>() / 4.0f).approx_equal({ 3.36396f, 1.707107f }));
        }

        test_section("scale");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr auto result = v1.scale({ 1.5f, -2.0f });
            ASSERT(result.approx_equal({ 3.0f, 6.0f }));
        }

        test_section("scale_at");
        {
            constexpr nnm::Vector2 v1 { 2.0f, -3.0f };
            constexpr auto result = v1.scale_at(origin, { 1.5f, -2.0f });
            ASSERT(result.approx_equal({ 4.5f, 9.0f }));
        }

        test_section("shear_x");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr auto result = v1.shear_x(0.5f);
            ASSERT(result.approx_equal({ 0.5f, -3.0f }));
        }

        test_section("shear_x_at");
        {
            constexpr nnm::Vector2 v1 { 2.0f, -3.0f };
            constexpr auto result = v1.shear_x_at(origin, 0.5f);
            ASSERT(result.approx_equal({ 0.0f, -3.0f }));
        }

        test_section("shear_y");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr auto result = v1.shear_y(-0.5f);
            ASSERT(result.approx_equal({ 2.0f, -4.0f }));
        }

        test_section("shear_y_at");
        {
            constexpr nnm::Vector2 v1 { 2.0f, -3.0f };
            constexpr auto result = v1.shear_y_at(origin, -0.5f);
            ASSERT(result.approx_equal({ 2.0f, -5.5f }));
        }

        test_section("transform(const Basis2&)");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr nnm::Basis2f basis({ { 1.0f, -2.0f }, { -4.0f, 1.2f } });
            constexpr auto result = v1.transform(basis);
            ASSERT(result.approx_equal({ 14.0f, -7.6f }));
        }

        test_section("transform_at(const Vector2&, const Basis2&)");
        {
            constexpr nnm::Vector2 v1 { 2.0f, -3.0f };
            constexpr nnm::Basis2f basis { { { 1.0f, -2.0f }, { -4.0f, 1.2f } } };
            constexpr auto result = v1.transform_at(origin, basis);
            ASSERT(result.approx_equal({ 18.0f, -13.8f }));
        }

        test_section("transform(const Transform2&, Real)");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr nnm::Transform2f transform(
                { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
            constexpr auto result = v1.transform(transform);
            ASSERT(result.approx_equal({ 17.0f, -2.8f }));
            ASSERT(v1.transform(transform, 2.3f).approx_equal({ 20.9f, -5.4f }));
        }

        test_section("transform_at(const Vector3&, const Transform2&, Real)");
        {
            constexpr nnm::Vector2 v1 { 2.0f, -3.0f };
            constexpr nnm::Transform2f transform {
                { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } }
            };
            constexpr auto result = v1.transform_at(origin, transform);
            ASSERT(result.approx_equal({ 21.0f, 2.6f }));
            ASSERT(v1.transform_at(origin, transform, 2.3f).approx_equal({ 24.9f, 0.0f }));
        }

        test_section("max");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.max();
            ASSERT(result == 4.0f);
            nnm::Vector2 v2(5.0f, 2.0f);
            ASSERT(v2.max() == 5.0f);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.max() == 0.0f);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.max() == 1.0f);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.max() == 1.0f);
        }

        test_section("abs_max");
        {
            constexpr nnm::Vector2f v1 { 3.0f, 4.0f };
            constexpr auto result = v1.abs_max();
            ASSERT(result == 4.0f);
            nnm::Vector2f v2 { 5.0f, 2.0f };
            ASSERT(v2.abs_max() == 5.0f);
            nnm::Vector2f v3 { 0.0f, 0.0f };
            ASSERT(v3.abs_max() == 0.0f);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.abs_max() == -2.0f);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.abs_max() == -2.0f);
        }

        test_section("min");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.min();
            ASSERT(result == 3.0f);
            nnm::Vector2 v2(5.0f, 2.0f);
            ASSERT(v2.min() == 2.0f);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.min() == 0.0f);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.min() == -2.0f);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.min() == -2.0f);
        }

        test_section("abs_min");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.abs_min();
            ASSERT(result == 3.0f);
            nnm::Vector2 v2(5.0f, 2.0f);
            ASSERT(v2.abs_min() == 2.0f);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.abs_min() == 0.0f);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.abs_min() == 1.0f);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.abs_min() == 1.0f);
        }

        test_section("max_index");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.max_index();
            ASSERT(result == 1);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.max_index() == 1);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.max_index() == 1);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.max_index() == 0);
        }

        test_section("abs_max_index");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.abs_max_index();
            ASSERT(result == 1);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.abs_max_index() == 1);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.abs_max_index() == 0);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.abs_max_index() == 0);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.abs_max_index() == 1);
        }

        test_section("min_index");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.min_index();
            ASSERT(result == 0);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.min_index() == 0);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.min_index() == 0);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.min_index() == 0);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.min_index() == 1);
        }

        test_section("abs_min_index");
        {
            constexpr nnm::Vector2 v1(3.0f, 4.0f);
            constexpr auto result = v1.abs_min_index();
            ASSERT(result == 0);
            nnm::Vector2 v2(2.0f, 5.0f);
            ASSERT(v2.abs_min_index() == 0);
            nnm::Vector2 v3(0.0f, 0.0f);
            ASSERT(v3.abs_min_index() == 0);
            nnm::Vector2f v4 { -2.0f, 1.0f };
            ASSERT(v4.abs_min_index() == 1);
            nnm::Vector2f v5 { 1.0f, -2.0f };
            ASSERT(v5.abs_min_index() == 0);
        }

        test_section("approx_equal");
        {
            constexpr nnm::Vector2 v1(1.0f, 1.0f);
            constexpr nnm::Vector2 v2(1.0f + nnm::epsilon<float>() / 2.0f, 1.0f);
            constexpr auto result = v1.approx_equal(v2);
            ASSERT(result);
            nnm::Vector2 v3(1.0f, 1.0f);
            nnm::Vector2 v4(1.0f + 2.0f * nnm::epsilon<float>(), 1.0f);
            ASSERT_FALSE(v3.approx_equal(v4));
        }

        test_section("approx_zero");
        {
            constexpr nnm::Vector2 v1(0.0f, 0.0f);
            constexpr auto result = v1.approx_zero();
            ASSERT(result);
            nnm::Vector2 v2(nnm::epsilon<float>(), 0.0f);
            ASSERT(v2.approx_zero());
            nnm::Vector2 v3(0.0f, nnm::epsilon<float>());
            ASSERT(v3.approx_zero());
            nnm::Vector2 v4(0.1f, 0.1f);
            ASSERT_FALSE(v4.approx_zero());
        }

        test_section("begin");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.begin() == &v1.x);
        }

        test_section("end");
        {
            nnm::Vector2 v1(2.0f, -3.0f);
            ASSERT(v1.end() == &v1.y + 1);
        }

        test_section("at");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr auto result = v1.at(0);
            ASSERT(result == 2.0f);
            ASSERT(v1.at(1) == -3.0f);
        }

        test_section("operator[]");
        {
            constexpr nnm::Vector2 v1(2.0f, -3.0f);
            constexpr auto result = v1[0];
            ASSERT(result == 2.0f);
            ASSERT(v1[1] == -3.0f);
        }

        constexpr nnm::Vector2 v1(1.0f, 2.0f);
        constexpr nnm::Vector2 v2(3.0f, 4.0f);
        constexpr nnm::Vector2 v3(1.0f, 2.0f);

        test_section("operator==");
        {
            constexpr auto result = v1 == v3;
            ASSERT(result);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            constexpr auto result = v1 != v3;
            ASSERT_FALSE(result);
            ASSERT(v1 != v2);
        }

        constexpr nnm::Vector2 v4(1.0f, 2.0f);
        constexpr nnm::Vector2 v5(3.0f, 4.0f);

        test_section("operator+(const Vector2&)");
        {
            constexpr auto result = v4 + v5;
            ASSERT(result == nnm::Vector2(4.0f, 6.0f));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v4_copy(1.0f, 2.0f);
                v4_copy += v5;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2(4.0f, 6.0f));
        }

        test_section("operator-(const Vector2&)");
        {
            constexpr auto result = v5 - v4;
            ASSERT(result == nnm::Vector2(2.0f, 2.0f));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v5_copy = v5;
                v5_copy -= v4;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2(2.0f, 2.0f))
        }

        test_section("operator*(const Vector2&)");
        {
            constexpr auto result = v4 * v5;
            ASSERT(result == nnm::Vector2(3.0f, 8.0f));
        }

        test_section("operator*=(const Vector2&)");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v4_copy = v4;
                v4_copy *= v5;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2(3.0f, 8.0f));
        }

        test_section("operator*(const Matrix2&)");
        {
            constexpr nnm::Matrix2f matrix { { 2.0f, -3.0f }, { 1.0f, -0.5f } };
            constexpr auto result = nnm::Vector2(2.0f, -3.0f) * matrix;
            ASSERT(result.approx_equal({ 13.0f, 3.5f }))
        }

        test_section("operator*(float)");
        {
            constexpr auto result = v4 * 2.0f;
            ASSERT(result == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator*(float, const Vector2&)");
        {
            constexpr auto result = 2.0f * v4;
            ASSERT(result == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v4_copy = v4;
                v4_copy *= 2.0f;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2(2.0f, 4.0f));
        }

        test_section("operator/(const Vector2&)");
        {
            constexpr auto result = v5 / v4;
            ASSERT(result == nnm::Vector2(3.0f, 2.0f));
        }

        test_section("operator/=(const Vector2&)");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v5_copy = v5;
                v5_copy /= v4;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2(3.0f, 2.0f));
        }

        test_section("operator/(float)");
        {
            constexpr auto result = v5 / 2.0f;
            ASSERT(result == nnm::Vector2(1.5f, 2.0f));
        }

        test_section("operator/(float, const Vector2&)");
        {
            constexpr auto result = 2.0f / v5;
            ASSERT(result.approx_equal(nnm::Vector2(0.666666f, 0.5f)));
        }

        test_section("operator/=(float)");
        {
            constexpr auto result = [=] {
                nnm::Vector2 v5_copy = v5;
                v5_copy /= 2.0f;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2(1.5f, 2.0f));
        }

        test_section("operator+");
        {
            constexpr auto result = +v4;
            ASSERT(result == v4);
        }

        test_section("operator-");
        {
            constexpr auto result = -v4;
            ASSERT(result == nnm::Vector2(-1.0f, -2.0f));
        }

        test_section("operator<");
        {
            constexpr nnm::Vector2 v6(1.0f, 2.0f);
            constexpr nnm::Vector2 v7(3.0f, 4.0f);
            constexpr auto result = v6 < v7;
            ASSERT(result);
            ASSERT_FALSE(v7 < v6);
        }

        test_section("operator bool");
        {
            constexpr nnm::Vector2 v8(1.0f, 2.0f);
            constexpr auto result = static_cast<bool>(v8);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
        }
    }

    test_case("Vector2i");
    {
        test_section("Vector2i()");
        {
            constexpr nnm::Vector2ii v1;
            ASSERT(v1.x == 0);
            ASSERT(v1.y == 0);
        }

        test_section("Vector2i(const Vector2&)");
        {
            constexpr nnm::Vector2ii v1(nnm::Vector2(1.1f, -10.7f));
            ASSERT(v1.x == 1);
            ASSERT(v1.y == -10);
        }

        test_section("Vector2i(int, int)");
        {
            constexpr nnm::Vector2i v2(1, 2);
            ASSERT(v2.x == 1);
            ASSERT(v2.y == 2);
        }

        test_section("all");
        {
            constexpr auto all_threes = nnm::Vector2ii::all(3);
            ASSERT(all_threes.x == 3);
            ASSERT(all_threes.y == 3);
        }

        test_section("zero");
        {
            constexpr auto zero = nnm::Vector2ii::zero();
            ASSERT(zero.x == 0);
            ASSERT(zero.y == 0);
        }

        test_section("one");
        {
            constexpr auto one = nnm::Vector2ii::one();
            ASSERT(one.x == 1);
            ASSERT(one.y == 1);
        }

        test_section("axis_x");
        {
            constexpr auto x = nnm::Vector2ii::axis_x();
            ASSERT(x.x == 1);
            ASSERT(x.y == 0);
        }

        test_section("axis_y");
        {
            constexpr auto y = nnm::Vector2ii::axis_y();
            ASSERT(y.x == 0);
            ASSERT(y.y == 1);
        }

        test_section("abs");
        {
            constexpr auto result = nnm::Vector2i(1, -2).abs();
            ASSERT(result == nnm::Vector2i(1, 2));
        }

        test_section("clamp");
        {
            constexpr auto result = nnm::Vector2i(1, -3).clamp({ 1, -2 }, { 2, 2 });
            ASSERT(result == nnm::Vector2i(1, -2));
        }

        test_section("manhattan_distance");
        {
            constexpr nnm::Vector2i from1(1, 1);
            constexpr nnm::Vector2i to1(2, 2);
            constexpr auto result = from1.manhattan_distance(to1);
            ASSERT(result == 2);

            auto from = nnm::Vector2i(-1, -1);
            auto to = nnm::Vector2i(1, 1);
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
            constexpr auto result = nnm::Vector2i(3, 4).length_sqrd();
            ASSERT(result == 25);
            ASSERT(nnm::Vector2i(-2, 5).length_sqrd() == 29);
            ASSERT(nnm::Vector2i(0, 0).length_sqrd() == 0);
        }

        test_section("dot");
        {
            constexpr nnm::Vector2i v1(2, 3);
            constexpr nnm::Vector2i v2(4, 5);
            constexpr auto result = v1.dot(v2);
            ASSERT(result == 23);
        }

        test_section("cross");
        {
            constexpr nnm::Vector2i v1(2, -3);
            constexpr nnm::Vector2i v2(-4, 5);
            constexpr auto result = v1.cross(v2);
            ASSERT(result == -2);
        }

        test_section("parallel");
        {
            constexpr nnm::Vector2i v1 { 1, -2 };
            ASSERT(v1.parallel(v1));
            constexpr nnm::Vector2i v2 { -2, 4 };
            constexpr auto result = v1.parallel(v2);
            ASSERT(result);
            constexpr nnm::Vector2i v3 { 1, -5 };
            ASSERT_FALSE(v1.parallel(v3));
        }

        test_section("perpendicular");
        {
            constexpr nnm::Vector2i v1 { 1, -2 };
            constexpr nnm::Vector2i v2 { 4, 2 };
            constexpr auto result = v1.perpendicular(v2);
            ASSERT(result);
            constexpr nnm::Vector2i v3 { -4, -2 };
            ASSERT(v1.perpendicular(v3));
        }

        test_section("arbitrary_perpendicular");
        {
            constexpr nnm::Vector2i v1 { 1, -2 };
            constexpr auto result = v1.arbitrary_perpendicular();
            ASSERT(v1.perpendicular(result));
            constexpr nnm::Vector2i v2 { 1, 0 };
            ASSERT(v2.perpendicular(v2.arbitrary_perpendicular()));
        }

        test_section("max");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.max();
            ASSERT(result == 4);
            nnm::Vector2i v2(5, 2);
            ASSERT(v2.max() == 5);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.max() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.max() == 1);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.max() == 1);
        }

        test_section("abs_max");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.abs_max();
            ASSERT(result == 4);
            nnm::Vector2i v2(5, 2);
            ASSERT(v2.abs_max() == 5);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.abs_max() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.abs_max() == -2);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.abs_max() == -2);
        }

        test_section("min");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.min();
            ASSERT(result == 3);
            nnm::Vector2i v2(5, 2);
            ASSERT(v2.min() == 2);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.min() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.min() == -2);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.min() == -2);
        }

        test_section("abs_min");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.abs_min();
            ASSERT(result == 3);
            nnm::Vector2i v2(5, 2);
            ASSERT(v2.abs_min() == 2);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.abs_min() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.abs_min() == 1);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.abs_min() == 1);
        }

        test_section("max_index");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.max_index();
            ASSERT(result == 1);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.max_index() == 1);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.max_index() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.max_index() == 1);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.max_index() == 0);
        }

        test_section("abs_max_index");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.abs_max_index();
            ASSERT(result == 1);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.abs_max_index() == 1);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.abs_max_index() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.abs_max_index() == 0);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.abs_max_index() == 1);
        }

        test_section("min_index");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.min_index();
            ASSERT(result == 0);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.min_index() == 0);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.min_index() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.min_index() == 0);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.min_index() == 1);
        }

        test_section("abs_min_index");
        {
            constexpr nnm::Vector2i v1(3, 4);
            constexpr auto result = v1.abs_min_index();
            ASSERT(result == 0);
            nnm::Vector2i v2(2, 5);
            ASSERT(v2.abs_min_index() == 0);
            nnm::Vector2i v3(0, 0);
            ASSERT(v3.abs_min_index() == 0);
            nnm::Vector2i v4 { -2, 1 };
            ASSERT(v4.abs_min_index() == 1);
            nnm::Vector2i v5 { 1, -2 };
            ASSERT(v5.abs_min_index() == 0);
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
            constexpr nnm::Vector2i v1(2, -3);
            constexpr auto result = v1.at(0);
            ASSERT(result == 2);
            ASSERT(v1.at(1) == -3);
        }

        test_section("operator[]");
        {
            constexpr nnm::Vector2i v1(2, -3);
            constexpr auto result = v1[0];
            ASSERT(result == 2);
            ASSERT(v1[1] == -3);
        }

        constexpr nnm::Vector2i v1(1, 2);
        constexpr nnm::Vector2i v2(3, 4);
        constexpr nnm::Vector2i v3(1, 2);

        test_section("operator==");
        {
            constexpr auto result = v1 == v3;
            ASSERT(result);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            constexpr auto result = v1 != v3;
            ASSERT_FALSE(result);
            ASSERT(v1 != v2);
        }

        constexpr nnm::Vector2i v4(1, 2);
        constexpr nnm::Vector2i v5(3, 4);

        test_section("operator+(const Vector2i&)");
        {
            constexpr auto result = v4 + v5;
            ASSERT(result == nnm::Vector2i(4, 6));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                auto v4_copy = v4;
                v4_copy += v5;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2i(4, 6));
        }

        test_section("operator-(const Vector2i&)");
        {
            constexpr auto result = v5 - v4;
            ASSERT(result == nnm::Vector2i(2, 2));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                auto v5_copy = v5;
                v5_copy -= v4;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2i(2, 2));
        }

        test_section("operator*(const Vector2i&)");
        {
            constexpr auto result = v4 * v5;
            ASSERT(result == nnm::Vector2i(3, 8));
        }

        test_section("operator*=(const Vector2i&)");
        {
            constexpr auto result = [=] {
                auto v4_copy = v4;
                v4_copy *= v5;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2i(3, 8));
        }

        test_section("operator*(int)");
        {
            constexpr auto result = v4 * 2;
            ASSERT(result == nnm::Vector2i(2, 4));
        }

        test_section("operator*(int, const Vector2i&)");
        {
            constexpr auto result = 2 * v4;
            ASSERT(result == nnm::Vector2i(2, 4));
        }

        test_section("operator*=(int)");
        {
            constexpr auto result = [=] {
                auto v4_copy = v4;
                v4_copy *= 2;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2i(2, 4));
        }

        test_section("operator/(const Vector2i&)");
        {
            constexpr auto result = v5 / v4;
            ASSERT(result == nnm::Vector2i(3, 2));
        }

        test_section("operator/=(const Vector2i&)");
        {
            constexpr auto result = [=] {
                auto v5_copy = v5;
                v5_copy /= v4;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2i(3, 2));
        }

        test_section("operator/(int)");
        {
            constexpr auto result = v5 / 2;
            ASSERT(result == nnm::Vector2i(1, 2));
        }

        test_section("operator/(int, const Vector2i&)");
        {
            constexpr auto result = 2 / v4;
            ASSERT(result == nnm::Vector2i(2, 1));
        }

        test_section("operator/=(int)");
        {
            constexpr auto result = [=] {
                auto v5_copy = v5;
                v5_copy /= 2;
                return v5_copy;
            }();
            ASSERT(result == nnm::Vector2i(1, 2));
        }

        test_section("operator%(const Vector2i&)");
        {
            constexpr auto result = v4 % v5;
            ASSERT(result == nnm::Vector2i(1, 2));
        }

        test_section("operator%=(const Vector2i&)");
        {
            constexpr auto result = [=] {
                auto v4_copy = v4;
                v4_copy %= v5;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2i(1, 2));
        }

        test_section("operator%(int)");
        {
            constexpr auto result = v4 % 2;
            ASSERT(result == nnm::Vector2i(1, 0));
        }

        test_section("operator%(int, const Vector2i&)");
        {
            constexpr auto result = 3 % nnm::Vector2i(2, 5);
            ASSERT(result == nnm::Vector2i(1, 3));
        }

        test_section("operator%=(int)");
        {
            constexpr auto result = [=] {
                auto v4_copy = v4;
                v4_copy %= 2;
                return v4_copy;
            }();
            ASSERT(result == nnm::Vector2i(1, 0));
        }

        test_section("operator+");
        {
            constexpr auto result = +v4;
            ASSERT(result == v4);
        }

        test_section("operator-");
        {
            constexpr auto result = -v4;
            ASSERT(result == nnm::Vector2i(-1, -2));
        }

        test_section("operator<");
        {
            constexpr nnm::Vector2i v7(1, 2);
            constexpr nnm::Vector2i v8(3, 4);
            constexpr auto result = v7 < v8;
            ASSERT(result);
            ASSERT_FALSE(v8 < v7);
        }

        test_section("operator bool");
        {
            constexpr nnm::Vector2i v7(1, 2);
            constexpr auto result = static_cast<bool>(v7);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
        }

        test_section("hash");
        {
            constexpr nnm::Vector2i v7(1, 2);
            const auto _ = nnm::Vector2ii::Hash()(v7);
        }
    }

    test_case("Vector3");
    {
        test_section("Vector3()");
        {
            constexpr nnm::Vector3f v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
        }

        test_section("Vector3(const Vector3i&)");
        {
            constexpr nnm::Vector3f v2(nnm::Vector3i(1, 2, 3));
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == 3.0f);
        }

        test_section("Vector3(const Vector3<Other>&)");
        {
            constexpr nnm::Vector3d v1(1.0, -2.0, 0.5);
            constexpr nnm::Vector3f v2(v1);
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == -2.0f);
            ASSERT(v2.z == 0.5f);
        }

        test_section("Vector3(const Vector2&, float)");
        {
            constexpr nnm::Vector3 v(nnm::Vector2(1.0f, 2.0f), 3.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == 2.0f);
            ASSERT(v.z == 3.0f);
        }

        test_section("Vector3(float, float, float)");
        {
            constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 2.0f);
            ASSERT(v3.z == 3.0f);
        }

        test_section("all");
        {
            constexpr auto v1 = nnm::Vector3f::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);
        }

        test_section("zero");
        {
            constexpr auto v2 = nnm::Vector3f::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);
        }

        test_section("one");
        {
            constexpr auto v3 = nnm::Vector3f::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
        }

        test_section("axis_x");
        {
            constexpr auto x = nnm::Vector3f::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
            ASSERT(x.z == 0.0f);
        }

        test_section("axis_y");
        {
            constexpr auto y = nnm::Vector3f::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
            ASSERT(y.z == 0.0f);
        }

        test_section("axis_z");
        {
            constexpr auto z = nnm::Vector3f::axis_z();
            ASSERT(z.x == 0.0f);
            ASSERT(z.y == 0.0f);
            ASSERT(z.z == 1.0f);
        }

        test_section("abs");
        {
            constexpr auto result = nnm::Vector3(0.0f, 1.0f, -2.0f).abs();
            ASSERT(result == nnm::Vector3(0.0f, 1.0f, 2.0f));
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
            constexpr nnm::Vector3 v(1.1f, -2.8f, 0.0f);
            ASSERT(v.round() == nnm::Vector3(1.0f, -3.0f, 0.0f));
        }

        test_section("clamp");
        {
            constexpr nnm::Vector3 v(0.0f, 10.0f, -2.0f);
            constexpr nnm::Vector3 min(-1.0f, 12.0f, -5.0f);
            constexpr nnm::Vector3 max(1.0f, 12.0f, -3.0f);
            constexpr auto result = v.clamp(min, max);
            ASSERT(result == nnm::Vector3(0.0f, 12.0f, -3.0f));
        }

        test_section("direction");
        {
            nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            auto direction = from.direction(to);
            ASSERT(direction.approx_equal(nnm::Vector3f::all(0.57735f)));

            from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            to = nnm::Vector3(1.0f, 1.0f, 1.0f);
            direction = from.direction(to);
            ASSERT(direction.approx_equal(nnm::Vector3f::all(0.57735f)));

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

        test_section("direction_unnormalized");
        {
            constexpr nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 to(2.0f, 2.0f, 2.0f);
            constexpr auto direction1 = from.direction_unnormalized(to);
            ASSERT(direction1.approx_equal(nnm::Vector3f::all(1.0f)));

            constexpr auto from1 = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            constexpr auto to1 = nnm::Vector3(1.0f, 1.0f, 1.0f);
            auto direction = from1.direction_unnormalized(to1);
            ASSERT(direction.approx_equal(nnm::Vector3f::all(2.0f)));

            constexpr auto from2 = nnm::Vector3(0.0f, 0.0f, 0.0f);
            constexpr auto to2 = nnm::Vector3(1.0f, 0.0f, 0.0f);
            direction = from2.direction_unnormalized(to2);
            ASSERT(nnm::approx_equal(direction.x, 1.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            constexpr auto from3 = nnm::Vector3(0.0f, 0.0f, 0.0f);
            constexpr auto to3 = nnm::Vector3(0.0f, 1.0f, 0.0f);
            direction = from3.direction_unnormalized(to3);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 1.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));

            constexpr auto from4 = nnm::Vector3(0.0f, 0.0f, 0.0f);
            constexpr auto to4 = nnm::Vector3(0.0f, 0.0f, 1.0f);
            direction = from4.direction_unnormalized(to4);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 1.0f));

            constexpr auto from5 = nnm::Vector3(1.0f, 2.0f, 3.0f);
            constexpr auto to5 = nnm::Vector3(1.0f, 2.0f, 3.0f);
            direction = from5.direction_unnormalized(to5);
            ASSERT(nnm::approx_equal(direction.x, 0.0f));
            ASSERT(nnm::approx_equal(direction.y, 0.0f));
            ASSERT(nnm::approx_equal(direction.z, 0.0f));
        }

        test_section("distance_sqrd");
        {
            constexpr nnm::Vector3 from1(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 to1(2.0f, 2.0f, 2.0f);
            constexpr auto result = from1.distance_sqrd(to1);
            ASSERT(nnm::approx_equal(result, 3.0f));

            auto from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            auto to = nnm::Vector3(1.0f, 1.0f, 1.0f);
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
            constexpr nnm::Vector3 from1(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 to1(2.0f, 2.0f, 2.0f);
            constexpr auto result = from1.manhattan_distance(to1);
            ASSERT(nnm::approx_equal(result, 3.0f));

            auto from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
            auto to = nnm::Vector3(1.0f, 1.0f, 1.0f);
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
            constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            constexpr auto result = v.length_sqrd();
            ASSERT(nnm::approx_equal(result, 14.0f));
        }

        test_section("length");
        {
            constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
        }

        test_section("clamp_length");
        {
            constexpr nnm::Vector3 v(1.0f, 2.0f, 3.0f);
            ASSERT(v.clamp_length(2.0f, 5.0f).approx_equal(nnm::Vector3(1.0f, 2.0f, 3.0f)));
            ASSERT(v.clamp_length(2.0f, 3.0f).approx_equal(nnm::Vector3(0.80178f, 1.603566f, 2.405352f)));
            ASSERT(v.clamp_length(10.0f, 100.0f).approx_equal(nnm::Vector3(2.67261f, 5.34522f, 8.01784f)));
        }

        test_section("normalize");
        {
            constexpr nnm::Vector3 v(1.0f, -2.0f, 3.0f);
            ASSERT(v.normalize().approx_equal(nnm::Vector3(0.267261f, -0.534522f, 0.801784f)));
        }

        test_section("lerp");
        {
            constexpr nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 to(3.0f, 5.0f, -2.0f);
            constexpr auto result = from.lerp(to, 0.0f);
            ASSERT(result == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
            ASSERT(from.lerp(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
            ASSERT(from.lerp(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
            ASSERT(from.lerp(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
        }

        test_section("lerp_clamped");
        {
            constexpr nnm::Vector3 from(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 to(3.0f, 5.0f, -2.0f);
            constexpr auto result = from.lerp_clamped(to, 0.0f);
            ASSERT(result == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
            ASSERT(from.lerp_clamped(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
            ASSERT(from.lerp_clamped(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
            ASSERT(from.lerp_clamped(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
            ASSERT(from.lerp_clamped(to, -5.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
            ASSERT(from.lerp_clamped(to, 5.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
        }

        test_section("dot");
        {
            constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            constexpr auto result = v1.dot(v2);
            ASSERT(result == -28.0f);
        }

        test_section("cross");
        {
            constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            constexpr auto result = v1.cross(v2);
            ASSERT(result == nnm::Vector3f::zero());
            constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
            constexpr nnm::Vector3 v4(-2.0f, 4.0f, 6.0f);
            ASSERT(v3.cross(v4) == nnm::Vector3(0.0f, -12.0f, 8.0f));
        }

        test_section("outer");
        {
            constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            constexpr nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
            constexpr nnm::Matrix3f expected {
                { -2.0f, 4.0f, -6.0f }, { 4.0f, -8.0f, 12.0f }, { -6.0f, 12.0f, -18.0f }
            };
            constexpr auto result = v1.outer(v2);
            ASSERT(result.approx_equal(expected));
        }

        test_section("reflect");
        {
            constexpr nnm::Vector3 incident(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 normal(0.0f, 1.0f, 0.0f);
            constexpr auto result = incident.reflect(normal);
            ASSERT(result == nnm::Vector3(1.0f, -1.0f, 1.0f));
        }

        test_section("project");
        {
            constexpr nnm::Vector3 v(1.0f, 2.0f, -3.0f);
            constexpr nnm::Vector3 onto(-4.0f, 0.5f, 10.0f);
            constexpr nnm::Vector3 expected(1.135483870967742f, -0.141935483870968f, -2.838709677419355f);
            constexpr auto result = v.project(onto);
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Vector3 v(1.0f, 2.0f, -3.0f);
            constexpr auto result = v.inverse();
            ASSERT(result.approx_equal(nnm::Vector3(1.0f, 0.5f, -1.0f / 3.0f)));
        }

        test_section("angle");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            ASSERT(nnm::approx_equal(v1.angle(v2), 2.52872f))
        }

        test_section("parallel");
        {
            constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.parallel({ 2.0f, 4.0f, -6.0f });
            ASSERT(result);
            ASSERT(v1.parallel(v1));
            ASSERT(v1.parallel({ -3.0f, -6.0f, 9.0f }));
            ASSERT_FALSE(v1.parallel({ 1.0f, 2.0f, 3.0f }));
        }

        test_section("perpendicular");
        {
            constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.perpendicular({ 30.0f, 0.0f, 10.0f });
            ASSERT(result);
            ASSERT(v1.perpendicular({ 0.0f, -6.0f, -4.0f }));
            ASSERT_FALSE(v1.perpendicular(v1));
            ASSERT_FALSE(v1.perpendicular({ 1.0f, 2.0f, 3.0f }));
        }

        test_section("arbitrary_perpendicular");
        {
            constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.arbitrary_perpendicular();
            ASSERT(result.perpendicular(v1));
        }

        test_section("translate");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            constexpr auto result = v1.translate(v2);
            ASSERT(result.approx_equal({ -3.0f, 2.5f, 7.0f }))
        }

        test_section("rotate_axis_angle");
        {
            nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            nnm::Vector3 axis = nnm::Vector3(2.0f, 0.5f, -0.8f).normalize();
            ASSERT(v1.rotate_axis_angle(axis, nnm::pi<float>() / 5.0f).approx_equal({ 1.2574f, 3.10567f, -1.66545f }))
        }

        constexpr nnm::Vector3f origin { -3.0f, 1.5f, 10.0f };

        test_section("rotate_axis_angle_at");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            const auto axis = nnm::Vector3 { 2.0f, 0.5f, -0.8f }.normalize();
            ASSERT(v1.rotate_axis_angle_at(origin, axis, nnm::pi<float>() / 5.0f)
                       .approx_equal({ 0.071436f, 8.32907f, -1.36574f }));
        }

        test_section("rotate_quaternion");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr nnm::QuaternionF quaternion { 0.27948463f, 0.0698711574f, -0.111793853f, 0.95105654f };
            constexpr auto result = v1.rotate_quaternion(quaternion);
            ASSERT(result.approx_equal({ 1.2574f, 3.10567f, -1.66545f }));
        }

        test_section("rotate_quaternion_at");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            constexpr nnm::QuaternionF q { 0.27948463f, 0.0698711574f, -0.111793853f, 0.95105654f };
            constexpr auto result = v1.rotate_quaternion_at(origin, q);
            ASSERT(result.approx_equal({ 0.071436f, 8.32907f, -1.36574f }));
        }

        test_section("scale");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr nnm::Vector3 v2(-4.0f, 0.5f, 10.0f);
            constexpr auto result = v1.scale(v2);
            ASSERT(result.approx_equal({ -4.0f, 1.0f, -30.0f }));
        }

        test_section("scale_at");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            constexpr nnm::Vector3 v2 { -4.0f, 0.5f, 10.0f };
            constexpr auto result = v1.scale_at(origin, v2);
            ASSERT(result.approx_equal({ -19.0f, 1.75f, -120.0f }));
        }

        test_section("shear_x");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr auto result = v1.shear_x(0.5f, -0.5f);
            ASSERT(result.approx_equal({ 1.0f, 2.5f, -3.5f }));
        }

        test_section("shear_x_at");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.shear_x_at(origin, 0.5f, -0.5f);
            ASSERT(result.approx_equal({ 1.0f, 4.0f, -5.0f }));
        }

        test_section("shear_y");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr auto result = v1.shear_y(0.5f, -0.5f);
            ASSERT(result.approx_equal({ 2.0f, 2.0f, -4.0f }));
        }

        test_section("shear_y_at");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.shear_y_at(origin, 0.5f, -0.5f);
            ASSERT(result.approx_equal({ 1.25f, 2.0f, -3.25f }));
        }

        test_section("shear_z");
        {
            constexpr nnm::Vector3 v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.shear_z(0.5f, -0.5f);
            ASSERT(result.approx_equal({ -0.5f, 3.5f, -3.0f }));
        }

        test_section("shear_z_at");
        {
            constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
            constexpr auto result = v1.shear_z_at(origin, 0.5f, -0.5f);
            ASSERT(result.approx_equal({ -5.5f, 8.5f, -3.0f }));
        }

        test_section("transform(const Basis3&)");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr nnm::Basis3f basis({ { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } });
            constexpr auto result = v1.transform(basis);
            ASSERT(result.approx_equal({ 9.0f, -12.4f, -30.44f }));
        }

        test_section("transform_at(const Vector3&, const Basis3&)");
        {
            constexpr nnm::Vector3f v1 { 1.0f, 2.0f, -3.0f };
            constexpr nnm::Basis3f basis { { { 1.0f, -3.0f, -2.0f }, { 4.0f, -0.5f, 0.78f }, { 0.0f, 2.8f, 10.0f } } };
            constexpr auto result = v1.transform_at(origin, basis);
            ASSERT(result.approx_equal({ 3.0f, -47.15f, -127.61f }));
        }

        test_section("transform(const Transform2&)");
        {
            constexpr nnm::Vector3 v1(2.0f, -3.0f, 4.0f);
            constexpr nnm::Transform2f transform(
                { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } });
            constexpr auto result = v1.transform(transform);
            ASSERT(result.approx_equal({ 26.0f, -8.8f, 1.0f }));
        }

        test_section("transform_at(const Vector2&, const Transform2&)");
        {
            constexpr nnm::Vector3f v1 { 2.0f, -3.0f, 4.0f };
            constexpr nnm::Transform2f transform {
                { { 1.0f, 2.0f, 3.0f }, { -4.0f, 1.6f, 3.0f }, { 3.0f, -2.0f, 1.0f } }
            };
            constexpr auto result = v1.transform_at({ -10.0f, 0.5f }, transform);
            ASSERT(result.approx_equal({ 28.0f, 10.9f, 29.5f }));
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
            ASSERT(result.approx_equal({ 45.9f, 6.96f, -34.6f }));
            ASSERT(v1.transform(transform, -2.4f).approx_equal({ 12.24f, 32.596f, -102.6f }));
        }

        test_section("transform(const Vector3&, const Transform3&, Real)");
        {
            constexpr nnm::Vector3f v1 { 2.0f, -3.0f, 4.0f };
            constexpr nnm::Transform3f transform { { { 1.0f, 2.0f, -3.0f, 4.0f },
                                                     { -10.0f, 0.5f, 20.6f, 0.0f },
                                                     { 1.0f, 3.0f, 3.3f, -1.0f },
                                                     { 9.9f, -7.54f, 20.0f, 0.1f } } };
            constexpr auto result = v1.transform_at(origin, transform);
            ASSERT(result.approx_equal({ 50.9f, -16.29f, -97.5f }));
            ASSERT(v1.transform_at(origin, transform, -2.4f).approx_equal({ 17.24f, 9.346f, -165.5f }));
        }

        test_section("max");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.max();
            ASSERT(result == 4.0);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.max() == 100.0f);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.max() == 0.0f);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.max() == 100.0f);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.max() == 100.0f);
        }

        test_section("abs_max");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.abs_max();
            ASSERT(result == 4.0);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.abs_max() == -200.0f);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.abs_max() == 0.0f);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.abs_max() == -200.0f);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.abs_max() == -200.0f);
        }

        test_section("min");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.min();
            ASSERT(result == -2.0f);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.min() == -200.0f);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.min() == 0.0f);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.min() == -200.0f);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.min() == -200.0f);
        }

        test_section("abs_min");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.abs_min();
            ASSERT(result == -2.0f);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.abs_min() == 5.0f);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.abs_min() == 0.0f);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.abs_min() == 5.0f);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.abs_min() == 5.0f);
        }

        test_section("max_index");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.max_index();
            ASSERT(result == 1);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.max_index() == 2);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.max_index() == 0);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.max_index() == 2);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.max_index() == 1);
        }

        test_section("abs_max_index");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.abs_max_index();
            ASSERT(result == 1);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.abs_max_index() == 0);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.abs_max_index() == 0);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.abs_max_index() == 1);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.abs_max_index() == 2);
        }

        test_section("min_index");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.min_index();
            ASSERT(result == 2);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.min_index() == 0);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.min_index() == 0);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.min_index() == 1);
            nnm::Vector3 v5(5.0f, 100.0f, -200.0f);
            ASSERT(v5.min_index() == 2);
        }

        test_section("abs_min_index");
        {
            constexpr nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
            constexpr auto result = v1.abs_min_index();
            ASSERT(result == 2);
            nnm::Vector3 v2(-200.0f, 5.0f, 100.0f);
            ASSERT(v2.abs_min_index() == 1);
            nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
            ASSERT(v3.abs_min_index() == 0);
            nnm::Vector3 v4(5.0f, -200.0f, 100.0f);
            ASSERT(v4.abs_min_index() == 0);
            nnm::Vector3 v5(-200.0f, 100.0f, 5.0f);
            ASSERT(v5.abs_min_index() == 2);
        }

        test_section("approx_equal");
        {
            constexpr nnm::Vector3 v1(1.0f, 1.0f, 1.0f);
            constexpr nnm::Vector3 v2(1.0f + nnm::epsilon<float>() / 2.0f, 1.0f, 1.0f);
            constexpr auto result = v1.approx_equal(v2);
            ASSERT(result);
            nnm::Vector3 v3(1.0f, 1.0f, 1.0f);
            nnm::Vector3 v4(1.0f + 2.0f * nnm::epsilon<float>(), 1.0f, 1.0f);
            ASSERT_FALSE(v3.approx_equal(v4));
        }

        test_section("approx_zero");
        {
            constexpr nnm::Vector3 v1(0.0f, 0.0f, 0.0f);
            constexpr auto result = v1.approx_zero();
            ASSERT(result);
            nnm::Vector3 v2(nnm::epsilon<float>(), 0.0f, 0.0f);
            ASSERT(v2.approx_zero());
            nnm::Vector3 v3(0.0f, nnm::epsilon<float>(), nnm::epsilon<float>());
            ASSERT(v3.approx_zero());
            nnm::Vector3 v4(0.1f, 0.1f, 0.1f);
            ASSERT_FALSE(v4.approx_zero());
        }

        test_section("xy");
        {
            constexpr nnm::Vector3 v1(1.0f, 2.0f, -3.0f);
            constexpr auto result = v1.xy();
            ASSERT(result == nnm::Vector2(1.0f, 2.0f));
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
            constexpr nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            constexpr auto result = v1.at(0);
            ASSERT(result == 1.0f);
            ASSERT(v1.at(1) == -3.0f);
            ASSERT(v1.at(2) == 4.0f);
        }

        test_section("operator[]");
        {
            constexpr nnm::Vector3 v1(1.0f, -3.0f, 4.0f);
            constexpr auto result = v1[0];
            ASSERT(result == 1.0f);
            ASSERT(v1[1] == -3.0f);
            ASSERT(v1[2] == 4.0f);
        }

        constexpr nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
        constexpr nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
        constexpr nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

        test_section("operator==");
        {
            constexpr auto result = v1 == v3;
            ASSERT(result);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            constexpr auto result = v1 != v3;
            ASSERT_FALSE(result);
            ASSERT(v1 != v2);
        }

        test_section("operator+(const Vector3&)");
        {
            constexpr auto result = v1 + v2;
            ASSERT(result == nnm::Vector3(4.0f, 6.0f, 1.0f));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy += v2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3(4.0f, 6.0f, 1.0f));
        }

        test_section("operator-(const Vector3&)");
        {
            constexpr auto result = v2 - v1;
            ASSERT(result == nnm::Vector3(2.0f, 2.0f, -5.0f));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy -= v1;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3(2.0f, 2.0f, -5.0f));
        }

        test_section("operator*(const Vector3&)");
        {
            constexpr auto result = v1 * v2;
            ASSERT(result == nnm::Vector3(3.0f, 8.0f, -6.0f));
        }

        test_section("operator*=(const Vector3&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= v2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3(3.0f, 8.0f, -6.0f));
        }

        test_section("operator*(const Matrix3&)");
        {
            constexpr nnm::Matrix3f matrix { { 1.0f, -3.0f, 4.0f }, { -1.6f, 0.5f, 20.0f }, { 0.0f, 2.0f, 1.0f } };
            constexpr auto result = v2 * matrix;
            ASSERT(result.approx_equal({ -17.0f, -42.8f, 6.0f }))
        }

        test_section("operator*(float)");
        {
            constexpr auto result = v1 * 2.0f;
            ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator*(float, const Vector3&)");
        {
            constexpr auto result = 2.0f * v1;
            ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= 2.0f;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("operator/(const Vector3&)");
        {
            constexpr auto result = v2 / v1;
            ASSERT(result == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        }

        test_section("operator/=(const Vector3&)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= v1;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        }

        test_section("operator/(float)");
        {
            constexpr auto result = v2 / 2.0f;
            ASSERT(result == nnm::Vector3(1.5f, 2.0f, -1.0f));
        }

        test_section("operator/(float, const Vector3&)");
        {
            constexpr auto result = 2.0f / v2;
            ASSERT(result == nnm::Vector3(0.66666666f, 0.5f, -1.0f));
        }

        test_section("operator/=(float)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= 2.0f;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3(1.5f, 2.0f, -1.0f));
        }

        test_section("operator+");
        {
            constexpr auto result = +v1;
            ASSERT(result == v1);
        }

        test_section("operator-");
        {
            constexpr auto result = -v1;
            ASSERT(result == nnm::Vector3(-1.0f, -2.0f, -3.0f));
        }

        test_section("operator<");
        {
            constexpr auto result = v1 < v2;
            ASSERT(result);
            ASSERT_FALSE(v2 < v1);
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(v1);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
        }
    }

    test_case("Vector3i");
    {
        test_section("Vector3i()");
        {
            constexpr nnm::Vector3ii v_default;
            ASSERT(v_default.x == 0);
            ASSERT(v_default.y == 0);
            ASSERT(v_default.z == 0);
        }

        test_section("Vector3i(const Vector3&)");
        {
            constexpr nnm::Vector3ii v(nnm::Vector3(1.1f, 0.2f, -1.6f));
            ASSERT(v.x == 1);
            ASSERT(v.y == 0);
            ASSERT(v.z == -1);
        }

        test_section("Vector3i(const Vector2i&, int)");
        {
            constexpr nnm::Vector3i v(nnm::Vector2i(1, -2), 3);
            ASSERT(v.x == 1);
            ASSERT(v.y == -2);
            ASSERT(v.z == 3);
        }

        test_section("Vector3i(int, int, int)");
        {
            constexpr nnm::Vector3i v_with_params(1, -2, 3);
            ASSERT(v_with_params.x == 1);
            ASSERT(v_with_params.y == -2);
            ASSERT(v_with_params.z == 3);
        }

        test_section("all");
        {
            constexpr auto v_all_threes = nnm::Vector3ii::all(3);
            ASSERT(v_all_threes.x == 3);
            ASSERT(v_all_threes.y == 3);
            ASSERT(v_all_threes.z == 3);
        }

        test_section("zero");
        {
            constexpr auto v_zero = nnm::Vector3ii::zero();
            ASSERT(v_zero.x == 0);
            ASSERT(v_zero.y == 0);
            ASSERT(v_zero.z == 0);
        }

        test_section("one");
        {
            constexpr auto v_one = nnm::Vector3ii::one();
            ASSERT(v_one.x == 1);
            ASSERT(v_one.y == 1);
            ASSERT(v_one.z == 1);
        }

        test_section("axis_x");
        {
            constexpr auto x = nnm::Vector3ii::axis_x();
            ASSERT(x.x == 1);
            ASSERT(x.y == 0);
            ASSERT(x.z == 0);
        }

        test_section("axis_y");
        {
            constexpr auto y = nnm::Vector3ii::axis_y();
            ASSERT(y.x == 0);
            ASSERT(y.y == 1);
            ASSERT(y.z == 0);
        }

        test_section("axis_z");
        {
            constexpr auto z = nnm::Vector3ii::axis_z();
            ASSERT(z.x == 0);
            ASSERT(z.y == 0);
            ASSERT(z.z == 1);
        }

        test_section("abs");
        {
            constexpr nnm::Vector3i v(0, -2, 3);
            constexpr auto result = v.abs();
            ASSERT(result == nnm::Vector3i(0, 2, 3));
        }

        test_section("clamp");
        {
            constexpr nnm::Vector3i v(0, -2, 3);
            constexpr auto result = v.clamp({ -1, -3, -2 }, { 1, 5, 100 });
            ASSERT(result == nnm::Vector3i(0, -2, 3));
            ASSERT(v.clamp({ 1, 3, 5 }, { 2, 5, 100 }) == nnm::Vector3i(1, 3, 5));
            ASSERT(v.clamp({ -10, -5, -100 }, { -1, -4, 3 }) == nnm::Vector3i(-1, -4, 3));
        }

        test_section("manhattan_distance");
        {
            constexpr nnm::Vector3i from1(1, 1, 1);
            constexpr nnm::Vector3i to1(2, 2, 2);
            constexpr auto result = from1.manhattan_distance(to1);
            ASSERT(result == 3);

            auto from = nnm::Vector3i(-1, -1, -1);
            auto to = nnm::Vector3i(1, 1, 1);
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
            constexpr nnm::Vector3i v(1, -2, 3);
            constexpr auto result = v.length_sqrd();
            ASSERT(result == 14);
        }

        test_section("dot");
        {
            constexpr nnm::Vector3i v1(1, -2, 3);
            constexpr nnm::Vector3i v2(-2, 4, -6);
            constexpr auto result = v1.dot(v2);
            ASSERT(result == -28);
        }

        test_section("cross");
        {
            constexpr nnm::Vector3i v1(1, -2, 3);
            constexpr nnm::Vector3i v2(-2, 4, -6);
            constexpr auto result = v1.cross(v2);
            ASSERT(result == nnm::Vector3ii::zero());
            constexpr nnm::Vector3i v3(1, 2, 3);
            constexpr nnm::Vector3i v4(-2, 4, 6);
            ASSERT(v3.cross(v4) == nnm::Vector3i(0, -12, 8));
        }

        test_section("parallel");
        {
            constexpr nnm::Vector3i v1 { 1, 2, -3 };
            constexpr auto result = v1.parallel({ 2, 4, -6 });
            ASSERT(result);
            ASSERT(v1.parallel(v1));
            ASSERT(v1.parallel({ -3, -6, 9 }));
            ASSERT_FALSE(v1.parallel({ 1, 2, 3 }));
        }

        test_section("approx_perpendicular");
        {
            constexpr nnm::Vector3i v1 { 1, 2, -3 };
            constexpr auto result = v1.perpendicular({ 30, 0, 10 });
            ASSERT(result);
            ASSERT(v1.perpendicular({ 0, -6, -4 }));
            ASSERT_FALSE(v1.perpendicular(v1));
            ASSERT_FALSE(v1.perpendicular({ 1, 2, 3 }));
        }

        test_section("arbitrary_perpendicular");
        {
            constexpr nnm::Vector3i v1 { 1, 2, -3 };
            constexpr auto result = v1.arbitrary_perpendicular();
            ASSERT(result.perpendicular(v1));
        }

        test_section("max");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.max();
            ASSERT(result == 4);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.max() == 100);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.max() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.max() == 100);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.max() == 100);
        }

        test_section("abs_max");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.abs_max();
            ASSERT(result == 4);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.abs_max() == -200);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.abs_max() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.abs_max() == -200);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.abs_max() == -200);
        }

        test_section("min");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.min();
            ASSERT(result == -2);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.min() == -200);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.min() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.min() == -200);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.min() == -200);
        }

        test_section("abs_min");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.abs_min();
            ASSERT(result == -2);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.abs_min() == 5);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.abs_min() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.abs_min() == 5);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.abs_min() == 5);
        }

        test_section("max_index");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.max_index();
            ASSERT(result == 1);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.max_index() == 2);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.max_index() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.max_index() == 2);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.max_index() == 1);
        }

        test_section("abs_max_index");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.abs_max_index();
            ASSERT(result == 1);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.abs_max_index() == 0);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.abs_max_index() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.abs_max_index() == 1);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.abs_max_index() == 2);
        }

        test_section("min_index");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.min_index();
            ASSERT(result == 2);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.min_index() == 0);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.min_index() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.min_index() == 1);
            nnm::Vector3i v5(5, 100, -200);
            ASSERT(v5.min_index() == 2);
        }

        test_section("abs_min_index");
        {
            constexpr nnm::Vector3i v1(3, 4, -2);
            constexpr auto result = v1.abs_min_index();
            ASSERT(result == 2);
            nnm::Vector3i v2(-200, 5, 100);
            ASSERT(v2.abs_min_index() == 1);
            nnm::Vector3i v3(0, 0, 0);
            ASSERT(v3.abs_min_index() == 0);
            nnm::Vector3i v4(5, -200, 100);
            ASSERT(v4.abs_min_index() == 0);
            nnm::Vector3i v5(-200, 100, 5);
            ASSERT(v5.abs_min_index() == 2);
        }

        test_section("xy");
        {
            constexpr nnm::Vector3i v(1, -2, 3);
            constexpr auto result = v.xy();
            ASSERT(result == nnm::Vector2i(1, -2));
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
            constexpr nnm::Vector3i v(1, -2, 3);
            constexpr auto result = v.at(0);
            ASSERT(result == 1);
            ASSERT(v.at(1) == -2);
            ASSERT(v.at(2) == 3);
        }

        test_section("operator[]");
        {
            constexpr nnm::Vector3i v(1, -2, 3);
            constexpr auto result = v[0];
            ASSERT(result == 1);
            ASSERT(v[1] == -2);
            ASSERT(v[2] == 3);
        }

        constexpr nnm::Vector3i v1(1, 2, -3);
        constexpr nnm::Vector3i v2(-3, 4, 100);
        constexpr nnm::Vector3i v3(1, 2, -3);

        test_section("operator==");
        {
            constexpr auto result = v1 == v3;
            ASSERT(result);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            constexpr auto result = v1 != v3;
            ASSERT_FALSE(result);
            ASSERT(v1 != v2);
        }

        test_section("operator+(const Vector3i&)");
        {
            constexpr auto result = v1 + v2;
            ASSERT(result == nnm::Vector3i(-2, 6, 97));
        }

        test_section("operator+=(const Vector3i&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy += v2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3i(-2, 6, 97));
        }

        test_section("operator-(const Vector3i&)");
        {
            constexpr auto result = v2 - v1;
            ASSERT(result == nnm::Vector3i(-4, 2, 103));
        }

        test_section("operator-=(const Vector3i&)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy -= v1;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3i(-4, 2, 103));
        }

        test_section("operator*(const Vector3i&)");
        {
            constexpr auto result = v1 * v2;
            ASSERT(result == nnm::Vector3i(-3, 8, -300));
        }

        test_section("operator*=(const Vector3i&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= v2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3i(-3, 8, -300));
        }

        test_section("operator*(int)");
        {
            constexpr auto result = v1 * 2;
            ASSERT(result == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator*(int, const Vector3i&)");
        {
            constexpr auto result = 2 * v1;
            ASSERT(result == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator*=(int)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= 2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3i(2, 4, -6));
        }

        test_section("operator/(const Vector3i&)");
        {
            constexpr auto result = v2 / v1;
            ASSERT(result == nnm::Vector3i(-3, 2, -33));
        }

        test_section("operator/=(const Vector3i&)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= v1;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3i(-3, 2, -33));
        }

        test_section("operator/(int)");
        {
            constexpr auto result = v2 / 2;
            ASSERT(result == nnm::Vector3i(-1, 2, 50));
        }

        test_section("operator/(int, const Vector3i&)");
        {
            constexpr auto result = 2 / v1;
            ASSERT(result == nnm::Vector3i(2, 1, 0));
        }

        test_section("operator/=(int)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= 2;
                return v2_copy;
            }();
            ASSERT(result == nnm::Vector3i(-1, 2, 50));
        }

        test_section("operator%(const Vector3i&)");
        {
            constexpr auto result = v1 % v2;
            ASSERT(result == nnm::Vector3i(1, 2, -3));
        }

        test_section("operator%=(const Vector3i&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy %= v2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3i(1, 2, -3));
        }

        test_section("operator%(int)");
        {
            constexpr auto result = v1 % 2;
            ASSERT(result == nnm::Vector3i(1, 0, -1));
        }

        test_section("operator%(int, const Vector3i&)");
        {
            constexpr auto result = 3 % v2;
            ASSERT(result == nnm::Vector3i(0, 3, 3));
        }

        test_section("operator%=(int)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy %= 2;
                return v1_copy;
            }();
            ASSERT(result == nnm::Vector3i(1, 0, -1));
        }

        test_section("operator+");
        {
            constexpr auto result = +v1;
            ASSERT(result == v1);
        }

        test_section("operator-");
        {
            constexpr auto result = -v1;
            ASSERT(result == nnm::Vector3i(-1, -2, 3));
        }

        test_section("operator<");
        {
            constexpr auto result = v2 < v1;
            ASSERT(result);
            ASSERT_FALSE(v1 < v2);
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(v1);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
        }

        test_section("hash");
        {
            constexpr nnm::Vector3i v { 1, -2, 3 };
            const auto _ = nnm::Vector3ii::Hash()(v);
        }
    }

    test_case("Vector4");
    {
        test_section("Vector4()");
        {
            constexpr nnm::Vector4f v1;
            ASSERT(v1.x == 0.0f);
            ASSERT(v1.y == 0.0f);
            ASSERT(v1.z == 0.0f);
            ASSERT(v1.w == 0.0f);
        }

        test_section("Vector4(const Vector4<Other>&)");
        {
            constexpr nnm::Vector4d v1(1.0, -2.0, 0.5, -0.75);
            constexpr nnm::Vector4f v2(v1);
            ASSERT(v2.x == 1.0f);
            ASSERT(v2.y == -2.0f);
            ASSERT(v2.z == 0.5f);
            ASSERT(v2.w == -0.75f);
        }

        test_section("Vector4(const Vector2&, float, float)");
        {
            constexpr nnm::Vector4 v(nnm::Vector2(1.0f, -2.0f), 3.0f, -4.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == -2.0f);
            ASSERT(v.z == 3.0f);
            ASSERT(v.w == -4.0f);
        }

        test_section("Vector4(const Vector3&, float)");
        {
            constexpr nnm::Vector4 v(nnm::Vector3(1.0f, -2.0f, 3.0f), -4.0f);
            ASSERT(v.x == 1.0f);
            ASSERT(v.y == -2.0f);
            ASSERT(v.z == 3.0f);
            ASSERT(v.w == -4.0f);
        }

        test_section("Vector4(float, float, float, float)");
        {
            constexpr nnm::Vector4 v2(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(v2.x == -1.0f);
            ASSERT(v2.y == 2.0f);
            ASSERT(v2.z == -3.0f);
            ASSERT(v2.w == 4.0f);
        }

        test_section("all");
        {
            constexpr auto v1 = nnm::Vector4f::all(3.0f);
            ASSERT(v1.x == 3.0f);
            ASSERT(v1.y == 3.0f);
            ASSERT(v1.z == 3.0f);
            ASSERT(v1.w == 3.0f);
        }

        test_section("zero");
        {
            constexpr auto v2 = nnm::Vector4f::zero();
            ASSERT(v2.x == 0.0f);
            ASSERT(v2.y == 0.0f);
            ASSERT(v2.z == 0.0f);
            ASSERT(v2.w == 0.0f);
        }

        test_section("one");
        {
            constexpr auto v3 = nnm::Vector4f::one();
            ASSERT(v3.x == 1.0f);
            ASSERT(v3.y == 1.0f);
            ASSERT(v3.z == 1.0f);
            ASSERT(v3.w == 1.0f);
        }

        test_section("axis_x");
        {
            constexpr auto x = nnm::Vector4f::axis_x();
            ASSERT(x.x == 1.0f);
            ASSERT(x.y == 0.0f);
            ASSERT(x.z == 0.0f);
            ASSERT(x.w == 0.0f);
        }

        test_section("axis_y");
        {
            constexpr auto y = nnm::Vector4f::axis_y();
            ASSERT(y.x == 0.0f);
            ASSERT(y.y == 1.0f);
            ASSERT(y.z == 0.0f);
            ASSERT(y.w == 0.0f);
        }

        test_section("axis_z");
        {
            constexpr auto z = nnm::Vector4f::axis_z();
            ASSERT(z.x == 0.0f);
            ASSERT(z.y == 0.0f);
            ASSERT(z.z == 1.0f);
            ASSERT(z.w == 0.0f);
        }

        test_section("axis_w");
        {
            constexpr auto w = nnm::Vector4f::axis_w();
            ASSERT(w.x == 0.0f);
            ASSERT(w.y == 0.0f);
            ASSERT(w.z == 0.0f);
            ASSERT(w.w == 1.0f);
        }

        test_section("abs");
        {
            constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            constexpr nnm::Vector4 v_expected(1.0f, 2.0f, 3.0f, 4.0f);
            constexpr auto result = v1.abs();
            ASSERT(result == v_expected);
        }

        test_section("ceil");
        {
            constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            constexpr nnm::Vector4 v_expected(-1.0f, 1.0f, 0.0f, 2.0f);
            ASSERT(v1.ceil() == v_expected);
        }

        test_section("floor");
        {
            constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            constexpr nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 1.0f);
            ASSERT(v1.floor() == v_expected);
        }

        test_section("round");
        {
            constexpr nnm::Vector4 v1(-1.9f, 0.001f, 0.0f, 1.6f);
            constexpr nnm::Vector4 v_expected(-2.0f, 0.0f, 0.0f, 2.0f);
            ASSERT(v1.round() == v_expected);
        }

        test_section("clamp");
        {
            constexpr nnm::Vector4 v1(-1.0f, 2.0f, 3.0f, -4.0f);
            constexpr nnm::Vector4 v2(2.0f, -3.0f, -2.0f, -3.0f);
            constexpr nnm::Vector4 v3(4.0f, 1.0f, 4.0f, 1.0f);
            constexpr auto result = v1.clamp(v2, v3);
            ASSERT(result == nnm::Vector4(2.0f, 1.0f, 3.0f, -3.0f));
        }

        test_section("length_sqrd");
        {
            constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            constexpr auto result = v1.length_sqrd();
            ASSERT(nnm::approx_equal(result, 30.0f));
        }

        test_section("length");
        {
            constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
            ASSERT(nnm::approx_equal(v1.length(), nnm::sqrt(30.0f)));
        }

        constexpr nnm::Vector4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
        constexpr nnm::Vector4 v2(4.0f, 5.0f, -2.0f, 1.5f);

        test_section("clamp_length");
        {
            ASSERT(v1.clamp_length(0.0f, 1.0f).approx_equal(v1.normalize()));
            ASSERT(v1.clamp_length(2.0f, 3.0f).approx_equal(v1.normalize() * 3.0f));
            ASSERT(v1.clamp_length(10.0f, 50.0f).approx_equal(v1.normalize() * 10.0f));
        }

        test_section("normalize");
        {
            ASSERT(nnm::Vector4f().normalize() == nnm::Vector4f());
            constexpr nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);
            constexpr nnm::Vector4 v_expected(-0.182574f, 0.365148f, -0.547723f, 0.730297f);
            ASSERT(v3.normalize().approx_equal(v_expected));
        }

        test_section("lerp");
        {
            constexpr auto result = v1.lerp(v2, 0.0f);
            ASSERT(result == v1);
            ASSERT(v1.lerp(v2, 1.0f) == v2);
            ASSERT(v1.lerp(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
        }

        test_section("lerp_clamped");
        {
            constexpr auto result = v1.lerp_clamped(v2, 0.0f);
            ASSERT(result == v1);
            ASSERT(v1.lerp_clamped(v2, 1.0f) == v2);
            ASSERT(v1.lerp_clamped(v2, 0.5f).approx_equal({ 1.5f, 3.5f, -2.5f, 2.75f }));
            ASSERT(v1.lerp_clamped(v2, -5.0f) == v1);
            ASSERT(v1.lerp_clamped(v2, 5.0f) == v2);
        }

        test_section("dot");
        {
            constexpr auto result = v1.dot(v2);
            ASSERT(nnm::approx_equal(result, 18.0f));
        }

        test_section("outer");
        {
            nnm::Matrix4f expected { { -4.0f, -5.0f, 2.0f, -1.5f },
                                     { 8.0f, 10.0f, -4.0f, 3.0f },
                                     { -12.0f, -15.0f, 6.0f, -4.5f },
                                     { 16.0f, 20.0f, -8.0f, 6.0f } };
            constexpr auto result = v1.outer(v2);
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Vector4 v_expected(-1.0f, 0.5f, -0.33333333f, 0.25f);
            constexpr auto result = v1.inverse();
            ASSERT(result.approx_equal(v_expected));
        }

        test_section("transform");
        {
            constexpr nnm::Transform3f transform(
                { { 1.0f, 2.0f, -3.0f, 4.0f },
                  { -10.0f, 0.5f, 20.6f, 0.0f },
                  { 1.0f, 3.0f, 3.3f, -1.0f },
                  { 9.9f, -7.54f, 20.0f, 0.1f } });
            constexpr auto result = v1.transform(transform);
            ASSERT(result.approx_equal({ 15.6f, -40.16f, 114.3f, -0.6f }))
        }

        test_section("transform_at");
        {
            constexpr nnm::Transform3f transform { { { 1.0f, 2.0f, -3.0f, 4.0f },
                                                     { -10.0f, 0.5f, 20.6f, 0.0f },
                                                     { 1.0f, 3.0f, 3.3f, -1.0f },
                                                     { 9.9f, -7.54f, 20.0f, 0.1f } } };
            constexpr auto result = v1.transform_at({ -3.0f, 1.5f, 10.0f }, transform);
            ASSERT(result.approx_equal({ 20.6f, -63.41f, 51.4f, 21.4f }));
        }

        test_section("max");
        {
            constexpr auto result = v1.max();
            ASSERT(result == 4.0f);
            ASSERT(v2.max() == 5.0f);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.max() == 4.0f);
        }

        test_section("abs_max");
        {
            constexpr auto result = v1.abs_max();
            ASSERT(result == 4.0f);
            ASSERT(v2.abs_max() == 5.0f);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.abs_max() == -5.0f);
        }

        test_section("min");
        {
            constexpr auto result = v1.min();
            ASSERT(result == -3.0f);
            ASSERT(v2.min() == -2.0f);
            constexpr nnm::Vector4f v3 { -2.0f, 2.0f, 3.0f, -1.0f };
            ASSERT(v3.min() == -2.0f);
            constexpr nnm::Vector4f v4 { -2.0f, 2.0f, 3.0f, -10.0f };
            ASSERT(v4.min() == -10.0f);
        }

        test_section("abs_min");
        {
            constexpr auto result = v1.abs_min();
            ASSERT(result == -1.0f);
            ASSERT(v2.abs_min() == 1.5f);
            constexpr nnm::Vector4f v3 { -2.0f, 2.0f, 3.0f, -1.0f };
            ASSERT(v3.abs_min() == -1.0f);
            constexpr nnm::Vector4f v4 { -2.0f, 2.0f, 3.0f, -10.0f };
            ASSERT(v4.abs_min() == -2.0f);
        }

        test_section("max_index");
        {
            constexpr auto result = v1.max_index();
            ASSERT(result == 3);
            ASSERT(v2.max_index() == 1);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.max_index() == 3);
        }

        test_section("abs_max_index");
        {
            constexpr auto result = v1.abs_max_index();
            ASSERT(result == 3);
            ASSERT(v2.abs_max_index() == 1);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.abs_max_index() == 1);
        }

        test_section("min_index");
        {
            constexpr auto result = v1.min_index();
            ASSERT(result == 2);
            ASSERT(v2.min_index() == 2);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.min_index() == 1);
        }

        test_section("abs_min_index");
        {
            constexpr auto result = v1.abs_min_index();
            ASSERT(result == 0);
            ASSERT(v2.abs_min_index() == 3);
            constexpr nnm::Vector4f v3(-1.0f, -5.0f, -3.0f, 4.0f);
            ASSERT(v3.abs_min_index() == 0);
        }

        test_section("approx_equal");
        {
            constexpr nnm::Vector4 v1_almost(-0.99999999f, 2.0f, -3.00000001f, 3.99999f);
            constexpr auto result = v1.approx_equal(v1_almost);
            ASSERT(result);
            ASSERT_FALSE(v1.approx_equal(v2));
        }

        test_section("approx_zero");
        {
            constexpr nnm::Vector4 almost_zero(0.00001f, -0.000001f, 0.0f, 0.00000001f);
            constexpr auto result = almost_zero;
            ASSERT(result);
        }

        test_section("xy");
        {
            constexpr auto result = v1.xy();
            ASSERT(result == nnm::Vector2(-1.0f, 2.0f));
        }

        test_section("xyz");
        {
            constexpr auto result = v1.xyz();
            ASSERT(result == nnm::Vector3(-1.0f, 2.0f, -3.0f));
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
            constexpr auto result = v1.at(0);
            ASSERT(result == -1.0f);
            ASSERT(v1.at(1) == 2.0f);
            ASSERT(v1.at(2) == -3.0f);
            ASSERT(v1.at(3) == 4.0f);
        }

        test_section("operator[]");
        {
            constexpr auto result = v1[0];
            ASSERT(result == -1.0f);
            ASSERT(v1[1] == 2.0f);
            ASSERT(v1[2] == -3.0f);
            ASSERT(v1[3] == 4.0f);
        }

        constexpr nnm::Vector4 v3(-1.0f, 2.0f, -3.0f, 4.0f);

        test_section("operator==");
        {
            constexpr auto result = v1 == v3;
            ASSERT(result);
            ASSERT_FALSE(v1 == v2);
        }

        test_section("operator!=");
        {
            constexpr auto result = v1 != v2;
            ASSERT(result);
            ASSERT_FALSE(v1 != v3);
        }

        test_section("operator+(const Vector4&)");
        {
            constexpr auto result = v1 + v2;
            ASSERT(result.approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
        }

        test_section("operator+=(const Vector4&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy += v2;
                return v1_copy;
            }();
            ASSERT(result.approx_equal({ 3.0f, 7.0f, -5.0f, 5.5f }));
        }

        test_section("operator-(const Vector4&)");
        {
            constexpr auto result = v1 - v2;
            ASSERT(result.approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
        }

        test_section("operator-=(const Vector4&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy -= v2;
                return v1_copy;
            }();
            ASSERT(result.approx_equal({ -5.0f, -3.0f, -1.0f, 2.5f }));
        }

        test_section("operator*(const Vector4&)");
        {
            constexpr auto result = v1 * v2;
            ASSERT(result.approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
        }

        test_section("operator*=(const Vector4&)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= v2;
                return v1_copy;
            }();
            ASSERT(result.approx_equal({ -4.0f, 10.0f, 6.0f, 6.0f }));
        }

        test_section("operator*(const Matrix4&)");
        {
            constexpr nnm::Matrix4f matrix { { 1.0f, 2.0f, 3.0f, 4.0f },
                                             { -1.0f, -2.0f, -3.0f, -4.0f },
                                             { 1.0f, 3.0f, 2.0f, 4.0f },
                                             { -4.0f, -2.0f, -3.0f, -1.0f } };
            constexpr auto result = v1 * matrix;
            ASSERT(result.approx_equal({ 10.0f, -10.0f, 15.0f, 5.0f }))
        }

        test_section("operator*(float)");
        {
            constexpr auto result = v1 * 2.0f;
            ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator*(float, const Vector4&)");
        {
            constexpr auto result = 2.0f * v1;
            ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                auto v1_copy = v1;
                v1_copy *= 2.0f;
                return v1_copy;
            }();
            ASSERT(result.approx_equal({ -2.0f, 4.0f, -6.0f, 8.0f }));
        }

        test_section("operator/(const Vector4&)");
        {
            constexpr auto result = v2 / v1;
            ASSERT(result.approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
        }

        test_section("operator/=(const Vector4&)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= v1;
                return v2_copy;
            }();
            ASSERT(result.approx_equal({ -4.0f, 2.5f, 0.66666666f, 0.375f }));
        }

        test_section("operator/(float)");
        {
            constexpr auto result = v2 / 2.0f;
            ASSERT(result.approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
        }

        test_section("operator/=(float)");
        {
            constexpr auto result = [=] {
                auto v2_copy = v2;
                v2_copy /= 2.0f;
                return v2_copy;
            }();
            ASSERT(result.approx_equal({ 2.0f, 2.5f, -1.0f, 0.75f }));
        }

        test_section("operator<(const Vector4&)");
        {
            constexpr auto result = v1 < v2;
            ASSERT(result);
            ASSERT_FALSE(v2 < v1);
        }

        test_section("operator+");
        {
            constexpr auto result = +v1;
            ASSERT(result == v1);
        }

        test_section("operator-");
        {
            constexpr auto result = -v1;
            ASSERT(result == nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(v1);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Vector4f::zero()));
        }
    }

    test_case("Quaternion");
    {
        test_section("Quaternion()");
        {
            constexpr nnm::QuaternionF q;
            ASSERT(q.x == 0.0f);
            ASSERT(q.y == 0.0f);
            ASSERT(q.z == 0.0f);
            ASSERT(q.w == 1.0f);
        }

        test_section("Quaternion(const Quaternion<Other>&)");
        {
            constexpr nnm::QuaternionD q1(1.0, -2.0, 3.0, -4.5);
            constexpr nnm::QuaternionF q2(q1);
            ASSERT(q2.x == 1.0f);
            ASSERT(q2.y == -2.0f);
            ASSERT(q2.z == 3.0f);
            ASSERT(q2.w == -4.5f);
        }

        test_section("Quaternion(const Vector4&)");
        {
            constexpr nnm::Quaternion q(nnm::Vector4(1.0f, -2.0f, 3.0f, -4.0f));
            ASSERT(q.x == 1.0f);
            ASSERT(q.y == -2.0f);
            ASSERT(q.z == 3.0f);
            ASSERT(q.w == -4.0f);
        }

        test_section("Quaternion(float, float, float, float)");
        {
            constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q.x == 1.0f);
            ASSERT(q.y == -2.0f);
            ASSERT(q.z == 3.0f);
            ASSERT(q.w == -4.0f);
        }

        test_section("identity");
        {
            constexpr auto q = nnm::QuaternionF::identity();
            ASSERT(q.x == 0.0f);
            ASSERT(q.y == 0.0f);
            ASSERT(q.z == 0.0f);
            ASSERT(q.w == 1.0f);
        }

        test_section("from_axis_angle");
        {
            const auto q = nnm::QuaternionF::from_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi<float>() / 9.0f);
            ASSERT(q.approx_equal({ 0.1515726f, -0.0757863f, 0.0378931f, 0.9848078f }))
        }

        test_section("from_vector_to_vector");
        {
            constexpr nnm::Vector3 from(1.0f, -2.0f, 3.0f);
            const auto to = from.rotate_axis_angle({ 2.0f, -1.0f, 0.5f }, nnm::pi<float>() / 9.0f);
            const auto q = nnm::QuaternionF::from_vector_to_vector(from, to);
            const auto rotated_from = from.rotate_quaternion(q);
            ASSERT(rotated_from.approx_equal(to));
        }

        test_section("normalize");
        {
            constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(q.normalize().approx_equal({ 0.182574f, -0.365148f, 0.547723f, -0.730297f }));
        }

        test_section("axis_to");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), 0.0f);
            const auto q2 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), nnm::pi<float>() / 4.0f);
            ASSERT(q1.axis_to(q2).approx_equal(nnm::Vector3f::axis_x()));
            const auto q3 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), nnm::pi<float>() / 9.0f);
            const auto q4 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), -nnm::pi<float>() / 3.0f);
            ASSERT(q3.axis_to(q4).approx_equal(-nnm::Vector3f::axis_y()));
        }

        test_section("angle_to");
        {
            const auto q1 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), 0.0f);
            const auto q2 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_x(), nnm::pi<float>() / 4.0f);
            ASSERT(nnm::approx_equal(q1.angle_to(q2), nnm::pi<float>() / 4.0f));
            const auto q3 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), nnm::pi<float>() / 9.0f);
            const auto q4 = nnm::QuaternionF::from_axis_angle(nnm::Vector3f::axis_y(), -nnm::pi<float>() / 3.0f);
            ASSERT(nnm::approx_equal(q3.angle_to(q4), 4.0f * nnm::pi<float>() / 9.0f));
        }

        test_section("axis");
        {
            const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
            constexpr float angle = nnm::pi<float>() / 9.0f;
            const auto q = nnm::QuaternionF::from_axis_angle(axis, angle);
            ASSERT(q.axis().approx_equal(axis));
        }

        test_section("angle");
        {
            const auto axis = nnm::Vector3(2.0f, -1.0f, 0.5f).normalize();
            constexpr float angle = nnm::pi<float>() / 9.0f;
            const auto q = nnm::QuaternionF::from_axis_angle(axis, angle);
            ASSERT(nnm::approx_equal(q.angle(), angle));
        }

        test_section("inverse");
        {
            constexpr auto q = nnm::Quaternion(1.0f, -2.0f, 3.0f, -4.0f);
            constexpr auto result = q.inverse();
            ASSERT(result.approx_equal({ -q.x, -q.y, -q.z, q.w }));
        }

        test_section("length_sqrd");
        {
            constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            constexpr auto result = q.length_sqrd();
            ASSERT(nnm::approx_equal(result, 30.0f));
        }

        test_section("length");
        {
            constexpr nnm::Quaternion q(1.0f, -2.0f, 3.0f, -4.0f);
            ASSERT(nnm::approx_equal(q.length(), 5.47723f));
        }

        constexpr auto q1 = nnm::Quaternion(0.151572555f, -0.0757862777f, 0.0378931388f, 0.984807729f);
        constexpr auto q2 = nnm::Quaternion(-0.109108947f, -0.545544684f, 0.436435789f, 0.707106769f);

        test_section("slerp");
        {
            ASSERT(q1.slerp(q2, 0.75f).approx_equal({ -0.0439172f, -0.4470681f, 0.3514504f, 0.8213915f }));
        }

        test_section("rotate_axis_angle");
        {
            const nnm::Quaternion q3 = q1.rotate_axis_angle({ -1.0f, 2.0f, -0.5f }, -nnm::pi<float>() / 3.0f);
            ASSERT(q3.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
        }

        test_section("rotate_quaternion");
        {
            constexpr nnm::QuaternionF q3 { 0.21821788f, -0.436435759f, 0.10910894f, 0.866025388f };
            constexpr nnm::Quaternion q4 = q1.rotate_quaternion(q3);
            ASSERT(q4.approx_equal({ 0.3378994f, -0.4871692f, 0.1898815f, 0.7825823f }));
        }

        test_section("approx_equal");
        {
            constexpr auto result = q1.approx_equal(q2);
            ASSERT_FALSE(result);
            ASSERT(q1.approx_equal(q1));
            constexpr nnm::Quaternion q3(0.15157f, -0.07579f, 0.03789f, 0.98481f);
            ASSERT(q1.approx_equal(q3));
        }

        test_section("at");
        {
            constexpr nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
            constexpr auto result = q3.at(0);
            ASSERT(result == 1.0f);
            ASSERT(q3.at(1) == -2.0f);
            ASSERT(q3.at(2) == 3.0f);
            ASSERT(q3.at(3) == -4.0f);
        }

        test_section("operator[]");
        {
            constexpr nnm::Quaternion q3(1.0f, -2.0f, 3.0f, -4.0f);
            constexpr auto result = q3[0];
            ASSERT(result == 1.0f);
            ASSERT(q3[1] == -2.0f);
            ASSERT(q3[2] == 3.0f);
            ASSERT(q3[3] == -4.0f);
        }

        test_section("operator==");
        {
            constexpr auto q3 = q1;
            constexpr auto result = q1 == q3;
            ASSERT(result);
            ASSERT_FALSE(q1 == q2);
        }

        test_section("operator!=");
        {
            constexpr auto q3 = q1;
            constexpr auto result = q1 != q3;
            ASSERT_FALSE(result);
            ASSERT(q1 != q2);
        }

        test_section("operator*");
        {
            constexpr auto result = q1 * q2;
            ASSERT(result.approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
        }

        test_section("operator*=");
        {
            constexpr auto result = [=] {
                auto q1_copy = q1;
                q1_copy *= q2;
                return q1_copy;
            }();
            ASSERT(result.approx_equal({ -0.0126768f, -0.6611317f, 0.3656413f, 0.6550194f }));
        }

        test_section("operator<");
        {
            constexpr auto result = q2 < q1;
            ASSERT(result);
            ASSERT_FALSE(q1 < q2);
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(q1);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Quaternion(nnm::Vector4f::zero())));
        }
    }

    test_case("Matrix2");
    {
        test_section("Matrix2()");
        {
            constexpr nnm::Matrix2f mat_default;
            ASSERT(mat_default.columns[0] == nnm::Vector2f(1.0f, 0.0f));
            ASSERT(mat_default.columns[1] == nnm::Vector2f(0.0f, 1.0f));
        }

        test_section("Matrix2(const Matrix2<Other>&)");
        {
            constexpr nnm::Matrix2d m1({ 1.0, -2.0 }, { 3.0, -4.5 });
            constexpr nnm::Matrix2f m2(m1);
            ASSERT(m2.columns[0] == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(m2.columns[1] == nnm::Vector2f(3.0f, -4.5f));
        }

        test_section("Matrix2(const Vector2&, const Vector2&)");
        {
            constexpr nnm::Matrix2f mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat_cols.columns[0] == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(mat_cols.columns[1] == nnm::Vector2f(-3.0f, 4.0f));
        }

        test_section("Matrix2(float, float, float, float)");
        {
            constexpr nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
            ASSERT(mat_elements.columns[0] == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(mat_elements.columns[1] == nnm::Vector2f(-3.0f, 4.0f));
        }

        test_section("all");
        {
            constexpr auto mat_all_three = nnm::Matrix2f::all(3.0f);
            ASSERT(mat_all_three.columns[0] == nnm::Vector2f(3.0f, 3.0f));
            ASSERT(mat_all_three.columns[1] == nnm::Vector2f(3.0f, 3.0f));
        }

        test_section("zero");
        {
            constexpr auto mat_zero = nnm::Matrix2f::zero();
            ASSERT(mat_zero.columns[0] == nnm::Vector2f::zero());
            ASSERT(mat_zero.columns[1] == nnm::Vector2f::zero());
        }

        test_section("one");
        {
            constexpr auto mat_one = nnm::Matrix2f::one();
            ASSERT(mat_one.columns[0] == nnm::Vector2f::one());
            ASSERT(mat_one.columns[1] == nnm::Vector2f::one());
        }

        test_section("identity");
        {
            constexpr auto mat_identity = nnm::Matrix2f::identity();
            ASSERT(mat_identity.columns[0] == nnm::Vector2f(1.0f, 0.0f));
            ASSERT(mat_identity.columns[1] == nnm::Vector2f(0.0f, 1.0f));
        }

        test_section("trace");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.trace();
            ASSERT(nnm::approx_equal(result, 5.0f));
        }

        test_section("determinant");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.determinant();
            ASSERT(nnm::approx_equal(result, -2.0f));
        }

        test_section("minor_at");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.minor_at(0, 0);
            ASSERT(result == 4.0f);
            ASSERT(mat.minor_at(0, 1) == -3.0f);
            ASSERT(mat.minor_at(1, 0) == -2.0f);
            ASSERT(mat.minor_at(1, 1) == 1.0f);
        }

        test_section("minor");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr nnm::Matrix2f minor = mat.minor();
            ASSERT(minor.approx_equal({ { 4.0f, -3.0f }, { -2.0f, 1.0f } }));
        }

        test_section("cofactor_at");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.cofactor_at(0, 0);
            ASSERT(result == 4.0f);
            ASSERT(mat.cofactor_at(0, 1) == 3.0f);
            ASSERT(mat.cofactor_at(1, 0) == 2.0f);
            ASSERT(mat.cofactor_at(1, 1) == 1.0f);
        }

        test_section("cofactor");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.cofactor();
            ASSERT(result == nnm::Matrix2f({ 4.0f, 3.0f }, { 2.0f, 1.0f }));
        }

        test_section("transpose");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.transpose();
            ASSERT(result == nnm::Matrix2f({ 1.0f, -3.0f }, { -2.0f, 4.0f }));
        }

        test_section("adjugate");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.adjugate();
            ASSERT(result == nnm::Matrix2f({ 4.0f, 2.0f }, { 3.0f, 1.0f }));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.unchecked_inverse();
            ASSERT(result.approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
        }

        test_section("inverse");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr std::optional<nnm::Matrix2f> mat_inv = mat.inverse();
            ASSERT(mat_inv.has_value());
            ASSERT(mat.inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
            ASSERT_FALSE(nnm::Matrix2f::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            constexpr nnm::Matrix2f mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat1.approx_equal({ { 1.00000001f, -1.9999999f }, { -3.00000001f, 3.99999999f } });
            ASSERT(result);
            ASSERT_FALSE(mat1.approx_equal({ { 1.1f, -1.9f }, { -3.1f, 3.9f } }));
        }

        test_section("approx_zero");
        {
            constexpr nnm::Matrix2f mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr nnm::Matrix2f mat2({ 0.00000001f, -0.00000001f }, { -0.00000001f, 0.00000001f });
            constexpr auto result = mat2.approx_zero();
            ASSERT(result);
            ASSERT_FALSE(mat1.approx_zero());
        }

        test_section("at");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(mat.at(0, 1) == -2.0f);
            ASSERT(mat.at(1, 0) == -3.0f);
            ASSERT(mat.at(1, 1) == 4.0f);
        }

        test_section("begin");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.begin() == &mat.columns[0].x);
        }

        test_section("end");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            ASSERT(mat.end() == &mat.columns[1].y + 1);
        }

        test_section("operator[]");
        {
            constexpr nnm::Matrix2f mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
            constexpr auto result = mat[0][0];
            ASSERT(result == 1.0f);
            ASSERT(mat[0][1] == -2.0f);
            ASSERT(mat[1][0] == -3.0f);
            ASSERT(mat[1][1] == 4.0f);
        }

        constexpr nnm::Matrix2f m1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr nnm::Matrix2f m2({ -4.0f, 3.0f }, { 2.0f, -1.0f });
        constexpr nnm::Matrix2f m3({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        constexpr nnm::Matrix2f m4({ 10.0f, -2.5f }, { 37.0f, -24.0f });

        test_section("operator==");
        {
            constexpr auto result = m1 == m3;
            ASSERT(result);
            ASSERT_FALSE(m1 == m2);
        }

        test_section("operator!=");
        {
            constexpr auto result = m1 != m3;
            ASSERT_FALSE(result);
            ASSERT(m1 != m2);
        }

        test_section("operator+");
        {
            constexpr auto result = m1 + m4;
            ASSERT(result.approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy += m4;
                return m1_copy;
            }();
            ASSERT(result.approx_equal({ { 11.0f, -4.5f }, { 34.0f, -20.0f } }));
        }

        test_section("operator-");
        {
            constexpr auto result = m1 - m4;
            ASSERT(result.approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy -= m4;
                return m1_copy;
            }();
            ASSERT(result.approx_equal({ { -9.0f, 0.5f }, { -40.0f, 28.0f } }));
        }

        test_section("operator*(const Matrix2&)");
        {
            constexpr auto result = m1 * m2;
            ASSERT(result == nnm::Matrix2f({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
            ASSERT((nnm::Matrix2f::identity() * nnm::Vector2(1.0f, 2.0f)).approx_equal(nnm::Vector2(1.0f, 2.0f)));
        }

        test_section("operator*=(const Matrix2&)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= m2;
                return m1_copy;
            }();
            ASSERT(result == nnm::Matrix2f({ -13.0f, 20.0f }, { 5.0f, -8.0f }));
        }

        test_section("operator*(const Vector2&)");
        {
            constexpr auto result = m1 * nnm::Vector2(1.0f, 2.0f);
            ASSERT(result.approx_equal(nnm::Vector2(-5.0f, 6.0f)));
        }

        test_section("operator*(float)");
        {
            constexpr auto result = m1 * 2.0f;
            ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator*(float, const Matrix2&)");
        {
            constexpr auto result = 2.0f * m1;
            ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= 2.0f;
                return m1_copy;
            }();
            ASSERT(result == nnm::Matrix2f({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        }

        test_section("operator/(float)");
        {
            constexpr auto result = m2 / 2.0f;
            ASSERT(result.approx_equal(nnm::Matrix2f({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
        }

        test_section("operator/(float, const Matrix2&)");
        {
            ASSERT((2.0f / m2).approx_equal(nnm::Matrix2f({ -0.5f, 0.666666666f }, { 1.0f, -2.0f })));
        }

        test_section("operator/=");
        {
            constexpr auto result = [=] {
                auto m2_copy = m2;
                m2_copy /= 2.0f;
                return m2_copy;
            }();
            ASSERT(result.approx_equal(nnm::Matrix2f({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
        }

        test_section("operator<");
        {
            constexpr auto result = m2 < m1;
            ASSERT(result);
            ASSERT_FALSE(m1 < m2);
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(m1);
            ASSERT(result);
            ASSERT_FALSE(static_cast<bool>(nnm::Matrix2f::zero()));
        }
    }

    test_case("Basis2");
    {
        test_section("Basis()");
        {
            constexpr nnm::Basis2f b;
            ASSERT(b.matrix == nnm::Matrix2f::identity());
        }

        test_section("Basis2(const Basis2<Other>&)");
        {
            constexpr nnm::Basis2d b1({ { 1.0, -2.0 }, { 3.0, -4.5 } });
            constexpr nnm::Basis2f b2(b1);
            ASSERT(b2.matrix.columns[0] == nnm::Vector2f(1.0f, -2.0f));
            ASSERT(b2.matrix.columns[1] == nnm::Vector2f(3.0f, -4.5f));
        }

        test_section("Basis2(const Matrix2&)");
        {
            constexpr auto m1 = nnm::Matrix2f::identity();
            constexpr auto b1 = nnm::Basis2(m1);
            ASSERT(b1 == nnm::Basis2f());
            ASSERT(b1.matrix == nnm::Matrix2f::identity());
        }

        test_section("from_rotation");
        {
            const auto b1 = nnm::Basis2f::from_rotation(0.0f);
            ASSERT(b1.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
            const auto b2 = nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f);
            ASSERT(b2.matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
            const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
            ASSERT(b3.matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
            const auto b4 = nnm::Basis2f::from_rotation(2.0f * nnm::pi<float>());
            ASSERT(b4.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
        }

        test_section("from_scale");
        {
            constexpr auto b1 = nnm::Basis2f::from_scale({ 2.0f, -3.0f });
            ASSERT(b1.matrix == nnm::Matrix2f({ 2.0f, 0.0f }, { 0.0f, -3.0f }));
        }

        test_section("from_shear_x");
        {
            constexpr auto b = nnm::Basis2f::from_shear_x(0.5f);
            ASSERT(b.matrix.approx_equal({ { 1.0f, 0.0f }, { 0.5f, 1.0f } }));
        }

        test_section("from_shear_y");
        {
            constexpr auto b = nnm::Basis2f::from_shear_y(-0.5f);
            ASSERT(b.matrix.approx_equal({ { 1.0f, -0.5f }, { 0.0f, 1.0f } }))
        }

        test_section("trace");
        {
            constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b.trace();
            ASSERT(result == b.matrix.trace());
        }

        test_section("determinant");
        {
            constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b.determinant();
            ASSERT(result == b.matrix.determinant());
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b.unchecked_inverse();
            ASSERT(result.matrix == b.matrix.unchecked_inverse());
        }

        test_section("inverse");
        {
            constexpr nnm::Basis2f b({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto inv = b.inverse();
            ASSERT(inv.has_value() && inv.value().matrix == b.matrix.inverse().value());
            ASSERT_FALSE(nnm::Basis2(nnm::Matrix2f::zero()).inverse().has_value());
        }

        test_section("valid");
        {
            constexpr nnm::Basis2f b1;
            constexpr auto b2 = nnm::Basis2(nnm::Matrix2f::zero());
            constexpr auto b3 = nnm::Basis2f({ { 1.0f, -2.0f }, { 2.0f, -4.0f } });
            constexpr auto result = b1.valid();
            ASSERT(result);
            ASSERT_FALSE(b2.valid());
            ASSERT_FALSE(b3.valid());
        }

        test_section("rotate");
        {
            constexpr nnm::Basis2f b1;
            ASSERT(b1.rotate(0.0f).approx_equal(b1));
            ASSERT(b1.rotate(nnm::pi<float>() / 2.0f).matrix.approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
            ASSERT(b1.rotate(-nnm::pi<float>() / 2.0f).matrix.approx_equal({ { 0.0f, -1.0f }, { 1.0f, 0.0f } }));
            ASSERT(b1.rotate(2.0f * nnm::pi<float>()).approx_equal(b1));
            constexpr auto b2 = nnm::Basis2f::from_scale({ 2.0f, 0.5f });
            const auto b2_rotated = b2.rotate(nnm::pi<float>() / 4.0f);
            ASSERT(b2_rotated.matrix.approx_equal({ { 1.41421f, 1.41421f }, { -0.353553f, 0.353553f } }));
        }

        test_section("rotate_local");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 1.96575f, -3.24747f }, { -2.47706f, 3.07473f } });
            ASSERT(b1.rotate_local(-nnm::pi<float>() / 9.0f).approx_equal(expected));
        }

        test_section("scale");
        {
            constexpr nnm::Basis2f b1;
            constexpr auto result = b1.scale({ 0.0f, 0.0f });
            ASSERT_FALSE(result.valid());
            ASSERT(b1.scale({ 0.0f, 0.0f }).matrix.approx_equal(nnm::Matrix2f::zero()));
            ASSERT(b1.scale({ 2.0f, 2.0f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 2.0f } }));
            ASSERT(b1.scale({ 2.0f, 0.5f }).matrix.approx_equal({ { 2.0f, 0.0f }, { 0.0f, 0.5f } }));
            ASSERT(b1.scale({ -1.0f, -1.0f }).matrix.approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
        }

        test_section("scale_local");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 2.0f, -4.0f }, { 1.5f, -2.0f } });
            constexpr auto result = b1.scale_local({ 2.0f, -0.5f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_x");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 0.0f, -2.0f }, { -1.0f, 4.0f } });
            constexpr auto result = b1.shear_x(0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 1.0f, -2.0f }, { -2.5f, 3.0f } });
            constexpr auto result = b1.shear_x_local(0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_y");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 1.0f, -2.5f }, { -3.0f, 5.5f } });
            constexpr auto result = b1.shear_y(-0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f expected({ { 2.5f, -4.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b1.shear_y_local(-0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("transform");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
            constexpr nnm::Basis2f expected({ { 7.75f, 17.5f }, { -16.25f, -55.0f } });
            constexpr auto result = b1.transform(b2);
            ASSERT(result.approx_equal(expected));
        }

        test_section("transform_local");
        {
            constexpr nnm::Basis2f b1({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr nnm::Basis2f b2({ { 0.75f, 20.0f }, { -3.5f, 1.25f } });
            constexpr nnm::Basis2f expected({ { -59.25f, 78.5f }, { -7.25f, 12.0f } });
            constexpr auto result = b1.transform_local(b2);
            ASSERT(result.approx_equal(expected));
        }

        test_section("approx_equal");
        {
            constexpr nnm::Basis2f b1;
            constexpr auto result
                = b1.approx_equal(nnm::Basis2f({ { 1.0000000f, 0.000000001f }, { -0.000000001f, 0.9999999f } }));
            ASSERT(result);
            const auto b2 = nnm::Basis2f::from_rotation(nnm::pi<float>());
            ASSERT_FALSE(b2.approx_equal(nnm::Basis2f()));
        }

        test_section("at");
        {
            constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b1.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
            ASSERT(b1.at(1, 1) == 4.0f);
            ASSERT(b1.at(0, 0) == 1.0f);
            ASSERT(b1.at(0, 1) == -2.0f);
            ASSERT(b1.at(1, 0) == -3.0f);
        }

        test_section("operator[]");
        {
            constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto result = b1[0];
            ASSERT(result == nnm::Vector2(1.0f, -2.0f));
            ASSERT(b1[1] == nnm::Vector2(-3.0f, 4.0f));
        }

        test_section("operator==");
        {
            constexpr nnm::Basis2f b1;
            constexpr nnm::Basis2f b2;
            const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
            constexpr auto result = b1 == b2;
            ASSERT(result);
            ASSERT_FALSE(b1 == b3);
        }

        test_section("operator!=");
        {
            constexpr nnm::Basis2f b1;
            constexpr nnm::Basis2f b2;
            const auto b3 = nnm::Basis2f::from_rotation(nnm::pi<float>());
            constexpr auto result = b1 != b2;
            ASSERT_FALSE(result);
            ASSERT(b1 != b3);
        }

        test_section("operator<");
        {
            constexpr auto b1 = nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } });
            constexpr auto b2 = nnm::Basis2f({ { -4.0f, 3.0f }, { 2.0f, -1.0f } });
            constexpr auto result = b2 < b1;
            ASSERT(result);
        }
    }

    test_case("Matrix3");
    {
        test_section("Matrix3()");
        {
            constexpr nnm::Matrix3f default_mat;
            ASSERT(default_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
            ASSERT(default_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
            ASSERT(default_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
        }

        test_section("Matrix3(const Matrix3<Other>&)");
        {
            constexpr nnm::Matrix3d m1({ 1.0, -2.0, 3.0 }, { 0.5, 0.75, -0.1 }, { 0.0, 2.0, -4.0 });
            constexpr nnm::Matrix3f m2(m1);
            ASSERT(m2.columns[0] == nnm::Vector3f(1.0f, -2.0f, 3.0f));
            ASSERT(m2.columns[1] == nnm::Vector3f(0.5f, 0.75f, -0.1f));
            ASSERT(m2.columns[2] == nnm::Vector3f(0.0f, 2.0f, -4.0f));
        }

        test_section("Matrix3(const Vector3&, const Vector3&, const Vector3&)");
        {
            constexpr nnm::Matrix3 cols(
                nnm::Vector3(1.0f, 2.0f, 3.0f), nnm::Vector3(-1.0f, -2.0f, -3.0f), nnm::Vector3(2.0f, 4.0f, 6.0f));
            ASSERT(cols.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(cols.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(cols.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section(
            "Matrix3(float, float, float, float, float, float, float, "
            "float, float)");
        {
            constexpr nnm::Matrix3 elems(1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, 2.0f, 4.0f, 6.0f);
            ASSERT(elems.columns[0] == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(elems.columns[1] == nnm::Vector3(-1.0f, -2.0f, -3.0f));
            ASSERT(elems.columns[2] == nnm::Vector3(2.0f, 4.0f, 6.0f));
        }

        test_section("all");
        {
            constexpr auto threes = nnm::Matrix3f::all(3.0f);
            ASSERT(threes.columns[0] == nnm::Vector3f::all(3.0f));
            ASSERT(threes.columns[1] == nnm::Vector3f::all(3.0f));
            ASSERT(threes.columns[2] == nnm::Vector3f::all(3.0f));
        }

        test_section("zero");
        {
            constexpr auto zeros = nnm::Matrix3f::zero();
            ASSERT(zeros.columns[0] == nnm::Vector3f::zero());
            ASSERT(zeros.columns[1] == nnm::Vector3f::zero());
            ASSERT(zeros.columns[2] == nnm::Vector3f::zero());
        }

        test_section("one");
        {
            constexpr auto ones = nnm::Matrix3f::one();
            ASSERT(ones.columns[0] == nnm::Vector3f::one());
            ASSERT(ones.columns[1] == nnm::Vector3f::one());
            ASSERT(ones.columns[2] == nnm::Vector3f::one());
        }

        test_section("identity");
        {
            constexpr auto identity_mat = nnm::Matrix3f::identity();
            ASSERT(identity_mat.columns[0] == nnm::Vector3(1.0f, 0.0f, 0.0f));
            ASSERT(identity_mat.columns[1] == nnm::Vector3(0.0f, 1.0f, 0.0f));
            ASSERT(identity_mat.columns[2] == nnm::Vector3(0.0f, 0.0f, 1.0f));
        }

        constexpr nnm::Matrix3f m1({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f });

        test_section("trace");
        {
            constexpr auto result = m1.trace();
            ASSERT(nnm::approx_equal(result, 5.0f));
        }

        test_section("determinant");
        {
            constexpr auto result = m1.determinant();
            ASSERT(nnm::approx_equal(result, 64.0f));
            ASSERT(nnm::approx_equal(nnm::Matrix3f::identity().determinant(), 1.0f));
            ASSERT(nnm::approx_equal(nnm::Matrix3f::zero().determinant(), 0.0f));
        }

        test_section("minor_matrix_at");
        {
            constexpr auto result = m1.minor_matrix_at(0, 0);
            ASSERT(result.approx_equal({ { -2.0f, -1.0f }, { -4.0f, 6.0f } }));
            ASSERT(m1.minor_matrix_at(1, 2).approx_equal({ { 1.0f, 2.0f }, { 2.0f, -4.0f } }));
        }

        test_section("minor_at");
        {
            constexpr nnm::Matrix3f expected({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
            constexpr auto result = m1.minor_at(0, 0);
            ASSERT(nnm::approx_equal(result, expected.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.minor_at(1, 2), expected.at(1, 2)));
        }

        test_section("minor");
        {
            constexpr nnm::Matrix3f expected({ -16.0f, -16.0f, 16.0f }, { 24.0f, 0.0f, -8.0f }, { 4.0f, 8.0f, 4.0f });
            constexpr auto result = m1.minor();
            ASSERT(result.approx_equal(expected));
        }

        test_section("cofactor_at");
        {
            constexpr nnm::Matrix3f expected({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
            constexpr auto result = m1.cofactor_at(0, 0);
            ASSERT(nnm::approx_equal(result, expected.at(0, 0)));
            ASSERT(nnm::approx_equal(m1.cofactor_at(1, 2), expected.at(1, 2)));
        }

        test_section("cofactor");
        {
            constexpr nnm::Matrix3f expected({ -16.0f, 16.0f, 16.0f }, { -24.0f, 0.0f, 8.0f }, { 4.0f, -8.0f, 4.0f });
            constexpr auto result = m1.cofactor();
            ASSERT(result.approx_equal(expected));
        }

        test_section("transpose");
        {
            constexpr nnm::Matrix3f expected({ 1.0f, -3.0f, 2.0f }, { 2.0f, -2.0f, -4.0f }, { 3.0f, -1.0f, 6.0f });
            constexpr auto result = m1.transpose();
            ASSERT(result == expected);
        }

        test_section("adjugate");
        {
            constexpr nnm::Matrix3f expected({ -16.0f, -24.0f, 4.0f }, { 16.0f, 0.0f, -8.0f }, { 16.0f, 8.0f, 4.0f });
            constexpr auto result = m1.adjugate();
            ASSERT(result.approx_equal(expected));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Matrix3f expected(
                { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
            constexpr auto result = m1.unchecked_inverse();
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Matrix3f expected(
                { -0.25f, -0.375f, 0.0625f }, { 0.25f, 0.0f, -0.125f }, { 0.25f, 0.125f, 0.0625f });
            constexpr auto result = m1.inverse();
            ASSERT(result.has_value());
            ASSERT(result.value().approx_equal(expected));
            ASSERT_FALSE(nnm::Matrix3f::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            constexpr nnm::Matrix3f almost_ident(
                { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
            constexpr nnm::Matrix3f almost_zero(
                { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
            constexpr auto result = nnm::Matrix3f::identity().approx_equal(almost_ident);
            ASSERT(result);
            ASSERT_FALSE(almost_zero.approx_equal(almost_ident));
        }

        test_section("approx_zero");
        {
            constexpr nnm::Matrix3f almost_ident(
                { 0.9999999f, 0.000001f, 0.0f }, { -0.00000001f, 1.00000001f, 0.0f }, { 0.0f, -0.000000001f, 1.0f });
            constexpr nnm::Matrix3f almost_zero(
                { 0.0f, 0.000000001f, -0.00000001f }, { -0.00000001f, 0.0f, 0.00000001f }, { 0.0f, 0.0f, 0.0f });
            constexpr auto result = nnm::Matrix3f::zero().approx_zero();
            ASSERT(result);
            ASSERT_FALSE(almost_ident.approx_zero());
            ASSERT(almost_zero.approx_zero());
        }

        test_section("at");
        {
            constexpr auto result = m1.at(0);
            ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1.at(1) == nnm::Vector3(-3.0f, -2.0f, -1.0f));
            ASSERT(m1.at(0, 0) == 1.0f);
            ASSERT(m1.at(1, 2) == -1.0f);
        }

        test_section("begin");
        {
            ASSERT(m1.begin() == &m1.columns[0].x);
        }

        test_section("end");
        {
            ASSERT(m1.end() == &m1.columns[2].z + 1);
        }

        test_section("operator[]");
        {
            constexpr auto result = m1[0];
            ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(m1[1] == nnm::Vector3(-3.0f, -2.0f, -1.0f));
        }

        test_section("operator==");
        {
            constexpr auto result
                = m1 == nnm::Matrix3f({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f });
            ASSERT(result);
            ASSERT_FALSE(m1 == nnm::Matrix3f::identity());
        }

        test_section("operator!=");
        {
            constexpr auto result = m1 != nnm::Matrix3f::identity();
            ASSERT(result);
            ASSERT_FALSE(m1 != nnm::Matrix3f({ 1.0f, 2.0f, 3.0f }, { -3.0f, -2.0f, -1.0f }, { 2.0f, -4.0f, 6.0f }));
        }

        constexpr nnm::Matrix3f m2({ 3.0f, -6.0f, -9.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 2.0f, 10.0f });

        test_section("operator+");
        {
            constexpr nnm::Matrix3f expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
            constexpr auto result = m1 + m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy += m2;
                return m1_copy;
            }();
            constexpr nnm::Matrix3f expected({ 4.0f, -4.0f, -6.0f }, { -2.0f, -2.0f, -1.0f }, { 1.0f, -2.0f, 16.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator-");
        {
            constexpr nnm::Matrix3f expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
            constexpr auto result = m1 - m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy -= m2;
                return m1_copy;
            }();
            constexpr nnm::Matrix3f expected({ -2.0f, 8.0f, 12.0f }, { -4.0f, -2.0f, -1.0f }, { 3.0f, -6.0f, -4.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(const Matrix3&)");
        {
            constexpr nnm::Matrix3f expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
            constexpr auto result = m1 * m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*=(const Matrix3&)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= m2;
                return m1_copy;
            }();
            constexpr nnm::Matrix3f expected({ 3.0f, 54.0f, -39.0f }, { 1.0f, 2.0f, 3.0f }, { 13.0f, -46.0f, 55.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(const Vector3&)");
        {
            constexpr nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
            constexpr auto result = m1 * v1;
            ASSERT(result.approx_equal({ 13.0f, -6.0f, 23.0f }));
        }

        test_section("operator*(float)");
        {
            constexpr nnm::Matrix3f expected(
                { 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            constexpr auto result = m1 * 5.0f;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(float, const Matrix3&)");
        {
            constexpr nnm::Matrix3f expected(
                { 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            constexpr auto result = 5.0f * m1;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= 5.0f;
                return m1_copy;
            }();
            constexpr nnm::Matrix3f expected(
                { 5.0f, 10.0f, 15.0f }, { -15.0f, -10.0f, -5.0f }, { 10.0f, -20.0f, 30.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator/(float)");
        {
            constexpr nnm::Matrix3f expected(
                { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
            constexpr auto result = m1 / 2.0f;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator/(float, const Matrix3&)");
        {
            constexpr nnm::Matrix3f expected(
                { 2.0f, 1.0f, 0.666666f }, { -0.6666666f, -1.0f, -2.0f }, { 1.0f, -0.5f, 0.3333333f });
            constexpr auto result = 2.0f / m1;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator/=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy /= 2.0f;
                return m1_copy;
            }();
            constexpr nnm::Matrix3f expected(
                { 0.5f, 1.0f, 3.0f / 2.0f }, { -3.0f / 2.0f, -1.0f, -0.5f }, { 1.0f, -2.0f, 3.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator<");
        {
            constexpr auto result = m1 < nnm::Matrix3f::identity();
            ASSERT_FALSE(result);
            ASSERT(m1 < nnm::Matrix3f::all(10.0f));
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(nnm::Matrix3f::zero());
            ASSERT_FALSE(result);
            ASSERT(static_cast<bool>(nnm::Matrix3f::identity()));
        }
    }

    test_case("Transform2");
    {
        test_section("Transform2");
        {
            constexpr nnm::Transform2f default_transform;
            ASSERT(default_transform.matrix == nnm::Matrix3f::identity());
        }

        test_section("Transform2(const Transform2<Other>&)");
        {
            constexpr nnm::Transform2d t1({ { 1.0, 2.0, 3.0 }, { -0.5, -0.75, 0.1 }, { 4.0, 28.0, 100.0 } });
            constexpr nnm::Transform2f t2(t1);
            ASSERT(t2.matrix.columns[0] == nnm::Vector3f(1.0f, 2.0f, 3.0f));
            ASSERT(t2.matrix.columns[1] == nnm::Vector3f(-0.5f, -0.75f, 0.1f));
            ASSERT(t2.matrix.columns[2] == nnm::Vector3f(4.0f, 28.0f, 100.0f));
        }

        test_section("Transform2(const Matrix3&)");
        {
            constexpr nnm::Transform2 transform_matrix(nnm::Matrix3f::all(3.0f));
            ASSERT(transform_matrix.matrix == nnm::Matrix3f::all(3.0f));
        }

        test_section("from_basis_translation");
        {
            constexpr nnm::Basis2f basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
            constexpr nnm::Vector2 pos(-1.0f, 2.0f);
            constexpr auto transform_basis_pos = nnm::Transform2f::from_basis_translation(basis, pos);
            constexpr nnm::Matrix3f expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
            ASSERT(transform_basis_pos.matrix.approx_equal(expected));
        }

        test_section("from_basis");
        {
            constexpr nnm::Basis2f basis({ { 1.0f, 2.0f }, { 3.0f, 4.0f } });
            constexpr nnm::Matrix3f expected({ 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            constexpr auto transform_basis = nnm::Transform2f::from_basis(basis);
            ASSERT(transform_basis.matrix.approx_equal(expected));
        }

        test_section("from_translation");
        {
            constexpr nnm::Vector2 pos(-1.0f, 2.0f);
            constexpr auto transform_pos = nnm::Transform2f::from_translation(pos);
            constexpr nnm::Matrix3f expected({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 2.0f, 1.0f });
            ASSERT(transform_pos.matrix.approx_equal(expected));
        }

        test_section("from_rotation");
        {
            const auto transform_rot = nnm::Transform2f::from_rotation(nnm::pi<float>() / 2.0f);
            constexpr nnm::Matrix3f expected({ 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            ASSERT(transform_rot.matrix.approx_equal(expected));
        }

        test_section("from_scale");
        {
            constexpr auto transform_scale = nnm::Transform2f::from_scale({ -2.0f, 3.0f });
            constexpr nnm::Matrix3f expected({ -2.0f, 0.0f, 0.0f }, { 0.0f, 3.0f, 0.0f }, { 0.0f, 0.0f, 1.0f });
            ASSERT(transform_scale.matrix.approx_equal(expected));
        }

        test_section("from_shear_x");
        {
            constexpr auto t = nnm::Transform2f::from_shear_x(0.5f);
            constexpr nnm::Transform2f expected({ { 1.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_shear_y");
        {
            constexpr auto t = nnm::Transform2f::from_shear_y(-0.5f);
            constexpr nnm::Transform2f expected({ { 1.0f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("trace");
        {
            constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr auto result = t.trace();
            ASSERT(nnm::approx_equal(result, 12.0f));
        }

        test_section("determinant");
        {
            constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr auto result = t.determinant();
            ASSERT(nnm::approx_equal(result, -54.925f));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { -0.254893f, -0.0345926f, 0.819299f },
                  { -0.559854f, -0.00455166f, 0.37096f },
                  { 0.270369f, 0.0509786f, -0.154756f } });
            constexpr auto result = t.unchecked_inverse();
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Transform2f t({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { -0.254893f, -0.0345926f, 0.819299f },
                  { -0.559854f, -0.00455166f, 0.37096f },
                  { 0.270369f, 0.0509786f, -0.154756f } });
            constexpr auto result = t.inverse();
            ASSERT(result.has_value() && result.value().approx_equal(expected));
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).inverse().has_value());
        }

        test_section("valid");
        {
            constexpr auto result = nnm::Transform2(nnm::Matrix3f::identity()).valid();
            ASSERT(result);
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).valid());
        }

        test_section("affine");
        {
            constexpr auto result = nnm::Transform2(nnm::Matrix3f::identity()).affine();
            ASSERT(result);
            ASSERT_FALSE(nnm::Transform2(nnm::Matrix3f::zero()).affine());
        }

        constexpr nnm::Transform2f t1({ { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { -1.0f, 2.0f, 1.0f } });

        test_section("basis");
        {
            constexpr auto result = t1.basis();
            ASSERT(result == nnm::Basis2f({ { 1.0f, -2.0f }, { -3.0f, 4.0f } }));
        }

        test_section("translation");
        {
            constexpr auto result = t1.translation();
            ASSERT(result == nnm::Vector2(-1.0f, 2.0f));
        }

        test_section("translate");
        {
            constexpr nnm::Transform2f expected(
                { { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 0.0f, -0.5f, 1.0f } });
            constexpr nnm::Transform2f t2 = t1.translate({ 1.0f, -2.5f });
            ASSERT(t2.approx_equal(expected));
        }

        test_section("translate_local");
        {
            constexpr nnm::Transform2f expected(
                { { 1.0f, -2.0f, 0.0f }, { -3.0f, 4.0f, 0.0f }, { 7.5f, -10.0f, 1.0f } });
            constexpr nnm::Transform2f t2 = t1.translate_local({ 1.0f, -2.5f });
            ASSERT(t2.approx_equal(expected));
        }

        test_section("rotate");
        {
            constexpr auto t = nnm::Transform2f::from_basis_translation(nnm::Basis2f(), { 1.0f, -2.0f });
            const auto t_rotated = t.rotate(nnm::pi<float>() / 2.0f);
            const auto t_expected = nnm::Transform2f::from_basis_translation(
                nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f), { 2.0f, 1.0f });
            ASSERT(t_rotated.approx_equal(t_expected));
        }

        test_section("rotate_local");
        {
            constexpr auto t = nnm::Transform2f::from_basis_translation(nnm::Basis2f(), { 1.0f, -2.0f });
            const auto t_rotated = t.rotate_local(nnm::pi<float>() / 2.0f);
            const auto t_expected = nnm::Transform2f::from_basis_translation(
                nnm::Basis2f::from_rotation(nnm::pi<float>() / 2.0f), { 1.0f, -2.0f });
            ASSERT(t_rotated.approx_equal(t_expected));
        }

        constexpr nnm::Transform2f t2 { { { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, -2.0f, 1.0f } } };
        constexpr nnm::Transform2f t3 { { { -1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { -3.0f, 4.0f, 1.0f } } };

        test_section("scale");
        {
            constexpr auto t_scaled = t2.scale({ 2.0f, -3.0f });
            constexpr auto t_expected
                = nnm::Transform2f::from_basis_translation(t2.basis().scale({ 2.0f, -3.0f }), { 2.0f, 6.0f });
            ASSERT(t_scaled.approx_equal(t_expected));
        }

        test_section("scale_local");
        {
            constexpr auto t_scaled = t2.scale_local({ 2.0f, -3.0f });
            constexpr auto t_expected
                = nnm::Transform2f::from_basis_translation(t2.basis().scale_local({ 2.0f, -3.0f }), { 1.0f, -2.0f });
            ASSERT(t_scaled.approx_equal(t_expected));
        }

        test_section("shear_x");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { 0.0f, -2.0f, 3.0f }, { -1.0f, 4.0f, -2.0f }, { 0.0f, 2.0f, 1.0f } });
            constexpr auto result = t4.shear_x(0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { 1.0f, -2.0f, 3.0f }, { -2.5f, 3.0f, -0.5f }, { -1.0f, 2.0f, 1.0f } });
            constexpr auto result = t4.shear_x_local(0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_y");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { 1.0f, -2.5f, 3.0f }, { -3.0f, 5.5f, -2.0f }, { -1.0f, 2.5f, 1.0f } });
            constexpr auto result = t4.shear_y(-0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            constexpr nnm::Transform2f expected(
                { { 2.5f, -4.0f, 4.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.0f } });
            constexpr auto result = t4.shear_y_local(-0.5f);
            ASSERT(result.approx_equal(expected));
        }

        test_section("transform");
        {
            constexpr auto t_transformed = t2.transform(t3);
            const auto t_expected = nnm::Transform2f::from_basis_translation(
                nnm::Basis2f::from_rotation(3.0f * nnm::pi<float>() / 2.0f), { -4.0f, 6.0f });
            ASSERT(t_transformed.approx_equal(t_expected));
        }

        test_section("transform_local");
        {
            constexpr auto t_transformed = t2.transform_local(t3);
            const auto t_expected = nnm::Transform2f::from_basis_translation(
                nnm::Basis2f::from_rotation(3.0f * nnm::pi<float>() / 2.0f), { -3.0f, -5.0f });
            ASSERT(t_transformed.approx_equal(t_expected));
        }

        test_section("approx_equal");
        {
            constexpr nnm::Transform2f t(
                { { 0.999999f, 0.0000001f, -0.0000001f }, { 0.0f, 1.00000001f, 0.0f }, { 0.0f, -0.0000001f, 1.0f } });
            constexpr auto result = t.approx_equal(nnm::Transform2f());
            ASSERT(result);
        }

        test_section("at");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            constexpr auto result = t4.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(t4.at(1, 2) == -2.0f);
            ASSERT(t4.at(2, 2) == 1.5f);
        }

        test_section("operator[]");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            constexpr auto result = t4[0];
            ASSERT(result == nnm::Vector3(1.0f, -2.0f, 3.0f));
            ASSERT(t4[1] == nnm::Vector3(-3.0f, 4.0f, -2.0f));
            ASSERT(t4[2] == nnm::Vector3(-1.0f, 2.0f, 1.5f));
        }

        test_section("operator==");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            constexpr nnm::Transform2f t6 = t4;
            constexpr auto result = t4 == t6;
            ASSERT(result);
            ASSERT_FALSE(t4 == t5);
        }

        test_section("operator!=");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            constexpr nnm::Transform2f t6 = t4;
            constexpr auto result = t4 != t5;
            ASSERT(result);
            ASSERT_FALSE(t4 != t6);
        }

        test_section("operator<");
        {
            constexpr nnm::Transform2f t4({ { 1.0f, -2.0f, 3.0f }, { -3.0f, 4.0f, -2.0f }, { -1.0f, 2.0f, 1.5f } });
            constexpr nnm::Transform2f t5({ { -1.0f, -20.0f, 3.0f }, { -35.0f, 4.0f, 2.0f }, { 0.0f, 2.0f, 1.5f } });
            constexpr auto result = t5 < t4;
            ASSERT(result);
            ASSERT_FALSE(t4 < t5);
        }
    }

    test_case("Basis3");
    {
        test_section("Basis3()");
        {
            constexpr nnm::Basis3f b1;
            ASSERT(b1.matrix == nnm::Matrix3f::identity());
        }

        test_section("Basis3(const Basis3<Other>&)");
        {
            constexpr nnm::Basis3d b1({ { 1.0, 2.0, 3.0 }, { -0.5, -0.75, 0.1 }, { 2.0, 88.0, -101.0 } });
            constexpr nnm::Basis3f b2(b1);
            ASSERT(b2.matrix.columns[0] == nnm::Vector3f(1.0f, 2.0f, 3.0f));
            ASSERT(b2.matrix.columns[1] == nnm::Vector3f(-0.5f, -0.75f, 0.1f));
            ASSERT(b2.matrix.columns[2] == nnm::Vector3f(2.0f, 88.0f, -101.0f));
        }

        test_section("Basis3(const Matrix3&)");
        {
            constexpr nnm::Matrix3f m1 { { 1.0f, 2.0f, 0.0f }, { 3.0f, 4.0f, 0.0f }, { 3.0f, -8.0f, 1.0f } };
            constexpr nnm::Basis3f b2(m1);
            ASSERT(b2.matrix == m1);
        }

        test_section("from_rotation_axis_angle");
        {
            auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, nnm::pi<float>());
            ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }))
            auto b2 = nnm::Basis3f::from_rotation_axis_angle({ 2.0f, 0.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(b2.matrix.approx_equal(
                { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.707107f, 0.707107f }, { 0.0f, -0.707107f, 0.707107f } }));
        }

        test_section("from_rotation_quaternion");
        {
            constexpr auto b = nnm::Basis3f::from_rotation_quaternion(
                nnm::Quaternion(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f));
            constexpr nnm::Basis3f expected(
                { { 0.9980918f, -0.0213389f, -0.0579437f },
                  {
                      0.0335516f,
                      0.9751930f,
                      0.2187989f,
                  },
                  { 0.0518374f, -0.2203254f, 0.9740480f } });
            ASSERT(b.approx_equal(expected));
        }

        test_section("from_scale");
        {
            constexpr auto b1 = nnm::Basis3f::from_scale({ -1.0f, 2.0f, 3.0f });
            ASSERT(b1.matrix.approx_equal({ { -1.0f, 0.0f, 0.0f }, { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.0f, 3.0f } }));
        }

        test_section("from_shear_x");
        {
            constexpr auto b1 = nnm::Basis3f::from_shear_x(0.5f, -0.1f);
            ASSERT(b1.matrix.approx_equal({ { 1.0f, 0.5f, -0.1f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }));
        }

        test_section("from_shear_y");
        {
            constexpr auto b1 = nnm::Basis3f::from_shear_y(0.5f, -0.1f);
            ASSERT(
                b1.approx_equal(nnm::Basis3f({ { 1.0f, 0.0f, 0.0f }, { 0.5f, 1.0f, -0.1f }, { 0.0f, 0.0f, 1.0f } })));
        }

        test_section("from_shear_z");
        {
            constexpr auto b1 = nnm::Basis3f::from_shear_z(0.5f, -0.1f);
            ASSERT(
                b1.approx_equal(nnm::Basis3f({ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, -0.1f, 1.0f } })));
        }

        test_section("trace");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr auto result = b.trace();
            ASSERT(nnm::approx_equal(result, 12.0f));
        }

        test_section("determinant");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr auto result = b.determinant();
            ASSERT(nnm::approx_equal(result, -54.925f));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Basis3f expected(
                { { -0.254893f, -0.0345926f, 0.819299f },
                  { -0.559854f, -0.00455166f, 0.37096f },
                  { 0.270369f, 0.0509786f, -0.154756f } });
            constexpr auto result = b.unchecked_inverse();
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Basis3f expected(
                { { -0.254893f, -0.0345926f, 0.819299f },
                  { -0.559854f, -0.00455166f, 0.37096f },
                  { 0.270369f, 0.0509786f, -0.154756f } });
            constexpr auto result = b.inverse();
            ASSERT(result.has_value() && result.value().approx_equal(expected));
            ASSERT_FALSE(nnm::Basis3(nnm::Matrix3f::zero()).inverse().has_value());
        }

        test_section("valid");
        {
            constexpr nnm::Basis3 b1(nnm::Matrix3f::zero());
            constexpr auto result = b1.valid();
            ASSERT_FALSE(result);
            nnm::Basis3f b2;
            ASSERT(b2.valid());
            nnm::Basis3f b3({ { 1.0f, 2.0f, 3.0f }, { 2.0f, 4.0f, 6.0f }, { 3.0f, 6.0f, 9.0f } });
            ASSERT_FALSE(b3.valid());
            nnm::Basis3f b4({ { 1.0f, 2.0f, 3.0f }, { 3.0f, 1.0f, 3.0f }, { -2.0f, 3.0f, 1.0f } });
            ASSERT(b4.valid());
        }

        test_section("rotate_axis_angle");
        {
            auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 1.0f, 0.0f, 0.0f }, nnm::pi<float>() / 2.0f);
            nnm::Basis3 b1_rot = b1.rotate_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi<float>() / 4.0f);
            ASSERT(b1_rot.matrix.approx_equal(
                { { 0.707107f, 0.0f, -0.707107f }, { 0.707107f, 0.0f, 0.707107f }, { 0.0f, -1.0f, 0.0f } }));
        }

        test_section("rotate_axis_angle_local");
        {
            auto b1 = nnm::Basis3f::from_rotation_axis_angle({ 0.0f, 1.0f, 0.0f }, -nnm::pi<float>() / 4.0f);
            nnm::Basis3 b1_rot = b1.rotate_axis_angle_local({ 0.0f, 0.0f, 3.0f }, nnm::pi<float>() / 2.0f);
            ASSERT(b1_rot.matrix.approx_equal(
                { { 0.0f, 1.0f, 0.0f }, { -0.707107f, 0.0f, -0.707107f }, { -0.707107f, 0.0f, 0.707107f } }))
        }

        test_section("rotate_quaternion");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
            constexpr nnm::Basis3f expected(
                { { 0.956907f, -2.08189f, -0.0085175f },
                  { 0.623695f, 5.36143f, 21.7124f },
                  { 1.54226f, -0.447372f, 0.843373f } });
            constexpr auto result = b.rotate_quaternion(q);
            ASSERT(result.approx_equal(expected));
        }

        test_section("rotate_quaternion_local");
        {
            constexpr nnm::Basis3f b({ { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } });
            constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
            constexpr nnm::Basis3f expected(
                { { 0.92718f, -2.19798f, 0.0143242f },
                  { -0.369645f, 9.64107f, 19.7394f },
                  { 1.67815f, -2.50174f, -3.40654f } });
            constexpr auto result = b.rotate_quaternion_local(q);
            ASSERT(result.approx_equal(expected));
        }

        test_section("scale");
        {
            constexpr nnm::Basis3f b1 { { { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } } };
            constexpr nnm::Basis3f b1_scaled = b1.scale({ 2.0f, -1.0f, 0.4f });
            ASSERT(
                b1_scaled.matrix.approx_equal({ { 0.0f, 0.0f, -0.4f }, { 0.0f, -1.0f, 0.0f }, { 2.0f, 0.0f, 0.0f } }));
        }

        test_section("scale_local");
        {
            constexpr nnm::Basis3f b1 {
                { { 0.707106769f, -0.707106769f, 0.0f }, { 0.707106769f, 0.707106769f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
            };
            constexpr nnm::Basis3f b1_scaled = b1.scale_local({ 0.6f, 2.0f, -1.5f });
            ASSERT(b1_scaled.matrix.approx_equal(
                { { 0.424264f, -0.424264f, 0.0f }, { 1.41421f, 1.41421f, 0.0f }, { 0.0f, 0.0f, -1.5f } }));
        }

        test_section("shear_x");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } } };
            constexpr auto b1_sheared = b1.shear_x(1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, -0.5f, 0.4f }, { -0.75f, 8.875f, 20.075f }, { 1.5f, 2.05f, 0.85f } }));
        }

        test_section("shear_x_local");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 0.5f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } } };
            constexpr auto b1_sheared = b1.shear_x_local(1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { -0.275f, 13.02f, 30.4f }, { -0.75f, 10.0f, 20.0f }, { 1.5f, -0.2f, 1.0f } }));
        }

        test_section("shear_y");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
            constexpr auto b1_sheared = b1.shear_y(-1.5f, -0.1f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 4.0f, -2.0f, 3.2f }, { -11.5f, 5.0f, -6.5f }, { -1.5f, 1.0f, -3.1f } }));
        }

        test_section("shear_y_local");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
            constexpr auto b1_sheared = b1.shear_y_local(1.3f, 0.3f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, -2.0f, 3.0f }, { -2.7f, 2.7f, -3.0f }, { 0.0f, 1.0f, -3.0f } }))
        }

        test_section("shear_z");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
            constexpr auto b1_sheared = b1.shear_z(1.2f, -0.8f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 4.6f, -4.4f, 3.0f }, { -11.2f, 9.8f, -6.0f }, { -3.6f, 3.4f, -3.0f } }))
        }

        test_section("shear_z_local");
        {
            constexpr nnm::Basis3f b1 { { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { 0.0f, 1.0f, -3.0f } } };
            constexpr auto b1_sheared = b1.shear_z_local(-1.2f, 0.8f);
            ASSERT(b1_sheared.matrix.approx_equal(
                { { 1.0f, -2.0f, 3.0f }, { -4.0f, 5.0f, -6.0f }, { -4.4f, 7.4f, -11.4f } }));
        }

        test_section("transform");
        {
            constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
            constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
            constexpr auto b3 = b1.transform(b2);
            ASSERT(
                b3.matrix.approx_equal({ { 34.0f, 11.5f, -111.0f }, { 2.0f, -2.8f, 5.5f }, { 13.0f, 4.25f, -35.0f } }))
        }

        test_section("transform_local");
        {
            constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
            constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });
            constexpr auto b3 = b1.transform_local(b2);
            ASSERT(b3.matrix.approx_equal({ { 5.0f, -0.5f, 6.15f }, { 0.5f, -4.0f, 0.2f }, { -38.5f, 14.0f, -4.8f } }))
        }

        test_section("approx_equal");
        {
            constexpr nnm::Basis3f b1(
                { { 1.000001f, -0.00001f, 0.0f }, { 0.0f, 0.99999999f, 0.000001f }, { 0.0f, 0.0f, 1.0f } });
            constexpr auto result = b1.approx_equal(nnm::Basis3f());
            ASSERT(result);
        }

        constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { 2.0f, -3.0f, 0.1f }, { 1.5f, 0.0f, 1.0f } });
        constexpr nnm::Basis3f b2({ { 2.0f, 1.5f, 0.0f }, { 1.0f, 2.0f, -3.0f }, { 10.0f, 2.0f, -35.0f } });

        test_section("at");
        {
            constexpr auto result = b1.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(b1.at(1, 2) == 0.1f);
            ASSERT(b2.at(2, 2) == -35.0f);
        }

        test_section("operator[]");
        {
            constexpr auto result = b1[0];
            ASSERT(result == nnm::Vector3(1.0f, 2.0f, 3.0f));
            ASSERT(b1[1] == nnm::Vector3(2.0f, -3.0f, 0.1f));
            ASSERT(b2[2] == nnm::Vector3(10.0f, 2.0f, -35.0f));
        }

        test_section("operator==");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = b1 == b1;
            ASSERT(result);
            ASSERT_FALSE(b1 == b2);
        }

        test_section("operator!=");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = b1 != b1;
            ASSERT_FALSE(result);
            ASSERT(b1 != b2);
        }

        test_section("operator<");
        {
            constexpr auto result = b1 < b2;
            ASSERT(result);
            ASSERT_FALSE(b2 < b1);
        }
    }

    test_case("Matrix4");
    {
        test_section("Matrix4()");
        {
            constexpr nnm::Matrix4f m1;
            ASSERT(m1.columns[0] == nnm::Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
            ASSERT(m1.columns[1] == nnm::Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
            ASSERT(m1.columns[2] == nnm::Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
            ASSERT(m1.columns[3] == nnm::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
        }

        test_section("Matrix4(const Matrix4<Other>&)");
        {
            constexpr nnm::Matrix4d m1(
                { 1.0, 2.0, 3.0, 4.0 },
                { -0.5, 0.75, 0.6, 0.1 },
                { -100.0, -88.0, 28.0, 0.0 },
                { 1.0, 29.0, -89.0, 67.0 });
            constexpr nnm::Matrix4f m2(m1);
            ASSERT(m2.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
            ASSERT(m2.columns[1] == nnm::Vector4f(-0.5f, 0.75f, 0.6f, 0.1f));
            ASSERT(m2.columns[2] == nnm::Vector4f(-100.0f, -88.0f, 28.0f, 0.0f));
            ASSERT(m2.columns[3] == nnm::Vector4f(1.0f, 29.0f, -89.0f, 67.0f));
        }

        test_section(
            "Matrix4(const Vector4&, const Vector4&, const Vector4&, "
            "const Vector4&)");
        {
            constexpr nnm::Matrix4f m3 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                         { -1.0f, -2.0f, -3.0f, -4.0f },
                                         { 4.0f, 3.0f, 2.0f, 1.0f },
                                         { -4.0f, -3.0f, -2.0f, -1.0f } };
            ASSERT(m3.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
            ASSERT(m3.columns[1] == nnm::Vector4f(-1.0f, -2.0f, -3.0f, -4.0f));
            ASSERT(m3.columns[2] == nnm::Vector4f(4.0f, 3.0f, 2.0f, 1.0f));
            ASSERT(m3.columns[3] == nnm::Vector4f(-4.0f, -3.0f, -2.0f, -1.0f));
        }

        test_section(
            "Matrix4(float, float, float, float, float, float, float, "
            "float, float, float, float, float, "
            "float, float, float, float)");
        {
            constexpr nnm::Matrix4 m2 { 1.0f, 2.0f, 3.0f, 4.0f, -1.0f, -2.0f, -3.0f, -4.0f,
                                        4.0f, 3.0f, 2.0f, 1.0f, -4.0f, -3.0f, -2.0f, -1.0f };
            ASSERT(m2.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
            ASSERT(m2.columns[1] == nnm::Vector4f(-1.0f, -2.0f, -3.0f, -4.0f));
            ASSERT(m2.columns[2] == nnm::Vector4f(4.0f, 3.0f, 2.0f, 1.0f));
            ASSERT(m2.columns[3] == nnm::Vector4f(-4.0f, -3.0f, -2.0f, -1.0f));
        }

        test_section("all");
        {
            constexpr auto m1 = nnm::Matrix4f::all(3.0f);
            ASSERT(m1.columns[0] == nnm::Vector4f::all(3.0f));
            ASSERT(m1.columns[1] == nnm::Vector4f::all(3.0f));
            ASSERT(m1.columns[2] == nnm::Vector4f::all(3.0f));
            ASSERT(m1.columns[3] == nnm::Vector4f::all(3.0f));
        }

        test_section("zero");
        {
            constexpr auto m2 = nnm::Matrix4f::zero();
            ASSERT(m2.columns[0] == nnm::Vector4f::zero());
            ASSERT(m2.columns[1] == nnm::Vector4f::zero());
            ASSERT(m2.columns[2] == nnm::Vector4f::zero());
            ASSERT(m2.columns[3] == nnm::Vector4f::zero());
        }

        test_section("one");
        {
            constexpr auto m3 = nnm::Matrix4f::one();
            ASSERT(m3.columns[0] == nnm::Vector4f::one());
            ASSERT(m3.columns[1] == nnm::Vector4f::one());
            ASSERT(m3.columns[2] == nnm::Vector4f::one());
            ASSERT(m3.columns[3] == nnm::Vector4f::one());
        }

        test_section("identity");
        {
            constexpr auto m4 = nnm::Matrix4f::identity();
            ASSERT(m4.columns[0] == nnm::Vector4f(1.0f, 0.0f, 0.0f, 0.0f));
            ASSERT(m4.columns[1] == nnm::Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
            ASSERT(m4.columns[2] == nnm::Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
            ASSERT(m4.columns[3] == nnm::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
        }

        constexpr nnm::Matrix4f m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                     { -1.0f, -3.0f, -2.0f, -4.0f },
                                     { 3.0f, 2.0f, -1.0f, -4.0f },
                                     { -4.0f, 1.0f, -3.0f, 0.0f } };

        test_section("trace");
        {
            constexpr auto result = m1.trace();
            ASSERT(result == -3.0f);
        }

        test_section("determinant");
        {
            constexpr auto result = m1.determinant();
            ASSERT(nnm::approx_equal(result, -64.0f));
        }

        test_section("minor_matrix_at");
        {
            constexpr nnm::Matrix3 m2 = m1.minor_matrix_at(0, 0);
            ASSERT(m2 == nnm::Matrix3f({ -3.0f, -2.0f, -4.0f }, { 2.0f, -1.0f, -4.0f }, { 1.0f, -3.0f, 0.0f }));

            constexpr nnm::Matrix3 m3 = m1.minor_matrix_at(1, 2);
            ASSERT(m3 == nnm::Matrix3f({ 1.0f, 2.0f, 4.0f }, { 3.0f, 2.0f, -4.0f }, { -4.0f, 1.0f, 0.0f }));
        }

        test_section("minor_at");
        {
            constexpr auto result = m1.minor_at(0, 0);
            ASSERT(nnm::approx_equal(result, 64.0f));
            ASSERT(nnm::approx_equal(m1.minor_at(1, 2), 80.0f));
        }

        test_section("minor");
        {
            nnm::Matrix4f expected(
                { 64.0f, 32.0f, -96.0f, -56.0f },
                { -56.0f, -16.0f, 80.0f, 54.0f },
                { 8.0f, 16.0f, -16.0f, -18.0f },
                { -24.0f, -16.0f, 16.0f, 14.0f });
            constexpr auto result = m1.minor();
            ASSERT(result.approx_equal(expected));
        }

        test_section("cofactor_at");
        {
            constexpr auto result = m1.cofactor_at(0, 0);
            ASSERT(nnm::approx_equal(result, 64.0f));
            ASSERT(nnm::approx_equal(m1.cofactor_at(2, 1), -16.0f));
        }

        test_section("cofactor");
        {
            constexpr nnm::Matrix4f expected { { 64.0f, -32.0f, -96.0f, 56.0f },
                                               { 56.0f, -16.0f, -80.0f, 54.0f },
                                               { 8.0f, -16.0f, -16.0f, 18.0f },
                                               { 24.0f, -16.0f, -16.0f, 14.0f } };
            constexpr auto result = m1.cofactor();
            ASSERT(result.approx_equal(expected))
        }

        test_section("transpose");
        {
            constexpr nnm::Matrix4f expected { { 1.0f, -1.0f, 3.0f, -4.0f },
                                               { 2.0f, -3.0f, 2.0f, 1.0f },
                                               { 3.0f, -2.0f, -1.0f, -3.0f },
                                               { 4.0f, -4.0f, -4.0f, 0.0f } };
            constexpr auto result = m1.transpose();
            ASSERT(result == expected);
        }

        test_section("adjugate");
        {
            constexpr nnm::Matrix4f expected { { 64.0f, 56.0f, 8.0f, 24.0f },
                                               { -32.0f, -16.0f, -16.0f, -16.0f },
                                               { -96.0f, -80.0f, -16.0f, -16.0f },
                                               { 56.0f, 54.0f, 18.0f, 14.0f } };
            constexpr auto result = m1.adjugate();
            ASSERT(result.approx_equal(expected));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Matrix4f expected { { -1.0f, -0.875f, -0.125f, -0.375f },
                                               { 0.5f, 0.25f, 0.25f, 0.25f },
                                               { 1.5f, 1.25f, 0.25f, 0.25f },
                                               { -0.875f, -0.84375f, -0.28125f, -0.21875f } };
            constexpr auto result = m1.unchecked_inverse();
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Matrix4f expected { { -1.0f, -0.875f, -0.125f, -0.375f },
                                               { 0.5f, 0.25f, 0.25f, 0.25f },
                                               { 1.5f, 1.25f, 0.25f, 0.25f },
                                               { -0.875f, -0.84375f, -0.28125f, -0.21875f } };
            constexpr auto result = m1.inverse();
            ASSERT(result.has_value() && result.value().approx_equal(expected));
            ASSERT_FALSE(nnm::Matrix4f::zero().inverse().has_value());
        }

        test_section("approx_equal");
        {
            constexpr nnm::Matrix4f m2 { { 1.000001f, 2.0f, 3.0f, 4.000001f },
                                         { -0.999999f, -3.0f, -2.0f, -4.0f },
                                         { 3.0f, 1.999999f, -1.0f, -4.0f },
                                         { -4.0f, 1.0f, -2.999999f, 0.0f } };
            constexpr auto result = m1.approx_equal(m2);
            ASSERT(result);
        }

        test_section("approx_zero");
        {
            constexpr nnm::Matrix4f m2 { { 0.000001f, 0.0f, 0.0f, 0.0f },
                                         { -0.000001f, -0.0f, -0.0f, 0.0f },
                                         { 0.0f, 0.000001f, 0.0f, 0.0f },
                                         { 0.0f, 0.0f, 0.0f, 0.0f } };
            constexpr auto result = m2.approx_zero();
            ASSERT(result);
        }

        test_section("at");
        {
            constexpr auto result = m1.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(m1.at(1, 2) == -2.0f);
            ASSERT(m1.at(3, 3) == 0.0f);
            ASSERT(m1.at(0) == nnm::Vector4(1.0f, 2.0f, 3.0f, 4.0f))
            ASSERT(m1.at(2) == nnm::Vector4(3.0f, 2.0f, -1.0f, -4.0f))
        }

        test_section("begin");
        {
            ASSERT(m1.begin() == &m1.columns[0].x);
        }

        test_section("end");
        {
            ASSERT(m1.end() == &m1.columns[3].w + 1);
        }

        test_section("operator[]");
        {
            constexpr auto result = m1[0][0];
            ASSERT(result == 1.0f);
            ASSERT(m1[1][2] == -2.0f);
            ASSERT(m1[3][3] == 0.0f);
        }

        constexpr nnm::Matrix4f m2 { { 1.5f, 3.0f, -3.0f, 4.0f },
                                     { -1.0f, 100.0f, -2.0f, -4.0f },
                                     { 0.0f, 29.0f, -129.0f, -4293.0f },
                                     { -4.0f, 100.3f, -3.0f, 0.0f } };

        test_section("operator==");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = m1 == m1;
            ASSERT(result);
            ASSERT_FALSE(m1 == m2);
            ASSERT(m2 == m2);
        }

        test_section("operator!=");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = m1 != m1;
            ASSERT_FALSE(result);
            ASSERT(m1 != m2);
            ASSERT_FALSE(m2 != m2);
        }

        test_section("operator+");
        {
            nnm::Matrix4f expected(
                { 2.5f, 5.0f, 0.0f, 8.0f },
                { -2.0f, 97.0f, -4.0f, -8.0f },
                { 3.0f, 31.0f, -130.0f, -4297.0f },
                { -8.0f, 101.3f, -6.0f, 0.0f });
            constexpr auto result = m1 + m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator+=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy += m2;
                return m1_copy;
            }();
            nnm::Matrix4f expected(
                { 2.5f, 5.0f, 0.0f, 8.0f },
                { -2.0f, 97.0f, -4.0f, -8.0f },
                { 3.0f, 31.0f, -130.0f, -4297.0f },
                { -8.0f, 101.3f, -6.0f, 0.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator-");
        {
            nnm::Matrix4f expected(
                { -0.5f, -1.0f, 6.0f, 0.0f },
                { 0.0f, -103.0f, 0.0f, 0.0f },
                { 3.0f, -27.0f, 128.0f, 4289.0f },
                { 0.0f, -99.3f, 0.0f, 0.0f });
            constexpr auto result = m1 - m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator-=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy -= m2;
                return m1_copy;
            }();
            nnm::Matrix4f expected(
                { -0.5f, -1.0f, 6.0f, 0.0f },
                { 0.0f, -103.0f, 0.0f, 0.0f },
                { 3.0f, -27.0f, 128.0f, 4289.0f },
                { 0.0f, -99.3f, 0.0f, 0.0f });
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(const Matrix4&)");
        {
            constexpr nnm::Matrix4f expected { { -26.5f, -8.0f, -10.5f, 6.0f },
                                               { -91.0f, -310.0f, -189.0f, -396.0f },
                                               { 16756.0f, -4638.0f, 12950.0f, 400.0f },
                                               { -113.3f, -314.9f, -209.6f, -405.2f } };
            constexpr auto result = m1 * m2;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*=(const Matrix4&)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= m2;
                return m1_copy;
            }();
            constexpr nnm::Matrix4f expected { { -26.5f, -8.0f, -10.5f, 6.0f },
                                               { -91.0f, -310.0f, -189.0f, -396.0f },
                                               { 16756.0f, -4638.0f, 12950.0f, 400.0f },
                                               { -113.3f, -314.9f, -209.6f, -405.2f } };
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(const Vector4&)");
        {
            constexpr nnm::Vector4 v { 1.0f, -2.0f, 3.0f, -4.0f };
            constexpr nnm::Vector4 expected { 28.0f, 10.0f, 16.0f, 0.0f };
            constexpr auto result = m1 * v;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(float)");
        {
            constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                               { 2.0f, 6.0f, 4.0f, 8.0f },
                                               { -6.0f, -4.0f, 2.0f, 8.0f },
                                               { 8.0f, -2.0f, 6.0f, 0.0f } };
            constexpr auto result = m1 * -2.0f;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*(float, const Matrix4&)");
        {
            constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                               { 2.0f, 6.0f, 4.0f, 8.0f },
                                               { -6.0f, -4.0f, 2.0f, 8.0f },
                                               { 8.0f, -2.0f, 6.0f, 0.0f } };
            constexpr auto result = -2.0f * m1;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator*=(float)");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy *= -2.0f;
                return m1_copy;
            }();
            constexpr nnm::Matrix4f expected { { -2.0, -4.0f, -6.0f, -8.0f },
                                               { 2.0f, 6.0f, 4.0f, 8.0f },
                                               { -6.0f, -4.0f, 2.0f, 8.0f },
                                               { 8.0f, -2.0f, 6.0f, 0.0f } };
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator/(float)");
        {
            constexpr nnm::Matrix4f expected { { -0.25, -0.5f, -0.75f, -1.0f },
                                               { 0.25f, 0.75f, 0.5f, 1.0f },
                                               { -0.75f, -0.5f, 0.25f, 1.0f },
                                               { 1.0f, -0.25f, 0.75f, 0.0f } };
            constexpr auto result = m1 / -4.0f;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator(float, const Matrix4&)");
        {
            constexpr nnm::Matrix4f m3 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                         { -1.0f, -3.0f, -2.0f, -4.0f },
                                         { 3.0f, 2.0f, -1.0f, -4.0f },
                                         { -4.0f, 1.0f, -3.0f, 1.5f } };
            constexpr nnm::Matrix4f expected { { -4.0f, -2.0f, -1.333333f, -1.0f },
                                               { 4.0f, 1.333333f, 2.0f, 1.0f },
                                               { -1.333333f, -2.0f, 4.0f, 1.0f },
                                               { 1.0f, -4.0f, 1.33333f, -2.6666666f } };
            constexpr auto result = -4.0f / m3;
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator/=");
        {
            constexpr auto result = [=] {
                auto m1_copy = m1;
                m1_copy /= -4.0f;
                return m1_copy;
            }();
            constexpr nnm::Matrix4f expected { { -0.25, -0.5f, -0.75f, -1.0f },
                                               { 0.25f, 0.75f, 0.5f, 1.0f },
                                               { -0.75f, -0.5f, 0.25f, 1.0f },
                                               { 1.0f, -0.25f, 0.75f, 0.0f } };
            ASSERT(result.approx_equal(expected));
        }

        test_section("operator<");
        {
            constexpr auto result = m1 < m2;
            ASSERT(result);
            ASSERT_FALSE(m2 < m1);
        }

        test_section("operator bool");
        {
            constexpr auto result = static_cast<bool>(nnm::Matrix4f::zero());
            ASSERT_FALSE(result);
            ASSERT(static_cast<bool>(nnm::Matrix4f::identity()));
            ASSERT(static_cast<bool>(m1));
        }
    }

    test_case("Transform3");
    {
        test_section("Transform3()");
        {
            constexpr nnm::Transform3f t1;
            ASSERT(t1.matrix == nnm::Matrix4f::identity());
        }

        test_section("Transform3(const Transform3<Other>&)");
        {
            constexpr nnm::Transform3d t1(
                { { 1.0, 2.0, 3.0, 4.0 },
                  { -0.5, 0.75, 0.6, 0.1 },
                  { -100.0, -88.0, 28.0, 0.0 },
                  { 1.0, 29.0, -89.0, 67.0 } });
            constexpr nnm::Transform3f t2(t1);
            ASSERT(t2.matrix.columns[0] == nnm::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
            ASSERT(t2.matrix.columns[1] == nnm::Vector4f(-0.5f, 0.75f, 0.6f, 0.1f));
            ASSERT(t2.matrix.columns[2] == nnm::Vector4f(-100.0f, -88.0f, 28.0f, 0.0f));
            ASSERT(t2.matrix.columns[3] == nnm::Vector4f(1.0f, 29.0f, -89.0f, 67.0f));
        }

        test_section("Transform3(const Matrix4&)");
        {
            constexpr nnm::Matrix4f m1 { { 1.0f, 2.0f, 3.0f, 4.0f },
                                         { 5.0f, 6.0f, 7.0f, 8.0f },
                                         { 9.0f, 10.0f, 11.0f, 12.0f },
                                         { 13.0f, 14.0f, 15.0f, 16.0f } };
            constexpr nnm::Transform3f t2(m1);
            ASSERT(t2.matrix == m1);
        }

        test_section("from_basis_translation");
        {
            constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { -4.0f, -1.0f, 3.5f }, { 1.0f, 0.0f, 1.0f } });
            constexpr auto t1 = nnm::Transform3f::from_basis_translation(b1, { 1.0f, -2.0f, 3.0f });
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -4.0f, -1.0f, 3.5f, 0.0f },
                                     { 1.0f, 0.0f, 1.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t1.matrix == expected);
        }

        test_section("from_basis");
        {
            constexpr nnm::Basis3f b1({ { 1.0f, 2.0f, 3.0f }, { -4.0f, -1.0f, 3.5f }, { 1.0f, 0.0f, 1.0f } });
            constexpr auto t3 = nnm::Transform3f::from_basis(b1);
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -4.0f, -1.0f, 3.5f, 0.0f },
                                     { 1.0f, 0.0f, 1.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t3.matrix == expected);
        }

        test_section("from_translation");
        {
            constexpr auto t2 = nnm::Transform3f::from_translation({ 1.0f, -2.0f, 3.0f });
            nnm::Matrix4f expected { { 1.0f, 0.0f, 0.0f, 0.0f },
                                     { 0.0f, 1.0f, 0.0f, 0.0f },
                                     { 0.0f, 0.0f, 1.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t2.matrix == expected);
        }

        test_section("from_rotation_axis_angle");
        {
            auto t1 = nnm::Transform3f::from_rotation_axis_angle({ 0.0f, 2.0f, 0.0f }, nnm::pi<float>() / 9.0f);
            nnm::Matrix4f expected1 { { 0.9396926f, 0.0f, -0.3420202f, 0.0f },
                                      { 0.0f, 1.0f, 0.0f, 0.0f },
                                      { 0.3420202f, 0.0f, 0.9396926f, 0.0f },
                                      { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_rotation_quaternion");
        {
            constexpr auto t = nnm::Transform3f::from_rotation_quaternion(
                nnm::Quaternion(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f));
            constexpr nnm::Transform3f expected(
                { { 0.9980918f, -0.0213389f, -0.0579437f, 0.0f },
                  { 0.0335516f, 0.9751930f, 0.2187989f, 0.0f },
                  { 0.0518374f, -0.2203254f, 0.9740480f, 0.0f },
                  { 0.0f, 0.0f, 0.0f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_scale");
        {
            constexpr auto t1 = nnm::Transform3f::from_scale({ 0.2f, -0.3f, 2.1f });
            nnm::Matrix4f expected1 { { 0.2f, 0.0f, 0.0f, 0.0f },
                                      { 0.0f, -0.3f, 0.0f, 0.0f },
                                      { 0.0f, 0.0f, 2.1f, 0.0f },
                                      { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_x");
        {
            constexpr auto t1 = nnm::Transform3f::from_shear_x(1.2f, -0.2f);
            nnm::Matrix4f expected1 { { 1.0f, 1.2f, -0.2f, 0.0f },
                                      { 0.0f, 1.0f, 0.0f, 0.0f },
                                      { 0.0f, 0.0f, 1.0f, 0.0f },
                                      { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_y");
        {
            constexpr auto t1 = nnm::Transform3f::from_shear_y(-0.2f, 1.2f);
            nnm::Matrix4f expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                      { -0.2f, 1.0f, 1.2f, 0.0f },
                                      { 0.0f, 0.0f, 1.0f, 0.0f },
                                      { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_shear_z");
        {
            constexpr auto t1 = nnm::Transform3f::from_shear_z(1.5f, -0.3f);
            nnm::Matrix4f expected1 { { 1.0f, 0.0f, 0.0f, 0.0f },
                                      { 0.0f, 1.0f, 0.0f, 0.0f },
                                      { 1.5f, -0.3f, 1.0f, 0.0f },
                                      { 0.0f, 0.0f, 0.0f, 1.0f } };
            ASSERT(t1.matrix.approx_equal(expected1));
        }

        test_section("from_perspective_left_hand_neg1to1");
        {
            const auto t = nnm::Transform3f::from_perspective_left_hand_neg1to1(
                nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
            constexpr nnm::Transform3f expected(
                { { 0.5625f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 1.0f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, -1.002f, -1.0f },
                  { 0.0f, 0.0f, -0.2002f, 0.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_perspective_left_hand_0to1");
        {
            const auto t = nnm::Transform3f::from_perspective_left_hand_0to1(
                nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
            constexpr nnm::Transform3f expected(
                { { 0.5625f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 1.0f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, -1.001f, -1.0f },
                  { 0.0f, 0.0f, -0.1001f, 0.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_perspective_right_hand_neg1to1");
        {
            const auto t = nnm::Transform3f::from_perspective_right_hand_neg1to1(
                nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
            constexpr nnm::Transform3f expected(
                { { 0.5625f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 1.0f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, 1.002f, 1.0f },
                  { 0.0f, 0.0f, -0.2002f, 0.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_perspective_right_hand_0to1");
        {
            const auto t = nnm::Transform3f::from_perspective_right_hand_0to1(
                nnm::pi<float>() / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
            constexpr nnm::Transform3f expected(
                { { 0.5625f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 1.0f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, 1.001f, 1.0f },
                  { 0.0f, 0.0f, -0.1001f, 0.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_orthographic_left_hand_neg1to1");
        {
            constexpr auto t
                = nnm::Transform3f::from_orthographic_left_hand_neg1to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
            constexpr nnm::Transform3f expected(
                { { 0.25f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 0.3333333f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, -0.040404f, 0.0f },
                  { -0.25f, -0.333333f, -1.020202f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_orthographic_left_hand_0to1");
        {
            constexpr auto t
                = nnm::Transform3f::from_orthographic_left_hand_0to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
            constexpr nnm::Transform3f expected(
                { { 0.25f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 0.3333333f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, -0.020202f, 0.0f },
                  { -0.25f, -0.333333f, -0.010101f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_orthographic_right_hand_neg1to1");
        {
            constexpr auto t
                = nnm::Transform3f::from_orthographic_right_hand_neg1to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
            constexpr nnm::Transform3f expected(
                { { 0.25f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 0.333333f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, 0.040404f, 0.0f },
                  { -0.25f, -0.3333333f, -1.020202f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        test_section("from_orthographic_right_hand_0to1");
        {
            constexpr auto t
                = nnm::Transform3f::from_orthographic_right_hand_0to1(-3.0f, 5.0f, -2.0f, 4.0f, 0.5f, 50.0f);
            constexpr nnm::Transform3f expected(
                { { 0.25f, 0.0f, 0.0f, 0.0f },
                  { 0.0f, 0.333333f, 0.0f, 0.0f },
                  { 0.0f, 0.0f, 0.020202f, 0.0f },
                  { -0.25f, -0.3333333f, -0.010101f, 1.0f } });
            ASSERT(t.approx_equal(expected));
        }

        constexpr auto t1 = nnm::Transform3f(
            { { 1.0f, 2.0f, 3.0f, 0.0f },
              { -0.5f, 2.0f, 3.0f, 0.0f },
              { 0.0f, 0.0f, 2.0f, 0.0f },
              { 1.0f, -2.0f, 3.0f, 1.0f } });

        constexpr auto t2 = nnm::Transform3f(
            { { 1.0f, 2.0f, 3.0f, 4.0f },
              { -0.5f, 2.0f, 3.0f, -3.0f },
              { 0.0f, 0.0f, 2.0f, 0.0f },
              { 1.0f, -2.0f, 3.0f, 1.0f } });

        test_section("trace");
        {
            constexpr auto result = t1.trace();
            ASSERT(nnm::approx_equal(result, 6.0f));
        }

        test_section("determinant");
        {
            constexpr auto result = t1.determinant();
            ASSERT(nnm::approx_equal(result, 6.0f));
        }

        test_section("unchecked_inverse");
        {
            constexpr nnm::Transform3f expected(
                { { 0.666666f, -0.6666666f, 0.0f, 0.0f },
                  { 0.16666666f, 0.3333333f, -0.75f, 0.0f },
                  { 0.0f, 0.0f, 0.5f, 0.0f },
                  { -0.33333333f, 1.33333333f, -3.0f, 1.0f } });
            constexpr auto result = t1.unchecked_inverse();
            ASSERT(result.approx_equal(expected));
        }

        test_section("inverse");
        {
            constexpr nnm::Transform3f expected(
                { { 0.666666f, -0.6666666f, 0.0f, 0.0f },
                  { 0.16666666f, 0.3333333f, -0.75f, 0.0f },
                  { 0.0f, 0.0f, 0.5f, 0.0f },
                  { -0.33333333f, 1.33333333f, -3.0f, 1.0f } });
            constexpr auto result = t1.inverse();
            ASSERT(result.has_value() && result.value().approx_equal(expected));
            ASSERT_FALSE(nnm::Transform3(nnm::Matrix4f::zero()).inverse().has_value());
        }

        test_section("valid");
        {
            constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).valid();
            ASSERT_FALSE(result);
            ASSERT(t1.valid());
            ASSERT(t2.valid());
        }

        test_section("affine");
        {
            constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).affine();
            ASSERT_FALSE(result);
            ASSERT(t1.affine());
            ASSERT_FALSE(t2.affine());
            ASSERT(nnm::Transform3f().affine());
        }

        test_section("basis");
        {
            nnm::Basis3f expected({ { 1.0f, 2.0f, 3.0f }, { -0.5f, 2.0f, 3.0f }, { 0.0f, 0.0f, 2.0f } });
            constexpr auto result = t2.basis();
            ASSERT(result == expected);
        }

        test_section("translation");
        {
            constexpr auto result = nnm::Transform3(nnm::Matrix4f::zero()).translation();
            ASSERT(result == nnm::Vector3(0.0f, 0.0f, 0.0f));
            ASSERT(t1.translation() == nnm::Vector3(1.0f, -2.0f, 3.0f));
            ASSERT(nnm::Transform3f().translation() == nnm::Vector3f(0.0f, 0.0f, 0.0f));
        }

        test_section("translate");
        {
            constexpr auto t3 = t1.translate({ 3.0f, -1.5f, 1.0f });
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -0.5f, 2.0f, 3.0f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 4.0f, -3.5f, 4.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("translate_local");
        {
            constexpr auto t3 = t1.translate_local({ 3.0f, -1.5f, 1.0f });
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -0.5f, 2.0f, 3.0f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 4.75f, 1.0f, 9.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("rotate_axis_angle");
        {
            auto t3 = t1.rotate_axis_angle({ 0.0f, 0.0f, 1.0f }, -nnm::pi<float>() / 9.0f);
            nnm::Matrix4f expected { { 1.62373f, 1.53737f, 3.0f, 0.0f },
                                     { 0.214194f, 2.0504f, 3.0f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 0.255652f, -2.22141f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("rotate_axis_angle_local");
        {
            auto t3 = t1.rotate_axis_angle_local({ 0.0f, 0.0f, 1.0f }, -nnm::pi<float>() / 9.0f);
            nnm::Matrix4f expected { { 1.1107f, 1.19534f, 1.79302f, 0.0f },
                                     { -0.127826f, 2.56343f, 3.84514f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("rotate_quaternion");
        {
            constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
            constexpr nnm::Transform3f expected(
                { { 1.22071f, 1.26807f, 3.3018f, 4.0f },
                  { -0.27643f, 1.30008f, 3.38871f, -3.0f },
                  { 0.103675f, -0.440651f, 1.9481f, 0.0f },
                  { 1.0865f, -2.6327f, 2.4266f, 1.0f } });
            constexpr auto result = t2.rotate_quaternion(q);
            ASSERT(result.approx_equal(expected));
        }

        test_section("rotate_quaternion_local");
        {
            constexpr nnm::Quaternion q(0.110511f, 0.0276278f, -0.0138139f, 0.9933948f);
            constexpr nnm::Transform3f expected(
                { { 1.00876f, 1.95351f, 2.81437f, 4.05638f },
                  { -0.454045f, 2.01749f, 3.46383f, -2.79137f },
                  { 0.162f, -0.336976f, 1.44263f, 0.868326f },
                  { 1.0f, -2.0f, 3.0f, 1.0f } });
            constexpr auto result = t2.rotate_quaternion_local(q);
            ASSERT(result.approx_equal(expected));
        }

        test_section("scale");
        {
            constexpr auto t3 = t1.scale({ 0.2f, -2.1f, 1.2f });
            nnm::Matrix4f expected { { 0.2f, -4.2f, 3.6f, 0.0f },
                                     { -0.1f, -4.2f, 3.6f, 0.0f },
                                     { 0.0f, 0.0f, 2.4f, 0.0f },
                                     { 0.2f, 4.2f, 3.6f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("scale_local");
        {
            constexpr auto t3 = t1.scale_local({ 0.2f, -2.1f, 1.2f });
            nnm::Matrix4f expected { { 0.2f, 0.4f, 0.6f, 0.0f },
                                     { 1.05f, -4.2f, -6.3f, 0.0f },
                                     { 0.0f, 0.0f, 2.4f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_x");
        {
            constexpr auto t3 = t1.shear_x(0.2f, -1.3f);
            nnm::Matrix4f expected { { 1.0f, 2.2f, 1.7f, 0.0f },
                                     { -0.5f, 1.9f, 3.65f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 1.0f, -1.8f, 1.7f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_x_local");
        {
            constexpr auto t3 = t1.shear_x_local(0.2f, -1.3f);
            nnm::Matrix4f expected { { 0.9f, 2.4f, 1.0f, 0.0f },
                                     { -0.5f, 2.0f, 3.0f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_y");
        {
            constexpr auto t3 = t1.shear_y(1.1f, -0.4f);
            nnm::Matrix4f expected { { 3.2f, 2.0f, 2.2f, 0.0f },
                                     { 1.7f, 2.0f, 2.2f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { -1.2f, -2.0f, 3.8f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_y_local");
        {
            constexpr auto t3 = t1.shear_y_local(1.1f, -0.4f);
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { 0.6f, 4.2f, 5.5f, 0.0f },
                                     { 0.0f, 0.0f, 2.0f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_z");
        {
            constexpr auto t3 = t1.shear_z(-1.25f, 0.45f);
            nnm::Matrix4f expected { { -2.75f, 3.35f, 3.0f, 0.0f },
                                     { -4.25f, 3.35f, 3.0f, 0.0f },
                                     { -2.5f, 0.9f, 2.0f, 0.0f },
                                     { -2.75f, -0.65f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("shear_z_local");
        {
            constexpr auto t3 = t1.shear_z_local(-1.25f, 0.45f);
            nnm::Matrix4f expected { { 1.0f, 2.0f, 3.0f, 0.0f },
                                     { -0.5f, 2.0f, 3.0f, 0.0f },
                                     { -1.475f, -1.6f, -0.4f, 0.0f },
                                     { 1.0f, -2.0f, 3.0f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("transform");
        {
            constexpr auto t3 = t1.transform(
                nnm::Transform3f(
                    { { 4.0f, 3.0f, 4.0f, 0.0f },
                      { 2.0f, -1.0f, -2.0f, 0.0f },
                      { 0.0f, 2.0f, -3.5f, 0.0f },
                      { 10.0f, -5.5f, 25.0f, 1.0f } }));
            nnm::Matrix4f expected { { 8.0f, 7.0f, -10.5f, 0.0f },
                                     { 2.0f, 2.5f, -16.5f, 0.0f },
                                     { 0.0f, 4.0f, -7.0f, 0.0f },
                                     { 10.0f, 5.5f, 22.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("transform_local");
        {
            constexpr auto t3 = t1.transform_local(
                nnm::Transform3f(
                    { { 4.0f, 3.0f, 4.0f, 0.0f },
                      { 2.0f, -1.0f, -2.0f, 0.0f },
                      { 0.0f, 2.0f, -3.5f, 0.0f },
                      { 10.0f, -5.5f, 25.0f, 1.0f } }));
            nnm::Matrix4f expected { { 2.5f, 14.0f, 29.0f, 0.0f },
                                     { 2.5f, 2.0f, -1.0f, 0.0f },
                                     { -1.0f, 4.0f, -1.0f, 0.0f },
                                     { 13.75f, 7.0f, 66.5f, 1.0f } };
            ASSERT(t3.matrix.approx_equal(expected));
        }

        test_section("approx_equal");
        {
            constexpr auto t3 = nnm::Transform3f(
                { { 1.0000001f, 2.0f, 3.0000001f, 0.0f },
                  { -0.5f, 1.999999f, 3.0f, -0.0000001f },
                  { 0.0f, 0.0f, 2.0f, 0.0f },
                  { 1.0f, -1.999999f, 3.0f, 0.999999f } });
            constexpr auto result = t1.approx_equal(t3);
            ASSERT(result);
        }

        test_section("at");
        {
            constexpr auto result = t1.at(0, 0);
            ASSERT(result == 1.0f);
            ASSERT(t1.at(1, 2) == 3.0f);
            ASSERT(t1.at(3, 3) == 1.0f);
            ASSERT(t1.at(1) == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
        }

        test_section("operator[]");
        {
            constexpr auto result = t1[1];
            ASSERT(result == nnm::Vector4(-0.5f, 2.0f, 3.0f, 0.0f));
        }

        test_section("operator==");
        {
            // ReSharper disable once CppIdenticalOperandsInBinaryExpression
            constexpr auto result = t1 == t1;
            ASSERT(result);
            ASSERT_FALSE(t1 == t2);
        }

        test_section("operator!=");
        {
            constexpr auto result = t1 != t2;
            ASSERT(result);
            ASSERT_FALSE(t1 != t1);
        }

        test_section("operator<");
        {
            constexpr auto result = t1 < t2;
            ASSERT(result);
            ASSERT_FALSE(t2 < t1);
        }
    }
}