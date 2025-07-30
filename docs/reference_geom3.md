# Reference

Reference for NNM math library 3d geometry extension.

## Contents

* [Line3](#Line3)
* [Ray3](#Ray3)

## Line3

### Aliases

```cpp
using Line3f = Line3<float>;
using Line3d = Line3<double>;
```

### Members

```cpp
Vector3 origin;
Vector3 direction;
```

### Constructors

```cpp
Line3();
Line3(const Vector3& origin, const Vector3& direction);
Line3(const Line3<Other>& other);
```

### Static Methods

```cpp
Line3 from_points(const Vector3& point1, const Vector3& point2);
Line3 from_segment(const Segment3& segment);
Line3 from_ray(const Ray3& ray);
Line3 axis_x();
Line3 axis_y();
Line3 axis_z();
Line3 axis_x_offset(Real y, Real z);
Line3 axis_y_offset(Real x, Real z);
Line3 axis_z_offset(Real x, Real y);
```

### Methods

```cpp
Line3 parallel_containing(const Vector3& point) const;
Line3 arbitrary_perpendicular_containing(const Vector3& point) const;
Line3 perpendicular_plane_parallel(const Plane& plane) const;
Line3 normalize() const;
bool collinear(const Ray3& ray) const;
bool collinear(const Segment3& segment) const;
bool coplanar(const Line3& other) const;
bool coplanar(const Ray3& ray) const;
bool coplanar(const Segment3& segment) const;
bool coplanar(const Plane& plane) const;
bool coplanar(const Triangle3& triangle) const;
bool contains(const Vector3& point) const;
Real distance(const Vector3& point) const;
Real distance(const Line3& other) const;
Real distance(const Ray3& ray) const;
bool parallel(const Line3& other) const;
bool parallel(const Ray3& ray) const;
bool perpendicular(const Line3& other) const;
bool perpendicular(const Ray3& ray) const;
bool intersects(const Line3& other) const;
std::optional<Vector3> intersection(const Line3& other) const;
bool intersects(const Ray3& ray) const;
std::optional<Vector3> intersection(const Ray3& ray) const;
Vector3 project_point(const Vector3& point) const;
bool coincident(const Line3& other) const;
Line3 translate(const Vector3& offset) const;
Line3 scale_at(const Vector3& scale_origin, const Vector3& factor) const;
Line3 scale(const Vector3& factor) const;
Line3 rotate_axis_angle_at(const Vector3& rotate_origin, const Vector3& axis, Real angle) const;
Line3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Line3 rotate_quaternion_at(const Vector3& rotate_origin, const Quaternion& quaternion) const;
Line3 rotate_quaternion(const Quaternion& quaternion) const;
Line3 shear_x_at(const Vector3& shear_origin, Real factor_y, Real factor_z) const;
Line3 shear_x(Real factor_y, Real factor_z);
Line3 shear_y_at(const Vector3& shear_origin, Real factor_x, Real factor_z) const;
Line3 shear_y(Real factor_x, Real factor_z) const;
Line3 shear_z_at(const Vector3& shear_origin, Real factor_x, Real factor_y) const;
Line3 shear_z(Real factor_x, Real factor_y) const;
bool approx_equal(const Line3& other) const;
```

### Operators

```cpp
bool operator==(const Line3& other) const;
bool operator!=(const Line3& other) const;
bool operator<(const Line3& other) const;
```

## Ray3

### Aliases

```cpp
using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;
```

### Members

```cpp
Vector3 origin;
Vector3 direction;
```

### Constructors

```cpp
Ray3();
Ray3(const Vector3& origin, const Vector3& direction);
Ray3(const Ray3<Other>& other);
```

### Static Methods

```cpp
Ray3 from_point_to_point(const Vector3& from, const Vector3& to);
```

### Methods

```cpp
Ray3 normalize() const;
bool collinear(const Vector3& point) const;
bool collinear(const Line3& line) const;
bool collinear(const Ray3& other) const;
bool coplanar(const Line3& line) const;
bool coplanar(const Ray3& ray) const;
bool coplanar(const Segment3& segment) const;
bool coplanar(const Plane& plane) const;
bool coplanar(const Triangle3& triangle) const;
bool contains(const Vector3& point) const;
Real distance(const Vector3& point) const;
Real distance(const Line3& line) const;
Real distance(const Ray3& other) const;
bool parallel(const Line3& line) const;
bool parallel(const Ray3& other) const;
bool perpendicular(const Line3& line) const;
bool perpendicular(const Ray3& ray) const;
bool intersects(const Line3& line) const;
std::optional<Vector3> intersection(const Line3& line) const;
bool intersects(const Ray3& other) const;
std::optional<Vector3> intersection(const Ray3& other) const;
Vector3 project_point(const Vector3& point) const;
Ray3 translate(const Vector3& offset) const;
Ray3 scale_at(const Vector3& scale_origin, const Vector3& offset) const;
Ray3 scale(const Vector3& factor) const;
Ray3 rotate_axis_angle_at(const Vector3& rotate_origin, const Vector3& axis, Real angle) const;
Ray3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Ray3 rotate_quaternion_at(const Vector3& rotate_origin, const Quaternion& quaternion) const;
Ray3 rotate_quaternion(const Quaternion& quaternion) const;
Ray3 shear_x_at(const Vector3& shear_origin, Real factor_y, Real factor_z) const;
Ray3 shear_x(Real factor_y, Real factor_z) const;
Ray3 shear_y_at(const Vector3& shear_origin, Real factor_x, Real factor_z) const;
Ray3 shear_y(Real factor_x, Real factor_z) const;
Ray3 shear_z_at(const Vector3& shear_origin, Real factor_x, Real factor_y) const;
Ray3 shear_z(Real factor_x, Real factor_y) const;
bool approx_equal(const Ray3& other) const;
```

### Operators

```cpp
bool operator==(const Ray3& other) const;
bool operator!=(const Ray3& other) const;
bool operator<(const Ray3& other) const;
```

## Segment3

### Aliases

```cpp
using Segment3f = Segment3<float>;
using Segment3d = Segment3<double>;
```

### Members

```cpp
Vector3 start;
Vector3 end;
```

### Constructors

```cpp
```

