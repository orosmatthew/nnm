/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_MATRIX4_HPP
#define NNM_MATRIX4_HPP

#include <nnm/forward.hpp>
#include <nnm/vector4.hpp>
#include <nnm/matrix3.hpp>

namespace nnm {

/**
 * 4x4 matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Matrix4 {
public:
    /**
     * Columns of matrix.
     */
    Vector4<Real> columns[4];

    /**
     * Initializes with identity matrix.
     */
    constexpr Matrix4()
        : columns { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                    { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } }

    {
    }

    /**
     * Casts from another matrix.
     * @tparam Other Other type to cast from.
     * @param matrix Other matrix.
     */
    template <typename Other>
    explicit constexpr Matrix4(const Matrix4<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x),
                      static_cast<Real>(matrix.columns[0].y),
                      static_cast<Real>(matrix.columns[0].z),
                      static_cast<Real>(matrix.columns[0].w) },
                    { static_cast<Real>(matrix.columns[1].x),
                      static_cast<Real>(matrix.columns[1].y),
                      static_cast<Real>(matrix.columns[1].z),
                      static_cast<Real>(matrix.columns[1].w) },
                    { static_cast<Real>(matrix.columns[2].x),
                      static_cast<Real>(matrix.columns[2].y),
                      static_cast<Real>(matrix.columns[2].z),
                      static_cast<Real>(matrix.columns[2].w) },
                    { static_cast<Real>(matrix.columns[3].x),
                      static_cast<Real>(matrix.columns[3].y),
                      static_cast<Real>(matrix.columns[3].z),
                      static_cast<Real>(matrix.columns[3].w) } }
    {
    }

    /**
     * Initializes with columns.
     * @param column0 First column.
     * @param column1 Second column.
     * @param column2 Third column.
     * @param column3 Fourth column.
     */
    constexpr Matrix4(
        const Vector4<Real>& column0,
        const Vector4<Real>& column1,
        const Vector4<Real>& column2,
        const Vector4<Real>& column3)
        : columns { column0, column1, column2, column3 }
    {
    }

    /**
     * Initializes with elements.
     * @param col0_row0 First column, first row.
     * @param col0_row1 First column, second row.
     * @param col0_row2 First column, third row.
     * @param col0_row3 First column, fourth row.
     * @param col1_row0 Second column, first row.
     * @param col1_row1 Second column, second row.
     * @param col1_row2 Second column, third row.
     * @param col1_row3 Second column, fourth row.
     * @param col2_row0 Third column, first row.
     * @param col2_row1 Third column, second row.
     * @param col2_row2 Third column, third row.
     * @param col2_row3 Third column, fourth row.
     * @param col3_row0 Fourth column, first row.
     * @param col3_row1 Fourth column, second row.
     * @param col3_row2 Fourth column, third row.
     * @param col3_row3 Fourth column, fourth row.
     */
    constexpr Matrix4(
        const Real col0_row0,
        const Real col0_row1,
        const Real col0_row2,
        const Real col0_row3,
        const Real col1_row0,
        const Real col1_row1,
        const Real col1_row2,
        const Real col1_row3,
        const Real col2_row0,
        const Real col2_row1,
        const Real col2_row2,
        const Real col2_row3,
        const Real col3_row0,
        const Real col3_row1,
        const Real col3_row2,
        const Real col3_row3)
        : columns { { col0_row0, col0_row1, col0_row2, col0_row3 },
                    { col1_row0, col1_row1, col1_row2, col1_row3 },
                    { col2_row0, col2_row1, col2_row2, col2_row3 },
                    { col3_row0, col3_row1, col3_row2, col3_row3 } }
    {
    }

    /**
     * Matrix with all element set to value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix4 all(const Real value)
    {
        return { { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value } };
    }

    /**
     * Matrix with all elements set to zero.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix4 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Matrix with all elements set to one.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix4 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Identity matrix.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix4 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1), static_cast<Real>(0) },
                 { static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(0), static_cast<Real>(1) } };
    }

    /**
     * Trace which is the sum of the matrix diagonal.
     * @return Result.
     */
    [[nodiscard]] constexpr Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2) + at(3, 3);
    }

    /**
     * Determinant of matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Real determinant() const
    {
        Real det = static_cast<Real>(0);
        for (uint8_t c = 0; c < 4; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1) : -static_cast<Real>(1)) * at(c, 0) * det_minor;
        }
        return det;
    }

    /**
     * Minor matrix at column and row which is the matrix where the specified column and row are removed.
     * @param column Index of column.
     * @param row Index of row.
     * @return Resulting 3x3 matrix.
     */
    [[nodiscard]] constexpr Matrix3<Real> minor_matrix_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        Matrix3<Real> minor_matrix;
        uint8_t minor_col = 0;
        for (uint8_t c = 0; c < 4; ++c) {
            if (c == column) {
                continue;
            }
            uint8_t minor_row = 0;
            for (uint8_t r = 0; r < 4; ++r) {
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
     * Minor at column and row which is the determinant of the minor matrix at the column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Result.
     */
    [[nodiscard]] constexpr Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return minor_matrix_at(column, row).determinant();
    }

    /**
     * Minor matrix which is a matrix where each element is the minor at the element.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 minor() const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    /**
     * Cofactor at column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Result.
     */
    [[nodiscard]] constexpr Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return ((column + row) % 2 == 0 ? static_cast<Real>(1) : static_cast<Real>(-1)) * minor_at(column, row);
    }

    /**
     * Cofactor matrix which is a matrix where each element is the cofactor at that element.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 cofactor() const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    /**
     * Transpose matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0), at(3, 0) },
                 { at(0, 1), at(1, 1), at(2, 1), at(3, 1) },
                 { at(0, 2), at(1, 2), at(2, 2), at(3, 2) },
                 { at(0, 3), at(1, 3), at(2, 3), at(3, 3) } };
    }

    /**
     * Adjugate matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 adjugate() const
    {
        return cofactor().transpose();
    }

    /**
     * Inverse matrix without first checking if a valid inverse if possible.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    /**
     * Inverse matrix.
     * @return Inverse matrix if one exists, null otherwise.
     */
    [[nodiscard]] constexpr std::optional<Matrix4> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    /**
     * Determines if approximately equal to another matrix.
     * @param other Other matrix.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Matrix4& other) const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Determines if all elements are approximately zero.
     * @return True if approximately all zero, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_zero() const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!at(c).approx_zero()) {
                return false;
            }
        }
        return true;
    }

    /**
     * Constant reference to column at index.
     * @param column Index of column.
     * @return Constant reference to column.
     */
    [[nodiscard]] constexpr const Vector4<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3);
        return columns[column];
    }

    /**
     * Reference to column at index.
     * @param column Index of column.
     * @return Reference to column.
     */
    constexpr Vector4<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3);
        return columns[column];
    }

    /**
     * Constant reference to element at index of column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Constant reference to element.
     */
    [[nodiscard]] constexpr const Real& at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return columns[column][row];
    }

    /**
     * Reference to element at index of column and row.
     * @param column Index of column.
     * @param row Index of row.
     * @return Reference to element.
     */
    constexpr Real& at(const uint8_t column, const uint8_t row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column <= 3 && row <= 3);
        return columns[column][row];
    }

    /**
     * Start of constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* begin() const
    {
        return columns[0].begin();
    }

    /**
     * End of constant iterator.
     * @return Constant iterator.
     */
    [[nodiscard]] const Real* end() const
    {
        return columns[3].end();
    }

    /**
     * Start of iterator.
     * @return Iterator.
     */
    Real* begin()
    {
        return columns[0].begin();
    }

    /**
     * End of iterator
     * @return Iterator
     */
    Real* end()
    {
        return columns[3].end();
    }

    /**
     * Constant reference to column at index.
     * @param index Index of column.
     * @return Constant reference to column.
     */
    constexpr const Vector4<Real>& operator[](const uint8_t index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index <= 3);
        return columns[index];
    }

    /**
     * Reference to column at index.
     * @param index
     * @return
     */
    constexpr Vector4<Real>& operator[](const uint8_t index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index <= 3);
        return columns[index];
    }

    /**
     * Element-wise equality.
     * @param other Other matrix.
     * @return True if all elements equal, false otherwise.
     */
    [[nodiscard]] constexpr bool operator==(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Element-wise inequality.
     * @param other Other matrix.
     * @return True if any elements are not equal, false otherwise.
     */
    constexpr bool operator!=(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
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
    [[nodiscard]] constexpr Matrix4 operator+(const Matrix4& other) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    /**
     * Element-wise addition.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix4& operator+=(const Matrix4& other)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 operator-(const Matrix4& other) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix4& operator-=(const Matrix4& other)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    /**
     * Matrix multiplication.
     * @param other Other matrix.
     * @return Result.
     */
    constexpr Matrix4 operator*(const Matrix4& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 4; ++c) {
            for (uint8_t r = 0; r < 4; ++r) {
                for (uint8_t i = 0; i < 4; ++i) {
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
    constexpr Matrix4& operator*=(const Matrix4& other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * Matrix-vector multiplication.
     * @param vector 4D vector.
     * @return Result.
     */
    constexpr Vector4<Real> operator*(const Vector4<Real>& vector) const
    {
        auto result = Vector4<Real>::zero();
        for (uint8_t r = 0; r < 4; ++r) {
            for (uint8_t c = 0; c < 4; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    /**
     * Matrix-scalar multiplication.
     * @param value Scalar value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 operator*(const Real value) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) * value;
        }
        return result;
    }

    /**
     * Matrix-scalar multiplication.
     * @param value Scalar value.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix4& operator*=(const Real value)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) *= value;
        }
        return *this;
    }

    /**
     * Element-wise division by value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix4 operator/(const Real value) const
    {
        Matrix4 result;
        for (uint8_t c = 0; c < 4; ++c) {
            result.at(c) = at(c) / value;
        }
        return result;
    }

    /**
     * Element-wise division by value.
     * @param value Value.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix4& operator/=(const Real value)
    {
        for (uint8_t c = 0; c < 4; ++c) {
            at(c) /= value;
        }
        return *this;
    }

    /**
     * Lexicographical comparison with another matrix.
     * @param other Other matrix.
     * @return True if less than, false otherwise.
     */
    constexpr bool operator<(const Matrix4& other) const
    {
        for (uint8_t i = 0; i < 4; ++i) {
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
     * True if any elements are non-zero, false otherwise.
     */
    constexpr explicit operator bool() const
    {
        for (uint8_t c = 0; c < 4; ++c) {
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Scalar-matrix multiplication.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param matrix Matrix.
 * @return Result.
 */
template <typename Real>
constexpr Matrix4<Real> operator*(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

/**
 * Element-wise division by value.
 * @tparam Real Floating-point type.
 * @param value Value.
 * @param matrix Matrix.
 * @return Result.
 */
template <typename Real>
constexpr Matrix4<Real> operator/(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 4; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}
}

#endif
