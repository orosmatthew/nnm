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
     * Point that the line intersects.
     */
    Vector3<Real> point;

    /**
     * Direction.
     */
    Vector3<Real> direction;

    /**
     * Default initialize with zero point in the direction of the x-axis.
     */
    constexpr Line3()
        : point { Vector3<Real>::zero() }
        , direction { Vector3<Real>::axis_x() }
    {
    }

    /**
     * Initialize with a point that the line intersects and a direction. The direction should be normalized.
     * @param point Point.
     * @param direction Normalized direction.
     */
    constexpr Line3(const Vector3<Real>& point, const Vector3<Real>& direction)
        : point { point }
        , direction { direction }
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
     * Normalize the line's direction.
     * @return Result.
     */
    [[nodiscard]] Line3 normalize() const
    {
        return { point, direction.normalize() };
    }

    /**
     * Determine if approximately collinear with a ray which means
     * that all points for both the line and the ray exist on the same line.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Ray3<Real>& ray) const;

    /**
     * Determine if approximately intersects a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - this->point;
        const Real t = dir.dot(direction);
        const Vector3<Real> proj = this->point + direction * t;
        return proj.approx_equal(point);
    }

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr Real distance(const Vector3<Real>& point) const
    {
        return (point - this->point).cross(direction).length();
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
            return distance(other.point);
        }
        const Vector3<Real> diff = point - other.point;
        return abs(dir_cross.dot(diff)) / dir_cross.length();
    }

    /**
     * Closest distance to a ray. Zero if they intersect.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Determine if approximately parallel with another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Line3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if approximately parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Ray3<Real>& ray) const;

    /**
     * Determine if approximately perpendicular to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Line3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if approximately perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if approximately intersects another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return approx_contains(other.point);
        }
        const Vector3<Real> diff = other.point - point;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = point + direction * t;
        const Vector3<Real> p_other = other.point + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Intersection point with another line.
     * @param other Other line.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.point - point;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = point + direction * t;
        if (const Vector3<Real> p_other = other.point + other.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Determine if approximately intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3<Real>& ray) const;

    /**
     * Project point on the line.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
    {
        const Vector3<Real> dir = point - this->point;
        const Real t = dir.dot(direction);
        return this->point + direction * t;
    }

    /**
     * Determine if approximately coincident with another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_coincident(const Line3& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector3<Real> diff = point - other.point;
        return diff.cross(other.direction).approx_zero();
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] Line3 translate(const Vector3<Real>& offset) const
    {
        return { point.translate(offset), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Line3 scale_at(const Vector3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { point.scale_at(scale_origin, factor), direction.scale(factor).normalize() };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Line3 scale(const Vector3<Real>& factor) const
    {
        return { point.scale(factor), direction.scale(factor).normalize() };
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
        return { point.rotate_axis_angle_at(rotate_origin, axis, angle),
                 direction.rotate_axis_angle(axis, angle).normalize() };
    }

    /**
     * Rotate about the origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Line3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { point.rotate_axis_angle(axis, angle), direction.rotate_axis_angle(axis, angle).normalize() };
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
        return { point.rotate_quaternion_at(rotate_origin, quaternion),
                 direction.rotate_quaternion(quaternion).normalize() };
    }

    /**
     * Rotate about the origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] Line3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { point.rotate_quaternion(quaternion), direction.rotate_quaternion(quaternion).normalize() };
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
        return { point.shear_x_at(shear_origin, factor_y, factor_z),
                 direction.shear_x(factor_y, factor_z).normalize() };
    }

    /**
     * Shear about the origin along the x-axis.
     * @param factor_y Y-Axis shear factor.
     * @param factor_z Z-Axis shear factor.
     * @return Result.
     */
    [[nodiscard]] Line3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return { point.shear_x(factor_y, factor_z), direction.shear_x(factor_y, factor_z).normalize() };
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
        return { point.shear_y_at(shear_origin, factor_x, factor_z),
                 direction.shear_y(factor_x, factor_z).normalize() };
    }

    /**
     * Shear about the origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] Line3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { point.shear_y(factor_x, factor_z), direction.shear_y(factor_x, factor_z).normalize() };
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
        return { point.shear_z_at(shear_origin, factor_x, factor_y),
                 direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Shear about the origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    [[nodiscard]] Line3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { point.shear_z(factor_x, factor_y), direction.shear_z(factor_x, factor_y).normalize() };
    }

    /**
     * Determine if the point and direction are approximately equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool approx_equal(const Line3& other) const
    {
        return point.approx_equal(other.point) && direction.approx_equal(other.direction);
    }

    /**
     * Determine if point and direction are exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool operator==(const Line3& other) const
    {
        return point == other.point && direction == other.direction;
    }

    /**
     * Determine if either point or direction are not exactly equal to another line.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool operator!=(const Line3& other) const
    {
        return point != other.point || direction != other.direction;
    }

    /**
     * Lexicographical comparison in the order of point then direction.
     * @param other Other line.
     * @return Result.
     */
    [[nodiscard]] bool operator<(const Line3& other) const
    {
        if (point == other.point) {
            return direction < other.direction;
        }
        return point < other.point;
    }
};

