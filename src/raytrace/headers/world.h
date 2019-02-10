#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include <memory>
#include "material.h"
#include "raymath"

#define MAXDEPTH 32

class WorldObject;

typedef std::unique_ptr<WorldObject> WorldObjectPtr;
typedef std::list<WorldObjectPtr> worldobject_list;

// World holds a list of WorldObjects, and can iterate through them checking for intersection.
// Additionally, World can trace a ray through itself, returning the color the ray found.
class World {
    worldobject_list objects;

   public:
    int max_depth;

    World() : max_depth(MAXDEPTH){};

    void add_object(WorldObject* obj) { objects.emplace_back(obj); }

    WorldObjectPtr* intersects(ray r, intersection& record);

    color trace(ray r, intersection& record, int depth);
};

// WorldObject joins geometry (possibly more than one) to a colorize function.
// This enables the use of materials, shading, and more.
class WorldObject {
    geometry_list geometrys;
    long id;
    Material* material;
    World* world;

   public:
    WorldObject(long id, Material* material, World* world, geometry* first_geometry)
        : id(id), material(material), world(world) {
        add_geometry(first_geometry);
    }

    void add_geometry(geometry* geom) { geometrys.emplace_back(geom); }

    virtual void intersects(ray r, intersection& record);

    virtual color colorize(ray r, intersection& record, int depth);
};

#endif
