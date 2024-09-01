#ifndef NNM_HPP
#define NNM_HPP

#include <cmath>
#include <functional>
#include <optional>

// ReSharper disable CppDFATimeOver

#if defined(NNM_BOUNDS_CHECK)
#include <stdexcept>
#define NNM_BOUNDS_CHECK_ASSERT(msg, expression) \
    if (!(expression))                           \
        throw std::out_of_range(msg);
#else
#define NNM_BOUNDS_CHECK_ASSERT(msg, expression)
#endif

namespace nnm {

template <typename Real = float>
constexpr Real pi()
{
    return static_cast<Real>(3.141592653589793238462643383279502);
}

template <typename Real = float>
constexpr Real epsilon()
{
    return static_cast<Real>(0.00001);
}

template <typename Real = float>
constexpr Real sign(const Real value)
{
    if (value < static_cast<Real>(0.0)) {
        return static_cast<Real>(-1.0);
    }
    return static_cast<Real>(1.0);
}

constexpr int sign(const int value)
{
    if (value < 0) {
        return -1;
    }
    return 1;
}

template <typename Real = float>
constexpr Real abs(const Real value)
{
    if (value < static_cast<Real>(0.0)) {
        return -value;
    }
    return value;
}

constexpr int abs(const int value)
{
    if (value < 0) {
        return -value;
    }
    return value;
}

template <typename Real = float>
constexpr Real max(const Real a, const Real b)
{
    if (a > b) {
        return a;
    }
    return b;
}

constexpr int max(const int a, const int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

template <typename Real = float>
constexpr bool approx_zero(const Real value)
{
    Real tolerance = epsilon<Real>() * abs(value);
    tolerance = max(tolerance, epsilon<Real>());
    return abs(value) <= tolerance;
}

template <typename Real = float>
constexpr bool approx_equal(const Real a, const Real b)
{
    if (a == b) {
        return true;
    }
    Real tolerance = epsilon<Real>() * max(abs(a), abs(b));
    tolerance = max(tolerance, epsilon<Real>());
    return abs(a - b) <= tolerance;
}

template <typename Real = float>
Real ceil(const Real value)
{
    return std::ceil(value);
}

template <typename Real = float>
constexpr Real clamp(const Real value, const Real min, const Real max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

constexpr int clamp(const int value, const int min, const int max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

template <typename Real = float>
Real sqrt(const Real value)
{
    return std::sqrt(value);
}

template <typename Real = float>
Real pow(const Real base, const Real power)
{
    return std::pow(base, power);
}

template <typename Real = float>
constexpr Real sqrd(const Real value)
{
    return value * value;
}

constexpr int sqrd(const int value)
{
    return value * value;
}

template <typename Real = float>
Real floor(const Real value)
{
    return std::floor(value);
}

template <typename Real = float>
constexpr Real lerp(const Real from, const Real to, const Real weight)
{
    return from + weight * (to - from);
}

template <typename Real = float>
constexpr Real lerp_clamped(const Real from, const Real to, const Real weight)
{
    if (weight >= static_cast<Real>(1.0)) {
        return to;
    }
    if (weight <= static_cast<Real>(0.0)) {
        return from;
    }
    return lerp(from, to, weight);
}

template <typename Real = float>
Real sin(const Real value)
{
    return std::sin(value);
}

template <typename Real = float>
Real cos(const Real value)
{
    return std::cos(value);
}

template <typename Real = float>
Real tan(const Real value)
{
    return std::tan(value);
}

template <typename Real = float>
Real round(const Real value)
{
    return std::round(value);
}

template <typename Real = float>
Real atan(const Real value)
{
    return std::atan(value);
}

template <typename Real = float>
Real atan2(const Real a, const Real b)
{
    return std::atan2(a, b);
}

template <typename Real = float>
constexpr Real radians(const Real degrees)
{
    return pi<Real>() / static_cast<Real>(180.0) * degrees;
}

template <typename Real = float>
constexpr Real degrees(const Real radians)
{
    return static_cast<Real>(180.0) / pi<Real>() * radians;
}

template <typename Real = float>
Real asin(const Real value)
{
    return std::asin(value);
}

template <typename Real = float>
Real acos(const Real value)
{
    return std::acos(value);
}

template <typename Real = float>
constexpr Real min(const Real a, const Real b)
{
    if (a < b) {
        return a;
    }
    return b;
}

constexpr int min(const int a, const int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

template <typename Real = float>
Real log2(const Real value)
{
    return std::log2(value);
}

template <typename Real = float>
class Vector2;
using Vector2f = Vector2<>;
using Vector2d = Vector2<double>;
class Vector2i;
template <typename Real = float>
class Vector3;
using Vector3f = Vector3<>;
using Vector3d = Vector3<double>;
class Vector3i;
template <typename Real = float>
class Vector4;
using Vector4f = Vector4<>;
using Vector4d = Vector4<double>;
template <typename Real = float>
class Quaternion;
using QuaternionF = Quaternion<>;
using QuaternionD = Quaternion<double>;
template <typename Real = float>
class Matrix2;
using Matrix2f = Matrix2<>;
using Matrix2d = Matrix2<double>;
template <typename Real = float>
class Basis2;
using Basis2f = Basis2<>;
using Basis2d = Basis2<double>;
template <typename Real = float>
class Matrix3;
using Matrix3f = Matrix3<>;
using Matrix3d = Matrix3<double>;
template <typename Real = float>
class Transform2;
using Transform2f = Transform2<>;
using Transform2d = Transform2<double>;
template <typename Real = float>
class Basis3;
using Basis3f = Basis3<>;
using Basis3d = Basis3<double>;
template <typename Real = float>
class Matrix4;
using Matrix4f = Matrix4<>;
using Matrix4d = Matrix4<double>;
template <typename Real = float>
class Transform3;
using Transform3f = Transform3<>;
using Transform3d = Transform3<double>;

template <typename Real>
class Vector2 {
public:
    union {
        struct {
            Real x;
            Real y;
        };
        Real data[2] {};
    };

    constexpr Vector2()
        : x(static_cast<Real>(0.0))
        , y(static_cast<Real>(0.0))
    {
    }

    explicit constexpr Vector2(const Vector2i& vector);

    template <typename Other>
    explicit constexpr Vector2(const Vector2<Other>& vector)
        : x(static_cast<Real>(vector.x))
        , y(static_cast<Real>(vector.y))
    {
    }

    constexpr Vector2(const Real x, const Real y)
        : x(x)
        , y(y)
    {
    }

    static constexpr Vector2 all(const Real value)
    {
        return { value, value };
    }

    static constexpr Vector2 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    static constexpr Vector2 one()
    {
        return all(static_cast<Real>(1.0));
    }

    static constexpr Vector2 axis_x()
    {
        return { static_cast<Real>(1.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector2 axis_y()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(1.0) };
    }

    [[nodiscard]] constexpr Vector2 abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    [[nodiscard]] Vector2 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y) };
    }

    [[nodiscard]] Vector2 floor() const
    {
        return { nnm::floor(x), nnm::floor(y) };
    }

    [[nodiscard]] Vector2 round() const
    {
        return { nnm::round(x), nnm::round(y) };
    }

    [[nodiscard]] constexpr Real aspect_ratio() const
    {
        return x / y;
    }

    [[nodiscard]] constexpr Vector2 clamp(const Vector2& min, const Vector2& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] Vector2 direction(const Vector2& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] constexpr Real distance_sqrd(const Vector2& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        return sqrd(diff_x) + sqrd(diff_y);
    }

    [[nodiscard]] Real distance(const Vector2& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    [[nodiscard]] constexpr Real manhattan_distance(const Vector2& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector2 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0.0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    [[nodiscard]] Vector2 normalize() const
    {
        if (const Real length = this->length(); length > static_cast<Real>(0.0)) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] constexpr Vector2 lerp(const Vector2& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight) };
    }

    [[nodiscard]] constexpr Vector2 lerp_clamped(const Vector2& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight), nnm::lerp_clamped(y, to.y, weight) };
    }

    [[nodiscard]] constexpr Real dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] constexpr Real cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    [[nodiscard]] Matrix2<Real> outer(const Vector2& other) const;

    [[nodiscard]] constexpr Vector2 reflect(const Vector2& normal) const
    {
        const Real dot = this->dot(normal);
        Vector2 result;
        result.x = x - static_cast<Real>(2.0) * normal.x * dot;
        result.y = y - static_cast<Real>(2.0) * normal.y * dot;
        return result;
    }

    [[nodiscard]] constexpr Vector2 project(const Vector2& onto) const
    {
        const Real onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == static_cast<Real>(0.0)) {
            return zero();
        }
        const Real scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    [[nodiscard]] constexpr Vector2 inverse() const
    {
        return { static_cast<Real>(1.0) / x, static_cast<Real>(1.0) / y };
    }

    [[nodiscard]] Real angle(const Vector2& to) const
    {
        const Real lengths = length() * to.length();
        if (lengths == 0) {
            return static_cast<Real>(0.0);
        }
        const Real cos_angle = nnm::clamp(dot(to) / lengths, static_cast<Real>(-1.0), static_cast<Real>(1.0));
        return acos(cos_angle);
    }

    [[nodiscard]] Vector2 translate(const Vector2& by) const;

