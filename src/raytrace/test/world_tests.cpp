#include <gtest/gtest.h>
#include "raymath"
#include "world.h"

TEST(World, CanAddGeometrys) {
    World w;

    geometry* sphere1 = new sphere(vector(0, 0, 0), 2);
    w.add_object(sphere1);
    geometry* sphere2 = new sphere(vector(0, 0, 2), 2);
    w.add_object(sphere2);
    geometry* sphere3 = new sphere(vector(0, 0, 0), 5);
    w.add_object(sphere3);
}

TEST(World, CanIntersectGeometrys) {
    World w;

    geometry* sphere1 = new sphere(vector(0, 0, 0), 2);
    w.add_object(sphere1);
    geometry* sphere2 = new sphere(vector(0, 0, 2), 4);
    w.add_object(sphere2);
    geometry* sphere3 = new sphere(vector(0, 0, 0), 5);
    w.add_object(sphere3);

    ray r(vector(0, 0, 15), vector(0, 0, -1));
    intersection hit;
    w.intersects(r, hit);
    vector expected(0, 0, 6);
    EXPECT_TRUE(hit) << "Failed to hit sphere2";
    EXPECT_TRUE(hit.position.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << hit.position[0] << ", " << hit.position[1] << ", " << hit.position[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}
