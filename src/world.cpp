#include "world.hpp"

World::World(int width, int height, int tile_width):
    world_w(width/tile_width),
    world_h(height/tile_width),
    new_turn(false),
    current_zone(4),
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

    zones[current_zone].update_physics();

    // get player
    auto view = zones[current_zone].m_registry.view<ControllableComponent>();
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
    auto &transform = zones[current_zone].m_registry.get<TransformComponent>(player);
    // WEST 
    if (transform.x < 0) {
        std::cout << "Exited west" << std::endl;
        transform.x = world_w;
 
        zones[current_zone].m_registry.destroy(player);
        current_zone--;
        factory.add_object("player", zones[current_zone].m_registry);
    // NORTH
    } else if (transform.y < 0) {
        std::cout << "Exited north" << std::endl;

        transform.y = world_h - 1;
 
        zones[current_zone].m_registry.destroy(player);
        current_zone-=3;
        factory.add_object("player", zones[current_zone].m_registry);

    // EAST
    } else if (transform.x > zones[current_zone].m_width) {
        std::cout << "Exited east" << std::endl;
        transform.x = 0;
 
        zones[current_zone].m_registry.destroy(player);
        current_zone++;
        factory.add_object("player", zones[current_zone].m_registry);

    // SOUTH
    } else if (transform.y > zones[current_zone].m_height) {
        std::cout << "Exited south" << std::endl;

        transform.y = 0;

        zones[current_zone].m_registry.destroy(player);
        current_zone+=3;
        factory.add_object("player", zones[current_zone].m_registry);
    }
}

void World::construct_zone(int zone_index) {
    int zone_h = zones[zone_index].m_height;
    int zone_w = zones[zone_index].m_width;

    std::mt19937 gen(zone_index);
    std::uniform_int_distribution<> distr(0, 100);

    // TODO: This entire function should really be local to the zone once proper
    // world gen is actually done. This could be mocked up pretty soon!
    for (int y = 0; y < zone_h; y++) {
        for (int x = 0; x < zone_w; x++) {
            entt::entity entity;

            int n = distr(gen);
            if (n > 0 && n <= 25) {
                entity = factory.add_object("stone_wall", zones[zone_index].m_registry);
            } else if (n > 25 && n <= 40) {
                entity = factory.add_object("dirt_wall", zones[zone_index].m_registry);
            } else {
                entity = entt::null;
            }

            // switch(distr(gen)) {
            //     case 0: entity = factory.add_object("stone_wall", zones[zone_index].m_registry); break;
            //     case 1: entity = factory.add_object("dirt_wall", zones[zone_index].m_registry); break;
            //     case 2: entity = entt::null; break;
            // }

            if (entity != entt::null) {
                auto &transform = zones[zone_index].m_registry.get<TransformComponent>(entity);
                transform.x = x;
                transform.y = y;
            }
        }
    }

    zones[zone_index].make_room(10, 10, 20, 20);
}
