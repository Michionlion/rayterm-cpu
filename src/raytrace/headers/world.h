#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <memory>
#include "raymath"
#include "world_object.h"

#define MAXDEPTH 32

class World {
    worldobject_list objects;
    int max_depth;

   public:
    World() : max_depth(MAXDEPTH){};

    void add_object(world_object* obj) { objects.push_back(std::unique_ptr<WorldObject>(obj)); }

    void intersects(ray r, intersection& record);

    void trace(ray r, intersection& record, int depth);
};

#endif
