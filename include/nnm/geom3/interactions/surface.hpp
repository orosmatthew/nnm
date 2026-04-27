/* NNM - No Nonsense Math
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_INTERACTIONS_SURFACE_HPP
#define NNM_GEOM3_INTERACTIONS_SURFACE_HPP

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
 * Determine if coplanar with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::coplanar(const Line3<Real>& line) const
{
    return contains(line.origin) && normal.perpendicular(line.direction);
}

template <typename Real>
/**
 * Determine if coplanar with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::coplanar(const Ray3<Real>& ray) const
{
    return contains(ray.origin) && normal.perpendicular(ray.direction);
}

template <typename Real>
/**
 * Determine if coplanar with a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::coplanar(const Segment3<Real>& segment) const
{
    return contains(segment.start) && contains(segment.end);
}

template <typename Real>
/**
 * Closest distance squared to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance_sqrd(const Line3<Real>& line) const
{
    if (!parallel(line)) {
        return static_cast<Real>(0);
    }
    return distance_sqrd(line.origin);
}

template <typename Real>
/**
 * Closest distance squared to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    return distance_sqrd(ray.origin);
}

template <typename Real>
/**
 * Closest distance squared to a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    if (intersects(segment)) {
        return static_cast<Real>(0);
    }
    const Real d1 = distance_sqrd(segment.start);
    const Real d2 = distance_sqrd(segment.end);
    return min(d1, d2);
}

template <typename Real>
/**
 * Determine the closest distance with a line. Zero if intersects.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance(const Line3<Real>& line) const
{
    if (!parallel(line)) {
        return static_cast<Real>(0);
    }
    return distance(line.origin);
}

template <typename Real>
/**
 * Determine the closest distance with a ray. Zero if intersects.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance(const Ray3<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    return distance(ray.origin);
}

template <typename Real>
/**
 * Determine the closest distance with a line segment. Zero if intersects.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Plane<Real>::distance(const Segment3<Real>& segment) const
{
    if (intersects(segment)) {
        return static_cast<Real>(0);
    }
    const Real d1 = distance(segment.start);
    const Real d2 = distance(segment.end);
    return min(d1, d2);
}

template <typename Real>
/**
 * Determine if parallel with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::parallel(const Line3<Real>& line) const
{
    return normal.perpendicular(line.direction);
}

template <typename Real>
/**
 * Determine if parallel with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::parallel(const Ray3<Real>& ray) const
{
    return normal.perpendicular(ray.direction);
}

template <typename Real>
/**
 * Determine if parallel with a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::parallel(const Segment3<Real>& segment) const
{
    const Real proj = normal.dot(segment.direction_unnormalized());
    return approx_zero(proj);
}

template <typename Real>
/**
 * Determine if perpendicular with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::perpendicular(const Line3<Real>& line) const
{
    return normal.parallel(line.direction);
}

template <typename Real>
/**
 * Determine if perpendicular with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::perpendicular(const Ray3<Real>& ray) const
{
    return normal.parallel(ray.direction);
}

template <typename Real>
/**
 * Determine if perpendicular with a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::perpendicular(const Segment3<Real>& segment) const
{
    const Vector3<Real> cross = normal.cross(segment.direction_unnormalized());
    return cross.approx_zero();
}

template <typename Real>
/**
 * Determine if intersects with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::intersects(const Line3<Real>& line) const
{
    const Real proj = normal.dot(line.direction);
    return !approx_zero(proj) || contains(line.origin);
}

template <typename Real>
/**
 * Intersection point with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Plane<Real>::intersection(const Line3<Real>& line) const
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

template <typename Real>
/**
 * Determine if intersects with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Plane<Real>::intersects(const Ray3<Real>& ray) const
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

template <typename Real>
/**
 * Intersection point with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Plane<Real>::intersection(const Ray3<Real>& ray) const
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

template <typename Real>
// tested
[[nodiscard]] constexpr bool Plane<Real>::intersects(const Segment3<Real>& segment) const
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

template <typename Real>
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Plane<Real>::intersection(const Segment3<Real>& segment) const
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

template <typename Real>
// tested
[[nodiscard]] std::optional<Line3<Real>> Plane<Real>::intersection(const Plane<Real>& other) const
{
    const Vector3<Real> dir = normal.cross(other.normal);
    if (dir.approx_zero()) {
        return std::nullopt;
    }

    const Real d1 = -normal.dot(origin.to_vector());
    const Real d2 = -other.normal.dot(other.origin.to_vector());
    Point3<Real> point;
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

template <typename Real>
/**
 * Closest distance squared to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Triangle3<Real>::distance_sqrd(const Line3<Real>& line) const
{
    if (intersects(line)) {
        return static_cast<Real>(0);
    }
    return min(edge(0).distance_sqrd(line), edge(1).distance_sqrd(line), edge(2).distance_sqrd(line));
}

template <typename Real>
/**
 * Closest distance squared to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Triangle3<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    return min(
        distance_sqrd(ray.origin), edge(0).distance_sqrd(ray), edge(1).distance_sqrd(ray), edge(2).distance_sqrd(ray));
}

template <typename Real>
/**
 * Closest distance squared to a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Triangle3<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    if (intersects(segment)) {
        return static_cast<Real>(0);
    }
    return min(
        distance_sqrd(segment.start),
        distance_sqrd(segment.end),
        edge(0).distance_sqrd(segment),
        edge(1).distance_sqrd(segment),
        edge(2).distance_sqrd(segment));
}

template <typename Real>
/**
 * Closest distance squared to a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Triangle3<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    if (intersects(plane)) {
        return static_cast<Real>(0);
    }
    return min(plane.distance_sqrd(vertices[0]), plane.distance_sqrd(vertices[1]), plane.distance_sqrd(vertices[2]));
}

template <typename Real>
/**
 * Closest distance to a line. Zero if intersects.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Triangle3<Real>::distance(const Line3<Real>& line) const
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
[[nodiscard]] Real Triangle3<Real>::distance(const Ray3<Real>& ray) const
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
[[nodiscard]] Real Triangle3<Real>::distance(const Segment3<Real>& segment) const
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
[[nodiscard]] constexpr Real Triangle3<Real>::distance(const Plane<Real>& plane) const
{
    if (intersects(plane)) {
        return static_cast<Real>(0);
    }
    return min(plane.distance(vertices[0]), plane.distance(vertices[1]), plane.distance(vertices[2]));
}

template <typename Real>
/**
 * Determine if parallel with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle3<Real>::parallel(const Line3<Real>& line) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->parallel(line);
    }
    const Vector3<Real> normal = (vertices[0] - vertices[1]).cross(vertices[0] - vertices[2]);
    return normal.perpendicular(line.direction);
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::parallel(const Ray3<Real>& ray) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->parallel(ray);
    }
    const Vector3<Real> normal = (vertices[0] - vertices[1]).cross(vertices[0] - vertices[2]);
    return normal.perpendicular(ray.direction);
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::perpendicular(const Line3<Real>& line) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->perpendicular(line);
    }
    const Vector3<Real> d01 = vertices[0] - vertices[1];
    const Vector3<Real> d02 = vertices[0] - vertices[2];
    const Vector3<Real> cross = d01.cross(d02);
    return cross.parallel(line.direction);
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->perpendicular(ray);
    }
    const Vector3<Real> normal = (vertices[0] - vertices[1]).cross(vertices[0] - vertices[2]);
    return normal.parallel(ray.direction);
}

template <typename Real>
/**
 * Determine if intersects with a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle3<Real>::intersects(const Line3<Real>& line) const
{
    // Degenerates are handled gracefully by det check below.
    const Vector3<Real> d10 = vertices[1] - vertices[0];
    const Vector3<Real> d20 = vertices[2] - vertices[0];
    const Vector3<Real> line_dir_edge_cross = line.direction.cross(d20);
    const Real det = d10.dot(line_dir_edge_cross);
    if (approx_zero(det)) {
        return edge(0).intersects(line) || edge(1).intersects(line) || edge(2).intersects(line);
    }
    // Moller–Trumbore algorithm
    const Real inv_det = static_cast<Real>(1) / det;
    const Vector3<Real> diff = line.origin - vertices[0];
    const Real u = inv_det * diff.dot(line_dir_edge_cross);
    if (approx_less_zero(u) || approx_greater(u, static_cast<Real>(1))) {
        return false;
    }
    const Real v = inv_det * line.direction.dot(diff.cross(d10));
    if (approx_less_zero(v) || approx_greater(u + v, static_cast<Real>(1))) {
        return false;
    }
    return true;
}

template <typename Real>
/**
 * Intersection point with a line. Returns null if coplanar intersection.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] std::optional<Point3<Real>> Triangle3<Real>::intersection(const Line3<Real>& line) const
{
    const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
    if (!plane.has_value()) {
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Point3<Real>> point = edge(i).intersection(line);
            if (point.has_value()) {
                return *point;
            }
        }
        return std::nullopt;
    }
    const std::optional<Point3<Real>> point = plane->intersection(line);
    if (!point.has_value() || !contains_projected(*point)) {
        return std::nullopt;
    }
    return *point;
}

template <typename Real>
/**
 * Determine if intersects with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle3<Real>::intersects(const Ray3<Real>& ray) const
{
    // Degenerates are handled gracefully by det check below.
    const Vector3<Real> d10 = vertices[1] - vertices[0];
    const Vector3<Real> d20 = vertices[2] - vertices[0];
    const Vector3<Real> ray_dir_edge_cross = ray.direction.cross(d20);
    const Real det = d10.dot(ray_dir_edge_cross);
    if (approx_zero(det)) {
        return edge(0).intersects(ray) || edge(1).intersects(ray) || edge(2).intersects(ray);
    }
    // Moller–Trumbore algorithm
    const Real inv_det = static_cast<Real>(1) / det;
    const Vector3<Real> diff = ray.origin - vertices[0];
    const Real u = inv_det * diff.dot(ray_dir_edge_cross);
    if (approx_less_zero(u) || approx_greater(u, static_cast<Real>(1))) {
        return false;
    }
    const Vector3<Real> diff_cross_edge = diff.cross(d10);
    const Real v = inv_det * ray.direction.dot(diff_cross_edge);
    if (approx_less_zero(v) || approx_greater(u + v, static_cast<Real>(1))) {
        return false;
    }
    const Real t = inv_det * d20.dot(diff_cross_edge);
    return approx_greater_equal_zero(t);
}

template <typename Real>
/**
 * Intersection point with a ray. Returns null if coplanar intersection.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] std::optional<Point3<Real>> Triangle3<Real>::intersection(const Ray3<Real>& ray) const
{
    const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
    if (!plane.has_value()) {
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Point3<Real>> point = edge(i).intersection(ray);
            if (point.has_value()) {
                return *point;
            }
        }
        return std::nullopt;
    }
    const std::optional<Point3<Real>> point = plane->intersection(ray);
    if (!point.has_value() || !contains_projected(*point)) {
        return std::nullopt;
    }
    return *point;
}

template <typename Real>
/**
 * Determine if intersects with a line segment
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle3<Real>::intersects(const Segment3<Real>& segment) const
{
    // Degenerates are handled gracefully by det check below.
    const Vector3<Real> d10 = vertices[1] - vertices[0];
    const Vector3<Real> d20 = vertices[2] - vertices[0];
    const Vector3<Real> seg_dir = segment.direction_unnormalized();
    const Vector3<Real> seg_dir_edge_cross = seg_dir.cross(d20);
    const Real det = d10.dot(seg_dir_edge_cross);
    if (approx_zero(det)) {
        return edge(0).intersects(segment) || edge(1).intersects(segment) || edge(2).intersects(segment);
    }
    // Moller–Trumbore algorithm
    const Real inv_det = static_cast<Real>(1) / det;
    const Vector3<Real> diff = segment.start - vertices[0];
    const Real u = inv_det * diff.dot(seg_dir_edge_cross);
    if (approx_less_zero(u) || approx_greater(u, static_cast<Real>(1))) {
        return false;
    }
    const Vector3<Real> diff_cross_edge = diff.cross(d10);
    const Real v = inv_det * seg_dir.dot(diff_cross_edge);
    if (approx_less_zero(v) || approx_greater(u + v, static_cast<Real>(1))) {
        return false;
    }
    const Real t = inv_det * d20.dot(diff_cross_edge);
    return approx_greater_equal_zero(t) && approx_less_equal(t, static_cast<Real>(1));
}

template <typename Real>
/**
 * Intersection point with a line segment. Returns null if coplanar intersection.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] std::optional<Point3<Real>> Triangle3<Real>::intersection(const Segment3<Real>& segment) const
{
    std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
    if (!plane.has_value()) {
        for (uint8_t i = 0; i < 3; ++i) {
            const std::optional<Point3<Real>> point = edge(i).intersection(segment);
            if (point.has_value()) {
                return *point;
            }
        }
        return std::nullopt;
    }
    const std::optional<Point3<Real>> point = plane->intersection(segment);
    if (!point.has_value() || !contains_projected(*point)) {
        return std::nullopt;
    }
    return *point;
}

template <typename Real>
/**
 * Determine if intersects with a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle3<Real>::intersects(const Plane<Real>& plane) const
{
    return plane.intersects(edge(0)) || plane.intersects(edge(1)) || plane.intersects(edge(2));
}

template <typename Real>
/**
 * Intersection with a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Segment3<Real>> Triangle3<Real>::intersection(const Plane<Real>& plane) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 3; ++i) {
        const std::optional<Point3<Real>> point = plane.intersection(edge(i));
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

template <typename Real>
/**
 * Intersection with another triangle.
 * If polygonal intersection exists, null is returned.
 * @param other Other triangle
 * @return Result.
 */
