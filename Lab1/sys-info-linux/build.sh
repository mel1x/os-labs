#!/bin/sh

if [ ! -d "build" ]; then
    mkdir "build"
fi

# Для x86_64 (Intel/AMD)
g++ ./src/main.cpp -std=c++17 -O2 -DNDEBUG -s -o ./build/sys-info-linux-x86_64

# Для ARM64 (Raspberry Pi 4, серверы ARM)
aarch64-linux-gnu-g++ ./src/main.cpp -std=c++17 -O2 -DNDEBUG -s -o ./build/sys-info-linux-arm64

# Для ARM 32-bit (старые Raspberry Pi)
arm-linux-gnueabihf-g++ ./src/main.cpp -std=c++17 -O2 -DNDEBUG -s -o ./build/sys-info-linux-armv7