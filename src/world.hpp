#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "zone.hpp"

class World {
    public:
        World(int width, int height, int tile_width);
        ~World();

        int world_w, world_h;

        // should be a list
        Zone zone;

    private:
};

#endif // WORLD_HPP