// tested
[[nodiscard]] std::optional<Segment3<Real>> Triangle3<Real>::intersection(const Triangle3<Real>& other) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 3; ++i) {
        const std::optional<Point3<Real>> point1 = intersection(other.edge(i));
        if (point1.has_value()) {
            inters.insert(*point1);
        }
        const std::optional<Point3<Real>> point2 = other.intersection(edge(i));
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

template <typename Real>
/**
 * Closest distance squared to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Rectangle3<Real>::distance_sqrd(const Line3<Real>& line) const
{
    if (intersects(line)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 4; ++i) {
        const Real dist = edge(i).distance_sqrd(line);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance squared to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Rectangle3<Real>::distance_sqrd(const Ray3<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    Real min_dist = distance_sqrd(ray.origin);
    for (uint8_t i = 0; i < 4; ++i) {
        const Real dist = edge(i).distance_sqrd(ray);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance squared to a line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Rectangle3<Real>::distance_sqrd(const Segment3<Real>& segment) const
{
    if (intersects(segment)) {
        return static_cast<Real>(0);
    }
    Real min_dist = min(distance_sqrd(segment.start), distance_sqrd(segment.end));
    for (uint8_t i = 0; i < 4; ++i) {
        const Real dist = edge(i).distance_sqrd(segment);
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance squared to a plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Rectangle3<Real>::distance_sqrd(const Plane<Real>& plane) const
{
    if (intersects(plane)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 4; ++i) {
        const Real dist = edge(i).distance_sqrd(plane);
        min_dist = min(min_dist, dist);
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
[[nodiscard]] constexpr Real Rectangle3<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return triangle.distance_sqrd(*degen_point);
    }
    if (const std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->distance_sqrd(triangle);
    }
    if (intersects(triangle)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (uint8_t i = 0; i < 3; ++i) {
        const Real dist = distance_sqrd(triangle.edge(i));
        min_dist = min(min_dist, dist);
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle3<Real>::distance(const Line3<Real>& line) const
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
[[nodiscard]] Real Rectangle3<Real>::distance(const Ray3<Real>& ray) const
{
    return sqrt(distance_sqrd(ray));
}

template <typename Real>
/**
 * Closest distance to line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle3<Real>::distance(const Segment3<Real>& segment) const
{
    return sqrt(distance_sqrd(segment));
}

template <typename Real>
/**
 * Closest distance to plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Rectangle3<Real>::distance(const Plane<Real>& plane) const
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

template <typename Real>
/**
 * Closest distance to triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle3<Real>::distance(const Triangle3<Real>& triangle) const
{
    return sqrt(distance_sqrd(triangle));
}

template <typename Real>
/**
 * Determine if parallel to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::parallel(const Line3<Real>& line) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->parallel(line);
    }
    const Vector3<Real> normal = half_span_u.cross(half_span_v);
    return normal.perpendicular(line.direction);
}

template <typename Real>
[[nodiscard]] constexpr bool Rectangle3<Real>::parallel(const Ray3<Real>& ray) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->parallel(ray);
    }
    const Vector3<Real> normal = half_span_u.cross(half_span_v);
    return normal.perpendicular(ray.direction);
}

template <typename Real>
/**
 * Determine if perpendicular to a line.
 * @param line Line
 * @returns Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::perpendicular(const Line3<Real>& line) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->perpendicular(line);
    }
    const Vector3<Real> cross = half_span_u.cross(half_span_v);
    return cross.parallel(line.direction);
}

template <typename Real>
[[nodiscard]] constexpr bool Rectangle3<Real>::perpendicular(const Ray3<Real>& ray) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->perpendicular(ray);
    }
    const Vector3<Real> normal = half_span_u.cross(half_span_v);
    return normal.parallel(ray.direction);
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::intersects(const Line3<Real>& line) const
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
    const Point3<Real> plane_inter = line.origin + line.direction * t;
    return contains(plane_inter);
}

template <typename Real>
/**
 * Intersection point with line. Returns null if coplanar.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Rectangle3<Real>::intersection(const Line3<Real>& line) const
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
    const Point3<Real> plane_inter = line.origin + line.direction * t;
    if (!contains(plane_inter)) {
        return std::nullopt;
    }
    return plane_inter;
}

template <typename Real>
/**
 * Determine if intersects with ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::intersects(const Ray3<Real>& ray) const
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
    const Point3<Real> plane_inter = ray.origin + ray.direction * t;
    return contains(plane_inter);
}

template <typename Real>
/**
 * Intersection point with ray. Returns null if coplanar.
 * @param ray Ray.
 * @return Result.
 */
[[nodiscard]] constexpr std::optional<Point3<Real>> Rectangle3<Real>::intersection(const Ray3<Real>& ray) const
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
    const Point3<Real> plane_inter = ray.origin + ray.direction * t;
    if (!contains(plane_inter)) {
        return std::nullopt;
    }
    return plane_inter;
}

