#include "camera.h"

ray Camera::get_screen_ray(scalar u, scalar v) {
    scalar camx = u * aspect_ratio * fov_height_len;
    scalar camy = v * fov_height_len;
    return ray(origin, (vector(camx, camy, -1) - vector(0, 0, 0)).normalized());
}