    [[nodiscard]] Vector2 rotate(Real angle) const;

    [[nodiscard]] Vector2 scale(const Vector2& factor) const;

    [[nodiscard]] Vector2 shear_x(Real angle_y) const;

    [[nodiscard]] Vector2 shear_y(Real angle_x) const;

    [[nodiscard]] Vector2 transform(const Basis2<Real>& by) const;

    [[nodiscard]] Vector2 transform(const Transform2<Real>& by, Real z = static_cast<Real>(1.0)) const;

    [[nodiscard]] constexpr int max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] constexpr int min_index() const
    {
        if (x < y) {
            return 0;
        }
        if (y < x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] constexpr bool approx_equal(const Vector2& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y);
    }

    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y);
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 2;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 2;
    }

    [[nodiscard]] Real at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    Real& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] const Real& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    Real& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] constexpr bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector2& other) const
    {
        return x != other.x || y != other.y;
    }

    [[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator*(const Vector2& other) const
    {
        return { x * other.x, y * other.y };
    }

    Vector2& operator*=(const Vector2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    [[nodiscard]] Vector2 operator*(const Matrix2<Real>& matrix) const;

    [[nodiscard]] constexpr Vector2 operator*(const Real value) const
    {
        return { x * value, y * value };
    }

    Vector2& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator/(const Vector2& other) const
    {
        return { x / other.x, y / other.y };
    }

    Vector2& operator/=(const Vector2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator/(const Real value) const
    {
        return { x / value, y / value };
    }

    Vector2& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector2 operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] constexpr Vector2 operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] constexpr bool operator<(const Vector2& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != 0.0 || y != 0.0;
    }
};

template <typename Real = float>
Vector2<Real> constexpr operator*(const Real value, const Vector2<Real>& vector)
{
    return { value * vector.x, value * vector.y };
}

template <typename Real = float>
Vector2<Real> constexpr operator/(const Real value, const Vector2<Real>& vector)
{
    return { value / vector.x, value / vector.y };
}

class Vector2i {
public:
    union {
        struct {
            int x;
            int y;
        };
        int data[2] {};
    };

    constexpr Vector2i()
        : x(0)
        , y(0)
    {
    }

    template <typename Real = float>
    explicit constexpr Vector2i(const Vector2<Real>& vector)
        : x(static_cast<int>(vector.x))
        , y(static_cast<int>(vector.y))
    {
    }

    constexpr Vector2i(const int x, const int y)
        : x(x)
        , y(y)
    {
    }

    static constexpr Vector2i all(int value)
    {
        return { value, value };
    }

    static constexpr Vector2i zero()
    {
        return { 0, 0 };
    }

    static constexpr Vector2i one()
    {
        return { 1, 1 };
    }

    static constexpr Vector2i axis_x()
    {
        return { 1, 0 };
    }

    static constexpr Vector2i axis_y()
    {
        return { 0, 1 };
    }

    [[nodiscard]] constexpr Vector2i abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    [[nodiscard]] constexpr Vector2i clamp(const Vector2i& min, const Vector2i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] constexpr int manhattan_distance(const Vector2i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    [[nodiscard]] constexpr int length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] constexpr int max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] constexpr int min_index() const
    {
        if (x < y) {
            return 0;
        }
        if (y < x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] const int* begin() const
    {
        return data;
    }

    [[nodiscard]] const int* end() const
    {
        return data + 2;
    }

    int* begin()
    {
        return data;
    }

    int* end()
    {
        return data + 2;
    }

    [[nodiscard]] int at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    int& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] int operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    int& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] constexpr bool operator==(const Vector2i& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector2i& other) const
    {
        return x != other.x || y != other.y;
    }

    [[nodiscard]] constexpr Vector2i operator+(const Vector2i& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2i& operator+=(const Vector2i& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator-(const Vector2i& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2i& operator-=(const Vector2i& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator*(const Vector2i& other) const
    {
        return { x * other.x, y * other.y };
    }

    Vector2i& operator*=(const Vector2i& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator*(const int value) const
    {
        return { x * value, y * value };
    }

    Vector2i& operator*=(const int value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator/(const Vector2i& other) const
    {
        return { x / other.x, y / other.y };
    }

    Vector2i& operator/=(const Vector2i& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator/(const int value) const
    {
        return { x / value, y / value };
    }

    Vector2i& operator/=(const int value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator%(const Vector2i& other) const
    {
        return { x % other.x, y % other.y };
    }

    Vector2i& operator%=(const Vector2i& other)
    {
        x %= other.x;
        y %= other.y;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator%(const int value) const
    {
        return { x % value, y % value };
    }

    Vector2i& operator%=(const int value)
    {
        x %= value;
        y %= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector2i operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] constexpr Vector2i operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] constexpr bool operator<(const Vector2i& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != 0 || y != 0;
    }
};

constexpr Vector2i operator*(const int value, const Vector2i& vector)
{
    return { value * vector.x, value * vector.y };
}

constexpr Vector2i operator/(const int value, const Vector2i& vector)
{
    return { value / vector.x, value / vector.y };
}

constexpr Vector2i operator%(const int value, const Vector2i& vector)
{
    return { value % vector.x, value % vector.y };
}

template <typename Real>
class Vector3 {
public:
    union {
        struct {
            Real x;
            Real y;
            Real z;
        };
        Real data[3] {};
    };

    constexpr Vector3()
        : x(static_cast<Real>(0.0))
        , y(static_cast<Real>(0.0))
        , z(static_cast<Real>(0.0))
    {
    }

    explicit constexpr Vector3(const Vector3i& vector);

    template <typename Other>
    explicit constexpr Vector3(const Vector3<Other>& vector)
        : x(static_cast<Real>(vector.x))
        , y(static_cast<Real>(vector.y))
        , z(static_cast<Real>(vector.z))
    {
    }

    constexpr Vector3(const Vector2<Real>& vector, const Real z)
        : x(vector.x)
        , y(vector.y)
        , z(z)
    {
    }

    constexpr Vector3(const Real x, const Real y, const Real z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static constexpr Vector3 all(Real value)
    {
        return { value, value, value };
    }

    static constexpr Vector3 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    static constexpr Vector3 one()
    {
        return all(static_cast<Real>(1.0));
    }

    static constexpr Vector3 axis_x()
    {
        return { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector3 axis_y()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector3 axis_z()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0) };
    }

    [[nodiscard]] constexpr Vector3 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] Vector3 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z) };
    }

    [[nodiscard]] Vector3 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z) };
    }

    [[nodiscard]] Vector3 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z) };
    }

    [[nodiscard]] constexpr Vector3 clamp(const Vector3& min, const Vector3& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] Vector3 direction(const Vector3& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] constexpr Real distance_sqrd(const Vector3& to) const
    {
        const Real diff_x = to.x - x;
        const Real diff_y = to.y - y;
        const Real diff_z = to.z - z;
        return sqrd(diff_x) + sqrd(diff_y) + sqrd(diff_z);
    }

    [[nodiscard]] Real distance(const Vector3& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    [[nodiscard]] constexpr Real manhattan_distance(const Vector3& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector3 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0.0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    [[nodiscard]] Vector3 normalize() const
    {
        if (const auto length = this->length(); length > static_cast<Real>(0.0)) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] constexpr Vector3 lerp(const Vector3& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    [[nodiscard]] constexpr Vector3 lerp_clamped(const Vector3& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight) };
    }

    [[nodiscard]] constexpr Real dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] constexpr Vector3 cross(const Vector3& other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    [[nodiscard]] Matrix3<Real> outer(const Vector3& other) const;

    [[nodiscard]] constexpr Vector3 reflect(const Vector3& normal) const
    {
        Vector3 result;
        const Real dot = this->dot(normal);
        result.x = x - static_cast<Real>(2.0) * normal.x * dot;
        result.y = y - static_cast<Real>(2.0) * normal.y * dot;
        result.z = z - static_cast<Real>(2.0) * normal.z * dot;
        return result;
    }

    [[nodiscard]] constexpr Vector3 project(const Vector3& onto) const
    {
        const Real onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == static_cast<Real>(0.0)) {
            return zero();
        }
        const Real scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    [[nodiscard]] constexpr Vector3 inverse() const
    {
        return { static_cast<Real>(1.0) / x, static_cast<Real>(1.0) / y, static_cast<Real>(1.0) / z };
    }

    [[nodiscard]] Real angle(const Vector3& to) const
    {
        return atan2(this->cross(to).length(), this->dot(to));
    }

    [[nodiscard]] Vector3 translate(const Vector3& by) const;

    [[nodiscard]] Vector3 rotate_axis_angle(const Vector3& axis, Real angle) const;

    [[nodiscard]] Vector3 rotate_quaternion(const Quaternion<Real>& quaternion) const;

    [[nodiscard]] Vector3 scale(const Vector3& factor) const;

    [[nodiscard]] Vector3 shear_x(Real angle_y, Real angle_z) const;

    [[nodiscard]] Vector3 shear_y(Real angle_x, Real angle_z) const;

    [[nodiscard]] Vector3 shear_z(Real angle_x, Real angle_y) const;

    [[nodiscard]] Vector3 transform(const Basis3<Real>& by) const;

    [[nodiscard]] Vector3 transform(const Transform2<Real>& by) const;

    [[nodiscard]] Vector3 transform(const Transform3<Real>& by, Real w = static_cast<Real>(1.0)) const;

    [[nodiscard]] constexpr int max_index() const
    {
        Real max_val = x;
        auto max_axis = 0;
        if (y > max_val) {
            max_val = y;
            max_axis = 1;
        }
        if (z > max_val) {
            max_axis = 2;
        }
        return max_axis;
    }

    [[nodiscard]] constexpr int min_index() const
    {
        Real min_val = x;
        auto min_axis = 0;
        if (y < min_val) {
            min_val = y;
            min_axis = 1;
        }
        if (z < min_val) {
            min_axis = 2;
        }
        return min_axis;
    }

    [[nodiscard]] constexpr bool approx_equal(const Vector3& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z);
    }

    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z);
    }

    [[nodiscard]] constexpr Vector2<Real> xy() const
    {
        return { x, y };
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 3;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 3;
    }

    [[nodiscard]] Real at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    Real& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] const Real& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    Real& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] constexpr bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    [[nodiscard]] constexpr Vector3 operator+(const Vector3& other) const
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector3& operator+=(const Vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    [[nodiscard]] constexpr Vector3 operator-(const Vector3& other) const
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

    [[nodiscard]] constexpr Vector3 operator*(const Vector3& other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    Vector3& operator*=(const Vector3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    [[nodiscard]] Vector3 operator*(const Matrix3<Real>& matrix) const;

    [[nodiscard]] constexpr Vector3 operator*(const Real value) const
    {
        return { x * value, y * value, z * value };
    }

    Vector3& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector3 operator/(const Vector3& other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    Vector3& operator/=(const Vector3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    [[nodiscard]] constexpr Vector3 operator/(const Real value) const
    {
        return { x / value, y / value, z / value };
    }

    Vector3& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector3 operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] constexpr Vector3 operator-() const
    {
        return { -x, -y, -z };
    }

    [[nodiscard]] bool operator<(const Vector3& other) const
    {
        for (int i = 0; i < 3; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0.0) || y != static_cast<Real>(0.0) || z != static_cast<Real>(0.0);
    }
};

template <typename Real = float>
constexpr Vector3<Real> operator*(const Real value, const Vector3<Real>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

template <typename Real = float>
constexpr Vector3<Real> operator/(const Real value, const Vector3<Real>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
}

class Vector3i {
public:
    union {
        struct {
            int x;
            int y;
            int z;
        };
        int data[3] {};
    };

    constexpr Vector3i()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    template <typename Real = float>
    explicit constexpr Vector3i(const Vector3<Real>& vector)
        : x(static_cast<int>(vector.x))
        , y(static_cast<int>(vector.y))
        , z(static_cast<int>(vector.z))
    {
    }

    constexpr Vector3i(const Vector2i& vector, const int z)
        : x(vector.x)
        , y(vector.y)
        , z(z)
    {
    }

    constexpr Vector3i(const int x, const int y, const int z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static constexpr Vector3i all(const int value)
    {
        return { value, value, value };
    }

    static constexpr Vector3i zero()
    {
        return { 0, 0, 0 };
    }

    static constexpr Vector3i one()
    {
        return { 1, 1, 1 };
    }

    static constexpr Vector3i axis_x()
    {
        return { 1, 0, 0 };
    }

    static constexpr Vector3i axis_y()
    {
        return { 0, 1, 0 };
    }

    static constexpr Vector3i axis_z()
    {
        return { 0, 0, 1 };
    }

    [[nodiscard]] constexpr Vector3i abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] constexpr Vector3i clamp(const Vector3i& min, const Vector3i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] constexpr int manhattan_distance(const Vector3i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    [[nodiscard]] constexpr int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] int max_index() const
    {
        int max_axis = 0;
        if (y > data[max_axis]) {
            max_axis = 1;
        }
        if (z > data[max_axis]) {
            max_axis = 2;
        }
        return max_axis;
    }

    [[nodiscard]] int min_index() const
    {
        int min_axis = 0;
        if (y < data[min_axis]) {
            min_axis = 1;
        }
        if (z < data[min_axis]) {
            min_axis = 2;
        }
        return min_axis;
    }

    [[nodiscard]] constexpr Vector2i xy() const
    {
        return { x, y };
    }

    [[nodiscard]] const int* begin() const
    {
        return data;
    }

    [[nodiscard]] const int* end() const
    {
        return data + 3;
    }

    int* begin()
    {
        return data;
    }

    int* end()
    {
        return data + 3;
    }

    [[nodiscard]] int at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    int& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] int operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    int& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] constexpr bool operator==(const Vector3i& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector3i& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    [[nodiscard]] constexpr Vector3i operator+(const Vector3i& other) const
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

    [[nodiscard]] constexpr Vector3i operator-(const Vector3i& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vector3i& operator-=(const Vector3i& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator*(const Vector3i& other) const
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    Vector3i& operator*=(const Vector3i& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator*(const int value) const
    {
        return { x * value, y * value, z * value };
    }

    Vector3i& operator*=(const int value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator/(const Vector3i& other) const
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    Vector3i& operator/=(const Vector3i& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator/(const int value) const
    {
        return { x / value, y / value, z / value };
    }

    Vector3i& operator/=(const int value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator%(const Vector3i& other) const
    {
        return { x % other.x, y % other.y, z % other.z };
    }

    Vector3i& operator%=(const Vector3i& other)
    {
        x %= other.x;
        y %= other.y;
        z %= other.z;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator%(const int value) const
    {
        return { x % value, y % value, z % value };
    }

    Vector3i& operator%=(const int value)
    {
        x %= value;
        y %= value;
        z %= value;
        return *this;
    }

    [[nodiscard]] constexpr Vector3i operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] constexpr Vector3i operator-() const
    {
        return { -x, -y, -z };
    }

    [[nodiscard]] bool operator<(const Vector3i& other) const
    {
        for (int i = 0; i < 3; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr explicit operator bool() const
    {
        return x != 0 || y != 0 || z != 0;
    }
};

constexpr Vector3i operator*(const int value, const Vector3i& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

constexpr Vector3i operator/(const int value, const Vector3i& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
}

constexpr Vector3i operator%(const int value, const Vector3i& vector)
{
    return { value % vector.x, value % vector.y, value % vector.z };
}

template <typename Real>
class Vector4 {
public:
    union {
        struct {
            Real x;
            Real y;
            Real z;
            Real w;
        };
        Real data[4] {};
    };

    constexpr Vector4()
        : x(static_cast<Real>(0.0))
        , y(static_cast<Real>(0.0))
        , z(static_cast<Real>(0.0))
        , w(static_cast<Real>(0.0))
    {
    }

    template <typename Other>
    explicit constexpr Vector4(const Vector4<Other>& vector)
        : x(static_cast<Real>(vector.x))
        , y(static_cast<Real>(vector.y))
        , z(static_cast<Real>(vector.z))
        , w(static_cast<Real>(vector.w))
    {
    }

    constexpr Vector4(const Vector2<Real>& vector, const Real z, const Real w)
        : x(vector.x)
        , y(vector.y)
        , z(z)
        , w(w)
    {
    }

    constexpr Vector4(const Vector3<Real>& vector, const Real w)
        : x(vector.x)
        , y(vector.y)
        , z(vector.z)
        , w(w)
    {
    }

    constexpr Vector4(const Real x, const Real y, const Real z, const Real w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    static constexpr Vector4 all(const Real value)
    {
        return { value, value, value, value };
    }

    static constexpr Vector4 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    static constexpr Vector4 one()
    {
        return all(static_cast<Real>(1.0));
    }

    static constexpr Vector4 axis_x()
    {
        return { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector4 axis_y()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector4 axis_z()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) };
    }

    static constexpr Vector4 axis_w()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0) };
    }

    [[nodiscard]] constexpr Vector4 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z), nnm::abs(w) };
    }

    [[nodiscard]] Vector4 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z), nnm::ceil(w) };
    }

    [[nodiscard]] Vector4 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z), nnm::floor(w) };
    }

    [[nodiscard]] Vector4 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z), nnm::round(w) };
    }

    [[nodiscard]] constexpr Vector4 clamp(const Vector4& min, const Vector4& max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector4 clamp_length(const Real min, const Real max) const
    {
        const Real length = this->length();
        if (length == static_cast<Real>(0.0)) {
            return zero();
        }
        const auto norm = normalize();
        if (length < min) {
            return norm * min;
        }
        if (length > max) {
            return norm * max;
        }
        return *this;
    }

    [[nodiscard]] Vector4 normalize() const
    {
        if (const Real length = this->length(); length > static_cast<Real>(0.0)) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] constexpr Vector4 lerp(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    [[nodiscard]] constexpr Vector4 lerp_clamped(const Vector4& to, const Real weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight),
                 nnm::lerp_clamped(w, to.w, weight) };
    }

    [[nodiscard]] constexpr Real dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] Matrix4<Real> outer(const Vector4& other) const;

    [[nodiscard]] constexpr Vector4 inverse() const
    {
        return { static_cast<Real>(1.0) / x,
                 static_cast<Real>(1.0) / y,
                 static_cast<Real>(1.0) / z,
                 static_cast<Real>(1.0) / w };
    }

    [[nodiscard]] Vector4 transform(const Transform3<Real>& by) const;

    [[nodiscard]] int max_index() const
    {
        int max_axis = 0;
        if (y > data[max_axis]) {
            max_axis = 1;
        }
        if (z > data[max_axis]) {
            max_axis = 2;
        }
        if (w > data[max_axis]) {
            max_axis = 3;
        }
        return max_axis;
    }

    [[nodiscard]] int min_index() const
    {
        int min_axis = 0;
        if (y < data[min_axis]) {
            min_axis = 1;
        }
        if (z < data[min_axis]) {
            min_axis = 2;
        }
        if (w < data[min_axis]) {
            min_axis = 3;
        }
        return min_axis;
    }

    [[nodiscard]] constexpr bool approx_equal(const Vector4& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] constexpr bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z) && nnm::approx_zero(w);
    }

    [[nodiscard]] constexpr Vector2<Real> xy() const
    {
        return { x, y };
    }

    [[nodiscard]] constexpr Vector3<Real> xyz() const
    {
        return { x, y, z };
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 4;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 4;
    }

    [[nodiscard]] Real at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    Real& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] const Real& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    Real& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] constexpr bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] constexpr Vector4 operator+(const Vector4& other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4& operator+=(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator-(const Vector4& other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4& operator-=(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator*(const Vector4& other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4& operator*=(const Vector4& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    [[nodiscard]] Vector4 operator*(const Matrix4<Real>& matrix) const;

    [[nodiscard]] constexpr Vector4 operator*(const Real value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    Vector4& operator*=(const Real value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    [[nodiscard]] Vector4 constexpr operator/(const Vector4& other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    Vector4& operator/=(const Vector4& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    [[nodiscard]] constexpr Vector4 operator/(const Real value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    Vector4& operator/=(const Real value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Vector4& other) const
    {
        for (int i = 0; i < 4; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    [[nodiscard]] constexpr Vector4 operator+() const
    {
        return { x, y, z, w };
    }

    [[nodiscard]] constexpr Vector4 operator-() const
    {
        return { -x, -y, -z, -w };
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0.0) || y != static_cast<Real>(0.0) || z != static_cast<Real>(0.0)
            || w != static_cast<Real>(0.0);
    }
};

template <typename Real = float>
Vector4<Real> constexpr operator*(const Real value, const Vector4<Real>& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z, value * vector.w };
}

template <typename Real = float>
Vector4<Real> constexpr operator/(const Real value, const Vector4<Real>& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z, value / vector.w };
}

template <typename Real>
class Quaternion {
public:
    union {
        struct {
            Real x;
            Real y;
            Real z;
            Real w;
        };
        Vector4<Real> vector;
        Real data[4] {};
    };

    constexpr Quaternion()
        : x(static_cast<Real>(0.0))
        , y(static_cast<Real>(0.0))
        , z(static_cast<Real>(0.0))
        , w(static_cast<Real>(1.0))
    {
    }

    template <typename Other>
    explicit constexpr Quaternion(const Quaternion<Other>& quaternion)
        : x(static_cast<Real>(quaternion.x))
        , y(static_cast<Real>(quaternion.y))
        , z(static_cast<Real>(quaternion.z))
        , w(static_cast<Real>(quaternion.w))
    {
    }

    explicit constexpr Quaternion(const Vector4<Real>& vector)
        : x(vector.x)
        , y(vector.y)
        , z(vector.z)
        , w(vector.w)
    {
    }

    constexpr Quaternion(const Real x, const Real y, const Real z, const Real w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    [[nodiscard]] static constexpr Quaternion identity()
    {
        return { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0) };
    }

    [[nodiscard]] static Quaternion from_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3 norm = axis.normalize();
        const Real half_sin = sin(angle / static_cast<Real>(2.0));
        Quaternion result;
        result.x = norm.x * half_sin;
        result.y = norm.y * half_sin;
        result.z = norm.z * half_sin;
        result.w = cos(angle / static_cast<Real>(2.0));
        return result;
    }

    [[nodiscard]] static Quaternion from_vector_to_vector(const Vector3<Real>& from, const Vector3<Real>& to)
    {
        const Vector3 from_norm = from.normalize();
        const Vector3 to_norm = to.normalize();
        const Vector3 axis = from_norm.cross(to_norm).normalize();
        const Real dot = clamp(from_norm.dot(to_norm), static_cast<Real>(-1.0), static_cast<Real>(1.0));
        const Real angle = acos(dot);
        return from_axis_angle(axis, angle);
    }

    [[nodiscard]] Quaternion normalize() const
    {
        return Quaternion(vector.normalize());
    }

    [[nodiscard]] Vector3<Real> axis(const Quaternion& to) const
    {
        const Vector3 cross = vector.xyz().cross(to.vector.xyz());
        return cross.normalize();
    }

    [[nodiscard]] Real angle(const Quaternion& to) const
    {
        return 2 * acos(vector.dot(to.vector));
    }

    [[nodiscard]] Vector3<Real> axis() const
    {
        const Real sin_half_angle = sqrt(1 - sqrd(w));
        if (sin_half_angle == static_cast<Real>(0.0)) {
            return vector.xyz();
        }
        return vector.xyz() / sin_half_angle;
    }

    [[nodiscard]] Real angle() const
    {
        return 2 * acos(w);
    }

    [[nodiscard]] constexpr Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] constexpr Real length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] Real length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Quaternion slerp(const Quaternion& to, const Real weight) const
    {
        const Real dot = clamp(vector.dot(to.vector), static_cast<Real>(-1.0), static_cast<Real>(1.0));
        const Real angle = acos(dot);
        const Real sin_angle = sin(angle);
        if (sin_angle == static_cast<Real>(0.0)) {
            return Quaternion(vector.lerp(to.vector, weight));
        }
        return Quaternion(
            (vector * sin((static_cast<Real>(1.0) - weight) * angle) + to.vector * sin(weight * angle)) / sin_angle);
    }

    [[nodiscard]] Quaternion rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return from_axis_angle(axis, angle) * *this;
    }

    [[nodiscard]] Quaternion rotate_quaternion(const Quaternion& by) const
    {
        return by * *this;
    }

    [[nodiscard]] constexpr bool approx_equal(const Quaternion& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] Real at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    Real& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    [[nodiscard]] const Real& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }

    [[nodiscard]] Real& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }

    [[nodiscard]] constexpr bool operator==(const Quaternion& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] constexpr bool operator!=(const Quaternion& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] constexpr Quaternion operator*(const Quaternion& other) const
    {
        Vector4 vector;
        vector.x = w * other.x + x * other.w + y * other.z - z * other.y;
        vector.y = w * other.y - x * other.z + y * other.w + z * other.x;
        vector.z = w * other.z + x * other.y - y * other.x + z * other.w;
        vector.w = w * other.w - x * other.x - y * other.y - z * other.z;
        return Quaternion(vector);
    }

    Quaternion& operator*=(const Quaternion& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] bool operator<(const Quaternion& other) const
    {
        return vector < other.vector;
    }

    [[nodiscard]] explicit constexpr operator bool() const
    {
        return x != static_cast<Real>(0.0) || y != static_cast<Real>(0.0) || z != static_cast<Real>(0.0)
            || w != static_cast<Real>(0.0);
    }
};

template <typename Real>
class Matrix2 {
public:
    union {
        struct {
            Real col0_row0;
            Real col0_row1;
            Real col1_row0;
            Real col1_row1;
        };
        Vector2<Real> columns[2];
        Real data[4] {};
    };

    constexpr Matrix2()
        : col0_row0(static_cast<Real>(1.0))
        , col0_row1(static_cast<Real>(0.0))
        , col1_row0(static_cast<Real>(0.0))
        , col1_row1(static_cast<Real>(1.0))
    {
    }

    template <typename Other>
    explicit constexpr Matrix2(const Matrix2<Other>& matrix)
        : col0_row0(static_cast<Real>(matrix.col0_row0))
        , col0_row1(static_cast<Real>(matrix.col0_row1))
        , col1_row0(static_cast<Real>(matrix.col1_row0))
        , col1_row1(static_cast<Real>(matrix.col1_row1))
    {
    }

    constexpr Matrix2(const Vector2<Real>& column0, const Vector2<Real>& column1)
        : col0_row0(column0.x)
        , col0_row1(column0.y)
        , col1_row0(column1.x)
        , col1_row1(column1.y)
    {
    }

    constexpr Matrix2(const Real col0_row0, const Real col0_row1, const Real col1_row0, const Real col1_row1)
        : col0_row0(col0_row0)
        , col0_row1(col0_row1)
        , col1_row0(col1_row0)
        , col1_row1(col1_row1)
    {
    }

    [[nodiscard]] static constexpr Matrix2 all(const Real value)
    {
        return { { value, value }, { value, value } };
    }

    [[nodiscard]] static constexpr Matrix2 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    [[nodiscard]] static constexpr Matrix2 one()
    {
        return all(static_cast<Real>(1.0));
    }

    [[nodiscard]] static constexpr Matrix2 identity()
    {
        return { { static_cast<Real>(1.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(1.0) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1);
    }

    [[nodiscard]] Real determinant() const
    {
        return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
    }

    [[nodiscard]] Real minor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        const int other_column = (column + 1) % 2;
        const int other_row = (row + 1) % 2;
        return at(other_column, other_row);
    }

    [[nodiscard]] Matrix2 minor() const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return pow(static_cast<Real>(-1.0), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix2 cofactor() const
    {
        return { { cofactor_at(0, 0), cofactor_at(0, 1) }, { cofactor_at(1, 0), cofactor_at(1, 1) } };
    }

    [[nodiscard]] Matrix2 transpose() const
    {
        return { { at(0, 0), at(1, 0) }, { at(0, 1), at(1, 1) } };
    }

    [[nodiscard]] Matrix2 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix2 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix2> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0.0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (!nnm::approx_equal(at(c, r), other.at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (!nnm::approx_zero(at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] Vector2<Real> at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    [[nodiscard]] Real at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 4;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 4;
    }

    const Vector2<Real>& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2<Real>& operator[](const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    bool operator==(const Matrix2& other) const
    {
        for (int i = 0; i < 4; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix2& other) const
    {
        for (int i = 0; i < 4; ++i) {
            if (data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix2 operator+(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix2& operator+=(const Matrix2& other)
    {
        for (int c = 0; c < 2; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator-(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix2& operator-=(const Matrix2& other)
    {
        for (int c = 0; c < 2; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator*(const Matrix2& other) const
    {
        auto result = zero();
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                for (int i = 0; i < 2; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix2& operator*=(const Matrix2& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector2<Real> operator*(const Vector2<Real>& vector) const
    {
        Vector2 result;
        for (int r = 0; r < 2; ++r) {
            result.at(r) = at(0, r) * vector.at(0) + at(1, r) * vector.at(1);
        }
        return result;
    }

    [[nodiscard]] Matrix2 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value };
    }

    Matrix2& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        return *this;
    }

    [[nodiscard]] Matrix2 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value };
    }

    Matrix2& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        return *this;
    }

    bool operator<(const Matrix2& other) const
    {
        for (int i = 0; i < 4; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) != 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

template <typename Real = float>
Matrix2<Real> operator*(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real = float>
Matrix2<Real> operator/(const Real value, const Matrix2<Real>& matrix)
{
    Matrix2<Real> result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Basis2 {
public:
    Matrix2<Real> matrix;

    constexpr Basis2()
        : matrix(Matrix2<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Basis2(const Basis2<Other>& basis)
        : matrix(Matrix2<Real>(basis.matrix))
    {
    }

    explicit constexpr Basis2(const Matrix2<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Basis2 from_rotation(const Real angle)
    {
        return Basis2({ { cos(angle), sin(angle) }, { -sin(angle), cos(angle) } });
    }

    static constexpr Basis2 from_scale(const Vector2<Real>& factor)
    {
        return Basis2({ { factor.x, static_cast<Real>(0.0) }, { static_cast<Real>(0.0), factor.y } });
    }

    static Basis2 from_shear_x(const Real angle_y)
    {
        return Basis2({ { static_cast<Real>(1.0), static_cast<Real>(0.0) }, { tan(angle_y), static_cast<Real>(1.0) } });
    }

    static Basis2 from_shear_y(const Real angle_x)
    {
        return Basis2({ { static_cast<Real>(1.0), tan(angle_x) }, { static_cast<Real>(0.0), static_cast<Real>(1.0) } });
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Basis2 unchecked_inverse() const
    {
        return Basis2(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Basis2> inverse() const
    {
        if (valid()) {
            return Basis2(matrix.unchecked_inverse());
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0.0);
    }

    [[nodiscard]] Basis2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Basis2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Basis2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis2 shear_x(const Real angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_x_local(const Real angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_y(const Real angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Basis2 shear_y_local(const Real angle_x) const
    {
        return transform_local(from_shear_y(angle_x));
    }

    [[nodiscard]] Basis2 transform(const Basis2& by) const
    {
        return Basis2(by.matrix * matrix);
    }

    [[nodiscard]] Basis2 transform_local(const Basis2& by) const
    {
        return Basis2(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Basis2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] const Vector2<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    Vector2<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    const Vector2<Real>& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index >= 0 && index <= 1);
        return matrix[index];
    }

    Vector2<Real>& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index >= 0 && index <= 1);
        return matrix[index];
    }

    bool operator==(const Basis2& other) const
    {
        return matrix == other.matrix;
    }

    bool operator!=(const Basis2& other) const
    {
        return matrix != other.matrix;
    }

    bool operator<(const Basis2& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Matrix3 {
public:
    union {
        struct {
            Real col0_row0;
            Real col0_row1;
            Real col0_row2;
            Real col1_row0;
            Real col1_row1;
            Real col1_row2;
            Real col2_row0;
            Real col2_row1;
            Real col2_row2;
        };
        Vector3<Real> columns[3];
        Real data[9] {};
    };

    constexpr Matrix3()
        : col0_row0(static_cast<Real>(1.0))
        , col0_row1(static_cast<Real>(0.0))
        , col0_row2(static_cast<Real>(0.0))
        , col1_row0(static_cast<Real>(0.0))
        , col1_row1(static_cast<Real>(1.0))
        , col1_row2(static_cast<Real>(0.0))
        , col2_row0(static_cast<Real>(0.0))
        , col2_row1(static_cast<Real>(0.0))
        , col2_row2(static_cast<Real>(1.0))
    {
    }

    template <typename Other>
    explicit constexpr Matrix3(const Matrix3<Other>& matrix)
        : col0_row0(static_cast<Real>(matrix.col0_row0))
        , col0_row1(static_cast<Real>(matrix.col0_row1))
        , col0_row2(static_cast<Real>(matrix.col0_row2))
        , col1_row0(static_cast<Real>(matrix.col1_row0))
        , col1_row1(static_cast<Real>(matrix.col1_row1))
        , col1_row2(static_cast<Real>(matrix.col1_row2))
        , col2_row0(static_cast<Real>(matrix.col2_row0))
        , col2_row1(static_cast<Real>(matrix.col2_row1))
        , col2_row2(static_cast<Real>(matrix.col2_row2))
    {
    }

    constexpr Matrix3(const Vector3<Real>& column0, const Vector3<Real>& column1, const Vector3<Real>& column2)
        : col0_row0(column0.x)
        , col0_row1(column0.y)
        , col0_row2(column0.z)
        , col1_row0(column1.x)
        , col1_row1(column1.y)
        , col1_row2(column1.z)
        , col2_row0(column2.x)
        , col2_row1(column2.y)
        , col2_row2(column2.z)
    {
    }

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
        : col0_row0(col0_row0)
        , col0_row1(col0_row1)
        , col0_row2(col0_row2)
        , col1_row0(col1_row0)
        , col1_row1(col1_row1)
        , col1_row2(col1_row2)
        , col2_row0(col2_row0)
        , col2_row1(col2_row1)
        , col2_row2(col2_row2)
    {
    }

    [[nodiscard]] static constexpr Matrix3 all(const Real value)
    {
        return { { value, value, value }, { value, value, value }, { value, value, value } };
    }

    [[nodiscard]] static constexpr Matrix3 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    [[nodiscard]] static constexpr Matrix3 one()
    {
        return all(static_cast<Real>(1.0));
    }

    [[nodiscard]] static constexpr Matrix3 identity()
    {
        return { { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2);
    }

    [[nodiscard]] Real determinant() const
    {
        Real det = static_cast<Real>(0.0);
        for (int c = 0; c < 3; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1.0) : -static_cast<Real>(1.0)) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix2<Real> minor_matrix_at(const int column, const int row) const
    {
        Matrix2 minor_matrix;
        int minor_col = 0;
        for (int c = 0; c < 3; ++c) {
            if (c == column) {
                continue;
            }
            int minor_row = 0;
            for (int r = 0; r < 3; ++r) {
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

    [[nodiscard]] Real minor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix3 minor() const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return pow(-static_cast<Real>(1.0), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix3 cofactor() const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0) }, { at(0, 1), at(1, 1), at(2, 1) }, { at(0, 2), at(1, 2), at(2, 2) } };
    }

    [[nodiscard]] Matrix3 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix3 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix3> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0.0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix3& other) const
    {
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                if (!nnm::approx_equal(at(c, r), other.at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                if (!nnm::approx_zero(at(c, r))) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] const Vector3<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 9;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 9;
    }

    const Vector3<Real>& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3<Real>& operator[](const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] bool operator==(const Matrix3& other) const
    {
        for (int i = 0; i < 9; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix3& other) const
    {
        for (int i = 0; i < 9; ++i) {
            if (data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix3 operator+(const Matrix3& other) const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix3& operator+=(const Matrix3& other)
    {
        for (int c = 0; c < 3; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator-(const Matrix3& other) const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix3& operator-=(const Matrix3& other)
    {
        for (int c = 0; c < 3; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator*(const Matrix3& other) const
    {
        auto result = zero();
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                for (int i = 0; i < 3; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix3& operator*=(const Matrix3& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector3<Real> operator*(const Vector3<Real>& vector) const
    {
        auto result = Vector3<Real>::zero();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 operator*(const Real value) const
    {
        return { at(0) * value, at(1) * value, at(2) * value };
    }

    Matrix3& operator*=(const Real value)
    {
        at(0) *= value;
        at(1) *= value;
        at(2) *= value;
        return *this;
    }

    [[nodiscard]] Matrix3 operator/(const Real value) const
    {
        return { at(0) / value, at(1) / value, at(2) / value };
    }

    Matrix3& operator/=(const Real value)
    {
        at(0) /= value;
        at(1) /= value;
        at(2) /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Matrix3& other) const
    {
        for (int i = 0; i < 9; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (int c = 0; c < 3; ++c) { // NOLINT(*-loop-convert)
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

template <typename Real = float>
Matrix3<Real> operator*(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real = float>
Matrix3<Real> operator/(const Real value, const Matrix3<Real>& matrix)
{
    Matrix3<Real> result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Transform2 {
public:
    Matrix3<Real> matrix;

    constexpr Transform2()
        : matrix(Matrix3<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Transform2(const Transform2<Other>& transform)
        : matrix(Matrix3<Real>(transform.matrix))
    {
    }

    explicit constexpr Transform2(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Transform2 from_basis_translation(const Basis2<Real>& basis, const Vector2<Real>& translation)
    {
        Matrix3 matrix;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(2, 0) = translation.x;
        matrix.at(2, 1) = translation.y;
        return Transform2(matrix);
    }

    static Transform2 from_basis(const Basis2<Real>& basis)
    {
        return from_basis_translation(basis, Vector2<Real>::zero());
    }

    static Transform2 from_translation(const Vector2<Real>& pos)
    {
        return from_basis_translation(Basis2(), pos);
    }

    static Transform2 from_rotation(const Real angle)
    {
        return from_basis_translation(Basis2<Real>::from_rotation(angle), Vector2());
    }

    static Transform2 from_scale(const Vector2<Real>& factor)
    {
        return from_basis_translation(Basis2<Real>::from_scale(factor), Vector2());
    }

    static Transform2 from_shear_x(const Real angle_y)
    {
        return from_basis_translation(Basis2<Real>::from_shear_x(angle_y), Vector2());
    }

    static Transform2 from_shear_y(const Real angle_x)
    {
        return from_basis_translation(Basis2<Real>::from_shear_y(angle_x), Vector2());
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Transform2 unchecked_inverse() const
    {
        return Transform2(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Transform2> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix.at(0, 2) == static_cast<Real>(0.0) && matrix.at(1, 2) == static_cast<Real>(0.0)
            && matrix.at(2, 2) == static_cast<Real>(1.0);
    }

    [[nodiscard]] Basis2<Real> basis() const
    {
        return Basis2(matrix.minor_matrix_at(2, 2));
    }

    [[nodiscard]] Vector2<Real> translation() const
    {
        return { matrix.at(2, 0), matrix.at(2, 1) };
    }

    [[nodiscard]] Transform2 translate(const Vector2<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform2 translate_local(const Vector2<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform2 rotate(const Real angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Transform2 rotate_local(const Real angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Transform2 scale(const Vector2<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform2 scale_local(const Vector2<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform2 shear_x(const Real angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_x_local(const Real angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_y(const Real angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Transform2 shear_y_local(const Real angle_x) const
    {
        return transform_local(from_shear_y(angle_x));
    }

    [[nodiscard]] Transform2 transform(const Transform2& by) const
    {
        return Transform2(by.matrix * matrix);
    }

    [[nodiscard]] Transform2 transform_local(const Transform2& by) const
    {
        return Transform2(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Transform2& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector3<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    Vector3<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return matrix.at(column, row);
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3<Real>& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    Vector3<Real>& operator[](const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    [[nodiscard]] bool operator==(const Transform2& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Transform2& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Transform2& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Basis3 {
public:
    Matrix3<Real> matrix;

    constexpr Basis3()
        : matrix(Matrix3<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Basis3(const Basis3<Other>& basis)
        : matrix(Matrix3<Real>(basis.matrix))
    {
    }

    explicit constexpr Basis3(const Matrix3<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Basis3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const Vector3 norm = axis.normalize();
        // Rodrigues' formula
        const Matrix3 k_matrix { { static_cast<Real>(0.0), norm.z, -norm.y },
                                 { -norm.z, static_cast<Real>(0.0), norm.x },
                                 { norm.y, -norm.x, static_cast<Real>(0.0) } };
        const Matrix3 r_matrix
            = Matrix3<Real>::identity() + sin(angle) * k_matrix + (1 - cos(angle)) * k_matrix * k_matrix;
        return Basis3(r_matrix);
    }

    static Basis3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const Quaternion<Real>& q = quaternion;
        Matrix3 matrix;
        matrix.at(0, 0) = 1 - 2 * (sqrd(q.y) + sqrd(q.z));
        matrix.at(0, 1) = 2 * (q.x * q.y + q.z * q.w);
        matrix.at(0, 2) = 2 * (q.x * q.z - q.y * q.w);
        matrix.at(1, 0) = 2 * (q.x * q.y - q.z * q.w);
        matrix.at(1, 1) = 1 - 2 * (sqrd(q.x) + sqrd(q.z));
        matrix.at(1, 2) = 2 * (q.y * q.z + q.x * q.w);
        matrix.at(2, 0) = 2 * (q.x * q.z + q.y * q.w);
        matrix.at(2, 1) = 2 * (q.y * q.z - q.x * q.w);
        matrix.at(2, 2) = 1 - 2 * (sqrd(q.x) + sqrd(q.y));
        return Basis3(matrix);
    }

    static constexpr Basis3 from_scale(const Vector3<Real>& factor)
    {
        return Basis3({ { factor.x, static_cast<Real>(0.0), static_cast<Real>(0.0) },
                        { static_cast<Real>(0.0), factor.y, static_cast<Real>(0.0) },
                        { static_cast<Real>(0.0), static_cast<Real>(0.0), factor.z } });
    }

    static Basis3 from_shear_x(const Real angle_y, const Real angle_z)
    {
        return Basis3({ { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) },
                        { tan(angle_y), static_cast<Real>(1.0), static_cast<Real>(0.0) },
                        { tan(angle_z), static_cast<Real>(0.0), static_cast<Real>(1.0) } });
    }

    static Basis3 from_shear_y(const Real angle_x, const Real angle_z)
    {
        return Basis3({ { static_cast<Real>(1.0), tan(angle_x), static_cast<Real>(0.0) },
                        { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) },
                        { static_cast<Real>(0.0), tan(angle_z), static_cast<Real>(1.0) } });
    }

    static Basis3 from_shear_z(const Real angle_x, const Real angle_y)
    {
        return Basis3({ { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) },
                        { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) },
                        { tan(angle_x), tan(angle_y), static_cast<Real>(1.0) } });
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Basis3 unchecked_inverse() const
    {
        return Basis3(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Basis3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != static_cast<Real>(0.0);
    }

    [[nodiscard]] Basis3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_x_local(const Real angle_y, const Real angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_y_local(const Real angle_x, const Real angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Basis3 shear_z_local(const Real angle_x, const Real angle_y) const
    {
        return transform_local(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Basis3 transform(const Basis3& by) const
    {
        return Basis3(by.matrix * matrix);
    }

    [[nodiscard]] Basis3 transform_local(const Basis3& by) const
    {
        return Basis3(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Basis3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector3<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector3<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3<Real>& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index >= 0 && index <= 3);
        return matrix[index];
    }

    Vector3<Real>& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index >= 0 && index <= 3);
        return matrix[index];
    }

    [[nodiscard]] bool operator==(const Basis3& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Basis3& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Basis3& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
class Matrix4 {
public:
    union {
        struct {
            Real col0_row0;
            Real col0_row1;
            Real col0_row2;
            Real col0_row3;
            Real col1_row0;
            Real col1_row1;
            Real col1_row2;
            Real col1_row3;
            Real col2_row0;
            Real col2_row1;
            Real col2_row2;
            Real col2_row3;
            Real col3_row0;
            Real col3_row1;
            Real col3_row2;
            Real col3_row3;
        };
        Vector4<Real> columns[4];
        Real data[16] {};
    };

    constexpr Matrix4()
        : col0_row0(static_cast<Real>(1.0))
        , col0_row1(static_cast<Real>(0.0))
        , col0_row2(static_cast<Real>(0.0))
        , col0_row3(static_cast<Real>(0.0))
        , col1_row0(static_cast<Real>(0.0))
        , col1_row1(static_cast<Real>(1.0))
        , col1_row2(static_cast<Real>(0.0))
        , col1_row3(static_cast<Real>(0.0))
        , col2_row0(static_cast<Real>(0.0))
        , col2_row1(static_cast<Real>(0.0))
        , col2_row2(static_cast<Real>(1.0))
        , col2_row3(static_cast<Real>(0.0))
        , col3_row0(static_cast<Real>(0.0))
        , col3_row1(static_cast<Real>(0.0))
        , col3_row2(static_cast<Real>(0.0))
        , col3_row3(static_cast<Real>(1.0))
    {
    }

    template <typename Other>
    explicit constexpr Matrix4(const Matrix4<Other>& matrix)
        : col0_row0(static_cast<Real>(matrix.col0_row0))
        , col0_row1(static_cast<Real>(matrix.col0_row1))
        , col0_row2(static_cast<Real>(matrix.col0_row2))
        , col0_row3(static_cast<Real>(matrix.col0_row3))
        , col1_row0(static_cast<Real>(matrix.col1_row0))
        , col1_row1(static_cast<Real>(matrix.col1_row1))
        , col1_row2(static_cast<Real>(matrix.col1_row2))
        , col1_row3(static_cast<Real>(matrix.col1_row3))
        , col2_row0(static_cast<Real>(matrix.col2_row0))
        , col2_row1(static_cast<Real>(matrix.col2_row1))
        , col2_row2(static_cast<Real>(matrix.col2_row2))
        , col2_row3(static_cast<Real>(matrix.col2_row3))
        , col3_row0(static_cast<Real>(matrix.col3_row0))
        , col3_row1(static_cast<Real>(matrix.col3_row1))
        , col3_row2(static_cast<Real>(matrix.col3_row2))
        , col3_row3(static_cast<Real>(matrix.col3_row3))
    {
    }

    constexpr Matrix4(
        const Vector4<Real>& column0,
        const Vector4<Real>& column1,
        const Vector4<Real>& column2,
        const Vector4<Real>& column3)
        : col0_row0(column0.x)
        , col0_row1(column0.y)
        , col0_row2(column0.z)
        , col0_row3(column0.w)
        , col1_row0(column1.x)
        , col1_row1(column1.y)
        , col1_row2(column1.z)
        , col1_row3(column1.w)
        , col2_row0(column2.x)
        , col2_row1(column2.y)
        , col2_row2(column2.z)
        , col2_row3(column2.w)
        , col3_row0(column3.x)
        , col3_row1(column3.y)
        , col3_row2(column3.z)
        , col3_row3(column3.w)
    {
    }

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
        : col0_row0(col0_row0)
        , col0_row1(col0_row1)
        , col0_row2(col0_row2)
        , col0_row3(col0_row3)
        , col1_row0(col1_row0)
        , col1_row1(col1_row1)
        , col1_row2(col1_row2)
        , col1_row3(col1_row3)
        , col2_row0(col2_row0)
        , col2_row1(col2_row1)
        , col2_row2(col2_row2)
        , col2_row3(col2_row3)
        , col3_row0(col3_row0)
        , col3_row1(col3_row1)
        , col3_row2(col3_row2)
        , col3_row3(col3_row3)
    {
    }

    [[nodiscard]] static constexpr Matrix4 all(const Real value)
    {
        return { { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value } };
    }

    [[nodiscard]] static constexpr Matrix4 zero()
    {
        return all(static_cast<Real>(0.0));
    }

    [[nodiscard]] static constexpr Matrix4 one()
    {
        return all(static_cast<Real>(1.0));
    }

    [[nodiscard]] static constexpr Matrix4 identity()
    {
        return { { static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0), static_cast<Real>(0.0) },
                 { static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(1.0) } };
    }

    [[nodiscard]] Real trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2) + at(3, 3);
    }

    [[nodiscard]] Real determinant() const
    {
        Real det = static_cast<Real>(0.0);
        for (int c = 0; c < 4; ++c) {
            const Real det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? static_cast<Real>(1.0) : -static_cast<Real>(1.0)) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix3<Real> minor_matrix_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        Matrix3 minor_matrix;
        int minor_col = 0;
        for (int c = 0; c < 4; ++c) {
            if (c == column) {
                continue;
            }
            int minor_row = 0;
            for (int r = 0; r < 4; ++r) {
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

    [[nodiscard]] Real minor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix4 minor() const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                result.at(c, r) = minor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Real cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return pow(-static_cast<Real>(1.0), static_cast<Real>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix4 cofactor() const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                result.at(c, r) = cofactor_at(c, r);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix4 transpose() const
    {
        return { { at(0, 0), at(1, 0), at(2, 0), at(3, 0) },
                 { at(0, 1), at(1, 1), at(2, 1), at(3, 1) },
                 { at(0, 2), at(1, 2), at(2, 2), at(3, 2) },
                 { at(0, 3), at(1, 3), at(2, 3), at(3, 3) } };
    }

    [[nodiscard]] Matrix4 adjugate() const
    {
        return cofactor().transpose();
    }

    [[nodiscard]] Matrix4 unchecked_inverse() const
    {
        return adjugate() / determinant();
    }

    [[nodiscard]] std::optional<Matrix4> inverse() const
    {
        const Real det = determinant();
        if (det == static_cast<Real>(0.0)) {
            return std::nullopt;
        }
        return adjugate() / det;
    }

    [[nodiscard]] bool approx_equal(const Matrix4& other) const
    {
        for (int c = 0; c < 4; ++c) {
            if (!at(c).approx_equal(other.at(c))) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool approx_zero() const
    {
        for (int c = 0; c < 4; ++c) {
            if (!at(c).approx_zero()) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] const Vector4<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    Vector4<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    [[nodiscard]] const Real* begin() const
    {
        return data;
    }

    [[nodiscard]] const Real* end() const
    {
        return data + 16;
    }

    Real* begin()
    {
        return data;
    }

    Real* end()
    {
        return data + 16;
    }

    const Vector4<Real>& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    Vector4<Real>& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    [[nodiscard]] bool operator==(const Matrix4& other) const
    {
        for (int i = 0; i < 16; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix4& other) const
    {
        for (int i = 0; i < 16; ++i) {
            if (data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Matrix4 operator+(const Matrix4& other) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix4& operator+=(const Matrix4& other)
    {
        for (int c = 0; c < 4; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator-(const Matrix4& other) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix4& operator-=(const Matrix4& other)
    {
        for (int c = 0; c < 4; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    Matrix4 operator*(const Matrix4& other) const
    {
        auto result = zero();
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                for (int i = 0; i < 4; ++i) {
                    result.at(c, r) += at(i, r) * other.at(c, i);
                }
            }
        }
        return result;
    }

    Matrix4& operator*=(const Matrix4& other)
    {
        *this = *this * other;
        return *this;
    }

    Vector4<Real> operator*(const Vector4<Real>& vector) const
    {
        auto result = Vector4<Real>::zero();
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix4 operator*(const Real value) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) * value;
        }
        return result;
    }

    Matrix4& operator*=(const Real value)
    {
        for (int c = 0; c < 4; ++c) {
            at(c) *= value;
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator/(const Real value) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) / value;
        }
        return result;
    }

    Matrix4& operator/=(const Real value)
    {
        for (int c = 0; c < 4; ++c) {
            at(c) /= value;
        }
        return *this;
    }

    bool operator<(const Matrix4& other) const
    {
        for (int i = 0; i < 16; ++i) {
            if (data[i] < other.data[i]) {
                return true;
            }
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return false;
    }

    explicit operator bool() const
    {
        for (int c = 0; c < 4; ++c) {
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
    }
};

template <typename Real = float>
Matrix4<Real> operator*(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real = float>
Matrix4<Real> operator/(const Real value, const Matrix4<Real>& matrix)
{
    Matrix4<Real> result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
class Transform3 {
public:
    Matrix4<Real> matrix;

    constexpr Transform3()
        : matrix(Matrix4<Real>::identity())
    {
    }

    template <typename Other>
    explicit constexpr Transform3(const Transform3<Other>& transform)
        : matrix(Matrix4<Real>(transform.matrix))
    {
    }

    explicit constexpr Transform3(const Matrix4<Real>& matrix)
        : matrix(matrix)
    {
    }

    static Transform3 from_basis_translation(const Basis3<Real>& basis, const Vector3<Real>& translation)
    {
        auto matrix = Matrix4<Real>::identity();
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                matrix.at(c, r) = basis.at(c, r);
            }
        }
        matrix.at(3, 0) = translation.x;
        matrix.at(3, 1) = translation.y;
        matrix.at(3, 2) = translation.z;
        return Transform3(matrix);
    }

    static Transform3 from_basis(const Basis3<Real>& basis)
    {
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_translation(const Vector3<Real>& translation)
    {
        return from_basis_translation(Basis3(), translation);
    }

    static Transform3 from_rotation_axis_angle(const Vector3<Real>& axis, const Real angle)
    {
        const auto basis = Basis3<Real>::from_rotation_axis_angle(axis, angle);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_rotation_quaternion(const Quaternion<Real>& quaternion)
    {
        const auto basis = Basis3<Real>::from_rotation_quaternion(quaternion);
        return from_basis_translation(basis, Vector3<Real>::zero());
    }

    static Transform3 from_scale(const Vector3<Real>& factor)
    {
        return from_basis(Basis3<Real>::from_scale(factor));
    }

    static Transform3 from_shear_x(const Real angle_y, const Real angle_z)
    {
        return from_basis(Basis3<Real>::from_shear_x(angle_y, angle_z));
    }

    static Transform3 from_shear_y(const Real angle_x, const Real angle_z)
    {
        return from_basis(Basis3<Real>::from_shear_y(angle_x, angle_z));
    }

    static Transform3 from_shear_z(const Real angle_x, const Real angle_y)
    {
        return from_basis(Basis3<Real>::from_shear_z(angle_x, angle_y));
    }

    static Transform3 from_perspective_left_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near, const Real far)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2.0));
        matrix.at(0, 0) = static_cast<Real>(1.0) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1.0) / tan_half_fov;
        matrix.at(2, 2) = -(far + near) / (far - near);
        matrix.at(2, 3) = -static_cast<Real>(1.0);
        matrix.at(3, 2) = -(static_cast<Real>(2.0) * far * near) / (far - near);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_left_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near, const Real far)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2.0));
        matrix.at(0, 0) = static_cast<Real>(1.0) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1.0) / tan_half_fov;
        matrix.at(2, 2) = -far / (far - near);
        matrix.at(2, 3) = -static_cast<Real>(1.0);
        matrix.at(3, 2) = -(far * near) / (far - near);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_right_hand_neg1to1(
        const Real fov, const Real aspect_ratio, const Real near, const Real far)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2.0));
        matrix.at(0, 0) = static_cast<Real>(1.0) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1.0) / tan_half_fov;
        matrix.at(2, 2) = (far + near) / (far - near);
        matrix.at(2, 3) = static_cast<Real>(1.0);
        matrix.at(3, 2) = -(static_cast<Real>(2.0) * far * near) / (far - near);
        return Transform3(matrix);
    }

    static Transform3 from_perspective_right_hand_0to1(
        const Real fov, const Real aspect_ratio, const Real near, const Real far)
    {
        auto matrix = Matrix4<Real>::zero();
        const Real tan_half_fov = tan(fov / static_cast<Real>(2.0));
        matrix.at(0, 0) = static_cast<Real>(1.0) / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = static_cast<Real>(1.0) / tan_half_fov;
        matrix.at(2, 2) = far / (far - near);
        matrix.at(2, 3) = static_cast<Real>(1.0);
        matrix.at(3, 2) = -(far * near) / (far - near);
        return Transform3(matrix);
    }

    static Transform3 from_projection_orthographic(
        const Real left, const Real right, const Real bottom, const Real top, const Real near, const Real far)
    {
        auto matrix = Matrix4<Real>::identity();
        matrix.at(0, 0) = static_cast<Real>(2.0) / (right - left);
        matrix.at(1, 1) = static_cast<Real>(2.0) / (top - bottom);
        matrix.at(2, 2) = -static_cast<Real>(2.0) / (far - near);
        matrix.at(3, 0) = -((right + left) / (right - left));
        matrix.at(3, 1) = -((top + bottom) / (top - bottom));
        matrix.at(3, 2) = -((far + near) / (far - near));
        return Transform3(matrix);
    }

    [[nodiscard]] Real trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] Real determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] Transform3 unchecked_inverse() const
    {
        return Transform3(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Transform3> inverse() const
    {
        if (valid()) {
            return unchecked_inverse();
        }
        return std::nullopt;
    }

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix.at(0, 3) == static_cast<Real>(0.0) && matrix.at(1, 3) == static_cast<Real>(0.0)
            && matrix.at(2, 3) == static_cast<Real>(0.0) && matrix.at(3, 3) == static_cast<Real>(1.0);
    }

    [[nodiscard]] Basis3<Real> basis() const
    {
        return Basis3(matrix.minor_matrix_at(3, 3));
    }

    [[nodiscard]] Vector3<Real> translation() const
    {
        return { matrix.at(3, 0), matrix.at(3, 1), matrix.at(3, 2) };
    }

    [[nodiscard]] Transform3 translate(const Vector3<Real>& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform3 translate_local(const Vector3<Real>& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform3 rotate_axis_angle(const Vector3<Real>& axis, const Real angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_axis_angle_local(const Vector3<Real>& axis, const Real angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_quaternion(const Quaternion<Real>& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 rotate_quaternion_local(const Quaternion<Real>& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 scale(const Vector3<Real>& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform3 scale_local(const Vector3<Real>& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform3 shear_x(const Real angle_y, const Real angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_x_local(const Real angle_y, const Real angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_y(const Real angle_x, const Real angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_y_local(const Real angle_x, const Real angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_z(const Real angle_x, const Real angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Transform3 shear_z_local(const Real angle_x, const Real angle_y) const
    {
        return transform_local(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Transform3 transform(const Transform3& by) const
    {
        return Transform3(by.matrix * matrix);
    }

    [[nodiscard]] Transform3 transform_local(const Transform3& by) const
    {
        return Transform3(matrix * by.matrix);
    }

    [[nodiscard]] bool approx_equal(const Transform3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector4<Real>& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector4<Real>& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const Real& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    Real& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector4<Real>& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix[column];
    }

    Vector4<Real>& operator[](const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix[column];
    }

    [[nodiscard]] bool operator==(const Transform3& other) const
    {
        return matrix == other.matrix;
    }

    [[nodiscard]] bool operator!=(const Transform3& other) const
    {
        return matrix != other.matrix;
    }

    [[nodiscard]] bool operator<(const Transform3& other) const
    {
        return matrix < other.matrix;
    }
};

template <typename Real>
constexpr Vector2<Real>::Vector2(const Vector2i& vector)
    : x(static_cast<Real>(vector.x))
    , y(static_cast<Real>(vector.y))
{
}

template <typename Real>
Matrix2<Real> Vector2<Real>::outer(const Vector2& other) const
{
    Matrix2<Real> result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector2<Real> Vector2<Real>::translate(const Vector2& by) const
{
    const auto transform = Transform2<Real>::from_translation(by);
    return this->transform(transform);
}

template <typename Real>
Vector2<Real> Vector2<Real>::rotate(const Real angle) const
{
    const auto transform = Transform2<Real>::from_rotation(angle);
    return this->transform(transform);
}

template <typename Real>
Vector2<Real> Vector2<Real>::scale(const Vector2& factor) const
{
    const auto transform = Transform2<Real>::from_scale(factor);
    return this->transform(transform);
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_x(const Real angle_y) const
{
    const auto transform = Transform2<Real>::from_shear_x(angle_y);
    return this->transform(transform);
}

template <typename Real>
Vector2<Real> Vector2<Real>::shear_y(const Real angle_x) const
{
    const auto transform = Transform2<Real>::from_shear_y(angle_x);
    return this->transform(transform);
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform(const Basis2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector2<Real> Vector2<Real>::transform(const Transform2<Real>& by, const Real z) const
{
    return Vector3(*this, z).transform(by).xy();
}

template <typename Real>
Vector2<Real> Vector2<Real>::operator*(const Matrix2<Real>& matrix) const
{
    Vector2 result;
    result.x = x * matrix.at(0, 0) + y * matrix.at(0, 1);
    result.y = x * matrix.at(1, 0) + y * matrix.at(1, 1);
    return result;
}

template <typename Real>
constexpr Vector3<Real>::Vector3(const Vector3i& vector)
    : x(static_cast<Real>(vector.x))
    , y(static_cast<Real>(vector.y))
    , z(static_cast<Real>(vector.z))
{
}

template <typename Real>
Matrix3<Real> Vector3<Real>::outer(const Vector3& other) const
{
    Matrix3<Real> result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector3<Real> Vector3<Real>::translate(const Vector3& by) const
{
    const auto transform = Transform3<Real>::from_translation(by);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_axis_angle(const Vector3& axis, const Real angle) const
{
    const auto transform = Transform3<Real>::from_rotation_axis_angle(axis, angle);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::rotate_quaternion(const Quaternion<Real>& quaternion) const
{
    const auto transform = Transform3<Real>::from_rotation_quaternion(quaternion);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::scale(const Vector3& factor) const
{
    const auto transform = Transform3<Real>::from_scale(factor);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_x(const Real angle_y, const Real angle_z) const
{
    const auto transform = Transform3<Real>::from_shear_x(angle_y, angle_z);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_y(const Real angle_x, const Real angle_z) const
{
    const auto transform = Transform3<Real>::from_shear_y(angle_x, angle_z);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::shear_z(const Real angle_x, const Real angle_y) const
{
    const auto transform = Transform3<Real>::from_shear_z(angle_x, angle_y);
    return this->transform(transform);
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Basis3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Transform2<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector3<Real> Vector3<Real>::transform(const Transform3<Real>& by, const Real w) const
{
    return Vector4(*this, w).transform(by).xyz();
}

template <typename Real>
Vector3<Real> Vector3<Real>::operator*(const Matrix3<Real>& matrix) const
{
    auto result = zero();
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}

template <typename Real>
Matrix4<Real> Vector4<Real>::outer(const Vector4& other) const
{
    Matrix4 result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

template <typename Real>
Vector4<Real> Vector4<Real>::transform(const Transform3<Real>& by) const
{
    return by.matrix * *this;
}

template <typename Real>
Vector4<Real> Vector4<Real>::operator*(const Matrix4<Real>& matrix) const
{
    auto result = zero();
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}
}

template <>
struct std::hash<nnm::Vector2i> {
    size_t operator()(const nnm::Vector2i& vector) const noexcept
    {
        const size_t hash1 = std::hash<int>()(vector.x);
        const size_t hash2 = std::hash<int>()(vector.y);
        return hash1 ^ hash2 << 1;
    }
};

template <>
struct std::hash<nnm::Vector3i> {
    size_t operator()(const nnm::Vector3i& vector) const noexcept
    {
        const size_t hash1 = std::hash<int>()(vector.x);
        const size_t hash2 = std::hash<int>()(vector.y);
        const size_t hash3 = std::hash<int>()(vector.z);
        return hash1 ^ hash2 << 1 ^ hash3 << 2;
    }
};

#endif
