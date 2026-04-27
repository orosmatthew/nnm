/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_VECTOR4_HPP
#define NNM_VECTOR4_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>
#include <nnm/vector3.hpp>

namespace nnm {

/**
 * Four-dimensional vector.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Vector4 {
public:
    Real x;
    Real y;
    Real z;
    Real w;

    /**
     * Initializes all components with zero.
     */
    constexpr Vector4()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
        , w { static_cast<Real>(0) }
    {
    }

    /**
     * Cast from another vector type.
     * @tparam Other Other type.
     * @param vector Vector to cast from.
     */
    template <typename Other>
    explicit constexpr Vector4(const Vector4<Other>& vector)
        : x { static_cast<Real>(vector.x) }
        , y { static_cast<Real>(vector.y) }
        , z { static_cast<Real>(vector.z) }
        , w { static_cast<Real>(vector.w) }
    {
    }

    /**
     * Initializes x and y from a two-dimensional vector and z and w from values.
     * @param vector Two-dimensional vector.
     * @param z Z value.
     * @param w W value.
     */
    constexpr Vector4(const Vector2<Real>& vector, const Real z, const Real w)
        : x { vector.x }
        , y { vector.y }
        , z { z }
        , w { w }
    {
    }

    /**
     * Initializes x, y, and z from a three-dimensional vector and w from a value.
     * @param vector Three-dimensional vector.
     * @param w W value.
     */
    constexpr Vector4(const Vector3<Real>& vector, const Real w)
        : x { vector.x }
        , y { vector.y }
        , z { vector.z }
        , w { w }
    {
    }

    /**
     * Initializes with components.
     * @param x X value.
     * @param y Y value.
     * @param z Z value.
     * @param w W value.
     */
    constexpr Vector4(const Real x, const Real y, const Real z, const Real w)
        : x { x }
        , y { y }
        , z { z }
        , w { w }
    {
    }

    /**
     * Vector from quaternion. X, Y, and Z values are copied directly.
     * @param quaternion Quaternion.
     * @return Result.
     */
    static constexpr Vector4 from_quaternion(const Quaternion<Real>& quaternion);

    /**
     * Vector with all components set to a value.
     * @param value Value.
     * @return Result.
     */
    static constexpr Vector4 all(const Real value)
    {
        return { value, value, value, value };
    }

    /**
     * Vector with all components set to zero.
     * @return Result.
     */
    static constexpr Vector4 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Vector with all components set to one.
     * @return Result.
     */
    static constexpr Vector4 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Normalized vector that points in the direction of the positive x-axis.
     * @return Result.
     */
    static constexpr Vector4 axis_x()
    {
        return { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive y-axis.
     * @return Result.
     */
    static constexpr Vector4 axis_y()
    {
        return { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive z-axis.
     * @return Result.
     */
    static constexpr Vector4 axis_z()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) };
    }

    /**
     * Normalized vector that points in the direction of the positive w-axis.
     * @return Result.
     */
    static constexpr Vector4 axis_w()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
    }

