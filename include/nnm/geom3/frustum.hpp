/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_FRUSTUM_HPP
#define NNM_GEOM3_FRUSTUM_HPP

#include <nnm/geom3/forward.hpp>
#include <nnm/nnm.hpp>
#include <algorithm>
#include <array>
#include <nnm/geom3/aligned_box.hpp>

namespace nnm {

template <typename Real>
class Frustum {
public:

    /**
     * Near plane with normal pointing inward.
     */
    Plane<Real> near_plane;

    /**
     * Far plane with normal pointing inward.
     */
    Plane<Real> far_plane;

    /**
     * Left plane with normal pointing inward.
     */
    Plane<Real> left_plane;

    /**
     * Right plane with normal pointing inward.
     */
    Plane<Real> right_plane;

    /**
     * Bottom plane with normal pointing inward.
     */
    Plane<Real> bottom_plane;

    /**
     * Top plane with normal pointing inward.
     */
    Plane<Real> top_plane;

    /**
     * Default initialize with all planes being default initialized.
     * This is an invalid view frustum.
     */
    // tested
    constexpr Frustum();

    /**
     * Initialize with 6 planes.
     * All normals must be pointing inwards.
     * @param near_plane Near plane with inward pointing normal.
     * @param far_plane Far plane with inward pointing normal.
     * @param left_plane Left plane with inward pointing normal.
     * @param right_plane Right plane with inward pointing normal.
     * @param bottom_plane Bottom plane with inward pointing normal.
     * @param top_plane Top plane with inward pointing normal.
     */
    // tested
    constexpr Frustum(
        const Plane<Real> near_plane,
        const Plane<Real> far_plane,
        const Plane<Real> left_plane,
        const Plane<Real> right_plane,
        const Plane<Real> bottom_plane,
        const Plane<Real> top_plane);

    /**
     * Create view frustum based on camera parameters in a left-handed coordinate system.
     * @param position Position of the camera.
     * @param forward Normalized vector pointing in the forward direction of the camera.
     * @param up Normalized vector that represents the up direction for the coordinate system.
     * @param fov Vertical field-of-view in radians.
     * @param aspect Aspect ratio (width/height).
     * @param near Near distance.
     * @param far Far distance.
     * @return Result.
     */
    // tested
    static Frustum from_camera_left_hand(
        const Point3<Real>& position,
        const Vector3<Real>& forward,
        const Vector3<Real>& up,
        const Real fov,
        const Real aspect,
        const Real near,
        const Real far);

    /**
     * Create view frustum based on camera parameters in a right-handed coordinate system.
     * @param position Position of the camera.
     * @param forward Normalized vector pointing in the forward direction of the camera.
     * @param up Normalized vector that represents the up direction for the coordinate system.
     * @param fov Vertical field-of-view in radians.
     * @param aspect Aspect ratio (width/height).
     * @param near Near distance.
     * @param far Far distance.
     * @return Result.
     */
    // tested
    static Frustum from_camera_right_hand(
        const Point3<Real>& position,
        const Vector3<Real>& forward,
        const Vector3<Real>& up,
        const Real fov,
        const Real aspect,
        const Real near,
        const Real far);

    /**
     * Vertex at an index.
     * @param index Index [0-7] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Point3<Real> vertex(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Frustum", index < 8);
        switch (index) {
        case 0: // near-left-bottom
            return near_plane.intersection(left_plane, bottom_plane).value();
        case 1: // near-left-top
            return near_plane.intersection(left_plane, top_plane).value();
        case 2: // near-right-bottom
            return near_plane.intersection(right_plane, bottom_plane).value();
        case 3: // near-right-top
            return near_plane.intersection(right_plane, top_plane).value();
        case 4: // far-left-bottom
            return far_plane.intersection(left_plane, bottom_plane).value();
        case 5: // far-left-top
            return far_plane.intersection(left_plane, top_plane).value();
        case 6: // far-right-bottom
            return far_plane.intersection(right_plane, bottom_plane).value();
        case 7: // far-right-top
        default:
            return far_plane.intersection(right_plane, top_plane).value();
        }
    }

    /**
     * Edge at an index.
     * @param index Index [0-11] inclusive.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const;

    /**
     * Determine if contains point.
     * @param point Point.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool contains(const Point3<Real>& point) const
    {
        return approx_greater_equal_zero(near_plane.signed_distance(point))
            && approx_greater_equal_zero(far_plane.signed_distance(point))
            && approx_greater_equal_zero(left_plane.signed_distance(point))
            && approx_greater_equal_zero(right_plane.signed_distance(point))
            && approx_greater_equal_zero(bottom_plane.signed_distance(point))
            && approx_greater_equal_zero(top_plane.signed_distance(point));
    }

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
     * A segment inside the frustum is considered intersecting.
     * @param segment Segment.
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
    [[nodiscard]] bool intersects(const Plane<Real>& plane) const;

    /**
     * Determine if intersects a triangle.
     * A triangle inside the frustum is considered intersecting.
     * @param triangle Triangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Triangle3<Real>& triangle) const;

    /**
     * Determine if intersects a rectangle.
     * A rectangle inside the frustum is considered intersecting.
     * @param rectangle Rectangle.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Rectangle3<Real>& rectangle) const;

    /**
     * Determine if intersects a sphere.
     * A sphere inside the frustum is considered intersecting.
     * @param sphere Sphere.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Sphere<Real>& sphere) const;

    /**
     * Determine if intersects an aligned box.
     * A box inside the frustum is considered intersecting.
     * @param box Aligned box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const AlignedBox<Real>& box) const;

    /**
     * Determine if intersects a box.
     * A box inside the frustum is considered intersecting.
     * @param box Box.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool intersects(const Box<Real>& box) const;

    /**
     * Determine if intersects another frustum.
     * One frustum inside another is considered intersecting.
     * @param other Other frustum.
     * @return Result.
     */
    // tested.
    [[nodiscard]] constexpr bool intersects(const Frustum& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (contains(other.vertex(i)) || other.contains(vertex(i))) {
                return true;
            }
        }
        for (uint8_t i = 0; i < 12; ++i) {
            if (intersects(other.edge(i)) || other.intersects(edge(i))) {
                return true;
            }
        }
        return false;
    }

