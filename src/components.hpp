#pragma once
#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <stdint.h>
#include <string>

/**
 * Physics Related Components
*/
struct PhysicsComponent {
    int vel_x, vel_y;

    PhysicsComponent() = default;
    PhysicsComponent(const int& vel_x, const int& vel_y):
        vel_x(vel_x), vel_y(vel_y) {};
    PhysicsComponent(const int& vel_x, const int& vel_y, const bool& inControl):
        vel_x(vel_x), vel_y(vel_y) {};
};

struct TransformComponent {
    int x, y;

    TransformComponent() = default;
    TransformComponent(const int& x, const int& y):
        x(x), y(y) {};
};

struct RenderComponent  {
    std::vector<uint32_t> tile;
    uint32_t color, bg_color;

    RenderComponent() = default;
    RenderComponent(const std::vector<uint32_t> &chr, const uint32_t& color, const uint32_t& bg_color):
        tile(chr), color(color), bg_color(bg_color){};
};

struct ControllableComponent {
    bool inControl;

    ControllableComponent() = default;
    ControllableComponent(const bool& inControl):
        inControl(inControl)
    {};
};


// this is not being used correctly at the moment
struct DecorativeComponent {
};

struct StatsComponent {
    int STR, DEX, CON;

    StatsComponent() = default;
    StatsComponent(const int& str, const int& dex, const int& con):
        STR(str), DEX(dex), CON(con)
    {};
};

struct NameComponent {
    std::string name, name_plr, description;

    NameComponent() = default;
    NameComponent(const std::string& name, const std::string& name_plr, const std::string& description):
        name(name), name_plr(name_plr), description(description) {};
    
};

#endif // COMPONENTS_HPP