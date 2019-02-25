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
    Material* grass   = new Lambertian(color(0.8, 0.8, 0));
    Material* metal   = new Metal(color(0.6, 0.2, 0.3), 0.4);
    Material* mirror  = new Metal(color(0.6, 0.6, 0.9), 0.04);
    Material* diffuse = new Metal(color(0.3, 0.5, 0.8), 0.75);
    Material* glass   = new Dielectric(1.5);

    // vector focus(0, 2, -2);

    // geometric shape declarations
    // geometry* pointer       = new sphere(focus, 0.3);
    geometry* ground   = new disk(vector(0, -1, -1.2), vector(0, 1, 0), 25);
    geometry* sphere1  = new sphere(vector(0, 0, -3), 1.0);
    geometry* sphere2  = new sphere(vector(2.0, -0.25, -3), 0.75);
    geometry* sphere3  = new sphere(vector(-2.75, 0.25, -3), 1.5);
    geometry* metal4   = new sphere(vector(-0.5, -0.5, -1.5), 0.5);
    geometry* mirror5  = new sphere(vector(15, 0, -3), 10);
    geometry* diffuse6 = new sphere(vector(-1, 2, -12), 6);

    // geometry* sphere7  = new sphere(vector(1, 0, -1.25), 0.5);
    // geometry* sphere8  = new sphere(vector(0, 0, -1.25), 0.5);
    // geometry* sphere9  = new sphere(vector(-1, 0, -1.25), 0.5);
    // geometry* sphere10 = new sphere(vector(-1, 0, -1.25), -0.45);

    // refractive scene tests
    geometry* sphere7 = new sphere(vector(0.75, 0, -1.5), 0.5);
    geometry* sphere8 = new sphere(vector(-0.75, 0, -1.5), 0.5);
    geometry* sphere9 = new sphere(vector(0, 0, -0.8), 0.5);

    // // world object addition and creation
    w.add_object(new WorldObject(0, grass, &w, ground));
    // w.add_object(new WorldObject(1, red, &w, sphere1));
    // w.add_object(new WorldObject(2, glass, &w, sphere2));
    // w.add_object(new WorldObject(3, mirror, &w, sphere3));
    // w.add_object(new WorldObject(4, metal, &w, metal4));
    // w.add_object(new WorldObject(5, mirror, &w, mirror5));
    // w.add_object(new WorldObject(6, blue, &w, diffuse6));

    // w.add_object(new WorldObject(11, new Lambertian(color(0, 0, 0)), &w, pointer));

    w.add_object(new WorldObject(7, new Metal(color(0.8, 0.6, 0.2), 0.25), &w, sphere7));
    // w.add_object(new WorldObject(7, new Metal(color(1, 1, 1), 0.0), &w, sphere7));
    w.add_object(new WorldObject(8, new Lambertian(color(0.1, 0.2, 0.5)), &w, sphere8));
    w.add_object(new WorldObject(9, new Dielectric(1.5), &w, sphere9));
    // w.add_object(new WorldObject(10, new Dielectric(1.5), &w, sphere10));

    Camera* cam = new Camera(width, height, 74);
    cam->position_look(vector(0, 0.5, 0.5), vector(0, 0, -1.2));

    fprintf(outfile, "P3\n%i %i\n255\n", width, height);
    intersection hit;
    float pixels = width * height;
    int pixel    = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            color outcol(0, 0, 0);
            ray r;
            for (int sample = 0; sample < SAMPLES; sample++) {
                scalar u = 2 * ((scalar(x) + random_scalar()) / scalar(width)) - 1;
                scalar v = 1 - 2 * ((scalar(y) + random_scalar()) / scalar(height));
                r        = cam->get_screen_ray(u, v);
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