    /**
     * Component-wise absolute value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z), nnm::abs(w) };
    }

    /**
     * Component-wise ceiling.
     * @return Result.
     */
    [[nodiscard]] Vector4 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z), nnm::ceil(w) };
    }

    /**
     * Component-wise floor.
     * @return Result.
     */
    [[nodiscard]] Vector4 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z), nnm::floor(w) };
    }

    /**
     * Component-wise round.
     * @return Result.
     */
    [[nodiscard]] Vector4 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z), nnm::round(w) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 clamp(const Vector4& min, const Vector4& max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    /**
     * Squared vector length.
     * @return Result.
     */
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
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
     * Vector with same direction but length is clamped between minimum and maximum values.
     * @param min Minimum length.
     * @param max Maximum length.
     * @return Result.
     */
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

    /**
     * Normalize vector length to one.
     * @return Result.
     */
    [[nodiscard]] Vector4 normalize() const
    {
        if (const Real length = this->length(); length > static_cast<Real>(0)) {
            return *this / length;
        }
        return zero();
    }

    /**
     * Component-wise linear interpolation.
     * @param to Vector to interpolate to.
     * @param weight Interpolation weight typically from zero to one.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 lerp(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    /**
     * Component-wise linear interpolation with weight clamped between zero and one.
     * @param to Vector to interpolate to.
     * @param weight Interpolation weight that is clamped between zero and one.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 lerp_clamped(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight),
                 nnm::lerp_clamped(w, to.w, weight) };
    }

    /**
     * Vector dot product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Real dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    /**
     * Vector outer product.
     * @param other Other vector.
     * @return Resulting 4x4 matrix.
     */
    [[nodiscard]] constexpr Matrix4<Real> outer(const Vector4& other) const;

    /**
     * Inverse vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 inverse() const
    {
        return {
            static_cast<Real>(1) / x, static_cast<Real>(1) / y, static_cast<Real>(1) / z, static_cast<Real>(1) / w
        };
    }

    /**
     * Transform by a three-dimensional transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 transform(const Transform3<Real>& by) const;

    /**
     * Transform by a three-dimensional transformation matrix about an origin.
     * @param origin Origin to transform about.
     * @param by Transformation matrix to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 transform_at(const Vector3<Real>& origin, const Transform3<Real>& by) const;

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
        return at(min_index());
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
     * Index of maximum component.
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
            max_val = z;
            max_axis = 2;
        }
        if (w > max_val) {
            max_axis = 3;
        }
        return max_axis;
    }

    [[nodiscard]] constexpr uint8_t abs_max_index() const
    {
        Real max_val = nnm::abs(x);
        uint8_t max_axis = 0;
        const Real y_abs = nnm::abs(y);
        if (y_abs > max_val) {
            max_val = y_abs;
            max_axis = 1;
        }
        const Real z_abs = nnm::abs(z);
        if (z_abs > max_val) {
            max_val = z_abs;
            max_axis = 2;
        }
        if (nnm::abs(w) > max_val) {
            max_axis = 3;
        }
        return max_axis;
    }

    /**
     * Index of minimum component.
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
            min_val = z;
            min_axis = 2;
        }
        if (w < min_val) {
            min_axis = 3;
        }
        return min_axis;
    }

    /**
     * Index of absolute-value minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t abs_min_index() const
    {
        Real min_val = nnm::abs(x);
        uint8_t min_axis = 0;
        const Real y_abs = nnm::abs(y);
        if (y_abs < min_val) {
            min_val = y_abs;
            min_axis = 1;
        }
        const Real z_abs = nnm::abs(z);
        if (z_abs < min_val) {
            min_val = z_abs;
            min_axis = 2;
        }
        if (nnm::abs(w) < min_val) {
            min_axis = 3;
        }
        return min_axis;
    }

    /**
     * If approximately equal to another vector.
     * @param other Other vector.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Vector4& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    /**
     * If all components are approximately zero.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z) && nnm::approx_zero(w);
    }

    /**
     * Two-dimensional vector from the first two components (x and y) of this vector.
     * @return Resulting two-dimensional vector.
     */
    [[nodiscard]] constexpr Vector2<Real> xy() const
    {
        return { x, y };
    }

    /**
     * Three-dimensional vector from the first three components (x, y, and z) of this vector.
     * @return Resulting three-dimensional vector.
     */
    [[nodiscard]] constexpr Vector3<Real> xyz() const
    {
        return { x, y, z };
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
        return &w + 1;
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
        return &w + 1;
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
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
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index <= 3);
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            return x;
        }
    }

    /**
     * Component-wise equality.
     * @param other Other vector.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    /**
     * Component-wise inequality.
     * @param other Other vector.
     * @return True if unequal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    /**
     * Component-wise addition.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator+(const Vector4& other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    /**
     * Adds another vector to this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator+=(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    /**
     * Component-wise subtraction.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator-(const Vector4& other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    /**
     * Subtracts another vector from this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator-=(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    /**
     * Component-wise multiplication.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator*(const Vector4& other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    /**
     * Multiplies each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator*=(const Vector4& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    /**
     * Vector-matrix multiplication.
     * @param matrix 4x4 matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator*(const Matrix4<Real>& matrix) const;

    /**
     * Vector-scalar multiplication.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator*(const Real value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    /**
     * Multiplies each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    /**
     * Component-wise division.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator/(const Vector4& other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    /**
     * Divides each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator/=(const Vector4& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    /**
     * Vector-scalar division.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator/(const Real value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    /**
     * Divides each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector4& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other vector.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Vector4& other) const
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

    /**
     * Unary plus. Does nothing but provide symmetry with unary minus.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator+() const
    {
        return { x, y, z, w };
    }

    /**
     * Component-wise negation.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector4 operator-() const
    {
        return { -x, -y, -z, -w };
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0) || z != static_cast<Real>(0)
            || w != static_cast<Real>(0);
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
constexpr Vector4<Real> operator*(const Real value, const Vector4<Real>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z, value * vector.w };
}

/**
 * Scalar-vector division.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param vector Vector.
 * @return Result.
 */
template <typename Real>
constexpr Vector4<Real> operator/(const Real value, const Vector4<Real>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z, value / vector.w };
}

template <typename Real>
constexpr Vector4<Real> Vector4<Real>::from_quaternion(const Quaternion<Real>& quaternion)
{
    return { quaternion.x, quaternion.y, quaternion.z, quaternion.w };
}

template <typename Real>
constexpr Matrix4<Real> Vector4<Real>::outer(const Vector4& other) const
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
constexpr Vector4<Real> Vector4<Real>::transform(const Transform3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
constexpr Vector4<Real> Vector4<Real>::transform_at(const Vector3<Real>& origin, const Transform3<Real>& by) const
{
    return (*this - Vector4 { origin, static_cast<Real>(0) }).transform(by) + Vector4 { origin, static_cast<Real>(0) };
}

template <typename Real>
constexpr Vector4<Real> Vector4<Real>::operator*(const Matrix4<Real>& matrix) const
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

#endif
