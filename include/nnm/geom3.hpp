/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_HPP
#define NNM_GEOM3_HPP

#include <nnm/nnm.hpp>

namespace nnm {

template <typename Real>
class Line3;
using Line3f = Line3<float>;
using Line3d = Line3<double>;
template <typename Real>
class Ray3;
using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;
template <typename Real>
class Segment3;
using Segment3f = Segment3<float>;
using Segment3d = Segment3<double>;

template <typename Real>
class Line3 {
public:
    Vector3<Real> origin;
    Vector3<Real> direction;

    constexpr Line3()
        : origin { Vector3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    constexpr Line3(const Vector3<Real>& origin, const Vector3<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    static Line3 from_points(const Vector3<Real>& point1, const Vector3<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    static Line3 from_ray(const Ray3<Real>& ray);

    static constexpr Line3 axis_x()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    static constexpr Line3 axis_y()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    static constexpr Line3 axis_z()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_z() };
    }

    static constexpr Line3 axis_x_offset(const Real y, const Real z)
    {
        return { { static_cast<Real>(0), y, z }, Vector3<Real>::axis_x() };
    }

    static constexpr Line3 axis_y_offset(const Real x, const Real z)
    {
        return { { x, static_cast<Real>(0), z }, Vector3<Real>::axis_y() };
    }

    static constexpr Line3 axis_z_offset(const Real x, const Real y)
    {
        return { { x, y, static_cast<Real>(0) }, Vector3<Real>::axis_z() };
    }

    [[nodiscard]] constexpr Line3 parallel_containing(const Vector3<Real>& point) const
    {
        return { point, direction };
    }

    [[nodiscard]] constexpr Line3 arbitrary_perpendicular_containing(const Vector3<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
    }

    [[nodiscard]] Line3 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] bool approx_collinear(const Ray3<Real>& ray) const;

    [[nodiscard]] constexpr bool approx_contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        const Vector3<Real> proj = origin + direction * t;
        return proj.approx_equal(point);
    }

    [[nodiscard]] constexpr Real distance(const Vector3<Real>& point) const
    {
        return (point - origin).cross(direction).length();
    }

    [[nodiscard]] Real distance(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        if (dir_cross.approx_zero()) {
            return distance(other.origin);
        }
        const Vector3<Real> diff = origin - other.origin;
        return abs(dir_cross.dot(diff)) / dir_cross.length();
    }

    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    [[nodiscard]] bool approx_parallel(const Line3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    [[nodiscard]] bool approx_parallel(const Ray3<Real>& ray) const;

    [[nodiscard]] bool approx_perpendicular(const Line3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] bool approx_perpendicular(const Ray3<Real>& ray) const;

    [[nodiscard]] bool approx_intersects(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return approx_contains(other.origin);
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = other.origin + other.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    [[nodiscard]] bool approx_intersects(const Ray3<Real>& ray) const;

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3<Real>& ray) const;

    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        return origin + direction * t;
    }

    [[nodiscard]] bool approx_coincident(const Line3& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector3<Real> diff = origin - other.origin;
        return diff.cross(other.direction).approx_zero();
    }

    [[nodiscard]] Line3 translate(const Vector3<Real>& by) const
    {
        return { origin.translate(by), direction };
    }

    [[nodiscard]] Line3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Line3 scale(const Vector3<Real>& by) const
    {
        return { origin.scale(by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Line3 rotate_axis_angle_at(
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Line3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), direction.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Line3 rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 direction.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Line3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), direction.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Line3 shear_x_at(const Vector3<Real>& shear_origin, const Real angle_y, const Real angle_z) const
    {
        return { origin.shear_x_at(shear_origin, angle_y, angle_z), direction.shear_x(angle_y, angle_z).normalize() };
    }

    [[nodiscard]] Line3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return { origin.shear_x(angle_y, angle_z), direction.shear_x(angle_y, angle_z).normalize() };
    }

    [[nodiscard]] Line3 shear_y_at(const Vector3<Real>& shear_origin, const Real angle_x, const Real angle_z) const
    {
        return { origin.shear_y_at(shear_origin, angle_x, angle_z), direction.shear_y(angle_x, angle_z).normalize() };
    }

    [[nodiscard]] Line3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return { origin.shear_y(angle_x, angle_z), direction.shear_y(angle_x, angle_z).normalize() };
    }

