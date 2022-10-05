#ifndef ENTITY_HPP
#define ENTITY_HPP


struct entity_t {
    // transform (these coordinates are world coordinates)
    int x, y;
    // character to use
    uint16_t chr;
    uint32_t color, bg_color;

    // not sure if 100% needed, feels icky and redunant
    entity_t(int x, int y, uint16_t chr, uint32_t color, uint32_t bg_color):
        x(x),
        y(y),
        chr(chr),
        color(color),
        bg_color(bg_color)
     {};
};

#endif