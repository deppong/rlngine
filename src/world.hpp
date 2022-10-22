#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "zone.hpp"
#include "entity_factory.hpp"
#include <random>

static const int MAX_WORLD_WIDTH = 256;

struct vec2 {
    int x, y;
    vec2() = default;
    vec2(int x, int y) : x(x), y(y) {};
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
        int current_zone;

        vec2 world_coords;
        std::map<int, Zone*> zone_map;

        entt::registry& current_registry();
        Zone& get_zone(int x, int y);
        bool zone_exists(int x, int y);

        void copyEntity(entt::entity dst, entt::entity source, entt::registry &curr, entt::registry &dest);

        // map gen?
        // 

        // old 
        void construct_zone(int x, int y);
        void load_zone(int zone_index);
        void reload_world();

        EntityFactory factory;
    private:
};

#endif // WORLD_HPP