    [[nodiscard]] Line3 shear_z_at(const Vector3<Real>& shear_origin, const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z_at(shear_origin, angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    [[nodiscard]] Line3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z(angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    [[nodiscard]] bool approx_equal(const Line3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    [[nodiscard]] bool operator==(const Line3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    [[nodiscard]] bool operator!=(const Line3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    [[nodiscard]] bool operator<(const Line3& other) const
    {
        if (origin == other.origin) {
            return direction < other.direction;
        }
        return origin < other.origin;
    }
};

template <typename Real>
class Ray3 {
public:
    Vector3<Real> origin;
    Vector3<Real> direction;

    constexpr Ray3()
        : origin { Vector3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    constexpr Ray3(const Vector3<Real>& origin, const Vector3<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    static Ray3 from_point_to_point(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        return { from, from.direction(to) };
    }

    [[nodiscard]] Ray3 normalize() const
    {
        return { origin, direction.normalize() };
    }

    [[nodiscard]] bool approx_collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_ray(*this).approx_contains(point);
    }

    [[nodiscard]] bool approx_collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).approx_coincident(line);
    }

    [[nodiscard]] bool approx_collinear(const Ray3& other) const
    {
        return Line3<Real>::from_ray(*this).approx_coincident(Line3<Real>::from_ray(other));
    }

    [[nodiscard]] bool approx_contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> proj = project_point(point);
        return proj.approx_equal(point);
    }

    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        if (t < static_cast<Real>(0)) {
            return origin.distance(point);
        }
        return dir.cross(direction).length();
    }

    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = line.origin - origin;
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return line.distance(origin);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_line = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return line.distance(origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = line.origin + line.direction * t_line;
        return p1.distance(p2);
    }

    [[nodiscard]] Real distance(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.origin - origin;
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            const Real d1 = distance(other.origin);
            const Real d2 = other.distance(origin);
            return min(d1, d2);
        }
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return other.distance(origin);
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
            return distance(other.origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = other.origin + other.direction * t_other;
        return p1.distance(p2);
    }

    [[nodiscard]] bool approx_parallel(const Line3<Real>& line) const
    {
        return direction.cross(line.direction).approx_zero();
    }

    [[nodiscard]] bool approx_parallel(const Ray3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    [[nodiscard]] bool approx_perpendicular(const Line3<Real>& line) const
    {
        return nnm::approx_zero(direction.dot(line.direction));
    }

    [[nodiscard]] bool approx_perpendicular(const Ray3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    [[nodiscard]] bool approx_intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.approx_contains(origin);
        }
        const Vector3<Real> diff = line.origin - origin;
        Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = max(static_cast<Real>(0), t);
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = line.origin + line.direction * t_other;
        return p.approx_equal(p_other);
    }

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.origin - origin;
        Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = max(static_cast<Real>(0), t);
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = line.origin + line.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    [[nodiscard]] bool approx_intersects(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return other.approx_contains(origin) || approx_contains(other.origin);
        }
        const Vector3<Real> diff = other.origin - origin;
        Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = max(static_cast<Real>(0), t);
        Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        t_other = max(static_cast<Real>(0), t_other);
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = max(static_cast<Real>(0), t);
        Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        t_other = max(static_cast<Real>(0), t_other);
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = other.origin + other.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = max(static_cast<Real>(0), dir.dot(direction));
        return origin + direction * t;
    }

    [[nodiscard]] Ray3 translate(const Vector3<Real>& by) const
    {
        return { origin.translate(by), direction };
    }

    [[nodiscard]] Ray3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Ray3 scale(const Vector3<Real>& by) const
    {
        return { origin.scale(by), direction.scale(by).normalize() };
    }

    [[nodiscard]] Ray3 rotate_axis_angle_at(
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Ray3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), direction.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Ray3 rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 direction.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Ray3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), direction.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Ray3 shear_x_at(const Vector3<Real>& shear_origin, const Real angle_y, const Real angle_z) const
    {
        return { origin.shear_x_at(shear_origin, angle_y, angle_z), direction.shear_x(angle_y, angle_z).normalize() };
    }

    [[nodiscard]] Ray3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return { origin.shear_x(angle_y, angle_z), direction.shear_x(angle_y, angle_z).normalize() };
    }

