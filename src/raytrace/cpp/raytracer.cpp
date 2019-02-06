#include "raytracer.h"
#include <cstdio>
#include "camera.h"
#include "raymath"
#include "world.h"

#define MAX_DEPTH 64
#define ABSORPTION 0.5
#define SAMPLES_PER_PIXE  128

int raytrace_ppm(const char* filename) {
    FILE* outfile = fopen(filename, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        return 1;
    }

    int width  = 16 * 40;
    int height = 9 * 40;
    //int width = 80;
    //int height = 52;

    World world;

    world.add_object(new sphere(vector(0, -301, -3), 300));
    world.add_object(new sphere(vector(0, 0, -3), 1.25));
    world.add_object(new sphere(vector(2, -0.25, -3), 0.75));

    // world.add_object(new sphere(vector(0, -1, -3), 1));
    // world.add_object(new sphere(vector(0, 1, -2.5), 1.5));
    // world.add_object(new sphere(vector(0, 0, 0), 2));

    Camera* cam = new Camera(width, height, 78);

    fprintf(outfile, "P3\n%i %i\n255\n", width, height);
    intersection hit;
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            color outcol(0, 0, 0);
            for (int sample = 0; sample < SAMPLES_PER_PIXEL; sample++) {
                scalar u = 2 * ((scalar(x) + random_scalar()) / scalar(width)) - 1;
                scalar v = 2 * ((scalar(y) + random_scalar()) / scalar(height)) - 1;
                ray r    = cam->get_screen_ray(u, v);
                outcol += trace(r, world, hit, 0);
            }

            // gamma correct outcol
            // raise to 1 / gamma (1/2 in our case)

            colori col((outcol / SAMPLES_PER_PIXEL).array().sqrt());
            // fprintf(outfile, "%i %i %i\n", 0, 0, 0);
            fprintf(outfile, "%i %i %i\n", col.r, col.g, col.b);
            // fprintf(outfile, "%i %i %i\n", int(yness * 255), int(yness * 255), int(yness * 255));
            // fprintf(outfile, "%i %i %i\n", int((u + 1) / 2 * 255), int((u + 1) / 2 * 255),
            //     int((u + 1) / 2 * 255));
        }
    }
    fclose(outfile);

    return 0;
}

color trace(ray r, World& world, intersection& hit, int depth) {
    if (depth < MAX_DEPTH) {
        world.intersects(r, hit);
        if (hit) {
            vector bounce(hit.position + hit.normal + random_in_usphere());
            // color with normal
            // return color(hit.normal + vector(1, 1, 1)) / 2;
            return ABSORPTION *
                   trace(ray(hit.position, bounce - hit.position), world, hit, depth + 1);
        }
    }

    scalar yness = (r.direction().normalized().y() + 1) / 2;
    return (1 - yness) * color(1, 1, 1) + yness * color(0.5, 0.7, 1);
}
