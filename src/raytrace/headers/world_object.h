#ifndef _RAYTERM_WORLD_OBJECT_H_
#define _RAYTERM_WORLD_OBJECT_H_
#include "raymath"

// WorldObject joins geometry (possibly more than one) to a colorize function.
// This enables the use of materials, shading, and more.
class WorldObject {
    geometry_list geometrys;
    long id;

   public:
    WorldObject(long id) : id(id){};

    void add_geometry(geometry* geom) { geometrys.push_back(std::unique_ptr<geometry>(geom)); }

    virtual void intersects(ray r, intersection& record);

    virtual color colorize(ray r, const intersection& record);
};

#endif
