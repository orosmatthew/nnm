#include <catch_amalgamated.hpp>
#include <nnm/nnm.hpp>

// ReSharper disable CppDFATimeOver

TEST_CASE("abs", "[abs]")
{
    REQUIRE(nnm::abs(0) == 0);
    REQUIRE(nnm::abs(1) == 1);
    REQUIRE(nnm::abs(-1) == 1);
    REQUIRE(nnm::abs(0.0f) == 0.0f);
    REQUIRE(nnm::abs(1.0f) == 1.0f);
    REQUIRE(nnm::abs(-1.0f) == 1.0f);
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

    REQUIRE(nnm::max(5.0f, 10.0f) == 10.0f);
    REQUIRE(nnm::max(10.0f, 5.0f) == 10.0f);
    REQUIRE(nnm::max(-5.0f, -10.0f) == -5.0f);
    REQUIRE(nnm::max(-10.0f, -5.0f) == -5.0f);
    REQUIRE(nnm::max(0.0f, 0.0f) == 0.0f);
    REQUIRE(nnm::max(3.14159f, 2.71828f) == 3.14159f);
    REQUIRE(nnm::max(-3.14159f, -2.71828f) == -2.71828f);
}

TEST_CASE("approx_lte", "[approx_lte]")
{
    REQUIRE(nnm::approx_lte(1.0f, 1.0f, 0.01f));
    REQUIRE(nnm::approx_lte(1.0f, 1.005f, 0.01f));
    REQUIRE(nnm::approx_lte(1.0f, 1.01f, 0.01f));
    REQUIRE(nnm::approx_lte(1.0f, 1.02f, 0.01f));
    REQUIRE(nnm::approx_lte(-1.0f, -1.005f, 0.01f));
    REQUIRE(nnm::approx_lte(1.0f, 1.0f, -0.01f));
    REQUIRE(nnm::approx_lte(1e-15f, 1e-16f, 1e-14f));
    REQUIRE_FALSE(nnm::approx_lte(4.0f, 2.0f, 1e-10f));
}

TEST_CASE("is_equal_approx", "[is_equal_approx]")
{
    REQUIRE(nnm::approx_equal(1.0f, 1.0f, 0.01f));
    REQUIRE(nnm::approx_equal(1.0f, 1.005f, 0.01f));
    REQUIRE(nnm::approx_equal(1.0f, 1.01f, 0.01f));
    REQUIRE_FALSE(nnm::approx_equal(1.0f, 1.02f, 0.01f));
    REQUIRE(nnm::approx_equal(-1.0f, -1.005f, 0.01f));
    REQUIRE(nnm::approx_equal(0.0f, 0.0f, 0.01f));
    REQUIRE(nnm::approx_equal(0.0f, 0.005f, 0.01f));
    REQUIRE(nnm::approx_equal(0.005f, 0.0f, 0.01f));
    REQUIRE(nnm::approx_equal(0.0f, 0.0f, 0.0f));
    REQUIRE(nnm::approx_equal(1.0f, 1.005f, -0.01f));
    REQUIRE(nnm::approx_equal(1.0e20f, 1.000000000001e20f, 1e-10f));
}

TEST_CASE("approx_gte", "[approx_gte]")
{
    REQUIRE(nnm::approx_gte(1.0f, 1.0f, 0.01f));
    REQUIRE(nnm::approx_gte(1.0f, 0.995f, 0.01f));
    REQUIRE(nnm::approx_gte(1.0f, 0.99f, 0.01f));
    REQUIRE(nnm::approx_gte(1.0f, 0.98f, 0.01f));
    REQUIRE(nnm::approx_gte(-1.0f, -1.005f, 0.01f));
    REQUIRE(nnm::approx_gte(1.0f, 1.0f, -0.01f));
    REQUIRE(nnm::approx_gte(1e-15f, 1e-16f, 1e-14f));
    REQUIRE_FALSE(nnm::approx_gte(2.0f, 4.0f, 1e-14f));
}

TEST_CASE("ceil", "[ceil]")
{
    REQUIRE(nnm::ceil(5.3f) == 6.0f);
    REQUIRE(nnm::ceil(5.7f) == 6.0f);
    REQUIRE(nnm::ceil(5.0f) == 5.0f);
    REQUIRE(nnm::ceil(-5.3f) == -5.0f);
    REQUIRE(nnm::ceil(-5.7f) == -5.0f);
    REQUIRE(nnm::ceil(-5.0f) == -5.0f);
    REQUIRE(nnm::ceil(0.0f) == 0.0f);
    REQUIRE(nnm::ceil(1.0e20f) == 1.0e20f);
    REQUIRE(nnm::ceil(-1.0e20f) == -1.0e20f);
    REQUIRE(nnm::ceil(3.14159f) == 4.0f);
    REQUIRE(nnm::ceil(-3.14159f) == -3.0f);
}

TEST_CASE("clamp", "[clamp]")
{
    REQUIRE(nnm::clamp(5, 0, 10) == 5);
    REQUIRE(nnm::clamp(-5, 0, 10) == 0);
    REQUIRE(nnm::clamp(15, 0, 10) == 10);
    REQUIRE(nnm::clamp(5, 5, 5) == 5);
    REQUIRE(nnm::clamp(3.5f, 1.0f, 5.0f) == 3.5f);
    REQUIRE(nnm::clamp(0.5f, 1.0f, 5.0f) == 1.0f);
    REQUIRE(nnm::clamp(6.0f, 1.0f, 5.0f) == 5.0f);
    REQUIRE(nnm::clamp(-5, -10, -2) == -5);
    REQUIRE(nnm::clamp(-15, -10, -2) == -10);
    REQUIRE(nnm::clamp(-3, -5, -1) == -3);
    REQUIRE(nnm::clamp(-6, -5, -1) == -5);
}

TEST_CASE("sqrt", "[sqrt]")
{
    REQUIRE(nnm::sqrt(4.0f) == 2.0f);
    REQUIRE(nnm::sqrt(9.0f) == 3.0f);
    REQUIRE(nnm::sqrt(16.0f) == 4.0f);

    REQUIRE(nnm::approx_equal(nnm::sqrt(4.0f), 2.0));
    REQUIRE(nnm::approx_equal(nnm::sqrt(9.0f), 3.0));
    REQUIRE(nnm::approx_equal(nnm::sqrt(16.0f), 4.0));

    REQUIRE(nnm::sqrt(0.0f) == 0.0f);

    REQUIRE(nnm::approx_equal(nnm::sqrt(1.0e20f), 1.0e10f));
}

