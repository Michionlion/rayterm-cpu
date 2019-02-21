#ifndef _RAYMATH_SPHERE_H_
#define _RAYMATH_SPHERE_H_
#include "geometry.h"
#include "intersection.h"
#include "types.h"

struct sphere : geometry {
    vector center;
    scalar radius;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    sphere(const vector& c, scalar r) : center(c), radius(r){};

    void intersects(ray r, intersection& record);
    using geometry::intersects;
    texcoord compute_texcoord(const intersection& record);
};

#endif
