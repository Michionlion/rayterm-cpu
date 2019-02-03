#ifndef _RAYMATH_SPHERE_H_
#define _RAYMATH_SPHERE_H_
#include "Eigen/Dense"
#include "intersection.h"
#include "types.h"

struct sphere {
    vector center;
    scalar radius;

    sphere(vector c, scalar r) : center(c), radius(r){};

    intersection intersects(ray r);
};

#endif
