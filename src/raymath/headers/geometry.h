#ifndef _RAYMATH_GEOMETRY_H_
#define _RAYMATH_GEOMETRY_H_
#include <list>
#include "color.h"
#include "intersection.h"
#include "types.h"

// geometry describes a geometric object, that is both intersectable and texturable.
// This means it can both interact with the 3D world (intersect),
// and itself in 2D (texture).
struct geometry {
    virtual texcoord compute_texcoord(const intersection& record) = 0;
    virtual void intersects(ray r, intersection& record)          = 0;

    intersection intersects(ray r) {
        intersection hit;
        this->intersects(r, hit);
        return hit;
    }

    virtual ~geometry() {}
};

typedef std::list<geometry*> geometry_list;

#endif
