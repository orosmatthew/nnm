#include <catch_amalgamated.hpp>
#include <nnm/nnm.hpp>

// ReSharper disable CppDFATimeOver

TEST_CASE("abs", "[abs]")
{
    REQUIRE(nnm::abs<int>(0) == 0);
    REQUIRE(nnm::abs<int>(1) == 1);
    REQUIRE(nnm::abs<int>(-1) == 1);
    REQUIRE(nnm::abs<float>(0.0f) == 0.0f);
    REQUIRE(nnm::abs<float>(1.0f) == 1.0f);
    REQUIRE(nnm::abs<float>(-1.0f) == 1.0f);
    REQUIRE(nnm::abs<double>(0.0) == 0.0);
    REQUIRE(nnm::abs<double>(1.0) == 1.0);
    REQUIRE(nnm::abs<double>(-1.0) == 1.0);
}

TEST_CASE("is_zero_approx", "[is_zero_approx]")
{
    REQUIRE(nnm::approx_zero(0.0, 0.01));
    REQUIRE(nnm::approx_zero(0.005, 0.01));
    REQUIRE(nnm::approx_zero(0.01, 0.01));
    REQUIRE(nnm::approx_zero(-0.005, 0.01));
    REQUIRE(nnm::approx_zero(-0.01, 0.01));
    REQUIRE(nnm::approx_zero(1e-15, 1e-14));
    REQUIRE_FALSE(nnm::approx_zero(1e-14, 1e-15));
    REQUIRE(nnm::approx_zero(-1e-15, 1e-14));
    REQUIRE_FALSE(nnm::approx_zero(-1e-14, 1e-15));
    REQUIRE_FALSE(nnm::approx_zero(1.0, 0.0));
    REQUIRE(nnm::approx_zero(0.0, 0.0));
}

TEST_CASE("max", "[max]")
{
    REQUIRE(nnm::max(5, 10) == 10);
    REQUIRE(nnm::max(10, 5) == 10);
    REQUIRE(nnm::max(-5, -10) == -5);
    REQUIRE(nnm::max(-10, -5) == -5);
    REQUIRE(nnm::max(0, 0) == 0);

    REQUIRE(nnm::max(5.0, 10.0) == 10.0);
    REQUIRE(nnm::max(10.0, 5.0) == 10.0);
    REQUIRE(nnm::max(-5.0, -10.0) == -5.0);
    REQUIRE(nnm::max(-10.0, -5.0) == -5.0);
    REQUIRE(nnm::max(0.0, 0.0) == 0.0);
    REQUIRE(nnm::max(3.14159, 2.71828) == 3.14159);
    REQUIRE(nnm::max(-3.14159, -2.71828) == -2.71828);
}

TEST_CASE("approx_lte", "[approx_lte]")
{
    REQUIRE(nnm::approx_lte(1.0, 1.0, 0.01));
    REQUIRE(nnm::approx_lte(1.0, 1.005, 0.01));
    REQUIRE(nnm::approx_lte(1.0, 1.01, 0.01));
    REQUIRE(nnm::approx_lte(1.0, 1.02, 0.01));
    REQUIRE(nnm::approx_lte(-1.0, -1.005, 0.01));
    REQUIRE(nnm::approx_lte(1.0, 1.0, -0.01));
    REQUIRE(nnm::approx_lte(1e-15, 1e-16, 1e-14));
    REQUIRE_FALSE(nnm::approx_lte(4.0, 2.0, 1e-10));
}

TEST_CASE("is_equal_approx", "[is_equal_approx]")
{
    REQUIRE(nnm::approx_equal(1.0, 1.0, 0.01));
    REQUIRE(nnm::approx_equal(1.0, 1.005, 0.01));
    REQUIRE(nnm::approx_equal(1.0, 1.01, 0.01));
    REQUIRE_FALSE(nnm::approx_equal(1.0, 1.02, 0.01));
    REQUIRE(nnm::approx_equal(-1.0, -1.005, 0.01));
    REQUIRE(nnm::approx_equal(0.0, 0.0, 0.01));
    REQUIRE(nnm::approx_equal(0.0, 0.005, 0.01));
    REQUIRE(nnm::approx_equal(0.005, 0.0, 0.01));
    REQUIRE(nnm::approx_equal(0.0, 0.0, 0.0));
    REQUIRE(nnm::approx_equal(1.0, 1.005, -0.01));
    REQUIRE_FALSE(nnm::approx_equal(1.0, 1.0000000000001, 1e-14));
    REQUIRE(nnm::approx_equal(1.0e20, 1.000000000001e20, 1e-10));
}

TEST_CASE("approx_gte", "[approx_gte]")
{
    REQUIRE(nnm::approx_gte(1.0, 1.0, 0.01));
    REQUIRE(nnm::approx_gte(1.0, 0.995, 0.01));
    REQUIRE(nnm::approx_gte(1.0, 0.99, 0.01));
    REQUIRE(nnm::approx_gte(1.0, 0.98, 0.01));
    REQUIRE(nnm::approx_gte(-1.0, -1.005, 0.01));
    REQUIRE(nnm::approx_gte(1.0, 1.0, -0.01));
    REQUIRE(nnm::approx_gte(1e-15, 1e-16, 1e-14));
    REQUIRE_FALSE(nnm::approx_gte(2.0, 4.0, 1e-14));
}

TEST_CASE("ceil", "[ceil]")
{
    REQUIRE(nnm::ceil(5.3) == 6.0);
    REQUIRE(nnm::ceil(5.7) == 6.0);
    REQUIRE(nnm::ceil(5.0) == 5.0);
    REQUIRE(nnm::ceil(-5.3) == -5.0);
    REQUIRE(nnm::ceil(-5.7) == -5.0);
    REQUIRE(nnm::ceil(-5.0) == -5.0);
    REQUIRE(nnm::ceil(0.0) == 0.0);
    REQUIRE(nnm::ceil(1.0e20) == 1.0e20);
    REQUIRE(nnm::ceil(-1.0e20) == -1.0e20);
    REQUIRE(nnm::ceil(3.14159) == 4.0);
    REQUIRE(nnm::ceil(-3.14159) == -3.0);
}

