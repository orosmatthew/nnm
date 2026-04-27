/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_CIRCLE2_HPP
#define NNM_GEOM2_CIRCLE2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>
#include <nnm/geom2/line2.hpp>
#include <nnm/geom2/segment2.hpp>

namespace nnm {

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
        return Circle2<Real> { center, radius };
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
        return Circle2<Real> { center.value(), radius };
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
    [[nodiscard]] Real distance(const Line2<Real>& line) const;

    /**
     * Closest distance to ray. Zero if intersects or is inside circle.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    /**
     * Closest distance to segment. Zero if intersects or is inside circle.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

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
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const;

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Line2<Real>& line) const;

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Ray2<Real>& ray) const;

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Ray2<Real>& ray) const;

    /**
     * Determine if intersects segment. Being inside the circle is considered an intersection.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const;

    /**
     * Intersection points with a segment. If only single intersection, both returned points are equal.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Segment2<Real>& segment) const;

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
    [[nodiscard]] constexpr bool tangent(const Line2<Real>& line) const;

    /**
     * Determine if tangent to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Ray2<Real>& ray) const;

    /**
     * Determine if tangent to a segment.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool tangent(const Segment2<Real>& segment) const;

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

} // namespace nnm

#endif
