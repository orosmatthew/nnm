/* NNM - No Nonsense Math
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_INTERACTIONS_LINEAR_HPP
#define NNM_GEOM2_INTERACTIONS_LINEAR_HPP

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
 * Line tangent to circle at angle.
 * @param circle Circle.
 * @param angle Angle in radians.
 * @return Result.
 */
// tested
Line2<Real> Line2<Real>::from_tangent(const Circle2<Real>& circle, const Real angle)
{
    const Point2<Real> p = circle.point_at(angle);
    const Vector2<Real> dir = p - circle.center;
    return { p, dir.arbitrary_perpendicular() };
}

template <typename Real>
/**
 * Determine if collinear with a point.
 * @param point Point.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::collinear(const Point2<Real>& point) const
{
    return Line2<Real>::from_ray(*this).contains(point);
}

template <typename Real>
/**
 * Determine if collinear with 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::collinear(const Line2<Real>& line) const
{
    return Line2<Real>::from_ray(*this).coincident(line);
}

template <typename Real>
/**
 * Determine if collinear with another ray.
 * @param other Other ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::collinear(const Ray2<Real>& other) const
{
    return Line2<Real>::from_ray(*this).coincident(Line2<Real>::from_ray(other));
}

template <typename Real>
/**
 * Closest distance to 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] Real Ray2<Real>::distance(const Line2<Real>& line) const
{
    if (intersects(line)) {
        return static_cast<Real>(0);
    }
    return line.distance(origin);
}

template <typename Real>
/**
 * Determine if parallel to 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::parallel(const Line2<Real>& line) const
{
    return approx_zero(direction.cross(line.direction));
}

template <typename Real>
/**
 * Determine if perpendicular to 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::perpendicular(const Line2<Real>& line) const
{
    return approx_zero(direction.dot(line.direction));
}

template <typename Real>
/**
 * Determine if intersects 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Ray2<Real>::intersects(const Line2<Real>& line) const
{
    const Real dir_cross = direction.cross(line.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return false;
    }
    const Vector2<Real> diff = line.origin - origin;
    const Real t_ray = diff.cross(line.direction) / dir_cross;
    return t_ray >= static_cast<Real>(0);
}

template <typename Real>
/**
 * Intersection point with 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point2<Real>> Ray2<Real>::intersection(const Line2<Real>& line) const
{
    const Real dir_cross = direction.cross(line.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return std::nullopt;
    }
    const Vector2<Real> diff = line.origin - origin;
    const Real t_ray = diff.cross(line.direction) / dir_cross;
    if (t_ray >= static_cast<Real>(0)) {
        return origin + direction * t_ray;
    }
    return std::nullopt;
}

template <typename Real>
/**
 * Determine if collinear with 2D line.
 * @param line 2D line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::collinear(const Line2<Real>& line) const
{
    if (!parallel(line)) {
        return false;
    }
    const Vector2<Real> diff = start - line.origin;
    return approx_zero(diff.cross(line.direction));
}

template <typename Real>
/**
 * Determine if collinear with 2D ray.
 * @param ray 2D ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::collinear(const Ray2<Real>& ray) const
{
    if (!parallel(ray)) {
        return false;
    }
    const Vector2<Real> diff = start - ray.origin;
    return approx_zero(diff.cross(ray.direction));
}

template <typename Real>
/**
 * Closest distance to line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr Real Segment2<Real>::distance(const Line2<Real>& line) const
{
    if (intersects(line)) {
        return static_cast<Real>(0);
    }
    const Real d1 = line.distance(start);
    const Real d2 = line.distance(end);
    return min(d1, d2);
}

template <typename Real>
/**
 * Closest distance to ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] Real Segment2<Real>::distance(const Ray2<Real>& ray) const
{
    if (intersects(ray)) {
        return static_cast<Real>(0);
    }
    const Real d1 = ray.distance(start);
    const Real d2 = ray.distance(end);
    const Real d3 = distance(ray.origin);
    return min(d1, min(d2, d3));
}

template <typename Real>
/**
 * Determine if parallel with line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::parallel(const Line2<Real>& line) const
{
    return approx_zero((end - start).cross(line.direction));
}

template <typename Real>
/**
 * Determine if parallel with ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::parallel(const Ray2<Real>& ray) const
{
    return approx_zero((end - start).cross(ray.direction));
}

template <typename Real>
/**
 * Determine if perpendicular with line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::perpendicular(const Line2<Real>& line) const
{
    return approx_zero((end - start).dot(line.direction));
}

template <typename Real>
/**
 * Determine if perpendicular with ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::perpendicular(const Ray2<Real>& ray) const
{
    return approx_zero((end - start).dot(ray.direction));
}

template <typename Real>
/**
 * Determine if intersects line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::intersects(const Line2<Real>& line) const
{
    const Vector2<Real> dir = end - start;
    const Real dir_cross = dir.cross(line.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return false;
    }
    const Vector2<Real> diff = line.origin - start;
    const Real t = diff.cross(line.direction) / dir_cross;
    return t >= static_cast<Real>(0) && t <= static_cast<Real>(1);
}

template <typename Real>
/**
 * Intersection point with line.
 * @param line Line.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point2<Real>> Segment2<Real>::intersection(const Line2<Real>& line) const
{
    const Vector2<Real> dir = end - start;
    const Real dir_cross = dir.cross(line.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return std::nullopt;
    }
    const Vector2<Real> diff = line.origin - start;
    const Real t = diff.cross(line.direction) / dir_cross;
    if (t < static_cast<Real>(0) || t > static_cast<Real>(1)) {
        return std::nullopt;
    }
    return start + dir * t;
}

template <typename Real>
/**
 * Determine if intersects ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr bool Segment2<Real>::intersects(const Ray2<Real>& ray) const
{
    const Vector2<Real> dir = end - start;
    const Real dir_cross = dir.cross(ray.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return false;
    }
    const Vector2<Real> diff = ray.origin - start;
    const Real t = diff.cross(ray.direction) / dir_cross;
    const Real t_ray = diff.cross(dir) / dir_cross;
    return t >= static_cast<Real>(0) && t <= static_cast<Real>(1) && t_ray >= static_cast<Real>(0);
}

template <typename Real>
/**
 * Intersection point with ray.
 * @param ray Ray.
 * @return Result.
 */
