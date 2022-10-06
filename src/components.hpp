#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <stdint.h>
#include <string>

struct NameComponent {
    std::string name, name_plr, description;
    
};

struct TransformComponent {
    int x, y;

    TransformComponent() = default;
    TransformComponent(const int& x, const int& y):
        x(x), y(y) {};
};

struct RenderComponent  {
    int tile;
    uint32_t color, bg_color;

    RenderComponent() = default;
    RenderComponent(const char& chr, const uint32_t& color, const uint32_t& bg_color):
        tile(chr), color(color), bg_color(bg_color) {};
};

#endif