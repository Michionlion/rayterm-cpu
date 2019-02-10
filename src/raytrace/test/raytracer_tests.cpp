#include <gtest/gtest.h>
#include <chrono>
#include <cstdio>
#include "raytracer.h"

void progress_cb(float progress) { printf("\b\b\b%02d%%", int(progress * 100)); }

TEST(RaytracerTest, Success) {
    printf("00%");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int status = raytrace_ppm("test_image.ppm", progress_cb);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printf("\b\b\b100% -- Render Complete!\n");

    printf("Completed in %dms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    EXPECT_EQ(raytrace_ppm("test_image.ppm"), 0) << "Did not successfully generate a test image!";
}
