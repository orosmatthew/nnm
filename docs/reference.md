# Reference

## Macros

```c++
// If defined, will throw std::out_of_range on invalid bounds access.
NNM_BOUNDS_CHECK

// Macro function to check bounds. Behavior dependes on NNM_BOUNDS_CHECK being defined.
// Default behavior is no bounds checking and thus will do nothing.
NNM_BOUNDS_CHECK_ASSERT(msg, expression)
```

## Constants

```c++
float pi = 3.141592653589793238462643383279502f;
float epsilon = 0.00001f;
```

## Functions

```c++
float sign(float value);
int sign(int value);
float abs(float value);
int abs(int value);
float max(float a, float b);
int max(int a, int b);
bool approx_zero(float value);
bool approx_equal(float a, float b);
float ceil(float value);
float clamp(float value, float min, float max);
int clamp(int value, int min, int max);
float sqrt(float value);
float pow(float base, float power);
float sqrd(float value);
int sqrd(int value);
float floor(float value);
float lerp(float from, float to, float weight);
float lerp_clamped(float from, float to, float weight);
float sin(float value);
float cos(float value);
float tan(float value);
float round(float value);
float atan(float value);
float atan2(float a, float b);
float radians(float degrees);
float degrees(float radians);
float asin(float value);
float acos(float value);
float min(float a, float b);
int min(int a, int b);
float log2(float value);
```

## Vector2

### Members

```c++
union {
    struct {
        float x;
        float y;
    };
    float data[2] {};
};
```

### Constructors

```c++
Vector2();
explicit Vector2(const Vector2i& vector);
Vector2(float x, float y);

```

### Static Methods

```c++
static Vector2 all(float value);
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
float aspect_ratio() const;
Vector2 clamp(const Vector2& min, const Vector2& max) const;
Vector2 direction(const Vector2& to) const;
float distance_sqrd(const Vector2& to) const;
float distance(const Vector2& to) const;
float manhattan_distance(const Vector2& to) const
float length_sqrd() const;
float length() const;
Vector2 clamp_length(float min, float max) const;
Vector2 normalize() const;
Vector2 lerp(const Vector2& to, float weight) const;
Vector2 lerp_clamped(const Vector2& to, float weight) const;
float dot(const Vector2& other) const;
float cross(const Vector2& other) const;
Matrix2 outer(const Vector2& other) const;
Vector2 reflect(const Vector2& normal) const;
Vector2 project(const Vector2& onto) const;
Vector2 inverse() const;
float angle(const Vector2& to) const;
Vector2 translate(const Vector2& by) const;
Vector2 rotate(float angle) const;
Vector2 scale(const Vector2& factor) const;
Vector2 shear_x(float angle_y) const;
Vector2 shear_y(float angle_x) const;
Vector2 transform(const Basis2& by) const;
Vector2 transform(const Transform2& by, float z = 1.0f) const;
int max_index() const;
int min_index() const;
bool approx_equal(const Vector2& other) const;
bool approx_zero() const;
const float* begin() const;
const float* end() const;
float* begin();
float* end();
float at(const int index) const;
float& at(const int index);
```

### Operators

```c++
float operator[](int index) const;
float& operator[](int index);
bool operator==(const Vector2& other) const;
bool operator!=(const Vector2& other) const;
Vector2 operator+(const Vector2& other) const;
Vector2& operator+=(const Vector2& other);
Vector2 operator-(const Vector2& other) const;
Vector2& operator-=(const Vector2& other);
Vector2 operator*(const Vector2& other) const;
Vector2& operator*=(const Vector2& other);
Vector2 operator*(float value) const;
Vector2 operator*(float value, const Vector2& vector);
Vector2& operator*=(float value);
Vector2 operator/(const Vector2& other) const;
Vector2& operator/=(const Vector2& other);
Vector2 operator/(float value) const;
Vector2 operator/(const float value, const Vector2& vector);
Vector2& operator/=(float value);
Vector2 operator+() const;
Vector2 operator-() const;
bool operator<(const Vector2& other) const;
operator bool() const;
```

## Vector2i

### Members

```c++
union {
    struct {
        int x;
        int y;
    };
    int data[2] {};
};
```

### Constructors

```c++
Vector2i();
explicit Vector2i(const Vector2& vector);
Vector2i(int x, int y);
```

### Static Methods

```c++
static Vector2i all(int value);
static Vector2i zero();
static Vector2i one();
static Vector2i axis_x();
static Vector2i axis_y();
```

### Methods

