#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <optional>

// ReSharper disable CppDFATimeOver

#if defined(NNM_BOUNDS_CHECK_THROW)
#include <stdexcept>
#define NNM_BOUNDS_CHECK(msg, expression) \
    if (!(expression))                    \
        throw std::out_of_range(msg);
#elif defined(NNM_BOUNDS_CHECK_PRINT)
#include <iostream>
#define NNM_BOUNDS_CHECK(msg, expression) \
    if (!(expression))                    \
        std::cerr << __FILE__ << ":" << __LINE__ << " Out of range: " << msg << std::endl;
#else
#define NNM_BOUNDS_CHECK(msg, expression)
#endif

namespace nnm {
constexpr float pi = 3.141592653589793238462643383279502f;
constexpr float epsilon = 0.00001f;

inline float sign(const float value)
{
    return std::copysign(1.0f, value);
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
    return std::clamp(value, min, max);
}

inline int clamp(const int value, const int min, const int max)
{
    return std::clamp(value, min, max);
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
class Quaternion;
class Basis2;
class Matrix3;
class Transform2;
class Basis3;
class Transform3;

inline Vector2 operator/(float value, const Vector2& vector);

class Vector2 {
public:
    union {
        struct {
            float x;
            float y;
        };
        std::array<float, 2> data;
    };

    Vector2() // NOLINT(*-pro-type-member-init)
        : x(0.0f)
        , y(0.0f)
    {
    }

    explicit Vector2(const Vector2i& vector);

    Vector2(const float x, const float y) // NOLINT(*-pro-type-member-init)
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

    [[nodiscard]] float aspect_ratio() const
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
        if (const float length = this->length(); length > 0.0f) {
            return *this / length;
        }
        return zero();
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

    [[nodiscard]] float angle(const Vector2& to) const
    {
        const float lengths = length() * to.length();
        if (lengths == 0) {
            return 0.0f;
        }
        const float cos_angle = nnm::clamp(dot(to) / lengths, -1.0f, 1.0f);
        return acos(cos_angle);
    }

    [[nodiscard]] Vector2 floor() const
    {
        return { nnm::floor(x), nnm::floor(y) };
    }

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector2 lerp(const Vector2& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight) };
    }

