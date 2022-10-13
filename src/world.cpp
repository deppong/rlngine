#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width)
{
    for (int i = 0; i < zones.size(); i++) {
        zones[i].m_width = world_w;
        zones[i].m_height = world_h;
    }
};

World::~World() {};

void World::load_zone(int zone_index, Atlas &a) {
    for (int y = 0; y < zones[zone_index].m_height; y++) {
        for (int x = 0; x < zones[zone_index].m_width; x++) {
            entt::entity e = zones[zone_index].m_registry.create();
            zones[zone_index].m_registry.emplace<TransformComponent>(e, x, y);
            zones[zone_index].m_registry.emplace<RenderComponent>(e, '.', COLOR_GRAY, COLOR_BLACK);
            zones[zone_index].m_registry.emplace<DecorativeComponent>(e);
            // m_registry.emplace<NameComponent>(e, "wall", "walls", "A solid slab of stone.");
        }
    }

}
