#ifndef _RAYMATH_TYPES_H_
#define _RAYMATH_TYPES_H_
#include "Eigen/Dense"
#include "Eigen/Geometry"

typedef double scalar;
typedef Eigen::Vector3d vector;
typedef Eigen::Vector2f texcoord;
typedef Eigen::ParametrizedLine<scalar, 3> ray;

#endif
