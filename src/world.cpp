#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    new_turn(false),
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

void World::update_physics() {

    zones[4].update_physics();

    // get player
    auto view = zones[4].m_registry.view<ControllableComponent>();
    entt::entity player;
    for (auto entity : view) {
        auto controllable = view.get<ControllableComponent>(entity);
        if (controllable.inControl) {
            player = entity;
            break;
        }
    }

    // did the player exit the current zone?

}

void World::load_zone(int zone_index) {

    for (int y = 0; y < zones[zone_index].m_height; y++) {
        for (int x = 0; x < zones[zone_index].m_width; x++) {
            auto entity = factory.add_object("stone_wall", zones[zone_index].m_registry);
            auto &transform = zones[zone_index].m_registry.get<TransformComponent>(entity);
            transform.x = x;
            transform.y = y;
        }
    }

    zones[zone_index].make_room(10, 10, 20, 20);

}
