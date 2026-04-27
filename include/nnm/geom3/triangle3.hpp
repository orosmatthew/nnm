/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_TRIANGLE3_HPP
#define NNM_GEOM3_TRIANGLE3_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/plane.hpp>
#include <nnm/geom3/line3.hpp>
#include <nnm/geom3/segment3.hpp>

namespace nnm {

template <typename Real>
class Triangle3 {
public:

    /**
     * Vertices.
     */
    Point3<Real> vertices[3];

    /**
     * Default initialize all vertices to origin.
     */
    // tested
    constexpr Triangle3()
        : vertices { Point3<Real>::zero(), Point3<Real>::zero(), Point3<Real>::zero() }
    {
    }

    /**
     * Initialize with provided vertices.
     * @param vertex0 First vertex.
     * @param vertex1 Second vertex.
     * @param vertex2 Third vertex.
     */
    // tested
    constexpr Triangle3(const Point3<Real>& vertex0, const Point3<Real>& vertex1, const Point3<Real>& vertex2)
        : vertices { vertex0, vertex1, vertex2 }
    {
    }

    /**
     * Cast from other type.
     * @tparam Other Other type.
     * @param other Other triangle.
     */
    // tested
    template <typename Other>
    explicit constexpr Triangle3(const Triangle3<Other>& other)
        : vertices {
            Point3<Real> { other.vertices[0] }, Point3<Real> { other.vertices[1] }, Point3<Real> { other.vertices[2] }
        }
    {
    }

    // TODO: test
    [[nodiscard]] constexpr bool degenerate() const
    {
        return edge(0).parallel(edge(1));
    }

    /**
     * If all vertices are collinear, returns the line segment that represents the degenerate triangle.
     * @return Result.
     */
    // tested.
    [[nodiscard]] constexpr std::optional<Segment3<Real>> collapse_segment() const;

