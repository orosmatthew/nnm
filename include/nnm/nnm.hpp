/* NNM - "No Nonsense Math"
 * v0.4.0
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_HPP
#define NNM_HPP

#include <cmath>
#include <cstdint>
#include <functional>
#include <optional>

// ReSharper disable CppDFATimeOver

#if defined(NNM_BOUNDS_CHECK)
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
 * @return Mathematical pi.
 */
template <typename Real>
constexpr Real pi()
{
    return static_cast<Real>(3.141592653589793238462643383279502);
}

/**
 * Epsilon value is the upper bound on approximation errors.
 * @tparam Real Floating-point type.
 * @return Epsilon value.
 */
template <typename Real>
constexpr Real epsilon()
{
    return static_cast<Real>(0.00001);
}

/**
 * One multiplied by the sign of a value.
 * @tparam Num Numeric type.
 * @param value Value to get the sign of.
 * @return -1 for negatives and 1 for 0 or positive.
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
 * Absolute value which is the number's distance from zero.
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
 * @param a First value.
 * @param b Second value.
 * @return Result.
 */
template <typename Num>
constexpr Num max(const Num a, const Num b)
{
    if (a > b) {
        return a;
    }
    return b;
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
    Real tolerance = epsilon<Real>() * abs(value);
    tolerance = max(tolerance, epsilon<Real>());
    return abs(value) <= tolerance;
}

/**
 * Determines if two values are approximately equal based on the epsilon value.
 * @tparam Real Floating-point type.
 * @param a First value.
 * @param b Second value.
 * @return True if approximately equal or false otherwise.
 */
