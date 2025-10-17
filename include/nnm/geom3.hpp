/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_HPP
#define NNM_GEOM3_HPP

#include <nnm/nnm.hpp>

#include <algorithm>
#include <array>

// ReSharper disable CppDFATimeOver

namespace nnm {

template <typename Real>
class Intersections3;
using Intersections3f = Intersections3<float>;
using Intersections3d = Intersections3<double>;
template <typename Real>
class Line3;
using Line3f = Line3<float>;
using Line3d = Line3<double>;
template <typename Real>
class Ray3;
using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;
template <typename Real>
class Segment3;
using Segment3f = Segment3<float>;
using Segment3d = Segment3<double>;
template <typename Real>
class Plane;
using PlaneF = Plane<float>;
using PlaneD = Plane<double>;
template <typename Real>
class Triangle3;
using Triangle3f = Triangle3<float>;
using Triangle3d = Triangle3<double>;
template <typename Real>
class Rectangle3;
using Rectangle3f = Rectangle3<float>;
using Rectangle3d = Rectangle3<double>;
template <typename Real>
class Sphere;
using SphereF = Sphere<float>;
using SphereD = Sphere<double>;
template <typename Real>
class AlignedBox;
using AlignedBoxF = AlignedBox<float>;
using AlignedBoxD = AlignedBox<double>;
template <typename Real>
class Box;
using BoxF = Box<float>;
using BoxD = Box<double>;
template <typename Real>
class Frustum;
using FrustumF = Frustum<float>;
using FrustumD = Frustum<double>;

/**
 * Fixed capacity, stack allocated set of Vector3 points.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Intersections3 {
public:
    /**
     * Default initialize to zero intersections.
     */
    // tested
    constexpr Intersections3()
        : m_points { Vector3<Real>::zero(), Vector3<Real>::zero() }
        , m_size { 0 }
    {
    }

    /**
     * Initialize with single intersection point.
     * @param point Intersection point.
     */
    // ReSharper disable once CppNonExplicitConvertingConstructor
    // tested
    constexpr Intersections3(const Vector3<Real>& point) // NOLINT(*-explicit-constructor)
        : m_points { Vector3<Real>::zero(), Vector3<Real>::zero() }
        , m_size { 0 }
    {
        insert(point);
    }

    /**
     * Initialize with two intersection points.
     * @param point1 First intersection.
     * @param point2 Second intersection.
     */
    // tested
    constexpr Intersections3(const Vector3<Real>& point1, const Vector3<Real>& point2)
        : m_points { Vector3<Real>::zero(), Vector3<Real>::zero() }
        , m_size { 0 }
    {
        insert(point1);
        insert(point2);
    }

    /**
     * Fixed capacity.
     * @return Result.
     */
    // tested
    [[nodiscard]] static constexpr uint8_t capacity()
    {
        return 2;
    }

    /**
     * Insert intersection with approximate duplicate checking.
     * @param point Point.
     */
    // tested
    constexpr void insert(const Vector3<Real>& point)
    {
        if (contains(point)) {
            return;
        }
        NNM_BOUNDS_CHECK_ASSERT("Intersections3", size < 2);
        m_points[m_size++] = point;
    }

    /**
     * Clear intersections.
     */
    // tested
    constexpr void clear()
    {
        m_points[0] = Vector3<Real>::zero();
        m_points[1] = Vector3<Real>::zero();
        m_size = 0;
    }

    /**
     * Number of intersections.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr uint8_t size() const
    {
        return m_size;
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    // tested
    constexpr Vector3<Real>* begin()
    {
        return &m_points[0];
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    // tested
    constexpr Vector3<Real>* end()
    {
        return &m_points[m_size + 1];
    }

    /**
     * Start const iterator.
     * @return Iterator.
     */
    // tested
    constexpr const Vector3<Real>* begin() const
    {
        return &m_points[0];
    }

