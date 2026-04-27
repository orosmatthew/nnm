/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_MATRIX2_HPP
#define NNM_MATRIX2_HPP

#include <nnm/forward.hpp>
#include <nnm/vector2.hpp>

namespace nnm {

/**
 * 2x2 matrix.
 * @tparam Real Floating-point type.
 */
template <typename Real>
class Matrix2 {
public:
    Vector2<Real> columns[2];

    /**
     * Initializes with identity matrix.
     */
    constexpr Matrix2()
        : columns { { static_cast<Real>(1), static_cast<Real>(0) }, { static_cast<Real>(0), static_cast<Real>(1) } }
    {
    }

    /**
     * Cast from another matrix type.
     * @tparam Other Other matrix type.
     * @param matrix Matrix to cast from.
     */
    template <typename Other>
    explicit constexpr Matrix2(const Matrix2<Other>& matrix)
        : columns { { static_cast<Real>(matrix.columns[0].x), static_cast<Real>(matrix.columns[0].y) },
                    { static_cast<Real>(matrix.columns[1].x), static_cast<Real>(matrix.columns[1].y) } }
    {
    }

    /**
     * Initializes with columns
     * @param column0 First column
     * @param column1 Second column
     */
    constexpr Matrix2(const Vector2<Real>& column0, const Vector2<Real>& column1)
        : columns { column0, column1 }
    {
    }

    /**
     * Initializes with elements
     * @param col0_row0 First column, first row
     * @param col0_row1 First column, second row
     * @param col1_row0 Second column, first row
     * @param col1_row1 Second column, second row
     */
    constexpr Matrix2(const Real col0_row0, const Real col0_row1, const Real col1_row0, const Real col1_row1)
        : columns { { col0_row0, col0_row1 }, { col1_row0, col1_row1 } }
    {
    }

    /**
     * Matrix with all elements equal to value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix2 all(const Real value)
    {
        return { { value, value }, { value, value } };
    }

    /**
     * Matrix with all elements equal to zero.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix2 zero()
    {
        return all(static_cast<Real>(0));
    }

    /**
     * Matrix with all elements equal to one.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix2 one()
    {
        return all(static_cast<Real>(1));
    }

    /**
     * Identity matrix.
     * @return Result.
     */
    [[nodiscard]] static constexpr Matrix2 identity()
    {
        return { { static_cast<Real>(1), static_cast<Real>(0) }, { static_cast<Real>(0), static_cast<Real>(1) } };
    }

    /**
     * Sum of the matrix diagonal.
     * @return Result.
     */
    [[nodiscard]] constexpr Real trace() const
    {
        return at(0, 0) + at(1, 1);
    }

    /**
     * Determinant of matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Real determinant() const
    {
        return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
    }

    /**
     * Minor matrix at column and row. This is the element with that particular row and column excluded.
     * @param column Column
     * @param row Row
     * @return Result.
     */
    [[nodiscard]] constexpr Real minor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        const uint8_t other_column = (column + 1) % 2;
        const uint8_t other_row = (row + 1) % 2;
        return at(other_column, other_row);
    }

    /**
     * Minor matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 minor() const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    /**
     * Cofactor at column and row.
     * @param column Column
     * @param row Row
     * @return Result.
     */
    [[nodiscard]] constexpr Real cofactor_at(const uint8_t column, const uint8_t row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        return ((column + row) % 2 == 0 ? static_cast<Real>(1) : static_cast<Real>(-1)) * minor_at(column, row);
    }

