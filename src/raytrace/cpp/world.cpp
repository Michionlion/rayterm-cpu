#include "world.h"

void World::intersects(ray r, intersection& record) {
    record.hit = false;
    intersection hit;
    scalar closest_t = INFINITY;
    for (geometry_list::const_iterator it = objects.cbegin(); it != objects.end(); ++it) {
        (*it)->intersects(r, hit);
        if (hit && hit.distance < closest_t) {
            record    = hit;
            closest_t = record.distance;
        }
    }
}