    /**
     * End const iterator.
     * @return Iterator.
     */
    // tested
    constexpr const Vector3<Real>* end() const
    {
        return &m_points[m_size + 1];
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr const Vector3<Real>* data() const
    {
        return m_points;
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr Vector3<Real>* data()
    {
        return m_points;
    }

    /**
     * Unordered approximate equality.
     * @param other Other intersections.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Intersections3& other) const
    {
        if (m_size != other.size()) {
            return false;
        }
        if (m_size == 0) {
            return true;
        }
        if (m_size == 1) {
            return m_points[0].approx_equal(other.m_points[0]);
        }
        return (m_points[0].approx_equal(other.m_points[0]) && m_points[1].approx_equal(other.m_points[1]))
            || (m_points[0].approx_equal(other.m_points[1]) && m_points[1].approx_equal(other.m_points[0]));
    }

    /**
     * Determine if approximately contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        for (uint8_t i = 0; i < m_size; ++i) {
            if (m_points[i].approx_equal(point)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if there are no intersections.
     */
    // tested
    [[nodiscard]] constexpr bool empty() const
    {
        return m_size == 0;
    }

    /**
     * Exact unordered equality.
     * @param other Other intersections.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Intersections3& other) const
    {
        if (m_size != other.size()) {
            return false;
        }
        if (m_size == 0) {
            return true;
        }
        if (m_size == 1) {
            return m_points[0] == other.m_points[0];
        }
        return (m_points[0] == other.m_points[0] && m_points[1] == other.m_points[1])
            || (m_points[0] == other.m_points[1] && m_points[1] == other.m_points[0]);
    }

    /**
     * Exact unordered inequality.
     * @param other Other intersections.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Intersections3& other) const
    {
        return !(*this == other);
    }

private:
    Vector3<Real> m_points[2];
    uint8_t m_size;
};

/**
 * Infinite line.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Line3 {
public:
    /**
     * Origin.
     */
    Vector3<Real> origin;

    /**
     * Direction.
     */
    Vector3<Real> direction;

    /**
     * Default initialize with zero origin in the direction of the x-axis.
     */
    // tested
    constexpr Line3()
        : origin { Vector3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin that the line intersects and a direction. The direction should be normalized.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Line3(const Vector3<Real>& origin, const Vector3<Real>& direction)
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
     * Line that intersects two points.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    // tested
    static Line3 from_points(const Vector3<Real>& point1, const Vector3<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    /**
     * Extends a line segment to an infinite line.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    static Line3 from_segment(const Segment3<Real>& segment);

    /**
     * Line that is an extension from a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    static constexpr Line3 from_ray(const Ray3<Real>& ray);

    /**
     * Line that intersects the origin and is in the direction of the x-axis.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_x()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    /**
     * Line that intersects the origin and is in the direction of the y-axis.
     * @return Result.
     */
    // tested
    static constexpr Line3 axis_y()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    /**
     * Line that intersects the origin and is in the direction of the z-axis.
     * @return
     */
    // tested
    static constexpr Line3 axis_z()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_z() };
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
     * Line that is parallel to this line and intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line3 parallel_containing(const Vector3<Real>& point) const
    {
        return { point, direction };
    }

    /**
     * Line that is perpendicular to this line and intersects a point.
     * Both direction and -direction are valid for the resulting line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line3 arbitrary_perpendicular_containing(const Vector3<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
    }

    /**
     * Line that is perpendicular to this line and parallel to a plane.
     * Both direction and -direction are valid for the resulting line.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 perpendicular_plane_parallel(const Plane<Real>& plane) const;

    /**
     * Normalize the line's direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 normalize() const
    {
        return { origin, direction.normalize() };
    }

    /**
     * Determine if collinear with a ray which means
     * that all points for both the line and the ray exist on the same line.
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
    [[nodiscard]] bool collinear(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3& other) const
    {
        if (parallel(other)) {
            return true;
        }
        const Vector3<Real> diff = origin - other.origin;
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        return approx_zero(diff.dot(dir_cross));
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
     * Determine if intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        const Real t = dir.dot(direction);
        const Vector3<Real> proj = origin + direction * t;
        return proj.approx_equal(point);
    }

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return (point - origin).cross(direction).length();
    }

    /**
     * Closest distance to another line. Zero if they intersect.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        if (dir_cross.approx_zero()) {
            return distance(other.origin);
        }
        const Vector3<Real> diff = origin - other.origin;
        return abs(dir_cross.dot(diff)) / dir_cross.length();
    }

    /**
     * Closest distance to a ray. Zero if they intersect.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Determine if parallel with another line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

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
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with another line.
     * @param other Other line.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Line3& other) const
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
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const;

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3<Real>& segment) const;

    /**
     * Project point on the line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> project(const Vector3<Real>& point) const
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
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 scale(const Vector3<Real>& factor) const
    {
        return { origin.scale(factor), direction.scale(factor).normalize() };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param rotate_origin Rotate origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 rotate_axis_angle_at(
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotate origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
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
    [[nodiscard]] Line3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), direction.rotate_quaternion(quaternion).normalize() };
    }

    /**
     * Shear about an origin along the x-axis.
     * @param shear_origin Shear origin.
     * @param factor_y Y-Axis shear factor.
     * @param factor_z Z-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_x_at(const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z),
                 direction.shear_x(factor_y, factor_z).normalize() };
    }

    /**
     * Shear about the global origin along the x-axis.
     * @param factor_y Y-Axis shear factor.
     * @param factor_z Z-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x(factor_y, factor_z), direction.shear_x(factor_y, factor_z).normalize() };
    }

    /**
     * Shear about an origin along the y-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_y_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z),
                 direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear about the global origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] Line3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y(factor_x, factor_z), direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear about an origin along the z-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_z_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z_at(shear_origin, factor_x, factor_y),
                 direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Shear about the global origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z(factor_x, factor_y), direction.shear_z(factor_x, factor_y).normalize() };
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

/**
 * 3D Ray.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Ray3 {
public:
    /**
     * Origin.
     */
    Vector3<Real> origin;

    /**
     * Normalized direction.
     */
    Vector3<Real> direction;

    /**
     * Default initialize with zero origin and in the direction of the positive x-axis.
     */
    // tested
    constexpr Ray3()
        : origin { Vector3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin and direction. No normalization is done on the direction.
     * @param origin Origin.
     * @param direction Direction.
     */
    // tested
    constexpr Ray3(const Vector3<Real>& origin, const Vector3<Real>& direction)
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
    static Ray3 from_point_to_point(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        return { from, from.direction(to) };
    }

    /**
     * Normalize the direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray3 normalize() const
    {
        return { origin, direction.normalize() };
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_ray(*this).contains(point);
    }

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).coincident(line);
    }

    /**
     * Determine if collinear with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray3& other) const
    {
        return Line3<Real>::from_ray(*this).coincident(Line3<Real>::from_ray(other));
    }

    /**
     * Determine if coplanar with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).coplanar(line);
    }

    /**
     * Determine if coplanar with another ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coplanar(const Ray3& ray) const
    {
        return Line3<Real>::from_ray(*this).coplanar(Line3<Real>::from_ray(ray));
    }

    /**
     * Determine if coplanar with line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const
    {
        return Line3<Real>::from_ray(*this).coplanar(segment);
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
    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if ray intersects a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> proj = project(point);
        return proj.approx_equal(point);
    }

    /**
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - origin;
        if (const Real t = dir.dot(direction); approx_less_zero(t)) {
            return origin.distance(point);
        }
        return dir.cross(direction).length();
    }

    /**
     * Closest distance to a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = line.origin - origin;
        if (approx_zero(dir_cross_len_sqrd)) {
            return line.distance(origin);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_line = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return line.distance(origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = line.origin + line.direction * t_line;
        return p1.distance(p2);
    }

    /**
     * Closest distance to another ray. Zero if intersects.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.origin - origin;
        if (approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = distance(other.origin);
            const Real d2 = other.distance(origin);
            return min(d1, d2);
        }
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return other.distance(origin);
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other)) {
            return distance(other.origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = other.origin + other.direction * t_other;
        return p1.distance(p2);
    }

    /**
     * Determine if parallel to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const
    {
        return direction.cross(line.direction).approx_zero();
    }

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
     * Determine if perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const
    {
        return nnm::approx_zero(direction.dot(line.direction));
    }

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
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.contains(origin);
        }
        const Vector3<Real> diff = line.origin - origin;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return false;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = line.origin + line.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with a line.
     * @param line Line.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.origin - origin;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = line.origin + line.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

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
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3<Real>& segment) const;

    /**
     * Intersection point with another ray.
     * @param other Other ray.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Ray3& other) const
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
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = other.origin + other.direction * t_other; !p.approx_equal(p_other)) {
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
    [[nodiscard]] constexpr Vector3<Real> project(const Vector3<Real>& point) const
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
    [[nodiscard]] Ray3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
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
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
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
    [[nodiscard]] Ray3 rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
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
    [[nodiscard]] Ray3 shear_x_at(const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
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
    [[nodiscard]] Ray3 shear_y_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
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
    [[nodiscard]] Ray3 shear_z_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
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

/**
 * 3D Line Segment.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Segment3 {
public:
    /**
     * Start position of the line segment.
     */
    Vector3<Real> start;

    /**
     * End position of the line segment.
     */
    Vector3<Real> end;

    /**
     * Default initialize to start from the origin and end at one unit away in the positive x-axis.
     */
    // tested
    constexpr Segment3()
        : start { Vector3<Real>::zero() }
        , end { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with start and end position.
     * @param start Start position.
     * @param end End position.
     */
    // tested
    constexpr Segment3(const Vector3<Real>& start, const Vector3<Real>& end)
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

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_segment(*this).contains(point);
    }

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_segment(*this).coincident(line);
    }

    /**
     * Determine if collinear with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool collinear(const Ray3<Real>& ray) const
    {
        return Line3<Real>::from_segment(*this).collinear(ray);
    }

    /**
     * Determine if collinear with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool collinear(const Segment3& other) const
    {
        return Line3<Real>::from_segment(*this).coincident(Line3<Real>::from_segment(other));
    }

    /**
     * Determine if coplanar with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Line3<Real>& line) const
    {
        return Line3<Real>::from_segment(*this).coplanar(line);
    }

    /**
     * Determine if coplanar with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const
    {
        return Line3<Real>::from_segment(*this).coplanar(ray);
    }

    /**
     * Determine if coplanar with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Segment3& other) const
    {
        return Line3<Real>::from_segment(*this).coplanar(Line3<Real>::from_segment(other));
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
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
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
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = end - start;
        const Vector3<Real> diff = point - start;
        Real t = diff.dot(dir) / dir.dot(dir);
        if (approx_less_zero(t)) {
            return diff.length();
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return (point - end).length();
        }
        Vector3<Real> proj = start + dir * t;
        return (point - proj).length();
    }

    /**
     * Closest distance to a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = line.origin - start;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = line.distance(start);
            const Real d2 = line.distance(end);
            return min(d1, d2);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return line.distance(start);
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return line.distance(end);
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p1 = start.lerp(end, t);
        const Vector3<Real> p2 = line.origin + line.direction * t_line;
        return p1.distance(p2);
    }

    /**
     * Closest distance to a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        // TODO: do this for other methods
        if (start.approx_equal(end)) {
            return ray.distance(start);
        }
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = ray.origin - start;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = ray.distance(start);
            const Real d2 = ray.distance(end);
            const Real d3 = distance(ray.origin);
            return min(d1, min(d2, d3));
        }
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return ray.distance(start);
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return ray.distance(end);
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_ray)) {
            return distance(ray.origin);
        }
        const Vector3<Real> p1 = start.lerp(end, t);
        const Vector3<Real> p2 = ray.origin + ray.direction * t_ray;
        return p1.distance(p2);
    }

    /**
     * Closest distance to another line segment. Zero if intersects.
     * @param other Other line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3& other) const
    {
        if (start.approx_equal(end)) {
            return other.distance(start);
        }
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        const Vector3<Real> diff = other.start - start;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = other.distance(start);
            const Real d2 = other.distance(end);
            const Real d3 = distance(other.start);
            const Real d4 = distance(other.end);
            return min(min(d1, d2), min(d3, d4));
        }
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t)) {
            return other.distance(start);
        }
        if (approx_greater(t, static_cast<Real>(1))) {
            return other.distance(end);
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_other)) {
            return distance(other.start);
        }
        if (approx_greater(t_other, static_cast<Real>(1))) {
            return distance(other.end);
        }
        const Vector3<Real> p1 = start.lerp(end, t);
        const Vector3<Real> p2 = other.start.lerp(other.end, t_other);
        return p1.distance(p2);
    }

    // TODO: test
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

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
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const
    {
        const Vector3<Real> proj = direction_unnormalized().cross(line.direction);
        return proj.approx_zero();
    }

    /**
     * Determine if parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const
    {
        const Vector3<Real> proj = direction_unnormalized().cross(ray.direction);
        return proj.approx_zero();
    }

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
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const
    {
        const Real proj = direction_unnormalized().dot(line.direction);
        return approx_zero(proj);
    }

    /**
     * Determine if perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const
    {
        const Real proj = direction_unnormalized().dot(ray.direction);
        return approx_zero(proj);
    }

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
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.contains(start);
        }
        const Vector3<Real> diff = line.origin - start;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return false;
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_other = line.origin + line.direction * t_line;
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with a line.
     * @param line Line.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.origin - start;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return std::nullopt;
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = start.lerp(end, t);
        if (const Vector3<Real> p_other = line.origin + line.direction * t_line; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return ray.contains(start) || ray.contains(end);
        }
        const Vector3<Real> diff = ray.origin - start;
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return false;
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_ray)) {
            return false;
        }
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray;
        return p.approx_equal(p_ray);
    }

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = ray.origin - start;
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return std::nullopt;
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (approx_less_zero(t_ray)) {
            return std::nullopt;
        }
        const Vector3<Real> p = start.lerp(end, t);
        if (const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray; !p.approx_equal(p_ray)) {
            return std::nullopt;
        }
        return p;
    }

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
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_other = other.start.lerp(other.end, t_other);
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with another line segment.
     * @param other Other line segment.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3& other) const
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
        const Vector3<Real> p = start.lerp(end, t);
        if (const Vector3<Real> p_other = other.start.lerp(other.end, t_other); !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Plane<Real>& plane) const;

    /**
     * Project a point on the line segment.
     * @param point Point.
     * @return Resulting projected point.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> project(const Vector3<Real>& point) const
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
    [[nodiscard]] constexpr Vector3<Real> midpoint() const
    {
        return (start + end) / static_cast<Real>(2);
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
    [[nodiscard]] constexpr Segment3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
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
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
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
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
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
        const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
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
        const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
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
        const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
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

/**
 * Plane.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Plane {
public:
    /**
     * Origin.
     */
    Vector3<Real> origin;

    /**
     * Normalized normal.
     */
    Vector3<Real> normal;

    /**
     * Default initialize with a zero origin and normal in the direction of the positive x-axis.
     */
    // tested
    constexpr Plane()
        : origin { Vector3<Real>::zero() }
        , normal { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with an origin and normalized normal. No normalization is performed.
     * @param origin Origin.
     * @param normal Normalized normal.
     */
    // tested
    constexpr Plane(const Vector3<Real>& origin, const Vector3<Real>& normal)
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
        const Vector3<Real>& point1, const Vector3<Real>& point2, const Vector3<Real>& point3)
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
        const Vector3<Real>& point1, const Vector3<Real>& point2, const Vector3<Real>& point3)
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

    /**
     * Plane that spans the x and y axes.
     * @return Result.
     */
    // tested
    static constexpr Plane xy()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_z() };
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
        return { Vector3<Real>::zero(), Vector3<Real>::axis_y() };
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
        return { Vector3<Real>::zero(), Vector3<Real>::axis_x() };
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
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const
    {
        return contains(line.origin) && normal.perpendicular(line.direction);
    }

    /**
     * Determine if coplanar with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Ray3<Real>& ray) const
    {
        return contains(ray.origin) && normal.perpendicular(ray.direction);
    }

    /**
     * Determine if coplanar with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Segment3<Real>& segment) const
    {
        return contains(segment.start) && contains(segment.end);
    }

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
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Real d = origin.dot(normal);
        const Real proj = point.dot(normal);
        return nnm::approx_equal(d, proj);
    }

    [[nodiscard]] constexpr Real signed_distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        return diff.dot(normal);
    }

    /**
     * Determine the closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Vector3<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    /**
     * Determine the closest distance with a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Line3<Real>& line) const
    {
        if (!parallel(line)) {
            return static_cast<Real>(0);
        }
        return distance(line.origin);
    }

    /**
     * Determine the closest distance with a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Ray3<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        return distance(ray.origin);
    }

    /**
     * Determine the closest distance with a line segment. Zero if intersects.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Segment3<Real>& segment) const
    {
        if (intersects(segment)) {
            return static_cast<Real>(0);
        }
        const Real d1 = distance(segment.start);
        const Real d2 = distance(segment.end);
        return min(d1, d2);
    }

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
     * Determine if parallel with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const
    {
        return normal.perpendicular(line.direction);
    }

    /**
     * Determine if parallel with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const
    {
        return normal.perpendicular(ray.direction);
    }

    /**
     * Determine if parallel with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment3<Real>& segment) const
    {
        const Real proj = normal.dot(segment.direction_unnormalized());
        return approx_zero(proj);
    }

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
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const
    {
        return normal.parallel(line.direction);
    }

    /**
     * Determine if perpendicular with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const
    {
        return normal.parallel(ray.direction);
    }

    /**
     * Determine if perpendicular with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment3<Real>& segment) const
    {
        const Vector3<Real> cross = normal.cross(segment.direction_unnormalized());
        return cross.approx_zero();
    }

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
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        const Real proj = normal.dot(line.direction);
        return !approx_zero(proj) || contains(line.origin);
    }

    /**
     * Intersection point with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
    {
        const Real proj = normal.dot(line.direction);
        if (approx_zero(proj)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = origin - line.origin;
        const Real dot_diff = normal.dot(diff);
        const Real t = dot_diff / proj;
        return line.origin + line.direction * t;
    }

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        const Real proj = normal.dot(ray.direction);
        if (approx_zero(proj)) {
            return contains(ray.origin);
        }
        const Vector3<Real> diff = origin - ray.origin;
        const Real dot_diff = normal.dot(diff);
        const Real t = dot_diff / proj;
        return approx_greater_equal_zero(t);
    }

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const
    {
        const Real proj = normal.dot(ray.direction);
        if (approx_zero(proj)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = origin - ray.origin;
        const Real dot_diff = normal.dot(diff);
        const Real t = dot_diff / proj;
        if (approx_less_zero(t)) {
            return std::nullopt;
        }
        return ray.origin + ray.direction * t;
    }

    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const
    {
        const Real proj = normal.dot(segment.direction_unnormalized());
        if (approx_zero(proj)) {
            return contains(segment.start) || contains(segment.end);
        }
        const Vector3<Real> diff = origin - segment.start;
        const Real dot_diff = normal.dot(diff);
        const Real t = dot_diff / proj;
        return approx_greater_equal_zero(t) && approx_less_equal(t, static_cast<Real>(1));
    }

    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3<Real>& segment) const
    {
        if (segment.start.approx_equal(segment.end)) {
            if (!contains(segment.start)) {
                return std::nullopt;
            }
            return segment.start;
        }
        const Vector3<Real> seg_dir = segment.direction_unnormalized();
        const Real proj = normal.dot(seg_dir);
        if (approx_zero(proj)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = origin - segment.start;
        const Real dot_diff = normal.dot(diff);
        const Real t = dot_diff / proj;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return std::nullopt;
        }
        return segment.start + seg_dir * t;
    }

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
    [[nodiscard]] std::optional<Line3<Real>> intersection(const Plane& other) const
    {
        const Vector3<Real> dir = normal.cross(other.normal);
        if (dir.approx_zero()) {
            return std::nullopt;
        }

        const Real d1 = -normal.dot(origin);
        const Real d2 = -other.normal.dot(other.origin);
        Vector3<Real> point;
        if (const uint8_t max_index = dir.abs_max_index(); max_index == 0) {
            point = { static_cast<Real>(0),
                      (d2 * normal.z - d1 * other.normal.z) / dir.x,
                      (d1 * other.normal.y - d2 * normal.y) / dir.x };
        }
        else if (max_index == 1) {
            point = { (d1 * other.normal.z - d2 * normal.z) / dir.y,
                      static_cast<Real>(0),
                      (d2 * normal.x - d1 * other.normal.x) / dir.y };
        }
        else {
            point = { (d2 * normal.y - d1 * other.normal.y) / dir.z,
                      (d1 * other.normal.x - d2 * normal.x) / dir.z,
                      static_cast<Real>(0) };
        }
        return Line3<Real> { point, dir.normalize() };
    }

    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Plane& other1, const Plane& other2) const
    {
        const Matrix3<Real> a { { normal.x, normal.y, normal.z },
                                { other1.normal.x, other1.normal.y, other1.normal.z },
                                { other2.normal.x, other2.normal.y, other2.normal.z } };
        if (const Real det = a.determinant(); approx_zero(det)) {
            return std::nullopt;
        }
        const Vector3<Real> b {
            normal.dot(origin), other1.normal.dot(other1.origin), other2.normal.dot(other2.origin)
        };
        const Matrix3<Real> a_inv = a.unchecked_inverse();
        const Vector3<Real> point { a_inv.at(0).dot(b), a_inv.at(1).dot(b), a_inv.at(2).dot(b) };
        return point;
    }

    // TODO: test
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Triangle3<Real>& triangle) const;

    // TODO: test
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Rectangle3<Real>& rectangle) const;

    // tested
    [[nodiscard]] constexpr Vector3<Real> project(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        const Real dist = diff.dot(normal) / normal.dot(normal);
        return point - normal * dist;
    }

    // tested
    [[nodiscard]] constexpr Plane translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), normal };
    }

    // tested
    [[nodiscard]] Plane scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
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
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
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
    [[nodiscard]] Plane rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 normal.rotate_quaternion(quaternion).normalize() };
    }

    // tested
    [[nodiscard]] Plane rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), normal.rotate_quaternion(quaternion).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_x_at(const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_x(const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x(factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_y_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_y(const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y(factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    // tested
    [[nodiscard]] Plane shear_z_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
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

/**
 * 3D Triangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Triangle3 {
public:
    /**
     * Vertices.
     */
    Vector3<Real> vertices[3];

    /**
     * Default initialize all vertices to origin.
     */
    // tested
    constexpr Triangle3()
        : vertices { Vector3<Real>::zero(), Vector3<Real>::zero(), Vector3<Real>::zero() }
    {
    }

    /**
     * Initialize with provided vertices.
     * @param vertex0 First vertex.
     * @param vertex1 Second vertex.
     * @param vertex2 Third vertex.
     */
    // tested
    constexpr Triangle3(const Vector3<Real>& vertex0, const Vector3<Real>& vertex1, const Vector3<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other triangle.
     */
    // tested
    template <typename Other>
    explicit constexpr Triangle3(const Triangle3<Other>& other)
        : vertices { Vector3<Real> { other.vertices[0] },
                     Vector3<Real> { other.vertices[1] },
                     Vector3<Real> { other.vertices[2] } }
    {
    }

    /**
     * Edge in the order of vertex 0 to 1, 1 to 2, then 2 to 0.
     * @param index Edge index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const uint8_t next_index = (index + 1) % 3;
        return { vertices[index], vertices[next_index] };
    }

    /**
     * Centroid which is the average between all vertices.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> centroid() const
    {
        return (vertices[0] + vertices[1] + vertices[2]) / static_cast<Real>(3);
    }

    /**
     * Circumcenter which is the intersection between the perpendicular bisectors of the edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> circumcenter() const
    {
        const std::optional<Line3<Real>> pb1 = perpendicular_bisector(0);
        if (!pb1.has_value()) {
            return std::nullopt;
        }
        const std::optional<Line3<Real>> pb2 = perpendicular_bisector(1);
        if (!pb2.has_value()) {
            return std::nullopt;
        }
        return pb1->intersection(*pb2);
    }

    /**
     * Perimeter which is the combined length of all edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real perimeter() const
    {
        return edge(0).length() + edge(1).length() + edge(2).length();
    }

    /**
     * Incenter which is the intersection between the interior angles' bisectors.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> incenter() const
    {
        return angle_bisector(0).intersection(angle_bisector(1));
    }

    /**
     * Orthocenter which is the intersection between the altitudes of the triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> orthocenter() const
    {
        const std::optional<Segment3<Real>> alt0 = altitude(0);
        if (!alt0.has_value()) {
            return std::nullopt;
        }
        const std::optional<Segment3<Real>> alt1 = altitude(1);
        if (!alt1.has_value()) {
            return std::nullopt;
        }
        return Line3<Real>::from_segment(*alt0).intersection(Line3<Real>::from_segment(*alt1));
    }

    /**
     * Area.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real area() const
    {
        const Vector3<Real> dir01 = vertices[0].direction_unnormalized(vertices[1]);
        const Vector3<Real> dir02 = vertices[0].direction_unnormalized(vertices[2]);
        return dir01.cross(dir02).length() / static_cast<Real>(2);
    }

    /**
     * Median which is the line segment from a vertex to the midpoint of its opposite edge.
     * It is indexed in the order of vertex 0 to midpoint of edge 1, vertex 1 to midpoint of edge 2,
     * then vertex 2 to midpoint of edge 0.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> median(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const uint8_t next_index = (index + 1) % 3;
        return { vertices[index], edge(next_index).midpoint() };
    }

    /**
     * Perpendicular bisector of an edge which is a line that divides an edge in half and
     * is perpendicular to the edge.
     * @param index Index of the edge.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Line3<Real>> perpendicular_bisector(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const std::optional<Plane<Real>> p = Plane<Real>::from_triangle(*this);
        if (!p.has_value()) {
            return std::nullopt;
        }
        const Segment3<Real> e = edge(index);
        const Vector3<Real> dir = Line3<Real>::from_segment(e).perpendicular_plane_parallel(*p).direction;
        return Line3<Real> { e.midpoint(), dir };
    }

    /**
     * Interior angle at a vertex index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real angle(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const uint8_t next_index = (index + 1) % 3;
        const uint8_t prev_index = (index + 2) % 3;
        const Vector3<Real> dir1 = vertices[prev_index] - vertices[index];
        const Vector3<Real> dir2 = vertices[next_index] - vertices[index];
        return acos(dir1.dot(dir2) / (dir1.length() * dir2.length()));
    }

    /**
     * Angle bisector of the angle at the vertex at an index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3<Real> angle_bisector(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const uint8_t next_index = (index + 1) % 3;
        const uint8_t prev_index = (index + 2) % 3;
        const Vector3<Real> dir1 = (vertices[prev_index] - vertices[index]).normalize();
        const Vector3<Real> dir2 = (vertices[next_index] - vertices[index]).normalize();
        const Vector3<Real> bisector_dir = (dir1 + dir2).normalize();
        return { vertices[index], bisector_dir };
    }

    /**
     * Altitude originating from the vertex at an index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Segment3<Real>> altitude(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const Vector3<Real>& vertex = vertices[index];
        const uint8_t next_index = (index + 1) % 3;
        const Line3<Real> base_line = Line3<Real>::from_segment(edge(next_index));
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            return std::nullopt;
        }
        const Vector3<Real> perp_dir = base_line.perpendicular_plane_parallel(*plane).direction;
        const Line3<Real> altitude_line { vertex, perp_dir };
        const std::optional<Vector3<Real>> intersection = altitude_line.intersection(base_line);
        if (!intersection.has_value()) {
            return std::nullopt;
        }
        return Segment3<Real> { vertex, *intersection };
    }

    /**
     * Linearly interpolate between the vertices with weights.
     * This returns the point from its barycentric coordinates.
     * @param weights Interpolation weights.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> lerp_point(const Vector3<Real> weights) const
    {
        return weights.x * vertices[0] + weights.y * vertices[1] + weights.z * vertices[2];
    }

    /**
     * Barycentric coordinates of a point which is its interpolation weights relative to the triangle's vertices.
     * Containment within the triangle is not checked.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector3<Real> barycentric_unchecked(const Vector3<Real>& point) const
    {
        const Real area_full = area();
        const Real area_p12 = Triangle3 { point, vertices[1], vertices[2] }.area();
        const Real area_0p2 = Triangle3 { vertices[0], point, vertices[2] }.area();
        const Real area_01p = Triangle3 { vertices[0], vertices[1], point }.area();
        return Vector3<Real> { area_p12 / area_full, area_0p2 / area_full, area_01p / area_full };
    }

    /**
     * Barycentric coordinates of a point which is its interpolation weights relative to the triangle's vertices.
     * Containment within the triangle is checked.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> barycentric(const Vector3<Real>& point) const
    {
        if (!contains(point)) {
            return std::nullopt;
        }
        const Real area_full = area();
        if (approx_zero(area_full)) {
            return std::nullopt;
        }
        const Real area_p12 = Triangle3 { point, vertices[1], vertices[2] }.area();
        const Real area_0p2 = Triangle3 { vertices[0], point, vertices[2] }.area();
        const Real area_01p = Triangle3 { vertices[0], vertices[1], point }.area();
        return Vector3<Real> { area_p12 / area_full, area_0p2 / area_full, area_01p / area_full };
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool contains(const Vector3<Real>& point) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            return edge(0).contains(point) || edge(1).contains(point) || edge(2).contains(point);
        }
        if (!plane->contains(point)) {
            return false;
        }
        return contains_projected(point);
    }

    /**
     * Determine if point is contained on the triangle when projected onto the plane coplanar to the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains_projected(const Vector3<Real>& point) const
    {
        const Vector3<Real> n = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
        const auto edge_func = [&n](const Vector3<Real>& a, const Vector3<Real>& b, const Vector3<Real>& p) -> Real {
            return n.dot((b - a).cross(p - a));
        };
        const Real e01 = edge_func(vertices[0], vertices[1], point);
        const Real e12 = edge_func(vertices[1], vertices[2], point);
        const Real e20 = edge_func(vertices[2], vertices[0], point);
        const bool cond1
            = approx_greater_equal_zero(e01) && approx_greater_equal_zero(e12) && approx_greater_equal_zero(e20);
        const bool cond2 = approx_less_equal_zero(e01) && approx_less_equal_zero(e12) && approx_less_equal_zero(e20);
        return cond1 || cond2;
    }

    /**
     * Determine if all vertices are collinear.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool collinear() const
    {
        const auto l1 = Line3<Real>::from_points(vertices[0], vertices[1]);
        const auto l2 = Line3<Real>::from_points(vertices[1], vertices[2]);
        return l1.coincident(l2);
    }

    /**
     * Determine if coplanar with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Vector3<Real>& point) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            return true;
        }
        return plane->contains(point);
    }

    /**
     * Determine if coplanar with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Line3<Real>& line) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            for (uint8_t i = 0; i < 3; ++i) {
                if (!edge(i).coplanar(line)) {
                    return false;
                }
            }
            return true;
        }
        return plane->coplanar(line);
    }

    /**
     * Determine if coplanar with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const
    {
        return coplanar(Line3<Real>::from_ray(ray));
    }

    /**
     * Determine if coplanar with a segment.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const
    {
        return coplanar(Line3<Real>::from_segment(segment));
    }

    /**
     * Determine if coplanar with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Plane<Real>& plane) const
    {
        const std::optional<Plane<Real>> p = Plane<Real>::from_triangle(*this);
        if (!p.has_value()) {
            for (uint8_t i = 0; i < 3; ++i) {
                if (!edge(i).coplanar(plane)) {
                    return false;
                }
            }
            return true;
        }
        return p->coplanar(plane);
    }

    /**
     * Project point onto the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector3<Real> project(const Vector3<Real>& point) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        Vector3<Real> plane_proj = point;
        if (plane.has_value()) {
            plane_proj = plane->project(point);
        }
        if (contains(plane_proj)) {
            return plane_proj;
        }
        uint8_t closest_edge = 0;
        Real closest_edge_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 3; ++i) {
            const Real dist = edge(i).distance(plane_proj);
            if (dist < closest_edge_dist) {
                closest_edge = i;
                closest_edge_dist = dist;
            }
        }
        return edge(closest_edge).project(plane_proj);
    }

    /**
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        if (contains(point)) {
            return static_cast<Real>(0);
        }
        const Vector3<Real> proj = project(point);
        return point.distance(proj);
    }

    /**
     * Closest distance to a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        return min(edge(0).distance(line), edge(1).distance(line), edge(2).distance(line));
    }

    /**
     * Closest distance to a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        return min(distance(ray.origin), edge(0).distance(ray), edge(1).distance(ray), edge(2).distance(ray));
    }

    /**
     * Closest distance to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const
    {
        if (intersects(segment)) {
            return static_cast<Real>(0);
        }
        return min(
            distance(segment.start),
            distance(segment.end),
            edge(0).distance(segment),
            edge(1).distance(segment),
            edge(2).distance(segment));
    }

    /**
     * Closest distance to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const
    {
        if (intersects(plane)) {
            return static_cast<Real>(0);
        }
        return min(plane.distance(vertices[0]), plane.distance(vertices[1]), plane.distance(vertices[2]));
    }

    /**
     * Closest distance to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        return min(
            edge(0).distance(other.edge(0)),
            edge(0).distance(other.edge(1)),
            edge(0).distance(other.edge(2)),
            edge(1).distance(other.edge(1)),
            edge(1).distance(other.edge(2)),
            edge(2).distance(other.edge(2)));
    }

    /**
     * Determine if intersects with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Line3<Real>& line) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value() || plane->coplanar(line)) {
            return edge(0).intersects(line) || edge(1).intersects(line) || edge(2).intersects(line);
        }
        const std::optional<Vector3<Real>> point = plane->intersection(line);
        if (!point.has_value()) {
            return false;
        }
        return contains_projected(*point);
    }

    /**
     * Intersection point with a line. Returns null if coplanar intersection.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            for (uint8_t i = 0; i < 3; ++i) {
                const std::optional<Vector3<Real>> point = edge(i).intersection(line);
                if (point.has_value()) {
                    return *point;
                }
            }
            return std::nullopt;
        }
        const std::optional<Vector3<Real>> point = plane->intersection(line);
        if (!point.has_value() || !contains_projected(*point)) {
            return std::nullopt;
        }
        return *point;
    }

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray3<Real>& ray) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value() || plane->coplanar(ray)) {
            return edge(0).intersects(ray) || edge(1).intersects(ray) || edge(2).intersects(ray);
        }
        const std::optional<Vector3<Real>> point = plane->intersection(ray);
        if (!point.has_value()) {
            return false;
        }
        return contains_projected(*point);
    }

    /**
     * Intersection point with a ray. Returns null if coplanar intersection.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const
    {
        const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            for (uint8_t i = 0; i < 3; ++i) {
                const std::optional<Vector3<Real>> point = edge(i).intersection(ray);
                if (point.has_value()) {
                    return *point;
                }
            }
            return std::nullopt;
        }
        const std::optional<Vector3<Real>> point = plane->intersection(ray);
        if (!point.has_value() || !contains_projected(*point)) {
            return std::nullopt;
        }
        return *point;
    }

    /**
     * Determine if intersects with a line segment
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment3<Real>& segment) const
    {
        std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value() || plane->coplanar(segment)) {
            return edge(0).intersects(segment) || edge(1).intersects(segment) || edge(2).intersects(segment)
                || contains(segment.start) || contains(segment.end);
        }
        const std::optional<Vector3<Real>> point = plane->intersection(segment);
        if (!point.has_value()) {
            return false;
        }
        return contains_projected(*point);
    }

    /**
     * Intersection point with a line segment. Returns null if coplanar intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Segment3<Real>& segment) const
    {
        std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
        if (!plane.has_value()) {
            for (uint8_t i = 0; i < 3; ++i) {
                const std::optional<Vector3<Real>> point = edge(i).intersection(segment);
                if (point.has_value()) {
                    return *point;
                }
            }
            return std::nullopt;
        }
        const std::optional<Vector3<Real>> point = plane->intersection(segment);
        if (!point.has_value() || !contains_projected(*point)) {
            return std::nullopt;
        }
        return *point;
    }

    /**
     * Determine if intersects with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const
    {
        return plane.intersects(edge(0)) || plane.intersects(edge(1)) || plane.intersects(edge(2));
    }

    /**
     * Intersection with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Plane<Real>& plane) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Vector3<Real>> point = plane.intersection(edge(i));
            if (point.has_value()) {
                inters.insert(*point);
            }
        }
        if (inters.empty()) {
            return std::nullopt;
        }
        if (inters.size() == 1) {
            return Segment3<Real> { inters.data()[0], inters.data()[0] };
        }
        return Segment3<Real> { inters.data()[0], inters.data()[1] };
    }

    /**
     * Determine if intersects with another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle3& other) const
    {
        return intersects(other.edge(0)) || intersects(other.edge(1)) || intersects(other.edge(2))
            || other.intersects(edge(0)) || other.intersects(edge(1)) || other.intersects(edge(2));
    }

    /**
     * Intersection with another triangle.
     * If polygonal intersection exists, null is returned.
     * @param other Other triangle
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Segment3<Real>> intersection(const Triangle3& other) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Vector3<Real>> point1 = intersection(other.edge(i));
            if (point1.has_value()) {
                inters.insert(*point1);
            }
            const std::optional<Vector3<Real>> point2 = other.intersection(edge(i));
            if (point2.has_value()) {
                inters.insert(*point2);
            }
            if (inters.size() >= 2) {
                return Segment3<Real> { inters.data()[0], inters.data()[1] };
            }
        }
        if (inters.empty()) {
            return std::nullopt;
        }
        if (inters.size() == 1) {
            return Segment3<Real> { inters.data()[0], inters.data()[0] };
        }
        return Segment3<Real> { inters.data()[0], inters.data()[1] };
    }

    /**
     * Determine if coincident with another triangle.
     * This is done by checking if the vertices are approximately equal order independently.
     * @param other Other triangle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coincident(const Triangle3& other) const
    {
        constexpr std::array<std::array<uint8_t, 3>, 6> permutations {
            { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 2, 0, 1 }, { 1, 2, 0 }, { 2, 1, 0 } }
        };
        for (const std::array<uint8_t, 3> permutation : permutations) {
            bool match = true;
            for (uint8_t i = 0; i < 3; ++i) {
                if (!vertices[i].approx_equal(other.vertices[permutation[i]])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    }

    /**
     * Transform vertices about an origin by a basis.
     * @param origin Transform origin.
     * @param by Basis.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform_at(const Vector3<Real> origin, const Basis3<Real>& by) const
    {
        return { vertices[0].transform_at(origin, by),
                 vertices[1].transform_at(origin, by),
                 vertices[2].transform_at(origin, by) };
    }

    /**
     * Transform vertices about the global origin by a basis.
     * @param by Basis.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform(const Basis3<Real>& by) const
    {
        return { vertices[0].transform(by), vertices[1].transform(by), vertices[2].transform(by) };
    }

    /**
     * Transform vertices about an origin by a transformation matrix.
     * @param origin Transform origin.
     * @param by Transformation matrix.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform_at(const Vector3<Real> origin, const Transform3<Real>& by) const
    {
        return { vertices[0].transform_at(origin, by, static_cast<Real>(1)),
                 vertices[1].transform_at(origin, by, static_cast<Real>(1)),
                 vertices[2].transform_at(origin, by, static_cast<Real>(1)) };
    }

    /**
     * Transform vertices about the global origin by a transformation matrix.
     * @param by Transformation matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Triangle3 transform(const Transform3<Real>& by) const
    {
        return { vertices[0].transform(by, static_cast<Real>(1)),
                 vertices[1].transform(by, static_cast<Real>(1)),
                 vertices[2].transform(by, static_cast<Real>(1)) };
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    constexpr Triangle3 translate(const Vector3<Real>& offset) const
    {
        return { vertices[0].translate(offset), vertices[1].translate(offset), vertices[2].translate(offset) };
    }

    /**
     * Scale about an origin.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { vertices[0].scale_at(scale_origin, factor),
                 vertices[1].scale_at(scale_origin, factor),
                 vertices[2].scale_at(scale_origin, factor) };
    }

    /**
     * Scale about the global origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 scale(const Vector3<Real>& factor) const
    {
        return { vertices[0].scale(factor), vertices[1].scale(factor), vertices[2].scale(factor) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param rotate_origin Rotation origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    Triangle3 rotate_axis_angle_at(
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { vertices[0].rotate_axis_angle_at(rotate_origin, axis, angle),
                 vertices[1].rotate_axis_angle_at(rotate_origin, axis, angle),
                 vertices[2].rotate_axis_angle_at(rotate_origin, axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    Triangle3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { vertices[0].rotate_axis_angle(axis, angle),
                 vertices[1].rotate_axis_angle(axis, angle),
                 vertices[2].rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    constexpr Triangle3 rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { vertices[0].rotate_quaternion_at(rotate_origin, quaternion),
                 vertices[1].rotate_quaternion_at(rotate_origin, quaternion),
                 vertices[2].rotate_quaternion_at(rotate_origin, quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    constexpr Triangle3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { vertices[0].rotate_quaternion(quaternion),
                 vertices[1].rotate_quaternion(quaternion),
                 vertices[2].rotate_quaternion(quaternion) };
    }

    /**
     * Shear about an origin along the x-axis.
     * @param shear_origin Shear origin.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_x_at(const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { vertices[0].shear_x_at(shear_origin, factor_y, factor_z),
                 vertices[1].shear_x_at(shear_origin, factor_y, factor_z),
                 vertices[2].shear_x_at(shear_origin, factor_y, factor_z) };
    }

    /**
     * Shear about the global origin along the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return { vertices[0].shear_x(factor_y, factor_z),
                 vertices[1].shear_x(factor_y, factor_z),
                 vertices[2].shear_x(factor_y, factor_z) };
    }

    /**
     * Shear about an origin along the y-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return
     */
    // tested
    constexpr Triangle3 shear_y_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { vertices[0].shear_y_at(shear_origin, factor_x, factor_z),
                 vertices[1].shear_y_at(shear_origin, factor_x, factor_z),
                 vertices[2].shear_y_at(shear_origin, factor_x, factor_z) };
    }

    /**
     * Shear about the global origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { vertices[0].shear_y(factor_x, factor_z),
                 vertices[1].shear_y(factor_x, factor_z),
                 vertices[2].shear_y(factor_x, factor_z) };
    }

    /**
     * Shear about an origin along the z-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_z_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { vertices[0].shear_z_at(shear_origin, factor_x, factor_y),
                 vertices[1].shear_z_at(shear_origin, factor_x, factor_y),
                 vertices[2].shear_z_at(shear_origin, factor_x, factor_y) };
    }

    /**
     * Shear about the global origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { vertices[0].shear_z(factor_x, factor_y),
                 vertices[1].shear_z(factor_x, factor_y),
                 vertices[2].shear_z(factor_x, factor_y) };
    }

    /**
     * Determine if all vertices are approximately equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool approx_equal(const Triangle3& other) const
    {
        return vertices[0].approx_equal(other.vertices[0]) && vertices[1].approx_equal(other.vertices[1])
            && vertices[2].approx_equal(other.vertices[2]);
    }

    /**
     * Determine if all vertices are exactly equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator==(const Triangle3& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    /**
     * Determine if any vertices are not equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator!=(const Triangle3& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    /**
     * Lexicographical comparison in the order of vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator<(const Triangle3& other) const
    {
        if (vertices[0] != other.vertices[0]) {
            return vertices[0] < other.vertices[0];
        }
        if (vertices[1] != other.vertices[1]) {
            return vertices[1] < other.vertices[1];
        }
        return vertices[2] < vertices[2];
    }
};

template <typename Real>
class Rectangle3 {
public:
    /**
     * Center.
     */
    Vector3<Real> center;
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
        : center { Vector3<Real>::zero() }
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
    constexpr Rectangle3(
        const Vector3<Real>& center, const Vector3<Real>& half_span_u, const Vector3<Real>& half_span_v)
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
    constexpr static Rectangle3 from_xy_offset_size(const Vector3<Real>& offset, const Real size_x, const Real size_y)
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
    constexpr static Rectangle3 from_xz_offset_size(const Vector3<Real>& offset, const Real size_x, const Real size_z)
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
    constexpr static Rectangle3 from_yz_offset_size(const Vector3<Real>& offset, const Real size_y, const Real size_z)
    {
        return { offset,
                 size_y / static_cast<Real>(2) * Vector3<Real>::axis_y(),
                 size_z / static_cast<Real>(2) * Vector3<Real>::axis_z() };
    }

    /**
     * Determine if valid. Validility is determined if half_span_u and half_span_v are orthogonal.
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
    [[nodiscard]] constexpr Vector3<Real> vertex(const uint8_t index) const
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
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Rectangle3", index < 4);
        switch (index) {
        case 1:
            return { vertex(1), vertex(3) };
        case 2:
            return { vertex(3), vertex(2) };
        case 3:
            return { vertex(2), vertex(0) };
        default:
            return { vertex(0), vertex(1) };
        }
    }

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

    // TODO: test
    [[nodiscard]] constexpr bool coplanar(const Plane<Real>& plane) const
    {
        return half_span_u.perpendicular(plane.normal) && half_span_v.perpendicular(plane.normal);
    }

    /**
     * Determine if contains a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        const Vector3<Real> diff = point - center;
        if (!approx_zero(diff.dot(normal))) {
            return false;
        }
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            return point.approx_equal(center);
        }
        if (approx_zero(u_dot)) {
            return Segment3<Real> { center - half_span_v, center + half_span_v }.contains(point);
        }
        if (approx_zero(v_dot)) {
            return Segment3<Real> { center - half_span_u, center + half_span_u }.contains(point);
        }
        const Vector2<Real> local { diff.dot(half_span_u) / u_dot, diff.dot(half_span_v) / v_dot };
        return approx_greater_equal(local.x, static_cast<Real>(-1)) && approx_less_equal(local.x, static_cast<Real>(1))
            && approx_greater_equal(local.y, static_cast<Real>(-1)) && approx_less_equal(local.y, static_cast<Real>(1));
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - center;
        const Vector2<Real> local = { diff.dot(half_span_u), diff.dot(half_span_v) };
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        const Vector2<Real> local_clamped = local.clamp({ -u_dot, -v_dot }, { u_dot, v_dot });
        const Vector3<Real> closest = center
            + (approx_zero(u_dot) ? static_cast<Real>(0) : local_clamped.x / u_dot) * half_span_u
            + (approx_zero(v_dot) ? static_cast<Real>(0) : local_clamped.y / v_dot) * half_span_v;
        return point.distance_sqrd(closest);
    }

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = edge(i).distance(line);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        Real min_dist = distance(ray.origin);
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = edge(i).distance(ray);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const
    {
        if (intersects(segment)) {
            return static_cast<Real>(0);
        }
        Real min_dist = min(distance(segment.start), distance(segment.end));
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = edge(i).distance(segment);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const
    {
        if (intersects(plane)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = edge(i).distance(plane);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const
    {
        if (intersects(triangle)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 3; ++i) {
            const Real dist = distance(triangle.edge(i));
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle3& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (uint8_t i = 0; i < 4; ++i) {
            const Real dist = distance(other.edge(i));
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    // TODO
    [[nodiscard]] Real distance(const Sphere<Real>& sphere) const;

    // TODO
    [[nodiscard]] Real distance(const AlignedBox<Real>& box) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            return line.contains(center);
        }
        if (approx_zero(u_dot)) {
            return line.intersects(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return line.intersects(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        if (line.direction.perpendicular(normal)) {
            for (uint8_t i = 0; i < 4; ++i) {
                if (edge(i).intersects(line)) {
                    return true;
                }
            }
            return false;
        }
        const Vector3<Real> diff = center - line.origin;
        const Real dir_dot_normal = line.direction.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        const Vector3<Real> plane_inter = line.origin + line.direction * t;
        return contains(plane_inter);
    }

    /**
     * Intersection point with line. Returns null if coplanar.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
    {
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            if (!line.contains(center)) {
                return std::nullopt;
            }
            return center;
        }
        if (approx_zero(u_dot)) {
            return line.intersection(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return line.intersection(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        if (line.direction.perpendicular(normal)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = center - line.origin;
        const Real dir_dot_normal = line.direction.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        const Vector3<Real> plane_inter = line.origin + line.direction * t;
        if (!contains(plane_inter)) {
            return std::nullopt;
        }
        return plane_inter;
    }

    /**
     * Determine if intersects with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            return ray.contains(center);
        }
        if (approx_zero(u_dot)) {
            return ray.intersects(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return ray.intersects(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        if (ray.direction.perpendicular(normal)) {
            for (uint8_t i = 0; i < 4; ++i) {
                if (edge(i).intersects(ray)) {
                    return true;
                }
            }
            return false;
        }
        const Vector3<Real> diff = center - ray.origin;
        const Real dir_dot_normal = ray.direction.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        if (approx_less_zero(t)) {
            return false;
        }
        const Vector3<Real> plane_inter = ray.origin + ray.direction * t;
        return contains(plane_inter);
    }

    /**
     * Intersection point with ray. Returns null if coplanar.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const
    {
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            if (!ray.contains(center)) {
                return std::nullopt;
            }
            return center;
        }
        if (approx_zero(u_dot)) {
            return ray.intersection(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return ray.intersection(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        if (ray.direction.perpendicular(normal)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = center - ray.origin;
        const Real dir_dot_normal = ray.direction.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        if (approx_less_zero(t)) {
            return std::nullopt;
        }
        const Vector3<Real> plane_inter = ray.origin + ray.direction * t;
        if (!contains(plane_inter)) {
            return std::nullopt;
        }
        return plane_inter;
    }

    /**
     * Determine if intersects line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const
    {
        if (segment.start.approx_equal(segment.end)) {
            return contains(segment.start);
        }
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            return segment.contains(center);
        }
        if (approx_zero(u_dot)) {
            return segment.intersects(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return segment.intersects(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        if (segment.direction_unnormalized().perpendicular(normal)) {
            for (uint8_t i = 0; i < 4; ++i) {
                if (edge(i).intersects(segment)) {
                    return true;
                }
            }
            return contains(segment.start) && contains(segment.end);
        }
        const Vector3<Real> diff = center - segment.start;
        const Vector3<Real> segment_dir = segment.direction_unnormalized();
        const Real dir_dot_normal = segment_dir.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return false;
        }
        const Vector3<Real> plane_inter = segment.start + segment_dir * t;
        return contains(plane_inter);
    }

    /**
     * Intersection point with line segment. Returns null if coplanar.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3<Real> segment) const
    {
        if (segment.start.approx_equal(segment.end)) {
            if (!contains(segment.start)) {
                return std::nullopt;
            }
            return segment.start;
        }
        const Real u_dot = half_span_u.dot(half_span_u);
        const Real v_dot = half_span_v.dot(half_span_v);
        if (approx_zero(u_dot) && approx_zero(v_dot)) {
            if (!segment.contains(center)) {
                return std::nullopt;
            }
            return center;
        }
        if (approx_zero(u_dot)) {
            return segment.intersection(Segment3<Real> { center - half_span_v, center + half_span_v });
        }
        if (approx_zero(v_dot)) {
            return segment.intersection(Segment3<Real> { center - half_span_u, center + half_span_u });
        }
        const Vector3<Real> normal = half_span_u.cross(half_span_v);
        const Vector3<Real> segment_dir = segment.direction_unnormalized();
        if (segment_dir.perpendicular(normal)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = center - segment.start;
        const Real dir_dot_normal = segment_dir.dot(normal);
        const Real t = diff.dot(normal) / dir_dot_normal;
        if (approx_less_zero(t) || approx_greater(t, static_cast<Real>(1))) {
            return std::nullopt;
        }
        const Vector3<Real> plane_inter = segment.start + segment_dir * t;
        if (!contains(plane_inter)) {
            return std::nullopt;
        }
        return plane_inter;
    }

    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Plane<Real>& plane) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(edge(i)); inter.has_value()) {
                inters.insert(inter.value());
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        if (inters.empty()) {
            return std::nullopt;
        }
        if (inters.size() == 1) {
            return Segment3<Real> { inters.data()[0], inters.data()[0] };
        }
        return Segment3<Real> { inters.data()[0], inters.data()[1] };
    }

    /**
     * Determine if intersects plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (edge(i).intersects(plane)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Intersection points between edges.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections3<Real> edge_intersections(const Plane<Real>& plane) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (const Segment3<Real> e = edge(i); !e.start.approx_equal(e.end) && plane.coplanar(e)) {
                return {};
            }
        }
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Vector3<Real>> inter = edge(i).intersection(plane); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        return inters;
    }

    /**
     * Determine if intersects triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle3<Real>& triangle) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (intersects(triangle.edge(i))) {
                return true;
            }
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (triangle.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    /**
     *Intersection points between the edges between this rectangle and a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections3<Real> edge_intersections(const Triangle3<Real>& triangle) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 3; ++i) {
            if (const std::optional<Vector3<Real>> inter = intersection(triangle.edge(i)); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Vector3<Real>> inter = triangle.intersection(edge(i)); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        return inters;
    }

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
    [[nodiscard]] Intersections3<Real> edge_intersections(const Rectangle3& other) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Vector3<Real>> inter = intersection(other.edge(i)); inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    return inters;
                }
            }
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (const std::optional<Vector3<Real>> inter = other.intersection(edge(i)); inter.has_value()) {
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
        const Vector3<Real>& origin, const Vector3<Real>& axis, const Real angle) const
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
        const Vector3<Real>& origin, const Quaternion<Real>& quaternion) const
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
    [[nodiscard]] constexpr Rectangle3 scale_at(const Vector3<Real>& origin, const Vector3<Real>& factor) const
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
        std::array<Vector3<Real>, 4> verts { vertex(0), vertex(1), vertex(2), vertex(3) };
        std::array<Vector3<Real>, 4> verts_other { other.vertex(0), other.vertex(1), other.vertex(2), other.vertex(3) };
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

/**
 * Sphere.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Sphere {
public:
    /**
     * Center
     */
    Vector3<Real> center;

    /**
     * Radius
     */
    Real radius;

    /**
     * Default initialize at the global origin and a radius of 1.
     */
    // tested
    constexpr Sphere()
        : center { Vector3<Real>::zero() }
        , radius { static_cast<Real>(1) }
    {
    }

    /**
     * Initialize with center and radius.
     * @param center Center.
     * @param radius Radius.
     */
    // tested
    constexpr Sphere(const Vector3<Real>& center, const Real radius)
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
    static Sphere from_center_surface_point(const Vector3<Real>& center, const Vector3<Real>& point)
    {
        return Sphere(center, center.distance(point));
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
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
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
    [[nodiscard]] Real signed_distance(const Vector3<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    /**
     * Closest distance to a point. Zero if point is inside the sphere.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    /**
     * Closest distance to a line. Zero if intersects or is inside the sphere.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        return max(static_cast<Real>(0), line.distance(center) - radius);
    }

    /**
     * Closest distance to a ray. Zero if intersects or is inside the sphere.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        return max(static_cast<Real>(0), ray.distance(center) - radius);
    }

    /**
     * Closest distance to a line segment. Zero if intersects or is inside the sphere.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const
    {
        return max(static_cast<Real>(0), segment.distance(center) - radius);
    }

    /**
     * Closest distance to a plane. Zero if intersects.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const
    {
        return max(static_cast<Real>(0), plane.distance(center) - radius);
    }

    /**
     * Closest distance to a triangle. Zero if intersects or if contains triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const
    {
        return max(static_cast<Real>(0), triangle.distance(center) - radius);
    }

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
    [[nodiscard]] constexpr Vector3<Real> point_at(const Vector3<Real>& dir) const
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
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = line.origin - center;
        const Real a = line.direction.dot(line.direction);
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        return approx_greater_equal_zero(discriminant);
    }

    /**
     * Intersection points with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections3<Real> surface_intersections(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = line.origin - center;
        const Real a = line.direction.dot(line.direction);
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return {};
        }
        if (approx_zero(discriminant)) {
            const Real t = -b / (static_cast<Real>(2) * a);
            const Vector3<Real> p = line.origin + line.direction * t;
            return { p };
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const Vector3<Real> p1 = line.origin + line.direction * t1;
        const Vector3<Real> p2 = line.origin + line.direction * t2;
        return { p1, p2 };
    }

    /**
     * Determine if intersects with a ray. Being inside the sphere is considered an intersection.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = ray.origin - center;
        const Real a = ray.direction.dot(ray.direction);
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        return approx_greater_equal_zero(t1) || approx_greater_equal_zero(t2);
    }

    /**
     * Intersection points with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections3<Real> surface_intersections(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = ray.origin - center;
        const Real a = ray.direction.dot(ray.direction);
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return {};
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        Intersections3<Real> inters;
        if (approx_greater_equal_zero(t1)) {
            inters.insert(ray.origin + ray.direction * t1);
        }
        if (approx_greater_equal_zero(t2)) {
            inters.insert(ray.origin + ray.direction * t2);
        }
        return inters;
    }

    /**
     * Determine if intersects with a line segment. Being inside the sphere is considered an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment3<Real>& segment) const
    {
        const Vector3<Real> seg_dir = segment.direction_unnormalized();
        const Vector3<Real> dir = segment.start - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * dir.dot(seg_dir);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return false;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const Real seg_length = segment.length();
        return (approx_greater_equal_zero(t1) && approx_less_equal(t1, static_cast<Real>(1)))
            || (approx_greater_equal_zero(t2) && approx_less_equal(t2, static_cast<Real>(1)));
    }

    /**
     * Intersection points with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections3<Real> surface_intersections(const Segment3<Real>& segment) const
    {
        const Vector3<Real> seg_dir = segment.direction_unnormalized();
        const Vector3<Real> dir = segment.start - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * dir.dot(seg_dir);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return {};
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const Real seg_length = segment.length();
        Intersections3<Real> inters;
        if (approx_greater_equal_zero(t1) && approx_less_equal(t1, static_cast<Real>(1))) {
            inters.insert(segment.start + seg_dir * t1);
        }
        if (approx_greater_equal_zero(t2) && approx_less_equal(t2, static_cast<Real>(1))) {
            inters.insert(segment.start + seg_dir * t2);
        }
        return inters;
    }

    // TODO: test
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const
    {
        return approx_less_equal(rectangle.distance_sqrd(center), sqrd(radius));
    }

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
    [[nodiscard]] constexpr bool tangent(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = line.origin - center;
        const Real a = line.direction.dot(line.direction);
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        return approx_zero(discriminant);
    }

    /**
     * Determine if tangent to ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = ray.origin - center;
        const Real a = ray.direction.dot(ray.direction);
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        if (const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c; !approx_zero(discriminant)) {
            return false;
        }
        const Real t = -b / (static_cast<Real>(2) * a);
        return approx_greater_equal_zero(t);
    }

    /**
     * Determine if tangent to line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Segment3<Real>& segment) const
    {
        const Vector3<Real> seg_dir = segment.direction();
        const Vector3<Real> dir = segment.start - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * dir.dot(seg_dir);
        const Real c = dir.dot(dir) - sqrd(radius);
        if (const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c; !approx_zero(discriminant)) {
            return false;
        }
        const Real t = -b / (static_cast<Real>(2) * a);
        return approx_greater_equal_zero(t) && approx_less_equal(t, segment.length());
    }

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
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
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
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
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
    [[nodiscard]] constexpr Sphere scale_at(const Vector3<Real>& scale_origin, const Real factor) const
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

template <typename Real>
class AlignedBox {
public:
    /**
     * Minimum corner point.
     */
    Vector3<Real> min;

    /**
     * Maximum corner point.
     */
    Vector3<Real> max;

    /**
     * Default initialize with zero min and max.
     */
    // tested
    constexpr AlignedBox()
        : min { Vector3<Real>::zero() }
        , max { Vector3<Real>::zero() }
    {
    }

    /**
     * Initialize with min and max. No validation to ensure min/max is done.
     * Use from_bounding_points if validation is desired.
     * @param min Minimum corner point.
     * @param max Maximum corner point.
     */
    // tested
    constexpr AlignedBox(const Vector3<Real>& min, const Vector3<Real>& max)
        : min { min }
        , max { max }
    {
    }

    /**
     * The smallest bounding box containing two points.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_points(const Vector3<Real>& point1, const Vector3<Real>& point2)
    {
        AlignedBox box { point1, point1 };
        box = box.extend_bounding(point2);
        return box;
    }

    /**
     * The smallest bounding box containing a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_segment(const Segment3<Real>& segment)
    {
        return from_bounding_points(segment.start, segment.end);
    }

    /**
     * The smallest bounding box containing a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_triangle(const Triangle3<Real>& triangle)
    {
        AlignedBox box { triangle.vertices[0], triangle.vertices[0] };
        box = box.extend_bounding(triangle.vertices[1]);
        box = box.extend_bounding(triangle.vertices[2]);
        return box;
    }

    /**
     * The smallest bounding box containing a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_rectangle(const Rectangle3<Real>& rectangle)
    {
        std::array<Vector3<Real>, 4> vertices {
            rectangle.vertex(0), rectangle.vertex(1), rectangle.vertex(2), rectangle.vertex(3)
        };
        AlignedBox box { vertices[0], vertices[0] };
        box = box.extend_bounding(vertices[1]);
        box = box.extend_bounding(vertices[2]);
        box = box.extend_bounding(vertices[3]);
        return box;
    }

    /**
     * The smallest bounding box containing a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_sphere(const Sphere<Real>& sphere)
    {
        const Vector3<Real> min = sphere.center - Vector3<Real>::all(sphere.radius);
        const Vector3<Real> max = sphere.center + Vector3<Real>::all(sphere.radius);
        return { min, max };
    }

    /**
     * Vertex at an index.
     * @param index Index from 0-7.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("AlignedBox", index < 8);
        switch (index) {
        case 0: // -x -y -z
            return min;
        case 1: // -x -y +z
            return { min.x, min.y, max.z };
        case 2: // -x +y -z
            return { min.x, max.y, min.z };
        case 3: // -x +y +z
            return { min.x, max.y, max.z };
        case 4: // +x -y -z
            return { max.x, min.y, min.z };
        case 5: // +x -y +z
            return { max.x, min.y, max.z };
        case 6: // +x +y -z
            return { max.x, max.y, min.z };
        default: // +x +y +z
            return max;
        }
    }

    /**
     * Edge at an index.
     * @param index Index from 0-11.
     * @return Result.
     */
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("AlignedBox", index < 12);
        switch (index) {
        case 0: // -x -y
            return { vertex(0), vertex(1) };
        case 1: // -x +y
            return { vertex(2), vertex(3) };
        case 2: // +x -y
            return { vertex(4), vertex(5) };
        case 3: // +x +y
            return { vertex(6), vertex(7) };
        case 4: // -x -z
            return { vertex(0), vertex(2) };
        case 5: // -x +z
            return { vertex(1), vertex(3) };
        case 6: // +x -z
            return { vertex(4), vertex(6) };
        case 7: // +x +z
            return { vertex(5), vertex(7) };
        case 8: // -y -z
            return { vertex(0), vertex(4) };
        case 9: // -y +z
            return { vertex(1), vertex(5) };
        case 10: // +y -z
            return { vertex(2), vertex(6) };
        default: // +y +z
            return { vertex(3), vertex(7) };
        }
    }

    /**
     * Face at an index.
     * @param index Index from [0-5].
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3<Real> face(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("AlignedBox", index < 6);
        const Vector3<Real> half_size = size() / static_cast<Real>(2);
        switch (index) {
        case 0: // -x
            return { Segment3<Real> { vertex(0), vertex(3) }.midpoint(),
                     Vector3<Real>::axis_y() * half_size.y,
                     Vector3<Real>::axis_z() * half_size.z };
        case 1: // +x
            return { Segment3<Real> { vertex(4), vertex(7) }.midpoint(),
                     Vector3<Real>::axis_y() * half_size.y,
                     Vector3<Real>::axis_z() * half_size.z };
        case 2: // -y
            return { Segment3<Real> { vertex(0), vertex(5) }.midpoint(),
                     Vector3<Real>::axis_x() * half_size.x,
                     Vector3<Real>::axis_z() * half_size.z };
        case 3: // +y
            return { Segment3<Real> { vertex(2), vertex(7) }.midpoint(),
                     Vector3<Real>::axis_x() * half_size.x,
                     Vector3<Real>::axis_z() * half_size.z };
        case 4: // -z
            return { Segment3<Real> { vertex(0), vertex(6) }.midpoint(),
                     Vector3<Real>::axis_x() * half_size.x,
                     Vector3<Real>::axis_y() * half_size.y };
        default: // +z
            return { Segment3<Real> { vertex(1), vertex(7) }.midpoint(),
                     Vector3<Real>::axis_x() * half_size.x,
                     Vector3<Real>::axis_y() * half_size.y };
        }
    }

    /**
     * Size.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> size() const
    {
        return max - min;
    }

    /**
     * Volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real volume() const
    {
        const Vector3<Real> s = size();
        return s.x * s.y * s.z;
    }

    /**
     * Surface area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real surface_area() const
    {
        const Vector3<Real> s = size();
        return static_cast<Real>(2) * (s.x * s.y + s.x * s.z + s.y * s.z);
    }

    /**
     * Extend box to fit a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox extend_bounding(const Vector3<Real>& point) const
    {
        return { { nnm::min(min.x, point.x), nnm::min(min.y, point.y), nnm::min(min.z, point.z) },
                 { nnm::max(max.x, point.x), nnm::max(max.y, point.y), nnm::max(max.z, point.z) } };
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        return approx_greater_equal(point.x, min.x) && approx_less_equal(point.x, max.x)
            && approx_greater_equal(point.y, min.y) && approx_less_equal(point.y, max.y)
            && approx_greater_equal(point.z, min.z) && approx_less_equal(point.z, max.z);
    }

    /**
     * Center by volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> center() const
    {
        return (min + max) / static_cast<Real>(2);
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Vector3<Real>& point) const
    {
        const Vector3<Real> closest = point.clamp(min, max);
        return closest.distance_sqrd(point);
    }

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(line)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(ray)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const
    {
        if (contains(segment.start) || contains(segment.end)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(segment)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(plane)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle3<Real>& triangle) const
    {
        if (contains(triangle.centroid())) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(triangle)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const
    {
        if (contains(rectangle.center)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(rectangle)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const
    {
        Vector3<Real> closest = sphere.center.clamp(min, max);
        const Real center_dist_sqrd = (closest - sphere.center).length_sqrd();
        return approx_less_equal(center_dist_sqrd, sqrd(sphere.radius));
    }

    /**
     * Determine if intersects another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedBox& other) const
    {
        return approx_less_equal(min.x, other.max.x) && approx_less_equal(other.min.x, max.x)
            && approx_less_equal(min.y, other.max.y) && approx_less_equal(other.min.y, max.y)
            && approx_less_equal(min.z, other.max.z) && approx_less_equal(other.min.z, max.z);
    }

    /**
     * Surface intersection points with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Line3<Real>& line) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(line);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    /**
     * Surface intersection points with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Ray3<Real>& ray) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(ray);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    /**
     * Surface intersection points with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Segment3<Real>& segment) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(segment);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    /**
     * Aligned box formed by the intersection with another aligned box. Null if no intersection.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<AlignedBox> intersection(const AlignedBox& other) const
    {
        const AlignedBox inter {
            { nnm::max(min.x, other.min.x), nnm::max(min.y, other.min.y), nnm::max(min.z, other.min.z) },
            { nnm::min(max.x, other.max.x), nnm::min(max.y, other.max.y), nnm::min(max.z, other.max.z) }
        };
        if (!inter.valid()) {
            return std::nullopt;
        }
        return inter;
    }

    /**
     * Determine if valid. The aligned box is valid if each component of the 'min' is
     * less than or equal to each corresponding component of 'max'.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        return approx_less_equal(min.x, max.x) && approx_less_equal(min.y, max.y) && approx_less_equal(min.z, max.z);
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox translate(const Vector3<Real>& offset) const
    {
        return { min.translate(offset), max.translate(offset) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param origin Rotation origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] AlignedBox rotate_axis_angle_at(
        const Vector3<Real>& origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { min.rotate_axis_angle_at(origin, axis, angle), max.rotate_axis_angle_at(origin, axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] AlignedBox rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { min.rotate_axis_angle(axis, angle), max.rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox rotate_quaternion_at(
        const Vector3<Real>& origin, const Quaternion<Real>& quaternion) const
    {
        return { min.rotate_quaternion_at(origin, quaternion), max.rotate_quaternion_at(origin, quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { min.rotate_quaternion(quaternion), max.rotate_quaternion(quaternion) };
    }

    /**
     * Scale about an origin by a factor.
     * @param origin Scaling origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox scale_at(const Vector3<Real>& origin, const Vector3<Real>& factor) const
    {
        return { min.scale_at(origin, factor), max.scale_at(origin, factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scaling factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox scale(const Vector3<Real>& factor) const
    {
        return { min.scale(factor), max.scale(factor) };
    }

    /**
     * Determine min and max are approximately equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const AlignedBox& other) const
    {
        return min.approx_equal(other.min) && max.approx_equal(other.max);
    }

    /**
     * Determine if min and max are exactly equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const AlignedBox& other) const
    {
        return min == other.min && max == other.max;
    }

    /**
     * Determine if min and max are not exactly equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const AlignedBox& other) const
    {
        return min != other.min || max != other.max;
    }

    /**
     * Lexicographical comparison in the order of min then max.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const AlignedBox& other) const
    {
        if (min != other.min) {
            return min < other.min;
        }
        return max < other.max;
    }
};

/**
 * Oriented rectangle prism (cuboid) defined by a center and orthogonal half-spans.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Box {
public:
    /**
     * Geometric center (centroid).
     */
    Vector3<Real> center;

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
        : center { Vector3<Real>::zero() }
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
        const Vector3<Real>& center,
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
        : center { Vector3<Real>(other.center) }
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
    constexpr static Box from_center_size(const Vector3<Real>& center, const Vector3<Real>& size)
    {
        return { center,
                 Vector3<Real>::axis_x() * size.x / static_cast<Real>(2),
                 Vector3<Real>::axis_y() * size.y / static_cast<Real>(2),
                 Vector3<Real>::axis_z() * size.z / static_cast<Real>(2) };
    }

    /**
     * Vertex at an index,
     * @param index Index [0-7] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> vertex(const uint8_t index) const
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
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Box", index < 12);
        switch (index) {
        case 0: // -u -v
            return { vertex(0), vertex(1) };
        case 1: // -u +v
            return { vertex(2), vertex(3) };
        case 2: // +u -v
            return { vertex(4), vertex(5) };
        case 3: // +u +v
            return { vertex(6), vertex(7) };
        case 4: // -u -w
            return { vertex(0), vertex(2) };
        case 5: // -u +w
            return { vertex(1), vertex(3) };
        case 6: // +u -w
            return { vertex(4), vertex(6) };
        case 7: // +u +w
            return { vertex(5), vertex(7) };
        case 8: // -v -w
            return { vertex(0), vertex(4) };
        case 9: // -v +w
            return { vertex(1), vertex(5) };
        case 10: // +v -w
            return { vertex(2), vertex(6) };
        case 11: // +v +w
        default:
            return { vertex(3), vertex(7) };
        }
    }

    /**
     * Face at an index.
     * @param index Index [0-5] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3<Real> face(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Box", index < 6);
        switch (index) {
        case 0: // -u
            return { Segment3<Real>(vertex(0), vertex(3)).midpoint(), half_span_v, half_span_w };
        case 1: // +u
            return { Segment3<Real>(vertex(4), vertex(7)).midpoint(), half_span_v, half_span_w };
        case 2: // -v
            return { Segment3<Real>(vertex(0), vertex(5)).midpoint(), half_span_u, half_span_w };
        case 3: // +v
            return { Segment3<Real>(vertex(2), vertex(7)).midpoint(), half_span_u, half_span_w };
        case 4: // -w
            return { Segment3<Real>(vertex(0), vertex(6)).midpoint(), half_span_u, half_span_v };
        case 5: // +w
        default:
            return { Segment3<Real>(vertex(1), vertex(7)).midpoint(), half_span_u, half_span_v };
        }
    }

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

    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - center;
        return approx_less_equal(abs(diff.dot(half_span_u)), half_span_u.length_sqrd())
            && approx_less_equal(abs(diff.dot(half_span_v)), half_span_v.length_sqrd())
            && approx_less_equal(abs(diff.dot(half_span_w)), half_span_w.length_sqrd());
    }

    [[nodiscard]] constexpr Real distance_sqrd(const Vector3<Real>& point) const
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

    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(line)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(ray)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const
    {
        if (contains(segment.start) || contains(segment.end)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(segment)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const
    {
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(plane)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool intersects(const Triangle3<Real>& triangle) const
    {
        if (contains(triangle.centroid())) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(triangle)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const
    {
        if (contains(rectangle.center)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(rectangle)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const
    {
        if (contains(sphere.center)) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(sphere)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& aligned_box) const
    {
        if (contains(aligned_box.center())) {
            return true;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (face(i).intersects(aligned_box)) {
                return true;
            }
        }
        return false;
    }

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

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Line3<Real>& line) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(line);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Ray3<Real>& ray) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(ray);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Segment3<Real>& segment) const
    {
        Intersections3<Real> inters;
        for (uint8_t i = 0; i < 6; ++i) {
            const std::optional<Vector3<Real>> inter = face(i).intersection(segment);
            if (inter.has_value()) {
                inters.insert(*inter);
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Box translate(const Vector3<Real>& offset) const
    {
        return { center.translate(offset), half_span_u, half_span_v, half_span_w };
    }

    [[nodiscard]] Box rotate_axis_angle(
        const Vector3<Real>& axis, const Real angle, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return { center.rotate_axis_angle_at(origin, axis, angle),
                 half_span_u.rotate_axis_angle(axis, angle),
                 half_span_v.rotate_axis_angle(axis, angle),
                 half_span_w.rotate_axis_angle(axis, angle) };
    }

    [[nodiscard]] constexpr Box rotate_quaternion(
        const Quaternion<Real>& quaternion, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return { center.rotate_quaternion_at(origin, quaternion),
                 half_span_u.rotate_quaternion(quaternion),
                 half_span_v.rotate_quaternion(quaternion),
                 half_span_w.rotate_quaternion(quaternion) };
    }

    [[nodiscard]] constexpr Box scale(
        const Vector3<Real>& factor, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return { center.scale_at(origin, factor),
                 half_span_u.scale(factor),
                 half_span_v.scale(factor),
                 half_span_w.scale(factor) };
    }

    [[nodiscard]] bool coincident(const Box& other) const
    {
        auto sorted_vertices = [](const Box& b) -> std::array<Vector3<Real>, 8> {
            std::array<Vector3<Real>, 8> verts { b.vertex(0), b.vertex(1), b.vertex(2), b.vertex(3),
                                                 b.vertex(4), b.vertex(5), b.vertex(6), b.vertex(7) };
            std::sort(verts.begin(), verts.end());
            return verts;
        };
        const std::array<Vector3<Real>, 8> verts = sorted_vertices(*this);
        const std::array<Vector3<Real>, 8> verts_other = sorted_vertices(other);
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

template <typename Real>
class Frustum {
public:
    Plane<Real> near_plane;
    Plane<Real> far_plane;
    Plane<Real> left_plane;
    Plane<Real> right_plane;
    Plane<Real> bottom_plane;
    Plane<Real> top_plane;

    constexpr Frustum()
        : near_plane { Plane<Real> {} }
        , far_plane { Plane<Real> {} }
        , left_plane { Plane<Real> {} }
        , right_plane { Plane<Real> {} }
        , bottom_plane { Plane<Real> {} }
        , top_plane { Plane<Real> {} }
    {
    }

    constexpr Frustum(
        const Plane<Real> near_plane,
        const Plane<Real> far_plane,
        const Plane<Real> left_plane,
        const Plane<Real> right_plane,
        const Plane<Real> bottom_plane,
        const Plane<Real> top_plane)
        : near_plane { std::move(near_plane) }
        , far_plane { std::move(far_plane) }
        , left_plane { std::move(left_plane) }
        , right_plane { std::move(right_plane) }
        , bottom_plane { std::move(bottom_plane) }
        , top_plane { std::move(top_plane) }
    {
    }

    static Frustum from_camera_left_hand_pos_forward_up_fov_aspect_near_far(
        const Vector3<Real>& position,
        const Vector3<Real>& forward,
        const Vector3<Real>& up,
        const Real fov,
        const Real aspect,
        const Real near,
        const Real far)
    {
        Vector3<Real> corrected_up = up;
        if (forward.parallel(up)) {
            if (!forward.parallel(Vector3<Real>::axis_x())) {
                corrected_up = Vector3<Real>::axis_x();
            }
            else {
                corrected_up = Vector3<Real>::axis_y();
            }
        }
        const Vector3<Real> right = corrected_up.cross(forward).normalize();
        corrected_up = forward.cross(right).normalize();
        const Real tan_fov_y = nnm::tan(fov / static_cast<Real>(2));
        const Real near_height_half = tan_fov_y * near;
        const Real near_width_half = near_height_half * aspect;
        const Vector3<Real> near_origin = position + forward * near;

        const Plane<Real> near_plane { near_origin, forward };
        const Plane<Real> far_plane { position + forward * far, -forward };

        const Vector3<Real> left_origin = near_origin - right * near_width_half;
        const Vector3<Real> left_normal = corrected_up.cross(left_origin - position).normalize();
        const Plane<Real> left_plane { left_origin, left_normal };

        const Vector3<Real> right_origin = near_origin + right * near_width_half;
        const Vector3<Real> right_normal = (right_origin - position).cross(corrected_up).normalize();
        const Plane<Real> right_plane { right_origin, right_normal };

        const Vector3<Real> bottom_origin = near_origin - corrected_up * near_height_half;
        const Vector3<Real> bottom_normal = (bottom_origin - position).cross(right).normalize();
        const Plane<Real> bottom_plane { bottom_origin, bottom_normal };

        const Vector3<Real> top_origin = near_origin + corrected_up * near_height_half;
        const Vector3<Real> top_normal = right.cross(top_origin - position).normalize();
        const Plane<Real> top_plane { top_origin, top_normal };

        return { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    }

    static Frustum from_camera_right_hand_pos_forward_up_fov_aspect_near_far(
        const Vector3<Real>& position,
        const Vector3<Real>& forward,
        const Vector3<Real>& up,
        const Real fov,
        const Real aspect,
        const Real near,
        const Real far)
    {
        Vector3<Real> corrected_up = up;
        if (forward.parallel(up)) {
            if (!forward.parallel(Vector3<Real>::axis_x())) {
                corrected_up = Vector3<Real>::axis_x();
            }
            else {
                corrected_up = Vector3<Real>::axis_y();
            }
        }
        const Vector3<Real> right = forward.cross(corrected_up).normalize();
        corrected_up = right.cross(forward).normalize();
        const Real tan_fov_y = nnm::tan(fov / static_cast<Real>(2));
        const Real near_height_half = tan_fov_y * near;
        const Real near_width_half = near_height_half * aspect;
        const Vector3<Real> near_origin = position + forward * near;

        const Plane<Real> near_plane { near_origin, forward };
        const Plane<Real> far_plane { position + forward * far, -forward };

        const Vector3<Real> left_origin = near_origin - right * near_width_half;
        const Vector3<Real> left_normal = (left_origin - position).cross(corrected_up).normalize();
        const Plane<Real> left_plane { left_origin, left_normal };

        const Vector3<Real> right_origin = near_origin + right * near_width_half;
        const Vector3<Real> right_normal = corrected_up.cross(right_origin - position).normalize();
        const Plane<Real> right_plane { right_origin, right_normal };

        const Vector3<Real> bottom_origin = near_origin - corrected_up * near_height_half;
        const Vector3<Real> bottom_normal = right.cross(bottom_origin - position).normalize();
        const Plane<Real> bottom_plane { bottom_origin, bottom_normal };

        const Vector3<Real> top_origin = near_origin + corrected_up * near_height_half;
        const Vector3<Real> top_normal = (top_origin - position).cross(right).normalize();
        const Plane<Real> top_plane { top_origin, top_normal };

        return { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    }

    // TODO: valid() method?

    [[nodiscard]] constexpr Vector3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Frustum", index < 8);
        switch (index) {
        case 0: // near-left-bottom
            return near_plane.intersection(left_plane, bottom_plane).value();
        case 1: // near-left-top
            return near_plane.intersection(left_plane, top_plane).value();
        case 2: // near-right-bottom
            return near_plane.intersection(right_plane, bottom_plane).value();
        case 3: // near-right-top
            return near_plane.intersection(right_plane, top_plane).value();
        case 4: // far-left-bottom
            return far_plane.intersection(left_plane, bottom_plane).value();
        case 5: // far-left-top
            return far_plane.intersection(left_plane, top_plane).value();
        case 6: // far-right-bottom
            return far_plane.intersection(right_plane, bottom_plane).value();
        case 7: // far-right-top
        default:
            return far_plane.intersection(right_plane, top_plane).value();
        }
    }

    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        switch (index) {
        case 0: // near-left
            return { vertex(0), vertex(1) };
        case 1: // near-right
            return { vertex(2), vertex(3) };
        case 2: // near-bottom
            return { vertex(0), vertex(2) };
        case 3: // near-top
            return { vertex(1), vertex(3) };
        case 4: // far-left
            return { vertex(4), vertex(5) };
        case 5: // far-right
            return { vertex(6), vertex(7) };
        case 6: // far-bottom
            return { vertex(4), vertex(6) };
        case 7: // far-top
            return { vertex(5), vertex(7) };
        case 8: // left-bottom
            return { vertex(0), vertex(4) };
        case 9: // left-top
            return { vertex(1), vertex(5) };
        case 10: // right-bottom
            return { vertex(2), vertex(6) };
        case 11: // right-top
        default:
            return { vertex(3), vertex(7) };
        }
    }

    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        return approx_greater_equal_zero(near_plane.signed_distance(point))
            && approx_greater_equal_zero(far_plane.signed_distance(point))
            && approx_greater_equal_zero(left_plane.signed_distance(point))
            && approx_greater_equal_zero(right_plane.signed_distance(point))
            && approx_greater_equal_zero(bottom_plane.signed_distance(point))
            && approx_greater_equal_zero(top_plane.signed_distance(point));
    }

    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            const std::optional<Vector3<Real>> inter = plane.intersection(line);
            if (inter.has_value() && contains(*inter)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(ray);
                inter.has_value() && contains(inter.value())) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const
    {
        if (contains(segment.midpoint())) {
            return true;
        }
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(segment);
                inter.has_value() && contains(inter.value())) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool intersects(const Plane<Real>& plane) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& p : planes) {
            if (const std::optional<Line3<Real>> inter = p.intersection(plane);
                inter.has_value() && intersects(inter.value())) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Triangle3<Real>& triangle) const
    {
        if (contains(triangle.centroid())) {
            return true;
        }
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Segment3<Real>> inter = plane.intersection(triangle);
                inter.has_value() && intersects(inter.value())) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const
    {
        if (contains(rectangle.center)) {
            return true;
        }
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Segment3<Real>> inter = plane.intersection(rectangle);
                inter.has_value() && intersects(inter.value())) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const Real signed_dist = plane.signed_distance(sphere.center);
                approx_less(signed_dist, -sphere.radius)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& box) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            const Vector3<Real> furthest { plane.normal.x > static_cast<Real>(0) ? box.max.x : box.min.x,
                                           plane.normal.y > static_cast<Real>(0) ? box.max.y : box.min.y,
                                           plane.normal.z > static_cast<Real>(0) ? box.max.z : box.min.z };
            if (const Real signed_dist = plane.signed_distance(furthest); approx_less_zero(signed_dist)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool intersects(const Box<Real>& box) const
    {
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            const Real center_signed_dist = plane.signed_distance(box.center);
            const Real extent = abs(plane.normal.dot(box.half_span_u)) + abs(plane.normal.dot(box.half_span_v))
                + abs(plane.normal.dot(box.half_span_w));
            if (approx_less_zero(center_signed_dist + extent)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool intersects(const Frustum& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (contains(other.vertex(i) || other.contains(vertex(i)))) {
                return true;
            }
        }
        for (uint8_t i = 0; i < 12; ++i) {
            if (intersects(other.edge(i)) || other.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Line3<Real>& line) const
    {
        Intersections3<Real> inters;
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(line); inter.has_value()) {
                inters.insert(inter.value());
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Ray3<Real>& ray) const
    {
        Intersections3<Real> inters;
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(ray); inter.has_value()) {
                inters.insert(inter.value());
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Intersections3<Real> surface_intersections(const Segment3<Real>& segment) const
    {
        Intersections3<Real> inters;
        std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
        for (const Plane<Real>& plane : planes) {
            if (const std::optional<Vector3<Real>> inter = plane.intersection(segment); inter.has_value()) {
                inters.insert(inter.value());
                if (inters.size() >= 2) {
                    break;
                }
            }
        }
        return inters;
    }

    [[nodiscard]] constexpr Frustum translate(const Vector3<Real>& offset) const
    {
        return { near_plane.translate(offset),  far_plane.translate(offset),    left_plane.translate(offset),
                 right_plane.translate(offset), bottom_plane.translate(offset), top_plane.translate(offset) };
    }

    [[nodiscard]] Frustum rotate_axis_angle(
        const Vector3<Real>& axis, const Real angle, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return { near_plane.rotate_axis_angle_at(origin, axis, angle),
                 far_plane.rotate_axis_angle_at(origin, axis, angle),
                 left_plane.rotate_axis_angle_at(origin, axis, angle),
                 right_plane.rotate_axis_angle_at(origin, axis, angle),
                 bottom_plane.rotate_axis_angle_at(origin, axis, angle),
                 top_plane.rotate_axis_angle_at(origin, axis, angle) };
    }

    [[nodiscard]] constexpr Frustum rotate_quaternion(
        const Quaternion<Real>& quaternion, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return {
            near_plane.rotate_quaternion_at(origin, quaternion),   far_plane.rotate_quaternion_at(origin, quaternion),
            left_plane.rotate_quaternion_at(origin, quaternion),   right_plane.rotate_quaternion_at(origin, quaternion),
            bottom_plane.rotate_quaternion_at(origin, quaternion), top_plane.rotate_quaternion_at(origin, quaternion)
        };
    }

    [[nodiscard]] constexpr Frustum scale(
        const Vector3<Real>& factor, const Vector3<Real>& origin = Vector3<Real>::zero()) const
    {
        return { near_plane.scale_at(origin, factor),   far_plane.scale_at(origin, factor),
                 left_plane.scale_at(origin, factor),   right_plane.scale_at(origin, factor),
                 bottom_plane.scale_at(origin, factor), top_plane.scale_at(origin, factor) };
    }

    [[nodiscard]] constexpr bool approx_equal(const Frustum& other) const
    {
        return near_plane.approx_equal(other.near_plane) && far_plane.approx_equal(other.far_plane)
            && left_plane.approx_equal(other.left_plane) && right_plane.approx_equal(other.right_plane)
            && bottom_plane.approx_equal(other.bottom_plane) && top_plane.approx_equal(other.top_plane);
    }

    [[nodiscard]] constexpr bool operator==(const Frustum& other) const
    {
        return near_plane == other.near_plane && far_plane == other.far_plane && left_plane == other.left_plane
            && right_plane == other.right_plane && bottom_plane == other.bottom_plane && top_plane == other.top_plane;
    }

    [[nodiscard]] constexpr bool operator!=(const Frustum& other) const
    {
        return near_plane != other.near_plane || far_plane != other.far_plane || left_plane != other.left_plane
            || right_plane != other.right_plane || bottom_plane != other.bottom_plane || top_plane != other.top_plane;
    }

    [[nodiscard]] constexpr bool operator<(const Frustum& other) const
    {
        if (near_plane != other.near_plane) {
            return near_plane < other.near_plane;
        }
        if (far_plane != other.far_plane) {
            return far_plane < other.far_plane;
        }
        if (left_plane != other.left_plane) {
            return left_plane < other.left_plane;
        }
        if (right_plane != other.right_plane) {
            return right_plane < other.right_plane;
        }
        if (bottom_plane != other.bottom_plane) {
            return bottom_plane < other.bottom_plane;
        }
        return top_plane < other.top_plane;
    }
};

template <typename Real>
Line3<Real> Line3<Real>::from_segment(const Segment3<Real>& segment)
{
    return { segment.start, (segment.end - segment.start).normalize() };
}

template <typename Real>
constexpr Line3<Real> Line3<Real>::from_ray(const Ray3<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
Line3<Real> Line3<Real>::perpendicular_plane_parallel(const Plane<Real>& plane) const
{
    const Vector3<Real> dir = direction.cross(plane.normal).normalize();
    return { origin, dir };
}

template <typename Real>
constexpr bool Line3<Real>::collinear(const Ray3<Real>& ray) const
{
    return ray.collinear(*this);
}

template <typename Real>
bool Line3<Real>::collinear(const Segment3<Real>& segment) const
{
    return segment.collinear(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Ray3<Real>& ray) const
{
    return ray.coplanar(*this);
}

template <typename Real>
bool Line3<Real>::coplanar(const Segment3<Real>& segment) const
{
    return segment.coplanar(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
bool Line3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Ray3<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Segment3<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector3<Real>> Line3<Real>::intersection(const Segment3<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Ray3<Real>& ray) const
{
    return ray.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    return ray.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Ray3<Real>& ray) const
{
    return ray.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector3<Real>> Line3<Real>::intersection(const Ray3<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::intersects(const Segment3<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector3<Real>> Ray3<Real>::intersection(const Segment3<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
bool Ray3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr bool Segment3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance(const Plane<Real>& plane) const
{
    return plane.distance(*this);
}

template <typename Real>
bool Segment3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr std::optional<Vector3<Real>> Segment3<Real>::intersection(const Plane<Real>& plane) const
{
    return plane.intersection(*this);
}

template <typename Real>
constexpr bool Plane<Real>::intersects(const Triangle3<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr std::optional<Segment3<Real>> Plane<Real>::intersection(const Triangle3<Real>& triangle) const
{
    return triangle.intersection(*this);
}

template <typename Real>
constexpr std::optional<Segment3<Real>> Plane<Real>::intersection(const Rectangle3<Real>& rectangle) const
{
    return rectangle.intersection(*this);
}

template <typename Real>
constexpr bool Segment3<Real>::intersects(const Plane<Real>& plane) const
{
    return plane.intersects(*this);
}

template <typename Real>
Plane<Real> Plane<Real>::from_triangle_unchecked(const Triangle3<Real>& triangle)
{
    return from_points_unchecked(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
}

template <typename Real>
std::optional<Plane<Real>> Plane<Real>::from_triangle(const Triangle3<Real>& triangle)
{
    return from_points(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
}

template <typename Real>
bool Plane<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr bool Rectangle3<Real>::intersects(const Sphere<Real>& sphere) const
{
    return sphere.intersects(*this);
}

template <typename Real>
constexpr bool Rectangle3<Real>::intersects(const AlignedBox<Real>& box) const
{
    return box.intersects(*this);
}

template <typename Real>
constexpr bool Rectangle3<Real>::intersects(const Box<Real>& box) const
{
    return box.intersects(*this);
}
}

#endif