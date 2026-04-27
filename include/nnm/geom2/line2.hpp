/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_LINE2_HPP
#define NNM_GEOM2_LINE2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>
#include <nnm/geom2/ray2.hpp>
#include <nnm/geom2/segment2.hpp>

namespace nnm {

template <typename Real>
class Line2 {
public:

    /**
     * Origin.
     */
    Point2<Real> origin;

    /**
     * Normalized direction.
     */
    Vector2<Real> direction;

    /**
     * Default initialize with zero origin and in the direction of the x-axis.
     */
    // tested
    constexpr Line2()
        : origin { Point2<Real>::zero() }
        , direction { Vector2<Real>::axis_x() }
    {
    }

    /**
     * Initialize with given origin and normalized direction. No normalization is done.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Line2(const Point2<Real>& origin, const Vector2<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    /**
     * Cast from another type. No normalization is done.
     * @tparam Other Other floating-point type.
     * @param other Other line.
     */
    // tested
    template <typename Other>
    explicit constexpr Line2(const Line2<Other>& other)
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
    static Line2 from_points(const Point2<Real>& point1, const Point2<Real>& point2)
    {
        return { point1, point1.direction(point2) };
    }

    /**
     * Extends a 2D segment to an infinite 2D line.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    static Line2 from_segment(const Segment2<Real>& segment)
    {
        return { segment.start, segment.start.direction(segment.end) };
    }

    /**
     * Extends a 2D ray to an infinite 2D line.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    static constexpr Line2 from_ray(const Ray2<Real>& ray)
    {
        return { ray.origin, ray.direction };
    }

    /**
     * Line tangent to circle at angle.
     * @param circle Circle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    static Line2 from_tangent(const Circle2<Real>& circle, const Real angle)
    {
        const Point2<Real> p = circle.point_at(angle);
        const Vector2<Real> dir = p - circle.center;
        return { p, dir.arbitrary_perpendicular() };
    }

    /**
     * Line at zero origin in the direction of the x-axis.
     * @return Result.
     */
    // tested
    static constexpr Line2 axis_x()
    {
        return { Point2<Real>::zero(), Vector2<Real>::axis_x() };
    }

    /**
     * Line at zero origin in the direction of the y-axis.
     * @return Result.
     */
    // tested
    static constexpr Line2 axis_y()
    {
        return { Point2<Real>::zero(), Vector2<Real>::axis_y() };
    }

    /**
     * Line at an offset parallel to the x-axis in the direction of the x-axis.
     * @param y Y offset from x-axis.
     * @return Result.
     */
    // tested
    static constexpr Line2 axis_x_offset(const Real y)
    {
        return { { static_cast<Real>(0), y }, Vector2<Real>::axis_x() };
    }

    /**
     * Line at an offset parallel to the y-axis in the direction of the y-axis.
     * @param x X offset from y-axis.
     * @return Result.
     */
    // tested
    static constexpr Line2 axis_y_offset(const Real x)
    {
        return { { x, static_cast<Real>(0) }, Vector2<Real>::axis_y() };
    }

    /**
     * Line that intersects point with a slope.
     * @param point Point.
     * @param slope Slope.
     * @return Result.
     */
    // tested
    static Line2 from_point_slope(const Point2<Real>& point, const Real slope)
    {
        return { point, nnm::Vector2<Real> { 1.0f, slope }.normalize() };
    }

    /**
     * Line parallel to this line and intersects point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line2 parallel_containing(const Point2<Real>& point) const
    {
        return { point, direction };
    }

    /**
     * Line perpendicular to this line and intersects point. Both direction and -direction are valid solutions.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line2 arbitrary_perpendicular_containing(const Point2<Real>& point) const
    {
        return { point, direction.arbitrary_perpendicular() };
    }

    /**
     * Normalize direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    /**
     * Determine if collinear with 2D ray.
     * @param ray 2D ray.
     * @return True if collinear, false otherwise.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray2<Real>& ray) const;

    /**
     * Determine if collinear with 2D segment.
     * @param segment 2D segment.
     * @return True if collinear, false otherwise.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects point.
     * @param point Point.
     * @return True if contains, false otherwise.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        const Vector2<Real> t = (point - origin) / direction;
        return approx_equal(t.x, t.y);
    }

    /**
     * Closest signed distance to point. Positive if +x from line, negative if -x from line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real signed_distance(const Point2<Real>& point) const
    {
        return direction.cross(point - origin);
    }

    /**
     * Closest distance to point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Point2<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    /**
     * Closest distance to other line. Zero if non-parallel.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Line2& other) const
    {
        if (direction.cross(other.direction) == static_cast<Real>(0)) {
            return abs((other.origin - origin).cross(direction));
        }
        return static_cast<Real>(0);
    }

    /**
     * Closest distance to 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    /**
     * Closest distance to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Segment2<Real>& segment) const;

    /**
     * Closest distance to 2D circle.
     * @param circle 2D circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    /**
     * Closest distance to 2D triangle.
     * @param triangle 2D triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to 2D rectangle.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to 2D aligned-rectangle.
     * @param rectangle 2D aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if parallel to other line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    /**
     * Determine if parallel to 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */// tested

