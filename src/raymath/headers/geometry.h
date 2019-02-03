#ifndef _RAYMATH_GEOMETRY_H_
#define _RAYMATH_GEOMETRY_H_
#include "Eigen/Dense"
#include "color.h"
#include "intersection.h"
#include "types.h"

struct geometry {
    virtual intersection intersects(ray r) = 0;
    virtual color colorize(texcoord tc)    = 0;
};

#endif
