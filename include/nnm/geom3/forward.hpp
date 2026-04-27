/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM3_FORWARD_HPP
#define NNM_GEOM3_FORWARD_HPP

#include <nnm/core.hpp>

namespace nnm {

template <typename Point, uint8_t Capacity>
class PointSet;

template <typename Real>
class Line3;
using Line3f = Line3<float>;
using Line3d = Line3<double>;

template <typename Real>
class Ray3;
using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;

template <typename Real>
class Segment3;
using Segment3f = Segment3<float>;
using Segment3d = Segment3<double>;

template <typename Real>
class Plane;
using PlaneF = Plane<float>;
using PlaneD = Plane<double>;

template <typename Real>
class Triangle3;
using Triangle3f = Triangle3<float>;
using Triangle3d = Triangle3<double>;

template <typename Real>
class Rectangle3;
using Rectangle3f = Rectangle3<float>;
using Rectangle3d = Rectangle3<double>;

template <typename Real>
class Sphere;
using SphereF = Sphere<float>;
using SphereD = Sphere<double>;

template <typename Real>
class AlignedBox;
using AlignedBoxF = AlignedBox<float>;
using AlignedBoxD = AlignedBox<double>;

template <typename Real>
class Box;
using BoxF = Box<float>;
using BoxD = Box<double>;

template <typename Real>
class Frustum;
using FrustumF = Frustum<float>;
using FrustumD = Frustum<double>;

} // namespace nnm

#endif
