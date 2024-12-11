# Reference

Reference for NNM math library geometry extension.

## Contents

* [Line2](#Line2)
* [Ray2](#Ray2)
* [Segment2](#Segment2)
* [Arc2](#Arc2)
* [Circle2](#Circle2)
* [Triangle2](#Triangle2)
* [Rectangle2](#Rectangle2)
* [AlignedRectangle2](#AlignedRectangle2)

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
static Line2 from_points(const Vector2& point1, const Vector2& point2);
static Line2 from_segment(const Segment2& segment);
static Line2 from_ray(const Ray2& ray);
static std::optional<Line2> from_tangent(const Arc2& arc, Real angle);
static Line2 from_tangent(const Circle2& circle, Real angle);
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
bool approx_collinear(const Ray2& ray) const;
bool approx_collinear(const Segment2& segment) const;
bool approx_contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& other) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& rectangle) const;
Real distance(const AlignedRectangle2& rectangle) const;
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
bool intersects(const Arc2& arc) const;
std::optional<std::array<Vector2, 2>> intersections(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const AlignedRectangle2& rectangle) const;
bool approx_tangent(const Arc2& arc) const;
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
bool approx_collinear(const Vector2& point) const;
bool approx_collinear(const Line2& line) const;
bool approx_collinear(const Ray2& other) const;
bool approx_collinear(const Segment2& segment) const;
bool approx_contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& rectangle) const;
Real distance(const AlignedRectangle2& rectangle) const;
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
bool intersects(const Arc2& arc) const;
std::optional<std::array<Vector2, 2>> intersections(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const AlignedRectangle2& rectangle) const;
bool approx_tangent(const Arc2& arc) const;
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
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& rectangle) const;
Real distance(const AlignedRectangle2& rectangle) const;
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
bool intersects(const Arc2& arc) const;
std::optional<std::array<Vector2, 2>> intersections(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) const;
std::optional<std::array<Vector2, 2>> intersections(const AlignedRectangle2& rectangle) const;
bool approx_tangent(const Arc2& arc) const;
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
bool approx_coincident(const Segment2& other) const;
bool approx_equal(const Segment2& other) const;
```

### Operators

```cpp
bool operator==(const Segment2& other) const;
bool operator!=(const Segment2& other) const;
bool operator<(const Segment2& other) const;
```

## Arc2

### Aliases

```cpp
using Arc2f = Arc2<float>;
using Arc2d = Arc2<double>;
```

### Members

```cpp
Vector2 pivot;
Vector2 from;
Real angle;
```

### Constructors

```cpp
Arc2();
Arc2(const Vector2& pivot, const Vector2& from, Real angle);
```

### Static Methods

```cpp
static Arc2 from_pivot_radius_angle_to_angle(const Vector2& pivot, Real radius, Real angle_from, Real angle_to);
static Arc2 from_points_unchecked(const Vector2& from, const Vector2& through, const Vector2& to);
static std::optional<Arc2> from_points(const Vector2& from, const Vector2& through, const Vector2& to);
```

### Methods

```cpp
Arc2 normalize_angle() const;
Real radius() const;
Real radius_sqrd() const;
Real angle_from() const;
REal angle_to() const;
bool approx_contains(const Vector2& point) const;
Vector2 unchecked_point_at(Real angle) const;
std::optional<Vector2> point_at(Real angle) const;
Vector2 to() const;
Real length() const;
Real length_sqrd() const;
Vector2 midpoint() const;
Vector2 project_point(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& other) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& rectangle) const;
bool distance(const AlignedRectangle2& rectangle) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersections(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool intersects(const Arc2& other) const;
std::optional<std::array<Vector2, 2>> intersections(const Arc2& other) const;
bool intersects(const Circle2& circle) const;
std::optional<std::array<Vector2, 2>> intersections(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) const;
bool approx_tangent(const Line2& line) const;
bool approx_tangent(const Ray2& ray) const;
bool approx_tangent(const Segment2& segment) const;
bool approx_tangent(const Arc2& other) const;
bool approx_tangent(const Circle2& circle) const;
Arc2 translate(const Vector2& by) const;
Arc2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Arc2 scale(const Vector2& by) const;
Arc2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Arc2 rotate(Real angle) const;
bool approx_coincident(const Arc2& other) const;
bool approx_equal(const Arc2& other) const;
```

### Operators

```cpp
bool operator==(const Arc2& other) const;
bool operator!=(const Arc2& other) const;
bool operator<(const Arc2& other) const;
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

### Static Methods

```cpp
static Circle2 from_center_point(const Vector2& center, const Vector2& point);
static Circle2 from_points_unchecked(const Vector2& point1, const Vector2& point2, const Vector2& point3);
static std::optional<Circle2> from_points(const Vector2& point1, const Vector2& point2, const Vector2& point3);
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
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& other) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& rectangle) const;
Real distance(const AlignedRectangle2& rectangle) const;
Vector2 point_at(Real angle) const;
Vector2 normal_at(Real angle) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersections(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool intersects(const Arc2& arc) const;
std::optional<std::array<Vector2, 2>> intersections(const Arc2& arc) const;
bool intersects(const Circle2& other) const;
std::optional<Vector2> intersect_depth(const Circle2& other) const;
bool intersects(const Triangle2& triangle) const;
std::optional<Vector2> intersect_depth(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<Vector2> intersect_depth(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) const;
std::optional<Vector2> intersect_depth(const AlignedRectangle2& rectangle) const;
bool approx_tangent(const Line2& line) const;
bool approx_tangent(const Ray2& ray) const;
bool approx_tangent(const Segment2& segment) const;
bool approx_tangent(const Arc2& arc) const;
bool approx_tangent(const Circle2& circle) const;
Circle2 translate(const Vector2& by) const;
Circle2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Circle2 rotate(Real angle) const;
Circle2 scale_at(const Vector2& scale_origin, Real by) const;
Circle2 scale(Real by) const;
bool approx_coincident(const Circle2& other) const;
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
Vector2 vertices[3];
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
Vector2 normal(int index) const;
Segment2 altitude(int index) const;
Vector2 lerp_point(const Vector3& weights) const;
Vector3 barycentric(const Vector2& point) const;
Circle2 circumcircle() const;
Circle2 incircle() const;
bool contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& other) const;
Real distance(const Rectangle2& rectangle) const;
Real distance(const AlignedRectangle2& rectangle) const;
bool intersects(const Triangle2& other) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersectioins(const Line2& line) const;
bool intersects(cosnt Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool intersects(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<Vector2> intersect_depth(const Circle2& circle) const;
bool intersects(const Triangle2& other) const;
std::optional<Vector2> intersect_depth(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<Vector2> intersect_depth(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle2& rectangle) conswt;
std::optional<Vector2> intersect_depth(const AlignedRectangle2& rectangle) const;
bool approx_equilateral() const;
bool approx_similar() const;
bool approx_right() const;
Triangle2 translate(const Vector2& by) const;
Triangle2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Triangle2 rotate(Real angle) const;
Triangle2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Triangle2 scale(const Vector2& by) const;
Triangle2 shear_x_at(const Vector2& shear_origin, Real angle_y) const;
Triangle2 shear_x(Real angle_y) const;
Triangle2 shear_y_at(const Vector2& shear_origin, Real angle_x) const;
Triangle2 shear_y(Real angle_x) const;
bool approx_coincident(const Triangle2& other) const;
bool approx_equal(const Triangle2& other) const;
```

### Operators

```cpp
bool operator==(const Triangle2& other) const;
bool operator!=(const Triangle2& other) const;
bool operator<(const Triangle2& other) const;
```

## Rectangle2

### Aliases

```cpp
using Rectangle2f = Rectangle2<float>;
using Rectangle2d = Rectangle2<double>;
```

### Members

```cpp
Vector2 center;
Vector2 size;
Real angle;
```

### Constructors

```cpp
Rectangle2();
Rectangle2(const Vector2& center, const Vector2& size, Real angle);
```

### Methods

```cpp
Vector2 vertex_nx_ny() const;
Vector2 vertex_nx_py() const;
Vector2 vertex_px_ny() const;
Vector2 vertex_px_py() const;
Segment2 edge_nx() const;
Segment2 edge_ny() const;
Segment2 edge_px() const;
Segment2 edge_py() const;
Vector2 normal_nx() const;
Vector2 normal_ny() const;
Vector2 normal_px() const;
Vector2 normal_py() const;
Real area() const;
Real perimeter() const;
bool contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle2& other) const;
Real distance(const AlignedRectangle2& rectangle) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersections(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersects(const Segment2& segment) const;
bool intersects(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<Vector2> intersect_depth(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<Vector2> intersect_depth(const Triangle2& triangle) const;
bool intersects(const Rectangle2& other) const;
std::optional<Vector2> intersect_depth(const Rectangle2& other) const;
bool intersects(const AlignedRectangle2& rectangle) const;
std::optional<Vector2> intersect_depth(const AlignedRectangle2& rectangle) const;
Rectangle2 translate(const Vector2& by) const;
Rectangle2 rotate_at(const Vector2& rotate_origin, Real angle) const;
Rectangle2 rotate(const Real angle) const;
Rectangle2 scale_at(const Vector2& scale_origin, const Vector2& by) const;
Rectangle2 scale(const Vector2& by) const;
bool approx_coincident(const Rectangle2& other) const;
bool approx_equal() const;
```

### Operators

```cpp
bool operator==(const Rectangle2& other) const;
bool operator!=(const Rectangle2& other) const;
bool operator<(const Rectangle2& other) const;
```

## AlignedRectangle2

### Aliases

```cpp
using AlignedRectangle2f = AlignedRectangle2<float>;
using AlignedRectangle2d = AlignedRectangle2<double>;
```

### Members

```cpp
Vector2 min;
Vector2 max;
```

### Constructors

```cpp
AlignedRectangle2();
AlignedRectangle2(const Vector2& min, const Vector2& max);
```

### Static Methods

```cpp
static AlignedRectangle2 from_bounding_points(const Vector2& point1, const Vector2& point2);
static AlignedRectangle2 from_bounding_segment2(const Segment2& segment);
static AlignedRectangle2 from_bounding_arc(const Arc2& arc);
static AlignedRectangle2 from_bounding_circle(const Circle2& circle);
static AlignedRectangle2 from_bounding_triangle(const Triangle2& triangle);
static AlignedRectangle2 from_bounding_rectangle(const Rectangle2& rectangle);
```

### Methods

```cpp
Vector2 vertex_nx_ny() const;
Vector2 vertex_nx_py() const;
Vector2 vertex_px_ny() const;
Vector2 vertex_px_py() const;
Segment2 edge_nx() const;
Segment2 edge_ny() const;
Segment2 edge_px() const;
Segment2 edge_py() const;
Vector2 normal_nx() const;
Vector2 normal_ny() const;
Vector2 normal_px() const;
Vector2 normal_py() const;
Vector2 size() const;
Real area() const;
Real perimeter() const;
bool contains(const Vector2& point) const;
Real signed_distance(const Vector2& point) const;
Real distance(const Vector2& point) const;
Real distance(const Line2& line) const;
Real distance(const Ray2& ray) const;
Real distance(const Segment2& segment) const;
Real distance(const Arc2& arc) const;
Real distance(const Circle2& circle) const;
Real distance(const Triangle2& triangle) const;
Real distance(const Rectangle& rectangle) const;
Real distance(const AlignedRectangle2& other) const;
bool intersects(const Line2& line) const;
std::optional<std::array<Vector2, 2>> intersections(const Line2& line) const;
bool intersects(const Ray2& ray) const;
std::optional<std::array<Vector2, 2>> intersections(const Ray2& ray) const;
bool intersects(const Segment2& segment) const;
std::optional<std::array<Vector2, 2>> intersections(const Segment2& segment) const;
bool intersects(const Arc2& arc) const;
bool intersects(const Circle2& circle) const;
std::optional<Vector2> intersect_depth(const Circle2& circle) const;
bool intersects(const Triangle2& triangle) const;
std::optional<Vector2> intersect_depth(const Triangle2& triangle) const;
bool intersects(const Rectangle2& rectangle) const;
std::optional<Vector2> intersect_depth(const Rectangle2& rectangle) const;
bool intersects(const AlignedRectangle& other) const;
std::optional<Vector2> intersect_depth(const AlignedRectangle2& other) const;
bool approx_equal(const AlignedRectangle2& rectangle) const;
```

### Operators

```cpp
bool operator==(const AlignedRectangle2& other) const;
bool operator!=(const AlignedRectangle2& other) const;
bool operator<(const AlignedRectangle2& other) const;
```
