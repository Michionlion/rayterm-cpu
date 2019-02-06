#include <gtest/gtest.h>
#include "raymath"
#include "world.h"

TEST(World, CanAddGeometrys) {
    World w;
    Material* red = new Lambertian(color(1, 0, 0));
    Material* green = new Lambertian(color(0, 1, 0));
    Material* blue = new Lambertian(color(0, 0, 1));
    geometry* sphere1 = new sphere(vector(0, 0, 0), 2);
    geometry* sphere2 = new sphere(vector(0, 0, 2), 4);
    geometry* sphere3 = new sphere(vector(0, 0, 0), 5);
    w.add_object(new WorldObject(1, red, &w, sphere1));
    w.add_object(new WorldObject(2, green, &w, sphere2));
    w.add_object(new WorldObject(3, blue, &w, sphere3));
}

TEST(World, CanIntersectGeometrys) {
    World w;
    Material* red = new Lambertian(color(1, 0, 0));
    Material* green = new Lambertian(color(0, 1, 0));
    Material* blue = new Lambertian(color(0, 0, 1));
    geometry* sphere1 = new sphere(vector(0, 0, 0), 2);
    geometry* sphere2 = new sphere(vector(0, 0, 2), 4);
    geometry* sphere3 = new sphere(vector(0, 0, 0), 5);
    w.add_object(new WorldObject(1, red, &w, sphere1));
    w.add_object(new WorldObject(2, green, &w, sphere2));
    w.add_object(new WorldObject(3, blue, &w, sphere3));

    ray r(vector(0, 0, 15), vector(0, 0, -1));
    intersection hit;
    w.intersects(r, hit);
    vector expected(0, 0, 6);
    EXPECT_TRUE(hit) << "Failed to hit anything";
    EXPECT_EQ(hit.id, 2) << "Failed to hit object 2";
    EXPECT_TRUE(hit.position.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << hit.position[0] << ", " << hit.position[1] << ", " << hit.position[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}
