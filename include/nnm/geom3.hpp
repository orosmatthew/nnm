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
        if (dir_cross != Vector3<Real>::zero()) {
            const Vector3<Real> diff = origin - other.origin;
            return abs(dir_cross.dot(diff)) / dir_cross.length();
        }
        return distance(other.origin);
    }

    [[nodiscard]] bool approx_parallel(const Line3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    [[nodiscard]] bool approx_perpendicular(const Line3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

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
            return diff.cross(direction).length();
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
        const Real origin_proj = origin.distance(other.project_point(origin));
        const Real origin_proj_other = other.origin.distance(project_point(other.origin));
        const Real origin_proj_min = min(origin_proj, origin_proj_other);
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return origin_proj_min;
        }
        Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        t = max(static_cast<Real>(0), t);
        t_other = max(static_cast<Real>(0), t_other);
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = other.origin + other.direction * t_other;
        return min(origin_proj_min, p1.distance(p2));
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

    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = max(static_cast<Real>(0), dir.dot(direction));
        return origin + direction * t;
    }
};

template <typename Real>
Line3<Real> Line3<Real>::from_ray(const Ray3<Real>& ray)
{
    return { ray.origin, ray.direction };
}

}

#endif