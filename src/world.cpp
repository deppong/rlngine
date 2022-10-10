#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width)
{
    for (int i = 0; i < Zones.size(); i++) {
        Zones[i].m_width = world_w;
        Zones[i].m_height = world_h;
    }
};

World::~World() {};