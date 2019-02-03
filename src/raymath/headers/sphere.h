#ifndef _RAYMATH_SPHERE_H_
#define _RAYMATH_SPHERE_H_
#include "Eigen/Dense"
#include "types.h"

struct sphere {
    vector center;
    scalar radius;

    sphere(vector center, scalar radius) : center(center), radius(radius){};

    bool intersects(ray r);
};

#endif
