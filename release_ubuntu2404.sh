rm -rf build
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=off .. 
cd ..
cmake --build build --config Release -j8 --target package
