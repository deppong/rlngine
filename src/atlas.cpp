#include "atlas.hpp"

#define STB_IMAGE_IMPLEMENTATION
#ifdef __unix__
    #include "../include/stb_image.h"
#elif defined _WIN32
    #include "stb_image.h"
#endif

Atlas::Atlas(int texture_width):
    texture_size(0),
    texture_count(0),
    tex_width(texture_width),
    atlas_w(0),
    atlas_h(0),
    nchannels(-1)
{
    
};

Atlas::~Atlas() {};

std::vector<uint32_t>& Atlas::get_tile(int tile) {
    return textures.at(tile);
}

// deprecated?
// std::vector<uint32_t> Atlas::from_char(uint16_t c) {
//     auto search = std::find(CP437.begin(), CP437.end(), c);
//     if (search == CP437.end()) {
//         std::cerr << "character not found in cp437!\ncharacter searched: " << c << std::endl;
//         return textures[0];
//     }
//     // yikes this is a mouthful, basically it's just finding the char value supplied in the big table
//     // listed in atlas.hpp
//     auto index = std::distance(CP437.begin(), search);
//     return textures[index];
// }

std::vector<uint32_t> Atlas::set_color(std::vector<uint32_t> tex, uint32_t fg, uint32_t bg) {
    std::vector<uint32_t> new_tex;
    for (uint32_t byte : tex) {
        if (byte == COLOR_BLACK)  {
            new_tex.push_back(bg);
        } else {
            new_tex.push_back(fg);
        }
    }

    return new_tex;
}


int Atlas::load_atlas(const char* filename) {
    
    unsigned char *pixels = stbi_load(filename, &atlas_w, &atlas_h, &nchannels, 0);
    if(!pixels) {
        std::cerr << "Failed to load image:\n" << stbi_failure_reason() << std::endl;
        stbi_image_free(pixels);
        return -1;
    }
    
    std::cout << "width: " << atlas_w << " height: " << atlas_h << " channels: " << nchannels << std::endl;

    if(nchannels != 4) {
        std::cerr << "Image must have 32-bit color, support for lower bit color will be available in the future" << std::endl;
        stbi_image_free(pixels);
        return -1;
    }

    if(atlas_w != atlas_h) {
        std::cerr << "Atlas must contain square textures packed in a square shape (ie, width of atlas must equal the height" << std::endl;
        stbi_image_free(pixels);
        return -1;
    }


    texture_count = (atlas_w/tex_width) * (atlas_w/tex_width);
    std::cout << "texture count: " << texture_count << std::endl;

    std::cout << pixels[0] << std::endl;

    // TODO: merge this group of loops with the lower, as
    // there is really no need to store the original atlas once it's
    // been processed into the list of tiles
    for (int y = 0; y < atlas_h; y++) {
        for (int x = 0; x < atlas_w; x++) {
            uint8_t r = pixels[(x + y*atlas_w) * 4 + 0];
            uint8_t g = pixels[(x + y*atlas_w) * 4 + 1];
            uint8_t b = pixels[(x + y*atlas_w) * 4 + 2];
            uint8_t a = pixels[(x + y*atlas_w) * 4 + 3];
            // TODO: get the pack_color() function back in here
            data.push_back(((a<<24) + (b<<16) + (g<<8) + r));
        }
    }

    // yeah lets just ignore the fact that we have 4 for loops lol
    // at least we only have to do this once
    for (int y = 0; y < (atlas_h/tex_width); y++) {
        for (int x = 0; x < (atlas_w/tex_width); x++) {
            textures.push_back(get_texture_from_atlas(x, y));
        }
    }


    stbi_image_free(pixels);
    return 0;
}


std::vector<uint32_t> Atlas::get_texture_from_atlas(int x, int y) {
    std::vector<uint32_t> tex;
    for (int j = 0; j < tex_width; j++) {
        for (int i = 0; i < tex_width; i++) {

            int x_offset = x*tex_width;
            int y_offset = y*tex_width;
            int next_pixel = (i + x_offset) + (j + y_offset)*atlas_w;

            tex.push_back(data[next_pixel]);
        }
    }
    return tex;
     
}