    /**
     * Surface intersection points with a line.
     * @param line Line.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Line3<Real>& line) const;

    /**
     * Surface intersections with a ray.
     * @param ray Ray.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr PointSet<Point3<Real>, 2> surface_intersections(const Ray3<Real>& ray) const;

    /**
     * Surface intersections with a line segment.
     * @param segment Segment.
     * @return Result.
     */
    // tested
    [[nodiscard]] PointSet<Point3<Real>, 2> surface_intersections(const Segment3<Real>& segment) const;

    /**
     * Translate by an offset.
     * @param offset Offset.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Frustum translate(const Vector3<Real>& offset) const
    {
        return { near_plane.translate(offset),  far_plane.translate(offset),    left_plane.translate(offset),
                 right_plane.translate(offset), bottom_plane.translate(offset), top_plane.translate(offset) };
    }

    /**
     * Rotate by an axis and angle.
     * @param axis Normalized axis vector.
     * @param angle Angle in radians.
     * @param origin Rotation origin defaulted to the global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Frustum rotate_axis_angle(
        const Vector3<Real>& axis, const Real angle, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return { near_plane.rotate_axis_angle_at(origin, axis, angle),
                 far_plane.rotate_axis_angle_at(origin, axis, angle),
                 left_plane.rotate_axis_angle_at(origin, axis, angle),
                 right_plane.rotate_axis_angle_at(origin, axis, angle),
                 bottom_plane.rotate_axis_angle_at(origin, axis, angle),
                 top_plane.rotate_axis_angle_at(origin, axis, angle) };
    }

    /**
     * Rotate by a quaternion.
     * @param quaternion Quaternion.
     * @param origin Rotation origin defaulted to the global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr Frustum rotate_quaternion(
        const Quaternion<Real>& quaternion, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return {
            near_plane.rotate_quaternion_at(origin, quaternion),   far_plane.rotate_quaternion_at(origin, quaternion),
            left_plane.rotate_quaternion_at(origin, quaternion),   right_plane.rotate_quaternion_at(origin, quaternion),
            bottom_plane.rotate_quaternion_at(origin, quaternion), top_plane.rotate_quaternion_at(origin, quaternion)
        };
    }

    /**
     * Scale by a factor.
     * @param factor Scaling factor.
     * @param origin Scaling origin defaulted to the global origin.
     * @return Result.
     */
    // tested
    [[nodiscard]] Frustum scale(const Vector3<Real>& factor, const Point3<Real>& origin = Point3<Real>::zero()) const
    {
        return { near_plane.scale_at(origin, factor),   far_plane.scale_at(origin, factor),
                 left_plane.scale_at(origin, factor),   right_plane.scale_at(origin, factor),
                 bottom_plane.scale_at(origin, factor), top_plane.scale_at(origin, factor) };
    }

    /**
     * Determine if all members are approximately equal to another frustum.
     * @param other Other frustum.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool approx_equal(const Frustum& other) const
    {
        return near_plane.approx_equal(other.near_plane) && far_plane.approx_equal(other.far_plane)
            && left_plane.approx_equal(other.left_plane) && right_plane.approx_equal(other.right_plane)
            && bottom_plane.approx_equal(other.bottom_plane) && top_plane.approx_equal(other.top_plane);
    }

    /**
     * Determine if all members are exactly equal to another frustum.
     * @param other Other frustum.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator==(const Frustum& other) const
    {
        return near_plane == other.near_plane && far_plane == other.far_plane && left_plane == other.left_plane
            && right_plane == other.right_plane && bottom_plane == other.bottom_plane && top_plane == other.top_plane;
    }

    /**
     * Determine if any members are not exactly equal to another frustum.
     * @param other Other frustum.
     * @return Result.
     */
    // tested
    [[nodiscard]] constexpr bool operator!=(const Frustum& other) const
    {
        return near_plane != other.near_plane || far_plane != other.far_plane || left_plane != other.left_plane
            || right_plane != other.right_plane || bottom_plane != other.bottom_plane || top_plane != other.top_plane;
    }

    /**
     * Lexicographical comparison in the order of near, far, left, right, bottom, then top planes.
     * @param other Other frustum.
     * @return Result.
     */
    [[nodiscard]] constexpr bool operator<(const Frustum& other) const
    {
        if (near_plane != other.near_plane) {
            return near_plane < other.near_plane;
        }
        if (far_plane != other.far_plane) {
            return far_plane < other.far_plane;
        }
        if (left_plane != other.left_plane) {
            return left_plane < other.left_plane;
        }
        if (right_plane != other.right_plane) {
            return right_plane < other.right_plane;
        }
        if (bottom_plane != other.bottom_plane) {
            return bottom_plane < other.bottom_plane;
        }
        return top_plane < other.top_plane;
    }
};

} // namespace nnm

#endif