/**
 * 3D ray.
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
     * Determine if approximately collinear with a point which means
     * that the point exists on the line extending in both +direction and -direction.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Vector3<Real>& point) const
    {
        return Line3<Real>::from_ray(*this).approx_contains(point);
    }

    /**
     * Determine if approximately collinear with a line which means that the ray existing entirely on the line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Line3<Real>& line) const
    {
        return Line3<Real>::from_ray(*this).approx_coincident(line);
    }

    /**
     * Determine if approximately collinear with another ray which means
     * both rays existing on the same infinite line.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Ray3& other) const
    {
        return Line3<Real>::from_ray(*this).approx_coincident(Line3<Real>::from_ray(other));
    }

    /**
     * Determine if ray approximately intersects a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool approx_contains(const Vector3<Real>& point) const
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
        const Real t = dir.dot(direction);
        if (t < static_cast<Real>(0)) {
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
        const Vector3<Real> diff = line.point - origin;
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return line.distance(origin);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Real t_line = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return line.distance(origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = line.point + line.direction * t_line;
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
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            const Real d1 = distance(other.origin);
            const Real d2 = other.distance(origin);
            return min(d1, d2);
        }
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return other.distance(origin);
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
            return distance(other.origin);
        }
        const Vector3<Real> p1 = origin + direction * t;
        const Vector3<Real> p2 = other.origin + other.direction * t_other;
        return p1.distance(p2);
    }

    /**
     * Determine if approximately parallel to a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Line3<Real>& line) const
    {
        return direction.cross(line.direction).approx_zero();
    }

    /**
     * Determine if approximately parallel to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Ray3& other) const
    {
        return direction.cross(other.direction).approx_zero();
    }

    /**
     * Determine if approximately perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Line3<Real>& line) const
    {
        return nnm::approx_zero(direction.dot(line.direction));
    }

    /**
     * Determine if approximately perpendicular to another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Ray3& other) const
    {
        return nnm::approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if approximately intersects a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.approx_contains(origin);
        }
        const Vector3<Real> diff = line.point - origin;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return false;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = line.point + line.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Approximate intersection with a line.
     * @param line Line.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir_cross = direction.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (dir_cross_len_sqrd == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.point - origin;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = origin + direction * t;
        if (const Vector3<Real> p_other = line.point + line.direction * t_other; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Determine if approximately intersects another ray.
     * @param other Other ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return other.approx_contains(origin) || approx_contains(other.origin);
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return false;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
            return false;
        }
        const Vector3<Real> p = origin + direction * t;
        const Vector3<Real> p_other = other.origin + other.direction * t_other;
        return p.approx_equal(p_other);
    }

    /**
     * Approximate intersection with another ray.
     * @param other Other ray.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3& other) const
    {
        const Vector3<Real> dir_cross = direction.cross(other.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
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
 * 3D line segment.
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
     * Determine if approximately collinear with a point which means the point intersects the
     * infinite line created from infinitely extending the line segment from both ends.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff1 = point - start;
        const Vector3<Real> diff2 = end - start;
        return diff1.cross(diff2).approx_zero();
    }

    /**
     * Determine if approximately collinear with a line which means the line is the same
     * as the infinite line created by infinitely extending the segment from both ends.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Line3<Real>& line) const
    {
        if (!approx_parallel(line)) {
            return false;
        }
        const Vector3<Real> diff = start - line.point;
        return diff.cross(line.direction).approx_zero();
    }

    /**
     * Determine if approximately collinear with a ray which means both existing on the same infinite line.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Ray3<Real>& ray) const
    {
        if (!approx_parallel(ray)) {
            return false;
        }
        const Vector3<Real> diff = start - ray.origin;
        return diff.cross(ray.direction).approx_zero();
    }

    /**
     * Determine if approximately collinear with another line segment
     * which means they both existing on the same infinite line.
     * @param other Other line segment.
     * @return Result.
     */
    [[nodiscard]] bool approx_collinear(const Segment3& other) const
    {
        if (!approx_parallel(other)) {
            return false;
        }
        const Vector3<Real> diff = start - other.start;
        return diff.cross(other.end - other.start).approx_zero();
    }

    /**
     * Determine if approximately intersects a point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool approx_contains(const Vector3<Real>& point) const
    {
        const Vector3<Real> diff1 = point - start;
        const Vector3<Real> diff2 = end - start;
        if (!diff1.cross(diff2).approx_zero()) {
            return false;
        }
        const Real dot = diff1.dot(diff2);
        const Real length_sqrd = diff2.dot(diff2);
        return dot >= static_cast<Real>(0) && dot <= length_sqrd;
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
        if (t < static_cast<Real>(0)) {
            return diff.length();
        }
        if (t > static_cast<Real>(1)) {
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
        const Vector3<Real> diff = line.point - start;
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            const Real d1 = line.distance(start);
            const Real d2 = line.distance(end);
            return min(d1, d2);
        }
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0)) {
            return line.distance(start);
        }
        if (t > static_cast<Real>(1)) {
            return line.distance(end);
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p1 = start.lerp(end, t);
        const Vector3<Real> p2 = line.point + line.direction * t_line;
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
        if (t < static_cast<Real>(0)) {
            return ray.distance(start);
        }
        if (t > static_cast<Real>(1)) {
            return ray.distance(end);
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_ray < static_cast<Real>(0)) {
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
        if (t < static_cast<Real>(0)) {
            return other.distance(start);
        }
        if (t > static_cast<Real>(1)) {
            return other.distance(end);
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0)) {
            return distance(other.start);
        }
        if (t_other > static_cast<Real>(1)) {
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
    [[nodiscard]] Vector3<Real> direction_unnormalized() const
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
     * Determine if approximately parallel to a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Line3<Real>& line) const
    {
        return direction().approx_parallel(line.direction);
    }

    /**
     * Determine if approximately parallel to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Ray3<Real>& ray) const
    {
        return direction().approx_parallel(ray.direction);
    }

    /**
     * Determine if approximately parallel to another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    [[nodiscard]] bool approx_parallel(const Segment3& other) const
    {
        return direction().approx_parallel(other.direction());
    }

    /**
     * Determine if approximately perpendicular to a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Line3<Real>& line) const
    {
        return direction().approx_perpendicular(line.direction);
    }

    /**
     * Determine if approximately perpendicular to a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Ray3<Real>& ray) const
    {
        return direction().approx_perpendicular(ray.direction);
    }

    /**
     * Determine if approximately perpendicular to another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    [[nodiscard]] bool approx_perpendicular(const Segment3& other) const
    {
        return direction().approx_perpendicular(other.direction());
    }

    /**
     * Determine if approximately intersects a line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return line.approx_contains(start);
        }
        const Vector3<Real> diff = line.point - start;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return false;
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_other = line.point + line.direction * t_line;
        return p.approx_equal(p_other);
    }

    /**
     * Approximate intersection with a line.
     * @param line Line.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Line3<Real>& line) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(line.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = line.point - start;
        const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return std::nullopt;
        }
        const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        const Vector3<Real> p = start.lerp(end, t);
        if (const Vector3<Real> p_other = line.point + line.direction * t_line; !p.approx_equal(p_other)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Determine if approximately intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return ray.approx_contains(start) || ray.approx_contains(end);
        }
        const Vector3<Real> diff = ray.origin - start;
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return false;
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_ray < static_cast<Real>(0)) {
            return false;
        }
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray;
        return p.approx_equal(p_ray);
    }

    /**
     * Approximate intersection with a ray.
     * @param ray Ray.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Ray3<Real>& ray) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(ray.direction);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return std::nullopt;
        }
        const Vector3<Real> diff = ray.origin - start;
        const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return std::nullopt;
        }
        const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_ray < static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector3<Real> p = start.lerp(end, t);
        if (const Vector3<Real> p_ray = ray.origin + ray.direction * t_ray; !p.approx_equal(p_ray)) {
            return std::nullopt;
        }
        return p;
    }

    /**
     * Approximate intersection with another line segment.
     * @param other Other line segment.
     * @return Result.
     */
    [[nodiscard]] bool approx_intersects(const Segment3& other) const
    {
        const Vector3<Real> dir = direction_unnormalized();
        const Vector3<Real> dir_other = other.direction_unnormalized();
        const Vector3<Real> dir_cross = dir.cross(dir_other);
        const Real dir_cross_len_sqrd = dir_cross.length_sqrd();
        if (nnm::approx_zero(dir_cross_len_sqrd)) {
            return approx_contains(other.start) || approx_contains(other.end) || other.approx_contains(start)
                || other.approx_contains(end);
        }
        const Vector3<Real> diff = other.start - start;
        const Real t = diff.cross(dir_other).dot(dir_cross) / dir_cross_len_sqrd;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return false;
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0) || t_other > static_cast<Real>(1)) {
            return false;
        }
        const Vector3<Real> p = start.lerp(end, t);
        const Vector3<Real> p_other = other.start.lerp(other.end, t_other);
        return p.approx_equal(p_other);
    }

    /**
     * Approximate intersection with another line segment.
     * @param other Other line segment.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector3<Real>> approx_intersection(const Segment3& other) const
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
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
            return std::nullopt;
        }
        const Real t_other = diff.cross(dir).dot(dir_cross) / dir_cross_len_sqrd;
        if (t_other < static_cast<Real>(0) || t_other > static_cast<Real>(1)) {
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
    [[nodiscard]] Vector3<Real> project_point(const Vector3<Real>& point) const
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
    [[nodiscard]] Vector3<Real> midpoint() const
    {
        return (start + end) / static_cast<Real>(2);
    }
};

template <typename Real>
class Sphere {
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
        return center.distance_sqrd(point) <= sqrd(radius);
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
};

template <typename Real>
Line3<Real> Line3<Real>::from_ray(const Ray3<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
bool Line3<Real>::approx_collinear(const Ray3<Real>& ray) const
{
    return ray.approx_collinear(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Ray3<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
bool Line3<Real>::approx_parallel(const Ray3<Real>& ray) const
{
    return ray.approx_parallel(*this);
}

template <typename Real>
bool Line3<Real>::approx_perpendicular(const Ray3<Real>& ray) const
{
    return ray.approx_perpendicular(*this);
}

template <typename Real>
bool Line3<Real>::approx_intersects(const Ray3<Real>& ray) const
{
    return ray.approx_intersects(*this);
}

template <typename Real>
std::optional<Vector3<Real>> Line3<Real>::approx_intersection(const Ray3<Real>& ray) const
{
    return ray.approx_intersection(*this);
}

}

#endif