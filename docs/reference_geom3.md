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
```

### Static Methods

```cpp
Line3 from_points(const Vector3& point1, const Vector3& point2);
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
Line3 normalize() const;
bool approx_contains(const Vector3& point) const;
Real distance(const Vector3& point) const;
Real distance(const Line3& other) const;
Real distance(const Ray3& ray) const;
bool approx_parallel(const Line3& other) const;
bool approx_parallel(const Ray3& ray) const;
bool approx_perpendicular(const Line3& other) const;
bool approx_perpendicular(const Ray3& ray) const;
bool approx_intersects(const Line3& other) const;
std::optional<Vector3> approx_intersection(const Line3& other) const;
bool approx_intersects(const Ray3& ray) const;
std::optional<Vector3> approx_intersection(const Ray3& ray) const;
Vector3 project_point(const Vector3& point) const;
bool approx_coincident(const Line3& other) const;
Line3 translate(const Vector3& by) const;
Line3 scale_at(const Vector3& scale_origin, const Vector3& by) const;
Line3 scale(const Vector3& by) const;
Line3 rotate_axis_angle_at(const Vector3& rotate_origin, const Vector3& axis, Real angle) const;
Line3 rotate_axis_angle(const Vector3& axis, Real angle) const;
Line3 rotate_quaternion_at(const Vector3& rotate_origin, const Quaternion& quaternion) const;
Line3 rotate_quaternion(const Quaternion& quaternion) const;
Line3 shear_x_at(const Vector3& shear_origin, Real angle_y, Real angle_z) const;
Line3 shear_x(Real angle_y, Real angle_z);
Line3 shear_y_at(const Vector3& shear_origin, Real angle_x, Real angle_z) const;
Line3 shear_y(Real angle_x, Real angle_z) const;
Line3 shear_z_at(const Vector3& shear_origin, Real angle_x, Real angle_y) const;
Line3 shear_z(Real angle_x, Real angle_y) const;
bool approx_equal(const Line3& other) const;
```

### Operators

```cpp
bool operator==(const Line3& other) const;
bool operator!=(const Line3& other) const;
bool operator<(const Line3& other) const;
```

