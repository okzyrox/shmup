@echo off
echo "-> Cleaning build directory"
if exist build (
    rmdir /s build
)
echo "-> Building project"
mkdir build
cd build
cmake -G Ninja ..
ninja

echo "-> Copying resources"

xcopy ..\resources\* .\resources\ /E

cd ..