TEST_CASE("clamp", "[clamp]")
{
    REQUIRE(nnm::clamp(5, 0, 10) == 5);
    REQUIRE(nnm::clamp(-5, 0, 10) == 0);
    REQUIRE(nnm::clamp(15, 0, 10) == 10);
    REQUIRE(nnm::clamp(5, 5, 5) == 5);
    REQUIRE(nnm::clamp(3.5, 1.0, 5.0) == 3.5);
    REQUIRE(nnm::clamp(0.5, 1.0, 5.0) == 1.0);
    REQUIRE(nnm::clamp(6.0, 1.0, 5.0) == 5.0);
    REQUIRE(nnm::clamp(-5, -10, -2) == -5);
    REQUIRE(nnm::clamp(-15, -10, -2) == -10);
    REQUIRE(nnm::clamp(-3, -5, -1) == -3);
    REQUIRE(nnm::clamp(-6, -5, -1) == -5);
}

TEST_CASE("sqrt", "[sqrt]")
{
    REQUIRE(nnm::sqrt(4.0) == 2);
    REQUIRE(nnm::sqrt(9.0) == 3);
    REQUIRE(nnm::sqrt(16.0) == 4);

    REQUIRE(nnm::approx_equal(nnm::sqrt(4.0), 2.0));
    REQUIRE(nnm::approx_equal(nnm::sqrt(9.0), 3.0));
    REQUIRE(nnm::approx_equal(nnm::sqrt(16.0), 4.0));

    REQUIRE(nnm::sqrt(0.0) == 0);
    REQUIRE(nnm::sqrt(0.0) == 0.0);

    REQUIRE(nnm::approx_equal(nnm::sqrt(1.0e20), 1.0e10));
}

TEST_CASE("pow", "[pow]")
{
    REQUIRE(nnm::pow(2.0, 3.0) == 8.0);
    REQUIRE(nnm::pow(3.0, 2.0) == 9.0);
    REQUIRE(nnm::pow(4.0, 0.0) == 1.0);

    REQUIRE(nnm::approx_equal(nnm::pow(2.0, 3.0), 8.0));
    REQUIRE(nnm::approx_equal(nnm::pow(3.0, 2.0), 9.0));
    REQUIRE(nnm::approx_equal(nnm::pow(4.0, 0.0), 1.0));

    REQUIRE(nnm::approx_equal(nnm::pow(-2.0, 2.0), 4.0));
    REQUIRE(nnm::approx_equal(nnm::pow(-3.0, 2.0), 9.0));

    REQUIRE(nnm::approx_equal(nnm::pow(-2.0, 3.0), -8.0));
    REQUIRE(nnm::approx_equal(nnm::pow(-3.0, 3.0), -27.0));

    REQUIRE(nnm::approx_equal(nnm::pow(0.0, 3.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::pow(0.0, 0.0), 1.0));

    REQUIRE(nnm::approx_equal(nnm::pow(0.5, 2.0), 0.25));
    REQUIRE(nnm::approx_equal(nnm::pow(0.25, 0.5), 0.5));

    REQUIRE(nnm::approx_equal(nnm::pow(10.0, 10.0), 1.0e10));
    REQUIRE(nnm::approx_equal(nnm::pow(2.0, 100.0), 1.2676506002282294e30));
}

TEST_CASE("sqrd", "[sqrd]")
{
    REQUIRE(nnm::sqrd(2) == 4);
    REQUIRE(nnm::sqrd(3) == 9);
    REQUIRE(nnm::sqrd(-4) == 16);

    REQUIRE(nnm::approx_equal(nnm::sqrd(2.0), 4.0));
    REQUIRE(nnm::approx_equal(nnm::sqrd(3.0), 9.0));
    REQUIRE(nnm::approx_equal(nnm::sqrd(-4.0), 16.0));

    REQUIRE(nnm::sqrd(0) == 0);
    REQUIRE(nnm::sqrd(0.0) == 0.0);

    REQUIRE(nnm::approx_equal(nnm::sqrd(1.0e20), 1.0e40));
    REQUIRE(nnm::approx_equal(nnm::sqrd(-1.0e20), 1.0e40));
}

TEST_CASE("floor", "[floor]")
{
    REQUIRE(nnm::floor(5.3) == 5);
    REQUIRE(nnm::floor(5.7) == 5);
    REQUIRE(nnm::floor(5.0) == 5);

    REQUIRE(nnm::floor(-5.3) == -6);
    REQUIRE(nnm::floor(-5.7) == -6);
    REQUIRE(nnm::floor(-5.0) == -5);

    REQUIRE(nnm::floor(0.0) == 0);

    REQUIRE(nnm::floor(1.0e20) == 1.0e20);
    REQUIRE(nnm::floor(-1.0e20) == -1.0e20);

    REQUIRE(nnm::floor(3.14159) == 3);
    REQUIRE(nnm::floor(-3.14159) == -4);
}

TEST_CASE("lerp", "[lerp]")
{
    REQUIRE(nnm::lerp(0.0, 10.0, 0.5) == 5.0);
    REQUIRE(nnm::lerp(0.0, 10.0, 0.25) == 2.5);
    REQUIRE(nnm::lerp(-5.0, 5.0, 0.75) == 2.5);

    REQUIRE(nnm::lerp(-10.0, -20.0, 0.5) == -15);
    REQUIRE(nnm::lerp(-10.0, -20.0, 0.25) == -12.5);
    REQUIRE(nnm::lerp(-15.0, -25.0, 0.75) == -22.5);

    REQUIRE(nnm::lerp(5.0, 10.0, 0.0) == 5);
    REQUIRE(nnm::lerp(5.0, 10.0, 0.0) == 5);

    REQUIRE(nnm::lerp(5.0, 10.0, 1.0) == 10);
    REQUIRE(nnm::lerp(5.0, 10.0, 1.0) == 10);
}

TEST_CASE("sin", "[sin]")
{
    REQUIRE(nnm::approx_equal(nnm::sin(0.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 6), 0.5));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 4), 1 / nnm::sqrt(2.0)));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 3), nnm::sqrt(3.0) / 2.0));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 2), 1.0));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi), 0.0));
    REQUIRE(nnm::approx_equal(nnm::sin(3 * nnm::pi / 2), -1.0));
    REQUIRE(nnm::approx_equal(nnm::sin(2 * nnm::pi), 0.0));

    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 6), -0.5));
    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 4), -1 / nnm::sqrt(2.0)));
    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 3), -nnm::sqrt(3.0) / 2.0));

    REQUIRE(nnm::approx_equal(nnm::sin(4 * nnm::pi), 0.0));
    REQUIRE(nnm::approx_equal(nnm::sin(6 * nnm::pi), 0.0));
}

