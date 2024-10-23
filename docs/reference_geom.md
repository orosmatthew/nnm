# Reference

Reference for NNM math library geometry extension.

## Contents

* [Line2](#Line2)
* [Ray2](#Ray2)
* [Segment2](#Segment2)

## Line2

### Aliases

```cpp
using Line2f = Line2<float>;
using Line2d = Line2<double>;
```

### Members

```c++
Vector2 origin;
Vector2 direction;
```

### Constructors

```c++
Line2();
Line2(const Vector2& origin, const Vector2& direction);
```

### Static Methods

```c++
static Line2 from_points(const Vector2<Real>& point1, const Vector2<Real>& point2);
static Line2 from_segment(const Segment2& segment);
static Line2 from_ray(const Ray2& ray);
static Line2 from_tangent_at(const Circle2& circle, Real angle);
static Line2 axis_x();
static Line2 axis_y();
static Line2 axis_x_offset(Real y);
static Line2 axis_y_offset(Real x);
static Line2 from_point_slope(const Vector2& point, Real slope);
```

### Methods

```c++
Line2 parallel_containing(const Vector2& point) const;
Line2 arbitrary_perpendicular_containing(const Vector2& point) const;
Line2 normalize() const;
bool approx_contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& other) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
bool approx_parallel(const Line2& other) const;
bool approx_parallel(const Ray2& ray) const;
bool approx_parallel(const Segment2& segment) const;
bool approx_perpendicular(const Line2& other) const;
bool approx_perpendicular(const Ray2& ray) const;
bool approx_perpendicular(const Segment2& segment) const;
Vector2 unchecked_intersection(const Line2& other) const;
std::optional<Vector2> intersection(const Line2& other) const;
bool intersects(const Ray2& ray) const;
std::optional<Vector2> intersection(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<Vector2> intersection(const Segment2& segment) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool approx_tangent(const Circle2& circle) const;
Real project_point_scalar(const Vector2& point) const;
Vector2 project_point(const Vector2& point) const;
Real unchecked_slope() const;
std::optional<Real> slope() const;
bool approx_coincident(const Line2& other) const;
Line2 translate(const Vector2& by) const;
Line2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Line2 scale(const Vector2& by) const;
Line2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Line2 rotate(Real angle) const;
Line2 shear_x_at(const Vector2& shear_origin, Real angle_y) const;
Line2 shear_x(Real angle_y) const;
Line2 shear_y_at(const Vector2& shear_origin, Real angle_x) const;
Line2 shear_y(Real angle_x) const;
```

### Operators

```c++
bool operator==(const Line2& other) const;
bool operator!=(const Line2& other) const;
bool operator<(const Line2& other) const;
```

## Ray2

### Aliases

```cpp
using Ray2f = Ray2<float>;
using Ray2d = Ray2<double>;
```

### Members

```cpp
Vector2 origin;
Vector2 direction;
```

### Constructors

```cpp
Ray2();
Ray2(const Vector2& origin, const Vector2& direction);
```

### Static Methods

```cpp
static Ray2 from_point_to_point(const Vector2& from, const Vector2& to);
```

### Methods

```cpp
Ray2 normalize() const;
bool approx_contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
bool approx_parallel(const Line2& line) const;
bool approx_parallel(const Ray2& other) const;
bool approx_parallel(const Segment2& segment) const;
bool approx_perpendicular(const Line2& line) const;
bool approx_perpendicular(const Ray2& other) const;
bool approx_perpendicular(const Segment2& segment) const;
bool intersects(const Line2& line) const;
std::optional<Vector2> intersection(const Line2& line);
bool intersects(const Ray2& other) const;
std::optional<Vector2> intersection(const Ray2& other) const;
bool intersects(const Segment2& segment) const;
std::optional<Vector2> intersection(const Segment2& segment) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool approx_tangent(const Circle2& circle) const;
Real project_point_scalar(const Vector2& point) const;
Vector2 project_point(const Vector2& point) const;
Ray2 translate(const Vector2& by) const;
Ray2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Ray2 scale(const Vector2& by) const;
Ray2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Ray2 rotate(Real angle) const;
Ray2 shear_x_at(const Vector2& shear_origin, Real angle_y) const;
Ray2 shear_x(Real angle_y) const;
Ray2 shear_y_at(const Vector2& shear_origin, Real angle_x) const;
Ray2 shear_y(Real angle_x) const;
```

### Operators

```cpp
bool operator==(const Ray2& other) const;
bool operator!=(const Ray2& other) const;
bool operator<(const Ray2& other) const;
```

## Segment2

### Aliases

```cpp
using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;
```

### Members

```cpp
Vector2 from;
Vector2 to;
```

### Constructors

```cpp
Segment2();
Segment2(const Vector2& from, const Vector2& to);
```

### Methods

```cpp
bool approx_collinear(const Vector2& point) const;
bool approx_collinear(const Line2& line) const;
bool approx_collinear(const Ray2& ray) const;
bool approx_collinear(const Segment2& other) const;
bool approx_contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& other) const;
Vector2 direction_unnormalized() const;
Vector2 direction() const;
bool approx_parallel(const Line2& line) const;
bool approx_parallel(const Ray2& ray) const;
bool approx_parallel(const Segment2& other) const;
bool approx_perpendicular(const Line2& line) const;
bool approx_perpendicular(const Ray2& ray) const;
bool approx_perpendicular(const Segment2& other) const;
bool intersects(Line2& line) const;
std::optional<Vector2> intersection(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<Vector2> intersection(const Ray2& ray) const;
bool intersects(const Segment2& other) const;
std::optional<Vector2> intersection(const Segment2& other) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool approx_tangent(const Circle2& circle) const;
Vector2 project_point(const Vector2& point) const;
Real unchecked_slope() const;
std::optional<Real> slope() const;
Real length_sqrd() const;
Real length() const;
Vector2 midpoint() const;
Segment2 translate(const Vector2& by) const;
Segment2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Segment2 scale(const Vector2& by) const;
Segment2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Segment2 rotate(Real angle) const;
Segment2 shear_x_at(const Vector2& shear_origin, Real angle_y) const;
Segment2 shear_x(Real angle_y) const;
Segment2 shear_y_at(const Vector2& shear_origin, Real angle_x) const;
Segment2 shear_y(Real angle_x) const;
bool approx_equal(const Segment2& other) const;
```

### Operators

```cpp
bool operator==(const Segment2& other) const;
bool operator!=(const Segment2& other) const;
bool operator<(const Segment2& other) const;
```

## Circle2

### Aliases

```cpp
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;
```

### Members

```cpp
Vector2 center;
Real radius;
```

### Constructors

```cpp
Circle2();
Circle2(const Vector2& center, Real radius);
```

### Methods

```cpp
Real circumference() const;
Real perimeter() const;
Real area() const;
Real diameter() const;
bool contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Vector2<Real> point_at(Real angle) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersections(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool intersects(const Circle2& other) const;
Vector2 intersect_depth(const Circle2& other) const;
bool approx_tangent(const Line2& line) const;
bool approx_tangent(const Ray2& ray) const;
bool approx_tangent(const Segment2& segment) const;
bool approx_tangent(const Circle2& circle) const;
Circle2 translate(const Vector2& by) const;
Circle2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Circle2 rotate(Real angle) const;
Circle2 scale_at(const Vector2& scale_origin, Real by) const;
Circle2 scale(Real by) const;
bool approx_equal(const Circle2& other) const;
```

### Operators

```cpp
bool operator==(const Circle2& other) const;
bool operator!=(const Circle2& other) const;
bool operator<(const Circle2& other) const;
```

## Triangle2

### Aliases

```cpp
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;
```

### Members

```cpp
Vector2<Real> vertices[3];
```

### Constructors

```cpp
Triangle2();
Triangle2(const Vector2& vertex0, const Vector2& vertex1, const Vector2& vertex2);
```

### Methods

```cpp
Segment2 edge(int index) const;
Vector2 centroid() const;
Vector2 circumcenter() const;
Real perimeter() const;
Vector2 incenter() const;
Vector2 orthocenter() const;
Real area() const;
Segment2 median(int index) const;
Line2 perpendicular_bisector(int index) const;
Real angle(int index) const;
Line2 angle_bisector(int index) const;
Segment2 altitude(int index) const;
Vector2 lerp_point(const Vector3& weights) const;
Vector3 barycentric(const Vector2& point) const;
bool contains(const Vector2& point) const;
bool intersects(const Triangle2& other) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersectioins(const Line2& line) const;
bool intersects(cosnt Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool approx_equilateral() const;
```

