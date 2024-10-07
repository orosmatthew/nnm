/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM_HPP
#define NNM_GEOM_HPP

#include <nnm/nnm.hpp>

// ReSharper disable once CppUnusedIncludeDirective
#include <utility>

namespace nnm {

template <typename Real>
class Line2;
using Line2f = Line2<float>;
using Line2d = Line2<double>;
template <typename Real>
class Ray2;
using Ray2f = Ray2<float>;
using Ray2d = Ray2<double>;
template <typename Real>
class Segment2;
using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;
template <typename Real>
class Circle2;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;
template <typename Real>
class Triangle2;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;

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

    static Line2 from_segment(const Segment2<Real>& segment);

    static constexpr Line2 from_ray(const Ray2<Real>& ray);

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

    [[nodiscard]] constexpr Line2 arbitrary_perpendicular_containing(const Vector2<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
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

    [[nodiscard]] constexpr bool approx_tangent(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr Real project_point_scalar(const Vector2<Real>& point) const
    {
        return (point - origin).dot(direction);
    }

    [[nodiscard]] constexpr Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        return origin + direction * project_point_scalar(point);
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

    [[nodiscard]] constexpr bool separates(const Triangle2<Real>& triangle1, const Triangle2<Real>& triangle2) const;

    [[nodiscard]] Line2 translate(const Vector2<Real>& by) const
    {
        return { origin.translate(by), direction };
    }

    [[nodiscard]] Line2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Line2 scale(const Vector2<Real>& by) const
    {
        return { origin.scale(by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Line2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { origin.rotate_at(rotate_origin, angle), direction.rotate(angle).normalize() };
    }

    [[nodiscard]] Line2 rotate(const Real angle) const
    {
        return { origin.rotate(angle), direction.rotate(angle).normalize() };
    }

    [[nodiscard]] Line2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return { origin.shear_x_at(shear_origin, angle_y), direction.shear_x(angle_y).normalize() };
    }

    [[nodiscard]] Line2 shear_x(const Real angle_y) const
    {
        return { origin.shear_x(angle_y), direction.shear_x(angle_y).normalize() };
    }

    [[nodiscard]] Line2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return { origin.shear_y_at(shear_origin, angle_x), direction.shear_y(angle_x).normalize() };
    }

    [[nodiscard]] Line2 shear_y(const Real angle_x) const
    {
        return { origin.shear_y(angle_x), direction.shear_y(angle_x).normalize() };
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

    static Ray2 from_point_slope(const Vector2<Real>& point, const Real slope)
    {
        return { point, Vector2<Real> { static_cast<Real>(1), slope }.normalize() };
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

    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr Real project_point_scalar(const Vector2<Real>& point) const
    {
        const Real t = (point - origin).dot(direction);
        if (t < static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        return t;
    }

    [[nodiscard]] constexpr Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        return origin + direction * project_point_scalar(point);
    }

    [[nodiscard]] Ray2 translate(const Vector2<Real>& by) const
    {
        return { origin.translate(by), direction };
    }

    [[nodiscard]] Ray2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Ray2 scale(const Vector2<Real>& by) const
    {
        return { origin.scale(by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Ray2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { origin.rotate_at(rotate_origin, angle), direction.rotate(angle).normalize() };
    }

    [[nodiscard]] Ray2 rotate(const Real angle) const
    {
        return { origin.rotate(angle), direction.rotate(angle).normalize() };
    }

    [[nodiscard]] Ray2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return { origin.shear_x_at(shear_origin, angle_y), direction.shear_x(angle_y).normalize() };
    }

    [[nodiscard]] Ray2 shear_x(const Real angle_y) const
    {
        return { origin.shear_x(angle_y), direction.shear_x(angle_y).normalize() };
    }

    [[nodiscard]] Ray2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return { origin.shear_y_at(shear_origin, angle_x), direction.shear_y(angle_x).normalize() };
    }

    [[nodiscard]] Ray2 shear_y(const Real angle_x) const
    {
        return { origin.shear_y(angle_x), direction.shear_y(angle_x).normalize() };
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

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(from.x - to.x) + sqrd(from.y - to.y);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector2<Real> midpoint() const
    {
        return (to + from) / static_cast<Real>(2);
    }

    [[nodiscard]] Segment2 translate(const Vector2<Real>& by) const
    {
        return { from.translate(by), to.translate(by) };
    }

    [[nodiscard]] Segment2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { from.scale_at(scale_origin, by), to.scale_at(scale_origin, by) };
    }

    [[nodiscard]] Segment2 scale(const Vector2<Real>& by) const
    {
        return { from.scale(by), to.scale(by) };
    }

    [[nodiscard]] Segment2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { from.rotate_at(rotate_origin, angle), to.rotate_at(rotate_origin, angle) };
    }

    [[nodiscard]] Segment2 rotate(const Real angle) const
    {
        return { from.rotate(angle), to.rotate(angle) };
    }

    [[nodiscard]] Segment2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return { from.shear_x_at(shear_origin, angle_y), to.shear_x_at(shear_origin, angle_y) };
    }

    [[nodiscard]] Segment2 shear_x(const Real angle_y) const
    {
        return { from.shear_x(angle_y), to.shear_x(angle_y) };
    }

    [[nodiscard]] Segment2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return { from.shear_y_at(shear_origin, angle_x), to.shear_y_at(shear_origin, angle_x) };
    }

    [[nodiscard]] Segment2 shear_y(const Real angle_x) const
    {
        return { from.shear_y(angle_x), to.shear_y(angle_x) };
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

template <typename Real>
class Circle2 {
public:
    Vector2<Real> center;
    Real radius;

    constexpr Circle2()
        : center { Vector2<Real>::zero() }
        , radius { static_cast<Real>(1) }
    {
    }

    constexpr Circle2(const Vector2<Real>& center, const Real radius)
        : center { center }
        , radius { radius }
    {
    }

    [[nodiscard]] Real circumference() const
    {
        return static_cast<Real>(2) * pi<Real>() * radius;
    }

    [[nodiscard]] Real perimeter() const
    {
        return circumference();
    }

    [[nodiscard]] Real area() const
    {
        return pi<Real>() * sqrd(radius);
    }

    [[nodiscard]] Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        return (point - center).length_sqrd() <= sqrd(radius);
    }

    [[nodiscard]] Vector2<Real> point(const Real angle) const
    {
        return { center.x + radius * cos(angle), center.y + radius * sin(angle) };
    }

    [[nodiscard]] Line2<Real> tangent(const Real angle) const
    {
        const Vector2<Real> p = point(angle);
        const Vector2<Real> dir = p - center;
        return { p, dir.arbitrary_perpendicular() };
    }

    [[nodiscard]] bool intersects(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        return discriminant >= static_cast<Real>(0);
    }

    [[nodiscard]] std::optional<std::pair<Vector2<Real>, Vector2<Real>>> intersections(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-b + disc_sqrt) / static_cast<Real>(2);
        const Vector2<Real> p1 = line.origin + line.direction * t1;
        const Vector2<Real> p2 = line.origin + line.direction * t2;
        return { p1, p2 };
    }

    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-b + disc_sqrt) / static_cast<Real>(2);
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            return true;
        }
        if (t1 >= static_cast<Real>(0) || t2 >= static_cast<Real>(0)) {
            return true;
        }
        return false;
    }

    [[nodiscard]] std::pair<std::optional<Vector2<Real>>, std::optional<Vector2<Real>>> intersections(
        const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        if (discriminant < static_cast<Real>(0)) {
            return { std::nullopt, std::nullopt };
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-b + disc_sqrt) / static_cast<Real>(2);
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            const Vector2<Real> p1 = ray.origin + ray.direction * t1;
            const Vector2<Real> p2 = ray.origin + ray.direction * t2;
            return { p1, p2 };
        }
        if (t1 >= static_cast<Real>(0)) {
            const Vector2<Real> p = ray.origin + ray.direction * t1;
            return { p, std::nullopt };
        }
        if (t2 >= static_cast<Real>(0)) {
            const Vector2<Real> p = ray.origin + ray.direction * t2;
            return { p, std::nullopt };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        const Vector2<Real> seg_dir = segment.to - segment.from;
        const Vector2<Real> circle_dir = segment.from - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real c = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1) && t2 >= static_cast<Real>(0)
            && t2 <= static_cast<Real>(1)) {
            return true;
        }
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1)) {
            return true;
        }
        if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
            return true;
        }
        return false;
    }

    [[nodiscard]] std::pair<std::optional<Vector2<Real>>, std::optional<Vector2<Real>>> intersections(
        const Segment2<Real>& segment) const
    {
        const Vector2<Real> seg_dir = segment.to - segment.from;
        const Vector2<Real> circle_dir = segment.from - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real c = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (discriminant < static_cast<Real>(0)) {
            return { std::nullopt, std::nullopt };
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1) && t2 >= static_cast<Real>(0)
            && t2 <= static_cast<Real>(1)) {
            const Vector2<Real> p1 = segment.from + seg_dir * t1;
            const Vector2<Real> p2 = segment.from + seg_dir * t2;
            return { p1, p2 };
        }
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1)) {
            const Vector2<Real> p = segment.from + seg_dir * t1;
            return { p, std::nullopt };
        }
        if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
            const Vector2<Real> p = segment.from + seg_dir * t2;
            return { p, std::nullopt };
        }
        return { std::nullopt, std::nullopt };
    }

    [[nodiscard]] bool intersects(const Circle2& other) const
    {
        return center.distance_sqrd(other.center) <= sqrd(radius + other.radius);
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2& other) const
    {
        const Vector2<Real> diff = other.center - center;
        const Real dist_sqrd = diff.length_sqrd();
        const Real radius_sum = radius + other.radius;
        if (dist_sqrd >= sqrd(radius_sum)) {
            return std::nullopt;
        }
        const Real dist = sqrt(dist_sqrd);
        const Real depth = radius_sum - dist;
        return diff.normalize() * depth;
    }

    [[nodiscard]] std::optional<std::pair<Vector2<Real>, Vector2<Real>>> intersections(const Circle2& other) const
    {
        const Vector2<Real> centers_diff = other.center - center;
        const Real centers_dist = centers_diff.length();
        const Real radius_sum = radius + other.radius;
        const Real radius_diff = abs(radius - other.radius);
        if (centers_dist > radius_sum || centers_dist < radius_diff) {
            return std::nullopt;
        }
        const Real center_intersections_dist
            = (sqrd(radius) - sqrd(other.radius) + sqrd(centers_dist)) / (static_cast<Real>(2) * centers_dist);
        const Vector2<Real> intersections_midpoint = center + centers_diff * (center_intersections_dist / centers_dist);
        const Real half_intersections_dist = sqrt(sqrd(radius) - sqrd(center_intersections_dist));
        const Vector2<Real> offset = centers_diff.arbitrary_perpendicular().normalize() * half_intersections_dist;
        return std::make_pair(intersections_midpoint + offset, intersections_midpoint - offset);
    }

    [[nodiscard]] Circle2 translate(const Vector2<Real>& by) const
    {
        return { center.translate(by), radius };
    }

    [[nodiscard]] Circle2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { center.rotate_at(rotate_origin, angle), radius };
    }

    [[nodiscard]] Circle2 rotate(const Real angle) const
    {
        return { center.rotate(angle), radius };
    }

    [[nodiscard]] Circle2 scale_at(const Vector2<Real>& scale_origin, const Real by) const
    {
        return { center.scale_at(scale_origin, Vector2<Real>::all(by)), radius * by };
    }

    [[nodiscard]] Circle2 scale(const Real by) const
    {
        return { center.scale(Vector2<Real>::all(by)), radius * by };
    }

    [[nodiscard]] bool approx_equal(const Circle2& other) const
    {
        return center.approx_equal(other.center) && approx_equal(radius, other.radius);
    }

    [[nodiscard]] bool operator==(const Circle2& other) const
    {
        return center == other.center && radius == other.radius;
    }

    [[nodiscard]] bool operator!=(const Circle2& other) const
    {
        return center != other.center || radius != other.radius;
    }

    [[nodiscard]] bool operator<(const Circle2& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        return radius < other.radius;
    }
};

