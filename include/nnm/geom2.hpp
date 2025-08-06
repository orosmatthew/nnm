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
class Arc2;
using Arc2f = Arc2<float>;
using Arc2d = Arc2<double>;
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
 * Fixed capacity, stack allocated set of Vector2 points.
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
        : m_points { Vector2<Real>::zero(), Vector2<Real>::zero() }
        , m_size { 0 }
    {
    }

    /**
     * Initialize with single intersection point.
     * @param point Intersection point.
     */
    // ReSharper disable once CppNonExplicitConvertingConstructor
    // tested
    constexpr Intersections2(const Vector2<Real>& point) // NOLINT(*-explicit-constructor)
        : m_points { point, Vector2<Real>::zero() }
        , m_size { 1 }
    {
    }

    /**
     * Initialize with two intersection points.
     * @param point1 First intersection.
     * @param point2 Second intersection.
     */
    // tested
    constexpr Intersections2(const Vector2<Real>& point1, const Vector2<Real>& point2)
        : m_points { point1, point2 }
        , m_size { 2 }
    {
    }

    /**
     * Fixed capacity.
     * @return Result.
     */
    // tested
    [[nodiscard]] static uint8_t capacity()
    {
        return 2;
    }

    /**
     * Insert intersection with approximate duplicate checking.
     * @param point Point.
     */
    // tested
    void insert(const Vector2<Real>& point)
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
    void clear()
    {
        m_points[0] = Vector2<Real>::zero();
        m_points[1] = Vector2<Real>::zero();
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
    Vector2<Real>* begin()
    {
        return &m_points[0];
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    // tested
    Vector2<Real>* end()
    {
        return &m_points[m_size + 1];
    }

    /**
     * Start const iterator.
     * @return Iterator.
     */
    // tested
    const Vector2<Real>* begin() const
    {
        return &m_points[0];
    }

    /**
     * End const iterator.
     * @return Iterator.
     */
    // tested
    const Vector2<Real>* end() const
    {
        return &m_points[m_size + 1];
    }

    /**
     * Data pointer.
     * @return Result.
     */
    const Vector2<Real>* data() const
    {
        return m_points;
    }

    /**
     * Data pointer.
     * @return Result.
     */
    Vector2<Real>* data()
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
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
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
    Vector2<Real> m_points[2];
    uint8_t m_size;
};

/**
 * 2D infinite line.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Line2 {
public:
    /**
     * Origin.
     */
    Vector2<Real> origin;
    /**
     * Normalized direction.
     */
    Vector2<Real> direction;

    /**
     * Default initialize with zero origin and in the direction of the x-axis.
     */
    // tested
    constexpr Line2()
        : origin { Vector2<Real>::zero() }
        , direction { Vector2<Real>::axis_x() }
    {
    }

    /**
     * Initialize with given origin and normalized direction. No normalization is done.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Line2(const Vector2<Real>& origin, const Vector2<Real>& direction)
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
    static Line2 from_points(const Vector2<Real>& point1, const Vector2<Real>& point2)
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
     * Line tangent to arc at angle.
     * @param arc Arc.
     * @param angle Angle in radians.
     * @return Result if tangent exists, otherwise null.
     */
    // tested
    static std::optional<Line2> from_tangent(const Arc2<Real>& arc, const Real angle)
    {
        const std::optional<Vector2<Real>> p = arc.point_at(angle);
        if (!p.has_value()) {
            return std::nullopt;
        }
        const Vector2<Real> dir = p.value() - arc.pivot;
        return Line2 { p.value(), dir.arbitrary_perpendicular() };
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
        const Vector2<Real> p = circle.point_at(angle);
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
        return { Vector2<Real>::zero(), Vector2<Real>::axis_x() };
    }

    /**
     * Line at zero origin in the direction of the y-axis.
     * @return Result.
     */
    // tested
    static constexpr Line2 axis_y()
    {
        return { Vector2<Real>::zero(), Vector2<Real>::axis_y() };
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
    static Line2 from_point_slope(const Vector2<Real>& point, const Real slope)
    {
        return { point, nnm::Vector2<Real> { 1.0f, slope }.normalize() };
    }

    /**
     * Line parallel to this line and intersects point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line2 parallel_containing(const Vector2<Real>& point) const
    {
        return { point, direction };
    }

    /**
     * Line perpendicular to this line and intersects point. Both direction and -direction are valid solutions.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Line2 arbitrary_perpendicular_containing(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
    {
        return direction.cross(point - origin);
    }

    /**
     * Closest distance to point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Vector2<Real>& point) const
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
     * Closest distance to 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr Vector2<Real> unchecked_intersection(const Line2& other) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2& other) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2<Real>& ray) const;

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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    /**
     * Intersection points with 2D arc. If only single intersection, both returned points are equal.
     * @param arc 2D Arc.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> intersections(const Arc2<Real>& arc) const;

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
     * Determine if tangent to 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool tangent(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr Vector2<Real> project(const Vector2<Real>& point) const
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
    [[nodiscard]] Line2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
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
    [[nodiscard]] Line2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
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
    [[nodiscard]] Line2 shear_x_at(const Vector2<Real>& shear_origin, const Real factor_y) const
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
    [[nodiscard]] Line2 shear_y_at(const Vector2<Real>& shear_origin, const Real factor_x) const
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
 * 2D Ray.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Ray2 {
public:
    /**
     * Origin
     */
    Vector2<Real> origin;
    /**
     * Normalized direction.
     */
    Vector2<Real> direction;

    /**
     * Initialize with zero origin and in the direction of the x-axis.
     */
    // tested
    constexpr Ray2()
        : origin { Vector2<Real>::zero() }
        , direction { Vector2<Real>::axis_x() }
    {
    }

    /**
     * Initialize with origin and direction. No normalization for the direction is done.
     * @param origin Origin.
     * @param direction Normalized direction.
     */
    // tested
    constexpr Ray2(const Vector2<Real>& origin, const Vector2<Real>& direction)
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
    static Ray2 from_point_to_point(const Vector2<Real>& from, const Vector2<Real>& to)
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
    [[nodiscard]] constexpr bool collinear(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr Real signed_distance(const Vector2<Real>& point) const
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
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
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
     * Closest distance to 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2<Real>& line) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2& other) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    /**
     * Intersection points with 2D arc. If only single intersection, both returned points are equal.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> intersections(const Arc2<Real>& arc) const;

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
     * Determine if tangent to 2D arc.
     * @param arc 2D arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool tangent(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr Vector2<Real> project(const Vector2<Real>& point) const
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
    [[nodiscard]] Ray2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
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
    [[nodiscard]] Ray2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
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
    [[nodiscard]] Ray2 shear_x_at(const Vector2<Real>& shear_origin, const Real factor_y) const
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
    [[nodiscard]] Ray2 shear_y_at(const Vector2<Real>& shear_origin, const Real factor_x) const
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
 * 2D segment.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Segment2 {
public:
    /**
     * Start point.
     */
    Vector2<Real> start;
    /**
     * End point.
     */
    Vector2<Real> end;

    /**
     * Initialize with both start and end points zero.
     */
    // tested
    constexpr Segment2()
        : start { Vector2<Real>::zero() }
        , end { Vector2<Real>::zero() }
    {
    }

    /**
     * Initialize with start and end points.
     * @param from Start point.
     * @param to End point.
     */
    // tested
    constexpr Segment2(const Vector2<Real>& from, const Vector2<Real>& to)
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
        : start { Vector2<Other> { other.start } }
        , end { Vector2<Other> { other.end } }
    {
    }

    /**
     * Determine if collinear with point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
    {
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
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = end - start;
        const Vector2<Real> diff = point - start;
        Real t = diff.dot(dir) / dir.dot(dir);
        Vector2<Real> closest;
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
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = end - start;
        const Vector2<Real> diff = point - start;
        Real t = diff.dot(dir) / dir.dot(dir);
        if (t < static_cast<Real>(0)) {
            return diff.length();
        }
        if (t > static_cast<Real>(1)) {
            return (point - end).length();
        }
        Vector2<Real> proj = start + dir * t;
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
     * Closest distance to arc.
     * @param arc Arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Line2<Real>& line) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Ray2<Real>& ray) const
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
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersection(const Segment2& other) const
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
     * Determine if intersects arc.
     * @param arc Arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const;

    /**
     * Intersection points with arc. If only single intersection, both returned points are equal.
     * @param arc Arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] Intersections2<Real> intersections(const Arc2<Real>& arc) const;

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
     * Determine if tangent to arc.
     * @param arc Arc.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool tangent(const Arc2<Real>& arc) const;

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
    [[nodiscard]] constexpr Vector2<Real> project(const Vector2<Real>& point) const
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
    [[nodiscard]] constexpr Vector2<Real> midpoint() const
    {
        return (end + start) / static_cast<Real>(2);
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
    [[nodiscard]] constexpr Segment2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& by) const
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
    [[nodiscard]] Segment2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
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
    [[nodiscard]] constexpr Segment2 shear_x_at(const Vector2<Real>& shear_origin, const Real factor_y) const
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
    [[nodiscard]] constexpr Segment2 shear_y_at(const Vector2<Real>& shear_origin, const Real angle_x) const
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
 * 2D arc.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Arc2 {
public:
    /**
     * Pivot.
     */
    Vector2<Real> pivot;

    /**
     * Start point.
     */
    Vector2<Real> start;

    /**
     * Angle extended from start point about the pivot.
     */
    Real angle;

    /**
     * Initialize will zero pivot, zero start, and zero angle.
     */
    constexpr Arc2()
        : pivot { Vector2<Real>::zero() }
        , start { Vector2<Real>::zero() }
        , angle { static_cast<Real>(0) }
    {
    }

    /**
     * Initialize with pivot, start, and angle.
     * @param pivot Pivot.
     * @param from Start.
     * @param angle Angle.
     */
    constexpr Arc2(const Vector2<Real>& pivot, const Vector2<Real>& from, const Real angle)
        : pivot { pivot }
        , start { from }
        , angle { angle }
    {
    }

    /**
     * Arc from a pivot and radius that starts at an angle and ends at another angle.
     * @param pivot Pivot.
     * @param radius Radius.
     * @param angle_start Start angle.
     * @param angle_end End angle.
     * @return Result.
     */
    static Arc2 from_pivot_radius_angle_to_angle(
        const Vector2<Real>& pivot, const Real radius, const Real angle_start, const Real angle_end)
    {
        const Vector2<Real> from { pivot.x + radius * cos(angle_start), pivot.y + radius * sin(angle_start) };
        const Real angle = angle_end - angle_start;
        return { pivot, from, angle };
    }

    /**
     * Arc from a start point, intersection point, and end point.
     * Does not check if all points are collinear; would result in a divide-by-zero.
     * @param start Start point.
     * @param through Point to intersect.
     * @param end End point.
     * @return Result.
     */
    static Arc2 from_points_unchecked(
        const Vector2<Real>& start, const Vector2<Real>& through, const Vector2<Real>& end)
    {
        const Vector2<Real> mid1 = nnm::Segment2<Real> { start, through }.midpoint();
        const Vector2<Real> mid2 = nnm::Segment2<Real> { through, end }.midpoint();
        const Vector2<Real> dir1 = through - start;
        const Vector2<Real> dir2 = end - through;
        const Vector2<Real> perp1 = dir1.arbitrary_perpendicular();
        const Vector2<Real> perp2 = dir2.arbitrary_perpendicular();
        const Line2<Real> l1 { mid1, perp1 };
        const Line2<Real> l2 { mid2, perp2 };
        const Vector2<Real> pivot = l1.unchecked_intersection(l2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real angle_start = remainder(pivot.angle_to(start) + pi<Real>(), two_pi);
        const Real angle_end = remainder(pivot.angle_to(end) + pi<Real>(), two_pi);
        const Real angle_through = remainder(pivot.angle_to(through) + pi<Real>(), two_pi);
        const Real angle_diff = abs(nnm::normalize_angle(angle_end - angle_start));
        const bool in_range = angle_in_range(angle_through, angle_start, angle_end);
        const Real angle = in_range   ? angle_end - angle_start
            : angle_end < angle_start ? two_pi - angle_diff
                                      : -two_pi + angle_diff;
        return Arc2 { pivot, start, angle };
    }

    /**
     * Arc from a start point, intersection point, and end point.
     * @param start Start point.
     * @param through Point to intersect.
     * @param end End point.
     * @return Result.
     */
    static std::optional<Arc2> from_points(
        const Vector2<Real>& start, const Vector2<Real>& through, const Vector2<Real>& end)
    {
        const Vector2<Real> mid1 = nnm::Segment2<Real> { start, through }.midpoint();
        const Vector2<Real> mid2 = nnm::Segment2<Real> { through, end }.midpoint();
        const Vector2<Real> dir1 = through - start;
        const Vector2<Real> dir2 = end - through;
        const Vector2<Real> perp1 = dir1.arbitrary_perpendicular();
        const Vector2<Real> perp2 = dir2.arbitrary_perpendicular();
        const Line2<Real> l1 { mid1, perp1 };
        const Line2<Real> l2 { mid2, perp2 };
        const std::optional<Vector2<Real>> pivot = l1.intersection(l2);
        if (!pivot.has_value()) {
            return std::nullopt;
        }
        const Real angle_start = pivot->angle_to(start);
        const Real angle_end = pivot->angle_to(end);
        const Real angle_through = pivot->angle_to(through);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real angle_diff = abs(nnm::normalize_angle(angle_end - angle_start));
        const bool in_range = angle_in_range(angle_through, angle_start, angle_end);
        const Real angle = in_range   ? angle_end - angle_start
            : angle_end < angle_start ? two_pi - angle_diff
                                      : -two_pi + angle_diff;
        return Arc2 { pivot.value(), start, angle };
    }

    /**
     * Normalize angle between -pi and pi.
     * @return Result.
     */
    [[nodiscard]] constexpr Arc2 normalize_angle() const
    {
        return { pivot, start, nnm::normalize_angle(angle) };
    }

    /**
     * Radius.
     * @return Result.
     */
    [[nodiscard]] Real radius() const
    {
        return pivot.distance(start);
    }

    /**
     * Squared radius.
     * @return Result.
     */
    [[nodiscard]] constexpr Real radius_sqrd() const
    {
        return pivot.distance_sqrd(start);
    }

    /**
     * Angle of start point in radians.
     * @return Result.
     */
    [[nodiscard]] Real angle_start() const
    {
        return nnm::normalize_angle(pivot.angle_to(start));
    }

    /**
     * Angle of end point in radians.
     * @return Result.
     */
    [[nodiscard]] Real angle_end() const
    {
        return angle_start() + angle;
    }

    /**
     * Determine if intersects point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        if (!nnm::approx_equal(point.distance_sqrd(pivot), sqrd(radius()))) {
            return false;
        }
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real point_angle = remainder(pivot.angle_to(point), two_pi);
        return angle_in_range(point_angle, angle_start(), angle_end());
    }

    /**
     * Point on the arc at an angle in radians. Does not check if the point is within range.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> unchecked_point_at(const Real angle_) const
    {
        const Real r = radius();
        return { pivot.x + cos(angle_) * r, pivot.y + sin(angle_) * r };
    }

    /**
     * Point on the arc at an angle in radians.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> point_at(const Real angle_) const
    {
        const Real r = radius();
        if (!angle_in_range(angle_, angle_start(), angle_end())) {
            return std::nullopt;
        }
        return Vector2<Real> { pivot.x + cos(angle_) * r, pivot.y + sin(angle_) * r };
    }

    /**
     * End point.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> end() const
    {
        return unchecked_point_at(angle_end());
    }

    /**
     * Arc-length.
     * @return Result.
     */
    [[nodiscard]] Real length() const
    {
        return abs(radius() * angle);
    }

    /**
     * Squared arc-length.
     * @return Result.
     */
    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return radius_sqrd() * sqrd(angle);
    }

    /**
     * Midpoint.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> midpoint() const
    {
        return Arc2 { pivot, start, angle / static_cast<Real>(2) }.end();
    }

    /**
     * Project point onto the arc.
     * @param point Point to project.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> project_point(const Vector2<Real>& point) const
    {
        const Vector2<Real> dir = pivot.direction(point);
        const Vector2<Real> proj = pivot + dir * radius();
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(proj) + two_pi, two_pi);
            angle_in_range(proj_angle, angle_start(), angle_end())) {
            return proj;
        }
        if (const Vector2<Real> to_ = end(); point.distance_sqrd(start) >= point.distance_sqrd(to_)) {
            return to_;
        }
        return start;
    }

    /**
     * Closest distance to point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        if (point == pivot) {
            return radius();
        }
        const Vector2<Real> dir = pivot.direction(point);
        const Vector2<Real> proj = pivot + dir * radius();
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(proj) + two_pi, two_pi);
            angle_in_range(proj_angle, angle_start(), angle_end())) {
            return point.distance(proj);
        }
        const Real from_dist = point.distance(start);
        const Real to_dist = point.distance(end());
        return min(from_dist, to_dist);
    }

    /**
     * Closest signed-distance to point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        const Real dist = distance(point);
        const Vector2<Real> from_point = point - start;
        const Vector2<Real> from_to = end() - start;
        const Real cross = from_to.cross(from_point);
        if (angle < static_cast<Real>(0)) {
            return cross > static_cast<Real>(0) ? dist : -dist;
        }
        return cross <= static_cast<Real>(0) ? dist : -dist;
    }

    /**
     * Closest distance to lin.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        if (intersects(line)) {
            return static_cast<Real>(0);
        }
        Real to_from_min_dist = min(line.distance(start), line.distance(end()));
        const Real proj_scalar = (pivot - line.origin).dot(line.direction);
        const Vector2<Real> closest_point_on_line = line.origin + line.direction * proj_scalar;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_line), two_pi);
            angle_in_range(proj_angle, angle_start(), angle_end())) {
            return min(abs(pivot.distance(closest_point_on_line) - radius()), to_from_min_dist);
        }
        return to_from_min_dist;
    }

    /**
     * Closest distance to ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        if (intersects(ray)) {
            return static_cast<Real>(0);
        }
        const Real to_from_origin_min_dist = min(distance(ray.origin), min(ray.distance(start), ray.distance(end())));
        const Real proj_scalar = (pivot - ray.origin).dot(ray.direction);
        if (proj_scalar >= static_cast<Real>(0)) {
            const Vector2<Real> closest_point_on_ray = ray.origin + ray.direction * proj_scalar;
            const Real two_pi = static_cast<Real>(2) * pi<Real>();
            if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_ray), two_pi);
                angle_in_range(proj_angle, angle_start(), angle_end())) {
                return min(abs(pivot.distance(closest_point_on_ray) - radius()), to_from_origin_min_dist);
            }
        }
        return to_from_origin_min_dist;
    }

    /**
     * Closest distance to segment.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        if (intersects(segment)) {
            return static_cast<Real>(0);
        }
        const Real ends_min_dist = min(
            distance(segment.start), min(distance(segment.end), min(segment.distance(start), segment.distance(end()))));
        const Vector2<Real> seg_dir = segment.direction_unnormalized();
        const Real proj_scalar = (pivot - segment.start).dot(seg_dir) / seg_dir.dot(seg_dir);
        if (proj_scalar >= static_cast<Real>(0) && proj_scalar <= static_cast<Real>(1)) {
            const Vector2<Real> closest_point_on_seg = segment.start + seg_dir * proj_scalar;
            const Real two_pi = static_cast<Real>(2) * pi<Real>();
            if (const Real proj_angle = remainder(pivot.angle_to(closest_point_on_seg), two_pi);
                angle_in_range(proj_angle, angle_start(), angle_end())) {
                return min(abs(pivot.distance(closest_point_on_seg) - radius()), ends_min_dist);
            }
        }
        return ends_min_dist;
    }

    /**
     * Closest distance to other arc.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Arc2& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        const Vector2<Real> dir = pivot.direction(other.pivot);
        const Real angle1 = Vector2<Real>::axis_x().angle_between(dir);
        const Real angle2 = Vector2<Real>::axis_x().angle_between(-dir);
        std::optional<Vector2<Real>> p1 = point_at(angle1);
        if (!p1.has_value()) {
            p1 = point_at(angle2);
        }
        std::optional<Vector2<Real>> p2 = other.point_at(angle1);
        if (!p2.has_value()) {
            p2 = other.point_at(angle2);
        }
        Real min_dist
            = p1.has_value() && p2.has_value() ? min(p1->distance(*p2), other.distance(start)) : other.distance(start);
        min_dist = min(min_dist, other.distance(end()));
        min_dist = min(min_dist, distance(other.start));
        min_dist = min(min_dist, distance(other.end()));
        return min_dist;
    }

    /**
     * Closest distance to circle.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    /**
     * Closest distance to triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Line2<Real>& line) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = line.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(line.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Vector2<Real> intersection1 = line.origin + line.direction * t1;
        const Vector2<Real> intersection2 = line.origin + line.direction * t2;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const Real intersection1_angle = remainder(pivot.angle_to(intersection1), two_pi);
        const Real intersection2_angle = remainder(pivot.angle_to(intersection2), two_pi);
        return angle_in_range(intersection1_angle, from_angle_, to_angle_)
            || angle_in_range(intersection2_angle, from_angle_, to_angle_);
    }

    /**
     * Intersection points with line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> intersections(const Line2<Real>& line) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = line.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(line.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Vector2<Real> intersection1 = line.origin + line.direction * t1;
        const Vector2<Real> intersection2 = line.origin + line.direction * t2;
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const Real intersection1_angle = remainder(pivot.angle_to(intersection1), two_pi);
        const Real intersection2_angle = remainder(pivot.angle_to(intersection2), two_pi);
        const bool in_arc1 = angle_in_range(intersection1_angle, from_angle_, to_angle_);
        const bool in_arc2 = angle_in_range(intersection2_angle, from_angle_, to_angle_);
        Intersections2<Real> intersections;
        if (in_arc1) {
            intersections.insert(intersection1);
        }
        if (in_arc2) {
            intersections.insert(intersection2);
        }
        return intersections;
    }

    /**
     * Determine if intersects ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = ray.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(ray.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const auto in_arc = [&](const Real t) -> bool {
            const Vector2<Real> intersection = ray.origin + ray.direction * t;
            const Real intersection_angle = modf(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const bool in_arc1 = t1 >= static_cast<Real>(0) ? in_arc(t1) : false;
        const bool in_arc2 = t2 >= static_cast<Real>(0) ? in_arc(t2) : false;
        return in_arc1 || in_arc2;
    }

    /**
     * Intersection points with ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> intersections(const Ray2<Real>& ray) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_origin_dir = ray.origin - pivot;
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_origin_dir.dot(ray.direction);
        const Real dot_minus_r_sqrd = pivot_origin_dir.dot(pivot_origin_dir) - sqrd(r);
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / static_cast<Real>(2);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / static_cast<Real>(2);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const auto intersection = [&](const Real t) -> std::optional<Vector2<Real>> {
            const Vector2<Real> point = ray.origin + ray.direction * t;
            if (const Real intersection_angle = modf(pivot.angle_to(point) + two_pi, two_pi);
                angle_in_range(intersection_angle, from_angle_, to_angle_)) {
                return point;
            }
            return std::nullopt;
        };
        const std::optional<Vector2<Real>> point1 = t1 > static_cast<Real>(0) ? intersection(t1) : std::nullopt;
        const std::optional<Vector2<Real>> point2 = t2 > static_cast<Real>(0) ? intersection(t2) : std::nullopt;
        Intersections2<Real> inters;
        if (point1.has_value()) {
            inters.insert(*point1);
        }
        if (point2.has_value()) {
            inters.insert(*point2);
        }
        return inters;
    }

    /**
     * Determine if intersects segment.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_seg_from_dir = segment.start - pivot;
        const Vector2<Real> seg_dir = segment.direction_unnormalized();
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_seg_from_dir.dot(seg_dir);
        const Real dot_minus_r_sqrd = pivot_seg_from_dir.dot(pivot_seg_from_dir) - sqrd(r);
        const Real seg_len_sqrd = segment.length_sqrd();
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * seg_len_sqrd * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return false;
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const auto in_arc = [&](const Vector2<Real>& intersection) -> bool {
            const Real intersection_angle = modf(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const auto in_segment
            = [&](const Real t) -> bool { return t >= static_cast<Real>(0) && t <= static_cast<Real>(1); };
        const Vector2<Real> intersection1 = segment.start + seg_dir * t1;
        const Vector2<Real> intersection2 = segment.start + seg_dir * t2;
        const bool valid1 = in_segment(t1) && in_arc(intersection1);
        const bool valid2 = in_segment(t2) && in_arc(intersection2);
        return valid1 || valid2;
    }

    /**
     * Intersection points with segment. If only single intersection, both returned points are equal.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> intersections(const Segment2<Real>& segment) const
    {
        const Real r = radius();
        const Vector2<Real> pivot_seg_from_dir = segment.start - pivot;
        const Vector2<Real> seg_dir = segment.direction_unnormalized();
        const Real twice_dot_dir = static_cast<Real>(2) * pivot_seg_from_dir.dot(seg_dir);
        const Real dot_minus_r_sqrd = pivot_seg_from_dir.dot(pivot_seg_from_dir) - sqrd(r);
        const Real seg_len_sqrd = segment.length_sqrd();
        const Real discriminant = sqrd(twice_dot_dir) - static_cast<Real>(4) * seg_len_sqrd * dot_minus_r_sqrd;
        if (discriminant < static_cast<Real>(0)) {
            return {};
        }
        const Real sqrt_discriminant = sqrt(discriminant);
        const Real t1 = (-twice_dot_dir - sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real t2 = (-twice_dot_dir + sqrt_discriminant) / (static_cast<Real>(2) * seg_len_sqrd);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle_ = angle_start();
        const Real to_angle_ = angle_end();
        const auto in_arc = [&](const Vector2<Real>& intersection) -> bool {
            const Real intersection_angle = modf(pivot.angle_to(intersection) + two_pi, two_pi);
            return angle_in_range(intersection_angle, from_angle_, to_angle_);
        };
        const auto in_segment
            = [&](const Real t) -> bool { return t >= static_cast<Real>(0) && t <= static_cast<Real>(1); };
        const Vector2<Real> intersection1 = segment.start + seg_dir * t1;
        const Vector2<Real> intersection2 = segment.start + seg_dir * t2;
        Intersections2<Real> inters;
        if (in_segment(t1) && in_arc(intersection1)) {
            inters.insert(intersection1);
        }
        if (in_segment(t2) && in_arc(intersection2)) {
            inters.insert(intersection2);
        }
        return inters;
    }

    /**
     * Determine if intersects other arc.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Arc2& other) const
    {
        if (const Vector2<Real> other_to = other.end();
            start.approx_equal(other.start) || start.approx_equal(other_to) || end().approx_equal(other_to)) {
            return true;
        }
        const Real r1 = radius();
        const Real r2 = other.radius();
        const Vector2<Real> pivot_diff = other.pivot - pivot;
        const Real pivot_dist_sqrd = pivot_diff.dot(pivot_diff);
        const Real pivot_dist = sqrt(pivot_dist_sqrd);
        if (pivot_dist > r1 + r2 || pivot_dist < abs(r1 - r2)) {
            return false;
        }
        const Real pivot_intersect_line_dist
            = (sqrd(r1) - sqrd(r2) + pivot_dist_sqrd) / (static_cast<Real>(2) * pivot_dist);
        const Real perp_dist_intersections = sqrt(sqrd(r1) - sqrd(pivot_intersect_line_dist));
        const Vector2<Real> pivots_line_base = pivot + pivot_diff * (pivot_intersect_line_dist / pivot_dist);
        const Vector2<Real> intersection1
            = pivots_line_base + Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Vector2<Real> intersection2
            = pivots_line_base - Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle1 = angle_start();
        const Real to_angle1 = angle_end();
        const Real from_angle2 = other.angle_start();
        const Real to_angle2 = other.angle_end();
        const auto in_arc
            = [&](const Vector2<Real>& intersection,
                  const Vector2<Real>& pivot,
                  const Real from_angle,
                  const Real to_angle) -> bool {
            const Real intersection_angle = remainder(pivot.angle_to(intersection), two_pi);
            return angle_in_range(intersection_angle, from_angle, to_angle);
        };
        const bool in_arc1_1 = in_arc(intersection1, pivot, from_angle1, to_angle1);
        const bool in_arc1_2 = in_arc(intersection2, pivot, from_angle1, to_angle1);
        const bool in_arc2_1 = in_arc(intersection1, other.pivot, from_angle2, to_angle2);
        const bool in_arc2_2 = in_arc(intersection2, other.pivot, from_angle2, to_angle2);
        return (in_arc1_1 && in_arc2_1) || (in_arc1_2 && in_arc2_2);
    }

    /**
     * Intersection points with other arc. If only single intersection, both returned points are equal.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> intersections(const Arc2& other) const
    {
        if (const Vector2<Real> other_to = other.end();
            start.approx_equal(other.start) || start.approx_equal(other_to) || end().approx_equal(other_to)) {
            return {};
        }
        const Real r1 = radius();
        const Real r2 = other.radius();
        const Vector2<Real> pivot_diff = other.pivot - pivot;
        const Real pivot_dist_sqrd = pivot_diff.dot(pivot_diff);
        const Real pivot_dist = sqrt(pivot_dist_sqrd);
        if (pivot_dist > r1 + r2 || pivot_dist < abs(r1 - r2)) {
            return {};
        }
        const Real pivot_intersect_line_dist
            = (sqrd(r1) - sqrd(r2) + pivot_dist_sqrd) / (static_cast<Real>(2) * pivot_dist);
        const Real perp_dist_intersections = sqrt(sqrd(r1) - sqrd(pivot_intersect_line_dist));
        const Vector2<Real> pivots_line_base = pivot + pivot_diff * (pivot_intersect_line_dist / pivot_dist);
        const Vector2<Real> intersection1
            = pivots_line_base + Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Vector2<Real> intersection2
            = pivots_line_base - Vector2<Real> { -pivot_diff.y, pivot_diff.x } * (perp_dist_intersections / pivot_dist);
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real from_angle1 = angle_start();
        const Real to_angle1 = angle_end();
        const Real from_angle2 = other.angle_start();
        const Real to_angle2 = other.angle_end();
        const auto in_arc
            = [&](const Vector2<Real>& intersection,
                  const Vector2<Real>& pivot,
                  const Real from_angle,
                  const Real to_angle) -> bool {
            const Real intersection_angle = remainder(pivot.angle_to(intersection), two_pi);
            return angle_in_range(intersection_angle, from_angle, to_angle);
        };
        const bool in_arc1_1 = in_arc(intersection1, pivot, from_angle1, to_angle1);
        const bool in_arc1_2 = in_arc(intersection2, pivot, from_angle1, to_angle1);
        const bool in_arc2_1 = in_arc(intersection1, other.pivot, from_angle2, to_angle2);
        const bool in_arc2_2 = in_arc(intersection2, other.pivot, from_angle2, to_angle2);
        Intersections2<Real> inters;
        if (in_arc1_1 && in_arc2_1) {
            inters.insert(intersection1);
        }
        if (in_arc1_2 && in_arc2_2) {
            inters.insert(intersection2);
        }
        return inters;
    }

    /**
     * Determine if intersects circle.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersection points with circle. If only single intersection, both returned points are equal.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> edge_intersections(const Circle2<Real>& circle) const;

    /**
     * Determine if intersects triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects with aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to line.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Line2<Real>& line) const
    {
        const Vector2<Real> dir = line.origin - pivot;
        const Real b = static_cast<Real>(2) * dir.dot(line.direction);
        const Real c = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(b) - static_cast<Real>(4) * c; !approx_zero(disc)) {
            return false;
        }
        const Real t = -b / static_cast<Real>(2);
        const Vector2<Real> p = line.origin + line.direction * t;
        return contains(p);
    }

    /**
     * Determine if tangent to ray.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Ray2<Real>& ray) const
    {
        const Vector2<Real> dir = ray.origin - pivot;
        const Real b = static_cast<Real>(2) * dir.dot(ray.direction);
        const Real c = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(b) - static_cast<Real>(4) * c; !approx_zero(disc)) {
            return false;
        }
        const Real t = -b / static_cast<Real>(2);
        if (t < static_cast<Real>(0)) {
            return false;
        }
        const Vector2<Real> p = ray.origin + ray.direction * t;
        return contains(p);
    }

    /**
     * Determine if tangent to segment.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Segment2<Real>& segment) const
    {
        const Vector2<Real> dir = segment.start - pivot;
        const Vector2<Real> segment_dir = segment.direction();
        const Real twice_dot = static_cast<Real>(2) * dir.dot(segment_dir);
        const Real dist_sqrd_minus_radius_sqrd = dir.dot(dir) - radius_sqrd();
        if (const Real disc = sqrd(twice_dot) - static_cast<Real>(4) * dist_sqrd_minus_radius_sqrd;
            !approx_zero(disc)) {
            return false;
        }
        const Real t = -twice_dot / static_cast<Real>(2);
        if (t < static_cast<Real>(0) || t > segment.length()) {
            return false;
        }
        const Vector2<Real> p = segment.start + segment_dir * t;
        return contains(p);
    }

    /**
     * Determine if tangent to other arc.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Arc2& other) const
    {
        if (pivot == other.pivot) {
            return false;
        }
        const Real dist_sqrd = pivot.distance_sqrd(other.pivot);
        const Real r = radius();
        const Real other_r = other.radius();
        if (!nnm::approx_equal(dist_sqrd, sqrd(r + other_r)) && !nnm::approx_equal(dist_sqrd, sqrd(r - other_r))) {
            return false;
        }
        const Real dist = sqrt(dist_sqrd);
        const Vector2<Real> dir = (other.pivot - pivot) / dist;
        const Vector2<Real> p1 = pivot + dir * r;
        const Vector2<Real> p2 = pivot - dir * other_r;
        return (contains(p1) && other.contains(p1)) || (contains(p2) && other.contains(p2));
    }

    /**
     * Determine if tangent to circle.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Circle2<Real>& circle) const;

    /**
     * Translate by offset.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] Arc2 translate(const Vector2<Real>& offset) const
    {
        return Arc2 { pivot.translate(offset), start.translate(offset), angle };
    }

    /**
     * Scale about an origin by a factor.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Arc2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& factor) const
    {
        return Arc2 { pivot.scale_at(scale_origin, factor), start.scale_at(scale_origin, factor), angle };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Arc2 scale(const Vector2<Real>& factor) const
    {
        return Arc2 { pivot.scale(factor), start.scale(factor), angle };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotate origin.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Arc2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle_) const
    {
        return Arc2 { pivot.rotate_at(rotate_origin, angle_), start.rotate_at(rotate_origin, angle_), angle };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Arc2 rotate(const Real angle_) const
    {
        return Arc2 { pivot.rotate(angle_), start.rotate(angle_), angle };
    }

    /**
     * Determine if coincident to another arc.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] bool coincident(const Arc2& other) const
    {
        if (!pivot.approx_equal(other.pivot)) {
            return false;
        }
        const Vector2<Real> to_ = end();
        const Vector2<Real> other_to = other.end();
        return (start.approx_equal(other.start) && to_.approx_equal(other_to))
            || (start.approx_equal(other_to) && to_.approx_equal(other.start));
    }

    /**
     * Determine if `from`, `pivot`, and `angle` are all approximately equal to another arc.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_equal(const Arc2& other) const
    {
        return start.approx_equal(other.start) && pivot.approx_equal(other.pivot)
            && nnm::approx_equal(angle, other.angle);
    }

    /**
     * Determine if all members are exactly equal.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator==(const Arc2& other) const
    {
        return pivot == other.pivot && start == other.start && angle == other.angle;
    }

    /**
     * Determine if any members are not equal.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Arc2& other) const
    {
        return pivot != other.pivot || start != other.start || angle != other.angle;
    }

    /**
     * Lexicographical compare in the order of pivot, start, then angle.
     * @param other Other arc.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator<(const Arc2& other) const
    {
        if (pivot != other.pivot) {
            return pivot < other.pivot;
        }
        if (start != other.start) {
            return start < other.start;
        }
        return angle < other.angle;
    }
};

/**
 * 2D circle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Circle2 {
public:
    /**
     * Center.
     */
    Vector2<Real> center;

    /**
     * Radius
     */
    Real radius;

    /**
     * Default initialize to zero center and radius of 1.
     */
    constexpr Circle2()
        : center { Vector2<Real>::zero() }
        , radius { static_cast<Real>(1) }
    {
    }

    /**
     * Initialize with center and radius.
     * @param center Center.
     * @param radius Radius.
     */
    constexpr Circle2(const Vector2<Real>& center, const Real radius)
        : center { center }
        , radius { radius }
    {
    }

    /**
     * Circle with a center and intersects a point.
     * @param center Center.
     * @param point Point.
     * @return Result.
     */
    static Circle2 from_center_point(const Vector2<Real>& center, const Vector2<Real>& point)
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
    static Circle2 from_points_unchecked(
        const Vector2<Real>& point1, const Vector2<Real>& point2, const Vector2<Real>& point3)
    {
        const Vector2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Vector2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const Vector2<Real> center = l1.unchecked_intersection(l2);
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
    static std::optional<Circle2> from_points(
        const Vector2<Real>& point1, const Vector2<Real>& point2, const Vector2<Real>& point3)
    {
        const Vector2<Real> mid12 = nnm::Segment2<Real> { point1, point2 }.midpoint();
        const Vector2<Real> mid23 = nnm::Segment2<Real> { point2, point3 }.midpoint();
        const Vector2<Real> dir12 = point2 - point1;
        const Vector2<Real> dir23 = point3 - point2;
        const Vector2<Real> perp12 = dir12.arbitrary_perpendicular();
        const Vector2<Real> perp23 = dir23.arbitrary_perpendicular();
        const Line2<Real> l1 { mid12, perp12 };
        const Line2<Real> l2 { mid23, perp23 };
        const std::optional<Vector2<Real>> center = l1.intersection(l2);
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
    [[nodiscard]] constexpr Real circumference() const
    {
        return static_cast<Real>(2) * pi<Real>() * radius;
    }

    /**
     * Length of the path around the circle.
     * @return Result.
     */
    [[nodiscard]] constexpr Real perimeter() const
    {
        return circumference();
    }

    /**
     * Area.
     * @return Result.
     */
    [[nodiscard]] constexpr Real area() const
    {
        return pi<Real>() * sqrd(radius);
    }

    /**
     * Distance of a segment that intersects the center and edges of the circle.
     * @return Result.
     */
    [[nodiscard]] constexpr Real diameter() const
    {
        return static_cast<Real>(2) * radius;
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
    {
        return (point - center).length_sqrd() <= sqrd(radius);
    }

    /**
     * Closest signed-distance to point. Positive if outside and negative if inside the circle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
    {
        return center.distance(point) - radius;
    }

    /**
     * Closest distance to point. Zero if point is inside circle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        return max(static_cast<Real>(0), signed_distance(point));
    }

    /**
     * Closest distance to line. Zero if intersects or is inside circle.
     * @param line Line.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Line2<Real>& line) const
    {
        return max(static_cast<Real>(0), line.distance(center) - radius);
    }

    /**
     * Closest distance to ray. Zero if intersects or is inside circle.
     * @param ray Ray.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const
    {
        return max(static_cast<Real>(0), ray.distance(center) - radius);
    }

    /**
     * Closest distance to segment. Zero if intersects or is inside circle.
     * @param segment Segment.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const
    {
        return max(static_cast<Real>(0), segment.distance(center) - radius);
    }

    /**
     * Closest distance to arc. Zero if intersects or is inside circle.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        return max(static_cast<Real>(0), arc.distance(center) - radius);
    }

    /**
     * Closest distance to another circle. Zero if intersects or inside this circle.
     * @param other Other circle.
     * @return Result.
     */
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
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to rectangle. Zero if intersects or inside circle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to aligned rectangle. Zero if intersects or inside circle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Point on the edge of the circle at an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> point_at(const Real angle) const
    {
        return { center.x + radius * cos(angle), center.y + radius * sin(angle) };
    }

    /**
     * Direction perpendicular from the edge of the circle at a given angle. Normal points outward from the center.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_at(const Real angle) const
    {
        return Vector2<Real>::axis_x().rotate(angle);
    }

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
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
        const Vector2<Real> p1 = line.origin + line.direction * t1;
        const Vector2<Real> p2 = line.origin + line.direction * t2;
        return { p1, p2 };
    }

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
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
            const Vector2<Real> p = ray.origin + ray.direction * t1;
            inters.insert(p);
        }
        if (t2 >= static_cast<Real>(0)) {
            const Vector2<Real> p = ray.origin + ray.direction * t2;
            inters.insert(p);
        }
        return inters;
    }

    /**
     * Determine if intersects segment. Being inside the circle is considered an intersection.
     * @param segment Segment.
     * @return Result.
     */
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
            const Vector2<Real> p = segment.start + seg_dir * t1;
            inters.insert(p);
        }
        if (t2 >= static_cast<Real>(0) && t2 <= static_cast<Real>(1)) {
            const Vector2<Real> p = segment.start + seg_dir * t2;
            inters.insert(p);
        }
        return inters;
    }

    /**
     * Determine if intersects with an arc. Being inside the circle is considered an intersection.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        if (contains(arc.start)) {
            return true;
        }
        const Real dist = center.distance(arc.pivot);
        const Real arc_radius = arc.radius();
        if (dist > radius + arc_radius || dist < abs(radius - arc_radius) || (dist == 0 && radius == arc_radius)) {
            return false;
        }
        const Real a = (sqrd(radius) - sqrd(arc_radius) + sqrd(dist)) / (static_cast<Real>(2) * dist);
        const Real h = sqrt(sqrd(radius) - sqrd(a));
        const Vector2<Real> diff = arc.pivot - center;
        const Vector2<Real> p = center + a * diff / dist;
        const Vector2<Real> inter1 { p.x + h * diff.y / dist, p.y - h * diff.x / dist };
        const Vector2<Real> inter2 { p.x - h * diff.y / dist, p.y + h * diff.x / dist };
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real inter1_angle = remainder(arc.pivot.angle_to(inter1), two_pi);
        const Real inter2_angle = remainder(arc.pivot.angle_to(inter2), two_pi);
        const Real arc_from_angle = arc.angle_start();
        const Real arc_to_angle = arc.angle_end();
        const bool in_arc = angle_in_range(inter1_angle, arc_from_angle, arc_to_angle)
            || angle_in_range(inter2_angle, arc_from_angle, arc_to_angle);
        return in_arc;
    }

    /**
     * Intersection points with an arc. If only single intersection, both returned points are equal.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] Intersections2<Real> edge_intersections(const Arc2<Real>& arc) const
    {
        const Real dist = center.distance(arc.pivot);
        const Real arc_radius = arc.radius();
        if (dist > radius + arc_radius || dist < abs(radius - arc_radius) || (dist == 0 && radius == arc_radius)) {
            return {};
        }
        const Real a = (sqrd(radius) - sqrd(arc_radius) + sqrd(dist)) / (static_cast<Real>(2) * dist);
        const Real h = sqrt(sqrd(radius) - sqrd(a));
        const Vector2<Real> diff = arc.pivot - center;
        const Vector2<Real> p = center + a * diff / dist;
        const Vector2<Real> inter1 { p.x + h * diff.y / dist, p.y - h * diff.x / dist };
        const Vector2<Real> inter2 { p.x - h * diff.y / dist, p.y + h * diff.x / dist };
        const Real two_pi = static_cast<Real>(2) * pi<Real>();
        const Real inter1_angle = remainder(arc.pivot.angle_to(inter1), two_pi);
        const Real inter2_angle = remainder(arc.pivot.angle_to(inter2), two_pi);
        const Real arc_from_angle = arc.angle_start();
        const Real arc_to_angle = arc.angle_end();
        Intersections2<Real> inters;
        if (angle_in_range(inter1_angle, arc_from_angle, arc_to_angle)) {
            inters.insert(inter1);
        }
        if (angle_in_range(inter2_angle, arc_from_angle, arc_to_angle)) {
            inters.insert(inter2);
        }
        return inters;
    }

    /**
     * Determine if intersects another circle. Being inside the circle is considered an intersection.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool intersects(const Circle2& other) const
    {
        return center.distance_sqrd(other.center) <= sqrd(radius + other.radius);
    }

    /**
     * Intersection depth with another circle.
     * @param other Other circle.
     * @return Result, null if no intersection.
     */
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
    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersect depth with triangle.
     * @param triangle Triangle.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with rectangle.
     * @param rectangle Rectangle.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if tangent to a line.
     * @param line Line.
     * @return Result.
     */
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
     * Determine if tangent to an arc.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] bool tangent(const Arc2<Real>& arc) const
    {
        if (center == arc.pivot) {
            return false;
        }
        const Real dist_sqrd = center.distance_sqrd(arc.pivot);
        const Real arc_radius = arc.radius();
        const bool is_circle_tangent = nnm::approx_equal(dist_sqrd, sqrd(radius + arc_radius))
            || nnm::approx_equal(dist_sqrd, sqrd(radius - arc_radius));
        if (!is_circle_tangent) {
            return false;
        }
        const Real arc_circle_angle = contains(arc.pivot) ? center.angle_to(arc.pivot) : arc.pivot.angle_to(center);
        return angle_in_range(arc_circle_angle, arc.angle_start(), arc.angle_end());
    }

    /**
     * Determine if tangent to another circle.
     * @param other Other circle.
     * @return Result.
     */
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
    [[nodiscard]] Circle2 translate(const Vector2<Real>& offset) const
    {
        return { center.translate(offset), radius };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Circle2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
    {
        return { center.rotate_at(rotate_origin, angle), radius };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle Angle in radians.
     * @return Result.
     */
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
    [[nodiscard]] Circle2 scale_at(const Vector2<Real>& scale_origin, const Real factor) const
    {
        return { center.scale_at(scale_origin, Vector2<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Circle2 scale(const Real factor) const
    {
        return { center.scale(Vector2<Real>::all(factor)), abs(radius * factor) };
    }

    /**
     * Determine if coincident to another circle.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coincident(const Circle2& other) const
    {
        return approx_equal(other);
    }

    /**
     * Determine if all members are approximately equal to another circle.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool approx_equal(const Circle2& other) const
    {
        return center.approx_equal(other.center) && nnm::approx_equal(radius, other.radius);
    }

    /**
     * Determine if all members are equal with another circle.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator==(const Circle2& other) const
    {
        return center == other.center && radius == other.radius;
    }

    /**
     * Determine if any members are not equal with another circle.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Circle2& other) const
    {
        return center != other.center || radius != other.radius;
    }

    /**
     * Lexicographical comparison in the order of center then radius with another circle.
     * @param other Other circle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator<(const Circle2& other) const
    {
        if (center != other.center) {
            return center < other.center;
        }
        return radius < other.radius;
    }
};

/**
 * 2D triangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Triangle2 {
public:
    /**
     * Vertices.
     */
    Vector2<Real> vertices[3];

    /**
     * Default initializes to all vertices at the origin.
     */
    constexpr Triangle2()
        : vertices { Vector2<Real>::zero(), Vector2<Real>::zero(), Vector2<Real>::zero() }
    {
    }

    /**
     * Initialize with provided vertices.
     * @param vertex0 First vertex.
     * @param vertex1 Second vertex.
     * @param vertex2 Third vertex.
     */
    constexpr Triangle2(const Vector2<Real>& vertex0, const Vector2<Real>& vertex1, const Vector2<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    /**
     * Edge as a line segment in the order of vertex 0 to 1, 1 to 2, then 2 to 0.
     * @param index Index.
     * @return Result.
     */
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
    [[nodiscard]] constexpr Vector2<Real> centroid() const
    {
        return (vertices[0] + vertices[1] + vertices[2]) / static_cast<Real>(3);
    }

    /**
     * Circumcenter which is the intersection between the perpendicular bisectors of the edges.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2<Real> circumcenter() const
    {
        const Segment2<Real> e0 = edge(0);
        const Segment2<Real> e1 = edge(1);
        // TODO: Why unnormalized?
        const Line2<Real> l0 { e0.midpoint(), e0.direction_unnormalized().arbitrary_perpendicular() };
        const Line2<Real> l1 { e1.midpoint(), e1.direction_unnormalized().arbitrary_perpendicular() };
        // TODO: Use checked and return optional.
        return l0.unchecked_intersection(l1);
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
    [[nodiscard]] Vector2<Real> incenter() const
    {
        // TODO: Use checked intersection and return optional.
        return angle_bisector(0).unchecked_intersection(angle_bisector(1));
    }

    /**
     * Orthocenter which is the intersection between the altitudes of the triangle.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> orthocenter() const
    {
        return Line2<Real>::from_segment(altitude(0)).unchecked_intersection(Line2<Real>::from_segment(altitude(1)));
    }

    /**
     * Area.
     * @return Result.
     */
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
    [[nodiscard]] Real angle(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const int next_index = (index + 1) % 3;
        const int prev_index = (index + 2) % 3;
        const Vector2<Real> dir1 = vertices[prev_index] - vertices[index];
        const Vector2<Real> dir2 = vertices[next_index] - vertices[index];
        return acos(dir1.dot(dir2) / (dir1.length() * dir2.length()));
    }

    /**
     * Perpendicular bisector of the interior angles in the order of the angle at vertex 0, 1, then 2.
     * The perpendicular bisector is a line that divides an interior angle evenly in half.
     * @param index Index of a vertex.
     * @return Result.
     */
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
    [[nodiscard]] Segment2<Real> altitude(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle2", index >= 0 && index <= 2);
        const Vector2<Real>& vertex = vertices[index];
        const Segment2<Real> base = edge((index + 1) % 3);
        const Vector2<Real> perp_dir = (base.end - base.start).arbitrary_perpendicular().normalize();
        const Line2<Real> altitude_line { vertex, perp_dir };
        // TODO: Use checked intersection and return optional.
        const Vector2<Real> intersection = altitude_line.unchecked_intersection(Line2<Real>::from_segment(base));
        return { vertex, intersection };
    }

    /**
     * A point that is the result of linearly interpolating between all vertices with given weights.
     * @param weights Weights.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector2<Real> lerp_point(const Vector3<Real>& weights) const
    {
        return weights.x * vertices[0] + weights.y * vertices[1] + weights.z * vertices[2];
    }

    /**
     * Barycentric coordinates of a point which is the weights for linearly interpolating between the vertices.
     * @param point Point.
     * @return Barycentric coordinates.
     */
    [[nodiscard]] constexpr Vector3<Real> barycentric(const Vector2<Real>& point) const
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
     * Circumcircle which is a circle that intersects all vertices.
     * @return Result.
     */
    [[nodiscard]] Circle2<Real> circumcircle() const
    {
        return Circle2<Real>::from_points_unchecked(vertices[0], vertices[1], vertices[2]);
    }

    /**
     * Incircle which is a circle inside the triangle and tangent to all edges.
     * @return Result.
     */
    [[nodiscard]] Circle2<Real> incircle() const
    {
        const Vector2<Real> center = incenter();
        return { center, edge(0).distance(center) };
    }

    /**
     * Determine if point is inside the triangle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] constexpr bool contains(const Vector2<Real>& point) const
    {
        const Vector3<Real> b = barycentric(point);
        // TODO: Use approx comparisons.
        return b.x >= static_cast<Real>(0) && b.x <= static_cast<Real>(1) && b.y >= static_cast<Real>(0)
            && b.y <= static_cast<Real>(1) && b.z >= static_cast<Real>(0) && b.z <= static_cast<Real>(1);
    }

    /**
     * Closest signed-distance to the edges of the triangle. Negative if inside, positive if outside.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
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
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
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
     * Closest distance to an arc. Zero if arc is inside the triangle.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        if (intersects(arc)) {
            return static_cast<Real>(0);
        }
        Real min_dist = std::numeric_limits<Real>::max();
        for (int i = 0; i < 3; ++i) {
            const Real dist = edge(i).distance(arc);
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
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to an aligned rectangle. Zero if aligned rectangle is inside triangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(line)) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(ray)) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> points;
        for (int i = 0; i < 3; ++i) {
            if (std::optional<Vector2<Real>> point = edge(i).intersection(segment)) {
                points.insert(*point);
            }
        }
        return points;
    }

    /**
     * Determine if intersects an arc. Being inside the triangle is an intersection.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        if (contains(arc.start)) {
            return true;
        }
        for (int i = 0; i < 3; ++i) {
            if (edge(i).intersects(arc)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Determine if intersects circle. Being inside the triangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
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
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
    {
        const auto depth_on_normal
            = [this, &circle](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
            Real tri_max = std::numeric_limits<Real>::lowest();
            for (const Vector2<Real>& v : vertices) {
                const Real proj = v.dot(normal);
                tri_max = max(tri_max, proj);
            }
            const Real circle_proj = circle.center.dot(normal) - circle.radius;
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
            Vector2<Real> closest;
            Real closest_dist_sqrd = std::numeric_limits<Real>::max();
            for (int i = 0; i < 3; ++i) {
                const Vector2<Real> proj = edge(i).project(circle.center);
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
    [[nodiscard]] bool intersects(const Triangle2& other) const
    {
        for (const Vector2<Real>& vertex : other.vertices) {
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
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2& other) const
    {
        const auto depth_on_normal
            = [this, &other](const Vector2<Real>& normal, float& min_overlap, Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : vertices) {
                const Real proj = v.dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Vector2<Real>& v : other.vertices) {
                const Real proj = v.dot(normal);
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
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with a rectangle.
     * @param rectangle Rectangle.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if equilateral which is where all edges have the same length.
     * @return Result.
     */
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
    [[nodiscard]] Triangle2 translate(const Vector2<Real>& offset) const
    {
        return { vertices[0].translate(offset), vertices[1].translate(offset), vertices[2].translate(offset) };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Triangle2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle) const
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
    [[nodiscard]] Triangle2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& factor) const
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
    [[nodiscard]] Triangle2 scale(const Vector2<Real>& factor) const
    {
        return { vertices[0].scale(factor), vertices[1].scale(factor), vertices[2].scale(factor) };
    }

    /**
     * Shear along the x-axis about an origin by a shear factor.
     * @param shear_origin Shear origin.
     * @param factor Y-Axis shear factor.
     * @return Result.
     */
    [[nodiscard]] Triangle2 shear_x_at(const Vector2<Real>& shear_origin, const Real factor) const
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
    [[nodiscard]] Triangle2 shear_x(const Real factor) const
    {
        return { vertices[0].shear_x(factor), vertices[1].shear_x(factor), vertices[2].shear_x(factor) };
    }

    /**
     * Shear along the y-axis about an origin by a shear factor.
     * @param shear_origin Shear origin.
     * @param factor X-Axis shear factor.
     * @return Result.
     */
    [[nodiscard]] Triangle2 shear_y_at(const Vector2<Real>& shear_origin, const Real factor) const
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
    [[nodiscard]] Triangle2 shear_y(const Real factor) const
    {
        return { vertices[0].shear_y(factor), vertices[1].shear_y(factor), vertices[2].shear_y(factor) };
    }

    /**
     * Determine if coincident with another triangle which is if the vertices of both triangle are
     * equal regardless of vertex order.
     * @param other Other triangle.
     * @return Result.
     */
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
    [[nodiscard]] constexpr bool operator==(const Triangle2& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    /**
     * Determine if any vertices are not exactly equal to another triangle's vertices.
     * @param other Other triangle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator!=(const Triangle2& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    /**
     * Lexicographical comparison in the order of the vertices.
     * @param other Other triangle.
     * @return Result.
     */
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
 * 2D rectangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Rectangle2 {
public:
    /**
     * Center.
     */
    Vector2<Real> center;

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
    constexpr Rectangle2()
        : center { Vector2<Real>::zero() }
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
    constexpr Rectangle2(const Vector2<Real>& center, const Vector2<Real>& size, const Real angle)
        : center { center }
        , size { size }
        , angle { angle }
    {
    }

    /**
     * Vertex in the negative x and negative y corner before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_nx_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center - half_size).rotate_at(center, angle);
    }

    /**
     * Vertex in the negative x and positive y corner before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_nx_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Vector2<Real> { center.x - half_size.x, center.y + half_size.y }.rotate_at(center, angle);
    }

    /**
     * Vertex in the positive x and negative y corner before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_px_ny() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return Vector2<Real> { center.x + half_size.x, center.y - half_size.y }.rotate_at(center, angle);
    }

    /**
     * Vertex in the positive x and positive y corner before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_px_py() const
    {
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return (center + half_size).rotate_at(center, angle);
    }

    /**
     * Edge in the negative x direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_nx() const
    {
        return { vertex_nx_ny(), vertex_nx_py() };
    }

    /**
     * Edge in the negative y direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_ny() const
    {
        return { vertex_nx_ny(), vertex_px_ny() };
    }

    /**
     * Edge in the positive x direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_px() const
    {
        return { vertex_px_ny(), vertex_px_py() };
    }

    /**
     * Edge in the positive y direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_py() const
    {
        return { vertex_nx_py(), vertex_px_py() };
    }

    /**
     * Normal of the edge in the negative x direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_nx() const
    {
        const Vector2<Real> dir = edge_nx().direction();
        return { -dir.y, dir.x };
    }

    /**
     * Normal of the edge in the negative y direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_ny() const
    {
        const Vector2<Real> dir = edge_ny().direction();
        return { dir.y, -dir.x };
    }

    /**
     * Normal of the edge in the positive x direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_px() const
    {
        const Vector2<Real> dir = edge_px().direction();
        return { dir.y, -dir.x };
    }

    /**
     * Normal of the edge in the positive y direction before rotation.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_py() const
    {
        const Vector2<Real> dir = edge_py().direction();
        return { -dir.y, dir.x };
    }

    /**
     * Area.
     * @return Area.
     */
    [[nodiscard]] constexpr Real area() const
    {
        return size.x * size.y;
    }

    /**
     * Perimeter which is the combined length of all edges.
     * @return Result.
     */
    [[nodiscard]] constexpr Real perimeter() const
    {
        return static_cast<Real>(2) * size.x + static_cast<Real>(2) * size.y;
    }

    /**
     * Determine if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        const Vector2<Real> local_point = point.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        return abs(local_point.x) <= half_size.x && abs(local_point.y) <= half_size.y;
    }

    /**
     * Closest signed distance to the edges of the rectangle. Negative if inside, positive if outside the rectangle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
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
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> local_point = point.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Vector2<Real> closest = local_point.clamp(-half_size, half_size);
        return local_point.distance(closest);
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
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
     * Closest distance to an arc. Zero if arc is inside the rectangle.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        if (contains(arc.start)) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(arc);
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
    [[nodiscard]] Real distance(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(segment);
                intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects an arc. Being inside the rectangle is an intersection.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        return contains(arc.start) || contains(arc.end()) || edge_nx().intersects(arc) || edge_ny().intersects(arc)
            || edge_px().intersects(arc) || edge_py().intersects(arc);
    }

    /**
     * Determine if intersects a circle.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
    {
        if (contains(circle.center)) {
            return true;
        }
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Circle2<Real> circle_local = circle.translate(-center).rotate(-angle);
        const Vector2<Real> closest = circle_local.center.clamp(-half_size, half_size);
        const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
        return dist_sqrd <= sqrd(circle.radius);
    }

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
    {
        const Circle2<Real> circle_local = circle.translate(-center).rotate(-angle);
        const Vector2<Real> half_size = size / static_cast<Real>(2);
        const Vector2<Real> closest = circle_local.center.clamp(-half_size, half_size);
        const Real dist_sqrd = circle_local.center.distance_sqrd(closest);
        if (dist_sqrd > sqrd(circle.radius)) {
            return std::nullopt;
        }
        const Vector2<Real> min_pos = -half_size - Vector2<Real>::all(circle.radius);
        const Vector2<Real> max_pos = half_size + Vector2<Real>::all(circle.radius);
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
            = [](const std::array<Vector2<Real>, 4>& rect_verts,
                 const std::array<Vector2<Real>, 3>& tri_verts,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real rect_max = std::numeric_limits<Real>::lowest();
            Real tri_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : rect_verts) {
                const Real proj = v.dot(normal);
                rect_max = max(rect_max, proj);
            }
            for (const Vector2<Real>& v : tri_verts) {
                const Real proj = v.dot(normal);
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
        const std::array<Vector2<Real>, 4> rect_verts
            = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 3> tri_verts
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
    [[nodiscard]] bool intersects(const Rectangle2& other) const
    {
        const std::array<Vector2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        for (const Vector2<Real>& vertex : vertices_other) {
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
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2& other) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& verts,
                 const std::array<Vector2<Real>, 4>& verts_other,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : verts) {
                const Real proj = v.dot(normal);
                this_max = max(this_max, proj);
            }
            for (const Vector2<Real>& v : verts_other) {
                const Real proj = v.dot(normal);
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
        const std::array<Vector2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 4> verts_other
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
    [[nodiscard]] bool intersects(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with an aligned rectangle.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2<Real>& rectangle) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] Rectangle2 translate(const Vector2<Real>& offset) const
    {
        return { center.translate(offset), size, angle };
    }

    /**
     * Rotate about an origin by an angle.
     * @param rotate_origin Rotation origin.
     * @param angle_ Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Rectangle2 rotate_at(const Vector2<Real>& rotate_origin, const Real angle_) const
    {
        return { center.rotate_at(rotate_origin, angle_), size, normalize_angle(angle + angle_) };
    }

    /**
     * Rotate about the origin by an angle.
     * @param angle_ Angle in radians.
     * @return Result.
     */
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
    [[nodiscard]] Rectangle2 scale_at(const Vector2<Real>& scale_origin, const Vector2<Real>& factor) const
    {
        return { center.scale_at(scale_origin, factor), size.scale(factor), angle };
    }

    /**
     * Scale about the origin by a factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] Rectangle2 scale(const Vector2<Real>& factor) const
    {
        return { center.scale(factor), size.scale(factor), angle };
    }

    /**
     * Determine if coincident which is if all vertices are equal regardless of their order.
     * @param other Other rectangle.
     * @return Result.
     */
    [[nodiscard]] bool coincident(const Rectangle2& other) const
    {
        const Vector2<Real> v1 = vertex_nx_ny();
        const Vector2<Real> v2 = vertex_nx_py();
        const Vector2<Real> v3 = vertex_px_ny();
        const Vector2<Real> v4 = vertex_px_py();
        std::array<Vector2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        const std::array<std::array<Vector2<Real>, 4>, 8> permutations {
            { { v1, v2, v3, v4 },
              { v2, v3, v4, v1 },
              { v3, v4, v1, v2 },
              { v4, v1, v2, v3 },
              { v4, v3, v2, v1 },
              { v3, v2, v1, v4 },
              { v2, v1, v4, v3 },
              { v1, v4, v3, v2 } }
        };
        for (const std::array<Vector2<Real>, 4> permutation : permutations) {
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
    [[nodiscard]] bool approx_equal(const Rectangle2& other) const
    {
        return center.approx_equal(other.center) && size.approx_equal(other.size)
            && nnm::approx_equal(angle, other.angle);
    }

    /**
     * Determine if all members are exactly equal with another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    [[nodiscard]] bool operator==(const Rectangle2& other) const
    {
        return center == other.center && size == other.size && angle == other.angle;
    }

    /**
     * Determine if any members are not exactly equal with another rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    [[nodiscard]] bool operator!=(const Rectangle2& other) const
    {
        return center != other.center || size != other.size || angle != other.angle;
    }

    /**
     * Lexicographical comparison in the order of center, size, the rotation angle.
     * @param other Other rectangle.
     * @return Result.
     */
    [[nodiscard]] bool operator<(const Rectangle2& other) const
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
 * 2D axis-aligned rectangle.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class AlignedRectangle2 {
public:
    /**
     * Minimum corner.
     */

    Vector2<Real> min;
    /**
     * Maximum corner.
     */
    Vector2<Real> max;

    /**
     * Default initialize to zero minimum and zero maximum.
     */
    constexpr AlignedRectangle2()
        : min { Vector2<Real>::zero() }
        , max { Vector2<Real>::zero() }
    {
    }

    /**
     * Initialize with minimum and maximum corners.
     * @param min Minimum corner.
     * @param max Maximum corner.
     */
    constexpr AlignedRectangle2(const Vector2<Real>& min, const Vector2<Real>& max)
        : min { min }
        , max { max }
    {
    }

    /**
     * Smallest aligned rectangle that contains two points.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    static constexpr AlignedRectangle2 from_bounding_points(const Vector2<Real>& point1, const Vector2<Real>& point2)
    {
        const Vector2<Real> min = { nnm::min(point1.x, point2.x), nnm::min(point1.y, point2.y) };
        const Vector2<Real> max = { nnm::max(point1.x, point2.x), nnm::max(point1.y, point2.y) };
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    static constexpr AlignedRectangle2 from_bounding_segment(const Segment2<Real>& segment)
    {
        return from_bounding_points(segment.start, segment.end);
    }

    /**
     * Smallest aligned rectangle that contains an arc.
     * @param arc Arc.
     * @return Result.
     */
    static AlignedRectangle2 from_bounding_arc(const Arc2<Real>& arc)
    {
        const Real half_pi = pi<float>() / static_cast<Real>(2);
        std::array<std::optional<Vector2<Real>>, 6> points {
            arc.start,
            arc.end(),
            arc.point_at(static_cast<Real>(0)),
            arc.point_at(half_pi),
            arc.point_at(pi<float>()),
            arc.point_at(-half_pi)
        };
        Vector2<Real> min { std::numeric_limits<Real>::max(), std::numeric_limits<Real>::max() };
        Vector2<Real> max { std::numeric_limits<Real>::lowest(), std::numeric_limits<Real>::lowest() };
        for (const std::optional<Vector2<Real>>& point : points) {
            if (!point.has_value()) {
                continue;
            }
            min.x = nnm::min(min.x, point->x);
            min.y = nnm::min(min.y, point->y);
            max.x = nnm::max(max.x, point->x);
            max.y = nnm::max(max.y, point->y);
        }
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a circle.
     * @param circle Circle.
     * @return Result.
     */
    static AlignedRectangle2 from_bounding_circle(const Circle2<Real>& circle)
    {
        const Vector2<Real> min = circle.center - Vector2<Real>::all(circle.radius);
        const Vector2<Real> max = circle.center + Vector2<Real>::all(circle.radius);
        return { min, max };
    }

    /**
     * Smallest aligned rectangle that contains a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    static AlignedRectangle2 from_bounding_triangle(const Triangle2<Real>& triangle)
    {
        Vector2<Real> min { std::numeric_limits<Real>::max(), std::numeric_limits<Real>::max() };
        Vector2<Real> max { std::numeric_limits<Real>::lowest(), std::numeric_limits<Real>::lowest() };
        for (const Vector2<Real>& v : triangle.vertices) {
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
    static AlignedRectangle2 from_bounding_rectangle(const Rectangle2<Real>& rectangle)
    {
        Vector2<Real> min { std::numeric_limits<Real>::max(), std::numeric_limits<Real>::max() };
        Vector2<Real> max { std::numeric_limits<Real>::lowest(), std::numeric_limits<Real>::lowest() };
        const std::array<Vector2<Real>, 4> vertices {
            rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py()
        };
        for (const Vector2<Real>& v : vertices) {
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
    [[nodiscard]] Vector2<Real> vertex_nx_ny() const
    {
        return min;
    }

    /**
     * Vertex in the negative x and positive y corner.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_nx_py() const
    {
        return { min.x, max.y };
    }

    /**
     * Vertex in the positive x and negative y corner.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_px_ny() const
    {
        return { max.x, min.y };
    }

    /**
     * Vertex in the positive x and positive y corner.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> vertex_px_py() const
    {
        return max;
    }

    /**
     * Edge in the negative x direction.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_nx() const
    {
        return { vertex_nx_ny(), vertex_nx_py() };
    }

    /**
     * Edge in the negative y direction.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_ny() const
    {
        return { vertex_nx_ny(), vertex_px_ny() };
    }

    /**
     * Edge in the positive x direction.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_px() const
    {
        return { vertex_px_ny(), vertex_px_py() };
    }

    /**
     * Edge in the positive y direction.
     * @return Result.
     */
    [[nodiscard]] Segment2<Real> edge_py() const
    {
        return { vertex_nx_py(), vertex_px_py() };
    }

    /**
     * Normal of the edge in the negative x direction.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_nx() const
    {
        return -Vector2<Real>::axis_x();
    }

    /**
     * Normal of the edge in the negative y direction.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_ny() const
    {
        return -Vector2<Real>::axis_y();
    }

    /**
     * Normal of the edge in the positive x direction.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_px() const
    {
        return Vector2<Real>::axis_x();
    }

    /**
     * Normal of the edge in the positive y direction.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> normal_py() const
    {
        return Vector2<Real>::axis_y();
    }

    /**
     * Size.
     * @return Result.
     */
    [[nodiscard]] Vector2<Real> size() const
    {
        return max - min;
    }

    /**
     * Area.
     * @return Result.
     */
    [[nodiscard]] Real area() const
    {
        const Vector2<Real> s = size();
        return s.x * s.y;
    }

    /**
     * Perimeter which is the combined length of all edges.
     * @return Result.
     */
    [[nodiscard]] Real perimeter() const
    {
        const Vector2<Real> s = size();
        return static_cast<Real>(2) * s.x + static_cast<Real>(2) * s.y;
    }

    /**
     * Determine if point is inside the rectangle.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] bool contains(const Vector2<Real>& point) const
    {
        return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
    }

    /**
     * Closest signed-distance of point to the rectangle's edges. Negative if inside, positive if outside.
     * @param point Point.
     * @return Result.
     */
    [[nodiscard]] Real signed_distance(const Vector2<Real>& point) const
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
    [[nodiscard]] Real distance(const Vector2<Real>& point) const
    {
        const Vector2<Real> closest = point.clamp(min, max);
        return point.distance(closest);
    }

    /**
     * Closest distance to a line.
     * @param line Line.
     * @return Result.
     */
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
     * Closest distance to an arc. Zero if the arc is inside the rectangle.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] Real distance(const Arc2<Real>& arc) const
    {
        if (contains(arc.start)) {
            return static_cast<Real>(0);
        }
        const std::array<Segment2<Real>, 4> edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        Real min_dist = std::numeric_limits<Real>::max();
        for (const Segment2<Real>& edge : edges) {
            const Real dist = edge.distance(arc);
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Line2<Real>& line) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(line); intersection.has_value()) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Ray2<Real>& ray) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(ray); intersection.has_value()) {
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
    [[nodiscard]] Intersections2<Real> edge_intersections(const Segment2<Real>& segment) const
    {
        Intersections2<Real> inters;
        const std::array edges { edge_nx(), edge_ny(), edge_px(), edge_py() };
        for (const Segment2<Real>& edge : edges) {
            if (const std::optional<Vector2<Real>> intersection = edge.intersection(segment);
                intersection.has_value()) {
                inters.insert(*intersection);
            }
        }
        return inters;
    }

    /**
     * Determine if intersects an arc. Being inside the rectangle is an intersection.
     * @param arc Arc.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Arc2<Real>& arc) const
    {
        return contains(arc.start) || contains(arc.end()) || edge_nx().intersects(arc) || edge_ny().intersects(arc)
            || edge_px().intersects(arc) || edge_py().intersects(arc);
    }

    /**
     * Determine if intersects a circle. Being inside the rectangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const
    {
        if (contains(circle.center)) {
            return true;
        }
        const Vector2<Real> closest = circle.center.clamp(min, max);
        const Real dist_sqrd = closest.distance_sqrd(circle.center);
        return dist_sqrd <= sqrd(circle.radius);
    }

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const
    {
        const Vector2<Real> closest = circle.center.clamp(min, max);
        const Real dist_sqrd = circle.center.distance_sqrd(closest);
        if (dist_sqrd > sqrd(circle.radius)) {
            return std::nullopt;
        }
        const Vector2<Real> min_pos = min - Vector2<Real>::all(circle.radius);
        const Vector2<Real> max_pos = max + Vector2<Real>::all(circle.radius);
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
     * @return Result, null if no intersection.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& rect_verts,
                 const std::array<Vector2<Real>, 3>& tri_verts,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real rect_max = std::numeric_limits<Real>::lowest();
            Real tri_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : rect_verts) {
                const Real proj = v.dot(normal);
                rect_max = nnm::max(rect_max, proj);
            }
            for (const Vector2<Real>& v : tri_verts) {
                const Real proj = v.dot(normal);
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
        const std::array<Vector2<Real>, 4> rect_verts
            = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 3> tri_verts
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
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const
    {
        const std::array<Vector2<Real>, 4> vertices_rect = {
            rectangle.vertex_nx_ny(), rectangle.vertex_nx_py(), rectangle.vertex_px_ny(), rectangle.vertex_px_py()
        };
        for (const Vector2<Real>& vertex : vertices_rect) {
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
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& verts,
                 const std::array<Vector2<Real>, 4>& verts_rect,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : verts) {
                const Real proj = v.dot(normal);
                this_max = nnm::max(this_max, proj);
            }
            for (const Vector2<Real>& v : verts_rect) {
                const Real proj = v.dot(normal);
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
        const std::array<Vector2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 4> verts_rect = {
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
    [[nodiscard]] bool intersects(const AlignedRectangle2& other) const
    {
        const std::array<Vector2<Real>, 4> vertices_other
            = { other.vertex_nx_ny(), other.vertex_nx_py(), other.vertex_px_ny(), other.vertex_px_py() };
        for (const Vector2<Real>& vertex : vertices_other) {
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
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const AlignedRectangle2& other) const
    {
        const auto depth_on_normal
            = [](const std::array<Vector2<Real>, 4>& verts,
                 const std::array<Vector2<Real>, 4>& verts_other,
                 const Vector2<Real>& normal,
                 float& min_overlap,
                 Vector2<Real>& min_normal) -> bool {
            Real this_max = std::numeric_limits<Real>::lowest();
            Real other_min = std::numeric_limits<Real>::max();
            for (const Vector2<Real>& v : verts) {
                const Real proj = v.dot(normal);
                this_max = nnm::max(this_max, proj);
            }
            for (const Vector2<Real>& v : verts_other) {
                const Real proj = v.dot(normal);
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
        const std::array<Vector2<Real>, 4> verts = { vertex_nx_ny(), vertex_nx_py(), vertex_px_ny(), vertex_px_py() };
        const std::array<Vector2<Real>, 4> verts_other
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
    [[nodiscard]] bool approx_equal(const AlignedRectangle2& rectangle) const
    {
        return min.approx_equal(rectangle.min) && max.approx_equal(rectangle.max);
    }

    /**
     * Determine if minimum and maximum corners are exactly equal with another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] bool operator==(const AlignedRectangle2& other) const
    {
        return min == other.min && max == other.max;
    }

    /**
     * Determine if either minimum or maximum corners are not exactly equal with another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return
     */
    [[nodiscard]] bool operator!=(const AlignedRectangle2& other) const
    {
        return min != other.min || max != other.max;
    }

    /**
     * Lexicographical comparison in the order of minimum then maximum.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    [[nodiscard]] bool operator<(const AlignedRectangle2& other) const
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
constexpr std::optional<Vector2<Real>> Line2<Real>::intersection(const Ray2<Real>& ray) const
{
    return ray.intersection(*this);
}

template <typename Real>
constexpr bool Line2<Real>::intersects(const Segment2<Real>& segment) const
{
    return segment.intersects(*this);
}

template <typename Real>
constexpr std::optional<Vector2<Real>> Line2<Real>::intersection(const Segment2<Real>& segment) const
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
Real Line2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
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
bool Line2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
Intersections2<Real> Line2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
}

template <typename Real>
bool Line2<Real>::tangent(const Arc2<Real>& arc) const
{
    return arc.tangent(*this);
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
constexpr std::optional<Vector2<Real>> Ray2<Real>::intersection(const Segment2<Real>& segment) const
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
Real Ray2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
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
bool Ray2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
Intersections2<Real> Ray2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
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
bool Ray2<Real>::tangent(const Arc2<Real>& arc) const
{
    return arc.tangent(*this);
}

template <typename Real>
Real Segment2<Real>::distance(const Arc2<Real>& arc) const
{
    return arc.distance(*this);
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
bool Segment2<Real>::intersects(const Arc2<Real>& arc) const
{
    return arc.intersects(*this);
}

template <typename Real>
Intersections2<Real> Segment2<Real>::intersections(const Arc2<Real>& arc) const
{
    return arc.intersections(*this);
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
bool Segment2<Real>::tangent(const Arc2<Real>& arc) const
{
    return arc.tangent(*this);
}

template <typename Real>
Real Arc2<Real>::distance(const Circle2<Real>& circle) const
{
    return circle.distance(*this);
}

template <typename Real>
Real Arc2<Real>::distance(const Triangle2<Real>& triangle) const
{
    return triangle.distance(*this);
}

template <typename Real>
Real Arc2<Real>::distance(const Rectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
Real Arc2<Real>::distance(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.distance(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const Circle2<Real>& circle) const
{
    return circle.intersects(*this);
}

template <typename Real>
Intersections2<Real> Arc2<Real>::edge_intersections(const Circle2<Real>& circle) const
{
    return circle.edge_intersections(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const Triangle2<Real>& triangle) const
{
    return triangle.intersects(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const Rectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
bool Arc2<Real>::intersects(const AlignedRectangle2<Real>& rectangle) const
{
    return rectangle.intersects(*this);
}

template <typename Real>
bool Arc2<Real>::tangent(const Circle2<Real>& circle) const
{
    return circle.tangent(*this);
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