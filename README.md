# RLEngine
An engine made for developing traditional roguelikes programmed in sdl/C++

Still a wip and under lots of development


# Build Instructions
For Linux you must install `cmake` and `libsdl2-dev`.
The lib and include directories are only necessary for the windows build.

run the commands

```
mkdir build
cmake -B build -S src
```

On windows you must edit in `/build/CMakeCache.txt` the SDL2_DIR variable to the path of this folder.

afterwards run the following commands on either windows or linux:
```
cmake -B build -S src
cd build
cmake --build .
```

On windows, be sure the SDL2.dll is in the same directory as the executable before executing. This file can be found in the lib directory