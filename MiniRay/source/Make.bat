echo "Compiling MiniRay"
g++ -std=c++11 camera.cpp miniray.cpp plane.cpp scene.cpp sphere.cpp -O3 -o miniray.exe
echo "Done!"