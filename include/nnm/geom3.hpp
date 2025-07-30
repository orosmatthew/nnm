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
class Sphere;
using SphereF = Sphere<float>;
using SphereD = Sphere<double>;

/**
 * 3D infinite line.
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
    static Line3 from_points(const Vector3<Real>& point1, const Vector3<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    /**
     * Extends a line segment to an infinite line.
     * @param segment Line segment.
     * @return Result.
     */
    static Line3 from_segment(const Segment3<Real>& segment);

    /**
     * Line that is an extension from a ray.
     * @param ray Ray.
     * @return Result.
     */
    static Line3 from_ray(const Ray3<Real>& ray);

    /**
     * Line that intersects the origin and is in the direction of the x-axis.
     * @return Result.
     */
    static constexpr Line3 axis_x()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    /**
     * Line that intersects the origin and is in the direction of the y-axis.
     * @return Result.
     */
    static constexpr Line3 axis_y()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    /**
     * Line that intersects the origin and is in the direction of the z-axis.
     * @return
     */
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
    static constexpr Line3 axis_z_offset(const Real offset_x, const Real offset_y)
    {
        return { { offset_x, offset_y, static_cast<Real>(0) }, Vector3<Real>::axis_z() };
    }

    /**
     * Line that is parallel to this line and intersects a point.
     * @param point Point.
     * @return Result.
     */
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
    [[nodiscard]] Line3 perpendicular_plane_parallel(const Plane<Real>& plane) const;

    /**
     * Normalize the line's direction.
     * @return Result.
     */
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
    [[nodiscard]] bool collinear(const Ray3<Real>& ray) const;

    [[nodiscard]] bool collinear(const Segment3<Real>& segment) const;

    [[nodiscard]] bool coplanar(const Line3& other) const
    {
        if (parallel(other)) {
            return true;
        }
        const Vector3<Real> diff = origin - other.origin;
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        return approx_zero(diff.dot(dir_cross));
    }

    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const;

    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const;

    [[nodiscard]] bool coplanar(const Plane<Real>& plane) const;

    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a point.
     * @param point Point.
     * @return Result.
     */
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
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return (point - origin).cross(direction).length();
    }

    /**
     * Closest distance to another line. Zero if they intersect.
     * @param other Other line.
     * @return Result.
     */
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
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Determine if parallel with another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool parallel(const Line3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if perpendicular to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool perpendicular(const Line3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Line3& other) const
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
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Line3& other) const
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
    [[nodiscard]] bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Ray3<Real>& ray) const;

    /**
     * Project point on the line.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
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
    [[nodiscard]] bool coincident(const Line3& other) const
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
    [[nodiscard]] Line3 translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Line3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
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
    [[nodiscard]] Line3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z(factor_x, factor_y), direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Determine if the origin and direction are approximately equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_equal(const Line3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    /**
     * Determine if origin and direction are exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool operator==(const Line3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine if either origin or direction are not exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool operator!=(const Line3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical comparison in the order of origin then direction.
     * @param other Other line.
     * @return Result.
     */
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
    static Ray3 from_point_to_point(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        return { from, from.direction(to) };
    }

    /**
     * Normalize the direction.
     * @return Result.
     */
    [[nodiscard]] Ray3 normalize() const
    {
        return { origin, direction.normalize() };
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_ray(*this).contains(point);
    }

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).coincident(line);
    }

    /**
     * Determine if collinear with another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Ray3& other) const
    {
        return Line3<Real>::from_ray(*this).coincident(Line3<Real>::from_ray(other));
    }

    [[nodiscard]] bool coplanar(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).coplanar(line);
    }

    [[nodiscard]] bool coplanar(const Ray3& ray) const
    {
        return Line3<Real>::from_ray(*this).coplanar(Line3<Real>::from_ray(ray));
    }

    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const
    {
        return Line3<Real>::from_ray(*this).coplanar(segment);
    }

    [[nodiscard]] bool coplanar(const Plane<Real>& plane) const;

    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if ray intersects a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> proj = project_point(point);
        return proj.approx_equal(point);
    }

    /**
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
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
    [[nodiscard]] bool parallel(const Line3<Real>& line) const
    {
        return direction.cross(line.direction).approx_zero();
    }

    /**
     * Determine if parallel to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool parallel(const Ray3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool perpendicular(const Line3<Real>& line) const
    {
        return nnm::approx_zero(direction.dot(line.direction));
    }

    /**
     * Determine if perpendicular to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool perpendicular(const Ray3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Line3<Real>& line) const
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
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Line3<Real>& line) const
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
    [[nodiscard]] bool intersects(const Ray3& other) const
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

    /**
     * Intersection point with another ray.
     * @param other Other ray.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> intersection(const Ray3& other) const
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
    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
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
    [[nodiscard]] Ray3 translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scaling origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Ray3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
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
    [[nodiscard]] Ray3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return { origin.shear_z(angle_x, angle_y), direction.shear_z(angle_x, angle_y).normalize() };
    }

    /**
     * Determine if both origin and direction are approximately equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_equal(const Ray3& other) const
    {
        return origin.approx_equal(other.origin) && direction.approx_equal(other.direction);
    }

    /**
     * Determine if both origin and direction are exactly equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool operator==(const Ray3& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine if either origin or direction are not exactly equal to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool operator!=(const Ray3& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical comparison in the order of origin then direction.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool operator<(const Ray3& other) const
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
    constexpr Segment3(const Vector3<Real>& start, const Vector3<Real>& end)
        : start { start }
        , end { end }
    {
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_segment(*this).contains(point);
    }

    /**
     * Determine if collinear with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_segment(*this).coincident(line);
    }

    /**
     * Determine if collinear with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Ray3<Real>& ray) const
    {
        return Line3<Real>::from_segment(*this).collinear(ray);
    }

    /**
     * Determine if collinear with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    [[nodiscard]] bool collinear(const Segment3& other) const
    {
        return Line3<Real>::from_segment(*this).coincident(Line3<Real>::from_segment(other));
    }

    [[nodiscard]] bool coplanar(const Line3<Real>& line) const
    {
        return Line3<Real>::from_segment(*this).coplanar(line);
    }

    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const
    {
        return Line3<Real>::from_segment(*this).coplanar(ray);
    }

    [[nodiscard]] bool coplanar(const Segment3& other) const
    {
        return Line3<Real>::from_segment(*this).coplanar(Line3<Real>::from_segment(other));
    }

    [[nodiscard]] bool coplanar(const Plane<Real>& plane) const;

    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if contains/intersects a point.
     * @param point Point.
     * @return Result.
     */
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
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
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
    [[nodiscard]] Real distance(const Segment3& other) const
    {
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

    /**
     * Non-normalized direction from the start position to the end position.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3<Real> direction_unnormalized() const
    {
        return end - start;
    }

    /**
     * Normalized direction from the start position to the end position.
     * @return Result.
     */
    [[nodiscard]] Vector3<Real> direction() const
    {
        return direction_unnormalized().normalize();
    }

    /**
     * Determine if parallel to a line.
     * @param line Line.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool intersects(const Segment3& other) const
    {
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

    /**
     * Project a point on the line segment.
     * @param point Point.
     * @return Resulting projected point.
     */
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
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(end.x - start.x) + sqrd(end.y - start.y) + sqrd(end.z - start.z);
    }

    /**
     * Length.
     * @return Result.
     */
    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    /**
     * Midpoint.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3<Real> midpoint() const
    {
        return (start + end) / static_cast<Real>(2);
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
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
    [[nodiscard]] constexpr Segment3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { start.scale_at(scale_origin, factor), end.scale_at(scale_origin, factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
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
    [[nodiscard]] constexpr Segment3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { start.shear_z(factor_x, factor_y), end.shear_z(factor_x, factor_y) };
    }

    /**
     * Determine if coincident with another segment.
     * @param other Other segment.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool approx_equal(const Segment3& other) const
    {
        return start.approx_equal(other.start) && end.approx_equal(other.end);
    }

    /**
     * Determine if start and end are exactly equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator==(const Segment3& other) const
    {
        return start == other.start && end == other.end;
    }

    /**
     * Determine if start and end are not exactly equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Segment3& other) const
    {
        return start != other.start || end != other.end;
    }

    /**
     * Lexicographical comparison in the order of start then end.
     * @param other Other segment.
     * @return Result.
     */
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
    constexpr Plane(const Vector3<Real>& origin, const Vector3<Real>& normal)
        : origin { origin }
        , normal { normal }
    {
    }

    /**
     * Plane that intersects all given points. Does not check for collinearity.
     * @param point1 First point.
     * @param point2 Second point.
     * @param point3 Third point.
     * @return Result.
     */
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
    static Plane from_triangle_unchecked(const Triangle3<Real>& triangle);

    /**
     * A plane that is coplanar to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    static std::optional<Plane> from_triangle(const Triangle3<Real>& triangle);

    static constexpr Plane xy()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_z() };
    }

    static constexpr Plane xy_offset(const float z_offset)
    {
        return xy().translate({ static_cast<Real>(0), static_cast<Real>(0), z_offset });
    }

    static constexpr Plane xz()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_y() };
    }

    static constexpr Plane xz_offset(const float y_offset)
    {
        return xz().translate({ static_cast<Real>(0), y_offset, static_cast<Real>(0) });
    }

    static constexpr Plane yz()
    {
        return { Vector3<Real>::zero(), Vector3<Real>::axis_x() };
    }

    static constexpr Plane yz_offset(const float x_offset)
    {
        return yz().translate({ x_offset, static_cast<Real>(0), static_cast<Real>(0) });
    }

    /**
     * Normalize the normal.
     * @return Result.
     */
    [[nodiscard]] Plane normalize() const
    {
        return { origin, normal.normalize() };
    }

    /**
     * Determine if coplanar with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool coplanar(const Line3<Real>& line) const
    {
        return contains(line.origin) && normal.perpendicular(line.direction);
    }

    /**
     * Determine if coplanar with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const
    {
        return approx_contains(ray.origin) && normal.approx_perpendicular(ray.direction);
    }

    /**
     * Determine if coplanar with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coplanar(const Segment3<Real>& segment) const
    {
        return contains(segment.start) && contains(segment.end);
    }

    /**
     * Determine if coplanar with another plane.
     * @param other Other plane.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coplanar(const Plane& other) const
    {
        return contains(other.origin) && normal.parallel(other.normal);
    }

    [[nodiscard]] bool coplanar(const Triangle3<Real>& triangle) const;

    /**
     * Determine if plane contains/intersects a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr bool contains(const Vector3<Real>& point) const
    {
        const Real d = origin.dot(normal);
        const Real proj = point.dot(normal);
        return nnm::approx_equal(d, proj);
    }

    /**
     * Determine the closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr Real distance(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        return abs(diff.dot(normal) / normal.dot(normal));
    }

    /**
     * Determine the closest distance with a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const
    {
        return normal.perpendicular(line.direction);
    }

    /**
     * Determine if parallel with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const
    {
        return normal.perpendicular(ray.direction);
    }

    /**
     * Determine if parallel with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool parallel(const Plane& other) const
    {
        return normal.parallel(other.normal);
    }

    /**
     * Determine if perpendicular with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const
    {
        return normal.parallel(line.direction);
    }

    /**
     * Determine if perpendicular with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const
    {
        return normal.parallel(ray.direction);
    }

    /**
     * Determine if perpendicular with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool perpendicular(const Plane& other) const
    {
        return normal.perpendicular(other.normal);
    }

    /**
     * Determine if intersects with a line.
     * @param line Line.
     * @return Result.
     */
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

    [[nodiscard]] constexpr std::optional<Vector3<Real>> intersection(const Segment3<Real>& segment) const
    {
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

    [[nodiscard]] constexpr bool intersects(const Plane& other) const
    {
        if (contains(other.origin)) {
            return true;
        }
        const Real dot = normal.dot(other.normal);
        return !nnm::approx_equal(dot, static_cast<Real>(1)) && !nnm::approx_equal(dot, static_cast<Real>(-1));
    }

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

    [[nodiscard]] constexpr Vector3<Real> project(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff = point - origin;
        const Real dist = diff.dot(normal) / normal.dot(normal);
        return point - normal * dist;
    }

    [[nodiscard]] constexpr Plane translate(const Vector3<Real>& offset) const
    {
        return { origin.translate(offset), normal };
    }

    [[nodiscard]] Plane scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { origin.scale_at(scale_origin, factor), normal.scale(factor).normalize() };
    }

    [[nodiscard]] Plane scale(const Vector3<Real>& factor) const
    {
        return { origin.scale(factor), normal.scale(factor).normalize() };
    }

    [[nodiscard]] Plane rotate_axis_angle_at(
        const Vector3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle_at(rotate_origin, axis, angle),
                 normal.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Plane rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { origin.rotate_axis_angle(axis, angle), normal.rotate_axis_angle(axis, angle).normalize() };
    }

    [[nodiscard]] Plane rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion_at(rotate_origin, quaternion),
                 normal.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Plane rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { origin.rotate_quaternion(quaternion), normal.rotate_quaternion(quaternion).normalize() };
    }

    [[nodiscard]] Plane shear_x_at(const Vector3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x_at(shear_origin, factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    [[nodiscard]] Plane shear_x(const Real factor_y, const Real factor_z) const
    {
        return { origin.shear_x(factor_y, factor_z), normal.shear_x(factor_y, factor_z).normalize() };
    }

    [[nodiscard]] Plane shear_y_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y_at(shear_origin, factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    [[nodiscard]] Plane shear_y(const Real factor_x, const Real factor_z) const
    {
        return { origin.shear_y(factor_x, factor_z), normal.shear_y(factor_x, factor_z).normalize() };
    }

    [[nodiscard]] Plane shear_z_at(const Vector3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z_at(shear_origin, factor_x, factor_y), normal.shear_z(factor_x, factor_y).normalize() };
    }

    [[nodiscard]] Plane shear_z(const Real factor_x, const Real factor_y) const
    {
        return { origin.shear_z(factor_x, factor_y), normal.shear_z(factor_x, factor_y).normalize() };
    }

    [[nodiscard]] bool approx_equal(const Plane& other) const
    {
        return origin.approx_equal(other.origin) && normal.approx_equal(other.normal);
    }

    [[nodiscard]] bool operator==(const Plane& other) const
    {
        return origin == other.origin && normal == other.normal;
    }

    [[nodiscard]] bool operator!=(const Plane& other) const
    {
        return origin != other.origin || normal != other.normal;
    }

    [[nodiscard]] bool operator<(const Plane& other) const
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
    constexpr Triangle3(const Vector3<Real>& vertex0, const Vector3<Real>& vertex1, const Vector3<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    /**
     * Edge in the order of vertex 0 to 1, 1 to 2, then 2 to 0.
     * @param index Edge index.
     * @return Result.
     */
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
    [[nodiscard]] constexpr Vector3<Real> centroid() const
    {
        return (vertices[0] + vertices[1] + vertices[2]) / static_cast<Real>(3);
    }

    /**
     * Circumcenter which is the intersection between the perpendicular bisectors of the edges.
     * @return Result.
     */
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
    [[nodiscard]] Real perimeter() const
    {
        return edge(0).length() + edge(1).length() + edge(2).length();
    }

    /**
     * Incenter which is the intersection between the interior angles' bisectors.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector3<Real>> incenter() const
    {
        return angle_bisector(0).intersection(angle_bisector(1));
    }

    /**
     * Orthocenter which is the intersection between the altitudes of the triangle.
     * @return Result.
     */
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
    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const
    {
        return coplanar(Line3<Real>::from_ray(ray));
    }

    /**
     * Determine if coplanar with a segment.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] bool coplanar(const Segment3<Real>& segment) const
    {
        return coplanar(Line3<Real>::from_segment(segment));
    }

    /**
     * Determine if coplanar with a plane.
     * @param plane Plane.
     * @return Result.
     */
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
    [[nodiscard]] Real distance(const Plane<Real>& plane) const
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
     * Determine if parallel with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const
    {
        return edge(0).parallel(line) && edge(1).parallel(line) && edge(2).parallel(line);
    }

    /**
     * Determine if parallel with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const
    {
        return edge(0).parallel(ray) && edge(1).parallel(ray) && edge(2).parallel(ray);
    }

    /**
     * Determine if parallel with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Segment3<Real>& segment) const
    {
        return edge(0).parallel(segment) && edge(1).parallel(segment) && edge(2).parallel(segment);
    }

    /**
     * Determine if parallel with a plane.
     * @param plane Plane.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Plane<Real>& plane) const
    {
        return plane.parallel(edge(0)) && plane.parallel(edge(1)) && plane.parallel(edge(2));
    }

    /**
     * Determine if parallel with another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool parallel(const Triangle3& other) const
    {
        return this->parallel(other.edge(0)) && this->parallel(other.edge(1)) && this->parallel(other.edge(2));
    }

    /**
     * Determine if perpendicular with a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const
    {
        return edge(0).perpendicular(line) && edge(1).perpendicular(line) && edge(2).perpendicular(line);
    }

    /**
     * Determine if perpendicular with a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const
    {
        return edge(0).perpendicular(ray) && edge(1).perpendicular(ray) && edge(2).perpendicular(ray);
    }

    /**
     * Determine if perpendicular with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Segment3<Real>& segment) const
    {
        return edge(0).perpendicular(segment) && edge(1).perpendicular(segment) && edge(2).perpendicular(segment);
    }

    /**
     * Determine if perpendicular with a plane.
     * @param plane Plane.
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Plane<Real>& plane) const
    {
        return plane.perpendicular(edge(0)) && plane.perpendicular(edge(1)) && plane.perpendicular(edge(2));
    }

    /**
     * Determine if perpendicular with another triangle.
     * @param other Other triangle/
     * @return Result.
     */
    [[nodiscard]] constexpr bool perpendicular(const Triangle3& other) const
    {
        return this->perpendicular(other.edge(0)) && this->perpendicular(other.edge(1))
            && this->perpendicular(other.edge(2));
    }

    /**
     * Determine if intersects with a line.
     * @param line Line.
     * @return Result.
     */
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
        if (!point.has_value() || !contains_projected(point)) {
            return std::nullopt;
        }
        return *point;
    }

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
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
        return contains_projected(point);
    }

    /**
     * Intersection point with a ray. Returns null if coplanar intersection.
     * @param ray Ray.
     * @return Result.
     */
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
        if (!point.has_value()) {
            return std::nullopt;
        }
        return contains_projected(point);
    }

    /**
     * Determine if intersects with a line segment
     * @param segment Line segment.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const
    {
        return plane.intersects(edge(0)) || plane.intersects(edge(1)) || plane.intersects(edge(2));
    }

    /**
     * Intersection points with a plane and the triangle's edges.
     * Returns equal points if only one intersection point exists.
     * Returns null if coplanar intersection.
     * @param plane Plane.
     * @return Result.
     */
    [[nodiscard]] std::optional<std::array<Vector3<Real>, 2>> intersections(const Plane<Real>& plane) const
    {
        std::array<Vector3<Real>, 2> points;
        uint8_t points_count = 0;
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Vector3<Real>> point = plane.intersection(edge(i));
            if (!point.has_value()) {
                continue;
            }
            points[points_count++] = *point;
            if (points_count >= 2) {
                return points;
            }
        }
        if (points_count == 0) {
            return std::nullopt;
        }
        if (points_count == 1) {
            return std::array { points[0], points[0] };
        }
        return points;
    }

    /**
     * Determine if intersects with another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Triangle3& other) const
    {
        return intersects(other.edge(0)) || intersects(other.edge(1)) || intersects(other.edge(2));
    }

    /**
     * Intersection between this and another triangle's edges.
     * Returns equal points if only one intersection exists.
     * Returns null if coplanar intersection.
     * @param other Other triangle
     * @return Result.
     */
    [[nodiscard]] std::optional<std::array<Vector3<Real>, 2>> intersections(const Triangle3& other) const
    {
        std::array<Vector3<Real>, 2> points;
        uint8_t points_count = 0;
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Vector3<Real>> point = intersection(other.edge(i));
            if (point.has_value()) {
                points[points_count++] = *point;
            }
            if (points_count >= 2) {
                return points;
            }
        }
        if (points_count == 0) {
            return std::nullopt;
        }
        if (points_count == 1) {
            return std::array { points[0], points[0] };
        }
        return points;
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
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
    constexpr bool operator==(const Triangle3& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    /**
     * Determine if any vertices are not equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    constexpr bool operator!=(const Triangle3& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    /**
     * Lexicographical comparison in the order of vertices.
     * @param other Other triangle.
     * @return Result.
     */
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
    static constexpr Sphere from_center_point(const Vector3<Real>& center, const Vector3<Real>& point)
    {
        return Sphere(center, center.distance(point));
    }

    /**
     * Surface area.
     * @return Result.
     */
    [[nodiscard]] constexpr Real surface_area() const
    {
        return static_cast<Real>(4) * pi<Real>() * sqrd(radius);
    }

    /**
     * Volume.
     * @return Result.
     */
    [[nodiscard]] constexpr Real volume() const
    {
        const Real radius_cubed = radius * radius * radius;
        return static_cast<Real>(4) / static_cast<Real>(3) * pi<Real>() * radius_cubed;
    }

    /**
     * Diameter.
     * @return Result.
     */
    [[nodiscard]] constexpr Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    /**
     * Determines if a point is contained inside the sphere.
     * @param point Point.
     * @return Result.
     */
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
    [[nodiscard]] Real signed_distance(const Vector3<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    /**
     * Closest distance to a point. Zero if point is inside the sphere.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Vector3<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    /**
     * Closest distance to a line. Zero if intersects or is inside the sphere.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Line3<Real>& line) const
    {
        return max(static_cast<Real>(0), line.distance(center) - radius);
    }

    /**
     * Closest distance to a ray. Zero if intersects or is inside the sphere.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const
    {
        return max(static_cast<Real>(0), ray.distance(center) - radius);
    }

    /**
     * Closest distance to a line segment. Zero if intersects or is inside the sphere.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const
    {
        return max(static_cast<Real>(0), segment.distance(center) - radius);
    }

    /**
     * Closest distance to a plane. Zero if intersects.
     * @param plane Plane.
     * @return Result.
     */
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const
    {
        return max(static_cast<Real>(0), plane.distance(center) - radius);
    }

    /**
     * Closest distance to a triangle. Zero if intersects or if contains triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const
    {
        return max(static_cast<Real>(0), triangle.distance(center) - radius);
    }

    /**
     * Closest distance to another sphere. Zero if intersects or is inside this sphere.
     * @param other Other sphere.
     * @return Result.
     */
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
    [[nodiscard]] Real point_at(const Vector3<Real>& dir) const
    {
        return center.translate(dir * radius);
    }

    /**
     * Normal of the surface of the sphere in the given direction from the center.
     * @param dir Normalized direction from the sphere's center. No normalization is done.
     * @return Result.
     */
    // ReSharper disable once CppMemberFunctionMayBeStatic
    [[nodiscard]] Vector3<Real> normal_at(const Vector3<Real>& dir) const
    {
        return dir;
    }

    /**
     * Determine if intersects with a line. Being inside the circle is considered an intersection.
     * @param line Line.
     * @return Result.
     */
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
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] std::optional<std::array<Vector3<Real>, 2>> intersections(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = line.origin - center;
        const Real a = line.direction.dot(line.direction);
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return std::nullopt;
        }
        if (approx_zero(discriminant)) {
            const Real t = -b / (static_cast<Real>(2) * a);
            const Vector3<Real> p = line.origin + line.direction * t;
            return { p, p };
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const Vector3<Real> p1 = line.origin + line.direction * t1;
        const Vector3<Real> p2 = line.origin + line.direction * t2;
        return p2 < p1 ? std::array { p2, p1 } : std::array { p1, p2 };
    }

    /**
     * Determine if intersects with a ray. Being inside the sphere is considered an intersection.
     * @param ray Ray.
     * @return Result.
     */
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
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] std::optional<std::array<Vector3<Real>, 2>> intersections(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = ray.origin - center;
        const Real a = ray.direction.dot(ray.direction);
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const std::optional<Vector3<Real>> p1
            = approx_greater_equal_zero(t1) ? ray.origin + ray.direction * t1 : std::nullopt;
        const std::optional<Vector3<Real>> p2
            = approx_greater_equal_zero(t2) ? ray.origin + ray.direction * t2 : std::nullopt;
        if (p1.has_value() && p2.has_value()) {
            return *p2 < *p1 ? std::array { *p2, *p1 } : std::array { *p1, *p2 };
        }
        if (p1.has_value()) {
            return std::array { *p1, *p1 };
        }
        if (p2.has_value()) {
            return std::array { *p2, *p2 };
        }
        return std::nullopt;
    }

    /**
     * Determine if intersects with a line segment. Being inside the sphere is considered an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Segment3<Real>& segment) const
    {
        const Vector3<Real> seg_dir = segment.direction();
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
        return (approx_greater_equal_zero(t1) && approx_less_equal(t1, seg_length))
            || (approx_greater_equal_zero(t2) && approx_less_equal(t2, seg_length));
    }

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    [[nodiscard]] std::optional<std::array<Vector3<Real>, 2>> intersections(const Segment3<Real>& segment) const
    {
        const Vector3<Real> seg_dir;
        const Vector3<Real> dir = segment.start - center;
        const Real a = seg_dir.dot(seg_dir);
        const Real b = static_cast<Real>(2) * dir.dot(seg_dir);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
        if (approx_less_zero(discriminant)) {
            return std::nullopt;
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
        const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
        const Real seg_length = segment.length();
        const std::optional<Vector3<Real>> p1 = approx_greater_equal_zero(t1) && approx_less_equal(t1, seg_length)
            ? segment.start + seg_dir * t1
            : std::nullopt;
        const std::optional<Vector3<Real>> p2 = approx_greater_equal_zero(t2) && approx_less_equal(t2, seg_length)
            ? segment.start + seg_dir * t2
            : std::nullopt;
        if (p1.has_value() && p2.has_value()) {
            return *p2 < *p1 ? std::array { *p2, *p1 } : std::array { *p1, *p2 };
        }
        if (p1.has_value()) {
            return std::array { *p1, *p1 };
        }
        if (p2.has_value()) {
            return std::array { *p2, *p2 };
        }
        return std::nullopt;
    }

    /**
     * Determine if intersects with another sphere. Being inside a sphere is considered an intersection.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Sphere& other) const
    {
        return approx_less_equal(center.distance_sqrd(other.center), sqrd(radius + other.radius));
    }

    /**
     * Intersection depth with another sphere.
     * @param other Other sphere.
     * @return Result.
     */
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
        if (approx_less_zero(depth)) {
            return std::nullopt;
        }
        return diff.normalize() * depth;
    }

    /**
     * Determine if tangent to line.
     * @param line Line.
     * @return Result.
     */
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
    [[nodiscard]] Sphere translate(const Vector3<Real>& offset) const
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
    [[nodiscard]] Sphere rotate_quaternion_at(
        const Vector3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion_at(rotate_origin, quaternion), radius };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] Sphere rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { center.rotate_quaternion(quaternion), radius };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Sphere scale_at(const Vector3<Real>& scale_origin, const Real factor) const
    {
        return { center.scale_at(scale_origin, Vector3<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Sphere scale(const Real factor)
    {
        return { center.scale(Vector3<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Determine if approximately coincident to another sphere which means
     * if both the center and radius are approximately equal to the other sphere.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_coincident(const Sphere& other) const
    {
        return approx_equal(other);
    }

    /**
     * Determine if all members are approximately equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_equal(const Sphere& other) const
    {
        return center.approx_equal(other.center) && nnm::approx_equal(radius, other.radius);
    }

    /**
     * Determine if all members are exactly equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator==(const Sphere& other) const
    {
        return center == other.center && radius == other.radius;
    }

    /**
     * Determine if any members are not exactly equal to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Sphere& other) const
    {
        return center != other.center || radius != other.radius;
    }

    /**
     * Lexicographical comparison in the order of center then radius to another sphere.
     * @param other Other sphere.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator<(const Sphere& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        return radius < other.radius;
    }
};

template <typename Real>
Line3<Real> Line3<Real>::from_segment(const Segment3<Real>& segment)
{
    return { segment.start, (segment.end - segment.start).normalize() };
}

template <typename Real>
Line3<Real> Line3<Real>::from_ray(const Ray3<Real>& ray)
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
bool Line3<Real>::collinear(const Ray3<Real>& ray) const
{
    return ray.collinear(*this);
}

template <typename Real>
bool Line3<Real>::collinear(const Segment3<Real>& segment) const
{
    return segment.collinear(*this);
}

template <typename Real>
bool Line3<Real>::coplanar(const Ray3<Real>& ray) const
{
    return ray.coplanar(*this);
}

template <typename Real>
bool Line3<Real>::coplanar(const Segment3<Real>& segment) const
{
    return segment.coplanar(*this);
}

template <typename Real>
bool Line3<Real>::coplanar(const Plane<Real>& plane) const
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
bool Line3<Real>::parallel(const Ray3<Real>& ray) const
{
    return ray.parallel(*this);
}

template <typename Real>
bool Line3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    return ray.perpendicular(*this);
}

template <typename Real>
bool Line3<Real>::intersects(const Ray3<Real>& ray) const
{
    return ray.intersects(*this);
}

template <typename Real>
std::optional<Vector3<Real>> Line3<Real>::intersection(const Ray3<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
bool Ray3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
bool Ray3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
bool Segment3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
bool Segment3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
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
}

#endif