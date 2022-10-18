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

    /**
     * if we shift north, 
     * 0 = 3, 1 = 4, 2 = 5,
     * 3 = 6, 4 = 7, 5 = 8
     * 6=new, 7=new, 8=new
     *
     * or:
     * if (i > 5) {zones[i] = zone();}
     * else {zones[i] = zones[i+3];}
     *
     * 0 1 2
     * 3 4 5  
     * 6 7 8  
    */
    // did the player exit the current zone?
    auto transform = zones[4].m_registry.get<TransformComponent>(player);
    // WEST 
    if (transform.x < 0) {
        
    // NORTH
    } else if (transform.y < 0) {

    // EAST
    } else if (transform.x > zones[4].m_width) {

    // SOUTH
    } else if (transform.y > zones[4].m_height) {

    }
}

void World::construct_zone(int zone_index) {

    // TODO: This entire function should really be local to the zone once proper
    // world gen is actually done. This could be mocked up pretty soon!
    for (int y = 0; y < zones[zone_index].m_height; y++) {
        for (int x = 0; x < zones[zone_index].m_width; x++) {
            auto entity = factory.add_object("stone_wall", zones[zone_index].m_registry);
            auto &transform = zones[zone_index].m_registry.get<TransformComponent>(entity);
            transform.x = x;
            transform.y = y;
        }
    }

    zones[zone_index].make_room(10, 10, 20, 20);
    zones[zone_index].make_room(30, 15, 1, 8);

}
