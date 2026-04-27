/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_ALIGNEDRECTANGLE2_HPP
#define NNM_GEOM2_ALIGNEDRECTANGLE2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>
#include <nnm/geom2/circle2.hpp>
#include <nnm/geom2/rectangle2.hpp>
#include <nnm/geom2/segment2.hpp>
#include <nnm/geom2/triangle2.hpp>

namespace nnm {

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
    [[nodiscard]] Real distance(const Line2<Real>& line) const;

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    /**
     * Closest distance to a line segment. Zero if the line segment is inside the rectangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

    /**
     * Closest distance to a circle. Zero if the circle is inside the rectangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    /**
     * Closest distance to a triangle. Zero if the triangle is inside the rectangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to a non-aligned rectangle. Zero if the non-aligned rectangle is inside this rectangle.
     * @param rectangle Non-aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2<Real>& rectangle) const;

    /**
     * Closest distance to another aligned rectangle. Zero if other rectangle is inside this rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedRectangle2& other) const;

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
    [[nodiscard]] constexpr PointSet<Point2<Real>, 2> edge_intersections(const Line2<Real>& line) const;

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray2<Real>& ray) const;

    /**
     * Intersection points with a ray. If only single intersection, both returned points are equal.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point2<Real>, 2> edge_intersections(const Ray2<Real>& ray) const;

    /**
     * Determine if intersects a line segment. Being inside the rectangle is an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment2<Real>& segment) const;

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point2<Real>, 2> edge_intersections(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects a circle. Being inside the rectangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const;

    /**
     * Determine if intersects a triangle. Being in the rectangle is an intersection.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersect depth with a triangle.
     * @param triangle Triangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects a non-aligned rectangle. Being inside this rectangle is an intersection.
     * @param rectangle Aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2<Real>& rectangle) const;

    /**
     * Intersect depth with a non-aligned rectangle.
     * @param rectangle Non-aligned rectangle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Rectangle2<Real>& rectangle) const;

    /**
     * Determine if intersects another aligned rectangle.
     * @param other Other aligned rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedRectangle2& other) const;

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

} // namespace nnm

#endif
