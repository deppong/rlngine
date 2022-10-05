#ifndef ENTITY_HPP
#define ENTITY_HPP


struct entity_t {
    // transform (these coordinates are world coordinates)
    int x, y;
    // character to use
    uint16_t chr;
    uint32_t color, bg_color;
};

#endif