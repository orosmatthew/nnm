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

inline float clamped_lerp(const float from, const float to, const float weight)
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
class Matrix2;
class Basis2;
class Matrix3;
class Matrix4;
class Vector4;
class Vector4i;
class Quaternion;

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
        Vector2 result;
        if (const float length = this->length(); length > 0.0f) {
            const float inverse_length = 1.0f / length;
            result = *this * inverse_length;
        }
        return result;
    }

    [[nodiscard]] Vector2 direction_to(const Vector2& to) const
    {
        return (to - *this).normalize();
    }

    [[nodiscard]] float distance_sqrd_to(const Vector2& to) const
    {
        const float diff_x = to.x - x;
        const float diff_y = to.y - y;
        return sqrd(diff_x) + sqrd(diff_y);
    }

    [[nodiscard]] float distance_to(const Vector2& to) const
    {
        return sqrt(this->distance_sqrd_to(to));
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

    [[nodiscard]] Vector2 clamped_lerp(const Vector2& to, const float weight) const
    {
        return { nnm::clamped_lerp(x, to.x, weight), nnm::clamped_lerp(y, to.y, weight) };
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

    [[nodiscard]] Vector2 rotate(const float angle) const
    {
        Vector2 result;
        result.x = x * cos(angle) - y * sin(angle);
        result.y = x * sin(angle) + y * cos(angle);
        return result;
    }

    [[nodiscard]] Vector2 inverse() const
    {
        return { 1.0f / x, 1.0f / y };
    }

    [[nodiscard]] Vector2 clamp_length(const float min, const float max) const
    {
        if (const float length_sqr = length_sqrd(); length_sqr > 0.0f) {
            const auto norm = normalize();
            if (const float length = sqrt(length_sqr); length < min) {
                return norm * min;
            }
            else if (length > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] Vector2 transform(const Basis2& by) const;

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

    [[nodiscard]] bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
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

    [[nodiscard]] float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector2", index >= 0 && index <= 1);
        return data[index];
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

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(static_cast<float>(length_sqrd()));
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

    [[nodiscard]] bool operator==(const Vector2i& other) const
    {
        return x == other.x && y == other.y;
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

    Vector3(const float x, const float y, const float z) // NOLINT(*-pro-type-member-init)
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
        if (const auto length = this->length(); length > 0.0f) {
            const float inverse_length = 1.0f / length;
            result = *this * inverse_length;
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

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector3 lerp(const Vector3& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight), nnm::lerp(y, to.y, weight), nnm::lerp(z, to.z, weight) };
    }

    [[nodiscard]] Vector3 clamped_lerp(const Vector3& to, const float weight) const
    {
        return { nnm::clamped_lerp(x, to.x, weight),
                 nnm::clamped_lerp(y, to.y, weight),
                 nnm::clamped_lerp(z, to.z, weight) };
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
        return { 1.0f / x, 1.0f / y, 1.0f / z };
    }

    [[nodiscard]] Vector3 clamp_length(const float min, const float max) const
    {
        if (const float length_sqr = length_sqrd(); length_sqr > 0.0f) {
            const auto norm = normalize();
            if (const float length = sqrt(length_sqr); length < min) {
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

    [[nodiscard]] float angle(const Vector3& other) const
    {
        return atan2(this->cross(other).length(), this->dot(other));
    }

    [[nodiscard]] Vector3 rotate(Vector3 axis, const float angle) const
    {
        axis = axis.normalize();
        // Rodrigues rotation formula
        return *this * cos(angle) + axis.cross(*this) * sin(angle) + axis * (1.0f - cos(angle)) * axis.dot(*this);
    }

    [[nodiscard]] bool operator!=(const Vector3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
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

    [[nodiscard]] Vector3 operator*(const float val) const
    {
        return { x * val, y * val, z * val };
    }

    Vector3& operator*=(const float val)
    {
        x *= val;
        y *= val;
        z *= val;
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

    [[nodiscard]] Vector3 operator/(const float val) const
    {
        return { x / val, y / val, z / val };
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

    [[nodiscard]] bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
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

    [[nodiscard]] Vector3i clamp(const Vector3i& min, const Vector3i& max) const
    {
        return { nnm::clamp(x, min.x, max.x), nnm::clamp(y, min.y, max.y), nnm::clamp(z, min.z, max.z) };
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(static_cast<float>(length_sqrd()));
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

    [[nodiscard]] bool operator!=(const Vector3i& other) const
    {
        return x != other.x || y != other.y || z != other.z;
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

    [[nodiscard]] bool operator==(const Vector3i& other) const
    {
        return x == other.x && y == other.y && z == other.z;
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
        if (const float len = length(); len > 0.0f) {
            const float inverse_length = 1.0f / len;
            result = *this * inverse_length;
        }
        return result;
    }

    [[nodiscard]] float length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(length_sqrd());
    }

    [[nodiscard]] Vector4 lerp(const Vector4& to, const float weight) const
    {
        return { nnm::lerp(x, to.x, weight),
                 nnm::lerp(y, to.y, weight),
                 nnm::lerp(z, to.z, weight),
                 nnm::lerp(w, to.w, weight) };
    }

    [[nodiscard]] Vector4 clamped_lerp(const Vector4& to, const float weight) const
    {
        return { nnm::clamped_lerp(x, to.x, weight),
                 nnm::clamped_lerp(y, to.y, weight),
                 nnm::clamped_lerp(z, to.z, weight),
                 nnm::clamped_lerp(w, to.w, weight) };
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

    [[nodiscard]] Vector4 clamp_length(const float min, const float max) const
    {
        if (const float length_sqr = length_sqrd(); length_sqr > 0.0f) {
            const auto norm = normalize();
            if (const float length = sqrt(length_sqr); length < min) {
                return norm * min;
            }
            else if (length > max) {
                return norm * max;
            }
        }
        return *this;
    }

    [[nodiscard]] Vector4 round() const
    {
        return { nnm::round(x), nnm::round(y), nnm::round(z), nnm::round(w) };
    }

    [[nodiscard]] bool operator!=(const Vector4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
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

    [[nodiscard]] bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    [[nodiscard]] float& operator[](const int index)
    {
        NNM_BOUNDS_CHECK("Vector4", index >= 0 && index <= 3);
        return data[index];
    }

    [[nodiscard]] const float& operator[](const int index) const
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

    [[nodiscard]] Vector4i clamped(const Vector4i& min, const Vector4i& max) const
    {
        return { clamp(x, min.x, max.x), clamp(y, min.y, max.y), clamp(z, min.z, max.z), clamp(w, min.w, max.w) };
    }

    [[nodiscard]] int length_sqrd() const
    {
        return sqrd(x) + sqrd(y) + sqrd(z) + sqrd(w);
    }

    [[nodiscard]] float length() const
    {
        return sqrt(static_cast<float>(length_sqrd()));
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

    [[nodiscard]] bool operator!=(const Vector4i& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
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

    [[nodiscard]] bool operator==(const Vector4i& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
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

class Quaternion {
public:
    union {
        Vector4 data;

        struct {
            float x;
            float y;
            float z;
            float w;
        };
    };

    Quaternion() // NOLINT(*-pro-type-member-init)
        : data(0.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    explicit Quaternion(const Vector4& vector) // NOLINT(*-pro-type-member-init)
        : data(vector)
    {
    }

    Quaternion(const float x, const float y, const float z, const float w) // NOLINT(*-pro-type-member-init)
        : data(x, y, z, w)
    {
    }

    [[nodiscard]] static Quaternion from_axis_angle(const Vector3& axis, const float angle)
    {
        Vector4 data;
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

    [[nodiscard]] static Quaternion from_euler(const Vector3& euler)
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

    [[nodiscard]] static Quaternion from_matrix(const Matrix3& matrix);

    [[nodiscard]] static Quaternion from_vector3_to_vector3(const Vector3& from, const Vector3& to)
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

    [[nodiscard]] static Quaternion from_direction(const Vector3& dir, const Vector3& up)
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

    // [[nodiscard]] Vector3 euler() const
    // {
    //     return matrix().euler();
    // }

    [[nodiscard]] Quaternion inverse() const
    {
        return { -x, -y, -z, w };
    }

    [[nodiscard]] bool is_equal_approx(const Quaternion& other) const
    {
        return approx_equal(x, other.x) && approx_equal(y, other.y) && approx_equal(z, other.z)
            && approx_equal(w, other.w);
    }

    [[nodiscard]] bool is_zero_approx() const
    {
        return approx_zero(x) && approx_zero(y) && approx_zero(z) && approx_zero(w);
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
        const Quaternion& to, const float weight, const float epsilon) const
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

    [[nodiscard]] Matrix3 matrix() const;

    [[nodiscard]] Quaternion normalize() const;

    [[nodiscard]] bool operator!=(const Quaternion& other) const
    {
        return data != other.data;
    }

    [[nodiscard]] Quaternion operator*(const Quaternion& other) const
    {
        return { w * other.x + x * other.w + y * other.z - z * other.y,
                 w * other.y + y * other.w + z * other.x - x * other.z,
                 w * other.z + z * other.w + x * other.y - y * other.x,
                 w * other.w - x * other.x - y * other.y - z * other.z };
    }

    void operator*=(const Quaternion& other)
    {
        const float new_x = w * other.x + x * other.w + y * other.z - z * other.y;
        const float new_y = w * other.y + y * other.w + z * other.x - x * other.z;
        const float new_z = w * other.z + z * other.w + x * other.y - y * other.x;
        w = w * other.w - x * other.x - y * other.y - z * other.z;
        x = new_x;
        y = new_y;
        z = new_z;
    }

    [[nodiscard]] Quaternion operator*(const float value) const
    {
        return Quaternion(data * value);
    }

    void operator*=(const float value)
    {
        data *= value;
    }

    [[nodiscard]] Quaternion operator+(const Quaternion& other) const
    {
        return Quaternion(data + other.data);
    }

    void operator+=(const Quaternion& other)
    {
        data += other.data;
    }

    [[nodiscard]] Quaternion operator-(const Quaternion& other) const
    {
        return Quaternion(data - other.data);
    }

    void operator-=(const Quaternion& other)
    {
        data -= other.data;
    }

    [[nodiscard]] Quaternion operator/(const float value) const
    {
        return Quaternion(data * (1.0f / value));
    }

    void operator/=(const float value)
    {
        data *= 1.0f / value;
    }

    [[nodiscard]] bool operator==(const Quaternion& other) const
    {
        return data == other.data;
    }

    [[nodiscard]] float& operator[](const int index)
    {
        return data[index];
    }

    [[nodiscard]] const float& operator[](const int index) const
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

class Matrix2 {
public:
    using Column = Vector2;

    union {
        struct {
            float c0r0;
            float c0r1;
            float c1r0;
            float c1r1;
        };

        std::array<Column, 2> columns;
    };

    Matrix2()
        : c0r0(1.0f)
        , c0r1(0.0f)
        , c1r0(0.0f)
        , c1r1(1.0f)
    {
    }

    Matrix2(const Column& column_0, const Column& column_1)
        : c0r0(column_0[0])
        , c0r1(column_0[1])
        , c1r0(column_1[0])
        , c1r1(column_1[1])
    {
    }

    Matrix2(const float c0r0, const float c0r1, const float c1r0, const float c1r1)
        : c0r0(c0r0)
        , c0r1(c0r1)
        , c1r0(c1r0)
        , c1r1(c1r1)
    {
    }

    [[nodiscard]] static Matrix2 all(float value)
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

    [[nodiscard]] Column at(const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Column& at(const int column)
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

    const Column& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    Column& operator[](const int column)
    {
        NNM_BOUNDS_CHECK("Matrix2", column >= 0 && column <= 1);
        return columns[column];
    }

    bool operator==(const Matrix2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) != other.at(c, r)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) != other.at(c, r)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool operator<(const Matrix2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) < other.at(c, r)) {
                    return true;
                }
                if (at(c, r) > other.at(c, r)) {
                    return false;
                }
            }
        }
        return false;
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

    static Basis2 from_shear(const Vector2& vector)
    {
        return Basis2({ { 1.0f, vector.x }, { vector.y, 1.0f } });
    }

    [[nodiscard]] bool valid() const
    {
        return matrix.determinant() != 0.0;
    }

    [[nodiscard]] Basis2 rotate(const float angle) const
    {
        return Basis2(matrix * from_rotation(angle).matrix);
    }

    [[nodiscard]] Basis2 rotate_local(const float angle) const
    {
        return Basis2(from_rotation(angle).matrix * matrix);
    }

    [[nodiscard]] Basis2 scale(const Vector2& factor) const
    {
        return Basis2(from_scale(factor).matrix * matrix);
    }

    [[nodiscard]] Basis2 scale_local(const Vector2& factor) const
    {
        return Basis2(matrix * from_scale(factor).matrix);
    }

    [[nodiscard]] Basis2 shear(const Vector2& vector) const
    {
        return Basis2(from_shear(vector).matrix * matrix);
    }

    [[nodiscard]] Basis2 shear_local(const Vector2& vector) const
    {
        return Basis2(matrix * from_shear(vector).matrix);
    }

    [[nodiscard]] Basis2 transform(const Basis2& by) const
    {
        return Basis2(matrix * by.matrix);
    }

    [[nodiscard]] Basis2 transform_local(const Basis2& by) const
    {
        return Basis2(by.matrix * matrix);
    }

    [[nodiscard]] bool approx_equal(const Basis2& other) const
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

    const Matrix2::Column& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Basis2", index >= 0 && index <= 1);
        return matrix[index];
    }

    bool operator==(const Basis2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) != other.at(c, r)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Basis2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) != other.at(c, r)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool operator<(const Basis2& other) const
    {
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                if (at(c, r) < other.at(c, r)) {
                    return true;
                }
                if (at(c, r) > other.at(c, r)) {
                    return false;
                }
            }
        }
        return false;
    }
};

class Matrix3 {
public:
    using Column = Vector3;

    union {
        struct {
            float c0r0;
            float c0r1;
            float c0r2;
            float c1r0;
            float c1r1;
            float c1r2;
            float c2r0;
            float c2r1;
            float c2r2;
        };

        std::array<Column, 3> columns;
    };

    Matrix3()
        : c0r0(1.0f)
        , c0r1(0.0f)
        , c0r2(0.0f)
        , c1r0(0.0f)
        , c1r1(1.0f)
        , c1r2(0.0f)
        , c2r0(0.0f)
        , c2r1(0.0f)
        , c2r2(1.0f)
    {
    }

    Matrix3(const Column& column_1, const Column& column_2, const Column& column_3)
        : c0r0(column_1[0])
        , c0r1(column_1[1])
        , c0r2(column_1[2])
        , c1r0(column_2[0])
        , c1r1(column_2[1])
        , c1r2(column_2[2])
        , c2r0(column_3[0])
        , c2r1(column_3[1])
        , c2r2(column_3[2])
    {
    }

    Matrix3(
        const float c0r0,
        const float c0r1,
        const float c0r2,
        const float c1r0,
        const float c1r1,
        const float c1r2,
        const float c2r0,
        const float c2r1,
        const float c2r2)
        : c0r0(c0r0)
        , c0r1(c0r1)
        , c0r2(c0r2)
        , c1r0(c1r0)
        , c1r1(c1r1)
        , c1r2(c1r2)
        , c2r0(c2r0)
        , c2r1(c2r1)
        , c2r2(c2r2)
    {
    }

    // TODO: move
    // [[nodiscard]] static Matrix3 from_axis_angle(const Vector3<Number>& axis, const float angle)
    // {
    //     Matrix3 result;
    //
    //     const Vector3 axis_norm = axis.normalize();
    //
    //     const float sin_angle = sin(angle);
    //     const float cos_angle = cos(angle);
    //     const float t = 1.0f - cos_angle;
    //
    //     result[0][0] = axis_norm.x * axis_norm.x * t + cos_angle;
    //     result[0][1] = axis_norm.y * axis_norm.x * t + axis_norm.z * sin_angle;
    //     result[0][2] = axis_norm.z * axis_norm.x * t - axis_norm.y * sin_angle;
    //
    //     result[1][0] = axis_norm.x * axis_norm.y * t - axis_norm.z * sin_angle;
    //     result[1][1] = axis_norm.y * axis_norm.y * t + cos_angle;
    //     result[1][2] = axis_norm.z * axis_norm.y * t + axis_norm.x * sin_angle;
    //
    //     result[2][0] = axis_norm.x * axis_norm.z * t + axis_norm.y * sin_angle;
    //     result[2][1] = axis_norm.y * axis_norm.z * t - axis_norm.x * sin_angle;
    //     result[2][2] = axis_norm.z * axis_norm.z * t + cos_angle;
    //
    //     return result;
    // }

    // TODO: move
    // [[nodiscard]] static Matrix3 from_euler(const Vector3<Number>& euler)
    // {
    //     float c = nnm::cos(euler.x);
    //     float s = nnm::sin(euler.x);
    //     const Matrix3 x { 1.0f, 0.0f, 0.0f, 0.0f, c, -s, 0.0f, s, c };
    //
    //     c = nnm::cos(euler.y);
    //     s = nnm::sin(euler.y);
    //     const Matrix3 y { c, 0.0f, s, 0.0f, 1.0f, 0.0f, -s, 0.0f, c };
    //
    //     c = nnm::cos(euler.z);
    //     s = nnm::sin(euler.z);
    //     const Matrix3 z { c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f };
    //
    //     return x * (y * z);
    // }

    [[nodiscard]] static Matrix3 all(float value)
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
        const float det_bottom_right = at(1, 1) * at(2, 2) - at(2, 1) * at(1, 2);
        const float det_bottom_split = at(0, 1) * at(2, 2) - at(2, 1) * at(0, 2);
        const float det_bottom_left = at(0, 1) * at(1, 2) - at(1, 1) * at(0, 2);
        return at(0, 0) * det_bottom_right - at(1, 0) * det_bottom_split + at(2, 0) * det_bottom_left;
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

    [[nodiscard]] Column at(const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Column& at(const int column)
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

    const Column& operator[](const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    Column& operator[](const int column)
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 2);
        return columns[column];
    }

    [[nodiscard]] Matrix2 sub_matrix2_at(const int column, const int row) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        Matrix2 result;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                result[c][r] = at(column + c, row + r);
            }
        }
        return result;
    }

    [[nodiscard]] Matrix3 sub_matrix2(const int column, const int row, const Matrix2& matrix) const
    {
        NNM_BOUNDS_CHECK("Matrix3", column >= 0 && column <= 1 && row >= 0 && row <= 1);
        Matrix3 result = *this;
        for (int c = 0; c < 2; ++c) {
            for (int r = 0; r < 2; ++r) {
                result[column + c][row + r] = matrix.at(c, r);
            }
        }
        return result;
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
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < 3; ++r) {
                if (at(c, r) < other.at(c, r)) {
                    return true;
                }
                if (at(c, r) > other.at(c, r)) {
                    return false;
                }
            }
        }
        return false;
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
            for (int r = 0; r < 3; ++r) {
                if (at(c, r) != 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

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
        matrix = matrix.sub_matrix2(0, 0, basis.matrix);
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

    static Transform2 from_shear(const Vector2& vector)
    {
        return from_basis_translation(Basis2::from_shear(vector), Vector2());
    }

    [[nodiscard]] bool valid() const
    {
        const bool basis_valid = matrix.sub_matrix2_at(0, 0).determinant() != 0.0;
        const bool last_row_valid = matrix.at(0, 2) == 0.0f && matrix.at(1, 2) == 0.0f && matrix.at(2, 2) == 1.0f;
        return basis_valid && last_row_valid;
    }

    [[nodiscard]] Basis2 basis() const
    {
        return Basis2(matrix.sub_matrix2_at(0, 0));
    }

    [[nodiscard]] Vector2 translation() const
    {
        return { matrix[2][0], matrix[2][1] };
    }

    [[nodiscard]] Transform2 rotate(const float angle) const
    {
        const Transform2 by = from_basis(Basis2::from_rotation(angle));
        return Transform2(by.matrix * matrix);
    }

    [[nodiscard]] Transform2 rotate_local(const float angle) const
    {
        const Transform2 by = from_basis(Basis2::from_rotation(angle));
        return Transform2(matrix * by.matrix);
    }

    [[nodiscard]] Transform2 scale(const Vector2& factor) const
    {
        const Transform2 by = from_basis(Basis2::from_scale(factor));
        return Transform2(by.matrix * matrix);
    }

    [[nodiscard]] Transform2 scale_local(const Vector2& factor) const
    {
        const Transform2 by = from_basis(Basis2::from_scale(factor));
        return Transform2(matrix * by.matrix);
    }

    [[nodiscard]] Transform2 shear(const Vector2& vector) const
    {
        const Transform2 by = from_basis(Basis2::from_shear(vector));
        return Transform2(by.matrix * matrix);
    }

    [[nodiscard]] Transform2 shear_local(const Vector2& vector) const
    {
        const Transform2 by = from_basis(Basis2::from_shear(vector));
        return Transform2(matrix * by.matrix);
    }

    [[nodiscard]] Transform2 translate(const Vector2& offset) const
    {
        return from_basis_translation(basis(), translation() + offset);
    }

    [[nodiscard]] Transform2 translate_local(const Vector2& offset) const
    {
        const Vector2 local_offset = offset.transform(basis());
        return from_basis_translation(basis(), translation() + local_offset);
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
    using Column = Vector4;

    union {
        struct {
            float c0r0;
            float c0r1;
            float c0r2;
            float c0r3;
            float c1r0;
            float c1r1;
            float c1r2;
            float c1r3;
            float c2r0;
            float c2r1;
            float c2r2;
            float c2r3;
            float c3r0;
            float c3r1;
            float c3r2;
            float c3r3;
        };
        std::array<Column, 4> columns;
    };

    Matrix4()
        : c0r0(1.0f)
        , c0r1(0.0f)
        , c0r2(0.0f)
        , c0r3(0.0f)
        , c1r0(0.0f)
        , c1r1(1.0f)
        , c1r2(0.0f)
        , c1r3(0.0f)
        , c2r0(0.0f)
        , c2r1(0.0f)
        , c2r2(1.0f)
        , c2r3(0.0f)
        , c3r0(0.0f)
        , c3r1(0.0f)
        , c3r2(0.0f)
        , c3r3(1.0f)
    {
    }

    Matrix4(const Column& column_1, const Column& column_2, const Column& column_3, const Column& column_4)
        : c0r0(column_1[0])
        , c0r1(column_1[1])
        , c0r2(column_1[2])
        , c0r3(column_1[3])
        , c1r0(column_2[0])
        , c1r1(column_2[1])
        , c1r2(column_2[2])
        , c1r3(column_2[3])
        , c2r0(column_3[0])
        , c2r1(column_3[1])
        , c2r2(column_3[2])
        , c2r3(column_3[3])
        , c3r0(column_4[0])
        , c3r1(column_4[1])
        , c3r2(column_4[2])
        , c3r3(column_4[3])
    {
    }

    [[nodiscard]] static Matrix4 all(float value)
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

    [[nodiscard]] float determinant() const
    {
        float det = 0.0f;
        for (int c = 0; c < 4; ++c) {
            const float det_minor = minor_at(c, 0);
            det += (c % 2 == 0 ? 1.0f : -1.0f) * at(0, c) * det_minor;
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

    [[nodiscard]] const Column& at(const int column) const
    {
        NNM_BOUNDS_CHECK("Matrix4", column >= 0 && column <= 3);
        return columns[column];
    }

    Column& at(const int column)
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

    const Column& operator[](const int index) const
    {
        NNM_BOUNDS_CHECK("Matrix4", index >= 0 && index <= 3);
        return columns[index];
    }

    Column& operator[](const int index)
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

    Matrix4 operator*(const float value) const
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

    Matrix4 operator/(const float value)
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

    [[nodiscard]] static Matrix4 from_rotation_translation(
        const Vector3& rotation_x, const Vector3& rotation_y, const Vector3& rotation_z, const Vector3& translation)
    {
        Matrix4 result;
        result[0] = Vector4(rotation_x.x, rotation_x.y, rotation_x.z, 0.0f);
        result[1] = Vector4(rotation_y.x, rotation_y.y, rotation_y.z, 0.0f);
        result[2] = Vector4(rotation_z.x, rotation_z.y, rotation_z.z, 0.0f);
        result[3] = Vector4(translation.x, translation.y, translation.z, 1.0f);
        return result;
    }

    [[nodiscard]] static Matrix4 from_basis_translation(const Matrix3& basis, const Vector3& translation)
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

    static Matrix4 from_look_at(const Vector3 eye, const Vector3 target, const Vector3 up)
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
        result[3][0] = -cross_up.dot(eye);
        result[3][1] = -cross.dot(eye);
        result[3][2] = target_eye.dot(eye);

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

    // [[nodiscard]] Matrix4 interpolate(const Matrix4& to, float weight) const
    // {
    //     const Vector3 from_scale = scale();
    //     Quaternion from_rotation = quaternion();
    //     Vector3 from_translation = translation();
    //
    //     const Vector3 to_scale = to.scale();
    //     Quaternion to_rotation = to.quaternion();
    //     Vector3 to_translation = to.translation();
    //
    //     Quaternion result_rotation = from_rotation.spherical_linear_interpolate(to_rotation, weight).normalize();
    //     Vector3 result_scale = from_scale.lerp(to_scale, weight);
    //     const Matrix3 result_basis = Matrix3::from_quaternion_scale(result_rotation, result_scale);
    //     const Vector3 result_translation = from_translation.linear_interpolate(to_translation, weight);
    //
    //     return Matrix4::from_basis_translation(result_basis, result_translation);
    // }

    // [[nodiscard]] Matrix4 rotate(const Vector3& axis, float angle) const
    // {
    //     const auto rotation_basis = Matrix3::from_axis_angle(axis, angle);
    //     return Matrix4::from_basis_translation(this->basis() * rotation_basis, translation());
    // }

    // [[nodiscard]] Matrix4 rotate(const Matrix3& basis) const
    // {
    //     return Matrix4::from_basis_translation(this->basis() * basis, this->translation());
    // }

    // [[nodiscard]] Matrix4 rotate_local(const Vector3& axis, float angle) const
    // {
    //     const auto rotation_basis = Matrix3::from_axis_angle(axis, angle);
    //     return Matrix4::from_basis_translation(rotation_basis * basis(), translation());
    // }

    // [[nodiscard]] Matrix4 rotate_local(const Matrix3& basis) const
    // {
    //     return Matrix4::from_basis_translation(basis * this->basis(), translation());
    // }
    //
    // [[nodiscard]] Matrix4 scale(const Vector3& scale) const
    // {
    //     const Matrix3 basis = this->basis().scale(scale);
    //     const Vector3 translation = this->translation() * scale;
    //     return Matrix4::from_basis_translation(basis, translation);
    // }
    //
    // [[nodiscard]] Matrix4 translate(const Vector3& offset) const
    // {
    //     return Matrix4::from_basis_translation(basis(), translation() + offset);
    // }
    //
    // [[nodiscard]] Matrix4 translate_local(const Vector3& offset) const
    // {
    //     const auto basis = this->basis();
    //     const auto basis_t = basis.transpose();
    //     const Vector3 rotated_offset { basis_t.col0.dot(offset), basis_t.col1.dot(offset), basis_t.col2.dot(offset)
    //     }; return Matrix4::from_basis_translation(basis, translation() + rotated_offset);
    // }

    // [[nodiscard]] bool is_equal_approx(const Matrix4& other) const
    // {
    //     return (*this)[0].approx_equal(other[0]) && (*this)[1].approx_equal(other[1])
    //         && (*this)[2].approx_equal(other[2]) && (*this)[3].approx_equal(other[3]);
    // }
    //
    // [[nodiscard]] bool is_zero_approx() const
    // {
    //     return (*this)[0].approx_zero() && (*this)[1].approx_zero() && (*this)[2].approx_zero()
    //         && (*this)[3].approx_zero();
    // }

    // [[nodiscard]] Matrix3 basis() const
    // {
    //     return Matrix3::from_matrix(*this);
    // }

    [[nodiscard]] Vector3 translation() const
    {
        return { (*this)[3][0], (*this)[3][1], (*this)[3][2] };
    }

    // [[nodiscard]] Quaternion quaternion() const
    // {
    //     return Quaternion::from_matrix(basis());
    // }
    //
    // [[nodiscard]] Vector3 scale() const
    // {
    //     return basis().scale();
    // }
    //
    // [[nodiscard]] Vector3 euler() const
    // {
    //     return basis().euler();
    // }
};

inline Vector3::Vector3(const Vector3i vector) // NOLINT(*-pro-type-member-init)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
    , z(static_cast<float>(vector.z))
{
}

inline Quaternion Quaternion::from_matrix(const Matrix3& matrix)
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

// inline Matrix3 Quaternion::matrix() const
// {
//     return Matrix3::from_quaternion(*this);
// }

inline Quaternion Quaternion::normalize() const
{
    return *this / this->length();
}

// template <typename Number>
// Matrix3<Number> Matrix3<Number>::from_matrix(const Matrix4<Number>& matrix)
// {
//     Matrix3 result;
//     result[0] = Column(matrix[0][0], matrix[0][1], matrix[0][2]);
//     result[1] = Column(matrix[1][0], matrix[1][1], matrix[1][2]);
//     result[2] = Column(matrix[2][0], matrix[2][1], matrix[2][2]);
//     return result;
// }

inline Vector2::Vector2(const Vector2i& vector) // NOLINT(*-pro-type-member-init)
    : x(static_cast<float>(vector.x))
    , y(static_cast<float>(vector.y))
{
}

inline Vector2 Vector2::transform(const Basis2& by) const
{
    return { by.at(0, 0) * x + by.at(1, 0) * y, by.at(0, 1) * x + by.at(1, 1) * y };
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
