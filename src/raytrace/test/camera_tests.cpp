#include <gtest/gtest.h>
#include "camera.h"

TEST(Camera, ToWorldDir) {
    vector expected, actual;
    Camera* cam = new Camera(80, 40, 90);

    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(0, 0, -1);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->look(vector(1, 0, 0));
    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(1, 0, 0);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->look(vector(0, 3, -3));
    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(0, -3, 3).normalized();
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->look(vector(1, 1, -1));
    actual = cam->toWorldDir(vector(0, 0, 1));
    expected = vector(-1, -1, -1).normalized();
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}

TEST(Camera, ToWorldDirDifferentOrigin) {
    vector expected, actual;
    Camera* cam = new Camera(80, 40, 90);

    cam->position(vector(1, 0, 0));
    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(0, 0, -1);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->look(vector(1, 0, 0));
    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(1, 0, 0);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->look(vector(0, 3, -3));
    actual = cam->toWorldDir(vector(0, 0, -1));
    expected = vector(0, -3, 3).normalized();
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}

TEST(Camera, ToWorldPos) {
    vector expected, actual;
    Camera* cam = new Camera(80, 40, 90);

    actual = cam->toWorldPos(vector(0, 0, 0));
    expected = vector(0, 0, 0);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->position(vector(1, 2, 3));
    actual = cam->toWorldPos(vector(0, 0, 0));
    expected = vector(1, 2, 3);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";

    cam->position(vector(1, -4, 7));
    actual = cam->toWorldPos(vector(3, 2, -2));
    expected = vector(4, -2, 5);
    EXPECT_TRUE(actual.isApprox(expected, 0.0001))
        << "  Actual: "
        << "{" << actual[0] << ", " << actual[1] << ", " << actual[2] << "}"
        << "\nExpected: "
        << "{" << expected[0] << ", " << expected[1] << ", " << expected[2] << "}";
}
