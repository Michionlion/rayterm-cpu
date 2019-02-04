#include <gtest/gtest.h>
#include "intersection.h"
#include "sphere.h"

TEST(Sphere, IntersectsTakesRay) {
    sphere object(vector(4, 4, 4), 4);
    ray light(vector(0, 0, 0), vector(1, 1, 1));
    EXPECT_NO_THROW(object.intersects(light));
}

TEST(Sphere, RayIntersection) {
    EXPECT_TRUE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 0, 1))));
    EXPECT_FALSE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 0, -1))));
    EXPECT_FALSE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
    EXPECT_FALSE(sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
    EXPECT_FALSE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 0, 1))));
    EXPECT_FALSE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 0.75, 1))));
    EXPECT_TRUE(sphere(vector(0, 5, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.75))));
}

TEST(Geometry, SphereGeometryInheritsOverloadedIntersects) {
    intersection hit;
    sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 0, 1)), hit);
    EXPECT_TRUE(hit);
    sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 2, -3), vector(0, 0, 1)), hit);
    EXPECT_FALSE(hit);

    intersection hit2 =
        sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 0, -3), vector(0, 0, 1)));
    EXPECT_TRUE(hit2);
    intersection hit3 =
        sphere(vector(0, 0, 0), 1).intersects(ray(vector(0, 2, -3), vector(0, 0, 1)));
    EXPECT_FALSE(hit3);
}
