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
class Line2 {
public:
    Real a;
    Real b;
    Real c;

    constexpr Line2()
        : a { static_cast<Real>(0) }
        , b { static_cast<Real>(0) }
        , c { static_cast<Real>(0) }
    {
    }

    constexpr Line2(const Real a, const Real b, const Real c)
        : a { a }
        , b { b }
        , c { c }
    {
    }

    static Line2 from_point_direction(const Vector2<Real>& point, const Vector2<Real>& direction)
    {
        const Vector2<Real> norm_dir = direction.normalize();
        const Line2 line { -norm_dir.y, norm_dir.x, -(-norm_dir.y * point.x + norm_dir.x * point.y) };
        return line.normalize();
    }

    static Line2 from_point_parallel(const Vector2<Real>& point, const Line2& line)
    {
        const Line2 result { line.a, line.b, -(line.a * point.x + line.b * point.y) };
        return result.normalize();
    }

    static Line2 from_points(const Vector2<Real>& point1, const Vector2<Real>& point2)
    {
        const Line2 line { point2.y - point1.y, point1.x - point2.x, point2.x * point1.y - point1.x * point2.y };
        return line.normalize();
    }

    static Line2 from_point_perpendicular(const Vector2<Real>& point, const Line2& line)
    {
        const Line2 result { line.b, -line.a, -(line.b * point.x + -line.a * point.y) };
        return result.normalize();
    }

    [[nodiscard]] Line2 normalize() const
    {
        const Real norm = sqrt(sqrd(a) + sqrd(b));
        if (norm != static_cast<Real>(0)) {
            return { a / norm, b / norm, c / norm };
        }
        return { a, b, c };
    }

    [[nodiscard]] constexpr bool approx_contains(const Vector2<Real>& point) const
    {
        return approx_zero(a * point.x + b * point.y + c);
    }

    [[nodiscard]] constexpr Real distance(const Vector2<Real>& point) const
    {
        return abs(a * point.x + b * point.y + c);
    }

    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
    {
        return a * point.x + b * point.y + c;
    }

    [[nodiscard]] constexpr bool approx_parallel(const Line2& other) const
    {
        return approx_zero(a * other.b - b * other.a);
    }

    [[nodiscard]] constexpr Vector2<Real> unchecked_intersection(const Line2& other) const
    {
        const Real det = a * other.b - other.a * b;
        const Real x = (other.b * c - b * other.c) / det;
        const Real y = (a * other.c - other.a * c) / det;
        return { x, y };
    }

    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2& other) const
    {
        const Real det = a * other.b - other.a * b;
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real x = (other.b * c - b * other.c) / det;
        const Real y = (a * other.c - other.a * c) / det;
        return { x, y };
    }

    [[nodiscard]] constexpr Vector2<Real> project(const Vector2<Real>& point) const
    {
        Real t = (a * point.x + b * point.y + c) / (sqrd(a) + sqrd(b));
        return { point.x - a * t, point.y - b * t };
    }

    [[nodiscard]] constexpr Real unchecked_slope() const
    {
        return -a / b;
    }

    [[nodiscard]] constexpr std::optional<Real> slope() const
    {
        if (b == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_slope();
    }

    [[nodiscard]] constexpr Real unchecked_intercept_x() const
    {
        return -c / a;
    }

    [[nodiscard]] constexpr std::optional<Real> intercept_x() const
    {
        if (a == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_intercept_x();
    }

    [[nodiscard]] Real unchecked_intercept_y() const
    {
        return -c / b;
    }

    [[nodiscard]] constexpr std::optional<Real> intercept_y() const
    {
        if (b == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_intercept_y();
    }

    [[nodiscard]] constexpr bool horizontal() const
    {
        return a == static_cast<Real>(0);
    }

    [[nodiscard]] constexpr bool approx_horizontal() const
    {
        return approx_zero(a);
    }

    [[nodiscard]] constexpr bool vertical() const
    {
        return b == static_cast<Real>(0);
    }

    [[nodiscard]] constexpr bool approx_vertical() const
    {
        return approx_zero(b);
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