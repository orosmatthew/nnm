/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_POINT3_HPP
#define NNM_POINT3_HPP

#include <nnm/forward.hpp>
#include <nnm/point2.hpp>
#include <nnm/vector3.hpp>

namespace nnm {

/**
 * 3-dimensional point.
 * @tparam Real Floating-point value.
 */
template <typename Real>
class Point3 {
public:
    Real x;
    Real y;
    Real z;

    /**
     * Constructs point at the origin.
     */
    constexpr Point3()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
        , z { static_cast<Real>(0) }
    {
    }

    /**
     * Copy constructs from another point with a potentially different floating-point type.
     * @tparam Other Other floating-point type.
     * @param point Point.
     */
    template <typename Other>
    explicit constexpr Point3(const Point3<Other>& point)
        : x { static_cast<Real>(point.x) }
        , y { static_cast<Real>(point.y) }
        , z { static_cast<Real>(point.z) }
    {
    }

    /**
     * Constructs point from x and y coordinates and z depth.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param z Z-coordinate.
     */
    constexpr Point3(const Real x, const Real y, const Real z)
        : x { x }
        , y { y }
        , z { z }
    {
    }

    /**
     * Constructs point from a vector.
     * @param vector Vector.
     * @return Resulting point.
     */
    static constexpr Point3 from_vector(const Vector3<Real>& vector)
    {
        return { vector.x, vector.y, vector.z };
    }

    /**
     * Point with all coordinates set to a value.
     * @param value Value.
     * @return Resulting point.
     */
    static constexpr Point3 all(const Real value)
    {
        return { value, value, value };
    }

    /**
     * Point at the origin.
     * @return Resulting point.
     */
    static constexpr Point3 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Converts point to vector.
     * @return Resulting vector.
     */
    [[nodiscard]] constexpr Vector3<Real> to_vector() const
    {
        return { x, y, z };
    }

    /**
     * Absolute value of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] constexpr Point3 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    /**
     * Ceiling of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] Point3 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z) };
    }

    /**
     * Floor of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] Point3 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z) };
    }

    /**
     * Round all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] Point3 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Point3 clamp(const Point3& min, const Point3& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    /**
     * Unit-length direction vector from this point to another point.
     * @param to Point to get the direction to.
     * @return Resulting direction vector.
     */
    [[nodiscard]] Vector3<Real> direction(const Point3& to) const
    {
        return (to - *this).normalize();
    }

    /**
     * Direction vector from this point to another point without normalizing.
     * @param to Point to get the direction to.
     * @return Resulting direction vector.
     */
    [[nodiscard]] constexpr Vector3<Real> direction_unnormalized(const Point3& to) const
    {
        return to - *this;
    }

    /**
     * Squared distance to another point.
     * @param to Other point.
     * @return Resulting squared distance.
     */
    [[nodiscard]] constexpr Real distance_sqrd(const Point3& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        const Real diff_z = to.z - z;
        return sqrd(diff_x) + sqrd(diff_y) + sqrd(diff_z);
    }

    /**
     * Distance to another point.
     * @param to Other point.
     * @return Resulting distance.
     */
    [[nodiscard]] Real distance(const Point3& to) const
    {
        return sqrt(distance_sqrd(to));
    }

