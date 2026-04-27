/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_SPHERE_HPP
#define NNM_GEOM3_SPHERE_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>

namespace nnm {

template <typename Real>
class Sphere {
public:

    /**
     * Center
     */
    Point3<Real> center;

    /**
     * Radius
     */
    Real radius;

    /**
     * Default initialize at the global origin and a radius of 1.
     */
    // tested
    constexpr Sphere()
        : center { Point3<Real>::zero() }
        , radius { static_cast<Real>(1) }
    {
    }

    /**
     * Initialize with center and radius.
     * @param center Center.
     * @param radius Radius.
     */
    // tested
    constexpr Sphere(const Point3<Real>& center, const Real radius)
        : center { center }
        , radius { radius }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other sphere.
     */
    template <typename Other>
    explicit constexpr Sphere(const Sphere<Other>& other)
        : center { other.center }
        , radius { static_cast<Real>(other.radius) }
    {
    }

    /**
     * From center and a point intersecting the surface.
     * @param center Center.
     * @param point Point that lies on the surface of the sphere.
     * @return Result.
     */
    // tested
    static Sphere from_center_surface_point(const Point3<Real>& center, const Point3<Real>& point)
    {
        return Sphere(center, center.distance(point));
    }

    /**
     * If radius is zero, returns the point representing the degenerate sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!approx_zero(radius)) {
            return std::nullopt;
        }
        return center;
    }

    /**
     * Surface area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real surface_area() const
    {
        return static_cast<Real>(4) * pi<Real>() * sqrd(radius);
    }

    /**
     * Volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real volume() const
    {
        const Real radius_cubed = radius * radius * radius;
        return static_cast<Real>(4) / static_cast<Real>(3) * pi<Real>() * radius_cubed;
    }

    /**
     * Diameter.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    /**
     * Determines if a point is contained inside the sphere.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        return approx_less_equal(center.distance_sqrd(point), sqrd(radius));
    }

    /**
     * Closest signed-distance to a point from the surface of the sphere.
     * Positive if outside and negative if inside the sphere.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real signed_distance(const Point3<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    /**
     * Closest distance to a point. Zero if point is inside the sphere.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    /**
     * Closest distance to a line. Zero if intersects or is inside the sphere.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const;

    /**
     * Closest distance to a ray. Zero if intersects or is inside the sphere.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Closest distance to a line segment. Zero if intersects or is inside the sphere.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to a plane. Zero if intersects.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    /**
     * Closest distance to a triangle. Zero if intersects or if contains triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to another sphere. Zero if intersects or is inside this sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Sphere& other) const
    {
        const Real dist = center.distance(other.center);
        const Real radius_sum = radius + other.radius;
        return max(static_cast<Real>(0), dist - radius_sum);
    }

    /**
     * Point on the surface of the sphere in the given direction from the center.
     * @param dir Normalized direction from the sphere's center. No normalization is done.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> point_at(const Vector3<Real>& dir) const
    {
        return center.translate(dir * radius);
    }

    /**
     * Normal of the surface of the sphere in the given direction from the center.
     * @param dir Normalized direction from the sphere's center. No normalization is done.
     * @return Result.
     */
    // tested
    // ReSharper disable once CppMemberFunctionMayBeStatic
    [[nodiscard]] constexpr Vector3<Real> normal_at(const Vector3<Real>& dir) const
    {
        return dir;
    }

    /**
     * Determine if intersects with a line. Being inside the circle is considered an intersection.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Intersection points with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> surface_intersections(const Line3<Real>& line) const;

    /**
     * Determine if intersects with a ray. Being inside the sphere is considered an intersection.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection points with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> surface_intersections(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects with a line segment. Being inside the sphere is considered an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment3<Real>& segment) const;

    /**
     * Intersection points with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> surface_intersections(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects with another sphere. Being inside a sphere is considered an intersection.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Sphere& other) const
    {
        return approx_less(center.distance_sqrd(other.center), sqrd(radius + other.radius));
    }

    /**
     * Intersection depth with another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> intersect_depth(const Sphere& other) const
    {
        const Vector3<Real> diff = other.center - center;
        const Real radius_sum = radius + other.radius;
        if (diff.approx_zero()) {
            return Vector3<Real>::axis_x() * radius_sum;
        }
        const Real dist_sqrd = diff.length_sqrd();
        const Real dist = sqrt(dist_sqrd);
        const Real depth = radius_sum - dist;
        if (approx_less_equal_zero(depth)) {
            return std::nullopt;
        }
        return diff.normalize() * depth;
    }

    /**
     * Determine if tangent to line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Line3<Real>& line) const;

    /**
     * Determine if tangent to ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Ray3<Real>& ray) const;

    /**
     * Determine if tangent to line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Segment3<Real>& segment) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Sphere translate(const Vector3<Real>& offset) const
    {
        return { center.translate(offset), radius };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param rotate_origin Rotation origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Sphere rotate_axis_angle_at(
        const Point3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { center.rotate_axis_angle_at(rotate_origin, axis, angle), radius };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Sphere rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { center.rotate_axis_angle(axis, angle), radius };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Sphere rotate_quaternion_at(
        const Point3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion_at(rotate_origin, quaternion), radius };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Sphere rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion(quaternion), radius };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Sphere scale_at(const Point3<Real>& scale_origin, const Real factor) const
    {
        return { center.scale_at(scale_origin, Vector3<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Sphere scale(const Real factor) const
    {
        return { center.scale(Vector3<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Determine if all members are approximately equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Sphere& other) const
    {
        return center.approx_equal(other.center) && nnm::approx_equal(radius, other.radius);
    }

    /**
     * Determine if all members are exactly equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Sphere& other) const
    {
        return center == other.center && radius == other.radius;
    }

    /**
     * Determine if any members are not exactly equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Sphere& other) const
    {
        return center != other.center || radius != other.radius;
    }

    /**
     * Lexicographical comparison in the order of center then radius to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Sphere& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        return radius < other.radius;
    }
};

} // namespace nnm

#endif
