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
