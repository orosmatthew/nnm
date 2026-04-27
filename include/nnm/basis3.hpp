/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_BASIS3_HPP
#define NNM_BASIS3_HPP

#include <nnm/forward.hpp>
#include <nnm/vector3.hpp>
#include <nnm/quaternion.hpp>
#include <nnm/matrix3.hpp>

namespace nnm {

/**
 * Three-dimensional basis matrix. Can represent three-dimensional scale, shear, and rotation.
 * @tparam Real
 */
template <typename Real>
class Basis3 {
public:
    Matrix3<Real> matrix;

    /**
     * Initializes with identity.
     */
    constexpr Basis3()
        : matrix(Matrix3<Real>::identity())
    {
    }

    /**
     * Casts from another basis type.
     * @tparam Other Other basis type.
     * @param basis Basis to cast from.
     */
    template <typename Other>
    explicit constexpr Basis3(const Basis3<Other>& basis)
        : matrix(Matrix3<Real>(basis.matrix))
    {
    }

    /**
     * Initializes from a 3x3 matrix. No validation is done.
     * @param matrix 3x3 matrix.
     */
    explicit constexpr Basis3(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    /**
     * Basis rotated from normalized axis and angle.
     * @param axis Normalized axis.
     * @param angle Angle in radians.
     * @return Result.
     */
    static Basis3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3<Real> norm = axis.normalize();
        // Rodrigues' formula
        const Matrix3<Real> k_matrix { { static_cast<Real>(0), norm.z, -norm.y },
                                       { -norm.z, static_cast<Real>(0), norm.x },
                                       { norm.y, -norm.x, static_cast<Real>(0) } };
        const Matrix3<Real> r_matrix = Matrix3<Real>::identity() + sin(angle) * k_matrix
            + (static_cast<Real>(1) - cos(angle)) * k_matrix * k_matrix;
        return Basis3(r_matrix);
    }