```c++
Vector2i abs() const;
Vector2i clamp(const Vector2i& min, const Vector2i& max) const;
int manhattan_distance(const Vector2i& to) const;
int length_sqrd() const;
int max_index() const;
int min_index() const;
const int* begin() const;
const int* end() const;
int* begin();
int* end();
int at(const int index) const;
int& at(const int index);
```

### Operators

```c++
int operator[](int index) const;
int& operator[](int index);
bool operator==(const Vector2i& other) const;
bool operator!=(const Vector2i& other) const;
Vector2i operator+(const Vector2i& other) const;
Vector2i& operator+=(const Vector2i& other);
Vector2i operator-(const Vector2i& other) const;
Vector2i& operator-=(const Vector2i& other);
Vector2i operator*(const Vector2i& other) const;
Vector2i& operator*=(const Vector2i& other);
Vector2i operator*(int value) const;
Vector2i operator*(int value, const Vector2i& vector);
Vector2i& operator*=(int value);
Vector2i operator/(const Vector2i& other) const;
Vector2i& operator/=(const Vector2i& other);
Vector2i operator/(int value) const;
Vector2i operator/(int value, const Vector2i& vector);
Vector2i& operator/=(int value);
Vector2i operator%(const Vector2i& other) const;
Vector2i& operator%=(const Vector2i& other);
Vector2i operator%(int value) const;
Vector2i operator&(int value, const Vector2i& vector);
Vector2i& operator%=(int value);
Vector2i operator+() const;
Vector2i operator-() const;
bool operator<(const Vector2i& other) const;
operator bool() const;
```

## Vector3

### Members

```c++
union {
    struct {
        float x;
        float y;
        float z;
    };
    float data[3] {};
};
```

### Constructors

```c++
Vector3();
explicit Vector3(const Vector3i& vector);
Vector3(const Vector2& vector, float z);
Vector3(float x, float y, float z);
```

### Static Methods

```c++
static Vector3 all(float value);
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
float distance_sqrd(const Vector3& to) const;
float distance(const Vector3& to) const;
float manhattan_distance(const Vector3& to) const;
float length_sqrd() const;
float length() const;
Vector3 clamp_length(float min, float max) const;
Vector3 normalize() const;
Vector3 lerp(const Vector3& to, float weight) const;
Vector3 lerp_clamped(const Vector3& to, float weight) const;
float dot(const Vector3& other) const;
Vector3 cross(const Vector3& other) const;
Matrix3 outer(const Vector3& other) const;
Vector3 reflect(const Vector3& normal) const;
Vector3 project(const Vector3& onto) const;
Vector3 inverse() const;
float angle(const Vector3& other) const;
Vector3 translate(const Vector3& by) const;
Vector3 rotate_axis_angle(const Vector3& axis, float angle) const;
Vector3 rotate_quaternion(const Quaternion& quaternion) const;
Vector3 scale(const Vector3& factor) const;
Vector3 shear_x(float angle_y, float angle_z) const;
Vector3 shear_y(float angle_x, float angle_z) const;
Vector3 shear_z(float angle_x, float angle_y) const;
Vector3 transform(const Basis3& by) const;
Vector3 transform(const Transform2& by) const;
Vector3 transform(const Transform3& by, float w = 1.0f) const;
int max_index() const;
int min_index() const;
bool approx_equal(const Vector3& other) const;
bool approx_zero() const;
Vector2 xy() const;
const float* begin() const;
const float* end() const;
float* begin();
float* end();
float at(int index) const;
float& at(int index);
```

### Operators

```c++
float operator[](int index) const;
float& operator[](int index);
bool operator==(const Vector3& other) const;
bool operator!=(const Vector3& other) const;
Vector3 operator+(const Vector3& other) const;
Vector3& operator+=(const Vector3& other);
Vector3 operator-(const Vector3& other) const;
Vector3& operator-=(const Vector3& other);
Vector3 operator*(const Vector3& other) const;
Vector3& operator*=(const Vector3& other);
Vector3 operator*(float value) const;
Vector3 operator*(float value, const Vector3& vector);
Vector3& operator*=(float value);
Vector3 operator/(const Vector3& other) const;
Vector3& operator/=(const Vector3& other);
Vector3 operator/(float value) const;
Vector3 operator/(float value, const Vector3& vector);
Vector3& operator/=(float value);
bool operator<(const Vector3& other) const;
Vector3 operator+() const;
Vector3 operator-() const;
operator bool() const;
```

## Vector3i

### Members

```c++
union {
    struct {
        int x;
        int y;
        int z;
    };
    int data[3] {};
};
```

### Constructors

