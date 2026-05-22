/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_VECTOR2I_HPP
#define NNM_VECTOR2I_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>

namespace nnm {

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
     * Initializes with specific components.
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
     * Vector with all components set to zero.
     * @return Resulting vector.
     */
    static constexpr Vector2i zero()
    {
        return { 0, 0 };
    }

    /**
     * Vector with all components set to one.
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
     * Manhattan distance to another vector.
     * @param to Other vector.
     * @return Resulting distance.
     */
    [[nodiscard]] constexpr Int manhattan_distance(const Vector2i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    /**
     * Squared length of the vector.
     * @return Resulting squared length.
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
     * Vector cross product.
     * @param other Other vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Int cross(const Vector2i& other) const
    {
        return x * other.y - y * other.x;
    }

    /**
     * Determines if this vector is parallel to another vector.
     * @param other Other vector.
     * @return True if parallel, false otherwise.
     */
    [[nodiscard]] constexpr bool parallel(const Vector2i& other) const
    {
        return cross(other) == 0;
    }

    /**
     * Determines if this vector is perpendicular to another vector.
     * @param other Other vector.
     * @return True if perpendicular, false otherwise.
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
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Int& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
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
    constexpr Int& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
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
    [[nodiscard]] constexpr const Int& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
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
    constexpr Int& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index <= 1);
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
     * Adds another vector to this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator+=(const Vector2i& other)
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
     * Subtracts another vector from this vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator-=(const Vector2i& other)
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
     * Multiplies each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator*=(const Vector2i& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    /**
     * Vector-scalar multiplication.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2i operator*(const Int value) const
    {
        return { x * value, y * value };
    }

    /**
     * Multiplies each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator*=(const Int value)
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
     * Divides each component by another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator/=(const Vector2i& other)
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
    [[nodiscard]] constexpr Vector2i operator/(const Int value) const
    {
        return { x / value, y / value };
    }

    /**
     * Divides each component by a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator/=(const Int value)
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
     * Applies component-wise remainder with another vector.
     * @param other Other vector.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator%=(const Vector2i& other)
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
     * Applies component-wise remainder with a value.
     * @param value Value.
     * @return Reference to this vector.
     */
    constexpr Vector2i& operator%=(const Int value)
    {
        x %= value;
        y %= value;
        return *this;
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
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != 0 || y != 0;
    }

    /**
     * Hash type for 2D integer vector.
     */
    struct Hash {
        size_t operator()(const Vector2i& vector) const noexcept
        {
            // Based on Boost's hash_combine.
            size_t seed = std::hash<Int>()(vector.x);
            seed ^= std::hash<Int>()(vector.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
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
constexpr Vector2i<Int> operator*(const Int value, const Vector2i<Int>& vector)
{
    return { value * vector.x, value * vector.y };
}

/**
 * Scalar-vector division.
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
}

#endif
