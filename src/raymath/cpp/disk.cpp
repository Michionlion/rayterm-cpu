#include "disk.h"
#include <cstdio>
#include "color.h"
#include "intersection.h"

#define MIN_CONTACT 0.0000001
#define MAX_CONTACT 20

void disk::intersects(ray r, intersection& record) {
    scalar denom = normal.dot(r.direction());
    if (denom > MIN_CONTACT || denom < MIN_CONTACT) {
        scalar t = (center - r.origin()).dot(normal) / denom;
        if (t > MIN_CONTACT && t < MAX_CONTACT) {
            record.position = r.pointAt(t);
            if ((record.position - center).squaredNorm() <= radius_sqr) {
                record.hit      = true;
                record.distance = t;
                record.normal   = normal;
                return;
            }
        }
    }
    record.hit = false;
}

texcoord disk::compute_texcoord(const intersection& record) { return texcoord(0, 0); }
