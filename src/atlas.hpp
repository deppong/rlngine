#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Atlas {
    public:
        Atlas();
        ~Atlas();

        int load_texture(const char* filename, int tex_width);
        std::vector<uint32_t> get_texture(int x, int y);

    private:
        int texture_size, texture_count;
        int w, h, nchannels;
        std::vector<uint32_t> data;
};