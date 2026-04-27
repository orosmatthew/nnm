/* NNM - No Nonsense Math
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_INTERACTIONS_LINEAR_HPP
#define NNM_GEOM3_INTERACTIONS_LINEAR_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/line3.hpp>
#include <nnm/geom3/ray3.hpp>
#include <nnm/geom3/segment3.hpp>
#include <nnm/geom3/plane.hpp>
#include <nnm/geom3/triangle3.hpp>
#include <nnm/geom3/rectangle3.hpp>
#include <nnm/geom3/sphere.hpp>
#include <nnm/geom3/aligned_box.hpp>
#include <nnm/geom3/box.hpp>
#include <nnm/geom3/frustum.hpp>

namespace nnm {

template <typename Real>
/**
 * Determine if collinear with a point.
 * @param point Point.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::collinear(const Point3<Real>& point) const
{
    return Line3<Real>::from_ray(*this).contains(point);
}

template <typename Real>
/**
 * Determine if collinear with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::collinear(const Line3<Real>& line) const
{
    return Line3<Real>::from_ray(*this).coincident(line);
}

template <typename Real>
/**
 * Determine if collinear with another ray.
 * @param other Other ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::collinear(const Ray3<Real>& other) const
{
    return Line3<Real>::from_ray(*this).coincident(Line3<Real>::from_ray(other));
}

template <typename Real>
/**
 * Determine if coplanar with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::coplanar(const Line3<Real>& line) const
{
    return Line3<Real>::from_ray(*this).coplanar(line);
}

template <typename Real>
/**
 * Determine if coplanar with another ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::coplanar(const Ray3<Real>& ray) const
{
    return Line3<Real>::from_ray(*this).coplanar(Line3<Real>::from_ray(ray));
}

template <typename Real>
/**
 * Determine if coplanar with line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] bool Ray3<Real>::coplanar(const Segment3<Real>& segment) const
{
    return Line3<Real>::from_ray(*this).coplanar(segment);
}

template <typename Real>
/**
 * Closest distance squared to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Ray3<Real>::distance_sqrd(const Line3<Real>& line) const
{
    const Vector3<Real> dir_cross = direction.cross(line.direction);
    const Real dir_cross_len = dir_cross.length_sqrd();
    const Vector3<Real> diff = line.origin - origin;
    if (approx_zero(dir_cross_len)) {
        return line.distance_sqrd(origin);
    }
    const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len;
    const Real t_line = diff.cross(direction).dot(dir_cross) / dir_cross_len;
    if (approx_less_zero(t)) {
        return line.distance_sqrd(origin);
    }
    const Point3<Real> p1 = origin + direction * t;
    const Point3<Real> p2 = line.origin + line.direction * t_line;
    return p1.distance_sqrd(p2);
}

template <typename Real>
/**
 * Closest distance to a line. Zero if intersects.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Ray3<Real>::distance(const Line3<Real>& line) const
{
    return sqrt(distance_sqrd(line));
}

template <typename Real>
/**
 * Determine if parallel to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::parallel(const Line3<Real>& line) const
{
    return direction.cross(line.direction).approx_zero();
}

template <typename Real>
/**
 * Determine if perpendicular to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::perpendicular(const Line3<Real>& line) const
{
    return nnm::approx_zero(direction.dot(line.direction));
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray3<Real>::intersects(const Line3<Real>& line) const
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
    const Point3<Real> p = origin + direction * t;
    const Point3<Real> p_other = line.origin + line.direction * t_other;
    return p.approx_equal(p_other);
}

template <typename Real>
/**
 * Intersection point with a line.
 * @param line Line.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Ray3<Real>::intersection(const Line3<Real>& line) const
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
    const Point3<Real> p = origin + direction * t;
    if (const Point3<Real> p_other = line.origin + line.direction * t_other; !p.approx_equal(p_other)) {
        return std::nullopt;
    }
    return p;
}

template <typename Real>
/**
 * Determine if collinear with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::collinear(const Line3<Real>& line) const
{
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = start.direction_unnormalized(line.origin);
    return dir.parallel(line.direction) && dir.parallel(diff);
}

template <typename Real>
/**
 * Determine if collinear with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::collinear(const Ray3<Real>& ray) const
{
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = start.direction_unnormalized(ray.origin);
    return dir.parallel(ray.direction) && dir.parallel(diff);
}

template <typename Real>
/**
 * Determine if coplanar with line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::coplanar(const Line3<Real>& line) const
{
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = start.direction_unnormalized(line.origin);
    const Vector3<Real> dir_cross = dir.cross(line.direction);
    return diff.perpendicular(dir_cross);
}

template <typename Real>
/**
 * Determine if coplanar with ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::coplanar(const Ray3<Real>& ray) const
{
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = start.direction_unnormalized(ray.origin);
    const Vector3<Real> dir_cross = dir.cross(ray.direction);
    return diff.perpendicular(dir_cross);
}

template <typename Real>
/**
 * Closest distance squared to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Segment3<Real>::distance_sqrd(const Line3<Real>& line) const
{
    if (std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return line.distance_sqrd(*degen_point);
    }
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = line.origin - start;
    const Vector3<Real> dir_cross = dir.cross(line.direction);
    const Real dir_cross_len = dir_cross.length_sqrd();
    if (approx_zero(dir_cross_len)) {
        const Real d1 = line.distance_sqrd(start);
        const Real d2 = line.distance_sqrd(end);
        return min(d1, d2);
    }
    const Real t = diff.cross(line.direction).dot(dir_cross) / dir_cross_len;
    if (approx_less_zero(t)) {
        return line.distance_sqrd(start);
    }
    if (approx_greater(t, static_cast<Real>(1))) {
        return line.distance_sqrd(end);
    }
    const Real t_line = diff.cross(dir).dot(dir_cross) / dir_cross_len;
    const Point3<Real> p1 = start + dir * t;
    const Point3<Real> p2 = line.origin + line.direction * t_line;
    return p1.distance_sqrd(p2);
}

template <typename Real>
/**
 * Closest distance squared to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Segment3<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return ray.distance_sqrd(*degen_point);
    }
    const Vector3<Real> dir = direction_unnormalized();
    const Vector3<Real> diff = ray.origin - start;
    const Vector3<Real> dir_cross = dir.cross(ray.direction);
    const Real dir_cross_len = dir_cross.length_sqrd();
    if (approx_zero(dir_cross_len)) {
        const Real d1 = ray.distance_sqrd(start);
        const Real d2 = ray.distance_sqrd(end);
        const Real d3 = distance_sqrd(ray.origin);
        return min(d1, d2, d3);
    }
    const Real t = diff.cross(ray.direction).dot(dir_cross) / dir_cross_len;
    if (approx_less_zero(t)) {
        return ray.distance_sqrd(start);
    }
    if (approx_greater(t, static_cast<Real>(1))) {
        return ray.distance_sqrd(end);
    }
    const Real t_ray = diff.cross(dir).dot(dir_cross) / dir_cross_len;
    if (approx_less_zero(t_ray)) {
        return distance_sqrd(ray.origin);
    }
    const Point3<Real> p1 = start + dir * t;
    const Point3<Real> p2 = ray.origin + ray.direction * t_ray;
    return p1.distance_sqrd(p2);
}

template <typename Real>
/**
 * Closest distance to a line. Zero if intersects.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Segment3<Real>::distance(const Line3<Real>& line) const
{
    return sqrt(distance_sqrd(line));
}

template <typename Real>
/**
 * Closest distance to a ray. Zero if intersects.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Segment3<Real>::distance(const Ray3<Real>& ray) const
{
    return sqrt(distance_sqrd(ray));
}

template <typename Real>
/**
 * Determine if parallel to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::parallel(const Line3<Real>& line) const
{
    const Vector3<Real> proj = direction_unnormalized().cross(line.direction);
    return proj.approx_zero();
}

template <typename Real>
/**
 * Determine if parallel to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::parallel(const Ray3<Real>& ray) const
{
    const Vector3<Real> proj = direction_unnormalized().cross(ray.direction);
    return proj.approx_zero();
}

template <typename Real>
/**
 * Determine if perpendicular to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::perpendicular(const Line3<Real>& line) const
{
    const Real proj = direction_unnormalized().dot(line.direction);
    return approx_zero(proj);
}

template <typename Real>
/**
 * Determine if perpendicular to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    const Real proj = direction_unnormalized().dot(ray.direction);
    return approx_zero(proj);
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::intersects(const Line3<Real>& line) const
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
    const Point3<Real> p = start.lerp(end, t);
    const Point3<Real> p_other = line.origin + line.direction * t_line;
    return p.approx_equal(p_other);
}

template <typename Real>
/**
 * Intersection point with a line.
 * @param line Line.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Segment3<Real>::intersection(const Line3<Real>& line) const
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
    const Point3<Real> p = start.lerp(end, t);
    if (const Point3<Real> p_other = line.origin + line.direction * t_line; !p.approx_equal(p_other)) {
        return std::nullopt;
    }
    return p;
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment3<Real>::intersects(const Ray3<Real>& ray) const
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
    const Point3<Real> p = start.lerp(end, t);
    const Point3<Real> p_ray = ray.origin + ray.direction * t_ray;
    return p.approx_equal(p_ray);
}

template <typename Real>
/**
 * Intersection point with a ray.
 * @param ray Ray.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Segment3<Real>::intersection(const Ray3<Real>& ray) const
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
    const Point3<Real> p = start.lerp(end, t);
    if (const Point3<Real> p_ray = ray.origin + ray.direction * t_ray; !p.approx_equal(p_ray)) {
        return std::nullopt;
    }
    return p;
}

template <typename Real>
constexpr bool Line3<Real>::collinear(const Ray3<Real>& ray) const
{
    return ray.collinear(*this);
}

template <typename Real>
constexpr bool Line3<Real>::collinear(const Segment3<Real>& segment) const
{
    return segment.collinear(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Ray3<Real>& ray) const
{
    return ray.coplanar(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Segment3<Real>& segment) const
{
    return segment.coplanar(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr bool Line3<Real>::coplanar(const Rectangle3<Real>& rectangle) const
{
    return rectangle.coplanar(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    return ray.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    return segment.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    return plane.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    return triangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const AlignedBox<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance_sqrd(const Box<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Ray3<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Segment3<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
constexpr Real Line3<Real>::distance(const Plane<Real>& plane) const
{
    return plane.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Triangle3<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Sphere<Real>& sphere) const
{
    return sphere.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const AlignedBox<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
Real Line3<Real>::distance(const Box<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Segment3<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Plane<Real>& plane) const
{
    return plane.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Triangle3<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Rectangle3<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Sphere<Real>& sphere) const
{
    return sphere.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const AlignedBox<Real>& box) const
{
    return box.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Box<Real>& box) const
{
    return box.intersects(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Frustum<Real>& frustum) const
{
    return frustum.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Line3<Real>::intersection(const Segment3<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Line3<Real>::intersection(const Plane<Real>& plane) const
{
    return plane.intersection(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Line3<Real>::intersection(const Triangle3<Real>& triangle) const
{
    return triangle.intersection(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Line3<Real>::intersection(const Rectangle3<Real>& rectangle) const
{
    return rectangle.intersection(*this);
}

template <typename Real>
constexpr PointSet<Point3<Real>, 2> Line3<Real>::surface_intersections(const Sphere<Real>& sphere) const
{
    return sphere.surface_intersections(*this);
}

template <typename Real>
constexpr PointSet<Point3<Real>, 2> Line3<Real>::surface_intersections(const AlignedBox<Real>& box) const
{
    return box.surface_intersections(*this);
}

template <typename Real>
constexpr PointSet<Point3<Real>, 2> Line3<Real>::surface_intersections(const Box<Real>& box) const
{
    return box.surface_intersections(*this);
}

template <typename Real>
constexpr PointSet<Point3<Real>, 2> Line3<Real>::surface_intersections(const Frustum<Real>& frustum) const
{
    return frustum.surface_intersections(*this);
}

template <typename Real>
constexpr bool Line3<Real>::tangent(const Sphere<Real>& sphere) const
{
    return sphere.tangent(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Ray3<Real>& ray) const
{
    return ray.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Segment3<Real>& segment) const
{
    return segment.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Plane<Real>& plane) const
{
    return plane.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Triangle3<Real>& triangle) const
{
    return triangle.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::parallel(const Rectangle3<Real>& rectangle) const
{
    return rectangle.parallel(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    return ray.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Segment3<Real>& segment) const
{
    return segment.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Plane<Real>& plane) const
{
    return plane.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Triangle3<Real>& triangle) const
{
    return triangle.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::perpendicular(const Rectangle3<Real>& rectangle) const
{
    return rectangle.perpendicular(*this);
}

template <typename Real>
constexpr bool Line3<Real>::intersects(const Ray3<Real>& ray) const
{
    return ray.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Line3<Real>::intersection(const Ray3<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::coplanar(const Plane<Real>& plane) const
{
    return plane.coplanar(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::coplanar(const Rectangle3<Real>& rectangle) const
{
    return rectangle.coplanar(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    return segment.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    return plane.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    return triangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const AlignedBox<Real>& box)
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance_sqrd(const Box<Real>& box)
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Ray3<Real>::distance(const Plane<Real>& plane) const
{
    return plane.distance(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::parallel(const Segment3<Real>& segment) const
{
    return segment.parallel(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::parallel(const Plane<Real>& plane) const
{
    return plane.parallel(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::parallel(const Triangle3<Real>& triangle) const
{
    return triangle.parallel(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::parallel(const Rectangle3<Real>& rectangle) const
{
    return rectangle.parallel(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::perpendicular(const Segment3<Real>& segment) const
{
    return segment.perpendicular(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::perpendicular(const Plane<Real>& plane) const
{
    return plane.perpendicular(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::perpendicular(const Triangle3<Real>& triangle) const
{
    return triangle.perpendicular(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::perpendicular(const Rectangle3<Real>& rectangle) const
{
    return rectangle.perpendicular(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const Segment3<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const Triangle3<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const Sphere<Real>& sphere) const
{
    return sphere.distance(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const AlignedBox<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
Real Ray3<Real>::distance(const Box<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
constexpr bool Ray3<Real>::intersects(const Segment3<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Ray3<Real>::intersection(const Segment3<Real>& segment) const
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
constexpr Real Segment3<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    return plane.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    return triangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance_sqrd(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance_sqrd(const AlignedBox<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance_sqrd(const Box<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Segment3<Real>::distance(const Plane<Real>& plane) const
{
    return plane.distance(*this);
}

template <typename Real>
Real Segment3<Real>::distance(const Triangle3<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Segment3<Real>::distance(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Segment3<Real>::distance(const Sphere<Real>& sphere) const
{
    return sphere.distance(*this);
}

template <typename Real>
Real Segment3<Real>::distance(const AlignedBox<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
Real Segment3<Real>::distance(const Box<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
bool Segment3<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr std::optional<Point3<Real>> Segment3<Real>::intersection(const Plane<Real>& plane) const
{
    return plane.intersection(*this);
}

template <typename Real>
constexpr bool Segment3<Real>::intersects(const Plane<Real>& plane) const
{
    return plane.intersects(*this);
}

} // namespace nnm

#endif
