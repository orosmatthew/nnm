/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM_HPP
#define NNM_GEOM_HPP

#include <nnm/nnm.hpp>

namespace nnm {

template <typename Real = float>
class Line2;
using Line2f = Line2<>;
using Line2d = Line2<double>;

template <typename Real>
class Line2 {
public:
    Vector2<Real> origin;
    Vector2<Real> direction;

    constexpr Line2()
        : origin { Vector2<Real>::zero() }
        , direction { static_cast<Real>(1), static_cast<Real>(0) }
    {
    }

    constexpr Line2(const Vector2<Real>& origin, const Vector2<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    static Line2 from_points(const Vector2<Real>& point1, const Vector2<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    [[nodiscard]] constexpr Line2 parallel_contains(const Vector2<Real>& point) const
    {
        return { point, direction };
    }

    [[nodiscard]] constexpr Line2 perpendicular_contains(const Vector2<Real>& point) const
    {
        return { point, { -direction.y, direction.x } };
    }

    [[nodiscard]] Line2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> t = (point - origin) / direction;
        return approx_equal(t.x, t.y);
    }

    [[nodiscard]] constexpr Real distance(const Vector2<Real>& point) const
    {
        return abs(direction.cross(point - origin));
    }

    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
    {
        return direction.cross(point - origin);
    }

    [[nodiscard]] constexpr bool approx_parallel(const Line2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Line2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] constexpr Vector2<Real> unchecked_intersection(const Line2& other) const
    {
        const Real denom = direction.cross(other.direction);
        const Vector2<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction) / denom;
        return origin + direction * t;
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2& other) const
    {
        const Real denom = direction.cross(other.direction);
        if (approx_zero(denom)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction) / denom;
        return origin + direction * t;
    }

    [[nodiscard]] constexpr Vector2<Real> project(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        const Real t = diff.dot(direction) / direction.dot(direction);
        return origin + direction * t;
    }

    [[nodiscard]] constexpr Real unchecked_slope() const
    {
        return direction.y / direction.x;
    }