TEST_CASE("pow", "[pow]")
{
    REQUIRE(nnm::pow(2.0f, 3.0f) == 8.0f);
    REQUIRE(nnm::pow(3.0f, 2.0f) == 9.0f);
    REQUIRE(nnm::pow(4.0f, 0.0f) == 1.0f);

    REQUIRE(nnm::approx_equal(nnm::pow(2.0f, 3.0f), 8.0f));
    REQUIRE(nnm::approx_equal(nnm::pow(3.0f, 2.0f), 9.0f));
    REQUIRE(nnm::approx_equal(nnm::pow(4.0f, 0.0f), 1.0f));

    REQUIRE(nnm::approx_equal(nnm::pow(-2.0f, 2.0f), 4.0f));
    REQUIRE(nnm::approx_equal(nnm::pow(-3.0f, 2.0f), 9.0f));

    REQUIRE(nnm::approx_equal(nnm::pow(-2.0f, 3.0f), -8.0f));
    REQUIRE(nnm::approx_equal(nnm::pow(-3.0f, 3.0f), -27.0f));

    REQUIRE(nnm::approx_equal(nnm::pow(0.0f, 3.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::pow(0.0f, 0.0f), 1.0f));

    REQUIRE(nnm::approx_equal(nnm::pow(0.5f, 2.0f), 0.25f));
    REQUIRE(nnm::approx_equal(nnm::pow(0.25f, 0.5f), 0.5f));

    REQUIRE(nnm::approx_equal(nnm::pow(10.0f, 10.0f), 1.0e10f));
    REQUIRE(nnm::approx_equal(nnm::pow(2.f, 100.0f), 1.2676506002282294e30f));
}

TEST_CASE("sqrd", "[sqrd]")
{
    REQUIRE(nnm::sqrd(2) == 4);
    REQUIRE(nnm::sqrd(3) == 9);
    REQUIRE(nnm::sqrd(-4) == 16);

    REQUIRE(nnm::approx_equal(nnm::sqrd(2.0f), 4.0f));
    REQUIRE(nnm::approx_equal(nnm::sqrd(3.0f), 9.0f));
    REQUIRE(nnm::approx_equal(nnm::sqrd(-4.0f), 16.0f));

    REQUIRE(nnm::sqrd(0) == 0);
    REQUIRE(nnm::sqrd(0.0f) == 0.0f);

    REQUIRE(nnm::approx_equal(nnm::sqrd(1.0e10f), 1.0e20f));
    REQUIRE(nnm::approx_equal(nnm::sqrd(-1.0e10f), 1.0e20f));
}

TEST_CASE("floor", "[floor]")
{
    REQUIRE(nnm::floor(5.3f) == 5.0f);
    REQUIRE(nnm::floor(5.7f) == 5.0f);
    REQUIRE(nnm::floor(5.0f) == 5.0f);

    REQUIRE(nnm::floor(-5.3f) == -6.0f);
    REQUIRE(nnm::floor(-5.7f) == -6.0f);
    REQUIRE(nnm::floor(-5.0f) == -5.0f);

    REQUIRE(nnm::floor(0.0f) == 0.0f);

    REQUIRE(nnm::floor(1.0e20f) == 1.0e20f);
    REQUIRE(nnm::floor(-1.0e20f) == -1.0e20f);

    REQUIRE(nnm::floor(3.14159f) == 3.0f);
    REQUIRE(nnm::floor(-3.14159f) == -4.0f);
}

TEST_CASE("lerp", "[lerp]")
{
    REQUIRE(nnm::lerp(0.0f, 10.0f, 0.5f) == 5.0f);
    REQUIRE(nnm::lerp(0.0f, 10.0f, 0.25f) == 2.5f);
    REQUIRE(nnm::lerp(-5.0f, 5.0f, 0.75f) == 2.5f);

    REQUIRE(nnm::lerp(-10.0f, -20.0f, 0.5f) == -15.0f);
    REQUIRE(nnm::lerp(-10.0f, -20.0f, 0.25f) == -12.5f);
    REQUIRE(nnm::lerp(-15.0f, -25.0f, 0.75f) == -22.5f);

    REQUIRE(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);
    REQUIRE(nnm::lerp(5.0f, 10.0f, 0.0f) == 5.0f);

    REQUIRE(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);
    REQUIRE(nnm::lerp(5.0f, 10.0f, 1.0f) == 10.0f);
}

TEST_CASE("sin", "[sin]")
{
    REQUIRE(nnm::approx_equal(nnm::sin(0.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 6.0f), 0.5f));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 3.0f), nnm::sqrt(3.0f) / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi / 2.0f), 1.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(nnm::pi), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(3.0f * nnm::pi / 2.0f), -1.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(2.0f * nnm::pi), 0.0f));

    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 6.0f), -0.5f));
    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 4.0f), -1.0f / nnm::sqrt(2.0f)));
    REQUIRE(nnm::approx_equal(nnm::sin(-nnm::pi / 3.0f), -nnm::sqrt(3.0f) / 2.0f));

    REQUIRE(nnm::approx_equal(nnm::sin(4.0f * nnm::pi), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::sin(6.0f * nnm::pi), 0.0f));
}

TEST_CASE("cos", "[cos]")
{
    REQUIRE(nnm::approx_equal(nnm::cos(0.0f), 1.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 6.0f), nnm::sqrt(3.0f) / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 3.0f), 0.5f));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi / 2.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(nnm::pi), -1.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(3.0f * nnm::pi / 2.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(2.0f * nnm::pi), 1.0f));

    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 6.0f), nnm::sqrt(3.0f) / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 4.0f), 1.0f / nnm::sqrt(2.0f)));
    REQUIRE(nnm::approx_equal(nnm::cos(-nnm::pi / 3.0f), 0.5f));

    REQUIRE(nnm::approx_equal(nnm::cos(4.0f * nnm::pi), 1.0f));
    REQUIRE(nnm::approx_equal(nnm::cos(6.0f * nnm::pi), 1.0f));
}

TEST_CASE("tan", "[tan]")
{
    REQUIRE(nnm::approx_equal(nnm::tan(0.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 4.0f), 1.0f));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 6.0f), 1.0f / nnm::sqrt(3.0f)));

    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 3.0f), nnm::sqrt(3.0f)));
    REQUIRE(nnm::approx_equal(nnm::tan(nnm::pi / 2.0f - 0.01f), 99.9967f));

    REQUIRE(nnm::approx_equal(nnm::tan(-nnm::pi / 3.0f), -nnm::sqrt(3.0f)));
    REQUIRE(nnm::approx_equal(nnm::tan(-nnm::pi / 2.0f + 0.01f), -99.9967f));

    REQUIRE(nnm::approx_equal(nnm::tan(3.0f * nnm::pi), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::tan(6.0f * nnm::pi), 0.0f));
}

TEST_CASE("round", "[round]")
{
    REQUIRE(nnm::round(5.3f) == 5.0f);
    REQUIRE(nnm::round(5.7f) == 6.0f);
    REQUIRE(nnm::round(5.0f) == 5.0f);

    REQUIRE(nnm::round(-5.3f) == -5.0f);
    REQUIRE(nnm::round(-5.7f) == -6.0f);
    REQUIRE(nnm::round(-5.0f) == -5.0f);

    REQUIRE(nnm::round(0.0f) == 0.0f);

    REQUIRE(nnm::round(3.14159f) == 3.0f);
    REQUIRE(nnm::round(-3.14159f) == -3.0f);
}

TEST_CASE("atan", "[atan]")
{
    REQUIRE(nnm::approx_equal(nnm::atan(0.5f), 0.4636476f));
    REQUIRE(nnm::approx_equal(nnm::atan(1.0f), 0.7853981f));
    REQUIRE(nnm::approx_equal(nnm::atan(2.0f), 1.1071487f));

    REQUIRE(nnm::approx_equal(nnm::atan(-0.5f), -0.4636476f));
    REQUIRE(nnm::approx_equal(nnm::atan(-1.0f), -0.7853981f));
    REQUIRE(nnm::approx_equal(nnm::atan(-2.0f), -1.1071487f));

    REQUIRE(nnm::approx_equal(nnm::atan(0.0f), 0.0f));

    REQUIRE(nnm::approx_equal(nnm::atan(1.0e20f), 1.5707963f));
    REQUIRE(nnm::approx_equal(nnm::atan(-1.0e20f), -1.5707963f));
}

