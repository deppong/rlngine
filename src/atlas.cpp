#include "atlas.hpp"

Atlas::Atlas():
    texture_size(0),
    texture_count(0),
    w(0),
    h(0),
    nchannels(0)
{};

Atlas::~Atlas() {};

int Atlas::load_texture(const char* filename, int tex_width) {
    unsigned char *pixels = stbi_load(filename, &w, &h, &nchannels, 0);
    if(!pixels) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    if(w != h) {
        std::cerr << "Atlas must contain square textures packed in a square shape (ie, width of atlas must equal the height" << std::endl;
        return -1;
    }

    texture_count = (w/tex_width) * (w/tex_width);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint8_t r = pixels[(x + y*w) * 4 + 0];
            uint8_t g = pixels[(x + y*w) * 4 + 1];
            uint8_t b = pixels[(x + y*w) * 4 + 2];
            uint8_t a = pixels[(x + y*w) * 4 + 3];
            data.push_back((a<<24) + (b<<16) + (g<<8) + r);
        }
    }
    
    stbi_image_free(pixels);
    return 0;
}

