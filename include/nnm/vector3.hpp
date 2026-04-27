/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_VECTOR3_HPP
#define NNM_VECTOR3_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>

namespace nnm {

/**
 * Three-dimensional vector.
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
     * Initializes x and y from a two-dimensional vector and z from a value.
     * @param vector Two-dimensional vector.
     * @param z Z value.
     */
    constexpr Vector3(const Vector2<Real>& vector, const Real z)
        : x { vector.x }
        , y { vector.y }
        , z { z }
    {
    }

    /**
     * Initializes with components.
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
     * Vector with all components set to a value.
     * @param value Value.
     * @return Result.
     */
    static constexpr Vector3 all(Real value)
    {
        return { value, value, value };
    }

    /**
     * Vector with all components set to zero.
     * @return Result.
     */
    static constexpr Vector3 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Vector with all components set to one.
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
    [[nodiscard]] constexpr Matrix3<Real> outer(const Vector3& other) const;

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
    [[nodiscard]] constexpr bool parallel(const Vector3& other) const
    {
        return cross(other).approx_zero();
    }

    /**
     * If this vector is perpendicular to another vector.
     * @param other Other vector.
     * @return True if perpendicular, false otherwise.
     */
    [[nodiscard]] constexpr bool perpendicular(const Vector3& other) const
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
     * Rotate via normalized axis and angle in radians about the origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector3 rotate_axis_angle(const Vector3& axis, Real angle) const;

    /**
     * Rotate via quaternion about the origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 rotate_quaternion(const Quaternion<Real>& quaternion) const;

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 scale(const Vector3& factor) const;

    /**
     * Shear along x-axis about the origin.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 shear_x(Real factor_y, Real factor_z) const;

    /**
     * Shear along y-axis about the origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 shear_y(Real factor_x, Real factor_z) const;

    /**
     * Shear along z-axis about the origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 shear_z(Real factor_x, Real factor_y) const;

    /**
     * Transform by a three-dimensional basis matrix about the origin.
     * @param by Basis to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 transform(const Basis3<Real>& by) const;

    /**
     * Transform by a two-dimensional transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 transform(const Transform2<Real>& by) const;

    /**
     * Transform by a three-dimensional transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @param w The homogenous coordinate that defaults to zero for direction vectors.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 transform(const Transform3<Real>& by, Real w = static_cast<Real>(0)) const;

    /**
     * Maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real max() const
    {
        return at(max_index());
    }

    /**
     * Absolute-value maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real abs_max() const
    {
        return at(abs_max_index());
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
     * Absolute-value minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Real abs_min() const
    {
        return at(abs_min_index());
    }

    /**
     * Index of the maximum component.
     * @return Index.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        Real max_val = x;
        uint8_t max_axis = 0;
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
     * Index of the absolute-value maximum component.
     * @return Index.
     */
    [[nodiscard]] constexpr uint8_t abs_max_index() const
    {
        Real max_val = nnm::abs(x);
        uint8_t max_axis = 0;
        const Real y_abs = nnm::abs(y);
        if (y_abs > max_val) {
            max_val = y_abs;
            max_axis = 1;
        }
        if (nnm::abs(z) > max_val) {
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
        uint8_t min_axis = 0;
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
     * Index of the absolute-value minimum component.
     * @return Index.
     */
    [[nodiscard]] constexpr uint8_t abs_min_index() const
    {
        Real min_val = nnm::abs(x);
        uint8_t min_axis = 0;
        const Real y_abs = nnm::abs(y);
        if (y_abs < min_val) {
            min_val = y;
            min_axis = 1;
        }
        if (nnm::abs(z) < min_val) {
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
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index <= 2);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
        }
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
     * Adds another vector to this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator+=(const Vector3& other)
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
     * Subtracts another vector from this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator-=(const Vector3& other)
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
     * Multiplies each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator*=(const Vector3& other)
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
    [[nodiscard]] constexpr Vector3 operator*(const Matrix3<Real>& matrix) const;

    /**
     * Vector-scalar multiplication.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator*(const Real value) const
    {
        return { x * value, y * value, z * value };
    }

    /**
     * Multiplies each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator*=(const Real value)
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
     * Divides each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator/=(const Vector3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    /**
     * Vector-scalar division.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3 operator/(const Real value) const
    {
        return { x / value, y / value, z / value };
    }

    /**
     * Divides each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector3& operator/=(const Real value)
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
    [[nodiscard]] constexpr bool operator<(const Vector3& other) const
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
}

#include <nnm/transform3.hpp>

namespace nnm {

/**
 * Scalar-vector multiplication.
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
 * Scalar-vector division.
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

template <typename Real>
template <typename Int>
constexpr Vector3<Real>::Vector3(const Vector3i<Int>& vector)
    : x { static_cast<Real>(vector.x) }
    , y { static_cast<Real>(vector.y) }
    , z { static_cast<Real>(vector.z) }
{
}

template <typename Real>
constexpr Matrix3<Real> Vector3<Real>::outer(const Vector3& other) const
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
Vector3<Real> Vector3<Real>::rotate_axis_angle(const Vector3& axis, const Real angle) const
{
    return transform(Basis3<Real>::from_rotation_axis_angle(axis, angle));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::rotate_quaternion(const Quaternion<Real>& quaternion) const
{
    return transform(Basis3<Real>::from_rotation_quaternion(quaternion));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::scale(const Vector3& factor) const
{
    return transform(Basis3<Real>::from_scale(factor));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::shear_x(const Real factor_y, const Real factor_z) const
{
    return transform(Basis3<Real>::from_shear_x(factor_y, factor_z));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::shear_y(const Real factor_x, const Real factor_z) const
{
    return transform(Basis3<Real>::from_shear_y(factor_x, factor_z));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::shear_z(const Real factor_x, const Real factor_y) const
{
    return transform(Basis3<Real>::from_shear_z(factor_x, factor_y));
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::transform(const Basis3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::transform(const Transform2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::transform(const Transform3<Real>& by, const Real w) const
{
    return Vector4<Real>(*this, w).transform(by).xyz();
}

template <typename Real>
constexpr Vector3<Real> Vector3<Real>::operator*(const Matrix3<Real>& matrix) const
{
    auto result = zero();
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}
}

#endif
