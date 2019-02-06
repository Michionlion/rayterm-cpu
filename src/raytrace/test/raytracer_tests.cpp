#include <gtest/gtest.h>
#include "raytracer.h"
#include <cstdio>

void progress_cb(float progress) {
    printf("\b\b\b%02d%%", int(progress * 100));
}

TEST(RaytracerTest, Success) {

    printf("00%");
    int status = raytrace_ppm("test_image.ppm", progress_cb);
    printf("\b\b\b100% -- Render Complete!\n");
    EXPECT_EQ(raytrace_ppm("test_image.ppm"), 0) << "Did not successfully generate a test image!";
}
