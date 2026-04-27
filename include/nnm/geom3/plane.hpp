/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_PLANE_HPP
#define NNM_GEOM3_PLANE_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/line3.hpp>

namespace nnm {

template <typename Real>
class Plane {
public:

    /**
     * Origin.
     */
    Point3<Real> origin;

    /**
     * Normalized normal.
     */
    Vector3<Real> normal;

    /**
     * Default initialize with a zero origin and normal in the direction of the positive x-axis.
     */
    // tested
    constexpr Plane()
        : origin { Point3<Real>::zero() }
        , normal { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin and normalized normal. No normalization is performed.
     * @param origin Origin.
     * @param normal Normalized normal.
     */
    // tested
    constexpr Plane(const Point3<Real>& origin, const Vector3<Real>& normal)
        : origin { origin }
        , normal { normal }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other plane.
     */
    // tested
    template <typename Other>
    explicit constexpr Plane(const Plane<Other>& other)
        : origin { other.origin }
        , normal { other.normal }
    {
    }

    /**
     * Plane that intersects all given points. Does not check for collinearity.
     * @param point1 First point.
     * @param point2 Second point.
     * @param point3 Third point.
     * @return Result.
     */
    // tested
    static Plane from_points_unchecked(
        const Point3<Real>& point1, const Point3<Real>& point2, const Point3<Real>& point3)
    {
        const Vector3<Real> dir12 = point2 - point1;
        const Vector3<Real> dir13 = point3 - point1;
        const Vector3<Real> normal = dir12.cross(dir13).normalize();
        return { point1, normal };
    }

    /**
     * Plane that intersects all given points. Checks for collinearity.
     * @param point1 First point.
     * @param point2 Second point.
     * @param point3 Third point.
     * @return Result.
     */
    // tested
    static std::optional<Plane> from_points(
        const Point3<Real>& point1, const Point3<Real>& point2, const Point3<Real>& point3)
    {
        const Vector3<Real> dir12 = point2 - point1;
        const Vector3<Real> dir13 = point3 - point1;
        const Vector3<Real> cross = dir12.cross(dir13);
        if (nnm::approx_equal(cross.length(), static_cast<Real>(0))) {
            return std::nullopt;
        }
        return Plane { point1, cross.normalize() };
    }

    /**
     * A plane that is coplanar to a triangle. Does not check if the triangle collinear.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    static Plane from_triangle_unchecked(const Triangle3<Real>& triangle);

    /**
     * A plane that is coplanar to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    static std::optional<Plane> from_triangle(const Triangle3<Real>& triangle);

    // TODO: test
    static Plane from_rectangle(const Rectangle3<Real>& rectangle);

    /**
     * Plane that spans the x and y axes.
     * @return Result.
     */
    // tested
    static constexpr Plane xy()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_z() };
    }

    /**
     * Plane that spans the x and y axes and is offset along the z-axis.
     * @param z_offset Z-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Plane xy_offset(const float z_offset)
    {
        return xy().translate({ static_cast<Real>(0), static_cast<Real>(0), z_offset });
    }

    /**
     * Plane that spans the x and z axes.
     * @return Result.
     */
    // tested
    static constexpr Plane xz()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    /**
     * Plane that spans the x and z axes and is offset along the y-axis.
     * @param y_offset Y-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Plane xz_offset(const float y_offset)
    {
        return xz().translate({ static_cast<Real>(0), y_offset, static_cast<Real>(0) });
    }

    /**
     * Plane that spans the y and z axes.
     * @return Result.
     */
    // tested
    static constexpr Plane yz()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    /**
     * Plane that spans the y and z axes and is offset from the x-axis.
     * @param x_offset X-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Plane yz_offset(const float x_offset)
    {
        return yz().translate({ x_offset, static_cast<Real>(0), static_cast<Real>(0) });
    }

    /**
     * Normalize the normal.
     * @return Result.
     */
    // tested
    [[nodiscard]] Plane normalize() const
    {
        return { origin, normal.normalize() };
    }

