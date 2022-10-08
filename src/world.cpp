#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    zone(width/tile_width, height/tile_width)
{
    zone.fill_zone_walls();
};

World::~World() {};