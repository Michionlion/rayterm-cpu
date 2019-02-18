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

    Eigen::Matrix<scalar, 4, 4> camera_to_world;

   public:
    Camera(int width, int height, scalar vertical_fov) : width(width), height(height), vertical_fov(vertical_fov) {
        aspect_ratio   = scalar(width) / scalar(height);
        fov_height_len = tan((vertical_fov / 2 * M_PI / 180));
        position(vector(0, 0, 0));
        look(vector(0, 0, -1));
        camera_to_world(0, 3) = 0;
        camera_to_world(1, 3) = 0;
        camera_to_world(2, 3) = 0;
        camera_to_world(3, 3) = 1;
    }

    void position(vector new_origin) {
        camera_to_world(3, 0) = new_origin.x();
        camera_to_world(3, 1) = new_origin.y();
        camera_to_world(3, 2) = new_origin.z();
    }

    void look(vector look_target) {
        vector origin = vector(camera_to_world(3, 0), camera_to_world(3, 1), camera_to_world(3, 2));
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
    ray get_screen_ray(scalar u, scalar v) {
        scalar camx = u * aspect_ratio * fov_height_len;
        scalar camy = v * fov_height_len;
        vector origin = toWorldPos(vector(0, 0, 0));
        vector direction = toWorldDir(vector(camx, camy, -1).normalized());
        return ray(origin, direction);
    }

    vector toWorldDir(vector direction) {
        return camera_to_world.block<3, 3>(0, 0) * direction;
    }

    vector toWorldPos(vector position) {
       Eigen::Vector4d vec4(position.x(), position.y(), position.z(), 1);
       return (camera_to_world * vec4).head<3>();
    }
};

#endif
