#ifndef _RAYMATH_INTERSECTION_H_
#define _RAYMATH_INTERSECTION_H_
#include "Eigen/Dense"
#include "types.h"

struct intersection {
    bool hit;
    long id;
    vector position;
    vector normal;
    scalar distance;

    intersection() : hit(false), id(-1){};
    intersection(long id, vector position, vector normal, scalar distance)
        : hit(true), id(id), position(position), normal(normal), distance(distance) {};
    operator bool() const { return hit; };
    bool operator!() const { return !hit; };
};

#endif
