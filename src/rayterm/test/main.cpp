#include <gtest/gtest.h>
#include "terminal.h"
#include "raytracer.h"

TEST(RaytracerTest, Success) {
    EXPECT_EQ(raytrace_ppm("test_image.ppm"), 0) << "Did not successfully generate a test image!";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
