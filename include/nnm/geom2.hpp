/* NNM - "No Nonsense Math"
 * v0.3.1
 * Copyright (c) 2024-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_HPP
#define NNM_GEOM2_HPP

// ReSharper disable CppDFATimeOver

#include <nnm/nnm.hpp>

#include <array>
#include <optional>

namespace nnm {

template <typename Real>
class Intersections2;
using Intersections2f = Intersections2<float>;
using Intersections2d = Intersections2<double>;
template <typename Real>
class Line2;
using Line2f = Line2<float>;
using Line2d = Line2<double>;
template <typename Real>
class Ray2;
using Ray2f = Ray2<float>;
using Ray2d = Ray2<double>;
template <typename Real>
class Segment2;
using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;
template <typename Real>
class Circle2;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;
template <typename Real>
class Triangle2;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;
template <typename Real>
class Rectangle2;
using Rectangle2f = Rectangle2<float>;
using Rectangle2d = Rectangle2<double>;
template <typename Real>
class AlignedRectangle2;
using AlignedRectangle2f = AlignedRectangle2<float>;
using AlignedRectangle2d = AlignedRectangle2<double>;

/**
 * Fixed capacity, stack allocated set of Point2 points.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Intersections2 {
public:
    /**
     * Default initialize to zero intersections.
     */
    // tested
    constexpr Intersections2()
        : m_points { Point2<Real>::zero(), Point2<Real>::zero() }
        , m_size { 0 }
    {
    }

    /**
     * Initialize with single intersection point.
     * @param point Intersection point.
     */
    // ReSharper disable once CppNonExplicitConvertingConstructor
    // tested
    constexpr Intersections2(const Point2<Real>& point) // NOLINT(*-explicit-constructor)
        : m_points { point, Point2<Real>::zero() }
        , m_size { 1 }
    {
    }

    /**
     * Initialize with two intersection points.
     * @param point1 First intersection.
     * @param point2 Second intersection.
     */
    // tested
    constexpr Intersections2(const Point2<Real>& point1, const Point2<Real>& point2)
        : m_points { point1, point2 }
        , m_size { 2 }
    {
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
    constexpr void insert(const Point2<Real>& point)
    {
        if (contains(point)) {
            return;
        }
        NNM_BOUNDS_CHECK_ASSERT("Intersections2", size < 2);
        m_points[m_size++] = point;
    }

    /**
     * Clear intersections.
     */
    // tested
    constexpr void clear()
    {
        m_points[0] = Point2<Real>::zero();
        m_points[1] = Point2<Real>::zero();
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
    constexpr Point2<Real>* begin()
    {
        return &m_points[0];
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    // tested
    constexpr Point2<Real>* end()
    {
        return &m_points[m_size + 1];
    }

    /**
     * Start const iterator.
     * @return Iterator.
     */
    // tested
    constexpr const Point2<Real>* begin() const
    {
        return &m_points[0];
    }

    /**
     * End const iterator.
     * @return Iterator.
     */
    // tested
    constexpr const Point2<Real>* end() const
    {
        return &m_points[m_size + 1];
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr const Point2<Real>* data() const
    {
        return m_points;
    }

    /**
     * Data pointer.
     * @return Result.
     */
    constexpr Point2<Real>* data()
    {
        return m_points;
    }

    /**
     * Unordered approximate equality.
     * @param other Other intersections.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Intersections2& other) const
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
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
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
    [[nodiscard]] constexpr bool operator==(const Intersections2& other) const
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
    [[nodiscard]] constexpr bool operator!=(const Intersections2& other) const
    {
        return !(*this == other);
    }

private:
    Point2<Real> m_points[2];
    uint8_t m_size;
};

/**
 * Infinite line.
 * @tparam Real Floating-point type.
 */
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
    static Line2 from_segment(const Segment2<Real>& segment);

    /**
     * Extends a 2D ray to an infinite 2D line.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    static constexpr Line2 from_ray(const Ray2<Real>& ray);

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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Circle2<Real>& circle) const;

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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Triangle2<Real>& triangle) const;

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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Rectangle2<Real>& rectangle) const;

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

/**
 * Ray.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Ray2 {
public:
    /**
     * Origin
     */
    Point2<Real> origin;
    /**
     * Normalized direction.
     */
    Vector2<Real> direction;

    /**
     * Initialize with zero origin and in the direction of the x-axis.
     */
    // tested
    constexpr Ray2()
        : origin { Point2<Real>::zero() }
        , direction { Vector2<Real>::axis_x() }
    {
    }

    /**
     * Initialize with origin and direction. No normalization for the direction is done.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Ray2(const Point2<Real>& origin, const Vector2<Real>& direction)
        : origin { origin }
        , direction { direction }
    {
    }

    /**
     * Cast from another type. No normalization is done.
     * @tparam Other Other floating-point type.
     * @param other Other ray.
     */
    // tested
    template <typename Other>
    explicit constexpr Ray2(const Ray2<Other> other)
        : origin { other.origin }
        , direction { other.direction }
    {
    }

    /**
     * Ray with origin in the direction of another point.
     * @param from Origin.
     * @param to To.
     * @return Result.
     */
    // tested
    static Ray2 from_point_to_point(const Point2<Real>& from, const Point2<Real>& to)
    {
        return { from, from.direction(to) };
    }

    /**
     * Normalize the direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray2 normalize() const
    {
        return { origin, direction.normalize() };
    }

    /**
     * Determine if collinear with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Point2<Real>& point) const
    {
        return Line2<Real>::from_ray(*this).contains(point);
    }

    /**
     * Determine if collinear with 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line2<Real>& line) const
    {
        return Line2<Real>::from_ray(*this).coincident(line);
    }

    /**
     * Determine if collinear with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray2& other) const
    {
        return Line2<Real>::from_ray(*this).coincident(Line2<Real>::from_ray(other));
    }

    /**
     * Determine if collinear with 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Segment2<Real>& segment) const;

    /**
     * Determine if contains a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> t = diff / direction;
        return approx_equal(t.x, t.y);
    }

    /**
     * Closest signed-distance to point. Positive if in the direction of the ray, negative otherwise.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real signed_distance(const Point2<Real>& point) const
    {
        const Vector2<Real> diff = point - origin;
        if (diff.dot(direction) < static_cast<Real>(0)) {
            return diff.length();
        }
        return direction.cross(diff);
    }

    /**
     * Closest distance to point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        return abs(signed_distance(point));
    }

    /**
     * Closest distance to 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        return line.distance(origin);
    }

    /**
     * Closest distance to other ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            if (direction.dot(other.direction) > static_cast<Real>(0)) {
                return abs((other.origin - origin).cross(direction));
            }
            return origin.distance(other.origin);
        }
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Real d1 = distance(other.origin);
        const Real d2 = other.distance(origin);
        return min(d1, d2);
    }

    /**
     * Closest distance to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

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
     * Determine if parallel to 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line2<Real>& line) const
    {
        return approx_zero(direction.cross(line.direction));
    }

    /**
     * Determine if parallel to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray2& other) const
    {
        return approx_zero(direction.cross(other.direction));
    }

    /**
     * Determine if parallel to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment2<Real>& segment) const;

    /**
     * Determine if perpendicular to 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line2<Real>& line) const
    {
        return approx_zero(direction.dot(line.direction));
    }

    /**
     * Determine if perpendicular to another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray2& other) const
    {
        return approx_zero(direction.dot(other.direction));
    }

    /**
     * Determine if perpendicular to 2D segment.
     * @param segment 2D segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        const Real dir_cross = direction.cross(line.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = line.origin - origin;
        const Real t_ray = diff.cross(line.direction) / dir_cross;
        return t_ray >= static_cast<Real>(0);
    }

    /**
     * Intersection point with 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Line2<Real>& line) const
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

    /**
     * Determine if intersects with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (approx_zero(dir_cross)) {
            return false;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t1 = diff.cross(other.direction) / dir_cross;
        const Real t2 = diff.cross(direction) / dir_cross;
        return t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0);
    }

    /**
     * Intersection point with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Ray2& other) const
    {
        const Real dir_cross = direction.cross(other.direction);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.origin - origin;
        const Real t1 = diff.cross(other.direction) / dir_cross;
        const Real t2 = diff.cross(direction) / dir_cross;
        if (t1 >= static_cast<Real>(0) && t2 >= static_cast<Real>(0)) {
            return origin + direction * t1;
        }
        return std::nullopt;
    }

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
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersection points with 2D circle. If only single intersection, both returned points are equal.
     * @param circle 2D circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Circle2<Real>& circle) const;

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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects 2D rectangle.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersection points with 2D rectangle. If only single intersection, both returned points are equal.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects 2D aligned-rectangle.
     * @param rectangle 2D aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersection points with 2D aligned-rectangle. If only single intersection, both returned points are equal.
     * @param rectangle 2D aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to 2D circle.
     * @param circle 2D circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Circle2<Real>& circle) const;

    /**
     * Projection of point on the ray.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> project(const Point2<Real>& point) const
    {
        const Real t = max(static_cast<Real>(0), (point - origin).dot(direction));
        return origin + direction * t;
    }

    /**
     * Translate by an offset.
     * @param by Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Ray2 translate(const Vector2<Real>& by) const
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
    [[nodiscard]] Ray2 scale_at(const Point2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { origin.scale_at(scale_origin, by), direction.scale(by).normalize() };
    }

    /**
     * Scale about the origin by a factor.
     * @param by Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray2 scale(const Vector2<Real>& by) const
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
    [[nodiscard]] Ray2 rotate_at(const Point2<Real>& rotate_origin, const Real angle) const
    {
        return { origin.rotate_at(rotate_origin, angle), direction.rotate(angle).normalize() };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray2 rotate(const Real angle) const
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
    [[nodiscard]] Ray2 shear_x_at(const Point2<Real>& shear_origin, const Real factor_y) const
    {
        return { origin.shear_x_at(shear_origin, factor_y), direction.shear_x(factor_y).normalize() };
    }

    /**
     * Shear along the x-axis about the origin.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray2 shear_x(const Real factor_y) const
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
    [[nodiscard]] Ray2 shear_y_at(const Point2<Real>& shear_origin, const Real factor_x) const
    {
        return { origin.shear_y_at(shear_origin, factor_x), direction.shear_y(factor_x).normalize() };
    }

    /**
     * Shear along the y-axis about the origin.
     * @param factor_x X-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] Ray2 shear_y(const Real factor_x) const
    {
        return { origin.shear_y(factor_x), direction.shear_y(factor_x).normalize() };
    }

    /**
     * Determine if origin and direction are equal with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Ray2& other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * Determine if origin or direction are not equal with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Ray2& other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * Lexicographical comparison with another ray in the order of origin then direction.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Ray2& other) const
    {
        if (origin != other.origin) {
            return origin < other.origin;
        }
        return direction < other.direction;
    }
};

/**
 * Line segment.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Segment2 {
public:
    /**
     * Start point.
     */
    Point2<Real> start;
    /**
     * End point.
     */
    Point2<Real> end;

    /**
     * Initialize with both start and end points zero.
     */
    // tested
    constexpr Segment2()
        : start { Point2<Real>::zero() }
        , end { Point2<Real>::zero() }
    {
    }

    /**
     * Initialize with start and end points.
     * @param from Start point.
     * @param to End point.
     */
    // tested
    constexpr Segment2(const Point2<Real>& from, const Point2<Real>& to)
        : start { from }
        , end { to }
    {
    }

    /**
     * Case from another type.
     * @tparam Other Other floating-point type.
     * @param other Other segment.
     */
    // tested
    template <typename Other>
    explicit constexpr Segment2(const Segment2<Other>& other)
        : start { Point2<Other> { other.start } }
        , end { Point2<Other> { other.end } }
    {
    }

    /**
     * Determine if collinear with point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Point2<Real>& point) const
    {
        const Vector2<Real> diff1 = point - start;
        const Vector2<Real> diff2 = end - start;
        return approx_zero(diff1.cross(diff2));
    }

    /**
     * Determine if collinear with 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line2<Real>& line) const
    {
        if (!parallel(line)) {
            return false;
        }
        const Vector2<Real> diff = start - line.origin;
        return approx_zero(diff.cross(line.direction));
    }

    /**
     * Determine if collinear with 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray2<Real>& ray) const
    {
        if (!parallel(ray)) {
            return false;
        }
        const Vector2<Real> diff = start - ray.origin;
        return approx_zero(diff.cross(ray.direction));
    }

    /**
     * Determine if collinear with other segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Segment2& other) const
    {
        if (!parallel(other)) {
            return false;
        }
        const Vector2<Real> diff = start - other.start;
        return approx_zero(diff.cross(other.end - other.start));
    }

    /**
     * Determine if intersects point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        if (start == end) {
            return start.approx_equal(point);
        }
        const Vector2<Real> diff1 = point - start;
        const Vector2<Real> diff2 = end - start;
        if (!approx_zero(diff1.cross(diff2))) {
            return false;
        }
        const Real dot = diff1.dot(diff2);
        const Real length_sqrd = diff2.dot(diff2);
        return dot >= static_cast<Real>(0) && dot <= length_sqrd;
    }

    /**
     * Closest signed-distance to point. Positive if +x above segment, negative otherwise.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const
    {
        const Vector2<Real> dir = end - start;
        const Vector2<Real> diff = point - start;
        Real t = diff.dot(dir) / dir.dot(dir);
        Point2<Real> closest;
        if (t < static_cast<Real>(0)) {
            closest = start;
        }
        else if (t > static_cast<Real>(1)) {
            closest = end;
        }
        else {
            closest = start + dir * t;
        }
        const Real dist = (point - closest).length();
        return sign(dir.cross(point - start)) * dist;
    }

    /**
     * Closest distance to point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        if (start == end) {
            return start.distance(point);
        }
        const Vector2<Real> dir = end - start;
        const Vector2<Real> diff = point - start;
        Real t = diff.dot(dir) / dir.dot(dir);
        if (t < static_cast<Real>(0)) {
            return diff.length();
        }
        if (t > static_cast<Real>(1)) {
            return (point - end).length();
        }
        Point2<Real> proj = start + dir * t;
        return (point - proj).length();
    }

    /**
     * Closest distance to line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        const Real d1 = line.distance(start);
        const Real d2 = line.distance(end);
        return min(d1, d2);
    }

    /**
     * Closest distance to ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        const Real d1 = ray.distance(start);
        const Real d2 = ray.distance(end);
        const Real d3 = distance(ray.origin);
        return min(d1, min(d2, d3));
    }

    /**
     * Closest distance to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Real d1 = distance(other.start);
        const Real d2 = distance(other.end);
        const Real d3 = other.distance(start);
        const Real d4 = other.distance(end);
        return min(d1, min(d2, min(d3, d4)));
    }

    /**
     * Closest distance to circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    /**
     * Closest distance to triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to aligned-rectangle.
     * @param rectangle Aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Unnormalized direction from start point towards the end point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> direction_unnormalized() const
    {
        return end - start;
    }

    /**
     * Normalized direction from start point towards end point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> direction() const
    {
        return direction_unnormalized().normalize();
    }

    /**
     * Determine if parallel with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line2<Real>& line) const
    {
        return approx_zero((end - start).cross(line.direction));
    }

    /**
     * Determine if parallel with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray2<Real>& ray) const
    {
        return approx_zero((end - start).cross(ray.direction));
    }

    /**
     * Determine if parallel with another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Segment2& other) const
    {
        return approx_zero((end - start).cross(other.end - other.start));
    }

    /**
     * Determine if perpendicular with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Line2<Real>& line) const
    {
        return approx_zero((end - start).dot(line.direction));
    }

    /**
     * Determine if perpendicular with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray2<Real>& ray) const
    {
        return approx_zero((end - start).dot(ray.direction));
    }

    /**
     * Determine if perpendicular with another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Segment2& other) const
    {
        return approx_zero((end - start).dot(other.end - other.start));
    }

    /**
     * Determine if intersects line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
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

    /**
     * Intersection point with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Line2<Real>& line) const
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

    /**
     * Determine if intersects ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const
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

    /**
     * Intersection point with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Ray2<Real>& ray) const
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

    /**
     * Determine if intersects with another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment2& other) const
    {
        const Vector2<Real> dir = end - start;
        const Vector2<Real> dir_other = other.end - other.start;
        const Real dir_cross = dir.cross(dir_other);
        if (dir_cross == static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> diff = other.start - start;
        const Real t = diff.cross(dir_other) / dir_cross;
        const Real t_other = diff.cross(dir) / dir_cross;
        return t >= static_cast<Real>(0) && t <= static_cast<Real>(1) && t_other >= static_cast<Real>(0)
            && t_other <= static_cast<Real>(1);
    }

    /**
     * Intersection point with another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Segment2& other) const
    {
        const Vector2<Real> dir = end - start;
        const Vector2<Real> dir_other = other.end - other.start;
        const Real dir_cross = dir.cross(dir_other);
        if (dir_cross == static_cast<Real>(0)) {
            return std::nullopt;
        }
        const Vector2<Real> diff = other.start - start;
        const Real t = diff.cross(dir_other) / dir_cross;
        const Real t_other = diff.cross(dir) / dir_cross;
        if (t < static_cast<Real>(0) || t > static_cast<Real>(1) || t_other < static_cast<Real>(0)
            || t_other > static_cast<Real>(1)) {
            return std::nullopt;
        }
        return start + dir * t;
    }

    /**
     * Determine if intersects circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersection points with circle. If only single intersection, both returned points are equal.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Circle2<Real>& circle) const;

    /**
     * Determine if intersects triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersection points with triangle. If only single intersection, both returned points are equal.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersection points with rectangle. If only single intersection, both returned points are equal.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects aligned-rectangle.
     * @param rectangle Aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersection points with aligned-rectangle. If only single intersection, both returned points are equal.
     * @param rectangle Aligned-rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Circle2<Real>& circle) const;

    /**
     * Projection of point onto segment.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> project(const Point2<Real>& point) const
    {
        const Vector2<Real> dir = end - start;
        const Real length_sqrd = dir.dot(dir);
        if (length_sqrd == static_cast<Real>(0)) {
            return start;
        }
        const Real t = (point - start).dot(dir) / length_sqrd;
        if (t < static_cast<Real>(0)) {
            return start;
        }
        if (t > static_cast<Real>(1)) {
            return end;
        }
        return start + dir * t;
    }

    /**
     * Slope which does not check if vertical. If vertical, divide-by-zero will occur.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real unchecked_slope() const
    {
        return (end.y - start.y) / (end.x - start.x);
    }

    /**
     * Slope.
     * @return Slope if exists, null if vertical.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Real> slope() const
    {
        const Real denom = end.x - start.x;
        if (denom == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return (end.y - start.y) / denom;
    }

    /**
     * Squared length.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(end.x - start.x) + sqrd(end.y - start.y);
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
    [[nodiscard]] constexpr Point2<Real> midpoint() const
    {
        return Point2<Real>::from_vector((start.to_vector() + end.to_vector()) / static_cast<Real>(2));
    }

    /**
     * Translate by an offset.
     * @param by Offset.
     * @return
     */
    // tested
    [[nodiscard]] constexpr Segment2 translate(const Vector2<Real>& by) const
    {
        return { start.translate(by), end.translate(by) };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Origin.
     * @param by Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 scale_at(const Point2<Real>& scale_origin, const Vector2<Real>& by) const
    {
        return { start.scale_at(scale_origin, by), end.scale_at(scale_origin, by) };
    }

    /**
     * Scale about the origin by a factor.
     * @param by Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 scale(const Vector2<Real>& by) const
    {
        return { start.scale(by), end.scale(by) };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2 rotate_at(const Point2<Real>& rotate_origin, const Real angle) const
    {
        return { start.rotate_at(rotate_origin, angle), end.rotate_at(rotate_origin, angle) };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2 rotate(const Real angle) const
    {
        return { start.rotate(angle), end.rotate(angle) };
    }

    /**
     * Shear along the x-axis about an origin by a factor.
     * @param shear_origin Origin.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 shear_x_at(const Point2<Real>& shear_origin, const Real factor_y) const
    {
        return { start.shear_x_at(shear_origin, factor_y), end.shear_x_at(shear_origin, factor_y) };
    }

    /**
     * Shear along the x-axis about the origin by a factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 shear_x(const Real factor_y) const
    {
        return { start.shear_x(factor_y), end.shear_x(factor_y) };
    }

    /**
     * Shear along the y-axis about an origin by a factor.
     * @param shear_origin Origin.
     * @param angle_x X-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 shear_y_at(const Point2<Real>& shear_origin, const Real angle_x) const
    {
        return { start.shear_y_at(shear_origin, angle_x), end.shear_y_at(shear_origin, angle_x) };
    }

    /**
     * Shear along the y-axis about the origin by a factor.
     * @param factor_x X-Axis factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2 shear_y(const Real factor_x) const
    {
        return { start.shear_y(factor_x), end.shear_y(factor_x) };
    }

    /**
     * Determine if coincident to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Segment2& other) const
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
    [[nodiscard]] constexpr bool approx_equal(const Segment2& other) const
    {
        return start.approx_equal(other.start) && end.approx_equal(other.end);
    }

    /**
     * Determine if start and end are equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Segment2& other) const
    {
        return start == other.start && end == other.end;
    }

    /**
     * Determine if start or end are not equal to another segment.
     * @param other Other segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Segment2& other) const
    {
        return start != other.start || end != other.end;
    }

    /**
     * Lexicographical comparison in the order of start then end.
     * @param other
     * @return
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Segment2& other) const
    {
        if (start != other.start) {
            return start < other.start;
        }
        return end < other.end;
    }
};

/**
 * Solid circle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Circle2 {
public:
    /**
     * Center.
     */
    Point2<Real> center;

    /**
     * Radius
     */
    Real radius;

    /**
     * Default initialize to zero center and radius of 1.
     */
    // tested
    constexpr Circle2()
        : center { Point2<Real>::zero() }
        , radius { static_cast<Real>(1) }
    {
    }

    /**
     * Initialize with center and radius.
     * @param center Center.
     * @param radius Radius.
     */
    // tested
    constexpr Circle2(const Point2<Real>& center, const Real radius)
        : center { center }
        , radius { radius }
    {
    }

    /**
     * Cast from another type.
     * @tparam Other Other type.
     * @param other Other circle.
     */
    // tested
    template <typename Other>
    explicit constexpr Circle2(const Circle2<Other>& other)
        : center { other.center }
        , radius { static_cast<Real>(other.radius) }
    {
    }

    /**
     * Circle with a center and intersects a point.
     * @param center Center.
     * @param point Point.
     * @return Result.
     */
    // tested
    static Circle2 from_center_point(const Point2<Real>& center, const Point2<Real>& point)
    {
        return { center, center.distance(point) };
    }

    /**
     * Circle from 3 points without checking for collinearity. Will result in a divide-by-zero otherwise.
     * @param point1 First point.
     * @param point2 Second point.
     * @param point3 Third point.
     * @return Result.
     */
    // tested
    static Circle2 from_points_unchecked(
        const Point2<Real>& point1, const Point2<Real>& point2, const Point2<Real>& point3)
    {
        const Point2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Point2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const Point2<Real> center = l1.unchecked_intersection(l2);
        const Real radius = center.distance(point1);
        return Circle2 { center, radius };
    }

    /**
     * Circle from points which checks for collinearity.
     * @param point1 First point.
     * @param point2 Second point.
     * @param point3 Third point.
     * @return Circle if exists, null if all 3 points are collinear.
     */
    // tested
    static std::optional<Circle2> from_points(
        const Point2<Real>& point1, const Point2<Real>& point2, const Point2<Real>& point3)
    {
        const Point2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Point2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const std::optional<Point2<Real>> center = l1.intersection(l2);
        if (!center.has_value()) {
            return std::nullopt;
        }
        const Real radius = center.value().distance(point1);
        return Circle2 { center.value(), radius };
    }

    /**
     * Length of the path around the circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real circumference() const
    {
        return static_cast<Real>(2) * pi<Real>() * radius;
    }

    /**
     * Length of the path around the circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real perimeter() const
    {
        return circumference();
    }

    /**
     * Area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real area() const
    {
        return pi<Real>() * sqrd(radius);
    }

    /**
     * Distance of a segment that intersects the center and edges of the circle.
     * @return Result.
     */
    // tested
    [[nodiscard]]
    constexpr Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        return (point - center).length_sqrd() <= sqrd(radius);
    }

    /**
     * Closest signed-distance to point. Positive if outside and negative if inside the circle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    /**
     * Closest distance to point. Zero if point is inside circle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    /**
     * Closest distance to line. Zero if intersects or is inside circle.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        return max(static_cast<Real>(0), line.distance(center) - radius);
    }

    /**
     * Closest distance to ray. Zero if intersects or is inside circle.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        return max(static_cast<Real>(0), ray.distance(center) - radius);
    }

    /**
     * Closest distance to segment. Zero if intersects or is inside circle.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        return max(static_cast<Real>(0), segment.distance(center) - radius);
    }

    /**
     * Closest distance to another circle. Zero if intersects or inside this circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2& other) const
    {
        const Real dist = center.distance(other.center);
        const Real radius_sum = radius + other.radius;
        return max(static_cast<Real>(0), dist - radius_sum);
    }

    /**
     * Closest distance to triangle. Zero if intersects or inside circle.
     * @param triangle Triangle
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to rectangle. Zero if intersects or inside circle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to aligned rectangle. Zero if intersects or inside circle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Point on the edge of the circle at an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Point2<Real> point_at(const Real angle) const
    {
        return { center.x + radius * cos(angle), center.y + radius * sin(angle) };
    }

    /**
     * Direction perpendicular from the edge of the circle at a given angle. Normal points outward from the center.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> normal_at(const Real angle) const
    {
        return Vector2<Real>::axis_x().rotate(angle);
    }

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
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

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(line.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
        const Point2<Real> p1 = line.origin + line.direction * t1;
        const Point2<Real> p2 = line.origin + line.direction * t2;
        return { p1, p2 };
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
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

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - center;
        const Real twice_proj_length = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real adjusted_dist_sqrd = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(twice_proj_length) - static_cast<Real>(4) * adjusted_dist_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_length - disc_sqrt) / static_cast<Real>(2);
        const Real t2 = (-twice_proj_length + disc_sqrt) / static_cast<Real>(2);
        Intersections2<Real> inters;
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

    /**
     * Determine if intersects segment. Being inside the circle is considered an intersection.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        if (contains(segment.start) || contains(segment.end)) {
            return true;
        }
        const Vector2<Real> seg_dir = segment.end - segment.start;
        const Vector2<Real> circle_dir = segment.start - center;
        const Real seg_len_sqrd = seg_dir.dot(seg_dir);
        const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant
            = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
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

    /**
     * Intersection points with a segment. If only single intersection, both returned points are equal.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        const Vector2<Real> seg_dir = segment.end - segment.start;
        const Vector2<Real> circle_dir = segment.start - center;
        const Real seg_len_sqrd = seg_dir.dot(seg_dir);
        const Real twice_proj_len = static_cast<Real>(2) * circle_dir.dot(seg_dir);
        const Real dist_sqrd_minus_radius_sqrd = circle_dir.dot(circle_dir) - sqrd(radius);
        const Real discriminant
            = sqrd(twice_proj_len) - static_cast<Real>(4) * seg_len_sqrd * dist_sqrd_minus_radius_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real disc_sqrt = sqrt(discriminant);
        const Real t1 = (-twice_proj_len - disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_proj_len + disc_sqrt) / (static_cast<Real>(2) * seg_len_sqrd);
        Intersections2<Real> inters;
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

    /**
     * Determine if intersects another circle. Being inside the circle is considered an intersection.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Circle2& other) const
    {
        return center.distance_sqrd(other.center) <= sqrd(radius + other.radius);
    }

    /**
     * Intersection depth with another circle.
     * @param other Other circle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2& other) const
    {
        const Vector2<Real> diff = other.center - center;
        const Real radius_sum = radius + other.radius;
        if (diff == Vector2<Real>::zero()) {
            return Vector2<Real>::axis_x() * radius_sum;
        }
        const Real dist_sqrd = diff.length_sqrd();
        const Real dist = sqrt(dist_sqrd);
        const Real depth = radius_sum - dist;
        if (depth < static_cast<Real>(0)) {
            return std::nullopt;
        }
        return diff.normalize() * depth;
    }

    /**
     * Determine if intersects a triangle. Being inside the circle is considered an intersection.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersect depth with triangle.
     * @param triangle Triangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with rectangle.
     * @param rectangle Rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - center;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - sqrd(radius);
        const Real discriminant = sqrd(b) - static_cast<Real>(4) * c;
        return approx_zero(discriminant);
    }

    /**
     * Determine if tangent to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Ray2<Real>& ray) const
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

    /**
     * Determine if tangent to a segment.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Segment2<Real>& segment) const
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

    /**
     * Determine if tangent to another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Circle2& other) const
    {
        if (center == other.center) {
            return false;
        }
        const Real dist_sqrd = center.distance_sqrd(other.center);
        return nnm::approx_equal(dist_sqrd, sqrd(radius + other.radius))
            || nnm::approx_equal(dist_sqrd, sqrd(radius - other.radius));
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Circle2 translate(const Vector2<Real>& offset) const
    {
        return { center.translate(offset), radius };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Circle2 rotate_at(const Point2<Real>& rotate_origin, const Real angle) const
    {
        return { center.rotate_at(rotate_origin, angle), radius };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Circle2 rotate(const Real angle) const
    {
        return { center.rotate(angle), radius };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Circle2 scale_at(const Point2<Real>& scale_origin, const Real factor) const
    {
        return { center.scale_at(scale_origin, Vector2<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Circle2 scale(const Real factor) const
    {
        return { center.scale(Vector2<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Determine if coincident to another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Circle2& other) const
    {
        return approx_equal(other);
    }

    /**
     * Determine if all members are approximately equal to another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Circle2& other) const
    {
        return center.approx_equal(other.center) && nnm::approx_equal(radius, other.radius);
    }

    /**
     * Determine if all members are equal with another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Circle2& other) const
    {
        return center == other.center && radius == other.radius;
    }

    /**
     * Determine if any members are not equal with another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Circle2& other) const
    {
        return center != other.center || radius != other.radius;
    }

    /**
     * Lexicographical comparison in the order of center then radius with another circle.
     * @param other Other circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Circle2& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        return radius < other.radius;
    }
};

/**
 * Solid triangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Triangle2 {
public:
    /**
     * Vertices.
     */
    Point2<Real> vertices[3];

    /**
     * Default initializes to all vertices at the origin.
     */
    // tested
    constexpr Triangle2()
        : vertices { Point2<Real>::zero(), Point2<Real>::zero(), Point2<Real>::zero() }
    {
    }

    /**
     * Initialize with provided vertices.
     * @param vertex0 First vertex.
     * @param vertex1 Second vertex.
     * @param vertex2 Third vertex.
     */
    // tested
    constexpr Triangle2(const Point2<Real>& vertex0, const Point2<Real>& vertex1, const Point2<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    /**
     * Cast from another type.
     * @tparam Other Other type.
     * @param other Other triangle.
     */
    // tested
    template <typename Other>
    explicit constexpr Triangle2(const Triangle2<Other>& other)
        : vertices { Point2<Real> { other.vertices[0] },
                     Point2<Real> { other.vertices[1] },
                     Point2<Real> { other.vertices[2] } }
    {
    }

    /**
     * Edge as a line segment in the order of vertex 0 to 1, 1 to 2, then 2 to 0.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> edge(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        return { vertices[index], vertices[next_index] };
    }

    /**
     * Centroid which is the average between all vertices.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> centroid() const
    {
        return Point2<Real>::from_vector(
            (vertices[0].to_vector() + vertices[1].to_vector() + vertices[2].to_vector()) / static_cast<Real>(3));
    }

    /**
     * Circumcenter which is the intersection between the perpendicular bisectors of the edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point2<Real>> circumcenter() const
    {
        const Segment2<Real> e0 = edge(0);
        const Segment2<Real> e1 = edge(1);
        const Line2<Real> l0 { e0.midpoint(), e0.direction().arbitrary_perpendicular() };
        const Line2<Real> l1 { e1.midpoint(), e1.direction().arbitrary_perpendicular() };
        return l0.intersection(l1);
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
    [[nodiscard]] std::optional<Point2<Real>> incenter() const
    {
        return angle_bisector(0).intersection(angle_bisector(1));
    }

    /**
     * Orthocenter which is the intersection between the altitudes of the triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point2<Real>> orthocenter() const
    {
        const std::optional<Segment2<Real>> a0 = altitude(0);
        if (!a0.has_value()) {
            return std::nullopt;
        }
        const std::optional<Segment2<Real>> a1 = altitude(1);
        if (!a1.has_value()) {
            return std::nullopt;
        }
        return Line2<Real>::from_segment(*a0).intersection(Line2<Real>::from_segment(*a1));
    }

    /**
     * Area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real area() const
    {
        const Real sum = vertices[0].x * (vertices[1].y - vertices[2].y)
            + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y);
        return abs(sum) / static_cast<Real>(2);
    }

    /**
     * Median which is the line segment from a vertex to the midpoint of its opposite edge.
     * It is indexed in the order of vertex 0 to midpoint of edge 1, vertex 1 to midpoint of edge 2, then vertex 2 to
     * midpoint of edge 0.
     * @param index Index of a vertex.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> median(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        return { vertices[index], edge(next_index).midpoint() };
    }

    /**
     * Perpendicular bisector of an edge.
     * The perpendicular bisector is a line that divides an edge in half and is perpendicular to the edge.
     * @param index Index of an edge.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2<Real> perpendicular_bisector(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        return { edge(index).midpoint(), edge(index).direction().arbitrary_perpendicular() };
    }

    /**
     * Interior angle at a vertex index.
     * @param index Index of a vertex.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real angle(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        const int prev_index = (index + 2) % 3;
        const Vector2<Real> dir1 = vertices[prev_index] - vertices[index];
        const Vector2<Real> dir2 = vertices[next_index] - vertices[index];
        const Real denom = dir1.length() * dir2.length();
        if (approx_zero(denom)) {
            return static_cast<Real>(0);
        }
        return acos(dir1.dot(dir2) / denom);
    }

    /**
     * Perpendicular bisector of the interior angles in the order of the angle at vertex 0, 1, then 2.
     * The perpendicular bisector is a line that divides an interior angle evenly in half.
     * @param index Index of a vertex.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line2<Real> angle_bisector(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        const int prev_index = (index + 2) % 3;
        const Vector2<Real> dir1 = (vertices[prev_index] - vertices[index]).normalize();
        const Vector2<Real> dir2 = (vertices[next_index] - vertices[index]).normalize();
        const Vector2<Real> bisector_dir = (dir1 + dir2).normalize();
        return { vertices[index], bisector_dir };
    }

    /**
     * Normal of an edge which is the vector perpendicular to the edge and points outward from the triangle.
     * @param index Index of an edge.
     * @return
     */
    // tested
    [[nodiscard]] Vector2<Real> normal(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const Vector2<Real> edge1_dir = edge(1).direction_unnormalized();
        const Vector2<Real> edge2_dir = edge(2).direction_unnormalized();
        const bool reverse = edge1_dir.cross(edge2_dir) > static_cast<Real>(0);
        const Vector2<Real> edge_dir = edge(index).direction();
        const Vector2<Real> normal = { -edge_dir.y, edge_dir.x };
        return reverse ? -normal : normal;
    }

    /**
     * Altitude which is a line segment through a vertex to a perpendicular line extending from its opposite edge.
     * @param index Index of a vertex.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Segment2<Real>> altitude(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const Point2<Real>& vertex = vertices[index];
        const Segment2<Real> base = edge((index + 1) % 3);
        const Vector2<Real> perp_dir = (base.end - base.start).arbitrary_perpendicular().normalize();
        const Line2<Real> altitude_line { vertex, perp_dir };
        const std::optional<Point2<Real>> intersection = altitude_line.intersection(Line2<Real>::from_segment(base));
        if (!intersection.has_value()) {
            return std::nullopt;
        }
        return Segment2<Real> { vertex, *intersection };
    }

    /**
     * A point that is the result of linearly interpolating between all vertices with given weights.
     * @param weights Weights.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> lerp_point(const Vector3<Real>& weights) const
    {
        return Point2<Real>::from_vector(
            weights.x * vertices[0].to_vector() + weights.y * vertices[1].to_vector() + weights.z * vertices[2].to_vector());
    }

    /**
     * Barycentric coordinates of a point which is the weights for linearly interpolating between the vertices.
     * @param point Point.
     * @return Barycentric coordinates.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> barycentric_unchecked(const Point2<Real>& point) const
    {
        const Vector2<Real> v0 = vertices[1] - vertices[0];
        const Vector2<Real> v1 = vertices[2] - vertices[0];
        const Vector2<Real> v2 = point - vertices[0];
        const Real cross01 = v0.cross(v1);
        const Real cross21 = v2.cross(v1);
        const Real cross02 = v0.cross(v2);
        const Real inv_cross01 = static_cast<Real>(1) / cross01;
        const Real y = cross21 * inv_cross01;
        const Real z = cross02 * inv_cross01;
        const Real x = static_cast<Real>(1) - y - z;
        return { x, y, z };
    }

    /**
     * Barycentric coordinates of a point which is the weights for linearly interpolating between the vertices.
     * @param point Point.
     * @return Barycentric coordinates.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector3<Real>> barycentric(const Point2<Real>& point) const
    {
        if (!contains(point)) {
            return std::nullopt;
        }
        const Vector2<Real> v0 = vertices[1] - vertices[0];
        const Vector2<Real> v1 = vertices[2] - vertices[0];
        const Vector2<Real> v2 = point - vertices[0];
        const Real cross01 = v0.cross(v1);
        const Real cross21 = v2.cross(v1);
        const Real cross02 = v0.cross(v2);
        if (approx_zero(cross01)) {
            return std::nullopt;
        }
        const Real inv_cross01 = static_cast<Real>(1) / cross01;
        const Real y = cross21 * inv_cross01;
        const Real z = cross02 * inv_cross01;
        const Real x = static_cast<Real>(1) - y - z;
        return Vector3<Real> { x, y, z };
    }

    /**
     * Circumcircle which is a circle that intersects all vertices.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Circle2<Real>> circumcircle() const
    {
        return Circle2<Real>::from_points(vertices[0], vertices[1], vertices[2]);
    }

    /**
     * Incircle which is a circle inside the triangle and tangent to all edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Circle2<Real>> incircle() const
    {
        const std::optional<Point2<Real>> center = incenter();
        if (!center.has_value()) {
            return std::nullopt;
        }
        return Circle2<Real> { *center, edge(0).distance(*center) };
    }

    /**
     * Determine if vertices are collinear.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear() const
    {
        return edge(0).collinear(edge(1));
    }

    /**
     * Determine if point is inside the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        if (collinear()) {
            return edge(0).contains(point) || edge(1).contains(point) || edge(2).contains(point);
        }
        const Vector3<Real> b = barycentric_unchecked(point);
        return approx_greater_equal_zero(b.x) && approx_less_equal(b.x, static_cast<Real>(1))
            && approx_greater_equal_zero(b.y) && approx_less_equal(b.y, static_cast<Real>(1))
            && approx_greater_equal_zero(b.z) && approx_less_equal(b.z, static_cast<Real>(1));
    }

    /**
     * Closest signed-distance to the edges of the triangle. Negative if inside, positive if outside.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const
    {
        Real min_dist = std::numeric_limits<Real>::max();
        for (int i = 0; i < 3; ++i) {
            const Real dist = edge(i).distance(point);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return contains(point) ? -min_dist : min_dist;
    }

    /**
     * Closest distance to a point. Zero if point is inside the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        if (contains(point)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (int i = 0; i < 3; ++i) {
            const Real dist = edge(i).distance(point);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line2<Real>& line) const
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

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
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

    /**
     * Closest distance to a line segment. Zero if segment is inside triangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
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

    /**
     * Closest distance to a circle. Zero if circle is inside triangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const
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

    /**
     * Closest distance to another triangle. Zero if other triangle is inside this triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (int i = 0; i < 3; ++i) {
            const Real dist = other.distance(edge(i));
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return min_dist;
    }

    /**
     * Closest distance to a rectangle. Zero if rectangle is inside triangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to an aligned rectangle. Zero if aligned rectangle is inside triangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(line)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Point2<Real>> point = edge(i).intersection(line)) {
                points.insert(*point);
            }
        }
        return points;
    }

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const
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

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Point2<Real>> point = edge(i).intersection(ray)) {
                points.insert(*point);
            }
        }
        return points;
    }

    /**
     * Determine if intersects a line segment. Being inside the triangle is considered an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const
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

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Point2<Real>> point = edge(i).intersection(segment)) {
                points.insert(*point);
            }
        }
        return points;
    }

    /**
     * Determine if intersects circle. Being inside the triangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
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

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
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

    /**
     * Determine if intersects another triangle. Being inside the triangle is an intersection.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle2& other) const
    {
        for (const Point2<Real>& vertex : other.vertices) {
            if (contains(vertex)) {
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (other.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    /**
     * Intersect depth with another triangle.
     * @param other Other triangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2& other) const
    {
        const auto depth_on_normal
            = [this, &other](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Point2<Real>& v : vertices) {
                const Real proj = v.to_vector().dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Point2<Real>& v : other.vertices) {
                const Real proj = v.to_vector().dot(normal);
                other_min = min(other_min, proj);
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
        const std::array<Vector2<Real>, 6> normals
            = { normal(0), normal(1), normal(2), -other.normal(0), -other.normal(1), -other.normal(2) };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if intersects a rectangle. Being inside the triangle is an intersection.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with a rectangle.
     * @param rectangle Rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if equilateral which is where all edges have the same length.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool equilateral() const
    {
        return nnm::approx_equal(edge(0).length_sqrd(), edge(1).length_sqrd())
            && nnm::approx_equal(edge(1).length_sqrd(), edge(2).length_sqrd())
            && nnm::approx_equal(edge(2).length_sqrd(), edge(0).length_sqrd());
    }

    /**
     * Determine if similar to another triangle.
     * Similarity is determined if one triangle can be translated, rotated, scaled, or flipped to become the other.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool similar(const Triangle2& other) const
    {
        std::array angles { angle(0), angle(1), angle(2) };
        std::array angles_other { other.angle(0), other.angle(1), other.angle(2) };
        int equal_count = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (nnm::approx_equal(angles[i], angles_other[j])) {
                    ++equal_count;
                    if (equal_count >= 2) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * Determine if a right triangle. This is if one of the interior angles is 90 degrees.
     * @return Result.
     */
    [[nodiscard]] bool right() const
    {
        constexpr Real right_angle = pi<float>() / static_cast<Real>(2);
        return nnm::approx_equal(angle(0), right_angle) || nnm::approx_equal(angle(1), right_angle)
            || nnm::approx_equal(angle(2), right_angle);
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 translate(const Vector2<Real>& offset) const
    {
        return { vertices[0].translate(offset), vertices[1].translate(offset), vertices[2].translate(offset) };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Triangle2 rotate_at(const Point2<Real>& rotate_origin, const Real angle) const
    {
        return { vertices[0].rotate_at(rotate_origin, angle),
                 vertices[1].rotate_at(rotate_origin, angle),
                 vertices[2].rotate_at(rotate_origin, angle) };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Triangle2 rotate(const Real angle) const
    {
        return { vertices[0].rotate(angle), vertices[1].rotate(angle), vertices[2].rotate(angle) };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 scale_at(const Point2<Real>& scale_origin, const Vector2<Real>& factor) const
    {
        return { vertices[0].scale_at(scale_origin, factor),
                 vertices[1].scale_at(scale_origin, factor),
                 vertices[2].scale_at(scale_origin, factor) };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 scale(const Vector2<Real>& factor) const
    {
        return { vertices[0].scale(factor), vertices[1].scale(factor), vertices[2].scale(factor) };
    }

    /**
     * Shear along the x-axis about an origin by a shear factor.
     * @param shear_origin Shear origin.
     * @param factor Y-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 shear_x_at(const Point2<Real>& shear_origin, const Real factor) const
    {
        return { vertices[0].shear_x_at(shear_origin, factor),
                 vertices[1].shear_x_at(shear_origin, factor),
                 vertices[2].shear_x_at(shear_origin, factor) };
    }

    /**
     * Shear along the x-axis about the origin by a shear factor.
     * @param factor Y-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 shear_x(const Real factor) const
    {
        return { vertices[0].shear_x(factor), vertices[1].shear_x(factor), vertices[2].shear_x(factor) };
    }

    /**
     * Shear along the y-axis about an origin by a shear factor.
     * @param shear_origin Shear origin.
     * @param factor X-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 shear_y_at(const Point2<Real>& shear_origin, const Real factor) const
    {
        return { vertices[0].shear_y_at(shear_origin, factor),
                 vertices[1].shear_y_at(shear_origin, factor),
                 vertices[2].shear_y_at(shear_origin, factor) };
    }

    /**
     * Shear along the y-axis about the origin by a shear factor.
     * @param factor X-Axis shear factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle2 shear_y(const Real factor) const
    {
        return { vertices[0].shear_y(factor), vertices[1].shear_y(factor), vertices[2].shear_y(factor) };
    }

    /**
     * Determine if coincident with another triangle which is if the vertices of both triangle are
     * equal regardless of vertex order.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coincident(const Triangle2& other) const
    {
        const std::array permutations {
            Triangle2 { vertices[0], vertices[1], vertices[2] }, Triangle2 { vertices[0], vertices[2], vertices[1] },
            Triangle2 { vertices[1], vertices[0], vertices[2] }, Triangle2 { vertices[1], vertices[2], vertices[0] },
            Triangle2 { vertices[2], vertices[0], vertices[1] }, Triangle2 { vertices[2], vertices[1], vertices[0] }
        };
        for (const Triangle2& permutation : permutations) {
            if (permutation.approx_equal(other)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if vertices are equal to another triangle's vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Triangle2& other) const
    {
        return vertices[0].approx_equal(other.vertices[0]) && vertices[1].approx_equal(other.vertices[1])
            && vertices[2].approx_equal(other.vertices[2]);
    }

    /**
     * Determine if all vertices are exactly equal to another triangle's vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Triangle2& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    /**
     * Determine if any vertices are not exactly equal to another triangle's vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Triangle2& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    /**
     * Lexicographical comparison in the order of the vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Triangle2& other) const
    {
        if (vertices[0] == other.vertices[0]) {
            if (vertices[1] == other.vertices[1]) {
                return vertices[2] < other.vertices[2];
            }
            return vertices[1] < other.vertices[1];
        }
        return vertices[0] < other.vertices[0];
    }
};

/**
 * Solid rectangle with rotation.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Rectangle2 {
public:
    /**
     * Center.
     */
    Point2<Real> center;

    /**
     * Size.
     */
    Vector2<Real> size;

    /**
     * Rotation angle.
     */
    Real angle;

    /**
     * Default initialize centered at the origin with zero size and zero rotation.
     */
    // tested
    constexpr Rectangle2()
        : center { Point2<Real>::zero() }
        , size { Vector2<Real>::zero() }
        , angle { static_cast<Real>(0) }
    {
    }

    /**
     * Initialize with center, size, and rotation angle.
     * @param center Center.
     * @param size Size.
     * @param angle Rotation angle in radians.
     */
    // tested
    constexpr Rectangle2(const Point2<Real>& center, const Vector2<Real>& size, const Real angle)
        : center { center }
        , size { size }
        , angle { angle }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other rectangle.
     */
    // tested
    template <typename Other>
    explicit constexpr Rectangle2(const Rectangle2<Other>& other)
        : center { other.center }
        , size { other.size }
        , angle { static_cast<Real>(other.angle) }
    {
    }

    /**
     * Vertex in the negative x and negative y corner before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Point2<Real> vertex_nx_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center - half_size).rotate_at(center, angle);
    }

    /**
     * Vertex in the negative x and positive y corner before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Point2<Real> vertex_nx_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Point2<Real> { center.x - half_size.x, center.y + half_size.y }.rotate_at(center, angle);
    }

    /**
     * Vertex in the positive x and negative y corner before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Point2<Real> vertex_px_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Point2<Real> { center.x + half_size.x, center.y - half_size.y }.rotate_at(center, angle);
    }

    /**
     * Vertex in the positive x and positive y corner before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Point2<Real> vertex_px_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center + half_size).rotate_at(center, angle);
    }

    /**
     * Edge in the negative x direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_nx() const
    {
        return { vertex_nx_ny(), vertex_nx_py() };
    }

    /**
     * Edge in the negative y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_ny() const
    {
        return { vertex_nx_ny(), vertex_px_ny() };
    }

    /**
     * Edge in the positive x direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_px() const
    {
        return { vertex_px_ny(), vertex_px_py() };
    }

    /**
     * Edge in the positive y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_py() const
    {
        return { vertex_nx_py(), vertex_px_py() };
    }

    /**
     * Normal of the edge in the negative x direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> normal_nx() const
    {
        const Vector2<Real> dir = edge_nx().direction();
        return { -dir.y, dir.x };
    }

    /**
     * Normal of the edge in the negative y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> normal_ny() const
    {
        const Vector2<Real> dir = edge_ny().direction();
        return { dir.y, -dir.x };
    }

    /**
     * Normal of the edge in the positive x direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> normal_px() const
    {
        const Vector2<Real> dir = edge_px().direction();
        return { dir.y, -dir.x };
    }

    /**
     * Normal of the edge in the positive y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector2<Real> normal_py() const
    {
        const Vector2<Real> dir = edge_py().direction();
        return { -dir.y, dir.x };
    }

    /**
     * Area.
     * @return Area.
     */
    // tested
    [[nodiscard]] constexpr Real area() const
    {
        return size.x * size.y;
    }

    /**
     * Perimeter which is the combined length of all edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real perimeter() const
    {
        return static_cast<Real>(2) * size.x + static_cast<Real>(2) * size.y;
    }

    /**
     * Determine if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool contains(const Point2<Real>& point) const
    {
        const Vector2<Real> local_point = (point - center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return abs(local_point.x) <= half_size.x && abs(local_point.y) <= half_size.y;
    }

    /**
     * Closest signed distance to the edges of the rectangle. Negative if inside, positive if outside the rectangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const
    {
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(point);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return contains(point) ? -min_dist : min_dist;
    }

    /**
     * Closest distance to point. Zero if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        const Vector2<Real> local_point = (point - center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Vector2<Real> closest = local_point.clamp(-half_size, half_size);
        return (local_point - closest).length();
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line2<Real>& line) const
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

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
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

    /**
     * Closest distance to a line segment. Zero if line segment is inside the rectangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
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

    /**
     * Closest distance to a circle. Zero if circle is inside the rectangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const
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

    /**
     * Closest distance to a triangle. Zero if triangle is inside the rectangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const
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

    /**
     * Closest distance to another rectangle. Zero if other rectangle is inside of this rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2& other) const
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

    /**
     * Closest distance to an aligned rectangle. Zero if the aligned rectangle is inside of this rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Line2<Real>& line) const
    {
        return edge_nx().intersects(line) || edge_ny().intersects(line) || edge_px().intersects(line)
            || edge_py().intersects(line);
    }

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        return edge_nx().intersects(ray) || edge_ny().intersects(ray) || edge_px().intersects(ray)
            || edge_py().intersects(ray);
    }

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a line segment. Being inside the rectangle is an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        return contains(segment.start) || contains(segment.end) || edge_nx().intersects(segment)
            || edge_ny().intersects(segment) || edge_px().intersects(segment) || edge_py().intersects(segment);
    }

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(segment);
                intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
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

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
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

    /**
     * Determine if intersects a triangle. Being inside the rectangle is an intersection.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const
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

    /**
     * Intersect depth with a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const
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
        const std::array<Point2<Real>, 4> rect_verts
            = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Point2<Real>, 3> tri_verts
            = { triangle.vertices[0], triangle.vertices[1], triangle.vertices[2] };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(rect_verts, tri_verts, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if intersects another rectangle. Being inside this rectangle is an intersection.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2& other) const
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

    /**
     * Intersect depth with another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2& other) const
    {
        const auto depth_on_normal
            = [](const std::array<Point2<Real>, 4>& verts,
                 const std::array<Point2<Real>, 4>& verts_other,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Point2<Real>& v : verts) {
                const Real proj = v.to_vector().dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Point2<Real>& v : verts_other) {
                const Real proj = v.to_vector().dot(normal);
                other_min = min(other_min, proj);
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
            normal_nx(),        normal_ny(),        normal_px(),        normal_py(),
            -other.normal_nx(), -other.normal_ny(), -other.normal_px(), -other.normal_py(),
        };
        const std::array<Point2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Point2<Real>, 4> verts_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(verts, verts_other, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if intersects an aligned rectangle. Being inside this rectangle is an intersection.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle2 translate(const Vector2<Real>& offset) const
    {
        return { center.translate(offset), size, angle };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Rectangle2 rotate_at(const Point2<Real>& rotate_origin, const Real angle_) const
    {
        return { center.rotate_at(rotate_origin, angle_), size, normalize_angle(angle + angle_) };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] Rectangle2 rotate(const Real angle_) const
    {
        return { center.rotate(angle_), size, normalize_angle(angle + angle_) };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle2 scale_at(const Point2<Real>& scale_origin, const Vector2<Real>& factor) const
    {
        return { center.scale_at(scale_origin, factor), size.scale(factor), angle };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle2 scale(const Vector2<Real>& factor) const
    {
        return { center.scale(factor), size.scale(factor), angle };
    }

    /**
     * Determine if coincident which is if all vertices are equal regardless of their order.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coincident(const Rectangle2& other) const
    {
        const Point2<Real> v1 = vertex_nx_ny();
        const Point2<Real> v2 = vertex_nx_py();
        const Point2<Real> v3 = vertex_px_ny();
        const Point2<Real> v4 = vertex_px_py();
        std::array<Point2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        const std::array<std::array<Point2<Real>, 4>, 8> permutations {
            { { v1, v2, v3, v4 },
              { v2, v3, v4, v1 },
              { v3, v4, v1, v2 },
              { v4, v1, v2, v3 },
              { v4, v3, v2, v1 },
              { v3, v2, v1, v4 },
              { v2, v1, v4, v3 },
              { v1, v4, v3, v2 } }
        };
        for (const std::array<Point2<Real>, 4> permutation : permutations) {
            bool equal = true;
            for (int i = 0; i < 4; ++i) {
                if (!vertices_other[i].approx_equal(permutation[i])) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if all members are approximately equal to another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Rectangle2& other) const
    {
        return center.approx_equal(other.center) && size.approx_equal(other.size)
            && nnm::approx_equal(angle, other.angle);
    }

    /**
     * Determine if all members are exactly equal with another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Rectangle2& other) const
    {
        return center == other.center && size == other.size && angle == other.angle;
    }

    /**
     * Determine if any members are not exactly equal with another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Rectangle2& other) const
    {
        return center != other.center || size != other.size || angle != other.angle;
    }

    /**
     * Lexicographical comparison in the order of center, size, the rotation angle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const Rectangle2& other) const
    {
        if (center == other.center) {
            if (size == other.size) {
                return angle < other.angle;
            }
            return size < other.size;
        }
        return center < other.center;
    }
};

/**
 * Solid axis-aligned rectangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class AlignedRectangle2 {
public:
    /**
     * Minimum corner.
     */
    Point2<Real> min;
    /**
     * Maximum corner.
     */
    Point2<Real> max;

    /**
     * Default initialize to zero minimum and zero maximum.
     */
    // tested
    constexpr AlignedRectangle2()
        : min { Point2<Real>::zero() }
        , max { Point2<Real>::zero() }
    {
    }

    /**
     * Initialize with minimum and maximum corners.
     * @param min Minimum corner.
     * @param max Maximum corner.
     */
    // tested
    constexpr AlignedRectangle2(const Point2<Real>& min, const Point2<Real>& max)
        : min { min }
        , max { max }
    {
    }

    /**
     * Cast from another type.
     * @tparam Other Other type.
     * @param other Other rectangle.
     */
    // tested
    template <typename Other>
    explicit constexpr AlignedRectangle2(const AlignedRectangle2<Other>& other)
        : min { other.min }
        , max { other.max }
    {
    }

    /**
     * Smallest aligned rectangle that contains two points.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    // tested
    static constexpr AlignedRectangle2 from_bounding_points(const Point2<Real>& point1, const Point2<Real>& point2)
    {
        const Point2<Real> min = { nnm::min(point1.x, point2.x), nnm::min(point1.y, point2.y) };
        const Point2<Real> max = { nnm::max(point1.x, point2.x), nnm::max(point1.y, point2.y) };
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    static constexpr AlignedRectangle2 from_bounding_segment(const Segment2<Real>& segment)
    {
        return from_bounding_points(segment.start, segment.end);
    }

    /**
     * Smallest aligned rectangle that contains a circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    static constexpr AlignedRectangle2 from_bounding_circle(const Circle2<Real>& circle)
    {
        const Point2<Real> min = circle.center - Vector2<Real>::all(circle.radius);
        const Point2<Real> max = circle.center + Vector2<Real>::all(circle.radius);
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    static constexpr AlignedRectangle2 from_bounding_triangle(const Triangle2<Real>& triangle)
    {
        Point2<Real> min { std::numeric_limits<Real>::max(), std::numeric_limits<Real>::max() };
        Point2<Real> max { std::numeric_limits<Real>::lowest(), std::numeric_limits<Real>::lowest() };
        for (const Point2<Real>& v : triangle.vertices) {
            min.x = nnm::min(min.x, v.x);
            min.y = nnm::min(min.y, v.y);
            max.x = nnm::max(max.x, v.x);
            max.y = nnm::max(max.y, v.y);
        }
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a non-aligned rectangle.
     * @param rectangle Non-aligned rectangle.
     * @return Result.
     */
    // tested
    static AlignedRectangle2 from_bounding_rectangle(const Rectangle2<Real>& rectangle)
    {
        Point2<Real> min { std::numeric_limits<Real>::max(), std::numeric_limits<Real>::max() };
        Point2<Real> max { std::numeric_limits<Real>::lowest(), std::numeric_limits<Real>::lowest() };
        const std::array<Point2<Real>, 4> vertices {
            rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py()
        };
        for (const Point2<Real>& v : vertices) {
            min.x = nnm::min(min.x, v.x);
            min.y = nnm::min(min.y, v.y);
            max.x = nnm::max(max.x, v.x);
            max.y = nnm::max(max.y, v.y);
        }
        return { min, max };
    }

    /**
     * Vertex in the negative x and negative y corner.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> vertex_nx_ny() const
    {
        return min;
    }

    /**
     * Vertex in the negative x and positive y corner.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> vertex_nx_py() const
    {
        return { min.x, max.y };
    }

    /**
     * Vertex in the positive x and negative y corner.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> vertex_px_ny() const
    {
        return { max.x, min.y };
    }

    /**
     * Vertex in the positive x and positive y corner.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point2<Real> vertex_px_py() const
    {
        return max;
    }

    /**
     * Edge in the negative x direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> edge_nx() const
    {
        return { vertex_nx_ny(), vertex_nx_py() };
    }

    /**
     * Edge in the negative y direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> edge_ny() const
    {
        return { vertex_nx_ny(), vertex_px_ny() };
    }

    /**
     * Edge in the positive x direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> edge_px() const
    {
        return { vertex_px_ny(), vertex_px_py() };
    }

    /**
     * Edge in the positive y direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment2<Real> edge_py() const
    {
        return { vertex_nx_py(), vertex_px_py() };
    }

    /**
     * Normal of the edge in the negative x direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> normal_nx() const
    {
        return -Vector2<Real>::axis_x();
    }

    /**
     * Normal of the edge in the negative y direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> normal_ny() const
    {
        return -Vector2<Real>::axis_y();
    }

    /**
     * Normal of the edge in the positive x direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> normal_px() const
    {
        return Vector2<Real>::axis_x();
    }

    /**
     * Normal of the edge in the positive y direction.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> normal_py() const
    {
        return Vector2<Real>::axis_y();
    }

    /**
     * Size.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector2<Real> size() const
    {
        return max - min;
    }

    /**
     * Area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real area() const
    {
        const Vector2<Real> s = size();
        return s.x * s.y;
    }

    /**
     * Perimeter which is the combined length of all edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real perimeter() const
    {
        const Vector2<Real> s = size();
        return static_cast<Real>(2) * s.x + static_cast<Real>(2) * s.y;
    }

    /**
     * Determine if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point2<Real>& point) const
    {
        // TODO: use approx
        return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
    }

    /**
     * Closest signed-distance of point to the rectangle's edges. Negative if inside, positive if outside.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const
    {
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(point);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        return contains(point) ? -min_dist : min_dist;
    }

    /**
     * Closest distance to the rectangle. Zero if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point2<Real>& point) const
    {
        const Point2<Real> closest = point.clamp(min, max);
        return point.distance(closest);
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line2<Real>& line) const
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

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
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

    /**
     * Closest distance to a line segment. Zero if the line segment is inside the rectangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
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

    /**
     * Closest distance to a circle. Zero if the circle is inside the rectangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const
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

    /**
     * Closest distance to a triangle. Zero if the triangle is inside the rectangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const
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

    /**
     * Closest distance to a non-aligned rectangle. Zero if the non-aligned rectangle is inside this rectangle.
     * @param rectangle Non-aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const
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

    /**
     * Closest distance to another aligned rectangle. Zero if other rectangle is inside this rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2& other) const
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

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const
    {
        return edge_nx().intersects(line) || edge_ny().intersects(line) || edge_px().intersects(line)
            || edge_py().intersects(line);
    }

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const
    {
        return edge_nx().intersects(ray) || edge_ny().intersects(ray) || edge_px().intersects(ray)
            || edge_py().intersects(ray);
    }

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a line segment. Being inside the rectangle is an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const
    {
        return contains(segment.start) || contains(segment.end) || edge_nx().intersects(segment)
            || edge_ny().intersects(segment) || edge_px().intersects(segment) || edge_py().intersects(segment);
    }

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Point2<Real>> intersection = edge.intersection(segment);
                intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects a circle. Being inside the rectangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Circle2<Real>& circle) const
    {
        if (contains(circle.center)) {
            return true;
        }
        const Point2<Real> closest = circle.center.clamp(min, max);
        const Real dist_sqrd = closest.distance_sqrd(circle.center);
        return dist_sqrd <= sqrd(circle.radius);
    }

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
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

    /**
     * Determine if intersects a triangle. Being in the rectangle is an intersection.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const
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

    /**
     * Intersect depth with a triangle.
     * @param triangle Triangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const
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
        const std::array<Point2<Real>, 4> rect_verts
            = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Point2<Real>, 3> tri_verts
            = { triangle.vertices[0], triangle.vertices[1], triangle.vertices[2] };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(rect_verts, tri_verts, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if intersects a non-aligned rectangle. Being inside this rectangle is an intersection.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const
    {
        const std::array<Point2<Real>, 4> vertices_rect = {
            rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py()
        };
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

    /**
     * Intersect depth with a non-aligned rectangle.
     * @param rectangle Non-aligned rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const
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
        const std::array<Point2<Real>, 4> verts_rect = {
            rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py()
        };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(verts, verts_rect, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if intersects another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedRectangle2& other) const
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

    /**
     * Intersect depth with another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2& other) const
    {
        const auto depth_on_normal
            = [](const std::array<Point2<Real>, 4>& verts,
                 const std::array<Point2<Real>, 4>& verts_other,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Point2<Real>& v : verts) {
                const Real proj = v.to_vector().dot(normal);
                this_max = nnm::max(this_max, proj);
            }
            for (const Point2<Real>& v : verts_other) {
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
        const std::array<Vector2<Real>, 4> normals = {
            normal_nx(),
            normal_ny(),
            normal_px(),
            normal_py(),
        };
        const std::array<Point2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Point2<Real>, 4> verts_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        Real min_overlap = std::numeric_limits<Real>::max();
        Vector2<Real> min_normal;
        for (const Vector2<Real>& axis : normals) {
            if (!depth_on_normal(verts, verts_other, axis, min_overlap, min_normal)) {
                return std::nullopt;
            }
        }
        return min_normal * min_overlap;
    }

    /**
     * Determine if minimum and maximum corners are approximately equal with another aligned rectangle.
     * @param rectangle Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const AlignedRectangle2& rectangle) const
    {
        return min.approx_equal(rectangle.min) && max.approx_equal(rectangle.max);
    }

    /**
     * Determine if minimum and maximum corners are exactly equal with another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const AlignedRectangle2& other) const
    {
        return min == other.min && max == other.max;
    }

    /**
     * Determine if either minimum or maximum corners are not exactly equal with another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const AlignedRectangle2& other) const
    {
        return min != other.min || max != other.max;
    }

    /**
     * Lexicographical comparison in the order of minimum then maximum.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const AlignedRectangle2& other) const
    {
        if (min == other.min) {
            return max < other.max;
        }
        return min < other.min;
    }
};

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
Intersections2<Real> Line2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
Intersections2<Real> Line2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Line2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Line2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
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
Intersections2<Real> Ray2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
Intersections2<Real> Ray2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Ray2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
bool Ray2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Ray2<Real>::edge_intersections(const AlignedRectangle2<Real>& rectangle) const
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
Intersections2<Real> Segment2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
Intersections2<Real> Segment2<Real>::edge_intersections(const Triangle2<Real>& triangle) const
{
    return triangle.edge_intersections(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Segment2<Real>::edge_intersections(const Rectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
}

template <typename Real>
bool Segment2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Segment2<Real>::edge_intersections(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.edge_intersections(*this);
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
}

#endif
