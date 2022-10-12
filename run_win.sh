#!/usr/bin/bash
# for windows
cmake --build build --config Release
cd build/Release
./rlngine.exe
