#pragma once

// ReSharper disable CppDFATimeOver

#include <algorithm>
#include <cmath>
#include <functional>

namespace nnm {

inline double pi = 3.141592653589793238462643383279502;
inline double epsilon = 0.00001;

template <typename Number>
Number abs(const Number value)
{
    return std::abs(value);
}

template <typename Number>
Number max(const Number a, const Number b)
{
    return std::max(a, b);
}

template <typename Number>
bool approx_zero(const Number value, Number epsilon = nnm::epsilon)
{
    Number tolerance = epsilon * nnm::abs(value);
    tolerance = nnm::max(tolerance, epsilon);
    return nnm::abs(value) <= tolerance;
}

template <typename Number>
bool approx_lte(const Number a, const Number b, Number epsilon)
{
    if (a <= b) {
        return true;
    }
    epsilon = nnm::abs(epsilon);
    Number tolerance = epsilon * nnm::max(nnm::abs(a), nnm::abs(b));
    tolerance = nnm::max(tolerance, epsilon);
    return nnm::abs(a - b) <= tolerance;
}

template <typename Number>
bool approx_equal(const Number a, const Number b, Number epsilon = nnm::epsilon)
{
    if (a == b) {
        return true;
    }
    epsilon = nnm::abs(epsilon);
    Number tolerance = epsilon * nnm::max(nnm::abs(a), nnm::abs(b));
    tolerance = nnm::max(tolerance, epsilon);
    return nnm::abs(a - b) <= tolerance;
}

template <typename Number>
bool approx_gte(const Number a, const Number b, Number epsilon)
{
    if (a >= b) {
        return true;
    }
    epsilon = nnm::abs(epsilon);
    Number tolerance = epsilon * nnm::max(nnm::abs(a), nnm::abs(b));
    tolerance = nnm::max(tolerance, epsilon);
    return nnm::abs(a - b) <= tolerance;
}

template <typename Number>
Number ceil(const Number value)
{
    return std::ceil(value);
}

template <typename Number>
Number clamp(const Number value, const Number min, const Number max)
{
    return std::clamp(value, min, max);
}

template <typename Number>
Number sqrt(const Number value)
{
    return std::sqrt(value);
}

template <typename Number>
Number pow(const Number base, const Number power)
{
    return std::pow(base, power);
}

template <typename Number>
Number sqrd(const Number value)
{
    return value * value;
}

template <typename Number>
Number floor(const Number value)
{
    return std::floor(value);
}

template <typename Number>
Number lerp(const Number from, const Number to, const Number weight)
{
    // TODO: Extra check weight between 0 and 1
    return from + weight * (to - from);
}

template <typename Number>
Number sin(const Number value)
{
    return std::sin(value);
}

template <typename Number>
Number cos(const Number value)
{
    return std::cos(value);
}

template <typename Number>
Number tan(const Number value)
{
    return std::tan(value);
}

template <typename Number>
Number round(const Number value)
{
    return std::round(value);
}

template <typename Number>
Number atan(const Number value)
{
    return std::atan(value);
}

template <typename Number>
Number atan2(const Number a, const Number b)
{
    return std::atan2(a, b);
}

template <typename Number>
Number radians(const Number degrees, Number pi = nnm::pi)
{
    return degrees * (pi / 180.0);
}

template <typename Number>
Number degrees(const Number radians, Number pi = nnm::pi)
{
    return radians * (180.0 / pi);
}

template <typename Number>
Number asin(const Number value)
{
    // TODO: Check range
    return std::asin(value);
}

template <typename Number>
Number acos(const Number value)
{
    // TODO: Check range
    return std::acos(value);
}

template <typename Number>
Number min(const Number a, const Number b)
{
    return std::min(a, b);
}

template <typename Number>
Number log2(const Number value)
{
    // TODO: Check 0 and negative
    return std::log2(value);
}

template <typename Number>
class Vector2;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
class Vector2i;

template <typename Number>
class Vector3;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
class Vector3i;

template <typename Number>
class Matrix3;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;

template <typename Number>
class Matrix4;
using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;

template <typename Number>
class Vector4;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
class Vector4i;

template <typename Number>
class Quaternion;
using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;

enum class Axis2 { x, y };
enum class Axis3 { x, y, z };
enum class Axis4 { x, y, z, w };

template <typename Number>
class Vector2 {
public:
    Number x;
    Number y;

    Vector2()
        : x(0.0)
        , y(0.0)
    {
    }

    explicit Vector2(const Vector2i& vector);

    Vector2(const Number x, const Number y)
        : x(x)
        , y(y)
    {
    }

    static Vector2 all(const Number value)
    {
        return { value, value };
    }

    static Vector2 zero()
    {
        return { 0.0, 0.0 };
    }

    static Vector2 one()
    {
        return { 1.0, 1.0 };
    }

    [[nodiscard]] Vector2 abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    [[nodiscard]] Number aspect_ratio() const
    {
        return x / y;
    }

