#include "raytracer.h"
#include <cstdio>
#include "camera.h"
#include "raymath"
#include "world.h"

#ifndef SAMPLES
#define SAMPLES 32
#endif

#ifndef RES_MULT
#define RES_MULT 1.0
#endif

int raytrace_ppm(const char* filename, progress_callback cb /* = NULL */) {
    FILE* outfile = fopen(filename, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        return 1;
    }

    int width  = int(80 * RES_MULT);
    int height = int(52 * RES_MULT);

    World w;

    // diffuse material declarations
    Material* red     = new Lambertian(color(1, 0, 0));
    Material* green   = new Lambertian(color(0, 1, 0));
    Material* blue    = new Lambertian(color(0, 0, 1));
    Material* ground  = new Lambertian(color(0.8, 0.8, 0));
    Material* metal   = new Metal(color(0.6, 0.2, 0.3), 0.1);
    Material* mirror  = new Metal(color(0.25, 0.25, 0.25), 0.02);
    Material* diffuse = new Metal(color(0.3, 0.5, 0.8), 1);

    // geometric shape declarations
    geometry* ground_sphere = new sphere(vector(0, -100.5, -1), 100);
    // geometry* sphere1       = new sphere(vector(0, 0, -3), 1.0);
    // geometry* sphere2       = new sphere(vector(1.8, -0.25, -3), 0.75);
    // geometry* sphere3       = new sphere(vector(-2.75, 0.25, -3), 1.5);
    // geometry* metal4        = new sphere(vector(-0.5, -0.6, -1.75), 0.4);
    // geometry* mirror5       = new sphere(vector(104, 0, -3), 100);
    // geometry* diffuse6      = new sphere(vector(-1, 2, -12), 6);

    geometry* sphere7 = new sphere(vector(1, 0, -1), 0.5);
    geometry* sphere8 = new sphere(vector(0, 0, -1), 0.5);
    geometry* sphere9 = new sphere(vector(-1, 0, -1), 0.5);

    // // world object addition and creation
    w.add_object(new WorldObject(0, ground, &w, ground_sphere));
    // w.add_object(new WorldObject(1, red, &w, sphere1));
    // w.add_object(new WorldObject(2, green, &w, sphere2));
    // w.add_object(new WorldObject(3, blue, &w, sphere3));
    // w.add_object(new WorldObject(4, metal, &w, metal4));
    // w.add_object(new WorldObject(5, mirror, &w, mirror5));
    // w.add_object(new WorldObject(6, diffuse, &w, diffuse6));

    w.add_object(new WorldObject(7, new Metal(color(0.8, 0.6, 0.2), 1.0), &w, sphere7));
    w.add_object(new WorldObject(8, new Lambertian(color(0.1, 0.2, 0.5)), &w, sphere8));
    w.add_object(new WorldObject(9, new Dielectric(1.5), &w, sphere9));

    Camera* cam = new Camera(width, height, 90);

    fprintf(outfile, "P3\n%i %i\n255\n", width, height);
    intersection hit;
    float pixels = width * height;
    int pixel    = 0;
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            color outcol(0, 0, 0);
            for (int sample = 0; sample < SAMPLES; sample++) {
                scalar u = 2 * ((scalar(x) + random_scalar()) / scalar(width)) - 1;
                scalar v = 2 * ((scalar(y) + random_scalar()) / scalar(height)) - 1;
                ray r    = cam->get_screen_ray(u, v);
                outcol += w.trace(r, hit, 0);
            }

            // gamma correct outcol
            // raise to 1 / gamma (1/2 in our case)

            colori col((outcol / SAMPLES).array().sqrt());
            fprintf(outfile, "%i %i %i\n", col.r, col.g, col.b);
            if (cb != NULL) {
                cb(pixel++ / pixels);
            }
        }
    }
    fclose(outfile);
    return 0;
}
