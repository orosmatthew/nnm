/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_BOX_HPP
#define NNM_GEOM3_BOX_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/rectangle3.hpp>
#include <nnm/geom3/segment3.hpp>

namespace nnm {

template <typename Real>
class Box {
public:

    /**
     * Geometric center (centroid).
     */
    Point3<Real> center;

    /**
     * Vector spanning from the center towards one of the box's dimensions face.
     * Must be orthogonal to half_span_v and half_span_w.
     */
    Vector3<Real> half_span_u;

    /**
     * Vector spanning from the center towards one of the box's dimensions face.
     * Must be orthogonal to half_span_u and half_span_w.
     */
    Vector3<Real> half_span_v;

    /**
     * Vector spanning from the center towards one of the box's dimensions face.
     * Must be orthogonal to half_span_u and half_span_v.
     */
    Vector3<Real> half_span_w;

    /**
     * Initialize to centered box with all zero half-spans. This box is invalid.
     */
    // tested
    constexpr Box()
        : center { Point3<Real>::zero() }
        , half_span_u { Vector3<Real>::zero() }
        , half_span_v { Vector3<Real>::zero() }
        , half_span_w { Vector3<Real>::zero() }
    {
    }

    /**
     * Initialize with center and 3 orthogonal half-spans. No validation is done.
     * Each half-span represents a vector from the center to one of the faces.
     * @param center Center.
     * @param half_span_u First half-span.
     * @param half_span_v Second half-span.
     * @param half_span_w Third half-span.
     */
    // tested
    constexpr Box(
        const Point3<Real>& center,
        const Vector3<Real>& half_span_u,
        const Vector3<Real>& half_span_v,
        const Vector3<Real>& half_span_w)
        : center { center }
        , half_span_u { half_span_u }
        , half_span_v { half_span_v }
        , half_span_w { half_span_w }
    {
    }

    /**
     * Case from another type.
     * @tparam Other Other floating-point type.
     * @param other Other box.
     */
    // tested
    template <typename Other>
    constexpr explicit Box(const Box<Other>& other)
        : center { Point3<Real>(other.center) }
        , half_span_u { Vector3<Real>(other.half_span_u) }
        , half_span_v { Vector3<Real>(other.half_span_v) }
        , half_span_w { Vector3<Real>(other.half_span_w) }
    {
    }

    /**
     * Create box at a center point and with a size.
     * @param center Center.
     * @param size Size.
     * @return Result.
     */
    // tested
    constexpr static Box from_center_size(const Point3<Real>& center, const Vector3<Real>& size)
    {
        return { center,
                 Vector3<Real>::axis_x() * size.x / static_cast<Real>(2),
                 Vector3<Real>::axis_y() * size.y / static_cast<Real>(2),
                 Vector3<Real>::axis_z() * size.z / static_cast<Real>(2) };
    }

