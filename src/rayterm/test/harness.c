# include "stdio.h"
# include "string.h"
# include "raytracer.h"
# include "terminal.h"
# include "translator.h"

// header declarations
int raytracing_suite();
int interface_suite();

int main(int argc, char** argv) {
    if(argc == 0) {
        printf("Missing test suite identifier!");
        exit(-1);
    }

    int retval = 0;
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "raytracing") == 0) {
            retval += raytracing_suite();
        } else if (strcmp(argv[i], "interface") == 0) {
            retval += interface_suite();
        }
    }

    return retval;
}

int raytracing_suite() {
    printf("Running ray-tracing test suite");
    // TODO: set up ray-tracing world
    // possible first version:
    //rt_sphere(0, -50, 0, 100);
    //rt_sphere(0, 0, 0, 2);
    //rt_sphere(0, 2, 0, 1);

    // render one ppm image
    int success = raytrace_ppm("test_image.ppm");
    return success;
}

int interface_suite() {
    printf("Running ncurses interface test suite");
    return 0;
}
