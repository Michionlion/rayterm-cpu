#include "world_object.h"

void WorldObject::intersects(ray r, intersection& record) {
    record.hit = false;
    intersection hit;
    scalar closest_t = INFINITY;
    for (geometry_list::const_iterator it = geometrys.cbegin(); it != geometrys.end(); ++it) {
        (*it)->intersects(r, hit);
        if (hit && hit.distance < closest_t) {
            record    = hit;
            closest_t = record.distance;
        }
    }
    if(record) {
        record.id = id;
    }
}

color WorldObject::colorize(ray r, const intersection& record) {
    color outcol(0, 0, 0);

    return outcol;
}