TEST_CASE("cos", "[cos]")
{
    REQUIRE(nnm::approx_equal(nnm::cos(0.0), 1.0));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 6), nnm::sqrt(3.0) / 2));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 4), 1 / nnm::sqrt(2.0)));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 3), 0.5));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 2), 0.0));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi), -1.0));
    REQUIRE(nnm::approx_equal(nnm::cos(3 * nnm::pi / 2), 0.0));
    REQUIRE(nnm::approx_equal(nnm::cos(2 * nnm::pi), 1.0));

    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 6), nnm::sqrt(3.0) / 2));
    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 4), 1 / nnm::sqrt(2.0)));
    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 3), 0.5));

    REQUIRE(nnm::approx_equal(nnm::cos(4 * nnm::pi), 1.0));
    REQUIRE(nnm::approx_equal(nnm::cos(6 * nnm::pi), 1.0));
}

TEST_CASE("tan", "[tan]")
{
    REQUIRE(nnm::approx_equal(nnm::tan(0.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 4), 1.0));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 6), 1 / nnm::sqrt(3.0)));

    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 3), nnm::sqrt(3.0)));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 2 - 0.01), 99.9967));

    REQUIRE(nnm::approx_equal(nnm::tan(-nnm::pi / 3), -nnm::sqrt(3.0)));
    REQUIRE(nnm::approx_equal(nnm::tan(-nnm::pi / 2 + 0.01), -99.9967));

    REQUIRE(nnm::approx_equal(nnm::tan(3 * nnm::pi), 0.0));
    REQUIRE(nnm::approx_equal(nnm::tan(6 * nnm::pi), 0.0));
}

TEST_CASE("round", "[round]")
{
    REQUIRE(nnm::round(5.3) == 5);
    REQUIRE(nnm::round(5.7) == 6);
    REQUIRE(nnm::round(5.0) == 5);

    REQUIRE(nnm::round(-5.3) == -5);
    REQUIRE(nnm::round(-5.7) == -6);
    REQUIRE(nnm::round(-5.0) == -5);

    REQUIRE(nnm::round(0.0) == 0);

    REQUIRE(nnm::round(3.14159) == 3);
    REQUIRE(nnm::round(-3.14159) == -3);
}

TEST_CASE("atan", "[atan]")
{
    REQUIRE(nnm::approx_equal(nnm::atan(0.5), 0.4636476));
    REQUIRE(nnm::approx_equal(nnm::atan(1.0), 0.7853981));
    REQUIRE(nnm::approx_equal(nnm::atan(2.0), 1.1071487));

    REQUIRE(nnm::approx_equal(nnm::atan(-0.5), -0.4636476));
    REQUIRE(nnm::approx_equal(nnm::atan(-1.0), -0.7853981));
    REQUIRE(nnm::approx_equal(nnm::atan(-2.0), -1.1071487));

    REQUIRE(nnm::approx_equal(nnm::atan(0.0), 0.0));

    REQUIRE(nnm::approx_equal(nnm::atan(1.0e20), 1.5707963));
    REQUIRE(nnm::approx_equal(nnm::atan(-1.0e20), -1.5707963));
}

TEST_CASE("atan2", "[atan2]")
{
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0, 1.0), 0.7853981633974483));
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0, 2.0), 0.4636476090008061));

    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0, -1.0), -2.356194490192345));
    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0, 2.0), -0.4636476090008061));

    REQUIRE(nnm::approx_equal(nnm::atan2(0.0, 1.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0, 0.0), 1.5707963267948966));
    REQUIRE(nnm::approx_equal(nnm::atan2(0.0, 0.0), 0.0));

    REQUIRE(nnm::approx_equal(nnm::atan2(1.0e20, 1.0e20), 0.7853981633974483));
    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0e20, -1.0e20), -2.356194490192345));
}

TEST_CASE("radians", "[radians]")
{
    REQUIRE(nnm::approx_equal(nnm::radians(0.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::radians(45.0), nnm::pi / 4));
    REQUIRE(nnm::approx_equal(nnm::radians(90.0), nnm::pi / 2));
    REQUIRE(nnm::approx_equal(nnm::radians(180.0), nnm::pi));
    REQUIRE(nnm::approx_equal(nnm::radians(270.0), 3 * nnm::pi / 2));
    REQUIRE(nnm::approx_equal(nnm::radians(360.0), 2 * nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(-45.0), -nnm::pi / 4));
    REQUIRE(nnm::approx_equal(nnm::radians(-90.0), -nnm::pi / 2));
    REQUIRE(nnm::approx_equal(nnm::radians(-180.0), -nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(720.0), 4 * nnm::pi));
    REQUIRE(nnm::approx_equal(nnm::radians(1080.0), 6 * nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(180.0, 3.14159), 3.14159));
}

TEST_CASE("degrees", "[degrees]")
{
    REQUIRE(nnm::approx_equal(nnm::degrees(0.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi / 4), 45.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi / 2), 90.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi), 180.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(3 * nnm::pi / 2), 270.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(2 * nnm::pi), 360.0));

    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi / 4), -45.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi / 2), -90.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi), -180.0));

    REQUIRE(nnm::approx_equal(nnm::degrees(4 * nnm::pi), 720.0));
    REQUIRE(nnm::approx_equal(nnm::degrees(6 * nnm::pi), 1080.0));

    REQUIRE(nnm::approx_equal(nnm::degrees(3.14159, 3.14159), 180.0));
}

