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
    const float aspect_ratio = nnm::Vector2(16.0f, 9.0f).aspect_ratio();
    const float fov = nnm::radians(90.0f);
    const auto projection = nnm::Transform3f::from_projection_perspective(
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

A full list of all functions/classes can be found in [**docs/reference.md**](docs/reference.md).

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

where the trailing number represents the "dimension" of the class. Most of these classes, except for the integer
variants, are templated for any `Real` value such as `float` or `double`. Aliases are created for those cases for
example `Vector2f` and `Vector2d` for `float` and `double` respectively.

In addition to these classes, NNM provides for a number of standalone math functions such as `lerp`, `clamp`,
`approx_equal`, etc.

Other notable features/qualities of NNM include:

* No template magic, just the basics for your choice of `Real` value.
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

## Compiling and Running Tests

After cloning the repository, configure the project with CMake ensuring to enable building tests:

```bash
cd nnm
mkdir build
cmake -S . -B build -DNNM_BUILD_TESTS=ON
cmake --build build
```

## License

NNM is licensed under the MIT license. See `LICENSE.txt` for full license.
