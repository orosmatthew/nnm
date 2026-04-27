/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_POINT2_HPP
#define NNM_POINT2_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>

namespace nnm {

/**
 * 2-dimensional point.
 * @tparam Real Floating-point value.
 */
template <typename Real>
class Point2 {
public:
    Real x;
    Real y;

    /**
     * Constructs point at the origin.
     */
    constexpr Point2()
        : x { static_cast<Real>(0) }
        , y { static_cast<Real>(0) }
    {
    }

    /**
     * Copy constructs from another point with a potentially different floating-point type.
     * @tparam Other Other floating-point type.
     * @param point Point.
     */
    template <typename Other>
    explicit constexpr Point2(const Point2<Other>& point)
        : x { static_cast<Real>(point.x) }
        , y { static_cast<Real>(point.y) }
    {
    }

    /**
     * Constructs point from x and y coordinates.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     */
    constexpr Point2(const Real x, const Real y)
        : x { x }
        , y { y }
    {
    }

    /**
     * Constructs point from a vector.
     * @param vector Vector.
     * @return Resulting point.
     */
    static constexpr Point2 from_vector(const Vector2<Real>& vector)
    {
        return Point2 { vector.x, vector.y };
    }

    /**
     * Point with all coordinates set to a value.
     * @param value Value.
     * @return Resulting point.
     */
    static constexpr Point2 all(const Real value)
    {
        return Point2 { value, value };
    }

    /**
     * Point at the origin.
     * @return Resulting point.
     */
    static constexpr Point2 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Converts point to vector.
     * @return Resulting vector.
     */
    [[nodiscard]] constexpr Vector2<Real> to_vector() const
    {
        return Vector2<Real> { x, y };
    }

    /**
     * Absolute value of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] constexpr Point2 abs() const
    {
        return Point2 { nnm::abs(x), nnm::abs(y) };
    }

    /**
     * Ceiling of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] constexpr Point2 ceil() const
    {
        return Point2 { nnm::ceil(x), nnm::ceil(y) };
    }

    /**
     * Floor of all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] constexpr Point2 floor() const
    {
        return Point2 { nnm::floor(x), nnm::floor(y) };
    }

    /**
     * Round all coordinates.
     * @return Resulting point.
     */
    [[nodiscard]] constexpr Point2 round() const
    {
        return Point2 { nnm::round(x), nnm::round(y) };
    }

    /**
     * Component-wise clamp.
     * @param min Minimum.
     * @param max Maximum.
     * @return Result.
     */
    [[nodiscard]] constexpr Point2 clamp(const Point2& min, const Point2& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    /**
     * Unit-length direction vector from this point to another point.
     * @param to Point to get the direction to.
     * @return Resulting direction vector.
     */
    [[nodiscard]] Vector2<Real> direction(const Point2& to) const
    {
        return (to - *this).normalize();
    }

    /**
     * Direction vector from this point to another point without normalizing.
     * @param to Point to get the direction to.
     * @return Resulting direction vector.
     */
    [[nodiscard]] constexpr Vector2<Real> direction_unnormalized(const Point2& to) const
    {
        return to - *this;
    }

    /**
     * Squared distance to another point.
     * @param to Other point.
     * @return Resulting squared distance.
     */
    [[nodiscard]] constexpr Real distance_sqrd(const Point2& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        return sqrd(diff_x) + sqrd(diff_y);
    }

    /**
     * Distance to another point.
     * @param to Other point.
     * @return Resulting distance.
     */
    [[nodiscard]] Real distance(const Point2& to) const
    {
        return sqrt(distance_sqrd(to));
    }

    /**
     * Manhattan distance to another point.
     * @param to Other point.
     * @return Resulting Manhattan distance.
     */
    [[nodiscard]] constexpr Real manhattan_distance(const Point2& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    /**
     * Linear interpolate between this point and another point.
     * @param to Point to interpolate to.
     * @param weight Weight between the two interpolated points.
     * @return Resulting interpolated point.
     */
    [[nodiscard]] constexpr Point2 lerp(const Point2& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight) };
    }