template <typename Real>
class Triangle2 {
public:
    union {
        struct {
            Vector2<Real> vertex0;
            Vector2<Real> vertex1;
            Vector2<Real> vertex2;
        };

        Vector2<Real> vertices[3];
    };

    constexpr Triangle2(const Vector2<Real>& vertex0, const Vector2<Real>& vertex1, const Vector2<Real>& vertex2)
        : vertex0 { vertex0 }
        , vertex1 { vertex1 }
        , vertex2 { vertex2 }
    {
    }

    [[nodiscard]] constexpr Vector2<Real> centroid() const
    {
        return (vertex0 + vertex1 + vertex2) / static_cast<Real>(3);
    }

    [[nodiscard]] constexpr Vector2<Real> circumcenter() const
    {
        const Vector2<Real> mid01 = (vertex0 + vertex1) / static_cast<Real>(2);
        const Vector2<Real> mid12 = (vertex1 + vertex2) / static_cast<Real>(2);
        const Vector2<Real> dir01 = vertex1 - vertex0;
        const Vector2<Real> dir12 = vertex2 - vertex1;
        const Vector2<Real> perp01 = dir01.arbitrary_perpendicular();
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Real t = (mid12 - mid01).cross(perp12) / perp01.cross(perp12);
        return mid01 + perp01 * t;
    }

