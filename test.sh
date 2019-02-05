#!/bin/bash
# Run raytraceTest only

gradle checkRaytraceTestReleaseGoogleTestExe

if [[ "$1" = "-o" ]]; then
    exec gthumb build/test-results/raytraceTest/release/test_image.ppm &> /dev/null &
    disown
fi
