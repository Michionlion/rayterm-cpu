#!/bin/bash
# Run raytraceTest only

gradle checkRaytraceTestReleaseGoogleTestExe

exec gthumb build/test-results/raytraceTest/release/test_image.ppm &> /dev/null &
disown