    /**
     * If all vertices are coincident, returns the point that represents the degenerate triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!vertices_coincident()) {
            return std::nullopt;
        }
        return vertices[0];
    }

    /**
     * Edge in the order of vertex 0 to 1, 1 to 2, then 2 to 0.
     * @param index Edge index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const;

    /**
     * Centroid which is the average between all vertices.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> centroid() const
    {
        return Point3<Real>::from_vector(
            (vertices[0].to_vector() + vertices[1].to_vector() + vertices[2].to_vector()) / static_cast<Real>(3));
    }

    /**
     * Circumcenter which is the intersection between the perpendicular bisectors of the edges.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point3<Real>> circumcenter() const;

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
    [[nodiscard]] std::optional<Point3<Real>> incenter() const
    {
        return angle_bisector(0).intersection(angle_bisector(1));
    }

    /**
     * Orthocenter which is the intersection between the altitudes of the triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point3<Real>> orthocenter() const;

    /**
     * Area.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real area() const
    {
        const Vector3<Real> dir01 = vertices[0].direction_unnormalized(vertices[1]);
        const Vector3<Real> dir02 = vertices[0].direction_unnormalized(vertices[2]);
        return dir01.cross(dir02).length() / static_cast<Real>(2);
    }

    /**
     * Median which is the line segment from a vertex to the midpoint of its opposite edge.
     * It is indexed in the order of vertex 0 to midpoint of edge 1, vertex 1 to midpoint of edge 2,
     * then vertex 2 to midpoint of edge 0.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> median(const uint8_t index) const;

    /**
     * Perpendicular bisector of an edge which is a line that divides an edge in half and
     * is perpendicular to the edge.
     * @param index Index of the edge.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Line3<Real>> perpendicular_bisector(const uint8_t index) const;

    /**
     * Interior angle at a vertex index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real angle(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Triangle3", index < 3);
        const uint8_t next_index = (index + 1) % 3;
        const uint8_t prev_index = (index + 2) % 3;
        const Vector3<Real> dir1 = vertices[prev_index] - vertices[index];
        const Vector3<Real> dir2 = vertices[next_index] - vertices[index];
        return acos(dir1.dot(dir2) / (dir1.length() * dir2.length()));
    }

    /**
     * Angle bisector of the angle at the vertex at an index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] Line3<Real> angle_bisector(const uint8_t index) const;

    /**
     * Altitude originating from the vertex at an index.
     * @param index Index.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Segment3<Real>> altitude(const uint8_t index) const;

    /**
     * Linearly interpolate between the vertices with weights.
     * This returns the point from its barycentric coordinates.
     * @param weights Interpolation weights.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> lerp_point(const Vector3<Real> weights) const
    {
        return Point3<Real>::from_vector(
            weights.x * vertices[0].to_vector() + weights.y * vertices[1].to_vector()
            + weights.z * vertices[2].to_vector());
    }

    /**
     * Barycentric coordinates of a point which is its interpolation weights relative to the triangle's vertices.
     * Containment within the triangle is not checked.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Vector3<Real> barycentric_unchecked(const Point3<Real>& point) const
    {
        const Real area_full = area();
        const Real area_p12 = Triangle3 { point, vertices[1], vertices[2] }.area();
        const Real area_0p2 = Triangle3 { vertices[0], point, vertices[2] }.area();
        const Real area_01p = Triangle3 { vertices[0], vertices[1], point }.area();
        return Vector3<Real> { area_p12 / area_full, area_0p2 / area_full, area_01p / area_full };
    }

    /**
     * Barycentric coordinates of a point which is its interpolation weights relative to the triangle's vertices.
     * Containment within the triangle is checked.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Vector3<Real>> barycentric(const Point3<Real>& point) const
    {
        if (!contains(point)) {
            return std::nullopt;
        }
        const Real area_full = area();
        if (approx_zero(area_full)) {
            return std::nullopt;
        }
        const Real area_p12 = Triangle3 { point, vertices[1], vertices[2] }.area();
        const Real area_0p2 = Triangle3 { vertices[0], point, vertices[2] }.area();
        const Real area_01p = Triangle3 { vertices[0], vertices[1], point }.area();
        return Vector3<Real> { area_p12 / area_full, area_0p2 / area_full, area_01p / area_full };
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const;

    /**
     * Determine if point is contained on the triangle when projected onto the plane coplanar to the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains_projected(const Point3<Real>& point) const
    {
        const Vector3<Real> n = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
        const auto edge_func = [&n](const Point3<Real>& a, const Point3<Real>& b, const Point3<Real>& p) -> Real {
            return n.dot((b - a).cross(p - a));
        };
        const Real e01 = edge_func(vertices[0], vertices[1], point);
        const Real e12 = edge_func(vertices[1], vertices[2], point);
        const Real e20 = edge_func(vertices[2], vertices[0], point);
        const bool cond1
            = approx_greater_equal_zero(e01) && approx_greater_equal_zero(e12) && approx_greater_equal_zero(e20);
        const bool cond2 = approx_less_equal_zero(e01) && approx_less_equal_zero(e12) && approx_less_equal_zero(e20);
        return cond1 || cond2;
    }

    // TODO: test
    [[nodiscard]] constexpr bool vertices_coincident() const
    {
        return vertices[0].approx_equal(vertices[1]) && vertices[0].approx_equal(vertices[2]);
    }

    /**
     * Determine if all vertices are collinear.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool vertices_collinear() const
    {
        return edge(0).parallel(edge(1));
    }

    /**
     * Determine if coplanar with a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Point3<Real>& point) const;

    /**
     * Determine if coplanar with line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Line3<Real>& line) const;

    /**
     * Determine if coplanar with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Ray3<Real>& ray) const;

    /**
     * Determine if coplanar with a segment.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool coplanar(const Segment3<Real>& segment) const;

    /**
     * Determine if coplanar with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool coplanar(const Plane<Real>& plane) const;

    /**
     * Project point onto the triangle.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> project(const Point3<Real>& point) const;

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        // Degenerates are handled by project method.
        return project(point).distance_sqrd(point);
    }

    /**
     * Closest distance squared to a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Line3<Real>& line) const;

    /**
     * Closest distance squared to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Ray3<Real>& ray) const;

    /**
     * Closest distance squared to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3<Real>& segment) const;

    /**
     * Closest distance squared to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Plane<Real>& plane) const;

    /**
     * Closest distance squared to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Triangle3& other) const
    {
        if (intersects(other)) {
            return static_cast<Real>(0);
        }
        return min(
            edge(0).distance_sqrd(other.edge(0)),
            edge(0).distance_sqrd(other.edge(1)),
            edge(0).distance_sqrd(other.edge(2)),
            edge(1).distance_sqrd(other.edge(1)),
            edge(1).distance_sqrd(other.edge(2)),
            edge(2).distance_sqrd(other.edge(2)));
    }

    /**
     * Closest distance squared to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance squared to an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const AlignedBox<Real>& box) const;

    /**
     * Closest distance squared to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Box<Real>& box) const;

    /**
     * Closest distance to a point. Zero if intersects.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to a line. Zero if intersects.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const;

    /**
     * Closest distance to a ray. Zero if intersects.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    /**
     * Closest distance to a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    /**
     * Closest distance to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Triangle3& other) const
    {
        return sqrt(distance_sqrd(other));
    }

    /**
     * Closest distance to a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Rectangle3<Real>& rectangle) const;

    /**
     * Closest distance to a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Sphere<Real>& sphere) const;

    /**
     * Closest distance to an aligned box.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const AlignedBox<Real>& box) const;

    /**
     * Closest distance to a box.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Box<Real>& box) const;

    /**
     * Determine if parallel with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool parallel(const Line3<Real>& line) const;

    [[nodiscard]] constexpr bool parallel(const Ray3<Real>& ray) const;

    [[nodiscard]] constexpr bool perpendicular(const Line3<Real>& line) const;

    [[nodiscard]] constexpr bool perpendicular(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Intersection point with a line. Returns null if coplanar intersection.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point3<Real>> intersection(const Line3<Real>& line) const;

    /**
     * Determine if intersects with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Intersection point with a ray. Returns null if coplanar intersection.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point3<Real>> intersection(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects with a line segment
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    /**
     * Intersection point with a line segment. Returns null if coplanar intersection.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Point3<Real>> intersection(const Segment3<Real>& segment) const;

    /**
     * Determine if intersects with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    /**
     * Intersection with a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Segment3<Real>> intersection(const Plane<Real>& plane) const;

    /**
     * Determine if intersects with another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle3& other) const
    {
        return intersects(other.edge(0)) || intersects(other.edge(1)) || intersects(other.edge(2))
            || other.intersects(edge(0)) || other.intersects(edge(1)) || other.intersects(edge(2));
    }

    /**
     * Intersection with another triangle.
     * If polygonal intersection exists, null is returned.
     * @param other Other triangle
     * @return Result.
     */
    // tested
    [[nodiscard]] std::optional<Segment3<Real>> intersection(const Triangle3& other) const;

