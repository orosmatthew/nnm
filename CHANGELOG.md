# Changelog

## v0.5.0

### Breaking Changes

* Move `Vector2i` and `Vector3i` hash functors out of std. They are now under `Vector2i::Hash` and `Vector3i::Hash`
  respectively.
* Replace shear methods input from angles to shear factors. This allows for `constexpr` and is computationally less
  expensive.
* Rename `Quaternion` `axis(const Quaternion&)` and `angle(Quaternion&)` to `axis_to(const Quaternion&)` and
  `angle_to(const Quaternion&)` respectively to avoid confusion with `axis()` and `angle()` methods.

### New Features

* Add doc-comments to all functions and methods.
* Significantly more `constexpr`. Almost all functions and methods are `constexpr` other than those that require
  trigonometric or square-root functions.
* Hash functions for `Vector2i` and `Vector3i` now use an improved method based on Boost's `hash_combine` which should
  improve hashing quality.

## v0.4.0

### Breaking Changes

* Default template parameter for `Real` type is no longer specified as `float`.
* Integer templates for various functions and classes such as `Vector2i` and `Vector3i` are now templated to allow for
  various integral types.
* Removal of unions in classes to properly follow C++ standards which does not allow for multiple active union types at
  once.
* Renamed `Real Vector2::angle(const Vector2& to)` to `Real Vector2::angle_between(const Vector2& other) const`.
* Index types for vector and matrix classes are now `uint8_t` instead of `int`.

### New Features

* Integral functions and classes such as `Vector2i` and `Vector3i` are now templated to allow for various integer types.

#### New `Vector2i` and `Vector3i` aliases

* `using Vector2ii = Vector2i<int>`

* `using Vector2i8 = Vector2i<int8_t>`

* `using Vector2i16 = Vector2i<int16_t>`
* `using Vector2i32 = Vector2i<int32_t>`
* `using Vector2i64 = Vector2i<int64_t>`
* `using Vector2iu = Vector2i<unsigned int>`
* `using Vector2u8 = Vector2i<uint8_t>`
* `using Vector2u16 = Vector2i<uint16_t>`
* `using Vector2u32 = Vector2i<uint32_t>`
* `using Vector2u64 = Vector2i<uint64_t>`


* similar aliases for `Vector3i`

#### New functions

* `Real modf(Real a, Real b)`
* `Int mod(Int a, Int b)`
* `Real remf(Real a, Real b)`
* `Int rem(Int a, Int b)`
* `Real normalize_angle(Real angle)`
* `bool angle_in_range(Real angle, Real from, Real to)`

#### New methods

* `Vector2`

    * `Vector2 direction_unnormalized(const Vector2& to) const`
    * `Real angle_to(const Vector2& to) const`
    * `bool approx_parallel(const Vector2& other) const`
    * `bool approx_perpendicular(const Vector2& other) const`
    * `Vector2 arbitrary_perpendicular() const`
    * `Vector2 rotate_at(const Vector2& origin, Real angle) const`
    * `Vector2 scale_at(const Vector2& origin, const Vector2& factor) const`
    * `Vector2 shear_x_at(const Vector2& origin, Real angle_y) const`
    * `Vector2 shear_y_at(const Vector2& origin, Real angle_x) const`
    * `Vector2 transform_at(const Vector2& origin, const Basis2& by) const`
    * `Vector2 transform_at(const Vector2& origin, const Transform2& by, Real z = 1)`
    * `Real max() const`
    * `Real min() const`

* `Vector2i`

    * `Int dot(const Vector2i& other) const`
    * `Int cross(const Vector2i& other) const`
    * `bool parallel(const Vector2i& other) const`
    * `bool perpendicular(const Vector2i& other) const`
    * `Vector2i arbitrary_perpendicular() const`
    * `Int max() const`
    * `Int min() const`

* `Vector3`

    * `Vector3 direction_unnormalized(const Vector3& to) const`
    * `bool approx_parallel(const Vector3& other) const`
    * `bool approx_perpendicular(const Vector3& other) const`
    * `Vector3 arbitrary_perpendicular() const`
    * `Vector3 rotate_axis_angle_at(const Vector3& origin, const Vector3& axis, Real angle) const`
    * `Vector3 rotate_quaternion_at(const Vector3& origin, const Quaternion& quaternion) const`
    * `Vector3 scale_at(const Vector3& origin, const Vector3& factor) const`
    * `Vector3 shear_x_at(const Vector3& origin, Real angle_y, Real angle_z) const`
    * `Vector3 shear_y_at(const Vector3& origin, Real angle_x, Real angle_z) const`
    * `Vector3 shear_z_at(const Vector3& origin, Real angle_x, Real angle_y) const`
    * `Vector3 transform_at(const Vector3& origin, const Basis3& by) const`
    * `Vector3 transform_at(const Vector2& origin, const Transform2& by) const`
    * `Vector3 transform_at(const Vector3& origin, const Transform3& by, Real w = 1) const`
    * `Real max() const`
    * `Real min() const`

* `Vector3i`

    * `Int dot(const Vector3i& other) const`
    * `Vector3i cross(const Vector3i& other) const`
    * `bool parallel(const Vector3i& other) const`
    * `bool perpendicular(const Vector3i& other) const`
    * `Vector3i arbitrary_perpendicular() const`
    * `Int max() const`
    * `Int min() const`
* `Vector4`

    * `static Vector4 from_quaternion(const Quaternion& quaternion)`
    * `Vector4 transform_at(const Vector3& origin, const Transform3& by) const`
    * `Real max() const`
    * `Real min() const`

## v0.3.1

- Replace double literals with casted integers
- Explicitly declare template types in more places to fix some compile issues

## v0.3.0

- Fix compiling with MSVC C++ greater than 17.
- Add perspective/orthographic projection variants for handedness and normalization. See README for an explanation as to
  which to use.
- Rename near/far to prevent clash with `windows.h`

## v0.2.0

* Added constexpr to trivial cases such as functions, class constructors, and methods that don't use index operators (
  mostly for vectors). I am unable to use constexpr in more places because of the inability to mark accessors (at() and
  operator[]) as constexpr due to the inability to arbitrarily switch active union members. If I find a workaround for
  this that is not too invasive then I can look into it.

## v0.1.1 (Pre-release)

* Add version info to CMakeLists.

## v0.1.0 (Pre-release)

* Initial release of NNM.