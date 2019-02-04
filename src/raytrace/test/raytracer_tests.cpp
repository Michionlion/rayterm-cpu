#include <gtest/gtest.h>
#include "raytracer.h"

TEST(RaytracerTest, Success) {
    EXPECT_EQ(raytrace_ppm("test_image.ppm"), 0) << "Did not successfully generate a test image!";
}
