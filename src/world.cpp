#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    factory()
{
    for (int i = 0; i < zones.size(); i++) {
        zones[i].m_width = world_w;
        zones[i].m_height = world_h;
    }

    factory.load_objects("../../objects/objects.json");
    std::cout << "loaded objects" << std::endl;
};

World::~World() {};

void World::load_zone(int zone_index) {
    srand(time(0));

    for (int i = 0; i < zones[zone_index].m_height * zones[zone_index].m_width; i++) {
        if(!factory.add_object("stone_wall", zones[zone_index].m_registry)) {
            std::cerr << "failed to add object stone_wall to registry" << std::endl;
        }
    }

    auto view = zones[zone_index].m_registry.view<TransformComponent, DecorativeComponent>();
    for (auto entity : view) {
        auto &transform = view.get<TransformComponent>(entity);

        transform.x = rand() % zones[zone_index].m_width;
        transform.y = rand() % zones[zone_index].m_width;
    }


}
