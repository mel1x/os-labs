@echo off

if not exist "build" (
    mkdir "build"
)

echo Building for x86_64 (64-bit Intel/AMD)...
g++ ./src/main.cpp -std=c++17 -O2 -DNDEBUG -s -static -static-libgcc -static-libstdc++ -o ./build/sys-info-win-x86_64.exe

echo Done!