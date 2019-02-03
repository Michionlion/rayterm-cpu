#include <gtest/gtest.h>
#include "sphere.h"

TEST(Sphere, IntersectsTakesRay) {
    sphere object(vector(4, 4, 4), 4);
    ray light(vector(0, 0, 0), vector(1, 1, 1));
    EXPECT_NO_THROW(object.intersects(light));
}

TEST(Sphere, RayIntersection) {
    EXPECT_TRUE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 0, 1))));
    EXPECT_FALSE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
    EXPECT_FALSE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
    EXPECT_FALSE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 0, 1))));
    EXPECT_FALSE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 0.75, 1))));
    EXPECT_TRUE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
