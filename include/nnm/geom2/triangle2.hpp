/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_TRIANGLE2_HPP
#define NNM_GEOM2_TRIANGLE2_HPP

#include <nnm/geom2/forward.hpp>
#include <nnm/nnm.hpp>
#include <array>
#include <nnm/geom2/line2.hpp>
#include <nnm/geom2/segment2.hpp>
#include <nnm/geom2/circle2.hpp>

namespace nnm {

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
        : vertices {
            Point2<Real> { other.vertices[0] }, Point2<Real> { other.vertices[1] }, Point2<Real> { other.vertices[2] }
        }
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
        NNM_BOUNDS_CHECK_ASSERT("Triangle2<Real>", index >= 0 && index <= 2);
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
        NNM_BOUNDS_CHECK_ASSERT("Triangle2<Real>", index >= 0 && index <= 2);
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
        NNM_BOUNDS_CHECK_ASSERT("Triangle2<Real>", index >= 0 && index <= 2);
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
        NNM_BOUNDS_CHECK_ASSERT("Triangle2<Real>", index >= 0 && index <= 2);
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
        NNM_BOUNDS_CHECK_ASSERT("Triangle2<Real>", index >= 0 && index <= 2);
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
            weights.x * vertices[0].to_vector() + weights.y * vertices[1].to_vector()
            + weights.z * vertices[2].to_vector());
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
    [[nodiscard]] Real distance(const Line2<Real>& line) const;

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray2<Real>& ray) const;

    /**
     * Closest distance to a line segment. Zero if segment is inside triangle.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment2<Real>& segment) const;

    /**
     * Closest distance to a circle. Zero if circle is inside triangle.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Circle2<Real>& circle) const;

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
    [[nodiscard]] constexpr bool intersects(const Line2<Real>& line) const;

    /**
     * Intersection points with a line. If only single intersection, both returned points are equal.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Line2<Real>& line) const;

    /**
     * Determine if intersects with a ray.
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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Ray2<Real>& ray) const;

    /**
     * Determine if intersects a line segment. Being inside the triangle is considered an intersection.
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
    [[nodiscard]] PointSet<Point2<Real>, 2> edge_intersections(const Segment2<Real>& segment) const;

    /**
     * Determine if intersects circle. Being inside the triangle is an intersection.
     * @param circle Circle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Circle2<Real>& circle) const;

    /**
     * Intersect depth with a circle.
     * @param circle Circle.
     * @return Result, null if no intersection.
     */
    // tested
    [[nodiscard]] std::optional<Vector2<Real>> intersect_depth(const Circle2<Real>& circle) const;

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

} // namespace nnm

#endif