template <typename Real>
constexpr bool approx_equal(const Real a, const Real b)
{
    if (a == b) {
        return true;
    }
    Real tolerance = epsilon<Real>() * max(abs(a), abs(b));
    tolerance = max(tolerance, epsilon<Real>());
    return abs(a - b) <= tolerance;
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
 * Floating-point mathematical modulus where the result is always positive.
 * @tparam Real Floating-point type.
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Real>
Real modf(const Real dividend, const Real divisor)
{
    const Real result = std::fmod(dividend, divisor);
    const Real zero = static_cast<Real>(0);
    if ((result < zero && divisor > zero) || (result > zero && divisor < zero)) {
        return result + divisor;
    }
    return result;
}

/**
 * Integer mathematical modulus where the result is always positive.
 * @tparam Int Integer type.
 * @param dividend Dividend.
 * @param divisor Divisor.
 * @return Result.
 */
template <typename Int>
constexpr Int mod(const Int dividend, const Int divisor)
{
    const Int result = dividend % divisor;
    if ((result < 0 && divisor > 0) || (result > 0 && divisor < 0)) {
        return result + divisor;
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
    return modf(angle + pi<Real>(), static_cast<Real>(2) * pi<Real>()) - pi<Real>();
}

/**
 * Determines if an angle in radians is within a range taking into account wrap-around.
 * @tparam Real Floating-point type.
 * @param angle Angle to test in radians.
 * @param from First angle in radians.
 * @param to Second angle in radians
 * @return True if within range, false otherwise.
 */
template <typename Real>
bool angle_in_range(const Real angle, const Real from, const Real to)
{
    const Real two_pi = static_cast<Real>(2) * pi<Real>();
    if (from <= to) {
        return modf(angle - from, two_pi) <= modf(to - from, two_pi);
    }
    return modf(angle - from, two_pi) >= modf(to - from, two_pi);
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

template <typename Real>
class Vector2;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
template <typename Int>
class Vector2i;
using Vector2ii = Vector2i<int>;
using Vector2i8 = Vector2i<int8_t>;
using Vector2i16 = Vector2i<int16_t>;
using Vector2i32 = Vector2i<int32_t>;
using Vector2i64 = Vector2i<int64_t>;
using Vector2iu = Vector2i<unsigned int>;
using Vector2u8 = Vector2i<uint8_t>;
using Vector2u16 = Vector2i<uint16_t>;
using Vector2u32 = Vector2i<uint32_t>;
using Vector2u64 = Vector2i<uint64_t>;
template <typename Real>
class Vector3;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
template <typename Int>
class Vector3i;
using Vector3ii = Vector3i<int>;
using Vector3i8 = Vector3i<int8_t>;
using Vector3i16 = Vector3i<int16_t>;
using Vector3i32 = Vector3i<int32_t>;
using Vector3i64 = Vector3i<int64_t>;
using Vector3iu = Vector3i<unsigned int>;
using Vector3u8 = Vector3i<uint8_t>;
using Vector3u16 = Vector3i<uint16_t>;
using Vector3u32 = Vector3i<uint32_t>;
using Vector3u64 = Vector3i<uint64_t>;
template <typename Real>
class Vector4;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
template <typename Real>
class Quaternion;
using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;
template <typename Real>
class Matrix2;
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;
template <typename Real>
class Basis2;
using Basis2f = Basis2<float>;
using Basis2d = Basis2<double>;
template <typename Real>
class Matrix3;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;
template <typename Real>
class Transform2;
using Transform2f = Transform2<float>;
using Transform2d = Transform2<double>;
template <typename Real>
class Basis3;
using Basis3f = Basis3<float>;
using Basis3d = Basis3<double>;
template <typename Real>
class Matrix4;
using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
template <typename Real>
class Transform3;
using Transform3f = Transform3<float>;
using Transform3d = Transform3<double>;

/**
 * 2-dimensional vector.
 * @tparam Real Floating-point value.
 */
template <typename Real>
class Vector2 {
public:
    Real x;
    Real y;

    /**
     * Default initializes to all zeros.
     */
    constexpr Vector2()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
    {
    }

    /**
     * Initializes by casting the integer 2D vector variant value.
     * @tparam Int Integer type.
     * @param vector Vector to cast from.
     */
    template <typename Int>
    explicit constexpr Vector2(const Vector2i<Int>& vector);

    /**
     * Initializes by casting a different floating-point type vector.
     * @tparam Other Other floating-point type.
     * @param vector Vector to cast from.
     */
    template <typename Other>
    explicit constexpr Vector2(const Vector2<Other>& vector)
        : x { static_cast<Real>(vector.x) }
        , y { static_cast<Real>(vector.y) }
    {
    }

    /**
     * Initializes from two provided values.
     * @param x X value.
     * @param y Y value.
     */
    constexpr Vector2(const Real x, const Real y)
        : x { x }
        , y { y }
    {
    }

    /**
     * Vector with all components set to a value.
     * @param value Value.
     * @return Resulting vector.
     */
    static constexpr Vector2 all(const Real value)
    {
        return { value, value };
    }

    /**
     * Vector with all components set to zero.
     * @return Resulting vector.
     */
    static constexpr Vector2 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Vector with all components set to one.
     * @return Resulting vector.
     */
    static constexpr Vector2 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Normalized vector that points in the direction of the positive x-axis.
     * @return Resulting vector.
     */
    static constexpr Vector2 axis_x()
    {
        return { static_cast<Real>(1), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive y-axis.
     * @return Resulting vector.
     */
    static constexpr Vector2 axis_y()
    {
        return { static_cast<Real>(0), static_cast<Real>(1) };
    }

    /**
     * Absolute value of all components.
     * @return Resulting vector.
     */
    [[nodiscard]] constexpr Vector2 abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    /**
     * Ceiling of all components.
     * @return Resulting vector.
     */
    [[nodiscard]] Vector2 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y) };
    }

    /**
     * Floor of all components.
     * @return Resulting vector.
     */
    [[nodiscard]] Vector2 floor() const
    {
        return { nnm::floor(x), nnm::floor(y) };
    }

    /**
     * Round all components.
     * @return Resulting vector.
     */
    [[nodiscard]] Vector2 round() const
    {
        return { nnm::round(x), nnm::round(y) };
    }

    /**
     * The ratio between the x and y components.
     * @return Resulting ratio.
     */
    [[nodiscard]] constexpr Real aspect_ratio() const
    {
        return x / y;
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 clamp(const Vector2& min, const Vector2& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    /**
     * Normalized vector that points in the direction from the position of this vector to another vector.
     * @param to Position to.
     * @return Resulting normalized direction vector.
     */
    [[nodiscard]] Vector2 direction(const Vector2& to) const
    {
        return (to - *this).normalize();
    }

    /**
     * Non-normalized Vector that points in the direction from the position of this vector to another vector.
     * @param to Position to.
     * @return Resulting non-normalized direction vector.
     */
    [[nodiscard]] Vector2 direction_unnormalized(const Vector2& to) const
    {
        return to - *this;
    }

    /**
     * Squared distance from the position of this vector to another vector.
     * @param to Position to.
     * @return Resulting squared distance.
     */
    [[nodiscard]] constexpr Real distance_sqrd(const Vector2& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        return sqrd(diff_x) + sqrd(diff_y);
    }

    /**
     * Distance from the position of this vector to another vector.
     * @param to Position to.
     * @return Resulting distance.
     */
    [[nodiscard]] Real distance(const Vector2& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    /**
     * Distance between the position of this vector to another vector along the grid defined by the x and y axes.
     * @param to Position to.
     * @return Resulting distance.
     */
    [[nodiscard]] constexpr Real manhattan_distance(const Vector2& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    /**
     * Squared length of the vector.
     * @return Resulting squared length.
     */
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    /**
     * Length of the vector.
     * @return Resulting length.
     */
    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    /**
     * A vector that has the same direction of this vector but whose length is clamped between minimum and maximum
     * values.
     * @param min Minimum length.
     * @param max Maximum length.
     * @return Resulting length-clamped vector.
     */
    [[nodiscard]] Vector2 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    /**
     * Normalize the vector which keeps the direction but with a length of one.
     * @return Resulting normalized vector.
     */
    [[nodiscard]] Vector2 normalize() const
    {
        if (const Real length = this->length(); length > static_cast<Real>(0)) {
            return *this / length;
        }
        return zero();
    }

    /**
     * Linear interpolate between two this vector and another vector.
     * @param to Vector to interpolate to.
     * @param weight Weight between the two interpolated vectors.
     * @return Resulting interpolated vector.
     */
    [[nodiscard]] constexpr Vector2 lerp(const Vector2& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight) };
    }

    /**
     * Linear interpolate between this vector and another vector where the weight is clamped between zero and one.
     * @param to Vector to interpolate to.
     * @param weight Weight between the two interpolate vectors that is clamped between zero and one.
     * @return Resulting interpolated vector.
     */
    [[nodiscard]] constexpr Vector2 lerp_clamped(const Vector2& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight), nnm::lerp_clamped(y, to.y, weight) };
    }

    /**
     * Dot product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Real dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    /**
     * Cross product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Real cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    /**
     * Outer product.
     * @param other Other vector.
     * @return Resulting 2x2 matrix.
     */
    [[nodiscard]] Matrix2<Real> outer(const Vector2& other) const;

    /**
     * Reflect this vector along a normal vector.
     * @param normal Normal to reflect along.
     * @return Resulting reflected vector.
     */
    [[nodiscard]] constexpr Vector2 reflect(const Vector2& normal) const
    {
        const Real dot = this->dot(normal);
        Vector2 result;
        result.x = x - static_cast<Real>(2) * normal.x * dot;
        result.y = y - static_cast<Real>(2) * normal.y * dot;
        return result;
    }

    /**
     * Project this vector onto another vector.
     * @param onto Vector to project onto.
     * @return Resulting projected vector.
     */
    [[nodiscard]] constexpr Vector2 project(const Vector2& onto) const
    {
        const Real onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == static_cast<Real>(0)) {
            return zero();
        }
        const Real scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    /**
     * Inverse of the vector.
     * @return Resulting inverse vector.
     */
    [[nodiscard]] constexpr Vector2 inverse() const
    {
        return { static_cast<Real>(1) / x, static_cast<Real>(1) / y };
    }

    /**
     * Angle in radians between this vector and another vector.
     * @param other Other vector.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle_between(const Vector2& other) const
    {
        const Real lengths = length() * other.length();
        if (lengths == 0) {
            return static_cast<Real>(0);
        }
        const Real cos_angle = nnm::clamp(dot(other) / lengths, static_cast<Real>(-1), static_cast<Real>(1));
        const Real angle = acos(cos_angle);
        return cross(other) < static_cast<Real>(0) ? -angle : angle;
    }

    /**
     * Angle in radians from this position vector to another position vector.
     * @param to Position to.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle_to(const Vector2& to) const
    {
        return atan2(to.y - y, to.x - x);
    }

    /**
     * Determines if this vector is approximately parallel to another vector.
     * @param other Other vector.
     * @return True if approximately parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_parallel(const Vector2& other) const
    {
        return nnm::approx_zero(cross(other));
    }

    /**
     * Determines if this vector is approximately perpendicular to another vector.
     * @param other Other vector.
     * @return True if approximately perpendicular, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_perpendicular(const Vector2& other) const
    {
        return nnm::approx_zero(dot(other));
    }

    /**
     * Returns a vector that is perpendicular to this vector. There are multiple possible perpendicular vectors so an
     * arbitrary perpendicular vector is returned and no assumptions should be made on which solution is returned.
     * @return Resulting perpendicular vector.
     */
    [[nodiscard]] constexpr Vector2 arbitrary_perpendicular() const
    {
        return { -y, x };
    }

    /**
     * Translate vector as a position.
     * @param by Offset.
     * @return Resulting translated vector.
     */
    [[nodiscard]] Vector2 translate(const Vector2& by) const;

    /**
     * Rotate about the origin.
     * @param angle Angle in radians.
     * @return Resulting rotated vector.
     */
    [[nodiscard]] Vector2 rotate(Real angle) const;

    /**
     * Rotate about an origin.
     * @param origin Origin to rotate about.
     * @param angle Angle in radians.
     * @return Resulting rotate vector.
     */
    [[nodiscard]] Vector2 rotate_at(const Vector2& origin, Real angle) const;

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Resulting scaled vector.
     */
    [[nodiscard]] Vector2 scale(const Vector2& factor) const;

    /**
     * Component-wise scale about an origin.
     * @param origin Origin to scale about.
     * @param factor Scale factor.
     * @return Resulting scaled vector.
     */
    [[nodiscard]] Vector2 scale_at(const Vector2& origin, const Vector2& factor) const;

    /**
     * Shear along the x-axis about the origin.
     * @param angle_y Angle in radians.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] Vector2 shear_x(Real angle_y) const;

    /**
     * Shear along the x-axis about an origin.
     * @param origin Origin to shear about.
     * @param angle_y Angle in radians.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] Vector2 shear_x_at(const Vector2& origin, Real angle_y) const;

    /**
     * Shear along the y-axis about the origin.
     * @param angle_x Angle in radians.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] Vector2 shear_y(Real angle_x) const;

    /**
     * Shear along the y-axis about an origin.
     * @param origin Origin to shear about.
     * @param angle_x Angle in radians.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] Vector2 shear_y_at(const Vector2& origin, Real angle_x) const;

    /**
     * Transform by a 2D basis about the origin.
     * @param by 2D basis to transform by.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] Vector2 transform(const Basis2<Real>& by) const;

    /**
     * Transform by a 2D basis about an origin.
     * @param origin Origin to transform about.
     * @param by 2D basis to transform by.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] Vector2 transform_at(const Vector2& origin, const Basis2<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about the origin.
     * @param by 2D transformation matrix to transform by.
     * @param z The homogenous coordinate which defaults to one.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] Vector2 transform(const Transform2<Real>& by, Real z = static_cast<Real>(1)) const;

    /**
     * Transform by a 2D transformation matrix about an origin.
     * @param origin Origin to transform about.
     * @param by 2D transformation matrix to transform by.
     * @param z The homogenous coordinate which defaults to one.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] Vector2 transform_at(
        const Vector2& origin, const Transform2<Real>& by, Real z = static_cast<Real>(1)) const;

    /**
     * The maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real max() const
    {
        return nnm::max(x, y);
    }

    /**
     * The minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real min() const
    {
        return nnm::min(x, y);
    }

    /**
     * Index of the maximum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    /**
     * Index of the minimum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t min_index() const
    {
        if (x < y) {
            return 0;
        }
        if (y < x) {
            return 1;
        }
        return 0;
    }

    /**
     * Determines if this vector is approximately equal to another vector.
     * @param other Other vector.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Vector2& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y);
    }

    /**
     * Determines if all components are approximately zero.
     * @return True if approximately zero, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y);
    }

    /**
     * Start of the constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* begin() const
    {
        return &x;
    }

    /**
     * End of the constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* end() const
    {
        return &y + 1;
    }

    /**
     * Start of the iterator.
     * @return Iterator.
     */
    Real* begin()
    {
        return &x;
    }

    /**
     * End of the iterator.
     * @return Iterator.
     */
    Real* end()
    {
        return &y + 1;
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        return *(begin() + index);
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        return *(begin() + index);
    }

    /**
     * Determines if this vector equals another.
     * @param other Other vector.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    /**
     * Determines if this vector does not equal another.
     * @param other Other vector.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector2& other) const
    {
        return x != other.x || y != other.y;
    }

    /**
     * Vector addition.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const
    {
        return { x + other.x, y + other.y };
    }

    /**
     * Adds another vector to this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * Vector subtraction.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const
    {
        return { x - other.x, y - other.y };
    }

    /**
     * Subtracts another vector from this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator*(const Vector2& other) const
    {
        return { x * other.x, y * other.y };
    }

    /**
     * Multiplied each component of this vector by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector2& operator*=(const Vector2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    /**
     * Vector-matrix multiplication.
     * @param matrix Matrix.
     * @return Result.
     */
    [[nodiscard]] Vector2 operator*(const Matrix2<Real>& matrix) const;

    /**
     * Vector-scalar multiplication.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator*(const Real value) const
    {
        return { x * value, y * value };
    }

    /**
     * Multiplies each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    Vector2& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Result/
     */
    [[nodiscard]] constexpr Vector2 operator/(const Vector2& other) const
    {
        return { x / other.x, y / other.y };
    }

    /**
     * Divide each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    Vector2& operator/=(const Vector2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    /**
     * Vector-scalar division.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator/(const Real value) const
    {
        return { x / value, y / value };
    }

    /**
     * Divides each component by a value.
     * @param value Value.
     * @return Result.
     */
    Vector2& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    /**
     * Unary plus. Does nothing but specified for symmetry with unary minus.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator+() const
    {
        return { x, y };
    }

    /**
     * Component-wise negation.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2 operator-() const
    {
        return { -x, -y };
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other vector.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Vector2& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != 0 || y != 0;
    }
};

/**
 * Scalar-vector multiplication.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Real>
Vector2<Real> constexpr operator*(const Real value, const Vector2<Real>& vector)
{
    return { value * vector.x, value * vector.y };
}

/**
 * Scalar-vector division.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Real>
Vector2<Real> constexpr operator/(const Real value, const Vector2<Real>& vector)
{
    return { value / vector.x, value / vector.y };
}

/**
 * 2-dimensional vector with integer components.
 * @tparam Int Integer value.
 */
template <typename Int>
class Vector2i {
public:
    Int x;
    Int y;

    /**
     * Initializes all components to zero.
     */
    constexpr Vector2i()
        : x { 0 }
        , y { 0 }
    {
    }

    /**
     * Casts one integer vector into another
     * @tparam Real Integer type.
     * @param vector Vector to cast from.
     */
    template <typename Real>
    explicit constexpr Vector2i(const Vector2<Real>& vector)
        : x { static_cast<Int>(vector.x) }
        , y { static_cast<Int>(vector.y) }
    {
    }

    /**
     * Initialize with specific components.
     * @param x X value.
     * @param y Y value.
     */
    constexpr Vector2i(const Int x, const Int y)
        : x { x }
        , y { y }
    {
    }

    /**
     * Vector with all components to a value.
     * @param value Value to initialize all components with.
     * @return Resulting vector.
     */
    static constexpr Vector2i all(Int value)
    {
        return { value, value };
    }

    /**
     * Vector with all components to zero.
     * @return Resulting vector.
     */
    static constexpr Vector2i zero()
    {
        return { 0, 0 };
    }

    /**
     * Vector with all components to one.
     * @return Resulting vector.
     */
    static constexpr Vector2i one()
    {
        return { 1, 1 };
    }

    /**
     * Normalized vector that points in the direction of the positive x-axis.
     * @return Resulting vector.
     */
    static constexpr Vector2i axis_x()
    {
        return { 1, 0 };
    }

    /**
     * Normalized vector that points in the direction of the positive y-axis.
     * @return Resulting vector.
     */
    static constexpr Vector2i axis_y()
    {
        return { 0, 1 };
    }

    /**
     * Component-wise absolute value.
     * @return Resulting vector.
     */
    [[nodiscard]] constexpr Vector2i abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Resulting vector.
     */
    [[nodiscard]] constexpr Vector2i clamp(const Vector2i& min, const Vector2i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    /**
     * Distance between the position of this vector to another vector along the grid defined by the x and y axes.
     * @param to Position to.
     * @return Resulting distance.
     */
    [[nodiscard]] constexpr Int manhattan_distance(const Vector2i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    /**
     * Squared length of the vector.
     * @return Resulting length.
     */
    [[nodiscard]] constexpr Int length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    /**
     * Vector dot product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Int dot(const Vector2i& other) const
    {
        return x * other.x + y * other.y;
    }

    /**
     * Vector cross product
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Int cross(const Vector2i& other) const
    {
        return x * other.y - y * other.x;
    }

    /**
     * Determines if parallel to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool parallel(const Vector2i& other) const
    {
        return cross(other) == 0;
    }

    /**
     * Determines if perpendicular to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool perpendicular(const Vector2i& other) const
    {
        return dot(other) == 0;
    }

    /**
     * Returns a vector that is perpendicular to this vector. There are multiple possible perpendicular vectors so an
     * arbitrary perpendicular vector is returned and no assumptions should be made on which solution is returned.
     * @return Resulting perpendicular vector.
     */
    [[nodiscard]] constexpr Vector2i arbitrary_perpendicular() const
    {
        return { -y, x };
    }

    /**
     * Maximum component
     * @return Result.
     */
    [[nodiscard]] constexpr Int max() const
    {
        return nnm::max(x, y);
    }

    /**
     * Minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int min() const
    {
        return nnm::min(x, y);
    }

    /**
     * Index of the maximum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    /**
     * Index of the minimum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t min_index() const
    {
        if (x < y) {
            return 0;
        }
        if (y < x) {
            return 1;
        }
        return 0;
    }

    /**
     * Start constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Int* begin() const
    {
        return &x;
    }

    /**
     * End constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Int* end() const
    {
        return &y + 1;
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    Int* begin()
    {
        return &x;
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    Int* end()
    {
        return &y + 1;
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Resulting constant reference.
     */
    [[nodiscard]] const Int& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Resulting reference.
     */
    Int& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
        return *(begin() + index);
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Resulting constant reference.
     */
    [[nodiscard]] const Int& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Resulting reference.
     */
    Int& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
        return *(begin() + index);
    }

    /**
     * Component-wise equality.
     * @param other Other vector.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Vector2i& other) const
    {
        return x == other.x && y == other.y;
    }

    /**
     * Component-wise inequality.
     * @param other Other vector.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector2i& other) const
    {
        return x != other.x || y != other.y;
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator+(const Vector2i& other) const
    {
        return { x + other.x, y + other.y };
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector2i& operator+=(const Vector2i& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator-(const Vector2i& other) const
    {
        return { x - other.x, y - other.y };
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector2i& operator-=(const Vector2i& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator*(const Vector2i& other) const
    {
        return { x * other.x, y * other.y };
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector2i& operator*=(const Vector2i& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator*(const Int value) const
    {
        return { x * value, y * value };
    }

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector2i& operator*=(const Int value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator/(const Vector2i& other) const
    {
        return { x / other.x, y / other.y };
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector2i& operator/=(const Vector2i& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    /**
     * Component-wise division with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator/(const Int value) const
    {
        return { x / value, y / value };
    }

    /**
     * Component-wise division with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector2i& operator/=(const Int value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    /**
     * Component-wise remainder.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator%(const Vector2i& other) const
    {
        return { x % other.x, y % other.y };
    }

    /**
     * Component-wise remainder.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector2i& operator%=(const Vector2i& other)
    {
        x %= other.x;
        y %= other.y;
        return *this;
    }

    /**
     * Component-wise remainder with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator%(const Int value) const
    {
        return { x % value, y % value };
    }

    /**
     * Component-wise remainder with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector2i& operator%=(const Int value)
    {
        x %= value;
        y %= value;
        return *this;
    }

    /**
     * Unary plus. Does nothing but specified for symmetry with unary minus.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator+() const
    {
        return { x, y };
    }

    /**
     * Component-wise negation.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator-() const
    {
        return { -x, -y };
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other vector.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Vector2i& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != 0 || y != 0;
    }
};

/**
 * Component-wise multiplication with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector2i<Int> operator*(const Int value, const Vector2i<Int>& vector)
{
    return { value * vector.x, value * vector.y };
}

/**
 * Component-wise division with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector2i<Int> operator/(const Int value, const Vector2i<Int>& vector)
{
    return { value / vector.x, value / vector.y };
}

/**
 * Component-wise remainder with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector2i<Int> operator%(const Int value, const Vector2i<Int>& vector)
{
    return { value % vector.x, value % vector.y };
}

/**
 * three-dimensional vector.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Vector3 {
public:
    Real x;
    Real y;
    Real z;

    /**
     * Initializes all components to zero.
     */
    constexpr Vector3()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
    {
    }

    /**
     * Casts from three-dimensional integer vector.
     * @tparam Int Integer type.
     * @param vector Vector to cast.
     */
    template <typename Int>
    explicit constexpr Vector3(const Vector3i<Int>& vector);

    /**
     * Casts from other vector.
     * @tparam Other Other floating-point type.
     * @param vector Vector to cast.
     */
    template <typename Other>
    explicit constexpr Vector3(const Vector3<Other>& vector)
        : x { static_cast<Real>(vector.x) }
        , y { static_cast<Real>(vector.y) }
        , z { static_cast<Real>(vector.z) }
    {
    }

    /**
     * Initialize initial components with two-dimensional vector and z with value.
     * @param vector Two-dimensional vector.
     * @param z Z value
     */
    constexpr Vector3(const Vector2<Real>& vector, const Real z)
        : x { vector.x }
        , y { vector.y }
        , z { z }
    {
    }

    /**
     * Initialize with components.
     * @param x X value.
     * @param y Y value.
     * @param z Z value.
     */
    constexpr Vector3(const Real x, const Real y, const Real z)
        : x { x }
        , y { y }
        , z { z }
    {
    }

    /**
     * Vector with all components with value.
     * @param value Value.
     * @return Result.
     */
    static constexpr Vector3 all(Real value)
    {
        return { value, value, value };
    }

    /**
     * Vector with all components zero.
     * @return Result.
     */
    static constexpr Vector3 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Vector with all components one.
     * @return Result.
     */
    static constexpr Vector3 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Normalized vector that points in the direction of the positive x-axis.
     * @return Result.
     */
    static constexpr Vector3 axis_x()
    {
        return { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive y-axis.
     * @return Result.
     */
    static constexpr Vector3 axis_y()
    {
        return { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive z-axis.
     * @return Result.
     */
    static constexpr Vector3 axis_z()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
    }

    /**
     * Component-wise absolute value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    /**
     * Component-wise ceiling.
     * @return Result.
     */
    [[nodiscard]] Vector3 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z) };
    }

    /**
     * Component-wise floor.
     * @return Result.
     */
    [[nodiscard]] Vector3 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z) };
    }

    /**
     * Component-wise round.
     * @return Result.
     */
    [[nodiscard]] Vector3 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 clamp(const Vector3& min, const Vector3& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    /**
     * The direction from position of this vector to the position of another vector.
     * @param to Position to.
     * @return Resulting normalized direction vector.
     */
    [[nodiscard]] Vector3 direction(const Vector3& to) const
    {
        return (to - *this).normalize();
    }

    /**
     * The non-normalized direction from position of this vector to the position of another vector.
     * @param to Position to.
     * @return Resulting non-normalized direction vector.
     */
    [[nodiscard]] Vector3 direction_unnormalized(const Vector3& to) const
    {
        return to - *this;
    }

    /**
     * Squared distance from the position of this vector to the position of another vector.
     * @param to Position to.
     * @return Resulting squared distance.
     */
    [[nodiscard]] constexpr Real distance_sqrd(const Vector3& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        const Real diff_z = to.z - z;
        return sqrd(diff_x) + sqrd(diff_y) + sqrd(diff_z);
    }

    /**
     * Distance from the position of this vector to the position of another vector.
     * @param to Position to.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Vector3& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    /**
     * Distance between the position of this vector to another vector along the grid defined by the x, y, and z axes.
     * @param to Position to.
     * @return Result.
     */
    [[nodiscard]] constexpr Real manhattan_distance(const Vector3& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    /**
     * Squared vector length.
     * @return Resulting squared length.
     */
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    /**
     * Vector length.
     * @return Result.
     */
    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    /**
     * Clamp length.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] Vector3 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    /**
     * Normalize vector length to one.
     * @return Result.
     */
    [[nodiscard]] Vector3 normalize() const
    {
        if (const auto length = this->length(); length > static_cast<Real>(0)) {
            return *this / length;
        }
        return zero();
    }

    /**
     * Linear interpolate from this vector to another.
     * @param to Vector to interpolate to.
     * @param weight Interpolation weight which typically ranges from zero to one.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 lerp(const Vector3& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    /**
     * Linear interpolate from this vector to another which a clamped weight between zero and one.
     * @param to Vector to interpolate to.
     * @param weight Interpolation weight which is clamped from zero to one.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 lerp_clamped(const Vector3& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight) };
    }

    /**
     * Vector dot product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Real dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    /**
     * Vector cross product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 cross(const Vector3& other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    /**
     * Vector outer product.
     * @param other Other vector.
     * @return Resulting 3x3 matrix.
     */
    [[nodiscard]] Matrix3<Real> outer(const Vector3& other) const;

    /**
     * Reflect this vector based on a normal vector.
     * @param normal Normal vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 reflect(const Vector3& normal) const
    {
        Vector3 result;
        const Real dot = this->dot(normal);
        result.x = x - static_cast<Real>(2) * normal.x * dot;
        result.y = y - static_cast<Real>(2) * normal.y * dot;
        result.z = z - static_cast<Real>(2) * normal.z * dot;
        return result;
    }

    /**
     * Project this vector onto another
     * @param onto Vector to project onto.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 project(const Vector3& onto) const
    {
        const Real onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == static_cast<Real>(0)) {
            return zero();
        }
        const Real scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    /**
     * Inverse vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 inverse() const
    {
        return { static_cast<Real>(1) / x, static_cast<Real>(1) / y, static_cast<Real>(1) / z };
    }

    /**
     * Angle in radians from this position vector to another position vector.
     * @param to Position to.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle(const Vector3& to) const
    {
        return atan2(this->cross(to).length(), this->dot(to));
    }

    /**
     * If this vector is parallel to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_parallel(const Vector3& other) const
    {
        return cross(other).approx_zero();
    }

    /**
     * If this vector is perpendicular to another vector.
     * @param other Other vector.
     * @return True if perpendicular, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_perpendicular(const Vector3& other) const
    {
        return nnm::approx_zero(dot(other));
    }

    /**
     * Returns a vector that is perpendicular to this vector. There are multiple possible perpendicular vectors so an
     * arbitrary perpendicular vector is returned and no assumptions should be made on which solution is returned.
     * @return Resulting perpendicular vector.
     */
    [[nodiscard]] constexpr Vector3 arbitrary_perpendicular() const
    {
        const Vector3 other = nnm::abs(x) > nnm::abs(y) ? Vector3 { 0, 1, 0 } : Vector3 { 1, 0, 0 };
        return cross(other);
    }

    /**
     * Translate vector as position.
     * @param by Offset to translate by.
     * @return Result.
     */
    [[nodiscard]] Vector3 translate(const Vector3& by) const;

    /**
     * Rotate via normalized axis and angle in radians about the origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 rotate_axis_angle(const Vector3& axis, Real angle) const;

    /**
     * Rotate via normalized axis and angle in radians around an origin.
     * @param origin Origin to rotate about.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 rotate_axis_angle_at(const Vector3& origin, const Vector3& axis, Real angle) const;

    /**
     * Rotate via quaternion about the origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] Vector3 rotate_quaternion(const Quaternion<Real>& quaternion) const;

    /**
     * Rotate via quaternion about an origin.
     * @param origin Origin to rotate about.
     * @param quaternion Quaternion
     * @return Result.
     */
    [[nodiscard]] Vector3 rotate_quaternion_at(const Vector3& origin, const Quaternion<Real>& quaternion) const;

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Vector3 scale(const Vector3& factor) const;

    /**
     * Component-wise scale about an origin.
     * @param origin Origin to scale bout.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Vector3 scale_at(const Vector3& origin, const Vector3& factor) const;

    /**
     * Shear along x-axis about the origin.
     * @param angle_y Y-Axis angle in radians.
     * @param angle_z Z-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_x(Real angle_y, Real angle_z) const;

    /**
     * Shear along x-axis about an origin.
     * @param origin Origin to shear about.
     * @param angle_y Y-Axis angle in radians.
     * @param angle_z Z-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_x_at(const Vector3& origin, Real angle_y, Real angle_z) const;

    /**
     * Shear along y-axis about the origin.
     * @param angle_x X-Axis angle in radians.
     * @param angle_z Z-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_y(Real angle_x, Real angle_z) const;

    /**
     * Shear along y-axis about the origin.
     * @param origin Origin to shear about.
     * @param angle_x X-Axis angle in radians.
     * @param angle_z Z-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_y_at(const Vector3& origin, Real angle_x, Real angle_z) const;

    /**
     * Shear along z-axis about the origin.
     * @param angle_x X-Axis angle in radians.
     * @param angle_y Y-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_z(Real angle_x, Real angle_y) const;

    /**
     * Shear along z-axis about an origin.
     * @param origin Origin to shear about.
     * @param angle_x X-Axis angle in radians.
     * @param angle_y Y-Axis angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 shear_z_at(const Vector3& origin, Real angle_x, Real angle_y) const;

    /**
     * Transform by a three-dimensional basis matrix about the origin.
     * @param by Basis to transform by.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform(const Basis3<Real>& by) const;

    /**
     * Transform by a three-dimensional basis matrix about an origin.
     * @param origin Origin to transform about.
     * @param by Basis to transform by.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform_at(const Vector3& origin, const Basis3<Real>& by) const;

    /**
     * Transform by a two-dimensional transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform(const Transform2<Real>& by) const;

    /**
     * Transform by a two-dimensional transformation matrix about an origin.
     * @param origin Origin to transform about.
     * @param by Transformation matrix to transform by.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform_at(const Vector2<Real>& origin, const Transform2<Real>& by) const;

    /**
     * Transform by a three-dimensional transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @param w The homogenous coordinate that defaults to one.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform(const Transform3<Real>& by, Real w = static_cast<Real>(1)) const;

    /**
     * Transform by a three-dimensional transformation matrix about an origin.
     * @param origin Origin to transform about.
     * @param by Transform matrix to transform by.
     * @param w The homogenous coordinate that defaults to one.
     * @return Result.
     */
    [[nodiscard]] Vector3 transform_at(
        const Vector3& origin, const Transform3<Real>& by, Real w = static_cast<Real>(1)) const;

    /**
     * Maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real max() const
    {
        return nnm::max(x, nnm::max(y, z));
    }

    /**
     * Minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real min() const
    {
        return nnm::min(x, nnm::min(y, z));
    }

    /**
     * Index of the maximum component.
     * @return Index.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        Real max_val = x;
        auto max_axis = 0;
        if (y > max_val) {
            max_val = y;
            max_axis = 1;
        }
        if (z > max_val) {
            max_axis = 2;
        }
        return max_axis;
    }

    /**
     * Index of the minimum component.
     * @return Index.
     */
    [[nodiscard]] constexpr uint8_t min_index() const
    {
        Real min_val = x;
        auto min_axis = 0;
        if (y < min_val) {
            min_val = y;
            min_axis = 1;
        }
        if (z < min_val) {
            min_axis = 2;
        }
        return min_axis;
    }

    /**
     * If approximately equal to another vector.
     * @param other Other vector.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Vector3& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z);
    }

    /**
     * If all components are approximately zero.
     * @return True if approximately zero, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z);
    }

    /**
     * Two-dimensional vector from the first two components of this vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2<Real> xy() const
    {
        return { x, y };
    }

    /**
     * Start constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* begin() const
    {
        return &x;
    }

    /**
     * End constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* end() const
    {
        return &z + 1;
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    Real* begin()
    {
        return &x;
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    Real* end()
    {
        return &z + 1;
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        return *(begin() + index);
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        return *(begin() + index);
    }

    /**
     * If all components are equal to another vector.
     * @param other Other vector.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    /**
     * If unequal to another vector.
     * @param other Other vector.
     * @return True if unequal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator+(const Vector3& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3& operator+=(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator-(const Vector3& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3& operator-=(const Vector3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator*(const Vector3& other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3& operator*=(const Vector3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    /**
     * Vector-matrix multiplication.
     * @param matrix 3x3 Matrix.
     * @return Result.
     */
    [[nodiscard]] Vector3 operator*(const Matrix3<Real>& matrix) const;

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator*(const Real value) const
    {
        return { x * value, y * value, z * value };
    }

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector3& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator/(const Vector3& other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3& operator/=(const Vector3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    /**
     * Component-wise division with value.
     * @param value Value
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator/(const Real value) const
    {
        return { x / value, y / value, z / value };
    }

    /**
     * Component-wise division with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector3& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    /**
     * Unary plus. Does nothing but provides symmetry with unary minus.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator+() const
    {
        return { x, y, z };
    }

    /**
     * Component-wise negation.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator-() const
    {
        return { -x, -y, -z };
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other vector.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] bool operator<(const Vector3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) > other.at(i)) {
                return false;
            }
        }
        return false;
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0) || z != static_cast<Real>(0);
    }
};

/**
 * Component-wise multiplication with value.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Real>
constexpr Vector3<Real> operator*(const Real value, const Vector3<Real>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

/**
 * Component-wise division with value.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Real>
constexpr Vector3<Real> operator/(const Real value, const Vector3<Real>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
}

/**
 * Three-dimensional vector with integer components.
 * @tparam Int Integer type.
 */
template <typename Int>
class Vector3i {
public:
    Int x;
    Int y;
    Int z;

    /**
     * Initialize with all zeros.
     */
    constexpr Vector3i()
        : x { 0 }
        , y { 0 }
        , z { 0 }
    {
    }

    /**
     * Cast from component with floating-point components.
     * @tparam Real Floating-point type.
     * @param vector Vector to cast from.
     */
    template <typename Real>
    explicit constexpr Vector3i(const Vector3<Real>& vector)
        : x { static_cast<Int>(vector.x) }
        , y { static_cast<Int>(vector.y) }
        , z { static_cast<Int>(vector.z) }
    {
    }

    /**
     * Initialize first two components from two-dimensional vector and z value.
     * @param vector Vector.
     * @param z Z value.
     */
    constexpr Vector3i(const Vector2i<Int>& vector, const Int z)
        : x { vector.x }
        , y { vector.y }
        , z { z }
    {
    }

    /**
     * Initialize with components.
     * @param x X value.
     * @param y Y value.
     * @param z Z value.
     */
    constexpr Vector3i(const Int x, const Int y, const Int z)
        : x { x }
        , y { y }
        , z { z }
    {
    }

    /**
     * Initialize all components with value.
     * @param value Value.
     * @return Result.
     */
    static constexpr Vector3i all(const Int value)
    {
        return { value, value, value };
    }

    /**
     * Initialize all components with zero.
     * @return Result.
     */
    static constexpr Vector3i zero()
    {
        return { 0, 0, 0 };
    }

    /**
     * Initialize all components with one.
     * @return Result.
     */
    static constexpr Vector3i one()
    {
        return { 1, 1, 1 };
    }

    /**
     * Normalized vector that points in the direction of the positive x-axis.
     * @return Result.
     */
    static constexpr Vector3i axis_x()
    {
        return { 1, 0, 0 };
    }

    /**
     * Normalized vector that points in the direction of the positive y-axis.
     * @return Result.
     */
    static constexpr Vector3i axis_y()
    {
        return { 0, 1, 0 };
    }

    /**
     * Normalized vector that points in the direction of the positive z-axis.
     * @return Result.
     */
    static constexpr Vector3i axis_z()
    {
        return { 0, 0, 1 };
    }

    /**
     * Component-wise absolute value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i clamp(const Vector3i& min, const Vector3i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    /**
     * Distance between the position of this vector to another vector along the grid defined by the x, y, and z axes.
     * @param to Position to.
     * @return Resulting distance.
     */
    [[nodiscard]] constexpr Int manhattan_distance(const Vector3i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    /**
     * Squared vector length.
     * @return Result.
     */
    [[nodiscard]] constexpr Int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    /**
     * Vector dot product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Int dot(const Vector3i& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    /**
     * Vector cross product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i cross(const Vector3i& other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    /**
     * If parallel to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool parallel(const Vector3i& other) const
    {
        return cross(other) == zero();
    }

    /**
     * If perpendicular to another vector.
     * @param other Other vector.
     * @return True if perpendicular, false otherwise.
     */
    [[nodiscard]] constexpr bool perpendicular(const Vector3i& other) const
    {
        return dot(other) == 0;
    }

    /**
     * Returns a vector that is perpendicular to this vector. There are multiple possible perpendicular vectors so an
     * arbitrary perpendicular vector is returned and no assumptions should be made on which solution is returned.
     * @return Resulting perpendicular vector.
     */
    [[nodiscard]] constexpr Vector3i arbitrary_perpendicular() const
    {
        const Vector3i other = nnm::abs(x) > nnm::abs(y) ? Vector3i { 0, 1, 0 } : Vector3i { 1, 0, 0 };
        return cross(other);
    }

    /**
     * Maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int max() const
    {
        return nnm::max(x, nnm::max(y, z));
    }

    /**
     * Minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int min() const
    {
        return nnm::min(x, nnm::min(y, z));
    }

    /**
     * Index of maximum component.
     * @return Result.
     */
    [[nodiscard]] uint8_t max_index() const
    {
        uint8_t max_axis = 0;
        if (y > at(max_axis)) {
            max_axis = 1;
        }
        if (z > at(max_axis)) {
            max_axis = 2;
        }
        return max_axis;
    }

    /**
     * Index of minimum component.
     * @return Result.
     */
    [[nodiscard]] uint8_t min_index() const
    {
        uint8_t min_axis = 0;
        if (y < at(min_axis)) {
            min_axis = 1;
        }
        if (z < at(min_axis)) {
            min_axis = 2;
        }
        return min_axis;
    }

    /**
     * Two-dimensional vector from the first two components of this vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i<Int> xy() const
    {
        return { x, y };
    }

    /**
     * Start constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Int* begin() const
    {
        return &x;
    }

    /**
     * End constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Int* end() const
    {
        return &z + 1;
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    Int* begin()
    {
        return &x;
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    Int* end()
    {
        return &z + 1;
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Int& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Int& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
        return *(begin() + index);
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] const Int& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
        return *(begin() + index);
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    Int& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
        return *(begin() + index);
    }

    /**
     * Component-wise equality.
     * @param other Other vector.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Vector3i& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    /**
     * Component-wise inequality.
     * @param other Other vector.
     * @return True if unequal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector3i& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator+(const Vector3i& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3i& operator+=(const Vector3i& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator-(const Vector3i& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3i& operator-=(const Vector3i& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator*(const Vector3i& other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    Vector3i& operator*=(const Vector3i& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator*(const Int value) const
    {
        return { x * value, y * value, z * value };
    }

    /**
     * Component-wise multiplication with value.
     * @param value Value.
     * @return Reference to this modified vector.
     */
    Vector3i& operator*=(const Int value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator/(const Vector3i& other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3i& operator/=(const Vector3i& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    /**
     * Component-wise division with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator/(const Int value) const
    {
        return { x / value, y / value, z / value };
    }

    /**
     * Component-wise division with value.
     * @param value Value.
     * @return Result.
     */
    Vector3i& operator/=(const Int value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    /**
     * Component-wise remainder.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator%(const Vector3i& other) const
    {
        return { x % other.x, y % other.y, z % other.z };
    }

    /**
     * Component-wise remainder.
     * @param other Other vector.
     * @return Reference to this modified vector.
     */
    Vector3i& operator%=(const Vector3i& other)
    {
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return *this;
    }

    /**
     * Component-wise remainder with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator%(const Int value) const
    {
        return { x % value, y % value, z % value };
    }

    /**
     * Component-wise remainder with value.
     * @param value Value.
     * @return Result.
     */
    Vector3i& operator%=(const Int value)
    {
        x %= value;
        y %= value;
        z %= value;
        return *this;
    }

    /**
     * Unary plus. Does nothing but provide symmetry with unary minus.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator+() const
    {
        return { x, y, z };
    }

    /**
     * Component-wise negation.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator-() const
    {
        return { -x, -y, -z };
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other vector.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] bool operator<(const Vector3i& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) > other.at(i)) {
                return false;
            }
        }
        return false;
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] constexpr explicit operator bool() const
    {
        return x != 0 || y != 0 || z != 0;
    }
};

/**
 * Component-wise multiplication with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector3i<Int> operator*(const Int value, const Vector3i<Int>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

/**
 * Component-wise division with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector3i<Int> operator/(const Int value, const Vector3i<Int>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
}

/**
 * Component-wise remainder with value.
 * @tparam Int Integer type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Int>
constexpr Vector3i<Int> operator%(const Int value, const Vector3i<Int>& vector)
{
    return { value % vector.x, value % vector.y, value % vector.z };
}

template <typename Real>
class Vector4 {
public:
    Real x;
    Real y;
    Real z;
    Real w;

    constexpr Vector4()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
        , w { static_cast<Real>(0) }
    {
    }

    template <typename Other>
    explicit constexpr Vector4(const Vector4<Other>& vector)
        : x { static_cast<Real>(vector.x) }
        , y { static_cast<Real>(vector.y) }
        , z { static_cast<Real>(vector.z) }
        , w { static_cast<Real>(vector.w) }
    {
    }

    constexpr Vector4(const Vector2<Real>& vector, const Real z, const Real w)
        : x { vector.x }
        , y { vector.y }
        , z { z }
        , w { w }
    {
    }

    constexpr Vector4(const Vector3<Real>& vector, const Real w)
        : x { vector.x }
        , y { vector.y }
        , z { vector.z }
        , w { w }
    {
    }

    constexpr Vector4(const Real x, const Real y, const Real z, const Real w)
        : x { x }
        , y { y }
        , z { z }
        , w { w }
    {
    }

    static constexpr Vector4 from_quaternion(const Quaternion<Real>& quaternion);

    static constexpr Vector4 all(const Real value)
    {
        return { value, value, value, value };
    }

    static constexpr Vector4 zero()
    {
        return all(static_cast<Real>(0));
    }

    static constexpr Vector4 one()
    {
        return all(static_cast<Real>(1));
    }

    static constexpr Vector4 axis_x()
    {
        return { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) };
    }

    static constexpr Vector4 axis_y()
    {
        return { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) };
    }

    static constexpr Vector4 axis_z()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) };
    }

    static constexpr Vector4 axis_w()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
    }

    [[nodiscard]] constexpr Vector4 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z), nnm::abs(w) };
    }

    [[nodiscard]] Vector4 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z), nnm::ceil(w) };
    }

    [[nodiscard]] Vector4 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z), nnm::floor(w) };
    }

    [[nodiscard]] Vector4 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z), nnm::round(w) };
    }

    [[nodiscard]] constexpr Vector4 clamp(const Vector4& min, const Vector4& max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector4 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    [[nodiscard]] Vector4 normalize() const
    {
        if (const Real length = this->length(); length > static_cast<Real>(0)) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] constexpr Vector4 lerp(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    [[nodiscard]] constexpr Vector4 lerp_clamped(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight),
                 nnm::lerp_clamped(w, to.w, weight) };
    }

    [[nodiscard]] constexpr Real dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] Matrix4<Real> outer(const Vector4& other) const;

    [[nodiscard]] constexpr Vector4 inverse() const
    {
        return {
            static_cast<Real>(1) / x, static_cast<Real>(1) / y, static_cast<Real>(1) / z, static_cast<Real>(1) / w
        };
    }

    [[nodiscard]] Vector4 transform(const Transform3<Real>& by) const;

    [[nodiscard]] Vector4 transform_at(const Vector3<Real>& origin, const Transform3<Real>& by) const;

    [[nodiscard]] constexpr Real max() const
    {
        return nnm::max(x, nnm::max(y, nnm::max(z, w)));
    }

    [[nodiscard]] constexpr Real min() const
    {
        return nnm::min(x, nnm::min(y, nnm::min(z, w)));
    }

    [[nodiscard]] uint8_t max_index() const
    {
        uint8_t max_axis = 0;
        if (y > at(max_axis)) {
            max_axis = 1;
        }
        if (z > at(max_axis)) {
            max_axis = 2;
        }
        if (w > at(max_axis)) {
            max_axis = 3;
        }
        return max_axis;
    }

    [[nodiscard]] uint8_t min_index() const
    {
        uint8_t min_axis = 0;
        if (y < at(min_axis)) {
            min_axis = 1;
        }
        if (z < at(min_axis)) {
            min_axis = 2;
        }
        if (w < at(min_axis)) {
            min_axis = 3;
        }
        return min_axis;
    }

    [[nodiscard]] constexpr bool approx_equal(const Vector4& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z) && nnm::approx_zero(w);
    }

    [[nodiscard]] constexpr Vector2<Real> xy() const
    {
        return { x, y };
    }

    [[nodiscard]] constexpr Vector3<Real> xyz() const
    {
        return { x, y, z };
    }

    [[nodiscard]] const Real* begin() const
    {
        return &x;
    }

    [[nodiscard]] const Real* end() const
    {
        return &w + 1;
    }

    Real* begin()
    {
        return &x;
    }

    Real* end()
    {
        return &w + 1;
    }

    [[nodiscard]] Real at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        return *(begin() + index);
    }

    Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        return *(begin() + index);
    }

    [[nodiscard]] const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        return *(begin() + index);
    }

    Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        return *(begin() + index);
    }

    [[nodiscard]] constexpr bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] constexpr Vector4 operator+(const Vector4& other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4& operator+=(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator-(const Vector4& other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4& operator-=(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator*(const Vector4& other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4& operator*=(const Vector4& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator*(const Matrix4<Real>& matrix) const;

    [[nodiscard]] constexpr Vector4 operator*(const Real value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    Vector4& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    [[nodiscard]] Vector4 constexpr operator/(const Vector4& other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    Vector4& operator/=(const Vector4& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator/(const Real value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    Vector4& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) > other.at(i)) {
                return false;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr Vector4 operator+() const
    {
        return { x, y, z, w };
    }

    [[nodiscard]] constexpr Vector4 operator-() const
    {
        return { -x, -y, -z, -w };
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0) || z != static_cast<Real>(0)
            || w != static_cast<Real>(0);
    }
};

template <typename Real>
Vector4<Real> constexpr operator*(const Real value, const Vector4<Real>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z, value * vector.w };
}

template <typename Real>
Vector4<Real> constexpr operator/(const Real value, const Vector4<Real>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z, value / vector.w };
}

template <typename Real>
class Quaternion {
public:
    Real x;
    Real y;
    Real z;
    Real w;

    constexpr Quaternion()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
        , w { static_cast<Real>(1) }
    {
    }

    template <typename Other>
    explicit constexpr Quaternion(const Quaternion<Other>& quaternion)
        : x { static_cast<Real>(quaternion.x) }
        , y { static_cast<Real>(quaternion.y) }
        , z { static_cast<Real>(quaternion.z) }
        , w { static_cast<Real>(quaternion.w) }
    {
    }

    explicit constexpr Quaternion(const Vector4<Real>& vector)
        : x { vector.x }
        , y { vector.y }
        , z { vector.z }
        , w { vector.w }
    {
    }

    constexpr Quaternion(const Real x, const Real y, const Real z, const Real w)
        : x { x }
        , y { y }
        , z { z }
        , w { w }
    {
    }

    [[nodiscard]] static constexpr Quaternion identity()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
    }

    [[nodiscard]] static Quaternion from_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3<Real> norm = axis.normalize();
        const Real half_sin = sin(angle / static_cast<Real>(2));
        Quaternion<Real> result;
        result.x = norm.x * half_sin;
        result.y = norm.y * half_sin;
        result.z = norm.z * half_sin;
        result.w = cos(angle / static_cast<Real>(2));
        return result;
    }

    [[nodiscard]] static Quaternion from_vector_to_vector(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        const Vector3<Real> from_norm = from.normalize();
        const Vector3<Real> to_norm = to.normalize();
        const Vector3<Real> axis = from_norm.cross(to_norm).normalize();
        const Real dot = clamp(from_norm.dot(to_norm), static_cast<Real>(-1), static_cast<Real>(1));
        const Real angle = acos(dot);
        return from_axis_angle(axis, angle);
    }

    [[nodiscard]] Quaternion normalize() const
    {
        return Quaternion(Vector4<Real>::from_quaternion(*this).normalize());
    }

    [[nodiscard]] Vector3<Real> axis(const Quaternion& to) const
    {
        const Vector3<Real> cross
            = Vector4<Real>::from_quaternion(*this).xyz().cross(Vector4<Real>::from_quaternion(to).xyz());
        return cross.normalize();
    }

    [[nodiscard]] Real angle(const Quaternion& to) const
    {
        return 2 * acos(Vector4<Real>::from_quaternion(*this).dot(Vector4<Real>::from_quaternion(to)));
    }

    [[nodiscard]] Vector3<Real> axis() const
    {
        const Real sin_half_angle = sqrt(1 - sqrd(w));
        if (sin_half_angle == static_cast<Real>(0)) {
            return Vector4<Real>::from_quaternion(*this).xyz();
        }
        return Vector4<Real>::from_quaternion(*this).xyz() / sin_half_angle;
    }

    [[nodiscard]] Real angle() const
    {
        return 2 * acos(w);
    }

    [[nodiscard]] constexpr Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Quaternion slerp(const Quaternion& to, const Real weight) const
    {
        const Vector4 vector = Vector4<Real>::from_quaternion(*this);
        const Vector4 vector_to = Vector4<Real>::from_quaternion(to);
        const Real dot = clamp(vector.dot(vector_to), static_cast<Real>(-1), static_cast<Real>(1));
        const Real angle = acos(dot);
        const Real sin_angle = sin(angle);
        if (sin_angle == static_cast<Real>(0)) {
            return Quaternion(vector.lerp(vector_to, weight));
        }
        return Quaternion(
            (vector * sin((static_cast<Real>(1) - weight) * angle) + vector_to * sin(weight * angle)) / sin_angle);
    }

    [[nodiscard]] Quaternion rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return from_axis_angle(axis, angle) * *this;
    }

    [[nodiscard]] Quaternion rotate_quaternion(const Quaternion& by) const
    {
        return by * *this;
    }

    [[nodiscard]] constexpr bool approx_equal(const Quaternion& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] Real at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
        return *(&x + index);
    }

    Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
        return *(&x + index);
    }

    [[nodiscard]] const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
        return *(&x + index);
    }

    [[nodiscard]] Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
        return *(&x + index);
    }

    [[nodiscard]] constexpr bool operator==(const Quaternion& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] constexpr bool operator!=(const Quaternion& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] constexpr Quaternion operator*(const Quaternion& other) const
    {
        Vector4<Real> vector;
        vector.x = w * other.x + x * other.w + y * other.z - z * other.y;
        vector.y = w * other.y - x * other.z + y * other.w + z * other.x;
        vector.z = w * other.z + x * other.y - y * other.x + z * other.w;
        vector.w = w * other.w - x * other.x - y * other.y - z * other.z;
        return Quaternion(vector);
    }

    Quaternion& operator*=(const Quaternion& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] bool operator<(const Quaternion& other) const
    {
        return Vector4<Real>::from_quaternion(*this) < Vector4<Real>::from_quaternion(other);
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0) || z != static_cast<Real>(0)
            || w != static_cast<Real>(0);
    }
};

template <typename Real>
class Matrix2 {
public:
    Vector2<Real> columns[2];

    constexpr Matrix2()
        : columns { { static_cast<Real>(1), static_cast<Real>(0) }, { static_cast<Real>(0), static_cast<Real>(1) } }
    {
    }

    template <typename Other>
    explicit constexpr Matrix2(const Matrix2<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x), static_cast<Real>(matrix.columns[0].y) },
                    { static_cast<Real>(matrix.columns[1].x), static_cast<Real>(matrix.columns[1].y) } }
    {
    }

    constexpr Matrix2(const Vector2<Real>& column0, const Vector2<Real>& column1)
        : columns { column0, column1 }
    {
    }

    constexpr Matrix2(const Real col0_row0, const Real col0_row1, const Real col1_row0, const Real col1_row1)
        : columns { { col0_row0, col0_row1 }, { col1_row0, col1_row1 } }
    {
    }

    [[nodiscard]] static constexpr Matrix2 all(const Real value)
    {
        return { { value, value }, { value, value } };
    }

    [[nodiscard]] static constexpr Matrix2 zero()
    {
        return all(static_cast<Real>(0));
    }

    [[nodiscard]] static constexpr Matrix2 one()
    {
        return all(static_cast<Real>(1));
    }

    [[nodiscard]] static constexpr Matrix2 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0) }, { static_cast<Real>(0), static_cast<Real>(1) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1);
    }

    [[nodiscard]] Real determinant() const
    {
        return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
    }

    [[nodiscard]] Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        const uint8_t other_column = (column + 1) % 2;
        const uint8_t other_row = (row + 1) % 2;
        return at(other_column, other_row);
    }

    [[nodiscard]] Matrix2 minor() const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        return pow(static_cast<Real>(-1), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix2 cofactor() const
    {
        return { { cofactor_at(0, 0), cofactor_at(0, 1) }, { cofactor_at(1, 0), cofactor_at(1, 1) } };
    }

    [[nodiscard]] Matrix2 transpose() const
    {
        return { { at(0, 0), at(1, 0) }, { at(0, 1), at(1, 1) } };
    }

    [[nodiscard]] Matrix2 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix2 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix2> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix2& other) const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                if (!nnm::approx_equal(at(c, r), other.at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                if (!nnm::approx_zero(at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] Vector2<Real> at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    Vector2<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    [[nodiscard]] Real at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        return columns[column][row];
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return columns[0].begin();
    }

    [[nodiscard]] const Real* end() const
    {
        return columns[1].end();
    }

    Real* begin()
    {
        return columns[0].begin();
    }

    Real* end()
    {
        return columns[1].end();
    }

    const Vector2<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    Vector2<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    bool operator==(const Matrix2& other) const
    {
        for (uint8_t i = 0; i < 2; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix2& other) const
    {
        for (uint8_t i = 0; i < 2; ++i) {
            if (at(i) != other.at(i)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix2 operator+(const Matrix2& other) const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix2& operator+=(const Matrix2& other)
    {
        for (uint8_t c = 0; c < 2; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator-(const Matrix2& other) const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix2& operator-=(const Matrix2& other)
    {
        for (uint8_t c = 0; c < 2; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator*(const Matrix2& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                for (uint8_t i = 0; i < 2; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix2& operator*=(const Matrix2& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector2<Real> operator*(const Vector2<Real>& vector) const
    {
        Vector2<Real> result;
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(r) = at(0, r) * vector.at(0) + at(1, r) * vector.at(1);
        }
        return result;
    }

    [[nodiscard]] Matrix2 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value };
    }

    Matrix2& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        return *this;
    }

    [[nodiscard]] Matrix2 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value };
    }

    Matrix2& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        return *this;
    }

    bool operator<(const Matrix2& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                if (at(c, r) != 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

template <typename Real>
Matrix2<Real> operator*(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (uint8_t c = 0; c < 2; ++c) {
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
Matrix2<Real> operator/(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (uint8_t c = 0; c < 2; ++c) {
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Basis2 {
public:
    Matrix2<Real> matrix;

    constexpr Basis2()
        : matrix(Matrix2<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Basis2(const Basis2<Other>& basis)
        : matrix(Matrix2<Real>(basis.matrix))
    {
    }

    explicit constexpr Basis2(const Matrix2<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Basis2 from_rotation(const Real angle)
    {
        return Basis2({ { cos(angle), sin(angle) }, { -sin(angle), cos(angle) } });
    }

    static constexpr Basis2 from_scale(const Vector2<Real>& factor)
    {
        return Basis2({ { factor.x, static_cast<Real>(0) }, { static_cast<Real>(0), factor.y } });
    }

    static Basis2 from_shear_x(const Real angle_y)
    {
        return Basis2({ { static_cast<Real>(1), static_cast<Real>(0) }, { tan(angle_y), static_cast<Real>(1) } });
    }

    static Basis2 from_shear_y(const Real angle_x)
    {
        return Basis2({ { static_cast<Real>(1), tan(angle_x) }, { static_cast<Real>(0), static_cast<Real>(1) } });
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Basis2 unchecked_inverse() const
    {
        return Basis2(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Basis2> inverse() const
    {
        if (valid()) {
            return Basis2(matrix.unchecked_inverse());
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0);
    }

    [[nodiscard]] Basis2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Basis2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Basis2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis2 shear_x(const Real angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_x_local(const Real angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_y(const Real angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Basis2 shear_y_local(const Real angle_x) const
    {
        return transform_local(from_shear_y(angle_x));
    }

    [[nodiscard]] Basis2 transform(const Basis2& by) const
    {
        return Basis2(by.matrix * matrix);
    }

    [[nodiscard]] Basis2 transform_local(const Basis2& by) const
    {
        return Basis2(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Basis2& other) const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] const Vector2<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1);
        return matrix[column];
    }

    Vector2<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1);
        return matrix[column];
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1 && row <= 1);
        return matrix[column][row];
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1 && row <= 1);
        return matrix[column][row];
    }

    const Vector2<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index <= 1);
        return matrix[index];
    }

    Vector2<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index <= 1);
        return matrix[index];
    }

    bool operator==(const Basis2& other) const
    {
        return matrix == other.matrix;
    }

    bool operator!=(const Basis2& other) const
    {
        return matrix != other.matrix;
    }

    bool operator<(const Basis2& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Matrix3 {
public:
    Vector3<Real> columns[3];

    constexpr Matrix3()
        : columns { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } }
    {
    }

    template <typename Other>
    explicit constexpr Matrix3(const Matrix3<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x),
                      static_cast<Real>(matrix.columns[0].y),
                      static_cast<Real>(matrix.columns[0].z) },
                    { static_cast<Real>(matrix.columns[1].x),
                      static_cast<Real>(matrix.columns[1].y),
                      static_cast<Real>(matrix.columns[1].z) },
                    { static_cast<Real>(matrix.columns[2].x),
                      static_cast<Real>(matrix.columns[2].y),
                      static_cast<Real>(matrix.columns[2].z) } }
    {
    }

    constexpr Matrix3(const Vector3<Real>& column0, const Vector3<Real>& column1, const Vector3<Real>& column2)
        : columns { column0, column1, column2 }
    {
    }

    constexpr Matrix3(
        const Real col0_row0,
        const Real col0_row1,
        const Real col0_row2,
        const Real col1_row0,
        const Real col1_row1,
        const Real col1_row2,
        const Real col2_row0,
        const Real col2_row1,
        const Real col2_row2)
        : columns { { col0_row0, col0_row1, col0_row2 },
                    { col1_row0, col1_row1, col1_row2 },
                    { col2_row0, col2_row1, col2_row2 } }
    {
    }

    [[nodiscard]] static constexpr Matrix3 all(const Real value)
    {
        return { { value, value, value }, { value, value, value }, { value, value, value } };
    }

    [[nodiscard]] static constexpr Matrix3 zero()
    {
        return all(static_cast<Real>(0));
    }

    [[nodiscard]] static constexpr Matrix3 one()
    {
        return all(static_cast<Real>(1));
    }

    [[nodiscard]] static constexpr Matrix3 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2);
    }

    [[nodiscard]] Real determinant() const
    {
        Real det = static_cast<Real>(0);
        for (uint8_t c = 0; c < 3; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1) : -static_cast<Real>(1)) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix2<Real> minor_matrix_at(const uint8_t column, const uint8_t row) const
    {
        Matrix2<Real> minor_matrix;
        uint8_t minor_col = 0;
        for (uint8_t c = 0; c < 3; ++c) {
            if (c == column) {
                continue;
            }
            uint8_t minor_row = 0;
            for (uint8_t r = 0; r < 3; ++r) {
                if (r == row) {
                    continue;
                }
                minor_matrix[minor_col][minor_row] = at(c, r);
                ++minor_row;
            }
            ++minor_col;
        }
        return minor_matrix;
    }

    [[nodiscard]] Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix3 minor() const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return pow(-static_cast<Real>(1), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix3 cofactor() const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0) }, { at(0, 1), at(1, 1), at(2, 1) }, { at(0, 2), at(1, 2), at(2, 2) } };
    }

    [[nodiscard]] Matrix3 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix3 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix3> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix3& other) const
    {
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                if (!nnm::approx_equal(at(c, r), other.at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                if (!nnm::approx_zero(at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return columns[column][row];
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return columns[0].begin();
    }

    [[nodiscard]] const Real* end() const
    {
        return columns[2].end();
    }

    Real* begin()
    {
        return columns[0].begin();
    }

    Real* end()
    {
        return columns[2].end();
    }

    const Vector3<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    Vector3<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    [[nodiscard]] bool operator==(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) != other.at(i)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix3 operator+(const Matrix3& other) const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix3& operator+=(const Matrix3& other)
    {
        for (uint8_t c = 0; c < 3; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator-(const Matrix3& other) const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix3& operator-=(const Matrix3& other)
    {
        for (uint8_t c = 0; c < 3; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator*(const Matrix3& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                for (uint8_t i = 0; i < 3; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix3& operator*=(const Matrix3& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector3<Real> operator*(const Vector3<Real>& vector) const
    {
        auto result = Vector3<Real>::zero();
        for (uint8_t r = 0; r < 3; ++r) {
            for (uint8_t c = 0; c < 3; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value, at(2) * value };
    }

    Matrix3& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        at(2) *= value;
        return *this;
    }

    [[nodiscard]] Matrix3 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value, at(2) / value };
    }

    Matrix3& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        at(2) /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (uint8_t c = 0; c < 3; ++c) { // NOLINT(*-loop-convert)
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

template <typename Real>
Matrix3<Real> operator*(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
Matrix3<Real> operator/(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Transform2 {
public:
    Matrix3<Real> matrix;

    constexpr Transform2()
        : matrix(Matrix3<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Transform2(const Transform2<Other>& transform)
        : matrix(Matrix3<Real>(transform.matrix))
    {
    }

    explicit constexpr Transform2(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Transform2 from_basis_translation(const Basis2<Real>& basis, const Vector2<Real>& translation)
    {
        Matrix3<Real> matrix;
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(2, 0) = translation.x;
        matrix.at(2, 1) = translation.y;
        return Transform2(matrix);
    }

    static Transform2 from_basis(const Basis2<Real>& basis)
    {
        return from_basis_translation(basis, Vector2<Real>::zero());
    }

    static Transform2 from_translation(const Vector2<Real>& pos)
    {
        return from_basis_translation(Basis2<Real>(), pos);
    }

    static Transform2 from_rotation(const Real angle)
    {
        return from_basis_translation(Basis2<Real>::from_rotation(angle), Vector2<Real>());
    }

    static Transform2 from_scale(const Vector2<Real>& factor)
    {
        return from_basis_translation(Basis2<Real>::from_scale(factor), Vector2<Real>());
    }

    static Transform2 from_shear_x(const Real angle_y)
    {
        return from_basis_translation(Basis2<Real>::from_shear_x(angle_y), Vector2<Real>());
    }

    static Transform2 from_shear_y(const Real angle_x)
    {
        return from_basis_translation(Basis2<Real>::from_shear_y(angle_x), Vector2<Real>());
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Transform2 unchecked_inverse() const
    {
        return Transform2(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Transform2> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix.at(0, 2) == static_cast<Real>(0) && matrix.at(1, 2) == static_cast<Real>(0)
            && matrix.at(2, 2) == static_cast<Real>(1);
    }

    [[nodiscard]] Basis2<Real> basis() const
    {
        return Basis2(matrix.minor_matrix_at(2, 2));
    }

    [[nodiscard]] Vector2<Real> translation() const
    {
        return { matrix.at(2, 0), matrix.at(2, 1) };
    }

    [[nodiscard]] Transform2 translate(const Vector2<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform2 translate_local(const Vector2<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Transform2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Transform2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform2 shear_x(const Real angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_x_local(const Real angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_y(const Real angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Transform2 shear_y_local(const Real angle_x) const
    {
        return transform_local(from_shear_y(angle_x));
    }

    [[nodiscard]] Transform2 transform(const Transform2& by) const
    {
        return Transform2(by.matrix * matrix);
    }

    [[nodiscard]] Transform2 transform_local(const Transform2& by) const
    {
        return Transform2(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Transform2& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2 && row <= 2);
        return matrix.at(column, row);
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2 && row <= 2);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    Vector3<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    [[nodiscard]] bool operator==(const Transform2& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Transform2& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Transform2& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Basis3 {
public:
    Matrix3<Real> matrix;

    constexpr Basis3()
        : matrix(Matrix3<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Basis3(const Basis3<Other>& basis)
        : matrix(Matrix3<Real>(basis.matrix))
    {
    }

    explicit constexpr Basis3(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Basis3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3<Real> norm = axis.normalize();
        // Rodrigues' formula
        const Matrix3<Real> k_matrix { { static_cast<Real>(0), norm.z, -norm.y },
                                       { -norm.z, static_cast<Real>(0), norm.x },
                                       { norm.y, -norm.x, static_cast<Real>(0) } };
        const Matrix3<Real> r_matrix
            = Matrix3<Real>::identity() + sin(angle) * k_matrix + (1 - cos(angle)) * k_matrix * k_matrix;
        return Basis3(r_matrix);
    }

    static Basis3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const Quaternion<Real>& q = quaternion;
        Matrix3<Real> matrix;
        matrix.at(0, 0) = 1 - 2 * (sqrd(q.y) + sqrd(q.z));
        matrix.at(0, 1) = 2 * (q.x * q.y + q.z * q.w);
        matrix.at(0, 2) = 2 * (q.x * q.z - q.y * q.w);
        matrix.at(1, 0) = 2 * (q.x * q.y - q.z * q.w);
        matrix.at(1, 1) = 1 - 2 * (sqrd(q.x) + sqrd(q.z));
        matrix.at(1, 2) = 2 * (q.y * q.z + q.x * q.w);
        matrix.at(2, 0) = 2 * (q.x * q.z + q.y * q.w);
        matrix.at(2, 1) = 2 * (q.y * q.z - q.x * q.w);
        matrix.at(2, 2) = 1 - 2 * (sqrd(q.x) + sqrd(q.y));
        return Basis3(matrix);
    }

    static constexpr Basis3 from_scale(const Vector3<Real>& factor)
    {
        return Basis3(
            { { factor.x, static_cast<Real>(0), static_cast<Real>(0) },
              { static_cast<Real>(0), factor.y, static_cast<Real>(0) },
              { static_cast<Real>(0), static_cast<Real>(0), factor.z } });
    }

    static Basis3 from_shear_x(const Real angle_y, const Real angle_z)
    {
        return Basis3(
            { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
              { tan(angle_y), static_cast<Real>(1), static_cast<Real>(0) },
              { tan(angle_z), static_cast<Real>(0), static_cast<Real>(1) } });
    }

    static Basis3 from_shear_y(const Real angle_x, const Real angle_z)
    {
        return Basis3(
            { { static_cast<Real>(1), tan(angle_x), static_cast<Real>(0) },
              { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
              { static_cast<Real>(0), tan(angle_z), static_cast<Real>(1) } });
    }

    static Basis3 from_shear_z(const Real angle_x, const Real angle_y)
    {
        return Basis3(
            { { static_cast<Real>(1), static_cast<Real>(0), tan(angle_x) },
              { static_cast<Real>(0), static_cast<Real>(1), tan(angle_y) },
              { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } });
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Basis3 unchecked_inverse() const
    {
        return Basis3(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Basis3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0);
    }

    [[nodiscard]] Basis3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_x_local(const Real angle_y, const Real angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_y_local(const Real angle_x, const Real angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Basis3 shear_z_local(const Real angle_x, const Real angle_y) const
    {
        return transform_local(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Basis3 transform(const Basis3& by) const
    {
        return Basis3(by.matrix * matrix);
    }

    [[nodiscard]] Basis3 transform_local(const Basis3& by) const
    {
        return Basis3(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Basis3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3);
        return matrix.at(column);
    }

    Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index <= 3);
        return matrix[index];
    }

    Vector3<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index <= 3);
        return matrix[index];
    }

    [[nodiscard]] bool operator==(const Basis3& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Basis3& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Basis3& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Matrix4 {
public:
    Vector4<Real> columns[4];

    constexpr Matrix4()
        : columns { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } }

    {
    }

    template <typename Other>
    explicit constexpr Matrix4(const Matrix4<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x),
                      static_cast<Real>(matrix.columns[0].y),
                      static_cast<Real>(matrix.columns[0].z),
                      static_cast<Real>(matrix.columns[0].w) },
                    { static_cast<Real>(matrix.columns[1].x),
                      static_cast<Real>(matrix.columns[1].y),
                      static_cast<Real>(matrix.columns[1].z),
                      static_cast<Real>(matrix.columns[1].w) },
                    { static_cast<Real>(matrix.columns[2].x),
                      static_cast<Real>(matrix.columns[2].y),
                      static_cast<Real>(matrix.columns[2].z),
                      static_cast<Real>(matrix.columns[2].w) },
                    { static_cast<Real>(matrix.columns[3].x),
                      static_cast<Real>(matrix.columns[3].y),
                      static_cast<Real>(matrix.columns[3].z),
                      static_cast<Real>(matrix.columns[3].w) } }
    {
    }

    constexpr Matrix4(
        const Vector4<Real>& column0,
        const Vector4<Real>& column1,
        const Vector4<Real>& column2,
        const Vector4<Real>& column3)
        : columns { column0, column1, column2, column3 }
    {
    }

    constexpr Matrix4(
        const Real col0_row0,
        const Real col0_row1,
        const Real col0_row2,
        const Real col0_row3,
        const Real col1_row0,
        const Real col1_row1,
        const Real col1_row2,
        const Real col1_row3,
        const Real col2_row0,
        const Real col2_row1,
        const Real col2_row2,
        const Real col2_row3,
        const Real col3_row0,
        const Real col3_row1,
        const Real col3_row2,
        const Real col3_row3)
        : columns { { col0_row0, col0_row1, col0_row2, col0_row3 },
                    { col1_row0, col1_row1, col1_row2, col1_row3 },
                    { col2_row0, col2_row1, col2_row2, col2_row3 },
                    { col3_row0, col3_row1, col3_row2, col3_row3 } }
    {
    }

    [[nodiscard]] static constexpr Matrix4 all(const Real value)
    {
        return { { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value } };
    }

    [[nodiscard]] static constexpr Matrix4 zero()
    {
        return all(static_cast<Real>(0));
    }

    [[nodiscard]] static constexpr Matrix4 one()
    {
        return all(static_cast<Real>(1));
    }

    [[nodiscard]] static constexpr Matrix4 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2) + at(3, 3);
    }

    [[nodiscard]] Real determinant() const
    {
        Real det = static_cast<Real>(0);
        for (uint8_t c = 0; c < 4; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1) : -static_cast<Real>(1)) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix3<Real> minor_matrix_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        Matrix3<Real> minor_matrix;
        uint8_t minor_col = 0;
        for (uint8_t c = 0; c < 4; ++c) {
            if (c == column) {
                continue;
            }
            uint8_t minor_row = 0;
            for (uint8_t r = 0; r < 4; ++r) {
                if (r == row) {
                    continue;
                }
                minor_matrix[minor_col][minor_row] = at(c, r);
                ++minor_row;
            }
            ++minor_col;
        }
        return minor_matrix;
    }

    [[nodiscard]] Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix4 minor() const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return pow(-static_cast<Real>(1), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix4 cofactor() const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix4 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0), at(3, 0) },
                 { at(0, 1), at(1, 1), at(2, 1), at(3, 1) },
                 { at(0, 2), at(1, 2), at(2, 2), at(3, 2) },
                 { at(0, 3), at(1, 3), at(2, 3), at(3, 3) } };
    }

    [[nodiscard]] Matrix4 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix4 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix4> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix4& other) const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!at(c).approx_zero()) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] const Vector4<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3);
        return columns[column];
    }

    Vector4<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3);
        return columns[column];
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return columns[column][row];
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return columns[0].begin();
    }

    [[nodiscard]] const Real* end() const
    {
        return columns[3].end();
    }

    Real* begin()
    {
        return columns[0].begin();
    }

    Real* end()
    {
        return columns[3].end();
    }

    const Vector4<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index <= 3);
        return columns[index];
    }

    Vector4<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index <= 3);
        return columns[index];
    }

    [[nodiscard]] bool operator==(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) != other.at(i)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix4 operator+(const Matrix4& other) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix4& operator+=(const Matrix4& other)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator-(const Matrix4& other) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix4& operator-=(const Matrix4& other)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    Matrix4 operator*(const Matrix4& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                for (uint8_t i = 0; i < 4; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix4& operator*=(const Matrix4& other)
    {
        *this = *this * other;
        return *this;
    }

    Vector4<Real> operator*(const Vector4<Real>& vector) const
    {
        auto result = Vector4<Real>::zero();
        for (uint8_t r = 0; r < 4; ++r) {
            for (uint8_t c = 0; c < 4; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix4 operator*(const Real value) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) * value;
        }
        return result;
    }

    Matrix4& operator*=(const Real value)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) *= value;
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator/(const Real value) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) / value;
        }
        return result;
    }

    Matrix4& operator/=(const Real value)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) /= value;
        }
        return *this;
    }

    bool operator<(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

template <typename Real>
Matrix4<Real> operator*(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
Matrix4<Real> operator/(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Transform3 {
public:
    Matrix4<Real> matrix;

    constexpr Transform3()
        : matrix(Matrix4<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Transform3(const Transform3<Other>& transform)
        : matrix(Matrix4<Real>(transform.matrix))
    {
    }

    explicit constexpr Transform3(const Matrix4<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Transform3 from_basis_translation(const Basis3<Real>& basis, const Vector3<Real>& translation)
    {
        auto matrix = Matrix4<Real>::identity();
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(3, 0) = translation.x;
        matrix.at(3, 1) = translation.y;
        matrix.at(3, 2) = translation.z;
        return Transform3(matrix);
    }

    static Transform3 from_basis(const Basis3<Real>& basis)
    {
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_translation(const Vector3<Real>& translation)
    {
        return from_basis_translation(Basis3<Real>(), translation);
    }

    static Transform3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const auto basis = Basis3<Real>::from_rotation_axis_angle(axis, angle);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const auto basis = Basis3<Real>::from_rotation_quaternion(quaternion);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_scale(const Vector3<Real>& factor)
    {
        return from_basis(Basis3<Real>::from_scale(factor));
    }

    static Transform3 from_shear_x(const Real angle_y, const Real angle_z)
    {
        return from_basis(Basis3<Real>::from_shear_x(angle_y, angle_z));
    }

    static Transform3 from_shear_y(const Real angle_x, const Real angle_z)
    {
        return from_basis(Basis3<Real>::from_shear_y(angle_x, angle_z));
    }

    static Transform3 from_shear_z(const Real angle_x, const Real angle_y)
    {
        return from_basis(Basis3<Real>::from_shear_z(angle_x, angle_y));
    }

    static Transform3 from_perspective_left_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        matrix.at(2, 3) = -static_cast<Real>(1);
        matrix.at(3, 2) = -(static_cast<Real>(2) * far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_left_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = -far_clip / (far_clip - near_clip);
        matrix.at(2, 3) = -static_cast<Real>(1);
        matrix.at(3, 2) = -(far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_right_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = (far_clip + near_clip) / (far_clip - near_clip);
        matrix.at(2, 3) = static_cast<Real>(1);
        matrix.at(3, 2) = -(static_cast<Real>(2) * far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_right_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = far_clip / (far_clip - near_clip);
        matrix.at(2, 3) = static_cast<Real>(1);
        matrix.at(3, 2) = -(far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_orthographic_left_hand_neg1to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = -static_cast<Real>(2) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_orthographic_left_hand_0to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = -static_cast<Real>(1) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -near_clip / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_orthographic_right_hand_neg1to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = static_cast<Real>(2) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    static Transform3 from_orthographic_right_hand_0to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = static_cast<Real>(1) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -near_clip / (far_clip - near_clip);
        return Transform3(matrix);
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Transform3 unchecked_inverse() const
    {
        return Transform3(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Transform3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix.at(0, 3) == static_cast<Real>(0) && matrix.at(1, 3) == static_cast<Real>(0)
            && matrix.at(2, 3) == static_cast<Real>(0) && matrix.at(3, 3) == static_cast<Real>(1);
    }

    [[nodiscard]] Basis3<Real> basis() const
    {
        return Basis3(matrix.minor_matrix_at(3, 3));
    }

    [[nodiscard]] Vector3<Real> translation() const
    {
        return { matrix.at(3, 0), matrix.at(3, 1), matrix.at(3, 2) };
    }

    [[nodiscard]] Transform3 translate(const Vector3<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform3 translate_local(const Vector3<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_x_local(const Real angle_y, const Real angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_y_local(const Real angle_x, const Real angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Transform3 shear_z_local(const Real angle_x, const Real angle_y) const
    {
        return transform_local(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Transform3 transform(const Transform3& by) const
    {
        return Transform3(by.matrix * matrix);
    }

    [[nodiscard]] Transform3 transform_local(const Transform3& by) const
    {
        return Transform3(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Transform3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector4<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix.at(column);
    }

    Vector4<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector4<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix[column];
    }

    Vector4<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix[column];
    }

    [[nodiscard]] bool operator==(const Transform3& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Transform3& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Transform3& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
template <typename Int>
constexpr Vector2<Real>::Vector2(const Vector2i<Int>& vector)
    : x { static_cast<Real>(vector.x) }
    , y { static_cast<Real>(vector.y) }
{
}

template <typename Real>
Matrix2<Real> Vector2<Real>::outer(const Vector2& other) const
{
    Matrix2<Real> result;
    for (uint8_t c = 0; c < 2; ++c) {
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::translate(const Vector2& by) const
{
    return transform(Transform2<Real>::from_translation(by));
}

template <typename Real>
Vector2<Real> Vector2<Real>::rotate(const Real angle) const
{
    return transform(Basis2<Real>::from_rotation(angle));
}

template <typename Real>
Vector2<Real> Vector2<Real>::rotate_at(const Vector2& origin, Real angle) const
{
    return transform_at(origin, Basis2<Real>::from_rotation(angle));
}

template <typename Real>
Vector2<Real> Vector2<Real>::scale(const Vector2& factor) const
{
    return transform(Basis2<Real>::from_scale(factor));
}

template <typename Real>
Vector2<Real> Vector2<Real>::scale_at(const Vector2& origin, const Vector2& factor) const
{
    return transform_at(origin, Basis2<Real>::from_scale(factor));
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_x(const Real angle_y) const
{
    return transform(Basis2<Real>::from_shear_x(angle_y));
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_x_at(const Vector2& origin, Real angle_y) const
{
    return transform_at(origin, Basis2<Real>::from_shear_x(angle_y));
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_y(const Real angle_x) const
{
    return transform(Basis2<Real>::from_shear_y(angle_x));
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_y_at(const Vector2& origin, Real angle_x) const
{
    return transform_at(origin, Basis2<Real>::from_shear_y(angle_x));
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform(const Basis2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform_at(const Vector2& origin, const Basis2<Real>& by) const
{
    return (*this - origin).transform(by) + origin;
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform(const Transform2<Real>& by, const Real z) const
{
    return Vector3<Real>(*this, z).transform(by).xy();
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform_at(const Vector2& origin, const Transform2<Real>& by, Real z) const
{
    return (*this - origin).transform(by, z) + origin;
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator*(const Matrix2<Real>& matrix) const
{
    Vector2 result;
    result.x = x * matrix.at(0, 0) + y * matrix.at(0, 1);
    result.y = x * matrix.at(1, 0) + y * matrix.at(1, 1);
    return result;
}

template <typename Real>
template <typename Int>
constexpr Vector3<Real>::Vector3(const Vector3i<Int>& vector)
    : x { static_cast<Real>(vector.x) }
    , y { static_cast<Real>(vector.y) }
    , z { static_cast<Real>(vector.z) }
{
}

template <typename Real>
Matrix3<Real> Vector3<Real>::outer(const Vector3& other) const
{
    Matrix3<Real> result;
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::translate(const Vector3& by) const
{
    return transform(Transform3<Real>::from_translation(by));
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_axis_angle(const Vector3& axis, const Real angle) const
{
    return transform(Basis3<Real>::from_rotation_axis_angle(axis, angle));
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_axis_angle_at(const Vector3& origin, const Vector3& axis, Real angle) const
{
    return transform_at(origin, Basis3<Real>::from_rotation_axis_angle(axis, angle));
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_quaternion(const Quaternion<Real>& quaternion) const
{
    return transform(Basis3<Real>::from_rotation_quaternion(quaternion));
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_quaternion_at(const Vector3& origin, const Quaternion<Real>& quaternion) const
{
    return transform_at(origin, Basis3<Real>::from_rotation_quaternion(quaternion));
}

template <typename Real>
Vector3<Real> Vector3<Real>::scale(const Vector3& factor) const
{
    return transform(Basis3<Real>::from_scale(factor));
}

template <typename Real>
Vector3<Real> Vector3<Real>::scale_at(const Vector3& origin, const Vector3& factor) const
{
    return transform_at(origin, Basis3<Real>::from_scale(factor));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_x(const Real angle_y, const Real angle_z) const
{
    return transform(Basis3<Real>::from_shear_x(angle_y, angle_z));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_x_at(const Vector3& origin, Real angle_y, Real angle_z) const
{
    return transform_at(origin, Basis3<Real>::from_shear_x(angle_y, angle_z));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_y(const Real angle_x, const Real angle_z) const
{
    return transform(Basis3<Real>::from_shear_y(angle_x, angle_z));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_y_at(const Vector3& origin, Real angle_x, Real angle_z) const
{
    return transform_at(origin, Basis3<Real>::from_shear_y(angle_x, angle_z));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_z(const Real angle_x, const Real angle_y) const
{
    return transform(Basis3<Real>::from_shear_z(angle_x, angle_y));
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_z_at(const Vector3& origin, Real angle_x, Real angle_y) const
{
    return transform_at(origin, Basis3<Real>::from_shear_z(angle_x, angle_y));
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Basis3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform_at(const Vector3& origin, const Basis3<Real>& by) const
{
    return (*this - origin).transform(by) + origin;
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Transform2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform_at(const Vector2<Real>& origin, const Transform2<Real>& by) const
{
    return (*this - Vector3 { origin, static_cast<Real>(0) }).transform(by) + Vector3 { origin, static_cast<Real>(0) };
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Transform3<Real>& by, const Real w) const
{
    return Vector4<Real>(*this, w).transform(by).xyz();
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform_at(const Vector3& origin, const Transform3<Real>& by, Real w) const
{
    return (*this - origin).transform(by, w) + origin;
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator*(const Matrix3<Real>& matrix) const
{
    auto result = zero();
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
constexpr Vector4<Real> Vector4<Real>::from_quaternion(const Quaternion<Real>& quaternion)
{
    return { quaternion.x, quaternion.y, quaternion.z, quaternion.w };
}

template <typename Real>
Matrix4<Real> Vector4<Real>::outer(const Vector4& other) const
{
    Matrix4<Real> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::transform(const Transform3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector4<Real> Vector4<Real>::transform_at(const Vector3<Real>& origin, const Transform3<Real>& by) const
{
    return (*this - Vector4 { origin, static_cast<Real>(0) }).transform(by) + Vector4 { origin, static_cast<Real>(0) };
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator*(const Matrix4<Real>& matrix) const
{
    auto result = zero();
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}
}

template <typename Int>
struct std::hash<nnm::Vector2i<Int>> {
    size_t operator()(const nnm::Vector2i<Int>& vector) const noexcept
    {
        const size_t hash1 = std::hash<Int>()(vector.x);
        const size_t hash2 = std::hash<Int>()(vector.y);
        return hash1 ^ hash2 << 1;
    }
};

template <typename Int>
struct std::hash<nnm::Vector3i<Int>> {
    size_t operator()(const nnm::Vector3i<Int>& vector) const noexcept
    {
        const size_t hash1 = std::hash<Int>()(vector.x);
        const size_t hash2 = std::hash<Int>()(vector.y);
        const size_t hash3 = std::hash<Int>()(vector.z);
        return hash1 ^ hash2 << 1 ^ hash3 << 2;
    }
};

#endif