    /**
     * Determine if coincident with another triangle.
     * This is done by checking if the vertices are approximately equal order independently.
     * @param other Other triangle.
     * @return Result.
     */
    [[nodiscard]] constexpr bool coincident(const Triangle3& other) const
    {
        constexpr std::array<std::array<uint8_t, 3>, 6> permutations {
            { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 2, 0, 1 }, { 1, 2, 0 }, { 2, 1, 0 } }
        };
        for (const std::array<uint8_t, 3> permutation : permutations) {
            bool match = true;
            for (uint8_t i = 0; i < 3; ++i) {
                if (!vertices[i].approx_equal(other.vertices[permutation[i]])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    }

    /**
     * Transform vertices about an origin by a basis.
     * @param origin Transform origin.
     * @param by Basis.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform_at(const Point3<Real>& origin, const Basis3<Real>& by) const
    {
        return { vertices[0].transform_at(origin, by),
                 vertices[1].transform_at(origin, by),
                 vertices[2].transform_at(origin, by) };
    }

    /**
     * Transform vertices about the global origin by a basis.
     * @param by Basis.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform(const Basis3<Real>& by) const
    {
        return { vertices[0].transform(by), vertices[1].transform(by), vertices[2].transform(by) };
    }

    /**
     * Transform vertices about an origin by a transformation matrix.
     * @param origin Transform origin.
     * @param by Transformation matrix.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Triangle3 transform_at(const Point3<Real>& origin, const Transform3<Real>& by) const
    {
        return { vertices[0].transform_at(origin, by, static_cast<Real>(1)),
                 vertices[1].transform_at(origin, by, static_cast<Real>(1)),
                 vertices[2].transform_at(origin, by, static_cast<Real>(1)) };
    }

    /**
     * Transform vertices about the global origin by a transformation matrix.
     * @param by Transformation matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Triangle3 transform(const Transform3<Real>& by) const
    {
        return { vertices[0].transform(by, static_cast<Real>(1)),
                 vertices[1].transform(by, static_cast<Real>(1)),
                 vertices[2].transform(by, static_cast<Real>(1)) };
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    constexpr Triangle3 translate(const Vector3<Real>& offset) const
    {
        return { vertices[0].translate(offset), vertices[1].translate(offset), vertices[2].translate(offset) };
    }

    /**
     * Scale about an origin.
     * @param scale_origin Scale origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 scale_at(const Point3<Real>& scale_origin, const Vector3<Real>& factor) const
    {
        return { vertices[0].scale_at(scale_origin, factor),
                 vertices[1].scale_at(scale_origin, factor),
                 vertices[2].scale_at(scale_origin, factor) };
    }

    /**
     * Scale about the global origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 scale(const Vector3<Real>& factor) const
    {
        return { vertices[0].scale(factor), vertices[1].scale(factor), vertices[2].scale(factor) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param rotate_origin Rotation origin.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    Triangle3 rotate_axis_angle_at(const Point3<Real>& rotate_origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { vertices[0].rotate_axis_angle_at(rotate_origin, axis, angle),
                 vertices[1].rotate_axis_angle_at(rotate_origin, axis, angle),
                 vertices[2].rotate_axis_angle_at(rotate_origin, axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    Triangle3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { vertices[0].rotate_axis_angle(axis, angle),
                 vertices[1].rotate_axis_angle(axis, angle),
                 vertices[2].rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param rotate_origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    constexpr Triangle3 rotate_quaternion_at(
        const Point3<Real>& rotate_origin, const Quaternion<Real>& quaternion) const
    {
        return { vertices[0].rotate_quaternion_at(rotate_origin, quaternion),
                 vertices[1].rotate_quaternion_at(rotate_origin, quaternion),
                 vertices[2].rotate_quaternion_at(rotate_origin, quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    constexpr Triangle3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { vertices[0].rotate_quaternion(quaternion),
                 vertices[1].rotate_quaternion(quaternion),
                 vertices[2].rotate_quaternion(quaternion) };
    }

    /**
     * Shear about an origin along the x-axis.
     * @param shear_origin Shear origin.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_x_at(const Point3<Real>& shear_origin, const Real factor_y, const Real factor_z) const
    {
        return { vertices[0].shear_x_at(shear_origin, factor_y, factor_z),
                 vertices[1].shear_x_at(shear_origin, factor_y, factor_z),
                 vertices[2].shear_x_at(shear_origin, factor_y, factor_z) };
    }

    /**
     * Shear about the global origin along the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return { vertices[0].shear_x(factor_y, factor_z),
                 vertices[1].shear_x(factor_y, factor_z),
                 vertices[2].shear_x(factor_y, factor_z) };
    }

    /**
     * Shear about an origin along the y-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return
     */
    // tested
    constexpr Triangle3 shear_y_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_z) const
    {
        return { vertices[0].shear_y_at(shear_origin, factor_x, factor_z),
                 vertices[1].shear_y_at(shear_origin, factor_x, factor_z),
                 vertices[2].shear_y_at(shear_origin, factor_x, factor_z) };
    }

    /**
     * Shear about the global origin along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return { vertices[0].shear_y(factor_x, factor_z),
                 vertices[1].shear_y(factor_x, factor_z),
                 vertices[2].shear_y(factor_x, factor_z) };
    }

    /**
     * Shear about an origin along the z-axis.
     * @param shear_origin Shear origin.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_z_at(const Point3<Real>& shear_origin, const Real factor_x, const Real factor_y) const
    {
        return { vertices[0].shear_z_at(shear_origin, factor_x, factor_y),
                 vertices[1].shear_z_at(shear_origin, factor_x, factor_y),
                 vertices[2].shear_z_at(shear_origin, factor_x, factor_y) };
    }

    /**
     * Shear about the global origin along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    // tested
    constexpr Triangle3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return { vertices[0].shear_z(factor_x, factor_y),
                 vertices[1].shear_z(factor_x, factor_y),
                 vertices[2].shear_z(factor_x, factor_y) };
    }

    /**
     * Determine if all vertices are approximately equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool approx_equal(const Triangle3& other) const
    {
        return vertices[0].approx_equal(other.vertices[0]) && vertices[1].approx_equal(other.vertices[1])
            && vertices[2].approx_equal(other.vertices[2]);
    }

    /**
     * Determine if all vertices are exactly equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator==(const Triangle3& other) const
    {
        return vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1] && vertices[2] == other.vertices[2];
    }

    /**
     * Determine if any vertices are not equal to another triangle.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator!=(const Triangle3& other) const
    {
        return vertices[0] != other.vertices[0] || vertices[1] != other.vertices[1] || vertices[2] != other.vertices[2];
    }

    /**
     * Lexicographical comparison in the order of vertices.
     * @param other Other triangle.
     * @return Result.
     */
    // tested
    constexpr bool operator<(const Triangle3& other) const
    {
        if (vertices[0] != other.vertices[0]) {
            return vertices[0] < other.vertices[0];
        }
        if (vertices[1] != other.vertices[1]) {
            return vertices[1] < other.vertices[1];
        }
        return vertices[2] < vertices[2];
    }
};

template <typename Real>
[[nodiscard]] constexpr std::optional<Segment3<Real>> Triangle3<Real>::collapse_segment() const
{
    if (!vertices_collinear()) {
        return std::nullopt;
    }
    const Real d01 = vertices[0].distance_sqrd(vertices[1]);
    const Real d02 = vertices[0].distance_sqrd(vertices[2]);
    const Real d12 = vertices[1].distance_sqrd(vertices[2]);
    if (approx_greater_equal(d01, d02) && approx_greater_equal(d01, d12)) {
        return Segment3<Real> { vertices[0], vertices[1] };
    }
    if (approx_greater_equal(d02, d01) && approx_greater_equal(d02, d12)) {
        return Segment3<Real> { vertices[0], vertices[2] };
    }
    return Segment3<Real> { vertices[1], vertices[2] };
}

template <typename Real>
[[nodiscard]] constexpr Segment3<Real> Triangle3<Real>::edge(const uint8_t index) const
{
    NNM_BOUNDS_CHECK_ASSERT("Triangle3<Real>", index < 3);
    const uint8_t next_index = (index + 1) % 3;
    return { vertices[index], vertices[next_index] };
}

template <typename Real>
[[nodiscard]] std::optional<Point3<Real>> Triangle3<Real>::circumcenter() const
{
    const std::optional<Line3<Real>> pb1 = perpendicular_bisector(0);
    if (!pb1.has_value()) {
        return std::nullopt;
    }
    const std::optional<Line3<Real>> pb2 = perpendicular_bisector(1);
    if (!pb2.has_value()) {
        return std::nullopt;
    }
    return pb1->intersection(*pb2);
}

template <typename Real>
[[nodiscard]] std::optional<Point3<Real>> Triangle3<Real>::orthocenter() const
{
    const std::optional<Segment3<Real>> alt0 = altitude(0);
    if (!alt0.has_value()) {
        return std::nullopt;
    }
    const std::optional<Segment3<Real>> alt1 = altitude(1);
    if (!alt1.has_value()) {
        return std::nullopt;
    }
    const std::optional<Line3<Real>> alt0_line = Line3<Real>::from_segment(*alt0);
    if (!alt0_line.has_value()) {
        return std::nullopt;
    }
    const std::optional<Line3<Real>> alt1_line = Line3<Real>::from_segment(*alt1);
    if (!alt1_line.has_value()) {
        return std::nullopt;
    }
    return alt0_line->intersection(*alt1_line);
}

template <typename Real>
[[nodiscard]] constexpr Segment3<Real> Triangle3<Real>::median(const uint8_t index) const
{
    NNM_BOUNDS_CHECK_ASSERT("Triangle3<Real>", index < 3);
    const uint8_t next_index = (index + 1) % 3;
    return { vertices[index], edge(next_index).midpoint() };
}

template <typename Real>
[[nodiscard]] std::optional<Line3<Real>> Triangle3<Real>::perpendicular_bisector(const uint8_t index) const
{
    NNM_BOUNDS_CHECK_ASSERT("Triangle3<Real>", index < 3);
    const std::optional<Plane<Real>> p = Plane<Real>::from_triangle(*this);
    if (!p.has_value()) {
        return std::nullopt;
    }
    const Segment3<Real> e = edge(index);
    const std::optional<Line3<Real>> e_line = Line3<Real>::from_segment(e);
    if (!e_line.has_value()) {
        return std::nullopt;
    }
    const Vector3<Real> dir = e_line->perpendicular_plane_parallel(*p).direction;
    return Line3<Real> { e.midpoint(), dir };
}

template <typename Real>
[[nodiscard]] Line3<Real> Triangle3<Real>::angle_bisector(const uint8_t index) const
{
    NNM_BOUNDS_CHECK_ASSERT("Triangle3<Real>", index < 3);
    const uint8_t next_index = (index + 1) % 3;
    const uint8_t prev_index = (index + 2) % 3;
    const Vector3<Real> dir1 = (vertices[prev_index] - vertices[index]).normalize();
    const Vector3<Real> dir2 = (vertices[next_index] - vertices[index]).normalize();
    const Vector3<Real> bisector_dir = (dir1 + dir2).normalize();
    return { vertices[index], bisector_dir };
}

template <typename Real>
[[nodiscard]] std::optional<Segment3<Real>> Triangle3<Real>::altitude(const uint8_t index) const
{
    NNM_BOUNDS_CHECK_ASSERT("Triangle3<Real>", index < 3);
    const Point3<Real>& vertex = vertices[index];
    const uint8_t next_index = (index + 1) % 3;
    const std::optional<Line3<Real>> base_line = Line3<Real>::from_segment(edge(next_index));
    if (!base_line.has_value()) {
        return std::nullopt;
    }
    const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
    if (!plane.has_value()) {
        return std::nullopt;
    }
    const Vector3<Real> perp_dir = base_line->perpendicular_plane_parallel(*plane).direction;
    const Line3<Real> altitude_line { vertex, perp_dir };
    const std::optional<Point3<Real>> intersection = altitude_line.intersection(*base_line);
    if (!intersection.has_value()) {
        return std::nullopt;
    }
    return Segment3<Real> { vertex, *intersection };
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::contains(const Point3<Real>& point) const
{
    if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return degen_point->approx_equal(point);
    }
    if (const std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->contains(point);
    }
    const Vector3<Real> normal = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
    const Vector3<Real> diff = point - vertices[0];
    if (!normal.perpendicular(diff)) {
        return false;
    }
    return contains_projected(point);
}

template <typename Real>
[[nodiscard]] bool Triangle3<Real>::coplanar(const Point3<Real>& point) const
{
    const std::optional<Plane<Real>> plane = Plane<Real>::from_triangle(*this);
    if (!plane.has_value()) {
        return true;
    }
    return plane->contains(point);
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::coplanar(const Line3<Real>& line) const
{
    return edge(0).coplanar(line) && edge(1).coplanar(line);
}

template <typename Real>
[[nodiscard]] bool Triangle3<Real>::coplanar(const Ray3<Real>& ray) const
{
    return coplanar(Line3<Real>::from_ray(ray));
}

template <typename Real>
[[nodiscard]] constexpr bool Triangle3<Real>::coplanar(const Segment3<Real>& segment) const
{
    if (collapse_point().has_value()) {
        return true;
    }
    if (std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->coplanar(segment);
    }
    return edge(0).coplanar(segment) && edge(1).coplanar(segment);
}

template <typename Real>
[[nodiscard]] bool Triangle3<Real>::coplanar(const Plane<Real>& plane) const
{
    const std::optional<Plane<Real>> p = Plane<Real>::from_triangle(*this);
    if (!p.has_value()) {
        for (uint8_t i = 0; i < 3; ++i) {
            if (!edge(i).coplanar(plane)) {
                return false;
            }
        }
        return true;
    }
    return p->coplanar(plane);
}

template <typename Real>
[[nodiscard]] constexpr Point3<Real> Triangle3<Real>::project(const Point3<Real>& point) const
{
    if (const std::optional<Point3<Real>> degen_point = collapse_point(); degen_point.has_value()) {
        return *degen_point;
    }
    if (const std::optional<Segment3<Real>> degen_segment = collapse_segment(); degen_segment.has_value()) {
        return degen_segment->project(point);
    }
    if (!contains_projected(point)) {
        const Real e0_dist = edge(0).distance_sqrd(point);
        const Real e1_dist = edge(1).distance_sqrd(point);
        const Real e2_dist = edge(2).distance_sqrd(point);
        if (e0_dist < e1_dist && e0_dist < e2_dist) {
            return edge(0).project(point);
        }
        if (e1_dist < e0_dist && e1_dist < e2_dist) {
            return edge(1).project(point);
        }
        return edge(2).project(point);
    }
    const Vector3<Real> diff = point - vertices[0];
    const Vector3<Real> normal = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
    const Real dist = diff.dot(normal) / normal.dot(normal);
    return point - normal * dist;
}

template <typename Real>
Plane<Real> Plane<Real>::from_triangle_unchecked(const Triangle3<Real>& triangle)
{
    return from_points_unchecked(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
}

template <typename Real>
std::optional<Plane<Real>> Plane<Real>::from_triangle(const Triangle3<Real>& triangle)
{
    return from_points(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
}

} // namespace nnm

#endif
