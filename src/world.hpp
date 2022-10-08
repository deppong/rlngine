#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "entt.hpp"
#include "components.hpp"

class World {
    public:
        World(int width, int height, int tile_width);
        ~World();

        entt::registry m_registry;

        int world_w, world_h;

    private:
};

#endif // WORLD_HPP