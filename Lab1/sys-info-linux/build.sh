#!/bin/sh

if [ ! -d "build" ]; then
    mkdir "build"
fi

g++ ./src/main.cpp -std=c++23 -O3 -DNDEBUG -s -fomit-frame-pointer -flto -o ./build/sys-info-linux