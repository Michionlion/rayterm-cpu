#ifndef _RAYTERM_CAMERA_H_
#define _RAYTERM_CAMERA_H_

#include "raymath"

class Camera {
    vector top_left_corner;
    vector horizontal;
    vector vertical;
    vector origin;
    int width;
    int height;
    scalar aspect_ratio;

   public:
    Camera(int width, int height) : width(width), height(height) {
        top_left_corner = vector(-2, 1, -1);
        horizontal      = vector(4, 0, 0);
        vertical        = vector(0, 2, 0);
        origin          = vector(0, 0, 0);
        aspect_ratio    = scalar(width) / scalar(height);
    }

    // get the ray originating from the camera going through screen coordinate (u, v)
    ray get_screen_ray(scalar u, scalar v) {
        return ray(origin, top_left_corner + u * horizontal + v * vertical - origin);
    }
};

#endif
