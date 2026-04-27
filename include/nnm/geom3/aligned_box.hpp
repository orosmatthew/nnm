/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_ALIGNEDBOX_HPP
#define NNM_GEOM3_ALIGNEDBOX_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/rectangle3.hpp>
#include <nnm/geom3/segment3.hpp>

namespace nnm {

template <typename Real>
class AlignedBox {
public:

    /**
     * Minimum corner point.
     */
    Point3<Real> min;

    /**
     * Maximum corner point.
     */
    Point3<Real> max;

    /**
     * Default initialize with zero min and max.
     */
    // tested
    constexpr AlignedBox()
        : min { Point3<Real>::zero() }
        , max { Point3<Real>::zero() }
    {
    }

    /**
     * Initialize with min and max. No validation to ensure min/max is done.
     * Use from_bounding_points if validation is desired.
     * @param min Minimum corner point.
     * @param max Maximum corner point.
     */
    // tested
    constexpr AlignedBox(const Point3<Real>& min, const Point3<Real>& max)
        : min { min }
        , max { max }
    {
    }

    /**
     * The smallest bounding box containing two points.
     * @param point1 First point.
     * @param point2 Second point.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_points(const Point3<Real>& point1, const Point3<Real>& point2)
    {
        AlignedBox box { point1, point1 };
        box = box.extend_bounding(point2);
        return box;
    }

    /**
     * The smallest bounding box containing a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_segment(const Segment3<Real>& segment);

    /**
     * The smallest bounding box containing a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_triangle(const Triangle3<Real>& triangle);

    /**
     * The smallest bounding box containing a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_rectangle(const Rectangle3<Real>& rectangle);

    /**
     * The smallest bounding box containing a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    static constexpr AlignedBox from_bounding_sphere(const Sphere<Real>& sphere);

    /**
     * If min and max are parallel with the xy, xz, or yz planes,
     * then returns the rectangle that represents the degenerate aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Rectangle3<Real>> collapse_rectangle() const;

    /**
     * If min and max are parallel with the x, y, or z axes,
     * then return the line segment that represents the degenerate aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Segment3<Real>> collapse_segment() const;

    /**
     * If min and and max are equal, then return the point that represents the degenerate aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<Point3<Real>> collapse_point() const
    {
        if (!min.approx_equal(max)) {
            return std::nullopt;
        }
        return min;
    }

    /**
     * Vertex at an index.
     * @param index Index from 0-7.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("AlignedBox", index < 8);
        switch (index) {
        case 0: // -x -y -z
            return min;
        case 1: // -x -y +z
            return { min.x, min.y, max.z };
        case 2: // -x +y -z
            return { min.x, max.y, min.z };
        case 3: // -x +y +z
            return { min.x, max.y, max.z };
        case 4: // +x -y -z
            return { max.x, min.y, min.z };
        case 5: // +x -y +z
            return { max.x, min.y, max.z };
        case 6: // +x +y -z
            return { max.x, max.y, min.z };
        default: // +x +y +z
            return max;
        }
    }

    /**
     * Edge at an index.
     * @param index Index from 0-11.
     * @return Result.
     */
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const;

