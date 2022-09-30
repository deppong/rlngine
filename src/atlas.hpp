#ifndef ATLAS_HPP
#define ATLAS_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>

class Atlas {
    public:
        int tex_width;
        Atlas(int texture_width);
        ~Atlas();

        int load_texture(const char* filename);
        std::vector<uint32_t> get_texture(int x, int y);

    private:
        int texture_size, texture_count;
        int atlas_w, atlas_h, nchannels;
        std::vector<uint32_t> data;
};

#endif