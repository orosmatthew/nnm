# [nnm] No Nonsense Math

NNM is a "No-Nonsense" C++ 17 Math library mainly geared at graphics programming. Think of it as a lightweight alternative to a library like [glm](https://github.com/g-truc/glm).

## A Quick Example

```cpp
#define NNM_BOUNDS_CHECK // optional bounds checking
#include <nnm/nnm.hpp>

nnm::Transform3f camera(const nnm::Vector3f& position, const nnm::Vector2f& rotation)
{
    const float aspect_ratio = nnm::Vector2(16.0f, 9.0f).aspect_ratio();
    const float fov = nnm::radians(90.0f);
    const auto projection = nnm::Transform3f::from_projection_perspective(fov, aspect_ratio, 0.1f, 100.0f);
    const auto view = nnm::Transform3f::from_translation(position)
                          .rotate_axis_angle(nnm::Vector3f::axis_y(), rotation.y)
                          .rotate_axis_angle(nnm::Vector3f::axis_x(), rotation.x);
    const auto model = nnm::Transform3f::from_scale(nnm::Vector3f::all(0.5f));
    return model.transform(view).transform(projection);
}
```



