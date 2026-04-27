/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_TRANSFORM3_HPP
#define NNM_TRANSFORM3_HPP

#include <nnm/forward.hpp>
#include <nnm/vector3.hpp>
#include <nnm/vector4.hpp>
#include <nnm/quaternion.hpp>
#include <nnm/transform2.hpp>
#include <nnm/basis3.hpp>
#include <nnm/matrix4.hpp>

namespace nnm {

/**
 * Three-dimensional transformation matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Transform3 {
public:
    /**
     * Matrix of transform
     */
    Matrix4<Real> matrix;

    /**
     * Initializes with identity.
     */
    constexpr Transform3()
        : matrix(Matrix4<Real>::identity())
    {
    }

    /**
     * Cast from other transform.
     * @tparam Other Other type.
     * @param transform Other transform.
     */
    template <typename Other>
    explicit constexpr Transform3(const Transform3<Other>& transform)
        : matrix(Matrix4<Real>(transform.matrix))
    {
    }

    /**
     * Initializes from a 4x4 matrix. No validation or checks are done.
     * @param matrix Matrix.
     */
    explicit constexpr Transform3(const Matrix4<Real>& matrix)
        : matrix(matrix)
    {
    }

    /**
     * Transform from a 3D basis and 3D translation.
     * @param basis 3D basis.
     * @param translation 3D translation vector.
     * @return Result.
     */
    static constexpr Transform3 from_basis_translation(const Basis3<Real>& basis, const Vector3<Real>& translation)
    {
        auto matrix = Matrix4<Real>::identity();
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(3, 0) = translation.x;
        matrix.at(3, 1) = translation.y;
        matrix.at(3, 2) = translation.z;
        return Transform3(matrix);
    }

