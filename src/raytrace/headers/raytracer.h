#ifndef _RAYTERM_RAYTRACER_H_
#define _RAYTERM_RAYTRACER_H_
#include "raymath"
#include "world.h"

int raytrace_ppm(const char* filename);

color trace(ray r, World& world, intersection& hit, int depth);

#endif
