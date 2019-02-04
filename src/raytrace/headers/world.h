#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <list>
#include "raymath"
class World {
    list<geometry> objects;

   public:
    World(){};

    void add_object(geometry& geom) { objects.push_back(geom); }
}

#endif
