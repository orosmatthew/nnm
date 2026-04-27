/* NNM - No Nonsense Math
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_INTERACTIONS_POLYGON_HPP
#define NNM_GEOM2_INTERACTIONS_POLYGON_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>
#include <nnm/geom2/line2.hpp>
#include <nnm/geom2/ray2.hpp>
#include <nnm/geom2/segment2.hpp>
#include <nnm/geom2/circle2.hpp>
#include <nnm/geom2/triangle2.hpp>
#include <nnm/geom2/rectangle2.hpp>
#include <nnm/geom2/aligned_rectangle2.hpp>

namespace nnm {

template <typename Real>
/**
 * Closest distance to line. Zero if intersects or is inside circle.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Circle2<Real>::distance(const Line2<Real>& line) const
{
    return max(static_cast<Real>(0), line.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to ray. Zero if intersects or is inside circle.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Circle2<Real>::distance(const Ray2<Real>& ray) const
{
    return max(static_cast<Real>(0), ray.distance(center) - radius);
}

template <typename Real>
/**
 * Closest distance to segment. Zero if intersects or is inside circle.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Circle2<Real>::distance(const Segment2<Real>& segment) const
{
    return max(static_cast<Real>(0), segment.distance(center) - radius);
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Circle2<Real>::intersects(const Line2<Real>& line) const
{
    if (contains(line.origin)) {
        return true;
    }
    const Vector2<Real> dir = line.origin - center;
    const Real twice_proj_length = static_cast<Real>(2) * dir.dot(line.direction);
    const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
    return discriminant >= static_cast<Real>(0);
}

template <typename Real>
/**
 * Intersection points with a line. If only single intersection, both returned points are equal.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Circle2<Real>::edge_intersections(const Line2<Real>& line) const
{
    const Vector2<Real> dir = line.origin - center;
    const Real twice_proj_length = static_cast<Real>(2) * dir.dot(line.direction);
    const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
    if (discriminant < static_cast<Real>(0)) {
        return { };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
    const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
    const Point2<Real> p1 = line.origin + line.direction * t1;
    const Point2<Real> p2 = line.origin + line.direction * t2;
    return { p1, p2 };
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] bool Circle2<Real>::intersects(const Ray2<Real>& ray) const
{
    if (contains(ray.origin)) {
        return true;
    }
    const Vector2<Real> dir = ray.origin - center;
    const Real twice_proj_length = static_cast<Real>(2) * dir.dot(ray.direction);
    const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
    if (discriminant < static_cast<Real>(0)) {
        return false;
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
    const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
    if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
        return true;
    }
    if (t1 >= static_cast<Real>(0) || t2 >= static_cast<Real>(0)) {
        return true;
    }
    return false;
}

template <typename Real>
/**
 * Intersection points with a ray. If only single intersection, both returned points are equal.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Circle2<Real>::edge_intersections(const Ray2<Real>& ray) const
{
    const Vector2<Real> dir = ray.origin - center;
    const Real twice_proj_length = static_cast<Real>(2) * dir.dot(ray.direction);
    const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
    if (discriminant < static_cast<Real>(0)) {
        return { };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
    const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
    PointSet<Point2<Real>, 2> inters;
    if (t1 >= static_cast<Real>(0)) {
        const Point2<Real> p = ray.origin + ray.direction * t1;
        inters.insert(p);
    }
    if (t2 >= static_cast<Real>(0)) {
        const Point2<Real> p = ray.origin + ray.direction * t2;
        inters.insert(p);
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects segment. Being inside the circle is considered an intersection.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] bool Circle2<Real>::intersects(const Segment2<Real>& segment) const
{
    if (contains(segment.start) || contains(segment.end)) {
        return true;
    }
    const Vector2<Real> seg_dir = segment.end - segment.start;
    const Vector2<Real> circle_dir = segment.start - center;
    const Real seg_len_sqrd = seg_dir.dot(seg_dir);
    const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
    const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
    if (discriminant < static_cast<Real>(0)) {
        return false;
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-twice_proj_len - disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
    const Real t2 = (-twice_proj_len + disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
    if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1) && t2 >= static_cast<Real>(0)
        && t2 <= static_cast<Real>(1)) {
        return true;
    }
    if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1)) {
        return true;
    }
    if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
        return true;
    }
    return false;
}

template <typename Real>
/**
 * Intersection points with a segment. If only single intersection, both returned points are equal.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Circle2<Real>::edge_intersections(const Segment2<Real>& segment) const
{
    const Vector2<Real> seg_dir = segment.end - segment.start;
    const Vector2<Real> circle_dir = segment.start - center;
    const Real seg_len_sqrd = seg_dir.dot(seg_dir);
    const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
    const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
    const Real discriminant = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
    if (discriminant < static_cast<Real>(0)) {
        return { };
    }
    const Real disc_sqrt = sqrt(discriminant);
    const Real t1 = (-twice_proj_len - disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
    const Real t2 = (-twice_proj_len + disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
    PointSet<Point2<Real>, 2> inters;
    if (t1 >= static_cast<Real>(0) && t1 <= static_cast<Real>(1)) {
        const Point2<Real> p = segment.start + seg_dir * t1;
        inters.insert(p);
    }
    if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
        const Point2<Real> p = segment.start + seg_dir * t2;
        inters.insert(p);
    }
    return inters;
}

template <typename Real>
/**
 * Determine if tangent to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Circle2<Real>::tangent(const Line2<Real>& line) const
{
    const Vector2<Real> dir = line.origin - center;
    const Real b = static_cast<Real>(2) * dir.dot(line.direction);
    const Real c = dir.dot(dir) - sqrd(radius);
    const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
    return approx_zero(discriminant);
}

template <typename Real>
/**
 * Determine if tangent to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Circle2<Real>::tangent(const Ray2<Real>& ray) const
{
    const Vector2<Real> dir = ray.origin - center;
    const Real twice_dot = static_cast<Real>(2) * dir.dot(ray.direction);
    const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - sqrd(radius);
    if (const Real discriminant = sqrd(twice_dot) - static_cast<Real>(4) * dist_sqrd_minus_radius_sqrd;
        !approx_zero(discriminant)) {
        return false;
    }
    const Real t = -twice_dot / static_cast<Real>(2);
    return t >= static_cast<Real>(0);
}

template <typename Real>
/**
 * Determine if tangent to a segment.
 * @param segment Segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Circle2<Real>::tangent(const Segment2<Real>& segment) const
{
    const Vector2<Real> dir = segment.start - center;
    const Vector2<Real> segment_dir = segment.end - segment.start;
    const Real twice_dot = static_cast<Real>(2) * dir.dot(segment_dir);
    const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - sqrd(radius);
    const Real len_sqrd = segment.length_sqrd();
    if (const Real discriminant = sqrd(twice_dot) - static_cast<Real>(4) * len_sqrd * dist_sqrd_minus_radius_sqrd;
        !approx_zero(discriminant)) {
        return false;
    }
    const Real t = -twice_dot / (static_cast<Real>(2) * len_sqrd);
    return t >= static_cast<Real>(0) && t <= static_cast<Real>(1);
}

template <typename Real>
Real Circle2<Real>::distance(const Triangle2<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Circle2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Circle2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Circle2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Circle2<Real>::intersect_depth(const Triangle2<Real>& triangle) const
{
    const std::optional<Vector2<Real>> result = triangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
bool Circle2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Circle2<Real>::intersect_depth(const Rectangle2<Real>& rectangle) const
{
    const std::optional<Vector2<Real>> result = rectangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
bool Circle2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Circle2<Real>::intersect_depth(const AlignedRectangle2<Real>& rectangle) const
{
    const std::optional<Vector2<Real>> result = rectangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
/**
 * Closest distance to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Triangle2<Real>::distance(const Line2<Real>& line) const
{
    if (intersects(line)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (int i = 0; i < 3; ++i) {
        const Real dist = edge(i).distance(line);
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Triangle2<Real>::distance(const Ray2<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (int i = 0; i < 3; ++i) {
        const Real dist = edge(i).distance(ray);
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line segment. Zero if segment is inside triangle.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Triangle2<Real>::distance(const Segment2<Real>& segment) const
{
    if (intersects(segment)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (int i = 0; i < 3; ++i) {
        const Real dist = edge(i).distance(segment);
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a circle. Zero if circle is inside triangle.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Triangle2<Real>::distance(const Circle2<Real>& circle) const
{
    if (intersects(circle)) {
        return static_cast<Real>(0);
    }
    Real min_dist = std::numeric_limits<Real>::max();
    for (int i = 0; i < 3; ++i) {
        const Real dist = edge(i).distance(circle);
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle2<Real>::intersects(const Line2<Real>& line) const
{
    for (int i = 0; i < 3; ++i) {
        if (edge(i).intersects(line)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersection points with a line. If only single intersection, both returned points are equal.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Triangle2<Real>::edge_intersections(const Line2<Real>& line) const
{
    PointSet<Point2<Real>, 2> points;
    for (int i = 0; i < 3; ++i) {
        if (std::optional<Point2<Real>> point = edge(i).intersection(line)) {
            points.insert(*point);
        }
    }
    return points;
}

template <typename Real>
/**
 * Determine if intersects with a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle2<Real>::intersects(const Ray2<Real>& ray) const
{
    if (contains(ray.origin)) {
        return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (edge(i).intersects(ray)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersection points with a ray. If only single intersection, both returned points are equal.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Triangle2<Real>::edge_intersections(const Ray2<Real>& ray) const
{
    PointSet<Point2<Real>, 2> points;
    for (int i = 0; i < 3; ++i) {
        if (std::optional<Point2<Real>> point = edge(i).intersection(ray)) {
            points.insert(*point);
        }
    }
    return points;
}

template <typename Real>
/**
 * Determine if intersects a line segment. Being inside the triangle is considered an intersection.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Triangle2<Real>::intersects(const Segment2<Real>& segment) const
{
    if (contains(segment.start) || contains(segment.end)) {
        return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (edge(i).intersects(segment)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersection points with a line segment. If only single intersection, both returned points are equal.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Triangle2<Real>::edge_intersections(const Segment2<Real>& segment) const
{
    PointSet<Point2<Real>, 2> points;
    for (int i = 0; i < 3; ++i) {
        if (std::optional<Point2<Real>> point = edge(i).intersection(segment)) {
            points.insert(*point);
        }
    }
    return points;
}

template <typename Real>
/**
 * Determine if intersects circle. Being inside the triangle is an intersection.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] bool Triangle2<Real>::intersects(const Circle2<Real>& circle) const
{
    if (contains(circle.center)) {
        return true;
    }
    for (int i = 0; i < 3; ++i) {
        if (edge(i).intersects(circle)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersect depth with a circle.
 * @param circle Circle.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] std::optional<Vector2<Real>> Triangle2<Real>::intersect_depth(const Circle2<Real>& circle) const
{
    const auto depth_on_normal
        = [this, &circle](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
        Real tri_max = std::numeric_limits<Real>::lowest();
        for (const Point2<Real>& v : vertices) {
            const Real proj = v.to_vector().dot(normal);
            tri_max = max(tri_max, proj);
        }
        const Real circle_proj = circle.center.to_vector().dot(normal) - circle.radius;
        const Real overlap = tri_max - circle_proj;
        if (overlap < static_cast<Real>(0)) {
            return false;
        }
        if (overlap < min_overlap) {
            min_overlap = overlap;
            min_normal = normal;
        }
        return true;
    };
    std::optional<Vector2<Real>> circle_normal;
    if (!contains(circle.center)) {
        Point2<Real> closest;
        Real closest_dist_sqrd = std::numeric_limits<Real>::max();
        for (int i = 0; i < 3; ++i) {
            const Point2<Real> proj = edge(i).project(circle.center);
            const Real dist_sqrd = circle.center.distance_sqrd(proj);
            if (dist_sqrd < closest_dist_sqrd) {
                closest_dist_sqrd = dist_sqrd;
                closest = proj;
            }
        }
        circle_normal = closest.direction(circle.center);
    }
    const std::array<Vector2<Real>, 3> normals = {
        normal(0),
        normal(1),
        normal(2),
    };
    Real min_overlap = std::numeric_limits<Real>::max();
    Vector2<Real> min_normal;
    if (circle_normal.has_value()) {
        if (!depth_on_normal(*circle_normal, min_overlap, min_normal)) {
            return std::nullopt;
        }
    }
    for (const Vector2<Real>& normal : normals) {
        if (!depth_on_normal(normal, min_overlap, min_normal)) {
            return std::nullopt;
        }
    }
    return min_normal * min_overlap;
}

template <typename Real>
/**
 * Closest distance to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Line2<Real>& line) const
{
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(line);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Ray2<Real>& ray) const
{
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(ray);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line segment. Zero if line segment is inside the rectangle.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Segment2<Real>& segment) const
{
    if (contains(segment.start)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(segment);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a circle. Zero if circle is inside the rectangle.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Circle2<Real>& circle) const
{
    if (intersects(circle)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(circle);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a triangle. Zero if triangle is inside the rectangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Triangle2<Real>& triangle) const
{
    if (contains(triangle.vertices[0])) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = triangle.distance(edge);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to another rectangle. Zero if other rectangle is inside of this rectangle.
 * @param other Other rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real Rectangle2<Real>::distance(const Rectangle2<Real>& other) const
{
    if (contains(other.vertex_nx_ny())) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    const std::array<Segment2<Real>, 4> edges_other {
        other.edge_nx(), other.edge_ny(), other.edge_px(), other.edge_py()
    };
    Real min_dist = std::numeric_limits<Real>::max();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            const Real dist = edges[i].distance(edges_other[j]);
            if (dist == static_cast<Real>(0)) {
                return static_cast<Real>(0);
            }
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Line2<Real>& line) const
{
    return edge_nx().intersects(line) || edge_ny().intersects(line) || edge_px().intersects(line)
        || edge_py().intersects(line);
}

template <typename Real>
/**
 * Intersection points with a line. If only single intersection, both returned points are equal.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Rectangle2<Real>::edge_intersections(const Line2<Real>& line) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Ray2<Real>& ray) const
{
    return edge_nx().intersects(ray) || edge_ny().intersects(ray) || edge_px().intersects(ray)
        || edge_py().intersects(ray);
}

template <typename Real>
/**
 * Intersection points with a ray. If only single intersection, both returned points are equal.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Rectangle2<Real>::edge_intersections(const Ray2<Real>& ray) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a line segment. Being inside the rectangle is an intersection.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Segment2<Real>& segment) const
{
    return contains(segment.start) || contains(segment.end) || edge_nx().intersects(segment)
        || edge_ny().intersects(segment) || edge_px().intersects(segment) || edge_py().intersects(segment);
}

template <typename Real>
/**
 * Intersection points with a line segment. If only single intersection, both returned points are equal.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] PointSet<Point2<Real>, 2> Rectangle2<Real>::edge_intersections(const Segment2<Real>& segment) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(segment); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a circle.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Circle2<Real>& circle) const
{
    if (contains(circle.center)) {
        return true;
    }
    const Vector2<Real> half_size = size / static_cast<Real>(2);
    const Circle2<Real> circle_local = circle.translate(-center.to_vector()).rotate(-angle);
    const Point2<Real> closest
        = circle_local.center.clamp({ -half_size.x, -half_size.y }, { half_size.x, half_size.y });
    const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
    return dist_sqrd <= sqrd(circle.radius);
}

template <typename Real>
/**
 * Intersect depth with a circle.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] std::optional<Vector2<Real>> Rectangle2<Real>::intersect_depth(const Circle2<Real>& circle) const
{
    const Circle2<Real> circle_local = circle.translate(-center.to_vector()).rotate(-angle);
    const Vector2<Real> half_size = size / static_cast<Real>(2);
    const Point2<Real> closest
        = circle_local.center.clamp({ -half_size.x, -half_size.y }, { half_size.x, half_size.y });
    const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
    if (dist_sqrd > sqrd(circle.radius)) {
        return std::nullopt;
    }
    const Point2<Real> min_pos = Point2<Real> { -half_size.x, -half_size.y } - Vector2<Real>::all(circle.radius);
    const Point2<Real> max_pos = Point2<Real> { half_size.x, half_size.y } + Vector2<Real>::all(circle.radius);
    const Vector2<Real> diff_min = min_pos - circle_local.center;
    const Vector2<Real> diff_max = max_pos - circle_local.center;
    const Real diff_x = abs(diff_min.x) <= abs(diff_max.x) ? diff_min.x : diff_max.x;
    const Real diff_y = abs(diff_min.y) <= abs(diff_max.y) ? diff_min.y : diff_max.y;
    return abs(diff_x) <= abs(diff_y)
        ? Vector2<Real> { diff_x, static_cast<Real>(0) }.rotate(angle)
        : Vector2<Real> { static_cast<Real>(0), diff_y }.rotate(angle);
}

template <typename Real>
/**
 * Determine if intersects a triangle. Being inside the rectangle is an intersection.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    for (int i = 0; i < 3; ++i) {
        if (contains(triangle.vertices[i])) {
            return true;
        }
    }
    const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (edge.intersects(triangle)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersect depth with a triangle.
 * @param triangle Triangle.
 * @return Result.
 */
