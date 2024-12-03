/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM_HPP
#define NNM_GEOM_HPP

// ReSharper disable CppDFATimeOver

#include <nnm/nnm.hpp>

#include <array>
#include <optional>

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
class Arc2;
using Arc2f = Arc2<float>;
using Arc2d = Arc2<double>;
template <typename Real>
class Circle2;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;
template <typename Real>
class Triangle2;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;
template <typename Real>
class Rectangle2;
using Rectangle2f = Rectangle2<float>;
using Rectangle2d = Rectangle2<double>;

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

    static std::optional<Line2> from_tangent(const Arc2<Real>& arc, const Real angle)
    {
        const std::optional<Vector2<Real>> p = arc.point_at(angle);
        if (!p.has_value()) {
            return std::nullopt;
        }
        const Vector2<Real> dir = p.value() - arc.pivot;
        return Line2 { p.value(), dir.arbitrary_perpendicular() };
    }

    static Line2 from_tangent(const Circle2<Real>& circle, const Real angle)
    {
        const Vector2<Real> p = circle.point_at(angle);
        const Vector2<Real> dir = p - circle.center;
        return { p, dir.arbitrary_perpendicular() };
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

    [[nodiscard]] constexpr Line2 arbitrary_perpendicular_containing(const Vector2<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
    }

    [[nodiscard]] Line2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] constexpr bool approx_collinear(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr bool approx_collinear(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> t = (point - origin) / direction;
        return approx_equal(t.x, t.y);
    }

    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
    {
        return direction.cross(point - origin);
    }

    [[nodiscard]] constexpr Real distance(const Vector2<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    [[nodiscard]] constexpr Real distance(const Line2& other) const
    {
        if (direction.cross(other.direction) == static_cast<Real>(0)) {
            return abs((other.origin - origin).cross(direction));
        }
        return static_cast<Real>(0);
    }

    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr Real distance(const Segment2<Real>& segment) const;

    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr bool approx_parallel(const Line2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr bool approx_parallel(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr bool approx_perpendicular(const Line2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Ray2<Real>& ray) const;

    [[nodiscard]] constexpr bool approx_perpendicular(const Segment2<Real>& segment) const;

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

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Arc2<Real>& arc) const;

    [[nodiscard]] constexpr bool intersects(const Circle2<Real>& circle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Triangle2<Real>& triangle) const;

    [[nodiscard]] bool approx_tangent(const Arc2<Real>& arc) const;

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

    [[nodiscard]] constexpr bool approx_coincident(const Line2& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = origin - other.origin;
        return approx_zero(diff.cross(other.direction));
    }

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

    static Ray2 from_point_to_point(const Vector2<Real>& from, const Vector2<Real>& to)
    {
        return { from, from.direction(to) };
    }

    [[nodiscard]] Ray2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] constexpr bool approx_collinear(const Vector2<Real>& point) const
    {
        return Line2<Real>::from_ray(*this).approx_contains(point);
    }

    [[nodiscard]] constexpr bool approx_collinear(const Line2<Real>& line) const
    {
        return Line2<Real>::from_ray(*this).approx_coincident(line);
    }

    [[nodiscard]] constexpr bool approx_collinear(const Ray2& other) const
    {
        return Line2<Real>::from_ray(*this).approx_coincident(Line2<Real>::from_ray(other));
    }

    [[nodiscard]] constexpr bool approx_collinear(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> t = diff / direction;
        return approx_equal(t.x, t.y);
    }

    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return diff.length();
        }
        return direction.cross(diff);
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        return line.distance(origin);
    }

    [[nodiscard]] Real distance(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            if (direction.dot(other.direction) > static_cast<Real>(0)) {
                return abs((other.origin - origin).cross(direction));
            }
            return origin.distance(other.origin);
        }
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Real d1 = distance(other.origin);
        const Real d2 = other.distance(origin);
        return min(d1, d2);
    }

    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr bool approx_parallel(const Line2<Real>& line) const
    {
        return approx_zero(direction.cross(line.direction));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Ray2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    [[nodiscard]] constexpr bool approx_parallel(const Segment2<Real>& segment) const;

    [[nodiscard]] constexpr bool approx_perpendicular(const Line2<Real>& line) const
    {
        return approx_zero(direction.dot(line.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Ray2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] constexpr bool approx_perpendicular(const Segment2<Real>& segment) const;

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

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Arc2<Real>& arc) const;

    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Triangle2<Real>& triangle) const;

    [[nodiscard]] bool approx_tangent(const Arc2<Real>& arc) const;

    [[nodiscard]] constexpr bool approx_tangent(const Circle2<Real>& circle) const;

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
        return sign(dir.cross(point - from)) * dist;
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

    [[nodiscard]] constexpr Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        const Real d1 = line.distance(from);
        const Real d2 = line.distance(to);
        return min(d1, d2);
    }

    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        const Real d1 = ray.distance(from);
        const Real d2 = ray.distance(to);
        const Real d3 = distance(ray.origin);
        return min(d1, min(d2, d3));
    }

    [[nodiscard]] Real distance(const Segment2& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Real d1 = distance(other.from);
        const Real d2 = distance(other.to);
        const Real d3 = other.distance(from);
        const Real d4 = other.distance(to);
        return min(d1, min(d2, min(d3, d4)));
    }

    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr Vector2<Real> direction_unnormalized() const
    {
        return to - from;
    }

    [[nodiscard]] Vector2<Real> direction() const
    {
        return direction_unnormalized().normalize();
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

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Arc2<Real>& arc) const;

    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Circle2<Real>& circle) const;

    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Triangle2<Real>& triangle) const;

    [[nodiscard]] bool approx_tangent(const Arc2<Real>& arc) const;

    [[nodiscard]] constexpr bool approx_tangent(const Circle2<Real>& circle) const;

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
        return sqrd(to.x - from.x) + sqrd(to.y - from.y);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] constexpr Vector2<Real> midpoint() const
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

    [[nodiscard]] constexpr bool approx_coincident(const Segment2& other) const
    {
        return (from.approx_equal(other.from) && to.approx_equal(other.to))
            || (from.approx_equal(other.to) && to.approx_equal(other.from));
    }

    [[nodiscard]] constexpr bool approx_equal(const Segment2& other) const
    {
        return from.approx_equal(other.from) && to.approx_equal(other.to);
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
class Arc2 {
public:
    Vector2<Real> pivot;
    Vector2<Real> from;
    Real angle;

    constexpr Arc2()
        : pivot { Vector2<Real>::zero() }
        , from { Vector2<Real>::zero() }
        , angle { static_cast<Real>(0) }
    {
    }

    constexpr Arc2(const Vector2<Real>& pivot, const Vector2<Real>& from, const Real angle)
        : pivot { pivot }
        , from { from }
        , angle { angle }
    {
    }

    static Arc2 from_pivot_radius_angle_to_angle(
        const Vector2<Real>& pivot, const Real radius, const Real angle_from, const Real angle_to)
    {
        const Vector2<Real> from { pivot.x + radius * cos(angle_from), pivot.y + radius * sin(angle_from) };
        const Real angle = angle_to - angle_from;
        return { pivot, from, angle };
    }

    static Arc2 from_points_unchecked(const Vector2<Real>& from, const Vector2<Real>& through, const Vector2<Real>& to)
    {
        const Vector2<Real> mid1 = nnm::Segment2<Real> { from, through }.midpoint();
        const Vector2<Real> mid2 = nnm::Segment2<Real> { through, to }.midpoint();
        const Vector2<Real> dir1 = through - from;
        const Vector2<Real> dir2 = to - through;
        const Vector2<Real> perp1 = dir1.arbitrary_perpendicular();
        const Vector2<Real> perp2 = dir2.arbitrary_perpendicular();
        const Line2<Real> l1 { mid1, perp1 };
        const Line2<Real> l2 { mid2, perp2 };
        const Vector2<Real> pivot = l1.unchecked_intersection(l2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real angle_from = remainder(pivot.angle_to(from) + pi<Real>(), two_pi);
        const Real angle_to = remainder(pivot.angle_to(to) + pi<Real>(), two_pi);
        const Real angle_through = remainder(pivot.angle_to(through) + pi<Real>(), two_pi);
        const Real angle_diff = abs(nnm::normalize_angle(angle_to - angle_from));
        const bool in_range = angle_in_range(angle_through, angle_from, angle_to);
        const Real angle = in_range ? angle_to - angle_from
            : angle_to < angle_from ? two_pi - angle_diff
                                    : -two_pi + angle_diff;
        return Arc2 { pivot, from, angle };
    }

    static std::optional<Arc2> from_points(
        const Vector2<Real>& from, const Vector2<Real>& through, const Vector2<Real>& to)
    {
        const Vector2<Real> mid1 = nnm::Segment2<Real> { from, through }.midpoint();
        const Vector2<Real> mid2 = nnm::Segment2<Real> { through, to }.midpoint();
        const Vector2<Real> dir1 = through - from;
        const Vector2<Real> dir2 = to - through;
        const Vector2<Real> perp1 = dir1.arbitrary_perpendicular();
        const Vector2<Real> perp2 = dir2.arbitrary_perpendicular();
        const Line2<Real> l1 { mid1, perp1 };
        const Line2<Real> l2 { mid2, perp2 };
        const std::optional<Vector2<Real>> pivot = l1.intersection(l2);
        if (!pivot.has_value()) {
            return std::nullopt;
        }
        const Real angle_from = pivot->angle_to(from);
        const Real angle_to = pivot->angle_to(to);
        const Real angle_through = pivot->angle_to(through);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real angle_diff = abs(nnm::normalize_angle(angle_to - angle_from));
        const bool in_range = angle_in_range(angle_through, angle_from, angle_to);
        const Real angle = in_range ? angle_to - angle_from
            : angle_to < angle_from ? two_pi - angle_diff
                                    : -two_pi + angle_diff;
        return Arc2 { pivot.value(), from, angle };
    }

    [[nodiscard]] constexpr Arc2 normalize_angle() const
    {
        return { pivot, from, nnm::normalize_angle(angle) };
    }

    [[nodiscard]] Real radius() const
    {
        return pivot.distance(from);
    }

    [[nodiscard]] constexpr Real radius_sqrd() const
    {
        return pivot.distance_sqrd(from);
    }

    [[nodiscard]] Real angle_from() const
    {
        return nnm::normalize_angle(pivot.angle_to(from));
    }

    [[nodiscard]] Real angle_to() const
    {
        return angle_from() + angle;
    }

    [[nodiscard]] bool approx_contains(const Vector2<Real>& point) const
    {
        if (!nnm::approx_equal(point.distance_sqrd(pivot), sqrd(radius()))) {
            return false;
        }
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real point_angle = remainder(pivot.angle_to(point), two_pi);
        return angle_in_range(point_angle, angle_from(), angle_to());
    }

    [[nodiscard]] Vector2<Real> unchecked_point_at(const Real angle) const
    {
        const Real r = radius();
        return { pivot.x + cos(angle) * r, pivot.y + sin(angle) * r };
    }

    [[nodiscard]] std::optional<Vector2<Real>> point_at(const Real angle) const
    {
        const Real r = radius();
        if (!angle_in_range(angle, angle_from(), angle_to())) {
            return std::nullopt;
        }
        return Vector2<Real> { pivot.x + cos(angle) * r, pivot.y + sin(angle) * r };
    }

    [[nodiscard]] Vector2<Real> to() const
    {
        return unchecked_point_at(angle_to());
    }

    [[nodiscard]] Real length() const
    {
        return abs(radius() * angle);
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return radius_sqrd() * sqrd(angle);
    }

    [[nodiscard]] Vector2<Real> midpoint() const
    {
        return Arc2 { pivot, from, angle / static_cast<Real>(2) }.to();
    }

    [[nodiscard]] Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = pivot.direction(point);
        const Vector2<Real> proj = pivot + dir * radius();
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(proj) + two_pi, two_pi);
            angle_in_range(proj_angle, angle_from(), angle_to())) {
            return proj;
        }
        if (const Vector2<Real> to_ = to(); point.distance_sqrd(from) >= point.distance_sqrd(to_)) {
            return to_;
        }
        return from;
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        if (point == pivot) {
            return radius();
        }
        const Vector2<Real> dir = pivot.direction(point);
        const Vector2<Real> proj = pivot + dir * radius();
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(proj) + two_pi, two_pi);
            angle_in_range(proj_angle, angle_from(), angle_to())) {
            return point.distance(proj);
        }
        const Real from_dist = point.distance(from);
        const Real to_dist = point.distance(to());
        return min(from_dist, to_dist);
    }

    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        const Real dist = distance(point);
        const Vector2<Real> from_point = point - from;
        const Vector2<Real> from_to = to() - from;
        const Real cross = from_to.cross(from_point);
        if (angle < static_cast<Real>(0)) {
            return cross > static_cast<Real>(0) ? dist : -dist;
        }
        return cross <= static_cast<Real>(0) ? dist : -dist;
    }

    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        Real to_from_min_dist = min(line.distance(from), line.distance(to()));
        const Real proj_scalar = (pivot - line.origin).dot(line.direction);
        const Vector2<Real> closest_point_on_line = line.origin + line.direction * proj_scalar;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_line), two_pi);
            angle_in_range(proj_angle, angle_from(), angle_to())) {
            return min(abs(pivot.distance(closest_point_on_line) - radius()), to_from_min_dist);
        }
        return to_from_min_dist;
    }

    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        const Real to_from_origin_min_dist = min(distance(ray.origin), min(ray.distance(from), ray.distance(to())));
        const Real proj_scalar = (pivot - ray.origin).dot(ray.direction);
        if (proj_scalar >= static_cast<Real>(0)) {
            const Vector2<Real> closest_point_on_ray = ray.origin + ray.direction * proj_scalar;
            const Real two_pi = static_cast<Real>(2) * pi<Real>();
            if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_ray), two_pi);
                angle_in_range(proj_angle, angle_from(), angle_to())) {
                return min(abs(pivot.distance(closest_point_on_ray) - radius()), to_from_origin_min_dist);
            }
        }
        return to_from_origin_min_dist;
    }

    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        if (intersects(segment)) {
            return static_cast<Real>(0);
        }
        const Real ends_min_dist = min(
            distance(segment.from), min(distance(segment.to), min(segment.distance(from), segment.distance(to()))));
        const Vector2<Real> seg_dir = segment.direction();
        const Real proj_scalar = (pivot - segment.from).dot(seg_dir);
        if (proj_scalar >= static_cast<Real>(0) && proj_scalar <= static_cast<Real>(1)) {
            const Vector2<Real> closest_point_on_seg = segment.from + seg_dir * proj_scalar;
            const Real two_pi = static_cast<Real>(2) * pi<Real>();
            if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_seg), two_pi);
                angle_in_range(proj_angle, angle_from(), angle_to())) {
                return min(abs(pivot.distance(closest_point_on_seg) - radius()), ends_min_dist);
            }
        }
        return ends_min_dist;
    }

    [[nodiscard]] Real distance(const Arc2& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Vector2<Real> dir = pivot.direction(other.pivot);
        const Real angle1 = Vector2<Real>::axis_x().angle_between(dir);
        const Real angle2 = Vector2<Real>::axis_x().angle_between(-dir);
        std::optional<Vector2<Real>> p1 = point_at(angle1);
        if (!p1.has_value()) {
            p1 = point_at(angle2);
        }
        std::optional<Vector2<Real>> p2 = other.point_at(angle1);
        if (!p2.has_value()) {
            p2 = other.point_at(angle2);
        }
        Real min_dist
            = p1.has_value() && p2.has_value() ? min(p1->distance(*p2), other.distance(from)) : other.distance(from);
        min_dist = min(min_dist, other.distance(to()));
        min_dist = min(min_dist, distance(other.from));
        min_dist = min(min_dist, distance(other.to()));
        return min_dist;
    }

    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    [[nodiscard]] bool intersects(const Line2<Real>& line) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = line.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(line.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Vector2<Real> intersection1 = line.origin + line.direction * t1;
        const Vector2<Real> intersection2 = line.origin + line.direction * t2;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const Real intersection1_angle = remainder(pivot.angle_to(intersection1), two_pi);
        const Real intersection2_angle = remainder(pivot.angle_to(intersection2), two_pi);
        return angle_in_range(intersection1_angle, from_angle_, to_angle_)
            || angle_in_range(intersection2_angle, from_angle_, to_angle_);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Line2<Real>& line) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = line.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(line.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Vector2<Real> intersection1 = line.origin + line.direction * t1;
        const Vector2<Real> intersection2 = line.origin + line.direction * t2;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const Real intersection1_angle = remainder(pivot.angle_to(intersection1), two_pi);
        const Real intersection2_angle = remainder(pivot.angle_to(intersection2), two_pi);
        const bool in_arc1 = angle_in_range(intersection1_angle, from_angle_, to_angle_);
        const bool in_arc2 = angle_in_range(intersection2_angle, from_angle_, to_angle_);
        if (in_arc1 && in_arc2) {
            return intersection2 < intersection1
                ? std::array { intersection2, intersection1 }
                : std::array { intersection1, intersection2 };
        }
        if (in_arc1) {
            return std::array { intersection1, intersection1 };
        }
        if (in_arc2) {
            return std::array { intersection2, intersection2 };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = ray.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(ray.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const auto in_arc = [&](const Real t) -> bool {
            const Vector2<Real> intersection = ray.origin + ray.direction * t;
            const Real intersection_angle = mod(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const bool in_arc1 = t1 >= static_cast<Real>(0) ? in_arc(t1) : false;
        const bool in_arc2 = t2 >= static_cast<Real>(0) ? in_arc(t2) : false;
        return in_arc1 || in_arc2;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Ray2<Real>& ray) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = ray.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(ray.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const auto intersection = [&](const Real t) -> std::optional<Vector2<Real>> {
            const Vector2<Real> point = ray.origin + ray.direction * t;
            if (const Real intersection_angle = mod(pivot.angle_to(point) + two_pi, two_pi);
                angle_in_range(intersection_angle, from_angle_, to_angle_)) {
                return point;
            }
            return std::nullopt;
        };
        const std::optional<Vector2<Real>> point1 = t1 > static_cast<Real>(0) ? intersection(t1) : std::nullopt;
        const std::optional<Vector2<Real>> point2 = t2 > static_cast<Real>(0) ? intersection(t2) : std::nullopt;
        if (point1.has_value() && point2.has_value()) {
            return point2.value() < point1.value()
                ? std::array { point2.value(), point1.value() }
                : std::array { point1.value(), point2.value() };
        }
        if (point1.has_value()) {
            return std::array { point1.value(), point1.value() };
        }
        if (point2.has_value()) {
            return std::array { point2.value(), point2.value() };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_seg_from_dir = segment.from - pivot;
        const Vector2<Real> seg_dir = segment.direction_unnormalized();
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_seg_from_dir.dot(seg_dir);
        const Real dot_minus_r_sqrd = pivot_seg_from_dir.dot(pivot_seg_from_dir) - sqrd(r);
        const Real seg_len_sqrd = segment.length_sqrd();
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * seg_len_sqrd * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const auto in_arc = [&](const Vector2<Real>& intersection) -> bool {
            const Real intersection_angle = mod(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const auto in_segment
            = [&](const Real t) -> bool { return t >= static_cast<Real>(0) && t <= static_cast<Real>(1); };
        const Vector2<Real> intersection1 = segment.from + seg_dir * t1;
        const Vector2<Real> intersection2 = segment.from + seg_dir * t2;
        const bool valid1 = in_segment(t1) && in_arc(intersection1);
        const bool valid2 = in_segment(t2) && in_arc(intersection2);
        return valid1 || valid2;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Segment2<Real>& segment) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_seg_from_dir = segment.from - pivot;
        const Vector2<Real> seg_dir = segment.direction_unnormalized();
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_seg_from_dir.dot(seg_dir);
        const Real dot_minus_r_sqrd = pivot_seg_from_dir.dot(pivot_seg_from_dir) - sqrd(r);
        const Real seg_len_sqrd = segment.length_sqrd();
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * seg_len_sqrd * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_from();
        const Real to_angle_ = angle_to();
        const auto in_arc = [&](const Vector2<Real>& intersection) -> bool {
            const Real intersection_angle = mod(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const auto in_segment
            = [&](const Real t) -> bool { return t >= static_cast<Real>(0) && t <= static_cast<Real>(1); };
        const Vector2<Real> intersection1 = segment.from + seg_dir * t1;
        const Vector2<Real> intersection2 = segment.from + seg_dir * t2;
        const bool valid1 = in_segment(t1) && in_arc(intersection1);
        const bool valid2 = in_segment(t2) && in_arc(intersection2);
        if (valid1 && valid2) {
            return intersection2 < intersection1
                ? std::array { intersection2, intersection1 }
                : std::array { intersection1, intersection2 };
        }
        if (valid1) {
            return std::array { intersection1, intersection1 };
        }
        if (valid2) {
            return std::array { intersection2, intersection2 };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Arc2& other) const
    {
        if (const Vector2<Real> other_to = other.to();
            from.approx_equal(other.from) || from.approx_equal(other_to) || to().approx_equal(other_to)) {
            return true;
        }
        const Real r1 = radius();
        const Real r2 = other.radius();
        const Vector2<Real> pivot_diff = other.pivot - pivot;
        const Real pivot_dist_sqrd = pivot_diff.dot(pivot_diff);
        const Real pivot_dist = sqrt(pivot_dist_sqrd);
        if (pivot_dist > r1 + r2 || pivot_dist < abs(r1 - r2)) {
            return false;
        }
        const Real pivot_intersect_line_dist
            = (sqrd(r1) - sqrd(r2) + pivot_dist_sqrd) / (static_cast<Real>(2) * pivot_dist);
        const Real perp_dist_intersections = sqrt(sqrd(r1) - sqrd(pivot_intersect_line_dist));
        const Vector2<Real> pivots_line_base = pivot + pivot_diff * (pivot_intersect_line_dist / pivot_dist);
        const Vector2<Real> intersection1
            = pivots_line_base + Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Vector2<Real> intersection2
            = pivots_line_base - Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle1 = angle_from();
        const Real to_angle1 = angle_to();
        const Real from_angle2 = other.angle_from();
        const Real to_angle2 = other.angle_to();
        const auto in_arc
            = [&](const Vector2<Real>& intersection,
                  const Vector2<Real>& pivot,
                  const Real from_angle,
                  const Real to_angle) -> bool {
            const Real intersection_angle = remainder(pivot.angle_to(intersection), two_pi);
            return angle_in_range(intersection_angle, from_angle, to_angle);
        };
        const bool in_arc1_1 = in_arc(intersection1, pivot, from_angle1, to_angle1);
        const bool in_arc1_2 = in_arc(intersection2, pivot, from_angle1, to_angle1);
        const bool in_arc2_1 = in_arc(intersection1, other.pivot, from_angle2, to_angle2);
        const bool in_arc2_2 = in_arc(intersection2, other.pivot, from_angle2, to_angle2);
        return (in_arc1_1 && in_arc2_1) || (in_arc1_2 && in_arc2_2);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Arc2& other) const
    {
        if (const Vector2<Real> other_to = other.to();
            from.approx_equal(other.from) || from.approx_equal(other_to) || to().approx_equal(other_to)) {
            return std::nullopt;
        }
        const Real r1 = radius();
        const Real r2 = other.radius();
        const Vector2<Real> pivot_diff = other.pivot - pivot;
        const Real pivot_dist_sqrd = pivot_diff.dot(pivot_diff);
        const Real pivot_dist = sqrt(pivot_dist_sqrd);
        if (pivot_dist > r1 + r2 || pivot_dist < abs(r1 - r2)) {
            return std::nullopt;
        }
        const Real pivot_intersect_line_dist
            = (sqrd(r1) - sqrd(r2) + pivot_dist_sqrd) / (static_cast<Real>(2) * pivot_dist);
        const Real perp_dist_intersections = sqrt(sqrd(r1) - sqrd(pivot_intersect_line_dist));
        const Vector2<Real> pivots_line_base = pivot + pivot_diff * (pivot_intersect_line_dist / pivot_dist);
        const Vector2<Real> intersection1
            = pivots_line_base + Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Vector2<Real> intersection2
            = pivots_line_base - Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle1 = angle_from();
        const Real to_angle1 = angle_to();
        const Real from_angle2 = other.angle_from();
        const Real to_angle2 = other.angle_to();
        const auto in_arc
            = [&](const Vector2<Real>& intersection,
                  const Vector2<Real>& pivot,
                  const Real from_angle,
                  const Real to_angle) -> bool {
            const Real intersection_angle = remainder(pivot.angle_to(intersection), two_pi);
            return angle_in_range(intersection_angle, from_angle, to_angle);
        };
        const bool in_arc1_1 = in_arc(intersection1, pivot, from_angle1, to_angle1);
        const bool in_arc1_2 = in_arc(intersection2, pivot, from_angle1, to_angle1);
        const bool in_arc2_1 = in_arc(intersection1, other.pivot, from_angle2, to_angle2);
        const bool in_arc2_2 = in_arc(intersection2, other.pivot, from_angle2, to_angle2);
        const bool intersection1_valid = in_arc1_1 && in_arc2_1;
        const bool intersection2_valid = in_arc1_2 && in_arc2_2;
        if (intersection1_valid && intersection2_valid) {
            return intersection2 < intersection1
                ? std::array { intersection2, intersection1 }
                : std::array { intersection1, intersection2 };
        }
        if (intersection1_valid) {
            return std::array { intersection1, intersection1 };
        }
        if (intersection2_valid) {
            return std::array { intersection2, intersection2 };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Circle2<Real>& circle) const;

    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    [[nodiscard]] bool approx_tangent(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - pivot;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(b) - static_cast<Real>(4) * c; !approx_zero(disc)) {
            return false;
        }
        const Real t = -b / static_cast<Real>(2);
        const Vector2<Real> p = line.origin + line.direction * t;
        return approx_contains(p);
    }

    [[nodiscard]] bool approx_tangent(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - pivot;
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(b) - static_cast<Real>(4) * c; !approx_zero(disc)) {
            return false;
        }
        const Real t = -b / static_cast<Real>(2);
        if (t < static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> p = ray.origin + ray.direction * t;
        return approx_contains(p);
    }

    [[nodiscard]] bool approx_tangent(const Segment2<Real>& segment) const
    {
        const Vector2<Real> dir = segment.from - pivot;
        const Vector2<Real> segment_dir = segment.direction();
        const Real twice_dot = static_cast<Real>(2) * dir.dot(segment_dir);
        const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(twice_dot) - static_cast<Real>(4) * dist_sqrd_minus_radius_sqrd;
            !approx_zero(disc)) {
            return false;
        }
        const Real t = -twice_dot / static_cast<Real>(2);
        if (t < static_cast<Real>(0) || t > segment.length()) {
            return false;
        }
        const Vector2<Real> p = segment.from + segment_dir * t;
        return approx_contains(p);
    }

    [[nodiscard]] bool approx_tangent(const Arc2& other) const
    {
        if (pivot == other.pivot) {
            return false;
        }
        const Real dist_sqrd = pivot.distance_sqrd(other.pivot);
        const Real r = radius();
        const Real other_r = other.radius();
        if (!nnm::approx_equal(dist_sqrd, sqrd(r + other_r)) && !nnm::approx_equal(dist_sqrd, sqrd(r - other_r))) {
            return false;
        }
        const Real dist = sqrt(dist_sqrd);
        const Vector2<Real> dir = (other.pivot - pivot) / dist;
        const Vector2<Real> p1 = pivot + dir * r;
        const Vector2<Real> p2 = pivot - dir * other_r;
        return (approx_contains(p1) && other.approx_contains(p1)) || (approx_contains(p2) && other.approx_contains(p2));
    }

    [[nodiscard]] bool approx_tangent(const Circle2<Real>& circle) const;

    [[nodiscard]] Arc2 translate(const Vector2<Real>& by) const
    {
        return Arc2 { pivot.translate(by), from.translate(by), angle };
    }

    [[nodiscard]] Arc2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return Arc2 { pivot.scale_at(scale_origin, by), from.scale_at(scale_origin, by), angle };
    }

    [[nodiscard]] Arc2 scale(const Vector2<Real>& by) const
    {
        return Arc2 { pivot.scale(by), from.scale(by), angle };
    }

    [[nodiscard]] Arc2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return Arc2 { pivot.rotate_at(rotate_origin, angle), from.rotate_at(rotate_origin, angle), this->angle };
    }

    [[nodiscard]] Arc2 rotate(const Real angle) const
    {
        return Arc2 { pivot.rotate(angle), from.rotate(angle), this->angle };
    }

    [[nodiscard]] bool approx_coincident(const Arc2& other) const
    {
        if (!pivot.approx_equal(other.pivot)) {
            return false;
        }
        const Vector2<Real> to_ = to();
        const Vector2<Real> other_to = other.to();
        return (from.approx_equal(other.from) && to_.approx_equal(other_to))
            || (from.approx_equal(other_to) && to_.approx_equal(other.from));
    }

    [[nodiscard]] constexpr bool approx_equal(const Arc2& other) const
    {
        return from.approx_equal(other.from) && pivot.approx_equal(other.pivot)
            && nnm::approx_equal(angle, other.angle);
    }

    [[nodiscard]] constexpr bool operator==(const Arc2& other) const
    {
        return pivot == other.pivot && from == other.from && angle == other.angle;
    }

    [[nodiscard]] constexpr bool operator!=(const Arc2& other) const
    {
        return pivot != other.pivot || from != other.from || angle != other.angle;
    }

    [[nodiscard]] constexpr bool operator<(const Arc2& other) const
    {
        if (pivot != other.pivot) {
            return pivot < other.pivot;
        }
        if (from != other.from) {
            return from < other.from;
        }
        return angle < other.angle;
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

    static Circle2 from_center_point(const Vector2<Real>& center, const Vector2<Real>& point)
    {
        return { center, center.distance(point) };
    }

    static Circle2 from_points_unchecked(
        const Vector2<Real>& point1, const Vector2<Real>& point2, const Vector2<Real>& point3)
    {
        const Vector2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Vector2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const Vector2<Real> center = l1.unchecked_intersection(l2);
        const Real radius = center.distance(point1);
        return Circle2 { center, radius };
    }

    static std::optional<Circle2> from_points(
        const Vector2<Real>& point1, const Vector2<Real>& point2, const Vector2<Real>& point3)
    {
        const Vector2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Vector2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const std::optional<Vector2<Real>> center = l1.intersection(l2);
        if (!center.has_value()) {
            return std::nullopt;
        }
        const Real radius = center.value().distance(point1);
        return Circle2 { center.value(), radius };
    }

    [[nodiscard]] constexpr Real circumference() const
    {
        return static_cast<Real>(2) * pi<Real>() * radius;
    }

    [[nodiscard]] constexpr Real perimeter() const
    {
        return circumference();
    }

    [[nodiscard]] constexpr Real area() const
    {
        return pi<Real>() * sqrd(radius);
    }

    [[nodiscard]] constexpr Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
    {
        return (point - center).length_sqrd() <= sqrd(radius);
    }

    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        return max(static_cast<Real>(0), line.distance(center) - radius);
    }

    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        return max(static_cast<Real>(0), ray.distance(center) - radius);
    }

    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        return max(static_cast<Real>(0), segment.distance(center) - radius);
    }

    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        return max(static_cast<Real>(0), arc.distance(center) - radius);
    }

    [[nodiscard]] Real distance(const Circle2& other) const
    {
        const Real dist = center.distance(other.center);
        const Real radius_sum = radius + other.radius;
        return max(static_cast<Real>(0), dist - radius_sum);
    }

    [[nodiscard]] Vector2<Real> point_at(const Real angle) const
    {
        return { center.x + radius * cos(angle), center.y + radius * sin(angle) };
    }

    [[nodiscard]] Vector2<Real> normal_at(const Real angle) const
    {
        return Vector2<Real>::axis_x().rotate(angle);
    }

    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        if (contains(line.origin)) {
            return true;
        }
        const Vector2<Real> dir = line.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(line.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        return discriminant >= static_cast<Real>(0);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(line.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
        const Vector2<Real> p1 = line.origin + line.direction * t1;
        const Vector2<Real> p2 = line.origin + line.direction * t2;
        return p2 < p1 ? std::array { p2, p1 } : std::array { p1, p2 };
    }

    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        if (contains(ray.origin)) {
            return true;
        }
        const Vector2<Real> dir = ray.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            return true;
        }
        if (t1 >= static_cast<Real>(0) || t2 >= static_cast<Real>(0)) {
            return true;
        }
        return false;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            const Vector2<Real> p1 = ray.origin + ray.direction * t1;
            const Vector2<Real> p2 = ray.origin + ray.direction * t2;
            return p2 < p1 ? std::array { p2, p1 } : std::array { p1, p2 };
        }
        if (t1 >= static_cast<Real>(0)) {
            const Vector2<Real> p = ray.origin + ray.direction * t1;
            return std::array { p, p };
        }
        if (t2 >= static_cast<Real>(0)) {
            const Vector2<Real> p = ray.origin + ray.direction * t2;
            return std::array { p, p };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        if (contains(segment.from) || contains(segment.to)) {
            return true;
        }
        const Vector2<Real> seg_dir = segment.to - segment.from;
        const Vector2<Real> circle_dir = segment.from - center;
        const Real seg_len_sqrd = seg_dir.dot(seg_dir);
        const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant
            = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_len - disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_proj_len + disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
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

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Segment2<Real>& segment) const
    {
        const Vector2<Real> seg_dir = segment.to - segment.from;
        const Vector2<Real> circle_dir = segment.from - center;
        const Real seg_len_sqrd = seg_dir.dot(seg_dir);
        const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant
            = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_len - disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_proj_len + disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1) && t2 >= static_cast<Real>(0)
            && t2 <= static_cast<Real>(1)) {
            const Vector2<Real> p1 = segment.from + seg_dir * t1;
            const Vector2<Real> p2 = segment.from + seg_dir * t2;
            return p2 < p1 ? std::array { p2, p1 } : std::array { p1, p2 };
        }
        if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1)) {
            const Vector2<Real> p = segment.from + seg_dir * t1;
            return std::array { p, p };
        }
        if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
            const Vector2<Real> p = segment.from + seg_dir * t2;
            return std::array { p, p };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        if (contains(arc.from)) {
            return true;
        }
        const Real dist = center.distance(arc.pivot);
        const Real arc_radius = arc.radius();
        if (dist > radius + arc_radius || dist < abs(radius - arc_radius) || (dist == 0 && radius == arc_radius)) {
            return false;
        }
        const Real a = (sqrd(radius) - sqrd(arc_radius) + sqrd(dist)) / (static_cast<Real>(2) * dist);
        const Real h = sqrt(sqrd(radius) - sqrd(a));
        const Vector2<Real> diff = arc.pivot - center;
        const Vector2<Real> p = center + a * diff / dist;
        const Vector2<Real> inter1 { p.x + h * diff.y / dist, p.y - h * diff.x / dist };
        const Vector2<Real> inter2 { p.x - h * diff.y / dist, p.y + h * diff.x / dist };
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real inter1_angle = remainder(arc.pivot.angle_to(inter1), two_pi);
        const Real inter2_angle = remainder(arc.pivot.angle_to(inter2), two_pi);
        const Real arc_from_angle = arc.angle_from();
        const Real arc_to_angle = arc.angle_to();
        const bool in_arc = angle_in_range(inter1_angle, arc_from_angle, arc_to_angle)
            || angle_in_range(inter2_angle, arc_from_angle, arc_to_angle);
        return in_arc;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Arc2<Real>& arc) const
    {
        const Real dist = center.distance(arc.pivot);
        const Real arc_radius = arc.radius();
        if (dist > radius + arc_radius || dist < abs(radius - arc_radius) || (dist == 0 && radius == arc_radius)) {
            return std::nullopt;
        }
        const Real a = (sqrd(radius) - sqrd(arc_radius) + sqrd(dist)) / (static_cast<Real>(2) * dist);
        const Real h = sqrt(sqrd(radius) - sqrd(a));
        const Vector2<Real> diff = arc.pivot - center;
        const Vector2<Real> p = center + a * diff / dist;
        const Vector2<Real> inter1 { p.x + h * diff.y / dist, p.y - h * diff.x / dist };
        const Vector2<Real> inter2 { p.x - h * diff.y / dist, p.y + h * diff.x / dist };
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real inter1_angle = remainder(arc.pivot.angle_to(inter1), two_pi);
        const Real inter2_angle = remainder(arc.pivot.angle_to(inter2), two_pi);
        const Real arc_from_angle = arc.angle_from();
        const Real arc_to_angle = arc.angle_to();
        const bool inter1_in_arc = angle_in_range(inter1_angle, arc_from_angle, arc_to_angle);
        const bool inter2_in_arc = angle_in_range(inter2_angle, arc_from_angle, arc_to_angle);
        if (inter1_in_arc && inter2_in_arc) {
            return inter2 < inter1 ? std::array { inter2, inter1 } : std::array { inter1, inter2 };
        }
        if (inter1_in_arc) {
            return std::array { inter1, inter1 };
        }
        if (inter2_in_arc) {
            return std::array { inter2, inter2 };
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr bool intersects(const Circle2& other) const
    {
        return center.distance_sqrd(other.center) <= sqrd(radius + other.radius);
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2& other) const
    {
        const Vector2<Real> diff = other.center - center;
        const Real radius_sum = radius + other.radius;
        if (diff == Vector2<Real>::zero()) {
            return Vector2<Real>::axis_x() * radius_sum;
        }
        const Real dist_sqrd = diff.length_sqrd();
        const Real dist = sqrt(dist_sqrd);
        const Real depth = radius_sum - dist;
        if (depth < static_cast<Real>(0)) {
            return std::nullopt;
        }
        return diff.normalize() * depth;
    }

    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const;

    [[nodiscard]] constexpr bool approx_tangent(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        return approx_zero(discriminant);
    }

    [[nodiscard]] constexpr bool approx_tangent(const Ray2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real twice_dot = static_cast<Real>(2) * dir.dot(line.direction);
        const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - sqrd(radius);
        if (const Real discriminant = sqrd(twice_dot) - static_cast<Real>(4) * dist_sqrd_minus_radius_sqrd;
            !approx_zero(discriminant)) {
            return false;
        }
        const Real t = -twice_dot / static_cast<Real>(2);
        return t >= static_cast<Real>(0);
    }

    [[nodiscard]] constexpr bool approx_tangent(const Segment2<Real>& segment) const
    {
        const Vector2<Real> dir = segment.from - center;
        const Vector2<Real> segment_dir = segment.to - segment.from;
        const Real twice_dot = static_cast<Real>(2) * dir.dot(segment_dir);
        const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - sqrd(radius);
        const Real len_sqrd = segment.length_sqrd();
        if (const Real discriminant = sqrd(twice_dot) - static_cast<Real>(4) * len_sqrd * dist_sqrd_minus_radius_sqrd;
            !approx_zero(discriminant)) {
            return false;
        }
        const Real t = -twice_dot / (static_cast<Real>(2) * len_sqrd);
        return t >= static_cast<Real>(0) && t <= static_cast<Real>(1);
    }

    [[nodiscard]] bool approx_tangent(const Arc2<Real>& arc) const
    {
        if (center == arc.pivot) {
            return false;
        }
        const Real dist_sqrd = center.distance_sqrd(arc.pivot);
        const Real arc_radius = arc.radius();
        const bool is_circle_tangent = nnm::approx_equal(dist_sqrd, sqrd(radius + arc_radius))
            || nnm::approx_equal(dist_sqrd, sqrd(radius - arc_radius));
        if (!is_circle_tangent) {
            return false;
        }
        const Real arc_circle_angle = contains(arc.pivot) ? center.angle_to(arc.pivot) : arc.pivot.angle_to(center);
        return angle_in_range(arc_circle_angle, arc.angle_from(), arc.angle_to());
    }

    [[nodiscard]] constexpr bool approx_tangent(const Circle2& other) const
    {
        if (center == other.center) {
            return false;
        }
        const Real dist_sqrd = center.distance_sqrd(other.center);
        return nnm::approx_equal(dist_sqrd, sqrd(radius + other.radius))
            || nnm::approx_equal(dist_sqrd, sqrd(radius - other.radius));
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
        return { center.scale_at(scale_origin, Vector2<Real>::all(by)), abs(radius * by) };
    }

    [[nodiscard]] Circle2 scale(const Real by) const
    {
        return { center.scale(Vector2<Real>::all(by)), abs(radius * by) };
    }

    [[nodiscard]] constexpr bool approx_coincident(const Circle2& other) const
    {
        return approx_equal(other);
    }

    [[nodiscard]] constexpr bool approx_equal(const Circle2& other) const
    {
        return center.approx_equal(other.center) && nnm::approx_equal(radius, other.radius);
    }

    [[nodiscard]] constexpr bool operator==(const Circle2& other) const
    {
        return center == other.center && radius == other.radius;
    }

    [[nodiscard]] constexpr bool operator!=(const Circle2& other) const
    {
        return center != other.center || radius != other.radius;
    }

    [[nodiscard]] constexpr bool operator<(const Circle2& other) const
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
    Vector2<Real> vertices[3];

    constexpr Triangle2()
        : vertices { Vector2<Real>::zero(), Vector2<Real>::zero(), Vector2<Real>::zero() }
    {
    }

    constexpr Triangle2(const Vector2<Real>& vertex0, const Vector2<Real>& vertex1, const Vector2<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    [[nodiscard]] constexpr Segment2<Real> edge(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        return { vertices[index], vertices[next_index] };
    }

    [[nodiscard]] constexpr Vector2<Real> centroid() const
    {
        return (vertices[0] + vertices[1] + vertices[2]) / static_cast<Real>(3);
    }

    [[nodiscard]] constexpr Vector2<Real> circumcenter() const
    {
        const Segment2<Real> e0 = edge(0);
        const Segment2<Real> e1 = edge(1);
        const Line2<Real> l0 { e0.midpoint(), e0.direction_unnormalized().arbitrary_perpendicular() };
        const Line2<Real> l1 { e1.midpoint(), e1.direction_unnormalized().arbitrary_perpendicular() };
        return l0.unchecked_intersection(l1);
    }

    [[nodiscard]] Real perimeter() const
    {
        return edge(0).length() + edge(1).length() + edge(2).length();
    }

    [[nodiscard]] Vector2<Real> incenter() const
    {
        return angle_bisector(0).unchecked_intersection(angle_bisector(1));
    }

    [[nodiscard]] constexpr Vector2<Real> orthocenter() const
    {
        return Line2<Real>::from_segment(altitude(0)).unchecked_intersection(Line2<Real>::from_segment(altitude(1)));
    }

    [[nodiscard]] constexpr Real area() const
    {
        const Real sum = vertices[0].x * (vertices[1].y - vertices[2].y)
            + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y);
        return abs(sum) / static_cast<Real>(2);
    }

    [[nodiscard]] constexpr Segment2<Real> median(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        return { vertices[index], edge(next_index).midpoint() };
    }

    [[nodiscard]] Line2<Real> perpendicular_bisector(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        return { edge(index).midpoint(), edge(index).direction().arbitrary_perpendicular() };
    }

    [[nodiscard]] Real angle(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        const int prev_index = (index + 2) % 3;
        const Vector2<Real> dir1 = vertices[prev_index] - vertices[index];
        const Vector2<Real> dir2 = vertices[next_index] - vertices[index];
        return acos(dir1.dot(dir2) / (dir1.length() * dir2.length()));
    }

    [[nodiscard]] Line2<Real> angle_bisector(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        const int prev_index = (index + 2) % 3;
        const Vector2<Real> dir1 = (vertices[prev_index] - vertices[index]).normalize();
        const Vector2<Real> dir2 = (vertices[next_index] - vertices[index]).normalize();
        const Vector2<Real> bisector_dir = (dir1 + dir2).normalize();
        return { vertices[index], bisector_dir };
    }

    [[nodiscard]] Vector2<Real> normal(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const Vector2<Real> edge1_dir = edge(1).direction_unnormalized();
        const Vector2<Real> edge2_dir = edge(2).direction_unnormalized();
        const bool reverse = edge1_dir.cross(edge2_dir) > static_cast<Real>(0);
        const Vector2<Real> edge_dir = edge(index).direction();
        const Vector2<Real> normal = { -edge_dir.y, edge_dir.x };
        return reverse ? -normal : normal;
    }

    [[nodiscard]] Segment2<Real> altitude(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const Vector2<Real>& vertex = vertices[index];
        const Segment2<Real> base = edge((index + 1) % 3);
        const Vector2<Real> perp_dir = (base.to - base.from).arbitrary_perpendicular().normalize();
        const Line2<Real> altitude_line { vertex, perp_dir };
        const Vector2<Real> intersection = altitude_line.unchecked_intersection(Line2<Real>::from_segment(base));
        return { vertex, intersection };
    }

    [[nodiscard]] constexpr Vector2<Real> lerp_point(const Vector3<Real>& weights) const
    {
        return weights.x * vertices[0] + weights.y * vertices[1] + weights.z * vertices[2];
    }

    [[nodiscard]] constexpr Vector3<Real> barycentric(const Vector2<Real>& point) const
    {
        const Vector2<Real> v0 = vertices[1] - vertices[0];
        const Vector2<Real> v1 = vertices[2] - vertices[0];
        const Vector2<Real> v2 = point - vertices[0];
        const Real cross01 = v0.cross(v1);
        const Real cross21 = v2.cross(v1);
        const Real cross02 = v0.cross(v2);
        const Real inv_cross01 = static_cast<Real>(1) / cross01;
        const Real y = cross21 * inv_cross01;
        const Real z = cross02 * inv_cross01;
        const Real x = static_cast<Real>(1) - y - z;
        return { x, y, z };
    }

    [[nodiscard]] Circle2<Real> circumcircle() const
    {
        return Circle2<Real>::from_points_unchecked(vertices[0], vertices[1], vertices[2]);
    }

    [[nodiscard]] Circle2<Real> incircle() const
    {
        const Vector2<Real> center = incenter();
        return { center, edge(0).distance(center) };
    }

    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
    {
        const Vector3<Real> b = barycentric(point);
        return b.x >= static_cast<Real>(0) && b.x <= static_cast<Real>(1) && b.y >= static_cast<Real>(0)
            && b.y <= static_cast<Real>(1) && b.z >= static_cast<Real>(0) && b.z <= static_cast<Real>(1);
    }

    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        if (contains(line.origin)) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(line)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Line2<Real>& line) const
    {
        std::array<Vector2<Real>, 2> points;
        int count = 0;
        for (int i = 0; i < 3 && count < 2; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(line)) {
                points[count++] = *point;
            }
        }
        if (count < 2) {
            return std::nullopt;
        }
        return points[1] < points[0] ? std::array { points[1], points[0] } : points;
    }

    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const
    {
        if (contains(ray.origin)) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(ray)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Ray2<Real>& ray) const
    {
        std::array<Vector2<Real>, 2> points;
        int count = 0;
        for (int i = 0; i < 3 && count < 2; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(ray)) {
                points[count++] = *point;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        if (count == 1) {
            points[1] = points[0];
        }
        return points[1] < points[0] ? std::array { points[1], points[0] } : points;
    }

    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const
    {
        if (contains(segment.from) || contains(segment.to)) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(segment)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Segment2<Real>& segment) const
    {
        std::array<Vector2<Real>, 2> points;
        int count = 0;
        for (int i = 0; i < 3 && count < 2; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(segment)) {
                points[count++] = *point;
            }
        }
        if (count == 0) {
            return std::nullopt;
        }
        if (count == 1) {
            points[1] = points[0];
        }
        return points[1] < points[0] ? std::array { points[1], points[0] } : points;
    }

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        if (contains(arc.from) || contains(arc.to())) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(arc)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
    {
        if (contains(circle.center)) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(circle)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
    {
        const auto depth_on_normal
            = [this, &circle](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
            Real tri_max = std::numeric_limits<Real>::lowest();
            for (const Vector2<Real>& v : vertices) {
                const Real proj = v.dot(normal);
                tri_max = max(tri_max, proj);
            }
            const Real circle_proj = circle.center.dot(normal) - circle.radius;
            const Real overlap = tri_max - circle_proj;
            if (overlap < static_cast<Real>(0)) {
                return false;
            }
            if (overlap < min_overlap) {
                min_overlap = overlap;
                min_normal = normal;
            }
            return true;
        };
        std::optional<Vector2<Real>> circle_normal;
        if (!contains(circle.center)) {
            Vector2<Real> closest;
            Real closest_dist_sqrd = std::numeric_limits<Real>::max();
            for (int i = 0; i < 3; ++i) {
                const Vector2<Real> proj = edge(i).project_point(circle.center);
                const Real dist_sqrd = circle.center.distance_sqrd(proj);
                if (dist_sqrd < closest_dist_sqrd) {
                    closest_dist_sqrd = dist_sqrd;
                    closest = proj;
                }
            }
            circle_normal = closest.direction(circle.center);
        }
        const std::array<Vector2<Real>, 3> normals = {
            normal(0),
            normal(1),
            normal(2),
        };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        if (circle_normal.has_value()) {
            if (!depth_on_normal(*circle_normal, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        for (const Vector2<Real>& normal : normals) {
            if (!depth_on_normal(normal, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    [[nodiscard]] bool intersects(const Triangle2& other) const
    {
        for (const Vector2<Real>& vertex : other.vertices) {
            if (contains(vertex)) {
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (other.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2& other) const
    {
        const auto depth_on_normal
            = [this, &other](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : vertices) {
                const Real proj = v.dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Vector2<Real>& v : other.vertices) {
                const Real proj = v.dot(normal);
                other_min = min(other_min, proj);
            }
            const Real overlap = this_max - other_min;
            if (overlap < static_cast<Real>(0)) {
                return false;
            }
            if (overlap < min_overlap) {
                min_overlap = overlap;
                min_normal = normal;
            }
            return true;
        };
        const std::array<Vector2<Real>, 6> normals
            = { normal(0), normal(1), normal(2), -other.normal(0), -other.normal(1), -other.normal(2) };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    [[nodiscard]] constexpr bool approx_equilateral() const
    {
        return nnm::approx_equal(edge(0).length_sqrd(), edge(1).length_sqrd())
            && nnm::approx_equal(edge(1).length_sqrd(), edge(2).length_sqrd())
            && nnm::approx_equal(edge(2).length_sqrd(), edge(0).length_sqrd());
    }

    [[nodiscard]] bool approx_similar(const Triangle2& other) const
    {
        std::array angles { angle(0), angle(1), angle(2) };
        std::array angles_other { other.angle(0), other.angle(1), other.angle(2) };
        int equal_count = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (nnm::approx_equal(angles[i], angles_other[j])) {
                    ++equal_count;
                    if (equal_count >= 2) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    [[nodiscard]] bool approx_right() const
    {
        constexpr Real right_angle = pi() / static_cast<Real>(2);
        return nnm::approx_equal(angle(0), right_angle) || nnm::approx_equal(angle(1), right_angle)
            || nnm::approx_equal(angle(2), right_angle);
    }

    [[nodiscard]] Triangle2 translate(const Vector2<Real>& by) const
    {
        return { vertices[0].translate(by), vertices[1].translate(by), vertices[2].translate(by) };
    }

    [[nodiscard]] Triangle2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { vertices[0].rotate_at(rotate_origin, angle),
                 vertices[1].rotate_at(rotate_origin, angle),
                 vertices[2].rotate_at(rotate_origin, angle) };
    }

    [[nodiscard]] Triangle2 rotate(const Real angle) const
    {
        return { vertices[0].rotate(angle), vertices[1].rotate(angle), vertices[2].rotate(angle) };
    }

    [[nodiscard]] Triangle2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { vertices[0].scale_at(scale_origin, by),
                 vertices[1].scale_at(scale_origin, by),
                 vertices[2].scale_at(scale_origin, by) };
    }

    [[nodiscard]] Triangle2 scale(const Vector2<Real>& by) const
    {
        return { vertices[0].scale(by), vertices[1].scale(by), vertices[2].scale(by) };
    }

    [[nodiscard]] Triangle2 shear_x_at(const Vector2<Real>& shear_origin, const Real angle_y) const
    {
        return { vertices[0].shear_x_at(shear_origin, angle_y),
                 vertices[1].shear_x_at(shear_origin, angle_y),
                 vertices[2].shear_x_at(shear_origin, angle_y) };
    }

    [[nodiscard]] Triangle2 shear_x(const Real angle_y) const
    {
        return { vertices[0].shear_x(angle_y), vertices[1].shear_x(angle_y), vertices[2].shear_x(angle_y) };
    }

    [[nodiscard]] Triangle2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
    {
        return { vertices[0].shear_y_at(shear_origin, angle_x),
                 vertices[1].shear_y_at(shear_origin, angle_x),
                 vertices[2].shear_y_at(shear_origin, angle_x) };
    }

    [[nodiscard]] Triangle2 shear_y(const Real angle_x) const
    {
        return { vertices[0].shear_y(angle_x), vertices[1].shear_y(angle_x), vertices[2].shear_y(angle_x) };
    }

    [[nodiscard]] constexpr bool approx_coincident(const Triangle2& other) const
    {
        const std::array permutations {
            Triangle2 { vertices[0], vertices[1], vertices[2] }, Triangle2 { vertices[0], vertices[2], vertices[1] },
            Triangle2 { vertices[1], vertices[0], vertices[2] }, Triangle2 { vertices[1], vertices[2], vertices[0] },
            Triangle2 { vertices[2], vertices[0], vertices[1] }, Triangle2 { vertices[2], vertices[1], vertices[0] }
        };
        for (const Triangle2& permutation : permutations) {
            if (permutation.approx_equal(other)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool approx_equal(const Triangle2& other) const
    {
        return vertices[0].approx_equal(other.vertices[0]) && vertices[1].approx_equal(other.vertices[1])
            && vertices[2].approx_equal(other.vertices[2]);
    }

    [[nodiscard]] constexpr bool operator==(const Triangle2& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    [[nodiscard]] constexpr bool operator!=(const Triangle2& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    [[nodiscard]] constexpr bool operator<(const Triangle2& other) const
    {
        if (vertices[0] == other.vertices[0]) {
            if (vertices[1] == other.vertices[1]) {
                return vertices[2] < other.vertices[2];
            }
            return vertices[1] < other.vertices[1];
        }
        return vertices[0] < other.vertices[0];
    }
};

template <typename Real>
class Rectangle2 {
public:
    Vector2<Real> center;
    Vector2<Real> size;
    Real angle;

    constexpr Rectangle2()
        : center { Vector2<Real>::zero() }
        , size { Vector2<Real>::zero() }
        , angle { static_cast<Real>(0) }
    {
    }

    constexpr Rectangle2(const Vector2<Real>& center, const Vector2<Real>& size, const Real angle)
        : center { center }
        , size { size }
        , angle { angle }
    {
    }

    [[nodiscard]] Vector2<Real> vertex_nx_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center - half_size).rotate_at(center, angle);
    }

    [[nodiscard]] Vector2<Real> vertex_nx_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Vector2<Real> { center.x - half_size.x, center.y + half_size.y }.rotate_at(center, angle);
    }

    [[nodiscard]] Vector2<Real> vertex_px_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Vector2<Real> { center.x + half_size.x, center.y - half_size.y }.rotate_at(center, angle);
    }

    [[nodiscard]] Vector2<Real> vertex_px_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center + half_size).rotate_at(center, angle);
    }

    [[nodiscard]] Segment2<Real> edge_nx() const
    {
        return { vertex_nx_ny(), vertex_nx_py() };
    }

    [[nodiscard]] Segment2<Real> edge_ny() const
    {
        return { vertex_nx_ny(), vertex_px_ny() };
    }

    [[nodiscard]] Segment2<Real> edge_px() const
    {
        return { vertex_px_ny(), vertex_px_py() };
    }

    [[nodiscard]] Segment2<Real> edge_py() const
    {
        return { vertex_nx_py(), vertex_px_py() };
    }

    [[nodiscard]] Vector2<Real> normal_nx() const
    {
        const Vector2<Real> dir = edge_nx().direction();
        return { -dir.y, dir.x };
    }

    [[nodiscard]] Vector2<Real> normal_ny() const
    {
        const Vector2<Real> dir = edge_ny().direction();
        return { dir.y, -dir.x };
    }

    [[nodiscard]] Vector2<Real> normal_px() const
    {
        const Vector2<Real> dir = edge_px().direction();
        return { dir.y, -dir.x };
    }

    [[nodiscard]] Vector2<Real> normal_py() const
    {
        const Vector2<Real> dir = edge_py().direction();
        return { -dir.y, dir.x };
    }

    [[nodiscard]] constexpr Real area() const
    {
        return size.x * size.y;
    }

    [[nodiscard]] constexpr Real perimeter() const
    {
        return static_cast<Real>(2) * size.x + static_cast<Real>(2) * size.y;
    }

    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> local_point = point.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return abs(local_point.x) <= half_size.x && abs(local_point.y) <= half_size.y;
    }

    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(point);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return contains(point) ? -min_dist : min_dist;
    }

    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> local_point = point.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Vector2<Real> closest = local_point.clamp(-half_size, half_size);
        return local_point.distance(closest);
    }

    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(line);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(ray);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        if (contains(segment.from)) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(segment);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        if (contains(arc.from)) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(arc);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    [[nodiscard]] Real distance(const Circle2<Real>& circle) const
    {
        if (intersects(circle)) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(circle);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    // TODO: test
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const
    {
        if (contains(triangle.vertices[0])) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = static_cast<Real>(0);
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(triangle);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    // TODO: test
    [[nodiscard]] Real distance(const Rectangle2& other) const
    {
        if (contains(other.vertex_nx_ny())) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        const std::array<Segment2<Real>, 4> edges_other {
            other.edge_nx(), other.edge_ny(), other.edge_px(), other.edge_py()
        };
        Real min_dist = static_cast<Real>(0);
        for (int i = 0; i < 4; ++i) {
            const Real dist = edges[i].distance(edges_other[i]);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    [[nodiscard]] bool intersects(const Line2<Real>& line) const
    {
        return edge_nx().intersects(line) || edge_ny().intersects(line) || edge_px().intersects(line)
            || edge_py().intersects(line);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Line2<Real>& line) const
    {
        std::array<Vector2<Real>, 2> inters;
        int inter_count = 0;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
                inters[inter_count++] = intersection.value();
            }
            if (inter_count >= 2) {
                break;
            }
        }
        if (inter_count >= 2) {
            return inters[1] < inters[0] ? std::array { inters[1], inters[0] } : inters;
        }
        if (inter_count == 1) {
            return std::array { inters[0], inters[0] };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        return edge_nx().intersects(ray) || edge_ny().intersects(ray) || edge_px().intersects(ray)
            || edge_py().intersects(ray);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Ray2<Real>& ray) const
    {
        std::array<Vector2<Real>, 2> inters;
        int inter_count = 0;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
                inters[inter_count++] = intersection.value();
            }
            if (inter_count >= 2) {
                break;
            }
        }
        if (inter_count >= 2) {
            return inters[1] < inters[0] ? std::array { inters[1], inters[0] } : inters;
        }
        if (inter_count == 1) {
            return std::array { inters[0], inters[0] };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        return contains(segment.from) || contains(segment.to) || edge_nx().intersects(segment)
            || edge_ny().intersects(segment) || edge_px().intersects(segment) || edge_py().intersects(segment);
    }

    [[nodiscard]] std::optional<std::array<Vector2<Real>, 2>> intersections(const Segment2<Real>& segment) const
    {
        std::array<Vector2<Real>, 2> inters;
        int inter_count = 0;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(segment);
                intersection.has_value()) {
                inters[inter_count++] = intersection.value();
            }
            if (inter_count >= 2) {
                break;
            }
        }
        if (inter_count >= 2) {
            return inters[1] < inters[0] ? std::array { inters[1], inters[0] } : inters;
        }
        if (inter_count == 1) {
            return std::array { inters[0], inters[0] };
        }
        return std::nullopt;
    }

    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        return contains(arc.from) || contains(arc.to()) || edge_nx().intersects(arc) || edge_ny().intersects(arc)
            || edge_px().intersects(arc) || edge_py().intersects(arc);
    }

    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
    {
        if (contains(circle.center)) {
            return true;
        }
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Circle2<Real> circle_local = circle.translate(-center).rotate(-angle);
        const Vector2<Real> closest = circle_local.center.clamp(-half_size, half_size);
        const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
        return dist_sqrd <= sqrd(circle.radius);
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
    {
        const Circle2<Real> circle_local = circle.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Vector2<Real> closest = circle_local.center.clamp(-half_size, half_size);
        const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
        if (dist_sqrd > sqrd(circle.radius)) {
            return std::nullopt;
        }
        const Vector2<Real> min_pos = -half_size - Vector2<Real>::all(circle.radius);
        const Vector2<Real> max_pos = half_size + Vector2<Real>::all(circle.radius);
        const Vector2<Real> diff_min = min_pos - circle_local.center;
        const Vector2<Real> diff_max = max_pos - circle_local.center;
        const Real diff_x = abs(diff_min.x) <= abs(diff_max.x) ? diff_min.x : diff_max.x;
        const Real diff_y = abs(diff_min.y) <= abs(diff_max.y) ? diff_min.y : diff_max.y;
        return abs(diff_x) <= abs(diff_y)
            ? Vector2<Real> { diff_x, static_cast<Real>(0) }.rotate(angle)
            : Vector2<Real> { static_cast<Real>(0), diff_y }.rotate(angle);
    }

    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const
    {
        for (int i = 0; i < 3; ++i) {
            if (contains(triangle.vertices[i])) {
                return true;
            }
        }
        const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (edge.intersects(triangle)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& rect_verts,
                 const std::array<Vector2<Real>, 3>& tri_verts,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real rect_max = std::numeric_limits<Real>::lowest();
            Real tri_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : rect_verts) {
                const Real proj = v.dot(normal);
                rect_max = max(rect_max, proj);
            }
            for (const Vector2<Real>& v : tri_verts) {
                const Real proj = v.dot(normal);
                tri_min = min(tri_min, proj);
            }
            const Real overlap = rect_max - tri_min;
            if (overlap < static_cast<Real>(0)) {
                return false;
            }
            if (overlap < min_overlap) {
                min_overlap = overlap;
                min_normal = normal;
            }
            return true;
        };
        const std::array<Vector2<Real>, 7> normals = {
            normal_nx(),         normal_ny(),         normal_px(),         normal_py(),
            -triangle.normal(0), -triangle.normal(1), -triangle.normal(2),
        };
        const std::array<Vector2<Real>, 4> rect_verts
            = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 3> tri_verts
            = { triangle.vertices[0], triangle.vertices[1], triangle.vertices[2] };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(rect_verts, tri_verts, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    [[nodiscard]] bool intersects(const Rectangle2& other) const
    {
        const std::array<Vector2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        for (const Vector2<Real>& vertex : vertices_other) {
            if (contains(vertex)) {
                return true;
            }
        }
        const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (other.intersects(edge)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2& other) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& verts,
                 const std::array<Vector2<Real>, 4>& verts_other,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : verts) {
                const Real proj = v.dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Vector2<Real>& v : verts_other) {
                const Real proj = v.dot(normal);
                other_min = min(other_min, proj);
            }
            const Real overlap = this_max - other_min;
            if (overlap < static_cast<Real>(0)) {
                return false;
            }
            if (overlap < min_overlap) {
                min_overlap = overlap;
                min_normal = normal;
            }
            return true;
        };
        const std::array<Vector2<Real>, 8> normals = {
            normal_nx(),        normal_ny(),        normal_px(),        normal_py(),
            -other.normal_nx(), -other.normal_ny(), -other.normal_px(), -other.normal_py(),
        };
        const std::array<Vector2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 4> verts_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(verts, verts_other, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    [[nodiscard]] bool approx_coincident(const Rectangle2& other) const
    {
        const Vector2<Real> v1 = vertex_nx_ny();
        const Vector2<Real> v2 = vertex_nx_py();
        const Vector2<Real> v3 = vertex_px_ny();
        const Vector2<Real> v4 = vertex_px_py();
        std::array<Vector2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        const std::array<std::array<Vector2<Real>, 4>, 8> permutations {
            { { v1, v2, v3, v4 },
              { v2, v3, v4, v1 },
              { v3, v4, v1, v2 },
              { v4, v1, v2, v3 },
              { v4, v3, v2, v1 },
              { v3, v2, v1, v4 },
              { v2, v1, v4, v3 },
              { v1, v4, v3, v2 } }
        };
        for (const std::array<Vector2<Real>, 4> permutation : permutations) {
            bool equal = true;
            for (int i = 0; i < 4; ++i) {
                if (!vertices_other[i].approx_equal(permutation[i])) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool approx_equal(const Rectangle2& other) const
    {
        return center.approx_equal(other.center) && size.approx_equal(other.size)
            && nnm::approx_equal(angle, other.angle);
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
constexpr bool Line2<Real>::approx_parallel(const Ray2<Real>& ray) const
{
    return ray.approx_parallel(*this);
}

template <typename Real>
constexpr bool Line2<Real>::approx_parallel(const Segment2<Real>& segment) const
{
    return segment.approx_parallel(*this);
}

template <typename Real>
constexpr bool Line2<Real>::approx_perpendicular(const Ray2<Real>& ray) const
{
    return ray.approx_perpendicular(*this);
}

template <typename Real>
constexpr bool Line2<Real>::approx_perpendicular(const Segment2<Real>& segment) const
{
    return segment.approx_perpendicular(*this);
}

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
constexpr bool Line2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
Line2<Real> Line2<Real>::from_segment(const Segment2<Real>& segment)
{
    return { segment.from, (segment.to - segment.from).normalize() };
}

template <typename Real>
constexpr bool Line2<Real>::approx_collinear(const Ray2<Real>& ray) const
{
    return ray.approx_collinear(*this);
}

template <typename Real>
constexpr bool Line2<Real>::approx_collinear(const Segment2<Real>& segment) const
{
    return segment.approx_collinear(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Ray2<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
constexpr Real Line2<Real>::distance(const Segment2<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Line2<Real>::intersections(const Circle2<Real>& circle) const
{
    return circle.intersections(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Line2<Real>::intersections(const Triangle2<Real>& triangle) const
{
    return triangle.intersections(*this);
}

template <typename Real>
bool Line2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Line2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
}

template <typename Real>
bool Line2<Real>::approx_tangent(const Arc2<Real>& arc) const
{
    return arc.approx_tangent(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr Line2<Real> Line2<Real>::from_ray(const Ray2<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
constexpr bool Line2<Real>::approx_tangent(const Circle2<Real>& circle) const
{
    return circle.approx_tangent(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::approx_parallel(const Segment2<Real>& segment) const
{
    return segment.approx_parallel(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::approx_perpendicular(const Segment2<Real>& segment) const
{
    return segment.approx_perpendicular(*this);
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

template <typename Real>
constexpr bool Ray2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::approx_tangent(const Circle2<Real>& circle) const
{
    return circle.approx_tangent(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::approx_collinear(const Segment2<Real>& segment) const
{
    return segment.approx_collinear(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Segment2<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Ray2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Ray2<Real>::intersections(const Circle2<Real>& circle) const
{
    return circle.intersections(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Ray2<Real>::intersections(const Triangle2<Real>& triangle) const
{
    return triangle.intersections(*this);
}

template <typename Real>
bool Ray2<Real>::approx_tangent(const Arc2<Real>& arc) const
{
    return arc.approx_tangent(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Segment2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Segment2<Real>::intersections(const Circle2<Real>& circle) const
{
    return circle.intersections(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Segment2<Real>::intersections(const Triangle2<Real>& triangle) const
{
    return triangle.intersections(*this);
}

template <typename Real>
bool Segment2<Real>::approx_tangent(const Arc2<Real>& arc) const
{
    return arc.approx_tangent(*this);
}

template <typename Real>
Real Arc2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
std::optional<std::array<Vector2<Real>, 2>> Arc2<Real>::intersections(const Circle2<Real>& circle) const
{
    return circle.intersections(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
bool Arc2<Real>::approx_tangent(const Circle2<Real>& circle) const
{
    return circle.approx_tangent(*this);
}

template <typename Real>
bool Circle2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Circle2<Real>::intersect_depth(const Triangle2<Real>& triangle) const
{
    const std::optional<Vector2<Real>> result = triangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
constexpr bool Segment2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr bool Segment2<Real>::approx_tangent(const Circle2<Real>& circle) const
{
    return circle.approx_tangent(*this);
}
}

#endif