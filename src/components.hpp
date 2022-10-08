#pragma once
#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <stdint.h>
#include <string>

struct NameComponent {
    std::string name, name_plr, description;

    NameComponent() = default;
    NameComponent(const std::string& name, const std::string& name_plr, const std::string& description):
        name(name), name_plr(name_plr), description(description) {};
    
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
    RenderComponent(const int& chr, const uint32_t& color, const uint32_t& bg_color):
        tile(chr), color(color), bg_color(bg_color){};
};

struct DecorativeComponent {
};

struct PhysicsComponent {
    int vel_x, vel_y;

    PhysicsComponent() = default;
    PhysicsComponent(const int& vel_x, const int& vel_y):
        vel_x(vel_x), vel_y(vel_y) {};
    PhysicsComponent(const int& vel_x, const int& vel_y, const bool& inControl):
        vel_x(vel_x), vel_y(vel_y) {};
};

struct ControllableComponent {
    bool inControl;

    ControllableComponent() = default;
    ControllableComponent(const bool& inControl):
        inControl(inControl)
    {};
};

struct StatsComponent {
    int STR, DEX, CON;

    StatsComponent() = default;
    StatsComponent(const int& str, const int& dex, const int& con):
        STR(str), DEX(dex), CON(con)
    {};
};

#endif // COMPONENTS_HPP