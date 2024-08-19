@echo off
if exist build (
    rmdir /s build
)
mkdir build
cd build
cmake -G Ninja ..
ninja

cd ..