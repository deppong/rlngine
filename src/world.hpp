#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "zone.hpp"
#include "entity_factory.hpp"
#include <random>

struct world_coord {
    int x, y; 
};

class World {
    public:
        World(int width, int height, int tile_width);
        ~World();

        int world_w, world_h;

        void update_physics();

        bool new_turn;

        // this is the area around the player that will all be processed
        // together. The actual world should be a map of positions and
        // zones.
        std::array<Zone, 9> zones;
        std::map<world_coord, Zone> zone_map;

        // map gen?
        // 

        // old 
        void construct_zone(int zone_index);
        void load_zone(int zone_index);
        void reload_world();

        EntityFactory factory;
    private:
};

#endif // WORLD_HPP
