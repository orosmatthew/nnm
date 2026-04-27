/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_VECTOR3I_HPP
#define NNM_VECTOR3I_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2i.hpp>
#include <nnm/vector3.hpp>

namespace nnm {

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
     * Initializes with all zeros.
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
     * Initializes x and y from a two-dimensional vector and z from a value.
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
     * Initializes with components.
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
     * Initializes all components with value.
     * @param value Value.
     * @return Result.
     */
    static constexpr Vector3i all(const Int value)
    {
        return { value, value, value };
    }

    /**
     * Initializes all components with zero.
     * @return Result.
     */
    static constexpr Vector3i zero()
    {
        return { 0, 0, 0 };
    }

    /**
     * Initializes all components with one.
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
        return at(max_index());
    }

    /**
     * Absolute-value maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int abs_max() const
    {
        return at(abs_max_index());
    }

    /**
     * Minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int min() const
    {
        return at(min_index());
    }

    /**
     * Absolute-value minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr Int abs_min() const
    {
        return at(abs_min_index());
    }

    /**
     * Index of maximum component.
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t max_index() const
    {
        Int max_val = x;
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
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t abs_max_index() const
    {
        Int max_val = nnm::abs(x);
        uint8_t max_axis = 0;
        const Int y_abs = nnm::abs(y);
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
     * Index of minimum component.
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t min_index() const
    {
        Int min_val = x;
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
     * @return Result.
     */
    [[nodiscard]] constexpr uint8_t abs_min_index() const
    {
        Int min_val = nnm::abs(x);
        uint8_t min_axis = 0;
        const Int y_abs = nnm::abs(y);
        if (y_abs < min_val) {
            min_val = y_abs;
            min_axis = 1;
        }
        if (nnm::abs(z) < min_val) {
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
    [[nodiscard]] constexpr const Int& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
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
    constexpr Int& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
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
    [[nodiscard]] constexpr const Int& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
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
    constexpr Int& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index <= 2);
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
     * Adds another vector to this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator+=(const Vector3i& other)
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
     * Subtracts another vector from this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator-=(const Vector3i& other)
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
     * Multiplies each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator*=(const Vector3i& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    /**
     * Vector-scalar multiplication.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3i operator*(const Int value) const
    {
        return { x * value, y * value, z * value };
    }

    /**
     * Multiplies each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator*=(const Int value)
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
     * Divides each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator/=(const Vector3i& other)
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
    [[nodiscard]] constexpr Vector3i operator/(const Int value) const
    {
        return { x / value, y / value, z / value };
    }

    /**
     * Divides each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator/=(const Int value)
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
     * Applies component-wise remainder with another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector3i& operator%=(const Vector3i& other)
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
    constexpr Vector3i& operator%=(const Int value)
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
    [[nodiscard]] constexpr bool operator<(const Vector3i& other) const
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

    /**
     * Hash type for 3D integer vector.
     */
    struct Hash {
        size_t operator()(const Vector3i& vector) const noexcept
        {
            // Based on Boost's hash_combine.
            size_t seed = std::hash<Int>()(vector.x);
            seed ^= std::hash<Int>()(vector.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<Int>()(vector.z) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
};

/**
 * Scalar-vector multiplication.
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
 * Scalar-vector division.
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
}

#endif
