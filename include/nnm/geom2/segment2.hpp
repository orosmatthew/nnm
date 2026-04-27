/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_SEGMENT2_HPP
#define NNM_GEOM2_SEGMENT2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>

namespace nnm {

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
    [[nodiscard]] constexpr bool collinear(const Line2<Real>& line) const;

    /**
     * Determine if collinear with 2D ray.
     * @param ray 2D ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray2<Real>& ray) const;

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
    [[nodiscard]] constexpr Real distance(const Line2<Real>& line) const;

    /**
     * Closest distance to ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

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
    [[nodiscard]] constexpr bool parallel(const Line2<Real>& line) const;

    /**
     * Determine if parallel with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Ray2<Real>& ray) const;

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
    [[nodiscard]] constexpr bool perpendicular(const Line2<Real>& line) const;

    /**
     * Determine if perpendicular with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool perpendicular(const Ray2<Real>& ray) const;

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
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const;

    /**
     * Intersection point with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Line2<Real>& line) const;

    /**
     * Determine if intersects ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const;

    /**
     * Intersection point with ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Ray2<Real>& ray) const;

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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Circle2<Real>& circle) const;

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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Triangle2<Real>& triangle) const;

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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Rectangle2<Real>& rectangle) const;

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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const AlignedRectangle2<Real>& rectangle) const;

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

} // namespace nnm

#endif