    [[nodiscard]] constexpr std::optional<Real> slope() const
    {
        if (direction.x == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_slope();
    }

    [[nodiscard]] constexpr Real unchecked_intercept_x() const
    {
        const Real t = -origin.y / direction.y;
        return origin.x + direction.x * t;
    }

    [[nodiscard]] constexpr std::optional<Real> intercept_x() const
    {
        if (direction.y == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_intercept_x();
    }

    [[nodiscard]] constexpr Real unchecked_intercept_y() const
    {
        const Real t = -origin.x / direction.x;
        return origin.y + direction.y * t;
    }

    [[nodiscard]] constexpr std::optional<Real> intercept_y() const
    {
        if (direction.x == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_intercept_y();
    }

    [[nodiscard]] bool approx_coincident(const Line2& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = origin - other.origin;
        return approx_zero(diff.cross(other.direction));
    }

    [[nodiscard]] Line2 transform(const Basis2<Real>& by) const
    {
        return { origin.transform(by), direction.transform(by).normalize() };
    }

    [[nodiscard]] Line2 transform_local(const Basis2<Real>& by) const
    {
        return { origin, direction.transform(by).normalize() };
    }

    [[nodiscard]] Line2 transform(const Transform2<Real>& by) const
    {
        return { origin.transform(by), direction.transform(by, static_cast<Real>(0)).normalize() };
    }

    [[nodiscard]] Line2 transform_local(const Transform2<Real>& by) const
    {
        return { origin, direction.transform(by, static_cast<Real>(0)).normalize() };
    }

    [[nodiscard]] Line2 translate(const Vector2<Real>& by) const
    {
        return transform(Transform2<Real>::from_translation(by));
    }

    [[nodiscard]] Line2 scale(const Vector2<Real>& by) const
    {
        return transform(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Line2 scale_local(const Vector2<Real>& by) const
    {
        return transform_local(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Line2 rotate(const Real angle) const
    {
        return transform(Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Line2 rotate_local(const Real angle) const
    {
        return transform(Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Line2 shear_x(const Real angle_y) const
    {
        return transform(Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Line2 shear_x_local(const Real angle_y) const
    {
        return transform_local(Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Line2 shear_y(const Real angle_x) const
    {
        return transform(Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] Line2 shear_y_local(const Real angle_x) const
    {
        return transform_local(Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] bool operator==(const Line2& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    [[nodiscard]] bool operator!=(const Line2& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    [[nodiscard]] bool operator<(const Line2& other) const
    {
        return origin < other.origin && direction < other.direction;
    }
};

template <typename Real = float>
class Ray2 {
public:
    Vector2<Real> origin;
    Vector2<Real> direction;

    Ray2(const Vector2<Real>& origin, const Vector2<Real>& direction)
    {
    }
};

template <typename Real = float>
class AlignedRectangle {
public:
    Vector2<Real> min;
    Vector2<Real> max;

    AlignedRectangle()
        : min { Vector2<Real>::zero() }
        , max { Vector2<Real>::zero() }
    {
    }

    AlignedRectangle(const Vector2<Real>& min, const Vector2<Real>& max)
        : min { min }
        , max { max }
    {
    }

    static AlignedRectangle from_center_size(const Vector2<Real>& center, const Vector2<Real>& size)
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return { { center.x - half_size.x, center.y - half_size.y },
                 { center.x + half_size.x, center.y + half_size.y } };
    }

    [[nodiscard]] Vector2<Real> vertex_nx_ny() const
    {
        return min;
    }

    [[nodiscard]] Vector2<Real> vertex_nx_py() const
    {
        return { min.x, max.y };
    }

    [[nodiscard]] Vector2<Real> vertex_px_ny() const
    {
        return { max.x, min.y };
    }

    [[nodiscard]] Vector2<Real> vertex_px_py() const
    {
        return max;
    }

    [[nodiscard]] Vector2<Real> center() const
    {
        return (min + max) / static_cast<Real>(2);
    }

    [[nodiscard]] Vector2<Real> size() const
    {
        return { max.x - min.x, max.y - min.y };
    }

    [[nodiscard]] AlignedRectangle center_to_origin() const
    {
        const Vector2<Real> c = center();
        return { { min.x - c.x, min.y - c.y }, { max.x - c.x, max.y - c.y } };
    }

    [[nodiscard]] AlignedRectangle translate(const Vector2<Real>& by) const
    {
        return transform(Transform2<Real>::from_translation(by));
    }

    [[nodiscard]] AlignedRectangle scale(const Vector2<Real>& by) const
    {
        return transform(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] AlignedRectangle scale_local(const Vector2<Real>& by) const
    {
        return transform_local(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] AlignedRectangle transform(const Basis2<Real>& by) const
    {
        return { min.transform(by), max.transform(by) };
    }

    [[nodiscard]] AlignedRectangle transform_local(const Basis2<Real>& by) const
    {
        const Vector2<Real> saved_center = center();
        return center_to_origin().transform(by).translate(saved_center);
    }

    [[nodiscard]] AlignedRectangle transform(const Transform2<Real>& by) const
    {
        return { min.transform(by), max.transform(by) };
    }

    [[nodiscard]] AlignedRectangle transform_local(const Transform2<Real>& by) const
    {
        const Vector2<Real> saved_center = center();
        return center_to_origin().transform(by).translate(saved_center);
    }

    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
    }
};

class AlignedRectangleI {
public:
    Vector2i min;
    Vector2i max;

    AlignedRectangleI()
        : min { Vector2i::zero() }
        , max { Vector2i::zero() }
    {
    }

    AlignedRectangleI(const Vector2i& min, const Vector2i& max)
        : min { min }
        , max { max }
    {
    }

    [[nodiscard]] Vector2i vertex_nx_ny() const
    {
        return min;
    }

    [[nodiscard]] Vector2i vertex_nx_py() const
    {
        return { min.x, max.y };
    }

    [[nodiscard]] Vector2i vertex_px_ny() const
    {
        return { max.x, min.y };
    }

    [[nodiscard]] Vector2i vertex_px_py() const
    {
        return max;
    }

    [[nodiscard]] Vector2i center_truncated() const
    {
        return (min + max) / 2;
    }

    [[nodiscard]] Vector2i size() const
    {
        return { max.x - min.x, max.y - min.y };
    }

    [[nodiscard]] AlignedRectangleI translate(const Vector2i& by) const
    {
        return { min + by, max + by };
    }

    [[nodiscard]] bool contains(const Vector2i& point) const
    {
        return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
    }
};

}

#endif