TEST_CASE("atan2", "[atan2]")
{
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0f, 1.0f), 0.7853981633974483f));
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0f, 2.0f), 0.4636476090008061f));

    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0f, -1.0f), -2.356194490192345f));
    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0f, 2.0f), -0.4636476090008061f));

    REQUIRE(nnm::approx_equal(nnm::atan2(0.0f, 1.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::atan2(1.0f, 0.0f), 1.5707963267948966f));
    REQUIRE(nnm::approx_equal(nnm::atan2(0.0f, 0.0f), 0.0f));

    REQUIRE(nnm::approx_equal(nnm::atan2(1.0e20f, 1.0e20f), 0.7853981633974483f));
    REQUIRE(nnm::approx_equal(nnm::atan2(-1.0e20f, -1.0e20f), -2.356194490192345f));
}

TEST_CASE("radians", "[radians]")
{
    REQUIRE(nnm::approx_equal(nnm::radians(0.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(45.0f), nnm::pi / 4.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(90.0f), nnm::pi / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(180.0f), nnm::pi));
    REQUIRE(nnm::approx_equal(nnm::radians(270.0f), 3.0f * nnm::pi / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(360.0f), 2.0f * nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(-45.0f), -nnm::pi / 4.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(-90.0f), -nnm::pi / 2.0f));
    REQUIRE(nnm::approx_equal(nnm::radians(-180.0f), -nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(720.0f), 4.0f * nnm::pi));
    REQUIRE(nnm::approx_equal(nnm::radians(1080.0f), 6.0f * nnm::pi));

    REQUIRE(nnm::approx_equal(nnm::radians(180.0f, 3.14159f), 3.14159f));
}

TEST_CASE("degrees", "[degrees]")
{
    REQUIRE(nnm::approx_equal(nnm::degrees(0.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi / 4.0f), 45.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi / 2.0f), 90.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(nnm::pi), 180.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(3.0f * nnm::pi / 2.0f), 270.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(2.0f * nnm::pi), 360.0f));

    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi / 4.0f), -45.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi / 2.0f), -90.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(-nnm::pi), -180.0f));

    REQUIRE(nnm::approx_equal(nnm::degrees(4.0f * nnm::pi), 720.0f));
    REQUIRE(nnm::approx_equal(nnm::degrees(6.0f * nnm::pi), 1080.0f));

    REQUIRE(nnm::approx_equal(nnm::degrees(3.14159f, 3.14159f), 180.0f));
}

