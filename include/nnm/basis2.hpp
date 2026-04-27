/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_BASIS2_HPP
#define NNM_BASIS2_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>
#include <nnm/matrix2.hpp>

namespace nnm {

/**
 * Two-dimensional basis matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Basis2 {
public:
    Matrix2<Real> matrix;

    /**
     * Initializes with identity basis.
     */
    constexpr Basis2()
        : matrix(Matrix2<Real>::identity())
    {
    }

    /**
     * Cast from other basis type.
     * @tparam Other Other type.
     * @param basis Basis to cast from.
     */
    template <typename Other>
    explicit constexpr Basis2(const Basis2<Other>& basis)
        : matrix(Matrix2<Real>(basis.matrix))
    {
    }

    /**
     * Initializes from a 2x2 matrix. No validation is done.
     * @param matrix 2x2 matrix to cast from.
     */
    explicit constexpr Basis2(const Matrix2<Real>& matrix)
        : matrix(matrix)
    {
    }

    /**
     * Basis rotate by angle in radians.
     * @param angle Angle in radians.
     * @return Result.
     */
    static Basis2 from_rotation(const Real angle)
    {
        return Basis2({ { cos(angle), sin(angle) }, { -sin(angle), cos(angle) } });
    }

    /**
     * Basis scaled by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    static constexpr Basis2 from_scale(const Vector2<Real>& factor)
    {
        return Basis2({ { factor.x, static_cast<Real>(0) }, { static_cast<Real>(0), factor.y } });
    }

    /**
     * Basis sheared along the x-axis.
     * @param factor Factor.
     * @return Result.
     */
    static constexpr Basis2 from_shear_x(const Real factor)
    {
        return Basis2({ { static_cast<Real>(1), static_cast<Real>(0) }, { factor, static_cast<Real>(1) } });
    }

    /**
     * Basis sheared along the y-axis.
     * @param factor Factor.
     * @return Result.
     */
    static constexpr Basis2 from_shear_y(const Real factor)
    {
        return Basis2({ { static_cast<Real>(1), factor }, { static_cast<Real>(0), static_cast<Real>(1) } });
    }

    /**
     * Trace which is the sum of the diagonal of the matrix.
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
     * Inverse without checking if the basis is valid first.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 unchecked_inverse() const
    {
        return Basis2(matrix.unchecked_inverse());
    }

    /**
     * Inverse which returns null if the basis is invalid.
     * @return Inverse if there is one, null if not.
     */
    [[nodiscard]] constexpr std::optional<Basis2> inverse() const
    {
        if (valid()) {
            return Basis2(matrix.unchecked_inverse());
        }
        return std::nullopt;
    }

    /**
     * If the elements of the matrix form a valid basis.
     * @return True if valid, false otherwise.
     */
    [[nodiscard]] constexpr bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0);
    }

    /**
     * Rotate by angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Basis2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    /**
     * Local rotation by angle.
     * @param angle Angle in radians.
     * @return Result.
     */
    [[nodiscard]] Basis2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    /**
     * Scale by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    /**
     * Local scale by factor.
     * @param factor Scale factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    /**
     * Shear along x-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 shear_x(const Real factor) const
    {
        return transform(from_shear_x(factor));
    }

    /**
     * Local shear along x-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 shear_x_local(const Real factor) const
    {
        return transform_local(from_shear_x(factor));
    }

    /**
     * Shear along y-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 shear_y(const Real factor) const
    {
        return transform(from_shear_y(factor));
    }

    /**
     * Local shear along y-axis.
     * @param factor Factor.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 shear_y_local(const Real factor) const
    {
        return transform_local(from_shear_y(factor));
    }

    /**
     * Transform by another basis.
     * @param by Basis to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 transform(const Basis2& by) const
    {
        return Basis2(by.matrix * matrix);
    }

    /**
     * Local transform by another basis.
     * @param by Basis to transform by.
     * @return Result.
     */
    [[nodiscard]] constexpr Basis2 transform_local(const Basis2& by) const
    {
        return Basis2(matrix * by.matrix);
    }

    /**
     * If approximately equal to another basis.
     * @param other Other basis.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Basis2& other) const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Constant reference to the matrix column at index.
     * @param column Column
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Vector2<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1);
        return matrix[column];
    }

    /**
     * Reference to the matrix column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector2<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1);
        return matrix[column];
    }

    /**
     * Constant reference to the matrix element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1 && row <= 1);
        return matrix[column][row];
    }

    /**
     * Reference to the matrix element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column <= 1 && row <= 1);
        return matrix[column][row];
    }

    /**
     * Constant reference to the matrix column at index.
     * @param index Index.
     * @return Constant reference.
     */
    constexpr const Vector2<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index <= 1);
        return matrix[index];
    }

    /**
     * Reference to the matrix column at index.
     * @param index Index.
     * @return Reference.
     */
    constexpr Vector2<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index <= 1);
        return matrix[index];
    }

    /**
     * Element-wise equality.
     * @param other Other basis.
     * @return True if equal, false otherwise.
     */
    constexpr bool operator==(const Basis2& other) const
    {
        return matrix == other.matrix;
    }

    /**
     * Element-wise inequality.
     * @param other Other basis.
     * @return True if not equal, false otherwise.
     */
    constexpr bool operator!=(const Basis2& other) const
    {
        return matrix != other.matrix;
    }

    /**
     * Lexicographical comparison between the matrix elements.
     * @param other Other basis.
     * @return True if less than, false otherwise.
     */
    constexpr bool operator<(const Basis2& other) const
    {
        return matrix < other.matrix;
    }
};
}

#endif
