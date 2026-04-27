# NNM - No Nonsense Math

NNM is a header-only C++17 math and geometry library geared toward graphics, games, simulations, and other code that
needs readable vector math without a large dependency footprint.

It is meant to feel lightweight and explicit: familiar vector, matrix, transform, quaternion, point, and shape types;
clear method names; no SIMD-specific code paths; and only modest use of templates. The style is inspired by object-first
math APIs such as Godot's, while staying small enough to drop into a project.

## Quick Example

```cpp
#define NNM_ENABLE_BOUNDS_CHECKS // optional, throws std::out_of_range from checked accessors
#include <nnm/nnm.hpp>

nnm::Transform3f object_to_clip(
    const nnm::Vector3f& position,
    const nnm::Vector2f& rotation)
{
    constexpr float aspect_ratio = nnm::Vector2f(16.0f, 9.0f).aspect_ratio();
    constexpr float fov = nnm::radians(90.0f);

    const auto projection =
        nnm::Transform3f::from_perspective_left_hand_neg1to1(
            fov, aspect_ratio, 0.1f, 100.0f);

    const auto view =
        nnm::Transform3f::from_translation(position)
            .rotate_axis_angle(nnm::Vector3f::axis_y(), rotation.y)
            .rotate_axis_angle(nnm::Vector3f::axis_x(), rotation.x);

    const auto model =
        nnm::Transform3f::from_scale(nnm::Vector3f::all(0.5f));

    return model.transform(view).transform(projection);
}
```

Geometry is split into separate convenience headers:

```cpp
#include <nnm/nnm.hpp>
#include <nnm/geom2.hpp>

const nnm::Circle2f circle({0.0f, 0.0f}, 4.0f);
const nnm::Segment2f segment({-5.0f, 1.0f}, {5.0f, 1.0f});

if (circle.intersects(segment)) {
    const nnm::PointSet<nnm::Point2f, 2> hits =
        circle.edge_intersections(segment);
}
```

## What's Included

The main math header, `nnm/nnm.hpp`, includes:

| Category             | Types                                                   |
|----------------------|---------------------------------------------------------|
| Vectors              | `Vector2`, `Vector2i`, `Vector3`, `Vector3i`, `Vector4` |
| Points               | `Point2`, `Point3`                                      |
| Matrices             | `Matrix2`, `Matrix3`, `Matrix4`                         |
| Bases and transforms | `Basis2`, `Transform2`, `Basis3`, `Transform3`          |
| Rotations            | `Quaternion`                                            |
| Utility containers   | `PointSet`                                              |

The geometry headers add shape types and interaction methods:

| Header          | Types                                                                                                     |
|-----------------|-----------------------------------------------------------------------------------------------------------|
| `nnm/geom2.hpp` | `Line2`, `Ray2`, `Segment2`, `Circle2`, `Triangle2`, `Rectangle2`, `AlignedRectangle2`                    |
| `nnm/geom3.hpp` | `Line3`, `Ray3`, `Segment3`, `Plane`, `Triangle3`, `Rectangle3`, `Sphere`, `AlignedBox`, `Box`, `Frustum` |

Most floating-point types are templated on `Real` and have `float`/`double` aliases such as `Vector3f`,
`Vector3d`, `Triangle2f`, and `SphereD`. Integer vectors are templated on `Int` and provide aliases such as
`Vector2i32`, `Vector2u64`, `Vector3i16`, and `Vector3iu`.

## Highlights

* Header-only C++17 library with no compiled library artifact.
* No third-party dependencies.
* Readable class and method names with minimal macro usage.
* Broad `constexpr` coverage where the underlying math permits it.
* Common scalar utilities such as `pi`, `epsilon`, `approx_equal`, `clamp`, `lerp`, `radians`, `degrees`,
  `normalize_angle`, `euclidean_mod`, and trigonometric wrappers.
* Vector and point operations for dot/cross products, normalization, distances, component-wise math, projection,
  interpolation, transforms, and iteration with `begin()`/`end()`.
* Matrix, basis, and transform helpers for translation, rotation, scale, shear, inverses, determinants, composition,
  and 2D/3D projection matrices.
* Geometry helpers for containment, signed distance, closest distance, intersections, intersection points, penetration
  depth for several 2D shapes, and surface/edge intersection sets.
* Optional bounds checking via `NNM_ENABLE_BOUNDS_CHECKS`.
* `Vector2i::Hash` and `Vector3i::Hash` hash functors for use with unordered containers.

Full generated API documentation is available at [nnm.pixeled.site](https://nnm.pixeled.site). You can also build the
documentation locally with Doxygen using the included `Doxyfile`.

## Installation

The simplest option is to copy the `include/nnm` directory into your project and include the headers you need:

```cpp
#include <nnm/nnm.hpp>   // core math
#include <nnm/geom2.hpp> // optional 2D geometry
#include <nnm/geom3.hpp> // optional 3D geometry
```

For CMake projects, add NNM as a subdirectory and link the interface target:

```cmake
add_subdirectory(external/nnm)
target_link_libraries(your_target PRIVATE nnm)
```

The project currently requires CMake 3.10 or newer and a C++17 compiler.

## Configuration

NNM can be used without any configuration macros. These optional macros may be defined before including NNM headers:

```cpp
#define NNM_ENABLE_BOUNDS_CHECKS
#define NNM_EPSILON_SCALE 100
#include <nnm/nnm.hpp>
```

`NNM_ENABLE_BOUNDS_CHECKS` enables checked index/accessor assertions that throw `std::out_of_range`.

`NNM_EPSILON_SCALE` controls the multiplier used by `nnm::epsilon<Real>()`. If not defined, it defaults to `100`.

## Projection Matrices

Projection helpers are named by handedness and normalized device coordinate depth range:

* `from_perspective_left_hand_neg1to1`
* `from_perspective_left_hand_0to1`
* `from_perspective_right_hand_neg1to1`
* `from_perspective_right_hand_0to1`
* `from_orthographic_left_hand_neg1to1`
* `from_orthographic_left_hand_0to1`
* `from_orthographic_right_hand_neg1to1`
* `from_orthographic_right_hand_0to1`

Choose the variant that matches your graphics API and coordinate convention. Common NDC depth conventions are:

| API                               | Typical NDC depth range |
|-----------------------------------|-------------------------|
| OpenGL / WebGL                    | `-1` to `1`             |
| DirectX / Vulkan / WebGPU / Metal | `0` to `1`              |

If your application's handedness differs from the projection/API convention, flip the z-axis after creating the
projection:

```cpp
const auto projection =
    nnm::Transform3f::from_perspective_left_hand_neg1to1(
        fov, aspect_ratio, near_clip, far_clip)
        .scale_local({1.0f, 1.0f, -1.0f});
```

## Building and Running Tests

Tests are optional and are enabled with `NNM_BUILD_TESTS`:

```bash
cmake -S . -B build -DNNM_BUILD_TESTS=ON
cmake --build build
```

Then run the produced `nnm_tests` executable from your build directory. On single-config generators this is usually:

```bash
./build/tests/nnm_tests
```

On Visual Studio or other multi-config generators, the executable may be under a configuration directory, for example:

```bash
./build/tests/Debug/nnm_tests
```

## License

NNM is licensed under the MIT license. See `LICENSE.txt` for the full license text.
