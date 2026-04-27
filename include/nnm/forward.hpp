/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_FORWARD_HPP
#define NNM_FORWARD_HPP

#include <nnm/core.hpp>

namespace nnm {

template <typename Real>
class Vector2;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

template <typename Real>
class Point2;
using Point2f = Point2<float>;
using Point2d = Point2<double>;

template <typename Int>
class Vector2i;
using Vector2ii = Vector2i<int>;
using Vector2i8 = Vector2i<int8_t>;
using Vector2i16 = Vector2i<int16_t>;
using Vector2i32 = Vector2i<int32_t>;
using Vector2i64 = Vector2i<int64_t>;
using Vector2iu = Vector2i<unsigned int>;
using Vector2u8 = Vector2i<uint8_t>;
using Vector2u16 = Vector2i<uint16_t>;
using Vector2u32 = Vector2i<uint32_t>;
using Vector2u64 = Vector2i<uint64_t>;

template <typename Real>
class Vector3;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

template <typename Real>
class Point3;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

template <typename Int>
class Vector3i;
using Vector3ii = Vector3i<int>;
using Vector3i8 = Vector3i<int8_t>;
using Vector3i16 = Vector3i<int16_t>;
using Vector3i32 = Vector3i<int32_t>;
using Vector3i64 = Vector3i<int64_t>;
using Vector3iu = Vector3i<unsigned int>;
using Vector3u8 = Vector3i<uint8_t>;
using Vector3u16 = Vector3i<uint16_t>;
using Vector3u32 = Vector3i<uint32_t>;
using Vector3u64 = Vector3i<uint64_t>;

template <typename Real>
class Vector4;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template <typename Real>
class Quaternion;
using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;

template <typename Real>
class Matrix2;
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;

template <typename Real>
class Basis2;
using Basis2f = Basis2<float>;
using Basis2d = Basis2<double>;

template <typename Real>
class Matrix3;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;

template <typename Real>
class Transform2;
using Transform2f = Transform2<float>;
using Transform2d = Transform2<double>;

template <typename Real>
class Basis3;
using Basis3f = Basis3<float>;
using Basis3d = Basis3<double>;

template <typename Real>
class Matrix4;
using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;

template <typename Real>
class Transform3;
using Transform3f = Transform3<float>;
using Transform3d = Transform3<double>;
}

#endif
