@echo off

if not exist "build" (
    mkdir "build"
)

g++ ./src/main.cpp -std=c++23 -O3 -DNDEBUG -s -fomit-frame-pointer -flto -o ./build/sys-info-win.exe