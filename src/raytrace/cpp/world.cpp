#include "world.h"

unique_ptr<WorldObject> World::intersects(ray r, intersection& record) {
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

void World::trace(ray r, intersection& record, int depth) {
    if (depth < max_depth) {
        intersects(r, hit);
        if (hit) {

            return 0.5 * trace(ray(hit.position, bounce - hit.position), world, hit, depth + 1);
        }
    }

    scalar yness = (r.direction().normalized().y() + 1) / 2;
    return (1 - yness) * color(1, 1, 1) + yness * color(0.5, 0.7, 1);
}
