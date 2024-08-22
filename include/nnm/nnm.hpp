#pragma once

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
constexpr float pi = 3.141592653589793238462643383279502f;
constexpr float epsilon = 0.00001f;

inline float sign(const float value)
{
    return std::copysignf(1.0f, value);
}

inline int sign(const int value)
{
    return (value >= 0) - (value < 0);
}

inline float abs(const float value)
{
    return std::abs(value);
}

inline int abs(const int value)
{
    return std::abs(value);
}

inline float max(const float a, const float b)
{
    return std::max(a, b);
}

inline int max(const int a, const int b)
{
    return std::max(a, b);
}

inline bool approx_zero(const float value)
{
    float tolerance = epsilon * abs(value);
    tolerance = max(tolerance, epsilon);
    return abs(value) <= tolerance;
}

inline bool approx_equal(const float a, const float b)
{
    if (a == b) {
        return true;
    }
    float tolerance = epsilon * max(abs(a), abs(b));
    tolerance = max(tolerance, epsilon);
    return abs(a - b) <= tolerance;
}

inline float ceil(const float value)
{
    return std::ceil(value);
}

inline float clamp(const float value, const float min, const float max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

inline int clamp(const int value, const int min, const int max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

inline float sqrt(const float value)
{
    return std::sqrt(value);
}

inline float pow(const float base, const float power)
{
    return std::pow(base, power);
}

inline float sqrd(const float value)
{
    return value * value;
}

inline int sqrd(const int value)
{
    return value * value;
}

inline float floor(const float value)
{
    return std::floor(value);
}

inline float lerp(const float from, const float to, const float weight)
{
    return from + weight * (to - from);
}

inline float lerp_clamped(const float from, const float to, const float weight)
{
    if (weight >= 1.0f) {
        return to;
    }
    if (weight <= 0.0f) {
        return from;
    }
    return lerp(from, to, weight);
}

inline float sin(const float value)
{
    return std::sin(value);
}

inline float cos(const float value)
{
    return std::cos(value);
}

inline float tan(const float value)
{
    return std::tan(value);
}

inline float round(const float value)
{
    return std::round(value);
}

inline float atan(const float value)
{
    return std::atan(value);
}

inline float atan2(const float a, const float b)
{
    return std::atan2(a, b);
}

inline float radians(const float degrees)
{
    return pi / 180.0f * degrees;
}

inline float degrees(const float radians)
{
    return 180.0f / pi * radians;
}

inline float asin(const float value)
{
    return std::asin(value);
}

inline float acos(const float value)
{
    return std::acos(value);
}

inline float min(const float a, const float b)
{
    return std::min(a, b);
}

inline int min(const int a, const int b)
{
    return std::min(a, b);
}

inline float log2(const float value)
{
    return std::log2(value);
}

class Vector2;
class Vector2i;
class Vector3;
class Vector3i;
class Vector4;
class Vector4i;
class Quaternion;
class Matrix2;
class Basis2;
class Matrix3;
class Transform2;
class Basis3;
class Matrix4;
class Transform3;

class Vector2 {
public:
    union {
        struct {
            float x;
            float y;
        };
        float data[2] {};
    };

    Vector2()
        : x(0.0f)
        , y(0.0f)
    {
    }

    explicit Vector2(const Vector2i& vector);

    Vector2(const float x, const float y)
        : x(x)
        , y(y)
    {
    }

    static Vector2 all(const float value)
    {
        return { value, value };
    }

    static Vector2 zero()
    {
        return { 0.0f, 0.0f };
    }

    static Vector2 one()
    {
        return { 1.0f, 1.0f };
    }

    static Vector2 axis_x()
    {
        return { 1.0f, 0.0f };
    }

    static Vector2 axis_y()
    {
        return { 0.0f, 1.0f };
    }

    [[nodiscard]] Vector2 abs() const
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

    [[nodiscard]] float aspect_ratio() const
    {
        return x / y;
    }

    [[nodiscard]] Vector2 clamp(const Vector2& min, const Vector2& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] Vector2 direction(const Vector2& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] float distance_sqrd(const Vector2& to) const
    {
        const float diff_x = to.x - x;
        const float diff_y = to.y - y;
        return sqrd(diff_x) + sqrd(diff_y);
    }

    [[nodiscard]] float distance(const Vector2& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    [[nodiscard]] float manhattan_distance(const Vector2& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector2 clamp_length(const float min, const float max) const
    {
        const float length = this->length();
        if (length == 0.0f) {
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
        if (const float length = this->length(); length > 0.0f) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] Vector2 lerp(const Vector2& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight) };
    }

    [[nodiscard]] Vector2 lerp_clamped(const Vector2& to, const float weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight), nnm::lerp_clamped(y, to.y, weight) };
    }

    [[nodiscard]] float dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] float cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    [[nodiscard]] Matrix2 outer(const Vector2& other) const;

    [[nodiscard]] Vector2 reflect(const Vector2& normal) const
    {
        const float dot = this->dot(normal);
        Vector2 result;
        result.x = x - 2.0f * normal.x * dot;
        result.y = y - 2.0f * normal.y * dot;
        return result;
    }

    [[nodiscard]] Vector2 project(const Vector2& onto) const
    {
        const float onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == 0.0f) {
            return zero();
        }
        const float scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    [[nodiscard]] Vector2 inverse() const
    {
        return { 1.0f / x, 1.0f / y };
    }

    [[nodiscard]] float angle(const Vector2& to) const
    {
        const float lengths = length() * to.length();
        if (lengths == 0) {
            return 0.0f;
        }
        const float cos_angle = nnm::clamp(dot(to) / lengths, -1.0f, 1.0f);
        return acos(cos_angle);
    }

    [[nodiscard]] Vector2 translate(const Vector2& by) const;

    [[nodiscard]] Vector2 rotate(float angle) const;

    [[nodiscard]] Vector2 scale(const Vector2& factor) const;

    [[nodiscard]] Vector2 shear_x(float angle_y) const;

    [[nodiscard]] Vector2 shear_y(float angle_x) const;

    [[nodiscard]] Vector2 transform(const Basis2& by) const;

    [[nodiscard]] Vector2 transform(const Transform2& by, float z = 1.0f) const;

    [[nodiscard]] int max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] int min_index() const
    {
        if (x < y) {
            return 0;
        }
        if (y < x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] bool approx_equal(const Vector2& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y);
    }

    [[nodiscard]] bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y);
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 2;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 2;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] const float& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] bool operator!=(const Vector2& other) const
    {
        return x != other.x || y != other.y;
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

    [[nodiscard]] Vector2 operator*(const Matrix2& matrix) const;

    [[nodiscard]] Vector2 operator*(const float value) const
    {
        return { x * value, y * value };
    }

    Vector2& operator*=(const float value)
    {
        x *= value;
        y *= value;
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

    [[nodiscard]] Vector2 operator/(const float value) const
    {
        return { x / value, y / value };
    }

    Vector2& operator/=(const float value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    [[nodiscard]] Vector2 operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector2 operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] bool operator<(const Vector2& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0.0 || y != 0.0;
    }
};

inline Vector2 operator*(const float value, const Vector2& vector)
{
    return { value * vector.x, value * vector.y };
}

inline Vector2 operator/(const float value, const Vector2& vector)
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

    Vector2i()
        : x(0)
        , y(0)
    {
    }

    explicit Vector2i(const Vector2& vector)
        : x(static_cast<int>(vector.x))
        , y(static_cast<int>(vector.y))
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

    static Vector2i axis_x()
    {
        return { 1, 0 };
    }

    static Vector2i axis_y()
    {
        return { 0, 1 };
    }

    [[nodiscard]] Vector2i abs() const
    {
        return { nnm::abs(x), nnm::abs(y) };
    }

    [[nodiscard]] Vector2i clamp(const Vector2i& min, const Vector2i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] int manhattan_distance(const Vector2i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y);
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] int max_index() const
    {
        if (x > y) {
            return 0;
        }
        if (y > x) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] int min_index() const
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

    [[nodiscard]] bool operator==(const Vector2i& other) const
    {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] bool operator!=(const Vector2i& other) const
    {
        return x != other.x || y != other.y;
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

    [[nodiscard]] Vector2i operator+() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector2i operator-() const
    {
        return { -x, -y };
    }

    [[nodiscard]] bool operator<(const Vector2i& other) const
    {
        if (x < other.x) {
            return true;
        }
        if (x > other.x) {
            return false;
        }
        return y < other.y;
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0 || y != 0;
    }
};

