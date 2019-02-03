#include <stdio.h>
#include "camera.h"
#include "raymath"

int raytrace_ppm(const char* filename) {
    FILE* outfile = fopen(filename, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        return 1;
    }

    int width  = 400;
    int height = 200;

    sphere object(vector(0, 0, -5), 2.5);
    Camera* cam = new Camera(width, height);

    fprintf(outfile, "P3\n%i %i\n255\n", width, height);
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            scalar u     = 2 * ((scalar(x) + 0.5) / scalar(width)) - 1;
            scalar v     = 2 * ((scalar(y) + 0.5) / scalar(height)) - 1;
            ray r        = cam->get_screen_ray(u, v);
            scalar yness = (r.direction().normalized()[1] + 1) / 2;
            color outcol = (1 - yness) * color(1, 1, 1) + yness * color(0, 0, 0);

            intersection hit = object.intersects(r);
            if (hit) {
                outcol = color(hit.normal + vector(1, 1, 1)) / 2;
            }

            colori col(outcol);
            // fprintf(outfile, "%i %i %i\n", 0, 0, 0);
            fprintf(outfile, "%i %i %i\n", col.r, col.g, col.b);
            // fprintf(outfile, "%i %i %i\n", int(yness * 255), int(yness * 255), int(yness * 255));
            // fprintf(outfile, "%i %i %i\n", int((u + 1) / 2 * 255), int((v + 1) / 2 * 255),
            //     int((v + u + 2) / 4 * 255));
        }
    }
    fclose(outfile);

    return 0;
}