    /**
     * Determine if coplanar with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const;

    /**
     * Determine if coplanar with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Ray3<Real>& ray) const;

    /**
     * Determine if coplanar with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with another plane.
     * @param other Other plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Plane& other) const
    {
        return contains(other.origin) && normal.parallel(other.normal);
    }

    /**
     * Determine if coplanar with triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if plane contains/intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        const Real d = origin.to_vector().dot(normal);
        const Real proj = point.to_vector().dot(normal);
        return nnm::approx_equal(d, proj);
    }

    [[nodiscard]] constexpr Real signed_distance(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        return diff.dot(normal);
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        return sqrd(signed_distance(point));
    }

    /**
     * Closest distance squared to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Line3<Real>& line) const;

    /**
     * Closest distance squared to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Ray3<Real>& ray) const;

    /**
     * Closest distance squared to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3<Real>& segment) const;

    /**
     * Closest distance squared to another plane.
     * @param other Other plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Plane& other) const
    {
        if (!parallel(other)) {
            return static_cast<Real>(0);
        }
        return distance_sqrd(other.origin);
    }

    /**
     * Closest distance squared to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance squared to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance squared to an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const AlignedBox<Real>& box) const;

    /**
     * Closest distance squared to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Box<Real>& box) const;

    /**
     * Determine the closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Point3<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    /**
     * Determine the closest distance with a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Line3<Real>& line) const;

    /**
     * Determine the closest distance with a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Ray3<Real>& ray) const;

    /**
     * Determine the closest distance with a line segment. Zero if intersects.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Segment3<Real>& segment) const;

    /**
     * Determine the closest distance with another plane. Zero if intersects.
     * @param other Other plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane& other) const
    {
        if (!parallel(other)) {
            return static_cast<Real>(0);
        }
        return distance(other.origin);
    }

    /**
     * Closest distance to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance to a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Sphere<Real>& sphere) const;

    /**
     * Closest distance to an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const AlignedBox<Real>& box) const;

    /**
     * Closest distance to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Box<Real>& box) const;

    /**
     * Determine if parallel with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const;

    /**
     * Determine if parallel with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if parallel with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment3<Real>& segment) const;

    /**
     * Determine if parallel with another plane.
     * @param other Other plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Plane& other) const
    {
        return normal.parallel(other.normal);
    }

    /**
     * Determine if perpendicular with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const;

    /**
     * Determine if perpendicular with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if perpendicular with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment3<Real>& segment) const;

    /**
     * Determine if perpendicular with another plane.
     * @param other Other plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Plane& other) const
    {
        return normal.perpendicular(other.normal);
    }

    /**
     * Determine if intersects with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Intersection point with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Line3<Real>& line) const;

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Ray3<Real>& ray) const;

    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Segment3<Real>& segment) const;

    // tested
    [[nodiscard]] constexpr bool intersects(const Plane& other) const
    {
        if (contains(other.origin)) {
            return true;
        }
        const Real dot = normal.dot(other.normal);
        return !nnm::approx_equal(dot, static_cast<Real>(1)) && !nnm::approx_equal(dot, static_cast<Real>(-1));
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Triangle3<Real>& triangle) const;

    // tested
    [[nodiscard]] std::optional<Line3<Real>> intersection(const Plane& other) const;

    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Plane& other1, const Plane& other2) const
    {
        const Matrix3<Real> a { { normal.x, normal.y, normal.z },
                                { other1.normal.x, other1.normal.y, other1.normal.z },
                                { other2.normal.x, other2.normal.y, other2.normal.z } };
        if (const Real det = a.determinant(); approx_zero(det)) {
            return std::nullopt;
        }
        const Vector3<Real> b { normal.dot(origin.to_vector()),
                                other1.normal.dot(other1.origin.to_vector()),
                                other2.normal.dot(other2.origin.to_vector()) };
        const Matrix3<Real> a_inv = a.unchecked_inverse();
        const Point3<Real> point { a_inv.at(0).dot(b), a_inv.at(1).dot(b), a_inv.at(2).dot(b) };
        return point;
    }

    // TODO: test
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Triangle3<Real>& triangle) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Rectangle3<Real>& rectangle) const;

    // tested
    [[nodiscard]] constexpr Point3<Real> project(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        const Real dist = diff.dot(normal);
        return point - normal * dist;
    }

    // tested
    [[nodiscard]] constexpr Plane translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), normal };
    }

    // tested
    [[nodiscard]] Plane scale_at(const Point3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), normal.scale(factor).normalize() };
    }

    // tested
    [[nodiscard]] Plane scale(const Vector3<Real>& factor) const
    {
        return { origin.scale(factor), normal.scale(factor).normalize() };
    }

    // tested
    [[nodiscard]] Plane rotate_axis_angle_at(
        const Point3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 normal.rotate_axis_angle(axis, angle).normalize() };
    }

    // tested
    [[nodiscard]] Plane rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), normal.rotate_axis_angle(axis, angle).normalize() };
    }

    // tested
    [[nodiscard]] constexpr Plane rotate_quaternion_at(
        const Point3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion), normal.rotate_quaternion(quaternion) };
    }

    // tested
    [[nodiscard]] constexpr Plane rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), normal.rotate_quaternion(quaternion) };
    }

    // tested
    [[nodiscard]] Plane shear_x_at(const Point3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_x(const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x(factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_y_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_y(const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y(factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_z_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z_at(shear_origin, factor_x, factor_y), normal.shear_z(factor_x, factor_y).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_z(const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z(factor_x, factor_y), normal.shear_z(factor_x, factor_y).normalize() };
    }

    // tested
    [[nodiscard]] constexpr bool approx_equal(const Plane& other) const
    {
        return origin.approx_equal(other.origin) && normal.approx_equal(other.normal);
    }

    // tested
    [[nodiscard]] constexpr bool operator==(const Plane& other) const
    {
        return origin == other.origin && normal == other.normal;
    }

    // tested
    [[nodiscard]] constexpr bool operator!=(const Plane& other) const
    {
        return origin != other.origin || normal != other.normal;
    }

    // tested
    [[nodiscard]] constexpr bool operator<(const Plane& other) const
    {
        if (origin != other.origin) {
            return origin < other.origin;
        }
        return normal < other.normal;
    }
};

} // namespace nnm

#endif
