#ifndef _RAYMATH_INTERSECTION_H_
#define _RAYMATH_INTERSECTION_H_
#include "Eigen/Dense"
#include "types.h"

struct intersection {
    bool hit;
    vector position;
    vector normal;
    texcoord texture;

    intersection(bool hit) : hit(hit){};
    intersection(vector position, vector normal, texcoord texture)
        : hit(true), position(position), normal(normal), texture(texture){};
    operator bool() const { return hit; };
    bool operator!() const { return !hit; };
};

#endif
