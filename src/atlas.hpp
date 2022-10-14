#pragma once
#ifndef ATLAS_HPP
#define ATLAS_HPP

#include "color.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <array>


class Atlas {
    public:
        int tex_width;
        Atlas(int texture_width);
        ~Atlas();

        int load_atlas(const char* filename);
        std::vector<uint32_t>& get_tile(int tile);
        std::vector<uint32_t> set_color(std::vector<uint32_t> tex, uint32_t fg, uint32_t bg);

        std::vector<uint32_t> data;

        std::vector<std::vector<uint32_t>> textures;

    private:
        std::vector<uint32_t> get_texture_from_atlas(int x, int y);
        int texture_size, texture_count;
        int atlas_w, atlas_h, nchannels;
};

#endif // ATLAS_HPP
