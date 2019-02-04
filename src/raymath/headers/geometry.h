#ifndef _RAYMATH_GEOMETRY_H_
#define _RAYMATH_GEOMETRY_H_
#include "Eigen/Dense"
#include "color.h"
#include "intersection.h"
#include "types.h"

struct geometry {
    virtual color colorize(texcoord tc)                  = 0;
    virtual void intersects(ray r, intersection& record) = 0;

    intersection intersects(ray r) {
        intersection hit;
        this->intersects(r, hit);
        return hit;
    }
};

#endif
