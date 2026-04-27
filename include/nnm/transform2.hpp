/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_TRANSFORM2_HPP
#define NNM_TRANSFORM2_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>
#include <nnm/vector3.hpp>
#include <nnm/basis2.hpp>
#include <nnm/matrix3.hpp>

namespace nnm {

/**
 * Two-dimensional transformation matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Transform2 {
public:
    Matrix3<Real> matrix;

    /**
     * Initializes with identity.
     */
    constexpr Transform2()
        : matrix(Matrix3<Real>::identity())
    {
    }

    /**
     * Cast from other transform type.
     * @tparam Other Other transform type.
     * @param transform Transform to cast from.
     */
    template <typename Other>
    explicit constexpr Transform2(const Transform2<Other>& transform)
        : matrix(Matrix3<Real>(transform.matrix))
    {
    }

    /**
     * Initializes from a 3x3 matrix. No validation is done.
     * @param matrix 3x3 matrix.
     */
    explicit constexpr Transform2(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    /**
     * Transform from a two-dimensional basis and two-dimensional translation. No validation is done.
     * @param basis Basis.
     * @param translation Translation.
     * @return Result.
     */
    static constexpr Transform2 from_basis_translation(const Basis2<Real>& basis, const Vector2<Real>& translation)
    {
        Matrix3<Real> matrix;
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(2, 0) = translation.x;
        matrix.at(2, 1) = translation.y;
        return Transform2(matrix);
    }

    /**
     * Transform from basis.
     * @param basis Basis.
     * @return Result.
     */
    static constexpr Transform2 from_basis(const Basis2<Real>& basis)
    {
        return from_basis_translation(basis, Vector2<Real>::zero());
    }

    /**
     * Transform from translation.
     * @param translation Translation.
     * @return Result.
     */
    static constexpr Transform2 from_translation(const Vector2<Real>& translation)
    {
        return from_basis_translation(Basis2<Real>(), translation);
    }

    /**
     * Transform with rotation.
     * @param angle Angle in radians.
     * @return Result.
     */
    static Transform2 from_rotation(const Real angle)
    {
        return from_basis_translation(Basis2<Real>::from_rotation(angle), Vector2<Real>());
    }

    /**
     * Transform with scale.
     * @param factor Scale factor.
     * @return Result.
     */
    static constexpr Transform2 from_scale(const Vector2<Real>& factor)
    {
        return from_basis_translation(Basis2<Real>::from_scale(factor), Vector2<Real>());
    }

    /**
     * Transform with shear along the x-axis.
     * @param factor Factor.
     * @return Result.
     */
    static constexpr Transform2 from_shear_x(const Real factor)
    {
        return from_basis_translation(Basis2<Real>::from_shear_x(factor), Vector2<Real>());
    }

    /**
     * Transform with shear along the y-axis.
     * @param factor Factor.
     * @return Result.
     */
    static constexpr Transform2 from_shear_y(const Real factor)
    {
        return from_basis_translation(Basis2<Real>::from_shear_y(factor), Vector2<Real>());
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
     * Determinant.
     * @return Result.
     */
    [[nodiscard]] constexpr Real determinant() const
    {
        return matrix.determinant();
    }

    /**
     * Inverse without checking if there is one.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 unchecked_inverse() const
    {
        return Transform2(matrix.unchecked_inverse());
    }

    /**
     * Inverse which returns null if there is none.
     * @return Inverse if there is one, null if not.
     */
    [[nodiscard]] constexpr std::optional<Transform2> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    /**
     * Determines if the transform is valid.
     * @return True if valid, false otherwise.
     */
    [[nodiscard]] constexpr bool valid() const
    {
        return basis().valid();
    }

    /**
     * If the transform is affine. A transform is affine if all lines remain straight and parallel lines are preserved.
     * @return True if affine, false otherwise.
     */
    [[nodiscard]] constexpr bool affine() const
    {
        return valid() && matrix.at(0, 2) == static_cast<Real>(0) && matrix.at(1, 2) == static_cast<Real>(0)
            && matrix.at(2, 2) == static_cast<Real>(1);
    }

    /**
     * Two-dimensional basis sub-matrix.
     * @return Basis.
     */
    [[nodiscard]] constexpr Basis2<Real> basis() const
    {
        return Basis2(matrix.minor_matrix_at(2, 2));
    }

    /**
     * Translation of the transform.
     * @return Resulting two-dimensional translation vector.
     */
    [[nodiscard]] constexpr Vector2<Real> translation() const
    {
        return { matrix.at(2, 0), matrix.at(2, 1) };
    }

    /**
     * Translate.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 translate(const Vector2<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    /**
     * Local translate.
     * @param offset Offset.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 translate_local(const Vector2<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    /**
     * Rotate by angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Transform2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    /**
     * Local rotate by angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Transform2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    /**
     * Scale by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    /**
     * Local scale by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    /**
     * Shear along the x-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 shear_x(const Real factor) const
    {
        return transform(from_shear_x(factor));
    }

    /**
     * Local shear along x-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 shear_x_local(const Real factor) const
    {
        return transform_local(from_shear_x(factor));
    }

    /**
     * Shear along y-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 shear_y(const Real factor) const
    {
        return transform(from_shear_y(factor));
    }

    /**
     * Local shear along y-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 shear_y_local(const Real factor) const
    {
        return transform_local(from_shear_y(factor));
    }

    /**
     * Transform by another transform.
     * @param by Transform to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 transform(const Transform2& by) const
    {
        return Transform2(by.matrix * matrix);
    }

    /**
     * Local transform by another transform.
     * @param by Transform to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Transform2 transform_local(const Transform2& by) const
    {
        return Transform2(matrix * by.matrix);
    }

    /**
     * Element-wise approximately equal.
     * @param other Other transform.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Transform2& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    /**
     * Constant reference to column at index.
     * @param column Column.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    /**
     * Reference to column
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    /**
     * Constant reference to element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2 && row <= 2);
        return matrix.at(column, row);
    }

    /**
     * Reference to element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2 && row <= 2);
        return matrix.at(column, row);
    }

    /**
     * Constant reference to column at index.
     * @param column Column.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Vector3<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    /**
     * Reference to column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector3<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column <= 2);
        return matrix[column];
    }

    /**
     * Element-wise equality.
     * @param other Other transform.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Transform2& other) const
    {
        return matrix == other.matrix;
    }

    /**
     * Element-wise inequality.
     * @param other Other transform.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Transform2& other) const
    {
        return matrix != other.matrix;
    }

    /**
     * Lexicographical comparison between elements.
     * @param other Other transform.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Transform2& other) const
    {
        return matrix < other.matrix;
    }
};
}

#endif
