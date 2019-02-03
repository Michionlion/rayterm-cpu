#include "sphere.h"

bool sphere::intersects(ray r) {
    // Solves (ray_dir^2)t^2 +2(ray_dir dot (ray_origin - sphere_center))t
    // + (ray_origin - sphere_center)^2 - sphere_radius^2 = 0 for t
    // this is formula 6 in the rayterm proposal

    scalar a = r.direction().dot(r.direction());
    vector i = r.origin() - center;
    scalar b = 2 * r.direction().dot(i);
    scalar c = i.dot(i) - radius * radius;

    scalar discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}