inline Vector2i operator*(const int value, const Vector2i& vector)
{
    return { value * vector.x, value * vector.y };
}

inline Vector2i operator/(const int value, const Vector2i& vector)
{
    return { value / vector.x, value / vector.y };
}

inline Vector2i operator%(const int value, const Vector2i& vector)
{
    return { value % vector.x, value % vector.y };
}

class Vector3 {
public:
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float data[3] {};
    };

    Vector3()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

    explicit Vector3(const Vector3i& vector);

    Vector3(const Vector2& vector, const float z)
        : x(vector.x)
        , y(vector.y)
        , z(z)
    {
    }

    Vector3(const float x, const float y, const float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static Vector3 all(float value)
    {
        return { value, value, value };
    }

    static Vector3 zero()
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    static Vector3 one()
    {
        return { 1.0f, 1.0f, 1.0f };
    }

    static Vector3 axis_x()
    {
        return { 1.0f, 0.0f, 0.0f };
    }

    static Vector3 axis_y()
    {
        return { 0.0f, 1.0f, 0.0f };
    }

    static Vector3 axis_z()
    {
        return { 0.0f, 0.0f, 1.0f };
    }

    [[nodiscard]] Vector3 abs() const
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

    [[nodiscard]] Vector3 clamp(const Vector3& min, const Vector3& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] Vector3 direction(const Vector3& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] float distance_sqrd(const Vector3& to) const
    {
        const float diff_x = to.x - x;
        const float diff_y = to.y - y;
        const float diff_z = to.z - z;
        return sqrd(diff_x) + sqrd(diff_y) + sqrd(diff_z);
    }

    [[nodiscard]] float distance(const Vector3& to) const
    {
        return sqrt(this->distance_sqrd(to));
    }

    [[nodiscard]] float manhattan_distance(const Vector3& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector3 clamp_length(const float min, const float max) const
    {
        const float length = this->length();
        if (length == 0.0f) {
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
        if (const auto length = this->length(); length > 0.0f) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] Vector3 lerp(const Vector3& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    [[nodiscard]] Vector3 lerp_clamped(const Vector3& to, const float weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight) };
    }

    [[nodiscard]] float dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] Vector3 cross(const Vector3& other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    [[nodiscard]] Matrix3 outer(const Vector3& other) const;

    [[nodiscard]] Vector3 reflect(const Vector3& normal) const
    {
        Vector3 result;
        const float dot = this->dot(normal);
        result.x = x - 2.0f * normal.x * dot;
        result.y = y - 2.0f * normal.y * dot;
        result.z = z - 2.0f * normal.z * dot;
        return result;
    }

    [[nodiscard]] Vector3 project(const Vector3& onto) const
    {
        const float onto_length_sqrd = onto.length_sqrd();
        if (onto_length_sqrd == 0.0f) {
            return zero();
        }
        const float scale = dot(onto) / onto_length_sqrd;
        return onto * scale;
    }

    [[nodiscard]] Vector3 inverse() const
    {
        return { 1.0f / x, 1.0f / y, 1.0f / z };
    }

    [[nodiscard]] float angle(const Vector3& to) const
    {
        return atan2(this->cross(to).length(), this->dot(to));
    }

    [[nodiscard]] Vector3 translate(const Vector3& by) const;

    [[nodiscard]] Vector3 rotate_axis_angle(const Vector3& axis, float angle) const;

    [[nodiscard]] Vector3 rotate_quaternion(const Quaternion& quaternion) const;

    [[nodiscard]] Vector3 scale(const Vector3& factor) const;

    [[nodiscard]] Vector3 shear_x(float angle_y, float angle_z) const;

    [[nodiscard]] Vector3 shear_y(float angle_x, float angle_z) const;

    [[nodiscard]] Vector3 shear_z(float angle_x, float angle_y) const;

    [[nodiscard]] Vector3 transform(const Basis3& by) const;

    [[nodiscard]] Vector3 transform(const Transform2& by) const;

    [[nodiscard]] Vector3 transform(const Transform3& by, float w = 1.0f) const;

    [[nodiscard]] int max_index() const
    {
        float max_val = x;
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

    [[nodiscard]] int min_index() const
    {
        float min_val = x;
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

    [[nodiscard]] bool approx_equal(const Vector3& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z);
    }

    [[nodiscard]] bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z);
    }

    [[nodiscard]] Vector2 xy() const
    {
        return { x, y };
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 3;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 3;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] const float& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] bool operator!=(const Vector3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    [[nodiscard]] Vector3 operator+(const Vector3& other) const
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

    [[nodiscard]] Vector3 operator*(const Vector3& other) const
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

    [[nodiscard]] Vector3 operator*(const Matrix3& matrix) const;

    [[nodiscard]] Vector3 operator*(const float value) const
    {
        return { x * value, y * value, z * value };
    }

    Vector3& operator*=(const float value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    [[nodiscard]] Vector3 operator/(const Vector3& other) const
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

    [[nodiscard]] Vector3 operator/(const float value) const
    {
        return { x / value, y / value, z / value };
    }

    Vector3& operator/=(const float value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    [[nodiscard]] Vector3 operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] Vector3 operator-() const
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

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0.0f || y != 0.0f || z != 0.0f;
    }
};