[[nodiscard]] std::optional<Vector2<Real>> Rectangle2<Real>::intersect_depth(const Triangle2<Real>& triangle) const
{
    const auto depth_on_normal
        = [](const std::array<Point2<Real>, 4>& rect_verts,
             const std::array<Point2<Real>, 3>& tri_verts,
             const Vector2<Real>& normal,
             float& min_overlap,
             Vector2<Real>& min_normal) -> bool {
        Real rect_max = std::numeric_limits<Real>::lowest();
        Real tri_min = std::numeric_limits<Real>::max();
        for (const Point2<Real>& v : rect_verts) {
            const Real proj = v.to_vector().dot(normal);
            rect_max = max(rect_max, proj);
        }
        for (const Point2<Real>& v : tri_verts) {
            const Real proj = v.to_vector().dot(normal);
            tri_min = min(tri_min, proj);
        }
        const Real overlap = rect_max - tri_min;
        if (overlap < static_cast<Real>(0)) {
            return false;
        }
        if (overlap < min_overlap) {
            min_overlap = overlap;
            min_normal = normal;
        }
        return true;
    };
    const std::array<Vector2<Real>, 7> normals = {
        normal_nx(),         normal_ny(),         normal_px(),         normal_py(),
        -triangle.normal(0), -triangle.normal(1), -triangle.normal(2),
    };
    const std::array<Point2<Real>, 4> rect_verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
    const std::array<Point2<Real>, 3> tri_verts = { triangle.vertices[0], triangle.vertices[1], triangle.vertices[2] };
    Real min_overlap = std::numeric_limits<Real>::max();
    Vector2<Real> min_normal;
    for (const Vector2<Real>& axis : normals) {
        if (!depth_on_normal(rect_verts, tri_verts, axis, min_overlap, min_normal)) {
            return std::nullopt;
        }
    }
    return min_normal * min_overlap;
}

