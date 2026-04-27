/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_SEGMENT3_HPP
#define NNM_GEOM3_SEGMENT3_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>

namespace nnm {

template <typename Real>
class Segment3 {
public:

    /**
     * Start position of the line segment.
     */
    Point3<Real> start;

    /**
     * End position of the line segment.
     */
    Point3<Real> end;

    /**
     * Default initialize to start from the origin and end at one unit away in the positive x-axis.
     */
    // tested
    constexpr Segment3()
        : start { Point3<Real>::zero() }
        , end { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) }
    {
    }

    /**
     * Initialize with start and end position.
     * @param start Start position.
     * @param end End position.
     */
    // tested
    constexpr Segment3(const Point3<Real>& start, const Point3<Real>& end)
        : start { start }
        , end { end }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other line segment.
     */
    // tested
    template <typename Other>
    explicit constexpr Segment3(const Segment3<Other>& other)
        : start { other.start }
        , end { other.end }
    {
    }

    // TODO: test
    [[nodiscard]] constexpr bool degenerate() const
    {
        return start.approx_equal(end);
    }

    /**
     * If start and end points are equal, returns the point that represents the degenerate line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!start.approx_equal(end)) {
            return std::nullopt;
        }
        return start;
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Point3<Real>& point) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> diff = start.direction_unnormalized(point);
        return dir.parallel(diff);
    }

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line3<Real>& line) const;

    /**
     * Determine if collinear with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray3<Real>& ray) const;

    /**
     * Determine if collinear with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> diff = start.direction_unnormalized(other.start);
        return dir.parallel(other.direction_unnormalized()) && dir.parallel(diff);
    }

    /**
     * Determine if coplanar with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const;

    /**
     * Determine if coplanar with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Ray3<Real>& ray) const;

    /**
     * Determine if coplanar with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> diff = start.direction_unnormalized(other.start);
        const Vector3<Real> dir_cross = dir.cross(other.direction_unnormalized());
        return diff.perpendicular(dir_cross);
    }

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
     * Determine if contains/intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        const Vector3<Real> diff1 = point - start;
        const Vector3<Real> diff2 = end - start;
        if (!diff1.cross(diff2).approx_zero()) {
            return false;
        }
        const Real dot = diff1.dot(diff2);
        const Real length_sqrd = diff2.dot(diff2);
        return approx_greater_equal_zero(dot) && approx_less_equal(dot, length_sqrd);
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        if (std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
            return degen_point->distance_sqrd(point);
        }
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> diff = point - start;
        const Real t = diff.dot(dir) / dir.dot(dir);
        if (approx_less_zero(t)) {
            return diff.length_sqrd();
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return (point - end).length_sqrd();
        }
        const Point3<Real> proj = start + dir * t;
        return (point - proj).length_sqrd();
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
     * Closest distance squared to another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3& other) const
    {
        if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
            return other.distance_sqrd(*degen_point);
        }
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.start - start;
        if (approx_zero(dir_cross_len)) {
            const Real d1 = other.distance_sqrd(start);
            const Real d2 = other.distance_sqrd(end);
            const Real d3 = distance_sqrd(other.start);
            const Real d4 = distance_sqrd(other.end);
            return min(d1, d2, d3, d4);
        }
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len;
        if (approx_less_zero(t)) {
            return other.distance_sqrd(start);
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return other.distance_sqrd(end);
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len;
        if (approx_less_zero(t_other)) {
            return distance_sqrd(other.start);
        }
        if (approx_greater(t_other, static_cast<Real>(1))) {
            return distance_sqrd(other.end);
        }
        const Point3<Real> p1 = start + dir * t;
        const Point3<Real> p2 = other.start + dir_other * t_other;
        return p1.distance_sqrd(p2);
    }

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
     * Closest distance to a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Closest distance to another line segment. Zero if intersects.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3& other) const
    {
        return sqrt(distance_sqrd(other));
    }

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
     * Non-normalized direction from the start position to the end position.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> direction_unnormalized() const
    {
        return end - start;
    }

    /**
     * Normalized direction from the start position to the end position.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector3<Real> direction() const
    {
        return direction_unnormalized().normalize();
    }

    /**
     * Determine if parallel to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const;

    /**
     * Determine if parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if parallel to another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment3& other) const
    {
        const Vector3<Real> proj = direction_unnormalized().cross(other.direction_unnormalized());
        return proj.approx_zero();
    }

    /**
     * Determine if perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const;

    /**
     * Determine if perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if perpendicular to another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment3& other) const
    {
        const Real proj = direction_unnormalized().dot(other.direction_unnormalized());
        return approx_zero(proj);
    }

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
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Ray3<Real>& ray) const;

    /**
     * Intersection point with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3& other) const
    {
        if (other.start.approx_equal(other.end)) {
            return contains(other.start);
        }
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return contains(other.start) || contains(other.end) || other.contains(start) || other.contains(end);
        }
        const Vector3<Real> diff = other.start - start;
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return false;
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other) || approx_greater(t_other, static_cast<Real>(1))) {
            return false;
        }
        const Point3<Real> p = start.lerp(end, t);
        const Point3<Real> p_other = other.start.lerp(other.end, t_other);
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with another line segment.
     * @param other Other line segment.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.start - start;
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other) || approx_greater(t_other, static_cast<Real>(1))) {
            return std::nullopt;
        }
        const Point3<Real> p = start.lerp(end, t);
        if (const Point3<Real> p_other = other.start.lerp(other.end, t_other); !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Plane<Real>& plane) const;

    /**
     * Project a point on the line segment.
     * @param point Point.
     * @return Resulting projected point.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> project(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - start;
        const Vector3<Real> dir = direction_unnormalized();
        const Real t = clamp(diff.dot(dir) / dir.length_sqrd(), static_cast<Real>(0), static_cast<Real>(1));
        return start.lerp(end, t);
    }

    /**
     * Squared length.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(end.x - start.x) + sqrd(end.y - start.y) + sqrd(end.z - start.z);
    }

    /**
     * Length.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    /**
     * Midpoint.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> midpoint() const
    {
        return Point3<Real>::from_vector((start.to_vector() + end.to_vector()) / static_cast<Real>(2));
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 translate(const Vector3<Real>& offset) const
    {
        return { start.translate(offset), end.translate(offset) };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 scale_at(const Point3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { start.scale_at(scale_origin, factor), end.scale_at(scale_origin, factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 scale(const Vector3<Real>& factor) const
    {
        return { start.scale(factor), end.scale(factor) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param rotate_origin Rotate origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment3 rotate_axis_angle_at(
        const Point3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { start.rotate_axis_angle_at(rotate_origin, axis, angle),
                 end.rotate_axis_angle_at(rotate_origin, axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { start.rotate_axis_angle(axis, angle), end.rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotate origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 rotate_quaternion_at(
        const Point3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { start.rotate_quaternion_at(rotate_origin, quaternion),
                 end.rotate_quaternion_at(rotate_origin, quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { start.rotate_quaternion(quaternion), end.rotate_quaternion(quaternion) };
    }

    /**
     * Shear about an origin along the x-axis.
     * @param shear_origin Shear origin.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_x_at(
        const Point3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { start.shear_x_at(shear_origin, factor_y, factor_z), end.shear_x_at(shear_origin, factor_y, factor_z) };
    }

    /**
     * Shear about the global origin along the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return { start.shear_x(factor_y, factor_z), end.shear_x(factor_y, factor_z) };
    }

    /**
     * Shear about an origin along the y-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_y_at(
        const Point3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { start.shear_y_at(shear_origin, factor_x, factor_z), end.shear_y_at(shear_origin, factor_x, factor_z) };
    }

    /**
     * Shear about the global origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { start.shear_y(factor_x, factor_z), end.shear_y(factor_x, factor_z) };
    }

    /**
     * Shear about an origin along the z-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_z_at(
        const Point3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { start.shear_z_at(shear_origin, factor_x, factor_y), end.shear_z_at(shear_origin, factor_x, factor_y) };
    }

    /**
     * Shear about the global origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { start.shear_z(factor_x, factor_y), end.shear_z(factor_x, factor_y) };
    }

    /**
     * Determine if coincident with another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Segment3& other) const
    {
        return (start.approx_equal(other.start) && end.approx_equal(other.end))
            || (start.approx_equal(other.end) && end.approx_equal(other.start));
    }

    /**
     * Determine if both start and end are approximately equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Segment3& other) const
    {
        return start.approx_equal(other.start) && end.approx_equal(other.end);
    }

    /**
     * Determine if start and end are exactly equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Segment3& other) const
    {
        return start == other.start && end == other.end;
    }

    /**
     * Determine if start and end are not exactly equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Segment3& other) const
    {
        return start != other.start || end != other.end;
    }

    /**
     * Lexicographical comparison in the order of start then end.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Segment3& other) const
    {
        if (start != other.start) {
            return start < other.start;
        }
        return end < other.end;
    }
};

} // namespace nnm

#endif