    [[nodiscard]] constexpr bool parallel(const Ray2<Real>& ray) const;

    /**
     * Determine if parallel to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment2<Real>& segment) const;

    /**
     * Determine if perpendicular to other line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if perpendicular to 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray2<Real>& ray) const;

    /**
     * Determine if perpendicular to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment2<Real>& segment) const;

    /**
     * Intersection point of two lines. Does not check if parallel; a divide-by-zero would occur if parallel.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> unchecked_intersection(const Line2& other) const
    {
        const Real denom = direction.cross(other.direction);
        const Vector2<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction) / denom;
        return origin + direction * t;
    }

    /**
     * Intersection point of two lines.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Line2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t = diff.cross(other.direction) / dir_cross;
        return origin + direction * t;
    }

    /**
     * Determine if intersects 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */// tested

    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const;

    /**
     * Intersection point with 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Ray2<Real>& ray) const;

    /**
     * Determine if intersects 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const;

    /**
     * Intersection point with 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects 2D circle.
     * @param circle 2D circle.
     * @return Result/
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersection points with 2D circle. If only single intersection, bot returned points are equal.
     * @param circle 2D circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Circle2<Real>& circle) const;

    /**
     * Determine if intersects 2D triangle.
     * @param triangle 2D triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersection points with 2D triangle. If only single intersection, both returned points are equal.
     * @param triangle 2D triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects 2D rectangle.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersections points with 2D rectangle. If only single intersection, both returned points are equal.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to 2D circle.
     * @param circle 2D circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Circle2<Real>& circle) const;

    /**
     * Projection of point on the line.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> project(const Point2<Real>& point) const
    {
        const Real t = (point - origin).dot(direction);
        return origin + direction * t;
    }

    /**
     * Slope without checking if line is vertical. Will result in divide-by-zero otherwise.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real unchecked_slope() const
    {
        return direction.y / direction.x;
    }

    /**
     * Slope of line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Real> slope() const
    {
        if (direction.x == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return unchecked_slope();
    }

    /**
     * Determine if coincident with other line.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Line2& other) const
    {
        if (!parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = origin - other.origin;
        return approx_zero(diff.cross(other.direction));
    }

    /**
     * Translate by an offset.
     * @param by Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line2 translate(const Vector2<Real>& by) const
    {
        return { origin.translate(by), direction };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Origin.
     * @param by Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 scale_at(const Point2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    /**
     * Scale about the global origin by a factor.
     * @param by Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 scale(const Vector2<Real>& by) const
    {
        return { origin.scale(by), direction.scale(by).normalize() };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 rotate_at(const Point2<Real>& rotate_origin, const Real angle) const
    {
        return { origin.rotate_at(rotate_origin, angle), direction.rotate(angle).normalize() };
    }

    /**
     * Rotate about the global origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 rotate(const Real angle) const
    {
        return { origin.rotate(angle), direction.rotate(angle).normalize() };
    }

    /**
     * Shear along the x-axis about an origin.
     * @param shear_origin Origin.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 shear_x_at(const Point2<Real>& shear_origin, const Real factor_y) const
    {
        return { origin.shear_x_at(shear_origin, factor_y), direction.shear_x(factor_y).normalize() };
    }

    /**
     * Shear along the x-axis about the global origin.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 shear_x(const Real factor_y) const
    {
        return { origin.shear_x(factor_y), direction.shear_x(factor_y).normalize() };
    }

    /**
     * Shear along the y-axis about an origin.
     * @param shear_origin Origin.
     * @param factor_x X-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 shear_y_at(const Point2<Real>& shear_origin, const Real factor_x) const
    {
        return { origin.shear_y_at(shear_origin, factor_x), direction.shear_y(factor_x).normalize() };
    }

    /**
     * Shear along the y-axis about the global origin.
     * @param factor_x X-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2 shear_y(const Real factor_x) const
    {
        return { origin.shear_y(factor_x), direction.shear_y(factor_x).normalize() };
    }

    /**
     * Determine if origin and direction are equal.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Line2& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine of origin or direction are not equal.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Line2& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical compare in the order of origin then direction.
     * @param other Other line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Line2& other) const
    {
        if (origin != other.origin) {
            return origin < other.origin;
        }
        return direction < other.direction;
    }
};

} // namespace nnm

#endif
