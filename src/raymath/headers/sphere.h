#ifndef _RAYMATH_SPHERE_H_
#define _RAYMATH_SPHERE_H_
#include "Eigen/Dense"
#include "color.h"
#include "geometry.h"
#include "intersection.h"
#include "types.h"

struct sphere : geometry {
    vector center;
    scalar radius;
    color shade = color(0, 1, 0);

    sphere(vector c, scalar r) : center(c), radius(r){};

    intersection intersects(const ray r);
    color colorize(const texcoord tc);
};

#endif