    /**
     * Cofactor matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 cofactor() const
    {
        return { { cofactor_at(0, 0), cofactor_at(0, 1) }, { cofactor_at(1, 0), cofactor_at(1, 1) } };
    }

    /**
     * Transpose matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 transpose() const
    {
        return { { at(0, 0), at(1, 0) }, { at(0, 1), at(1, 1) } };
    }

    /**
     * Adjugate matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 adjugate() const
    {
        return cofactor().transpose();
    }

    /**
     * Inverse without checking if the matrix is singular first.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    /**
     * Inverse that returns null if the matrix does not have an inverse.
     * @return The inverse if there is one, null if not.
     */
    [[nodiscard]] constexpr std::optional<Matrix2> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    /**
     * Element-wise approximate equality.
     * @param other Other matrix.
     * @return True if approximately equal, false otherwise.
     */
    [[nodiscard]] constexpr bool approx_equal(const Matrix2& other) const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
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
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
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
     * @return Constant Reference.
     */
    [[nodiscard]] constexpr const Vector2<Real>& at(const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    /**
     * Reference to column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector2<Real>& at(const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
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
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
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
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1 && row <= 1);
        return columns[column][row];
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
        return columns[1].end();
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
        return columns[1].end();
    }

    /**
     * Constant Reference to column at index.
     * @param column Column.
     * @return Constant reference.
     */
    constexpr const Vector2<Real>& operator[](const uint8_t column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    /**
     * Reference to column at index.
     * @param column Column.
     * @return Reference.
     */
    constexpr Vector2<Real>& operator[](const uint8_t column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column <= 1);
        return columns[column];
    }

    /**
     * Element-wise equality.
     * @param other Other matrix.
     * @return True if equal, false otherwise.
     */
    constexpr bool operator==(const Matrix2& other) const
    {
        for (uint8_t i = 0; i < 2; ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Element-wise inequality.
     * @param other Other matrix.
     * @return True if unequal, false otherwise.
     */
    constexpr bool operator!=(const Matrix2& other) const
    {
        for (uint8_t i = 0; i < 2; ++i) {
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
    [[nodiscard]] constexpr Matrix2 operator+(const Matrix2& other) const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    /**
     * Element-wise addition.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix2& operator+=(const Matrix2& other)
    {
        for (uint8_t c = 0; c < 2; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 operator-(const Matrix2& other) const
    {
        Matrix2 result;
        for (uint8_t c = 0; c < 2; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    /**
     * Element-wise subtraction.
     * @param other Other matrix.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix2& operator-=(const Matrix2& other)
    {
        for (uint8_t c = 0; c < 2; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    /**
     * Matrix multiplication.
     * @param other Other matrix.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 operator*(const Matrix2& other) const
    {
        auto result = zero();
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                for (uint8_t i = 0; i < 2; ++i) {
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
    constexpr Matrix2& operator*=(const Matrix2& other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * Matrix-vector multiplication.
     * @param vector Vector.
     * @return Resulting two-dimensional vector.
     */
    [[nodiscard]] constexpr Vector2<Real> operator*(const Vector2<Real>& vector) const
    {
        Vector2<Real> result;
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(r) = at(0, r) * vector.at(0) + at(1, r) * vector.at(1);
        }
        return result;
    }

    /**
     * Element-wise multiplication with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value };
    }

    /**
     * Element-wise multiplication with value.
     * @param value Value.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix2& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        return *this;
    }

    /**
     * Element-wise division with value.
     * @param value Value.
     * @return Result.
     */
    [[nodiscard]] constexpr Matrix2 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value };
    }

    /**
     * Element-wise division with value.
     * @param value Value.
     * @return Reference to this modified matrix.
     */
    constexpr Matrix2& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        return *this;
    }

    /**
     * Lexicographical comparison between elements.
     * @param other Other matrix.
     * @return True if less than, false otherwise.
     */
    constexpr bool operator<(const Matrix2& other) const
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
     * Evaluates to false if all elements are zero, true otherwise.
     */
    constexpr explicit operator bool() const
    {
        for (uint8_t c = 0; c < 2; ++c) {
            for (uint8_t r = 0; r < 2; ++r) {
                if (at(c, r) != 0) {
                    return true;
                }
            }
        }
        return false;
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
constexpr Matrix2<Real> operator*(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (uint8_t c = 0; c < 2; ++c) {
        for (uint8_t r = 0; r < 2; ++r) {
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
constexpr Matrix2<Real> operator/(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (uint8_t c = 0; c < 2; ++c) {
        for (uint8_t r = 0; r < 2; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}
}

#endif
