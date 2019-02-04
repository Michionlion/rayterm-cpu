#ifndef _RAYTERM_CAMERA_H_
#define _RAYTERM_CAMERA_H_
#include <cmath>
#include "raymath"

class Camera {
    vector origin;
    int width;
    int height;
    scalar aspect_ratio;
    scalar fov;
    scalar fov_height_len;

   public:
    Camera(int width, int height, scalar fov) : width(width), height(height), fov(fov) {
        origin          = vector(0, 0, 0);
        aspect_ratio    = scalar(width) / scalar(height);
        fov_height_len  = tan((fov / 2 * M_PI / 180));
    }

    // get the ray originating from the camera going through screen coordinate (u, v)
    ray get_screen_ray(scalar u, scalar v);
};

#endif