```c++
Vector3i();
explicit Vector3i(const Vector3& vector);
Vector3i(const Vector2i& vector, int z);
Vector3i(int x, int y, int z);
```
### Static Methods

```c++
static Vector3i all(int value);
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
int manhattan_distance(const Vector3i& to) const;
int length_sqrd() const;
int max_index() const;
int min_index() const;
Vector2i xy() const;
const int* begin() const;
const int* end() const;
int* begin();
int* end();
int at(int index) const;
int& at(int index);
```

### Operators

```c++
int operator[](int index) const;
int& operator[](int index);
bool operator==(const Vector3i& other) const;
bool operator!=(const Vector3i& other) const;
Vector3i operator+(const Vector3i& other) const;
Vector3i& operator+=(const Vector3i& other);
Vector3i operator-(const Vector3i& other) const;
Vector3i& operator-=(const Vector3i& other);
Vector3i operator*(const Vector3i& other) const;
Vector3i& operator*=(const Vector3i& other);
Vector3i operator*(int value) const;
Vector3i operator*(int value, const Vector3i& vector);
Vector3i& operator*=(int value);
Vector3i operator/(const Vector3i& other) const;
Vector3i& operator/=(const Vector3i& other);
Vector3i operator/(int value) const;
Vector3i operator/(int value, const Vector3i& vector);
Vector3i& operator/=(int value);
Vector3i operator%(const Vector3i& other) const;
Vector3i& operator%=(const Vector3i& other);
Vector3i operator%(int val) const;
Vector3i& operator%=(int val);
Vector3i operator+() const;
Vector3i operator-() const;
bool operator<(const Vector3i& other) const;
operator bool() const;
```

## Vector4

### Members

```c++
union {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float data[4] {};
};
```

### Constructors

```c++
Vector4();
explicit Vector4(const Vector4i& vector);
Vector4(const Vector2& vector, const float z, const float w);
Vector4(const Vector3& vector, const float w);
Vector4(float x, float y, float z, float w);
```

### Static Methods

```c++
static Vector4 all(float value);
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
float length_sqrd() const;
float length() const;
Vector4 clamp_length(float min, float max) const;
Vector4 normalize() const;
Vector4 lerp(const Vector4& to, float weight) const;
Vector4 lerp_clamped(const Vector4& to, float weight) const;
float dot(const Vector4& other) const;
Matrix4 outer(const Vector4& other) const;
Vector4 inverse() const;
Vector4 translate(const Vector3& by) const;
Vector4 rotate_axis_angle(const Vector3& axis, float angle) const;
Vector4 rotate_quaternion(const Quaternion& quaternion) const;
Vector4 scale(const Vector3& factor) const;
Vector4 shear_x(float angle_y, float angle_z) const;
Vector4 shear_y(float angle_x, float angle_z) const;
Vector4 shear_z(float angle_x, float angle_y) const;
Vector4 transform(const Transform& by) const;
int max_index() const;
int min_index() const;
bool approx_equal(const Vector4& other) const;
bool approx_zero() const;
Vector2 xy() const;
Vector3 xyz() const;
const float* begin() const;
const float* end() const;
float* begin();
float* end();
float at(int index) const;
float& at(int index);
```

### Operators

```c++
float operator[](int index) const;
float& operator[](int index);
bool operator==(const Vector4& other) const;
bool operator!=(const Vector4& other) const;
Vector4 operator+(const Vector4& other) const;
Vector4& operator+=(const Vector4& other);
Vector4 operator-(const Vector4& other) const;
Vector4& operator-=(const Vector4& other);
Vector4 operator*(const Vector4& other) const;
Vector4& operator*=(const Vector4& other);
Vector4 operator*(float value) const;
Vector4 operator*(float value, const Vector4& vector);
Vector4& operator*=(float value);
Vector4 operator/(const Vector4& other) const;
Vector4& operator/=(const Vector4& other);
Vector4 operator/(float value) const;
Vector4 operator/(float value, const Vector4& vector)
Vector4& operator/=(float value);
bool operator<(const Vector4& other) const;
Vector4 operator+() const;
Vector4 operator-() const;
explicit operator bool() const;
```

## Quaternion

### 

## Matrix2

### Types

```c++
using Column = Vector2;
```

### Members

```c++
union {
    struct {
        float col0_row0;
        float col0_row1;
        float col1_row0;
        float col1_row1;
    };
    std::array<Column, 2> columns;
};
```

### Constructors

```c++
Matrix2();
Matrix2(const Column& column0, const Column& column1);
Matrix2(float col0_row0, float col0_row1, float col1_row0, float col1_row1);
static Matrix2 all(float value);
static Matrix2 zero();
static Matrix2 one();
static Matrix2 identity();
```

