#!/bin/bash

if ! [ -d build ]; then
    mkdir build
fi

cd build
cmake -G "MSYS Makefiles" -DCMAKE_TOOLCHAIN_FILE=$HOME/Toolchain-mingw64.cmake ..
make 