TEST_CASE("asin", "[asin]")
{
    REQUIRE(nnm::approx_equal(nnm::asin(0.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::asin(0.5f), 0.5235987756f));
    REQUIRE(nnm::approx_equal(nnm::asin(-0.5f), -0.5235987756f));
    REQUIRE(nnm::approx_equal(nnm::asin(1.0f), 1.570796327f));
    REQUIRE(nnm::approx_equal(nnm::asin(-1.0f), -1.570796327f));

    // TODO: Check range
}

TEST_CASE("acos", "[acos]")
{
    REQUIRE(nnm::approx_equal(nnm::acos(1.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::acos(0.5f), 1.047197551f));
    REQUIRE(nnm::approx_equal(nnm::acos(-0.5f), 2.094395102f));
    REQUIRE(nnm::approx_equal(nnm::acos(0.0f), 1.570796327f));
    REQUIRE(nnm::approx_equal(nnm::acos(-1.0f), 3.141592654f));

    // TODO: Check range
}

TEST_CASE("min", "[min]")
{
    REQUIRE(nnm::min(1, 2) == 1);
    REQUIRE(nnm::min(5, 3) == 3);
    REQUIRE(nnm::min(-1, -5) == -5);

    REQUIRE(nnm::min(1.0f, 2.0f) == 1.0f);
    REQUIRE(nnm::min(5.5f, 3.5f) == 3.5f);
    REQUIRE(nnm::min(-1.0f, -5.0f) == -5.0f);

    REQUIRE(nnm::min('a', 'b') == 'a');
    REQUIRE(nnm::min(3.14f, 2.71f) == 2.71f);
}

TEST_CASE("log2", "[log2]")
{
    REQUIRE(nnm::approx_equal(nnm::log2(1.0f), 0.0f));
    REQUIRE(nnm::approx_equal(nnm::log2(2.0f), 1.0f));
    REQUIRE(nnm::approx_equal(nnm::log2(8.0f), 3.0f));
    REQUIRE(nnm::approx_equal(nnm::log2(16.0f), 4.0f));

    REQUIRE(nnm::approx_equal(nnm::log2(0.5f), -1.0f));
    REQUIRE(nnm::approx_equal(nnm::log2(4.0f), 2.0f));

    // TODO: Check 0 and negative
}

TEST_CASE("Vector2", "[Vector2]")
{
    SECTION("Default constructor")
    {
        const nnm::Vector2 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
    }

    SECTION("From Vector2i constructor")
    {
        const nnm::Vector2 v(nnm::Vector2i(1, 2));
        REQUIRE(v.x == 1.0f);
        REQUIRE(v.y == 2.0f);
    }

    SECTION("Constructor with params")
    {
        const nnm::Vector2 v(1.0f, 2.0f);
        REQUIRE(v.x == 1.0f);
        REQUIRE(v.y == 2.0f);
    }

    SECTION("Static methods")
    {
        const auto all_threes = nnm::Vector2::all(3.0f);
        REQUIRE(all_threes.x == 3.0f);
        REQUIRE(all_threes.y == 3.0f);

        const auto zero = nnm::Vector2::zero();
        REQUIRE(zero.x == 0.0f);
        REQUIRE(zero.y == 0.0f);

        const auto one = nnm::Vector2::one();
        REQUIRE(one.x == 1.0f);
        REQUIRE(one.y == 1.0f);
    }

    SECTION("abs")
    {
        const nnm::Vector2 v(1.0f, -2.0f);
        REQUIRE(v.abs() == nnm::Vector2(1.0f, 2.0f));
    }

    SECTION("aspect_ratio")
    {
        const nnm::Vector2 v(1.0f, -2.0f);
        REQUIRE(v.aspect_ratio() == 1.0f / -2.0f);
    }

    SECTION("ceil")
    {
        const nnm::Vector2 v(1.1f, -1.9f);
        REQUIRE(v.ceil() == nnm::Vector2(2.0f, -1.0f));
    }

    SECTION("clamp")
    {
        const nnm::Vector2 v(1.1f, -3.0f);
        REQUIRE(v.clamp({ 1.0f, -2.0f }, { 2.0f, 2.0f }) == nnm::Vector2(1.1f, -2.0f));
    }

    SECTION("normalize")
    {
        const nnm::Vector2 v(1.1f, -3.0f);
        const auto norm = v.normalize();
        REQUIRE(nnm::approx_equal(norm.x, 0.344255f));
        REQUIRE(nnm::approx_equal(norm.y, -0.938876f));
    }

    SECTION("direction_to")
    {
        const nnm::Vector2 from1(1.0f, 1.0f);
        const nnm::Vector2 to1(2.0f, 2.0f);
        auto direction1 = from1.direction_to(to1);
        REQUIRE(nnm::approx_equal(direction1.x, 0.7071067812f));
        REQUIRE(nnm::approx_equal(direction1.y, 0.7071067812f));

        const nnm::Vector2 from2(-1.0f, -1.0f);
        const nnm::Vector2 to2(1.0f, 1.0f);
        auto direction2 = from2.direction_to(to2);
        REQUIRE(nnm::approx_equal(direction2.x, 0.7071067812f));
        REQUIRE(nnm::approx_equal(direction2.y, 0.7071067812f));

        const nnm::Vector2 from3(0.0f, 0.0f);
        const nnm::Vector2 to3(1.0f, 0.0f);
        auto direction3 = from3.direction_to(to3);
        REQUIRE(nnm::approx_equal(direction3.x, 1.0f));
        REQUIRE(nnm::approx_equal(direction3.y, 0.0f));

        const nnm::Vector2 from4(0.0f, 0.0f);
        const nnm::Vector2 to4(0.0f, 1.0f);
        auto direction4 = from4.direction_to(to4);
        REQUIRE(nnm::approx_equal(direction4.x, 0.0f));
        REQUIRE(nnm::approx_equal(direction4.y, 1.0f));

        const nnm::Vector2 from5(1.0f, 2.0f);
        const nnm::Vector2 to5(1.0f, 2.0f);
        auto direction5 = from5.direction_to(to5);
        REQUIRE(nnm::approx_equal(direction5.x, 0.0f));
        REQUIRE(nnm::approx_equal(direction5.y, 0.0f));
    }

    SECTION("distance_sqrd_to")
    {
        const nnm::Vector2 from1(1.0f, 1.0f);
        const nnm::Vector2 to1(2.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from1.distance_sqrd_to(to1), 2.0f));

        const nnm::Vector2 from2(-1.0f, -1.0f);
        const nnm::Vector2 to2(1.0f, 1.0f);
        REQUIRE(nnm::approx_equal(from2.distance_sqrd_to(to2), 8.0f));

        const nnm::Vector2 from3(0.0f, 0.0f);
        const nnm::Vector2 to3(3.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from3.distance_sqrd_to(to3), 9.0f));

        const nnm::Vector2 from4(0.0f, 0.0f);
        const nnm::Vector2 to4(0.0f, 4.0f);
        REQUIRE(nnm::approx_equal(from4.distance_sqrd_to(to4), 16.0f));

        const nnm::Vector2 from5(1.0f, 2.0f);
        const nnm::Vector2 to5(1.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from5.distance_sqrd_to(to5), 0.0f));
    }

    SECTION("distance_to")
    {
        nnm::Vector2 from(1.0f, 1.0f);
        nnm::Vector2 to(2.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(2.0f)));

        from = nnm::Vector2(-1.0f, -1.0f);
        to = nnm::Vector2(1.0f, 1.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(8.0f)));

        from = nnm::Vector2(0.0f, 0.0f);
        to = nnm::Vector2(3.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 3.0f));

        from = nnm::Vector2(0.0f, 0.0f);
        to = nnm::Vector2(0.0f, 4.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 4.0f));

        from = nnm::Vector2(1.0f, 2.0f);
        to = nnm::Vector2(1.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 0.0f));
    }

    SECTION("floor")
    {
        const nnm::Vector2 v(1.1f, -1.9f);
        REQUIRE(v.floor() == nnm::Vector2(1.0f, -2.0f));
    }

    SECTION("length_sqrd")
    {
        nnm::Vector2 v(3.0f, 4.0f);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 25.0f));

        v = nnm::Vector2(-2.0f, 5.0f);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 29.0f));

        v = nnm::Vector2(0.0f, 0.0f);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 0.0f));
    }

    SECTION("length")
    {
        nnm::Vector2 v(3.0f, 4.0f);
        REQUIRE(nnm::approx_equal(v.length(), 5.0f));

        v = nnm::Vector2(-2.0f, 5.0f);
        REQUIRE(nnm::approx_equal(v.length(), sqrt(29.0f)));

        v = nnm::Vector2(0.0f, 0.0f);
        REQUIRE(nnm::approx_equal(v.length(), 0.0f));
    }

    SECTION("lerp")
    {
        const nnm::Vector2 from(1.0f, 1.0f);
        const nnm::Vector2 to(3.0f, 5.0f);
        REQUIRE(from.lerp(to, 0.0f) == nnm::Vector2(1.0f, 1.0f));
        REQUIRE(from.lerp(to, 1.0f) == nnm::Vector2(3.0f, 5.0f));
        REQUIRE(from.lerp(to, 0.5f) == nnm::Vector2(2.0f, 3.0f));
        REQUIRE(from.lerp(to, 0.25f) == nnm::Vector2(1.5f, 2.0f));
        REQUIRE(from.lerp(to, 0.75f) == nnm::Vector2(2.5f, 4.0f));
    }

    SECTION("min/max_axis")
    {
        nnm::Vector2 v1(3.0f, 4.0f);
        REQUIRE(v1.max_axis() == nnm::Axis2::y);
        REQUIRE(v1.min_axis() == nnm::Axis2::x);

        nnm::Vector2 v2(2.0f, 5.0f);
        REQUIRE(v2.max_axis() == nnm::Axis2::y);
        REQUIRE(v2.min_axis() == nnm::Axis2::x);

        nnm::Vector2 v3(0.0f, 0.0f);
        REQUIRE(v3.max_axis() == nnm::Axis2::x);
        REQUIRE(v3.min_axis() == nnm::Axis2::x);
    }

    SECTION("approx_equal")
    {
        nnm::Vector2 v1(1.0f, 1.0f);
        nnm::Vector2 v2(1.0f + nnm::epsilon / 2.0f, 1.0f);
        REQUIRE(v1.approx_equal(v2));
        nnm::Vector2 v3(1.0f, 1.0f);
        nnm::Vector2 v4(1.0f + 2.0f * nnm::epsilon, 1.0f);
        REQUIRE_FALSE(v3.approx_equal(v4));
    }

    SECTION("approx_zero")
    {
        nnm::Vector2 v1(0.0f, 0.0f);
        REQUIRE(v1.approx_zero());
        nnm::Vector2 v2(nnm::epsilon, 0.0f);
        REQUIRE(v2.approx_zero());
        nnm::Vector2 v3(0.0f, nnm::epsilon);
        REQUIRE(v3.approx_zero());
        nnm::Vector2 v4(0.1f, 0.1f);
        REQUIRE_FALSE(v4.approx_zero());
    }

    SECTION("dot")
    {
        nnm::Vector2 v1(2.0f, 3.0f);
        nnm::Vector2 v2(4.0f, 5.0f);
        REQUIRE(v1.dot(v2) == 23.0f);
    }

    SECTION("reflect")
    {
        nnm::Vector2 incident(3.0f, 4.0f);
        nnm::Vector2 normal(1.0f, 0.0f);
        REQUIRE(incident.reflect(normal) == nnm::Vector2(-3.0f, 4.0f));
    }

    SECTION("rotate")
    {
        nnm::Vector2 v(1.0f, 0.0f);
        REQUIRE(v.rotate(nnm::radians(90.0f)).approx_equal(nnm::Vector2(0.0f, 1.0f)));
    }

    SECTION("inverse")
    {
        nnm::Vector2 v(2.0f, 3.0f);
        REQUIRE(v.inverse().approx_equal(nnm::Vector2(1.0f / 2.0f, 1.0f / 3.0f)));
    }

    SECTION("clamp_length")
    {
        REQUIRE(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 5.0f) == nnm::Vector2(3.0f, 4.0f));
        REQUIRE(nnm::Vector2(1.0f, 2.0f).clamp_length(0.5f, 3.0f) == nnm::Vector2(1.0f, 2.0f));
        REQUIRE(nnm::Vector2(3.0f, 4.0f).clamp_length(2.0f, 2.0f).approx_equal(nnm::Vector2(1.2f, 1.6f)));
        REQUIRE(nnm::approx_equal(nnm::Vector2(1.0f, 1.0f).clamp_length(2.0f, 5.0f).length(), 2.0f));
        REQUIRE(nnm::Vector2(5.0f, 6.0f).clamp_length(2.0f, 5.0f).length() == 5.0f);
    }

    nnm::Vector2 v1(1.0f, 2.0f);
    nnm::Vector2 v2(3.0f, 4.0f);
    nnm::Vector2 v3(1.0f, 2.0f);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 * v2 == nnm::Vector2(3.0f, 8.0f));
        REQUIRE(v1 * 2.0f == nnm::Vector2(2.0f, 4.0f));
        REQUIRE(v2 / v1 == nnm::Vector2(3.0f, 2.0f));
        REQUIRE(v2 / 2.0f == nnm::Vector2(1.5f, 2.0f));
        REQUIRE(v1 + v2 == nnm::Vector2(4.0f, 6.0f));
        REQUIRE(v2 - v1 == nnm::Vector2(2.0f, 2.0f));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector2(-1.0f, -2.0f));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector2 v_copy(v1);

        v1 *= v2;
        REQUIRE(v1 == nnm::Vector2(3.0f, 8.0f));
        v1 = v_copy;

        v1 *= 2.0f;
        REQUIRE(v1 == nnm::Vector2(2.0f, 4.0f));
        v1 = v_copy;

        v2 /= v1;
        REQUIRE(v2 == nnm::Vector2(3.0f, 2.0f));

        v2 /= 2.0f;
        REQUIRE(v2 == nnm::Vector2(1.5f, 1.0f));
        v2 = v_copy;

        v1 += v2;
        REQUIRE(v1 == nnm::Vector2(2.0f, 4.0f));
        v1 = v_copy;

        v2 -= v1;
        REQUIRE(v2 == nnm::Vector2(0.0f, 0.0f));
        v2 = v_copy;
    }

    SECTION("Comparison Operator")
    {
        REQUIRE(v1 < v2);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1.0f);
        REQUIRE(v1[1] == 2.0f);

        REQUIRE(v1[nnm::Axis2::x] == 1.0f);
        REQUIRE(v1[nnm::Axis2::y] == 2.0f);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector2(0.0f, 0.0f)));
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
        REQUIRE(nnm::Vector2i(1, -2).aspect_ratio() == 1.0f / -2.0f);
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
        REQUIRE(nnm::approx_equal(nnm::Vector2i(3, 4).length(), 5.0f));
        REQUIRE(nnm::approx_equal(nnm::Vector2i(-2, 5).length(), nnm::sqrt(29.0f)));
        REQUIRE(nnm::approx_equal(nnm::Vector2i(0, 0).length(), 0.0f));
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

    SECTION("Comparison Operator")
    {
        REQUIRE(v1 < v2);
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
        const nnm::Vector3 v1;
        REQUIRE(v1.x == 0.0f);
        REQUIRE(v1.y == 0.0f);

        const nnm::Vector3 v2(nnm::Vector3i(1, 2, 3));
        REQUIRE(v2.x == 1.0f);
        REQUIRE(v2.y == 2.0f);
        REQUIRE(v2.z == 3.0f);

        const nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
        REQUIRE(v3.x == 1.0f);
        REQUIRE(v3.y == 2.0f);
        REQUIRE(v3.z == 3.0f);
    }

    SECTION("Static methods")
    {
        const auto v1 = nnm::Vector3::all(3.0f);
        REQUIRE(v1.x == 3.0f);
        REQUIRE(v1.y == 3.0f);
        REQUIRE(v1.z == 3.0f);

        const auto v2 = nnm::Vector3::zero();
        REQUIRE(v2.x == 0.0f);
        REQUIRE(v2.y == 0.0f);
        REQUIRE(v2.z == 0.0f);

        const auto v3 = nnm::Vector3::one();
        REQUIRE(v3.x == 1.0f);
        REQUIRE(v3.y == 1.0f);
        REQUIRE(v3.z == 1.0f);
    }

    SECTION("abs")
    {
        REQUIRE(nnm::Vector3(0.0f, 1.0f, -2.0f).abs() == nnm::Vector3(0.0f, 1.0f, 2.0f));
    }

    SECTION("ceil")
    {
        REQUIRE(nnm::Vector3(0.1f, -2.1f, 1.1f).ceil() == nnm::Vector3(1.0f, -2.0f, 2.0f));
    }

    SECTION("clamp")
    {
        const nnm::Vector3 v(0.0f, 10.0f, -2.0f);
        const nnm::Vector3 min(-1.0f, 12.0f, -5.0f);
        const nnm::Vector3 max(1.0f, 12.0f, -3.0f);
        REQUIRE(v.clamp(min, max) == nnm::Vector3(0.0f, 12.0f, -3.0f));
    }

    SECTION("normalize")
    {
        const nnm::Vector3 v(1.0f, -2.0f, 3.0f);
        REQUIRE(v.normalize().approx_equal(nnm::Vector3(0.267261f, -0.534522f, 0.801784f)));
    }

    SECTION("direction_to")
    {
        nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        nnm::Vector3 to(2.0f, 2.0f, 2.0f);
        auto direction = from.direction_to(to);
        REQUIRE(direction.approx_equal(nnm::Vector3::all(0.57735f)));

        from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
        to = nnm::Vector3(1.0f, 1.0f, 1.0f);
        direction = from.direction_to(to);
        REQUIRE(direction.approx_equal(nnm::Vector3::all(0.57735f)));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(1.0f, 0.0f, 0.0f);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 1.0f));
        REQUIRE(nnm::approx_equal(direction.y, 0.0f));
        REQUIRE(nnm::approx_equal(direction.z, 0.0f));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(0.0f, 1.0f, 0.0f);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0f));
        REQUIRE(nnm::approx_equal(direction.y, 1.0f));
        REQUIRE(nnm::approx_equal(direction.z, 0.0f));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(0.0f, 0.0f, 1.0f);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0f));
        REQUIRE(nnm::approx_equal(direction.y, 0.0f));
        REQUIRE(nnm::approx_equal(direction.z, 1.0f));

        from = nnm::Vector3(1.0f, 2.0f, 3.0f);
        to = nnm::Vector3(1.0f, 2.0f, 3.0f);
        direction = from.direction_to(to);
        REQUIRE(nnm::approx_equal(direction.x, 0.0f));
        REQUIRE(nnm::approx_equal(direction.y, 0.0f));
        REQUIRE(nnm::approx_equal(direction.z, 0.0f));
    }

    SECTION("distance_sqrd_to")
    {
        nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        nnm::Vector3 to(2.0f, 2.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 3.0f));

        from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
        to = nnm::Vector3(1.0f, 1.0f, 1.0f);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 12.0f));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(3.0f, 0.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 9.0f));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(0.0f, 4.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 16.0f));

        from = nnm::Vector3(1.0f, 2.0f, 3.0f);
        to = nnm::Vector3(1.0f, 2.0f, 3.0f);
        REQUIRE(nnm::approx_equal(from.distance_sqrd_to(to), 0.0f));
    }

    SECTION("distance_to")
    {
        nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        nnm::Vector3 to(2.0f, 2.0f, 2.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(3.0f)));

        from = nnm::Vector3(-1.0f, -1.0f, -1.0f);
        to = nnm::Vector3(1.0f, 1.0f, 1.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), nnm::sqrt(12.0f)));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(3.0f, 0.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 3.0f));

        from = nnm::Vector3(0.0f, 0.0f, 0.0f);
        to = nnm::Vector3(0.0f, 4.0f, 0.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 4.0f));

        from = nnm::Vector3(1.0f, 2.0f, 3.0f);
        to = nnm::Vector3(1.0f, 2.0f, 3.0f);
        REQUIRE(nnm::approx_equal(from.distance_to(to), 0.0f));
    }

    SECTION("floor")
    {
        REQUIRE(nnm::Vector3(0.1f, -2.1f, 1.1f).floor() == nnm::Vector3(0.0f, -3.0f, 1.0f));
    }

    SECTION("length_sqrd")
    {
        const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        REQUIRE(nnm::approx_equal(v.length_sqrd(), 14.0f));
    }

    SECTION("length")
    {
        const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        REQUIRE(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
    }

    SECTION("lerp")
    {
        nnm::Vector3 from(1.0f, 1.0f, 1.0f);
        nnm::Vector3 to(3.0f, 5.0f, -2.0f);
        REQUIRE(from.lerp(to, 0.0f) == nnm::Vector3(1.0f, 1.0f, 1.0f));
        REQUIRE(from.lerp(to, 1.0f) == nnm::Vector3(3.0f, 5.0f, -2.0f));
        REQUIRE(from.lerp(to, 0.5f) == nnm::Vector3(2.0f, 3.0f, -0.5f));
        REQUIRE(from.lerp(to, 0.25f) == nnm::Vector3(1.5f, 2.0f, 0.25f));
        REQUIRE(from.lerp(to, 0.75f) == nnm::Vector3(2.5f, 4.0f, -1.25f));
    }

    SECTION("min/max_axis")
    {
        nnm::Vector3 v1(3.0f, 4.0f, -2.0f);
        REQUIRE(v1.max_axis() == nnm::Axis3::y);
        REQUIRE(v1.min_axis() == nnm::Axis3::z);

        nnm::Vector3 v2(-100.0f, 5.0f, 100.0f);
        REQUIRE(v2.max_axis() == nnm::Axis3::z);
        REQUIRE(v2.min_axis() == nnm::Axis3::x);

        nnm::Vector3 v3(0.0f, 0.0f, 0.0f);
        REQUIRE(v3.max_axis() == nnm::Axis3::x);
        REQUIRE(v3.min_axis() == nnm::Axis3::x);
    }

    SECTION("approx_equal")
    {
        nnm::Vector3 v1(1.0f, 1.0f, 1.0f);
        nnm::Vector3 v2(1.0f + nnm::epsilon / 2.0f, 1.0f, 1.0f);
        REQUIRE(v1.approx_equal(v2));
        nnm::Vector3 v3(1.0f, 1.0f, 1.0f);
        nnm::Vector3 v4(1.0f + 2.0f * nnm::epsilon, 1.0f, 1.0f);
        REQUIRE_FALSE(v3.approx_equal(v4));
    }

    SECTION("approx_zero")
    {
        nnm::Vector3 v1(0.0f, 0.0f, 0.0f);
        REQUIRE(v1.approx_zero());
        nnm::Vector3 v2(nnm::epsilon, 0.0f, 0.0f);
        REQUIRE(v2.approx_zero());
        nnm::Vector3 v3(0.0f, nnm::epsilon, nnm::epsilon);
        REQUIRE(v3.approx_zero());
        nnm::Vector3 v4(0.1f, 0.1f, 0.1f);
        REQUIRE_FALSE(v4.approx_zero());
    }

    SECTION("dot")
    {
        const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
        REQUIRE(v1.dot(v2) == -28.0f);
    }

    SECTION("cross")
    {
        const nnm::Vector3 v1(1.0f, -2.0f, 3.0f);
        const nnm::Vector3 v2(-2.0f, 4.0f, -6.0f);
        REQUIRE(v1.cross(v2) == nnm::Vector3::zero());
        const nnm::Vector3 v3(1.0f, 2.0f, 3.0f);
        const nnm::Vector3 v4(-2.0f, 4.0f, 6.0f);
        REQUIRE(v3.cross(v4) == nnm::Vector3(0.0f, -12.0f, 8.0f));
    }

    SECTION("reflect")
    {
        nnm::Vector3 incident(1.0f, 1.0f, 1.0f);
        nnm::Vector3 normal(0.0f, 1.0f, 0.0f);
        REQUIRE(incident.reflect(normal) == nnm::Vector3(1.0f, -1.0f, 1.0f));
    }

    SECTION("inverse")
    {
        nnm::Vector3 v(1.0f, 2.0f, -3.0f);
        REQUIRE(v.inverse().approx_equal(nnm::Vector3(1.0f, 0.5f, -1.0f / 3.0f)));
    }

    SECTION("clamp_length")
    {
        const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        REQUIRE(v.clamp_length(2.0f, 5.0f).approx_equal(nnm::Vector3(1.0f, 2.0f, 3.0f)));
        REQUIRE(v.clamp_length(2.0f, 3.0f).approx_equal(nnm::Vector3(0.80178f, 1.603566f, 2.405352f)));
        REQUIRE(v.clamp_length(10.0f, 100.0f).approx_equal(nnm::Vector3(2.67261f, 5.34522f, 8.01784f)));
    }

    SECTION("round")
    {
        const nnm::Vector3 v(1.1f, -2.8f, 0.0f);
        REQUIRE(v.round() == nnm::Vector3(1.0f, -3.0f, 0.0f));
    }

    SECTION("angle")
    {
        const nnm::Vector3 v1(1.0f, 0.0f, 0.0f);
        const nnm::Vector3 v2(0.0f, 1.0f, 0.0f);
        const nnm::Vector3 v3(1.0f, 1.0f, 0.0f);
        REQUIRE(nnm::approx_equal(v1.angle(v2), nnm::pi / 2.0f));
        REQUIRE(nnm::approx_equal(v1.angle(v3), nnm::pi / 4.0f));
        REQUIRE(nnm::approx_zero(v1.angle(v1)));
        REQUIRE(nnm::approx_zero(v2.angle(v2)));
        REQUIRE(nnm::approx_zero(v3.angle(v3)));
    }

    SECTION("rotate")
    {
        const nnm::Vector3 v(1.0f, 2.0f, 3.0f);
        const nnm::Vector3 axis(0.0f, 0.0f, 1.0f);
        const float angle = nnm::pi / 2.0f;

        REQUIRE(v.rotate(axis, angle).approx_equal(nnm::Vector3(-2.0f, 1.0f, 3.0f)));
        REQUIRE(v.rotate(axis, 2.0f * angle).approx_equal(nnm::Vector3(-1.0f, -2.0f, 3.0f)));
        REQUIRE(v.rotate(axis, 4.0f * angle).approx_equal(v));
        REQUIRE(v.rotate(axis, 0.0f).approx_equal(v));
    }

    SECTION("rotate by matrix")
    {
        // TODO
    }

    SECTION("transform by matrix")
    {
    }

    nnm::Vector3 v1(1.0f, 2.0f, 3.0f);
    nnm::Vector3 v2(3.0f, 4.0f, -2.0f);
    nnm::Vector3 v3(1.0f, 2.0f, 3.0f);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 * v2 == nnm::Vector3(3.0f, 8.0f, -6.0f));
        REQUIRE(v1 * 2.0 == nnm::Vector3(2.0f, 4.0f, 6.0f));
        REQUIRE(v2 / v1 == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        REQUIRE(v2 / 2.0 == nnm::Vector3(1.5f, 2.0f, -1.0f));
        REQUIRE(v1 + v2 == nnm::Vector3(4.0f, 6.0f, 1.0f));
        REQUIRE(v2 - v1 == nnm::Vector3(2.0f, 2.0f, -5.0f));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector3(-1.0f, -2.0f, -3.0f));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector3 v1_copy(v1);
        nnm::Vector3 v2_copy(v2);

        v1 *= v2;
        REQUIRE(v1 == nnm::Vector3(3.0f, 8.0f, -6.0f));
        v1 = v1_copy;

        v1 *= 2.0f;
        REQUIRE(v1 == nnm::Vector3(2.0f, 4.0f, 6.0f));
        v1 = v1_copy;

        v2 /= v1;
        REQUIRE(v2 == nnm::Vector3(3.0f, 2.0f, -2.0f / 3.0f));
        v2 = v2_copy;

        v2 /= 2.0f;
        REQUIRE(v2 == nnm::Vector3(1.5f, 2.0f, -1.0f));
        v2 = v2_copy;

        v1 += v2;
        REQUIRE(v1 == nnm::Vector3(4.0f, 6.0f, 1.0f));
        v1 = v1_copy;

        v2 -= v1;
        REQUIRE(v2 == nnm::Vector3(2.0f, 2.0f, -5.0f));
        v2 = v2_copy;
    }

    SECTION("Comparison Operator")
    {
        REQUIRE(v1 < v2);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1.0f);
        REQUIRE(v1[1] == 2.0f);
        REQUIRE(v1[2] == 3.0f);

        REQUIRE(v1[nnm::Axis3::x] == 1.0f);
        REQUIRE(v1[nnm::Axis3::y] == 2.0f);
        REQUIRE(v1[nnm::Axis3::z] == 3.0f);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector3(0.0f, 0.0f, 0.0f)));
    }
}

