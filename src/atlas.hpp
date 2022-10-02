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
        std::vector<uint32_t> data;

        // The idea here is when you load the atlas, it will
        // actually precompute all of the textures to this
        // vector of textures. This will speed up the rendering 
        // of any tiles/sprites/textures immensely!
        std::vector<std::vector<uint32_t>> textures;

    private:
        std::vector<uint32_t> get_texture_from_atlas(int x, int y);
        int texture_size, texture_count;
        int atlas_w, atlas_h, nchannels;
};

#endif