/* NNM - No Nonsense Math
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_INTERACTIONS_VOLUME_HPP
#define NNM_GEOM3_INTERACTIONS_VOLUME_HPP

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
 * Closest distance to a line. Zero if intersects or is inside the sphere.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Sphere<Real>::distance(const Line3<Real>& line) const
{
    return max(static_cast<Real>(0), line.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to a ray. Zero if intersects or is inside the sphere.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Sphere<Real>::distance(const Ray3<Real>& ray) const
{
    return max(static_cast<Real>(0), ray.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to a line segment. Zero if intersects or is inside the sphere.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Sphere<Real>::distance(const Segment3<Real>& segment) const
{
    return max(static_cast<Real>(0), segment.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to a plane. Zero if intersects.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Sphere<Real>::distance(const Plane<Real>& plane) const
{
    return max(static_cast<Real>(0), plane.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to a triangle. Zero if intersects or if contains triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Sphere<Real>::distance(const Triangle3<Real>& triangle) const
{
    return max(static_cast<Real>(0), triangle.distance(center) - radius);
}

template <typename Real>
/**
 * Determine if intersects with a line. Being inside the circle is considered an intersection.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Sphere<Real>::intersects(const Line3<Real>& line) const
{
    const Vector3<Real> dir = line.origin - center;
    const Real a = line.direction.dot(line.direction);
    const Real b = static_cast<Real>(2) * dir.dot(line.direction);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
    return approx_greater_equal_zero(discriminant);
}

template <typename Real>
/**
 * Intersection points with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point3<Real>, 2> Sphere<Real>::surface_intersections(const Line3<Real>& line) const
{
    const Vector3<Real> dir = line.origin - center;
    const Real a = line.direction.dot(line.direction);
    const Real b = static_cast<Real>(2) * dir.dot(line.direction);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
    if (approx_less_zero(discriminant)) {
        return { };
    }
    if (approx_zero(discriminant)) {
        const Real t = -b / (static_cast<Real>(2) * a);
        const Point3<Real> p = line.origin + line.direction * t;
        return PointSet<Point3<Real>, 2> { p };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
    const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
    const Point3<Real> p1 = line.origin + line.direction * t1;
    const Point3<Real> p2 = line.origin + line.direction * t2;
    return { p1, p2 };
}

template <typename Real>
/**
 * Determine if intersects with a ray. Being inside the sphere is considered an intersection.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] bool Sphere<Real>::intersects(const Ray3<Real>& ray) const
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

template <typename Real>
/**
 * Intersection points with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point3<Real>, 2> Sphere<Real>::surface_intersections(const Ray3<Real>& ray) const
{
    const Vector3<Real> dir = ray.origin - center;
    const Real a = ray.direction.dot(ray.direction);
    const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
    if (approx_less_zero(discriminant)) {
        return { };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
    const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
    PointSet<Point3<Real>, 2> inters;
    if (approx_greater_equal_zero(t1)) {
        inters.insert(ray.origin + ray.direction * t1);
    }
    if (approx_greater_equal_zero(t2)) {
        inters.insert(ray.origin + ray.direction * t2);
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects with a line segment. Being inside the sphere is considered an intersection.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] bool Sphere<Real>::intersects(const Segment3<Real>& segment) const
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

template <typename Real>
/**
 * Intersection points with a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point3<Real>, 2> Sphere<Real>::surface_intersections(const Segment3<Real>& segment) const
{
    const Vector3<Real> seg_dir = segment.direction_unnormalized();
    const Vector3<Real> dir = segment.start - center;
    const Real a = seg_dir.dot(seg_dir);
    const Real b = static_cast<Real>(2) * dir.dot(seg_dir);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
    if (approx_less_zero(discriminant)) {
        return { };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-b - disc_sqrt) / (static_cast<Real>(2) * a);
    const Real t2 = (-b + disc_sqrt) / (static_cast<Real>(2) * a);
    const Real seg_length = segment.length();
    PointSet<Point3<Real>, 2> inters;
    if (approx_greater_equal_zero(t1) && approx_less_equal(t1, static_cast<Real>(1))) {
        inters.insert(segment.start + seg_dir * t1);
    }
    if (approx_greater_equal_zero(t2) && approx_less_equal(t2, static_cast<Real>(1))) {
        inters.insert(segment.start + seg_dir * t2);
    }
    return inters;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr bool Sphere<Real>::intersects(const Rectangle3<Real>& rectangle) const
{
    return approx_less_equal(rectangle.distance_sqrd(center), sqrd(radius));
}

template <typename Real>
/**
 * Determine if tangent to line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Sphere<Real>::tangent(const Line3<Real>& line) const
{
    const Vector3<Real> dir = line.origin - center;
    const Real a = line.direction.dot(line.direction);
    const Real b = static_cast<Real>(2) * dir.dot(line.direction);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * a * c;
    return approx_zero(discriminant);
}

template <typename Real>
/**
 * Determine if tangent to ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Sphere<Real>::tangent(const Ray3<Real>& ray) const
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

template <typename Real>
/**
 * Determine if tangent to line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Sphere<Real>::tangent(const Segment3<Real>& segment) const
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

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real AlignedBox<Real>::distance_sqrd(const Line3<Real>& line) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(line);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real AlignedBox<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(ray);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real AlignedBox<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(segment);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real AlignedBox<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(plane);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance squared to a triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real AlignedBox<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(triangle);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line. Zero if intersecting.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedBox<Real>::distance(const Line3<Real>& line) const
{
    return sqrt(distance_sqrd(line));
}

template <typename Real>
/**
 * Closest distance to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedBox<Real>::distance(const Ray3<Real>& ray) const
{
    return sqrt(distance_sqrd(ray));
}

template <typename Real>
// TODO: test
[[nodiscard]] Real AlignedBox<Real>::distance(const Segment3<Real>& segment) const
{
    return sqrt(distance_sqrd(segment));
}

template <typename Real>
/**
 * Closest distance to a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real AlignedBox<Real>::distance(const Plane<Real>& plane) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance(plane);
        min_dist = nnm::min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] Real AlignedBox<Real>::distance(const Triangle3<Real>& triangle) const
{
    return sqrt(distance_sqrd(triangle));
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Line3<Real>& line) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(line)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Ray3<Real>& ray) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(ray)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Segment3<Real>& segment) const
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

template <typename Real>
/**
 * Determine if intersects a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Plane<Real>& plane) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(plane)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] bool AlignedBox<Real>::intersects(const Triangle3<Real>& triangle) const
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

template <typename Real>
/**
 * Determine if intersects a rectangle.
 * @param rectangle Rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Rectangle3<Real>& rectangle) const
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

template <typename Real>
/**
 * Determine if intersects a sphere.
 * @param sphere Sphere.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedBox<Real>::intersects(const Sphere<Real>& sphere) const
{
    Point3<Real> closest = sphere.center.clamp(min, max);
    const Real center_dist_sqrd = (closest - sphere.center).length_sqrd();
    return approx_less_equal(center_dist_sqrd, sqrd(sphere.radius));
}

template <typename Real>
/**
 * Surface intersection points with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> AlignedBox<Real>::surface_intersections(const Line3<Real>& line) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(line);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Surface intersection points with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> AlignedBox<Real>::surface_intersections(const Ray3<Real>& ray) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(ray);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Surface intersection points with a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> AlignedBox<Real>::surface_intersections(
    const Segment3<Real>& segment) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(segment);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real Box<Real>::distance_sqrd(const Line3<Real>& line) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(line);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real Box<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(ray);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO:test
[[nodiscard]] constexpr Real Box<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(segment);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] constexpr Real Box<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(plane);
        min_dist = min(min_dist, dist);
        if (approx_zero(min_dist)) {
            break;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance squared to a triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Box<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance_sqrd(triangle);
        min_dist = min(min_dist, dist);
        if (approx_zero(min_dist)) {
            break;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line. Zero if intersecting.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Box<Real>::distance(const Line3<Real>& line) const
{
    return sqrt(distance_sqrd(line));
}

template <typename Real>
/**
 * Closest distance to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Box<Real>::distance(const Ray3<Real>& ray) const
{
    return sqrt(distance_sqrd(ray));
}

template <typename Real>
/**
 * Closest distance to a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Box<Real>::distance(const Segment3<Real>& segment) const
{
    return sqrt(distance_sqrd(segment));
}

template <typename Real>
/**
 * Closest distance to a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Box<Real>::distance(const Plane<Real>& plane) const
{
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 6; ++i) {
        const Real dist = face(i).distance(plane);
        min_dist = min(min_dist, dist);
        if (approx_zero(min_dist)) {
            break;
        }
    }
    return min_dist;
}

template <typename Real>
// TODO: test
[[nodiscard]] Real Box<Real>::distance(const Triangle3<Real>& triangle) const
{
    return sqrt(distance_sqrd(triangle));
}

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Line3<Real>& line) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(line)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Ray3<Real>& ray) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(ray)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Segment3<Real>& segment) const
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

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Plane<Real>& plane) const
{
    for (uint8_t i = 0; i < 6; ++i) {
        if (face(i).intersects(plane)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
[[nodiscard]] bool Box<Real>::intersects(const Triangle3<Real>& triangle) const
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

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Rectangle3<Real>& rectangle) const
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

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const Sphere<Real>& sphere) const
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

template <typename Real>
[[nodiscard]] constexpr bool Box<Real>::intersects(const AlignedBox<Real>& aligned_box) const
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

template <typename Real>
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Box<Real>::surface_intersections(const Line3<Real>& line) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(line);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Box<Real>::surface_intersections(const Ray3<Real>& ray) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(ray);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Box<Real>::surface_intersections(const Segment3<Real>& segment) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 6; ++i) {
        const std::optional<Point3<Real>> inter = face(i).intersection(segment);
        if (inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Line3<Real>& line) const
{
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        const std::optional<Point3<Real>> inter = plane.intersection(line);
        if (inter.has_value() && contains(*inter)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Ray3<Real>& ray) const
{
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(ray);
            inter.has_value() && contains(inter.value())) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a line segment.
 * A segment inside the frustum is considered intersecting.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Segment3<Real>& segment) const
{
    if (contains(segment.midpoint())) {
        return true;
    }
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(segment);
            inter.has_value() && contains(inter.value())) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Determine if intersects a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] bool Frustum<Real>::intersects(const Plane<Real>& plane) const
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

template <typename Real>
/**
 * Determine if intersects a triangle.
 * A triangle inside the frustum is considered intersecting.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Triangle3<Real>& triangle) const
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

template <typename Real>
/**
 * Determine if intersects a rectangle.
 * A rectangle inside the frustum is considered intersecting.
 * @param rectangle Rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Rectangle3<Real>& rectangle) const
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

template <typename Real>
/**
 * Determine if intersects a sphere.
 * A sphere inside the frustum is considered intersecting.
 * @param sphere Sphere.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Sphere<Real>& sphere) const
{
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const Real signed_dist = plane.signed_distance(sphere.center); approx_less(signed_dist, -sphere.radius)) {
            return false;
        }
    }
    return true;
}

template <typename Real>
/**
 * Determine if intersects an aligned box.
 * A box inside the frustum is considered intersecting.
 * @param box Aligned box.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const AlignedBox<Real>& box) const
{
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        const Point3<Real> furthest { plane.normal.x > static_cast<Real>(0) ? box.max.x : box.min.x,
                                      plane.normal.y > static_cast<Real>(0) ? box.max.y : box.min.y,
                                      plane.normal.z > static_cast<Real>(0) ? box.max.z : box.min.z };
        if (const Real signed_dist = plane.signed_distance(furthest); approx_less_zero(signed_dist)) {
            return false;
        }
    }
    return true;
}

template <typename Real>
/**
 * Determine if intersects a box.
 * A box inside the frustum is considered intersecting.
 * @param box Box.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Frustum<Real>::intersects(const Box<Real>& box) const
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

template <typename Real>
/**
 * Surface intersection points with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Frustum<Real>::surface_intersections(const Line3<Real>& line) const
{
    PointSet<Point3<Real>, 2> inters;
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(line);
            inter.has_value() && contains(inter.value())) {
            inters.insert(inter.value());
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Surface intersections with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Frustum<Real>::surface_intersections(const Ray3<Real>& ray) const
{
    PointSet<Point3<Real>, 2> inters;
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(ray);
            inter.has_value() && contains(inter.value())) {
            inters.insert(inter.value());
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Surface intersections with a line segment.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point3<Real>, 2> Frustum<Real>::surface_intersections(const Segment3<Real>& segment) const
{
    PointSet<Point3<Real>, 2> inters;
    std::array<Plane<Real>, 6> planes { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    for (const Plane<Real>& plane : planes) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(segment);
            inter.has_value() && contains(inter.value())) {
            inters.insert(inter.value());
            if (inters.size() >= 2) {
                break;
            }
        }
    }
    return inters;
}

} // namespace nnm

#endif