TEST_CASE("Vector3i", "[Vector3i]")
{
    SECTION("Constructors")
    {
        const nnm::Vector3i v_default;
        REQUIRE(v_default.x == 0);
        REQUIRE(v_default.y == 0);
        REQUIRE(v_default.z == 0);
        const nnm::Vector3i v_with_params(1, -2, 3);
        REQUIRE(v_with_params.x == 1);
        REQUIRE(v_with_params.y == -2);
        REQUIRE(v_with_params.z == 3);
    }

    SECTION("Static methods")
    {
        const auto v_all_threes = nnm::Vector3i::all(3);
        REQUIRE(v_all_threes.x == 3);
        REQUIRE(v_all_threes.y == 3);
        REQUIRE(v_all_threes.z == 3);
        const auto v_zero = nnm::Vector3i::zero();
        REQUIRE(v_zero.x == 0);
        REQUIRE(v_zero.y == 0);
        REQUIRE(v_zero.z == 0);
        const auto v_one = nnm::Vector3i::one();
        REQUIRE(v_one.x == 1);
        REQUIRE(v_one.y == 1);
        REQUIRE(v_one.z == 1);
    }

    SECTION("abs")
    {
        nnm::Vector3i v(0, -2, 3);
        REQUIRE(v.abs() == nnm::Vector3i(0, 2, 3));
    }

    SECTION("clamp")
    {
        nnm::Vector3i v(0, -2, 3);
        REQUIRE(v.clamp({ -1, -3, -2 }, { 1, 5, 100 }) == nnm::Vector3i(0, -2, 3));
        REQUIRE(v.clamp({ 1, 3, 5 }, { 2, 5, 100 }) == nnm::Vector3i(1, 3, 5));
        REQUIRE(v.clamp({ -10, -5, -100 }, { -1, -4, 3 }) == nnm::Vector3i(-1, -4, 3));
    }

    SECTION("length_sqrd")
    {
        nnm::Vector3i v(1, -2, 3);
        REQUIRE(v.length_sqrd() == 14);
    }

    SECTION("length")
    {
        nnm::Vector3i v(1, -2, 3);
        REQUIRE(nnm::approx_equal(v.length(), nnm::sqrt(14.0f)));
    }

    SECTION("min/max axis")
    {
        nnm::Vector3i v1(1, -2, 3);
        REQUIRE(v1.min_axis() == nnm::Axis3::y);
        REQUIRE(v1.max_axis() == nnm::Axis3::z);
        nnm::Vector3i v2(-1, 2, -3);
        REQUIRE(v2.min_axis() == nnm::Axis3::z);
        REQUIRE(v2.max_axis() == nnm::Axis3::y);
    }

    nnm::Vector3i v1(1, 2, -3);
    nnm::Vector3i v2(-3, 4, 100);
    nnm::Vector3i v3(1, 2, -3);

    SECTION("Equality and Inequality Operators")
    {
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 != v3);
        REQUIRE(v1 != v2);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Arithmetic Operators")
    {
        REQUIRE(v1 % v2 == nnm::Vector3i(1, 2, -3));
        REQUIRE(v1 % 2 == nnm::Vector3i(1, 0, -1));
        REQUIRE(v1 * v2 == nnm::Vector3i(-3, 8, -300));
        REQUIRE(v1 * 2 == nnm::Vector3i(2, 4, -6));
        REQUIRE(v1 + v2 == nnm::Vector3i(-2, 6, 97));
        REQUIRE(v2 - v1 == nnm::Vector3i(-4, 2, 103));
        REQUIRE(v2 / v1 == nnm::Vector3i(-3, 2, -33));
        REQUIRE(v2 / 2 == nnm::Vector3i(-1, 2, 50));
        REQUIRE(+v1 == v1);
        REQUIRE(-v1 == nnm::Vector3i(-1, -2, 3));
    }

    SECTION("Compound Assignment Operators")
    {
        nnm::Vector3i v1_copy(v1);
        nnm::Vector3i v2_copy(v2);

        v1 *= v2;
        REQUIRE(v1 == nnm::Vector3i(-3, 8, -300));
        v1 = v1_copy;

        v1 *= 2;
        REQUIRE(v1 == nnm::Vector3i(2, 4, -6));
        v1 = v1_copy;

        v2 /= v1;
        REQUIRE(v2 == nnm::Vector3i(-3, 2, -33));
        v2 = v2_copy;

        v2 /= 2;
        REQUIRE(v2 == nnm::Vector3i(-1, 2, 50));
        v2 = v2_copy;

        v1 += v2;
        REQUIRE(v1 == nnm::Vector3i(-2, 6, 97));
        v1 = v1_copy;

        v2 -= v1;
        REQUIRE(v2 == nnm::Vector3i(-4, 2, 103));
        v2 = v2_copy;
    }

    SECTION("Comparison Operator")
    {
        REQUIRE(v2 < v1);
    }

    SECTION("Indexing Operators")
    {
        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);
        REQUIRE(v1[2] == -3);

        REQUIRE(v1[nnm::Axis3::x] == 1);
        REQUIRE(v1[nnm::Axis3::y] == 2);
        REQUIRE(v1[nnm::Axis3::z] == -3);
    }

    SECTION("Conversion Operators")
    {
        REQUIRE(static_cast<bool>(v1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Vector3i(0, 0, 0)));
    }
}