// tested
[[nodiscard]] constexpr std::optional<Point2<Real>> Segment2<Real>::intersection(const Ray2<Real>& ray) const
{
    const Vector2<Real> dir = end - start;
    const Real dir_cross = dir.cross(ray.direction);
    if (dir_cross == static_cast<Real>(0)) {
        return std::nullopt;
    }
    const Vector2<Real> diff = ray.origin - start;
    const Real t = diff.cross(ray.direction) / dir_cross;
    const Real t_ray = diff.cross(dir) / dir_cross;
    if (t < static_cast<Real>(0) || t > static_cast<Real>(1) || t_ray < static_cast<Real>(0)) {
        return std::nullopt;
    }
    return start + dir * t;
}

template <typename Real>
constexpr bool Line2<Real>::parallel(const Ray2<Real>& ray) const
{
    return ray.parallel(*this);
}

template <typename Real>
constexpr bool Line2<Real>::parallel(const Segment2<Real>& segment) const
{
    return segment.parallel(*this);
}

template <typename Real>
constexpr bool Line2<Real>::perpendicular(const Ray2<Real>& ray) const
{
    return ray.perpendicular(*this);
}

template <typename Real>
constexpr bool Line2<Real>::perpendicular(const Segment2<Real>& segment) const
{
    return segment.perpendicular(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Ray2<Real>& ray) const
{
    return ray.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point2<Real>> Line2<Real>::intersection(const Ray2<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point2<Real>> Line2<Real>::intersection(const Segment2<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
Line2<Real> Line2<Real>::from_segment(const Segment2<Real>& segment)
{
    return { segment.start, (segment.end - segment.start).normalize() };
}

template <typename Real>
constexpr bool Line2<Real>::collinear(const Ray2<Real>& ray) const
{
    return ray.collinear(*this);
}

template <typename Real>
constexpr bool Line2<Real>::collinear(const Segment2<Real>& segment) const
{
    return segment.collinear(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Ray2<Real>& ray) const
{
    return ray.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Triangle2<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Line2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
constexpr Real Line2<Real>::distance(const Segment2<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Line2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Line2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Line2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Line2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr Line2<Real> Line2<Real>::from_ray(const Ray2<Real>& ray)
{
    return { ray.origin, ray.direction };
}

template <typename Real>
constexpr bool Line2<Real>::tangent(const Circle2<Real>& circle) const
{
    return circle.tangent(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::parallel(const Segment2<Real>& segment) const
{
    return segment.parallel(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::perpendicular(const Segment2<Real>& segment) const
{
    return segment.perpendicular(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Point2<Real>> Ray2<Real>::intersection(const Segment2<Real>& segment) const
{
    return segment.intersection(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::tangent(const Circle2<Real>& circle) const
{
    return circle.tangent(*this);
}

template <typename Real>
constexpr bool Ray2<Real>::collinear(const Segment2<Real>& segment) const
{
    return segment.collinear(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Segment2<Real>& segment) const
{
    return segment.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Triangle2<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Ray2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Ray2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Ray2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Ray2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Ray2<Real>::edge_intersections(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Triangle2<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Segment2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Segment2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Segment2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
PointSet<Point2<Real>, 2> Segment2<Real>::edge_intersections(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
constexpr bool Segment2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
constexpr bool Segment2<Real>::tangent(const Circle2<Real>& circle) const
{
    return circle.tangent(*this);
}

} // namespace nnm

#endif
