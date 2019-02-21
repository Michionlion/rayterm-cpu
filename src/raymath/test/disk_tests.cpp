#include <gtest/gtest.h>
#include "disk.h"
#include "intersection.h"

TEST(Disk, IntersectsTakesRay) {
    disk object(vector(0, 0, 0), vector(0, 1, 0), 1);
    ray light(vector(0, 1, 0), vector(1, 1, 1));
    EXPECT_NO_THROW(object.intersects(light));
}

TEST(Disk, RayIntersection) {
    EXPECT_TRUE(disk(vector(0, 0, 0), vector(0, 1, 0), 2.5)
                    .intersects(ray(vector(0, 1, -3), vector(0, -1, 1))));
    EXPECT_FALSE(disk(vector(0, 0, 0), vector(0, 1, 0), 2.5)
                     .intersects(ray(vector(0, 1, -3), vector(0, 0, -1))));
    EXPECT_FALSE(disk(vector(0, 0, 0), vector(0, 1, 0), 2.5)
                     .intersects(ray(vector(0, 1, -3), vector(0, 1, -1))));
    EXPECT_FALSE(disk(vector(0, 0, 0), vector(0, 1, 0), 1.5)
                     .intersects(ray(vector(0, 1, -3), vector(0, -1, 1))));
}
