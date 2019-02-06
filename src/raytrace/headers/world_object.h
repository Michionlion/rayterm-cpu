#ifndef _RAYTERM_WORLD_OBJECT_H_
#define _RAYTERM_WORLD_OBJECT_H_
#include "raymath"
#include "material.h"

// WorldObject joins geometry (possibly more than one) to a colorize function.
// This enables the use of materials, shading, and more.
class WorldObject {
    geometry_list geometrys;
    long id;
    Material* material;
    World* world;

   public:
    WorldObject(long id, Material* material, World* world, geometry* first_geometry) : id(id), material(material), world(world){} {
        add_geometry(first_geometry);
    }

    void add_geometry(geometry* geom) { geometrys.push_back(std::unique_ptr<geometry>(geom)); }

    virtual void intersects(ray r, intersection& record);

    virtual color colorize(ray r, const intersection& record);
};

typedef std::list<std::unique_ptr<WorldObject>> worldobject_list;

#endif
