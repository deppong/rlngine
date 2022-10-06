#ifndef WORLD_HPP
#define WORLD_HPP

#include "entt.hpp"
#include "components.hpp"

class World {
    public:
        World(int width, int height, int tex_width);
        ~World();

        entt::registry m_registry;

    private:
};

#endif