#include "sphere.h"
#include <cstdio>
#include "color.h"
#include "intersection.h"

#define MIN_CONTACT 0.00001

void sphere::intersects(ray r, intersection& record) {
    // Solves (ray_dir^2)t^2 +2(ray_dir dot (ray_origin - sphere_center))t
    // + (ray_origin - sphere_center)^2 - sphere_radius^2 = 0 for t
    // this is formula 6 in the rayterm proposal

    scalar a = r.direction().dot(r.direction());
    vector i = r.origin() - center;
    scalar b = i.dot(r.direction());
    scalar c = i.dot(i) - radius * radius;

    scalar discriminant = b * b - a * c;

    if (discriminant >= 0) {
        // check both roots -- get smallest non-negative
        scalar sqrt_discrim = sqrt(discriminant);
        scalar inv_denom    = 1 / a;
        scalar t            = (-b - sqrt_discrim) * inv_denom;

        if (t > MIN_CONTACT) {
            // FIXME: in the future, this could be put into a lambda (which captures r, center and
            // texcoord stuff), and only evaluated once the caller used t to determine which
            // intersection was the closest. This will probably only be efficient when most rays
            // intersect at least a few things, otherwise there is no point to saving anything.

            record.hit      = true;
            record.distance = t;
            record.position = r.pointAt(t);
            record.normal   = (record.position - center) / radius;

            return;
        }

        t = (-b + sqrt_discrim) * inv_denom;
        if (t > MIN_CONTACT) {
            record.hit      = true;
            record.distance = t;
            record.position = r.pointAt(t);
            record.normal   = (record.position - center) / radius;

            return;
        }
    }

    record.hit = false;
}

texcoord sphere::compute_texcoord(const intersection& record) { return texcoord(0, 0); }
