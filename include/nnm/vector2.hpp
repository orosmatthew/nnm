/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_VECTOR2_HPP
#define NNM_VECTOR2_HPP

#include <nnm/forward.hpp>

namespace nnm {

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
     * Initializes all components to zero.
     */
    constexpr Vector2()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
    {
    }

    /**
     * Casts from the two-dimensional integer vector variant.
     * @tparam Int Integer type.
     * @param vector Vector to cast from.
     */
    template <typename Int>
    explicit constexpr Vector2(const Vector2i<Int>& vector);

    /**
     * Casts from a vector with a different floating-point type.
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
     * Initializes with components.
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
     * Linear interpolate between this vector and another vector.
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
     * @param weight Weight between the two interpolated vectors that is clamped between zero and one.
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
    [[nodiscard]] constexpr Matrix2<Real> outer(const Vector2& other) const;

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
     * Determines if this vector is parallel to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool parallel(const Vector2& other) const
    {
        return nnm::approx_zero(cross(other));
    }

    /**
     * Determines if this vector is perpendicular to another vector.
     * @param other Other vector.
     * @return True if perpendicular, false otherwise.
     */
    [[nodiscard]] constexpr bool perpendicular(const Vector2& other) const
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
     * Rotate about the origin.
     * @param angle Angle in radians.
     * @return Resulting rotated vector.
     */
    [[nodiscard]] Vector2 rotate(Real angle) const;

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Resulting scaled vector.
     */
    [[nodiscard]] constexpr Vector2 scale(const Vector2& factor) const;

    /**
     * Shear along the x-axis about the origin.
     * @param factor Factor.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] constexpr Vector2 shear_x(Real factor) const;

    /**
     * Shear along the y-axis about the origin.
     * @param factor Factor.
     * @return Resulting sheared vector.
     */
    [[nodiscard]] constexpr Vector2 shear_y(Real factor) const;

    /**
     * Transform by a 2D basis about the origin.
     * @param by 2D basis to transform by.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] constexpr Vector2 transform(const Basis2<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about the origin.
     * @param by 2D transformation matrix to transform by.
     * @return Resulting transformed vector.
     */
    [[nodiscard]] constexpr Vector2 transform(const Transform2<Real>& by) const;

    /**
     * The maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real max() const
    {
        return at(max_index());
    }

    /**
     * The absolute-value maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real abs_max() const
    {
        return at(abs_max_index());
    }

    /**
     * The minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real min() const
    {
        return at(min_index());
    }

    /**
     * The absolute-value minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real abs_min() const
    {
        return at(abs_min_index());
    }

    /**
     * Index of the maximum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        if (y > x) {
            return 1;
        }
        return 0;
    }

    /**
     * Index of the absolute-value maximum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t abs_max_index() const
    {
        if (nnm::abs(y) > nnm::abs(x)) {
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
        if (y < x) {
            return 1;
        }
        return 0;
    }

    /**
     * Index of the absolute-value minimum component.
     * @return Resulting index.
     */
    [[nodiscard]] constexpr uint8_t abs_min_index() const
    {
        if (nnm::abs(y) < nnm::abs(x)) {
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
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
    }

    /**
     * Reference to component at index.
     * @param index Index.
     * @return Reference.
     */
    constexpr Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index <= 1);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
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
    constexpr Vector2& operator+=(const Vector2& other)
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
    constexpr Vector2& operator-=(const Vector2& other)
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
     * Multiplies each component of this vector by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2& operator*=(const Vector2& other)
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
    [[nodiscard]] constexpr Vector2 operator*(const Matrix2<Real>& matrix) const;

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
    constexpr Vector2& operator*=(const Real value)
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
    [[nodiscard]] constexpr Vector2 operator/(const Vector2& other) const
    {
        return { x / other.x, y / other.y };
    }

    /**
     * Divides each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2& operator/=(const Vector2& other)
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
    constexpr Vector2& operator/=(const Real value)
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
}

#include <nnm/transform2.hpp>

namespace nnm {

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

template <typename Real>
template <typename Int>
constexpr Vector2<Real>::Vector2(const Vector2i<Int>& vector)
    : x { static_cast<Real>(vector.x) }
    , y { static_cast<Real>(vector.y) }
{
}

template <typename Real>
constexpr Matrix2<Real> Vector2<Real>::outer(const Vector2& other) const
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
Vector2<Real> Vector2<Real>::rotate(const Real angle) const
{
    return transform(Basis2<Real>::from_rotation(angle));
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::scale(const Vector2& factor) const
{
    return transform(Basis2<Real>::from_scale(factor));
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::shear_x(const Real factor) const
{
    return transform(Basis2<Real>::from_shear_x(factor));
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::shear_y(const Real factor) const
{
    return transform(Basis2<Real>::from_shear_y(factor));
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::transform(const Basis2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::transform(const Transform2<Real>& by) const
{
    return (by.matrix * Vector3<Real> { *this, static_cast<Real>(0) }).xy();
}

template <typename Real>
constexpr Vector2<Real> Vector2<Real>::operator*(const Matrix2<Real>& matrix) const
{
    Vector2 result;
    result.x = x * matrix.at(0, 0) + y * matrix.at(0, 1);
    result.y = x * matrix.at(1, 0) + y * matrix.at(1, 1);
    return result;
}
}

#endif
