# include "stdio.h"

int raytrace_ppm(const char* filename) {

    FILE* outfile = fopen(filename, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s!\n", filename);
        return 1;
    }

    int width = 128;
    int height = 128;

    fprintf(outfile, "P3\n%i %i\n255\n", width, height);
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int r = (int) (255.99 * x / width);
            int g = (int) (255.99 * y / height);
            int b = 0.2;
            fprintf(outfile, "%i %i %i", r, g, b);
        }
    }
    fclose(outfile);

    return 0;
}