template <typename Real>
/**
 * Determine if intersects line segment.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::intersects(const Segment3<Real>& segment) const
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
    const Point3<Real> plane_inter = segment.start + segment_dir * t;
    return contains(plane_inter);
}

template <typename Real>
/**
 * Intersection point with line segment. Returns null if coplanar.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point3<Real>> Rectangle3<Real>::intersection(const Segment3<Real> segment) const
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
    const Point3<Real> plane_inter = segment.start + segment_dir * t;
    if (!contains(plane_inter)) {
        return std::nullopt;
    }
    return plane_inter;
}

template <typename Real>
[[nodiscard]] constexpr std::optional<Segment3<Real>> Rectangle3<Real>::intersection(const Plane<Real>& plane) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 4; ++i) {
        if (const std::optional<Point3<Real>> inter = plane.intersection(edge(i)); inter.has_value()) {
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

template <typename Real>
/**
 * Determine if intersects plane.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::intersects(const Plane<Real>& plane) const
{
    for (uint8_t i = 0; i < 4; ++i) {
        if (edge(i).intersects(plane)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersection points between edges.
 * @param plane Plane.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point3<Real>, 2> Rectangle3<Real>::edge_intersections(const Plane<Real>& plane) const
{
    for (uint8_t i = 0; i < 4; ++i) {
        if (const Segment3<Real> e = edge(i); !e.start.approx_equal(e.end) && plane.coplanar(e)) {
            return { };
        }
    }
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 4; ++i) {
        if (const std::optional<Point3<Real>> inter = edge(i).intersection(plane); inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                return inters;
            }
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Rectangle3<Real>::intersects(const Triangle3<Real>& triangle) const
{
    if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return triangle.contains(*degen_point);
    }
    if (const std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return triangle.intersects(*degen_segment);
    }
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

template <typename Real>
/**
 *Intersection points between the edges between this rectangle and a triangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point3<Real>, 2> Rectangle3<Real>::edge_intersections(const Triangle3<Real>& triangle) const
{
    PointSet<Point3<Real>, 2> inters;
    for (uint8_t i = 0; i < 3; ++i) {
        if (const std::optional<Point3<Real>> inter = intersection(triangle.edge(i)); inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                return inters;
            }
        }
    }
    for (uint8_t i = 0; i < 4; ++i) {
        if (const std::optional<Point3<Real>> inter = triangle.intersection(edge(i)); inter.has_value()) {
            inters.insert(*inter);
            if (inters.size() >= 2) {
                return inters;
            }
        }
    }
    return inters;
}

template <typename Real>
constexpr Real Plane<Real>::distance_sqrd(const Triangle3<Real>& triangle) const
{
    return triangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance_sqrd(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance_sqrd(const AlignedBox<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance_sqrd(const Box<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance(const Triangle3<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance(*this);
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
constexpr Real Triangle3<Real>::distance_sqrd(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Triangle3<Real>::distance_sqrd(const AlignedBox<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
constexpr Real Triangle3<Real>::distance_sqrd(const Box<Real>& box) const
{
    return box.distance_sqrd(*this);
}

template <typename Real>
bool Plane<Real>::coplanar(const Triangle3<Real>& triangle) const
{
    return triangle.coplanar(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance(const AlignedBox<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance(const Box<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
constexpr Real Plane<Real>::distance(const Sphere<Real>& sphere) const
{
    return sphere.distance(*this);
}

template <typename Real>
Real Triangle3<Real>::distance(const Rectangle3<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Triangle3<Real>::distance(const Sphere<Real>& sphere) const
{
    return sphere.distance(*this);
}

template <typename Real>
Real Triangle3<Real>::distance(const AlignedBox<Real>& box) const
{
    return box.distance(*this);
}

template <typename Real>
Real Triangle3<Real>::distance(const Box<Real>& box) const
{
    return box.distance(*this);
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

} // namespace nnm

#endif
