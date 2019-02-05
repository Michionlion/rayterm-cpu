#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <memory>
#include "raymath"

class World {
    geometry_list objects;

   public:
    World(){};

    void add_object(geometry* geom) { objects.push_back(std::unique_ptr<geometry>(geom)); }

    void intersects(ray r, intersection& record);
};

#endif
