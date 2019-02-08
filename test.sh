#!/bin/bash
# Run raytraceTest only

gradle installRaytraceTestReleaseGoogleTestExe

if  [[ "$?" != "0" ]]; then
    exit;
fi

./build/install/raytraceTest/release/raytraceTest --gtest_filter=RaytracerTest.Success

if [[ "$1" = "-o" ]]; then
    exec feh --force-aliasing -Z test_image.ppm &
    disown
fi
