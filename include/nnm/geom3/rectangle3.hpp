/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_RECTANGLE3_HPP
#define NNM_GEOM3_RECTANGLE3_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/segment3.hpp>

namespace nnm {

template <typename Real>
class Rectangle3 {
public:

    /**
     * Center.
     */
    Point3<Real> center;

    /**
     * Vector spanning from the center towards one of the rectangle's dimensions edge.
     * Must be orthogonal to half_span_v.
     */
    Vector3<Real> half_span_u;

    /**
     * Vector spanning from the center towards one of the rectangle's dimensions edge.
     * Must be orthogonal to half_span_u.
     */
    Vector3<Real> half_span_v;

    /**
     * Default initialize with center at global origin size zero.
     */
    // tested
    constexpr Rectangle3()
        : center { Point3<Real>::zero() }
        , half_span_u { Vector3<Real>::zero() }
        , half_span_v { Vector3<Real>::zero() }
    {
    }

    /**
     * Initialize with center, half span u, and half span v.
     * @param center Center.
     * @param half_span_u First half span vector u.
     * @param half_span_v Second half span vector v.
     */
    // tested
    constexpr Rectangle3(const Point3<Real>& center, const Vector3<Real>& half_span_u, const Vector3<Real>& half_span_v)
        : center { center }
        , half_span_u { half_span_u }
        , half_span_v { half_span_v }
    {
    }

    /**
     * Initialize spanning the x and y axes with given x/y-axis sizes.
     * @param offset Offset from origin.
     * @param size_x Size along the x-axis.
     * @param size_y Size along the y-axis.
     * @return Result.
     */
    // tested
    constexpr static Rectangle3 from_xy_offset_size(const Point3<Real>& offset, const Real size_x, const Real size_y)
    {
        return { offset,
                 size_x / static_cast<Real>(2) * Vector3<Real>::axis_x(),
                 size_y / static_cast<Real>(2) * Vector3<Real>::axis_y() };
    }

    /**
     * Initialize spanning the x and z axes with given x/z-axis sizes.
     * @param offset Offset from origin.
     * @param size_x Size along the x-axis.
     * @param size_z Size along the z-axis.
     * @return Result.
     */
    // tested
    constexpr static Rectangle3 from_xz_offset_size(const Point3<Real>& offset, const Real size_x, const Real size_z)
    {
        return { offset,
                 size_x / static_cast<Real>(2) * Vector3<Real>::axis_x(),
                 size_z / static_cast<Real>(2) * Vector3<Real>::axis_z() };
    }

    /**
     * Initialize spanning the y and z axes with given y/z-axis sizes.
     * @param offset Offset from origin.
     * @param size_y Size along the y-axis.
     * @param size_z Size along the z-axis.
     * @return Result.
     */
    // tested
    constexpr static Rectangle3 from_yz_offset_size(const Point3<Real>& offset, const Real size_y, const Real size_z)
    {
        return { offset,
                 size_y / static_cast<Real>(2) * Vector3<Real>::axis_y(),
                 size_z / static_cast<Real>(2) * Vector3<Real>::axis_z() };
    }

    [[nodiscard]] constexpr bool degenerate() const
    {
        return half_span_v.approx_zero() || half_span_u.approx_zero();
    }