    [[nodiscard]] Ray3 shear_y_at(const Vector3<Real>& shear_origin, const Real angle_x, const Real angle_z) const
    {
        return { origin.shear_y_at(shear_origin, angle_x, angle_z), direction.shear_y(angle_x, angle_z).normalize() };
    }

    [[nodiscard]] Ray3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return { origin.shear_y(angle_x, angle_z), direction.shear_y(angle_x, angle_z).normalize() };
    }

    [[nodiscard]] Ray3 shear_z_at(const Vector3<Real>& shear_origin, const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z_at(shear_origin, angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    [[nodiscard]] Ray3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z(angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    [[nodiscard]] bool approx_equal(const Ray3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    [[nodiscard]] bool operator==(const Ray3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    [[nodiscard]] bool operator!=(const Ray3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    [[nodiscard]] bool operator<(const Ray3& other) const
    {
        if (origin == other.origin) {
            return direction < other.direction;
        }
        return origin < other.origin;
    }
};

template <typename Real>
class Segment3 {
public:
    Vector3<Real> from;
    Vector3<Real> to;

    constexpr Segment3()
        : from { Vector3<Real>::zero() }
        , to { Vector3<Real>::zero() }
    {
    }

    constexpr Segment3(const Vector3<Real>& from, const Vector3<Real>& to)
        : from { from }
        , to { to }
    {
    }

    [[nodiscard]] bool approx_collinear(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff1 = point - from;
        const Vector3<Real> diff2 = to - from;
        return diff1.cross(diff2).approx_zero();
    }

    [[nodiscard]] bool approx_collinear(const Line3<Real>& line) const
    {
        if (!approx_parallel(line)) {
            return false;
        }
        const Vector3<Real> diff = from - line.origin;
        return diff.cross(line.direction).approx_zero();
    }

    [[nodiscard]] bool approx_collinear(const Ray3<Real>& ray) const
    {
        if (!approx_parallel(ray)) {
            return false;
        }
        const Vector3<Real> diff = from - ray.origin;
        return diff.cross(ray.direction).approx_zero();
    }

    [[nodiscard]] bool approx_collinear(const Segment3& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector3<Real> diff = from - other.from;
        return diff.cross(other.to - other.from).approx_zero();
    }

    [[nodiscard]] bool approx_contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff1 = point - from;
        const Vector3<Real> diff2 = to - from;
        if (!diff1.cross(diff2).approx_zero()) {
            return false;
        }
        const Real dot = diff1.dot(diff2);
        const Real length_sqrd = diff2.dot(diff2);
        return dot >= static_cast<Real>(0) && dot <= length_sqrd;
    }

    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = to - from;
        const Vector3<Real> diff = point - from;
        Real t = diff.dot(dir) / dir.dot(dir);
        if (t < static_cast<Real>(0)) {
            return diff.length();
        }
        if (t > static_cast<Real>(1)) {
            return (point - to).length();
        }
        Vector3<Real> proj = from + dir * t;
        return (point - proj).length();
    }

    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = line.origin - from;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = line.distance(from);
            const Real d2 = line.distance(to);
            return min(d1, d2);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return line.distance(from);
        }
        if (t > static_cast<Real>(1)) {
            return line.distance(to);
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p1 = from.lerp(to, t);
        const Vector3<Real> p2 = line.origin + line.direction * t_line;
        return p1.distance(p2);
    }

    // TODO: test
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = ray.origin - from;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = ray.distance(from);
            const Real d2 = ray.distance(to);
            const Real d3 = distance(ray.origin);
            return min(d1, min(d2, d3));
        }
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return ray.distance(from);
        }
        if (t > static_cast<Real>(1)) {
            return ray.distance(to);
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_ray < static_cast<Real>(0)) {
            return distance(ray.origin);
        }
        const Vector3<Real> p1 = from.lerp(to, t);
        const Vector3<Real> p2 = ray.origin + ray.direction * t_ray;
        return p1.distance(p2);
    }

    [[nodiscard]] Real distance(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.from - from;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = other.distance(from);
            const Real d2 = other.distance(to);
            const Real d3 = distance(other.from);
            const Real d4 = distance(other.to);
            return min(min(d1, d2), min(d3, d4));
        }
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return other.distance(from);
        }
        if (t > static_cast<Real>(1)) {
            return other.distance(to);
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
            return distance(other.from);
        }
        if (t_other > static_cast<Real>(1)) {
            return distance(other.to);
        }
        const Vector3<Real> p1 = from.lerp(to, t);
        const Vector3<Real> p2 = other.from.lerp(other.to, t_other);
        return p1.distance(p2);
    }

    // TODO: test
    [[nodiscard]] Vector3<Real> direction_unnormalized() const
    {
        return to - from;
    }

    // TODO: test
    [[nodiscard]] Vector3<Real> direction() const
    {
        return direction_unnormalized().normalize();
    }

    // TODO: test
    [[nodiscard]] bool approx_parallel(const Line3<Real>& line) const
    {
        return direction_unnormalized().cross(line.direction).approx_zero();
    }

    // TODO: test
    [[nodiscard]] bool approx_parallel(const Ray3<Real>& ray) const
    {
        return direction_unnormalized().cross(ray.direction).approx_zero();
    }

    // TODO: test
    [[nodiscard]] bool approx_parallel(const Segment3& other) const
    {
        return direction_unnormalized().cross(other.direction_unnormalized()).approx_zero();
    }

    // TODO: test
    [[nodiscard]] bool approx_perpendicular(const Line3<Real>& line) const
    {
        return approx_zero(direction_unnormalized().dot(line.direction));
    }

    // TODO: test
    [[nodiscard]] bool approx_perpendicular(const Ray3<Real>& ray) const
    {
        return approx_zero(direction_unnormalized().dot(ray.direction));
    }

    // TODO: test
    [[nodiscard]] bool approx_perpendicular(const Segment3& other) const
    {
        return approx_zero(direction_unnormalized().dot(other.direction_unnormalized()));
    }

    [[nodiscard]] bool approx_intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.approx_contains(from);
        }
        const Vector3<Real> diff = line.origin - from;
        Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = from.lerp(to, t);
        const Vector3<Real> p_other = line.origin + line.direction * t_line;
        return p.approx_equal(p_other);
    }

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.origin - from;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = from.lerp_clamped(to, t);
        if (const Vector3<Real> p_other = line.origin + line.direction * t_line; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    // TODO: test
    [[nodiscard]] bool approx_intersects(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return ray.approx_contains(from) || ray.approx_contains(to);
        }
        const Vector3<Real> diff = ray.origin - from;
        Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        t_ray = max(static_cast<Real>(0), t_ray);
        const Vector3<Real> p = from.lerp(to, t);
        const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray;
        return p.approx_equal(p_ray);
    }

    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = ray.origin - from;
        Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        t_ray = max(static_cast<Real>(0), t_ray);
        const Vector3<Real> p = from.lerp(to, t);
        if (const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray; !p.approx_equal(p_ray)) {
            return std::nullopt;
        }
        return p;
    }

    // TODO: test
    [[nodiscard]] bool approx_intersects(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return approx_contains(other.from) || approx_contains(other.to) || other.approx_contains(from)
                || other.approx_contains(to);
        }
        const Vector3<Real> diff = other.from - from;
        Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        t = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        t_other = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        const Vector3<Real> p = from.lerp(to, t);
        const Vector3<Real> p_other = from.lerp(to, t_other);
        return p.approx_equal(p_other);
    }

    // TODO: test
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.from - from;
        Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        t = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        t_other = clamp(t, static_cast<Real>(0), static_cast<Real>(1));
        const Vector3<Real> p = from.lerp(to, t);
        if (const Vector3<Real> p_other = from.lerp(to, t_other); !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }
};

template <typename Real>
Line3<Real> Line3<Real>::from_ray(const Ray3<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
bool Line3<Real>::approx_collinear(const Ray3<Real>& ray) const
{
    return ray.approx_collinear(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Ray3<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
bool Line3<Real>::approx_parallel(const Ray3<Real>& ray) const
{
    return ray.approx_parallel(*this);
}

template <typename Real>
bool Line3<Real>::approx_perpendicular(const Ray3<Real>& ray) const
{
    return ray.approx_perpendicular(*this);
}

template <typename Real>
bool Line3<Real>::approx_intersects(const Ray3<Real>& ray) const
{
    return ray.approx_intersects(*this);
}

template <typename Real>
std::optional<Vector3<Real>> Line3<Real>::approx_intersection(const Ray3<Real>& ray) const
{
    return ray.approx_intersection(*this);
}

}

#endif