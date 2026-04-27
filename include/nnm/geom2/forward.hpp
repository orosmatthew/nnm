/* NNM - "No Nonsense Math"
 * v0.5.0
 * Copyright (c) 2025-present Matthew Oros
 * Licensed under MIT
 */

#ifndef NNM_GEOM2_FORWARD_HPP
#define NNM_GEOM2_FORWARD_HPP

#include <nnm/core.hpp>

namespace nnm {

template <typename Point, uint8_t Capacity>
class PointSet;

template <typename Real>
class Line2;
using Line2f = Line2<float>;
using Line2d = Line2<double>;

template <typename Real>
class Ray2;
using Ray2f = Ray2<float>;
using Ray2d = Ray2<double>;

template <typename Real>
class Segment2;
using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;

template <typename Real>
class Circle2;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;

template <typename Real>
class Triangle2;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;

template <typename Real>
class Rectangle2;
using Rectangle2f = Rectangle2<float>;
using Rectangle2d = Rectangle2<double>;

template <typename Real>
class AlignedRectangle2;
using AlignedRectangle2f = AlignedRectangle2<float>;
using AlignedRectangle2d = AlignedRectangle2<double>;

} // namespace nnm

#endif