template <typename Real>
/**
 * Determine if intersects another rectangle. Being inside this rectangle is an intersection.
 * @param other Other rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] bool Rectangle2<Real>::intersects(const Rectangle2<Real>& other) const
{
    const std::array<Point2<Real>, 4> vertices_other
        = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
    for (const Point2<Real>& vertex : vertices_other) {
        if (contains(vertex)) {
            return true;
        }
    }
    const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (other.intersects(edge)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Closest distance to a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Line2<Real>& line) const
{
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(line);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Ray2<Real>& ray) const
{
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(ray);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a line segment. Zero if the line segment is inside the rectangle.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Segment2<Real>& segment) const
{
    if (contains(segment.start)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(segment);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a circle. Zero if the circle is inside the rectangle.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Circle2<Real>& circle) const
{
    if (intersects(circle)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(circle);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a triangle. Zero if the triangle is inside the rectangle.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Triangle2<Real>& triangle) const
{
    if (contains(triangle.vertices[0])) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = triangle.distance(edge);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to a non-aligned rectangle. Zero if the non-aligned rectangle is inside this rectangle.
 * @param rectangle Non-aligned rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    if (intersects(rectangle)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = edge.distance(rectangle);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Closest distance to another aligned rectangle. Zero if other rectangle is inside this rectangle.
 * @param other Other aligned rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] Real AlignedRectangle2<Real>::distance(const AlignedRectangle2<Real>& other) const
{
    if (intersects(other)) {
        return static_cast<Real>(0);
    }
    const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    Real min_dist = std::numeric_limits<Real>::max();
    for (const Segment2<Real>& edge : edges) {
        const Real dist = other.distance(edge);
        if (dist == static_cast<Real>(0)) {
            return static_cast<Real>(0);
        }
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

template <typename Real>
/**
 * Determine if intersects a line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const Line2<Real>& line) const
{
    return edge_nx().intersects(line) || edge_ny().intersects(line) || edge_px().intersects(line)
        || edge_py().intersects(line);
}

template <typename Real>
/**
 * Intersection points with a line. If only single intersection, both returned points are equal.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point2<Real>, 2> AlignedRectangle2<Real>::edge_intersections(
    const Line2<Real>& line) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const Ray2<Real>& ray) const
{
    return edge_nx().intersects(ray) || edge_ny().intersects(ray) || edge_px().intersects(ray)
        || edge_py().intersects(ray);
}

template <typename Real>
/**
 * Intersection points with a ray. If only single intersection, both returned points are equal.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point2<Real>, 2> AlignedRectangle2<Real>::edge_intersections(
    const Ray2<Real>& ray) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a line segment. Being inside the rectangle is an intersection.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const Segment2<Real>& segment) const
{
    return contains(segment.start) || contains(segment.end) || edge_nx().intersects(segment)
        || edge_ny().intersects(segment) || edge_px().intersects(segment) || edge_py().intersects(segment);
}

template <typename Real>
/**
 * Intersection points with a line segment. If only single intersection, both returned points are equal.
 * @param segment Line segment.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr PointSet<Point2<Real>, 2> AlignedRectangle2<Real>::edge_intersections(
    const Segment2<Real>& segment) const
{
    PointSet<Point2<Real>, 2> inters;
    const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (const std::optional<Point2<Real>> intersection = edge.intersection(segment); intersection.has_value()) {
            inters.insert(*intersection);
        }
    }
    return inters;
}

template <typename Real>
/**
 * Determine if intersects a circle. Being inside the rectangle is an intersection.
 * @param circle Circle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const Circle2<Real>& circle) const
{
    if (contains(circle.center)) {
        return true;
    }
    const Point2<Real> closest = circle.center.clamp(min, max);
    const Real dist_sqrd = closest.distance_sqrd(circle.center);
    return dist_sqrd <= sqrd(circle.radius);
}

template <typename Real>
/**
 * Intersect depth with a circle.
 * @param circle Circle.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] constexpr std::optional<Vector2<Real>> AlignedRectangle2<Real>::intersect_depth(
    const Circle2<Real>& circle) const
{
    const Point2<Real> closest = circle.center.clamp(min, max);
    const Real dist_sqrd = circle.center.distance_sqrd(closest);
    if (dist_sqrd > sqrd(circle.radius)) {
        return std::nullopt;
    }
    const Point2<Real> min_pos = min - Vector2<Real>::all(circle.radius);
    const Point2<Real> max_pos = max + Vector2<Real>::all(circle.radius);
    const Vector2<Real> diff_min = min_pos - circle.center;
    const Vector2<Real> diff_max = max_pos - circle.center;
    const Real diff_x = abs(diff_min.x) <= abs(diff_max.x) ? diff_min.x : diff_max.x;
    const Real diff_y = abs(diff_min.y) <= abs(diff_max.y) ? diff_min.y : diff_max.y;
    return abs(diff_x) <= abs(diff_y)
        ? Vector2<Real> { diff_x, static_cast<Real>(0) }
        : Vector2<Real> { static_cast<Real>(0), diff_y };
}

template <typename Real>
/**
 * Determine if intersects a triangle. Being in the rectangle is an intersection.
 * @param triangle Triangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    for (int i = 0; i < 3; ++i) {
        if (contains(triangle.vertices[i])) {
            return true;
        }
    }
    const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (edge.intersects(triangle)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersect depth with a triangle.
 * @param triangle Triangle.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] std::optional<Vector2<Real>> AlignedRectangle2<Real>::intersect_depth(
    const Triangle2<Real>& triangle) const
{
    const auto depth_on_normal
        = [](const std::array<Point2<Real>, 4>& rect_verts,
             const std::array<Point2<Real>, 3>& tri_verts,
             const Vector2<Real>& normal,
             float& min_overlap,
             Vector2<Real>& min_normal) -> bool {
        Real rect_max = std::numeric_limits<Real>::lowest();
        Real tri_min = std::numeric_limits<Real>::max();
        for (const Point2<Real>& v : rect_verts) {
            const Real proj = v.to_vector().dot(normal);
            rect_max = nnm::max(rect_max, proj);
        }
        for (const Point2<Real>& v : tri_verts) {
            const Real proj = v.to_vector().dot(normal);
            tri_min = nnm::min(tri_min, proj);
        }
        const Real overlap = rect_max - tri_min;
        if (overlap < static_cast<Real>(0)) {
            return false;
        }
        if (overlap < min_overlap) {
            min_overlap = overlap;
            min_normal = normal;
        }
        return true;
    };
    const std::array<Vector2<Real>, 7> normals = {
        normal_nx(),         normal_ny(),         normal_px(),         normal_py(),
        -triangle.normal(0), -triangle.normal(1), -triangle.normal(2),
    };
    const std::array<Point2<Real>, 4> rect_verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
    const std::array<Point2<Real>, 3> tri_verts = { triangle.vertices[0], triangle.vertices[1], triangle.vertices[2] };
    Real min_overlap = std::numeric_limits<Real>::max();
    Vector2<Real> min_normal;
    for (const Vector2<Real>& axis : normals) {
        if (!depth_on_normal(rect_verts, tri_verts, axis, min_overlap, min_normal)) {
            return std::nullopt;
        }
    }
    return min_normal * min_overlap;
}

template <typename Real>
/**
 * Determine if intersects a non-aligned rectangle. Being inside this rectangle is an intersection.
 * @param rectangle Aligned rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] bool AlignedRectangle2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    const std::array<Point2<Real>, 4> vertices_rect
        = { rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py() };
    for (const Point2<Real>& vertex : vertices_rect) {
        if (contains(vertex)) {
            return true;
        }
    }
    const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (rectangle.intersects(edge)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
/**
 * Intersect depth with a non-aligned rectangle.
 * @param rectangle Non-aligned rectangle.
 * @return Result, null if no intersection.
 */