### Methods

```c++
float trace() const;
float determinant() const;
float minor(int column, int row) const;
float cofactor_at(int column, int row) const;
Matrix2 cofactor() const;
Matrix2 transpose() const;
Matrix2 adjugate() const;
Matrix2 unchecked_inverse() const;
std::optional<Matrix2> inverse() const;
bool approx_equal(const Matrix2& other) const;
bool approx_zero() const;
Column at(int column) const;
Column& at(int column);
float at(int column, int row) const;
float& at(int column, int row);
const Column& operator[](int column) const;
Column& operator[](int column);
bool operator==(const Matrix2& other) const;
bool operator!=(const Matrix2& other) const;
bool operator<(const Matrix2& other) const;
Matrix2 operator*(const Matrix2& other) const;
Matrix2& operator*=(const Matrix2& other);
Vector2 operator*(const Vector2& vector) const;
Matrix2 operator*(float value) const;
Matrix2& operator*=(float value);
Matrix2 operator/(float value) const;
Matrix2& operator/=(float value);
operator bool() const;
```

## Basis2

### Members

```c++
Matrix2 matrix;
```

### Constructors

```c++
Basis2();
Basis2(const Matrix2& matrix);
static Basis2 from_rotation(float angle);
static Basis2 from_scale(const Vector2& factor);
static Basis2 from_shear(const Vector2& vector);
```

### Methods

```c++
bool valid() const;
Basis2 rotate(float angle) const;
Basis2 rotate_local(float angle) const;
Basis2 scale(const Vector2& factor) const;
Basis2 scale_local(const Vector2& factor) const;
Basis2 shear(const Vector2& vector) const;
Basis2 shear_local(const Vector2& vector) const;
Basis2 transform(const Basis2& by) const;
Basis2 transform_local(const Basis2& by) const;
bool approx_equal(const Basis2& other) const;
float at(int column, int row) const;
float& at(int column, int row);
```

### Operators

```c++
const Matrix2::Column& operator[](int index) const;
bool operator==(const Basis2& other) const;
bool operator!=(const Basis2& other) const;
bool operator<(const Basis2& other) const;
```

## Matrix3

### Types

```c++
using Column = Vector3;
```

### Members

```c++
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
    std::array<Column, 3> columns;
};
```

### Constructors

```c++
Matrix3();
Matrix3(const Column& column1, const Column& column2, const Column& column3)
Matrix3(
    float col0_row0,
    float col0_row1,
    float col0_row2,
    float col1_row0,
    float col1_row1,
    float col1_row2,
    float col2_row0,
    float col2_row1,
    float col2_row2);
static Matrix3 all(float value);
static Matrix3 zero();
static Matrix3 one()
static Matrix3 identity()
```

### Methods

```c++
float trace() const
float determinant() const
float minor_at(int column, int row) const
Matrix3 minor() const
float cofactor_at(int column, int row) const
Matrix3 cofactor() const
Matrix3 transpose() const
Matrix3 adjugate() const
Matrix3 unchecked_inverse() const
std::optional<Matrix3> inverse() const
bool approx_equal(const Matrix3& other) const
bool approx_zero() const
Column at(int column) const
Column& at(int column)
float at(int column, int row) const
float& at(int column, int row)
```

### Operators

```c++
const Column& operator[](int column) const
Column& operator[](int column)
Matrix2 sub_matrix2_at(int column, int row) const
Matrix3 sub_matrix2(int column, int row, const Matrix2& matrix) const
bool operator==(const Matrix3& other) const
bool operator!=(const Matrix3& other) const
bool operator<(const Matrix3& other) const
Matrix3 operator*(const Matrix3& other) const
Matrix3& operator*=(const Matrix3& other)
Vector3 operator*(const Vector3& vector) const
Matrix3 operator*(float value) const
Matrix3& operator*=(float value)
Matrix3 operator/(float value) const
Matrix3& operator/=(float value)
operator bool() const
```

## Transform2

### Members
```c++
Matrix3 matrix;
```

### Constructors
```c++
Transform2();
Transform2(const Matrix3& matrix);
static Transform2 from_basis_translation(const Basis2& basis, const Vector2& pos);
static Transform2 from_translation(const Vector2& pos);
static Transform2 from_basis(const Basis2& basis);
static Transform2 from_rotation(float angle);
static Transform2 from_scale(const Vector2& factor);
static Transform2 from_shear(const Vector2& vector);
```

