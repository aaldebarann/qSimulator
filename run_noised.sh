#!/bin/bash

rm -rf build/bin
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/bin/noised_sample