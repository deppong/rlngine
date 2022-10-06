# RLEngine
A framework made for developing traditional roguelikes programmed in sdl/C++. The main goals of this program is to simplify making a tilebased game in C++ mostly for myself. You could potentially make a traditional roguelike using this simple framework around SDL 2.0

## Still a wip and under lots of development

# Build Instructions

Libraries Used
- [SDL2](https://www.libsdl.org/)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
- [entt](https://github.com/skypjack/entt)

For Linux you must install `cmake` and `libsdl2-dev`.
The lib directory is only necessary for the windows build.
Only `stb_image.h` and `entt.h` are required for linux, all SDL header files are covered through the `libsdl2-dev` package

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
Also on windows, when running, make sure the directory you are running from is `.../rlngine/build/Debug/rlngine.exe`, and for linux currently
on this build you also need move the rlngine executable to a secondary directory inside of the `build` directory
