#ifndef _RAYTERM_CAMERA_H_
#define _RAYTERM_CAMERA_H_
#include <cmath>
#include "raymath"

class Camera {
    int width;
    int height;
    scalar aspect_ratio;
    scalar vertical_fov;
    scalar fov_height_len;

    vector look_target;
    vector origin;
    matrix44 camera_to_world;

   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Camera(int width, int height, scalar vertical_fov)
        : width(width), height(height), vertical_fov(vertical_fov) {
        aspect_ratio                   = scalar(width) / scalar(height);
        fov_height_len                 = tan((vertical_fov / 2 * M_PI / 180));
        origin                         = vector(0, 0, 0);
        look_target                    = vector(0, 0, -1);
        camera_to_world.coeffRef(0, 3) = 0;
        camera_to_world.coeffRef(1, 3) = 0;
        camera_to_world.coeffRef(2, 3) = 0;
        camera_to_world.coeffRef(3, 3) = 1;
        update_camera_matrix();
    }

    void position(const vector& new_origin) {
        origin = new_origin;
        update_camera_matrix();
    }

    void look(const vector& target) {
        look_target = target;
        update_camera_matrix();
    }

    void position_look(const vector& from, const vector& target) {
        this->origin      = from;
        this->look_target = target;
        update_camera_matrix();
    }

    void update_camera_matrix() {
        vector wup     = vector(0, 1, 0);  // must be normalized
        vector forward = (origin - look_target).normalized();
        vector right   = wup.cross(forward);
        vector up      = forward.cross(right);

        camera_to_world.coeffRef(0, 0) = right.coeff(0);
        camera_to_world.coeffRef(0, 1) = right.coeff(1);
        camera_to_world.coeffRef(0, 2) = right.coeff(2);
        camera_to_world.coeffRef(1, 0) = up.coeff(0);
        camera_to_world.coeffRef(1, 1) = up.coeff(1);
        camera_to_world.coeffRef(1, 2) = up.coeff(2);
        camera_to_world.coeffRef(2, 0) = forward.coeff(0);
        camera_to_world.coeffRef(2, 1) = forward.coeff(1);
        camera_to_world.coeffRef(2, 2) = forward.coeff(2);
        camera_to_world.coeffRef(3, 0) = origin.coeff(0);
        camera_to_world.coeffRef(3, 1) = origin.coeff(1);
        camera_to_world.coeffRef(3, 2) = origin.coeff(2);
    }

    // get the ray originating from the camera going through screen coordinate (u, v)
    // screen coordinates are in (-1, 1)
    ray get_screen_ray(scalar u, scalar v) {
        scalar camx      = u * aspect_ratio * fov_height_len;
        scalar camy      = v * fov_height_len;
        vector origin    = toWorldPos(vector(0, 0, 0));
        vector direction = toWorldDir(vector(camx, camy, -1).normalized());
        return ray(origin, direction);
    }

    vector toWorldDir(const vector& direction) {
        vector4 mult   = vector4::Constant(1);
        mult.head<3>() = direction;
        return (camera_to_world * mult).head<3>();
    }

    vector toWorldPos(const vector& position) {
        vector4 mult   = vector4::Constant(0);
        mult.head<3>() = position;
        return (camera_to_world * mult).head<3>();
    }
};

#endif
