#include "raytracer.h"
#include <cstdio>
#include "camera.h"
#include "raymath"
#include "world.h"

#define MAX_DEPTH 32
#define ABSORPTION 0.5
#define SAMPLES_PER_PIXEL 8

int raytrace_ppm(const char* filename) {
    FILE* outfile = fopen(filename, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        return 1;
    }

    int width  = 16 * 20;
    int height = 9 * 20;
    //int width = 80;
    //int height = 52;

    World w;

    // diffuse material declarations
    Material* red = new Lambertian(color(1, 0, 0));
    Material* green = new Lambertian(color(0, 1, 0));
    Material* blue = new Lambertian(color(0, 0, 1));
    Material* ground = new Lambertian(color(0.3, 0.25, 0.4));

    // geometric shape declarations
    geometry* ground_sphere = new sphere(vector(0, -301, -3), 300);
    geometry* sphere1 = new sphere(vector(0, 0, -3), 1.25);
    geometry* sphere2 = new sphere(vector(2, -0.25, -3), 0.75);
    geometry* sphere3 = new sphere(vector(-4, 0.25, -3), 1.5);

    // world object addition and creation
    w.add_object(new WorldObject(0, ground, &w, ground_sphere));
    w.add_object(new WorldObject(1, red, &w, sphere1));
    w.add_object(new WorldObject(2, green, &w, sphere2));
    w.add_object(new WorldObject(3, blue, &w, sphere3));

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
                outcol += w.trace(r, hit, 0);
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