// tested
[[nodiscard]] std::optional<Vector2<Real>> AlignedRectangle2<Real>::intersect_depth(
    const Rectangle2<Real>& rectangle) const
{
    const auto depth_on_normal
        = [](const std::array<Point2<Real>, 4>& verts,
             const std::array<Point2<Real>, 4>& verts_rect,
             const Vector2<Real>& normal,
             float& min_overlap,
             Vector2<Real>& min_normal) -> bool {
        Real this_max = std::numeric_limits<Real>::lowest();
        Real other_min = std::numeric_limits<Real>::max();
        for (const Point2<Real>& v : verts) {
            const Real proj = v.to_vector().dot(normal);
            this_max = nnm::max(this_max, proj);
        }
        for (const Point2<Real>& v : verts_rect) {
            const Real proj = v.to_vector().dot(normal);
            other_min = nnm::min(other_min, proj);
        }
        const Real overlap = this_max - other_min;
        if (overlap < static_cast<Real>(0)) {
            return false;
        }
        if (overlap < min_overlap) {
            min_overlap = overlap;
            min_normal = normal;
        }
        return true;
    };
    const std::array<Vector2<Real>, 8> normals = {
        normal_nx(),
        normal_ny(),
        normal_px(),
        normal_py(),
        -rectangle.normal_nx(),
        -rectangle.normal_ny(),
        -rectangle.normal_px(),
        -rectangle.normal_py(),
    };
    const std::array<Point2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
    const std::array<Point2<Real>, 4> verts_rect
        = { rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py() };
    Real min_overlap = std::numeric_limits<Real>::max();
    Vector2<Real> min_normal;
    for (const Vector2<Real>& axis : normals) {
        if (!depth_on_normal(verts, verts_rect, axis, min_overlap, min_normal)) {
            return std::nullopt;
        }
    }
    return min_normal * min_overlap;
}