    [[nodiscard]] Segment2<Real> edge0() const
    {
        return { vertex0, vertex1 };
    }

    [[nodiscard]] Segment2<Real> edge1() const
    {
        return { vertex1, vertex2 };
    }

    [[nodiscard]] Segment2<Real> edge2() const
    {
        return { vertex2, vertex0 };
    }

    [[nodiscard]] Real perimeter() const
    {
        return edge0().length() + edge1().length() + edge2().length();
    }

    [[nodiscard]] Vector2<Real> incenter() const
    {
        const Real len0 = edge0().length();
        const Real len1 = edge1().length();
        const Real len2 = edge2().length();
        const Real perim = len0 + len1 + len2;
        const Real x = (len0 * vertex0.x + len1 * vertex1.x + len2 * vertex2.x) / perim;
        const Real y = (len0 * vertex0.y + len1 * vertex1.y + len2 * vertex2.y) / perim;
        return { x, y };
    }

    [[nodiscard]] constexpr Vector2<Real> orthocenter() const
    {
        const Vector2<Real> dir01 = vertex1 - vertex0;
        const Vector2<Real> dir12 = vertex2 - vertex1;
        const Vector2<Real> alt12 = vertex0 - vertex1;
        const Real t = alt12.cross(dir12) / dir01.cross(dir12);
        return vertex0 + dir01 * t;
    }

