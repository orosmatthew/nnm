/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_RAY2_HPP
#define NNM_GEOM2_RAY2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>

namespace nnm {

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
    [[nodiscard]] constexpr bool collinear(const Point2<Real>& point) const;

    /**
     * Determine if collinear with 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Line2<Real>& line) const;

    /**
     * Determine if collinear with another ray.
     * @param other Other ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool collinear(const Ray2& other) const;

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
    [[nodiscard]] Real distance(const Line2<Real>& line) const;

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
    [[nodiscard]] constexpr bool parallel(const Line2<Real>& line) const;

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
    [[nodiscard]] constexpr bool perpendicular(const Line2<Real>& line) const;

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
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const;

    /**
     * Intersection point with 2D line.
     * @param line 2D line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point2<Real>> intersection(const Line2<Real>& line) const;

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
     * Intersection points with 2D rectangle. If only single intersection, both returned points are equal.
     * @param rectangle 2D rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Rectangle2<Real>& rectangle) const;

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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const AlignedRectangle2<Real>& rectangle) const;

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

} // namespace nnm

#endif
