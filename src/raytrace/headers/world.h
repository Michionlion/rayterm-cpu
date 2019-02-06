#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <memory>
#include "raymath"
#define MAXDEPTH 32

class World {
    geometry_list objects;
    int max_depth;

   public:
    World() : max_depth(MAXDEPTH){};

    void add_object(geometry* geom) { objects.push_back(std::unique_ptr<geometry>(geom)); }

    void intersects(ray r, intersection& record);

    void trace(ray r, intersection& record, int depth);
};

#endif
