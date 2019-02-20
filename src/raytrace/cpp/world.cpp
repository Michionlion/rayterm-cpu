#include "world.h"

WorldObject* World::intersects(ray r, intersection& record) {
    record.hit = false;
    intersection hit;
    WorldObject* obj_hit;
    scalar closest_t = INFINITY;
    for (worldobject_list::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->intersects(r, hit);
        if (hit && hit.distance < closest_t) {
            record    = hit;
            closest_t = record.distance;
            obj_hit   = *it;
        }
    }
    return obj_hit;
}

color World::trace(ray r, intersection& record, int depth) {
    if (depth < max_depth) {
        WorldObject* obj_hit = intersects(r, record);
        if (record) {
            return obj_hit->colorize(r, record, depth);
        }
    }

    scalar yness = (r.direction().normalized().y() + 1) / 2;
    return (1 - yness) * color(1, 1, 1) + yness * color(0.3, 0.5, 1);
}
