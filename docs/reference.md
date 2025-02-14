# Reference

Reference for NNM math library.

Functions and classes are templated with either `Num`, `Real`, or `Int`.

- `Num` means that any numeric type can be used such as `float` or `int`.
- `Real` means that any floating point type can be used such as `float` or `double`.
- `Int` means that any integral type can be used such as `int` or `uint64_t`.

## Contents

* [Macros](#Macros)
* [Functions](#Functions)
* [Vector2](#Vector2)
* [Vector2i](#Vector2i)
* [Vector3](#Vector3)
* [Vector3i](#Vector3i)
* [Vector4](#Vector4)
* [Quaternion](#Quaternion)
* [Matrix2](#Matrix2)
* [Basis2](#Basis2)
* [Matrix3](#Matrix3)
* [Transform2](#Transform2)
* [Basis3](#Basis3)
* [Matrix4](#Matrix4)
* [Transform3](#Transform3)

## Macros

```c++
// If defined, will throw std::out_of_range on invalid bounds access.
NNM_BOUNDS_CHECK

// Macro function to check bounds. Behavior dependes on NNM_BOUNDS_CHECK being defined.
// Default behavior is no bounds checking and thus will do nothing.
NNM_BOUNDS_CHECK_ASSERT(msg, expression)
```

## Functions

```c++
Real pi();
Real epsilon();
Num sign(Num value);
Num abs(Num value);
Num max(Num a, Num b);
bool approx_zero(Real value);
bool approx_equal(Real a, Real b);
Real ceil(Real value);
Num clamp(Num value, Num min, Num max);
Real sqrt(Real value);
Real pow(Real base, Real power);
Num sqrd(Num value);
Real modf(Real a, Real b);
Int mod(Int a, Int b);
Real remf(Real a, Real b);
Int rem(Int a, Int b);
Real normalize_angle(Real angle);
bool angle_in_range(Real angle, Real from, Real to);
Real floor(Real value);
Real lerp(Real from, Real to, Real weight);
Real lerp_clamped(Real from, Real to, Real weight);
Real sin(Real value);
Real cos(Real value);
Real tan(Real value);
Real round(Real value);
Real atan(Real value);
Real atan2(Real a, Real b);
Real radians(Real degrees);
Real degrees(Real radians);
Real asin(Real value);
Real acos(Real value);
Num min(Num a, Num b);
Real log2(Real value);
```

## Vector2

### Aliases

```cpp
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
```

### Members

```c++
Real x;
Real y;
```

### Constructors

```c++
Vector2();
explicit Vector2(const Vector2i& vector);
explicit Vector2(const Vector2<Other>& vector);
Vector2(Real x, Real y);
```

### Static Methods

```c++
static Vector2 all(Real value);
static Vector2 zero();
static Vector2 one();
static Vector2 axis_x();
static Vector2 axis_y();
```

### Methods

```c++
Vector2 abs() const;
Vector2 ceil() const;
Vector2 floor() const;
Vector2 round() const;
Real aspect_ratio() const;
Vector2 clamp(const Vector2& min, const Vector2& max) const;
Vector2 direction(const Vector2& to) const;
Vector2 direction_unnormalized(const Vector2& to) const;
Real distance_sqrd(const Vector2& to) const;
Real distance(const Vector2& to) const;
Real manhattan_distance(const Vector2& to) const
Real length_sqrd() const;
Real length() const;
Vector2 clamp_length(Real min, Real max) const;
Vector2 normalize() const;
Vector2 lerp(const Vector2& to, Real weight) const;
Vector2 lerp_clamped(const Vector2& to, Real weight) const;
Real dot(const Vector2& other) const;
Real cross(const Vector2& other) const;
Matrix2 outer(const Vector2& other) const;
Vector2 reflect(const Vector2& normal) const;
Vector2 project(const Vector2& onto) const;
Vector2 inverse() const;
Real angle_between(const Vector2& to) const;
Real angle_to(const Vector2& to) const;
bool approx_parallel(const Vector2& other) const;
bool approx_perpendicular(const Vector2& other) const;
Vector2 arbitrary_perpendicular() const;
Vector2 translate(const Vector2& by) const;
Vector2 rotate(Real angle) const;
Vector2 rotate_at(const Vector2& origin, Real angle) const;
Vector2 scale(const Vector2& factor) const;
Vector2 scale_at(const Vector2& origin, const Vector2& factor) const;
Vector2 shear_x(Real factor) const;
Vector2 shear_x_at(const Vector2& origin, Real factor) const;
Vector2 shear_y(Real factor) const;
Vector2 shear_y_at(const Vector2& origin, Real factor) const;
Vector2 transform(const Basis2& by) const;
Vector2 transform_at(const Vector2& origin, const Basis2& by) const;
Vector2 transform(const Transform2& by, Real z = 1.0) const;
Vector2 transform_at(const Vector2& origin, const Transform2& by, Real z = 1.0) const;
Real max() const;
Real min() const;
uint8_t max_index() const;
uint8_t min_index() const;
bool approx_equal(const Vector2& other) const;
bool approx_zero() const;
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
Real at(const uint8_t index) const;
Real& at(const uint8_t index);
```

### Operators

```c++
Real operator[](uint8_t index) const;
Real& operator[](uint8_t index);
bool operator==(const Vector2& other) const;
bool operator!=(const Vector2& other) const;
Vector2 operator+(const Vector2& other) const;
Vector2& operator+=(const Vector2& other);
Vector2 operator-(const Vector2& other) const;
Vector2& operator-=(const Vector2& other);
Vector2 operator*(const Vector2& other) const;
Vector2& operator*=(const Vector2& other);
Vector2 operator*(const Matrix2& matrix) const;
Vector2 operator*(Real value) const;
Vector2 operator*(Real value, const Vector2& vector);
Vector2& operator*=(Real value);
Vector2 operator/(const Vector2& other) const;
Vector2& operator/=(const Vector2& other);
Vector2 operator/(Real value) const;
Vector2 operator/(const Real value, const Vector2& vector);
Vector2& operator/=(Real value);
Vector2 operator+() const;
Vector2 operator-() const;
bool operator<(const Vector2& other) const;
operator bool() const;
```

## Vector2i

### Aliases

```cpp
using Vector2ii = Vector2i<int>;
using Vector2i8 = Vector2i<int8_t>;
using Vector2i16 = Vector2i<int16_t>;
using Vector2i32 = Vector2i<int32_t>;
using Vector2i64 = Vector2i<int64_t>;
using Vector2iu = Vector2i<unsigned int>;
using Vector2u8 = Vector2i<uint8_t>;
using Vector2u16 = Vector2i<uint16_t>;
using Vector2u32 = Vector2i<uint32_t>;
using Vector2u64 = Vector2i<uint64_t>;
```

### Members

```c++
Int x;
Int y;
```

### Constructors

```c++
Vector2i();
explicit Vector2i(const Vector2& vector);
Vector2i(Int x, Int y);
```

### Static Methods

```c++
static Vector2i all(Int value);
static Vector2i zero();
static Vector2i one();
static Vector2i axis_x();
static Vector2i axis_y();
```

### Methods

```c++
Vector2i abs() const;
Vector2i clamp(const Vector2i& min, const Vector2i& max) const;
Int manhattan_distance(const Vector2i& to) const;
Int length_sqrd() const;
Int dot(const Vector2i& other) const;
Int cross(const Vector2i& other) const;
bool parallel(const Vector2i& other) const;
bool perpendicular(const Vector2i& other) const;
Vector2i arbitrary_perpendicular() const;
Int max() const;
Int min() const;
uint8_t max_index() const;
uint8_t min_index() const;
const Int* begin() const;
const Int* end() const;
Int* begin();
Int* end();
Int at(const uint8_t index) const;
Int& at(const uint8_t index);
```

### Operators

```c++
Int operator[](uint8_t index) const;
Int& operator[](uint8_t index);
bool operator==(const Vector2i& other) const;
bool operator!=(const Vector2i& other) const;
Vector2i operator+(const Vector2i& other) const;
Vector2i& operator+=(const Vector2i& other);
Vector2i operator-(const Vector2i& other) const;
Vector2i& operator-=(const Vector2i& other);
Vector2i operator*(const Vector2i& other) const;
Vector2i& operator*=(const Vector2i& other);
Vector2i operator*(Int value) const;
Vector2i operator*(Int value, const Vector2i& vector);
Vector2i& operator*=(Int value);
Vector2i operator/(const Vector2i& other) const;
Vector2i& operator/=(const Vector2i& other);
Vector2i operator/(Int value) const;
Vector2i operator/(Int value, const Vector2i& vector);
Vector2i& operator/=(Int value);
Vector2i operator%(const Vector2i& other) const;
Vector2i& operator%=(const Vector2i& other);
Vector2i operator%(Int value) const;
Vector2i operator&(Int value, const Vector2i& vector);
Vector2i& operator%=(Int value);
Vector2i operator+() const;
Vector2i operator-() const;
bool operator<(const Vector2i& other) const;
operator bool() const;
```

### Types

```c++
struct Vector2i::Hash {
    size_t operator()(const nnm::Vector2i& vector) const noexcept;
}
```

## Vector3

### Aliases

```cpp
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
```

### Members

```c++
Real x;
Real y;
Real z;
```

### Constructors

```c++
Vector3();
explicit Vector3(const Vector3i& vector);
explicit Vector3(const Vector3<Other>& vector);
Vector3(const Vector2& vector, Real z);
Vector3(Real x, Real y, Real z);
```

### Static Methods

```c++
static Vector3 all(Real value);
static Vector3 zero();
static Vector3 one();
static Vector3 axis_x();
static Vector3 axis_y();
static Vector3 axis_z();
```

### Methods

```c++
Vector3 abs() const;
Vector3 ceil() const;
Vector3 floor() const;
Vector3 round() const;
Vector3 clamp(const Vector3& min, const Vector3& max) const;
Vector3 direction(const Vector3& to) const;
Vector3 direction_unnormalized(const Vector3& to) const;
Real distance_sqrd(const Vector3& to) const;
Real distance(const Vector3& to) const;
Real manhattan_distance(const Vector3& to) const;
Real length_sqrd() const;
Real length() const;
Vector3 clamp_length(Real min, Real max) const;
Vector3 normalize() const;
Vector3 lerp(const Vector3& to, Real weight) const;
Vector3 lerp_clamped(const Vector3& to, Real weight) const;
Real dot(const Vector3& other) const;
Vector3 cross(const Vector3& other) const;
Matrix3 outer(const Vector3& other) const;
Vector3 reflect(const Vector3& normal) const;
Vector3 project(const Vector3& onto) const;
Vector3 inverse() const;
Real angle(const Vector3& other) const;
bool approx_parallel(const Vector3& other) const;
bool approx_perpendicular(const Vector3& other) const;
Vector3 arbitrary_perpendicular() const;
Vector3 translate(const Vector3& by) const;
Vector3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Vector3 rotate_axis_angle_at(const Vector3& origin, const Vector3& axis, Real angle) const;
Vector3 rotate_quaternion(const Quaternion& quaternion) const;
Vector3 rotate_quaternion_at(const Vector3& origin, const Quaternion& quaternion) const;
Vector3 scale(const Vector3& factor) const;
Vector3 scale_at(const Vector3& origin, const Vector3& factor) const;
Vector3 shear_x(Real factor_y, Real factor_z) const;
Vector3 shear_x_at(const Vector3& origin, Real factor_y, Real factor_z) const;
Vector3 shear_y(Real factor_x, Real factor_z) const;
Vector3 shear_y_at(const Vector3& origin, Real factor_x, Real factor_z) const;
Vector3 shear_z(Real factor_x, Real factor_y) const;
Vector3 shear_z_at(const Vector3& origin, Real factor_x, Real factor_y) const;
Vector3 transform(const Basis3& by) const;
Vector3 transform_at(const Vector3& origin, const Basis3& by) const;
Vector3 transform(const Transform2& by) const;
Vector3 transform_at(const Vector2& origin, const Transform2& by) const;
Vector3 transform(const Transform3& by, Real w = 1.0) const;
Vector3 transform_at(const Vector3& origin, const Transform3& by, Real w = 1.0) const;
Real max() const;
Real min() const;
uint8_t max_index() const;
uint8_t min_index() const;
bool approx_equal(const Vector3& other) const;
bool approx_zero() const;
Vector2 xy() const;
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
Real at(uint8_t index) const;
Real& at(uint8_t index);
```

### Operators

```c++
Real operator[](uint8_t index) const;
Real& operator[](uint8_t index);
bool operator==(const Vector3& other) const;
bool operator!=(const Vector3& other) const;
Vector3 operator+(const Vector3& other) const;
Vector3& operator+=(const Vector3& other);
Vector3 operator-(const Vector3& other) const;
Vector3& operator-=(const Vector3& other);
Vector3 operator*(const Vector3& other) const;
Vector3& operator*=(const Vector3& other);
Vector3 operator*(const Matrix3& other) const;
Vector3 operator*(Real value) const;
Vector3 operator*(Real value, const Vector3& vector);
Vector3& operator*=(Real value);
Vector3 operator/(const Vector3& other) const;
Vector3& operator/=(const Vector3& other);
Vector3 operator/(Real value) const;
Vector3 operator/(Real value, const Vector3& vector);
Vector3& operator/=(Real value);
bool operator<(const Vector3& other) const;
Vector3 operator+() const;
Vector3 operator-() const;
operator bool() const;
```

## Vector3i

```cpp
using Vector3ii = Vector3i<int>;
using Vector3i8 = Vector3i<int8_t>;
using Vector3i16 = Vector3i<int16_t>;
using Vector3i32 = Vector3i<int32_t>;
using Vector3i64 = Vector3i<int64_t>;
using Vector3iu = Vector3i<unsigned int>;
using Vector3u8 = Vector3i<uint8_t>;
using Vector3u16 = Vector3i<uint16_t>;
using Vector3u32 = Vector3i<uint32_t>;
using Vector3u64 = Vector3i<uint64_t>;
```

### Members

```c++
Int x;
Int y;
Int z;
```

### Constructors

```c++
Vector3i();
explicit Vector3i(const Vector3& vector);
Vector3i(const Vector2i& vector, Int z);
Vector3i(Int x, Int y, Int z);
```

### Static Methods

```c++
static Vector3i all(Int value);
static Vector3i zero();
static Vector3i one();
static Vector3i axis_x();
static Vector3i axis_y();
static Vector3i axis_z();
```

### Methods

```c++
Vector3i abs() const;
Vector3i clamp(const Vector3i& min, const Vector3i& max) const;
Int manhattan_distance(const Vector3i& to) const;
Int length_sqrd() const;
Int dot(const Vector3i& other) const;
Vector3i cross(const Vector3i& other) const;
bool parallel(const Vector3i& other) const;
bool perpendicular(const Vector3i& other) const;
Vector3i arbitrary_perpendicular() const;
Int max() const;
Int min() const;
uint8_t max_index() const;
uint8_t min_index() const;
Vector2i xy() const;
const Int* begin() const;
const Int* end() const;
Int* begin();
Int* end();
Int at(uint8_t index) const;
Int& at(uint8_t index);
```

### Operators

```c++
Int operator[](uint8_t index) const;
Int& operator[](uint8_t index);
bool operator==(const Vector3i& other) const;
bool operator!=(const Vector3i& other) const;
Vector3i operator+(const Vector3i& other) const;
Vector3i& operator+=(const Vector3i& other);
Vector3i operator-(const Vector3i& other) const;
Vector3i& operator-=(const Vector3i& other);
Vector3i operator*(const Vector3i& other) const;
Vector3i& operator*=(const Vector3i& other);
Vector3i operator*(Int value) const;
Vector3i operator*(Int value, const Vector3i& vector);
Vector3i& operator*=(Int value);
Vector3i operator/(const Vector3i& other) const;
Vector3i& operator/=(const Vector3i& other);
Vector3i operator/(Int value) const;
Vector3i operator/(Int value, const Vector3i& vector);
Vector3i& operator/=(Int value);
Vector3i operator%(const Vector3i& other) const;
Vector3i& operator%=(const Vector3i& other);
Vector3i operator%(Int val) const;
Vector3i& operator%=(Int val);
Vector3i operator+() const;
Vector3i operator-() const;
bool operator<(const Vector3i& other) const;
operator bool() const;
```

### Types

```c++
struct Vector3i::Hash {
    size_t operator()(const nnm::Vector3i& vector) const noexcept;
}
```

## Vector4

### Aliases

```cpp
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
```

### Members

```c++
Real x;
Real y;
Real z;
Real w;
```

### Constructors

```c++
Vector4();
explicit Vector4(const Vector4<Other>& vector);
Vector4(const Vector2& vector, const Real z, const Real w);
Vector4(const Vector3& vector, const Real w);
Vector4(Real x, Real y, Real z, Real w);
```

### Static Methods

```c++
static Vector4 from_quaternion(const Quaternion& quaternion);
static Vector4 all(Real value);
static Vector4 zero();
static Vector4 one();
static Vector4 axis_x();
static Vector4 axis_y();
static Vector4 axis_z();
static Vector4 axis_w();
```

### Methods

```c++
Vector4 abs() const;
Vector4 ceil() const;
Vector4 floor() const;
Vector4 round() const;
Vector4 clamp(const Vector4& min, const Vector4& max) const;
Real length_sqrd() const;
Real length() const;
Vector4 clamp_length(Real min, Real max) const;
Vector4 normalize() const;
Vector4 lerp(const Vector4& to, Real weight) const;
Vector4 lerp_clamped(const Vector4& to, Real weight) const;
Real dot(const Vector4& other) const;
Matrix4 outer(const Vector4& other) const;
Vector4 inverse() const;
Vector4 transform(const Transform3& by) const;
Vector4 transform_at(const Vector3& origin, const Transform3& by) const;
Int max() const;
Int min() const;
uint8_t max_index() const;
uint8_t min_index() const;
bool approx_equal(const Vector4& other) const;
bool approx_zero() const;
Vector2 xy() const;
Vector3 xyz() const;
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
Real at(uint8_t index) const;
Real& at(uint8_t index);
```

### Operators

```c++
Real operator[](uint8_t index) const;
Real& operator[](uint8_t index);
bool operator==(const Vector4& other) const;
bool operator!=(const Vector4& other) const;
Vector4 operator+(const Vector4& other) const;
Vector4& operator+=(const Vector4& other);
Vector4 operator-(const Vector4& other) const;
Vector4& operator-=(const Vector4& other);
Vector4 operator*(const Vector4& other) const;
Vector4& operator*=(const Vector4& other);
Vector4 operator*(Real value) const;
Vector4 operator*(Real value, const Vector4& vector);
Vector4& operator*=(Real value);
Vector4 operator/(const Vector4& other) const;
Vector4& operator/=(const Vector4& other);
Vector4 operator/(Real value) const;
Vector4 operator/(Real value, const Vector4& vector)
Vector4& operator/=(Real value);
bool operator<(const Vector4& other) const;
Vector4 operator+() const;
Vector4 operator-() const;
explicit operator bool() const;
```

## Quaternion

### Aliases

```cpp
using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;
```

### Members

```c++
Real x;
Real y;
Real z;
Real w;
```

### Constructors

```c++
Quaternion();
explicit Quaternion(const Quaternion<Other>& quaternion);
explicit Quaternion(const Vector4& vector);
Quaternion(Real x, Real y, Real z, Real w);
```

### Static Methods

```c++
static Quaternion identity();
static Quaternion from_axis_angle(const Vector3& axis, Real angle);
static Quaternion from_vector_to_vector(const Vector3& from, const Vector3& to);
```

### Methods

```c++
Quaternion normalize() const;
Vector3 axis(const Quaternion& to) const;
Real angle(const Quaternion& to) const;
Vector3 axis() const;
Real angle() const;
Quaternion inverse() const;
Real length_sqrd() const;
Real length() const;
Quaternion slerp(const Quaternion& to, Real weight) const;
Quaternion rotate_axis_angle(const Vector3& axis, Real angle) const;
Quaternion rotate_quaternion(const Quaternion& by) const;
bool approx_equal(const Quaternion& other) const;
Real at(uint8_t index) const;
Real& at(uint8_t index);
```

### Operators

```c++
Real operator[](uint8_t index) const;
Real& operator[](uint8_t index);
bool operator==(const Quaternion& other) const;
bool operator!=(const Quaternion& other) const;
Quaternion operator*(const Quaternion& other) const;
Quaternion& operator*=(const Quaternion& other);
bool operator<(const Quaternion& other) const;
explicit operator bool() const;
```

## Matrix2

### Aliases

```cpp
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;
```

### Members

```c++
Vector2 columns[2];
```

### Constructors

```c++
Matrix2();
explicit Matrix2(const Matrix2<Other>& matrix);
Matrix2(const Vector2& column0, const Vector2& column1);
Matrix2(Real col0_row0, Real col0_row1, Real col1_row0, Real col1_row1);
```

### Static Methods

```c++
static Matrix2 all(Real value);
static Matrix2 zero();
static Matrix2 one();
static Matrix2 identity();
```

### Methods

```c++
Real trace() const;
Real determinant() const;
Real minor_at(uint8_t column, uint8_t row) const;
Matrix2 minor() const;
Real cofactor_at(uint8_t column, uint8_t row) const;
Matrix2 cofactor() const;
Matrix2 transpose() const;
Matrix2 adjugate() const;
Matrix2 unchecked_inverse() const;
std::optional<Matrix2> inverse() const;
bool approx_equal(const Matrix2& other) const;
bool approx_zero() const;
Vector2 at(uint8_t column) const;
Vector2& at(uint8_t column);
Real at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
```

### Operators

```c++
Vector2 operator[](uint8_t column) const;
Vector2& operator[](uint8_t column);
bool operator==(const Matrix2& other) const;
bool operator!=(const Matrix2& other) const;
Matrix2 operator+(const Matrix2& other) const;
Matrix2& operator+=(const Matrix2& other);
Matrix2 operator-(const Matrix2& other) const;
Matrix2& operator-=(const Matrix2& other);
Matrix2 operator*(const Matrix2& other) const;
Matrix2& operator*=(const Matrix2& other);
Vector2 operator*(const Vector2& vector) const;
Matrix2 operator*(Real value) const;
Matrix2 operator*(Real value, const Matrix2& matrix);
Matrix2& operator*=(Real value);
Matrix2 operator/(Real value) const;
Matrix2 operator/(Real value, const Matrix2& matrix);
Matrix2& operator/=(Real value);
bool operator<(const Matrix2& other) const;
explicit operator bool() const;
```

## Basis2

### Aliases

```cpp
using Basis2f = Basis2<float>;
using Basis2d = Basis2<double>;
```

### Members

```c++
Matrix2 matrix;
```

### Constructors

```c++
Basis2();
explicit Basis2(const Basis2<Other>& basis);
explicit Basis2(const Matrix2& matrix);
```

### Static Methods

```c++
static Basis2 from_rotation(Real angle);
static Basis2 from_scale(const Vector2& factor);
static Basis2 from_shear_x(Real factor);
static Basis2 from_shear_y(Real factor);
```

### Methods

```c++
Real trace() const;
Real determinant();
Basis2 unchecked_inverse() const;
std::optional<Basis2> inverse() const;
bool valid() const;
Basis2 rotate(Real angle) const;
Basis2 rotate_local(Real angle) const;
Basis2 scale(const Vector2& factor) const;
Basis2 scale_local(const Vector2& factor) const;
Basis2 shear_x(Real factor) const;
Basis2 shear_x_local(Real factor) const;
Basis2 shear_y(Real factor) const;
Basis2 shear_y_local(Real factor) const;
Basis2 transform(const Basis2& by) const;
Basis2 transform_local(const Basis2& by) const;
bool approx_equal(const Basis2& other) const;
const Vector2& at(const uint8_t column) const;
Vector2& at(const uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
```

### Operators

```c++
const Vector2& operator[](uint8_t index) const;
Vector2& operator[](uint8_t index);
bool operator==(const Basis2& other) const;
bool operator!=(const Basis2& other) const;
bool operator<(const Basis2& other) const;
```

## Matrix3

### Aliases

```cpp
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;
```

### Members

```c++
Vector3 columns[3];
```

### Constructors

```c++
Matrix3();
explicit Matrix3(const Matrix3<Other>& matrix);
Matrix3(const Column& column0, const Column& column1, const Column& column2);
Matrix3(
    Real col0_row0,
    Real col0_row1,
    Real col0_row2,
    Real col1_row0,
    Real col1_row1,
    Real col1_row2,
    Real col2_row0,
    Real col2_row1,
    Real col2_row2);
```

### Static Methods

```c++
static Matrix3 all(Real value);
static Matrix3 zero();
static Matrix3 one();
static Matrix3 identity();
```

### Methods

```c++
Real trace() const;
Real determinant() const;
Matrix2 minor_matrix_at(uint8_t column, uint8_t row) const;
Real minor_at(uint8_t column, uint8_t row) const;
Matrix3 minor() const;
Real cofactor_at(uint8_t column, uint8_t row) const;
Matrix3 cofactor() const;
Matrix3 transpose() const;
Matrix3 adjugate() const;
Matrix3 unchecked_inverse() const;
std::optional<Matrix3> inverse() const;
bool approx_equal(const Matrix3& other) const;
bool approx_zero() const;
const Vector3& at(uint8_t column) const;
Column& at(uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
```

### Operators

```c++
const Vector3& operator[](uint8_t column) const;
Vector3& operator[](uint8_t column);
bool operator==(const Matrix3& other) const;
bool operator!=(const Matrix3& other) const;
Matrix3 operator+(const Matrix3& other) const;
Matrix3& operator+=(const Matrix3& other);
Matrix3 operator-(Matrix3& other) const;
Matrix3& operator-=(const Matrix3& other);
Matrix3 operator*(const Matrix3& other) const;
Matrix3& operator*=(const Matrix3& other);
Vector3 operator*(const Vector3& vector) const;
Matrix3 operator*(Real value) const;
Matrix3 operator*(Real value, const Matrix3& matrix);
Matrix3& operator*=(Real value);
Matrix3 operator/(Real value) const;
Matrix3 operator/(Real value, const Matrix3& matrix);
Matrix3& operator/=(Real value);
bool operator<(const Matrix3& other) const;
explicit operator bool() const;
```

## Transform2

### Aliases

```cpp
using Transform2f = Transform2<float>;
using Transform2d = Transform2<double>;
```

### Members

```c++
Matrix3 matrix;
```

### Constructors

```c++
Transform2();
explicit Transform2(const Transform2<Other>& transform);
explicit Transform2(const Matrix3& matrix);
static Transform2 from_basis_translation(const Basis2& basis, const Vector2& translation);
static Transform2 from_basis(const Basis2& basis);
static Transform2 from_translation(const Vector2& pos);
static Transform2 from_rotation(Real angle);
static Transform2 from_scale(const Vector2& factor);
static Transform2 from_shear_x(Real factor);
static Transform2 from_shear_y(Real factor);
```

### Methods

```c++
Real trace() const;
Real determinant() const;
Transform2 unchecked_inverse() const;
std::optional<Transform2> inverse() const;
bool valid() const;
bool affine() const;
Basis2 basis() const;
Vector2 translation() const;
Transform2 translate(const Vector2& offset) const;
Transform2 translate_local(const Vector2& offset) const;
Transform2 rotate(Real angle) const;
Transform2 rotate_local(Real angle) const;
Transform2 scale(const Vector2& factor) const;
Transform2 scale_local(const Vector2& factor) const;
Transform2 shear_x(Real factor) const;
Transform2 shear_x_local(Real factor) const;
Transform2 shear_y(Real factor) const;
Transform2 shear_y_local(Real factor) const;
Transform2 transform(const Transform2& by) const;
Transform2 transform_local(const Transform2& by) const;
bool approx_equal(const Transform2& other) const;
const Vector3& at(uint8_t column) const;
Vector3& at(uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
```

### Operators

```cpp
const Vector3& operator[](uint8_t column) const;
Vector3& operator[](uint8_t column);
bool operator==(const Transform2& other) const;
bool operator!=(const Transform2& other) const;
bool operator<(const Transform2& other) const;
```

## Basis3

### Aliases

```cpp
using Basis3f = Basis3<float>;
using Basis3d = Basis3<double>;
```

### Members

```c++
Matrix3 matrix;
```

### Constructors

```cpp
Basis3();
explicit Basis3(const Basis3<Other>& basis);
explicit Basis3(const Matrix3& matrix);
```

### Static Methods

```c++
static Basis3 from_rotation_axis_angle(const Vector3& axis, Real angle);
static Basis3 from_rotation_quaternion(const Quaternion& quaternion);
static Basis3 from_scale(const Vector3& factor)
static Basis3 from_shear_x(Real factor_y, Real factor_z);
static Basis3 from_shear_y(Real factor_x, Real factor_z);
static Basis3 from_shear_z(Real factor_x, Real factor_y);
```

### Methods

```cpp
Real trace() const;
Real determinant() const;
Basis3 unchecked_inverse() const;
std::optional<Basis3> inverse() const;
bool valid() const;
Basis3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Basis3 rotate_axis_angle_local(const Vector3& axis, Real angle) const;
Basis3 rotate_quaternion(const Quaternion& quaternion) const;
Basis3 rotate_quaternion_local(const Quaternion& quaternion) const;
Basis3 scale(const Vector3& factor) const;
Basis3 scale_local(const Vector3& factor) const;
Basis3 shear_x(Real factor_y, Real factor_z) const;
Basis3 shear_x_local(Real factor_y, Real factor_z) const;
Basis3 shear_y(Real factor_x, Real factor_z) const;
Basis3 shear_y_local(Real factor_x, Real factor_z) const;
Basis3 shear_z(Real factor_x, Real factor_y) const;
Basis3 shear_z_local(Real factor_x, Real factor_y) const;
Basis3 transform(const Basis3& by) const;
Basis3 transform_local(const Basis3& by) const;
bool approx_equal(const Basis3& other) const;
const Vector3& at(uint8_t column) const;
Vector3& at(const uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(const uint8_t column, const uint8_t row);
```

### Operators

```cpp
const Vector3& operator[](uint8_t index) const;
Vector3& operator[](uint8_t index);
bool operator==(const Basis3& other) const;
bool operator!=(const Basis3& other) const;
bool operator<(const Basis3& other) const;
```

## Matrix4

### Aliases

```cpp
using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
```

### Members

```cpp
Vector4 columns[4];
```

### Constructors

```cpp
Matrix4();
explicit Matrix4(const Matrix4<Other>& matrix);
Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);
Matrix4(
    Real col0_row0,
    Real col0_row1,
    Real col0_row2,
    Real col0_row3,
    Real col1_row0,
    Real col1_row1,
    Real col1_row2,
    Real col1_row3,
    Real col2_row0,
    Real col2_row1,
    Real col2_row2,
    Real col2_row3,
    Real col3_row0,
    Real col3_row1,
    Real col3_row2,
    Real col3_row3);
```

### Static Methods

```c++
static Matrix4 all(Real value);
static Matrix4 zero();
static Matrix4 one();
static Matrix4 identity();
```

### Methods

```cpp
Real trace() const;
Real determinant() const;
Matrix3 minor_matrix_at(uint8_t column, uint8_t row) const;
Real minor_at(uint8_t column, uint8_t row) const;
Matrix4 minor() const
Real cofactor_at(uint8_t column, uint8_t row) const;
Matrix4 cofactor() const;
Matrix4 transpose() const;
Matrix4 adjugate() const;
Matrix4 unchecked_inverse() const;
std::optional<Matrix4> inverse() const;
bool approx_equal(const Matrix4& other) const;
bool approx_zero() const;
const Vector4& at(uint8_t column) const;
Vector4& at(uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
const Real* begin() const;
const Real* end() const;
Real* begin();
Real* end();
```

### Operators

```cpp
const Vector4& operator[](uint8_t index) const;
Vector4& operator[](uint8_t index);
bool operator==(const Matrix4& other) const;
bool operator!=(const Matrix4& other) const;
Matrix4 operator+(const Matrix4& other) const;
Matrix4& operator+=(const Matrix4& other);
Matrix4 operator-(const Matrix4& other) const;
Matrix4& operator-=(const Matrix4& other);
Matrix4 operator*(const Matrix4& other) const;
Matrix4& operator*=(const Matrix4& other);
Vector4 operator*(const Vector4& vector) const;
Matrix4 operator*(Real value) const;
Matrix4 operator*(Real value, const Matrix4& matrix);
Matrix4& operator*=(Real value);
Matrix4 operator/(Real value) const;
Matrix4 operator/(Real value, const Matrix4& matrix);
Matrix4& operator/=(Real value);
bool operator<(const Matrix4& other) const;
explicit operator bool() const;
```

## Transform3

### Aliases

```cpp
using Transform3f = Transform3<float>;
using Transform3d = Transform3<double>;
```

### Members

```c++
Matrix4 matrix;
```

### Constructors

```c++
Transform3();
explicit Transform3(const Transform3<Other>& transform);
explicit Transform3(const Matrix4& matrix);
```

### Static Methods

```c++
static Transform3 from_basis_translation(const Basis3& basis, const Vector3& translation);
static Transform3 from_basis(const Basis3& basis);
static Transform3 from_translation(const Vector3& translation);
static Transform3 from_rotation_axis_angle(const Vector3& axis, Real angle);
static Transform3 from_rotation_quaternion(const Quaternion& quaternion);
static Transform3 from_scale(const Vector3& factor);
static Transform3 from_shear_x(Real factor_y, Real factor_z);
static Transform3 from_shear_y(Real factor_x, Real factor_z);
static Transform3 from_shear_z(Real factor_x, Real factor_y);
static Transform3 from_perspective_left_hand_neg1to1(Real fov, Real aspect_ratio, Real near_clip, Real far_clip);
static Transform3 from_perspective_left_hand_0to1(Real fov, Real aspect_ratio, Real near_clip, Real far_clip);
static Transform3 from_perspective_right_hand_neg1to1(Real fov, Real aspect_ratio, Real near_clip, Real far_clip);
static Transform3 from_perspective_right_hand_0to1(Real fov, Real aspect_ratio, Real near_clip, Real far_clip);
static Transform3 from_orthographic_left_hand_neg1to1(Real left, Real right, Real bottom, Real top, Real near_clip, Real far_clip);
static Transform3 from_orthographic_left_hand_0to1(Real left, Real right, Real bottom, Real top, Real near_clip, Real far_clip);
static Transform3 from_orthographic_right_hand_neg1to1(Real left, Real right, Real bottom, Real top, Real near_clip, Real far_clip);
static Transform3 from_orthographic_right_hand_0to1(Real left, Real right, Real bottom, Real top, Real near_clip, Real far_clip);
```

### Methods

```c++
Real trace() const;
Real determinant() const;
Transform3 unchecked_inverse() const;
std::optional<Transform3> inverse() const;
bool valid() const;
bool affine() const;
Basis3 basis() const;
Vector3 translation() const;
Transform3 translate(const Vector3& offset) const;
Transform3 translate_local(const Vector3& offset) const;
Transform3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Transform3 rotate_axis_angle_local(const Vector3& axis, Real angle) const;
Transform3 rotate_quaternion(const Quaternion& quaternion) const;
Transform3 rotate_quaternion_local(const Quaternion& quaternion) const;
Transform3 scale(const Vector3& factor) const;
Transform3 scale_local(const Vector3& factor) const;
Transform3 shear_x(Real factor_y, Real factor_z) const;
Transform3 shear_x_local(Real factor_y, Real factor_z) const;
Transform3 shear_y(Real factor_x, Real factor_z) const;
Transform3 shear_y_local(Real factor_x, Real factor_z) const;
Transform3 shear_z(Real factor_x, Real factor_y) const;
Transform3 shear_z_local(Real factor_x, Real factor_y) const;
Transform3 transform(const Transform3& by) const;
Transform3 transform_local(const Transform3& by) const;
bool approx_equal(const Transform3& other) const;
const Vector4& at(uint8_t column) const;
Vector4& at(uint8_t column);
const Real& at(uint8_t column, uint8_t row) const;
Real& at(uint8_t column, uint8_t row);
```

### Operators

```c++
const Vector4& operator[](uint8_t column) const;
Vector4& operator[](uint8_t column);
bool operator==(const Transform3& other) const;
bool operator!=(const Transform3& other) const;
bool operator<(const Transform3& other) const;
```