    [[nodiscard]] Vector2 lerp_clamped(const Vector2& to, const float weight) const
    {
        return { nnm::lerp_clamped(x, to.x, weight), nnm::lerp_clamped(y, to.y, weight) };
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

    [[nodiscard]] bool approx_equal(const Vector2& other) const
    {
        return nnm::approx_equal(x, other.x) && nnm::approx_equal(y, other.y);
    }

    [[nodiscard]] bool approx_zero() const
    {
        return nnm::approx_zero(x) && nnm::approx_zero(y);
    }

    [[nodiscard]] float dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] float cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

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
        return onto * (dot(onto) / onto.length_sqrd());
    }

    [[nodiscard]] Vector2 rotate(float angle) const;

    [[nodiscard]] Vector2 scale(const Vector2& factor) const;

    [[nodiscard]] Vector2 shear_x(float angle_y) const;

    [[nodiscard]] Vector2 shear_y(float angle_x) const;

    [[nodiscard]] Vector2 transform(const Basis2& by) const;

    [[nodiscard]] Vector2 transform(const Transform2& by, float z = 1.0f) const;

    [[nodiscard]] Vector2 inverse() const
    {
        return 1.0f / *this;
    }

    [[nodiscard]] Vector2 clamp_length(const float min, const float max) const
    {
        if (const float length_sqrd = this->length_sqrd(); length_sqrd > 0.0f) {
            const auto norm = normalize();
            if (const float length = sqrt(length_sqrd); length < min) {
                return norm * min;
            }
            else if (length > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] float operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector2", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] bool operator==(const Vector2& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] bool operator!=(const Vector2& other) const
    {
        return data != other.data;
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
        return data < other.data;
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
        std::array<int, 2> data;
    };

    Vector2i() // NOLINT(*-pro-type-member-init)
        : x(0)
        , y(0)
    {
    }

    Vector2i(const int x, const int y) // NOLINT(*-pro-type-member-init)
        : x(x)
        , y(y)
    {
    }

    static Vector2i axis_x()
    {
        return { 1, 0 };
    }

    static Vector2i axis_y()
    {
        return { 0, 1 };
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

    [[nodiscard]] float aspect_ratio() const
    {
        return static_cast<float>(x) / static_cast<float>(y);
    }

    [[nodiscard]] Vector2i clamp(const Vector2i& min, const Vector2i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y) };
    }

    [[nodiscard]] int magnitude_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(static_cast<float>(magnitude_sqrd()));
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

    [[nodiscard]] const int* ptr() const
    {
        return data.data();
    }

    int* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const int* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const int* end() const
    {
        return data.end();
    }

    int* begin()
    {
        return data.begin();
    }

    int* end()
    {
        return data.end();
    }

    [[nodiscard]] bool operator!=(const Vector2i& other) const
    {
        return data != other.data;
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
        return data < other.data;
    }

    [[nodiscard]] bool operator==(const Vector2i& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] int at(const int index) const
    {
        NNM_BOUNDS_CHECK("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    int& at(const int index)
    {
        NNM_BOUNDS_CHECK("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    [[nodiscard]] int operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Vector2i", index >= 0 && index <= 1);
        return data[index];
    }

    int& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector2i", index >= 0 && index <= 1);
        return data[index];
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

inline Vector2i operator%(const int value, const Vector2i& vector)
{
    return { value % vector.x, value % vector.y };
}

inline Vector2i operator*(const int value, const Vector2i& vector)
{
    return { value * vector.x, value * vector.y };
}

inline Vector2i operator/(const int value, const Vector2i& vector)
{
    return { value / vector.x, value / vector.y };
}

inline Vector3 operator/(float value, const Vector3& vector);

class Vector3 {
public:
    union {
        struct {
            float x;
            float y;
            float z;
        };
        std::array<float, 3> data;
    };

    Vector3() // NOLINT(*-pro-type-member-init)
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

    explicit Vector3(Vector3i vector);

    Vector3(const Vector2& vector, const float z) // NOLINT(*-pro-type-member-init)
        : x(vector.x)
        , y(vector.y)
        , z(z)
    {
    }

    Vector3(const float x, const float y, const float z) // NOLINT(*-pro-type-member-init)
        : x(x)
        , y(y)
        , z(z)
    {
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

    [[nodiscard]] Vector3 abs() const
    {
        return { nnm::abs(x), nnm::abs(y), nnm::abs(z) };
    }

    [[nodiscard]] Vector3 ceil() const
    {
        return { nnm::ceil(x), nnm::ceil(y), nnm::ceil(z) };
    }

    [[nodiscard]] Vector3 clamp(const Vector3& min, const Vector3& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] Vector3 normalize() const
    {
        Vector3 result;
        if (const auto mag = this->magnitude(); mag > 0.0f) {
            result = *this / mag;
        }
        return result;
    }

    [[nodiscard]] Vector3 direction_to(const Vector3& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] float distance_sqrd_to(const Vector3& to) const
    {
        const float diff_x = to.x - x;
        const float diff_y = to.y - y;
        const float diff_z = to.z - z;
        return sqrd(diff_x) + sqrd(diff_y) + sqrd(diff_z);
    }

    [[nodiscard]] float distance_to(const Vector3 to) const
    {
        return sqrt(this->distance_sqrd_to(to));
    }

    [[nodiscard]] Vector3 floor() const
    {
        return { nnm::floor(x), nnm::floor(y), nnm::floor(z) };
    }

    [[nodiscard]] float magnitude_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(magnitude_sqrd());
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

    [[nodiscard]] float dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] Matrix3 outer(const Vector3& other) const;

    [[nodiscard]] Vector3 cross(const Vector3& other) const
    {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    [[nodiscard]] Vector3 reflect(const Vector3& normal) const
    {
        Vector3 result;
        const float dot = x * normal.x + y * normal.y + z * normal.z;
        result.x = x - 2.0f * normal.x * dot;
        result.y = y - 2.0f * normal.y * dot;
        result.z = z - 2.0f * normal.z * dot;
        return result;
    }

    [[nodiscard]] Vector3 inverse() const
    {
        return 1.0f / *this;
    }

    [[nodiscard]] Vector3 clamp_magnitude(const float min, const float max) const
    {
        if (const float mag_sqrd = magnitude_sqrd(); mag_sqrd > 0.0f) {
            const auto norm = normalize();
            if (const float mag = sqrt(mag_sqrd); mag < min) {
                return norm * min;
            }
            else if (mag > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] Vector3 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z) };
    }

    [[nodiscard]] float angle(const Vector3& other) const
    {
        return atan2(this->cross(other).magnitude(), this->dot(other));
    }

    [[nodiscard]] Vector3 rotate_axis_angle(const Vector3& axis, float angle) const;

    [[nodiscard]] Vector3 rotate_quaternion(const Quaternion& quaternion) const;

    [[nodiscard]] Vector3 scale(const Vector3& factor) const;

    [[nodiscard]] Vector3 shear_x(float angle_y, float angle_z) const;

    [[nodiscard]] Vector3 shear_y(float angle_x, float angle_z) const;

    [[nodiscard]] Vector3 shear_z(float angle_x, float angle_y) const;

    [[nodiscard]] Vector3 transform(const Basis3& by) const;

    [[nodiscard]] Vector3 transform(const Transform2& by) const;

    [[nodiscard]] Vector3 transform(const Transform3& by, float w = 1.0f) const;

    [[nodiscard]] Vector2 xy() const
    {
        return { x, y };
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    [[nodiscard]] bool operator!=(const Vector3& other) const
    {
        return data != other.data;
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

    Vector3& operator/=(const float val)
    {
        x /= val;
        y /= val;
        z /= val;

        return *this;
    }

    [[nodiscard]] bool operator<(const Vector3& other) const
    {
        return data < other.data;
    }

    [[nodiscard]] bool operator==(const Vector3& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] float operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Vector3", index >= 0 && index <= 2);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector3", index >= 0 && index <= 2);
        return data[index];
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
        std::array<int, 3> data {};
    };

    Vector3i()
        : x(0)
        , y(0)
        , z(0)
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

    [[nodiscard]] Vector3i clamp(const Vector3i& min, const Vector3i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] int magnitude_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(static_cast<float>(magnitude_sqrd()));
    }

    [[nodiscard]] int min_index() const
    {
        int min_val = x;
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

    [[nodiscard]] int max_index() const
    {
        int max_val = x;
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

    [[nodiscard]] Vector2i xy() const
    {
        return { x, y };
    }

    [[nodiscard]] const int* ptr() const
    {
        return data.data();
    }

    int* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const int* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const int* end() const
    {
        return data.end();
    }

    int* begin()
    {
        return data.begin();
    }

    int* end()
    {
        return data.end();
    }

    [[nodiscard]] bool operator!=(const Vector3i& other) const
    {
        return data != other.data;
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

    [[nodiscard]] bool operator<(const Vector3i& other) const
    {
        return data < other.data;
    }

    [[nodiscard]] bool operator==(const Vector3i& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] int at(const int index) const
    {
        NNM_BOUNDS_CHECK("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    int& at(const int index)
    {
        NNM_BOUNDS_CHECK("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] int operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    int& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector3i", index >= 0 && index <= 2);
        return data[index];
    }

    [[nodiscard]] Vector3i operator+() const
    {
        return { x, y, z };
    }

    [[nodiscard]] Vector3i operator-() const
    {
        return { -x, -y, -z };
    }

    [[nodiscard]] explicit operator bool() const
    {
        return x != 0 || y != 0 || z != 0;
    }
};

inline Vector3i operator%(const int value, const Vector3i& vector)
{
    return { value % vector.x, value % vector.y, value % vector.z };
}

inline Vector3i operator*(const int value, const Vector3i& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

inline Vector3i operator/(const int value, const Vector3i& vector)
{
    return { value / vector.x, value / vector.y, value / vector.z };
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
        std::array<float, 4> data {};
    };

    Vector4()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(0.0f)
    {
    }

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

    [[nodiscard]] Vector4 clamp(const Vector4& min, const Vector4& max) const
    {
        return { nnm::clamp(x, min.x, max.x),
                 nnm::clamp(y, min.y, max.y),
                 nnm::clamp(z, min.z, max.z),
                 nnm::clamp(w, min.w, max.w) };
    }

    [[nodiscard]] Vector4 normalize() const
    {
        Vector4 result;
        if (const float mag = magnitude(); mag > 0.0f) {
            result = *this / mag;
        }
        return result;
    }

    [[nodiscard]] float magnitude_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(magnitude_sqrd());
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

    [[nodiscard]] int min_index() const
    {
        float min_val = x;
        auto min_axis = 0;
        if (y < min_val) {
            min_val = y;
            min_axis = 1;
        }
        if (z < min_val) {
            min_val = z;
            min_axis = 2;
        }
        if (w < min_val) {
            min_axis = 3;
        }
        return min_axis;
    }

    [[nodiscard]] int max_index() const
    {
        float max_val = x;
        auto max_axis = 0;
        if (y > max_val) {
            max_val = y;
            max_axis = 1;
        }
        if (z > max_val) {
            max_val = z;
            max_axis = 2;
        }
        if (w > max_val) {
            max_axis = 3;
        }
        return max_axis;
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

    [[nodiscard]] float dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] Vector4 inverse() const
    {
        return { 1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w };
    }

    [[nodiscard]] Vector4 clamp_magnitude(const float min, const float max) const
    {
        if (const float mag_sqrd = magnitude_sqrd(); mag_sqrd > 0.0f) {
            const auto norm = normalize();
            if (const float mag = sqrt(mag_sqrd); mag < min) {
                return norm * min;
            }
            else if (mag > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] Vector4 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z), nnm::round(w) };
    }

    [[nodiscard]] Vector4 transform(const Transform3& by) const;

    [[nodiscard]] Vector2 xy() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector3 xyz() const
    {
        return { x, y, z };
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    [[nodiscard]] bool operator!=(const Vector4& other) const
    {
        return data != other.data;
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
        return data < other.data;
    }

    [[nodiscard]] bool operator==(const Vector4& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] float operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector4", index >= 0 && index <= 3);
        return data[index];
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

class Vector4i {
public:
    union {
        struct {
            int x;
            int y;
            int z;
            int w;
        };
        std::array<int, 4> data {};
    };

    Vector4i()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    {
    }

    Vector4i(const Vector2i& vector, const int z, const int w)
        : x(vector.x)
        , y(vector.y)
        , z(z)
        , w(w)
    {
    }

    Vector4i(const Vector3i& vector, const int w)
        : x(vector.x)
        , y(vector.y)
        , z(vector.z)
        , w(w)
    {
    }

    Vector4i(const int x, const int y, const int z, const int w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    static Vector4i axis_x()
    {
        return { 1, 0, 0, 0 };
    }

    static Vector4i axis_y()
    {
        return { 0, 1, 0, 0 };
    }

    static Vector4i axis_z()
    {
        return { 0, 0, 1, 0 };
    }

    static Vector4i axis_w()
    {
        return { 0, 0, 0, 1 };
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

    [[nodiscard]] Vector4i clamped(const Vector4i& min, const Vector4i& max) const
    {
        return { clamp(x, min.x, max.x), clamp(y, min.y, max.y), clamp(z, min.z, max.z), clamp(w, min.w, max.w) };
    }

    [[nodiscard]] int magnitude_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(static_cast<float>(magnitude_sqrd()));
    }

    [[nodiscard]] int max_index() const
    {
        int max_val = x;
        auto max_axis = 0;
        if (y > max_val) {
            max_val = y;
            max_axis = 1;
        }
        if (z > max_val) {
            max_val = z;
            max_axis = 2;
        }
        if (w > max_val) {
            max_axis = 3;
        }
        return max_axis;
    }

    [[nodiscard]] int min_index() const
    {
        int min_val = x;
        auto min_axis = 0;
        if (y < min_val) {
            min_val = y;
            min_axis = 1;
        }
        if (z < min_val) {
            min_val = z;
            min_axis = 2;
        }
        if (w < min_val) {
            min_axis = 3;
        }
        return min_axis;
    }

    [[nodiscard]] Vector2i xy() const
    {
        return { x, y };
    }

    [[nodiscard]] Vector3i xyz() const
    {
        return { x, y, z };
    }

    [[nodiscard]] const int* ptr() const
    {
        return data.data();
    }

    int* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const int* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const int* end() const
    {
        return data.end();
    }

    int* begin()
    {
        return data.begin();
    }

    int* end()
    {
        return data.end();
    }

    [[nodiscard]] bool operator!=(const Vector4i& other) const
    {
        return data != other.data;
    }

    [[nodiscard]] Vector4i operator%(const Vector4i& other) const
    {
        return { x % other.x, y & other.y, z % other.z, w % other.w };
    }

    Vector4i& operator%=(const Vector4i& other)
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

    [[nodiscard]] Vector4i operator*(const Vector4i& other) const
    {
        return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4i& operator*=(const Vector4i& other)
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

    [[nodiscard]] Vector4i operator+(const Vector4i& other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4i& operator+=(const Vector4i& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator-(const Vector4i& other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4i& operator-=(const Vector4i& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    [[nodiscard]] Vector4i operator/(const Vector4i& other) const
    {
        return { x / other.x, y / other.y, z / other.z, w / other.w };
    }

    Vector4i& operator/=(const Vector4i& other)
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

    [[nodiscard]] bool operator<(const Vector4i& other) const
    {
        return data < other.data;
    }

    [[nodiscard]] bool operator==(const Vector4i& other) const
    {
        return data == other.data;
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

inline Vector4i operator%(const int value, const Vector4i& vector)
{
    return { value % vector.x, value % vector.y, value % vector.z, value % vector.w };
}

inline Vector4i operator*(const int value, const Vector4i& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z, value * vector.w };
}

inline Vector4i operator/(const int value, const Vector4i& vector)
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
        std::array<float, 4> data;
    };

    Quaternion() // NOLINT(*-pro-type-member-init)
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(1.0f)
    {
    }

    explicit Quaternion(const Vector4& vector) // NOLINT(*-pro-type-member-init)
        : vector(vector)
    {
    }

    Quaternion(const float x, const float y, const float z, const float w) // NOLINT(*-pro-type-member-init)
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

    [[nodiscard]] float angle(const Quaternion& to) const
    {
        return 2 * acos(vector.dot(to.vector));
    }

    [[nodiscard]] float angle() const
    {
        return 2 * acos(w);
    }

    [[nodiscard]] Vector3 axis() const
    {
        const float sin_half_angle = sqrt(1 - sqrd(w));
        if (sin_half_angle == 0.0f) {
            return vector.xyz();
        }
        return vector.xyz() / sin_half_angle;
    }

    [[nodiscard]] Quaternion conjugate() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] Quaternion inverse() const
    {
        return conjugate();
    }

    [[nodiscard]] float magnitude_sqrd() const
    {
        return vector.magnitude_sqrd();
    }

    [[nodiscard]] float magnitude() const
    {
        return sqrt(magnitude_sqrd());
    }

    [[nodiscard]] Quaternion slerp(const Quaternion& to, const float weight) const
    {
        const float dot = clamp(vector.dot(to.vector), -1.0f, 1.0f);
        const float theta = acos(dot);
        const float sin_theta = sin(theta);
        if (sin_theta == 0.0f) {
            return Quaternion(vector.lerp(to.vector, weight));
        }
        return Quaternion((vector * sin((1.0f - weight) * theta) + to.vector * sin(weight * theta)) / sin_theta);
    }

    [[nodiscard]] bool is_equal_approx(const Quaternion& other) const
    {
        return vector.approx_equal(other.vector);
    }

    [[nodiscard]] bool operator==(const Quaternion& other) const
    {
        return vector == other.vector;
    }

    [[nodiscard]] bool operator!=(const Quaternion& other) const
    {
        return vector != other.vector;
    }

    [[nodiscard]] float at(const int index) const
    {
        NNM_BOUNDS_CHECK("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    float& at(const int index)
    {
        NNM_BOUNDS_CHECK("Quaternion", index >= 0 && index <= 3);
        return vector.at(index);
    }

    [[nodiscard]] float operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }

    [[nodiscard]] float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Quaternion", index >= 0 && index <= 3);
        return vector[index];
    }
};

class Matrix2 {
public:
    union {
        struct {
            float col0_row0;
            float col0_row1;
            float col1_row0;
            float col1_row1;
        };
        std::array<Vector2, 2> columns;
        std::array<float, 4> data;
    };

    Matrix2() // NOLINT(*-pro-type-member-init)
        : col0_row0(1.0f)
        , col0_row1(0.0f)
        , col1_row0(0.0f)
        , col1_row1(1.0f)
    {
    }

    Matrix2(const Vector2& column0, const Vector2& column1) // NOLINT(*-pro-type-member-init)
        : col0_row0(column0[0])
        , col0_row1(column0[1])
        , col1_row0(column1[0])
        , col1_row1(column1[1])
    {
    }

    Matrix2( // NOLINT(*-pro-type-member-init)
        const float col0_row0,
        const float col0_row1,
        const float col1_row0,
        const float col1_row1)
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

    [[nodiscard]] float minor(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        const int other_column = (column + 1) % 2;
        const int other_row = (row + 1) % 2;
        return at(other_column, other_row);
    }

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor(column, row);
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

    [[nodiscard]] const Vector2& at(const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2& at(const int column)
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return columns[column][row];
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    const Vector2& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Vector2& operator[](const int column)
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    bool operator==(const Matrix2& other) const
    {
        return columns == other.columns;
    }

    bool operator!=(const Matrix2& other) const
    {
        return columns != other.columns;
    }

    bool operator<(const Matrix2& other) const
    {
        return columns < other.columns;
    }

    [[nodiscard]] Matrix2 operator+(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            result[c] = columns[c] + other[c];
        }
        return result;
    }

    Matrix2& operator+=(const Matrix2& other)
    {
        for (int c = 0; c < 2; ++c) {
            columns[c] += other[c];
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator-(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            result[c] = columns[c] - other[c];
        }
        return result;
    }

    Matrix2& operator-=(const Matrix2& other)
    {
        for (int c = 0; c < 2; ++c) {
            columns[c] += other[c];
        }
        return *this;
    }

    [[nodiscard]] Matrix2 operator*(const Matrix2& other) const
    {
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                result.at(c, r) = at(0, r) * other.at(c, 0) + at(1, r) * other.at(c, 1);
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
            result[r] = at(0, r) * vector[0] + at(1, r) * vector[1];
        }
        return result;
    }

    [[nodiscard]] Matrix2 operator*(const float value) const
    {
        return { columns[0] * value, columns[1] * value };
    }

    Matrix2& operator*=(const float value)
    {
        columns[0] *= value;
        columns[1] *= value;
        return *this;
    }

    [[nodiscard]] Matrix2 operator/(const float value) const
    {
        return { columns[0] / value, columns[1] / value };
    }

    Matrix2& operator/=(const float value)
    {
        columns[0] /= value;
        columns[1] /= value;
        return *this;
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

    static Basis2 from_shear_x(const float angle_y)
    {
        return Basis2({ { 1.0f, 0.0f }, { tan(angle_y), 1.0f } });
    }

    static Basis2 from_shear_y(const float angle_x)
    {
        return Basis2({ { 1.0f, tan(angle_x) }, { 0.0f, 1.0f } });
    }

    static Basis2 from_scale(const Vector2& factor)
    {
        return Basis2({ { factor.x, 0.0f }, { 0.0f, factor.y } });
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != 0.0;
    }

    [[nodiscard]] Basis2 rotate(const float angle) const
    {
        return transform(from_rotation(angle));
    }

    [[nodiscard]] Basis2 rotate_local(const float angle) const
    {
        return transform_local(from_rotation(angle));
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

    [[nodiscard]] Basis2 scale(const Vector2& factor) const
    {
        return transform(from_scale(factor));
    }

    [[nodiscard]] Basis2 scale_local(const Vector2& factor) const
    {
        return transform_local(from_scale(factor));
    }

    [[nodiscard]] Basis2 transform(const Basis2& by) const
    {
        return Basis2(by.matrix * matrix);
    }

    [[nodiscard]] Basis2 transform_local(const Basis2& by) const
    {
        return Basis2(matrix * by.matrix);
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

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
    {
        return matrix.determinant();
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
        NNM_BOUNDS_CHECK("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    Vector2& at(const int column)
    {
        NNM_BOUNDS_CHECK("Basis2", column >= 0 && column <= 1);
        return matrix[column];
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Basis2", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        return matrix[column][row];
    }

    const Vector2& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Basis2", index >= 0 && index <= 1);
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
        std::array<Vector3, 3> columns;
        std::array<float, 9> data;
    };

    Matrix3() // NOLINT(*-pro-type-member-init)
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

    Matrix3(const Vector3& column1, const Vector3& column2, const Vector3& column3) // NOLINT(*-pro-type-member-init)
        : col0_row0(column1[0])
        , col0_row1(column1[1])
        , col0_row2(column1[2])
        , col1_row0(column2[0])
        , col1_row1(column2[1])
        , col1_row2(column2[2])
        , col2_row0(column3[0])
        , col2_row1(column3[1])
        , col2_row2(column3[2])
    {
    }

    Matrix3( // NOLINT(*-pro-type-member-init)
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
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix3 minor() const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                result[c][r] = minor_at(c, r);
            }
        }
        return result;
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

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix3 cofactor() const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                result[c][r] = cofactor_at(c, r);
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
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3& at(const int column)
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2 && row >= 0 && row <= 2);
        return columns[column][row];
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    const Vector3& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Vector3& operator[](const int column)
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] bool operator==(const Matrix3& other) const
    {
        return columns == other.columns;
    }

    bool operator!=(const Matrix3& other) const
    {
        return columns != other.columns;
    }

    [[nodiscard]] bool operator<(const Matrix3& other) const
    {
        return columns < other.columns;
    }

    [[nodiscard]] Matrix3 operator+(const Matrix3& other) const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            result[c] = columns[c] + other[c];
        }
        return result;
    }

    Matrix3& operator+=(const Matrix3& other)
    {
        for (int c = 0; c < 3; ++c) {
            columns[c] += other[c];
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator-(const Matrix3& other) const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            result[c] = columns[c] - other[c];
        }
        return result;
    }

    Matrix3& operator-=(const Matrix3& other)
    {
        for (int c = 0; c < 3; ++c) {
            columns[c] -= other[c];
        }
        return *this;
    }

    [[nodiscard]] Matrix3 operator*(const Matrix3& other) const
    {
        Matrix3 result;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                result.at(c, r) = at(0, r) * other.at(c, 0) + at(1, r) * other.at(c, 1) + at(2, r) * other.at(c, 2);
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
        Vector3 result;
        for (int r = 0; r < 3; ++r) {
            result[r] = at(0, r) * vector[0] + at(1, r) * vector[1] + at(2, r) * vector[2];
        }
        return result;
    }

    [[nodiscard]] Matrix3 operator*(const float value) const
    {
        return { columns[0] * value, columns[1] * value, columns[2] * value };
    }

    Matrix3& operator*=(const float value)
    {
        columns[0] *= value;
        columns[1] *= value;
        columns[2] *= value;
        return *this;
    }

    [[nodiscard]] Matrix3 operator/(const float value) const
    {
        return { columns[0] / value, columns[1] / value, columns[2] / value };
    }

    Matrix3& operator/=(const float value)
    {
        columns[0] /= value;
        columns[1] /= value;
        columns[2] /= value;
        return *this;
    }

    explicit operator bool() const
    {
        for (int c = 0; c < 3; ++c) {
            if (!static_cast<bool>(columns[c])) {
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

    static Transform2 from_basis_translation(const Basis2& basis, const Vector2& pos)
    {
        Matrix3 matrix;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                matrix[c][r] = basis.matrix[c][r];
            }
        }
        matrix[2][0] = pos.x;
        matrix[2][1] = pos.y;
        return Transform2(matrix);
    }

    static Transform2 from_translation(const Vector2& pos)
    {
        return from_basis_translation(Basis2(), pos);
    }

    static Transform2 from_basis(const Basis2& basis)
    {
        return from_basis_translation(basis, Vector2::zero());
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

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix[0][2] == 0.0f && matrix[1][2] == 0.0f && matrix[2][2] == 1.0f;
    }

    [[nodiscard]] Basis2 basis() const
    {
        Matrix2 basis_matrix;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                basis_matrix[c][r] = matrix[c][r];
            }
        }
        return Basis2(basis_matrix);
    }

    [[nodiscard]] Vector2 translation() const
    {
        return { matrix[2][0], matrix[2][1] };
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

    [[nodiscard]] Transform2 translate(const Vector2& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform2 translate_local(const Vector2& offset) const
    {
        return transform_local(from_translation(offset));
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

    [[nodiscard]] float at(const int column, const int row) const
    {
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3& operator[](const int column) const
    {
        return matrix[column];
    }

    Vector3& operator[](const int column)
    {
        return matrix[column];
    }

    bool operator==(const Transform2& other) const
    {
        return matrix == other.matrix;
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
        std::array<Vector4, 4> columns;
        std::array<float, 16> data;
    };

    Matrix4() // NOLINT(*-pro-type-member-init)
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

    Matrix4( // NOLINT(*-pro-type-member-init)
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

    Matrix4( // NOLINT(*-pro-type-member-init)
        const Vector4& column1,
        const Vector4& column2,
        const Vector4& column3,
        const Vector4& column4)
        : col0_row0(column1[0])
        , col0_row1(column1[1])
        , col0_row2(column1[2])
        , col0_row3(column1[3])
        , col1_row0(column2[0])
        , col1_row1(column2[1])
        , col1_row2(column2[2])
        , col1_row3(column2[3])
        , col2_row0(column3[0])
        , col2_row1(column3[1])
        , col2_row2(column3[2])
        , col2_row3(column3[3])
        , col3_row0(column4[0])
        , col3_row1(column4[1])
        , col3_row2(column4[2])
        , col3_row3(column4[3])
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

    [[nodiscard]] Matrix3 minor_matrix_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
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
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return minor_matrix_at(column, row).determinant();
    }

    [[nodiscard]] Matrix4 minor() const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                result[c][r] = minor_at(c, r);
            }
        }
        return result;
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

    [[nodiscard]] float cofactor_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return pow(-1.0f, static_cast<float>(column + 1 + row + 1)) * minor_at(column, row);
    }

    [[nodiscard]] Matrix4 cofactor() const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                result[c][r] = cofactor_at(c, r);
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
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    Vector4& at(const int column)
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    [[nodiscard]] float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return columns[column][row];
    }

    [[nodiscard]] const float* ptr() const
    {
        return data.data();
    }

    float* ptr()
    {
        return data.data();
    }

    [[nodiscard]] const float* begin() const
    {
        return data.begin();
    }

    [[nodiscard]] const float* end() const
    {
        return data.end();
    }

    float* begin()
    {
        return data.begin();
    }

    float* end()
    {
        return data.end();
    }

    const Vector4& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    Vector4& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    [[nodiscard]] bool operator==(const Matrix4& other) const
    {
        return columns == other.columns;
    }

    bool operator!=(const Matrix4& other) const
    {
        return columns != other.columns;
    }

    bool operator<(const Matrix4& other) const
    {
        return columns < other.columns;
    }

    Matrix4 operator*(const Matrix4& other) const
    {
        Matrix4 result;
        for (int c = 0; c < 4; ++c) {
            for (int r = 0; r < 4; ++r) {
                result.at(c, r) = at(0, r) * other.at(c, 0) + at(1, r) * other.at(c, 1) + at(2, r) * other.at(c, 2)
                    + at(3, r) * other.at(c, 3);
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
        Vector4 result;
        for (int r = 0; r < 4; ++r) {
            result[r] = at(0, r) * vector[0] + at(1, r) * vector[1] + at(2, r) * vector[2] + at(3, r) * vector[3];
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

    explicit operator bool() const
    {
        for (int c = 0; c < 4; ++c) {
            if (!static_cast<bool>(at(c))) {
                return false;
            }
        }
        return true;
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

class Basis3 {
public:
    Matrix3 matrix;

    Basis3() = default;

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

    static Basis3 from_scale(const Vector3& factor)
    {
        return Basis3({ { factor.x, 0.0f, 0.0f }, { 0.0f, factor.y, 0.0f }, { 0.0f, 0.0f, factor.z } });
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

    [[nodiscard]] Basis3 unchecked_inverse() const
    {
        return Basis3(matrix.unchecked_inverse());
    }

    [[nodiscard]] std::optional<Basis3> inverse() const
    {
        if (valid()) {
            return Basis3(matrix.unchecked_inverse());
        }
        return std::nullopt;
    }

    [[nodiscard]] float trace() const
    {
        return matrix.trace();
    }

    [[nodiscard]] float determinant() const
    {
        return matrix.determinant();
    }

    [[nodiscard]] bool approx_equal(const Basis3& other) const
    {
        return matrix.approx_equal(other.matrix);
    }

    [[nodiscard]] const Vector3& at(const int column) const
    {
        NNM_BOUNDS_CHECK("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector3& at(const int column)
    {
        NNM_BOUNDS_CHECK("Basis3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Basis3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector3& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Basis3", index >= 0 && index <= 3);
        return matrix[index];
    }

    Vector3& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Basis3", index >= 0 && index <= 3);
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

class Transform3 {
public:
    Matrix4 matrix;

    Transform3() = default;

    explicit Transform3(const Matrix4& matrix)
        : matrix(matrix)
    {
    }

    static Transform3 from_basis_translation(const Basis3& basis, const Vector3& translation)
    {
        Matrix4 matrix;
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                matrix[c][r] = basis.matrix[c][r];
            }
        }
        matrix[3][0] = translation.x;
        matrix[3][1] = translation.y;
        matrix[3][2] = translation.z;
        return Transform3(matrix);
    }

    static Transform3 from_translation(const Vector3& translation)
    {
        return from_basis_translation(Basis3(), translation);
    }

    static Transform3 from_basis(const Basis3& basis)
    {
        return from_basis_translation(basis, Vector3::zero());
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

    [[nodiscard]] Basis3 basis() const
    {
        return Basis3(matrix.minor_matrix_at(3, 3));
    }

    [[nodiscard]] bool valid() const
    {
        return basis().valid();
    }

    [[nodiscard]] bool affine() const
    {
        return valid() && matrix[0][3] == 0.0f && matrix[1][3] == 0.0f && matrix[2][3] == 0.0f && matrix[3][3] == 1.0f;
    }

    [[nodiscard]] Vector3 translation() const
    {
        return { matrix[3][0], matrix[3][1], matrix[3][2] };
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

    [[nodiscard]] Transform3 translate(const Vector3& offset) const
    {
        return transform(from_translation(offset));
    }

    [[nodiscard]] Transform3 translate_local(const Vector3& offset) const
    {
        return transform_local(from_translation(offset));
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
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    Vector4& at(const int column)
    {
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3);
        return matrix.at(column);
    }

    [[nodiscard]] Vector4 row_at(const int row) const
    {
        NNM_BOUNDS_CHECK("Transform3", row >= 0 && row <= 3);
        return { at(0, row), at(1, row), at(2, row), at(3, row) };
    }

    [[nodiscard]] float at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    float& at(const int column, const int row)
    {
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3 && row >= 0 && row <= 3);
        return matrix.at(column, row);
    }

    [[nodiscard]] const Vector4& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3);
        return matrix[column];
    }

    Vector4& operator[](const int column)
    {
        NNM_BOUNDS_CHECK("Transform3", column >= 0 && column <= 3);
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

inline Vector3::Vector3(const Vector3i vector) // NOLINT(*-pro-type-member-init)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
    , z(static_cast<float>(vector.z))
{
}

inline Matrix3 Vector3::outer(const Vector3& other) const
{
    return { { x * other.x, x * other.y, x * other.z },
             { y * other.x, y * other.y, y * other.z },
             { z * other.x, z * other.y, z * other.z } };
}

inline Vector4 Vector4::transform(const Transform3& by) const
{
    return by.matrix * *this;
}

inline Vector2::Vector2(const Vector2i& vector) // NOLINT(*-pro-type-member-init)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
{
}

inline Vector2 Vector2::rotate(const float angle) const
{
    const auto basis = Basis2::from_rotation(angle);
    return transform(basis);
}

inline Vector2 Vector2::scale(const Vector2& factor) const
{
    const auto basis = Basis2::from_scale(factor);
    return transform(basis);
}

inline Vector2 Vector2::shear_x(const float angle_y) const
{
    const auto basis = Basis2::from_shear_x(angle_y);
    return transform(basis);
}

inline Vector2 Vector2::shear_y(const float angle_x) const
{
    const auto basis = Basis2::from_shear_y(angle_x);
    return transform(basis);
}

inline Vector2 Vector2::transform(const Basis2& by) const
{
    return by.matrix * *this;
}

inline Vector2 Vector2::transform(const Transform2& by, const float z) const
{
    return Vector3(*this, z).transform(by).xy();
}

inline Vector3 Vector3::rotate_axis_angle(const Vector3& axis, const float angle) const
{
    const auto basis = Basis3::from_rotation_axis_angle(axis, angle);
    return transform(basis);
}

inline Vector3 Vector3::rotate_quaternion(const Quaternion& quaternion) const
{
    const auto basis = Basis3::from_rotation_quaternion(quaternion);
    return transform(basis);
}

inline Vector3 Vector3::scale(const Vector3& factor) const
{
    const auto basis = Basis3::from_scale(factor);
    return transform(basis);
}

inline Vector3 Vector3::shear_x(const float angle_y, const float angle_z) const
{
    const auto basis = Basis3::from_shear_x(angle_y, angle_z);
    return transform(basis);
}

inline Vector3 Vector3::shear_y(const float angle_x, const float angle_z) const
{
    const auto basis = Basis3::from_shear_y(angle_x, angle_z);
    return transform(basis);
}

inline Vector3 Vector3::shear_z(const float angle_x, const float angle_y) const
{
    const auto basis = Basis3::from_shear_z(angle_x, angle_y);
    return transform(basis);
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