TEST_CASE("asin", "[asin]")
{
    REQUIRE(nnm::approx_equal(nnm::asin(0.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::asin(0.5), 0.5235987756));
    REQUIRE(nnm::approx_equal(nnm::asin(-0.5), -0.5235987756));
    REQUIRE(nnm::approx_equal(nnm::asin(1.0), 1.570796327));
    REQUIRE(nnm::approx_equal(nnm::asin(-1.0), -1.570796327));

    // TODO: Check range
}

TEST_CASE("acos", "[acos]")
{
    REQUIRE(nnm::approx_equal(nnm::acos(1.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::acos(0.5), 1.047197551));
    REQUIRE(nnm::approx_equal(nnm::acos(-0.5), 2.094395102));
    REQUIRE(nnm::approx_equal(nnm::acos(0.0), 1.570796327));
    REQUIRE(nnm::approx_equal(nnm::acos(-1.0), 3.141592654));

    // TODO: Check range
}

TEST_CASE("min", "[min]")
{
    REQUIRE(nnm::min(1, 2) == 1);
    REQUIRE(nnm::min(5, 3) == 3);
    REQUIRE(nnm::min(-1, -5) == -5);

    REQUIRE(nnm::min(1.0, 2.0) == 1.0);
    REQUIRE(nnm::min(5.5, 3.5) == 3.5);
    REQUIRE(nnm::min(-1.0, -5.0) == -5.0);

    REQUIRE(nnm::min('a', 'b') == 'a');
    REQUIRE(nnm::min(3.14f, 2.71f) == 2.71f);
}

TEST_CASE("log2", "[log2]")
{
    REQUIRE(nnm::approx_equal(nnm::log2(1.0), 0.0));
    REQUIRE(nnm::approx_equal(nnm::log2(2.0), 1.0));
    REQUIRE(nnm::approx_equal(nnm::log2(8.0), 3.0));
    REQUIRE(nnm::approx_equal(nnm::log2(16.0), 4.0));

    REQUIRE(nnm::approx_equal(nnm::log2(0.5), -1.0));
    REQUIRE(nnm::approx_equal(nnm::log2(4.0), 2.0));

    // TODO: Check 0 and negative
}

TEST_CASE("Vector2", "[Vector2]")
{
    SECTION("Default constructor")
    {
        const nnm::Vector2<double> v;
        REQUIRE(v.x == 0.0);
        REQUIRE(v.y == 0.0);
    }

    SECTION("From Vector2i constructor")
    {
        const nnm::Vector2<double> v(nnm::Vector2i(1, 2));
        REQUIRE(v.x == 1.0);
        REQUIRE(v.y == 2.0);
    }

    SECTION("Constructor with params")
    {
        const nnm::Vector2 v(1.0, 2.0);
        REQUIRE(v.x == 1.0);
        REQUIRE(v.y == 2.0);
    }

    SECTION("Static methods")
    {
        const auto all_threes = nnm::Vector2<double>::all(3.0);
        REQUIRE(all_threes.x == 3.0);
        REQUIRE(all_threes.y == 3.0);

        const auto zero = nnm::Vector2<double>::zero();
        REQUIRE(zero.x == 0.0);
        REQUIRE(zero.y == 0.0);

        const auto one = nnm::Vector2<double>::one();
        REQUIRE(one.x == 1.0);
        REQUIRE(one.y == 1.0);
    }

    SECTION("abs")
    {
        const nnm::Vector2 v(1.0, -2.0);
        REQUIRE(v.abs() == nnm::Vector2(1.0, 2.0));
    }

    SECTION("aspect_ratio")
    {
        const nnm::Vector2 v(1.0, -2.0);
        REQUIRE(v.aspect_ratio() == 1.0 / -2.0);
    }

    SECTION("ceil")
    {
        const nnm::Vector2 v(1.1, -1.9);
        REQUIRE(v.ceil() == nnm::Vector2(2.0, -1.0));
    }

    SECTION("clamp")
    {
        const nnm::Vector2 v(1.1, -3.0);
        REQUIRE(v.clamp({ 1.0, -2.0 }, { 2.0, 2.0 }) == nnm::Vector2(1.1, -2.0));
    }

    SECTION("normalize")
    {
        const nnm::Vector2 v(1.1, -3.0);
        const auto norm = v.normalize();
        REQUIRE(nnm::approx_equal(norm.x, 0.344255));
        REQUIRE(nnm::approx_equal(norm.y, -0.938876));
    }

    SECTION("direction_to")
    {
        const nnm::Vector2 from1(1.0, 1.0);
        const nnm::Vector2 to1(2.0, 2.0);
        auto direction1 = from1.direction_to(to1);
        REQUIRE(nnm::approx_equal(direction1.x, 0.7071067812));
        REQUIRE(nnm::approx_equal(direction1.y, 0.7071067812));

        const nnm::Vector2 from2(-1.0, -1.0);
        const nnm::Vector2 to2(1.0, 1.0);
        auto direction2 = from2.direction_to(to2);
        REQUIRE(nnm::approx_equal(direction2.x, 0.7071067812));
        REQUIRE(nnm::approx_equal(direction2.y, 0.7071067812));

        const nnm::Vector2 from3(0.0, 0.0);
        const nnm::Vector2 to3(1.0, 0.0);
        auto direction3 = from3.direction_to(to3);
        REQUIRE(nnm::approx_equal(direction3.x, 1.0));
        REQUIRE(nnm::approx_equal(direction3.y, 0.0));

        const nnm::Vector2 from4(0.0, 0.0);
        const nnm::Vector2 to4(0.0, 1.0);
        auto direction4 = from4.direction_to(to4);
        REQUIRE(nnm::approx_equal(direction4.x, 0.0));
        REQUIRE(nnm::approx_equal(direction4.y, 1.0));

        const nnm::Vector2 from5(1.0, 2.0);
        const nnm::Vector2 to5(1.0, 2.0);
        auto direction5 = from5.direction_to(to5);
        REQUIRE(nnm::approx_equal(direction5.x, 0.0));
        REQUIRE(nnm::approx_equal(direction5.y, 0.0));
    }

    SECTION("distance_sqrd_to")
    {
        const nnm::Vector2 from1(1.0, 1.0);
        const nnm::Vector2 to1(2.0, 2.0);
        REQUIRE(nnm::approx_equal(from1.distance_sqrd_to(to1), 2.0));

        const nnm::Vector2 from2(-1.0, -1.0);
        const nnm::Vector2 to2(1.0, 1.0);
        REQUIRE(nnm::approx_equal(from2.distance_sqrd_to(to2), 8.0));

        const nnm::Vector2 from3(0.0, 0.0);
        const nnm::Vector2 to3(3.0, 0.0);
        REQUIRE(nnm::approx_equal(from3.distance_sqrd_to(to3), 9.0));

        const nnm::Vector2 from4(0.0, 0.0);
        const nnm::Vector2 to4(0.0, 4.0);
        REQUIRE(nnm::approx_equal(from4.distance_sqrd_to(to4), 16.0));

        const nnm::Vector2 from5(1.0, 2.0);
        const nnm::Vector2 to5(1.0, 2.0);
        REQUIRE(nnm::approx_equal(from5.distance_sqrd_to(to5), 0.0));
    }

    SECTION("distance_to")
    {
        nnm::Vector2 from(1.0, 1.0);
        nnm::Vector2 to(2.0, 2.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(2.0)));

        from = nnm::Vector2(-1.0, -1.0);
        to = nnm::Vector2(1.0, 1.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(8.0)));

        from = nnm::Vector2(0.0, 0.0);
        to = nnm::Vector2(3.0, 0.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 3.0));

        from = nnm::Vector2(0.0, 0.0);
        to = nnm::Vector2(0.0, 4.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 4.0));

        from = nnm::Vector2(1.0, 2.0);
        to = nnm::Vector2(1.0, 2.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 0.0));
    }

    SECTION("floor")
    {
        const nnm::Vector2 v(1.1, -1.9);
        REQUIRE(v.floor() == nnm::Vector2(1.0, -2.0));
    }

    SECTION("length_sqrd")
    {
        nnm::Vector2 v(3.0, 4.0);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 25.0));

        v = nnm::Vector2(-2.0, 5.0);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 29.0));

        v = nnm::Vector2(0.0, 0.0);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 0.0));
    }

    SECTION("length")
    {
        nnm::Vector2 v(3.0, 4.0);
        REQUIRE(nnm::approx_equal(v.length(), 5.0));

        v = nnm::Vector2(-2.0, 5.0);
        REQUIRE(nnm::approx_equal(v.length(), sqrt(29.0)));

        v = nnm::Vector2(0.0, 0.0);
        REQUIRE(nnm::approx_equal(v.length(), 0.0));
    }

    SECTION("lerp")
    {
        const nnm::Vector2 from(1.0, 1.0);
        const nnm::Vector2 to(3.0, 5.0);
        REQUIRE(from.lerp(to, 0.0) == nnm::Vector2<double>(1.0, 1.0));
        REQUIRE(from.lerp(to, 1.0) == nnm::Vector2<double>(3.0, 5.0));
        REQUIRE(from.lerp(to, 0.5) == nnm::Vector2<double>(2.0, 3.0));
        REQUIRE(from.lerp(to, 0.25) == nnm::Vector2<double>(1.5, 2.0));
        REQUIRE(from.lerp(to, 0.75) == nnm::Vector2<double>(2.5, 4.0));
    }

    SECTION("min/max_axis")
    {
        nnm::Vector2 v1(3.0, 4.0);
        REQUIRE(v1.max_axis() == nnm::Axis2::y);
        REQUIRE(v1.min_axis() == nnm::Axis2::x);

        nnm::Vector2 v2(2.0, 5.0);
        REQUIRE(v2.max_axis() == nnm::Axis2::y);
        REQUIRE(v2.min_axis() == nnm::Axis2::x);

        nnm::Vector2 v3(0.0, 0.0);
        REQUIRE(v3.max_axis() == nnm::Axis2::x);
        REQUIRE(v3.min_axis() == nnm::Axis2::x);
    }

    SECTION("approx_equal")
    {
        nnm::Vector2 v1(1.0, 1.0);
        nnm::Vector2 v2(1.0 + nnm::epsilon / 2, 1.0);
        REQUIRE(v1.approx_equal(v2));
        nnm::Vector2 v3(1.0, 1.0);
        nnm::Vector2 v4(1.0 + 2 * nnm::epsilon, 1.0);
        REQUIRE_FALSE(v3.approx_equal(v4));
    }

    SECTION("approx_zero")
    {
        nnm::Vector2 v1(0.0, 0.0);
        REQUIRE(v1.approx_zero());
        nnm::Vector2 v2(nnm::epsilon, 0.0);
        REQUIRE(v2.approx_zero());
        nnm::Vector2 v3(0.0, nnm::epsilon);
        REQUIRE(v3.approx_zero());
        nnm::Vector2 v4(0.1, 0.1);
        REQUIRE_FALSE(v4.approx_zero());
    }

    SECTION("dot")
    {
        nnm::Vector2 v1(2.0, 3.0);
        nnm::Vector2 v2(4.0, 5.0);
        REQUIRE(v1.dot(v2) == 23.0);
    }

    SECTION("reflect")
    {
        nnm::Vector2 incident(3.0, 4.0);
        nnm::Vector2 normal(1.0, 0.0);
        REQUIRE(incident.reflect(normal) == nnm::Vector2(-3.0, 4.0));
    }

    SECTION("rotate")
    {
        nnm::Vector2 v(1.0, 0.0);
        REQUIRE(v.rotate(nnm::radians(90.0)).approx_equal(nnm::Vector2(0.0, 1.0)));
    }

    SECTION("inverse")
    {
        nnm::Vector2 v(2.0, 3.0);
        REQUIRE(v.inverse().approx_equal(nnm::Vector2(1 / 2.0, 1.0 / 3.0)));
    }

    SECTION("clamp_length")
    {
        REQUIRE(nnm::Vector2(3.0, 4.0).clamp_length(2.0, 5.0) == nnm::Vector2(3.0, 4.0));
        REQUIRE(nnm::Vector2(1.0, 2.0).clamp_length(0.5, 3.0) == nnm::Vector2(1.0, 2.0));
        REQUIRE(nnm::Vector2(3.0, 4.0).clamp_length(2.0, 2.0).approx_equal(nnm::Vector2(1.2, 1.6)));
        REQUIRE(nnm::approx_equal(nnm::Vector2(1.0, 1.0).clamp_length(2.0, 5.0).length(), 2.0));
        REQUIRE(nnm::Vector2(5.0, 6.0).clamp_length(2.0, 5.0).length() == 5.0);
    }

    nnm::Vector2 v1(1.0, 2.0);
    nnm::Vector2 v2(3.0, 4.0);
    nnm::Vector2 v3(1.0, 2.0);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 * v2 == nnm::Vector2<double>(3.0, 8.0));
        REQUIRE(v1 * 2.0 == nnm::Vector2<double>(2.0, 4.0));
        REQUIRE(v2 / v1 == nnm::Vector2<double>(3.0, 2.0));
        REQUIRE(v2 / 2.0 == nnm::Vector2<double>(1.5, 2.0));
        REQUIRE(v1 + v2 == nnm::Vector2<double>(4.0, 6.0));
        REQUIRE(v2 - v1 == nnm::Vector2<double>(2.0, 2.0));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector2<double>(-1.0, -2.0));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector2 v_copy(v1);

        v1 *= v2;
        REQUIRE(v1 == nnm::Vector2<double>(3.0, 8.0));
        v1 = v_copy;

        v1 *= 2.0;
        REQUIRE(v1 == nnm::Vector2<double>(2.0, 4.0));
        v1 = v_copy;

        v2 /= v1;
        REQUIRE(v2 == nnm::Vector2<double>(3.0, 2.0));

        v2 /= 2.0;
        REQUIRE(v2 == nnm::Vector2<double>(1.5, 1.0));
        v2 = v_copy;

        v1 += v2;
        REQUIRE(v1 == nnm::Vector2<double>(2.0, 4.0));
        v1 = v_copy;

        v2 -= v1;
        REQUIRE(v2 == nnm::Vector2<double>(0.0, 0.0));
        v2 = v_copy;
    }

    SECTION("Comparison Operators")
    {
        REQUIRE(v1 < v2);
        REQUIRE(v1 <= v2);
        REQUIRE_FALSE(v1 > v2);
        REQUIRE_FALSE(v1 >= v2);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1.0);
        REQUIRE(v1[1] == 2.0);

        REQUIRE(v1[nnm::Axis2::x] == 1.0);
        REQUIRE(v1[nnm::Axis2::y] == 2.0);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector2<double>(0.0, 0.0)));
    }
}