    /**
     * Manhattan distance to another point.
     * @param to Other point.
     * @return Resulting Manhattan distance.
     */
    [[nodiscard]] constexpr Real manhattan_distance(const Point3& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    /**
     * Linear interpolate between this point and another point.
     * @param to Point to interpolate to.
     * @param weight Weight between the two interpolated points.
     * @return Resulting interpolated point.
     */
    [[nodiscard]] constexpr Point3 lerp(const Point3& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    /**
     * Linear interpolate between this point and another point where the weight is clamped between zero and one.
     * @param to Point to interpolate to.
     * @param weight Weight between the two interpolated points that is clamped between zero and one.
     * @return Resulting interpolated point.
     */
    [[nodiscard]] constexpr Point3 lerp_clamped(const Point3& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight) };
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Resulting translated point.
     */
    [[nodiscard]] constexpr Point3 translate(const Vector3<Real>& offset) const
    {
        return { x + offset.x, y + offset.y, z + offset.z };
    }

    /**
     * Rotate via normalized axis and angle in radians about the origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Resulting rotated point.
     */
    [[nodiscard]] Point3 rotate_axis_angle(const Vector3<Real>& axis, Real angle) const;

    /**
     * Rotate via normalized axis and angle in radians around an origin.
     * @param origin Origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Resulting rotated point.
     */
    [[nodiscard]] Point3 rotate_axis_angle_at(const Point3& origin, const Vector3<Real>& axis, Real angle) const;

    /**
     * Rotate via quaternion about the origin.
     * @param quaternion Quaternion.
     * @return Resulting rotated point.
     */
    [[nodiscard]] constexpr Point3 rotate_quaternion(const Quaternion<Real>& quaternion) const;

    /**
     * Rotate via quaternion about an origin.
     * @param origin Origin.
     * @param quaternion Quaternion.
     * @return Resulting rotated point.
     */
    [[nodiscard]] constexpr Point3 rotate_quaternion_at(const Point3& origin, const Quaternion<Real>& quaternion) const;

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Resulting scaled point.
     */
    [[nodiscard]] constexpr Point3 scale(const Vector3<Real>& factor) const;

    /**
     * Component-wise scale about an origin.
     * @param origin Origin.
     * @param factor Scale factor.
     * @return Resulting scaled point.
     */
    [[nodiscard]] constexpr Point3 scale_at(const Point3& origin, const Vector3<Real>& factor) const;

    /**
     * Shear along the x-axis about the origin.
     * @param factor_y Y-axis factor.
     * @param factor_z Z-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_x(Real factor_y, Real factor_z) const;

    /**
     * Shear along the x-axis about an origin.
     * @param origin Origin.
     * @param factor_y Y-axis factor.
     * @param factor_z Z-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_x_at(const Point3& origin, Real factor_y, Real factor_z) const;

    /**
     * Shear along the y-axis about the origin.
     * @param factor_x X-axis factor.
     * @param factor_z Z-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_y(Real factor_x, Real factor_z) const;

    /**
     * Shear along the y-axis about an origin.
     * @param origin Origin.
     * @param factor_x X-axis factor.
     * @param factor_z Z-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_y_at(const Point3& origin, Real factor_x, Real factor_z) const;

    /**
     * Shear along the z-axis about the origin.
     * @param factor_x X-axis factor.
     * @param factor_y Y-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_z(Real factor_x, Real factor_y) const;

    /**
     * Shear along the z-axis about an origin.
     * @param origin Origin.
     * @param factor_x X-axis factor.
     * @param factor_y Y-axis factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point3 shear_z_at(const Point3& origin, Real factor_x, Real factor_y) const;

    /**
     * Transform by a 3D basis about the origin.
     * @param by Basis to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform(const Basis3<Real>& by) const;

    /**
     * Transform by a 3D basis about an origin.
     * @param origin Origin.
     * @param by Basis to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform_at(const Point3& origin, const Basis3<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform(const Transform2<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about an origin.
     * @param origin Origin.
     * @param by Transformation matrix to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform_at(const Point2<Real>& origin, const Transform2<Real>& by) const;

    /**
     * Transform by a 3D transformation matrix about the origin.
     * @param by Transformation matrix to transform by.
     * @param w Homogenous coordinate that defaults to one.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform(const Transform3<Real>& by, Real w = static_cast<Real>(1)) const;

    /**
     * Transform by a 3D transformation matrix about an origin.
     * @param origin Origin.
     * @param by Transformation matrix to transform by.
     * @param w Homogenous coordinate that defaults to one.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point3 transform_at(
        const Point3& origin, const Transform3<Real>& by, Real w = static_cast<Real>(1)) const;

    /**
     * Determines if this point is approximately equal to another point.
     * @param other Other point.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Point3& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z);
    }

    /**
     * Determines if all coordinates are approximately zero.
     * @return True if approximately zero, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z);
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
        return &z + 1;
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
        return &z + 1;
    }

    /**
     * Constant reference to coordinate at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Point3", index <= 2);
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
     * Reference to coordinate at index.
     * @param index Index.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Point3", index <= 2);
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
     * Constant reference to coordinate at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Point3", index <= 2);
        return at(index);
    }

    /**
     * Reference to coordinate at index.
     * @param index Index.
     * @return Reference.
     */
    [[nodiscard]] Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Point3", index <= 2);
        return at(index);
    }

