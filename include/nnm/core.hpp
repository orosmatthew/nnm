/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_CORE_HPP
#define NNM_CORE_HPP

#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>

// ReSharper disable CppDFATimeOver

#ifndef NNM_EPSILON_SCALE
#define NNM_EPSILON_SCALE 100
#endif

#if defined(NNM_ENABLE_BOUNDS_CHECKS)
#include <stdexcept>
#define NNM_BOUNDS_CHECK_ASSERT(msg, expression) \
    if (!(expression))                           \
        throw std::out_of_range(msg);
#else
#define NNM_BOUNDS_CHECK_ASSERT(msg, expression)
#endif

namespace nnm {

/**
 * Mathematical pi.
 * @tparam Real Floating-point type.
 * @return Value of pi.
 */
template <typename Real>
constexpr Real pi()
{
    return static_cast<Real>(3.141592653589793238462643383279502);
}

/**
 * Mathematical pi as a float.
 * @return Value of pi.
 */
constexpr float pi_f()
{
    return pi<float>();
}

/**
 * Mathematical pi as a double.
 * @return Value of pi.
 */
constexpr double pi_d()
{
    return pi<double>();
}

/**
 * Epsilon value is the upper bound on approximation errors.
 * @tparam Real Floating-point type.
 * @return Value of epsilon.
 */
template <typename Real>
constexpr Real epsilon()
{
    return std::numeric_limits<Real>::epsilon() * static_cast<Real>(NNM_EPSILON_SCALE);
}

/**
 * 1 multiplied by the sign of a value.
 * @tparam Num Numeric type.
 * @param value Value to get the sign of.
 * @return -1 for negatives and 1 for positives or 0.
 */
template <typename Num>
constexpr Num sign(const Num value)
{
    if (value < static_cast<Num>(0)) {
        return static_cast<Num>(-1);
    }
    return static_cast<Num>(1);
}

/**
 * Absolute value.
 * @tparam Num Numeric type
 * @param value Value to take the absolute value of.
 * @return Result.
 */
template <typename Num>
constexpr Num abs(const Num value)
{
    if (value < static_cast<Num>(0)) {
        return -value;
    }
    return value;
}

/**
 * The maximum between two values.
 * @tparam Num Numeric type.
 * @param first First value.
 * @param second Second value.
 * @return Result.
 */
template <typename Num>
constexpr Num max(const Num first, const Num second)
{
    if (first > second) {
        return first;
    }
    return second;
}

/**
 * The maximum between values.
 * @tparam Num Numeric type.
 * @tparam Rest Numeric types.
 * @param first First value.
 * @param rest Rest of the values.
 * @return Result.
 */
template <typename Num, typename... Rest>
constexpr Num max(const Num first, const Rest... rest)
{
    Num max_value = first;
    max_value = max(first, max(rest...));
    return max_value;
}

/**
 * Determines if a value is approximately zero based on the epsilon value.
 * @tparam Real Floating-point type.
 * @param value Value to test.
 * @return True if approximately zero or false otherwise.
 */
template <typename Real>
constexpr bool approx_zero(const Real value)
{
    if (value == static_cast<Real>(0)) {
        return true;
    }
    Real tolerance = epsilon<Real>() * abs(value);
    tolerance = max(tolerance, epsilon<Real>());
    return abs(value) <= tolerance;
}

/**
 * Determines if two values are approximately equal based on the epsilon value.
 * @tparam Real Floating-point type.
 * @param first First value.
 * @param second Second value.
 * @return True if approximately equal or false otherwise.
 */
template <typename Real>
constexpr bool approx_equal(const Real first, const Real second)
{
    if (first == second) {
        return true;
    }
    Real tolerance = epsilon<Real>() * max(abs(first), abs(second));
    tolerance = max(tolerance, epsilon<Real>());
    return abs(first - second) <= tolerance;
}

/**
 * Determine if the first value is approximately less-than but not equal to the second value.
 * @tparam Real Floating-point type.
 * @param first First value.
 * @param second Second value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_less(const Real first, const Real second)
{
    return first < second && !approx_equal(first, second);
}

/**
 * Determine if the first value is approximately greater-than but not equal to the second value.
 * @tparam Real Floating-point type.
 * @param first First value.
 * @param second Second value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_greater(const Real first, const Real second)
{
    return first > second && !approx_equal(first, second);
}

/**
 * Determine if the first value is approximately less-than or equal to the second value.
 * @tparam Real Floating-point type.
 * @param first First value.
 * @param second Second value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_less_equal(const Real first, const Real second)
{
    return first <= second || approx_equal(first, second);
}

/**
 * Determine if the first value is approximately greater-than or equal to the second value.
 * @tparam Real Floating-point type.
 * @param first First value.
 * @param second Second value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_greater_equal(const Real first, const Real second)
{
    return first >= second || approx_equal(first, second);
}

/**
 * Determine if a value is approximately less-than but not equal to zero.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_less_zero(const Real value)
{
    return value < static_cast<Real>(0) && !approx_zero(value);
}

/**
 * Determine if a value is approximately greater-than but not equal to zero.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_greater_zero(const Real value)
{
    return value > static_cast<Real>(0) && !approx_zero(value);
}

/**
 * Determine if a value is approximately less-than or equal to zero.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_less_equal_zero(const Real value)
{
    return value <= static_cast<Real>(0) || approx_zero(value);
}

/**
 * Determine if a value is approximately greater-than or equal to zero.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @return Result.
 */
template <typename Real>
constexpr bool approx_greater_equal_zero(const Real value)
{
    return value >= static_cast<Real>(0) || approx_zero(value);
}

/**
 * The least integer value greater than a value.
 * @tparam Real Floating-point type.
 * @param value Value to take the ceiling of.
 * @return Result.
 */
template <typename Real>
Real ceil(const Real value)
{
    return std::ceil(value);
}

/**
 * Restricts a value between a minimum and maximum range.
 * @tparam Num Numeric type.
 * @param value Value to clamp.
 * @param min Minimum allowed value.
 * @param max Maximum allowed value.
 * @return Result.
 */
template <typename Num>
constexpr Num clamp(const Num value, const Num min, const Num max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

/**
 * Square-root of a value.
 * @tparam Real Floating-point type.
 * @param value Value to square-root.
 * @return Result.
 */
template <typename Real>
Real sqrt(const Real value)
{
    return std::sqrt(value);
}

/**
 * Exponential operation between two values.
 * @tparam Real Floating-point type.
 * @param base Base value.
 * @param power Power value.
 * @return Result.
 */
template <typename Real>
Real pow(const Real base, const Real power)
{
    return std::pow(base, power);
}

/**
 * Square of a value.
 * @tparam Num Numeric type.
 * @param value Value to square.
 * @return Result.
 */
template <typename Num>
constexpr Num sqrd(const Num value)
{
    return value * value;
}

/**
 * Floating-point Euclidean modulus where the result is always positive.
 * @tparam Real Floating-point type.
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Real>
Real euclidean_modf(const Real dividend, const Real divisor)
{
    const Real result = std::fmod(dividend, divisor);
    if (result < static_cast<Real>(0)) {
        return result + abs(divisor);
    }
    return result;
}

/**
 * Integer Euclidean modulus where the result is always positive.
 * @tparam Int Integer type.
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Int>
constexpr Int euclidean_mod(const Int dividend, const Int divisor)
{
    const Int result = dividend % divisor;
    if (result < static_cast<Int>(0)) {
        return result + abs(divisor);
    }
    return result;
}

/**
 * Remainder of the division between two floating-point values.
 * @tparam Real Floating-point type
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Real>
Real remf(const Real dividend, const Real divisor)
{
    return std::fmod(dividend, divisor);
}

/**
 * Remainder of the division between two integer values.
 * @tparam Int Integer type.
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Int>
constexpr Int rem(const Int dividend, const Int divisor)
{
    return dividend % divisor;
}

/**
 * Normalizes an angle in radians between -pi and pi.
 * @tparam Real Floating-point type.
 * @param angle Angle to normalize in radians.
 * @return Result.
 */
template <typename Real>
Real normalize_angle(const Real angle)
{
    constexpr Real two = static_cast<Real>(2);
    constexpr Real p = pi<Real>();
    return euclidean_modf(angle + p, two * p) - p;
}

/**
 * The greatest integer value less or equal to a value.
 * @tparam Real Floating-point type.
 * @param value Value to take the floor of.
 * @return Result.
 */
template <typename Real>
Real floor(const Real value)
{
    return std::floor(value);
}

/**
 * Linear interpolation between two values based on a weight value.
 * @tparam Real Floating-point value.
 * @param from Value to interpolate from.
 * @param to Value to interpolate to.
 * @param weight Value that indicates interpolation between the two values normally between 0 and 1.
 * @return Result.
 */
template <typename Real>
constexpr Real lerp(const Real from, const Real to, const Real weight)
{
    return from + weight * (to - from);
}

/**
 * Linear interpolation between two values based on a weight value that is clamped between 0 and 1.
 * @tparam Real Floating-point value.
 * @param from Value to interpolate from.
 * @param to Value to interpolate to.
 * @param weight Value that indicates interpolation between the two values that is clamped between 0 and 1.
 * @return Result.
 */
template <typename Real>
constexpr Real lerp_clamped(const Real from, const Real to, const Real weight)
{
    if (weight >= static_cast<Real>(1)) {
        return to;
    }
    if (weight <= static_cast<Real>(0)) {
        return from;
    }
    return lerp(from, to, weight);
}

/**
 * Mathematical sine of a value
 * @tparam Real Floating-point type.
 * @param value Value to take the sine of in radians.
 * @return Result.
 */
template <typename Real>
Real sin(const Real value)
{
    return std::sin(value);
}

/**
 * Mathematical cosine.
 * @tparam Real Floating-point value.
 * @param value Value to take the cosine of in radians.
 * @return Result.
 */
template <typename Real>
Real cos(const Real value)
{
    return std::cos(value);
}

/**
 * Mathematical tangent.
 * @tparam Real Floating-point value.
 * @param value Value to take the tangent of in radians.
 * @return Result.
 */
template <typename Real>
Real tan(const Real value)
{
    return std::tan(value);
}

/**
 * Rounds a value to the nearest integer value.
 * @tparam Real Floating-point value.
 * @param value Value to round.
 * @return Result.
 */
template <typename Real>
Real round(const Real value)
{
    return std::round(value);
}

/**
 * Mathematical inverse tangent.
 * @tparam Real Floating-point value.
 * @param value Value to take inverse tangent of.
 * @return Result in radians.
 */
template <typename Real>
Real atan(const Real value)
{
    return std::atan(value);
}

/**
 * Mathematical inverse tangent that takes into account all four-quadrants.
 * @tparam Real Floating-point value.
 * @param y Y value.
 * @param x X value.
 * @return Result in radians.
 */
template <typename Real>
Real atan2(const Real y, const Real x)
{
    return std::atan2(y, x);
}

/**
 * Converts angle in degrees to radians.
 * @tparam Real Floating-point value.
 * @param degrees Angle in degrees.
 * @return Resulting angle in radians.
 */
template <typename Real>
constexpr Real radians(const Real degrees)
{
    return pi<Real>() / static_cast<Real>(180) * degrees;
}

/**
 * Converts angle in radians to degrees.
 * @tparam Real Floating-point value.
 * @param radians Angle in radians.
 * @return Resulting angle in degrees.
 */
template <typename Real>
constexpr Real degrees(const Real radians)
{
    return static_cast<Real>(180) / pi<Real>() * radians;
}

/**
 * Mathematical inverse sine.
 * @tparam Real Floating-point value.
 * @param value Value to take inverse sine of.
 * @return Resulting angle in radians.
 */
template <typename Real>
Real asin(const Real value)
{
    return std::asin(value);
}

/**
 * Mathematical inverse cosine.
 * @tparam Real Floating-point value.
 * @param value Value to take the inverse cosine of.
 * @return Resulting angle in radians.
 */
template <typename Real>
Real acos(const Real value)
{
    return std::acos(value);
}

/**
 * The minimum value between two values.
 * @tparam Num Numeric type.
 * @param a First value.
 * @param b Second value.
 * @return Result.
 */
template <typename Num>
constexpr Num min(const Num a, const Num b)
{
    if (a < b) {
        return a;
    }
    return b;
}

/**
 * The minimum between values.
 * @tparam Num Numeric type.
 * @tparam Rest Numeric types.
 * @param first First value.
 * @param rest Rest of the values.
 * @return Result.
 */
template <typename Num, typename... Rest>
constexpr Num min(const Num first, const Rest... rest)
{
    Num min_value = first;
    min_value = min(first, min(rest...));
    return min_value;
}

/**
 * Binary logarithm of a value which is the power to which the number 2 must be raised to obtain the value.
 * @tparam Real Floating-point value.
 * @param value Value to take logarithm of.
 * @return Result.
 */
template <typename Real>
Real log2(const Real value)
{
    return std::log2(value);
}
}

#endif