TEST_CASE("Vector2i", "[Vector2i]")
{
    SECTION("Default constructor")
    {
        const nnm::Vector2i v;
        REQUIRE(v.x == 0);
        REQUIRE(v.y == 0);
    }

    SECTION("Constructor with params")
    {
        const nnm::Vector2i v(1, 2);
        REQUIRE(v.x == 1);
        REQUIRE(v.y == 2);
    }

    SECTION("Static methods")
    {
        const auto all_threes = nnm::Vector2i::all(3);
        REQUIRE(all_threes.x == 3);
        REQUIRE(all_threes.y == 3);

        const auto zero = nnm::Vector2i::zero();
        REQUIRE(zero.x == 0);
        REQUIRE(zero.y == 0);

        const auto one = nnm::Vector2i::one();
        REQUIRE(one.x == 1);
        REQUIRE(one.y == 1);
    }

    SECTION("abs")
    {
        REQUIRE(nnm::Vector2i(1, -2).abs() == nnm::Vector2i(1, 2));
    }

    SECTION("aspect_ratio")
    {
        REQUIRE(nnm::Vector2i(1, -2).aspect_ratio<double>() == 1.0 / -2.0);
    }

    SECTION("clamp")
    {
        REQUIRE(nnm::Vector2i(1, -3).clamp({ 1, -2 }, { 2, 2 }) == nnm::Vector2i(1, -2));
    }

    SECTION("length_sqrd")
    {
        REQUIRE(nnm::Vector2i(3, 4).length_sqrd() == 25);
        REQUIRE(nnm::Vector2i(-2, 5).length_sqrd() == 29);
        REQUIRE(nnm::Vector2i(0, 0).length_sqrd() == 0);
    }

    SECTION("length")
    {
        REQUIRE(nnm::approx_equal(nnm::Vector2i(3, 4).length<double>(), 5.0));
        REQUIRE(nnm::approx_equal(nnm::Vector2i(-2, 5).length<double>(), nnm::sqrt(29.0)));
        REQUIRE(nnm::approx_equal(nnm::Vector2i(0, 0).length<double>(), 0.0));
    }

    SECTION("min/max_axis")
    {
        nnm::Vector2i v1(3, 4);
        REQUIRE(v1.max_axis() == nnm::Axis2::y);
        REQUIRE(v1.min_axis() == nnm::Axis2::x);

        nnm::Vector2i v2(2, 5);
        REQUIRE(v2.max_axis() == nnm::Axis2::y);
        REQUIRE(v2.min_axis() == nnm::Axis2::x);

        nnm::Vector2i v3(0, 0);
        REQUIRE(v3.max_axis() == nnm::Axis2::x);
        REQUIRE(v3.min_axis() == nnm::Axis2::x);
    }

    nnm::Vector2i v1(1, 2);
    nnm::Vector2i v2(3, 4);
    nnm::Vector2i v3(1, 2);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 % v2 == nnm::Vector2i(1, 2));
        REQUIRE(v1 % 2 == nnm::Vector2i(1, 0));
        REQUIRE(v1 * v2 == nnm::Vector2i(3, 8));
        REQUIRE(v1 * 2 == nnm::Vector2i(2, 4));
        REQUIRE(v1 + v2 == nnm::Vector2i(4, 6));
        REQUIRE(v2 - v1 == nnm::Vector2i(2, 2));
        REQUIRE(v2 / v1 == nnm::Vector2i(3, 2));
        REQUIRE(v2 / 2 == nnm::Vector2i(1, 2));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector2i(-1, -2));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector2i v_copy(v1);

        v1 *= v2;
        REQUIRE(v1 == nnm::Vector2i(3, 8));
        v1 = v_copy;

        v1 *= 2;
        REQUIRE(v1 == nnm::Vector2i(2, 4));
        v1 = v_copy;

        v2 /= v1;
        REQUIRE(v2 == nnm::Vector2i(3, 2));

        v2 /= 2;
        REQUIRE(v2 == nnm::Vector2i(1, 1));
        v2 = v_copy;

        v1 += v2;
        REQUIRE(v1 == nnm::Vector2i(2, 4));
        v1 = v_copy;

        v2 -= v1;
        REQUIRE(v2 == nnm::Vector2i(0, 0));
        v2 = v_copy;
    }

    SECTION("Comparison Operators")
    {
        REQUIRE(v1 < v2);
        REQUIRE(v1 <= v2);
        REQUIRE_FALSE(v1 > v2);
        REQUIRE_FALSE(v1 >= v2);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);

        REQUIRE(v1[nnm::Axis2::x] == 1);
        REQUIRE(v1[nnm::Axis2::y] == 2);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector2i(0, 0)));
    }
}