    /**
     * If either half-span is zero, returns the line segment that represents the degenerate rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Segment3<Real>> collapse_segment() const;

    /**
     * If both half-spans are zero, returns the point that represents the degenerate rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!half_span_u.approx_zero() || !half_span_v.approx_zero()) {
            return std::nullopt;
        }
        return center;
    }

    /**
     * Determine if valid. Validity is determined if half_span_u and half_span_v are orthogonal.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        return approx_zero(half_span_u.dot(half_span_v));
    }

    /**
     * Vertex from index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Rectangle3", index < 4);
        switch (index) {
        case 1:
            return center - half_span_u + half_span_v;
        case 2:
            return center + half_span_u - half_span_v;
        case 3:
            return center + half_span_u + half_span_v;
        default:
            return center - half_span_u - half_span_v;
        }
    }

    /**
     * Edge from index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const;

    /**
     * Size of the first dimension which is defined by the direction of half_span_u.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real size_u() const
    {
        return half_span_u.length() * static_cast<Real>(2);
    }

    /**
     * Size of the second dimension which is defined by the direction of half_span_v.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real size_v() const
    {
        return half_span_v.length() * static_cast<Real>(2);
    }

    /**
     * Area of one side of the rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real area() const
    {
        return size_u() * size_v();
    }

    /**
     * Combined length of all edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real perimeter() const
    {
        return static_cast<Real>(2) * size_u() + static_cast<Real>(2) * size_v();
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

    // TODO: test
    [[nodiscard]] constexpr bool coplanar(const Plane<Real>& plane) const;

    /**
     * Determine if contains a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const;

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - center;
        const Vector2<Real> local = { diff.dot(half_span_u), diff.dot(half_span_v) };
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        const Vector2<Real> local_clamped = local.clamp({ -u_dot, -v_dot }, { u_dot, v_dot });
        const Point3<Real> closest = center
            + (approx_zero(u_dot) ? static_cast<Real>(0) : local_clamped.x / u_dot) * half_span_u
            + (approx_zero(v_dot) ? static_cast<Real>(0) : local_clamped.y / v_dot) * half_span_v;
        return point.distance_sqrd(closest);
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
     * Closest distance squared to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Rectangle3& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = distance_sqrd(other.edge(i));
            min_dist = min(min_dist, dist);
        }
        return min_dist;
    }

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
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const;

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Closest distance to line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    /**
     * Closest distance to triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle3& other) const
    {
        return sqrt(distance_sqrd(other));
    }

    // TODO
    [[nodiscard]] Real distance(const Sphere<Real>& sphere) const;

    // TODO
    [[nodiscard]] Real distance(const AlignedBox<Real>& box) const;

    /**
     * Determine if parallel to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const;

    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if perpendicular to a line.
     * @param line Line
     * @returns Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const;

    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Intersection point with line. Returns null if coplanar.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Line3<Real>& line) const;

    /**
     * Determine if intersects with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with ray. Returns null if coplanar.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    /**
     * Intersection point with line segment. Returns null if coplanar.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> intersection(const Segment3<Real> segment) const;

    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Plane<Real>& plane) const;

    /**
     * Determine if intersects plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    /**
     * Intersection points between edges.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> edge_intersections(const Plane<Real>& plane) const;

    /**
     * Determine if intersects triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle3<Real>& triangle) const;

    /**
     *Intersection points between the edges between this rectangle and a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> edge_intersections(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Rectangle3& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (intersects(other.edge(i))) {
                return true;
            }
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (other.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    /**
     * Intersection points between the edges of this rectangle and another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> edge_intersections(const Rectangle3& other) const
    {
        PointSet<Point3<Real>, 2> inters;
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Point3<Real>> inter = intersection(other.edge(i)); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Point3<Real>> inter = other.intersection(edge(i)); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        return inters;
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const;

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& box) const;

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Box<Real>& box) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3 translate(const Vector3<Real>& offset) const
    {
        return { center.translate(offset), half_span_u, half_span_v };
    }

    /**
     * Rotate about an origin by an axis and an angle.
     * @param origin Rotation origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Rectangle3 rotate_axis_angle_at(
        const Point3<Real>& origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { center.rotate_axis_angle_at(origin, axis, angle),
                 half_span_u.rotate_axis_angle(axis, angle),
                 half_span_v.rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Rectangle3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { center.rotate_axis_angle(axis, angle),
                 half_span_u.rotate_axis_angle(axis, angle),
                 half_span_v.rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3 rotate_quaternion_at(
        const Point3<Real>& origin, const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion_at(origin, quaternion),
                 half_span_u.rotate_quaternion(quaternion),
                 half_span_v.rotate_quaternion(quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion(quaternion),
                 half_span_u.rotate_quaternion(quaternion),
                 half_span_v.rotate_quaternion(quaternion) };
    }

    /**
     * Scale about an origin by a factor.
     * @param origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3 scale_at(const Point3<Real>& origin, const Vector3<Real>& factor) const
    {
        return { center.scale_at(origin, factor), half_span_u.scale(factor), half_span_v.scale(factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3 scale(const Vector3<Real>& factor) const
    {
        return { center.scale(factor), half_span_u.scale(factor), half_span_v.scale(factor) };
    }

    /**
     * Determine if this rectangle's vertices match another rectangle's vertices order independent.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coincident(const Rectangle3& other) const
    {
        std::array<Point3<Real>, 4> verts { vertex(0), vertex(1), vertex(2), vertex(3) };
        std::array<Point3<Real>, 4> verts_other { other.vertex(0), other.vertex(1), other.vertex(2), other.vertex(3) };
        std::sort(verts.begin(), verts.end());
        std::sort(verts_other.begin(), verts_other.end());
        for (uint8_t i = 0; i < 4; ++i) {
            if (!verts[i].approx_equal(verts_other[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * Determine if all members are approximately equal to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Rectangle3& other) const
    {
        return center.approx_equal(other.center) && half_span_u.approx_equal(other.half_span_u)
            && half_span_v.approx_equal(other.half_span_v);
    }

    /**
     * Determine if all members are exactly equal to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Rectangle3& other) const
    {
        return center == other.center && half_span_u == other.half_span_u && half_span_v == other.half_span_v;
    }

    /**
     * Determine if any members are not exactly equal to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Rectangle3& other) const
    {
        return center != other.center || half_span_u != other.half_span_u || half_span_v != other.half_span_v;
    }

    /**
     * Lexicographical comparison in the order of center, half_span_u, then half_span_v.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Rectangle3& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        if (half_span_u != other.half_span_u) {
            return half_span_u < other.half_span_u;
        }
        return half_span_v < other.half_span_v;
    }
};

} // namespace nnm

#endif