    /**
     * Determines if this point equals another.
     * @param other Other point.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Point3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    /**
     * Determines if this point does not equal another.
     * @param other Other point.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Point3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    /**
     * Point-vector addition.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Point3 operator+(const Vector3<Real>& offset) const
    {
        return translate(offset);
    }

    /**
     * Adds an offset to this point.
     * @param offset Offset.
     * @return Reference to this point.
     */
    constexpr Point3& operator+=(const Vector3<Real>& offset)
    {
        *this = *this + offset;
        return *this;
    }

    /**
     * Point-point subtraction.
     * @param other Other point.
     * @return Resulting offset vector.
     */
    [[nodiscard]] constexpr Vector3<Real> operator-(const Point3& other) const
    {
        return to_vector() - other.to_vector();
    }

    /**
     * Point-vector subtraction.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Point3 operator-(const Vector3<Real>& offset) const
    {
        return translate(-offset);
    }

    /**
     * Subtracts an offset from this point.
     * @param offset Offset.
     * @return Reference to this point.
     */
    constexpr Point3& operator-=(const Vector3<Real>& offset)
    {
        *this = *this - offset;
        return *this;
    }

    /**
     * Lexicographical comparison between coordinates.
     * @param other Other point.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Point3& other) const
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
     * Evaluates to false if all coordinates are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0) || z != static_cast<Real>(0);
    }
};

template <typename Real>
Point3<Real> Point3<Real>::rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
{
    return transform(Basis3<Real>::from_rotation_axis_angle(axis, angle));
}

template <typename Real>
Point3<Real> Point3<Real>::rotate_axis_angle_at(const Point3& origin, const Vector3<Real>& axis, Real angle) const
{
    return transform_at(origin, Basis3<Real>::from_rotation_axis_angle(axis, angle));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::rotate_quaternion(const Quaternion<Real>& quaternion) const
{
    return transform(Basis3<Real>::from_rotation_quaternion(quaternion));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::rotate_quaternion_at(
    const Point3& origin, const Quaternion<Real>& quaternion) const
{
    return transform_at(origin, Basis3<Real>::from_rotation_quaternion(quaternion));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::scale(const Vector3<Real>& factor) const
{
    return transform(Basis3<Real>::from_scale(factor));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::scale_at(const Point3& origin, const Vector3<Real>& factor) const
{
    return transform_at(origin, Basis3<Real>::from_scale(factor));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_x(Real factor_y, Real factor_z) const
{
    return transform(Basis3<Real>::from_shear_x(factor_y, factor_z));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_x_at(const Point3& origin, Real factor_y, Real factor_z) const
{
    return transform_at(origin, Basis3<Real>::from_shear_x(factor_y, factor_z));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_y(Real factor_x, Real factor_z) const
{
    return transform(Basis3<Real>::from_shear_y(factor_x, factor_z));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_y_at(const Point3& origin, Real factor_x, Real factor_z) const
{
    return transform_at(origin, Basis3<Real>::from_shear_y(factor_x, factor_z));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_z(Real factor_x, Real factor_y) const
{
    return transform(Basis3<Real>::from_shear_z(factor_x, factor_y));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::shear_z_at(const Point3& origin, Real factor_x, Real factor_y) const
{
    return transform_at(origin, Basis3<Real>::from_shear_z(factor_x, factor_y));
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform(const Basis3<Real>& by) const
{
    return from_vector(by.matrix * to_vector());
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform_at(const Point3& origin, const Basis3<Real>& by) const
{
    return from_vector(by.matrix * (*this - origin) + origin.to_vector());
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform(const Transform2<Real>& by) const
{
    return from_vector(by.matrix * to_vector());
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform_at(const Point2<Real>& origin, const Transform2<Real>& by) const
{
    return from_vector(
        (to_vector() - Vector3<Real> { origin.to_vector(), static_cast<Real>(0) }).transform(by)
        + Vector3<Real> { origin.to_vector(), static_cast<Real>(0) });
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform(const Transform3<Real>& by, const Real w) const
{
    return from_vector(Vector4<Real>(to_vector(), w).transform(by).xyz());
}

template <typename Real>
constexpr Point3<Real> Point3<Real>::transform_at(const Point3& origin, const Transform3<Real>& by, Real w) const
{
    return from_vector((*this - origin).transform(by, w) + origin.to_vector());
}
}

#endif
