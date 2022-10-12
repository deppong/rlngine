#!/usr/bin/bash
# for linux
cmake --build build --config Release
cd build/Release
mv ../rlngine .
./rlngine