    [[nodiscard]] Vector2 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y) };
    }

    [[nodiscard]] Vector2 clamp(const Vector2& min, const Vector2& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] Vector2 normalize() const
    {
        Vector2 result;
        if (const Number length = this->length(); length > 0) {
            const Number inverse_length = 1.0 / length;
            result = *this * inverse_length;
        }
        return result;
    }

    [[nodiscard]] Vector2 direction_to(const Vector2& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] Number distance_sqrd_to(const Vector2& to) const
    {
        const Number diff_x = to.x - x;
        const Number diff_y = to.y - y;
        return nnm::sqrd(diff_x) + nnm::sqrd(diff_y);
    }

    [[nodiscard]] Number distance_to(const Vector2& to) const
    {
        return nnm::sqrt(this->distance_sqrd_to(to));
    }

    [[nodiscard]] Vector2 floor() const
    {
        return { nnm::floor(x), nnm::floor(y) };
    }

    [[nodiscard]] Number length_sqrd() const
    {
        return nnm::sqrd(x) + nnm::sqrd(y);
    }

    [[nodiscard]] Number length() const
    {
        return nnm::sqrt(length_sqrd());
    }

    [[nodiscard]] Vector2 lerp(const Vector2& to, const Number weight) const
    {
        return *this * (1.0 - weight) + to * weight;
    }

    [[nodiscard]] Axis2 max_axis() const
    {
        if (x > y) {
            return Axis2::x;
        }
        if (y > x) {
            return Axis2::y;
        }
        return Axis2::x;
    }

    [[nodiscard]] Axis2 min_axis() const
    {
        if (x < y) {
            return Axis2::x;
        }
        if (y < x) {
            return Axis2::y;
        }
        return Axis2::x;
    }

    [[nodiscard]] bool approx_equal(const Vector2& other, const Number epsilon = nnm::epsilon) const
    {
        return nnm::approx_equal(x, other.x, epsilon) && nnm::approx_equal(y, other.y, epsilon);
    }

    [[nodiscard]] bool approx_zero(Number epsilon = nnm::epsilon) const
    {
        return nnm::approx_zero(x, epsilon) && nnm::approx_zero(y, epsilon);
    }

    [[nodiscard]] Number dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] Vector2 reflect(const Vector2& normal) const
    {
        const Number dot = this->dot(normal);
        Vector2 result;
        result.x = x - 2.0 * normal.x * dot;
        result.y = y - 2.0 * normal.y * dot;
        return result;
    }

    [[nodiscard]] Vector2 rotate(const Number angle) const
    {
        Vector2 result;
        result.x = x * nnm::cos(angle) - y * nnm::sin(angle);
        result.y = x * nnm::sin(angle) + y * nnm::cos(angle);
        return result;
    }

    [[nodiscard]] Vector2 inverse() const
    {
        return { 1.0 / x, 1.0 / y };
    }

    [[nodiscard]] Vector2 clamp_length(const Number min, const Number max) const
    {
        if (const Number length_sqr = length_sqrd(); length_sqr > 0.0) {
            auto norm = normalize();
            if (const Number length = nnm::sqrt(length_sqr); length < min) {
                return norm * min;
            }
            else if (length > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] bool operator!=(const Vector2& other) const
    {
        return x != other.x || y != other.y;
    }

    [[nodiscard]] Vector2 operator*(const Vector2& other) const
    {
        return { x * other.x, y * other.y };
    }

    Vector2& operator*=(const Vector2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    [[nodiscard]] Vector2 operator*(Number value) const
    {
        return { x * value, y * value };
    }

    Vector2& operator*=(Number value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    [[nodiscard]] Vector2 operator+(const Vector2& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] Vector2 operator-(const Vector2& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    [[nodiscard]] Vector2 operator/(const Vector2& other) const
    {
        return { x / other.x, y / other.y };
    }

    Vector2& operator/=(const Vector2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    [[nodiscard]] Vector2 operator/(Number value) const
    {
        return { x / value, y / value };
    }

    Vector2& operator/=(Number value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector2& other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector2& other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        return true;
    }

    [[nodiscard]] bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] bool operator>(const Vector2& other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector2& other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        return true;
    }

    [[nodiscard]] Number& operator[](const int index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
    }

    [[nodiscard]] Number& operator[](const Axis2 axis)
    {
        switch (axis) {
        case Axis2::x:
            return x;
        case Axis2::y:
            return y;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector2 operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector2 operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0.0 || y != 0.0;
    }
};

class Vector2i {
public:
    int x;
    int y;

    Vector2i()
        : x(0)
        , y(0)
    {
    }

    Vector2i(const int x, const int y)
        : x(x)
        , y(y)
    {
    }

    static Vector2i all(int value)
    {
        return { value, value };
    }

    static Vector2i zero()
    {
        return { 0, 0 };
    }

    static Vector2i one()
    {
        return { 1, 1 };
    }

    [[nodiscard]] Vector2i abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    template <typename Number>
    [[nodiscard]] Number aspect_ratio() const
    {
        return static_cast<Number>(x) / static_cast<Number>(y);
    }

    [[nodiscard]] Vector2i clamp(const Vector2i& min, const Vector2i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    template <typename Number>
    [[nodiscard]] Number length() const
    {
        return sqrt(static_cast<Number>(length_sqrd()));
    }

    [[nodiscard]] Axis2 max_axis() const
    {
        if (x > y) {
            return Axis2::x;
        }
        if (y > x) {
            return Axis2::y;
        }
        return Axis2::x;
    }

    [[nodiscard]] Axis2 min_axis() const
    {
        if (x < y) {
            return Axis2::x;
        }
        if (y < x) {
            return Axis2::y;
        }
        return Axis2::x;
    }

    [[nodiscard]] bool operator!=(const Vector2i& other) const
    {
        return x != other.x || y != other.y;
    }

    [[nodiscard]] Vector2i operator%(const Vector2i& other) const
    {
        return { x % other.x, y % other.y };
    }

    Vector2i& operator%=(const Vector2i& other)
    {
        x %= other.x;
        y %= other.y;
        return *this;
    }

    [[nodiscard]] Vector2i operator%(const int value) const
    {
        return { x % value, y % value };
    }

    Vector2i& operator%=(const int value)
    {
        x %= value;
        y %= value;
        return *this;
    }

    [[nodiscard]] Vector2i operator*(const Vector2i& other) const
    {
        return { x * other.x, y * other.y };
    }

    Vector2i& operator*=(const Vector2i& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    [[nodiscard]] Vector2i operator*(const int value) const
    {
        return { x * value, y * value };
    }

    Vector2i& operator*=(const int value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    [[nodiscard]] Vector2i operator+(const Vector2i& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2i& operator+=(const Vector2i& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] Vector2i operator-(const Vector2i& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2i& operator-=(const Vector2i& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    [[nodiscard]] Vector2i operator/(const Vector2i& other) const
    {
        return { x / other.x, y / other.y };
    }

    Vector2i& operator/=(const Vector2i& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    [[nodiscard]] Vector2i operator/(const int value) const
    {
        return { x / value, y / value };
    }

    Vector2i& operator/=(const int value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector2i& other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector2i& other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        return true;
    }

    [[nodiscard]] bool operator==(const Vector2i& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] bool operator>(const Vector2i& other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector2i& other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        return true;
    }

    [[nodiscard]] int& operator[](const int index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return x;
        }
    }

    [[nodiscard]] int& operator[](const Axis2 axis)
    {
        switch (axis) {
        case Axis2::x:
            return x;
        case Axis2::y:
            return y;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector2i operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector2i operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0 || y != 0;
    }
};

template <typename Number>
class Vector3 {
public:
    union {
        struct {
            Number x;
            Number y;
            Number z;
        };
        Number data[3];
    };

    Vector3()
        : x(0.0)
        , y(0.0)
        , z(0.0)
    {
    }

    explicit Vector3(Vector3i vector);

    Vector3(const Number x, const Number y, const Number z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static Vector3 all(Number value)
    {
        return { value, value, value };
    }

    static Vector3 zero()
    {
        return { 0.0, 0.0, 0.0 };
    }

    static Vector3 one()
    {
        return { 1.0, 1.0, 1.0 };
    }

    [[nodiscard]] Vector3 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] Vector3 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z) };
    }

    [[nodiscard]] Vector3 clamp(const Vector3 min, const Vector3 max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] Vector3 normalize() const
    {
        Vector3 result;
        if (const auto length = this->length(); length > 0) {
            const Number inverse_length = 1.0 / length;
            result = *this * inverse_length;
        }
        return result;
    }

    [[nodiscard]] Vector3 direction_to(const Vector3 to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] Number distance_sqrd_to(const Vector3 to) const
    {
        const Number diff_x = to.x - x;
        const Number diff_y = to.y - y;
        const Number diff_z = to.z - z;
        return nnm::sqrd(diff_x) + nnm::sqrd(diff_y) + nnm::sqrd(diff_z);
    }

    [[nodiscard]] Number distance_to(const Vector3 to) const
    {
        return nnm::sqrt(this->distance_sqrd_to(to));
    }

    [[nodiscard]] Vector3 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z) };
    }

    [[nodiscard]] Number length_sqrd() const
    {
        return nnm::sqrd(x) + nnm::sqrd(y) + nnm::sqrd(z);
    }

    [[nodiscard]] Number length() const
    {
        return nnm::sqrt(length_sqrd());
    }

    [[nodiscard]] Vector3 lerp(const Vector3 to, const Number weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    [[nodiscard]] Axis3 max_axis() const
    {
        Number max_val = x;
        auto max_axis = Axis3::x;
        if (y > max_val) {
            max_val = y;
            max_axis = Axis3::y;
        }
        if (z > max_val) {
            max_axis = Axis3::z;
        }
        return max_axis;
    }

    [[nodiscard]] Axis3 min_axis() const
    {
        Number min_val = x;
        auto min_axis = Axis3::x;
        if (y < min_val) {
            min_val = y;
            min_axis = Axis3::y;
        }
        if (z < min_val) {
            min_axis = Axis3::z;
        }
        return min_axis;
    }

    [[nodiscard]] bool approx_equal(const Vector3 other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z);
    }

    [[nodiscard]] bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z);
    }

    [[nodiscard]] Number dot(const Vector3 other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] Vector3 cross(Vector3 other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    [[nodiscard]] Vector3 reflect(const Vector3 normal) const
    {
        Vector3 result;
        const Number dot = x * normal.x + y * normal.y + z * normal.z;
        result.x = x - 2.0f * normal.x * dot;
        result.y = y - 2.0f * normal.y * dot;
        result.z = z - 2.0f * normal.z * dot;
        return result;
    }

    [[nodiscard]] Vector3 inverse() const
    {
        return { 1.0f / x, 1.0f / y, 1.0f / z };
    }

    [[nodiscard]] Vector3 clamp_length(const Number min, const Number max) const
    {
        // TODO: add checks for min/max
        if (const Number length_sqr = length_sqrd(); length_sqr > 0.0) {
            auto norm = normalize();
            if (const Number length = nnm::sqrt(length_sqr); length < min) {
                return norm * min;
            }
            else if (length > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] Vector3 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z) };
    }

    [[nodiscard]] Number angle(const Vector3 other) const
    {
        return nnm::atan2(this->cross(other).length(), this->dot(other));
    }

    [[nodiscard]] Vector3 rotate(Vector3 axis, Number angle) const
    {
        // TODO: maybe just check normalization
        axis = axis.normalize();
        // Rodrigues rotation formula
        return *this * nnm::cos(angle) + axis.cross(*this) * nnm::sin(angle)
            + axis * (1 - nnm::cos(angle)) * axis.dot(*this);
    }

    [[nodiscard]] Vector3 rotate(const Matrix3<Number>& matrix) const;

    [[nodiscard]] Vector3 transform(const Matrix4<Number>& matrix) const;

    [[nodiscard]] bool operator!=(const Vector3 other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    [[nodiscard]] Vector3 operator*(const Vector3 other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    Vector3& operator*=(const Vector3 other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    [[nodiscard]] Vector3 operator*(const Number val) const
    {
        return { x * val, y * val, z * val };
    }

    Vector3& operator*=(const Number val)
    {
        x *= val;
        y *= val;
        z *= val;
        return *this;
    }

    [[nodiscard]] Vector3 operator+(Vector3 other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector3& operator+=(Vector3 other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    [[nodiscard]] Vector3 operator-(const Vector3& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vector3& operator-=(const Vector3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    [[nodiscard]] Vector3 operator/(Vector3 other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    Vector3& operator/=(Vector3 other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    [[nodiscard]] Vector3 operator/(Number val) const
    {
        return { x / val, y / val, z / val };
    }

    Vector3& operator/=(Number val)
    {
        x /= val;
        y /= val;
        z /= val;

        return *this;
    }

    [[nodiscard]] bool operator<(Vector3 other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector3 other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        return true;
    }

    [[nodiscard]] bool operator==(const Vector3 other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] bool operator>(const Vector3 other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector3 other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        return true;
    }

    [[nodiscard]] Number& operator[](const int index)
    {
        return data[index];
    }

    [[nodiscard]] const Number& operator[](const int index) const
    {
        return data[index];
    }

    [[nodiscard]] Number& operator[](const Axis3 axis)
    {
        switch (axis) {
        case Axis3::x:
            return x;
        case Axis3::y:
            return y;
        case Axis3::z:
            return z;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector3 operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] Vector3 operator-() const
    {
        return { -x, -y, -z };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0.0 || y != 0.0 || z != 0.0;
    }
};

class Vector3i {
public:
    int x;
    int y;
    int z;

    Vector3i()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    template <typename Number>
    explicit Vector3i(Vector3<Number> vector)
        : x(static_cast<int>(vector.x))
        , y(static_cast<int>(vector.y))
        , z(static_cast<int>(vector.z))
    {
    }

    Vector3i(const int x, const int y, const int z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static Vector3i all(const int value)
    {
        return { value, value, value };
    }

    static Vector3i zero()
    {
        return { 0, 0, 0 };
    }

    static Vector3i one()
    {
        return { 1, 1, 1 };
    }

    [[nodiscard]] Vector3i abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] Vector3i clamp(const Vector3i min, const Vector3i max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    template <typename Number>
    [[nodiscard]] Number length() const
    {
        return sqrt(static_cast<Number>(length_sqrd()));
    }

    [[nodiscard]] Axis3 max_axis() const
    {
        int max_val = x;
        auto max_axis = Axis3::x;
        if (y > max_val) {
            max_val = y;
            max_axis = Axis3::y;
        }
        if (z > max_val) {
            max_axis = Axis3::z;
        }
        return max_axis;
    }

    [[nodiscard]] Axis3 min_axis() const
    {
        int min_val = x;
        auto min_axis = Axis3::x;
        if (y < min_val) {
            min_val = y;
            min_axis = Axis3::y;
        }
        if (z < min_val) {
            min_axis = Axis3::z;
        }
        return min_axis;
    }

    [[nodiscard]] bool operator!=(const Vector3i other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    [[nodiscard]] Vector3i operator%(const Vector3i other) const
    {
        return { x % other.x, y % other.y, z % other.z };
    }

    Vector3i& operator%=(Vector3i other)
    {
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return *this;
    }

    [[nodiscard]] Vector3i operator%(const int val) const
    {
        return { x % val, y % val, z % val };
    }

    Vector3i& operator%=(const int val)
    {
        x %= val;
        y %= val;
        z %= val;
        return *this;
    }

    [[nodiscard]] Vector3i operator*(const Vector3i other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    Vector3i& operator*=(const Vector3i other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    [[nodiscard]] Vector3i operator+(const Vector3i& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector3i& operator+=(const Vector3i& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    [[nodiscard]] Vector3i operator-(Vector3i other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vector3i& operator-=(const Vector3i other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    [[nodiscard]] Vector3i operator/(const Vector3i other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    Vector3i& operator/=(const Vector3i other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    [[nodiscard]] Vector3i operator/(const int val) const
    {
        return { x / val, y / val, z / val };
    }

    Vector3i& operator/=(const int val)
    {
        x /= val;
        y /= val;
        z /= val;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector3i other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector3i other) const
    {
        return *this < other || *this == other;
    }

    [[nodiscard]] bool operator==(const Vector3i other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] bool operator>(const Vector3i other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector3i other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        return true;
    }

    [[nodiscard]] int& operator[](const int index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
        }
    }

    [[nodiscard]] int& operator[](const Axis3 axis)
    {
        switch (axis) {
        case Axis3::x:
            return x;
        case Axis3::y:
            return y;
        case Axis3::z:
            return z;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector3i operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] Vector3i operator-() const
    {
        return { -x, -y, -z };
    }
};

template <typename Number>
class Vector4 {
public:
    Number x;
    Number y;
    Number z;
    Number w;

    Vector4()
        : x(0.0)
        , y(0.0)
        , z(0.0)
        , w(0.0)
    {
    }

    static Vector4 all(const Number value)
    {
        return { value, value, value, value };
    }

    Vector4(const Number x, const Number y, const Number z, const Number w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    static Vector4 zero()
    {
        return { 0.0, 0.0, 0.0, 0.0 };
    }

    static Vector4 one()
    {
        return { 1.0, 1.0, 1.0, 1.0 };
    }

    [[nodiscard]] Vector4 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z), nnm::abs(w) };
    }

    [[nodiscard]] Vector4 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z), nnm::ceil(w) };
    }

    [[nodiscard]] Vector4 clamp(const Vector4 min, const Vector4 max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    [[nodiscard]] Vector4 normalized() const
    {
        Vector4 result;
        if (const Number len = length(); len > 0) {
            const Number inverse_length = 1.0f / len;
            result = *this * inverse_length;
        }
        return result;
    }

    [[nodiscard]] Vector4 direction_to(const Vector4 to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] Number distance_sqrd_to(const Vector4 to) const
    {
        const Number diff_x = to.x - x;
        const Number diff_y = to.y - y;
        const Number diff_z = to.z - z;
        const Number diff_w = to.w - w;
        return nnm::sqrd(diff_x) + nnm::sqrd(diff_y) + nnm::sqrd(diff_z) + nnm::sqrd(diff_w);
    }

    [[nodiscard]] Number distance_to(const Vector4 to) const
    {
        return nnm::sqrt(distance_sqrd_to(to));
    }

    [[nodiscard]] Vector4 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z), nnm::floor(w) };
    }

    [[nodiscard]] Number length_sqrd() const
    {
        return nnm::sqrd(x) + nnm::sqrd(y) + nnm::sqrd(z) + nnm::sqrd(w);
    }

    [[nodiscard]] Number length() const
    {
        return nnm::sqrt(length_sqrd());
    }

    [[nodiscard]] Vector4 lerp(const Vector4 to, const Number weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    [[nodiscard]] Axis4 min_axis() const
    {
        Number min_val = x;
        auto min_axis = Axis4::x;
        if (y < min_val) {
            min_val = y;
            min_axis = Axis4::y;
        }
        if (z < min_val) {
            min_val = z;
            min_axis = Axis4::z;
        }
        if (w < min_val) {
            min_axis = Axis4::w;
        }
        return min_axis;
    }

    [[nodiscard]] Axis4 max_axis() const
    {
        Number max_val = x;
        auto max_axis = Axis4::x;
        if (y > max_val) {
            max_val = y;
            max_axis = Axis4::y;
        }
        if (z > max_val) {
            max_val = z;
            max_axis = Axis4::z;
        }
        if (w > max_val) {
            max_axis = Axis4::w;
        }
        return max_axis;
    }

    [[nodiscard]] bool is_equal_approx(const Vector4 other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] bool is_zero_approx() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z) && nnm::approx_zero(w);
    }

    [[nodiscard]] Number dot(const Vector4 other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] Vector4 inverse() const
    {
        return { 1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w };
    }

    [[nodiscard]] Vector4 length_clamped(const Number min, const Number max) const
    {
        auto result = *this;
        if (const Number length_sqr = length_sqrd(); length_sqr > 0.0f) {
            result = normalized();
            if (const Number length = sqrt(length_sqr); length < min) {
                return result * min;
            }
            else if (length > max) {
                return result * max;
            }
        }
        return result;
    }

    [[nodiscard]] Vector4 rounded() const
    {
        return { round(x), round(y), round(z), round(w) };
    }

    [[nodiscard]] bool operator!=(const Vector4 other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] Vector4 operator*(const Vector4 other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4& operator*=(const Vector4 other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator*(const Number value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    Vector4& operator*=(const Number value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    [[nodiscard]] Vector4 operator+(const Vector4 other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4& operator+=(const Vector4 other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator-(Vector4 other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4& operator-=(const Vector4 other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator/(const Vector4 other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    Vector4& operator/=(const Vector4 other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator/(const Number value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    Vector4& operator/=(const Number value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector4 other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        if (w != other.w) {
            return w < other.w;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector4 other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        if (w != other.w) {
            return w < other.w;
        }
        return true;
    }

    [[nodiscard]] bool operator==(const Vector4 other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] bool operator>(const Vector4 other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        if (w != other.w) {
            return w > other.w;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector4 other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        if (w != other.w) {
            return w > other.w;
        }
        return true;
    }

    [[nodiscard]] Number& operator[](const int index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            return x;
        }
    }

    [[nodiscard]] const Number& operator[](const int index) const
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            return x;
        }
    }

    [[nodiscard]] Number& operator[](const Axis4 axis)
    {
        switch (axis) {
        case Axis4::x:
            return x;
        case Axis4::y:
            return y;
        case Axis4::z:
            return z;
        case Axis4::w:
            return w;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector4 operator+() const
    {
        return { x, y, z, w };
    }

    [[nodiscard]] Vector4 operator-() const
    {
        return { -x, -y, -z, -w };
    }
};

class Vector4i {
public:
    int x;
    int y;
    int z;
    int w;

    Vector4i()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    {
    }

    template <typename Number>
    explicit Vector4i(const Vector4<Number>& vector);

    Vector4i(const int x, const int y, const int z, const int w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    static Vector4i all(const int value)
    {
        return { value, value, value, value };
    }

    static Vector4i zero()
    {
        return { 0, 0, 0, 0 };
    }

    static Vector4i one()
    {
        return { 1, 1, 1, 1 };
    }

    [[nodiscard]] Vector4i abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z), nnm::abs(w) };
    }

    [[nodiscard]] Vector4i clamped(const Vector4i min, const Vector4i max) const
    {
        return { clamp(x, min.x, max.x), clamp(y, min.y, max.y), clamp(z, min.z, max.z), clamp(w, min.w, max.w) };
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    template <typename Number>
    [[nodiscard]] Number length() const
    {
        return nnm::sqrt(static_cast<Number>(length_sqrd()));
    }

    [[nodiscard]] Axis4 max_axis() const
    {
        int max_val = x;
        auto max_axis = Axis4::x;
        if (y > max_val) {
            max_val = y;
            max_axis = Axis4::y;
        }
        if (z > max_val) {
            max_val = z;
            max_axis = Axis4::z;
        }
        if (w > max_val) {
            max_axis = Axis4::w;
        }
        return max_axis;
    }

    [[nodiscard]] Axis4 min_axis() const
    {
        int min_val = x;
        auto min_axis = Axis4::x;
        if (y < min_val) {
            min_val = y;
            min_axis = Axis4::y;
        }
        if (z < min_val) {
            min_val = z;
            min_axis = Axis4::z;
        }
        if (w < min_val) {
            min_axis = Axis4::w;
        }
        return min_axis;
    }

    [[nodiscard]] bool operator!=(const Vector4i other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] Vector4i operator%(const Vector4i other) const
    {
        return { x % other.x, y & other.y, z % other.z, w % other.w };
    }

    Vector4i& operator%=(const Vector4i other)
    {
        x %= other.x;
        y %= other.y;
        z %= other.z;
        w %= other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator%(const int value) const
    {
        return { x % value, y % value, z % value, w % value };
    }

    Vector4i& operator%=(const int value)
    {
        x %= value;
        y %= value;
        z %= value;
        w %= value;
        return *this;
    }

    [[nodiscard]] Vector4i operator*(const Vector4i other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4i& operator*=(const Vector4i other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator*(const int value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    Vector4i& operator*=(const int value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    [[nodiscard]] Vector4i operator+(const Vector4i other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4i& operator+=(const Vector4i other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator-(const Vector4i other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4i& operator-=(const Vector4i other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator/(const Vector4i other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    Vector4i& operator/=(const Vector4i other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator/(const int value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    Vector4i& operator/=(const int value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector4i other) const
    {
        if (x != other.x) {
            return x < other.x;
        }
        if (y != other.y) {
            return y < other.y;
        }
        if (z != other.z) {
            return z < other.z;
        }
        if (w != other.w) {
            return w < other.w;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Vector4i other) const
    {
        return *this < other || *this == other;
    }

    [[nodiscard]] bool operator==(const Vector4i other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] bool operator>(const Vector4i other) const
    {
        if (x != other.x) {
            return x > other.x;
        }
        if (y != other.y) {
            return y > other.y;
        }
        if (z != other.z) {
            return z > other.z;
        }
        if (w != other.w) {
            return w > other.w;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Vector4i other) const
    {
        return *this > other || *this == other;
    }

    [[nodiscard]] int& operator[](const int index)
    {
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            return x;
        }
    }

    [[nodiscard]] int& operator[](const Axis4 axis)
    {
        switch (axis) {
        case Axis4::x:
            return x;
        case Axis4::y:
            return y;
        case Axis4::z:
            return z;
        case Axis4::w:
            return w;
        default:
            return x;
        }
    }

    [[nodiscard]] Vector4i operator+() const
    {
        return { x, y, z, w };
    }

    [[nodiscard]] Vector4i operator-() const
    {
        return { -x, -y, -z, -w };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0 || y != 0 || z != 0 || w != 0;
    }
};

template <typename Number>
class Quaternion {
public:
    using Vector = Vector4<Number>;

    union {
        Vector data;
        struct {
            float x;
            float y;
            float z;
            float w;
        };
    };

    Quaternion()
        : data(0.0, 0.0, 0.0, 0.0)
    {
    }

    explicit Quaternion(const Vector& vector)
        : data(vector)
    {
    }

    Quaternion(float x, float y, float z, float w)
        : data(x, y, z, w)
    {
    }

    [[nodiscard]] static Quaternion from_axis_angle(const Vector3<Number>& axis, const float angle)
    {
        Vector data;
        if (const float axis_length = axis.length(); axis_length == 0) {
            data.x = 0.0f;
            data.y = 0.0f;
            data.z = 0.0f;
            data.w = 0.0f;
        }
        else {
            const float angle_sin = sin(angle * 0.5f);
            const float angle_cos = cos(angle * 0.5f);
            const float s = angle_sin / axis_length;
            data.x = axis.x * s;
            data.y = axis.y * s;
            data.z = axis.z * s;
            data.w = angle_cos;
        }

        return Quaternion(data);
    }

    [[nodiscard]] static Quaternion from_euler(const Vector3<Number>& euler)
    {
        const Vector3 half = euler / 2.0f;

        const float cos_x = cos(half.x);
        const float sin_x = sin(half.x);
        const float cos_y = cos(half.y);
        const float sin_y = sin(half.y);
        const float cos_z = cos(half.z);
        const float sin_z = sin(half.z);

        return { sin_x * cos_y * sin_z + cos_x * sin_y * cos_z,
                 sin_x * cos_y * cos_z - cos_x * sin_y * sin_z,
                 -sin_x * sin_y * cos_z + cos_x * cos_y * sin_z,
                 sin_x * sin_y * sin_z + cos_x * cos_y * cos_z };
    }

    [[nodiscard]] static Quaternion from_matrix(const Matrix3<Number>& matrix)
    {
        const float trace = matrix.trace();
        Quaternion result;

        if (trace > 0.0f) {
            float s = sqrt(trace + 1.0f);
            result.w = s * 0.5f;
            s = 0.5f / s;

            result.x = (matrix[1][2] - matrix[2][1]) * s;
            result.y = (matrix[2][0] - matrix[0][2]) * s;
            result.z = (matrix[0][1] - matrix[1][0]) * s;
        }
        else {
            int i;
            if (matrix[0][0] < matrix[1][1]) {
                i = matrix[1][1] < matrix[2][2] ? 2 : 1;
            }
            else {
                i = matrix[0][0] < matrix[2][2] ? 2 : 0;
            }
            const int j = (i + 1) % 3;
            const int k = (i + 2) % 3;

            float s = sqrt(matrix[i][i] - matrix[j][j] - matrix[k][k] + 1.0f);
            result[i] = s * 0.5f;
            s = 0.5f / s;

            result.w = (matrix[j][k] - matrix[k][j]) * s;
            result[j] = (matrix[i][j] + matrix[j][i]) * s;
            result[k] = (matrix[i][k] + matrix[k][i]) * s;
        }

        return result;
    }

    [[nodiscard]] static Quaternion from_vector3_to_vector3(const Vector3<Number>& from, const Vector3<Number>& to)
    {
        Quaternion result;

        const float cos_2_theta = from.x * to.x + from.y * to.y + from.z * to.z; // Vector3DotProduct(from, to)
        const Vector3 cross = {
            from.y * to.z - from.z * to.y, from.z * to.x - from.x * to.z, from.x * to.y - from.y * to.x
        }; // Vector3CrossProduct(from, to)

        result.x = cross.x;
        result.y = cross.y;
        result.z = cross.z;
        result.w = 1.0f + cos_2_theta;

        // QuaternionNormalize(q);
        // NOTE: Normalize to essentially nlerp the original and identity to 0.5
        const Quaternion q = result;
        float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        if (length == 0.0f)
            length = 1.0f;
        const float ilength = 1.0f / length;

        result.x = q.x * ilength;
        result.y = q.y * ilength;
        result.z = q.z * ilength;
        result.w = q.w * ilength;

        return result;
    }

    [[nodiscard]] static Quaternion from_direction(const Vector3<Number>& dir, const Vector3<Number>& up)
    {
        Quaternion result;
        const float angle = atan2(dir.x, dir.z);
        result.x = up.x;
        result.y = up.y * sin(angle / 2.0f);
        result.z = up.z;
        result.w = cos(angle / 2.0f);
        return result;
    }

    [[nodiscard]] float angle_to(const Quaternion& to) const
    {
        const float dot = this->dot(to);
        return acos(clamp(sqrd(dot) * 2.0f - 1.0f, -1.0f, 1.0f));
    }

    [[nodiscard]] float dot(const Quaternion& other) const
    {
        return data.dot(other.data);
    }

    [[nodiscard]] Vector3<Number> euler() const
    {
        return matrix().euler();
    }

    [[nodiscard]] Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] bool is_equal_approx(const Quaternion& other, Number epsilon) const
    {
        return nnm::approx_equal(x, other.x, epsilon) && nnm::approx_equal(y, other.y, epsilon)
            && nnm::approx_equal(z, other.z, epsilon) && nnm::approx_equal(w, other.w, epsilon);
    }

    [[nodiscard]] bool is_zero_approx(Number epsilon) const
    {
        return nnm::approx_zero(x, epsilon) && nnm::approx_zero(y, epsilon) && nnm::approx_zero(z, epsilon)
            && nnm::approx_zero(w, epsilon);
    }

    [[nodiscard]] float length() const
    {
        return data.length();
    }

    [[nodiscard]] float length_sqrd() const
    {
        return data.length_sqrd();
    }

    [[nodiscard]] Quaternion spherical_linear_interpolate(
        const Quaternion& to, const Number weight, Number epsilon) const
    {
        float dot = this->dot(to);

        Quaternion to_new;
        if (dot < 0.0f) {
            dot = -dot;
            to_new = -to;
        }
        else {
            to_new = to;
        }

        float scale0;
        float scale1;
        if (1.0f - dot > epsilon) {
            const float omega = acos(dot);
            const float omega_sin = sin(omega);
            scale0 = sin((1.0f - weight) * omega) / omega_sin;
            scale1 = sin(weight * omega) / omega_sin;
        }
        else {
            scale0 = 1.0f - weight;
            scale1 = weight;
        }

        return { scale0 * x + scale1 * to_new.x,
                 scale0 * y + scale1 * to_new.y,
                 scale0 * z + scale1 * to_new.z,
                 scale0 * w + scale1 * to_new.w };
    }

    [[nodiscard]] Matrix3<Number> matrix() const;

    [[nodiscard]] Quaternion normalize() const;

    [[nodiscard]] bool operator!=(const Quaternion& other) const
    {
        return data != other.data;
    }

    [[nodiscard]] inline Quaternion operator*(const Quaternion& other) const
    {
        return { w * other.x + x * other.w + y * other.z - z * other.y,
                 w * other.y + y * other.w + z * other.x - x * other.z,
                 w * other.z + z * other.w + x * other.y - y * other.x,
                 w * other.w - x * other.x - y * other.y - z * other.z };
    }

    inline void operator*=(const Quaternion& other)
    {
        const float new_x = w * other.x + x * other.w + y * other.z - z * other.y;
        const float new_y = w * other.y + y * other.w + z * other.x - x * other.z;
        const float new_z = w * other.z + z * other.w + x * other.y - y * other.x;
        w = w * other.w - x * other.x - y * other.y - z * other.z;
        x = new_x;
        y = new_y;
        z = new_z;
    }

    [[nodiscard]] Quaternion operator*(float value) const
    {
        return Quaternion(data * value);
    }

    void operator*=(float value)
    {
        data *= value;
    }

    [[nodiscard]] Quaternion operator*(int value) const
    {
        return Quaternion(data * value);
    }

    void operator*=(int value)
    {
        data *= value;
    }

    [[nodiscard]] inline Quaternion operator+(const Quaternion& other) const
    {
        return Quaternion(data + other.data);
    }

    inline void operator+=(const Quaternion& other)
    {
        data += other.data;
    }

    [[nodiscard]] inline Quaternion operator-(const Quaternion& other) const
    {
        return Quaternion(data - other.data);
    }

    inline void operator-=(const Quaternion& other)
    {
        data -= other.data;
    }

    [[nodiscard]] Quaternion operator/(Number value) const
    {
        return Quaternion(data * (1.0f / value));
    }

    void operator/=(const Number value)
    {
        data *= 1.0 / value;
    }

    [[nodiscard]] bool operator==(const Quaternion& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] float& operator[](int index)
    {
        return data[index];
    }

    [[nodiscard]] const float& operator[](int index) const
    {
        return data[index];
    }

    [[nodiscard]] Quaternion operator+() const
    {
        return Quaternion(data);
    }

    [[nodiscard]] Quaternion operator-() const
    {
        return Quaternion(-data);
    }
};

template <typename Number>
class Matrix3 {
public:
    using Column = Vector3<Number>;

    Column col0;
    Column col1;
    Column col2;

    Matrix3()
        : col0(Column(1.0f, 0.0f, 0.0f))
        , col1(Column(0.0f, 1.0f, 0.0f))
        , col2(Column(0.0f, 0.0f, 1.0f))
    {
    }

    Matrix3(const Column& col0, const Column& col1, const Column& col2)
        : col0(col0)
        , col1(col1)
        , col2(col2)
    {
    }

    Matrix3(float c0r0, float c0r1, float c0r2, float c1r0, float c1r1, float c1r2, float c2r0, float c2r1, float c2r2)
        : col0(Column(c0r0, c0r1, c0r2))
        , col1(Column(c1r0, c1r1, c1r2))
        , col2(Column(c2r0, c2r1, c2r2))
    {
    }

    [[nodiscard]] static Matrix3 from_axis_angle(const Vector3<Number>& axis, const float angle)
    {
        Matrix3 result;

        const Vector3 axis_norm = axis.normalize();

        const float sin_angle = sin(angle);
        const float cos_angle = cos(angle);
        const float t = 1.0f - cos_angle;

        result[0][0] = axis_norm.x * axis_norm.x * t + cos_angle;
        result[0][1] = axis_norm.y * axis_norm.x * t + axis_norm.z * sin_angle;
        result[0][2] = axis_norm.z * axis_norm.x * t - axis_norm.y * sin_angle;

        result[1][0] = axis_norm.x * axis_norm.y * t - axis_norm.z * sin_angle;
        result[1][1] = axis_norm.y * axis_norm.y * t + cos_angle;
        result[1][2] = axis_norm.z * axis_norm.y * t + axis_norm.x * sin_angle;

        result[2][0] = axis_norm.x * axis_norm.z * t + axis_norm.y * sin_angle;
        result[2][1] = axis_norm.y * axis_norm.z * t - axis_norm.x * sin_angle;
        result[2][2] = axis_norm.z * axis_norm.z * t + cos_angle;

        return result;
    }

    [[nodiscard]] static Matrix3 from_euler(const Vector3<Number>& euler)
    {
        float c = nnm::cos(euler.x);
        float s = nnm::sin(euler.x);
        const Matrix3 x { 1.0f, 0.0f, 0.0f, 0.0f, c, -s, 0.0f, s, c };

        c = nnm::cos(euler.y);
        s = nnm::sin(euler.y);
        const Matrix3 y { c, 0.0f, s, 0.0f, 1.0f, 0.0f, -s, 0.0f, c };

        c = nnm::cos(euler.z);
        s = nnm::sin(euler.z);
        const Matrix3 z { c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f };

        return x * (y * z);
    }

    [[nodiscard]] static Matrix3 zero()
    {
        return { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    }

    [[nodiscard]] static Matrix3 identity()
    {
        return { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    }

    [[nodiscard]] static Matrix3 from_quaternion(const Quaternion<Number>& quaternion)
    {
        Matrix3 result;
        result[0][0] = 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y) - 1;
        result[0][1] = 2 * (quaternion.y * quaternion.z - quaternion.x * quaternion.w);
        result[0][2] = 2 * (quaternion.y * quaternion.w + quaternion.x * quaternion.z);

        result[1][0] = 2 * (quaternion.y * quaternion.z + quaternion.x * quaternion.w);
        result[1][1] = 2 * (quaternion.x * quaternion.x + quaternion.z * quaternion.z) - 1;
        result[1][2] = 2 * (quaternion.z * quaternion.w - quaternion.x * quaternion.y);

        result[2][0] = 2 * (quaternion.y * quaternion.w - quaternion.x * quaternion.z);
        result[2][1] = 2 * (quaternion.z * quaternion.w + quaternion.x * quaternion.y);
        result[2][2] = 2 * (quaternion.x * quaternion.x + quaternion.w * quaternion.w) - 1;

        return result;
    }

    [[nodiscard]] static Matrix3 from_quaternion_scale(
        const Quaternion<Number>& quaternion, const Vector3<Number>& scale)
    {
        Matrix3 result;

        result[0][0] = scale.x;
        result[1][1] = scale.y;
        result[2][2] = scale.z;

        result = result.rotate(quaternion);
        return result;
    }

    [[nodiscard]] static Matrix3 from_scale(const Vector3<Number>& scale)
    {
        return identity().scale(scale);
    }

    [[nodiscard]] static Matrix3 look_at(const Vector3<Number>& target, const Vector3<Number>& up)
    {
        Matrix3 result;

        const Vector3 vz = normalize(-target);
        const Vector3 vx = normalize(up.cross(vz));
        const Vector3 vy = vz.cross(vx);

        result[0][0] = vx.x;
        result[0][1] = vy.x;
        result[0][2] = vz.x;
        result[1][0] = vx.y;
        result[1][1] = vy.y;
        result[1][2] = vz.y;
        result[2][0] = vx.z;
        result[2][1] = vy.z;
        result[2][2] = vz.z;

        return result;
    }

    [[nodiscard]] static Matrix3 from_matrix(const Matrix4<Number>& matrix);

    [[nodiscard]] static Matrix3 from_direction(const Vector3<Number>& dir, const Vector3<Number>& up)
    {
        const Vector3 axis_x = up.cross(dir).normalize();
        const Vector3 axis_y = dir.cross(axis_x).normalize();

        Matrix3 result;

        result[0][0] = axis_x.x;
        result[0][1] = axis_y.x;
        result[0][2] = dir.x;
        result[1][0] = axis_x.y;
        result[1][1] = axis_y.y;
        result[1][2] = dir.y;
        result[2][0] = axis_x.z;
        result[2][1] = axis_y.z;
        result[2][2] = dir.z;

        return result;
    }

    [[nodiscard]] Vector3<Number> euler() const
    {
        Vector3<Number> euler;
        if (const float sy = (*this)[2][0]; sy < 1.0f) {
            if (sy > -1.0f) {
                if ((*this)[0][1] == 0.0f && (*this)[1][0] == 0.0f && (*this)[2][1] == 0.0f && (*this)[1][2] == 0.0f
                    && (*this)[1][1] == 1.0f) {
                    euler.x = 0.0f;
                    euler.y = atan2((*this)[2][0], (*this)[0][0]);
                    euler.z = 0.0f;
                }
                else {
                    euler.x = atan2(-(*this)[2][1], (*this)[2][2]);
                    euler.y = asin(sy);
                    euler.z = atan2(-(*this)[1][0], (*this)[0][0]);
                }
            }
            else {
                euler.x = atan2((*this)[1][2], (*this)[1][1]);
                euler.y = -pi / 2.0f;
                euler.z = 0.0f;
            }
        }
        else {
            euler.x = atan2((*this)[1][2], (*this)[1][1]);
            euler.y = pi / 2.0f;
            euler.z = 0.0f;
        }
        return euler;
    }

    [[nodiscard]] Vector3<Number> scale() const
    {
        const Vector3 scale_abs = Vector3(
            Vector3((*this)[0][0], (*this)[0][1], (*this)[0][2]).length(),
            Vector3((*this)[1][0], (*this)[1][1], (*this)[1][2]).length(),
            Vector3((*this)[2][0], (*this)[2][1], (*this)[2][2]).length());

        if (determinant() > 0) {
            return scale_abs;
        }
        return -scale_abs;
    }

    [[nodiscard]] float determinant() const
    {
        const float a00 = (*this)[0][0];
        const float a01 = (*this)[1][0];
        const float a02 = (*this)[2][0];
        const float a10 = (*this)[0][1];
        const float a11 = (*this)[1][1];
        const float a12 = (*this)[2][1];
        const float a20 = (*this)[0][2];
        const float a21 = (*this)[1][2];
        const float a22 = (*this)[2][2];

        return a00 * a11 * a22 + a01 * a12 * a20 + a02 * a10 * a21 - a02 * a11 * a20 - a01 * a10 * a22
            - a00 * a12 * a21;
    }

    [[nodiscard]] float trace() const
    {
        return (*this)[0][0] + (*this)[1][1] + (*this)[2][2];
    }

    [[nodiscard]] Matrix3 transpose() const
    {
        Matrix3 result;

        result[0][0] = (*this)[0][0];
        result[0][1] = (*this)[1][0];
        result[0][2] = (*this)[2][0];
        result[1][0] = (*this)[0][1];
        result[1][1] = (*this)[1][1];
        result[1][2] = (*this)[2][1];
        result[2][0] = (*this)[0][2];
        result[2][1] = (*this)[1][2];
        result[2][2] = (*this)[2][2];

        return result;
    }

    [[nodiscard]] Matrix3 inverse() const
    {
        const float a11 = (*this)[0][0];
        const float a12 = (*this)[1][0];
        const float a13 = (*this)[2][0];
        const float a21 = (*this)[0][1];
        const float a22 = (*this)[1][1];
        const float a23 = (*this)[2][1];
        const float a31 = (*this)[0][2];
        const float a32 = (*this)[1][2];
        const float a33 = (*this)[2][2];

        const float inv_det = 1.0f
            / (a11 * a22 * a33 + a12 * a33 * a31 + a13 * a21 * a32 - a13 * a22 * a31 - a12 * a21 * a33
               - a11 * a23 * a32);

        Matrix3 result;

        result[0][0] = (a22 * a33 - a23 * a32) * inv_det;
        result[0][1] = -(a21 * a33 - a23 * a31) * inv_det;
        result[0][2] = (a21 * a32 - a22 * a31) * inv_det;
        result[1][0] = -(a12 * a33 - a13 * a32) * inv_det;
        result[1][1] = (a11 * a33 - a13 * a31) * inv_det;
        result[1][2] = -(a11 * a32 - a12 * a31) * inv_det;
        result[2][0] = (a12 * a23 - a13 * a22) * inv_det;
        result[2][1] = -(a11 * a23 - a13 * a21) * inv_det;
        result[2][2] = (a11 * a22 - a12 * a21) * inv_det;

        return result;
    }

    [[nodiscard]] Matrix3 spherical_linear_interpolate(const Matrix3& to, float weight) const
    {
        const Quaternion<Number> from_quat = quaternion();
        const Quaternion<Number> to_quat = to.quaternion();

        Matrix3 matrix = from_quat.spherical_linear_interpolate(to_quat, weight).matrix();
        matrix[0] *= lerp((*this)[0].length(), to[0].length(), weight);
        matrix[1] *= lerp((*this)[1].length(), to[1].length(), weight);
        matrix[2] *= lerp((*this)[2].length(), to[2].length(), weight);

        return matrix;
    }

    [[nodiscard]] Matrix3 rotate(const Vector3<Number>& axis, const float angle) const
    {
        return Matrix3::from_axis_angle(axis, angle) * *this;
    }

    [[nodiscard]] Matrix3 rotate(const Quaternion<Number>& quaternion) const
    {
        return quaternion.matrix() * *this;
    }

    [[nodiscard]] Matrix3 scale(const Vector3<Number>& scale) const
    {
        Matrix3 result = *this;
        result[0][0] *= scale.x;
        result[1][0] *= scale.x;
        result[2][0] *= scale.x;
        result[0][1] *= scale.y;
        result[1][1] *= scale.y;
        result[2][1] *= scale.y;
        result[0][2] *= scale.z;
        result[1][2] *= scale.z;
        result[2][2] *= scale.z;

        return result;
    }

    [[nodiscard]] Matrix3 orthonormalize() const
    {
        Column x = col0;
        Column y = col1;
        Column z = col2;

        x = normalize(x);
        y = y - x * dot(x, y);
        y = normalize(y);
        z = z - x * dot(x, z) - y * dot(y, z);
        z = normalize(z);

        return { x, y, z };
    }

    [[nodiscard]] bool is_equal_approx(const Matrix3& other) const
    {
        for (int c = 0; c < 3; c++) {
            if (!is_equal_approx((*this)[c], other[c])) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool is_zero_approx() const
    {
        for (int c = 0; c < 3; c++) {
            if (!is_zero_approx((*this)[c])) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] Quaternion<Number> quaternion() const
    {
        return Quaternion<Number>::from_matrix(*this);
    }

    [[nodiscard]] Matrix4<Number> with_translation(Vector3<Number> translation) const
    {
        return Matrix4<Number>::from_basis_translation(*this, translation);
    }

    Column& operator[](const int index)
    {
        switch (index) {
        case 0:
            return col0;
        case 1:
            return col1;
        case 2:
            return col2;
        default:
            return col0;
        }
    }

    const Column& operator[](const int index) const
    {
        switch (index) {
        case 0:
            return col0;
        case 1:
            return col1;
        case 2:
            return col2;
        default:
            return col0;
        }
    }

    [[nodiscard]] Matrix3 operator+(const Matrix3& other) const
    {
        auto result = *this;
        result[0] += other[0];
        result[1] += other[1];
        result[2] += other[2];
        return result;
    }

    void operator+=(const Matrix3& other)
    {
        col0 += other[0];
        col1 += other[1];
        col2 += other[2];
    }

    [[nodiscard]] Matrix3 operator-(const Matrix3& other) const
    {
        auto result = *this;
        result[0] -= other[0];
        result[1] -= other[1];
        result[2] -= other[2];
        return result;
    }

    void operator-=(const Matrix3& other)
    {
        col0 -= other[0];
        col1 -= other[1];
        col2 -= other[2];
    }

    [[nodiscard]] Matrix3 operator*(const Matrix3& other) const
    {
        Matrix3 result;
        result[0][0] = (*this)[0][0] * other[0][0] + (*this)[0][1] * other[1][0] + (*this)[0][2] * other[2][0];
        result[0][1] = (*this)[0][0] * other[0][1] + (*this)[0][1] * other[1][1] + (*this)[0][2] * other[2][1];
        result[0][2] = (*this)[0][0] * other[0][2] + (*this)[0][1] * other[1][2] + (*this)[0][2] * other[2][2];
        result[1][0] = (*this)[1][0] * other[0][0] + (*this)[1][1] * other[1][0] + (*this)[1][2] * other[2][0];
        result[1][1] = (*this)[1][0] * other[0][1] + (*this)[1][1] * other[1][1] + (*this)[1][2] * other[2][1];
        result[1][2] = (*this)[1][0] * other[0][2] + (*this)[1][1] * other[1][2] + (*this)[1][2] * other[2][2];
        result[2][0] = (*this)[2][0] * other[0][0] + (*this)[2][1] * other[1][0] + (*this)[2][2] * other[2][0];
        result[2][1] = (*this)[2][0] * other[0][1] + (*this)[2][1] * other[1][1] + (*this)[2][2] * other[2][1];
        result[2][2] = (*this)[2][0] * other[0][2] + (*this)[2][1] * other[1][2] + (*this)[2][2] * other[2][2];
        return result;
    }

    void operator*=(const Matrix3& other)
    {
        *this = *this * other;
    }

    [[nodiscard]] Matrix3 operator*(float val) const
    {
        Matrix3 result = *this;
        result[0] *= val;
        result[1] *= val;
        result[2] *= val;
        return result;
    }

    void operator*=(float val)
    {
        col0 *= val;
        col1 *= val;
        col2 *= val;
    }

    [[nodiscard]] Matrix3 operator*(int val) const
    {
        Matrix3 result = *this;
        result[0] *= val;
        result[1] *= val;
        result[2] *= val;
        return result;
    }

    void operator*=(int val)
    {
        col0 *= val;
        col1 *= val;
        col2 *= val;
    }

    [[nodiscard]] Vector3<Number> operator*(Vector3<Number> vector) const
    {
        const Matrix3& m = *this;
        return { m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z,
                 m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z,
                 m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z };
    }

    [[nodiscard]] bool operator!=(const Matrix3& other) const
    {
        if (col0 != other.col0) {
            return false;
        }
        if (col1 != other.col1) {
            return false;
        }
        if (col2 != other.col2) {
            return false;
        }
        return true;
    }

    [[nodiscard]] bool operator==(const Matrix3& other) const
    {
        return col0 == other.col0 && col1 == other.col1 && col2 == other.col2;
    }

    [[nodiscard]] bool operator<(const Matrix3& other) const
    {
        if (col0 != other.col0) {
            return col0 < other.col0;
        }
        if (col1 != other.col1) {
            return col1 < other.col1;
        }
        if (col2 != other.col2) {
            return col2 < other.col2;
        }
        return false;
    }

    [[nodiscard]] bool operator<=(const Matrix3& other) const
    {
        if (col0 != other.col0) {
            return col0 < other.col0;
        }
        if (col1 != other.col1) {
            return col1 < other.col1;
        }
        if (col2 != other.col2) {
            return col2 < other.col2;
        }
        return true;
    }

    [[nodiscard]] bool operator>(const Matrix3& other) const
    {
        if (col0 != other.col0) {
            return col0 > other.col0;
        }
        if (col1 != other.col1) {
            return col1 > other.col1;
        }
        if (col2 != other.col2) {
            return col2 > other.col2;
        }
        return false;
    }

    [[nodiscard]] bool operator>=(const Matrix3& other) const
    {
        if (col0 != other.col0) {
            return col0 > other.col0;
        }
        if (col1 != other.col1) {
            return col1 > other.col1;
        }
        if (col2 != other.col2) {
            return col2 > other.col2;
        }
        return true;
    }
};

template <typename Number>
class Matrix4 {
public:
    using Column = Vector4<Number>;

    Column col0;
    Column col1;
    Column col2;
    Column col3;

    Matrix4()
        : col0({ 1.0f, 0.0f, 0.0f, 0.0f })
        , col1({ 0.0f, 1.0f, 0.0f, 0.0f })
        , col2({ 0.0f, 0.0f, 1.0f, 0.0f })
        , col3({ 0.0f, 0.0f, 0.0f, 1.0f })
    {
    }

    Matrix4(const Column& col0, const Column& col1, const Column& col2, const Column& col3)
        : col0(col0)
        , col1(col1)
        , col2(col2)
        , col3(col3)
    {
    }

    [[nodiscard]] static Matrix4 zero()
    {
        return { { 0.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 0.0f } };
    }

    [[nodiscard]] static Matrix4 identity()
    {
        return { { 1.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, 1.0f, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 1.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } };
    }

    [[nodiscard]] static Matrix4 from_rotation_translation(
        const Vector3<Number>& rotation_x,
        const Vector3<Number>& rotation_y,
        const Vector3<Number>& rotation_z,
        const Vector3<Number>& translation)
    {
        Matrix4 result;
        result[0] = Vector4(rotation_x.x, rotation_x.y, rotation_x.z, 0.0f);
        result[1] = Vector4(rotation_y.x, rotation_y.y, rotation_y.z, 0.0f);
        result[2] = Vector4(rotation_z.x, rotation_z.y, rotation_z.z, 0.0f);
        result[3] = Vector4(translation.x, translation.y, translation.z, 1.0f);
        return result;
    }

    [[nodiscard]] static Matrix4 from_basis_translation(
        const Matrix3<Number>& basis, const Vector3<Number>& translation)
    {
        Matrix4 result;
        result[0][0] = basis[0][0];
        result[0][1] = basis[0][1];
        result[0][2] = basis[0][2];
        result[1][0] = basis[1][0];
        result[1][1] = basis[1][1];
        result[1][2] = basis[1][2];
        result[2][0] = basis[2][0];
        result[2][1] = basis[2][1];
        result[2][2] = basis[2][2];
        result[3][0] = translation[0];
        result[3][1] = translation[1];
        result[3][2] = translation[2];
        return result;
    }

    static Matrix4 from_perspective(const float fov_y, const float aspect, const float front, const float back)
    {
        const float top = front * tan(fov_y * 0.5f);
        const float bottom = -top;
        const float right = top * aspect;
        const float left = -right;

        const float right_left = right - left;
        const float top_bottom = top - bottom;
        const float far_near = back - front;

        Matrix4 result = Matrix4::zero();

        result[0][0] = front * 2.0f / right_left;
        result[1][1] = -(front * 2.0f) / top_bottom;
        result[2][0] = (right + left) / right_left;
        result[2][1] = (top + bottom) / top_bottom;
        result[2][2] = -(back + front) / far_near;
        result[2][3] = -1.0f;
        result[3][2] = -(back * front * 2.0f) / far_near;

        return result;
    }

    Matrix4 from_look_at(const Vector3<Number> eye, const Vector3<Number> target, const Vector3<Number> up)
    {
        const Vector3 target_eye = (target - eye).normalize();
        const Vector3 cross_up = target_eye.cross(up).normalize();
        const Vector3 cross = cross_up.cross(target_eye);

        Matrix4 result;

        result[0][0] = cross_up.x;
        result[1][0] = cross_up.y;
        result[2][0] = cross_up.z;
        result[0][1] = cross.x;
        result[1][1] = cross.y;
        result[2][1] = cross.z;
        result[0][2] = -target_eye.x;
        result[1][2] = -target_eye.y;
        result[2][2] = -target_eye.z;
        result[3][0] = -dot(cross_up, eye);
        result[3][1] = -dot(cross, eye);
        result[3][2] = dot(target_eye, eye);

        return result;
    }

    static Matrix4 from_ortho(
        const float left, const float right, const float bottom, const float top, const float front, const float back)
    {
        const float rl = right - left;
        const float tb = top - bottom;
        const float bf = back - front;

        Matrix4 result;
        result[0][0] = 2.0f / rl;
        result[0][1] = 0.0f;
        result[0][2] = 0.0f;
        result[0][3] = 0.0f;
        result[1][0] = 0.0f;
        result[1][1] = 2.0f / tb;
        result[1][2] = 0.0f;
        result[1][3] = 0.0f;
        result[2][0] = 0.0f;
        result[2][1] = 0.0f;
        result[2][2] = -2.0f / bf;
        result[2][3] = 0.0f;
        result[3][0] = -(left + right) / rl;
        result[3][1] = -(top + bottom) / tb;
        result[3][2] = -(back + front) / bf;
        result[3][3] = 1.0f;

        return result;
    }

    [[nodiscard]] Number determinant() const
    {
        const Number a00 = (*this)[0][0];
        const Number a01 = (*this)[1][0];
        const Number a02 = (*this)[2][0];
        const Number a03 = (*this)[3][0];
        const Number a10 = (*this)[0][1];
        const Number a11 = (*this)[1][1];
        const Number a12 = (*this)[2][1];
        const Number a13 = (*this)[3][1];
        const Number a20 = (*this)[0][2];
        const Number a21 = (*this)[1][2];
        const Number a22 = (*this)[2][2];
        const Number a23 = (*this)[3][2];
        const Number a30 = (*this)[0][3];
        const Number a31 = (*this)[1][3];
        const Number a32 = (*this)[2][3];
        const Number a33 = (*this)[3][3];

        return a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03
            + a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13
            + a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13
            + a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23
            + a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33
            + a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;
    }

    [[nodiscard]] Number trace() const
    {
        return (*this)[0][0] + (*this)[1][1] + (*this)[2][2] + (*this)[3][3];
    }

    [[nodiscard]] Matrix4 transposed() const
    {
        Matrix4 result;
        result[0][0] = (*this)[0][0];
        result[0][1] = (*this)[1][0];
        result[0][2] = (*this)[2][0];
        result[0][3] = (*this)[3][0];
        result[1][0] = (*this)[0][1];
        result[1][1] = (*this)[1][1];
        result[1][2] = (*this)[2][1];
        result[1][3] = (*this)[3][1];
        result[2][0] = (*this)[0][2];
        result[2][1] = (*this)[1][2];
        result[2][2] = (*this)[2][2];
        result[2][3] = (*this)[3][2];
        result[3][0] = (*this)[0][3];
        result[3][1] = (*this)[1][3];
        result[3][2] = (*this)[2][3];
        result[3][3] = (*this)[3][3];
        return result;
    }

    [[nodiscard]] Matrix4 inverse() const
    {
        Matrix4 result;

        result[0][0] = (*this)[1][1] * (*this)[2][2] * (*this)[3][3] - (*this)[1][1] * (*this)[2][3] * (*this)[3][2]
            - (*this)[2][1] * (*this)[1][2] * (*this)[3][3] + (*this)[2][1] * (*this)[1][3] * (*this)[3][2]
            + (*this)[3][1] * (*this)[1][2] * (*this)[2][3] - (*this)[3][1] * (*this)[1][3] * (*this)[2][2];

        result[1][0] = -(*this)[1][0] * (*this)[2][2] * (*this)[3][3] + (*this)[1][0] * (*this)[2][3] * (*this)[3][2]
            + (*this)[2][0] * (*this)[1][2] * (*this)[3][3] - (*this)[2][0] * (*this)[1][3] * (*this)[3][2]
            - (*this)[3][0] * (*this)[1][2] * (*this)[2][3] + (*this)[3][0] * (*this)[1][3] * (*this)[2][2];

        result[2][0] = (*this)[1][0] * (*this)[2][1] * (*this)[3][3] - (*this)[1][0] * (*this)[2][3] * (*this)[3][1]
            - (*this)[2][0] * (*this)[1][1] * (*this)[3][3] + (*this)[2][0] * (*this)[1][3] * (*this)[3][1]
            + (*this)[3][0] * (*this)[1][1] * (*this)[2][3] - (*this)[3][0] * (*this)[1][3] * (*this)[2][1];

        result[3][0] = -(*this)[1][0] * (*this)[2][1] * (*this)[3][2] + (*this)[1][0] * (*this)[2][2] * (*this)[3][1]
            + (*this)[2][0] * (*this)[1][1] * (*this)[3][2] - (*this)[2][0] * (*this)[1][2] * (*this)[3][1]
            - (*this)[3][0] * (*this)[1][1] * (*this)[2][2] + (*this)[3][0] * (*this)[1][2] * (*this)[2][1];

        result[0][1] = -(*this)[0][1] * (*this)[2][2] * (*this)[3][3] + (*this)[0][1] * (*this)[2][3] * (*this)[3][2]
            + (*this)[2][1] * (*this)[0][2] * (*this)[3][3] - (*this)[2][1] * (*this)[0][3] * (*this)[3][2]
            - (*this)[3][1] * (*this)[0][2] * (*this)[2][3] + (*this)[3][1] * (*this)[0][3] * (*this)[2][2];

        result[1][1] = (*this)[0][0] * (*this)[2][2] * (*this)[3][3] - (*this)[0][0] * (*this)[2][3] * (*this)[3][2]
            - (*this)[2][0] * (*this)[0][2] * (*this)[3][3] + (*this)[2][0] * (*this)[0][3] * (*this)[3][2]
            + (*this)[3][0] * (*this)[0][2] * (*this)[2][3] - (*this)[3][0] * (*this)[0][3] * (*this)[2][2];

        result[2][1] = -(*this)[0][0] * (*this)[2][1] * (*this)[3][3] + (*this)[0][0] * (*this)[2][3] * (*this)[3][1]
            + (*this)[2][0] * (*this)[0][1] * (*this)[3][3] - (*this)[2][0] * (*this)[0][3] * (*this)[3][1]
            - (*this)[3][0] * (*this)[0][1] * (*this)[2][3] + (*this)[3][0] * (*this)[0][3] * (*this)[2][1];

        result[3][1] = (*this)[0][0] * (*this)[2][1] * (*this)[3][2] - (*this)[0][0] * (*this)[2][2] * (*this)[3][1]
            - (*this)[2][0] * (*this)[0][1] * (*this)[3][2] + (*this)[2][0] * (*this)[0][2] * (*this)[3][1]
            + (*this)[3][0] * (*this)[0][1] * (*this)[2][2] - (*this)[3][0] * (*this)[0][2] * (*this)[2][1];

        result[0][2] = (*this)[0][1] * (*this)[1][2] * (*this)[3][3] - (*this)[0][1] * (*this)[1][3] * (*this)[3][2]
            - (*this)[1][1] * (*this)[0][2] * (*this)[3][3] + (*this)[1][1] * (*this)[0][3] * (*this)[3][2]
            + (*this)[3][1] * (*this)[0][2] * (*this)[1][3] - (*this)[3][1] * (*this)[0][3] * (*this)[1][2];

        result[1][2] = -(*this)[0][0] * (*this)[1][2] * (*this)[3][3] + (*this)[0][0] * (*this)[1][3] * (*this)[3][2]
            + (*this)[1][0] * (*this)[0][2] * (*this)[3][3] - (*this)[1][0] * (*this)[0][3] * (*this)[3][2]
            - (*this)[3][0] * (*this)[0][2] * (*this)[1][3] + (*this)[3][0] * (*this)[0][3] * (*this)[1][2];

        result[2][2] = (*this)[0][0] * (*this)[1][1] * (*this)[3][3] - (*this)[0][0] * (*this)[1][3] * (*this)[3][1]
            - (*this)[1][0] * (*this)[0][1] * (*this)[3][3] + (*this)[1][0] * (*this)[0][3] * (*this)[3][1]
            + (*this)[3][0] * (*this)[0][1] * (*this)[1][3] - (*this)[3][0] * (*this)[0][3] * (*this)[1][1];

        result[3][2] = -(*this)[0][0] * (*this)[1][1] * (*this)[3][2] + (*this)[0][0] * (*this)[1][2] * (*this)[3][1]
            + (*this)[1][0] * (*this)[0][1] * (*this)[3][2] - (*this)[1][0] * (*this)[0][2] * (*this)[3][1]
            - (*this)[3][0] * (*this)[0][1] * (*this)[1][2] + (*this)[3][0] * (*this)[0][2] * (*this)[1][1];

        result[0][3] = -(*this)[0][1] * (*this)[1][2] * (*this)[2][3] + (*this)[0][1] * (*this)[1][3] * (*this)[2][2]
            + (*this)[1][1] * (*this)[0][2] * (*this)[2][3] - (*this)[1][1] * (*this)[0][3] * (*this)[2][2]
            - (*this)[2][1] * (*this)[0][2] * (*this)[1][3] + (*this)[2][1] * (*this)[0][3] * (*this)[1][2];

        result[1][3] = (*this)[0][0] * (*this)[1][2] * (*this)[2][3] - (*this)[0][0] * (*this)[1][3] * (*this)[2][2]
            - (*this)[1][0] * (*this)[0][2] * (*this)[2][3] + (*this)[1][0] * (*this)[0][3] * (*this)[2][2]
            + (*this)[2][0] * (*this)[0][2] * (*this)[1][3] - (*this)[2][0] * (*this)[0][3] * (*this)[1][2];

        result[2][3] = -(*this)[0][0] * (*this)[1][1] * (*this)[2][3] + (*this)[0][0] * (*this)[1][3] * (*this)[2][1]
            + (*this)[1][0] * (*this)[0][1] * (*this)[2][3] - (*this)[1][0] * (*this)[0][3] * (*this)[2][1]
            - (*this)[2][0] * (*this)[0][1] * (*this)[1][3] + (*this)[2][0] * (*this)[0][3] * (*this)[1][1];

        result[3][3] = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] - (*this)[0][0] * (*this)[1][2] * (*this)[2][1]
            - (*this)[1][0] * (*this)[0][1] * (*this)[2][2] + ((*this))[1][0] * (*this)[0][2] * (*this)[2][1]
            + (*this)[2][0] * (*this)[0][1] * (*this)[1][2] - (*this)[2][0] * (*this)[0][2] * (*this)[1][1];

        float det = (*this)[0][0] * result[0][0] + (*this)[0][1] * result[1][0] + (*this)[0][2] * result[2][0]
            + (*this)[0][3] * result[3][0];

        if (det == 0.0f)
            return identity();

        det = 1.0f / det;

        for (int c = 0; c < 4; c++) {
            for (int r = 0; r < 4; r++) {
                result[c][r] *= det;
            }
        }

        return result.transposed();
    }

    [[nodiscard]] Matrix4 interpolate(const Matrix4& to, float weight) const
    {
        Vector3 from_scale = scale();
        Quaternion<Number> from_rotation = quaternion();
        Vector3<Number> from_translation = translation();

        Vector3 to_scale = to.scale();
        Quaternion to_rotation = to.quaternion();
        Vector3 to_translation = to.translation();

        Quaternion result_rotation = from_rotation.spherical_linear_interpolate(to_rotation, weight).normalize();
        Vector3 result_scale = from_scale.linear_interpolate(to_scale, weight);
        Matrix3<Number> result_basis = Matrix3<Number>::from_quaternion_scale(result_rotation, result_scale);
        Vector3 result_translation = from_translation.linear_interpolate(to_translation, weight);

        return Matrix4::from_basis_translation(result_basis, result_translation);
    }

    [[nodiscard]] Matrix4 rotate(const Vector3<Number>& axis, float angle) const
    {
        const auto rotation_basis = Matrix3<Number>::from_axis_angle(axis, angle);
        return Matrix4::from_basis_translation(this->basis() * rotation_basis, translation());
    }

    [[nodiscard]] Matrix4 rotate(const Matrix3<Number>& basis) const
    {
        return Matrix4::from_basis_translation(this->basis() * basis, this->translation());
    }

    [[nodiscard]] Matrix4 rotate_local(const Vector3<Number>& axis, float angle) const
    {
        const auto rotation_basis = Matrix3<Number>::from_axis_angle(axis, angle);
        return Matrix4::from_basis_translation(rotation_basis * basis(), translation());
    }

    [[nodiscard]] Matrix4 rotate_local(const Matrix3<Number>& basis) const
    {
        return Matrix4::from_basis_translation(basis * this->basis(), translation());
    }

    [[nodiscard]] Matrix4 scale(const Vector3<Number>& scale) const
    {
        const Matrix3 basis = this->basis().scale(scale);
        const Vector3 translation = this->translation() * scale;
        return Matrix4::from_basis_translation(basis, translation);
    }

    [[nodiscard]] Matrix4 translate(const Vector3<Number>& offset) const
    {
        return Matrix4::from_basis_translation(basis(), translation() + offset);
    }

    [[nodiscard]] Matrix4 translate_local(const Vector3<Number>& offset) const
    {
        const auto basis = this->basis();
        const auto basis_t = basis.transpose();
        const Vector3 rotated_offset { basis_t.col0.dot(offset), basis_t.col1.dot(offset), basis_t.col2.dot(offset) };
        return Matrix4::from_basis_translation(basis, translation() + rotated_offset);
    }

    [[nodiscard]] bool is_equal_approx(const Matrix4& other) const
    {
        return (*this)[0].approx_equal(other[0]) && (*this)[1].approx_equal(other[1])
            && (*this)[2].approx_equal(other[2]) && (*this)[3].approx_equal(other[3]);
    }

    [[nodiscard]] bool is_zero_approx() const
    {
        return (*this)[0].approx_zero() && (*this)[1].approx_zero() && (*this)[2].approx_zero()
            && (*this)[3].approx_zero();
    }

    [[nodiscard]] Matrix3<Number> basis() const
    {
        return Matrix3<Number>::from_matrix(*this);
    }

    [[nodiscard]] Vector3<Number> translation() const
    {
        return { (*this)[3][0], (*this)[3][1], (*this)[3][2] };
    }

    [[nodiscard]] Quaternion<Number> quaternion() const
    {
        return Quaternion<Number>::from_matrix(basis());
    }

    [[nodiscard]] Vector3<Number> scale() const
    {
        return basis().scale();
    }

    [[nodiscard]] Vector3<Number> euler() const
    {
        return basis().euler();
    }

    Column& operator[](const int index)
    {
        switch (index) {
        case 0:
            return col0;
        case 1:
            return col1;
        case 2:
            return col2;
        case 3:
            return col3;
        default:
            return col0;
        }
    }

    const Column& operator[](const int index) const
    {
        switch (index) {
        case 0:
            return col0;
        case 1:
            return col1;
        case 2:
            return col2;
        case 3:
            return col3;
        default:
            return col0;
        }
    }

    [[nodiscard]] Matrix4 operator+(const Matrix4& other) const
    {
        return { col0 + other.col0, col1 + other.col1, col2 + other.col2, col3 + other.col3 };
    }

    void operator+=(const Matrix4& other)
    {
        col0 += other.col0;
        col1 += other.col1;
        col2 += other.col2;
        col3 += other.col3;
    }

    [[nodiscard]] Matrix4 operator-(const Matrix4& other) const
    {
        return { col0 - other.col0, col1 - other.col1, col2 - other.col2, col3 - other.col3 };
    }

    void operator-=(const Matrix4& other)
    {
        col0 -= other.col0;
        col1 -= other.col1;
        col2 -= other.col2;
        col3 -= other.col3;
    }

    [[nodiscard]] Matrix4 operator*(const Matrix4& other) const
    {
        Matrix4 result;

        result[0][0] = (*this)[0][0] * other[0][0] + (*this)[0][1] * other[1][0] + (*this)[0][2] * other[2][0]
            + (*this)[0][3] * other[3][0];
        result[0][1] = (*this)[0][0] * other[0][1] + (*this)[0][1] * other[1][1] + (*this)[0][2] * other[2][1]
            + (*this)[0][3] * other[3][1];
        result[0][2] = (*this)[0][0] * other[0][2] + (*this)[0][1] * other[1][2] + (*this)[0][2] * other[2][2]
            + (*this)[0][3] * other[3][2];
        result[0][3] = (*this)[0][0] * other[0][3] + (*this)[0][1] * other[1][3] + (*this)[0][2] * other[2][3]
            + (*this)[0][3] * other[3][3];
        result[1][0] = (*this)[1][0] * other[0][0] + (*this)[1][1] * other[1][0] + (*this)[1][2] * other[2][0]
            + (*this)[1][3] * other[3][0];
        result[1][1] = (*this)[1][0] * other[0][1] + (*this)[1][1] * other[1][1] + (*this)[1][2] * other[2][1]
            + (*this)[1][3] * other[3][1];
        result[1][2] = (*this)[1][0] * other[0][2] + (*this)[1][1] * other[1][2] + (*this)[1][2] * other[2][2]
            + (*this)[1][3] * other[3][2];
        result[1][3] = (*this)[1][0] * other[0][3] + (*this)[1][1] * other[1][3] + (*this)[1][2] * other[2][3]
            + (*this)[1][3] * other[3][3];
        result[2][0] = (*this)[2][0] * other[0][0] + (*this)[2][1] * other[1][0] + (*this)[2][2] * other[2][0]
            + (*this)[2][3] * other[3][0];
        result[2][1] = (*this)[2][0] * other[0][1] + (*this)[2][1] * other[1][1] + (*this)[2][2] * other[2][1]
            + (*this)[2][3] * other[3][1];
        result[2][2] = (*this)[2][0] * other[0][2] + (*this)[2][1] * other[1][2] + (*this)[2][2] * other[2][2]
            + (*this)[2][3] * other[3][2];
        result[2][3] = (*this)[2][0] * other[0][3] + (*this)[2][1] * other[1][3] + (*this)[2][2] * other[2][3]
            + (*this)[2][3] * other[3][3];
        result[3][0] = (*this)[3][0] * other[0][0] + (*this)[3][1] * other[1][0] + (*this)[3][2] * other[2][0]
            + (*this)[3][3] * other[3][0];
        result[3][1] = (*this)[3][0] * other[0][1] + (*this)[3][1] * other[1][1] + (*this)[3][2] * other[2][1]
            + (*this)[3][3] * other[3][1];
        result[3][2] = (*this)[3][0] * other[0][2] + (*this)[3][1] * other[1][2] + (*this)[3][2] * other[2][2]
            + (*this)[3][3] * other[3][2];
        result[3][3] = (*this)[3][0] * other[0][3] + (*this)[3][1] * other[1][3] + (*this)[3][2] * other[2][3]
            + (*this)[3][3] * other[3][3];

        return result;
    }

    void operator*=(const Matrix4& other)
    {
        *this = *this * other;
    }

    [[nodiscard]] Vector4<Number> operator*(const Vector4<Number>& vector) const
    {
        const Matrix4& m = *this;
        return { vector.x * m[0][0] + vector.y * m[1][0] + vector.z * m[2][0] + vector.w * m[3][0],
                 vector.x * m[0][1] + vector.y * m[1][1] + vector.z * m[2][1] + vector.w * m[3][1],
                 vector.x * m[0][2] + vector.y * m[1][2] + vector.z * m[2][2] + vector.w * m[3][2],
                 vector.x * m[0][3] + vector.y * m[1][3] + vector.z * m[2][3] + vector.w * m[3][3] };
    }
};

template <typename Number>
Vector3<Number>::Vector3(const Vector3i vector)
    : x(static_cast<Number>(vector.x))
    , y(static_cast<Number>(vector.y))
    , z(static_cast<Number>(vector.z))
{
}

template <typename Number>
Vector3<Number> Vector3<Number>::rotate(const Matrix3<Number>& matrix) const
{
    return matrix * *this;
}

template <typename Number>
Vector3<Number> Vector3<Number>::transform(const Matrix4<Number>& matrix) const
{
    Vector4 result_4d = matrix * Vector4(x, y, z, 1.0f);
    return { result_4d.x, result_4d.y, result_4d.z };
}

template <typename Number>
Matrix3<Number> Quaternion<Number>::matrix() const
{
    return Matrix3<Number>::from_quaternion(*this);
}
template <typename Number>
Quaternion<Number> Quaternion<Number>::normalize() const
{
    return *this / this->length();
}

template <typename Number>
Matrix3<Number> Matrix3<Number>::from_matrix(const Matrix4<Number>& matrix)
{
    Matrix3 result;
    result[0] = Column(matrix[0][0], matrix[0][1], matrix[0][2]);
    result[1] = Column(matrix[1][0], matrix[1][1], matrix[1][2]);
    result[2] = Column(matrix[2][0], matrix[2][1], matrix[2][2]);
    return result;
}

template <typename Number>
Vector4i::Vector4i(const Vector4<Number>& vector)
    : x(static_cast<int>(vector.x))
    , y(static_cast<int>(vector.y))
    , z(static_cast<int>(vector.z))
    , w(static_cast<int>(vector.w))
{
}

template <typename Number>
Vector2<Number>::Vector2(const Vector2i& vector)
    : x(vector.x)
    , y(vector.y)
{
}

}

template <>
struct std::hash<nnm::Vector2i> {
    int operator()(const nnm::Vector2i& vector) const noexcept
    {
        return (vector.x + vector.y + 1) * (vector.x + vector.y) / 2 + vector.y;
    }
};

template <>
struct std::hash<nnm::Vector4i> {
    int operator()(const nnm::Vector4i& vector) const noexcept
    {
        const int cantor_z_w = (vector.z + vector.w + 1) * (vector.z + vector.w) / 2 + vector.w;
        const int cantor_y_z_w = (vector.y + cantor_z_w + 1) * (vector.y + cantor_z_w) / 2 + cantor_z_w;
        return (vector.x + cantor_y_z_w) * (vector.x + cantor_y_z_w) / 2 + cantor_y_z_w;
    }
};

template <>
struct std::hash<nnm::Vector3i> {
    int operator()(const nnm::Vector3i& vector) const noexcept
    {
        const int cantor_y_z = (vector.y + vector.z + 1) * (vector.y + vector.z) / 2 + vector.z;
        return (vector.x + cantor_y_z) * (vector.x + cantor_y_z) / 2 + cantor_y_z;
    }
};