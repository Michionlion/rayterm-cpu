#include "world.h"

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
    if (record) {
        record.id = id;
    }
}

// colorize colors the given ray as if it hit at the given intersection, with the given trace depth
color WorldObject::colorize(ray r, intersection& record, int depth) {
    ray scattered;
    color outcol(1, 1, 1);
    if (depth < world->max_depth && material->scatter(r, scattered, record, outcol)) {
        return outcol.cwiseProduct(world->trace(scattered, record, depth + 1));
    }
    return outcol;
}