    /**
     * Basis rotated from quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    static constexpr Basis3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const Quaternion<Real>& q = quaternion;
        Matrix3<Real> matrix;
        const Real one = static_cast<Real>(1);
        const Real two = static_cast<Real>(2);
        matrix.at(0, 0) = one - two * (sqrd(q.y) + sqrd(q.z));
        matrix.at(0, 1) = two * (q.x * q.y + q.z * q.w);
        matrix.at(0, 2) = two * (q.x * q.z - q.y * q.w);
        matrix.at(1, 0) = two * (q.x * q.y - q.z * q.w);
        matrix.at(1, 2) = two * (q.y * q.z + q.x * q.w);
        matrix.at(2, 0) = two * (q.x * q.z + q.y * q.w);
        matrix.at(1, 1) = one - two * (sqrd(q.x) + sqrd(q.z));
        matrix.at(2, 1) = two * (q.y * q.z - q.x * q.w);
        matrix.at(2, 2) = one - two * (sqrd(q.x) + sqrd(q.y));
        return Basis3(matrix);
    }

    /**
     * Basis scaled by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    static constexpr Basis3 from_scale(const Vector3<Real>& factor)
    {
        return Basis3(
            { { factor.x, static_cast<Real>(0), static_cast<Real>(0) },
              { static_cast<Real>(0), factor.y, static_cast<Real>(0) },
              { static_cast<Real>(0), static_cast<Real>(0), factor.z } });
    }

    /**
     * Basis sheared along the x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    static constexpr Basis3 from_shear_x(const Real factor_y, const Real factor_z)
    {
        return Basis3(
            { { static_cast<Real>(1), factor_y, factor_z },
              { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
              { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } });
    }

    /**
     * Basis sheared along the y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    static constexpr Basis3 from_shear_y(const Real factor_x, const Real factor_z)
    {
        return Basis3(
            { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
              { factor_x, static_cast<Real>(1), factor_z },
              { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } });
    }

    /**
     * Basis sheared along the z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    static constexpr Basis3 from_shear_z(const Real factor_x, const Real factor_y)
    {
        return Basis3(
            { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
              { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
              { factor_x, factor_y, static_cast<Real>(1) } });
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
     * Inverse without checking if the basis is valid first.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 unchecked_inverse() const
    {
        return Basis3(matrix.unchecked_inverse());
    }

    /**
     * Inverse of the basis.
     * @return Inverse basis if the basis is valid or null otherwise.
     */
    [[nodiscard]] constexpr std::optional<Basis3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    /**
     * Determines if the basis is valid.
     * @return True if valid, false otherwise.
     */
    [[nodiscard]] constexpr bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0);
    }

    /**
     * Rotate about an axis by an angle.
     * @param axis Normalized axis vector.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Basis3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    /**
     * Local rotate about an axis by an angle.
     * @param axis Normalize axis vector.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Basis3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    /**
     * Rotate by quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    /**
     * Local rotate by quaternion.
     * @param quaternion Quaternion.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    /**
     * Per-axis scale by factor.
     * @param factor Vector scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    /**
     * Local per-axis scale by factor.
     * @param factor Vector scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    /**
     * Shear about x-axis.
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_x(const Real factor_y, const Real factor_z) const
    {
        return transform(from_shear_x(factor_y, factor_z));
    }

    /**
     * Local shear about x-axis
     * @param factor_y Y-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_x_local(const Real factor_y, const Real factor_z) const
    {
        return transform_local(from_shear_x(factor_y, factor_z));
    }

    /**
     * Shear about y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_y(const Real factor_x, const Real factor_z) const
    {
        return transform(from_shear_y(factor_x, factor_z));
    }

    /**
     * Local shear about y-axis.
     * @param factor_x X-Axis factor.
     * @param factor_z Z-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_y_local(const Real factor_x, const Real factor_z) const
    {
        return transform_local(from_shear_y(factor_x, factor_z));
    }

    /**
     * Shear about z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_z(const Real factor_x, const Real factor_y) const
    {
        return transform(from_shear_z(factor_x, factor_y));
    }

    /**
     * Local shear about z-axis.
     * @param factor_x X-Axis factor.
     * @param factor_y Y-Axis factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 shear_z_local(const Real factor_x, const Real factor_y) const
    {
        return transform_local(from_shear_z(factor_x, factor_y));
    }

    /**
     * Transform by another basis.
     * @param by Basis.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 transform(const Basis3& by) const
    {
        return Basis3(by.matrix * matrix);
    }

    /**
     * Local transform by another basis.
     * @param by Basis.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis3 transform_local(const Basis3& by) const
    {
        return Basis3(matrix * by.matrix);
    }

    /**
     * Determines if approximately equal to another basis.
     * @param other Other basis.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Basis3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    /**
     * Constant reference to column at index.
     * @param column Index of column.
     * @return Constant reference to column.
     */
    [[nodiscard]] constexpr const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3);
        return matrix.at(column);
    }

    /**
     * Reference to column at index.
     * @param column Index of column.
     * @return Reference to column.
     */
    constexpr Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3);
        return matrix.at(column);
    }

    /**
     * Constant reference of element at index of column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Constant reference to element.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    /**
     * Reference of element at index of column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Reference to element.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column <= 3 && row <= 3);
        return matrix.at(column, row);
    }

    /**
     * Constant reference to column at index.
     * @param index Index of column.
     * @return Constant reference to column.
     */
    [[nodiscard]] constexpr const Vector3<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index <= 3);
        return matrix[index];
    }

    /**
     * Reference to column at index.
     * @param index Index of column.
     * @return Reference to column.
     */
    constexpr Vector3<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index <= 3);
        return matrix[index];
    }

    /**
     * Element-wise equality with another basis.
     * @param other Other basis.
     * @return True if all elements are equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Basis3& other) const
    {
        return matrix == other.matrix;
    }

    /**
     * Element-wise inequality with another basis.
     * @param other Other basis.
     * @return True if any elements are not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Basis3& other) const
    {
        return matrix != other.matrix;
    }

    /**
     * Lexicographical comparison between elements.
     * @param other Other basis.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Basis3& other) const
    {
        return matrix < other.matrix;
    }
};
}

#endif