    [[nodiscard]] constexpr Real area() const
    {
        const Real sum = vertex0.x * (vertex1.y - vertex2.y) + vertex1.x * (vertex2.y - vertex0.y)
            + vertex2.x * (vertex0.y - vertex1.y);
        return abs(sum) / static_cast<Real>(2);
    }

    [[nodiscard]] Segment2<Real> median0() const
    {
        return { vertex0, edge1().midpoint() };
    }

    [[nodiscard]] Segment2<Real> median1() const
    {
        return { vertex1, edge2().midpoint() };
    }

    [[nodiscard]] Segment2<Real> median2() const
    {
        return { vertex2, edge0().midpoint() };
    }

    [[nodiscard]] Line2<Real> perpendicular_bisector0() const
    {
        return { edge0().midpoint(), edge0().direction.arbitrary_perpendicular() };
    }

    [[nodiscard]] Line2<Real> perpendicular_bisector1() const
    {
        return { edge1().midpoint(), edge1().direction.arbitrary_perpendicular() };
    }

    [[nodiscard]] Line2<Real> perpendicular_bisector2() const
    {
        return { edge2().midpoint(), edge2().direction.arbitrary_perpendicular() };
    }

    [[nodiscard]] Real angle0() const
    {
        const Vector2<Real> dir01 = vertex1 - vertex0;
        const Vector2<Real> dir02 = vertex2 - vertex0;
        return acos(dir01.dot(dir02) / (dir01.length() * dir02.length()));
    }

    [[nodiscard]] Real angle1() const
    {
        const Vector2<Real> dir10 = vertex0 - vertex1;
        const Vector2<Real> dir12 = vertex2 - vertex1;
        return acos(dir10.dot(dir12) / (dir10.length() * dir12.length()));
    }