    /**
     * Linear interpolate between this point and another point where the weight is clamped between zero and one.
     * @param to Point to interpolate to.
     * @param weight Weight between the two interpolated points that is clamped between zero and one.
     * @return Resulting interpolated point.
     */
    [[nodiscard]] constexpr Point2 lerp_clamped(const Point2& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight), nnm::lerp_clamped(y, to.y, weight) };
    }

    /**
     * Angle in radians from this point to another point.
     * @param to Other point.
     * @return Resulting angle in radians.
     */
    [[nodiscard]] Real angle_to(const Point2& to) const
    {
        return atan2(to.y - y, to.x - x);
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Resulting translated point.
     */
    [[nodiscard]] constexpr Point2 translate(const Vector2<Real>& offset) const
    {
        return { x + offset.x, y + offset.y };
    }

    /**
     * Component-wise scale about the origin.
     * @param factor Scale factor.
     * @return Resulting scaled point.
     */
    [[nodiscard]] constexpr Point2 scale(const Vector2<Real>& factor) const;

    /**
     * Component-wise scale about an origin.
     * @param origin Origin.
     * @param factor Scale factor.
     * @return Resulting scaled point.
     */
    [[nodiscard]] constexpr Point2 scale_at(const Point2& origin, const Vector2<Real>& factor) const;

    /**
     * Rotate about the origin.
     * @param angle Angle in radians.
     * @return Resulting rotated point.
     */
    [[nodiscard]] Point2 rotate(Real angle) const;

    /**
     * Rotate about an origin.
     * @param origin Origin.
     * @param angle Angle in radians.
     * @return Resulting rotated point.
     */
    [[nodiscard]] Point2 rotate_at(const Point2& origin, Real angle) const;

    /**
     * Shear along the x-axis about the origin.
     * @param factor Factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point2 shear_x(Real factor) const;

    /**
     * Shear along the x-axis about an origin.
     * @param origin Origin.
     * @param factor Factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point2 shear_x_at(const Point2& origin, Real factor) const;

    /**
     * Shear along the y-axis about the origin.
     * @param factor Factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point2 shear_y(Real factor) const;

    /**
     * Shear along the y-axis about an origin.
     * @param origin Origin.
     * @param factor Factor.
     * @return Resulting sheared point.
     */
    [[nodiscard]] constexpr Point2 shear_y_at(const Point2& origin, Real factor) const;

    /**
     * Transform by a 2D basis about the origin.
     * @param by 2D basis to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point2 transform(const Basis2<Real>& by) const;

    /**
     * Transform by a 2D basis about an origin.
     * @param origin Origin.
     * @param by 2D basis to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point2 transform_at(const Point2& origin, const Basis2<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about the origin.
     * @param by 2D transformation matrix to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point2 transform(const Transform2<Real>& by) const;

    /**
     * Transform by a 2D transformation matrix about an origin.
     * @param origin Origin.
     * @param by 2D transformation matrix to transform by.
     * @return Resulting transformed point.
     */
    [[nodiscard]] constexpr Point2 transform_at(const Point2& origin, const Transform2<Real>& by) const;

    /**
     * Determines if this point is approximately equal to another point.
     * @param other Other point.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Point2& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y);
    }

    /**
     * Determines if all coordinates are approximately zero.
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
     * Constant reference to coordinate at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Point2", index <= 1);
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
     * Reference to coordinate at index.
     * @param index Index.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Point2", index <= 1);
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
     * Constant reference to coordinate at index.
     * @param index Index.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Point2", index <= 1);
        return at(index);
    }

    /**
     * Reference to coordinate at index.
     * @param index Index.
     * @return Reference.
     */
    [[nodiscard]] Real& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Point2", index <= 1);
        return at(index);
    }

    /**
     * Determines if this point equals another.
     * @param other Other point.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Point2& other) const
    {
        return x == other.x && y == other.y;
    }

    /**
     * Determines if this point does not equal another.
     * @param other Other point.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Point2& other) const
    {
        return x != other.x || y != other.y;
    }

    /**
     * Point-vector addition.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Point2 operator+(const Vector2<Real>& offset) const
    {
        return translate(offset);
    }

    /**
     * Adds an offset to this point.
     * @param offset Offset.
     * @return Reference to this point.
     */
    constexpr Point2& operator+=(const Vector2<Real>& offset)
    {
        *this = *this + offset;
        return *this;
    }

    /**
     * Point-point subtraction.
     * @param other Other point.
     * @return Resulting offset vector.
     */
    [[nodiscard]] constexpr Vector2<Real> operator-(const Point2& other) const
    {
        return to_vector() - other.to_vector();
    }

    /**
     * Point-vector subtraction.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Point2 operator-(const Vector2<Real>& offset) const
    {
        return translate(-offset);
    }

    /**
     * Subtracts an offset from this point.
     * @param offset Offset.
     * @return Reference to this point.
     */
    constexpr Point2& operator-=(const Vector2<Real>& offset)
    {
        *this = *this - offset;
        return *this;
    }

    /**
     * Lexicographical comparison between coordinates.
     * @param other Other point.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Point2& other) const
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
     * Evaluates to false if all coordinates are zero, true otherwise.
     */
    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0) || y != static_cast<Real>(0);
    }
};

template <typename Real>
Point2<Real> Point2<Real>::rotate(Real angle) const
{
    return transform(Basis2<Real>::from_rotation(angle));
}

template <typename Real>
Point2<Real> Point2<Real>::rotate_at(const Point2& origin, Real angle) const
{
    return transform_at(origin, Basis2<Real>::from_rotation(angle));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::scale(const Vector2<Real>& factor) const
{
    return transform(Basis2<Real>::from_scale(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::scale_at(const Point2& origin, const Vector2<Real>& factor) const
{
    return transform_at(origin, Basis2<Real>::from_scale(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::shear_x(Real factor) const
{
    return transform(Basis2<Real>::from_shear_x(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::shear_x_at(const Point2& origin, Real factor) const
{
    return transform_at(origin, Basis2<Real>::from_shear_x(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::shear_y(Real factor) const
{
    return transform(Basis2<Real>::from_shear_y(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::shear_y_at(const Point2& origin, Real factor) const
{
    return transform_at(origin, Basis2<Real>::from_shear_y(factor));
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::transform(const Basis2<Real>& by) const
{
    return from_vector(by.matrix * to_vector());
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::transform_at(const Point2& origin, const Basis2<Real>& by) const
{
    return from_vector(by.matrix * (*this - origin) + origin.to_vector());
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::transform(const Transform2<Real>& by) const
{
    return from_vector((by.matrix * Vector3<Real> { to_vector(), static_cast<Real>(1) }).xy());
}

template <typename Real>
constexpr Point2<Real> Point2<Real>::transform_at(const Point2& origin, const Transform2<Real>& by) const
{
    return from_vector((by.matrix * Vector3<Real> { *this - origin, static_cast<Real>(1) }).xy() + origin.to_vector());
}
}

#endif
