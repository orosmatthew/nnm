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
#include <nnm/geom3/plane.hpp>
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
    constexpr Frustum()
        : near_plane { Plane<Real> { } }
        , far_plane { Plane<Real> { } }
        , left_plane { Plane<Real> { } }
        , right_plane { Plane<Real> { } }
        , bottom_plane { Plane<Real> { } }
        , top_plane { Plane<Real> { } }
    {
    }

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
        const Plane<Real> top_plane)
        : near_plane { std::move(near_plane) }
        , far_plane { std::move(far_plane) }
        , left_plane { std::move(left_plane) }
        , right_plane { std::move(right_plane) }
        , bottom_plane { std::move(bottom_plane) }
        , top_plane { std::move(top_plane) }
    {
    }

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
        const Real far)
    {
        Vector3<Real> corrected_up = up;
        if (forward.parallel(up)) {
            if (!forward.parallel(Vector3<Real>::axis_x())) {
                corrected_up = Vector3<Real>::axis_x();
            }
            else {
                corrected_up = Vector3<Real>::axis_y();
            }
        }
        const Vector3<Real> right = corrected_up.cross(forward).normalize();
        corrected_up = forward.cross(right).normalize();
        const Real tan_fov_y = nnm::tan(fov / static_cast<Real>(2));
        const Real near_height_half = tan_fov_y * near;
        const Real near_width_half = near_height_half * aspect;
        const Point3<Real> near_origin = position + forward * near;

        const Plane<Real> near_plane { near_origin, forward };
        const Plane<Real> far_plane { position + forward * far, -forward };

        const Point3<Real> left_origin = near_origin - right * near_width_half;
        const Vector3<Real> left_normal = corrected_up.cross(left_origin - position).normalize();
        const Plane<Real> left_plane { left_origin, left_normal };

        const Point3<Real> right_origin = near_origin + right * near_width_half;
        const Vector3<Real> right_normal = (right_origin - position).cross(corrected_up).normalize();
        const Plane<Real> right_plane { right_origin, right_normal };

        const Point3<Real> bottom_origin = near_origin - corrected_up * near_height_half;
        const Vector3<Real> bottom_normal = (bottom_origin - position).cross(right).normalize();
        const Plane<Real> bottom_plane { bottom_origin, bottom_normal };

        const Point3<Real> top_origin = near_origin + corrected_up * near_height_half;
        const Vector3<Real> top_normal = right.cross(top_origin - position).normalize();
        const Plane<Real> top_plane { top_origin, top_normal };

        return { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    }

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
        const Real far)
    {
        Vector3<Real> corrected_up = up;
        if (forward.parallel(up)) {
            if (!forward.parallel(Vector3<Real>::axis_x())) {
                corrected_up = Vector3<Real>::axis_x();
            }
            else {
                corrected_up = Vector3<Real>::axis_y();
            }
        }
        const Vector3<Real> right = forward.cross(corrected_up).normalize();
        corrected_up = right.cross(forward).normalize();
        const Real tan_fov_y = nnm::tan(fov / static_cast<Real>(2));
        const Real near_height_half = tan_fov_y * near;
        const Real near_width_half = near_height_half * aspect;
        const Point3<Real> near_origin = position + forward * near;

        const Plane<Real> near_plane { near_origin, forward };
        const Plane<Real> far_plane { position + forward * far, -forward };

        const Point3<Real> left_origin = near_origin - right * near_width_half;
        const Vector3<Real> left_normal = (left_origin - position).cross(corrected_up).normalize();
        const Plane<Real> left_plane { left_origin, left_normal };

        const Point3<Real> right_origin = near_origin + right * near_width_half;
        const Vector3<Real> right_normal = corrected_up.cross(right_origin - position).normalize();
        const Plane<Real> right_plane { right_origin, right_normal };

        const Point3<Real> bottom_origin = near_origin - corrected_up * near_height_half;
        const Vector3<Real> bottom_normal = right.cross(bottom_origin - position).normalize();
        const Plane<Real> bottom_plane { bottom_origin, bottom_normal };

        const Point3<Real> top_origin = near_origin + corrected_up * near_height_half;
        const Vector3<Real> top_normal = (top_origin - position).cross(right).normalize();
        const Plane<Real> top_plane { top_origin, top_normal };

        return { near_plane, far_plane, left_plane, right_plane, bottom_plane, top_plane };
    }

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
    [[nodiscard]] constexpr Segment3<Real> edge(const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Frustum<Real>", index < 12);
        switch (index) {
        case 0: // near-left
            return { vertex(0), vertex(1) };
        case 1: // near-right
            return { vertex(2), vertex(3) };
        case 2: // near-bottom
            return { vertex(0), vertex(2) };
        case 3: // near-top
            return { vertex(1), vertex(3) };
        case 4: // far-left
            return { vertex(4), vertex(5) };
        case 5: // far-right
            return { vertex(6), vertex(7) };
        case 6: // far-bottom
            return { vertex(4), vertex(6) };
        case 7: // far-top
            return { vertex(5), vertex(7) };
        case 8: // left-bottom
            return { vertex(0), vertex(4) };
        case 9: // left-top
            return { vertex(1), vertex(5) };
        case 10: // right-bottom
            return { vertex(2), vertex(6) };
        case 11: // right-top
        default:
            return { vertex(3), vertex(7) };
        }
    }

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
        for (uint8_t i = 0; i < 8; ++i) {
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