TEST_CASE("Vector3", "[Vector3]")
{
    SECTION("Constructors")
    {
        const nnm::Vector3<double> v1;
        REQUIRE(v1.x == 0.0);
        REQUIRE(v1.y == 0.0);

        const nnm::Vector3<double> v2(nnm::Vector3i(1, 2, 3));
        REQUIRE(v2.x == 1.0);
        REQUIRE(v2.y == 2.0);
        REQUIRE(v2.z == 3.0);

        const nnm::Vector3 v3(1.0, 2.0, 3.0);
        REQUIRE(v3.x == 1.0);
        REQUIRE(v3.y == 2.0);
        REQUIRE(v3.z == 3.0);
    }

    SECTION("Static methods")
    {
        const auto v1 = nnm::Vector3<double>::all(3.0);
        REQUIRE(v1.x == 3.0);
        REQUIRE(v1.y == 3.0);
        REQUIRE(v1.z == 3.0);

        const auto v2 = nnm::Vector3<double>::zero();
        REQUIRE(v2.x == 0.0);
        REQUIRE(v2.y == 0.0);
        REQUIRE(v2.z == 0.0);

        const auto v3 = nnm::Vector3<double>::one();
        REQUIRE(v3.x == 1.0);
        REQUIRE(v3.y == 1.0);
        REQUIRE(v3.z == 1.0);
    }

    SECTION("abs")
    {
        REQUIRE(nnm::Vector3<double>(0.0, 1.0, -2.0).abs() == nnm::Vector3<double>(0.0, 1.0, 2.0));
    }

    SECTION("ceil")
    {
        REQUIRE(nnm::Vector3<double>(0.1, -2.1, 1.1).ceil() == nnm::Vector3<double>(1.0, -2.0, 2.0));
    }

    SECTION("clamp")
    {
        const nnm::Vector3 v(0.0, 10.0, -2.0);
        const nnm::Vector3 min(-1.0, 12.0, -5.0);
        const nnm::Vector3 max(1.0, 12.0, -3.0);
        REQUIRE(v.clamp(min, max) == nnm::Vector3(0.0, 12.0, -3.0));
    }

    SECTION("normalize")
    {
        const nnm::Vector3 v(1.0, -2.0, 3.0);
        REQUIRE(v.normalize().approx_equal(nnm::Vector3(0.267261, -0.534522, 0.801784)));
    }

    SECTION("direction_to")
    {
        nnm::Vector3 from(1.0, 1.0, 1.0);
        nnm::Vector3 to(2.0, 2.0, 2.0);
        auto direction = from.direction_to(to);
        REQUIRE(direction.approx_equal(nnm::Vector3<double>::all(0.57735)));

        from = nnm::Vector3(-1.0, -1.0, -1.0);
        to = nnm::Vector3(1.0, 1.0, 1.0);
        direction = from.direction_to(to);
        REQUIRE(direction.approx_equal(nnm::Vector3<double>::all(0.57735)));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(1.0, 0.0, 0.0);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 1.0));
        REQUIRE(nnm::approx_equal(direction.y, 0.0));
        REQUIRE(nnm::approx_equal(direction.z, 0.0));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(0.0, 1.0, 0.0);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0));
        REQUIRE(nnm::approx_equal(direction.y, 1.0));
        REQUIRE(nnm::approx_equal(direction.z, 0.0));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(0.0, 0.0, 1.0);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0));
        REQUIRE(nnm::approx_equal(direction.y, 0.0));
        REQUIRE(nnm::approx_equal(direction.z, 1.0));

        from = nnm::Vector3(1.0, 2.0, 3.0);
        to = nnm::Vector3(1.0, 2.0, 3.0);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0));
        REQUIRE(nnm::approx_equal(direction.y, 0.0));
        REQUIRE(nnm::approx_equal(direction.z, 0.0));
    }

    SECTION("distance_sqrd_to")
    {
        nnm::Vector3 from(1.0, 1.0, 1.0);
        nnm::Vector3 to(2.0, 2.0, 2.0);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 3.0));

        from = nnm::Vector3(-1.0, -1.0, -1.0);
        to = nnm::Vector3(1.0, 1.0, 1.0);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 12.0));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(3.0, 0.0, 0.0);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 9.0));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(0.0, 4.0, 0.0);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 16.0));

        from = nnm::Vector3(1.0, 2.0, 3.0);
        to = nnm::Vector3(1.0, 2.0, 3.0);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 0.0));
    }

    SECTION("distance_to")
    {
        nnm::Vector3 from(1.0, 1.0, 1.0);
        nnm::Vector3 to(2.0, 2.0, 2.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(3.0)));

        from = nnm::Vector3(-1.0, -1.0, -1.0);
        to = nnm::Vector3(1.0, 1.0, 1.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(12.0)));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(3.0, 0.0, 0.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 3.0));

        from = nnm::Vector3(0.0, 0.0, 0.0);
        to = nnm::Vector3(0.0, 4.0, 0.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 4.0));

        from = nnm::Vector3(1.0, 2.0, 3.0);
        to = nnm::Vector3(1.0, 2.0, 3.0);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 0.0));
    }

    SECTION("floor")
    {
        REQUIRE(nnm::Vector3<double>(0.1, -2.1, 1.1).floor() == nnm::Vector3<double>(0.0, -3.0, 1.0));
    }

    SECTION("length_sqrd")
    {
        const nnm::Vector3 v(1.0, 2.0, 3.0);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 14.0));
    }

    SECTION("length")
    {
        const nnm::Vector3 v(1.0, 2.0, 3.0);
        REQUIRE(nnm::approx_equal(v.length(), nnm::sqrt(14.0)));
    }

    SECTION("lerp")
    {
        nnm::Vector3 from(1.0, 1.0, 1.0);
        nnm::Vector3 to(3.0, 5.0, -2.0);
        REQUIRE(from.lerp(to, 0.0) == nnm::Vector3<double>(1.0, 1.0, 1.0));
        REQUIRE(from.lerp(to, 1.0) == nnm::Vector3<double>(3.0, 5.0, -2.0));
        REQUIRE(from.lerp(to, 0.5) == nnm::Vector3<double>(2.0, 3.0, -0.5));
        REQUIRE(from.lerp(to, 0.25) == nnm::Vector3<double>(1.5, 2.0, 0.25));
        REQUIRE(from.lerp(to, 0.75) == nnm::Vector3<double>(2.5, 4.0, -1.25));
    }

    SECTION("min/max_axis")
    {
        nnm::Vector3 v1(3.0, 4.0, -2.0);
        REQUIRE(v1.max_axis() == nnm::Axis3::y);
        REQUIRE(v1.min_axis() == nnm::Axis3::z);

        nnm::Vector3 v2(-100.0, 5.0, 100.0);
        REQUIRE(v2.max_axis() == nnm::Axis3::z);
        REQUIRE(v2.min_axis() == nnm::Axis3::x);

        nnm::Vector3 v3(0.0, 0.0, 0.0);
        REQUIRE(v3.max_axis() == nnm::Axis3::x);
        REQUIRE(v3.min_axis() == nnm::Axis3::x);
    }

    SECTION("approx_equal")
    {
        nnm::Vector3 v1(1.0, 1.0, 1.0);
        nnm::Vector3 v2(1.0 + nnm::epsilon / 2, 1.0, 1.0);
        REQUIRE(v1.approx_equal(v2));
        nnm::Vector3 v3(1.0, 1.0, 1.0);
        nnm::Vector3 v4(1.0 + 2 * nnm::epsilon, 1.0, 1.0);
        REQUIRE_FALSE(v3.approx_equal(v4));
    }

    SECTION("approx_zero")
    {
        nnm::Vector3 v1(0.0, 0.0, 0.0);
        REQUIRE(v1.approx_zero());
        nnm::Vector3 v2(nnm::epsilon, 0.0, 0.0);
        REQUIRE(v2.approx_zero());
        nnm::Vector3 v3(0.0, nnm::epsilon, nnm::epsilon);
        REQUIRE(v3.approx_zero());
        nnm::Vector3 v4(0.1, 0.1, 0.1);
        REQUIRE_FALSE(v4.approx_zero());
    }

    SECTION("dot")
    {
        const nnm::Vector3 v1(1.0, -2.0, 3.0);
        const nnm::Vector3 v2(-2.0, 4.0, -6.0);
        REQUIRE(v1.dot(v2) == -28);
    }

    SECTION("cross")
    {
        const nnm::Vector3 v1(1.0, -2.0, 3.0);
        const nnm::Vector3 v2(-2.0, 4.0, -6.0);
        REQUIRE(v1.cross(v2) == nnm::Vector3<double>::zero());
        const nnm::Vector3 v3(1.0, 2.0, 3.0);
        const nnm::Vector3 v4(-2.0, 4.0, 6.0);
        REQUIRE(v3.cross(v4) == nnm::Vector3(0.0, -12.0, 8.0));
    }

    SECTION("reflect")
    {
        nnm::Vector3 incident(1.0, 1.0, 1.0);
        nnm::Vector3 normal(0.0, 1.0, 0.0);
        REQUIRE(incident.reflect(normal) == nnm::Vector3(1.0, -1.0, 1.0));
    }

    SECTION("inverse")
    {
        nnm::Vector3 v(1.0, 2.0, -3.0);
        REQUIRE(v.inverse().approx_equal(nnm::Vector3(1.0, 0.5, -1.0 / 3.0)));
    }

    SECTION("clamp_length")
    {
        const nnm::Vector3 v(1.0, 2.0, 3.0);
        REQUIRE(v.clamp_length(2.0, 5.0).approx_equal(nnm::Vector3(1.0, 2.0, 3.0)));
        REQUIRE(v.clamp_length(2.0, 3.0).approx_equal(nnm::Vector3(0.80178, 1.603566, 2.405352)));
        REQUIRE(v.clamp_length(10.0, 100.0).approx_equal(nnm::Vector3(2.67261, 5.34522, 8.01784)));
    }

    SECTION("round")
    {
        const nnm::Vector3 v(1.1, -2.8, 0.0);
        REQUIRE(v.round() == nnm::Vector3(1.0, -3.0, 0.0));
    }

    SECTION("angle")
    {
        const nnm::Vector3 v1(1.0, 0.0, 0.0);
        const nnm::Vector3 v2(0.0, 1.0, 0.0);
        const nnm::Vector3 v3(1.0, 1.0, 0.0);
        REQUIRE(nnm::approx_equal(v1.angle(v2), nnm::pi / 2));
        REQUIRE(nnm::approx_equal(v1.angle(v3), nnm::pi / 4));
        REQUIRE(nnm::approx_zero(v1.angle(v1)));
        REQUIRE(nnm::approx_zero(v2.angle(v2)));
        REQUIRE(nnm::approx_zero(v3.angle(v3)));
    }

    SECTION("rotate")
    {
        const nnm::Vector3 v(1.0, 2.0, 3.0);
        const nnm::Vector3 axis(0.0, 0.0, 1.0);
        const double angle = nnm::pi / 2;

        REQUIRE(v.rotate(axis, angle).approx_equal(nnm::Vector3(-2.0, 1.0, 3.0)));
        REQUIRE(v.rotate(axis, 2 * angle).approx_equal(nnm::Vector3(-1.0, -2.0, 3.0)));
        REQUIRE(v.rotate(axis, 4 * angle).approx_equal(v));
        REQUIRE(v.rotate(axis, 0).approx_equal(v));
    }

    SECTION("rotate by matrix")
    {
        // TODO
    }

    SECTION("transform by matrix")
    {
    }

    nnm::Vector3 v1(1.0, 2.0, 3.0);
    nnm::Vector3 v2(3.0, 4.0, -2.0);
    nnm::Vector3 v3(1.0, 2.0, 3.0);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 * v2 == nnm::Vector3(3.0, 8.0, -6.0));
        REQUIRE(v1 * 2.0 == nnm::Vector3(2.0, 4.0, 6.0));
        REQUIRE(v2 / v1 == nnm::Vector3(3.0, 2.0, -2.0 / 3.0));
        REQUIRE(v2 / 2.0 == nnm::Vector3(1.5, 2.0, -1.0));
        REQUIRE(v1 + v2 == nnm::Vector3(4.0, 6.0, 1.0));
        REQUIRE(v2 - v1 == nnm::Vector3(2.0, 2.0, -5.0));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector3(-1.0, -2.0, -3.0));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector3 v1_copy(v1);
        nnm::Vector3 v2_copy(v2);
        v1 *= v2;
        REQUIRE(v1 == nnm::Vector3(3.0, 8.0, -6.0));
        v1 = v1_copy;
        v1 *= 2.0;
        REQUIRE(v1 == nnm::Vector3(2.0, 4.0, 6.0));
        v1 = v1_copy;
        v2 /= v1;
        REQUIRE(v2 == nnm::Vector3(3.0, 2.0, -2.0 / 3.0));
        v2 = v2_copy;
        v2 /= 2.0;
        REQUIRE(v2 == nnm::Vector3(1.5, 2.0, -1.0));
        v2 = v2_copy;
        v1 += v2;
        REQUIRE(v1 == nnm::Vector3(4.0, 6.0, 1.0));
        v1 = v1_copy;
        v2 -= v1;
        REQUIRE(v2 == nnm::Vector3(2.0, 2.0, -5.0));
        v2 = v2_copy;
    }

    SECTION("Comparison Operators")
    {
        REQUIRE(v1 < v2);
        REQUIRE(v1 <= v2);
        REQUIRE_FALSE(v1 > v2);
        REQUIRE_FALSE(v1 >= v2);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1.0);
        REQUIRE(v1[1] == 2.0);
        REQUIRE(v1[2] == 3.0);

        REQUIRE(v1[nnm::Axis3::x] == 1.0);
        REQUIRE(v1[nnm::Axis3::y] == 2.0);
        REQUIRE(v1[nnm::Axis3::z] == 3.0);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector3(0.0, 0.0, 0.0)));
    }
}
