mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PREFIX ../
#    -DENABLE_LEGACY=1 \

cmake --build . --config Release

cmake --build . --target install