TEST_CASE("Matrix2", "[Matrix2]")
{
    SECTION("Constructors")
    {
        const nnm::Matrix2 mat_default;
        REQUIRE(mat_default.c0r0 == 1.0f);
        REQUIRE(mat_default.c0r1 == 0.0f);
        REQUIRE(mat_default.c1r0 == 0.0f);
        REQUIRE(mat_default.c1r1 == 1.0f);

        const nnm::Matrix2 mat_cols({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat_cols.c0r0 == 1.0f);
        REQUIRE(mat_cols.c0r1 == -2.0f);
        REQUIRE(mat_cols.c1r0 == -3.0f);
        REQUIRE(mat_cols.c1r1 == 4.0f);

        const nnm::Matrix2 mat_elements(1.0f, -2.0f, -3.0f, 4.0f);
        REQUIRE(mat_elements.c0r0 == 1.0f);
        REQUIRE(mat_elements.c0r1 == -2.0f);
        REQUIRE(mat_elements.c1r0 == -3.0f);
        REQUIRE(mat_elements.c1r1 == 4.0f);
    }

    SECTION("Static methods")
    {
        const auto mat_all_three = nnm::Matrix2::all(3.0f);
        REQUIRE(mat_all_three.c0r0 == 3.0f);
        REQUIRE(mat_all_three.c0r1 == 3.0f);
        REQUIRE(mat_all_three.c1r0 == 3.0f);
        REQUIRE(mat_all_three.c1r1 == 3.0f);

        const auto mat_zero = nnm::Matrix2::zero();
        REQUIRE(mat_zero.c0r0 == 0.0f);
        REQUIRE(mat_zero.c0r1 == 0.0f);
        REQUIRE(mat_zero.c1r0 == 0.0f);
        REQUIRE(mat_zero.c1r1 == 0.0f);

        const auto mat_one = nnm::Matrix2::one();
        REQUIRE(mat_one.c0r0 == 1.0f);
        REQUIRE(mat_one.c0r1 == 1.0f);
        REQUIRE(mat_one.c1r0 == 1.0f);
        REQUIRE(mat_one.c1r1 == 1.0f);

        const auto mat_identity = nnm::Matrix2::identity();
        REQUIRE(mat_identity.c0r0 == 1.0f);
        REQUIRE(mat_identity.c0r1 == 0.0f);
        REQUIRE(mat_identity.c1r0 == 0.0f);
        REQUIRE(mat_identity.c1r1 == 1.0f);
    }

    SECTION("trace")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(nnm::approx_equal(mat.trace(), 5.0f));
    }

    SECTION("determinant")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(nnm::approx_equal(mat.determinant(), -2.0f));
    }

    SECTION("minor")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat.minor(0, 0) == 4.0f);
        REQUIRE(mat.minor(0, 1) == -3.0f);
        REQUIRE(mat.minor(1, 0) == -2.0f);
        REQUIRE(mat.minor(1, 1) == 1.0f);
    }

    SECTION("cofactor")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat.cofactor_at(0, 0) == 4.0f);
        REQUIRE(mat.cofactor_at(0, 1) == 3.0f);
        REQUIRE(mat.cofactor_at(1, 0) == 2.0f);
        REQUIRE(mat.cofactor_at(1, 1) == 1.0f);
        REQUIRE(mat.cofactor() == nnm::Matrix2({ 4.0f, 3.0f }, { 2.0f, 1.0f }));
    }

    SECTION("transpose")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat.transpose() == nnm::Matrix2({ 1.0f, -3.0f }, { -2.0f, 4.0f }));
    }

    SECTION("adjugate")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat.adjugate() == nnm::Matrix2({ 4.0f, 2.0f }, { 3.0f, 1.0f }));
    }

    SECTION("inverse")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        const std::optional<nnm::Matrix2> mat_inv = mat.inverse();
        REQUIRE(mat_inv.has_value());
        REQUIRE(mat.inverse()->approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
        REQUIRE(mat.unsafe_inverse().approx_equal({ { -2.0f, -1.0f }, { -1.5f, -0.5f } }));
        REQUIRE_FALSE(nnm::Matrix2::zero().inverse().has_value());
    }

    SECTION("approx")
    {
        const nnm::Matrix2 mat1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat1.approx_equal({ { 1.00000001f, -1.9999999f }, { -3.00000001f, 3.99999999f } }));
        REQUIRE_FALSE(mat1.approx_equal({ { 1.1f, -1.9f }, { -3.1f, 3.9f } }));
        const nnm::Matrix2 mat2({ 0.00000001f, -0.00000001f }, { -0.00000001f, 0.00000001f });
        REQUIRE(mat2.approx_zero());
        REQUIRE_FALSE(mat1.approx_zero());
    }

    SECTION("accessors")
    {
        const nnm::Matrix2 mat({ 1.0f, -2.0f }, { -3.0f, 4.0f });
        REQUIRE(mat.at(0, 0) == 1.0f);
        REQUIRE(mat.at(0, 1) == -2.0f);
        REQUIRE(mat.at(1, 0) == -3.0f);
        REQUIRE(mat.at(1, 1) == 4.0f);

        REQUIRE(mat[0][0] == 1.0f);
        REQUIRE(mat[0][1] == -2.0f);
        REQUIRE(mat[1][0] == -3.0f);
        REQUIRE(mat[1][1] == 4.0f);
    }

    nnm::Matrix2 m1({ 1.0f, -2.0f }, { -3.0f, 4.0f });
    nnm::Matrix2 m2({ -4.0f, 3.0f }, { 2.0f, -1.0f });
    nnm::Matrix2 m3({ 1.0f, -2.0f }, { -3.0f, 4.0f });

    SECTION("equality and inequality")
    {
        REQUIRE(m1 == m3);
        REQUIRE_FALSE(m1 != m3);
        REQUIRE(m1 != m2);
        REQUIRE_FALSE(m1 == m2);
    }

    SECTION("arithmetic")
    {
        REQUIRE(m1 * m2 == nnm::Matrix2({ -8.0f, 5.0f }, { 20.0f, -13.0f }));
        REQUIRE(m1 * 2.0f == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        REQUIRE((m2 / 2.0f).approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
    }

    SECTION("compound assignment")
    {
        nnm::Matrix2 m1_copy(m1);
        nnm::Matrix2 m2_copy(m2);

        m1 *= m2;
        REQUIRE(m1 == nnm::Matrix2({ -8.0f, 5.0f }, { 20.0f, -13.0f }));
        m1 = m1_copy;

        m1 *= 2.0f;
        REQUIRE(m1 == nnm::Matrix2({ 2.0f, -4.0f }, { -6.0f, 8.0f }));
        m1 = m1_copy;

        m2 /= 2.0f;
        REQUIRE(m2.approx_equal(nnm::Matrix2({ -2.0f, 1.5f }, { 1.0f, -0.5f })));
        m2 = m2_copy;
    }

    SECTION("comparison")
    {
        REQUIRE(m2 < m1);
        REQUIRE_FALSE(m1 < m2);
    }

    SECTION("bool conversion")
    {
        REQUIRE(static_cast<bool>(m1));
        REQUIRE_FALSE(static_cast<bool>(nnm::Matrix2::zero()));
    }
}

TEST_CASE("Basis2", "[Basis2]")
{
    SECTION("constructor")
    {
        const nnm::Basis2 b;
        REQUIRE(b.matrix() == nnm::Matrix2::identity());
    }

    SECTION("from angle")
    {
        const auto b1 = nnm::Basis2::from_angle(0.0f);
        REQUIRE(b1.matrix().approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
        const auto b2 = nnm::Basis2::from_angle(nnm::pi / 2.0f);
        REQUIRE(b2.matrix().approx_equal({ { 0.0f, 1.0f }, { -1.0f, 0.0f } }));
        const auto b3 = nnm::Basis2::from_angle(nnm::pi);
        REQUIRE(b3.matrix().approx_equal({ { -1.0f, 0.0f }, { 0.0f, -1.0f } }));
        const auto b4 = nnm::Basis2::from_angle(2.0f * nnm::pi);
        REQUIRE(b4.matrix().approx_equal({ { 1.0f, 0.0f }, { 0.0f, 1.0f } }));
    }

    SECTION("valid")
    {
        const nnm::Basis2 b1;
        const auto b2 = nnm::Basis2::unsafe_from_matrix(nnm::Matrix2::zero());
        const auto b3 = nnm::Basis2::unsafe_from_matrix({ { 1.0f, -2.0f }, { 2.0f, -4.0f } });
        REQUIRE(b1.valid());
        REQUIRE_FALSE(b2.valid());
        REQUIRE_FALSE(b3.valid());
    }
}
