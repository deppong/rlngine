#pragma once
#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <stdint.h>
#include <string>

/**
 * Physics Related Components
*/
struct PhysicsComponent {
    int vel_x, vel_y, solid;

    PhysicsComponent() = default;
    PhysicsComponent(const int& vel_x = 0, const int& vel_y = 0, const int& solid = 1):
        vel_x(vel_x), vel_y(vel_y), solid(solid) {};
};

struct TransformComponent {
    int x, y;

    TransformComponent() = default;
    TransformComponent(const int& x = 0, const int& y = 0):
        x(x), y(y) {};
};

struct RenderComponent  {
    int tile;
    uint32_t color, bg_color;

    RenderComponent() = default;
    RenderComponent(const int &chr = 0, const uint32_t& color = 0, const uint32_t& bg_color = 0):
        tile(chr), color(color), bg_color(bg_color){};
};

struct ControllableComponent {
    bool inControl;

    ControllableComponent() = default;
    ControllableComponent(const bool& inControl = false):
        inControl(inControl)
    {};
};


// this is not being used correctly at the moment
struct DecorativeComponent {
};

struct StatsComponent {
    int STR, DEX, CON;

    StatsComponent() = default;
    StatsComponent(const int& str = 0, const int& dex = 0, const int& con = 0):
        STR(str), DEX(dex), CON(con)
    {};
};

struct NameComponent {
    std::string name, name_plr, description;

    NameComponent() = default;
    NameComponent(const std::string& name = "", const std::string& name_plr = "", const std::string& description = ""):
        name(name), name_plr(name_plr), description(description) {};
    
};

#endif // COMPONENTS_HPP