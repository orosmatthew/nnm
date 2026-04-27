/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_RECTANGLE2_HPP
#define NNM_GEOM2_RECTANGLE2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>

namespace nnm {

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
    [[nodiscard]] Segment2<Real> edge_nx() const;

    /**
     * Edge in the negative y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_ny() const;

    /**
     * Edge in the positive x direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_px() const;

    /**
     * Edge in the positive y direction before rotation.
     * @return Result.
     */
    // tested
    [[nodiscard]] Segment2<Real> edge_py() const;

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
    [[nodiscard]] Real signed_distance(const Point2<Real>& point) const;

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
    [[nodiscard]] Real distance(const Line2<Real>& line) const;

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    /**
     * Closest distance to a line segment. Zero if line segment is inside the rectangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

    /**
     * Closest distance to a circle. Zero if circle is inside the rectangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

    /**
     * Closest distance to a triangle. Zero if triangle is inside the rectangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle2<Real>& triangle) const;

    /**
     * Closest distance to another rectangle. Zero if other rectangle is inside of this rectangle.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle2& other) const;

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
    [[nodiscard]] bool intersects(const Line2<Real>& line) const;

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
     * Determine if intersects a line segment. Being inside the rectangle is an intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Segment2<Real>& segment) const;

    /**
     * Intersection points with a line segment. If only single intersection, both returned points are equal.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects a circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const;

    /**
     * Determine if intersects a triangle. Being inside the rectangle is an intersection.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle2<Real>& triangle) const;

    /**
     * Intersect depth with a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Triangle2<Real>& triangle) const;

    /**
     * Determine if intersects another rectangle. Being inside this rectangle is an intersection.
     * @param other Other rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Rectangle2& other) const;

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

} // namespace nnm

#endif
