#include "sphere.h"
#include "color.h"
#include "intersection.h"

intersection sphere::intersects(const ray r) {
    // Solves (ray_dir^2)t^2 +2(ray_dir dot (ray_origin - sphere_center))t
    // + (ray_origin - sphere_center)^2 - sphere_radius^2 = 0 for t
    // this is formula 6 in the rayterm proposal

    scalar a = r.direction().dot(r.direction());
    vector i = r.origin() - center;
    scalar b = 2 * r.direction().dot(i);
    scalar c = i.dot(i) - radius * radius;

    scalar discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return intersection(false);
    } else {
        scalar t   = (-b - sqrt(discriminant)) / (2.0 * a);
        vector pos = r.pointAt(t);
        return intersection(pos, (pos - center).normalized(), texcoord(0, 0));
    }
}

color sphere::colorize(const texcoord tc) { return shade; }