inline Vector3 operator*(const float value, const Vector3& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

inline Vector3 operator/(const float value, const Vector3& vector)
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

    Vector3i()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    explicit Vector3i(const Vector3& vector)
        : x(static_cast<int>(vector.x))
        , y(static_cast<int>(vector.y))
        , z(static_cast<int>(vector.z))
    {
    }

    Vector3i(const Vector2i& vector, const int z)
        : x(vector.x)
        , y(vector.y)
        , z(z)
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

    static Vector3i axis_x()
    {
        return { 1, 0, 0 };
    }

    static Vector3i axis_y()
    {
        return { 0, 1, 0 };
    }

    static Vector3i axis_z()
    {
        return { 0, 0, 1 };
    }

    [[nodiscard]] Vector3i abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] Vector3i clamp(const Vector3i& min, const Vector3i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] int manhattan_distance(const Vector3i& to) const
    {
        return nnm::abs(x - to.x) + nnm::abs(y - to.y) + nnm::abs(z - to.z);
    }

    [[nodiscard]] int length_sqrd() const
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

    [[nodiscard]] Vector2i xy() const
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

    [[nodiscard]] bool operator==(const Vector3i& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    [[nodiscard]] bool operator!=(const Vector3i& other) const
    {
        return x != other.x || y != other.y || z != other.z;
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

    [[nodiscard]] Vector3i operator-(const Vector3i& other) const
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

    [[nodiscard]] Vector3i operator*(const Vector3i& other) const
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

    [[nodiscard]] Vector3i operator*(const int value) const
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

    [[nodiscard]] Vector3i operator/(const Vector3i& other) const
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

    [[nodiscard]] Vector3i operator/(const int value) const
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

    [[nodiscard]] Vector3i operator%(const Vector3i& other) const
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

    [[nodiscard]] Vector3i operator%(const int value) const
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

    [[nodiscard]] Vector3i operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] Vector3i operator-() const
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

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0 || y != 0 || z != 0;
    }
};

inline Vector3i operator*(const int value, const Vector3i& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

inline Vector3i operator/(const int value, const Vector3i& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
}

inline Vector3i operator%(const int value, const Vector3i& vector)
{
    return { value % vector.x, value % vector.y, value % vector.z };
}

class Vector4 {
public:
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4] {};
    };

    Vector4()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(0.0f)
    {
    }

    explicit Vector4(const Vector4i& vector);

    Vector4(const Vector2& vector, const float z, const float w)
        : x(vector.x)
        , y(vector.y)
        , z(z)
        , w(w)
    {
    }

    Vector4(const Vector3& vector, const float w)
        : x(vector.x)
        , y(vector.y)
        , z(vector.z)
        , w(w)
    {
    }

    Vector4(const float x, const float y, const float z, const float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    static Vector4 all(const float value)
    {
        return { value, value, value, value };
    }

    static Vector4 zero()
    {
        return { 0.0, 0.0, 0.0, 0.0 };
    }

    static Vector4 one()
    {
        return { 1.0, 1.0, 1.0, 1.0 };
    }

    static Vector4 axis_x()
    {
        return { 1.0f, 0.0f, 0.0f, 0.0f };
    }

    static Vector4 axis_y()
    {
        return { 0.0f, 1.0f, 0.0f, 0.0f };
    }

    static Vector4 axis_z()
    {
        return { 0.0f, 0.0f, 1.0f, 0.0f };
    }

    static Vector4 axis_w()
    {
        return { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    [[nodiscard]] Vector4 abs() const
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

    [[nodiscard]] Vector4 clamp(const Vector4& min, const Vector4& max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector4 clamp_length(const float min, const float max) const
    {
        const float length = this->length();
        if (length == 0.0f) {
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
        if (const float length = this->length(); length > 0.0f) {
            return *this / length;
        }
        return zero();
    }

    [[nodiscard]] Vector4 lerp(const Vector4& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    [[nodiscard]] Vector4 lerp_clamped(const Vector4& to, const float weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight),
                 nnm::lerp_clamped(y, to.y, weight),
                 nnm::lerp_clamped(z, to.z, weight),
                 nnm::lerp_clamped(w, to.w, weight) };
    }

    [[nodiscard]] float dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] Matrix4 outer(const Vector4& other) const;

    [[nodiscard]] Vector4 inverse() const
    {
        return { 1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w };
    }

    [[nodiscard]] Vector4 transform(const Transform3& by) const;

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

    [[nodiscard]] bool approx_equal(const Vector4& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y) && nnm::approx_equal(z, other.z)
            && nnm::approx_equal(w, other.w);
    }

    [[nodiscard]] bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y) && nnm::approx_zero(z) && nnm::approx_zero(w);
    }

    [[nodiscard]] Vector2 xy() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector3 xyz() const
    {
        return { x, y, z };
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 4;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 4;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] const float& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] bool operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    [[nodiscard]] Vector4 operator+(const Vector4& other) const
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

    [[nodiscard]] Vector4 operator-(const Vector4& other) const
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

    [[nodiscard]] Vector4 operator*(const Vector4& other) const
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

    [[nodiscard]] Vector4 operator*(const Matrix4& matrix) const;

    [[nodiscard]] Vector4 operator*(const float value) const
    {
        return { x * value, y * value, z * value, w * value };
    }

    Vector4& operator*=(const float value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    [[nodiscard]] Vector4 operator/(const Vector4& other) const
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

    [[nodiscard]] Vector4 operator/(const float value) const
    {
        return { x / value, y / value, z / value, w / value };
    }

    Vector4& operator/=(const float value)
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

    [[nodiscard]] Vector4 operator+() const
    {
        return { x, y, z, w };
    }

    [[nodiscard]] Vector4 operator-() const
    {
        return { -x, -y, -z, -w };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0.0f || y != 0.0f || z != 0.0f || w != 0.0f;
    }
};

inline Vector4 operator*(const float value, const Vector4& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z, value * vector.w };
}

