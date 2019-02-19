#ifndef _RAYTERM_CAMERA_H_
#define _RAYTERM_CAMERA_H_
#include <cmath>
#include "raymath"
#include "Eigen/Dense"

class Camera {
    int width;
    int height;
    scalar aspect_ratio;
    scalar vertical_fov;
    scalar fov_height_len;

    vector look_target;
    vector origin;
    Eigen::Matrix<scalar, 3, 3> camera_to_world;

   public:
    Camera(int width, int height, scalar vertical_fov) : width(width), height(height), vertical_fov(vertical_fov) {
        aspect_ratio   = scalar(width) / scalar(height);
        fov_height_len = tan((vertical_fov / 2 * M_PI / 180));
        origin = vector(0, 0, 0);
        look_target = vector(0, 0, -1);
        update_camera_matrix();
    }

    void position(vector new_origin) {
        origin = new_origin;
        update_camera_matrix();
    }

    void look(vector target) {
        look_target = target;
        update_camera_matrix();
    }

    void position_look(vector from, vector target) {
        this->origin = from;
        this->look_target = target;
        update_camera_matrix();
    }

    void update_camera_matrix() {
        vector wup = vector(0, 1, 0); // must be normalized
        vector forward = (origin - look_target).normalized();
        vector right = wup.cross(forward);
        vector up = forward.cross(right);

        camera_to_world(0, 0) = right.x();
        camera_to_world(0, 1) = right.y();
        camera_to_world(0, 2) = right.z();
        camera_to_world(1, 0) = up.x();
        camera_to_world(1, 1) = up.y();
        camera_to_world(1, 2) = up.z();
        camera_to_world(2, 0) = forward.x();
        camera_to_world(2, 1) = forward.y();
        camera_to_world(2, 2) = forward.z();
    }

    // get the ray originating from the camera going through screen coordinate (u, v)
    // screen coordinates are in (-1, 1)
    ray get_screen_ray(scalar u, scalar v) {
        scalar camx = u * aspect_ratio * fov_height_len;
        scalar camy = v * fov_height_len;
        vector origin = toWorldPos(vector(0, 0, 0));
        vector direction = toWorldDir(vector(camx, camy, -1).normalized());
        return ray(origin, direction);
    }

    vector toWorldDir(vector direction) {
        return camera_to_world * direction;
    }

    vector toWorldPos(vector position) {
       return origin + position;
    }
};

#endif
