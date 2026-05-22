/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_MATRIX3_HPP
#define NNM_MATRIX3_HPP

#include <nnm/forward.hpp>
#include <nnm/vector3.hpp>
#include <nnm/matrix2.hpp>

namespace nnm {

/**
 * 3x3 matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Matrix3 {
public:
    Vector3<Real> columns[3];

    /**
     * Initializes with identity matrix.
     */
    constexpr Matrix3()
        : columns { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } }
    {
    }

    /**
     * Cast from other matrix type.
     * @tparam Other Other matrix type.
     * @param matrix Matrix to cast from
     */
    template <typename Other>
    explicit constexpr Matrix3(const Matrix3<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x),
                      static_cast<Real>(matrix.columns[0].y),
                      static_cast<Real>(matrix.columns[0].z) },
                    { static_cast<Real>(matrix.columns[1].x),
                      static_cast<Real>(matrix.columns[1].y),
                      static_cast<Real>(matrix.columns[1].z) },
                    { static_cast<Real>(matrix.columns[2].x),
                      static_cast<Real>(matrix.columns[2].y),
                      static_cast<Real>(matrix.columns[2].z) } }
    {
    }

    /**
     * Initializes with columns.
     * @param column0 First column.
     * @param column1 Second column.
     * @param column2 Third column.
     */
    constexpr Matrix3(const Vector3<Real>& column0, const Vector3<Real>& column1, const Vector3<Real>& column2)
        : columns { column0, column1, column2 }
    {
    }

    /**
     * Initializes with elements.
     * @param col0_row0 First column, first row
     * @param col0_row1 First column, second row
     * @param col0_row2 First column, third row
     * @param col1_row0 Second column, first row
     * @param col1_row1 Second column, second row
     * @param col1_row2 Second column, third row
     * @param col2_row0 Third column, first row
     * @param col2_row1 Third column, second row
     * @param col2_row2 Third column, third row
     */
    constexpr Matrix3(
        const Real col0_row0,
        const Real col0_row1,
        const Real col0_row2,
        const Real col1_row0,
        const Real col1_row1,
        const Real col1_row2,
        const Real col2_row0,
        const Real col2_row1,
        const Real col2_row2)
        : columns { { col0_row0, col0_row1, col0_row2 },
                    { col1_row0, col1_row1, col1_row2 },
                    { col2_row0, col2_row1, col2_row2 } }
    {
    }

    /**
     * Matrix with all elements equal to value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix3 all(const Real value)
    {
        return { { value, value, value }, { value, value, value }, { value, value, value } };
    }

    /**
     * Matrix with all elements zero.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix3 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Matrix with all elements one.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix3 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Identity matrix.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix3 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } };
    }

    /**
     * Sum of matrix diagonal.
     * @return Result.
     */
    [[nodiscard]] constexpr Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2);
    }

    /**
     * Matrix determinant.
     * @return Result.
     */
    [[nodiscard]] constexpr Real determinant() const
    {
        Real det = static_cast<Real>(0);
        for (uint8_t c = 0; c < 3; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1) : -static_cast<Real>(1)) * at(c, 0) * det_minor;
        }
        return det;
    }

    /**
     * Minor matrix at column and row which is the resulting 2x2 matrix with that column and row excluded.
     * @param column Column.
     * @param row Row.
     * @return Resulting 2x2 matrix.
     */
    [[nodiscard]] constexpr Matrix2<Real> minor_matrix_at(const uint8_t column, const uint8_t row) const
    {
        Matrix2<Real> minor_matrix;
        uint8_t minor_col = 0;
        for (uint8_t c = 0; c < 3; ++c) {
            if (c == column) {
                continue;
            }
            uint8_t minor_row = 0;
            for (uint8_t r = 0; r < 3; ++r) {
                if (r == row) {
                    continue;
                }
                minor_matrix[minor_col][minor_row] = at(c, r);
                ++minor_row;
            }
            ++minor_col;
        }
        return minor_matrix;
    }

    /**
     * Minor at column and row which is the determinant of the minor matrix at that column and row.
     * @param column Column.
     * @param row Row.
     * @return Result.
     */
    [[nodiscard]] constexpr Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return minor_matrix_at(column, row).determinant();
    }

    /**
     * Minor matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 minor() const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    /**
     * Cofactor at column and row.
     * @param column
     * @param row
     * @return Result.
     */
    [[nodiscard]] constexpr Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return ((column + row) % 2 == 0 ? static_cast<Real>(1) : static_cast<Real>(-1)) * minor_at(column, row);
    }

    /**
     * Cofactor matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 cofactor() const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    /**
     * Transpose matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0) }, { at(0, 1), at(1, 1), at(2, 1) }, { at(0, 2), at(1, 2), at(2, 2) } };
    }

    /**
     * Adjugate matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 adjugate() const
    {
        return cofactor().transpose();
    }

    /**
     * Inverse without first checking if the matrix is singular.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    /**
     * Inverse which returns null if there is no inverse.
     * @return Inverse if there is one, null if not.
     */
    [[nodiscard]] constexpr std::optional<Matrix3> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    /**
     * Element-wise approximately equal.
     * @param other Other matrix.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Matrix3& other) const
    {
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                if (!nnm::approx_equal(at(c, r), other.at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * If all elements are approximately zero.
     * @return True if approximately zero, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                if (!nnm::approx_zero(at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Constant reference to column at index.
     * @param column Column.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Vector3<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    /**
     * Reference to column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector3<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    /**
     * Constant reference to element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Constant reference.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return columns[column][row];
    }

    /**
     * Reference to element at column and row.
     * @param column Column.
     * @param row Row.
     * @return Reference.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2 && row <= 2);
        return columns[column][row];
    }

    /**
     * Constant reference to column at index.
     * @param column Column.
     * @return Constant reference.
     */
    constexpr const Vector3<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    /**
     * Reference to column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector3<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column <= 2);
        return columns[column];
    }

    /**
     * Start constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* begin() const
    {
        return columns[0].begin();
    }

    /**
     * End constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* end() const
    {
        return columns[2].end();
    }

    /**
     * Start iterator.
     * @return Iterator.
     */
    Real* begin()
    {
        return columns[0].begin();
    }

    /**
     * End iterator.
     * @return Iterator.
     */
    Real* end()
    {
        return columns[2].end();
    }

    /**
     * Element-wise equality.
     * @param other Other matrix.
     * @return True if equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Element-wise inequality.
     * @param other Other matrix.
     * @return True if not equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator!=(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) != other.at(i)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Element-wise addition.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 operator+(const Matrix3& other) const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    /**
     * Element-wise addition.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix3& operator+=(const Matrix3& other)
    {
        for (uint8_t c = 0; c < 3; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 operator-(const Matrix3& other) const
    {
        Matrix3 result;
        for (uint8_t c = 0; c < 3; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix3& operator-=(const Matrix3& other)
    {
        for (uint8_t c = 0; c < 3; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    /**
     * Matrix multiplication.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 operator*(const Matrix3& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 3; ++c) {
            for (uint8_t r = 0; r < 3; ++r) {
                for (uint8_t i = 0; i < 3; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    /**
     * Matrix multiplication.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix3& operator*=(const Matrix3& other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * Matrix-vector multiplication.
     * @param vector Vector.
     * @return Resulting three-dimensional vector.
     */
    [[nodiscard]] constexpr Vector3<Real> operator*(const Vector3<Real>& vector) const
    {
        auto result = Vector3<Real>::zero();
        for (uint8_t r = 0; r < 3; ++r) {
            for (uint8_t c = 0; c < 3; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    /**
     * Element-wise multiplication with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value, at(2) * value };
    }

    /**
     * Element-wise multiplication with value.
     * @param value Value.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix3& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        at(2) *= value;
        return *this;
    }

    /**
     * Element-wise division by value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix3 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value, at(2) / value };
    }

    /**
     * Element-wise division by value.
     * @param value Value.
     * @return Reference this modified matrix.
     */
    constexpr Matrix3& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        at(2) /= value;
        return *this;
    }

    /**
     * Lexicographical comparison between elements.
     * @param other Other matrix.
     * @return True if less than, false otherwise.
     */
    [[nodiscard]] constexpr bool operator<(const Matrix3& other) const
    {
        for (uint8_t i = 0; i < 3; ++i) {
            if (at(i) < other.at(i)) {
                return true;
            }
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return false;
    }

    /**
     * Evaluates to false if all components are zero, true otherwise.
     */
    [[nodiscard]] constexpr explicit operator bool() const
    {
        for (uint8_t c = 0; c < 3; ++c) { // NOLINT(*-loop-convert)
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Element-wise multiplication with value.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param matrix Matrix.
 * @return Result.
 */
template <typename Real>
constexpr Matrix3<Real> operator*(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

/**
 * Element-wise division with value.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param matrix Matrix.
 * @return Result.
 */
template <typename Real>
constexpr Matrix3<Real> operator/(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (uint8_t c = 0; c < 3; ++c) {
        for (uint8_t r = 0; r < 3; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}
}

#endif
