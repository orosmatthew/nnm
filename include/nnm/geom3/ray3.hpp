/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_RAY3_HPP
#define NNM_GEOM3_RAY3_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>

namespace nnm {

template <typename Real>
class Ray3 {
public:

    /**
     * Origin.
     */
    Point3<Real> origin;

    /**
     * Normalized direction.
     */
    Vector3<Real> direction;

    /**
     * Default initialize with zero origin and in the direction of the positive x-axis.
     */
    // tested
    constexpr Ray3()
        : origin { Point3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin and direction. No normalization is done on the direction.
     * @param origin Origin.
     * @param direction Direction.
     */
    // tested
    constexpr Ray3(const Point3<Real>& origin, const Vector3<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    /**
     * Cast from another type.
     * @tparam Other Other type.
     * @param other Other ray.
     */
    // tested
    template <typename Other>
    explicit constexpr Ray3(const Ray3<Other>& other)
        : origin { other.origin }
        , direction { other.direction }
    {
    }

    /**
     * Ray from a point in the direction of another point.
     * @param from Origin.
     * @param to Point in the direction of the ray.
     * @return Result.
     */
    // tested
    static Ray3 from_point_to_point(const Point3<Real>& from, const Point3<Real>& to)
    {
        return { from, from.direction(to) };
    }

    /**
     * Determine if ray is valid.
     * A ray is valid if its direction vector is non-zero and normalized.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        return nnm::approx_equal(direction.length_sqrd(), static_cast<Real>(1));
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Point3<Real>& point) const;

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line3<Real>& line) const;

    /**
     * Determine if collinear with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray3& other) const;

    // TODO: test
    [[nodiscard]] constexpr bool collinear(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const;

    /**
     * Determine if coplanar with another ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Ray3& ray) const;

    /**
     * Determine if coplanar with line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Plane<Real>& plane) const;

    /**
     * Determine if coplanar with triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if coplanar with a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if ray intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        const Point3<Real> proj = project(point);
        return proj.approx_equal(point);
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        if (const Real t = diff.dot(direction); approx_less_zero(t)) {
            return origin.distance_sqrd(point);
        }
        return diff.cross(direction).length_sqrd();
    }

    /**
     * Closest distance squared to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Line3<Real>& line) const;

    /**
     * Closest distance squared to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.origin - origin;
        if (approx_zero(dir_cross_len)) {
            const Real d1 = distance_sqrd(other.origin);
            const Real d2 = other.distance_sqrd(origin);
            return min(d1, d2);
        }
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len;
        if (approx_less_zero(t)) {
            return other.distance_sqrd(origin);
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len;
        if (approx_less_zero(t_other)) {
            return distance_sqrd(other.origin);
        }
        const Point3<Real> p1 = origin + direction * t;
        const Point3<Real> p2 = other.origin + other.direction * t_other;
        return p1.distance_sqrd(p2);
    }

    /**
     * Closest distance squared to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3<Real>& segment) const;

    /**
     * Closest distance squared to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Plane<Real>& plane) const;

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
    [[nodiscard]] constexpr Real distance_sqrd(const AlignedBox<Real>& box);

    /**
     * Closest distance squared to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Box<Real>& box);

    /**
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const;

    /**
     * Closest distance to another ray. Zero if intersects.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3& other) const
    {
        return sqrt(distance_sqrd(other));
    }

    /**
     * Closest distance to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    /**
     * Closest distance to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance to a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Sphere<Real>& sphere) const;

    /**
     * Closest distance to an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedBox<Real>& box) const;

    /**
     * Closest distance to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Box<Real>& box) const;

    /**
     * Determine if parallel to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const;

    /**
     * Determine if parallel to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if parallel to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment3<Real>& segment) const;

    /**
     * Determine if parallel with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Plane<Real>& plane) const;

    /**
     * Determine if parallel with a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Triangle3<Real>& triangle) const;

    /**
     * Determine if parallel with a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const;

    /**
     * Determine if perpendicular to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if perpendicular to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment3<Real>& segment) const;

    /**
     * Determine if perpendicular to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Plane<Real>& plane) const;

    /**
     * Determine if perpendicular to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Triangle3<Real>& triangle) const;

    /**
     * Determine if perpendicular to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Intersection point with a line.
     * @param line Line.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Line3<Real>& line) const;

    /**
     * Determine if intersects another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return other.contains(origin) || contains(other.origin);
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return false;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other)) {
            return false;
        }
        const Point3<Real> p = origin + direction * t;
        const Point3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Segment3<Real>& segment) const;

    /**
     * Intersection point with another ray.
     * @param other Other ray.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other)) {
            return std::nullopt;
        }
        const Point3<Real> p = origin + direction * t;
        if (const Point3<Real> p_other = other.origin + other.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Project point onto the ray.
     * @param point Point.
     * @return Resulting projected point.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> project(const Point3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = max(static_cast<Real>(0), dir.dot(direction));
        return origin + direction * t;
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Ray3 translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scaling origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 scale_at(const Point3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 scale(const Vector3<Real>& factor) const
    {
        return { origin.scale(factor), direction.scale(factor).normalize() };
    }

    /**
     * Rotate about an origin by an axis by an angle.
     * @param rotate_origin Rotation origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 rotate_axis_angle_at(
        const Point3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about the global origin by an axis by an angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 rotate_quaternion_at(const Point3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 direction.rotate_quaternion(quaternion).normalize() };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), direction.rotate_quaternion(quaternion).normalize() };
    }

    /**
     * Shear along the x-axis about an origin by y-axis and z-axis factors.
     * @param shear_origin Shear origin.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 shear_x_at(const Point3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z),
                 direction.shear_x(factor_y, factor_z).normalize() };
    }

    /**
     * Shear along the x-axis about the global origin by y-axis and z-axis factors.
     * @param angle_y Y-Axis factor.
     * @param angle_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return { origin.shear_x(angle_y, angle_z), direction.shear_x(angle_y, angle_z).normalize() };
    }

    /**
     * Shear along the y-axis about an origin by x-axis and z-axis factors.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return
     */
    // tested
    [[nodiscard]] Ray3 shear_y_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z),
                 direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear along the y-axis about the global origin by x-axis and z-axis factors.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y(factor_x, factor_z), direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear along the z-axis about an origin by x-axis and y-axis factors.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return
     */
    // tested
    [[nodiscard]] Ray3 shear_z_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z_at(shear_origin, factor_x, factor_y),
                 direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Shear along the z-axis about the global origin by x-axis and y-axis factors.
     * @param angle_x X-Axis factor.
     * @param angle_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z(angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    /**
     * Determine if both origin and direction are approximately equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Ray3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    /**
     * Determine if both origin and direction are exactly equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Ray3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine if either origin or direction are not exactly equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Ray3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical comparison in the order of origin then direction.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Ray3& other) const
    {
        if (origin == other.origin) {
            return direction < other.direction;
        }
        return origin < other.origin;
    }
};

} // namespace nnm

#endif