    [[nodiscard]] Real angle2() const
    {
        const Vector2<Real> dir20 = vertex0 - vertex2;
        const Vector2<Real> dir21 = vertex1 - vertex2;
        return acos(dir20.dot(dir21) / (dir20.length() * dir21.length()));
    }

    [[nodiscard]] Line2<Real> angle_bisector0() const
    {
        const Vector2<Real> dir01 = (vertex1 - vertex0).normalize();
        const Vector2<Real> dir02 = (vertex2 - vertex0).normalize();
        const Vector2<Real> bisector_dir = (dir01 + dir02).normalize();
        return { vertex0, bisector_dir };
    }

    [[nodiscard]] Line2<Real> angle_bisector1() const
    {
        const Vector2<Real> dir10 = (vertex0 - vertex1).normalize();
        const Vector2<Real> dir12 = (vertex2 - vertex1).normalize();
        const Vector2<Real> bisector_dir = (dir10 + dir12).normalize();
        return { vertex1, bisector_dir };
    }

    [[nodiscard]] Line2<Real> angle_bisector2() const
    {
        const Vector2<Real> dir20 = (vertex0 - vertex2).normalize();
        const Vector2<Real> dir21 = (vertex1 - vertex2).normalize();
        const Vector2<Real> bisector_dir = (dir20 + dir21).normalize();
        return { vertex2, bisector_dir };
    }

    [[nodiscard]] Line2<Real> altitude0() const
    {
        const Vector2<Real> dir12 = vertex2 - vertex1;
        return { vertex0, dir12.arbitrary_perpendicular().normalize() };
    }

    [[nodiscard]] Line2<Real> altitude1() const
    {
        const Vector2<Real> dir20 = vertex0 - vertex2;
        return { vertex1, dir20.arbitrary_perpendicular().normalize() };
    }

    [[nodiscard]] Line2<Real> altitude2() const
    {
        const Vector2<Real> dir01 = vertex1 - vertex0;
        return { vertex2, dir01.arbitrary_perpendicular().normalize() };
    }

    [[nodiscard]] Triangle2 project(const Line2<Real>& line) const
    {
        return { line.project_point(vertex0), line.project_point(vertex1), line.project_point(vertex2) };
    }

    [[nodiscard]] constexpr Vector3<Real> project_scalars(const Line2<Real>& line) const
    {
        return { line.project_point_scalar(vertex0),
                 line.project_point_scalar(vertex1),
                 line.project_point_scalar(vertex2) };
    }

    [[nodiscard]] bool overlaps(const Triangle2& other) const
    {
        auto has_separating_line = [](const Triangle2& triangle1, const Triangle2& triangle2) -> bool {
            return Line2<Real>::from_segment(triangle1.edge0()).separates(triangle1, triangle2)
                || Line2<Real>::from_segment(triangle1.edge1()).separates(triangle1, triangle2)
                || Line2<Real>::from_segment(triangle1.edge2()).separates(triangle1, triangle2);
        };
        return !has_separating_line(*this, other) && !has_separating_line(other, *this);
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
Line2<Real> Line2<Real>::from_segment(const Segment2<Real>& segment)
{
    return { segment.from, (segment.to - segment.from).normalize() };
}

template <typename Real>
constexpr Line2<Real> Line2<Real>::from_ray(const Ray2<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
constexpr bool Line2<Real>::approx_tangent(const Circle2<Real>& circle) const
{
    const Vector2<Real> dir = origin - circle.center;
    const Real b = static_cast<Real>(2) * dir.dot(direction);
    const Real c = dir.dot(dir) - sqrd(circle.radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
    return approx_zero(discriminant);
}

template <typename Real>
constexpr bool Line2<Real>::separates(const Triangle2<Real>& triangle1, const Triangle2<Real>& triangle2) const
{
    const Vector3<Real> proj1 = triangle1.project_scalars(*this);
    const Vector3<Real> proj2 = triangle2.project_scalars(*this);
    return proj1.max() < proj2.min() || proj2.max() < proj1.min();
}

template <typename Real>
constexpr bool Ray2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector2<Real>> Ray2<Real>::intersection(const Segment2<Real>& segment) const
{
    return segment.intersection(*this);
}
}

#endif