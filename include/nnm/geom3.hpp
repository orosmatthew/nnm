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
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
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
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        if (!p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }
};

}

#endif