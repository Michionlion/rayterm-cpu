#include <gtest/gtest.h>
#include "intersection.h"
#include "sphere.h"

TEST(Intersection, BoolEvaluation) {
    intersection hit(true);
    if (hit) {
        SUCCEED();
    } else {
        ADD_FAILURE() << "intersection did not evaluate to true when hit was true";
    }

    hit.hit = false;
    if (hit) {
        ADD_FAILURE() << "intersection did not evaluate to false when hit was false";
    } else {
        SUCCEED();
    }

    hit.hit = false;
    if (!hit) {
        SUCCEED();
    } else {
        ADD_FAILURE() << "!intersection did not evaluate to true when hit was false";
    }

    hit.hit = true;
    if (!hit) {
        ADD_FAILURE() << "!intersection did not evaluate to false when hit was true";
    } else {
        SUCCEED();
    }
}

TEST(Intersection, SphereRayIntersectionPosition) {
    intersection hit(false);
    vector expected;

    hit      = sphere(vector(0, 0, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 0, 1)));
    expected = vector(0, 0, -2);
    EXPECT_TRUE(hit.position.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << hit.position[0] << ", " << hit.position[1] << ", " << hit.position[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    hit      = sphere(vector(0, 3, 0), 2).intersects(ray(vector(0, 0, -3), vector(0, 1, 0.5)));
    expected = vector(0, 2.27335, -1.863325);
    EXPECT_TRUE(hit.position.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << hit.position[0] << ", " << hit.position[1] << ", " << hit.position[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}