    /**
     * Transform from a 3D basis and no translation.
     * @param basis 3D Basis.
     * @return Result.
     */
    static constexpr Transform3 from_basis(const Basis3<Real>& basis)
    {
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    /**
     * Transform with a translation.
     * @param translation 3D translation vector.
     * @return Result.
     */
    static constexpr Transform3 from_translation(const Vector3<Real>& translation)
    {
        return from_basis_translation(Basis3<Real>(), translation);
    }

    /**
     * Transform rotated about a normalized axis and angle.
     * @param axis Normalized 3D axis vector.
     * @param angle Angle in radians.
     * @return Result.
     */
    static Transform3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const auto basis = Basis3<Real>::from_rotation_axis_angle(axis, angle);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    /**
     * Transform rotated by quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    static constexpr Transform3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const auto basis = Basis3<Real>::from_rotation_quaternion(quaternion);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    /**
     * Transform scaled by per-axis factor.
     * @param factor Scale factor vector.
     * @return Result.
     */
    static constexpr Transform3 from_scale(const Vector3<Real>& factor)
    {
        return from_basis(Basis3<Real>::from_scale(factor));
    }

    /**
     * Transform sheared about the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    static constexpr Transform3 from_shear_x(const Real factor_y, const Real factor_z)
    {
        return from_basis(Basis3<Real>::from_shear_x(factor_y, factor_z));
    }

    /**
     * Transform sheared about the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    static constexpr Transform3 from_shear_y(const Real factor_x, const Real factor_z)
    {
        return from_basis(Basis3<Real>::from_shear_y(factor_x, factor_z));
    }

    /**
     * Transform sheared about the z-axis.
     * @param factor_x X-axis factor.
     * @param factor_y Y-axis factor.
     * @return Result.
     */
    static constexpr Transform3 from_shear_z(const Real factor_x, const Real factor_y)
    {
        return from_basis(Basis3<Real>::from_shear_z(factor_x, factor_y));
    }

    /**
     * Transform with perspective projection with left-handed coordinate system and normalized from -1 to 1.
     * @param fov Field-of-view in radians.
     * @param aspect_ratio Aspect ratio.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static Transform3 from_perspective_left_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        matrix.at(2, 3) = -static_cast<Real>(1);
        matrix.at(3, 2) = -(static_cast<Real>(2) * far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with perspective projection with left-handed coordinate system and normalized from 0 to 1.
     * @param fov Field-of-view in radians.
     * @param aspect_ratio Aspect ratio.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static Transform3 from_perspective_left_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = -far_clip / (far_clip - near_clip);
        matrix.at(2, 3) = -static_cast<Real>(1);
        matrix.at(3, 2) = -(far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with perspective projection with right-handed coordinate system and normalized from -1 to 1.
     * @param fov Field-of-view in radians.
     * @param aspect_ratio Aspect ratio.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static Transform3 from_perspective_right_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = (far_clip + near_clip) / (far_clip - near_clip);
        matrix.at(2, 3) = static_cast<Real>(1);
        matrix.at(3, 2) = -(static_cast<Real>(2) * far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with perspective projection with right-handed coordinate system and normalized from 0 to 1.
     * @param fov Field-of-view in radians.
     * @param aspect_ratio Aspect ratio.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static Transform3 from_perspective_right_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2));
        matrix.at(0, 0) = static_cast<Real>(1) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1) / tan_half_fov;
        matrix.at(2, 2) = far_clip / (far_clip - near_clip);
        matrix.at(2, 3) = static_cast<Real>(1);
        matrix.at(3, 2) = -(far_clip * near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with orthographic projection with left-handed coordinate system and normalized from -1 to 1.
     * @param left Left distance.
     * @param right Right distance.
     * @param bottom Bottom distance.
     * @param top Top distance.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static constexpr Transform3 from_orthographic_left_hand_neg1to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = -static_cast<Real>(2) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with orthographic projection with left-handed coordinate system and normalized from 0 to 1.
     * @param left Left distance.
     * @param right Right distance.
     * @param bottom Bottom distance.
     * @param top Top distance.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static constexpr Transform3 from_orthographic_left_hand_0to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = -static_cast<Real>(1) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -near_clip / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with orthographic projection with right-handed coordinate system and normalized from -1 to 1.
     * @param left Left distance.
     * @param right Right distance.
     * @param bottom Bottom distance.
     * @param top Top distance.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static constexpr Transform3 from_orthographic_right_hand_neg1to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = static_cast<Real>(2) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -(far_clip + near_clip) / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Transform with orthographic projection with right-handed coordinate system and normalized from 0 to 1.
     * @param left Left distance.
     * @param right Right distance.
     * @param bottom Bottom distance.
     * @param top Top distance.
     * @param near_clip Near clipping plane distance.
     * @param far_clip Far clipping plane distance.
     * @return Result.
     */
    static constexpr Transform3 from_orthographic_right_hand_0to1(
        const Real left, const Real right, const Real bottom, const Real top, const Real near_clip, const Real far_clip)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2) / (top - bottom);
        matrix.at(2, 2) = static_cast<Real>(1) / (far_clip - near_clip);
        matrix.at(3, 0) = -(right + left) / (right - left);
        matrix.at(3, 1) = -(top + bottom) / (top - bottom);
        matrix.at(3, 2) = -near_clip / (far_clip - near_clip);
        return Transform3(matrix);
    }

    /**
     * Trace which is the sum of the matrix diagonal.
     * @return Result.
     */
    [[nodiscard]] constexpr Real trace() const
    {
        return matrix.trace();
    }

    /**
     * Determinant of the matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Real determinant() const
    {
        return matrix.determinant();
    }

    /**
     * Inverse of the transform without checking if a valid inverse is possible.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 unchecked_inverse() const
    {
        return Transform3(matrix.unchecked_inverse());
    }

    /**
     * Inverse of the transform.
     * @return Inverse if one exists, null otherwise.
     */
    [[nodiscard]] constexpr std::optional<Transform3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    /**
     * Determines if transform is valid. Validity is determined based on if the transform's basis is valid.
     * @return True if valid, false otherwise.
     */
    [[nodiscard]] constexpr bool valid() const
    {
        return basis().valid();
    }

    /**
     * Determines if transform is affine. Affine means that the transform preserves parallel lines.
     * @return True if affine, false otherwise.
     */
    [[nodiscard]] constexpr bool affine() const
    {
        return valid() && matrix.at(0, 3) == static_cast<Real>(0) && matrix.at(1, 3) == static_cast<Real>(0)
            && matrix.at(2, 3) == static_cast<Real>(0) && matrix.at(3, 3) == static_cast<Real>(1);
    }

    /**
     * Basis of the transform.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3<Real> basis() const
    {
        return Basis3(matrix.minor_matrix_at(3, 3));
    }

    /**
     * Translation vector of the transform.
     * @return Result.
     */
    [[nodiscard]] constexpr Vector3<Real> translation() const
    {
        return { matrix.at(3, 0), matrix.at(3, 1), matrix.at(3, 2) };
    }

    /**
     * Translation.
     * @param offset Offset vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 translate(const Vector3<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    /**
     * Local translation.
     * @param offset Offset vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 translate_local(const Vector3<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    /**
     * Rotation about an axis by an angle.
     * @param axis Normalized 3D vector axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Transform3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    /**
     * Local rotation about an axis by an angle.
     * @param axis Normalized 3D vector axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Transform3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    /**
     * Rotation by quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    /**
     * Location rotation by quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    /**
     * Per-axis scale by factor.
     * @param factor 3D scale factor vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    /**
     * Local per-axis scale by factor.
     * @param factor 3D scale factor vector.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    /**
     * Shear about the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return transform(from_shear_x(factor_y, factor_z));
    }

    /**
     * Local shear about the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_x_local(const Real factor_y, const Real factor_z) const
    {
        return transform_local(from_shear_x(factor_y, factor_z));
    }

    /**
     * Shear about the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return transform(from_shear_y(factor_x, factor_z));
    }

    /**
     * Local shear about the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_y_local(const Real factor_x, const Real factor_z) const
    {
        return transform_local(from_shear_y(factor_x, factor_z));
    }

    /**
     * Shear about the z-axis.
     * @param factor_x X-axis factor.
     * @param factor_y Y-axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return transform(from_shear_z(factor_x, factor_y));
    }

    /**
     * Local shear about the z-axis.
     * @param factor_x X-axis factor.
     * @param factor_y Y-axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 shear_z_local(const Real factor_x, const Real factor_y) const
    {
        return transform_local(from_shear_z(factor_x, factor_y));
    }

    /**
     * Transform by another transform.
     * @param by Other transform.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 transform(const Transform3& by) const
    {
        return Transform3(by.matrix * matrix);
    }

    /**
     * Local transform by another transform.
     * @param by Other transform.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform3 transform_local(const Transform3& by) const
    {
        return Transform3(matrix * by.matrix);
    }

    /**
     * Determines if approximately equal to another transform.
     * @param other Other transform.
     * @return True if all elements are approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Transform3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    /**
     * Constant reference to column at index.
     * @param column Index of column.
     * @return Constant reference to column.
     */
    [[nodiscard]] constexpr const Vector4<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix.at(column);
    }

    /**
     * Reference to column at index.
     * @param column Index of column.
     * @return Reference to column.
     */
    constexpr Vector4<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix.at(column);
    }

    /**
     * Constant reference to element at column and row index.
     * @param column Index of column.
     * @param row Index of row.
     * @return Constant reference to element.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    /**
     * Reference to element at column and row index.
     * @param column Index of column.
     * @param row Index of row.
     * @return Reference to element.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    /**
     * Constant reference to column at column index.
     * @param column Index of column.
     * @return Constant reference to column.
     */
    [[nodiscard]] constexpr const Vector4<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix[column];
    }

    /**
     * Reference to column at column index.
     * @param column Index of column.
     * @return Reference to column.
     */
    constexpr Vector4<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column <= 3);
        return matrix[column];
    }

    /**
     * Element-wise equality.
     * @param other Other transform.
     * @return True if all elements are equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Transform3& other) const
    {
        return matrix == other.matrix;
    }

    /**
     * Element-wise inequality
     * @param other Other transform.
     * @return True if any element is not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Transform3& other) const
    {
        return matrix != other.matrix;
    }

    /**
     * Lexicographical comparison.
     * @param other Other transform.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Transform3& other) const
    {
        return matrix < other.matrix;
    }
};
}

#endif
