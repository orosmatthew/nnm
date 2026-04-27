/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_LINE3_HPP
#define NNM_GEOM3_LINE3_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/ray3.hpp>
#include <nnm/geom3/segment3.hpp>

namespace nnm {

template <typename Real>
class Line3 {
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
     * Default initialize with zero origin in the direction of the x-axis.
     */
    // tested
    constexpr Line3()
        : origin { Point3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin that the line intersects and a direction. The direction should be normalized.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Line3(const Point3<Real>& origin, const Vector3<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    /**
     * Cast from another type.
     * @tparam Other Other type.
     * @param other Other line.
     */
    // tested
    template <typename Other>
    explicit constexpr Line3(const Line3<Other>& other)
        : origin { other.origin }
        , direction { other.direction }
    {
    }

    /**
     * Line that intersects two points. Null if points are coincident.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    // tested
    static std::optional<Line3> from_points(const Point3<Real>& point1, const Point3<Real>& point2)
    {
        if (point1.approx_equal(point2)) {
            return std::nullopt;
        }
        return Line3 { point1, point1.direction(point2) };
    }

    /**
     * Extends a line segment to an infinite line. Null if segment is degenerate.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    static std::optional<Line3> from_segment(const Segment3<Real>& segment)
    {
        if (segment.start.approx_equal(segment.end)) {
            return std::nullopt;
        }
        return Line3 { segment.start, segment.start.direction(segment.end) };
    }

    /**
     * Line that is an extension from a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    static constexpr Line3 from_ray(const Ray3<Real>& ray)
    {
        return { ray.origin, ray.direction };
    }

    /**
     * Line that intersects the origin and is in the direction of the x-axis.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_x()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    /**
     * Line that intersects the origin and is in the direction of the y-axis.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_y()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    /**
     * Line that intersects the origin and is in the direction of the z-axis.
     * @return
     */
    // tested
    static constexpr Line3 axis_z()
    {
        return { Point3<Real>::zero(), Vector3<Real>::axis_z() };
    }

    /**
     * Line that is in the direction of the x-axis and is offset from the y and z axes.
     * @param offset_y Y-Axis offset.
     * @param offset_z Z-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_x_offset(const Real offset_y, const Real offset_z)
    {
        return { { static_cast<Real>(0), offset_y, offset_z }, Vector3<Real>::axis_x() };
    }

    /**
     * Line that is in the direction of the y-axis and is offset from the x and z axes.
     * @param offset_x X-Axis offset.
     * @param offset_z Z-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_y_offset(const Real offset_x, const Real offset_z)
    {
        return { { offset_x, static_cast<Real>(0), offset_z }, Vector3<Real>::axis_y() };
    }

    /**
     * Line that is in the direction of the z-axis and is offset from the x and y axes.
     * @param offset_x X-Axis offset.
     * @param offset_y Y-Axis offset.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_z_offset(const Real offset_x, const Real offset_y)
    {
        return { { offset_x, offset_y, static_cast<Real>(0) }, Vector3<Real>::axis_z() };
    }

    /**
     * Determine if line is valid.
     * A line is valid if its direction vector is non-zero and normalized.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        return nnm::approx_equal(direction.length_sqrd(), static_cast<Real>(1));
    }

    /**
     * Create a line that is parallel to this line and intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line3 parallel_containing(const Point3<Real>& point) const
    {
        return { point, direction };
    }

    /**
     * Create a line that is perpendicular to this line and intersects a point.
     * Both direction and -direction are valid for the resulting line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line3 arbitrary_perpendicular_containing(const Point3<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
    }

    /**
     * Create a line that is perpendicular to this line and parallel to a plane.
     * Both direction and -direction are valid for the resulting line.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 perpendicular_plane_parallel(const Plane<Real>& plane) const;

    /**
     * Determine if collinear with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray3<Real>& ray) const;

    /**
     * Determine if collinear with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3& other) const
    {
        const Vector3<Real> diff = origin - other.origin;
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        return diff.perpendicular(dir_cross);
    }

    /**
     * Determine if coplanar with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Ray3<Real>& ray) const;

    /**
     * Determine if coplanar with line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Segment3<Real>& segment) const;

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
    [[nodiscard]] constexpr bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if coplanar with a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        const Point3<Real> proj = origin + direction * t;
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
        return (point - origin).cross(direction).length_sqrd();
    }

    /**
     * Closest distance squared to another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        if (dir_cross.approx_zero()) {
            return distance_sqrd(other.origin);
        }
        const Vector3<Real> diff = origin - other.origin;
        return sqrd(dir_cross.dot(diff)) / dir_cross.length_sqrd();
    }

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
    [[nodiscard]] constexpr Real distance_sqrd(const AlignedBox<Real>& box) const;

    /**
     * Closest distance squared to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Box<Real>& box) const;

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to another line. Zero if they intersect.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3& other) const
    {
        return sqrt(distance_sqrd(other));
    }

    /**
     * Closest distance to a ray. Zero if they intersect.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Closest distance to a line segment. Zero if they intersect.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to a plane. Zero if they intersect.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    /**
     * Closest distance to a triangle. Zero if they intersect.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to a rectangle. Zero if they intersect.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance to a sphere. Zero if they intersect.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Sphere<Real>& sphere) const;

    /**
     * Closest distance to an aligned box. Zero if intersecting.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedBox<Real>& box) const;

    /**
     * Closest distance to box. Zero if intersecting.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Box<Real>& box) const;

    /**
     * Determine if parallel with another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3& other) const
    {
        return direction.parallel(other.direction);
    }

    /**
     * Determine if parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if parallel to line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment3<Real>& segment) const;

    /**
     * Determine if parallel to plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Plane<Real>& plane) const;

    /**
     * Determine if parallel to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Triangle3<Real>& triangle) const;

    /**
     * Determine if parallel to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if perpendicular to another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const;

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
     * Determine if intersects another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return contains(other.origin);
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Point3<Real> p = origin + direction * t;
        const Point3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    /**
     * Determine if intersects a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    /**
     * Determine if intersects a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const;

    /**
     * Determine if intersects an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& box) const;

    /**
     * Determine if intersects a box.
     * @param box Box.
     * @return Results.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Box<Real>& box) const;

    /**
     * Determine if intersects a view frustum.
     * @param frustum View frustum.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Frustum<Real>& frustum) const;

    /**
     * Intersection point with another line.
     * @param other Other line.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Point3<Real> p = origin + direction * t;
        if (const Point3<Real> p_other = other.origin + other.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Ray3<Real>& ray) const;

    /**
     * Intersection point with segment. Null if collinear.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Segment3<Real>& segment) const;

    /**
     * Intersection point with plane. Null if coplanar.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Plane<Real>& plane) const;

    /**
     * Intersection point with triangle. Null if coplanar.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle. Null if coplanar.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Rectangle3<Real>& rectangle) const;

    /**
     * Surface intersections with sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Sphere<Real>& sphere) const;

    /**
     * Surface intersections with an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const AlignedBox<Real>& box) const;

    /**
     * Surface intersections with a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Box<Real>& box) const;

    /**
     * Surface intersections with view frustum.
     * @param frustum View frustum.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Frustum<Real>& frustum) const;

    /**
     * Project point on the line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> project(const Point3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        return origin + direction * t;
    }

    /**
     * Determine if coincident with another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Line3& other) const
    {
        if (!parallel(other)) {
            return false;
        }
        const Vector3<Real> diff = origin - other.origin;
        return diff.cross(other.direction).approx_zero();
    }

    /**
     * Determine if tangent to a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Sphere<Real>& sphere) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line3 translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param factor Scale factor.
     * @param scale_origin Scaling origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 scale(
        const Vector3<Real>& factor, const Point3<Real>& scale_origin = Point3<Real>::zero()) const
    {
        return { origin.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @param rotate_origin Rotate origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 rotate_axis_angle(
        const Vector3<Real>& axis, const Real angle, const Point3<Real>& rotate_origin = Point3<Real>::zero()) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param quaternion Quaternion.
     * @param rotate_origin Rotate origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 rotate_quaternion(
        const Quaternion<Real>& quaternion, const Point3<Real>& rotate_origin = Point3<Real>::zero()) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 direction.rotate_quaternion(quaternion).normalize() };
    }

    /**
     * Shear about an origin along the x-axis.
     * @param factor_y Y-Axis shear factor.
     * @param factor_z Z-Axis shear factor.
     * @param shear_origin Shear origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_x(
        const Real factor_y, const Real factor_z, const Point3<Real>& shear_origin = Point3<Real>::zero()) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z),
                 direction.shear_x(factor_y, factor_z).normalize() };
    }

    /**
     * Shear about an origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @param shear_origin Shear origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_y(
        const Real factor_x, const Real factor_z, const Point3<Real>& shear_origin = Point3<Real>::zero()) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z),
                 direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear about an origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @param shear_origin Shear origin. Defaults to global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_z(
        const Real factor_x, const Real factor_y, const Point3<Real>& shear_origin = Point3<Real>::zero()) const
    {
        return { origin.shear_z_at(shear_origin, factor_x, factor_y),
                 direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Determine if the origin and direction are approximately equal to another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool approx_equal(const Line3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    /**
     * Determine if origin and direction are exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool operator==(const Line3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine if either origin or direction are not exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool operator!=(const Line3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical comparison in the order of origin then direction.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool operator<(const Line3& other) const
    {
        if (origin == other.origin) {
            return direction < other.direction;
        }
        return origin < other.origin;
    }
};

} // namespace nnm

#endif