template <typename Real>
/**
 * Determine if intersects another aligned rectangle.
 * @param other Other aligned rectangle.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool AlignedRectangle2<Real>::intersects(const AlignedRectangle2<Real>& other) const
{
    const std::array<Point2<Real>, 4> vertices_other
        = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
    for (const Point2<Real>& vertex : vertices_other) {
        if (contains(vertex)) {
            return true;
        }
    }
    const std::array edges = { edge_nx(), edge_ny(), edge_px(), edge_py() };
    for (const Segment2<Real>& edge : edges) {
        if (other.intersects(edge)) {
            return true;
        }
    }
    return false;
}

template <typename Real>
Real Triangle2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Triangle2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Triangle2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Triangle2<Real>::intersect_depth(const Rectangle2<Real>& rectangle) const
{
    const std::optional<Vector2<Real>> result = rectangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
bool Triangle2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Triangle2<Real>::intersect_depth(const AlignedRectangle2<Real>& rectangle) const
{
    const std::optional<Vector2<Real>> result = rectangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

template <typename Real>
Real Rectangle2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Rectangle2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
std::optional<Vector2<Real>> Rectangle2<Real>::intersect_depth(const AlignedRectangle2<Real>& rectangle) const
{
    const std::optional<Vector2<Real>> result = rectangle.intersect_depth(*this);
    if (!result.has_value()) {
        return std::nullopt;
    }
    return -result.value();
}

} // namespace nnm

#endif
