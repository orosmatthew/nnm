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
template <typename Real = float>
class Ray2;
using Ray2f = Ray2<>;
using Ray2d = Ray2<double>;
template <typename Real = float>
class Segment2;
using Segment2f = Segment2<>;
using Segment2d = Segment2<double>;

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

    static constexpr Line2 axis_x()
    {
        return { Vector2<Real>::zero(), Vector2<Real>::axis_x() };
    }

    static constexpr Line2 axis_y()
    {
        return { Vector2<Real>::zero(), Vector2<Real>::axis_y() };
    }

    static constexpr Line2 axis_x_offset(const Real y)
    {
        return { { static_cast<Real>(0), y }, Vector2<Real>::axis_x() };
    }

    static constexpr Line2 axis_y_offset(const Real x)
    {
        return { { x, static_cast<Real>(0) }, Vector2<Real>::axis_y() };
    }

    static Line2 from_point_slope(const Vector2<Real>& point, const Real slope)
    {
        return { point, nnm::Vector2<Real> { 1.0f, slope }.normalize() };
    }

    [[nodiscard]] constexpr Line2 parallel_containing(const Vector2<Real>& point) const
    {
        return { point, direction };
    }

    [[nodiscard]] constexpr Line2 perpendicular_containing(const Vector2<Real>& point) const
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
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction) / dir_cross;
        return origin + direction * t;
    }

    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr Vector2<Real> project_point(const Vector2<Real>& point) const
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

    [[nodiscard]] constexpr bool approx_coincident(const Line2& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = origin - other.origin;
        return approx_zero(diff.cross(other.direction));
    }

    [[nodiscard]] Line2 transform_at(const Vector2<Real>& basis_origin, const Basis2<Real>& by) const
    {
        return { (origin - basis_origin).transform(by) + basis_origin, direction.transform(by).normalize() };
    }

    [[nodiscard]] Line2 transform(const Basis2<Real>& by) const
    {
        return transform_at(Vector2<Real>::zero(), by);
    }

    [[nodiscard]] Line2 transform_at(const Vector2<Real>& transform_origin, const Transform2<Real>& by) const
    {
        return { (origin - transform_origin).transform(by) + transform_origin,
                 direction.transform(by, static_cast<Real>(0)).normalize() };
    }

    [[nodiscard]] Line2 transform(const Transform2<Real>& by) const
    {
        return transform_at(Vector2<Real>::zero(), by);
    }

    [[nodiscard]] Line2 translate(const Vector2<Real>& by) const
    {
        return transform(Transform2<Real>::from_translation(by));
    }

    [[nodiscard]] Line2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return transform_at(scale_origin, Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Line2 scale(const Vector2<Real>& by) const
    {
        return transform(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Line2 rotate(const Real angle) const
    {
        return transform(Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Line2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Line2 shear_x(const Real angle_y) const
    {
        return transform(Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Line2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] Line2 shear_y(const Real angle_x) const
    {
        return transform(Basis2<Real>::from_shear_y(angle_x));
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
        if (origin != other.origin) {
            return origin < other.origin;
        }
        return direction < other.direction;
    }
};

template <typename Real>
class Ray2 {
public:
    Vector2<Real> origin;
    Vector2<Real> direction;

    constexpr Ray2()
        : origin { Vector2<Real>::zero() }
        , direction { static_cast<Real>(1), static_cast<Real>(0) }
    {
    }

    constexpr Ray2(const Vector2<Real>& origin, const Vector2<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    static Ray2 from_point_to_point(const Vector2<Real>& point1, const Vector2<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    [[nodiscard]] Ray2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> t = diff / direction;
        return approx_equal(t.x, t.y);
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return diff.length();
        }
        return abs(direction.cross(diff));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Ray2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Ray2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        const Real dir_cross = direction.cross(line.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = line.origin - origin;
        const Real t_ray = diff.cross(line.direction) / dir_cross;
        return t_ray >= static_cast<Real>(0);
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2<Real>& line) const
    {
        const Real dir_cross = direction.cross(line.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = line.origin - origin;
        const Real t_ray = diff.cross(line.direction) / dir_cross;
        if (t_ray >= static_cast<Real>(0)) {
            return origin + direction * t_ray;
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr bool intersects(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (approx_zero(dir_cross)) {
            return false;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t1 = diff.cross(other.direction) / dir_cross;
        const Real t2 = diff.cross(direction) / dir_cross;
        return t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0);
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t1 = diff.cross(other.direction) / dir_cross;
        const Real t2 = diff.cross(direction) / dir_cross;
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            return origin + direction * t1;
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const;

    [[nodiscard]] std::optional<Vector2<Real>> intersection(const Segment2<Real>& segment) const;

    [[nodiscard]] Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        Real t = diff.dot(direction);
        if (t < static_cast<Real>(0)) {
            return origin;
        }
        return origin + direction * t;
    }

    [[nodiscard]] Ray2 transform_at(const Vector2<Real>& transform_origin, const Basis2<Real>& by) const
    {
        return { (origin - transform_origin).transform(by) + transform_origin, direction.transform(by).normalize() };
    }

    [[nodiscard]] Ray2 transform(const Basis2<Real>& by) const
    {
        return transform_at(Vector2<Real>::zero(), by);
    }

    [[nodiscard]] Ray2 transform_at(const Vector2<Real>& transform_origin, const Transform2<Real>& by) const
    {
        return { (origin - transform_origin).transform(by) + transform_origin,
                 direction.transform(by, 0.0f).normalize() };
    }

    [[nodiscard]] Ray2 transform(const Transform2<Real>& by) const
    {
        return { origin.transform(by), direction.transform(by, static_cast<Real>(0)).normalize() };
    }

    [[nodiscard]] Ray2 translate(const Vector2<Real>& by) const
    {
        return transform(Transform2<Real>::from_translation(by));
    }

    [[nodiscard]] Ray2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return transform_at(scale_origin, Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Ray2 scale(const Vector2<Real>& by) const
    {
        return transform(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Ray2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return transform_at(rotate_origin, Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Ray2 rotate(const Real angle) const
    {
        return transform(Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Ray2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Ray2 shear_x(const Real angle_y) const
    {
        return transform(Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Ray2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] Ray2 shear_y(const Real angle_x) const
    {
        return transform(Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] bool operator==(const Ray2& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    [[nodiscard]] bool operator!=(const Ray2& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    [[nodiscard]] bool operator<(const Ray2& other) const
    {
        if (origin != other.origin) {
            return origin < other.origin;
        }
        return direction < other.direction;
    }
};

template <typename Real>
class Segment2 {
public:
    Vector2<Real> from;
    Vector2<Real> to;

    constexpr Segment2()
        : from { Vector2<Real>::zero() }
        , to { Vector2<Real>::zero() }
    {
    }

    constexpr Segment2(const Vector2<Real>& from, const Vector2<Real>& to)
        : from { from }
        , to { to }
    {
    }

    [[nodiscard]] constexpr bool approx_collinear(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff1 = point - from;
        const Vector2<Real> diff2 = to - from;
        return approx_zero(diff1.cross(diff2));
    }

    [[nodiscard]] constexpr bool approx_collinear(const Line2<Real>& line) const
    {
        if (!approx_parallel(line)) {
            return false;
        }
        const Vector2<Real> diff = from - line.origin;
        return approx_zero(diff.cross(line.direction));
    }

    [[nodiscard]] constexpr bool approx_collinear(const Ray2<Real>& ray) const
    {
        if (!approx_parallel(ray)) {
            return false;
        }
        const Vector2<Real> diff = from - ray.origin;
        return approx_zero(diff.cross(ray.direction));
    }

    [[nodiscard]] constexpr bool approx_collinear(const Segment2& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = from - other.from;
        return approx_zero(diff.cross(other.to - other.from));
    }

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff1 = point - from;
        const Vector2<Real> diff2 = to - from;
        if (!approx_zero(diff1.cross(diff2))) {
            return false;
        }
        const Real dot = diff1.dot(diff2);
        const Real length_sqrd = diff2.dot(diff2);
        return dot >= static_cast<Real>(0) && dot <= length_sqrd;
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = to - from;
        const Vector2<Real> diff = point - from;
        Real t = diff.dot(dir) / dir.dot(dir);
        if (t < static_cast<Real>(0)) {
            return diff.length();
        }
        if (t > static_cast<Real>(1)) {
            return (point - to).length();
        }
        Vector2<Real> proj = from + dir * t;
        return (point - proj).length();
    }

    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = to - from;
        const Vector2<Real> diff = point - from;
        Real t = diff.dot(dir) / dir.dot(dir);
        Vector2<Real> closest;
        if (t < static_cast<Real>(0)) {
            closest = from;
        }
        else if (t > static_cast<Real>(1)) {
            closest = to;
        }
        else {
            closest = from + dir * t;
        }
        const Real dist = (point - closest).length();
        const Real sign = dir.cross(point - from) < static_cast<Real>(0) ? static_cast<Real>(-1) : static_cast<Real>(1);
        return sign * dist;
    }

    [[nodiscard]] Vector2<Real> direction() const
    {
        return (to - from).normalize();
    }

    [[nodiscard]] constexpr bool approx_parallel(const Line2<Real>& line) const
    {
        return approx_zero((to - from).cross(line.direction));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Ray2<Real>& ray) const
    {
        return approx_zero((to - from).cross(ray.direction));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Segment2& other) const
    {
        return approx_zero((to - from).cross(other.to - other.from));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Line2<Real>& line) const
    {
        return approx_zero((to - from).dot(line.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Ray2<Real>& ray) const
    {
        return approx_zero((to - from).dot(ray.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Segment2& other) const
    {
        return approx_zero((to - from).dot(other.to - other.from));
    }

    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = to - from;
        const Real dir_cross = dir.cross(line.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = line.origin - from;
        const Real t = diff.cross(line.direction) / dir_cross;
        return t >= static_cast<Real>(0) && t <= static_cast<Real>(1);
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = to - from;
        const Real dir_cross = dir.cross(line.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = line.origin - from;
        const Real t = diff.cross(line.direction) / dir_cross;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return std::nullopt;
        }
        return from + dir * t;
    }

    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = to - from;
        const Real dir_cross = dir.cross(ray.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = ray.origin - from;
        const Real t = diff.cross(ray.direction) / dir_cross;
        const Real t_ray = diff.cross(dir) / dir_cross;
        return t >= static_cast<Real>(0) && t <= static_cast<Real>(1) && t_ray >= static_cast<Real>(0);
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = to - from;
        const Real dir_cross = dir.cross(ray.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = ray.origin - from;
        const Real t = diff.cross(ray.direction) / dir_cross;
        const Real t_ray = diff.cross(dir) / dir_cross;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1) || t_ray < static_cast<Real>(0)) {
            return std::nullopt;
        }
        return from + dir * t;
    }

    [[nodiscard]] constexpr bool intersects(const Segment2& other) const
    {
        const Vector2<Real> dir = to - from;
        const Vector2<Real> dir_other = other.to - other.from;
        const Real dir_cross = dir.cross(dir_other);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = other.from - from;
        const Real t = diff.cross(dir_other) / dir_cross;
        const Real t_other = diff.cross(dir) / dir_cross;
        return t >= static_cast<Real>(0) && t <= static_cast<Real>(1) && t_other >= static_cast<Real>(0)
            && t_other <= static_cast<Real>(1);
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2& other) const
    {
        const Vector2<Real> dir = to - from;
        const Vector2<Real> dir_other = other.to - other.from;
        const Real dir_cross = dir.cross(dir_other);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.from - from;
        const Real t = diff.cross(dir_other) / dir_cross;
        const Real t_other = diff.cross(dir) / dir_cross;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1) || t_other < static_cast<Real>(0)
            || t_other > static_cast<Real>(1)) {
            return std::nullopt;
        }
        return from + dir * t;
    }

    [[nodiscard]] constexpr Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = to - from;
        const Real length_sqrd = dir.dot(dir);
        if (length_sqrd == static_cast<Real>(0)) {
            return from;
        }
        const Real t = (point - from).dot(dir) / length_sqrd;
        if (t < static_cast<Real>(0)) {
            return from;
        }
        if (t > static_cast<Real>(1)) {
            return to;
        }
        return from + dir * t;
    }

    [[nodiscard]] constexpr Real unchecked_slope() const
    {
        return (to.y - from.y) / (to.x - from.x);
    }

    [[nodiscard]] constexpr std::optional<Real> slope() const
    {
        const Real denom = to.x - from.x;
        if (denom == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return (to.y - from.y) / denom;
    }

    [[nodiscard]] Segment2 transform_at(const Vector2<Real>& basis_origin, const Basis2<Real>& by) const
    {
        return { (from - basis_origin).transform(by) + basis_origin, (to - basis_origin).transform(by) + basis_origin };
    }

    [[nodiscard]] Segment2 transform(const Basis2<Real>& by) const
    {
        return transform_at(Vector2<Real>::zero(), by);
    }

    [[nodiscard]] Segment2 transform_at(const Vector2<Real>& transform_origin, const Transform2<Real>& by) const
    {
        return { (from - transform_origin).transform(by) + transform_origin,
                 (to - transform_origin).transform(by) + transform_origin };
    }

    [[nodiscard]] Segment2 transform(const Transform2<Real>& by) const
    {
        return transform_at(Vector2<Real>::zero(), by);
    }

    [[nodiscard]] Segment2 translate(const Vector2<Real>& by) const
    {
        return transform(Transform2<Real>::from_translation(by));
    }

    [[nodiscard]] Segment2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return transform_at(scale_origin, Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Segment2 scale(const Vector2<Real>& by) const
    {
        return transform(Basis2<Real>::from_scale(by));
    }

    [[nodiscard]] Segment2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return transform_at(rotate_origin, Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Segment2 rotate(const Real angle) const
    {
        return transform(Basis2<Real>::from_rotation(angle));
    }

    [[nodiscard]] Segment2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Segment2 shear_x(const Real angle_y) const
    {
        return transform(Basis2<Real>::from_shear_x(angle_y));
    }

    [[nodiscard]] Segment2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return transform_at(shear_origin, Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] Segment2 shear_y(const Real angle_x) const
    {
        return transform(Basis2<Real>::from_shear_y(angle_x));
    }

    [[nodiscard]] constexpr bool operator==(const Segment2& other) const
    {
        return from == other.from && to == other.to;
    }

    [[nodiscard]] constexpr bool operator!=(const Segment2& other) const
    {
        return from != other.from || to != other.to;
    }

    [[nodiscard]] constexpr bool operator<(const Segment2& other) const
    {
        if (from != other.from) {
            return from < other.from;
        }
        return to < other.to;
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

template <typename Real>
constexpr bool Line2<Real>::intersects(const Ray2<Real>& ray) const
{
    return ray.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector2<Real>> Line2<Real>::intersection(const Ray2<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector2<Real>> Line2<Real>::intersection(const Segment2<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Ray2<Real>::intersection(const Segment2<Real>& segment) const
{
    return segment.intersection(*this);
}

}

#endif