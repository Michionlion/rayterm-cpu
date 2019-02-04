#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <list>
#include <memory>
#include "raymath"

typedef std::list<std::unique_ptr<geometry>> geometry_list;

class World : geometry {
    geometry_list objects;

   public:
    World(){};

    void add_object(geometry& geom) { objects.push_back(std::unique_ptr<geometry>(&geom)); }

    using geometry::intersects;
    void intersects(ray r, intersection& record);
};

#endif