    /**
     * If any half span is zero, then return the rectangle that represents the degenerate box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Rectangle3<Real>> collapse_rectangle() const;

    /**
     * If any two half-spans are zero, return the line segment that represents the degenerate box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Segment3<Real>> collapse_segment() const;

    /**
     * If all half-spans are zero, then return the point that represents the degenerate box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!half_span_u.approx_zero() || !half_span_v.approx_zero() || !half_span_w.approx_zero()) {
            return std::nullopt;
        }
        return center;
    }

    /**
     * Vertex at an index,
     * @param index Index [0-7] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Box", index < 8);
        switch (index) {
        case 0:
            return center - half_span_u - half_span_v - half_span_w;
        case 1:
            return center - half_span_u - half_span_v + half_span_w;
        case 2:
            return center - half_span_u + half_span_v - half_span_w;
        case 3:
            return center - half_span_u + half_span_v + half_span_w;
        case 4:
            return center + half_span_u - half_span_v - half_span_w;
        case 5:
            return center + half_span_u - half_span_v + half_span_w;
        case 6:
            return center + half_span_u + half_span_v - half_span_w;
        case 7:
        default:
            return center + half_span_u + half_span_v + half_span_w;
        }
    }

    /**
     * Edge at an index.
     * @param index Index [0-11] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const;

    /**
     * Face at an index.
     * @param index Index [0-5] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3<Real> face(const uint8_t index) const;

    /**
     * Determine if box is valid. A box is valid if all three half-spans are orthogonal and none are length zero.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        const bool non_zero = !approx_zero(half_span_u.length_sqrd()) && !approx_zero(half_span_v.length_sqrd())
            && !approx_zero(half_span_w.length_sqrd());
        const bool orthogonal = half_span_u.perpendicular(half_span_v) && half_span_v.perpendicular(half_span_w)
            && half_span_w.perpendicular(half_span_u);
        return non_zero && orthogonal;
    }

    /**
     * Size. Length per axis.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector3<Real> size() const
    {
        const auto two = static_cast<Real>(2);
        return { half_span_u.length() * two, half_span_v.length() * two, half_span_w.length() * two };
    }

    /**
     * Volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real volume() const
    {
        return abs(static_cast<Real>(8) * half_span_u.cross(half_span_v).dot(half_span_w));
    }

    /**
     * Surface area.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real surface_area() const
    {
        Real total = 0;
        for (uint8_t i = 0; i < 6; ++i) {
            total += face(i).area();
        }
        return total;
    }

    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - center;
        return approx_less_equal(abs(diff.dot(half_span_u)), half_span_u.length_sqrd())
            && approx_less_equal(abs(diff.dot(half_span_v)), half_span_v.length_sqrd())
            && approx_less_equal(abs(diff.dot(half_span_w)), half_span_w.length_sqrd());
    }

    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        const Vector3<Real> diff = point - center;

        const Real u_len_sqrd = half_span_u.length_sqrd();
        const Real v_len_sqrd = half_span_v.length_sqrd();
        const Real w_len_sqrd = half_span_w.length_sqrd();

        const auto zero = static_cast<Real>(0);
        const Real u_proj = u_len_sqrd > zero ? diff.dot(half_span_u) / u_len_sqrd : zero;
        const Real v_proj = v_len_sqrd > zero ? diff.dot(half_span_v) / v_len_sqrd : zero;
        const Real w_proj = w_len_sqrd > zero ? diff.dot(half_span_w) / w_len_sqrd : zero;

        const Real u_clamp = clamp(u_proj, static_cast<Real>(-1), static_cast<Real>(1));
        const Real v_clamp = clamp(v_proj, static_cast<Real>(-1), static_cast<Real>(1));
        const Real w_clamp = clamp(w_proj, static_cast<Real>(-1), static_cast<Real>(1));

        const Vector3<Real> delta = diff - (half_span_u * u_clamp + half_span_v * v_clamp + half_span_w * w_clamp);
        return delta.length_sqrd();
    }

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Line3<Real>& line) const;

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Ray3<Real>& ray) const;

    // TODO:test
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Plane<Real>& plane) const;

    /**
     * Closest distance squared to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Triangle3<Real>& triangle) const;

    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to a line. Zero if intersecting.
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

    // TODO: test
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    [[nodiscard]] bool intersects(const Triangle3<Real>& triangle) const;

    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const;

    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const;

    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& aligned_box) const;

    [[nodiscard]] constexpr bool intersects(const Box& other) const
    {
        if (contains(other.center)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(other)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Line3<Real>& line) const;

    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Ray3<Real>& ray) const;

    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Segment3<Real>& segment) const;

    [[nodiscard]] constexpr Box translate(const Vector3<Real>& offset) const
    {
        return { center.translate(offset), half_span_u, half_span_v, half_span_w };
    }

    [[nodiscard]] Box rotate_axis_angle(
        const Vector3<Real>& axis, const Real angle, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return { center.rotate_axis_angle_at(origin, axis, angle),
                 half_span_u.rotate_axis_angle(axis, angle),
                 half_span_v.rotate_axis_angle(axis, angle),
                 half_span_w.rotate_axis_angle(axis, angle) };
    }

    [[nodiscard]] constexpr Box rotate_quaternion(
        const Quaternion<Real>& quaternion, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return { center.rotate_quaternion_at(origin, quaternion),
                 half_span_u.rotate_quaternion(quaternion),
                 half_span_v.rotate_quaternion(quaternion),
                 half_span_w.rotate_quaternion(quaternion) };
    }

    [[nodiscard]] constexpr Box scale(
        const Vector3<Real>& factor, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return { center.scale_at(origin, factor),
                 half_span_u.scale(factor),
                 half_span_v.scale(factor),
                 half_span_w.scale(factor) };
    }

    [[nodiscard]] bool coincident(const Box& other) const
    {
        auto sorted_vertices = [](const Box& b) -> std::array<Point3<Real>, 8> {
            std::array<Point3<Real>, 8> verts { b.vertex(0), b.vertex(1), b.vertex(2), b.vertex(3),
                                                b.vertex(4), b.vertex(5), b.vertex(6), b.vertex(7) };
            std::sort(verts.begin(), verts.end());
            return verts;
        };
        const std::array<Point3<Real>, 8> verts = sorted_vertices(*this);
        const std::array<Point3<Real>, 8> verts_other = sorted_vertices(other);
        for (uint8_t i = 0; i < 8; ++i) {
            if (!verts[i].approx_equal(verts_other[i])) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool approx_equal(const Box& other) const
    {
        return center.approx_equal(other.center) && half_span_u.approx_equal(other.half_span_u)
            && half_span_v.approx_equal(other.half_span_v) && half_span_w.approx_equal(other.half_span_w);
    }

    [[nodiscard]] constexpr bool operator==(const Box& other) const
    {
        return center == other.center && half_span_u == other.half_span_u && half_span_v == other.half_span_v
            && half_span_w == other.half_span_w;
    }

    [[nodiscard]] constexpr bool operator!=(const Box& other) const
    {
        return center != other.center || half_span_u != other.half_span_u || half_span_v != other.half_span_v
            || half_span_w != other.half_span_w;
    }

    [[nodiscard]] constexpr bool operator<(const Box& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        if (half_span_u != other.half_span_u) {
            return half_span_u < other.half_span_u;
        }
        if (half_span_v != other.half_span_v) {
            return half_span_v < other.half_span_v;
        }
        return half_span_w < other.half_span_w;
    }
};

} // namespace nnm

#endif
