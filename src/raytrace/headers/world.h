#ifndef _RAYTERM_WORLD_H_
#define _RAYTERM_WORLD_H_
#include "material.h"
#include "raymath"

#define MAXDEPTH 32

class World;

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
    virtual ~WorldObject() {
        for (geometry_list::iterator it = geometrys.begin(); it != geometrys.end(); ++it) {
            delete (*it);
        }
        // other things may also use this -- leave the creator to delete it
        // only assume we own the geometry
        // delete material;
    }

    void add_geometry(geometry* geom) { geometrys.push_back(geom); }

    virtual void intersects(ray r, intersection& record);

    virtual color colorize(ray r, intersection& record, int depth);
};

typedef std::list<WorldObject*> worldobject_list;

// World holds a list of WorldObjects, and can iterate through them checking for intersection.
// Additionally, World can trace a ray through itself, returning the color the ray found.
class World {
    worldobject_list objects;

   public:
    int max_depth;

    World() : max_depth(MAXDEPTH){};
    virtual ~World() {
        for (worldobject_list::iterator it = objects.begin(); it != objects.end(); ++it) {
            delete *it;
        }
    }

    void add_object(WorldObject* obj) { objects.push_back(obj); }

    WorldObject* intersects(ray r, intersection& record);

    color trace(ray r, intersection& record, int depth);
};

#endif
