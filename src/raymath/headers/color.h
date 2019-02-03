#ifndef _RAYMATH_COLOR_H_
#define _RAYMATH_COLOR_H_
#include <cstdint>
#include "Eigen/Dense"
#include "types.h"

typedef Eigen::Vector3f color;

struct colori {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    colori(color source)
        : r(uint8_t(source[0] * 255.0)),
          g(uint8_t(source[1] * 255.0)),
          b(uint8_t(source[2] * 255.0)){};
    colori(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b){};
};

#endif
