#ifndef _RAYMATH_TYPES_H_
#define _RAYMATH_TYPES_H_
#include "Eigen/Dense"
#include "Eigen/Geometry"

typedef double scalar;
typedef Eigen::Matrix<scalar, 2, 1> texcoord;
typedef Eigen::Matrix<scalar, 3, 1> vector;
typedef Eigen::Matrix<scalar, 4, 1> vector4;
typedef Eigen::Matrix<scalar, 4, 4> matrix44;
typedef Eigen::ParametrizedLine<scalar, 3> ray;

#endif
