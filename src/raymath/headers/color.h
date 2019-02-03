#ifndef _RAYMATH_COLOR_H_
#define _RAYMATH_COLOR_H_
#include "Eigen/Dense"
#include "types.h"

typedef Eigen::Vector3f color;

struct colori {
    int r : 8;
    int g : 8;
    int b : 8;

    colori(color source)
        : r(int(source[0] * 255.0)), g(int(source[1] * 255.0)), b(int(source[2] * 255.0)){};
    colori(int r, int g, int b) : r(r), g(g), b(b){};
};

#endif