    /**
     * Face at an index.
     * @param index Index from [0-5].
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Rectangle3<Real> face(const uint8_t index) const;

    /**
     * Size.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Vector3<Real> size() const
    {
        return max - min;
    }

    /**
     * Volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real volume() const
    {
        const Vector3<Real> s = size();
        return s.x * s.y * s.z;
    }

    /**
     * Surface area.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real surface_area() const
    {
        const Vector3<Real> s = size();
        return static_cast<Real>(2) * (s.x * s.y + s.x * s.z + s.y * s.z);
    }

    /**
     * Extend box to fit a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox extend_bounding(const Point3<Real>& point) const
    {
        return { { nnm::min(min.x, point.x), nnm::min(min.y, point.y), nnm::min(min.z, point.z) },
                 { nnm::max(max.x, point.x), nnm::max(max.y, point.y), nnm::max(max.z, point.z) } };
    }

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        return approx_greater_equal(point.x, min.x) && approx_less_equal(point.x, max.x)
            && approx_greater_equal(point.y, min.y) && approx_less_equal(point.y, max.y)
            && approx_greater_equal(point.z, min.z) && approx_less_equal(point.z, max.z);
    }

    /**
     * Center by volume.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> center() const
    {
        return Point3<Real>::from_vector((min.to_vector() + max.to_vector()) / static_cast<Real>(2));
    }

    /**
     * Closest distance squared to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Point3<Real>& point) const
    {
        const Point3<Real> closest = point.clamp(min, max);
        return closest.distance_sqrd(point);
    }

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Line3<Real>& line) const;

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Ray3<Real>& ray) const;

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Segment3<Real>& segment) const;

    // TODO: test
    [[nodiscard]] constexpr Real distance_sqrd(const Plane<Real>& plane) const;

    /**
     * Closest distance squared to a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance_sqrd(const Triangle3<Real>& triangle) const;

    /**
     * Closest distance to a point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Point3<Real>& point) const
    {
        return sqrt(distance_sqrd(point));
    }

    /**
     * Closest distance to a line. Zero if intersecting.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Line3<Real>& line) const;

    /**
     * Closest distance to a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] Real distance(const Ray3<Real>& ray) const;

    // TODO: test
    [[nodiscard]] Real distance(const Segment3<Real>& segment) const;

    /**
     * Closest distance to a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Real distance(const Plane<Real>& plane) const;

    // TODO: test
    [[nodiscard]] Real distance(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Line3<Real>& line) const;

    /**
     * Determine if intersects a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Ray3<Real>& ray) const;

    /**
     * Determine if intersects a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Segment3<Real>& segment) const;

    /**
     * Determine if intersects a plane.
     * @param plane Plane.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Plane<Real>& plane) const;

    /**
     * Determine if intersects a triangle.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] bool intersects(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects a sphere.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const;

    /**
     * Determine if intersects another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedBox& other) const
    {
        return approx_less_equal(min.x, other.max.x) && approx_less_equal(other.min.x, max.x)
            && approx_less_equal(min.y, other.max.y) && approx_less_equal(other.min.y, max.y)
            && approx_less_equal(min.z, other.max.z) && approx_less_equal(other.min.z, max.z);
    }

    /**
     * Surface intersection points with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Line3<Real>& line) const;

    /**
     * Surface intersection points with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Ray3<Real>& ray) const;

    /**
     * Surface intersection points with a line segment.
     * @param segment Line segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Segment3<Real>& segment) const;

    /**
     * Aligned box formed by the intersection with another aligned box. Null if no intersection.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr std::optional<AlignedBox> intersection(const AlignedBox& other) const
    {
        const AlignedBox inter {
            { nnm::max(min.x, other.min.x), nnm::max(min.y, other.min.y), nnm::max(min.z, other.min.z) },
            { nnm::min(max.x, other.max.x), nnm::min(max.y, other.max.y), nnm::min(max.z, other.max.z) }
        };
        if (!inter.valid()) {
            return std::nullopt;
        }
        return inter;
    }

    /**
     * Determine if valid. The aligned box is valid if each component of the 'min' is
     * less than or equal to each corresponding component of 'max'.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool valid() const
    {
        return approx_less_equal(min.x, max.x) && approx_less_equal(min.y, max.y) && approx_less_equal(min.z, max.z);
    }

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox translate(const Vector3<Real>& offset) const
    {
        return { min.translate(offset), max.translate(offset) };
    }

    /**
     * Rotate about an origin by an axis and angle.
     * @param origin Rotation origin.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] AlignedBox rotate_axis_angle_at(
        const Point3<Real>& origin, const Vector3<Real>& axis, const Real angle) const
    {
        return { min.rotate_axis_angle_at(origin, axis, angle), max.rotate_axis_angle_at(origin, axis, angle) };
    }

    /**
     * Rotate about the global origin by an axis and angle.
     * @param axis Normalized rotation axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    // tested
    [[nodiscard]] AlignedBox rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return { min.rotate_axis_angle(axis, angle), max.rotate_axis_angle(axis, angle) };
    }

    /**
     * Rotate about an origin by a quaternion.
     * @param origin Rotation origin.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox rotate_quaternion_at(
        const Point3<Real>& origin, const Quaternion<Real>& quaternion) const
    {
        return { min.rotate_quaternion_at(origin, quaternion), max.rotate_quaternion_at(origin, quaternion) };
    }

    /**
     * Rotate about the global origin by a quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return { min.rotate_quaternion(quaternion), max.rotate_quaternion(quaternion) };
    }

    /**
     * Scale about an origin by a factor.
     * @param origin Scaling origin.
     * @param factor Scale factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox scale_at(const Point3<Real>& origin, const Vector3<Real>& factor) const
    {
        return { min.scale_at(origin, factor), max.scale_at(origin, factor) };
    }

    /**
     * Scale about the global origin by a factor.
     * @param factor Scaling factor.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr AlignedBox scale(const Vector3<Real>& factor) const
    {
        return { min.scale(factor), max.scale(factor) };
    }

    /**
     * Determine min and max are approximately equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const AlignedBox& other) const
    {
        return min.approx_equal(other.min) && max.approx_equal(other.max);
    }

    /**
     * Determine if min and max are exactly equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const AlignedBox& other) const
    {
        return min == other.min && max == other.max;
    }

    /**
     * Determine if min and max are not exactly equal to another aligned box.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const AlignedBox& other) const
    {
        return min != other.min || max != other.max;
    }

    /**
     * Lexicographical comparison in the order of min then max.
     * @param other Other aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator<(const AlignedBox& other) const
    {
        if (min != other.min) {
            return min < other.min;
        }
        return max < other.max;
    }
};

} // namespace nnm

#endif
