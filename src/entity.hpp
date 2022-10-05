#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "color.hpp"

struct entity_t {
    // transform (these coordinates are world coordinates)
    int x, y;
    // atlas texture coordinates
    int tile_x, tile_y;
    uint32_t color, bg_color;
};

#endif