inline Vector4 operator/(const float value, const Vector4& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z, value / vector.w };
}

class Quaternion {
public:
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        Vector4 vector;
        float data[4] {};
    };

    Quaternion()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(1.0f)
    {
    }

    explicit Quaternion(const Vector4& vector)
        : x(vector.x)
        , y(vector.y)
        , z(vector.z)
        , w(vector.w)
    {
    }

    Quaternion(const float x, const float y, const float z, const float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    [[nodiscard]] static Quaternion identity()
    {
        return { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    [[nodiscard]] static Quaternion from_axis_angle(const Vector3& axis, const float angle)
    {
        const Vector3 norm = axis.normalize();
        const float half_sin = sin(angle / 2.0f);
        Quaternion result;
        result.x = norm.x * half_sin;
        result.y = norm.y * half_sin;
        result.z = norm.z * half_sin;
        result.w = cos(angle / 2.0f);
        return result;
    }

    [[nodiscard]] static Quaternion from_vector_to_vector(const Vector3& from, const Vector3& to)
    {
        const Vector3 from_norm = from.normalize();
        const Vector3 to_norm = to.normalize();
        const Vector3 axis = from_norm.cross(to_norm);
        const float angle = acos(from_norm.dot(to_norm));
        return from_axis_angle(axis, angle);
    }

    [[nodiscard]] Quaternion normalize() const
    {
        return Quaternion(vector.normalize());
    }

    [[nodiscard]] Vector3 axis(const Quaternion& to) const
    {
        const Vector3 cross = vector.xyz().cross(to.vector.xyz());
        return cross.normalize();
    }

    [[nodiscard]] float angle(const Quaternion& to) const
    {
        return 2 * acos(vector.dot(to.vector));
    }

    [[nodiscard]] Vector3 axis() const
    {
        const float sin_half_angle = sqrt(1 - sqrd(w));
        if (sin_half_angle == 0.0f) {
            return vector.xyz();
        }
        return vector.xyz() / sin_half_angle;
    }

    [[nodiscard]] float angle() const
    {
        return 2 * acos(w);
    }

    [[nodiscard]] Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] float length_sqrd() const
    {
        return vector.length_sqrd();
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Quaternion slerp(const Quaternion& to, const float weight) const
    {
        const float dot = clamp(vector.dot(to.vector), -1.0f, 1.0f);
        const float angle = acos(dot);
        const float sin_angle = sin(angle);
        if (sin_angle == 0.0f) {
            return Quaternion(vector.lerp(to.vector, weight));
        }
        return Quaternion((vector * sin((1.0f - weight) * angle) + to.vector * sin(weight * angle)) / sin_angle);
    }

    [[nodiscard]] Quaternion rotate_axis_angle(const Vector3& axis, const float angle) const
    {
        return from_axis_angle(axis, angle) * *this;
    }

    [[nodiscard]] Quaternion rotate_quaternion(const Quaternion& by) const
    {
        return by * *this;
    }

    [[nodiscard]] bool is_equal_approx(const Quaternion& other) const
    {
        return vector.approx_equal(other.vector);
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    [[nodiscard]] const float& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }

    [[nodiscard]] float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK_ASSERT("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }

    [[nodiscard]] bool operator==(const Quaternion& other) const
    {
        return vector == other.vector;
    }

    [[nodiscard]] bool operator!=(const Quaternion& other) const
    {
        return vector != other.vector;
    }

    [[nodiscard]] Quaternion operator*(const Quaternion& other) const
    {
        Vector4 vector;
        vector.x = w * other.x + x * other.w + y * other.z - z * other.y;
        vector.y = w * other.y - x * other.z + y * other.w + z * other.x;
        vector.z = w * other.z + x * other.y - y * other.x + z * other.w;
        vector.w = w * other.w - x * other.x - y * other.y - z * other.z;
        return Quaternion(vector);
    }

    [[nodiscard]] Quaternion operator*(const float value) const
    {
        return Quaternion(vector * value);
    }

    Quaternion& operator*=(const float value)
    {
        vector *= value;
        return *this;
    }

    Quaternion& operator*=(const Quaternion& other)
    {
        const Quaternion result = *this * other;
        *this = result;
        return *this;
    }

    [[nodiscard]] Quaternion operator/(const float value) const
    {
        return Quaternion(vector / value);
    }

    Quaternion& operator/=(const float value)
    {
        vector /= value;
        return *this;
    }

    [[nodiscard]] bool operator<(const Quaternion& other) const
    {
        return vector < other.vector;
    }
};

inline Quaternion operator*(const float value, const Quaternion& quaternion)
{
    return Quaternion(value * quaternion.vector);
}

inline Quaternion operator/(const float value, const Quaternion& quaternion)
{
    return Quaternion(value / quaternion.vector);
}

class Matrix2 {
public:
    union {
        struct {
            float col0_row0;
            float col0_row1;
            float col1_row0;
            float col1_row1;
        };
        Vector2 columns[2];
        float data[4] {};
    };

    Matrix2()
        : col0_row0(1.0f)
        , col0_row1(0.0f)
        , col1_row0(0.0f)
        , col1_row1(1.0f)
    {
    }

    Matrix2(const Vector2& column0, const Vector2& column1)
        : col0_row0(column0.at(0))
        , col0_row1(column0.at(1))
        , col1_row0(column1.at(0))
        , col1_row1(column1.at(1))
    {
    }

    Matrix2(const float col0_row0, const float col0_row1, const float col1_row0, const float col1_row1)
        : col0_row0(col0_row0)
        , col0_row1(col0_row1)
        , col1_row0(col1_row0)
        , col1_row1(col1_row1)
    {
    }

    [[nodiscard]] static Matrix2 all(const float value)
    {
        return { { value, value }, { value, value } };
    }

    [[nodiscard]] static Matrix2 zero()
    {
        return all(0.0f);
    }

    [[nodiscard]] static Matrix2 one()
    {
        return all(1.0f);
    }

    [[nodiscard]] static Matrix2 identity()
    {
        return { { 1.0f, 0.0f }, { 0.0f, 1.0f } };
    }

    [[nodiscard]] float trace() const
    {
        return at(0, 0) + at(1, 1);
    }

    [[nodiscard]] float determinant() const
    {
        return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
    }

    [[nodiscard]] float minor_at(const int column, const int row) const
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

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor_at(column, row);
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
        const float det = determinant();
        if (det == 0.0f) {
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

    [[nodiscard]] Vector2 at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 4;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 4;
    }

    const Vector2& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2& operator[](const int column)
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
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator*(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                const float sum1 = at(0, r) * other.at(c, 0);
                const float sum2 = at(1, r) * other.at(c, 1);
                result.at(c, r) = sum1 + sum2;
            }
        }
        return result;
    }

    Matrix2& operator*=(const Matrix2& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector2 operator*(const Vector2& vector) const
    {
        Vector2 result;
        for (int r = 0; r < 2; ++r) {
            result.at(r) = at(0, r) * vector.at(0) + at(1, r) * vector.at(1);
        }
        return result;
    }

    [[nodiscard]] Matrix2 operator*(const float value) const
    {
        return { at(0) * value, at(1) * value };
    }

    Matrix2& operator*=(const float value)
    {
        at(0) *= value;
        at(1) *= value;
        return *this;
    }

    [[nodiscard]] Matrix2 operator/(const float value) const
    {
        return { at(0) / value, at(1) / value };
    }

    Matrix2& operator/=(const float value)
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

inline Matrix2 operator*(const float value, const Matrix2& matrix)
{
    Matrix2 result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

inline Matrix2 operator/(const float value, const Matrix2& matrix)
{
    Matrix2 result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

class Basis2 {
public:
    Matrix2 matrix;

    Basis2()
        : matrix(Matrix2::identity())
    {
    }

    explicit Basis2(const Matrix2& matrix)
        : matrix(matrix)
    {
    }

    static Basis2 from_rotation(const float angle)
    {
        return Basis2({ { cos(angle), sin(angle) }, { -sin(angle), cos(angle) } });
    }

    static Basis2 from_scale(const Vector2& factor)
    {
        return Basis2({ { factor.x, 0.0f }, { 0.0f, factor.y } });
    }

    static Basis2 from_shear_x(const float angle_y)
    {
        return Basis2({ { 1.0f, 0.0f }, { tan(angle_y), 1.0f } });
    }

    static Basis2 from_shear_y(const float angle_x)
    {
        return Basis2({ { 1.0f, tan(angle_x) }, { 0.0f, 1.0f } });
    }

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
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
        return matrix.determinant() != 0.0f;
    }

    [[nodiscard]] Basis2 rotate(const float angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Basis2 rotate_local(const float angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Basis2 scale(const Vector2& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis2 scale_local(const Vector2& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis2 shear_x(const float angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_x_local(const float angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Basis2 shear_y(const float angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Basis2 shear_y_local(const float angle_x) const
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

    [[nodiscard]] const Vector2& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    Vector2& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    const Vector2& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis2", index >= 0 && index <= 1);
        return matrix[index];
    }

    Vector2& operator[](const int index)
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

class Matrix3 {
public:
    union {
        struct {
            float col0_row0;
            float col0_row1;
            float col0_row2;
            float col1_row0;
            float col1_row1;
            float col1_row2;
            float col2_row0;
            float col2_row1;
            float col2_row2;
        };
        Vector3 columns[3];
        float data[9] {};
    };

    Matrix3()
        : col0_row0(1.0f)
        , col0_row1(0.0f)
        , col0_row2(0.0f)
        , col1_row0(0.0f)
        , col1_row1(1.0f)
        , col1_row2(0.0f)
        , col2_row0(0.0f)
        , col2_row1(0.0f)
        , col2_row2(1.0f)
    {
    }

    Matrix3(const Vector3& column0, const Vector3& column1, const Vector3& column2)
        : col0_row0(column0.at(0))
        , col0_row1(column0.at(1))
        , col0_row2(column0.at(2))
        , col1_row0(column1.at(0))
        , col1_row1(column1.at(1))
        , col1_row2(column1.at(2))
        , col2_row0(column2.at(0))
        , col2_row1(column2.at(1))
        , col2_row2(column2.at(2))
    {
    }

    Matrix3(
        const float col0_row0,
        const float col0_row1,
        const float col0_row2,
        const float col1_row0,
        const float col1_row1,
        const float col1_row2,
        const float col2_row0,
        const float col2_row1,
        const float col2_row2)
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

    [[nodiscard]] static Matrix3 all(const float value)
    {
        return { { value, value, value }, { value, value, value }, { value, value, value } };
    }

    [[nodiscard]] static Matrix3 zero()
    {
        return all(0.0f);
    }

    [[nodiscard]] static Matrix3 one()
    {
        return all(1.0f);
    }

    [[nodiscard]] static Matrix3 identity()
    {
        return { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };
    }

    [[nodiscard]] float trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2);
    }

    [[nodiscard]] float determinant() const
    {
        float det = 0.0f;
        for (int c = 0; c < 3; ++c) {
            const float det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? 1.0f : -1.0f) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix2 minor_matrix_at(const int column, const int row) const
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

    [[nodiscard]] float minor_at(const int column, const int row) const
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

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor_at(column, row);
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
        const float det = determinant();
        if (det == 0.0f) {
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

    [[nodiscard]] const Vector3& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 9;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 9;
    }

    const Vector3& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3& operator[](const int column)
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
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                const float sum1 = at(0, r) * other.at(c, 0);
                const float sum2 = at(1, r) * other.at(c, 1);
                const float sum3 = at(2, r) * other.at(c, 2);
                result.at(c, r) = sum1 + sum2 + sum3;
            }
        }
        return result;
    }

    Matrix3& operator*=(const Matrix3& other)
    {
        *this = *this * other;
        return *this;
    }

    [[nodiscard]] Vector3 operator*(const Vector3& vector) const
    {
        auto result = Vector3::zero();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 operator*(const float value) const
    {
        return { at(0) * value, at(1) * value, at(2) * value };
    }

    Matrix3& operator*=(const float value)
    {
        at(0) *= value;
        at(1) *= value;
        at(2) *= value;
        return *this;
    }

    [[nodiscard]] Matrix3 operator/(const float value) const
    {
        return { at(0) / value, at(1) / value, at(2) / value };
    }

    Matrix3& operator/=(const float value)
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

inline Matrix3 operator*(const float value, const Matrix3& matrix)
{
    Matrix3 result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

inline Matrix3 operator/(const float value, const Matrix3& matrix)
{
    Matrix3 result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

class Transform2 {
public:
    Matrix3 matrix;

    Transform2()
        : matrix(Matrix3::identity())
    {
    }

    explicit Transform2(const Matrix3& matrix)
        : matrix(matrix)
    {
    }

    static Transform2 from_basis_translation(const Basis2& basis, const Vector2& translation)
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

    static Transform2 from_basis(const Basis2& basis)
    {
        return from_basis_translation(basis, Vector2::zero());
    }

    static Transform2 from_translation(const Vector2& pos)
    {
        return from_basis_translation(Basis2(), pos);
    }

    static Transform2 from_rotation(const float angle)
    {
        return from_basis_translation(Basis2::from_rotation(angle), Vector2());
    }

    static Transform2 from_scale(const Vector2& factor)
    {
        return from_basis_translation(Basis2::from_scale(factor), Vector2());
    }

    static Transform2 from_shear_x(const float angle_y)
    {
        return from_basis_translation(Basis2::from_shear_x(angle_y), Vector2());
    }

    static Transform2 from_shear_y(const float angle_x)
    {
        return from_basis_translation(Basis2::from_shear_y(angle_x), Vector2());
    }

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
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
        return valid() && matrix.at(0, 2) == 0.0f && matrix.at(1, 2) == 0.0f && matrix.at(2, 2) == 1.0f;
    }

    [[nodiscard]] Basis2 basis() const
    {
        return Basis2(matrix.minor_matrix_at(2, 2));
    }

    [[nodiscard]] Vector2 translation() const
    {
        return { matrix.at(2, 0), matrix.at(2, 1) };
    }

    [[nodiscard]] Transform2 translate(const Vector2& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform2 translate_local(const Vector2& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform2 rotate(const float angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Transform2 rotate_local(const float angle) const
    {
        return transform_local(from_rotation(angle));
    }

    [[nodiscard]] Transform2 scale(const Vector2& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform2 scale_local(const Vector2& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform2 shear_x(const float angle_y) const
    {
        return transform(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_x_local(const float angle_y) const
    {
        return transform_local(from_shear_x(angle_y));
    }

    [[nodiscard]] Transform2 shear_y(const float angle_x) const
    {
        return transform(from_shear_y(angle_x));
    }

    [[nodiscard]] Transform2 shear_y_local(const float angle_x) const
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

    [[nodiscard]] const Vector3& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    Vector3& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform2", column >= 0 && column <= 2);
        return matrix[column];
    }

    Vector3& operator[](const int column)
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

class Basis3 {
public:
    Matrix3 matrix;

    Basis3()
        : matrix(Matrix3::identity())
    {
    }

    explicit Basis3(const Matrix3& matrix)
        : matrix(matrix)
    {
    }

    static Basis3 from_rotation_axis_angle(const Vector3& axis, const float angle)
    {
        const Vector3 norm = axis.normalize();
        // Rodrigues' formula
        const Matrix3 k_matrix { { 0.0f, norm.z, -norm.y }, { -norm.z, 0.0f, norm.x }, { norm.y, -norm.x, 0.0f } };
        const Matrix3 r_matrix = Matrix3::identity() + sin(angle) * k_matrix + (1 - cos(angle)) * k_matrix * k_matrix;
        return Basis3(r_matrix);
    }

    static Basis3 from_rotation_quaternion(const Quaternion& quaternion)
    {
        const Quaternion& q = quaternion;
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

    static Basis3 from_scale(const Vector3& factor)
    {
        return Basis3({ { factor.x, 0.0f, 0.0f }, { 0.0f, factor.y, 0.0f }, { 0.0f, 0.0f, factor.z } });
    }

    static Basis3 from_shear_x(const float angle_y, const float angle_z)
    {
        return Basis3({ { 1.0f, 0.0f, 0.0f }, { tan(angle_y), 1.0f, 0.0f }, { tan(angle_z), 0.0f, 1.0f } });
    }

    static Basis3 from_shear_y(const float angle_x, const float angle_z)
    {
        return Basis3({ { 1.0f, tan(angle_x), 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, tan(angle_z), 1.0f } });
    }

    static Basis3 from_shear_z(const float angle_x, const float angle_y)
    {
        return Basis3({ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { tan(angle_x), tan(angle_y), 1.0f } });
    }

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
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
        return matrix.determinant() != 0.0f;
    }

    [[nodiscard]] Basis3 rotate_axis_angle(const Vector3& axis, const float angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_axis_angle_local(const Vector3& axis, const float angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Basis3 rotate_quaternion(const Quaternion& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 rotate_quaternion_local(const Quaternion& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Basis3 scale(const Vector3& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis3 scale_local(const Vector3& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis3 shear_x(const float angle_y, const float angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_x_local(const float angle_y, const float angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Basis3 shear_y(const float angle_x, const float angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_y_local(const float angle_x, const float angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Basis3 shear_z(const float angle_x, const float angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Basis3 shear_z_local(const float angle_x, const float angle_y) const
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

    [[nodiscard]] const Vector3& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector3& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Basis3", index >= 0 && index <= 3);
        return matrix[index];
    }

    Vector3& operator[](const int index)
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

class Matrix4 {
public:
    union {
        struct {
            float col0_row0;
            float col0_row1;
            float col0_row2;
            float col0_row3;
            float col1_row0;
            float col1_row1;
            float col1_row2;
            float col1_row3;
            float col2_row0;
            float col2_row1;
            float col2_row2;
            float col2_row3;
            float col3_row0;
            float col3_row1;
            float col3_row2;
            float col3_row3;
        };
        Vector4 columns[4];
        float data[16] {};
    };

    Matrix4()
        : col0_row0(1.0f)
        , col0_row1(0.0f)
        , col0_row2(0.0f)
        , col0_row3(0.0f)
        , col1_row0(0.0f)
        , col1_row1(1.0f)
        , col1_row2(0.0f)
        , col1_row3(0.0f)
        , col2_row0(0.0f)
        , col2_row1(0.0f)
        , col2_row2(1.0f)
        , col2_row3(0.0f)
        , col3_row0(0.0f)
        , col3_row1(0.0f)
        , col3_row2(0.0f)
        , col3_row3(1.0f)
    {
    }

    Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3)
        : col0_row0(column0.at(0))
        , col0_row1(column0.at(1))
        , col0_row2(column0.at(2))
        , col0_row3(column0.at(3))
        , col1_row0(column1.at(0))
        , col1_row1(column1.at(1))
        , col1_row2(column1.at(2))
        , col1_row3(column1.at(3))
        , col2_row0(column2.at(0))
        , col2_row1(column2.at(1))
        , col2_row2(column2.at(2))
        , col2_row3(column2.at(3))
        , col3_row0(column3.at(0))
        , col3_row1(column3.at(1))
        , col3_row2(column3.at(2))
        , col3_row3(column3.at(3))
    {
    }

    Matrix4(
        const float col0_row0,
        const float col0_row1,
        const float col0_row2,
        const float col0_row3,
        const float col1_row0,
        const float col1_row1,
        const float col1_row2,
        const float col1_row3,
        const float col2_row0,
        const float col2_row1,
        const float col2_row2,
        const float col2_row3,
        const float col3_row0,
        const float col3_row1,
        const float col3_row2,
        const float col3_row3)
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

    [[nodiscard]] static Matrix4 all(const float value)
    {
        return { { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value },
                 { value, value, value, value } };
    }

    [[nodiscard]] static Matrix4 zero()
    {
        return all(0.0f);
    }

    [[nodiscard]] static Matrix4 one()
    {
        return all(1.0f);
    }

    [[nodiscard]] static Matrix4 identity()
    {
        return { { 1.0f, 0.0f, 0.0f, 0.0f },
                 { 0.0f, 1.0f, 0.0f, 0.0f },
                 { 0.0f, 0.0f, 1.0f, 0.0f },
                 { 0.0f, 0.0f, 0.0f, 1.0f } };
    }

    [[nodiscard]] float trace() const
    {
        return at(0, 0) + at(1, 1) + at(2, 2) + at(3, 3);
    }

    [[nodiscard]] float determinant() const
    {
        float det = 0.0f;
        for (int c = 0; c < 4; ++c) {
            const float det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? 1.0f : -1.0f) * at(c, 0) * det_minor;
        }
        return det;
    }

    [[nodiscard]] Matrix3 minor_matrix_at(const int column, const int row) const
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

    [[nodiscard]] float minor_at(const int column, const int row) const
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

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor_at(column, row);
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
        const float det = determinant();
        if (det == 0.0f) {
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

    [[nodiscard]] const Vector4& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    Vector4& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    [[nodiscard]] const float* begin() const
    {
        return data;
    }

    [[nodiscard]] const float* end() const
    {
        return data + 16;
    }

    float* begin()
    {
        return data;
    }

    float* end()
    {
        return data + 16;
    }

    const Vector4& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    Vector4& operator[](const int index)
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
        for (int c = 0; c < 3; ++c) {
            result.at(c) = at(c) + other.at(c);
        }
        return result;
    }

    Matrix4& operator+=(const Matrix4& other)
    {
        for (int c = 0; c < 3; ++c) {
            at(c) += other.at(c);
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator-(const Matrix4& other) const
    {
        Matrix4 result;
        for (int c = 0; c < 3; ++c) {
            result.at(c) = at(c) - other.at(c);
        }
        return result;
    }

    Matrix4& operator-=(const Matrix4& other)
    {
        for (int c = 0; c < 3; ++c) {
            at(c) -= other.at(c);
        }
        return *this;
    }

    Matrix4 operator*(const Matrix4& other) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                const float sum1 = at(0, r) * other.at(c, 0);
                const float sum2 = at(1, r) * other.at(c, 1);
                const float sum3 = at(2, r) * other.at(c, 2);
                const float sum4 = at(3, r) * other.at(c, 3);
                result.at(c, r) = sum1 + sum2 + sum3 + sum4;
            }
        }
        return result;
    }

    Matrix4& operator*=(const Matrix4& other)
    {
        *this = *this * other;
        return *this;
    }

    Vector4 operator*(const Vector4& vector) const
    {
        auto result = Vector4::zero();
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                result.at(r) += at(c, r) * vector.at(c);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix4 operator*(const float value) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) * value;
        }
        return result;
    }

    Matrix4& operator*=(const float value)
    {
        for (int c = 0; c < 4; ++c) {
            at(c) *= value;
        }
        return *this;
    }

    [[nodiscard]] Matrix4 operator/(const float value) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            result.at(c) = at(c) / value;
        }
        return result;
    }

    Matrix4& operator/=(const float value)
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

inline Matrix4 operator*(const float value, const Matrix4& matrix)
{
    Matrix4 result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = value * matrix.at(c, r);
        }
    }
    return result;
}

inline Matrix4 operator/(const float value, const Matrix4& matrix)
{
    Matrix4 result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = value / matrix.at(c, r);
        }
    }
    return result;
}

class Transform3 {
public:
    Matrix4 matrix;

    Transform3()
        : matrix(Matrix4::identity())
    {
    }

    explicit Transform3(const Matrix4& matrix)
        : matrix(matrix)
    {
    }

    static Transform3 from_basis_translation(const Basis3& basis, const Vector3& translation)
    {
        auto matrix = Matrix4::identity();
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

    static Transform3 from_basis(const Basis3& basis)
    {
        return from_basis_translation(basis, Vector3::zero());
    }

    static Transform3 from_translation(const Vector3& translation)
    {
        return from_basis_translation(Basis3(), translation);
    }

    static Transform3 from_rotation_axis_angle(const Vector3& axis, const float angle)
    {
        const auto basis = Basis3::from_rotation_axis_angle(axis, angle);
        return from_basis_translation(basis, Vector3::zero());
    }

    static Transform3 from_rotation_quaternion(const Quaternion& quaternion)
    {
        const auto basis = Basis3::from_rotation_quaternion(quaternion);
        return from_basis_translation(basis, Vector3::zero());
    }

    static Transform3 from_scale(const Vector3& factor)
    {
        return from_basis(Basis3::from_scale(factor));
    }

    static Transform3 from_shear_x(const float angle_y, const float angle_z)
    {
        return from_basis(Basis3::from_shear_x(angle_y, angle_z));
    }

    static Transform3 from_shear_y(const float angle_x, const float angle_z)
    {
        return from_basis(Basis3::from_shear_y(angle_x, angle_z));
    }

    static Transform3 from_shear_z(const float angle_x, const float angle_y)
    {
        return from_basis(Basis3::from_shear_z(angle_x, angle_y));
    }

    static Transform3 from_projection_perspective(
        const float fov, const float aspect_ratio, const float near, const float far)
    {
        Matrix4 matrix;
        const float tan_half_fov = tan(fov / 2.0f);
        matrix.at(0, 0) = 1.0f / (aspect_ratio * tan_half_fov);
        matrix.at(1, 1) = 1.0f / tan_half_fov;
        matrix.at(2, 2) = (far + near) / (near - far);
        matrix.at(2, 3) = -1.0f;
        matrix.at(3, 2) = 2.0f * far * near / (near - far);
        matrix.at(3, 3) = 0.0f;
        return Transform3(matrix);
    }

    static Transform3 from_projection_orthographic(
        const float left, const float right, const float bottom, const float top, const float near, const float far)
    {
        auto matrix = Matrix4::identity();
        matrix.at(0, 0) = 2.0f / (right - left);
        matrix.at(1, 1) = 2.0f / (top - bottom);
        matrix.at(2, 2) = -2.0f / (far - near);
        matrix.at(3, 0) = -((right + left) / (right - left));
        matrix.at(3, 1) = -((top + bottom) / (top - bottom));
        matrix.at(3, 2) = -((far + near) / (far - near));
        return Transform3(matrix);
    }

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
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
        return valid() && matrix.at(0, 3) == 0.0f && matrix.at(1, 3) == 0.0f && matrix.at(2, 3) == 0.0f
            && matrix.at(3, 3) == 1.0f;
    }

    [[nodiscard]] Basis3 basis() const
    {
        return Basis3(matrix.minor_matrix_at(3, 3));
    }

    [[nodiscard]] Vector3 translation() const
    {
        return { matrix.at(3, 0), matrix.at(3, 1), matrix.at(3, 2) };
    }

    [[nodiscard]] Transform3 translate(const Vector3& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform3 translate_local(const Vector3& offset) const
    {
        return transform_local(from_translation(offset));
    }

    [[nodiscard]] Transform3 rotate_axis_angle(const Vector3& axis, const float angle) const
    {
        return transform(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_axis_angle_local(const Vector3& axis, const float angle) const
    {
        return transform_local(from_rotation_axis_angle(axis, angle));
    }

    [[nodiscard]] Transform3 rotate_quaternion(const Quaternion& quaternion) const
    {
        return transform(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 rotate_quaternion_local(const Quaternion& quaternion) const
    {
        return transform_local(from_rotation_quaternion(quaternion));
    }

    [[nodiscard]] Transform3 scale(const Vector3& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Transform3 scale_local(const Vector3& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Transform3 shear_x(const float angle_y, const float angle_z) const
    {
        return transform(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_x_local(const float angle_y, const float angle_z) const
    {
        return transform_local(from_shear_x(angle_y, angle_z));
    }

    [[nodiscard]] Transform3 shear_y(const float angle_x, const float angle_z) const
    {
        return transform(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_y_local(const float angle_x, const float angle_z) const
    {
        return transform_local(from_shear_y(angle_x, angle_z));
    }

    [[nodiscard]] Transform3 shear_z(const float angle_x, const float angle_y) const
    {
        return transform(from_shear_z(angle_x, angle_y));
    }

    [[nodiscard]] Transform3 shear_z_local(const float angle_x, const float angle_y) const
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

    [[nodiscard]] const Vector4& at(const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector4& at(const int column)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] const float& at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector4& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK_ASSERT("Transform3", column >= 0 && column <= 3);
        return matrix[column];
    }

    Vector4& operator[](const int column)
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

inline Vector2::Vector2(const Vector2i& vector)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
{
}

inline Matrix2 Vector2::outer(const Vector2& other) const
{
    Matrix2 result;
    for (int c = 0; c < 2; ++c) {
        for (int r = 0; r < 2; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

inline Vector2 Vector2::translate(const Vector2& by) const
{
    const auto transform = Transform2::from_translation(by);
    return this->transform(transform);
}

inline Vector2 Vector2::rotate(const float angle) const
{
    const auto transform = Transform2::from_rotation(angle);
    return this->transform(transform);
}

inline Vector2 Vector2::scale(const Vector2& factor) const
{
    const auto transform = Transform2::from_scale(factor);
    return this->transform(transform);
}

inline Vector2 Vector2::shear_x(const float angle_y) const
{
    const auto transform = Transform2::from_shear_x(angle_y);
    return this->transform(transform);
}

inline Vector2 Vector2::shear_y(const float angle_x) const
{
    const auto transform = Transform2::from_shear_y(angle_x);
    return this->transform(transform);
}

inline Vector2 Vector2::transform(const Basis2& by) const
{
    return by.matrix * *this;
}

inline Vector2 Vector2::transform(const Transform2& by, const float z) const
{
    return Vector3(*this, z).transform(by).xy();
}

inline Vector2 Vector2::operator*(const Matrix2& matrix) const
{
    Vector2 result;
    result.x = x * matrix.at(0, 0) + y * matrix.at(0, 1);
    result.y = x * matrix.at(1, 0) + y * matrix.at(1, 1);
    return result;
}

inline Vector3::Vector3(const Vector3i& vector)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
    , z(static_cast<float>(vector.z))
{
}

inline Matrix3 Vector3::outer(const Vector3& other) const
{
    Matrix3 result;
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

inline Vector3 Vector3::translate(const Vector3& by) const
{
    const auto transform = Transform3::from_translation(by);
    return this->transform(transform);
}

inline Vector3 Vector3::rotate_axis_angle(const Vector3& axis, const float angle) const
{
    const auto transform = Transform3::from_rotation_axis_angle(axis, angle);
    return this->transform(transform);
}

inline Vector3 Vector3::rotate_quaternion(const Quaternion& quaternion) const
{
    const auto transform = Transform3::from_rotation_quaternion(quaternion);
    return this->transform(transform);
}

inline Vector3 Vector3::scale(const Vector3& factor) const
{
    const auto transform = Transform3::from_scale(factor);
    return this->transform(transform);
}

inline Vector3 Vector3::shear_x(const float angle_y, const float angle_z) const
{
    const auto transform = Transform3::from_shear_x(angle_y, angle_z);
    return this->transform(transform);
}

inline Vector3 Vector3::shear_y(const float angle_x, const float angle_z) const
{
    const auto transform = Transform3::from_shear_y(angle_x, angle_z);
    return this->transform(transform);
}

inline Vector3 Vector3::shear_z(const float angle_x, const float angle_y) const
{
    const auto transform = Transform3::from_shear_z(angle_x, angle_y);
    return this->transform(transform);
}

inline Vector3 Vector3::transform(const Basis3& by) const
{
    return by.matrix * *this;
}

inline Vector3 Vector3::transform(const Transform2& by) const
{
    return by.matrix * *this;
}

inline Vector3 Vector3::transform(const Transform3& by, const float w) const
{
    return Vector4(*this, w).transform(by).xyz();
}

inline Vector3 Vector3::operator*(const Matrix3& matrix) const
{
    auto result = zero();
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 3; ++r) {
            result.at(c) += at(r) * matrix.at(c, r);
        }
    }
    return result;
}

inline Matrix4 Vector4::outer(const Vector4& other) const
{
    Matrix4 result;
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c, r) = at(c) * other.at(r);
        }
    }
    return result;
}

inline Vector4 Vector4::transform(const Transform3& by) const
{
    return by.matrix * *this;
}
inline Vector4 Vector4::operator*(const Matrix4& matrix) const
{
    auto result = zero();
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            result.at(c) += at(c) * matrix.at(c, r);
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