### Methods
```c++
bool valid() const;
Basis2 basis() const;
Vector2 translation() const;
Transform2 rotate(float angle) const;
Transform2 rotate_local(float angle) const;
Transform2 scale(const Vector2& factor) const;
Transform2 scale_local(const Vector2& factor) const;
Transform2 shear(const Vector2& vector) const;
Transform2 shear_local(const Vector2& vector) const;
Transform2 translate(const Vector2& offset) const;
Transform2 translate_local(const Vector2& offset) const;
Transform2 transform(const Transform2& by) const;
Transform2 transform_local(const Transform2& by) const;
bool approx_equal(const Transform2& other) const;
float at(int column, int row) const;
float& at(int column, int row);
```

### Operators

```cpp
const Vector3& operator[](int column) const;
Vector3& operator[](int column);
bool operator==(const Transform2& other) const;
```



## Matrix4

### Types

```cpp
using Column = Vector4;
```

### Members

```cpp
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
    std::array<Column, 4> columns;
};
```

### Constructors

```cpp
Matrix4();

Matrix4(const Column& column1, const Column& column2, const Column& column3, const Column& column4);
Matrix4(
    float col0_row0,
    float col0_row1,
    float col0_row2,
    float col0_row3,
    float col1_row0,
    float col1_row1,
    float col1_row2,
    float col1_row3,
    float col2_row0,
    float col2_row1,
    float col2_row2,
    float col2_row3,
    float col3_row0,
    float col3_row1,
    float col3_row2,
    float col3_row3);
static Matrix4 all(float value);
static Matrix4 zero();
static Matrix4 one();
static Matrix4 identity();
```

### Methods

```cpp
float trace() const;
Matrix3 minor_matrix_at(int column, int row) const;
float minor_at(int column, int row) const;
Matrix4 minor() const
float determinant() const;
float cofactor_at(int column, int row) const;
Matrix4 cofactor() const;
Matrix4 transpose() const;
Matrix4 adjugate() const;
Matrix4 unchecked_inverse() const;
std::optional<Matrix4> inverse() const;
bool approx_equal(const Matrix4& other) const;
bool approx_zero() const;
const Column& at(int column) const;
Column& at(int column);
float at(int column, int row) const;
float& at(int column, int row);
```

### Operators

```cpp
const Column& operator[](int index) const;
Column& operator[](int index);
bool operator==(const Matrix4& other) const;
bool operator!=(const Matrix4& other) const;
bool operator<(const Matrix4& other) const;
Matrix4 operator*(const Matrix4& other) const;
Matrix4& operator*=(const Matrix4& other);
Vector4 operator*(const Vector4& vector) const;
Matrix4 operator*(float value) const;
Matrix4& operator*=(float value);
Matrix4 operator/(float value) const;
Matrix4& operator/=(float value);
explicit operator bool() const;
```

## Basis3

### Constructors

```cpp
Basis3();
explicit Basis3(const Matrix3& matrix);
static Basis3 from_rotation_axis_angle(const Vector3& axis, float angle);
static Basis3 from_rotation_quaternion(const Quaternion& quaternion);
static Basis3 from_shear_x(float angle_y, float angle_z);
static Basis3 from_shear_y(float angle_x, float angle_z);
static Basis3 from_shear_z(float angle_x, float angle_y);
static Basis3 from_scale(const Vector3& factor)
```

### Methods

```cpp
bool valid() const;
Basis3 rotate_axis_angle(const Vector3& axis, float angle) const;
Basis3 rotate_axis_angle_local(const Vector3& axis, float angle) const;
Basis3 scale(const Vector3& factor) const;
Basis3 scale_local(const Vector3& factor) const;
Basis3 shear_x(float angle_y, float angle_z) const;
Basis3 shear_x_local(float angle_y, float angle_z) const;
Basis3 shear_y(float angle_x, float angle_z) const;
Basis3 shear_y_local(float angle_x, float angle_z) const;
Basis3 shear_z(float angle_x, float angle_y) const;
Basis3 shear_z_local(float angle_x, float angle_y) const;
Basis3 transform(const Basis3& by) const;
Basis3 transform_local(const Basis3& by) const;
Basis3 unchecked_inverse() const;
std::optional<Basis3> inverse() const;
float trace() const;
float determinant() const;
bool approx_equal(const Basis3& other) const;
const Matrix3::Column& at(int column) const;
Matrix3::Column& at(const int column);
float at(int column, int row) const;
float& at(const int column, const int row);
```

### Operators

```cpp
const Matrix3::Column& operator[](int index) const;
Matrix3::Column& operator[](int index);
bool operator==(const Basis3& other) const;
bool operator!=(const Basis3& other) const;
bool operator<(const Basis3& other) const;
```



