/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_QUATERNION_HPP
#define NNM_QUATERNION_HPP

#include <nnm/forward.hpp>
#include <nnm/vector3.hpp>
#include <nnm/vector4.hpp>

namespace nnm {

/**
 * Quaternion which is a four-component vector that represents rotations in three-dimensional space.
 * @tparam Real Floating-point value.
 */
template <typename Real>
class Quaternion {
public:
    Real x;
    Real y;
    Real z;
    Real w;

    /**
     * Initializes with quaternion identity.
     */
    constexpr Quaternion()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
        , w { static_cast<Real>(1) }
    {
    }

    /**
     * Cast from another quaternion type.
     * @tparam Other Other type.
     * @param quaternion Quaternion to cast from.
     */
    template <typename Other>
    explicit constexpr Quaternion(const Quaternion<Other>& quaternion)
        : x { static_cast<Real>(quaternion.x) }
        , y { static_cast<Real>(quaternion.y) }
        , z { static_cast<Real>(quaternion.z) }
        , w { static_cast<Real>(quaternion.w) }
    {
    }

    /**
     * Initializes from a four-dimensional vector. No normalization is done.
     * @param vector Vector.
     */
    explicit constexpr Quaternion(const Vector4<Real>& vector)
        : x { vector.x }
        , y { vector.y }
        , z { vector.z }
        , w { vector.w }
    {
    }

    /**
     * Initializes with components. No normalization is done.
     * @param x X value.
     * @param y Y value.
     * @param z Z value.
     * @param w W value.
     */
    constexpr Quaternion(const Real x, const Real y, const Real z, const Real w)
        : x { x }
        , y { y }
        , z { z }
        , w { w }
    {
    }

    /**
     * Quaternion identity which is x, y, and z being zero and w being one.
     * @return Result.
     */
    [[nodiscard]] static constexpr Quaternion identity()
    {
        return { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) };
    }

    /**
     * Quaternion from a normalized axis and angle in radians.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] static Quaternion from_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3<Real> norm = axis.normalize();
        const Real half_sin = sin(angle / static_cast<Real>(2));
        Quaternion result;
        result.x = norm.x * half_sin;
        result.y = norm.y * half_sin;
        result.z = norm.z * half_sin;
        result.w = cos(angle / static_cast<Real>(2));
        return result;
    }

    /**
     * Quaternion that represents the rotation required to align one vector in the direction of another vector.
     * @param from Vector from.
     * @param to Vector to.
     * @return Result.
     */
    [[nodiscard]] static Quaternion from_vector_to_vector(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        const Vector3<Real> from_norm = from.normalize();
        const Vector3<Real> to_norm = to.normalize();
        const Vector3<Real> axis = from_norm.cross(to_norm).normalize();
        const Real dot = clamp(from_norm.dot(to_norm), static_cast<Real>(-1), static_cast<Real>(1));
        const Real angle = acos(dot);
        return from_axis_angle(axis, angle);
    }

    /**
     * Normalize quaternion.
     * @return Result.
     */
    [[nodiscard]] Quaternion normalize() const
    {
        return Quaternion(Vector4<Real>::from_quaternion(*this).normalize());
    }

    /**
     * The normalized axis of rotation between this quaternion and another quaternion.
     * @param to Quaternion to.
     * @return Resulting normalized, three-dimensional axis.
     */
    [[nodiscard]] Vector3<Real> axis_to(const Quaternion& to) const
    {
        const Quaternion relative = (to * inverse()).normalize();
        const Real sin_half_angle = sqrt(static_cast<Real>(1) - sqrd(relative.w));
        if (sin_half_angle == static_cast<Real>(0)) {
            return Vector3<Real>::axis_x();
        }
        return Vector4<Real>::from_quaternion(relative).xyz() / sin_half_angle;
    }

    /**
     * Angle of rotation, in radians, between this quaternion and another quaternion.
     * @param to Quaternion to.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle_to(const Quaternion& to) const
    {
        Real dot = Vector4<Real>::from_quaternion(*this).dot(Vector4<Real>::from_quaternion(to));
        dot = clamp(dot, static_cast<Real>(-1), static_cast<Real>(1));
        return static_cast<Real>(2) * acos(dot);
    }

    /**
     * The axis of rotation of the quaternion.
     * @return Resulting normalized axis.
     */
    [[nodiscard]] Vector3<Real> axis() const
    {
        const Real sin_half_angle = sqrt(static_cast<Real>(1) - sqrd(w));
        if (sin_half_angle == static_cast<Real>(0)) {
            return Vector4<Real>::from_quaternion(*this).xyz();
        }
        return Vector4<Real>::from_quaternion(*this).xyz() / sin_half_angle;
    }

    /**
     * The angle of rotation of the quaternion in radians.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle() const
    {
        return static_cast<Real>(2) * acos(w);
    }

    /**
     * Quaternion inverse.
     * @return Result.
     */
    [[nodiscard]] constexpr Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    /**
     * Squared length of quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    /**
     * Length of quaternion.
     * @return Result.
     */
    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    /**
     * Spherical linear interpolation from one quaternion to another.
     * @param to Quaternion to interpolate to.
     * @param weight Interpolate weight typically from zero to one.
     * @return Result.
     */
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

    /**
     * Rotate about a normalized axis and angle in radians.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Quaternion rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return from_axis_angle(axis, angle) * *this;
    }

    /**
     * Rotate by another quaternion.
     * @param by Quaternion to rotate by.
     * @return Result.
     */
    [[nodiscard]] constexpr Quaternion rotate_quaternion(const Quaternion& by) const
    {
        return by * *this;
    }

    /**
     * Component-wise equality.
     * @param other Other quaternion.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Quaternion& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    /**
     * Constant reference to component at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
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
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
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
     * @return Result.
     */
    [[nodiscard]] constexpr const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
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
     * @return Result.
     */
    [[nodiscard]] constexpr Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index <= 3);
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
     * @param other Other quaternion.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Quaternion& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    /**
     * Component-wise inequality.
     * @param other Other quaternion.
     * @return True if unequal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Quaternion& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    /**
     * Quaternion multiplication.
     * @param other Other quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Quaternion operator*(const Quaternion& other) const
    {
        Vector4<Real> vector;
        vector.x = w * other.x + x * other.w + y * other.z - z * other.y;
        vector.y = w * other.y - x * other.z + y * other.w + z * other.x;
        vector.z = w * other.z + x * other.y - y * other.x + z * other.w;
        vector.w = w * other.w - x * other.x - y * other.y - z * other.z;
        return Quaternion(vector);
    }

    /**
     * Quaternion multiplication.
     * @param other Other quaternion.
     * @return Reference to this modified quaternion.
     */
    constexpr Quaternion& operator*=(const Quaternion& other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * Lexicographical comparison between components.
     * @param other Other quaternion.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Quaternion& other) const
    {
        return Vector4<Real>::from_quaternion(*this) < Vector4<Real>::from_quaternion(other);
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
}

#endif
