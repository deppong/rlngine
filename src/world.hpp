#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "zone.hpp"
#include "entity_factory.hpp"

class World {
    public:
        World(int width, int height, int tile_width);
        ~World();

        int world_w, world_h;

        void update_physics();

        bool new_turn;

        // should be a list or array 
        std::array<Zone, 9> zones;

        // map gen?
        void load_zone(int zone_index);

        EntityFactory factory;
    private:
};

#endif // WORLD_HPP