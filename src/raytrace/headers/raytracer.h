#ifndef _RAYTERM_RAYTRACER_H_
#define _RAYTERM_RAYTRACER_H_
#include "raymath"
#include "world.h"

typedef void (*progress_callback)(float);

int raytrace_ppm(const char* filename, progress_callback cb = NULL);

color trace(ray r, World& world, intersection& hit, int depth);

#endif
