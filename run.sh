#!/bin/sh

gradle build --console=rich

if [ $? -eq 0 ]; then
    TYPE="$1"
    if [ -z "$TYPE" ]; then
        TYPE="debug"
    fi
    rm error.log

    printf "\nRunning $TYPE executable...\n"
    sleep 0.5

    #LD_LIBRARY_PATH=build/libs/rayterm/shared/$TYPE/ ./build/exe/rtexplore/$TYPE/rtexplore 2> error.log
    ./build/exe/rtexplore//$TYPE/rtexplore 2> error.log

    LOG=$(cat error.log)

    if [ -z "$LOG" ]; then
        printf "\n -- No Errors -- \n"
    else
        printf "\n -- Error Log -- \n"
        echo "$LOG"
    fi
fi
