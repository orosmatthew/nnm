# [nnm] No Nonsense Math

NNM is a "No-Nonsense", C++ 17, single-header-only Math library geared towards graphics programming. Think of it as a
lightweight, more readable alternative to a library like [glm](https://github.com/g-truc/glm) and inspired by the OOP
style of [Godot's](https://github.com/godotengine/godot) math library.

## A Quick Example

```cpp
#define NNM_BOUNDS_CHECK // optional bounds checking
#include <nnm/nnm.hpp>

// Compute transform of an object in 3d space
nnm::Transform3f calculate_object_transform(
    const nnm::Vector3f& position, const nnm::Vector2f& rotation)
{
    constexpr float aspect_ratio = nnm::Vector2(16.0f, 9.0f).aspect_ratio();
    constexpr float fov = nnm::radians(90.0f);
    const auto projection
        = nnm::Transform3f::from_perspective_left_hand_neg1to1(
            fov, aspect_ratio, 0.1f, 100.0f);
    const auto view
        = nnm::Transform3f::from_translation(position)
              .rotate_axis_angle(nnm::Vector3f::axis_y(), rotation.y)
              .rotate_axis_angle(nnm::Vector3f::axis_x(), rotation.x);
    const auto model = nnm::Transform3f::from_scale(nnm::Vector3f::all(0.5f));
    return model.transform(view).transform(projection);
}
```

## Features

A full list of all functions/classes can be found at [**nnm.pixeled.site**](https://nnm.pixeled.site).

NNM provides classes for:

* Vectors
    * `Vector2`
    * `Vector2i`
    * `Vector3`
    * `Vector3i`
    * `Vector4`

* Matrices
    * `Matrix2`
    * `Matrix3`
    * `Matrix4`

* Transformations
    * `Basis2`
    * `Transform2`
    * `Basis3`
    * `Transform3`

* Misc.
    * `Quaternion`

where the trailing number represents the "dimension" of the class. These classes are templated with either `Real` or
`Int` types that allow for various floating point and integer types. Aliases are created for those cases such
as `Vector2f` and `Vector2d` for `float` and `double` respectively as well as `Vector3i32`, `Vector2u16`,
`Vector3i64`, etc. for integer classes.

In addition to these classes, NNM provides for a number of standalone math functions such as `lerp`, `clamp`,
`approx_equal`, etc.

Other notable features/qualities of NNM include:

* No template magic, just the basics for your choice of `Real` floating-point value and `Int` integer value.
* Extremely readable. There are almost no macros and light use of templates.
* Minimal abbreviations. It's the 21st century, we can afford readable function names!
* Optional bounds checking for accessors with an optional `#define NNM_BOUNDS_CHECK` before including.
* No external dependencies! Even minimal use of the standard library to just `<cmath>`, `<functional>`, `<optional>`,
  and `<stdexcept>` if optional bounds checking is enabled.
* No special SIMD instructions or compiler intrinsics. This makes NNM extremely portable. I personally have faith in
  modern compilers to auto-vectorize when necessary.
* `std::hash` specializations for `Vector2i` and `Vector3i`.
* `begin()` and `end()` iterators for looping through classes with a ranged-for loop.

## Installation Instructions

The easiest way would be to just copy the `include/nnm/nnm.hpp` file directly into your project and just `#include` it
to use!

Another method is to add the project as a CMake submodule by copying the repository to a directory and adding:

```cmake
add_subdirectory(external/path/to/nnm)
target_link_libraries(your_project PRIVATE nnm)
```

## Projection Matrices

You might be asking, "What is up with all these variations of perspective/orthographic projection methods? Which one do
I use??" This depends on the graphics API you are using as well as the coordinate system you choose for your
application. There are two considerations to be aware of, the handedness and the normalization of the graphics API. Here
is a short list of common graphics APIs' normalized device coordinate (NDC) conventions:

* OpenGL/WebGL/WebGPU/Metal: left-handed, -1 to 1
* DirectX: left-handed, 0 to 1
* Vulkan: right-handed, 0 to 1

This means if your application and graphics API use the same coordinate system, you just need to choose the method with
the correct handedness and normalization corresponding to that graphics API. However, if your application and chosen
graphics API have mismatching handedness, you must flip the z-axis. For example, if you are using OpenGL (which is
left-handed) but wish to use right-handed coordinates in your application, you would still use the projection method
corresponding with OpenGL's convention of left-handed and -1 to 1 normalization but just need to flip the z-axis to
account for the switched handedness:

```cpp
const auto proj = nnm::Transform3f::from_perspective_left_hand_neg1to1(...).scale_local({1, 1, -1});
```

## Compiling and Running Tests

After cloning the repository, configure the project with CMake ensuring to enable building tests:

```bash
cd nnm
cmake -S . -B build -DNNM_BUILD_TESTS=ON
cmake --build build
```

## License

NNM is licensed under the MIT license. See `LICENSE.txt` for full license.
