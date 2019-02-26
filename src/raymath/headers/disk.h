#ifndef _RAYMATH_DISK_H_
#define _RAYMATH_DISK_H_
#include "geometry.h"
#include "intersection.h"
#include "types.h"

struct disk : geometry {
    vector center;
    vector normal;
    scalar radius;
    scalar radius_sqr;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    disk(const vector& c, const vector& n, scalar r)
        : center(c), normal(n), radius(r), radius_sqr(r * r){};

    void intersects(ray r, intersection& record);
    using geometry::intersects;
    texcoord compute_texcoord(const intersection& record);
};

#endif
